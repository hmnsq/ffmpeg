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
    만약 (!obj)
        반환 NULL;
    class = *(const AVClass**)obj;
    만약 (!last && class && class->option && class->option[0].name)
        반환 class->option;
    만약 (last && last[1].name)
        반환 ++last;
    반환 NULL;
}

static const struct {
    size_t      size;
    const char *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { sizeof(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { sizeof(정수),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { sizeof(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { sizeof(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { sizeof(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { sizeof(double),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { sizeof(float),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { sizeof(char *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { sizeof(AVRational),     "<rational>" },
    [AV_OPT_TYPE_BINARY]        = { sizeof(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { sizeof(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { sizeof(정수[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { sizeof(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { sizeof(enum AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { sizeof(enum AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { sizeof(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { sizeof(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { sizeof(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { sizeof(정수),            "<boolean>" },
};

// option is plain old data
static 정수 opt_is_pod(enum AVOptionType type)
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
        반환 1;
    }
    반환 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    반환 (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    반환 (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    반환 (unsigned *)((const void * const *)parray + 1);
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
    위해 (unsigned i = 0; i < *count; i++)
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
static 정수 opt_set_init(void *obj, const char *name, 정수 search_flags,
                        정수 require_type,
                        void **ptgt, const AVOption **po, void **pdst)
{
    void *logctx;
    const AVOption *o;
    void *tgt;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &tgt);
    만약 (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        반환 AVERROR_OPTION_NOT_FOUND;

    만약 (o->flags & AV_OPT_FLAG_READONLY)
        반환 AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    만약 (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        반환 AVERROR(EINVAL);
    }

    만약 (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        만약 (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        만약 (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            만약 (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        만약 (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            반환 AVERROR(EINVAL);
        }
    }

    만약 (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    만약 (po)
        *po   = o;
    만약 (ptgt)
        *ptgt = tgt;
    만약 (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    반환 0;
}

static AVRational double_to_rational(double d)
{
     AVRational r = av_d2q(d, 1 << 24);
     만약 ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     반환 r;
}

static 정수 read_number(const AVOption *o, const void *dst, double *num, 정수 *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    case AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned 정수*)dst;
        반환 0;
    case AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(enum AVPixelFormat *)dst;
        반환 0;
    case AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(enum AVSampleFormat *)dst;
        반환 0;
    case AV_OPT_TYPE_BOOL:
    case AV_OPT_TYPE_INT:
        *intnum = *(정수 *)dst;
        반환 0;
    case AV_OPT_TYPE_UINT:
        *intnum = *(unsigned 정수 *)dst;
        반환 0;
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        반환 0;
    case AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        반환 0;
    case AV_OPT_TYPE_DOUBLE:
        *num = *(double *)dst;
        반환 0;
    case AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        반환 0;
    case AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        반환 0;
    }
    반환 AVERROR(EINVAL);
}

static 정수 write_number(void *obj, const AVOption *o, void *dst,
                        double num, 정수 den, int64_t intnum,
                        정수 ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const enum AVOptionType type = TYPE_BASE(o->type);

    만약 (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        반환 AVERROR(ERANGE);
    }
    만약 (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        double d = num*intnum/den;
        만약 (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            반환 AVERROR(ERANGE);
        }
    }

    만약 (!dst)
        반환 0;

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
        *(정수 *)dst = llrint(num / den) * intnum;
        break;
    case AV_OPT_TYPE_DURATION:
    case AV_OPT_TYPE_INT64:{
        double d = num / den;
        만약 (intnum == 1 && d == (double)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } 아니면
            *(int64_t *)dst = llrint(d) * intnum;
        break;}
    case AV_OPT_TYPE_UINT64:{
        double d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        만약 (intnum == 1 && d == (double)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } 아니면 만약 (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } 아니면 {
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
        만약 ((정수) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        아니면
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        break;
    default:
        반환 AVERROR(EINVAL);
    }
    반환 0;
}

static 정수 hexchar2int(char c) {
    만약 (c >= '0' && c <= '9')
        반환 c - '0';
    만약 (c >= 'a' && c <= 'f')
        반환 c - 'a' + 10;
    만약 (c >= 'A' && c <= 'F')
        반환 c - 'A' + 10;
    반환 -1;
}

static 정수 set_string_binary(void *obj, const AVOption *o, const char *val, uint8_t **dst)
{
    정수 *lendst;
    uint8_t *bin, *ptr;
    정수 len;

    만약 (dst) {
        lendst = (정수 *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    만약 (!val || !(len = strlen(val)))
        반환 0;

    만약 (len & 1)
        반환 AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    만약 (!ptr)
        반환 AVERROR(ENOMEM);
    동안 (*val) {
        정수 a = hexchar2int(*val++);
        정수 b = hexchar2int(*val++);
        만약 (a < 0 || b < 0) {
            av_free(bin);
            반환 AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    만약 (dst) {
        *dst    = bin;
        *lendst = len;
    } 아니면 {
        av_free(bin);
    }

    반환 0;
}

static 정수 set_string(void *obj, const AVOption *o, const char *val, uint8_t **dst)
{
    만약 (!dst)
        반환 0;
    av_freep(dst);
    만약 (!val)
        반환 0;
    *dst = av_strdup(val);
    반환 *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

static 정수 set_string_number(void *obj, void *target_obj, const AVOption *o, const char *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const enum AVOptionType type = TYPE_BASE(o->type);
    정수 ret = 0;

    만약 (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        정수 num, den;
        char c;
        만약 (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            만약 ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                반환 ret;
            ret = 0;
        }
    }

    위해 (;;) {
        정수 i = 0;
        char buf[256];
        정수 cmd = 0;
        double d;
        int64_t intnum = 1;

        만약 (type == AV_OPT_TYPE_FLAGS) {
            만약 (*val == '+' || *val == '-')
                cmd = *(val++);
            위해 (; i < sizeof(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            정수 res;
            정수 ci = 0;
            double const_values[64];
            const char * const_names[64];
            정수 search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            const AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            만약 (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                만약 (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } 아니면 {
                만약 (o->unit) {
                    위해 (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        만약 (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            만약 (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                반환 AVERROR_PATCHWELCOME;
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
                만약 (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    반환 res;
                }
            }
        }
        만약 (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned 정수*)dst;
            만약 (cmd == '+')
                d = intnum | (int64_t)d;
            아니면 만약 (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        만약 ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            반환 ret;
        val += i;
        만약 (!i || !*val)
            반환 0;
    }
}

static 정수 set_string_image_size(void *obj, const AVOption *o, const char *val, 정수 *dst)
{
    void *logctx = dst ? obj : NULL;
    정수 tmp[2];
    정수 ret;

    만약 (!val || !strcmp(val, "none")) {
        만약 (dst) {
        dst[0] =
        dst[1] = 0;
        }
        반환 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    만약 (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        반환 ret;
    }
    만약 (dst)
        memcpy(dst, tmp, sizeof(tmp));
    반환 ret;
}

static 정수 set_string_video_rate(void *obj, const AVOption *o, const char *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    정수 ret = av_parse_video_rate(&tmp, val);
    만약 (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    만약 (dst)
        *dst = tmp;
    반환 ret;
}

static 정수 set_string_color(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    정수 ret;

    만약 (!val) {
        반환 0;
    } 아니면 {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        만약 (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            반환 ret;
        }
        만약 (dst)
            memcpy(dst, tmp, sizeof(tmp));
        반환 ret;
    }
    반환 0;
}

static const char *get_bool_name(정수 val)
{
    만약 (val < 0)
        반환 "auto";
    반환 val ? "true" : "false";
}

static 정수 set_string_bool(void *obj, const AVOption *o, const char *val, 정수 *dst)
{
    void *logctx = dst ? obj : NULL;
    정수 n;

    만약 (!val)
        반환 0;

    만약 (!strcmp(val, "auto")) {
        n = -1;
    } 아니면 만약 (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } 아니면 만약 (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } 아니면 {
        char *end = NULL;
        n = strtol(val, &end, 10);
        만약 (val + strlen(val) != end)
            goto fail;
    }

    만약 (n < o->min || n > o->max)
        goto fail;

    만약 (dst)
    *dst = n;
    반환 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    반환 AVERROR(EINVAL);
}

static 정수 set_string_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst,
                          정수 fmt_nb, 정수 ((*get_fmt)(const char *)), const char *desc,
                          enum AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    정수 fmt, min, max;

    만약 (!val || !strcmp(val, "none")) {
        fmt = -1;
    } 아니면 {
        fmt = get_fmt(val);
        만약 (fmt == -1) {
            char *tail;
            fmt = strtol(val, &tail, 0);
            만약 (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                반환 AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    만약(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    만약 (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        반환 AVERROR(ERANGE);
    }

    만약 (dst)
    switch (type) {
    case AV_OPT_TYPE_PIXEL_FMT:  *(enum AVPixelFormat *)dst = fmt; break;
    case AV_OPT_TYPE_SAMPLE_FMT: *(enum AVSampleFormat*)dst = fmt; break;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    반환 0;
}

static 정수 get_pix_fmt(const char *name)
{
    반환 av_get_pix_fmt(name);
}

static 정수 set_string_pixel_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    반환 set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static 정수 get_sample_fmt(const char *name)
{
    반환 av_get_sample_fmt(name);
}

static 정수 set_string_sample_fmt(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    반환 set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static 정수 set_string_dict(void *obj, const AVOption *o, const char *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    만약 (val) {
        정수 ret = av_dict_parse_string(&options, val, "=", ":", 0);
        만약 (ret < 0) {
            av_dict_free(&options);
            반환 ret;
        }
    }

    만약 (!dst) {
        av_dict_free(&options);
        반환 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    반환 0;
}

static 정수 set_string_channel_layout(void *obj, const AVOption *o,
                                     const char *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    정수 ret;
    만약 (dst)
    av_channel_layout_uninit(channel_layout);
    아니면
        channel_layout = &tmp;
    만약 (!val)
        반환 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    만약 (ret < 0)
        반환 ret;
    만약 (!dst)
        av_channel_layout_uninit(channel_layout);
    반환 0;
}

static 정수 opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const char *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const enum AVOptionType type = TYPE_BASE(o->type);
    정수 ret;

    만약 (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        반환 AVERROR(EINVAL);

    switch (type) {
    case AV_OPT_TYPE_BOOL:
        반환 set_string_bool(obj, o, val, dst);
    case AV_OPT_TYPE_STRING:
        반환 set_string(obj, o, val, dst);
    case AV_OPT_TYPE_BINARY:
        반환 set_string_binary(obj, o, val, dst);
    case AV_OPT_TYPE_FLAGS:
    case AV_OPT_TYPE_INT:
    case AV_OPT_TYPE_UINT:
    case AV_OPT_TYPE_INT64:
    case AV_OPT_TYPE_UINT64:
    case AV_OPT_TYPE_FLOAT:
    case AV_OPT_TYPE_DOUBLE:
    case AV_OPT_TYPE_RATIONAL:
        반환 set_string_number(obj, target_obj, o, val, dst);
    case AV_OPT_TYPE_IMAGE_SIZE:
        반환 set_string_image_size(obj, o, val, dst);
    case AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        만약 (ret < 0)
            반환 ret;
        반환 write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    case AV_OPT_TYPE_PIXEL_FMT:
        반환 set_string_pixel_fmt(obj, o, val, dst);
    case AV_OPT_TYPE_SAMPLE_FMT:
        반환 set_string_sample_fmt(obj, o, val, dst);
    case AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            만약 (val) {
                만약 ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    반환 ret;
                }
            }
            만약 (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                반환 AVERROR(ERANGE);
            }
            만약 (dst)
            *(int64_t *)dst = usecs;
            반환 0;
        }
    case AV_OPT_TYPE_COLOR:
        반환 set_string_color(obj, o, val, dst);
    case AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        만약 (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        반환 ret;
    case AV_OPT_TYPE_DICT:
        반환 set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    반환 AVERROR(EINVAL);
}

static 정수 opt_set_array(void *obj, void *target_obj, const AVOption *o,
                         const char *val, void *dst)
{
    const AVOptionArrayDef *arr = o->default_val.arr;
    const size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    const uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = NULL;

    void      *logctx = dst ? obj : NULL;
    void       *elems = NULL;
    unsigned nb_elems = 0;
    정수 ret;

    만약 (val && *val) {
        str = av_malloc(strlen(val) + 1);
        만약 (!str)
            반환 AVERROR(ENOMEM);
    }

    // split and unescape the string
    동안 (val && *val) {
        uint8_t *p = str;
        void *tmp;

        만약 (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        위해 (; *val; val++, p++) {
            만약 (*val == '\\' && val[1])
                val++;
            아니면 만약 (*val == sep) {
                val++;
                break;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        만약 (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        만약 (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    만약 (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    만약 (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    만약 (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } 아니면
        opt_free_array(o, &elems, &nb_elems);

    반환 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    반환 ret;
}

정수 av_opt_set(void *obj, const char *name, const char *val, 정수 search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    정수 ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    만약 (ret < 0)
        반환 ret;

    반환 ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
정수 av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const char *val, vartype *name ## _out)        \
{                                                                       \
    만약 (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        반환 AVERROR(EINVAL);                                         \
    반환 set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    정수)
OPT_EVAL_NUMBER(정수,    AV_OPT_TYPE_INT,      정수)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(float,  AV_OPT_TYPE_FLOAT,    float)
OPT_EVAL_NUMBER(double, AV_OPT_TYPE_DOUBLE,   double)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

static 정수 set_number(void *obj, const char *name, double num, 정수 den, int64_t intnum,
                      정수 search_flags, 정수 require_type)
{
    void *dst;
    const AVOption *o;
    정수 ret;

    ret = opt_set_init(obj, name, search_flags, require_type, NULL, &o, &dst);
    만약 (ret < 0)
        반환 ret;
    만약 (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    반환 ret;
}

정수 av_opt_set_int(void *obj, const char *name, int64_t val, 정수 search_flags)
{
    반환 set_number(obj, name, 1, 1, val, search_flags, 0);
}

정수 av_opt_set_double(void *obj, const char *name, double val, 정수 search_flags)
{
    반환 set_number(obj, name, val, 1, 1, search_flags, 0);
}

정수 av_opt_set_q(void *obj, const char *name, AVRational val, 정수 search_flags)
{
    반환 set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

정수 av_opt_set_bin(void *obj, const char *name, const uint8_t *val, 정수 len, 정수 search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    정수 *lendst;
    정수 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    만약 (ret < 0)
        반환 ret;

    만약 (dst) {
    ptr = len ? av_malloc(len) : NULL;
    만약 (len && !ptr)
        반환 AVERROR(ENOMEM);

    lendst = (정수 *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    만약 (len)
        memcpy(ptr, val, len);
    }

    반환 0;
}

정수 av_opt_set_image_size(void *obj, const char *name, 정수 w, 정수 h, 정수 search_flags)
{
    const AVOption *o;
    void *logctx;
    정수 *dst;
    정수 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    만약 (ret < 0)
        반환 ret;

    logctx = dst ? obj : NULL;

    만약 (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        반환 AVERROR(EINVAL);
    }

    만약 (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    반환 0;
}

정수 av_opt_set_video_rate(void *obj, const char *name, AVRational val, 정수 search_flags)
{
    반환 set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static 정수 set_format(void *obj, const char *name, 정수 fmt, 정수 search_flags,
                      enum AVOptionType type, const char *desc, 정수 nb_fmts)
{
    const AVOption *o;
    void *logctx;
    정수 *dst;
    정수 min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    만약 (ret < 0)
        반환 ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    만약 (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        반환 AVERROR(ERANGE);
    }
    만약 (dst)
    *dst = fmt;
    반환 0;
}

정수 av_opt_set_pixel_fmt(void *obj, const char *name, enum AVPixelFormat fmt, 정수 search_flags)
{
    반환 set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

정수 av_opt_set_sample_fmt(void *obj, const char *name, enum AVSampleFormat fmt, 정수 search_flags)
{
    반환 set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

정수 av_opt_set_dict_val(void *obj, const char *name, const AVDictionary *val,
                        정수 search_flags)
{
    AVDictionary **dst;
    정수 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    만약 (ret < 0)
        반환 ret;

    만약 (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    반환 ret;
}

정수 av_opt_set_chlayout(void *obj, const char *name,
                        const AVChannelLayout *channel_layout,
                        정수 search_flags)
{
    AVChannelLayout *dst;
    정수 ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    만약 (ret < 0)
        반환 ret;

    만약 (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    반환 ret;
}

static void format_duration(char *buf, size_t size, int64_t d)
{
    char *e;

    av_assert0(size >= 25);
    만약 (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    만약 (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    아니면 만약 (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    아니면 만약 (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (정수)((d / 60000000) % 60),
                 (정수)((d / 1000000) % 60),
                 (정수)(d % 1000000));
    아니면 만약 (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (정수)(d / 60000000),
                 (정수)((d / 1000000) % 60),
                 (정수)(d % 1000000));
    아니면
        snprintf(buf, size, "%d.%06d",
                 (정수)(d / 1000000),
                 (정수)(d % 1000000));
    e = buf + strlen(buf);
    동안 (e > buf && e[-1] == '0')
        *(--e) = 0;
    만약 (e > buf && e[-1] == '.')
        *(--e) = 0;
}

static 정수 opt_get_elem(const AVOption *o, uint8_t **pbuf, size_t buf_len,
                        const void *dst, 정수 search_flags)
{
    정수 ret;

    switch (TYPE_BASE(o->type)) {
    case AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(정수 *)dst));
        break;
    case AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(정수 *)dst);
        break;
    case AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(정수 *)dst);
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
        만약 (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } 아니면 만약 (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            반환 0;
        } 아니면 {
            *pbuf = av_strdup("");
        }
        반환 *pbuf ? 0 : AVERROR(ENOMEM);
    case AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        정수 len;

        만약 (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            반환 0;
        }
        len = *(정수 *)(((uint8_t *)dst) + sizeof(uint8_t *));
        만약 ((uint64_t)len * 2 + 1 > INT_MAX)
            반환 AVERROR(EINVAL);
        만약 (!(*pbuf = av_malloc(len * 2 + 1)))
            반환 AVERROR(ENOMEM);
        만약 (!len) {
            *pbuf[0] = '\0';
            반환 0;
        }
        bin = *(uint8_t **)dst;
        위해 (정수 i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        반환 0;
    }
    case AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((정수 *)dst)[0], ((정수 *)dst)[1]);
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
                       (정수)((uint8_t *)dst)[0], (정수)((uint8_t *)dst)[1],
                       (정수)((uint8_t *)dst)[2], (정수)((uint8_t *)dst)[3]);
        break;
    case AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        break;
    case AV_OPT_TYPE_DICT:
        만약 (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            반환 0;
        }
        반환 av_dict_get_string(*(AVDictionary **)dst, (char **)pbuf, '=', ':');
    default:
        반환 AVERROR(EINVAL);
    }

    반환 ret;
}

static 정수 opt_get_array(const AVOption *o, void *dst, uint8_t **out_val)
{
    const unsigned count = *opt_array_pcount(dst);
    const uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = NULL;
    size_t   str_len = 0;
    정수 ret;

    *out_val = NULL;

    위해 (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, sizeof(buf),
                           opt_array_pelem(o, *(void **)dst, i), 0);
        만약 (ret < 0)
            goto fail;

        out_len = strlen(out);
        만약 (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        만약 (ret < 0)
            goto fail;

        // add separator if needed
        만약 (i)
            str[str_len++] = sep;

        // escape the element
        위해 (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            만약 (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        만약 (out != buf)
            av_freep(&out);
        만약 (ret < 0) {
            av_freep(&str);
            반환 ret;
        }
    }

    *out_val = str;

    반환 0;
}

정수 av_opt_get(void *obj, const char *name, 정수 search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    정수 ret;

    만약 (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        반환 AVERROR_OPTION_NOT_FOUND;

    만약 (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    만약 (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        만약 (ret < 0)
            반환 ret;
        만약 (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            만약 (!*out_val)
               반환 AVERROR(ENOMEM);
        }
        반환 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, sizeof(buf), dst, search_flags);
    만약 (ret < 0)
        반환 ret;
    만약 (out != buf) {
        *out_val = out;
        반환 0;
    }

    만약 (ret >= sizeof(buf))
        반환 AVERROR(EINVAL);
    *out_val = av_strdup(out);
    반환 *out_val ? 0 : AVERROR(ENOMEM);
}

static 정수 get_number(void *obj, const char *name, double *num, 정수 *den, int64_t *intnum,
                      정수 search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        반환 AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    반환 read_number(o, dst, num, den, intnum);
}

정수 av_opt_get_int(void *obj, const char *name, 정수 search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    double num = 1;
    정수 ret, den = 1;

    만약 ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        반환 ret;
    만약 (num == den)
        *out_val = intnum;
    아니면
        *out_val = num * intnum / den;
    반환 0;
}

정수 av_opt_get_double(void *obj, const char *name, 정수 search_flags, double *out_val)
{
    int64_t intnum = 1;
    double num = 1;
    정수 ret, den = 1;

    만약 ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        반환 ret;
    *out_val = num * intnum / den;
    반환 0;
}

정수 av_opt_get_q(void *obj, const char *name, 정수 search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    double num = 1;
    정수 ret, den = 1;

    만약 ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        반환 ret;

    만약 (num == 1.0 && (정수)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    아니면
        *out_val = double_to_rational(num*intnum/den);
    반환 0;
}

정수 av_opt_get_image_size(void *obj, const char *name, 정수 search_flags, 정수 *w_out, 정수 *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        반환 AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    만약 (w_out) *w_out = *(정수 *)dst;
    만약 (h_out) *h_out = *((정수 *)dst+1);
    반환 0;
}

정수 av_opt_get_video_rate(void *obj, const char *name, 정수 search_flags, AVRational *out_val)
{
    반환 av_opt_get_q(obj, name, search_flags, out_val);
}

static 정수 get_format(void *obj, const char *name, 정수 search_flags, void *out_fmt,
                      enum AVOptionType type, const char *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        반환 AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    만약 (type == AV_OPT_TYPE_PIXEL_FMT)
        *(enum AVPixelFormat *)out_fmt = *(enum AVPixelFormat *)dst;
    아니면
        *(enum AVSampleFormat*)out_fmt = *(enum AVSampleFormat*)dst;

    반환 0;
}

정수 av_opt_get_pixel_fmt(void *obj, const char *name, 정수 search_flags, enum AVPixelFormat *out_fmt)
{
    반환 get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

정수 av_opt_get_sample_fmt(void *obj, const char *name, 정수 search_flags, enum AVSampleFormat *out_fmt)
{
    반환 get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

정수 av_opt_get_chlayout(void *obj, const char *name, 정수 search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        반환 AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    반환 av_channel_layout_copy(cl, dst);
}

정수 av_opt_get_dict_val(void *obj, const char *name, 정수 search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (o->type != AV_OPT_TYPE_DICT)
        반환 AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    반환 av_dict_copy(out_val, src, 0);
}

정수 av_opt_flag_is_set(void *obj, const char *field_name, const char *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    만약 (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        반환 0;
    반환 res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, 정수 level, int64_t i)
{
    만약 (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } 아니면 만약 (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } 아니면 만약 (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } 아니면 만약 (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } 아니면 만약 (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } 아니면 {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, 정수 level, double d)
{
    만약      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } 아니면 만약 (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } 아니면 만약 (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } 아니면 만약 (d == (double)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } 아니면 만약 (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } 아니면 만약 (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } 아니면 만약 (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } 아니면 만약 (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } 아니면 만약 (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } 아니면 만약 (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } 아니면 만약 (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } 아니면 만약 (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } 아니면 만약 (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } 아니면 {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const char *get_opt_const_name(void *obj, const char *unit, int64_t value)
{
    const AVOption *opt = NULL;

    만약 (!unit)
        반환 NULL;
    동안 ((opt = av_opt_next(obj, opt)))
        만약 (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            반환 opt->name;
    반환 NULL;
}

static char *get_opt_flags_string(void *obj, const char *unit, int64_t value)
{
    const AVOption *opt = NULL;
    char flags[512];

    flags[0] = 0;
    만약 (!unit)
        반환 NULL;
    동안 ((opt = av_opt_next(obj, opt))) {
        만약 (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            만약 (flags[0])
                av_strlcatf(flags, sizeof(flags), "+");
            av_strlcatf(flags, sizeof(flags), "%s", opt->name);
        }
    }
    만약 (flags[0])
        반환 av_strdup(flags);
    반환 NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     enum AVOptionType parent_type)
{
    const enum AVOptionType type = TYPE_BASE(o->type);

    만약 (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    아니면 만약 (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        만약 (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        아니면
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    아니면
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    만약 (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        반환;
    만약 ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        반환;

    만약 (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        만약 (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        반환;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    case AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        break;
    case AV_OPT_TYPE_FLAGS: {
        char *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        만약 (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } 아니면 {
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
        만약 (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        아니면
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
                     정수 req_flags, 정수 rej_flags, enum AVOptionType parent_type)
{
    const AVOption *opt = NULL;
    AVOptionRanges *r;
    정수 i;

    동안 ((opt = av_opt_next(obj, opt))) {
        만약 (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        만약 (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        아니면 만약 (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        아니면 만약 (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        아니면 만약 (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        아니면
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

        만약 (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        만약 (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
            switch (opt->type) {
            case AV_OPT_TYPE_INT:
            case AV_OPT_TYPE_UINT:
            case AV_OPT_TYPE_INT64:
            case AV_OPT_TYPE_UINT64:
            case AV_OPT_TYPE_DOUBLE:
            case AV_OPT_TYPE_FLOAT:
            case AV_OPT_TYPE_RATIONAL:
                위해 (i = 0; i < r->nb_ranges; i++) {
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
        만약 (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

정수 av_opt_show2(void *obj, void *av_log_obj, 정수 req_flags, 정수 rej_flags)
{
    만약 (!obj)
        반환 -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    반환 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, 정수 mask, 정수 flags)
{
    const AVOption *opt = NULL;
    동안 ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        만약 ((opt->flags & mask) != flags)
            continue;

        만약 (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        만약 (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const char              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            만약 (arr && arr->def)
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
static 정수 parse_key_value_pair(void *ctx, const char **buf,
                                const char *key_val_sep, const char *pairs_sep)
{
    char *key = av_get_token(buf, key_val_sep);
    char *val;
    정수 ret;

    만약 (!key)
        반환 AVERROR(ENOMEM);

    만약 (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        만약 (!val) {
            av_freep(&key);
            반환 AVERROR(ENOMEM);
        }
    } 아니면 {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        반환 AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    만약 (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    반환 ret;
}

정수 av_set_options_string(void *ctx, const char *opts,
                          const char *key_val_sep, const char *pairs_sep)
{
    정수 ret, count = 0;

    만약 (!opts)
        반환 0;

    동안 (*opts) {
        만약 ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            반환 ret;
        count++;

        만약 (*opts)
            opts++;
    }

    반환 count;
}

#define WHITESPACES " \n\t\r"

static 정수 is_key_char(char c)
{
    반환 (unsigned)((c | 32) - 'a') < 26 ||
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
static 정수 get_key(const char **ropts, const char *delim, char **rkey)
{
    const char *opts = *ropts;
    const char *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    동안 (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    만약 (!*opts || !strchr(delim, *opts))
        반환 AVERROR(EINVAL);
    opts++;
    만약 (!(*rkey = av_malloc(key_end - key_start + 1)))
        반환 AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    반환 0;
}

정수 av_opt_get_key_value(const char **ropts,
                         const char *key_val_sep, const char *pairs_sep,
                         unsigned flags,
                         char **rkey, char **rval)
{
    정수 ret;
    char *key = NULL, *val;
    const char *opts = *ropts;

    만약 ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        반환 AVERROR(EINVAL);
    만약 (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        반환 AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    반환 0;
}

정수 av_opt_set_from_string(void *ctx, const char *opts,
                           const char *const *shorthand,
                           const char *key_val_sep, const char *pairs_sep)
{
    정수 ret, count = 0;
    const char *dummy_shorthand = NULL;
    const char *key;

    만약 (!opts)
        반환 0;
    만약 (!shorthand)
        shorthand = &dummy_shorthand;

    동안 (*opts) {
        char *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        만약 (ret < 0) {
            만약 (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            아니면
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            반환 ret;
        }
        만약 (*opts)
            opts++;
        만약 (parsed_key) {
            key = parsed_key;
            동안 (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } 아니면 {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        만약 ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            만약 (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            반환 ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    반환 count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    동안 ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        만약 (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        아니면
            opt_free_elem(o->type, pitem);
    }
}

정수 av_opt_set_dict2(void *obj, AVDictionary **options, 정수 search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    정수 ret;

    만약 (!options)
        반환 0;

    동안 ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        만약 (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        만약 (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            반환 ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    반환 0;
}

정수 av_opt_set_dict(void *obj, AVDictionary **options)
{
    반환 av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const char *name, const char *unit,
                            정수 opt_flags, 정수 search_flags)
{
    반환 av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const char *name, const char *unit,
                             정수 opt_flags, 정수 search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    만약(!obj)
        반환 NULL;

    c= *(AVClass**)obj;

    만약 (!c)
        반환 NULL;

    만약 (search_flags & AV_OPT_SEARCH_CHILDREN) {
        만약 (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            동안 (child = av_opt_child_class_iterate(c, &iter))
                만약 (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    반환 o;
        } 아니면 {
            void *child = NULL;
            동안 (child = av_opt_child_next(obj, child))
                만약 (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    반환 o;
        }
    }

    동안 (o = av_opt_next(obj, o)) {
        만약 (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            만약 (target_obj) {
                만약 (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                아니면
                    *target_obj = NULL;
            }
            반환 o;
        }
    }
    반환 NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    만약 (c->child_next)
        반환 c->child_next(obj, prev);
    반환 NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    만약 (parent->child_class_iterate)
        반환 parent->child_class_iterate(iter);
    반환 NULL;
}

static 정수 opt_copy_elem(void *logctx, enum AVOptionType type,
                         void *dst, const void *src)
{
    만약 (type == AV_OPT_TYPE_STRING) {
        const char *src_str = *(const char *const *)src;
        char         **dstp =  (char **)dst;
        만약 (*dstp != src_str)
            av_freep(dstp);
        만약 (src_str) {
            *dstp = av_strdup(src_str);
            만약 (!*dstp)
                반환 AVERROR(ENOMEM);
        }
    } 아니면 만약 (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        정수 len = *(const 정수 *)(src8 + 1);
        만약 (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        만약 (len && !*dst8) {
            *(정수 *)(dst8 + 1) = 0;
            반환 AVERROR(ENOMEM);
        }
        *(정수 *)(dst8 + 1) = len;
    } 아니면 만약 (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } 아니면 만약 (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        만약 (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        반환 av_dict_copy(ddictp, sdict, 0);
    } 아니면 만약 (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        만약 (dlayout != slayout) {
            만약 (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            반환 av_channel_layout_copy(dst, src);
        }
    } 아니면 만약 (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } 아니면 {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        반환 AVERROR(EINVAL);
    }

    반환 0;
}

static 정수 opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    정수 ret;

    만약 (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    만약 (!dst)
        반환 AVERROR(ENOMEM);

    위해 (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        만약 (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            반환 ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    반환 0;
}

정수 av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    정수 ret = 0;

    만약 (!src)
        반환 AVERROR(EINVAL);

    c = *(AVClass **)src;
    만약 (!c || c != *(AVClass **)dst)
        반환 AVERROR(EINVAL);

    동안 ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        정수 err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        만약 (err < 0)
            ret = err;
    }
    반환 ret;
}

정수 av_opt_get_array_size(void *obj, const char *name, 정수 search_flags,
                          unsigned 정수 *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        반환 AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    반환 0;
}

정수 av_opt_get_array(void *obj, const char *name, 정수 search_flags,
                     unsigned 정수 start_elem, unsigned 정수 nb_elems,
                     enum AVOptionType out_type, void *out_val)
{
    const size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    const AVOption *o;
    void *target_obj;

    const void *parray;
    unsigned array_size;

    정수 ret;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    만약 (!o || !target_obj)
        반환 AVERROR_OPTION_NOT_FOUND;
    만약 (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        반환 AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    만약 (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        반환 AVERROR(EINVAL);

    위해 (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        만약 (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            만약 (ret < 0)
                goto fail;
        } 아니면 만약 (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, sizeof(buf), src, search_flags);
            만약 (ret < 0)
                goto fail;

            만약 (out == buf) {
                out = av_strdup(buf);
                만약 (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } 아니면 만약 (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            double     num = 1.0;
            정수        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            만약 (ret < 0)
                goto fail;

            switch (out_type) {
            case AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                break;
            case AV_OPT_TYPE_DOUBLE:
                *(double*)dst = num * intnum / den;
                break;
            case AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (정수)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                break;
            default: av_assert0(0);
            }
        } 아니면
            반환 AVERROR(ENOSYS);
    }

    반환 0;
fail:
    위해 (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    반환 ret;
}

정수 av_opt_set_array(void *obj, const char *name, 정수 search_flags,
                     unsigned 정수 start_elem, unsigned 정수 nb_elems,
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

    정수 ret = 0;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    만약 (ret < 0)
        반환 ret;

    만약 (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        반환 AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    만약 (start_elem > *array_size)
        반환 AVERROR(EINVAL);

    // compute new array size
    만약 (!val) {
        만약 (*array_size - start_elem < nb_elems)
            반환 AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } 아니면 만약 (search_flags & AV_OPT_ARRAY_REPLACE) {
        만약 (start_elem >= UINT_MAX - nb_elems)
            반환 AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } 아니면 {
        만약 (nb_elems >= UINT_MAX - *array_size)
            반환 AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    만약 (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        반환 AVERROR(EINVAL);

    // desired operation is shrinking the array
    만약 (!val) {
        void *array = *(void**)parray;

        위해 (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        만약 (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            만약 (!array)
                반환 AVERROR(ENOMEM);

            *(void**)parray = array;
        } 아니면
            av_freep(parray);

        *array_size = new_size;

        반환 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    만약 (!new_elems)
        반환 AVERROR(ENOMEM);

    // convert/validate each new element
    위해 (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        double     num = 1.0;
        정수        den = 1;
        int64_t intnum = 1;

        만약 (val_type == TYPE_BASE(o->type)) {
            정수 err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            만약 (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            만약 (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } 아니면 만약 (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const char **)src, dst);
            만약 (ret < 0)
                goto fail;
        } 아니면 만약 (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            switch (val_type) {
            case AV_OPT_TYPE_INT:       intnum = *(정수*)src;                break;
            case AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            break;
            case AV_OPT_TYPE_FLOAT:     num    = *(float*)src;              break;
            case AV_OPT_TYPE_DOUBLE:    num    = *(double*)src;             break;
            case AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   break;
            default: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            만약 (ret < 0)
                goto fail;
        } 아니면 {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    만약 (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } 아니면 {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        만약 (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        만약 (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            위해 (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } 아니면 {
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

    반환 ret;
}

정수 av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const char *key, 정수 flags)
{
    정수 ret;
    const AVClass *c = *(AVClass**)obj;
    정수 (*callback)(AVOptionRanges **, void *obj, const char *key, 정수 flags) = c->query_ranges;

    만약 (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    만약 (ret >= 0) {
        만약 (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    반환 ret;
}

정수 av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const char *key, 정수 flags)
{
    AVOptionRanges *ranges = av_mallocz(sizeof(*ranges));
    AVOptionRange **range_array = av_mallocz(sizeof(void*));
    AVOptionRange *range = av_mallocz(sizeof(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    정수 ret;

    *ranges_arg = NULL;

    만약 (!ranges || !range || !range_array || !field) {
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
    반환 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    반환 ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    정수 i;
    AVOptionRanges *ranges = *rangesp;

    만약 (!ranges)
        반환;

    위해 (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        만약 (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

정수 av_opt_is_set_to_default(void *obj, const AVOption *o)
{
    int64_t i64;
    double d;
    AVRational q;
    정수 ret, w, h;
    char *str;
    void *dst;

    만약 (!o || !obj)
        반환 AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    만약 (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const char *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        만약 (ret < 0)
            반환 ret;

        만약 (!!val != !!def)
            ret = 0;
        아니면 만약 (val)
            ret = !strcmp(val, def);
        아니면
            ret = 1;

        av_freep(&val);

        반환 ret;
    }

    switch (o->type) {
    case AV_OPT_TYPE_CONST:
        반환 1;
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
        반환 o->default_val.i64 == i64;
    case AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        만약 (o->default_val.str) {
            만약 ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                반환 ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        반환 ret;
    }
    case AV_OPT_TYPE_STRING:
        str = *(char **)dst;
        만약 (str == o->default_val.str) //2 NULLs
            반환 1;
        만약 (!str || !o->default_val.str) //1 NULL
            반환 0;
        반환 !strcmp(str, o->default_val.str);
    case AV_OPT_TYPE_DOUBLE:
        d = *(double *)dst;
        반환 o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    case AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        반환 (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    case AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        반환 !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    case AV_OPT_TYPE_BINARY: {
        struct {
            uint8_t *data;
            정수 size;
        } tmp = {0};
        정수 opt_size = *(정수 *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        만약 (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            반환 1;
        만약 (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            반환 0;
        만약 (opt_size != strlen(o->default_val.str) / 2)
            반환 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        만약 (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        반환 ret;
    }
    case AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        만약 (ret < 0) {
            av_dict_free(&dict1);
            반환 ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } 동안 (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        반환 (!en1 && !en2);
    }
    case AV_OPT_TYPE_IMAGE_SIZE:
        만약 (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        아니면 만약 ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            반환 ret;
        반환 (w == *(정수 *)dst) && (h == *((정수 *)dst+1));
    case AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        만약 (o->default_val.str) {
            만약 ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                반환 ret;
        }
        반환 !av_cmp_q(*(AVRational*)dst, q);
    case AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        만약 (o->default_val.str) {
            만약 ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                반환 ret;
        }
        반환 !memcmp(color, dst, sizeof(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        break;
    }
    반환 AVERROR_PATCHWELCOME;
}

정수 av_opt_is_set_to_default_by_name(void *obj, const char *name, 정수 search_flags)
{
    const AVOption *o;
    void *target;
    만약 (!obj)
        반환 AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    만약 (!o)
        반환 AVERROR_OPTION_NOT_FOUND;
    반환 av_opt_is_set_to_default(target, o);
}

static 정수 opt_serialize(void *obj, 정수 opt_flags, 정수 flags, 정수 *cnt,
                         AVBPrint *bprint, const char key_val_sep, const char pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    정수 ret;
    const char special_chars[] = {pairs_sep, key_val_sep, '\0'};

    만약 (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        동안 (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            만약 (ret < 0)
                반환 ret;
        }

    동안 (o = av_opt_next(obj, o)) {
        만약 (o->type == AV_OPT_TYPE_CONST)
            continue;
        만약 ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            만약 ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                만약 (o->flags == opt_flags)
                    continue;
            } 아니면 만약 ((o->flags & opt_flags) == opt_flags)
                continue;
        } 아니면 {
            만약 ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            아니면 만약 (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        만약 (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        만약 ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            반환 ret;
        }
        만약 (buf) {
            만약 ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    반환 0;
}

정수 av_opt_serialize(void *obj, 정수 opt_flags, 정수 flags, char **buffer,
                     const char key_val_sep, const char pairs_sep)
{
    AVBPrint bprint;
    정수 ret, cnt = 0;

    만약 (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        반환 AVERROR(EINVAL);
    }

    만약 (!obj || !buffer)
        반환 AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    만약 (ret < 0)
        반환 ret;

    ret = av_bprint_finalize(&bprint, buffer);
    만약 (ret < 0)
        반환 ret;
    반환 0;
}
