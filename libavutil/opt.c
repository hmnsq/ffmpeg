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
    ᤀᤡ᤺ (!obj)
        ᤀᤡᤴ NULL;
    class = *(const AVClass**)obj;
    ᤀᤡ᤺ (!last && class && class->option && class->option[0].name)
        ᤀᤡᤴ class->option;
    ᤀᤡ᤺ (last && last[1].name)
        ᤀᤡᤴ ++last;
    ᤀᤡᤴ NULL;
}

static const sa_nracanaa {
    size_t      size;
    const var_na *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { parimaa_na(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { parimaa_na(puur_naa_nka),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { parimaa_na(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { parimaa_na(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { parimaa_na(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { parimaa_na(dviguu_na),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { parimaa_na(float),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { parimaa_na(var_na *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { parimaa_na(AVRational),     "<rational>" },
    [AV_OPT_TYPE_BINARY]        = { parimaa_na(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { parimaa_na(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { parimaa_na(puur_naa_nka[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { parimaa_na(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { parimaa_na(ga_nanaa AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { parimaa_na(ga_nanaa AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { parimaa_na(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { parimaa_na(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { parimaa_na(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { parimaa_na(puur_naa_nka),            "<boolean>" },
};

// option is plain old data
static puur_naa_nka opt_is_pod(ga_nanaa AVOptionType type)
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
        ᤀᤡᤴ 1;
    }
    ᤀᤡᤴ 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ᤀᤡᤴ (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ᤀᤡᤴ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    ᤀᤡᤴ (unsigned *)((const void * const *)parray + 1);
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
    for (unsigned i = 0; i < *count; i++)
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
static puur_naa_nka opt_set_init(void *obj, const var_na *name, puur_naa_nka search_flags,
                        puur_naa_nka require_type,
                        void **ptgt, const AVOption **po, void **pdst)
{
    void *logctx;
    const AVOption *o;
    void *tgt;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &tgt);
    ᤀᤡ᤺ (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;

    ᤀᤡ᤺ (o->flags & AV_OPT_FLAG_READONLY)
        ᤀᤡᤴ AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    ᤀᤡ᤺ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    ᤀᤡ᤺ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        ᤀᤡ᤺ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        ᤀᤡ᤺ (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            ᤀᤡ᤺ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        ᤀᤡ᤺ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ᤀᤡᤴ AVERROR(EINVAL);
        }
    }

    ᤀᤡ᤺ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ᤀᤡ᤺ (po)
        *po   = o;
    ᤀᤡ᤺ (ptgt)
        *ptgt = tgt;
    ᤀᤡ᤺ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    ᤀᤡᤴ 0;
}

static AVRational double_to_rational(dviguu_na d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ᤀᤡ᤺ ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ᤀᤡᤴ r;
}

static puur_naa_nka read_number(const AVOption *o, const void *dst, dviguu_na *num, puur_naa_nka *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned puur_naa_nka*)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ga_nanaa AVPixelFormat *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ga_nanaa AVSampleFormat *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_INT:
        *intnum = *(puur_naa_nka *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_UINT:
        *intnum = *(unsigned puur_naa_nka *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_DOUBLE:
        *num = *(dviguu_na *)dst;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        ᤀᤡᤴ 0;
    pak_sa AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ᤀᤡᤴ 0;
    }
    ᤀᤡᤴ AVERROR(EINVAL);
}

static puur_naa_nka write_number(void *obj, const AVOption *o, void *dst,
                        dviguu_na num, puur_naa_nka den, int64_t intnum,
                        puur_naa_nka ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    ᤀᤡ᤺ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        ᤀᤡᤴ AVERROR(ERANGE);
    }
    ᤀᤡ᤺ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        dviguu_na d = num*intnum/den;
        ᤀᤡ᤺ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            ᤀᤡᤴ AVERROR(ERANGE);
        }
    }

    ᤀᤡ᤺ (!dst)
        ᤀᤡᤴ 0;

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
        *(puur_naa_nka *)dst = llrint(num / den) * intnum;
        bha_nga;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:{
        dviguu_na d = num / den;
        ᤀᤡ᤺ (intnum == 1 && d == (dviguu_na)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ᤀᤡ᤺ᤆᤡ
            *(int64_t *)dst = llrint(d) * intnum;
        bha_nga;}
    pak_sa AV_OPT_TYPE_UINT64:{
        dviguu_na d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ᤀᤡ᤺ (intnum == 1 && d == (dviguu_na)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ᤀᤡ᤺ᤆᤡ {
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
        ᤀᤡ᤺ ((puur_naa_nka) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        ᤀᤡ᤺ᤆᤡ
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        bha_nga;
    default:
        ᤀᤡᤴ AVERROR(EINVAL);
    }
    ᤀᤡᤴ 0;
}

static puur_naa_nka hexchar2int(var_na c) {
    ᤀᤡ᤺ (c >= '0' && c <= '9')
        ᤀᤡᤴ c - '0';
    ᤀᤡ᤺ (c >= 'a' && c <= 'f')
        ᤀᤡᤴ c - 'a' + 10;
    ᤀᤡ᤺ (c >= 'A' && c <= 'F')
        ᤀᤡᤴ c - 'A' + 10;
    ᤀᤡᤴ -1;
}

static puur_naa_nka set_string_binary(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    puur_naa_nka *lendst;
    uint8_t *bin, *ptr;
    puur_naa_nka len;

    ᤀᤡ᤺ (dst) {
        lendst = (puur_naa_nka *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ᤀᤡ᤺ (!val || !(len = strlen(val)))
        ᤀᤡᤴ 0;

    ᤀᤡ᤺ (len & 1)
        ᤀᤡᤴ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ᤀᤡ᤺ (!ptr)
        ᤀᤡᤴ AVERROR(ENOMEM);
    ᤀᤠ᤺ (*val) {
        puur_naa_nka a = hexchar2int(*val++);
        puur_naa_nka b = hexchar2int(*val++);
        ᤀᤡ᤺ (a < 0 || b < 0) {
            av_free(bin);
            ᤀᤡᤴ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ᤀᤡ᤺ (dst) {
        *dst    = bin;
        *lendst = len;
    } ᤀᤡ᤺ᤆᤡ {
        av_free(bin);
    }

    ᤀᤡᤴ 0;
}

static puur_naa_nka set_string(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    ᤀᤡ᤺ (!dst)
        ᤀᤡᤴ 0;
    av_freep(dst);
    ᤀᤡ᤺ (!val)
        ᤀᤡᤴ 0;
    *dst = av_strdup(val);
    ᤀᤡᤴ *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

static puur_naa_nka set_string_number(void *obj, void *target_obj, const AVOption *o, const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    puur_naa_nka ret = 0;

    ᤀᤡ᤺ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        puur_naa_nka num, den;
        var_na c;
        ᤀᤡ᤺ (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            ᤀᤡ᤺ ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                ᤀᤡᤴ ret;
            ret = 0;
        }
    }

    for (;;) {
        puur_naa_nka i = 0;
        var_na buf[256];
        puur_naa_nka cmd = 0;
        dviguu_na d;
        int64_t intnum = 1;

        ᤀᤡ᤺ (type == AV_OPT_TYPE_FLAGS) {
            ᤀᤡ᤺ (*val == '+' || *val == '-')
                cmd = *(val++);
            for (; i < parimaa_na(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            puur_naa_nka res;
            puur_naa_nka ci = 0;
            dviguu_na const_values[64];
            const var_na * const_names[64];
            puur_naa_nka search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            const AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            ᤀᤡ᤺ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ᤀᤡ᤺ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ᤀᤡ᤺ᤆᤡ {
                ᤀᤡ᤺ (o->unit) {
                    for (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        ᤀᤡ᤺ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ᤀᤡ᤺ (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ᤀᤡᤴ AVERROR_PATCHWELCOME;
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
                ᤀᤡ᤺ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ᤀᤡᤴ res;
                }
            }
        }
        ᤀᤡ᤺ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned puur_naa_nka*)dst;
            ᤀᤡ᤺ (cmd == '+')
                d = intnum | (int64_t)d;
            ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ᤀᤡ᤺ ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            ᤀᤡᤴ ret;
        val += i;
        ᤀᤡ᤺ (!i || !*val)
            ᤀᤡᤴ 0;
    }
}

static puur_naa_nka set_string_image_size(void *obj, const AVOption *o, const var_na *val, puur_naa_nka *dst)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka tmp[2];
    puur_naa_nka ret;

    ᤀᤡ᤺ (!val || !strcmp(val, "none")) {
        ᤀᤡ᤺ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ᤀᤡᤴ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    ᤀᤡ᤺ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ᤀᤡᤴ ret;
    }
    ᤀᤡ᤺ (dst)
        memcpy(dst, tmp, parimaa_na(tmp));
    ᤀᤡᤴ ret;
}

static puur_naa_nka set_string_video_rate(void *obj, const AVOption *o, const var_na *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    puur_naa_nka ret = av_parse_video_rate(&tmp, val);
    ᤀᤡ᤺ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ᤀᤡ᤺ (dst)
        *dst = tmp;
    ᤀᤡᤴ ret;
}

static puur_naa_nka set_string_color(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka ret;

    ᤀᤡ᤺ (!val) {
        ᤀᤡᤴ 0;
    } ᤀᤡ᤺ᤆᤡ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ᤀᤡ᤺ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ᤀᤡᤴ ret;
        }
        ᤀᤡ᤺ (dst)
            memcpy(dst, tmp, parimaa_na(tmp));
        ᤀᤡᤴ ret;
    }
    ᤀᤡᤴ 0;
}

static const var_na *get_bool_name(puur_naa_nka val)
{
    ᤀᤡ᤺ (val < 0)
        ᤀᤡᤴ "auto";
    ᤀᤡᤴ val ? "true" : "false";
}

static puur_naa_nka set_string_bool(void *obj, const AVOption *o, const var_na *val, puur_naa_nka *dst)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka n;

    ᤀᤡ᤺ (!val)
        ᤀᤡᤴ 0;

    ᤀᤡ᤺ (!strcmp(val, "auto")) {
        n = -1;
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ᤀᤡ᤺ᤆᤡ {
        var_na *end = NULL;
        n = strtol(val, &end, 10);
        ᤀᤡ᤺ (val + strlen(val) != end)
            goto fail;
    }

    ᤀᤡ᤺ (n < o->min || n > o->max)
        goto fail;

    ᤀᤡ᤺ (dst)
    *dst = n;
    ᤀᤡᤴ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ᤀᤡᤴ AVERROR(EINVAL);
}

static puur_naa_nka set_string_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst,
                          puur_naa_nka fmt_nb, puur_naa_nka ((*get_fmt)(const var_na *)), const var_na *desc,
                          ga_nanaa AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka fmt, min, max;

    ᤀᤡ᤺ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ᤀᤡ᤺ᤆᤡ {
        fmt = get_fmt(val);
        ᤀᤡ᤺ (fmt == -1) {
            var_na *tail;
            fmt = strtol(val, &tail, 0);
            ᤀᤡ᤺ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ᤀᤡᤴ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ᤀᤡ᤺(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ᤀᤡ᤺ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ᤀᤡᤴ AVERROR(ERANGE);
    }

    ᤀᤡ᤺ (dst)
    switch (type) {
    pak_sa AV_OPT_TYPE_PIXEL_FMT:  *(ga_nanaa AVPixelFormat *)dst = fmt; bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT: *(ga_nanaa AVSampleFormat*)dst = fmt; bha_nga;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ᤀᤡᤴ 0;
}

static puur_naa_nka get_pix_fmt(const var_na *name)
{
    ᤀᤡᤴ av_get_pix_fmt(name);
}

static puur_naa_nka set_string_pixel_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ᤀᤡᤴ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static puur_naa_nka get_sample_fmt(const var_na *name)
{
    ᤀᤡᤴ av_get_sample_fmt(name);
}

static puur_naa_nka set_string_sample_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ᤀᤡᤴ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static puur_naa_nka set_string_dict(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    ᤀᤡ᤺ (val) {
        puur_naa_nka ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ᤀᤡ᤺ (ret < 0) {
            av_dict_free(&options);
            ᤀᤡᤴ ret;
        }
    }

    ᤀᤡ᤺ (!dst) {
        av_dict_free(&options);
        ᤀᤡᤴ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ᤀᤡᤴ 0;
}

static puur_naa_nka set_string_channel_layout(void *obj, const AVOption *o,
                                     const var_na *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    puur_naa_nka ret;
    ᤀᤡ᤺ (dst)
    av_channel_layout_uninit(channel_layout);
    ᤀᤡ᤺ᤆᤡ
        channel_layout = &tmp;
    ᤀᤡ᤺ (!val)
        ᤀᤡᤴ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;
    ᤀᤡ᤺ (!dst)
        av_channel_layout_uninit(channel_layout);
    ᤀᤡᤴ 0;
}

static puur_naa_nka opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    puur_naa_nka ret;

    ᤀᤡ᤺ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ᤀᤡᤴ AVERROR(EINVAL);

    switch (type) {
    pak_sa AV_OPT_TYPE_BOOL:
        ᤀᤡᤴ set_string_bool(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_STRING:
        ᤀᤡᤴ set_string(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_BINARY:
        ᤀᤡᤴ set_string_binary(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_RATIONAL:
        ᤀᤡᤴ set_string_number(obj, target_obj, o, val, dst);
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ᤀᤡᤴ set_string_image_size(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        ᤀᤡ᤺ (ret < 0)
            ᤀᤡᤴ ret;
        ᤀᤡᤴ write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        ᤀᤡᤴ set_string_pixel_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        ᤀᤡᤴ set_string_sample_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ᤀᤡ᤺ (val) {
                ᤀᤡ᤺ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ᤀᤡᤴ ret;
                }
            }
            ᤀᤡ᤺ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ᤀᤡᤴ AVERROR(ERANGE);
            }
            ᤀᤡ᤺ (dst)
            *(int64_t *)dst = usecs;
            ᤀᤡᤴ 0;
        }
    pak_sa AV_OPT_TYPE_COLOR:
        ᤀᤡᤴ set_string_color(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        ᤀᤡ᤺ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ᤀᤡᤴ ret;
    pak_sa AV_OPT_TYPE_DICT:
        ᤀᤡᤴ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ᤀᤡᤴ AVERROR(EINVAL);
}

static puur_naa_nka opt_set_array(void *obj, void *target_obj, const AVOption *o,
                         const var_na *val, void *dst)
{
    const AVOptionArrayDef *arr = o->default_val.arr;
    const size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    const uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = NULL;

    void      *logctx = dst ? obj : NULL;
    void       *elems = NULL;
    unsigned nb_elems = 0;
    puur_naa_nka ret;

    ᤀᤡ᤺ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        ᤀᤡ᤺ (!str)
            ᤀᤡᤴ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ᤀᤠ᤺ (val && *val) {
        uint8_t *p = str;
        void *tmp;

        ᤀᤡ᤺ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        for (; *val; val++, p++) {
            ᤀᤡ᤺ (*val == '\\' && val[1])
                val++;
            ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (*val == sep) {
                val++;
                bha_nga;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        ᤀᤡ᤺ (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        ᤀᤡ᤺ (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    ᤀᤡ᤺ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ᤀᤡ᤺ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    ᤀᤡ᤺ (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ᤀᤡ᤺ᤆᤡ
        opt_free_array(o, &elems, &nb_elems);

    ᤀᤡᤴ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_set(void *obj, const var_na *name, const var_na *val, puur_naa_nka search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ᤀᤡᤴ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
puur_naa_nka av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const var_na *val, vartype *name ## _out)        \
{                                                                       \
    ᤀᤡ᤺ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ᤀᤡᤴ AVERROR(EINVAL);                                         \
    ᤀᤡᤴ set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    puur_naa_nka)
OPT_EVAL_NUMBER(puur_naa_nka,    AV_OPT_TYPE_INT,      puur_naa_nka)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(float,  AV_OPT_TYPE_FLOAT,    float)
OPT_EVAL_NUMBER(dviguu_na, AV_OPT_TYPE_DOUBLE,   dviguu_na)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

static puur_naa_nka set_number(void *obj, const var_na *name, dviguu_na num, puur_naa_nka den, int64_t intnum,
                      puur_naa_nka search_flags, puur_naa_nka require_type)
{
    void *dst;
    const AVOption *o;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, require_type, NULL, &o, &dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;
    ᤀᤡ᤺ (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_set_int(void *obj, const var_na *name, int64_t val, puur_naa_nka search_flags)
{
    ᤀᤡᤴ set_number(obj, name, 1, 1, val, search_flags, 0);
}

puur_naa_nka av_opt_set_double(void *obj, const var_na *name, dviguu_na val, puur_naa_nka search_flags)
{
    ᤀᤡᤴ set_number(obj, name, val, 1, 1, search_flags, 0);
}

puur_naa_nka av_opt_set_q(void *obj, const var_na *name, AVRational val, puur_naa_nka search_flags)
{
    ᤀᤡᤴ set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

puur_naa_nka av_opt_set_bin(void *obj, const var_na *name, const uint8_t *val, puur_naa_nka len, puur_naa_nka search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    puur_naa_nka *lendst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (dst) {
    ptr = len ? av_malloc(len) : NULL;
    ᤀᤡ᤺ (len && !ptr)
        ᤀᤡᤴ AVERROR(ENOMEM);

    lendst = (puur_naa_nka *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ᤀᤡ᤺ (len)
        memcpy(ptr, val, len);
    }

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_set_image_size(void *obj, const var_na *name, puur_naa_nka w, puur_naa_nka h, puur_naa_nka search_flags)
{
    const AVOption *o;
    void *logctx;
    puur_naa_nka *dst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    logctx = dst ? obj : NULL;

    ᤀᤡ᤺ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    ᤀᤡ᤺ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_set_video_rate(void *obj, const var_na *name, AVRational val, puur_naa_nka search_flags)
{
    ᤀᤡᤴ set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static puur_naa_nka set_format(void *obj, const var_na *name, puur_naa_nka fmt, puur_naa_nka search_flags,
                      ga_nanaa AVOptionType type, const var_na *desc, puur_naa_nka nb_fmts)
{
    const AVOption *o;
    void *logctx;
    puur_naa_nka *dst;
    puur_naa_nka min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ᤀᤡ᤺ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ᤀᤡᤴ AVERROR(ERANGE);
    }
    ᤀᤡ᤺ (dst)
    *dst = fmt;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_set_pixel_fmt(void *obj, const var_na *name, ga_nanaa AVPixelFormat fmt, puur_naa_nka search_flags)
{
    ᤀᤡᤴ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

puur_naa_nka av_opt_set_sample_fmt(void *obj, const var_na *name, ga_nanaa AVSampleFormat fmt, puur_naa_nka search_flags)
{
    ᤀᤡᤴ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

puur_naa_nka av_opt_set_dict_val(void *obj, const var_na *name, const AVDictionary *val,
                        puur_naa_nka search_flags)
{
    AVDictionary **dst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_set_chlayout(void *obj, const var_na *name,
                        const AVChannelLayout *channel_layout,
                        puur_naa_nka search_flags)
{
    AVChannelLayout *dst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ᤀᤡᤴ ret;
}

static void format_duration(var_na *buf, size_t size, int64_t d)
{
    var_na *e;

    av_assert0(size >= 25);
    ᤀᤡ᤺ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    ᤀᤡ᤺ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (puur_naa_nka)((d / 60000000) % 60),
                 (puur_naa_nka)((d / 1000000) % 60),
                 (puur_naa_nka)(d % 1000000));
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (puur_naa_nka)(d / 60000000),
                 (puur_naa_nka)((d / 1000000) % 60),
                 (puur_naa_nka)(d % 1000000));
    ᤀᤡ᤺ᤆᤡ
        snprintf(buf, size, "%d.%06d",
                 (puur_naa_nka)(d / 1000000),
                 (puur_naa_nka)(d % 1000000));
    e = buf + strlen(buf);
    ᤀᤠ᤺ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ᤀᤡ᤺ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

static puur_naa_nka opt_get_elem(const AVOption *o, uint8_t **pbuf, size_t buf_len,
                        const void *dst, puur_naa_nka search_flags)
{
    puur_naa_nka ret;

    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(puur_naa_nka *)dst));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(puur_naa_nka *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(puur_naa_nka *)dst);
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
        ᤀᤡ᤺ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            ᤀᤡᤴ 0;
        } ᤀᤡ᤺ᤆᤡ {
            *pbuf = av_strdup("");
        }
        ᤀᤡᤴ *pbuf ? 0 : AVERROR(ENOMEM);
    pak_sa AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        puur_naa_nka len;

        ᤀᤡ᤺ (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ᤀᤡᤴ 0;
        }
        len = *(puur_naa_nka *)(((uint8_t *)dst) + parimaa_na(uint8_t *));
        ᤀᤡ᤺ ((uint64_t)len * 2 + 1 > INT_MAX)
            ᤀᤡᤴ AVERROR(EINVAL);
        ᤀᤡ᤺ (!(*pbuf = av_malloc(len * 2 + 1)))
            ᤀᤡᤴ AVERROR(ENOMEM);
        ᤀᤡ᤺ (!len) {
            *pbuf[0] = '\0';
            ᤀᤡᤴ 0;
        }
        bin = *(uint8_t **)dst;
        for (puur_naa_nka i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ᤀᤡᤴ 0;
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((puur_naa_nka *)dst)[0], ((puur_naa_nka *)dst)[1]);
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
                       (puur_naa_nka)((uint8_t *)dst)[0], (puur_naa_nka)((uint8_t *)dst)[1],
                       (puur_naa_nka)((uint8_t *)dst)[2], (puur_naa_nka)((uint8_t *)dst)[3]);
        bha_nga;
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        bha_nga;
    pak_sa AV_OPT_TYPE_DICT:
        ᤀᤡ᤺ (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ᤀᤡᤴ 0;
        }
        ᤀᤡᤴ av_dict_get_string(*(AVDictionary **)dst, (var_na **)pbuf, '=', ':');
    default:
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    ᤀᤡᤴ ret;
}

static puur_naa_nka opt_get_array(const AVOption *o, void *dst, uint8_t **out_val)
{
    const unsigned count = *opt_array_pcount(dst);
    const uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = NULL;
    size_t   str_len = 0;
    puur_naa_nka ret;

    *out_val = NULL;

    for (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, parimaa_na(buf),
                           opt_array_pelem(o, *(void **)dst, i), 0);
        ᤀᤡ᤺ (ret < 0)
            goto fail;

        out_len = strlen(out);
        ᤀᤡ᤺ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        ᤀᤡ᤺ (ret < 0)
            goto fail;

        // add separator if needed
        ᤀᤡ᤺ (i)
            str[str_len++] = sep;

        // escape the element
        for (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            ᤀᤡ᤺ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ᤀᤡ᤺ (out != buf)
            av_freep(&out);
        ᤀᤡ᤺ (ret < 0) {
            av_freep(&str);
            ᤀᤡᤴ ret;
        }
    }

    *out_val = str;

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get(void *obj, const var_na *name, puur_naa_nka search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    puur_naa_nka ret;

    ᤀᤡ᤺ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;

    ᤀᤡ᤺ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    ᤀᤡ᤺ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        ᤀᤡ᤺ (ret < 0)
            ᤀᤡᤴ ret;
        ᤀᤡ᤺ (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            ᤀᤡ᤺ (!*out_val)
               ᤀᤡᤴ AVERROR(ENOMEM);
        }
        ᤀᤡᤴ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, parimaa_na(buf), dst, search_flags);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;
    ᤀᤡ᤺ (out != buf) {
        *out_val = out;
        ᤀᤡᤴ 0;
    }

    ᤀᤡ᤺ (ret >= parimaa_na(buf))
        ᤀᤡᤴ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ᤀᤡᤴ *out_val ? 0 : AVERROR(ENOMEM);
}

static puur_naa_nka get_number(void *obj, const var_na *name, dviguu_na *num, puur_naa_nka *den, int64_t *intnum,
                      puur_naa_nka search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ᤀᤡᤴ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ᤀᤡᤴ read_number(o, dst, num, den, intnum);
}

puur_naa_nka av_opt_get_int(void *obj, const var_na *name, puur_naa_nka search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    puur_naa_nka ret, den = 1;

    ᤀᤡ᤺ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ᤀᤡᤴ ret;
    ᤀᤡ᤺ (num == den)
        *out_val = intnum;
    ᤀᤡ᤺ᤆᤡ
        *out_val = num * intnum / den;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_double(void *obj, const var_na *name, puur_naa_nka search_flags, dviguu_na *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    puur_naa_nka ret, den = 1;

    ᤀᤡ᤺ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ᤀᤡᤴ ret;
    *out_val = num * intnum / den;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_q(void *obj, const var_na *name, puur_naa_nka search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    puur_naa_nka ret, den = 1;

    ᤀᤡ᤺ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (num == 1.0 && (puur_naa_nka)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    ᤀᤡ᤺ᤆᤡ
        *out_val = double_to_rational(num*intnum/den);
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_image_size(void *obj, const var_na *name, puur_naa_nka search_flags, puur_naa_nka *w_out, puur_naa_nka *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ᤀᤡ᤺ (w_out) *w_out = *(puur_naa_nka *)dst;
    ᤀᤡ᤺ (h_out) *h_out = *((puur_naa_nka *)dst+1);
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_video_rate(void *obj, const var_na *name, puur_naa_nka search_flags, AVRational *out_val)
{
    ᤀᤡᤴ av_opt_get_q(obj, name, search_flags, out_val);
}

static puur_naa_nka get_format(void *obj, const var_na *name, puur_naa_nka search_flags, void *out_fmt,
                      ga_nanaa AVOptionType type, const var_na *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ᤀᤡ᤺ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ga_nanaa AVPixelFormat *)out_fmt = *(ga_nanaa AVPixelFormat *)dst;
    ᤀᤡ᤺ᤆᤡ
        *(ga_nanaa AVSampleFormat*)out_fmt = *(ga_nanaa AVSampleFormat*)dst;

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_pixel_fmt(void *obj, const var_na *name, puur_naa_nka search_flags, ga_nanaa AVPixelFormat *out_fmt)
{
    ᤀᤡᤴ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

puur_naa_nka av_opt_get_sample_fmt(void *obj, const var_na *name, puur_naa_nka search_flags, ga_nanaa AVSampleFormat *out_fmt)
{
    ᤀᤡᤴ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

puur_naa_nka av_opt_get_chlayout(void *obj, const var_na *name, puur_naa_nka search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ᤀᤡᤴ av_channel_layout_copy(cl, dst);
}

puur_naa_nka av_opt_get_dict_val(void *obj, const var_na *name, puur_naa_nka search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (o->type != AV_OPT_TYPE_DICT)
        ᤀᤡᤴ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ᤀᤡᤴ av_dict_copy(out_val, src, 0);
}

puur_naa_nka av_opt_flag_is_set(void *obj, const var_na *field_name, const var_na *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    ᤀᤡ᤺ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ᤀᤡᤴ 0;
    ᤀᤡᤴ res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, puur_naa_nka level, int64_t i)
{
    ᤀᤡ᤺ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ᤀᤡ᤺ᤆᤡ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, puur_naa_nka level, dviguu_na d)
{
    ᤀᤡ᤺      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == (dviguu_na)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ᤀᤡ᤺ᤆᤡ {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const var_na *get_opt_const_name(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;

    ᤀᤡ᤺ (!unit)
        ᤀᤡᤴ NULL;
    ᤀᤠ᤺ ((opt = av_opt_next(obj, opt)))
        ᤀᤡ᤺ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            ᤀᤡᤴ opt->name;
    ᤀᤡᤴ NULL;
}

static var_na *get_opt_flags_string(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;
    var_na flags[512];

    flags[0] = 0;
    ᤀᤡ᤺ (!unit)
        ᤀᤡᤴ NULL;
    ᤀᤠ᤺ ((opt = av_opt_next(obj, opt))) {
        ᤀᤡ᤺ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            ᤀᤡ᤺ (flags[0])
                av_strlcatf(flags, parimaa_na(flags), "+");
            av_strlcatf(flags, parimaa_na(flags), "%s", opt->name);
        }
    }
    ᤀᤡ᤺ (flags[0])
        ᤀᤡᤴ av_strdup(flags);
    ᤀᤡᤴ NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     ga_nanaa AVOptionType parent_type)
{
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    ᤀᤡ᤺ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ᤀᤡ᤺ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ᤀᤡ᤺ᤆᤡ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ᤀᤡ᤺ᤆᤡ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    ᤀᤡ᤺ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        ᤀᤡᤴ;
    ᤀᤡ᤺ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ᤀᤡᤴ;

    ᤀᤡ᤺ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        ᤀᤡ᤺ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ᤀᤡᤴ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    pak_sa AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS: {
        var_na *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ᤀᤡ᤺ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ᤀᤡ᤺ᤆᤡ {
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
        ᤀᤡ᤺ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ᤀᤡ᤺ᤆᤡ
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
                     puur_naa_nka req_flags, puur_naa_nka rej_flags, ga_nanaa AVOptionType parent_type)
{
    const AVOption *opt = NULL;
    AVOptionRanges *r;
    puur_naa_nka i;

    ᤀᤠ᤺ ((opt = av_opt_next(obj, opt))) {
        ᤀᤡ᤺ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ᤀᤡ᤺ (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ᤀᤡ᤺ᤆᤡ
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

        ᤀᤡ᤺ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ᤀᤡ᤺ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
            switch (opt->type) {
            pak_sa AV_OPT_TYPE_INT:
            pak_sa AV_OPT_TYPE_UINT:
            pak_sa AV_OPT_TYPE_INT64:
            pak_sa AV_OPT_TYPE_UINT64:
            pak_sa AV_OPT_TYPE_DOUBLE:
            pak_sa AV_OPT_TYPE_FLOAT:
            pak_sa AV_OPT_TYPE_RATIONAL:
                for (i = 0; i < r->nb_ranges; i++) {
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
        ᤀᤡ᤺ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

puur_naa_nka av_opt_show2(void *obj, void *av_log_obj, puur_naa_nka req_flags, puur_naa_nka rej_flags)
{
    ᤀᤡ᤺ (!obj)
        ᤀᤡᤴ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    ᤀᤡᤴ 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, puur_naa_nka mask, puur_naa_nka flags)
{
    const AVOption *opt = NULL;
    ᤀᤠ᤺ ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        ᤀᤡ᤺ ((opt->flags & mask) != flags)
            continue;

        ᤀᤡ᤺ (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        ᤀᤡ᤺ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const var_na              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ᤀᤡ᤺ (arr && arr->def)
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
static puur_naa_nka parse_key_value_pair(void *ctx, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val;
    puur_naa_nka ret;

    ᤀᤡ᤺ (!key)
        ᤀᤡᤴ AVERROR(ENOMEM);

    ᤀᤡ᤺ (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        ᤀᤡ᤺ (!val) {
            av_freep(&key);
            ᤀᤡᤴ AVERROR(ENOMEM);
        }
    } ᤀᤡ᤺ᤆᤡ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    ᤀᤡ᤺ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    ᤀᤡᤴ ret;
}

puur_naa_nka av_set_options_string(void *ctx, const var_na *opts,
                          const var_na *key_val_sep, const var_na *pairs_sep)
{
    puur_naa_nka ret, count = 0;

    ᤀᤡ᤺ (!opts)
        ᤀᤡᤴ 0;

    ᤀᤠ᤺ (*opts) {
        ᤀᤡ᤺ ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            ᤀᤡᤴ ret;
        count++;

        ᤀᤡ᤺ (*opts)
            opts++;
    }

    ᤀᤡᤴ count;
}

#define WHITESPACES " \n\t\r"

static puur_naa_nka is_key_char(var_na c)
{
    ᤀᤡᤴ (unsigned)((c | 32) - 'a') < 26 ||
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
static puur_naa_nka get_key(const var_na **ropts, const var_na *delim, var_na **rkey)
{
    const var_na *opts = *ropts;
    const var_na *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    ᤀᤠ᤺ (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    ᤀᤡ᤺ (!*opts || !strchr(delim, *opts))
        ᤀᤡᤴ AVERROR(EINVAL);
    opts++;
    ᤀᤡ᤺ (!(*rkey = av_malloc(key_end - key_start + 1)))
        ᤀᤡᤴ AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_key_value(const var_na **ropts,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         unsigned flags,
                         var_na **rkey, var_na **rval)
{
    puur_naa_nka ret;
    var_na *key = NULL, *val;
    const var_na *opts = *ropts;

    ᤀᤡ᤺ ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        ᤀᤡᤴ AVERROR(EINVAL);
    ᤀᤡ᤺ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        ᤀᤡᤴ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_set_from_string(void *ctx, const var_na *opts,
                           const var_na *const *shorthand,
                           const var_na *key_val_sep, const var_na *pairs_sep)
{
    puur_naa_nka ret, count = 0;
    const var_na *dummy_shorthand = NULL;
    const var_na *key;

    ᤀᤡ᤺ (!opts)
        ᤀᤡᤴ 0;
    ᤀᤡ᤺ (!shorthand)
        shorthand = &dummy_shorthand;

    ᤀᤠ᤺ (*opts) {
        var_na *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        ᤀᤡ᤺ (ret < 0) {
            ᤀᤡ᤺ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ᤀᤡ᤺ᤆᤡ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ᤀᤡᤴ ret;
        }
        ᤀᤡ᤺ (*opts)
            opts++;
        ᤀᤡ᤺ (parsed_key) {
            key = parsed_key;
            ᤀᤠ᤺ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ᤀᤡ᤺ᤆᤡ {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        ᤀᤡ᤺ ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            ᤀᤡ᤺ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            ᤀᤡᤴ ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    ᤀᤡᤴ count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    ᤀᤠ᤺ ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        ᤀᤡ᤺ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ᤀᤡ᤺ᤆᤡ
            opt_free_elem(o->type, pitem);
    }
}

puur_naa_nka av_opt_set_dict2(void *obj, AVDictionary **options, puur_naa_nka search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    puur_naa_nka ret;

    ᤀᤡ᤺ (!options)
        ᤀᤡᤴ 0;

    ᤀᤠ᤺ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        ᤀᤡ᤺ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        ᤀᤡ᤺ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            ᤀᤡᤴ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_set_dict(void *obj, AVDictionary **options)
{
    ᤀᤡᤴ av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const var_na *name, const var_na *unit,
                            puur_naa_nka opt_flags, puur_naa_nka search_flags)
{
    ᤀᤡᤴ av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const var_na *name, const var_na *unit,
                             puur_naa_nka opt_flags, puur_naa_nka search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    ᤀᤡ᤺(!obj)
        ᤀᤡᤴ NULL;

    c= *(AVClass**)obj;

    ᤀᤡ᤺ (!c)
        ᤀᤡᤴ NULL;

    ᤀᤡ᤺ (search_flags & AV_OPT_SEARCH_CHILDREN) {
        ᤀᤡ᤺ (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            ᤀᤠ᤺ (child = av_opt_child_class_iterate(c, &iter))
                ᤀᤡ᤺ (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    ᤀᤡᤴ o;
        } ᤀᤡ᤺ᤆᤡ {
            void *child = NULL;
            ᤀᤠ᤺ (child = av_opt_child_next(obj, child))
                ᤀᤡ᤺ (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    ᤀᤡᤴ o;
        }
    }

    ᤀᤠ᤺ (o = av_opt_next(obj, o)) {
        ᤀᤡ᤺ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ᤀᤡ᤺ (target_obj) {
                ᤀᤡ᤺ (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                ᤀᤡ᤺ᤆᤡ
                    *target_obj = NULL;
            }
            ᤀᤡᤴ o;
        }
    }
    ᤀᤡᤴ NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    ᤀᤡ᤺ (c->child_next)
        ᤀᤡᤴ c->child_next(obj, prev);
    ᤀᤡᤴ NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    ᤀᤡ᤺ (parent->child_class_iterate)
        ᤀᤡᤴ parent->child_class_iterate(iter);
    ᤀᤡᤴ NULL;
}

static puur_naa_nka opt_copy_elem(void *logctx, ga_nanaa AVOptionType type,
                         void *dst, const void *src)
{
    ᤀᤡ᤺ (type == AV_OPT_TYPE_STRING) {
        const var_na *src_str = *(const var_na *const *)src;
        var_na         **dstp =  (var_na **)dst;
        ᤀᤡ᤺ (*dstp != src_str)
            av_freep(dstp);
        ᤀᤡ᤺ (src_str) {
            *dstp = av_strdup(src_str);
            ᤀᤡ᤺ (!*dstp)
                ᤀᤡᤴ AVERROR(ENOMEM);
        }
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        puur_naa_nka len = *(const puur_naa_nka *)(src8 + 1);
        ᤀᤡ᤺ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ᤀᤡ᤺ (len && !*dst8) {
            *(puur_naa_nka *)(dst8 + 1) = 0;
            ᤀᤡᤴ AVERROR(ENOMEM);
        }
        *(puur_naa_nka *)(dst8 + 1) = len;
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ᤀᤡ᤺ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        ᤀᤡᤴ av_dict_copy(ddictp, sdict, 0);
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ᤀᤡ᤺ (dlayout != slayout) {
            ᤀᤡ᤺ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            ᤀᤡᤴ av_channel_layout_copy(dst, src);
        }
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } ᤀᤡ᤺ᤆᤡ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    ᤀᤡᤴ 0;
}

static puur_naa_nka opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    puur_naa_nka ret;

    ᤀᤡ᤺ (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    ᤀᤡ᤺ (!dst)
        ᤀᤡᤴ AVERROR(ENOMEM);

    for (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        ᤀᤡ᤺ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ᤀᤡᤴ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    puur_naa_nka ret = 0;

    ᤀᤡ᤺ (!src)
        ᤀᤡᤴ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ᤀᤡ᤺ (!c || c != *(AVClass **)dst)
        ᤀᤡᤴ AVERROR(EINVAL);

    ᤀᤠ᤺ ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        puur_naa_nka err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        ᤀᤡ᤺ (err < 0)
            ret = err;
    }
    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_get_array_size(void *obj, const var_na *name, puur_naa_nka search_flags,
                          unsigned puur_naa_nka *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ᤀᤡᤴ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_get_array(void *obj, const var_na *name, puur_naa_nka search_flags,
                     unsigned puur_naa_nka start_elem, unsigned puur_naa_nka nb_elems,
                     ga_nanaa AVOptionType out_type, void *out_val)
{
    const size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    const AVOption *o;
    void *target_obj;

    const void *parray;
    unsigned array_size;

    puur_naa_nka ret;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᤀᤡ᤺ (!o || !target_obj)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡ᤺ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ᤀᤡᤴ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    ᤀᤡ᤺ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ᤀᤡᤴ AVERROR(EINVAL);

    for (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        ᤀᤡ᤺ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            ᤀᤡ᤺ (ret < 0)
                goto fail;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, parimaa_na(buf), src, search_flags);
            ᤀᤡ᤺ (ret < 0)
                goto fail;

            ᤀᤡ᤺ (out == buf) {
                out = av_strdup(buf);
                ᤀᤡ᤺ (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            dviguu_na     num = 1.0;
            puur_naa_nka        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            ᤀᤡ᤺ (ret < 0)
                goto fail;

            switch (out_type) {
            pak_sa AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:
                *(dviguu_na*)dst = num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (puur_naa_nka)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                bha_nga;
            default: av_assert0(0);
            }
        } ᤀᤡ᤺ᤆᤡ
            ᤀᤡᤴ AVERROR(ENOSYS);
    }

    ᤀᤡᤴ 0;
fail:
    for (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_set_array(void *obj, const var_na *name, puur_naa_nka search_flags,
                     unsigned puur_naa_nka start_elem, unsigned puur_naa_nka nb_elems,
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

    puur_naa_nka ret = 0;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ᤀᤡ᤺ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ᤀᤡᤴ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    ᤀᤡ᤺ (start_elem > *array_size)
        ᤀᤡᤴ AVERROR(EINVAL);

    // compute new array size
    ᤀᤡ᤺ (!val) {
        ᤀᤡ᤺ (*array_size - start_elem < nb_elems)
            ᤀᤡᤴ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (search_flags & AV_OPT_ARRAY_REPLACE) {
        ᤀᤡ᤺ (start_elem >= UINT_MAX - nb_elems)
            ᤀᤡᤴ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } ᤀᤡ᤺ᤆᤡ {
        ᤀᤡ᤺ (nb_elems >= UINT_MAX - *array_size)
            ᤀᤡᤴ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    ᤀᤡ᤺ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ᤀᤡᤴ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ᤀᤡ᤺ (!val) {
        void *array = *(void**)parray;

        for (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        ᤀᤡ᤺ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            ᤀᤡ᤺ (!array)
                ᤀᤡᤴ AVERROR(ENOMEM);

            *(void**)parray = array;
        } ᤀᤡ᤺ᤆᤡ
            av_freep(parray);

        *array_size = new_size;

        ᤀᤡᤴ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    ᤀᤡ᤺ (!new_elems)
        ᤀᤡᤴ AVERROR(ENOMEM);

    // convert/validate each new element
    for (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        dviguu_na     num = 1.0;
        puur_naa_nka        den = 1;
        int64_t intnum = 1;

        ᤀᤡ᤺ (val_type == TYPE_BASE(o->type)) {
            puur_naa_nka err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ᤀᤡ᤺ (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            ᤀᤡ᤺ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const var_na **)src, dst);
            ᤀᤡ᤺ (ret < 0)
                goto fail;
        } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            switch (val_type) {
            pak_sa AV_OPT_TYPE_INT:       intnum = *(puur_naa_nka*)src;                bha_nga;
            pak_sa AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            bha_nga;
            pak_sa AV_OPT_TYPE_FLOAT:     num    = *(float*)src;              bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:    num    = *(dviguu_na*)src;             bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   bha_nga;
            default: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            ᤀᤡ᤺ (ret < 0)
                goto fail;
        } ᤀᤡ᤺ᤆᤡ {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    ᤀᤡ᤺ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } ᤀᤡ᤺ᤆᤡ {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        ᤀᤡ᤺ (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        ᤀᤡ᤺ (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            for (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ᤀᤡ᤺ᤆᤡ {
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

    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const var_na *key, puur_naa_nka flags)
{
    puur_naa_nka ret;
    const AVClass *c = *(AVClass**)obj;
    puur_naa_nka (*callback)(AVOptionRanges **, void *obj, const var_na *key, puur_naa_nka flags) = c->query_ranges;

    ᤀᤡ᤺ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    ᤀᤡ᤺ (ret >= 0) {
        ᤀᤡ᤺ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ᤀᤡᤴ ret;
}

puur_naa_nka av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const var_na *key, puur_naa_nka flags)
{
    AVOptionRanges *ranges = av_mallocz(parimaa_na(*ranges));
    AVOptionRange **range_array = av_mallocz(parimaa_na(void*));
    AVOptionRange *range = av_mallocz(parimaa_na(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    puur_naa_nka ret;

    *ranges_arg = NULL;

    ᤀᤡ᤺ (!ranges || !range || !range_array || !field) {
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
    ᤀᤡᤴ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ᤀᤡᤴ ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    puur_naa_nka i;
    AVOptionRanges *ranges = *rangesp;

    ᤀᤡ᤺ (!ranges)
        ᤀᤡᤴ;

    for (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ᤀᤡ᤺ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

puur_naa_nka av_opt_is_set_to_default(void *obj, const AVOption *o)
{
    int64_t i64;
    dviguu_na d;
    AVRational q;
    puur_naa_nka ret, w, h;
    var_na *str;
    void *dst;

    ᤀᤡ᤺ (!o || !obj)
        ᤀᤡᤴ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    ᤀᤡ᤺ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const var_na *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ᤀᤡ᤺ (ret < 0)
            ᤀᤡᤴ ret;

        ᤀᤡ᤺ (!!val != !!def)
            ret = 0;
        ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (val)
            ret = !strcmp(val, def);
        ᤀᤡ᤺ᤆᤡ
            ret = 1;

        av_freep(&val);

        ᤀᤡᤴ ret;
    }

    switch (o->type) {
    pak_sa AV_OPT_TYPE_CONST:
        ᤀᤡᤴ 1;
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
        ᤀᤡᤴ o->default_val.i64 == i64;
    pak_sa AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ᤀᤡ᤺ (o->default_val.str) {
            ᤀᤡ᤺ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ᤀᤡᤴ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ᤀᤡᤴ ret;
    }
    pak_sa AV_OPT_TYPE_STRING:
        str = *(var_na **)dst;
        ᤀᤡ᤺ (str == o->default_val.str) //2 NULLs
            ᤀᤡᤴ 1;
        ᤀᤡ᤺ (!str || !o->default_val.str) //1 NULL
            ᤀᤡᤴ 0;
        ᤀᤡᤴ !strcmp(str, o->default_val.str);
    pak_sa AV_OPT_TYPE_DOUBLE:
        d = *(dviguu_na *)dst;
        ᤀᤡᤴ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        ᤀᤡᤴ (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ᤀᤡᤴ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    pak_sa AV_OPT_TYPE_BINARY: {
        sa_nracanaa {
            uint8_t *data;
            puur_naa_nka size;
        } tmp = {0};
        puur_naa_nka opt_size = *(puur_naa_nka *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        ᤀᤡ᤺ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ᤀᤡᤴ 1;
        ᤀᤡ᤺ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ᤀᤡᤴ 0;
        ᤀᤡ᤺ (opt_size != strlen(o->default_val.str) / 2)
            ᤀᤡᤴ 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        ᤀᤡ᤺ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ᤀᤡᤴ ret;
    }
    pak_sa AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ᤀᤡ᤺ (ret < 0) {
            av_dict_free(&dict1);
            ᤀᤡᤴ ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ᤀᤠ᤺ (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        ᤀᤡᤴ (!en1 && !en2);
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ᤀᤡ᤺ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ᤀᤡᤴ ret;
        ᤀᤡᤴ (w == *(puur_naa_nka *)dst) && (h == *((puur_naa_nka *)dst+1));
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        ᤀᤡ᤺ (o->default_val.str) {
            ᤀᤡ᤺ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ᤀᤡᤴ ret;
        }
        ᤀᤡᤴ !av_cmp_q(*(AVRational*)dst, q);
    pak_sa AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ᤀᤡ᤺ (o->default_val.str) {
            ᤀᤡ᤺ ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                ᤀᤡᤴ ret;
        }
        ᤀᤡᤴ !memcmp(color, dst, parimaa_na(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        bha_nga;
    }
    ᤀᤡᤴ AVERROR_PATCHWELCOME;
}

puur_naa_nka av_opt_is_set_to_default_by_name(void *obj, const var_na *name, puur_naa_nka search_flags)
{
    const AVOption *o;
    void *target;
    ᤀᤡ᤺ (!obj)
        ᤀᤡᤴ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    ᤀᤡ᤺ (!o)
        ᤀᤡᤴ AVERROR_OPTION_NOT_FOUND;
    ᤀᤡᤴ av_opt_is_set_to_default(target, o);
}

static puur_naa_nka opt_serialize(void *obj, puur_naa_nka opt_flags, puur_naa_nka flags, puur_naa_nka *cnt,
                         AVBPrint *bprint, const var_na key_val_sep, const var_na pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    puur_naa_nka ret;
    const var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ᤀᤡ᤺ (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        ᤀᤠ᤺ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            ᤀᤡ᤺ (ret < 0)
                ᤀᤡᤴ ret;
        }

    ᤀᤠ᤺ (o = av_opt_next(obj, o)) {
        ᤀᤡ᤺ (o->type == AV_OPT_TYPE_CONST)
            continue;
        ᤀᤡ᤺ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ᤀᤡ᤺ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ᤀᤡ᤺ (o->flags == opt_flags)
                    continue;
            } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ ((o->flags & opt_flags) == opt_flags)
                continue;
        } ᤀᤡ᤺ᤆᤡ {
            ᤀᤡ᤺ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        ᤀᤡ᤺ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        ᤀᤡ᤺ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            ᤀᤡᤴ ret;
        }
        ᤀᤡ᤺ (buf) {
            ᤀᤡ᤺ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ᤀᤡᤴ 0;
}

puur_naa_nka av_opt_serialize(void *obj, puur_naa_nka opt_flags, puur_naa_nka flags, var_na **buffer,
                     const var_na key_val_sep, const var_na pairs_sep)
{
    AVBPrint bprint;
    puur_naa_nka ret, cnt = 0;

    ᤀᤡ᤺ (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ᤀᤡᤴ AVERROR(EINVAL);
    }

    ᤀᤡ᤺ (!obj || !buffer)
        ᤀᤡᤴ AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    ᤀᤡ᤺ (ret < 0)
        ᤀᤡᤴ ret;
    ᤀᤡᤴ 0;
}
