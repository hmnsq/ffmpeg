/*
 * AVOptions
 * Copyright (c) 2005 Michael Niedermayer <michaelni@gmx.at>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * AVOptions
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#include "avutil.h"
#include "avassert.h"
#include "avstring.h"
#include "channel_layout.h"
#include "dict.h"
#include "eval.h"
#include "log.h"
#include "mem.h"
#include "parseutils.h"
#include "pixdesc.h"
#include "mathematics.h"
#include "opt.h"
#include "samplefmt.h"
#include "bprint.h"

#include <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

const AVOption *av_opt_next(const void *obj, const AVOption *last)
{
    const AVClass *class;
    もし (!obj)
        戻る NULL;
    class = *(const AVClass**)obj;
    もし (!last && class && class->option && class->option[0].name)
        戻る class->option;
    もし (last && last[1].name)
        戻る ++last;
    戻る NULL;
}

static const struct {
    size_t      size;
    const char *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { sizeof(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { sizeof(整数),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { sizeof(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { sizeof(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { sizeof(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { sizeof(double),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { sizeof(float),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { sizeof(char *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { sizeof(AVRational),     "<rational>" },
    [AV_OPT_TYPE_BINARY]        = { sizeof(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { sizeof(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { sizeof(整数[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { sizeof(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { sizeof(enum AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { sizeof(enum AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { sizeof(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { sizeof(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { sizeof(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { sizeof(整数),            "<boolean>" },
};

// option is plain old data
static 整数 opt_is_pod(enum AVOptionType type)
{
    switch (type) {
    case AV_OPT_TYPE_FLAGS:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_DOUBLE:
    case AV_OPT_TYPE_FLOAT:
    case AV_OPT_TYPE_RATIONAL:
    case AV_OPT_TYPE_UINT64:
    case AV_OPT_TYPE_IMAGE_SIZE:
    case AV_OPT_TYPE_PIXEL_FMT:
    case AV_OPT_TYPE_SAMPLE_FMT:
    case AV_OPT_TYPE_VIDEO_RATE:
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_COLOR:
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_UINT:
        戻る 1;
    }
    戻る 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    戻る (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    戻る (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    戻る (unsigned *)((const void * const *)parray + 1);
}

static void opt_free_elem(enum AVOptionType type, void *ptr)
{
    switch (TYPE_BASE(type)) {
    case AV_OPT_TYPE_STRING:
    case AV_OPT_TYPE_BINARY:
        av_freep(ptr);
        break;

    case AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        break;

    case AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        break;

    default:
        break;
    }
}

static void opt_free_array(const AVOption *o, void *parray, unsigned *count)
{
    ために (unsigned i = 0; i < *count; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(void **)parray, i));

    av_freep(parray);
    *count = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
static 整数 opt_set_init(void *obj, const char *name, 整数 search_flags,
                        整数 require_type,
                        void **ptgt, const AVOption **po, void **pdst)
{
    void *logctx;
    const AVOption *o;
    void *tgt;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &tgt);
    もし (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        戻る AVERROR_OPTION_NOT_FOUND;

    もし (o->flags & AV_OPT_FLAG_READONLY)
        戻る AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    もし (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        戻る AVERROR(EINVAL);
    }

    もし (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        もし (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        もし (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            もし (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        もし (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            戻る AVERROR(EINVAL);
        }
    }

    もし (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    もし (po)
        *po   = o;
    もし (ptgt)
        *ptgt = tgt;
    もし (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    戻る 0;
}

static AVRational double_to_rational(double d)
{
     AVRational r = av_d2q(d, 1 << 24);
     もし ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     戻る r;
}

static 整数 read_number(const AVOption *o, const void *dst, double *num, 整数 *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    case AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned 整数*)dst;
        戻る 0;
    case AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(enum AVPixelFormat *)dst;
        戻る 0;
    case AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(enum AVSampleFormat *)dst;
        戻る 0;
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_INT:
        *intnum = *(整数 *)dst;
        戻る 0;
    case AV_OPT_TYPE_UINT:
        *intnum = *(unsigned 整数 *)dst;
        戻る 0;
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        戻る 0;
    case AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        戻る 0;
    case AV_OPT_TYPE_DOUBLE:
        *num = *(double *)dst;
        戻る 0;
    case AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        戻る 0;
    case AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        戻る 0;
    }
    戻る AVERROR(EINVAL);
}

static 整数 write_number(void *obj, const AVOption *o, void *dst,
                        double num, 整数 den, int64_t intnum,
                        整数 ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const enum AVOptionType type = TYPE_BASE(o->type);

    もし (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        戻る AVERROR(ERANGE);
    }
    もし (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        double d = num*intnum/den;
        もし (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            戻る AVERROR(ERANGE);
        }
    }

    もし (!dst)
        戻る 0;

    switch (type) {
    case AV_OPT_TYPE_PIXEL_FMT:
        *(enum AVPixelFormat *)dst = llrint(num / den) * intnum;
        break;
    case AV_OPT_TYPE_SAMPLE_FMT:
        *(enum AVSampleFormat *)dst = llrint(num / den) * intnum;
        break;
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_FLAGS:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_UINT:
        *(整数 *)dst = llrint(num / den) * intnum;
        break;
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_INT64:{
        double d = num / den;
        もし (intnum == 1 && d == (double)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } 否则
            *(int64_t *)dst = llrint(d) * intnum;
        break;}
    case AV_OPT_TYPE_UINT64:{
        double d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        もし (intnum == 1 && d == (double)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } 否则 もし (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } 否则 {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        break;}
    case AV_OPT_TYPE_FLOAT:
        *(float *)dst = num * intnum / den;
        break;
    case AV_OPT_TYPE_DOUBLE:
        *(double    *)dst = num * intnum / den;
        break;
    case AV_OPT_TYPE_RATIONAL:
    case AV_OPT_TYPE_VIDEO_RATE:
        もし ((整数) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        否则
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        break;
    default:
        戻る AVERROR(EINVAL);
    }
    戻る 0;
}

static 整数 hexchar2int(char c) {
    もし (c >= '0' && c <= '9')
        戻る c - '0';
    もし (c >= 'a' && c <= 'f')
        戻る c - 'a' + 10;
    もし (c >= 'A' && c <= 'F')
        戻る c - 'A' + 10;
    戻る -1;
}

static 整数 set_string_binary(void *obj, const AVOption *o, const char *val, uint8_t **dst)
{
    整数 *lendst;
    uint8_t *bin, *ptr;
    整数 len;

    もし (dst) {
        lendst = (整数 *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    もし (!val || !(len = strlen(val)))
        戻る 0;

    もし (len & 1)
        戻る AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    もし (!ptr)
        戻る AVERROR(ENOMEM);
    ながら (*val) {
        整数 a = hexchar2int(*val++);
        整数 b = hexchar2int(*val++);
        もし (a < 0 || b < 0) {
            av_free(bin);
            戻る AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    もし (dst) {
        *dst    = bin;
        *lendst = len;
    } 否则 {
        av_free(bin);
    }

    戻る 0;
}

static 整数 set_string(void *obj, const AVOption *o, const char *val, uint8_t **dst)
{
    もし (!dst)
        戻る 0;
    av_freep(dst);
    もし (!val)
        戻る 0;
    *dst = av_strdup(val);
    戻る *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

static 整数 set_string_number(void *obj, void *target_obj, const AVOption *o, const char *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const enum AVOptionType type = TYPE_BASE(o->type);
    整数 ret = 0;

    もし (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        整数 num, den;
        char c;
        もし (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            もし ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                戻る ret;
            ret = 0;
        }
    }

    ために (;;) {
        整数 i = 0;
        char buf[256];
        整数 cmd = 0;
        double d;
        int64_t intnum = 1;

        もし (type == AV_OPT_TYPE_FLAGS) {
            もし (*val == '+' || *val == '-')
                cmd = *(val++);
            ために (; i < sizeof(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            整数 res;
            整数 ci = 0;
            double const_values[64];
            const char * const_names[64];
            整数 search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            const AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            もし (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                もし (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } 否则 {
                もし (o->unit) {
                    ために (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        もし (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            もし (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                戻る AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_values[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_values[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_values[ci++] = o->max;
                const_names [ci  ] = "min";
                const_values[ci++] = o->min;
                const_names [ci  ] = "none";
                const_values[ci++] = 0;
                const_names [ci  ] = "all";
                const_values[ci++] = ~0;
                const_names [ci] = NULL;
                const_values[ci] = 0;

                res = av_expr_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_values, NULL, NULL, NULL, NULL, NULL, 0, obj);
                もし (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    戻る res;
                }
            }
        }
        もし (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned 整数*)dst;
            もし (cmd == '+')
                d = intnum | (int64_t)d;
            否则 もし (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        もし ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            戻る ret;
        val += i;
        もし (!i || !*val)
            戻る 0;
    }
}

static 整数 set_string_image_size(void *obj, const AVOption *o, const char *val, 整数 *dst)
{
    void *logctx = dst ? obj : NULL;
    整数 tmp[2];
    整数 ret;

    もし (!val || !strcmp(val, "none")) {
        もし (dst) {
        dst[0] =
        dst[1] = 0;
        }
        戻る 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    もし (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        戻る ret;
    }
    もし (dst)
        memcpy(dst, tmp, sizeof(tmp));
    戻る ret;
}

static 整数 set_string_video_rate(void *obj, const AVOption *o, const char *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    整数 ret = av_parse_video_rate(&tmp, val);
    もし (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    もし (dst)
        *dst = tmp;
    戻る ret;
}

static 整数 set_string_color(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    整数 ret;

    もし (!val) {
        戻る 0;
    } 否则 {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        もし (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            戻る ret;
        }
        もし (dst)
            memcpy(dst, tmp, sizeof(tmp));
        戻る ret;
    }
    戻る 0;
}

static const char *get_bool_name(整数 val)
{
    もし (val < 0)
        戻る "auto";
    戻る val ? "true" : "false";
}

static 整数 set_string_bool(void *obj, const AVOption *o, const char *val, 整数 *dst)
{
    void *logctx = dst ? obj : NULL;
    整数 n;

    もし (!val)
        戻る 0;

    もし (!strcmp(val, "auto")) {
        n = -1;
    } 否则 もし (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } 否则 もし (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } 否则 {
        char *end = NULL;
        n = strtol(val, &end, 10);
        もし (val + strlen(val) != end)
            goto fail;
    }

    もし (n < o->min || n > o->max)
        goto fail;

    もし (dst)
    *dst = n;
    戻る 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    戻る AVERROR(EINVAL);
}

static 整数 set_string_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst,
                          整数 fmt_nb, 整数 ((*get_fmt)(const char *)), const char *desc,
                          enum AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    整数 fmt, min, max;

    もし (!val || !strcmp(val, "none")) {
        fmt = -1;
    } 否则 {
        fmt = get_fmt(val);
        もし (fmt == -1) {
            char *tail;
            fmt = strtol(val, &tail, 0);
            もし (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                戻る AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    もし(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    もし (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        戻る AVERROR(ERANGE);
    }

    もし (dst)
    switch (type) {
    case AV_OPT_TYPE_PIXEL_FMT:  *(enum AVPixelFormat *)dst = fmt; break;
    case AV_OPT_TYPE_SAMPLE_FMT: *(enum AVSampleFormat*)dst = fmt; break;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    戻る 0;
}

static 整数 get_pix_fmt(const char *name)
{
    戻る av_get_pix_fmt(name);
}

static 整数 set_string_pixel_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    戻る set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static 整数 get_sample_fmt(const char *name)
{
    戻る av_get_sample_fmt(name);
}

static 整数 set_string_sample_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    戻る set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static 整数 set_string_dict(void *obj, const AVOption *o, const char *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    もし (val) {
        整数 ret = av_dict_parse_string(&options, val, "=", ":", 0);
        もし (ret < 0) {
            av_dict_free(&options);
            戻る ret;
        }
    }

    もし (!dst) {
        av_dict_free(&options);
        戻る 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    戻る 0;
}

static 整数 set_string_channel_layout(void *obj, const AVOption *o,
                                     const char *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    整数 ret;
    もし (dst)
    av_channel_layout_uninit(channel_layout);
    否则
        channel_layout = &tmp;
    もし (!val)
        戻る 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    もし (ret < 0)
        戻る ret;
    もし (!dst)
        av_channel_layout_uninit(channel_layout);
    戻る 0;
}

static 整数 opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const char *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const enum AVOptionType type = TYPE_BASE(o->type);
    整数 ret;

    もし (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        戻る AVERROR(EINVAL);

    switch (type) {
    case AV_OPT_TYPE_BOOL:
        戻る set_string_bool(obj, o, val, dst);
    case AV_OPT_TYPE_STRING:
        戻る set_string(obj, o, val, dst);
    case AV_OPT_TYPE_BINARY:
        戻る set_string_binary(obj, o, val, dst);
    case AV_OPT_TYPE_FLAGS:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_UINT:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
    case AV_OPT_TYPE_FLOAT:
    case AV_OPT_TYPE_DOUBLE:
    case AV_OPT_TYPE_RATIONAL:
        戻る set_string_number(obj, target_obj, o, val, dst);
    case AV_OPT_TYPE_IMAGE_SIZE:
        戻る set_string_image_size(obj, o, val, dst);
    case AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        もし (ret < 0)
            戻る ret;
        戻る write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    case AV_OPT_TYPE_PIXEL_FMT:
        戻る set_string_pixel_fmt(obj, o, val, dst);
    case AV_OPT_TYPE_SAMPLE_FMT:
        戻る set_string_sample_fmt(obj, o, val, dst);
    case AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            もし (val) {
                もし ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    戻る ret;
                }
            }
            もし (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                戻る AVERROR(ERANGE);
            }
            もし (dst)
            *(int64_t *)dst = usecs;
            戻る 0;
        }
    case AV_OPT_TYPE_COLOR:
        戻る set_string_color(obj, o, val, dst);
    case AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        もし (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        戻る ret;
    case AV_OPT_TYPE_DICT:
        戻る set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    戻る AVERROR(EINVAL);
}

static 整数 opt_set_array(void *obj, void *target_obj, const AVOption *o,
                         const char *val, void *dst)
{
    const AVOptionArrayDef *arr = o->default_val.arr;
    const size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    const uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = NULL;

    void      *logctx = dst ? obj : NULL;
    void       *elems = NULL;
    unsigned nb_elems = 0;
    整数 ret;

    もし (val && *val) {
        str = av_malloc(strlen(val) + 1);
        もし (!str)
            戻る AVERROR(ENOMEM);
    }

    // split and unescape the string
    ながら (val && *val) {
        uint8_t *p = str;
        void *tmp;

        もし (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        ために (; *val; val++, p++) {
            もし (*val == '\\' && val[1])
                val++;
            否则 もし (*val == sep) {
                val++;
                break;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        もし (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        もし (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    もし (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    もし (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    もし (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } 否则
        opt_free_array(o, &elems, &nb_elems);

    戻る 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    戻る ret;
}

整数 av_opt_set(void *obj, const char *name, const char *val, 整数 search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    整数 ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    もし (ret < 0)
        戻る ret;

    戻る ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
整数 av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const char *val, vartype *name ## _out)        \
{                                                                       \
    もし (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        戻る AVERROR(EINVAL);                                         \
    戻る set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    整数)
OPT_EVAL_NUMBER(整数,    AV_OPT_TYPE_INT,      整数)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(float,  AV_OPT_TYPE_FLOAT,    float)
OPT_EVAL_NUMBER(double, AV_OPT_TYPE_DOUBLE,   double)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

static 整数 set_number(void *obj, const char *name, double num, 整数 den, int64_t intnum,
                      整数 search_flags, 整数 require_type)
{
    void *dst;
    const AVOption *o;
    整数 ret;

    ret = opt_set_init(obj, name, search_flags, require_type, NULL, &o, &dst);
    もし (ret < 0)
        戻る ret;
    もし (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    戻る ret;
}

整数 av_opt_set_int(void *obj, const char *name, int64_t val, 整数 search_flags)
{
    戻る set_number(obj, name, 1, 1, val, search_flags, 0);
}

整数 av_opt_set_double(void *obj, const char *name, double val, 整数 search_flags)
{
    戻る set_number(obj, name, val, 1, 1, search_flags, 0);
}

整数 av_opt_set_q(void *obj, const char *name, AVRational val, 整数 search_flags)
{
    戻る set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

整数 av_opt_set_bin(void *obj, const char *name, const uint8_t *val, 整数 len, 整数 search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    整数 *lendst;
    整数 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    もし (ret < 0)
        戻る ret;

    もし (dst) {
    ptr = len ? av_malloc(len) : NULL;
    もし (len && !ptr)
        戻る AVERROR(ENOMEM);

    lendst = (整数 *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    もし (len)
        memcpy(ptr, val, len);
    }

    戻る 0;
}

整数 av_opt_set_image_size(void *obj, const char *name, 整数 w, 整数 h, 整数 search_flags)
{
    const AVOption *o;
    void *logctx;
    整数 *dst;
    整数 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    もし (ret < 0)
        戻る ret;

    logctx = dst ? obj : NULL;

    もし (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        戻る AVERROR(EINVAL);
    }

    もし (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    戻る 0;
}

整数 av_opt_set_video_rate(void *obj, const char *name, AVRational val, 整数 search_flags)
{
    戻る set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static 整数 set_format(void *obj, const char *name, 整数 fmt, 整数 search_flags,
                      enum AVOptionType type, const char *desc, 整数 nb_fmts)
{
    const AVOption *o;
    void *logctx;
    整数 *dst;
    整数 min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    もし (ret < 0)
        戻る ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    もし (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        戻る AVERROR(ERANGE);
    }
    もし (dst)
    *dst = fmt;
    戻る 0;
}

整数 av_opt_set_pixel_fmt(void *obj, const char *name, enum AVPixelFormat fmt, 整数 search_flags)
{
    戻る set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

整数 av_opt_set_sample_fmt(void *obj, const char *name, enum AVSampleFormat fmt, 整数 search_flags)
{
    戻る set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

整数 av_opt_set_dict_val(void *obj, const char *name, const AVDictionary *val,
                        整数 search_flags)
{
    AVDictionary **dst;
    整数 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    もし (ret < 0)
        戻る ret;

    もし (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    戻る ret;
}

整数 av_opt_set_chlayout(void *obj, const char *name,
                        const AVChannelLayout *channel_layout,
                        整数 search_flags)
{
    AVChannelLayout *dst;
    整数 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    もし (ret < 0)
        戻る ret;

    もし (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    戻る ret;
}

static void format_duration(char *buf, size_t size, int64_t d)
{
    char *e;

    av_assert0(size >= 25);
    もし (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    もし (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    否则 もし (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    否则 もし (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (整数)((d / 60000000) % 60),
                 (整数)((d / 1000000) % 60),
                 (整数)(d % 1000000));
    否则 もし (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (整数)(d / 60000000),
                 (整数)((d / 1000000) % 60),
                 (整数)(d % 1000000));
    否则
        snprintf(buf, size, "%d.%06d",
                 (整数)(d / 1000000),
                 (整数)(d % 1000000));
    e = buf + strlen(buf);
    ながら (e > buf && e[-1] == '0')
        *(--e) = 0;
    もし (e > buf && e[-1] == '.')
        *(--e) = 0;
}

static 整数 opt_get_elem(const AVOption *o, uint8_t **pbuf, size_t buf_len,
                        const void *dst, 整数 search_flags)
{
    整数 ret;

    switch (TYPE_BASE(o->type)) {
    case AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(整数 *)dst));
        break;
    case AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(整数 *)dst);
        break;
    case AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(整数 *)dst);
        break;
    case AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        break;
    case AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        break;
    case AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        break;
    case AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(float *)dst);
        break;
    case AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(double *)dst);
        break;
    case AV_OPT_TYPE_VIDEO_RATE:
    case AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->num, ((AVRational *)dst)->den);
        break;
    case AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        break;
    case AV_OPT_TYPE_STRING:
        もし (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } 否则 もし (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            戻る 0;
        } 否则 {
            *pbuf = av_strdup("");
        }
        戻る *pbuf ? 0 : AVERROR(ENOMEM);
    case AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        整数 len;

        もし (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            戻る 0;
        }
        len = *(整数 *)(((uint8_t *)dst) + sizeof(uint8_t *));
        もし ((uint64_t)len * 2 + 1 > INT_MAX)
            戻る AVERROR(EINVAL);
        もし (!(*pbuf = av_malloc(len * 2 + 1)))
            戻る AVERROR(ENOMEM);
        もし (!len) {
            *pbuf[0] = '\0';
            戻る 0;
        }
        bin = *(uint8_t **)dst;
        ために (整数 i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        戻る 0;
    }
    case AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((整数 *)dst)[0], ((整数 *)dst)[1]);
        break;
    case AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (char *)av_x_if_null(av_get_pix_fmt_name(*(enum AVPixelFormat *)dst), "none"));
        break;
    case AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (char *)av_x_if_null(av_get_sample_fmt_name(*(enum AVSampleFormat *)dst), "none"));
        break;
    case AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        break;
    }
    case AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (整数)((uint8_t *)dst)[0], (整数)((uint8_t *)dst)[1],
                       (整数)((uint8_t *)dst)[2], (整数)((uint8_t *)dst)[3]);
        break;
    case AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        break;
    case AV_OPT_TYPE_DICT:
        もし (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            戻る 0;
        }
        戻る av_dict_get_string(*(AVDictionary **)dst, (char **)pbuf, '=', ':');
    default:
        戻る AVERROR(EINVAL);
    }

    戻る ret;
}

static 整数 opt_get_array(const AVOption *o, void *dst, uint8_t **out_val)
{
    const unsigned count = *opt_array_pcount(dst);
    const uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = NULL;
    size_t   str_len = 0;
    整数 ret;

    *out_val = NULL;

    ために (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, sizeof(buf),
                           opt_array_pelem(o, *(void **)dst, i), 0);
        もし (ret < 0)
            goto fail;

        out_len = strlen(out);
        もし (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        もし (ret < 0)
            goto fail;

        // add separator if needed
        もし (i)
            str[str_len++] = sep;

        // escape the element
        ために (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            もし (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        もし (out != buf)
            av_freep(&out);
        もし (ret < 0) {
            av_freep(&str);
            戻る ret;
        }
    }

    *out_val = str;

    戻る 0;
}

整数 av_opt_get(void *obj, const char *name, 整数 search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    整数 ret;

    もし (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        戻る AVERROR_OPTION_NOT_FOUND;

    もし (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    もし (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        もし (ret < 0)
            戻る ret;
        もし (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            もし (!*out_val)
               戻る AVERROR(ENOMEM);
        }
        戻る 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, sizeof(buf), dst, search_flags);
    もし (ret < 0)
        戻る ret;
    もし (out != buf) {
        *out_val = out;
        戻る 0;
    }

    もし (ret >= sizeof(buf))
        戻る AVERROR(EINVAL);
    *out_val = av_strdup(out);
    戻る *out_val ? 0 : AVERROR(ENOMEM);
}

static 整数 get_number(void *obj, const char *name, double *num, 整数 *den, int64_t *intnum,
                      整数 search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        戻る AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    戻る read_number(o, dst, num, den, intnum);
}

整数 av_opt_get_int(void *obj, const char *name, 整数 search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    double num = 1;
    整数 ret, den = 1;

    もし ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        戻る ret;
    もし (num == den)
        *out_val = intnum;
    否则
        *out_val = num * intnum / den;
    戻る 0;
}

整数 av_opt_get_double(void *obj, const char *name, 整数 search_flags, double *out_val)
{
    int64_t intnum = 1;
    double num = 1;
    整数 ret, den = 1;

    もし ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        戻る ret;
    *out_val = num * intnum / den;
    戻る 0;
}

整数 av_opt_get_q(void *obj, const char *name, 整数 search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    double num = 1;
    整数 ret, den = 1;

    もし ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        戻る ret;

    もし (num == 1.0 && (整数)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    否则
        *out_val = double_to_rational(num*intnum/den);
    戻る 0;
}

整数 av_opt_get_image_size(void *obj, const char *name, 整数 search_flags, 整数 *w_out, 整数 *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        戻る AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    もし (w_out) *w_out = *(整数 *)dst;
    もし (h_out) *h_out = *((整数 *)dst+1);
    戻る 0;
}

整数 av_opt_get_video_rate(void *obj, const char *name, 整数 search_flags, AVRational *out_val)
{
    戻る av_opt_get_q(obj, name, search_flags, out_val);
}

static 整数 get_format(void *obj, const char *name, 整数 search_flags, void *out_fmt,
                      enum AVOptionType type, const char *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        戻る AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    もし (type == AV_OPT_TYPE_PIXEL_FMT)
        *(enum AVPixelFormat *)out_fmt = *(enum AVPixelFormat *)dst;
    否则
        *(enum AVSampleFormat*)out_fmt = *(enum AVSampleFormat*)dst;

    戻る 0;
}

整数 av_opt_get_pixel_fmt(void *obj, const char *name, 整数 search_flags, enum AVPixelFormat *out_fmt)
{
    戻る get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

整数 av_opt_get_sample_fmt(void *obj, const char *name, 整数 search_flags, enum AVSampleFormat *out_fmt)
{
    戻る get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

整数 av_opt_get_chlayout(void *obj, const char *name, 整数 search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        戻る AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    戻る av_channel_layout_copy(cl, dst);
}

整数 av_opt_get_dict_val(void *obj, const char *name, 整数 search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (o->type != AV_OPT_TYPE_DICT)
        戻る AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    戻る av_dict_copy(out_val, src, 0);
}

整数 av_opt_flag_is_set(void *obj, const char *field_name, const char *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    もし (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        戻る 0;
    戻る res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, 整数 level, int64_t i)
{
    もし (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } 否则 もし (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } 否则 もし (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } 否则 もし (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } 否则 もし (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } 否则 {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, 整数 level, double d)
{
    もし      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } 否则 もし (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } 否则 もし (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } 否则 もし (d == (double)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } 否则 もし (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } 否则 もし (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } 否则 もし (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } 否则 もし (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } 否则 もし (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } 否则 もし (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } 否则 もし (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } 否则 もし (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } 否则 もし (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } 否则 {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const char *get_opt_const_name(void *obj, const char *unit, int64_t value)
{
    const AVOption *opt = NULL;

    もし (!unit)
        戻る NULL;
    ながら ((opt = av_opt_next(obj, opt)))
        もし (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            戻る opt->name;
    戻る NULL;
}

static char *get_opt_flags_string(void *obj, const char *unit, int64_t value)
{
    const AVOption *opt = NULL;
    char flags[512];

    flags[0] = 0;
    もし (!unit)
        戻る NULL;
    ながら ((opt = av_opt_next(obj, opt))) {
        もし (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            もし (flags[0])
                av_strlcatf(flags, sizeof(flags), "+");
            av_strlcatf(flags, sizeof(flags), "%s", opt->name);
        }
    }
    もし (flags[0])
        戻る av_strdup(flags);
    戻る NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     enum AVOptionType parent_type)
{
    const enum AVOptionType type = TYPE_BASE(o->type);

    もし (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    否则 もし (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        もし (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        否则
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    否则
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    もし (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        戻る;
    もし ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        戻る;

    もし (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        もし (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        戻る;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    case AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        break;
    case AV_OPT_TYPE_FLAGS: {
        char *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        もし (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } 否则 {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        break;
    }
    case AV_OPT_TYPE_DURATION: {
        char buf[25];
        format_duration(buf, sizeof(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        break;
    }
    case AV_OPT_TYPE_UINT:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_UINT64:
    case AV_OPT_TYPE_INT64: {
        const char *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        もし (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        否则
            log_int_value(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        break;
    }
    case AV_OPT_TYPE_DOUBLE:
    case AV_OPT_TYPE_FLOAT:
        log_value(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        break;
    case AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.num, q.den); }
        break;
    case AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (char *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        break;
    case AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (char *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        break;
    case AV_OPT_TYPE_COLOR:
    case AV_OPT_TYPE_IMAGE_SIZE:
    case AV_OPT_TYPE_STRING:
    case AV_OPT_TYPE_DICT:
    case AV_OPT_TYPE_VIDEO_RATE:
    case AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        break;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

static void opt_list(void *obj, void *av_log_obj, const char *unit,
                     整数 req_flags, 整数 rej_flags, enum AVOptionType parent_type)
{
    const AVOption *opt = NULL;
    AVOptionRanges *r;
    整数 i;

    ながら ((opt = av_opt_next(obj, opt))) {
        もし (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        もし (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        否则 もし (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        否则 もし (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        否则 もし (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        否则
            av_log(av_log_obj, AV_LOG_INFO, "  %s%-17s ",
                   (opt->flags & AV_OPT_FLAG_FILTERING_PARAM) ? " " : "-",
                   opt->name);

        log_type(av_log_obj, opt, parent_type);

        av_log(av_log_obj, AV_LOG_INFO, "%c%c%c%c%c%c%c%c%c%c%c",
               (opt->flags & AV_OPT_FLAG_ENCODING_PARAM)  ? 'E' : '.',
               (opt->flags & AV_OPT_FLAG_DECODING_PARAM)  ? 'D' : '.',
               (opt->flags & AV_OPT_FLAG_FILTERING_PARAM) ? 'F' : '.',
               (opt->flags & AV_OPT_FLAG_VIDEO_PARAM)     ? 'V' : '.',
               (opt->flags & AV_OPT_FLAG_AUDIO_PARAM)     ? 'A' : '.',
               (opt->flags & AV_OPT_FLAG_SUBTITLE_PARAM)  ? 'S' : '.',
               (opt->flags & AV_OPT_FLAG_EXPORT)          ? 'X' : '.',
               (opt->flags & AV_OPT_FLAG_READONLY)        ? 'R' : '.',
               (opt->flags & AV_OPT_FLAG_BSF_PARAM)       ? 'B' : '.',
               (opt->flags & AV_OPT_FLAG_RUNTIME_PARAM)   ? 'T' : '.',
               (opt->flags & AV_OPT_FLAG_DEPRECATED)      ? 'P' : '.');

        もし (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        もし (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
            switch (opt->type) {
            case AV_OPT_TYPE_INT:
            case AV_OPT_TYPE_UINT:
            case AV_OPT_TYPE_INT64:
            case AV_OPT_TYPE_UINT64:
            case AV_OPT_TYPE_DOUBLE:
            case AV_OPT_TYPE_FLOAT:
            case AV_OPT_TYPE_RATIONAL:
                ために (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_value(av_log_obj, AV_LOG_INFO, r->range[i]->value_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_value(av_log_obj, AV_LOG_INFO, r->range[i]->value_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                break;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        もし (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

整数 av_opt_show2(void *obj, void *av_log_obj, 整数 req_flags, 整数 rej_flags)
{
    もし (!obj)
        戻る -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    戻る 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, 整数 mask, 整数 flags)
{
    const AVOption *opt = NULL;
    ながら ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        もし ((opt->flags & mask) != flags)
            continue;

        もし (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        もし (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const char              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            もし (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            continue;
        }

        switch (opt->type) {
            case AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                break;
            case AV_OPT_TYPE_BOOL:
            case AV_OPT_TYPE_FLAGS:
            case AV_OPT_TYPE_INT:
            case AV_OPT_TYPE_UINT:
            case AV_OPT_TYPE_INT64:
            case AV_OPT_TYPE_UINT64:
            case AV_OPT_TYPE_DURATION:
            case AV_OPT_TYPE_PIXEL_FMT:
            case AV_OPT_TYPE_SAMPLE_FMT:
                write_number(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                break;
            case AV_OPT_TYPE_DOUBLE:
            case AV_OPT_TYPE_FLOAT: {
                double val;
                val = opt->default_val.dbl;
                write_number(s, opt, dst, val, 1, 1, 1);
            }
            break;
            case AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_number(s, opt, dst, 1, val.den, val.num, 1);
            }
            break;
            case AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_BINARY:
                set_string_binary(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                break;
            case AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                break;
        default:
            av_log(s, AV_LOG_DEBUG, "AVOption type %d of option %s not implemented yet\n",
                   opt->type, opt->name);
        }
    }
}

/**
 * Store the value in the field in ctx that is named like key.
 * ctx must be an AVClass context, storing is done using AVOptions.
 *
 * @param buf the string to parse, buf will be updated to point at the
 * separator just after the parsed key/value pair
 * @param key_val_sep a 0-terminated list of characters used to
 * separate key from value
 * @param pairs_sep a 0-terminated list of characters used to separate
 * two pairs from each other
 * @return 0 if the key/value pair has been successfully parsed and
 * set, or a negative value corresponding to an AVERROR code in case
 * of error:
 * AVERROR(EINVAL) if the key/value pair cannot be parsed,
 * the error code issued by av_opt_set() if the key/value pair
 * cannot be set
 */
static 整数 parse_key_value_pair(void *ctx, const char **buf,
                                const char *key_val_sep, const char *pairs_sep)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val;
    整数 ret;

    もし (!key)
        戻る AVERROR(ENOMEM);

    もし (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        もし (!val) {
            av_freep(&key);
            戻る AVERROR(ENOMEM);
        }
    } 否则 {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        戻る AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    もし (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    戻る ret;
}

整数 av_set_options_string(void *ctx, const char *opts,
                          const char *key_val_sep, const char *pairs_sep)
{
    整数 ret, count = 0;

    もし (!opts)
        戻る 0;

    ながら (*opts) {
        もし ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            戻る ret;
        count++;

        もし (*opts)
            opts++;
    }

    戻る count;
}

#define WHITESPACES " \n\t\r"

static 整数 is_key_char(char c)
{
    戻る (unsigned)((c | 32) - 'a') < 26 ||
           (unsigned)(c - '0') < 10 ||
           c == '-' || c == '_' || c == '/' || c == '.';
}

/**
 * Read a key from a string.
 *
 * The key consists of is_key_char characters and must be terminated by a
 * character from the delim string; spaces are ignored.
 *
 * @return  0 for success (even with ellipsis), <0 for failure
 */
static 整数 get_key(const char **ropts, const char *delim, char **rkey)
{
    const char *opts = *ropts;
    const char *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    ながら (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    もし (!*opts || !strchr(delim, *opts))
        戻る AVERROR(EINVAL);
    opts++;
    もし (!(*rkey = av_malloc(key_end - key_start + 1)))
        戻る AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    戻る 0;
}

整数 av_opt_get_key_value(const char **ropts,
                         const char *key_val_sep, const char *pairs_sep,
                         unsigned flags,
                         char **rkey, char **rval)
{
    整数 ret;
    char *key = NULL, *val;
    const char *opts = *ropts;

    もし ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        戻る AVERROR(EINVAL);
    もし (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        戻る AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    戻る 0;
}

整数 av_opt_set_from_string(void *ctx, const char *opts,
                           const char *const *shorthand,
                           const char *key_val_sep, const char *pairs_sep)
{
    整数 ret, count = 0;
    const char *dummy_shorthand = NULL;
    const char *key;

    もし (!opts)
        戻る 0;
    もし (!shorthand)
        shorthand = &dummy_shorthand;

    ながら (*opts) {
        char *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        もし (ret < 0) {
            もし (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            否则
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            戻る ret;
        }
        もし (*opts)
            opts++;
        もし (parsed_key) {
            key = parsed_key;
            ながら (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } 否则 {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        もし ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            もし (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            戻る ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    戻る count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    ながら ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        もし (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        否则
            opt_free_elem(o->type, pitem);
    }
}

整数 av_opt_set_dict2(void *obj, AVDictionary **options, 整数 search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    整数 ret;

    もし (!options)
        戻る 0;

    ながら ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        もし (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        もし (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            戻る ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    戻る 0;
}

整数 av_opt_set_dict(void *obj, AVDictionary **options)
{
    戻る av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const char *name, const char *unit,
                            整数 opt_flags, 整数 search_flags)
{
    戻る av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const char *name, const char *unit,
                             整数 opt_flags, 整数 search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    もし(!obj)
        戻る NULL;

    c= *(AVClass**)obj;

    もし (!c)
        戻る NULL;

    もし (search_flags & AV_OPT_SEARCH_CHILDREN) {
        もし (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            ながら (child = av_opt_child_class_iterate(c, &iter))
                もし (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    戻る o;
        } 否则 {
            void *child = NULL;
            ながら (child = av_opt_child_next(obj, child))
                もし (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    戻る o;
        }
    }

    ながら (o = av_opt_next(obj, o)) {
        もし (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            もし (target_obj) {
                もし (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                否则
                    *target_obj = NULL;
            }
            戻る o;
        }
    }
    戻る NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    もし (c->child_next)
        戻る c->child_next(obj, prev);
    戻る NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    もし (parent->child_class_iterate)
        戻る parent->child_class_iterate(iter);
    戻る NULL;
}

static 整数 opt_copy_elem(void *logctx, enum AVOptionType type,
                         void *dst, const void *src)
{
    もし (type == AV_OPT_TYPE_STRING) {
        const char *src_str = *(const char *const *)src;
        char         **dstp =  (char **)dst;
        もし (*dstp != src_str)
            av_freep(dstp);
        もし (src_str) {
            *dstp = av_strdup(src_str);
            もし (!*dstp)
                戻る AVERROR(ENOMEM);
        }
    } 否则 もし (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        整数 len = *(const 整数 *)(src8 + 1);
        もし (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        もし (len && !*dst8) {
            *(整数 *)(dst8 + 1) = 0;
            戻る AVERROR(ENOMEM);
        }
        *(整数 *)(dst8 + 1) = len;
    } 否则 もし (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } 否则 もし (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        もし (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        戻る av_dict_copy(ddictp, sdict, 0);
    } 否则 もし (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        もし (dlayout != slayout) {
            もし (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            戻る av_channel_layout_copy(dst, src);
        }
    } 否则 もし (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } 否则 {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        戻る AVERROR(EINVAL);
    }

    戻る 0;
}

static 整数 opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    整数 ret;

    もし (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    もし (!dst)
        戻る AVERROR(ENOMEM);

    ために (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        もし (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            戻る ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    戻る 0;
}

整数 av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    整数 ret = 0;

    もし (!src)
        戻る AVERROR(EINVAL);

    c = *(AVClass **)src;
    もし (!c || c != *(AVClass **)dst)
        戻る AVERROR(EINVAL);

    ながら ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        整数 err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        もし (err < 0)
            ret = err;
    }
    戻る ret;
}

整数 av_opt_get_array_size(void *obj, const char *name, 整数 search_flags,
                          unsigned 整数 *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        戻る AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    戻る 0;
}

整数 av_opt_get_array(void *obj, const char *name, 整数 search_flags,
                     unsigned 整数 start_elem, unsigned 整数 nb_elems,
                     enum AVOptionType out_type, void *out_val)
{
    const size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    const AVOption *o;
    void *target_obj;

    const void *parray;
    unsigned array_size;

    整数 ret;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    もし (!o || !target_obj)
        戻る AVERROR_OPTION_NOT_FOUND;
    もし (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        戻る AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    もし (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        戻る AVERROR(EINVAL);

    ために (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        もし (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            もし (ret < 0)
                goto fail;
        } 否则 もし (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, sizeof(buf), src, search_flags);
            もし (ret < 0)
                goto fail;

            もし (out == buf) {
                out = av_strdup(buf);
                もし (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } 否则 もし (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            double     num = 1.0;
            整数        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            もし (ret < 0)
                goto fail;

            switch (out_type) {
            case AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                break;
            case AV_OPT_TYPE_DOUBLE:
                *(double*)dst = num * intnum / den;
                break;
            case AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (整数)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                break;
            default: av_assert0(0);
            }
        } 否则
            戻る AVERROR(ENOSYS);
    }

    戻る 0;
fail:
    ために (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    戻る ret;
}

整数 av_opt_set_array(void *obj, const char *name, 整数 search_flags,
                     unsigned 整数 start_elem, unsigned 整数 nb_elems,
                     enum AVOptionType val_type, const void *val)
{
    const size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    const AVOption *o;
    const AVOptionArrayDef *arr;
    void *target_obj;

    void *parray;
    void *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    整数 ret = 0;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    もし (ret < 0)
        戻る ret;

    もし (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        戻る AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    もし (start_elem > *array_size)
        戻る AVERROR(EINVAL);

    // compute new array size
    もし (!val) {
        もし (*array_size - start_elem < nb_elems)
            戻る AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } 否则 もし (search_flags & AV_OPT_ARRAY_REPLACE) {
        もし (start_elem >= UINT_MAX - nb_elems)
            戻る AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } 否则 {
        もし (nb_elems >= UINT_MAX - *array_size)
            戻る AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    もし (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        戻る AVERROR(EINVAL);

    // desired operation is shrinking the array
    もし (!val) {
        void *array = *(void**)parray;

        ために (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        もし (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            もし (!array)
                戻る AVERROR(ENOMEM);

            *(void**)parray = array;
        } 否则
            av_freep(parray);

        *array_size = new_size;

        戻る 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    もし (!new_elems)
        戻る AVERROR(ENOMEM);

    // convert/validate each new element
    ために (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        double     num = 1.0;
        整数        den = 1;
        int64_t intnum = 1;

        もし (val_type == TYPE_BASE(o->type)) {
            整数 err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            もし (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            もし (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } 否则 もし (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const char **)src, dst);
            もし (ret < 0)
                goto fail;
        } 否则 もし (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            switch (val_type) {
            case AV_OPT_TYPE_INT:       intnum = *(整数*)src;                break;
            case AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            break;
            case AV_OPT_TYPE_FLOAT:     num    = *(float*)src;              break;
            case AV_OPT_TYPE_DOUBLE:    num    = *(double*)src;             break;
            case AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   break;
            default: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            もし (ret < 0)
                goto fail;
        } 否则 {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    もし (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } 否则 {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        もし (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        もし (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            ために (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } 否则 {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(void**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    戻る ret;
}

整数 av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const char *key, 整数 flags)
{
    整数 ret;
    const AVClass *c = *(AVClass**)obj;
    整数 (*callback)(AVOptionRanges **, void *obj, const char *key, 整数 flags) = c->query_ranges;

    もし (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    もし (ret >= 0) {
        もし (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    戻る ret;
}

整数 av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const char *key, 整数 flags)
{
    AVOptionRanges *ranges = av_mallocz(sizeof(*ranges));
    AVOptionRange **range_array = av_mallocz(sizeof(void*));
    AVOptionRange *range = av_mallocz(sizeof(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    整数 ret;

    *ranges_arg = NULL;

    もし (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->value_min = field->min;
    range->value_max = field->max;

    switch (field->type) {
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_UINT:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
    case AV_OPT_TYPE_PIXEL_FMT:
    case AV_OPT_TYPE_SAMPLE_FMT:
    case AV_OPT_TYPE_FLOAT:
    case AV_OPT_TYPE_DOUBLE:
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_COLOR:
        break;
    case AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->value_min = -1;
        range->value_max = INT_MAX;
        break;
    case AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        break;
    case AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->value_min = 0;
        range->value_max = INT_MAX/8;
        break;
    case AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->value_min = 1;
        range->value_max = INT_MAX;
        break;
    default:
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    *ranges_arg = ranges;
    戻る 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    戻る ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    整数 i;
    AVOptionRanges *ranges = *rangesp;

    もし (!ranges)
        戻る;

    ために (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        もし (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

整数 av_opt_is_set_to_default(void *obj, const AVOption *o)
{
    int64_t i64;
    double d;
    AVRational q;
    整数 ret, w, h;
    char *str;
    void *dst;

    もし (!o || !obj)
        戻る AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    もし (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const char *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        もし (ret < 0)
            戻る ret;

        もし (!!val != !!def)
            ret = 0;
        否则 もし (val)
            ret = !strcmp(val, def);
        否则
            ret = 1;

        av_freep(&val);

        戻る ret;
    }

    switch (o->type) {
    case AV_OPT_TYPE_CONST:
        戻る 1;
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_FLAGS:
    case AV_OPT_TYPE_PIXEL_FMT:
    case AV_OPT_TYPE_SAMPLE_FMT:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_UINT:
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
        read_number(o, dst, NULL, NULL, &i64);
        戻る o->default_val.i64 == i64;
    case AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        もし (o->default_val.str) {
            もし ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                戻る ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        戻る ret;
    }
    case AV_OPT_TYPE_STRING:
        str = *(char **)dst;
        もし (str == o->default_val.str) //2 NULLs
            戻る 1;
        もし (!str || !o->default_val.str) //1 NULL
            戻る 0;
        戻る !strcmp(str, o->default_val.str);
    case AV_OPT_TYPE_DOUBLE:
        d = *(double *)dst;
        戻る o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    case AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        戻る (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    case AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        戻る !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    case AV_OPT_TYPE_BINARY: {
        struct {
            uint8_t *data;
            整数 size;
        } tmp = {0};
        整数 opt_size = *(整数 *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        もし (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            戻る 1;
        もし (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            戻る 0;
        もし (opt_size != strlen(o->default_val.str) / 2)
            戻る 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        もし (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        戻る ret;
    }
    case AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        もし (ret < 0) {
            av_dict_free(&dict1);
            戻る ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ながら (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        戻る (!en1 && !en2);
    }
    case AV_OPT_TYPE_IMAGE_SIZE:
        もし (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        否则 もし ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            戻る ret;
        戻る (w == *(整数 *)dst) && (h == *((整数 *)dst+1));
    case AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        もし (o->default_val.str) {
            もし ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                戻る ret;
        }
        戻る !av_cmp_q(*(AVRational*)dst, q);
    case AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        もし (o->default_val.str) {
            もし ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                戻る ret;
        }
        戻る !memcmp(color, dst, sizeof(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        break;
    }
    戻る AVERROR_PATCHWELCOME;
}

整数 av_opt_is_set_to_default_by_name(void *obj, const char *name, 整数 search_flags)
{
    const AVOption *o;
    void *target;
    もし (!obj)
        戻る AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    もし (!o)
        戻る AVERROR_OPTION_NOT_FOUND;
    戻る av_opt_is_set_to_default(target, o);
}

static 整数 opt_serialize(void *obj, 整数 opt_flags, 整数 flags, 整数 *cnt,
                         AVBPrint *bprint, const char key_val_sep, const char pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    整数 ret;
    const char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    もし (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        ながら (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            もし (ret < 0)
                戻る ret;
        }

    ながら (o = av_opt_next(obj, o)) {
        もし (o->type == AV_OPT_TYPE_CONST)
            continue;
        もし ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            もし ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                もし (o->flags == opt_flags)
                    continue;
            } 否则 もし ((o->flags & opt_flags) == opt_flags)
                continue;
        } 否则 {
            もし ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            否则 もし (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        もし (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        もし ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            戻る ret;
        }
        もし (buf) {
            もし ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    戻る 0;
}

整数 av_opt_serialize(void *obj, 整数 opt_flags, 整数 flags, char **buffer,
                     const char key_val_sep, const char pairs_sep)
{
    AVBPrint bprint;
    整数 ret, cnt = 0;

    もし (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        戻る AVERROR(EINVAL);
    }

    もし (!obj || !buffer)
        戻る AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    もし (ret < 0)
        戻る ret;

    ret = av_bprint_finalize(&bprint, buffer);
    もし (ret < 0)
        戻る ret;
    戻る 0;
}
