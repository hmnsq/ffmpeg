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
    ᯀᯮᯝ (!obj)
        ᯀᯮᯞ NULL;
    class = *(const AVClass**)obj;
    ᯀᯮᯝ (!last && class && class->option && class->option[0].name)
        ᯀᯮᯞ class->option;
    ᯀᯮᯝ (last && last[1].name)
        ᯀᯮᯞ ++last;
    ᯀᯮᯞ NULL;
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
        ᯀᯮᯞ 1;
    }
    ᯀᯮᯞ 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ᯀᯮᯞ (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ᯀᯮᯞ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    ᯀᯮᯞ (unsigned *)((const void * const *)parray + 1);
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
    ᯀᯮᯝ (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;

    ᯀᯮᯝ (o->flags & AV_OPT_FLAG_READONLY)
        ᯀᯮᯞ AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    ᯀᯮᯝ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    ᯀᯮᯝ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        ᯀᯮᯝ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        ᯀᯮᯝ (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            ᯀᯮᯝ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        ᯀᯮᯝ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ᯀᯮᯞ AVERROR(EINVAL);
        }
    }

    ᯀᯮᯝ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ᯀᯮᯝ (po)
        *po   = o;
    ᯀᯮᯝ (ptgt)
        *ptgt = tgt;
    ᯀᯮᯝ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    ᯀᯮᯞ 0;
}

static AVRational double_to_rational(dviguu_na d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ᯀᯮᯝ ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ᯀᯮᯞ r;
}

static puur_naa_nka read_number(const AVOption *o, const void *dst, dviguu_na *num, puur_naa_nka *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned puur_naa_nka*)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ga_nanaa AVPixelFormat *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ga_nanaa AVSampleFormat *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_INT:
        *intnum = *(puur_naa_nka *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_UINT:
        *intnum = *(unsigned puur_naa_nka *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_DOUBLE:
        *num = *(dviguu_na *)dst;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        ᯀᯮᯞ 0;
    pak_sa AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ᯀᯮᯞ 0;
    }
    ᯀᯮᯞ AVERROR(EINVAL);
}

static puur_naa_nka write_number(void *obj, const AVOption *o, void *dst,
                        dviguu_na num, puur_naa_nka den, int64_t intnum,
                        puur_naa_nka ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    ᯀᯮᯝ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        ᯀᯮᯞ AVERROR(ERANGE);
    }
    ᯀᯮᯝ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        dviguu_na d = num*intnum/den;
        ᯀᯮᯝ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            ᯀᯮᯞ AVERROR(ERANGE);
        }
    }

    ᯀᯮᯝ (!dst)
        ᯀᯮᯞ 0;

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
        ᯀᯮᯝ (intnum == 1 && d == (dviguu_na)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ᯀᯮᯝᯂᯪ
            *(int64_t *)dst = llrint(d) * intnum;
        bha_nga;}
    pak_sa AV_OPT_TYPE_UINT64:{
        dviguu_na d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ᯀᯮᯝ (intnum == 1 && d == (dviguu_na)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ᯀᯮᯝᯂᯪ {
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
        ᯀᯮᯝ ((puur_naa_nka) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        ᯀᯮᯝᯂᯪ
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        bha_nga;
    default:
        ᯀᯮᯞ AVERROR(EINVAL);
    }
    ᯀᯮᯞ 0;
}

static puur_naa_nka hexchar2int(var_na c) {
    ᯀᯮᯝ (c >= '0' && c <= '9')
        ᯀᯮᯞ c - '0';
    ᯀᯮᯝ (c >= 'a' && c <= 'f')
        ᯀᯮᯞ c - 'a' + 10;
    ᯀᯮᯝ (c >= 'A' && c <= 'F')
        ᯀᯮᯞ c - 'A' + 10;
    ᯀᯮᯞ -1;
}

static puur_naa_nka set_string_binary(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    puur_naa_nka *lendst;
    uint8_t *bin, *ptr;
    puur_naa_nka len;

    ᯀᯮᯝ (dst) {
        lendst = (puur_naa_nka *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ᯀᯮᯝ (!val || !(len = strlen(val)))
        ᯀᯮᯞ 0;

    ᯀᯮᯝ (len & 1)
        ᯀᯮᯞ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ᯀᯮᯝ (!ptr)
        ᯀᯮᯞ AVERROR(ENOMEM);
    ᯀᯬᯝ (*val) {
        puur_naa_nka a = hexchar2int(*val++);
        puur_naa_nka b = hexchar2int(*val++);
        ᯀᯮᯝ (a < 0 || b < 0) {
            av_free(bin);
            ᯀᯮᯞ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ᯀᯮᯝ (dst) {
        *dst    = bin;
        *lendst = len;
    } ᯀᯮᯝᯂᯪ {
        av_free(bin);
    }

    ᯀᯮᯞ 0;
}

static puur_naa_nka set_string(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    ᯀᯮᯝ (!dst)
        ᯀᯮᯞ 0;
    av_freep(dst);
    ᯀᯮᯝ (!val)
        ᯀᯮᯞ 0;
    *dst = av_strdup(val);
    ᯀᯮᯞ *dst ? 0 : AVERROR(ENOMEM);
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

    ᯀᯮᯝ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        puur_naa_nka num, den;
        var_na c;
        ᯀᯮᯝ (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            ᯀᯮᯝ ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                ᯀᯮᯞ ret;
            ret = 0;
        }
    }

    for (;;) {
        puur_naa_nka i = 0;
        var_na buf[256];
        puur_naa_nka cmd = 0;
        dviguu_na d;
        int64_t intnum = 1;

        ᯀᯮᯝ (type == AV_OPT_TYPE_FLAGS) {
            ᯀᯮᯝ (*val == '+' || *val == '-')
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
            ᯀᯮᯝ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ᯀᯮᯝ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ᯀᯮᯝᯂᯪ {
                ᯀᯮᯝ (o->unit) {
                    for (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        ᯀᯮᯝ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ᯀᯮᯝ (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ᯀᯮᯞ AVERROR_PATCHWELCOME;
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
                ᯀᯮᯝ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ᯀᯮᯞ res;
                }
            }
        }
        ᯀᯮᯝ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned puur_naa_nka*)dst;
            ᯀᯮᯝ (cmd == '+')
                d = intnum | (int64_t)d;
            ᯀᯮᯝᯂᯪ ᯀᯮᯝ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ᯀᯮᯝ ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            ᯀᯮᯞ ret;
        val += i;
        ᯀᯮᯝ (!i || !*val)
            ᯀᯮᯞ 0;
    }
}

static puur_naa_nka set_string_image_size(void *obj, const AVOption *o, const var_na *val, puur_naa_nka *dst)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka tmp[2];
    puur_naa_nka ret;

    ᯀᯮᯝ (!val || !strcmp(val, "none")) {
        ᯀᯮᯝ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ᯀᯮᯞ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    ᯀᯮᯝ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ᯀᯮᯞ ret;
    }
    ᯀᯮᯝ (dst)
        memcpy(dst, tmp, parimaa_na(tmp));
    ᯀᯮᯞ ret;
}

static puur_naa_nka set_string_video_rate(void *obj, const AVOption *o, const var_na *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    puur_naa_nka ret = av_parse_video_rate(&tmp, val);
    ᯀᯮᯝ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ᯀᯮᯝ (dst)
        *dst = tmp;
    ᯀᯮᯞ ret;
}

static puur_naa_nka set_string_color(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka ret;

    ᯀᯮᯝ (!val) {
        ᯀᯮᯞ 0;
    } ᯀᯮᯝᯂᯪ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ᯀᯮᯝ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ᯀᯮᯞ ret;
        }
        ᯀᯮᯝ (dst)
            memcpy(dst, tmp, parimaa_na(tmp));
        ᯀᯮᯞ ret;
    }
    ᯀᯮᯞ 0;
}

static const var_na *get_bool_name(puur_naa_nka val)
{
    ᯀᯮᯝ (val < 0)
        ᯀᯮᯞ "auto";
    ᯀᯮᯞ val ? "true" : "false";
}

static puur_naa_nka set_string_bool(void *obj, const AVOption *o, const var_na *val, puur_naa_nka *dst)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka n;

    ᯀᯮᯝ (!val)
        ᯀᯮᯞ 0;

    ᯀᯮᯝ (!strcmp(val, "auto")) {
        n = -1;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ᯀᯮᯝᯂᯪ {
        var_na *end = NULL;
        n = strtol(val, &end, 10);
        ᯀᯮᯝ (val + strlen(val) != end)
            goto fail;
    }

    ᯀᯮᯝ (n < o->min || n > o->max)
        goto fail;

    ᯀᯮᯝ (dst)
    *dst = n;
    ᯀᯮᯞ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ᯀᯮᯞ AVERROR(EINVAL);
}

static puur_naa_nka set_string_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst,
                          puur_naa_nka fmt_nb, puur_naa_nka ((*get_fmt)(const var_na *)), const var_na *desc,
                          ga_nanaa AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    puur_naa_nka fmt, min, max;

    ᯀᯮᯝ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ᯀᯮᯝᯂᯪ {
        fmt = get_fmt(val);
        ᯀᯮᯝ (fmt == -1) {
            var_na *tail;
            fmt = strtol(val, &tail, 0);
            ᯀᯮᯝ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ᯀᯮᯞ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ᯀᯮᯝ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ᯀᯮᯝ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ᯀᯮᯞ AVERROR(ERANGE);
    }

    ᯀᯮᯝ (dst)
    switch (type) {
    pak_sa AV_OPT_TYPE_PIXEL_FMT:  *(ga_nanaa AVPixelFormat *)dst = fmt; bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT: *(ga_nanaa AVSampleFormat*)dst = fmt; bha_nga;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ᯀᯮᯞ 0;
}

static puur_naa_nka get_pix_fmt(const var_na *name)
{
    ᯀᯮᯞ av_get_pix_fmt(name);
}

static puur_naa_nka set_string_pixel_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ᯀᯮᯞ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static puur_naa_nka get_sample_fmt(const var_na *name)
{
    ᯀᯮᯞ av_get_sample_fmt(name);
}

static puur_naa_nka set_string_sample_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ᯀᯮᯞ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static puur_naa_nka set_string_dict(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    ᯀᯮᯝ (val) {
        puur_naa_nka ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ᯀᯮᯝ (ret < 0) {
            av_dict_free(&options);
            ᯀᯮᯞ ret;
        }
    }

    ᯀᯮᯝ (!dst) {
        av_dict_free(&options);
        ᯀᯮᯞ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ᯀᯮᯞ 0;
}

static puur_naa_nka set_string_channel_layout(void *obj, const AVOption *o,
                                     const var_na *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    puur_naa_nka ret;
    ᯀᯮᯝ (dst)
    av_channel_layout_uninit(channel_layout);
    ᯀᯮᯝᯂᯪ
        channel_layout = &tmp;
    ᯀᯮᯝ (!val)
        ᯀᯮᯞ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;
    ᯀᯮᯝ (!dst)
        av_channel_layout_uninit(channel_layout);
    ᯀᯮᯞ 0;
}

static puur_naa_nka opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    puur_naa_nka ret;

    ᯀᯮᯝ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ᯀᯮᯞ AVERROR(EINVAL);

    switch (type) {
    pak_sa AV_OPT_TYPE_BOOL:
        ᯀᯮᯞ set_string_bool(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_STRING:
        ᯀᯮᯞ set_string(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_BINARY:
        ᯀᯮᯞ set_string_binary(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_RATIONAL:
        ᯀᯮᯞ set_string_number(obj, target_obj, o, val, dst);
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ᯀᯮᯞ set_string_image_size(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;
        ᯀᯮᯞ write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        ᯀᯮᯞ set_string_pixel_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        ᯀᯮᯞ set_string_sample_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ᯀᯮᯝ (val) {
                ᯀᯮᯝ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ᯀᯮᯞ ret;
                }
            }
            ᯀᯮᯝ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ᯀᯮᯞ AVERROR(ERANGE);
            }
            ᯀᯮᯝ (dst)
            *(int64_t *)dst = usecs;
            ᯀᯮᯞ 0;
        }
    pak_sa AV_OPT_TYPE_COLOR:
        ᯀᯮᯞ set_string_color(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        ᯀᯮᯝ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ᯀᯮᯞ ret;
    pak_sa AV_OPT_TYPE_DICT:
        ᯀᯮᯞ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ᯀᯮᯞ AVERROR(EINVAL);
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

    ᯀᯮᯝ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        ᯀᯮᯝ (!str)
            ᯀᯮᯞ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ᯀᯬᯝ (val && *val) {
        uint8_t *p = str;
        void *tmp;

        ᯀᯮᯝ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        for (; *val; val++, p++) {
            ᯀᯮᯝ (*val == '\\' && val[1])
                val++;
            ᯀᯮᯝᯂᯪ ᯀᯮᯝ (*val == sep) {
                val++;
                bha_nga;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        ᯀᯮᯝ (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        ᯀᯮᯝ (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    ᯀᯮᯝ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ᯀᯮᯝ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    ᯀᯮᯝ (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ᯀᯮᯝᯂᯪ
        opt_free_array(o, &elems, &nb_elems);

    ᯀᯮᯞ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ᯀᯮᯞ ret;
}

puur_naa_nka av_opt_set(void *obj, const var_na *name, const var_na *val, puur_naa_nka search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    ᯀᯮᯞ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
puur_naa_nka av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const var_na *val, vartype *name ## _out)        \
{                                                                       \
    ᯀᯮᯝ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ᯀᯮᯞ AVERROR(EINVAL);                                         \
    ᯀᯮᯞ set_string_number(obj, obj, o, val, name ## _out);           \
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
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;
    ᯀᯮᯝ (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    ᯀᯮᯞ ret;
}

puur_naa_nka av_opt_set_int(void *obj, const var_na *name, int64_t val, puur_naa_nka search_flags)
{
    ᯀᯮᯞ set_number(obj, name, 1, 1, val, search_flags, 0);
}

puur_naa_nka av_opt_set_double(void *obj, const var_na *name, dviguu_na val, puur_naa_nka search_flags)
{
    ᯀᯮᯞ set_number(obj, name, val, 1, 1, search_flags, 0);
}

puur_naa_nka av_opt_set_q(void *obj, const var_na *name, AVRational val, puur_naa_nka search_flags)
{
    ᯀᯮᯞ set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

puur_naa_nka av_opt_set_bin(void *obj, const var_na *name, const uint8_t *val, puur_naa_nka len, puur_naa_nka search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    puur_naa_nka *lendst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    ᯀᯮᯝ (dst) {
    ptr = len ? av_malloc(len) : NULL;
    ᯀᯮᯝ (len && !ptr)
        ᯀᯮᯞ AVERROR(ENOMEM);

    lendst = (puur_naa_nka *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ᯀᯮᯝ (len)
        memcpy(ptr, val, len);
    }

    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_set_image_size(void *obj, const var_na *name, puur_naa_nka w, puur_naa_nka h, puur_naa_nka search_flags)
{
    const AVOption *o;
    void *logctx;
    puur_naa_nka *dst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    logctx = dst ? obj : NULL;

    ᯀᯮᯝ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    ᯀᯮᯝ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_set_video_rate(void *obj, const var_na *name, AVRational val, puur_naa_nka search_flags)
{
    ᯀᯮᯞ set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static puur_naa_nka set_format(void *obj, const var_na *name, puur_naa_nka fmt, puur_naa_nka search_flags,
                      ga_nanaa AVOptionType type, const var_na *desc, puur_naa_nka nb_fmts)
{
    const AVOption *o;
    void *logctx;
    puur_naa_nka *dst;
    puur_naa_nka min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ᯀᯮᯝ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ᯀᯮᯞ AVERROR(ERANGE);
    }
    ᯀᯮᯝ (dst)
    *dst = fmt;
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_set_pixel_fmt(void *obj, const var_na *name, ga_nanaa AVPixelFormat fmt, puur_naa_nka search_flags)
{
    ᯀᯮᯞ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

puur_naa_nka av_opt_set_sample_fmt(void *obj, const var_na *name, ga_nanaa AVSampleFormat fmt, puur_naa_nka search_flags)
{
    ᯀᯮᯞ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

puur_naa_nka av_opt_set_dict_val(void *obj, const var_na *name, const AVDictionary *val,
                        puur_naa_nka search_flags)
{
    AVDictionary **dst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    ᯀᯮᯝ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ᯀᯮᯞ ret;
}

puur_naa_nka av_opt_set_chlayout(void *obj, const var_na *name,
                        const AVChannelLayout *channel_layout,
                        puur_naa_nka search_flags)
{
    AVChannelLayout *dst;
    puur_naa_nka ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    ᯀᯮᯝ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ᯀᯮᯞ ret;
}

static void format_duration(var_na *buf, size_t size, int64_t d)
{
    var_na *e;

    av_assert0(size >= 25);
    ᯀᯮᯝ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    ᯀᯮᯝ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (puur_naa_nka)((d / 60000000) % 60),
                 (puur_naa_nka)((d / 1000000) % 60),
                 (puur_naa_nka)(d % 1000000));
    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (puur_naa_nka)(d / 60000000),
                 (puur_naa_nka)((d / 1000000) % 60),
                 (puur_naa_nka)(d % 1000000));
    ᯀᯮᯝᯂᯪ
        snprintf(buf, size, "%d.%06d",
                 (puur_naa_nka)(d / 1000000),
                 (puur_naa_nka)(d % 1000000));
    e = buf + strlen(buf);
    ᯀᯬᯝ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ᯀᯮᯝ (e > buf && e[-1] == '.')
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
        ᯀᯮᯝ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            ᯀᯮᯞ 0;
        } ᯀᯮᯝᯂᯪ {
            *pbuf = av_strdup("");
        }
        ᯀᯮᯞ *pbuf ? 0 : AVERROR(ENOMEM);
    pak_sa AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        puur_naa_nka len;

        ᯀᯮᯝ (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ᯀᯮᯞ 0;
        }
        len = *(puur_naa_nka *)(((uint8_t *)dst) + parimaa_na(uint8_t *));
        ᯀᯮᯝ ((uint64_t)len * 2 + 1 > INT_MAX)
            ᯀᯮᯞ AVERROR(EINVAL);
        ᯀᯮᯝ (!(*pbuf = av_malloc(len * 2 + 1)))
            ᯀᯮᯞ AVERROR(ENOMEM);
        ᯀᯮᯝ (!len) {
            *pbuf[0] = '\0';
            ᯀᯮᯞ 0;
        }
        bin = *(uint8_t **)dst;
        for (puur_naa_nka i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ᯀᯮᯞ 0;
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
        ᯀᯮᯝ (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ᯀᯮᯞ 0;
        }
        ᯀᯮᯞ av_dict_get_string(*(AVDictionary **)dst, (var_na **)pbuf, '=', ':');
    default:
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    ᯀᯮᯞ ret;
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
        ᯀᯮᯝ (ret < 0)
            goto fail;

        out_len = strlen(out);
        ᯀᯮᯝ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        ᯀᯮᯝ (ret < 0)
            goto fail;

        // add separator if needed
        ᯀᯮᯝ (i)
            str[str_len++] = sep;

        // escape the element
        for (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            ᯀᯮᯝ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ᯀᯮᯝ (out != buf)
            av_freep(&out);
        ᯀᯮᯝ (ret < 0) {
            av_freep(&str);
            ᯀᯮᯞ ret;
        }
    }

    *out_val = str;

    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get(void *obj, const var_na *name, puur_naa_nka search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    puur_naa_nka ret;

    ᯀᯮᯝ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;

    ᯀᯮᯝ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    ᯀᯮᯝ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;
        ᯀᯮᯝ (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            ᯀᯮᯝ (!*out_val)
               ᯀᯮᯞ AVERROR(ENOMEM);
        }
        ᯀᯮᯞ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, parimaa_na(buf), dst, search_flags);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;
    ᯀᯮᯝ (out != buf) {
        *out_val = out;
        ᯀᯮᯞ 0;
    }

    ᯀᯮᯝ (ret >= parimaa_na(buf))
        ᯀᯮᯞ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ᯀᯮᯞ *out_val ? 0 : AVERROR(ENOMEM);
}

static puur_naa_nka get_number(void *obj, const var_na *name, dviguu_na *num, puur_naa_nka *den, int64_t *intnum,
                      puur_naa_nka search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ᯀᯮᯞ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ᯀᯮᯞ read_number(o, dst, num, den, intnum);
}

puur_naa_nka av_opt_get_int(void *obj, const var_na *name, puur_naa_nka search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    puur_naa_nka ret, den = 1;

    ᯀᯮᯝ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ᯀᯮᯞ ret;
    ᯀᯮᯝ (num == den)
        *out_val = intnum;
    ᯀᯮᯝᯂᯪ
        *out_val = num * intnum / den;
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get_double(void *obj, const var_na *name, puur_naa_nka search_flags, dviguu_na *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    puur_naa_nka ret, den = 1;

    ᯀᯮᯝ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ᯀᯮᯞ ret;
    *out_val = num * intnum / den;
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get_q(void *obj, const var_na *name, puur_naa_nka search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    puur_naa_nka ret, den = 1;

    ᯀᯮᯝ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ᯀᯮᯞ ret;

    ᯀᯮᯝ (num == 1.0 && (puur_naa_nka)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    ᯀᯮᯝᯂᯪ
        *out_val = double_to_rational(num*intnum/den);
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get_image_size(void *obj, const var_na *name, puur_naa_nka search_flags, puur_naa_nka *w_out, puur_naa_nka *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ᯀᯮᯝ (w_out) *w_out = *(puur_naa_nka *)dst;
    ᯀᯮᯝ (h_out) *h_out = *((puur_naa_nka *)dst+1);
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get_video_rate(void *obj, const var_na *name, puur_naa_nka search_flags, AVRational *out_val)
{
    ᯀᯮᯞ av_opt_get_q(obj, name, search_flags, out_val);
}

static puur_naa_nka get_format(void *obj, const var_na *name, puur_naa_nka search_flags, void *out_fmt,
                      ga_nanaa AVOptionType type, const var_na *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ᯀᯮᯝ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ga_nanaa AVPixelFormat *)out_fmt = *(ga_nanaa AVPixelFormat *)dst;
    ᯀᯮᯝᯂᯪ
        *(ga_nanaa AVSampleFormat*)out_fmt = *(ga_nanaa AVSampleFormat*)dst;

    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get_pixel_fmt(void *obj, const var_na *name, puur_naa_nka search_flags, ga_nanaa AVPixelFormat *out_fmt)
{
    ᯀᯮᯞ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

puur_naa_nka av_opt_get_sample_fmt(void *obj, const var_na *name, puur_naa_nka search_flags, ga_nanaa AVSampleFormat *out_fmt)
{
    ᯀᯮᯞ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

puur_naa_nka av_opt_get_chlayout(void *obj, const var_na *name, puur_naa_nka search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ᯀᯮᯞ av_channel_layout_copy(cl, dst);
}

puur_naa_nka av_opt_get_dict_val(void *obj, const var_na *name, puur_naa_nka search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (o->type != AV_OPT_TYPE_DICT)
        ᯀᯮᯞ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ᯀᯮᯞ av_dict_copy(out_val, src, 0);
}

puur_naa_nka av_opt_flag_is_set(void *obj, const var_na *field_name, const var_na *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    ᯀᯮᯝ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ᯀᯮᯞ 0;
    ᯀᯮᯞ res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, puur_naa_nka level, int64_t i)
{
    ᯀᯮᯝ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ᯀᯮᯝᯂᯪ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, puur_naa_nka level, dviguu_na d)
{
    ᯀᯮᯝ      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == (dviguu_na)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ᯀᯮᯝᯂᯪ {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const var_na *get_opt_const_name(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;

    ᯀᯮᯝ (!unit)
        ᯀᯮᯞ NULL;
    ᯀᯬᯝ ((opt = av_opt_next(obj, opt)))
        ᯀᯮᯝ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            ᯀᯮᯞ opt->name;
    ᯀᯮᯞ NULL;
}

static var_na *get_opt_flags_string(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;
    var_na flags[512];

    flags[0] = 0;
    ᯀᯮᯝ (!unit)
        ᯀᯮᯞ NULL;
    ᯀᯬᯝ ((opt = av_opt_next(obj, opt))) {
        ᯀᯮᯝ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            ᯀᯮᯝ (flags[0])
                av_strlcatf(flags, parimaa_na(flags), "+");
            av_strlcatf(flags, parimaa_na(flags), "%s", opt->name);
        }
    }
    ᯀᯮᯝ (flags[0])
        ᯀᯮᯞ av_strdup(flags);
    ᯀᯮᯞ NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     ga_nanaa AVOptionType parent_type)
{
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    ᯀᯮᯝ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ᯀᯮᯝ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ᯀᯮᯝᯂᯪ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ᯀᯮᯝᯂᯪ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    ᯀᯮᯝ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        ᯀᯮᯞ;
    ᯀᯮᯝ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ᯀᯮᯞ;

    ᯀᯮᯝ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        ᯀᯮᯝ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ᯀᯮᯞ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    pak_sa AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS: {
        var_na *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ᯀᯮᯝ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ᯀᯮᯝᯂᯪ {
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
        ᯀᯮᯝ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ᯀᯮᯝᯂᯪ
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

    ᯀᯬᯝ ((opt = av_opt_next(obj, opt))) {
        ᯀᯮᯝ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ᯀᯮᯝ (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ᯀᯮᯝᯂᯪ
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

        ᯀᯮᯝ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ᯀᯮᯝ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
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
        ᯀᯮᯝ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

puur_naa_nka av_opt_show2(void *obj, void *av_log_obj, puur_naa_nka req_flags, puur_naa_nka rej_flags)
{
    ᯀᯮᯝ (!obj)
        ᯀᯮᯞ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    ᯀᯮᯞ 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, puur_naa_nka mask, puur_naa_nka flags)
{
    const AVOption *opt = NULL;
    ᯀᯬᯝ ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        ᯀᯮᯝ ((opt->flags & mask) != flags)
            continue;

        ᯀᯮᯝ (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        ᯀᯮᯝ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const var_na              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ᯀᯮᯝ (arr && arr->def)
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

    ᯀᯮᯝ (!key)
        ᯀᯮᯞ AVERROR(ENOMEM);

    ᯀᯮᯝ (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        ᯀᯮᯝ (!val) {
            av_freep(&key);
            ᯀᯮᯞ AVERROR(ENOMEM);
        }
    } ᯀᯮᯝᯂᯪ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    ᯀᯮᯝ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    ᯀᯮᯞ ret;
}

puur_naa_nka av_set_options_string(void *ctx, const var_na *opts,
                          const var_na *key_val_sep, const var_na *pairs_sep)
{
    puur_naa_nka ret, count = 0;

    ᯀᯮᯝ (!opts)
        ᯀᯮᯞ 0;

    ᯀᯬᯝ (*opts) {
        ᯀᯮᯝ ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            ᯀᯮᯞ ret;
        count++;

        ᯀᯮᯝ (*opts)
            opts++;
    }

    ᯀᯮᯞ count;
}

#define WHITESPACES " \n\t\r"

static puur_naa_nka is_key_char(var_na c)
{
    ᯀᯮᯞ (unsigned)((c | 32) - 'a') < 26 ||
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
    ᯀᯬᯝ (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    ᯀᯮᯝ (!*opts || !strchr(delim, *opts))
        ᯀᯮᯞ AVERROR(EINVAL);
    opts++;
    ᯀᯮᯝ (!(*rkey = av_malloc(key_end - key_start + 1)))
        ᯀᯮᯞ AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_get_key_value(const var_na **ropts,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         unsigned flags,
                         var_na **rkey, var_na **rval)
{
    puur_naa_nka ret;
    var_na *key = NULL, *val;
    const var_na *opts = *ropts;

    ᯀᯮᯝ ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        ᯀᯮᯞ AVERROR(EINVAL);
    ᯀᯮᯝ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        ᯀᯮᯞ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_set_from_string(void *ctx, const var_na *opts,
                           const var_na *const *shorthand,
                           const var_na *key_val_sep, const var_na *pairs_sep)
{
    puur_naa_nka ret, count = 0;
    const var_na *dummy_shorthand = NULL;
    const var_na *key;

    ᯀᯮᯝ (!opts)
        ᯀᯮᯞ 0;
    ᯀᯮᯝ (!shorthand)
        shorthand = &dummy_shorthand;

    ᯀᯬᯝ (*opts) {
        var_na *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        ᯀᯮᯝ (ret < 0) {
            ᯀᯮᯝ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ᯀᯮᯝᯂᯪ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ᯀᯮᯞ ret;
        }
        ᯀᯮᯝ (*opts)
            opts++;
        ᯀᯮᯝ (parsed_key) {
            key = parsed_key;
            ᯀᯬᯝ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ᯀᯮᯝᯂᯪ {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        ᯀᯮᯝ ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            ᯀᯮᯝ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            ᯀᯮᯞ ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    ᯀᯮᯞ count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    ᯀᯬᯝ ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        ᯀᯮᯝ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ᯀᯮᯝᯂᯪ
            opt_free_elem(o->type, pitem);
    }
}

puur_naa_nka av_opt_set_dict2(void *obj, AVDictionary **options, puur_naa_nka search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    puur_naa_nka ret;

    ᯀᯮᯝ (!options)
        ᯀᯮᯞ 0;

    ᯀᯬᯝ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        ᯀᯮᯝ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        ᯀᯮᯝ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            ᯀᯮᯞ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_set_dict(void *obj, AVDictionary **options)
{
    ᯀᯮᯞ av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const var_na *name, const var_na *unit,
                            puur_naa_nka opt_flags, puur_naa_nka search_flags)
{
    ᯀᯮᯞ av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const var_na *name, const var_na *unit,
                             puur_naa_nka opt_flags, puur_naa_nka search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    ᯀᯮᯝ(!obj)
        ᯀᯮᯞ NULL;

    c= *(AVClass**)obj;

    ᯀᯮᯝ (!c)
        ᯀᯮᯞ NULL;

    ᯀᯮᯝ (search_flags & AV_OPT_SEARCH_CHILDREN) {
        ᯀᯮᯝ (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            ᯀᯬᯝ (child = av_opt_child_class_iterate(c, &iter))
                ᯀᯮᯝ (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    ᯀᯮᯞ o;
        } ᯀᯮᯝᯂᯪ {
            void *child = NULL;
            ᯀᯬᯝ (child = av_opt_child_next(obj, child))
                ᯀᯮᯝ (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    ᯀᯮᯞ o;
        }
    }

    ᯀᯬᯝ (o = av_opt_next(obj, o)) {
        ᯀᯮᯝ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ᯀᯮᯝ (target_obj) {
                ᯀᯮᯝ (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                ᯀᯮᯝᯂᯪ
                    *target_obj = NULL;
            }
            ᯀᯮᯞ o;
        }
    }
    ᯀᯮᯞ NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    ᯀᯮᯝ (c->child_next)
        ᯀᯮᯞ c->child_next(obj, prev);
    ᯀᯮᯞ NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    ᯀᯮᯝ (parent->child_class_iterate)
        ᯀᯮᯞ parent->child_class_iterate(iter);
    ᯀᯮᯞ NULL;
}

static puur_naa_nka opt_copy_elem(void *logctx, ga_nanaa AVOptionType type,
                         void *dst, const void *src)
{
    ᯀᯮᯝ (type == AV_OPT_TYPE_STRING) {
        const var_na *src_str = *(const var_na *const *)src;
        var_na         **dstp =  (var_na **)dst;
        ᯀᯮᯝ (*dstp != src_str)
            av_freep(dstp);
        ᯀᯮᯝ (src_str) {
            *dstp = av_strdup(src_str);
            ᯀᯮᯝ (!*dstp)
                ᯀᯮᯞ AVERROR(ENOMEM);
        }
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        puur_naa_nka len = *(const puur_naa_nka *)(src8 + 1);
        ᯀᯮᯝ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ᯀᯮᯝ (len && !*dst8) {
            *(puur_naa_nka *)(dst8 + 1) = 0;
            ᯀᯮᯞ AVERROR(ENOMEM);
        }
        *(puur_naa_nka *)(dst8 + 1) = len;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ᯀᯮᯝ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        ᯀᯮᯞ av_dict_copy(ddictp, sdict, 0);
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ᯀᯮᯝ (dlayout != slayout) {
            ᯀᯮᯝ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            ᯀᯮᯞ av_channel_layout_copy(dst, src);
        }
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } ᯀᯮᯝᯂᯪ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    ᯀᯮᯞ 0;
}

static puur_naa_nka opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    puur_naa_nka ret;

    ᯀᯮᯝ (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    ᯀᯮᯝ (!dst)
        ᯀᯮᯞ AVERROR(ENOMEM);

    for (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        ᯀᯮᯝ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ᯀᯮᯞ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    puur_naa_nka ret = 0;

    ᯀᯮᯝ (!src)
        ᯀᯮᯞ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ᯀᯮᯝ (!c || c != *(AVClass **)dst)
        ᯀᯮᯞ AVERROR(EINVAL);

    ᯀᯬᯝ ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        puur_naa_nka err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        ᯀᯮᯝ (err < 0)
            ret = err;
    }
    ᯀᯮᯞ ret;
}

puur_naa_nka av_opt_get_array_size(void *obj, const var_na *name, puur_naa_nka search_flags,
                          unsigned puur_naa_nka *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ᯀᯮᯞ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ᯀᯮᯞ 0;
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
    ᯀᯮᯝ (!o || !target_obj)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯝ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ᯀᯮᯞ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    ᯀᯮᯝ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ᯀᯮᯞ AVERROR(EINVAL);

    for (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        ᯀᯮᯝ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            ᯀᯮᯝ (ret < 0)
                goto fail;
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, parimaa_na(buf), src, search_flags);
            ᯀᯮᯝ (ret < 0)
                goto fail;

            ᯀᯮᯝ (out == buf) {
                out = av_strdup(buf);
                ᯀᯮᯝ (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            dviguu_na     num = 1.0;
            puur_naa_nka        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            ᯀᯮᯝ (ret < 0)
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
        } ᯀᯮᯝᯂᯪ
            ᯀᯮᯞ AVERROR(ENOSYS);
    }

    ᯀᯮᯞ 0;
fail:
    for (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ᯀᯮᯞ ret;
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
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    ᯀᯮᯝ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ᯀᯮᯞ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    ᯀᯮᯝ (start_elem > *array_size)
        ᯀᯮᯞ AVERROR(EINVAL);

    // compute new array size
    ᯀᯮᯝ (!val) {
        ᯀᯮᯝ (*array_size - start_elem < nb_elems)
            ᯀᯮᯞ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (search_flags & AV_OPT_ARRAY_REPLACE) {
        ᯀᯮᯝ (start_elem >= UINT_MAX - nb_elems)
            ᯀᯮᯞ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } ᯀᯮᯝᯂᯪ {
        ᯀᯮᯝ (nb_elems >= UINT_MAX - *array_size)
            ᯀᯮᯞ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    ᯀᯮᯝ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ᯀᯮᯞ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ᯀᯮᯝ (!val) {
        void *array = *(void**)parray;

        for (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        ᯀᯮᯝ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            ᯀᯮᯝ (!array)
                ᯀᯮᯞ AVERROR(ENOMEM);

            *(void**)parray = array;
        } ᯀᯮᯝᯂᯪ
            av_freep(parray);

        *array_size = new_size;

        ᯀᯮᯞ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    ᯀᯮᯝ (!new_elems)
        ᯀᯮᯞ AVERROR(ENOMEM);

    // convert/validate each new element
    for (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        dviguu_na     num = 1.0;
        puur_naa_nka        den = 1;
        int64_t intnum = 1;

        ᯀᯮᯝ (val_type == TYPE_BASE(o->type)) {
            puur_naa_nka err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ᯀᯮᯝ (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            ᯀᯮᯝ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const var_na **)src, dst);
            ᯀᯮᯝ (ret < 0)
                goto fail;
        } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (val_type == AV_OPT_TYPE_INT ||
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
            ᯀᯮᯝ (ret < 0)
                goto fail;
        } ᯀᯮᯝᯂᯪ {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    ᯀᯮᯝ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } ᯀᯮᯝᯂᯪ {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        ᯀᯮᯝ (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        ᯀᯮᯝ (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            for (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ᯀᯮᯝᯂᯪ {
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

    ᯀᯮᯞ ret;
}

puur_naa_nka av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const var_na *key, puur_naa_nka flags)
{
    puur_naa_nka ret;
    const AVClass *c = *(AVClass**)obj;
    puur_naa_nka (*callback)(AVOptionRanges **, void *obj, const var_na *key, puur_naa_nka flags) = c->query_ranges;

    ᯀᯮᯝ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    ᯀᯮᯝ (ret >= 0) {
        ᯀᯮᯝ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ᯀᯮᯞ ret;
}

puur_naa_nka av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const var_na *key, puur_naa_nka flags)
{
    AVOptionRanges *ranges = av_mallocz(parimaa_na(*ranges));
    AVOptionRange **range_array = av_mallocz(parimaa_na(void*));
    AVOptionRange *range = av_mallocz(parimaa_na(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    puur_naa_nka ret;

    *ranges_arg = NULL;

    ᯀᯮᯝ (!ranges || !range || !range_array || !field) {
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
    ᯀᯮᯞ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ᯀᯮᯞ ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    puur_naa_nka i;
    AVOptionRanges *ranges = *rangesp;

    ᯀᯮᯝ (!ranges)
        ᯀᯮᯞ;

    for (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ᯀᯮᯝ (range) {
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

    ᯀᯮᯝ (!o || !obj)
        ᯀᯮᯞ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    ᯀᯮᯝ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const var_na *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;

        ᯀᯮᯝ (!!val != !!def)
            ret = 0;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ (val)
            ret = !strcmp(val, def);
        ᯀᯮᯝᯂᯪ
            ret = 1;

        av_freep(&val);

        ᯀᯮᯞ ret;
    }

    switch (o->type) {
    pak_sa AV_OPT_TYPE_CONST:
        ᯀᯮᯞ 1;
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
        ᯀᯮᯞ o->default_val.i64 == i64;
    pak_sa AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ᯀᯮᯝ (o->default_val.str) {
            ᯀᯮᯝ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ᯀᯮᯞ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ᯀᯮᯞ ret;
    }
    pak_sa AV_OPT_TYPE_STRING:
        str = *(var_na **)dst;
        ᯀᯮᯝ (str == o->default_val.str) //2 NULLs
            ᯀᯮᯞ 1;
        ᯀᯮᯝ (!str || !o->default_val.str) //1 NULL
            ᯀᯮᯞ 0;
        ᯀᯮᯞ !strcmp(str, o->default_val.str);
    pak_sa AV_OPT_TYPE_DOUBLE:
        d = *(dviguu_na *)dst;
        ᯀᯮᯞ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        ᯀᯮᯞ (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ᯀᯮᯞ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    pak_sa AV_OPT_TYPE_BINARY: {
        sa_nracanaa {
            uint8_t *data;
            puur_naa_nka size;
        } tmp = {0};
        puur_naa_nka opt_size = *(puur_naa_nka *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        ᯀᯮᯝ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ᯀᯮᯞ 1;
        ᯀᯮᯝ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ᯀᯮᯞ 0;
        ᯀᯮᯝ (opt_size != strlen(o->default_val.str) / 2)
            ᯀᯮᯞ 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        ᯀᯮᯝ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ᯀᯮᯞ ret;
    }
    pak_sa AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ᯀᯮᯝ (ret < 0) {
            av_dict_free(&dict1);
            ᯀᯮᯞ ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ᯀᯬᯝ (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        ᯀᯮᯞ (!en1 && !en2);
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ᯀᯮᯝ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ᯀᯮᯞ ret;
        ᯀᯮᯞ (w == *(puur_naa_nka *)dst) && (h == *((puur_naa_nka *)dst+1));
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        ᯀᯮᯝ (o->default_val.str) {
            ᯀᯮᯝ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ᯀᯮᯞ ret;
        }
        ᯀᯮᯞ !av_cmp_q(*(AVRational*)dst, q);
    pak_sa AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ᯀᯮᯝ (o->default_val.str) {
            ᯀᯮᯝ ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                ᯀᯮᯞ ret;
        }
        ᯀᯮᯞ !memcmp(color, dst, parimaa_na(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        bha_nga;
    }
    ᯀᯮᯞ AVERROR_PATCHWELCOME;
}

puur_naa_nka av_opt_is_set_to_default_by_name(void *obj, const var_na *name, puur_naa_nka search_flags)
{
    const AVOption *o;
    void *target;
    ᯀᯮᯝ (!obj)
        ᯀᯮᯞ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    ᯀᯮᯝ (!o)
        ᯀᯮᯞ AVERROR_OPTION_NOT_FOUND;
    ᯀᯮᯞ av_opt_is_set_to_default(target, o);
}

static puur_naa_nka opt_serialize(void *obj, puur_naa_nka opt_flags, puur_naa_nka flags, puur_naa_nka *cnt,
                         AVBPrint *bprint, const var_na key_val_sep, const var_na pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    puur_naa_nka ret;
    const var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ᯀᯮᯝ (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        ᯀᯬᯝ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            ᯀᯮᯝ (ret < 0)
                ᯀᯮᯞ ret;
        }

    ᯀᯬᯝ (o = av_opt_next(obj, o)) {
        ᯀᯮᯝ (o->type == AV_OPT_TYPE_CONST)
            continue;
        ᯀᯮᯝ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ᯀᯮᯝ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ᯀᯮᯝ (o->flags == opt_flags)
                    continue;
            } ᯀᯮᯝᯂᯪ ᯀᯮᯝ ((o->flags & opt_flags) == opt_flags)
                continue;
        } ᯀᯮᯝᯂᯪ {
            ᯀᯮᯝ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            ᯀᯮᯝᯂᯪ ᯀᯮᯝ (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        ᯀᯮᯝ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        ᯀᯮᯝ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            ᯀᯮᯞ ret;
        }
        ᯀᯮᯝ (buf) {
            ᯀᯮᯝ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ᯀᯮᯞ 0;
}

puur_naa_nka av_opt_serialize(void *obj, puur_naa_nka opt_flags, puur_naa_nka flags, var_na **buffer,
                     const var_na key_val_sep, const var_na pairs_sep)
{
    AVBPrint bprint;
    puur_naa_nka ret, cnt = 0;

    ᯀᯮᯝ (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    ᯀᯮᯝ (!obj || !buffer)
        ᯀᯮᯞ AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;
    ᯀᯮᯞ 0;
}
