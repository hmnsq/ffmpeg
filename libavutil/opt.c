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
    නම් (!obj)
        ආපසු NULL;
    class = *(const AVClass**)obj;
    නම් (!last && class && class->option && class->option[0].name)
        ආපසු class->option;
    නම් (last && last[1].name)
        ආපසු ++last;
    ආපසු NULL;
}

static const sa_nracanaa {
    size_t      size;
    const var_na *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { parimaa_na(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { parimaa_na(පූර්ණ_සංඛ්‍යා),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { parimaa_na(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { parimaa_na(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { parimaa_na(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { parimaa_na(dviguu_na),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { parimaa_na(float),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { parimaa_na(var_na *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { parimaa_na(AVRational),     "<rational>" },
    [AV_OPT_TYPE_BINARY]        = { parimaa_na(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { parimaa_na(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { parimaa_na(පූර්ණ_සංඛ්‍යා[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { parimaa_na(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { parimaa_na(ga_nanaa AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { parimaa_na(ga_nanaa AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { parimaa_na(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { parimaa_na(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { parimaa_na(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { parimaa_na(පූර්ණ_සංඛ්‍යා),            "<boolean>" },
};

// option is plain old data
static පූර්ණ_සංඛ්‍යා opt_is_pod(ga_nanaa AVOptionType type)
{
    switch (type) {
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_RATIONAL:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_COLOR:
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_UINT:
        ආපසු 1;
    }
    ආපසු 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ආපසු (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ආපසු (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    ආපසු (unsigned *)((const void * const *)parray + 1);
}

static void opt_free_elem(ga_nanaa AVOptionType type, void *ptr)
{
    switch (TYPE_BASE(type)) {
    pak_sa AV_OPT_TYPE_STRING:
    pak_sa AV_OPT_TYPE_BINARY:
        av_freep(ptr);
        bha_nga;

    pak_sa AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        bha_nga;

    pak_sa AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        bha_nga;

    default:
        bha_nga;
    }
}

static void opt_free_array(const AVOption *o, void *parray, unsigned *count)
{
    සඳහා (unsigned i = 0; i < *count; i++)
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
static පූර්ණ_සංඛ්‍යා opt_set_init(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags,
                        පූර්ණ_සංඛ්‍යා require_type,
                        void **ptgt, const AVOption **po, void **pdst)
{
    void *logctx;
    const AVOption *o;
    void *tgt;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &tgt);
    නම් (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        ආපසු AVERROR_OPTION_NOT_FOUND;

    නම් (o->flags & AV_OPT_FLAG_READONLY)
        ආපසු AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    නම් (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ආපසු AVERROR(EINVAL);
    }

    නම් (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        නම් (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        නම් (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            නම් (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        නම් (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ආපසු AVERROR(EINVAL);
        }
    }

    නම් (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    නම් (po)
        *po   = o;
    නම් (ptgt)
        *ptgt = tgt;
    නම් (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    ආපසු 0;
}

static AVRational double_to_rational(dviguu_na d)
{
     AVRational r = av_d2q(d, 1 << 24);
     නම් ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ආපසු r;
}

static පූර්ණ_සංඛ්‍යා read_number(const AVOption *o, const void *dst, dviguu_na *num, පූර්ණ_සංඛ්‍යා *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned පූර්ණ_සංඛ්‍යා*)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ga_nanaa AVPixelFormat *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ga_nanaa AVSampleFormat *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_INT:
        *intnum = *(පූර්ණ_සංඛ්‍යා *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_UINT:
        *intnum = *(unsigned පූර්ණ_සංඛ්‍යා *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_DOUBLE:
        *num = *(dviguu_na *)dst;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        ආපසු 0;
    pak_sa AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ආපසු 0;
    }
    ආපසු AVERROR(EINVAL);
}

static පූර්ණ_සංඛ්‍යා write_number(void *obj, const AVOption *o, void *dst,
                        dviguu_na num, පූර්ණ_සංඛ්‍යා den, int64_t intnum,
                        පූර්ණ_සංඛ්‍යා ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    නම් (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        ආපසු AVERROR(ERANGE);
    }
    නම් (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        dviguu_na d = num*intnum/den;
        නම් (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            ආපසු AVERROR(ERANGE);
        }
    }

    නම් (!dst)
        ආපසු 0;

    switch (type) {
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        *(ga_nanaa AVPixelFormat *)dst = llrint(num / den) * intnum;
        bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        *(ga_nanaa AVSampleFormat *)dst = llrint(num / den) * intnum;
        bha_nga;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
        *(පූර්ණ_සංඛ්‍යා *)dst = llrint(num / den) * intnum;
        bha_nga;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:{
        dviguu_na d = num / den;
        නම් (intnum == 1 && d == (dviguu_na)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } නැතහොත්
            *(int64_t *)dst = llrint(d) * intnum;
        bha_nga;}
    pak_sa AV_OPT_TYPE_UINT64:{
        dviguu_na d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        නම් (intnum == 1 && d == (dviguu_na)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } නැතහොත් නම් (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } නැතහොත් {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        bha_nga;}
    pak_sa AV_OPT_TYPE_FLOAT:
        *(float *)dst = num * intnum / den;
        bha_nga;
    pak_sa AV_OPT_TYPE_DOUBLE:
        *(dviguu_na    *)dst = num * intnum / den;
        bha_nga;
    pak_sa AV_OPT_TYPE_RATIONAL:
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        නම් ((පූර්ණ_සංඛ්‍යා) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        නැතහොත්
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        bha_nga;
    default:
        ආපසු AVERROR(EINVAL);
    }
    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා hexchar2int(var_na c) {
    නම් (c >= '0' && c <= '9')
        ආපසු c - '0';
    නම් (c >= 'a' && c <= 'f')
        ආපසු c - 'a' + 10;
    නම් (c >= 'A' && c <= 'F')
        ආපසු c - 'A' + 10;
    ආපසු -1;
}

static පූර්ණ_සංඛ්‍යා set_string_binary(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    පූර්ණ_සංඛ්‍යා *lendst;
    uint8_t *bin, *ptr;
    පූර්ණ_සංඛ්‍යා len;

    නම් (dst) {
        lendst = (පූර්ණ_සංඛ්‍යා *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    නම් (!val || !(len = strlen(val)))
        ආපසු 0;

    නම් (len & 1)
        ආපසු AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    නම් (!ptr)
        ආපසු AVERROR(ENOMEM);
    අතරතුර (*val) {
        පූර්ණ_සංඛ්‍යා a = hexchar2int(*val++);
        පූර්ණ_සංඛ්‍යා b = hexchar2int(*val++);
        නම් (a < 0 || b < 0) {
            av_free(bin);
            ආපසු AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    නම් (dst) {
        *dst    = bin;
        *lendst = len;
    } නැතහොත් {
        av_free(bin);
    }

    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා set_string(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    නම් (!dst)
        ආපසු 0;
    av_freep(dst);
    නම් (!val)
        ආපසු 0;
    *dst = av_strdup(val);
    ආපසු *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

static පූර්ණ_සංඛ්‍යා set_string_number(void *obj, void *target_obj, const AVOption *o, const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    පූර්ණ_සංඛ්‍යා ret = 0;

    නම් (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        පූර්ණ_සංඛ්‍යා num, den;
        var_na c;
        නම් (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            නම් ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                ආපසු ret;
            ret = 0;
        }
    }

    සඳහා (;;) {
        පූර්ණ_සංඛ්‍යා i = 0;
        var_na buf[256];
        පූර්ණ_සංඛ්‍යා cmd = 0;
        dviguu_na d;
        int64_t intnum = 1;

        නම් (type == AV_OPT_TYPE_FLAGS) {
            නම් (*val == '+' || *val == '-')
                cmd = *(val++);
            සඳහා (; i < parimaa_na(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            පූර්ණ_සංඛ්‍යා res;
            පූර්ණ_සංඛ්‍යා ci = 0;
            dviguu_na const_values[64];
            const var_na * const_names[64];
            පූර්ණ_සංඛ්‍යා search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            const AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            නම් (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                නම් (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } නැතහොත් {
                නම් (o->unit) {
                    සඳහා (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        නම් (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            නම් (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ආපසු AVERROR_PATCHWELCOME;
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
                නම් (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ආපසු res;
                }
            }
        }
        නම් (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned පූර්ණ_සංඛ්‍යා*)dst;
            නම් (cmd == '+')
                d = intnum | (int64_t)d;
            නැතහොත් නම් (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        නම් ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            ආපසු ret;
        val += i;
        නම් (!i || !*val)
            ආපසු 0;
    }
}

static පූර්ණ_සංඛ්‍යා set_string_image_size(void *obj, const AVOption *o, const var_na *val, පූර්ණ_සංඛ්‍යා *dst)
{
    void *logctx = dst ? obj : NULL;
    පූර්ණ_සංඛ්‍යා tmp[2];
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!val || !strcmp(val, "none")) {
        නම් (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ආපසු 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    නම් (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ආපසු ret;
    }
    නම් (dst)
        memcpy(dst, tmp, parimaa_na(tmp));
    ආපසු ret;
}

static පූර්ණ_සංඛ්‍යා set_string_video_rate(void *obj, const AVOption *o, const var_na *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    පූර්ණ_සංඛ්‍යා ret = av_parse_video_rate(&tmp, val);
    නම් (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    නම් (dst)
        *dst = tmp;
    ආපසු ret;
}

static පූර්ණ_සංඛ්‍යා set_string_color(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!val) {
        ආපසු 0;
    } නැතහොත් {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        නම් (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ආපසු ret;
        }
        නම් (dst)
            memcpy(dst, tmp, parimaa_na(tmp));
        ආපසු ret;
    }
    ආපසු 0;
}

static const var_na *get_bool_name(පූර්ණ_සංඛ්‍යා val)
{
    නම් (val < 0)
        ආපසු "auto";
    ආපසු val ? "true" : "false";
}

static පූර්ණ_සංඛ්‍යා set_string_bool(void *obj, const AVOption *o, const var_na *val, පූර්ණ_සංඛ්‍යා *dst)
{
    void *logctx = dst ? obj : NULL;
    පූර්ණ_සංඛ්‍යා n;

    නම් (!val)
        ආපසු 0;

    නම් (!strcmp(val, "auto")) {
        n = -1;
    } නැතහොත් නම් (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } නැතහොත් නම් (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } නැතහොත් {
        var_na *end = NULL;
        n = strtol(val, &end, 10);
        නම් (val + strlen(val) != end)
            goto fail;
    }

    නම් (n < o->min || n > o->max)
        goto fail;

    නම් (dst)
    *dst = n;
    ආපසු 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ආපසු AVERROR(EINVAL);
}

static පූර්ණ_සංඛ්‍යා set_string_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst,
                          පූර්ණ_සංඛ්‍යා fmt_nb, පූර්ණ_සංඛ්‍යා ((*get_fmt)(const var_na *)), const var_na *desc,
                          ga_nanaa AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    පූර්ණ_සංඛ්‍යා fmt, min, max;

    නම් (!val || !strcmp(val, "none")) {
        fmt = -1;
    } නැතහොත් {
        fmt = get_fmt(val);
        නම් (fmt == -1) {
            var_na *tail;
            fmt = strtol(val, &tail, 0);
            නම් (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ආපසු AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    නම්(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    නම් (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ආපසු AVERROR(ERANGE);
    }

    නම් (dst)
    switch (type) {
    pak_sa AV_OPT_TYPE_PIXEL_FMT:  *(ga_nanaa AVPixelFormat *)dst = fmt; bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT: *(ga_nanaa AVSampleFormat*)dst = fmt; bha_nga;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා get_pix_fmt(const var_na *name)
{
    ආපසු av_get_pix_fmt(name);
}

static පූර්ණ_සංඛ්‍යා set_string_pixel_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ආපසු set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static පූර්ණ_සංඛ්‍යා get_sample_fmt(const var_na *name)
{
    ආපසු av_get_sample_fmt(name);
}

static පූර්ණ_සංඛ්‍යා set_string_sample_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ආපසු set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static පූර්ණ_සංඛ්‍යා set_string_dict(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    නම් (val) {
        පූර්ණ_සංඛ්‍යා ret = av_dict_parse_string(&options, val, "=", ":", 0);
        නම් (ret < 0) {
            av_dict_free(&options);
            ආපසු ret;
        }
    }

    නම් (!dst) {
        av_dict_free(&options);
        ආපසු 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා set_string_channel_layout(void *obj, const AVOption *o,
                                     const var_na *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    පූර්ණ_සංඛ්‍යා ret;
    නම් (dst)
    av_channel_layout_uninit(channel_layout);
    නැතහොත්
        channel_layout = &tmp;
    නම් (!val)
        ආපසු 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    නම් (ret < 0)
        ආපසු ret;
    නම් (!dst)
        av_channel_layout_uninit(channel_layout);
    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ආපසු AVERROR(EINVAL);

    switch (type) {
    pak_sa AV_OPT_TYPE_BOOL:
        ආපසු set_string_bool(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_STRING:
        ආපසු set_string(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_BINARY:
        ආපසු set_string_binary(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_RATIONAL:
        ආපසු set_string_number(obj, target_obj, o, val, dst);
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ආපසු set_string_image_size(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        නම් (ret < 0)
            ආපසු ret;
        ආපසු write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        ආපසු set_string_pixel_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        ආපසු set_string_sample_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            නම් (val) {
                නම් ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ආපසු ret;
                }
            }
            නම් (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ආපසු AVERROR(ERANGE);
            }
            නම් (dst)
            *(int64_t *)dst = usecs;
            ආපසු 0;
        }
    pak_sa AV_OPT_TYPE_COLOR:
        ආපසු set_string_color(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        නම් (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ආපසු ret;
    pak_sa AV_OPT_TYPE_DICT:
        ආපසු set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ආපසු AVERROR(EINVAL);
}

static පූර්ණ_සංඛ්‍යා opt_set_array(void *obj, void *target_obj, const AVOption *o,
                         const var_na *val, void *dst)
{
    const AVOptionArrayDef *arr = o->default_val.arr;
    const size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    const uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = NULL;

    void      *logctx = dst ? obj : NULL;
    void       *elems = NULL;
    unsigned nb_elems = 0;
    පූර්ණ_සංඛ්‍යා ret;

    නම් (val && *val) {
        str = av_malloc(strlen(val) + 1);
        නම් (!str)
            ආපසු AVERROR(ENOMEM);
    }

    // split and unescape the string
    අතරතුර (val && *val) {
        uint8_t *p = str;
        void *tmp;

        නම් (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        සඳහා (; *val; val++, p++) {
            නම් (*val == '\\' && val[1])
                val++;
            නැතහොත් නම් (*val == sep) {
                val++;
                bha_nga;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        නම් (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        නම් (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    නම් (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    නම් (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    නම් (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } නැතහොත්
        opt_free_array(o, &elems, &nb_elems);

    ආපසු 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_set(void *obj, const var_na *name, const var_na *val, පූර්ණ_සංඛ්‍යා search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    පූර්ණ_සංඛ්‍යා ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    නම් (ret < 0)
        ආපසු ret;

    ආපසු ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
පූර්ණ_සංඛ්‍යා av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const var_na *val, vartype *name ## _out)        \
{                                                                       \
    නම් (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ආපසු AVERROR(EINVAL);                                         \
    ආපසු set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    පූර්ණ_සංඛ්‍යා)
OPT_EVAL_NUMBER(පූර්ණ_සංඛ්‍යා,    AV_OPT_TYPE_INT,      පූර්ණ_සංඛ්‍යා)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(float,  AV_OPT_TYPE_FLOAT,    float)
OPT_EVAL_NUMBER(dviguu_na, AV_OPT_TYPE_DOUBLE,   dviguu_na)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

static පූර්ණ_සංඛ්‍යා set_number(void *obj, const var_na *name, dviguu_na num, පූර්ණ_සංඛ්‍යා den, int64_t intnum,
                      පූර්ණ_සංඛ්‍යා search_flags, පූර්ණ_සංඛ්‍යා require_type)
{
    void *dst;
    const AVOption *o;
    පූර්ණ_සංඛ්‍යා ret;

    ret = opt_set_init(obj, name, search_flags, require_type, NULL, &o, &dst);
    නම් (ret < 0)
        ආපසු ret;
    නම් (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_set_int(void *obj, const var_na *name, int64_t val, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු set_number(obj, name, 1, 1, val, search_flags, 0);
}

පූර්ණ_සංඛ්‍යා av_opt_set_double(void *obj, const var_na *name, dviguu_na val, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු set_number(obj, name, val, 1, 1, search_flags, 0);
}

පූර්ණ_සංඛ්‍යා av_opt_set_q(void *obj, const var_na *name, AVRational val, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

පූර්ණ_සංඛ්‍යා av_opt_set_bin(void *obj, const var_na *name, const uint8_t *val, පූර්ණ_සංඛ්‍යා len, පූර්ණ_සංඛ්‍යා search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    පූර්ණ_සංඛ්‍යා *lendst;
    පූර්ණ_සංඛ්‍යා ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    නම් (ret < 0)
        ආපසු ret;

    නම් (dst) {
    ptr = len ? av_malloc(len) : NULL;
    නම් (len && !ptr)
        ආපසු AVERROR(ENOMEM);

    lendst = (පූර්ණ_සංඛ්‍යා *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    නම් (len)
        memcpy(ptr, val, len);
    }

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_set_image_size(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා w, පූර්ණ_සංඛ්‍යා h, පූර්ණ_සංඛ්‍යා search_flags)
{
    const AVOption *o;
    void *logctx;
    පූර්ණ_සංඛ්‍යා *dst;
    පූර්ණ_සංඛ්‍යා ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    නම් (ret < 0)
        ආපසු ret;

    logctx = dst ? obj : NULL;

    නම් (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ආපසු AVERROR(EINVAL);
    }

    නම් (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_set_video_rate(void *obj, const var_na *name, AVRational val, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static පූර්ණ_සංඛ්‍යා set_format(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා fmt, පූර්ණ_සංඛ්‍යා search_flags,
                      ga_nanaa AVOptionType type, const var_na *desc, පූර්ණ_සංඛ්‍යා nb_fmts)
{
    const AVOption *o;
    void *logctx;
    පූර්ණ_සංඛ්‍යා *dst;
    පූර්ණ_සංඛ්‍යා min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    නම් (ret < 0)
        ආපසු ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    නම් (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ආපසු AVERROR(ERANGE);
    }
    නම් (dst)
    *dst = fmt;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_set_pixel_fmt(void *obj, const var_na *name, ga_nanaa AVPixelFormat fmt, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

පූර්ණ_සංඛ්‍යා av_opt_set_sample_fmt(void *obj, const var_na *name, ga_nanaa AVSampleFormat fmt, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

පූර්ණ_සංඛ්‍යා av_opt_set_dict_val(void *obj, const var_na *name, const AVDictionary *val,
                        පූර්ණ_සංඛ්‍යා search_flags)
{
    AVDictionary **dst;
    පූර්ණ_සංඛ්‍යා ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    නම් (ret < 0)
        ආපසු ret;

    නම් (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_set_chlayout(void *obj, const var_na *name,
                        const AVChannelLayout *channel_layout,
                        පූර්ණ_සංඛ්‍යා search_flags)
{
    AVChannelLayout *dst;
    පූර්ණ_සංඛ්‍යා ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    නම් (ret < 0)
        ආපසු ret;

    නම් (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ආපසු ret;
}

static void format_duration(var_na *buf, size_t size, int64_t d)
{
    var_na *e;

    av_assert0(size >= 25);
    නම් (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    නම් (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    නැතහොත් නම් (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    නැතහොත් නම් (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (පූර්ණ_සංඛ්‍යා)((d / 60000000) % 60),
                 (පූර්ණ_සංඛ්‍යා)((d / 1000000) % 60),
                 (පූර්ණ_සංඛ්‍යා)(d % 1000000));
    නැතහොත් නම් (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (පූර්ණ_සංඛ්‍යා)(d / 60000000),
                 (පූර්ණ_සංඛ්‍යා)((d / 1000000) % 60),
                 (පූර්ණ_සංඛ්‍යා)(d % 1000000));
    නැතහොත්
        snprintf(buf, size, "%d.%06d",
                 (පූර්ණ_සංඛ්‍යා)(d / 1000000),
                 (පූර්ණ_සංඛ්‍යා)(d % 1000000));
    e = buf + strlen(buf);
    අතරතුර (e > buf && e[-1] == '0')
        *(--e) = 0;
    නම් (e > buf && e[-1] == '.')
        *(--e) = 0;
}

static පූර්ණ_සංඛ්‍යා opt_get_elem(const AVOption *o, uint8_t **pbuf, size_t buf_len,
                        const void *dst, පූර්ණ_සංඛ්‍යා search_flags)
{
    පූර්ණ_සංඛ්‍යා ret;

    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(පූර්ණ_සංඛ්‍යා *)dst));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(පූර්ණ_සංඛ්‍යා *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(පූර්ණ_සංඛ්‍යා *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(float *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(dviguu_na *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
    pak_sa AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->num, ((AVRational *)dst)->den);
        bha_nga;
    pak_sa AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        bha_nga;
    pak_sa AV_OPT_TYPE_STRING:
        නම් (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } නැතහොත් නම් (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            ආපසු 0;
        } නැතහොත් {
            *pbuf = av_strdup("");
        }
        ආපසු *pbuf ? 0 : AVERROR(ENOMEM);
    pak_sa AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        පූර්ණ_සංඛ්‍යා len;

        නම් (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ආපසු 0;
        }
        len = *(පූර්ණ_සංඛ්‍යා *)(((uint8_t *)dst) + parimaa_na(uint8_t *));
        නම් ((uint64_t)len * 2 + 1 > INT_MAX)
            ආපසු AVERROR(EINVAL);
        නම් (!(*pbuf = av_malloc(len * 2 + 1)))
            ආපසු AVERROR(ENOMEM);
        නම් (!len) {
            *pbuf[0] = '\0';
            ආපසු 0;
        }
        bin = *(uint8_t **)dst;
        සඳහා (පූර්ණ_සංඛ්‍යා i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ආපසු 0;
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((පූර්ණ_සංඛ්‍යා *)dst)[0], ((පූර්ණ_සංඛ්‍යා *)dst)[1]);
        bha_nga;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (var_na *)av_x_if_null(av_get_pix_fmt_name(*(ga_nanaa AVPixelFormat *)dst), "none"));
        bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (var_na *)av_x_if_null(av_get_sample_fmt_name(*(ga_nanaa AVSampleFormat *)dst), "none"));
        bha_nga;
    pak_sa AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        bha_nga;
    }
    pak_sa AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (පූර්ණ_සංඛ්‍යා)((uint8_t *)dst)[0], (පූර්ණ_සංඛ්‍යා)((uint8_t *)dst)[1],
                       (පූර්ණ_සංඛ්‍යා)((uint8_t *)dst)[2], (පූර්ණ_සංඛ්‍යා)((uint8_t *)dst)[3]);
        bha_nga;
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        bha_nga;
    pak_sa AV_OPT_TYPE_DICT:
        නම් (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ආපසු 0;
        }
        ආපසු av_dict_get_string(*(AVDictionary **)dst, (var_na **)pbuf, '=', ':');
    default:
        ආපසු AVERROR(EINVAL);
    }

    ආපසු ret;
}

static පූර්ණ_සංඛ්‍යා opt_get_array(const AVOption *o, void *dst, uint8_t **out_val)
{
    const unsigned count = *opt_array_pcount(dst);
    const uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = NULL;
    size_t   str_len = 0;
    පූර්ණ_සංඛ්‍යා ret;

    *out_val = NULL;

    සඳහා (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, parimaa_na(buf),
                           opt_array_pelem(o, *(void **)dst, i), 0);
        නම් (ret < 0)
            goto fail;

        out_len = strlen(out);
        නම් (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        නම් (ret < 0)
            goto fail;

        // add separator if needed
        නම් (i)
            str[str_len++] = sep;

        // escape the element
        සඳහා (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            නම් (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        නම් (out != buf)
            av_freep(&out);
        නම් (ret < 0) {
            av_freep(&str);
            ආපසු ret;
        }
    }

    *out_val = str;

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ආපසු AVERROR_OPTION_NOT_FOUND;

    නම් (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    නම් (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        නම් (ret < 0)
            ආපසු ret;
        නම් (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            නම් (!*out_val)
               ආපසු AVERROR(ENOMEM);
        }
        ආපසු 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, parimaa_na(buf), dst, search_flags);
    නම් (ret < 0)
        ආපසු ret;
    නම් (out != buf) {
        *out_val = out;
        ආපසු 0;
    }

    නම් (ret >= parimaa_na(buf))
        ආපසු AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ආපසු *out_val ? 0 : AVERROR(ENOMEM);
}

static පූර්ණ_සංඛ්‍යා get_number(void *obj, const var_na *name, dviguu_na *num, පූර්ණ_සංඛ්‍යා *den, int64_t *intnum,
                      පූර්ණ_සංඛ්‍යා search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ආපසු AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ආපසු read_number(o, dst, num, den, intnum);
}

පූර්ණ_සංඛ්‍යා av_opt_get_int(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    පූර්ණ_සංඛ්‍යා ret, den = 1;

    නම් ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ආපසු ret;
    නම් (num == den)
        *out_val = intnum;
    නැතහොත්
        *out_val = num * intnum / den;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_double(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, dviguu_na *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    පූර්ණ_සංඛ්‍යා ret, den = 1;

    නම් ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ආපසු ret;
    *out_val = num * intnum / den;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_q(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    පූර්ණ_සංඛ්‍යා ret, den = 1;

    නම් ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ආපසු ret;

    නම් (num == 1.0 && (පූර්ණ_සංඛ්‍යා)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    නැතහොත්
        *out_val = double_to_rational(num*intnum/den);
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_image_size(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, පූර්ණ_සංඛ්‍යා *w_out, පූර්ණ_සංඛ්‍යා *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ආපසු AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    නම් (w_out) *w_out = *(පූර්ණ_සංඛ්‍යා *)dst;
    නම් (h_out) *h_out = *((පූර්ණ_සංඛ්‍යා *)dst+1);
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_video_rate(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, AVRational *out_val)
{
    ආපසු av_opt_get_q(obj, name, search_flags, out_val);
}

static පූර්ණ_සංඛ්‍යා get_format(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, void *out_fmt,
                      ga_nanaa AVOptionType type, const var_na *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ආපසු AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    නම් (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ga_nanaa AVPixelFormat *)out_fmt = *(ga_nanaa AVPixelFormat *)dst;
    නැතහොත්
        *(ga_nanaa AVSampleFormat*)out_fmt = *(ga_nanaa AVSampleFormat*)dst;

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_pixel_fmt(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, ga_nanaa AVPixelFormat *out_fmt)
{
    ආපසු get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

පූර්ණ_සංඛ්‍යා av_opt_get_sample_fmt(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, ga_nanaa AVSampleFormat *out_fmt)
{
    ආපසු get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

පූර්ණ_සංඛ්‍යා av_opt_get_chlayout(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ආපසු AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ආපසු av_channel_layout_copy(cl, dst);
}

පූර්ණ_සංඛ්‍යා av_opt_get_dict_val(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (o->type != AV_OPT_TYPE_DICT)
        ආපසු AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ආපසු av_dict_copy(out_val, src, 0);
}

පූර්ණ_සංඛ්‍යා av_opt_flag_is_set(void *obj, const var_na *field_name, const var_na *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    නම් (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ආපසු 0;
    ආපසු res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, පූර්ණ_සංඛ්‍යා level, int64_t i)
{
    නම් (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } නැතහොත් නම් (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } නැතහොත් නම් (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } නැතහොත් නම් (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } නැතහොත් නම් (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } නැතහොත් {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, පූර්ණ_සංඛ්‍යා level, dviguu_na d)
{
    නම්      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } නැතහොත් නම් (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } නැතහොත් නම් (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } නැතහොත් නම් (d == (dviguu_na)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } නැතහොත් නම් (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } නැතහොත් නම් (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } නැතහොත් නම් (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } නැතහොත් නම් (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } නැතහොත් නම් (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } නැතහොත් නම් (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } නැතහොත් නම් (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } නැතහොත් නම් (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } නැතහොත් නම් (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } නැතහොත් {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const var_na *get_opt_const_name(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;

    නම් (!unit)
        ආපසු NULL;
    අතරතුර ((opt = av_opt_next(obj, opt)))
        නම් (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            ආපසු opt->name;
    ආපසු NULL;
}

static var_na *get_opt_flags_string(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;
    var_na flags[512];

    flags[0] = 0;
    නම් (!unit)
        ආපසු NULL;
    අතරතුර ((opt = av_opt_next(obj, opt))) {
        නම් (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            නම් (flags[0])
                av_strlcatf(flags, parimaa_na(flags), "+");
            av_strlcatf(flags, parimaa_na(flags), "%s", opt->name);
        }
    }
    නම් (flags[0])
        ආපසු av_strdup(flags);
    ආපසු NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     ga_nanaa AVOptionType parent_type)
{
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    නම් (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    නැතහොත් නම් (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        නම් (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        නැතහොත්
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    නැතහොත්
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    නම් (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        ආපසු;
    නම් ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ආපසු;

    නම් (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        නම් (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ආපසු;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    pak_sa AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS: {
        var_na *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        නම් (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } නැතහොත් {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        bha_nga;
    }
    pak_sa AV_OPT_TYPE_DURATION: {
        var_na buf[25];
        format_duration(buf, parimaa_na(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        bha_nga;
    }
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_INT64: {
        const var_na *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        නම් (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        නැතහොත්
            log_int_value(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        bha_nga;
    }
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_FLOAT:
        log_value(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        bha_nga;
    pak_sa AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.num, q.den); }
        bha_nga;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (var_na *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (var_na *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        bha_nga;
    pak_sa AV_OPT_TYPE_COLOR:
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
    pak_sa AV_OPT_TYPE_STRING:
    pak_sa AV_OPT_TYPE_DICT:
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        bha_nga;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

static void opt_list(void *obj, void *av_log_obj, const var_na *unit,
                     පූර්ණ_සංඛ්‍යා req_flags, පූර්ණ_සංඛ්‍යා rej_flags, ga_nanaa AVOptionType parent_type)
{
    const AVOption *opt = NULL;
    AVOptionRanges *r;
    පූර්ණ_සංඛ්‍යා i;

    අතරතුර ((opt = av_opt_next(obj, opt))) {
        නම් (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        නම් (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        නැතහොත් නම් (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        නැතහොත් නම් (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        නැතහොත් නම් (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        නැතහොත්
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

        නම් (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        නම් (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
            switch (opt->type) {
            pak_sa AV_OPT_TYPE_INT:
            pak_sa AV_OPT_TYPE_UINT:
            pak_sa AV_OPT_TYPE_INT64:
            pak_sa AV_OPT_TYPE_UINT64:
            pak_sa AV_OPT_TYPE_DOUBLE:
            pak_sa AV_OPT_TYPE_FLOAT:
            pak_sa AV_OPT_TYPE_RATIONAL:
                සඳහා (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_value(av_log_obj, AV_LOG_INFO, r->range[i]->value_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_value(av_log_obj, AV_LOG_INFO, r->range[i]->value_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                bha_nga;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        නම් (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

පූර්ණ_සංඛ්‍යා av_opt_show2(void *obj, void *av_log_obj, පූර්ණ_සංඛ්‍යා req_flags, පූර්ණ_සංඛ්‍යා rej_flags)
{
    නම් (!obj)
        ආපසු -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    ආපසු 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, පූර්ණ_සංඛ්‍යා mask, පූර්ණ_සංඛ්‍යා flags)
{
    const AVOption *opt = NULL;
    අතරතුර ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        නම් ((opt->flags & mask) != flags)
            continue;

        නම් (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        නම් (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const var_na              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            නම් (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            continue;
        }

        switch (opt->type) {
            pak_sa AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                bha_nga;
            pak_sa AV_OPT_TYPE_BOOL:
            pak_sa AV_OPT_TYPE_FLAGS:
            pak_sa AV_OPT_TYPE_INT:
            pak_sa AV_OPT_TYPE_UINT:
            pak_sa AV_OPT_TYPE_INT64:
            pak_sa AV_OPT_TYPE_UINT64:
            pak_sa AV_OPT_TYPE_DURATION:
            pak_sa AV_OPT_TYPE_PIXEL_FMT:
            pak_sa AV_OPT_TYPE_SAMPLE_FMT:
                write_number(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:
            pak_sa AV_OPT_TYPE_FLOAT: {
                dviguu_na val;
                val = opt->default_val.dbl;
                write_number(s, opt, dst, val, 1, 1, 1);
            }
            bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_number(s, opt, dst, 1, val.den, val.num, 1);
            }
            bha_nga;
            pak_sa AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                bha_nga;
            pak_sa AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                bha_nga;
            pak_sa AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                bha_nga;
            pak_sa AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                bha_nga;
            pak_sa AV_OPT_TYPE_BINARY:
                set_string_binary(s, opt, opt->default_val.str, dst);
                bha_nga;
            pak_sa AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                bha_nga;
            pak_sa AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                bha_nga;
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
static පූර්ණ_සංඛ්‍යා parse_key_value_pair(void *ctx, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val;
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!key)
        ආපසු AVERROR(ENOMEM);

    නම් (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        නම් (!val) {
            av_freep(&key);
            ආපසු AVERROR(ENOMEM);
        }
    } නැතහොත් {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        ආපසු AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    නම් (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_set_options_string(void *ctx, const var_na *opts,
                          const var_na *key_val_sep, const var_na *pairs_sep)
{
    පූර්ණ_සංඛ්‍යා ret, count = 0;

    නම් (!opts)
        ආපසු 0;

    අතරතුර (*opts) {
        නම් ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            ආපසු ret;
        count++;

        නම් (*opts)
            opts++;
    }

    ආපසු count;
}

#define WHITESPACES " \n\t\r"

static පූර්ණ_සංඛ්‍යා is_key_char(var_na c)
{
    ආපසු (unsigned)((c | 32) - 'a') < 26 ||
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
static පූර්ණ_සංඛ්‍යා get_key(const var_na **ropts, const var_na *delim, var_na **rkey)
{
    const var_na *opts = *ropts;
    const var_na *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    අතරතුර (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    නම් (!*opts || !strchr(delim, *opts))
        ආපසු AVERROR(EINVAL);
    opts++;
    නම් (!(*rkey = av_malloc(key_end - key_start + 1)))
        ආපසු AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_key_value(const var_na **ropts,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         unsigned flags,
                         var_na **rkey, var_na **rval)
{
    පූර්ණ_සංඛ්‍යා ret;
    var_na *key = NULL, *val;
    const var_na *opts = *ropts;

    නම් ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        ආපසු AVERROR(EINVAL);
    නම් (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        ආපසු AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_set_from_string(void *ctx, const var_na *opts,
                           const var_na *const *shorthand,
                           const var_na *key_val_sep, const var_na *pairs_sep)
{
    පූර්ණ_සංඛ්‍යා ret, count = 0;
    const var_na *dummy_shorthand = NULL;
    const var_na *key;

    නම් (!opts)
        ආපසු 0;
    නම් (!shorthand)
        shorthand = &dummy_shorthand;

    අතරතුර (*opts) {
        var_na *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        නම් (ret < 0) {
            නම් (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            නැතහොත්
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ආපසු ret;
        }
        නම් (*opts)
            opts++;
        නම් (parsed_key) {
            key = parsed_key;
            අතරතුර (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } නැතහොත් {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        නම් ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            නම් (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            ආපසු ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    ආපසු count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    අතරතුර ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        නම් (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        නැතහොත්
            opt_free_elem(o->type, pitem);
    }
}

පූර්ණ_සංඛ්‍යා av_opt_set_dict2(void *obj, AVDictionary **options, පූර්ණ_සංඛ්‍යා search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    පූර්ණ_සංඛ්‍යා ret;

    නම් (!options)
        ආපසු 0;

    අතරතුර ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        නම් (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        නම් (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            ආපසු ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_set_dict(void *obj, AVDictionary **options)
{
    ආපසු av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const var_na *name, const var_na *unit,
                            පූර්ණ_සංඛ්‍යා opt_flags, පූර්ණ_සංඛ්‍යා search_flags)
{
    ආපසු av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const var_na *name, const var_na *unit,
                             පූර්ණ_සංඛ්‍යා opt_flags, පූර්ණ_සංඛ්‍යා search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    නම්(!obj)
        ආපසු NULL;

    c= *(AVClass**)obj;

    නම් (!c)
        ආපසු NULL;

    නම් (search_flags & AV_OPT_SEARCH_CHILDREN) {
        නම් (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            අතරතුර (child = av_opt_child_class_iterate(c, &iter))
                නම් (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    ආපසු o;
        } නැතහොත් {
            void *child = NULL;
            අතරතුර (child = av_opt_child_next(obj, child))
                නම් (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    ආපසු o;
        }
    }

    අතරතුර (o = av_opt_next(obj, o)) {
        නම් (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            නම් (target_obj) {
                නම් (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                නැතහොත්
                    *target_obj = NULL;
            }
            ආපසු o;
        }
    }
    ආපසු NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    නම් (c->child_next)
        ආපසු c->child_next(obj, prev);
    ආපසු NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    නම් (parent->child_class_iterate)
        ආපසු parent->child_class_iterate(iter);
    ආපසු NULL;
}

static පූර්ණ_සංඛ්‍යා opt_copy_elem(void *logctx, ga_nanaa AVOptionType type,
                         void *dst, const void *src)
{
    නම් (type == AV_OPT_TYPE_STRING) {
        const var_na *src_str = *(const var_na *const *)src;
        var_na         **dstp =  (var_na **)dst;
        නම් (*dstp != src_str)
            av_freep(dstp);
        නම් (src_str) {
            *dstp = av_strdup(src_str);
            නම් (!*dstp)
                ආපසු AVERROR(ENOMEM);
        }
    } නැතහොත් නම් (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        පූර්ණ_සංඛ්‍යා len = *(const පූර්ණ_සංඛ්‍යා *)(src8 + 1);
        නම් (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        නම් (len && !*dst8) {
            *(පූර්ණ_සංඛ්‍යා *)(dst8 + 1) = 0;
            ආපසු AVERROR(ENOMEM);
        }
        *(පූර්ණ_සංඛ්‍යා *)(dst8 + 1) = len;
    } නැතහොත් නම් (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } නැතහොත් නම් (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        නම් (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        ආපසු av_dict_copy(ddictp, sdict, 0);
    } නැතහොත් නම් (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        නම් (dlayout != slayout) {
            නම් (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            ආපසු av_channel_layout_copy(dst, src);
        }
    } නැතහොත් නම් (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } නැතහොත් {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ආපසු AVERROR(EINVAL);
    }

    ආපසු 0;
}

static පූර්ණ_සංඛ්‍යා opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    පූර්ණ_සංඛ්‍යා ret;

    නම් (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    නම් (!dst)
        ආපසු AVERROR(ENOMEM);

    සඳහා (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        නම් (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ආපසු ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    පූර්ණ_සංඛ්‍යා ret = 0;

    නම් (!src)
        ආපසු AVERROR(EINVAL);

    c = *(AVClass **)src;
    නම් (!c || c != *(AVClass **)dst)
        ආපසු AVERROR(EINVAL);

    අතරතුර ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        පූර්ණ_සංඛ්‍යා err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        නම් (err < 0)
            ret = err;
    }
    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_get_array_size(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags,
                          unsigned පූර්ණ_සංඛ්‍යා *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ආපසු AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_get_array(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags,
                     unsigned පූර්ණ_සංඛ්‍යා start_elem, unsigned පූර්ණ_සංඛ්‍යා nb_elems,
                     ga_nanaa AVOptionType out_type, void *out_val)
{
    const size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    const AVOption *o;
    void *target_obj;

    const void *parray;
    unsigned array_size;

    පූර්ණ_සංඛ්‍යා ret;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    නම් (!o || !target_obj)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    නම් (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ආපසු AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    නම් (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ආපසු AVERROR(EINVAL);

    සඳහා (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        නම් (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            නම් (ret < 0)
                goto fail;
        } නැතහොත් නම් (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, parimaa_na(buf), src, search_flags);
            නම් (ret < 0)
                goto fail;

            නම් (out == buf) {
                out = av_strdup(buf);
                නම් (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } නැතහොත් නම් (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            dviguu_na     num = 1.0;
            පූර්ණ_සංඛ්‍යා        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            නම් (ret < 0)
                goto fail;

            switch (out_type) {
            pak_sa AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:
                *(dviguu_na*)dst = num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (පූර්ණ_සංඛ්‍යා)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                bha_nga;
            default: av_assert0(0);
            }
        } නැතහොත්
            ආපසු AVERROR(ENOSYS);
    }

    ආපසු 0;
fail:
    සඳහා (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_set_array(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags,
                     unsigned පූර්ණ_සංඛ්‍යා start_elem, unsigned පූර්ණ_සංඛ්‍යා nb_elems,
                     ga_nanaa AVOptionType val_type, const void *val)
{
    const size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    const AVOption *o;
    const AVOptionArrayDef *arr;
    void *target_obj;

    void *parray;
    void *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    පූර්ණ_සංඛ්‍යා ret = 0;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    නම් (ret < 0)
        ආපසු ret;

    නම් (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ආපසු AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    නම් (start_elem > *array_size)
        ආපසු AVERROR(EINVAL);

    // compute new array size
    නම් (!val) {
        නම් (*array_size - start_elem < nb_elems)
            ආපසු AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } නැතහොත් නම් (search_flags & AV_OPT_ARRAY_REPLACE) {
        නම් (start_elem >= UINT_MAX - nb_elems)
            ආපසු AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } නැතහොත් {
        නම් (nb_elems >= UINT_MAX - *array_size)
            ආපසු AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    නම් (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ආපසු AVERROR(EINVAL);

    // desired operation is shrinking the array
    නම් (!val) {
        void *array = *(void**)parray;

        සඳහා (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        නම් (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            නම් (!array)
                ආපසු AVERROR(ENOMEM);

            *(void**)parray = array;
        } නැතහොත්
            av_freep(parray);

        *array_size = new_size;

        ආපසු 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    නම් (!new_elems)
        ආපසු AVERROR(ENOMEM);

    // convert/validate each new element
    සඳහා (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        dviguu_na     num = 1.0;
        පූර්ණ_සංඛ්‍යා        den = 1;
        int64_t intnum = 1;

        නම් (val_type == TYPE_BASE(o->type)) {
            පූර්ණ_සංඛ්‍යා err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            නම් (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            නම් (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } නැතහොත් නම් (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const var_na **)src, dst);
            නම් (ret < 0)
                goto fail;
        } නැතහොත් නම් (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            switch (val_type) {
            pak_sa AV_OPT_TYPE_INT:       intnum = *(පූර්ණ_සංඛ්‍යා*)src;                bha_nga;
            pak_sa AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            bha_nga;
            pak_sa AV_OPT_TYPE_FLOAT:     num    = *(float*)src;              bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:    num    = *(dviguu_na*)src;             bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   bha_nga;
            default: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            නම් (ret < 0)
                goto fail;
        } නැතහොත් {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    නම් (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } නැතහොත් {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        නම් (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        නම් (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            සඳහා (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } නැතහොත් {
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

    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const var_na *key, පූර්ණ_සංඛ්‍යා flags)
{
    පූර්ණ_සංඛ්‍යා ret;
    const AVClass *c = *(AVClass**)obj;
    පූර්ණ_සංඛ්‍යා (*callback)(AVOptionRanges **, void *obj, const var_na *key, පූර්ණ_සංඛ්‍යා flags) = c->query_ranges;

    නම් (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    නම් (ret >= 0) {
        නම් (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ආපසු ret;
}

පූර්ණ_සංඛ්‍යා av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const var_na *key, පූර්ණ_සංඛ්‍යා flags)
{
    AVOptionRanges *ranges = av_mallocz(parimaa_na(*ranges));
    AVOptionRange **range_array = av_mallocz(parimaa_na(void*));
    AVOptionRange *range = av_mallocz(parimaa_na(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    පූර්ණ_සංඛ්‍යා ret;

    *ranges_arg = NULL;

    නම් (!ranges || !range || !range_array || !field) {
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
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_COLOR:
        bha_nga;
    pak_sa AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->value_min = -1;
        range->value_max = INT_MAX;
        bha_nga;
    pak_sa AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        bha_nga;
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->value_min = 0;
        range->value_max = INT_MAX/8;
        bha_nga;
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->value_min = 1;
        range->value_max = INT_MAX;
        bha_nga;
    default:
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    *ranges_arg = ranges;
    ආපසු 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ආපසු ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    පූර්ණ_සංඛ්‍යා i;
    AVOptionRanges *ranges = *rangesp;

    නම් (!ranges)
        ආපසු;

    සඳහා (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        නම් (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

පූර්ණ_සංඛ්‍යා av_opt_is_set_to_default(void *obj, const AVOption *o)
{
    int64_t i64;
    dviguu_na d;
    AVRational q;
    පූර්ණ_සංඛ්‍යා ret, w, h;
    var_na *str;
    void *dst;

    නම් (!o || !obj)
        ආපසු AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    නම් (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const var_na *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        නම් (ret < 0)
            ආපසු ret;

        නම් (!!val != !!def)
            ret = 0;
        නැතහොත් නම් (val)
            ret = !strcmp(val, def);
        නැතහොත්
            ret = 1;

        av_freep(&val);

        ආපසු ret;
    }

    switch (o->type) {
    pak_sa AV_OPT_TYPE_CONST:
        ආපසු 1;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
        read_number(o, dst, NULL, NULL, &i64);
        ආපසු o->default_val.i64 == i64;
    pak_sa AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        නම් (o->default_val.str) {
            නම් ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ආපසු ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ආපසු ret;
    }
    pak_sa AV_OPT_TYPE_STRING:
        str = *(var_na **)dst;
        නම් (str == o->default_val.str) //2 NULLs
            ආපසු 1;
        නම් (!str || !o->default_val.str) //1 NULL
            ආපසු 0;
        ආපසු !strcmp(str, o->default_val.str);
    pak_sa AV_OPT_TYPE_DOUBLE:
        d = *(dviguu_na *)dst;
        ආපසු o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        ආපසු (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ආපසු !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    pak_sa AV_OPT_TYPE_BINARY: {
        sa_nracanaa {
            uint8_t *data;
            පූර්ණ_සංඛ්‍යා size;
        } tmp = {0};
        පූර්ණ_සංඛ්‍යා opt_size = *(පූර්ණ_සංඛ්‍යා *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        නම් (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ආපසු 1;
        නම් (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ආපසු 0;
        නම් (opt_size != strlen(o->default_val.str) / 2)
            ආපසු 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        නම් (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ආපසු ret;
    }
    pak_sa AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        නම් (ret < 0) {
            av_dict_free(&dict1);
            ආපසු ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } අතරතුර (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        ආපසු (!en1 && !en2);
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        නම් (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        නැතහොත් නම් ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ආපසු ret;
        ආපසු (w == *(පූර්ණ_සංඛ්‍යා *)dst) && (h == *((පූර්ණ_සංඛ්‍යා *)dst+1));
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        නම් (o->default_val.str) {
            නම් ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ආපසු ret;
        }
        ආපසු !av_cmp_q(*(AVRational*)dst, q);
    pak_sa AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        නම් (o->default_val.str) {
            නම් ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                ආපසු ret;
        }
        ආපසු !memcmp(color, dst, parimaa_na(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        bha_nga;
    }
    ආපසු AVERROR_PATCHWELCOME;
}

පූර්ණ_සංඛ්‍යා av_opt_is_set_to_default_by_name(void *obj, const var_na *name, පූර්ණ_සංඛ්‍යා search_flags)
{
    const AVOption *o;
    void *target;
    නම් (!obj)
        ආපසු AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    නම් (!o)
        ආපසු AVERROR_OPTION_NOT_FOUND;
    ආපසු av_opt_is_set_to_default(target, o);
}

static පූර්ණ_සංඛ්‍යා opt_serialize(void *obj, පූර්ණ_සංඛ්‍යා opt_flags, පූර්ණ_සංඛ්‍යා flags, පූර්ණ_සංඛ්‍යා *cnt,
                         AVBPrint *bprint, const var_na key_val_sep, const var_na pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    පූර්ණ_සංඛ්‍යා ret;
    const var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    නම් (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        අතරතුර (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            නම් (ret < 0)
                ආපසු ret;
        }

    අතරතුර (o = av_opt_next(obj, o)) {
        නම් (o->type == AV_OPT_TYPE_CONST)
            continue;
        නම් ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            නම් ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                නම් (o->flags == opt_flags)
                    continue;
            } නැතහොත් නම් ((o->flags & opt_flags) == opt_flags)
                continue;
        } නැතහොත් {
            නම් ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            නැතහොත් නම් (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        නම් (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        නම් ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            ආපසු ret;
        }
        නම් (buf) {
            නම් ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ආපසු 0;
}

පූර්ණ_සංඛ්‍යා av_opt_serialize(void *obj, පූර්ණ_සංඛ්‍යා opt_flags, පූර්ණ_සංඛ්‍යා flags, var_na **buffer,
                     const var_na key_val_sep, const var_na pairs_sep)
{
    AVBPrint bprint;
    පූර්ණ_සංඛ්‍යා ret, cnt = 0;

    නම් (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ආපසු AVERROR(EINVAL);
    }

    නම් (!obj || !buffer)
        ආපසු AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    නම් (ret < 0)
        ආපසු ret;

    ret = av_bprint_finalize(&bprint, buffer);
    නම් (ret < 0)
        ආපසු ret;
    ආපසු 0;
}
