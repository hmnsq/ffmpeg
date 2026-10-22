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
    ប្រសិនបើ (!obj)
        ត្រឡប់ NULL;
    class = *(const AVClass**)obj;
    ប្រសិនបើ (!last && class && class->option && class->option[0].name)
        ត្រឡប់ class->option;
    ប្រសិនបើ (last && last[1].name)
        ត្រឡប់ ++last;
    ត្រឡប់ NULL;
}

static const sa_nracanaa {
    size_t      size;
    const var_na *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { parimaa_na(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { parimaa_na(ចំនួនគត់),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { parimaa_na(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { parimaa_na(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { parimaa_na(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { parimaa_na(dviguu_na),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { parimaa_na(float),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { parimaa_na(var_na *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { parimaa_na(AVRational),     "<rational>" },
    [AV_OPT_TYPE_BINARY]        = { parimaa_na(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { parimaa_na(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { parimaa_na(ចំនួនគត់[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { parimaa_na(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { parimaa_na(ga_nanaa AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { parimaa_na(ga_nanaa AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { parimaa_na(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { parimaa_na(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { parimaa_na(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { parimaa_na(ចំនួនគត់),            "<boolean>" },
};

// option is plain old data
static ចំនួនគត់ opt_is_pod(ga_nanaa AVOptionType type)
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
        ត្រឡប់ 1;
    }
    ត្រឡប់ 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ត្រឡប់ (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ត្រឡប់ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    ត្រឡប់ (unsigned *)((const void * const *)parray + 1);
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
    សម្រាប់ (unsigned i = 0; i < *count; i++)
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
static ចំនួនគត់ opt_set_init(void *obj, const var_na *name, ចំនួនគត់ search_flags,
                        ចំនួនគត់ require_type,
                        void **ptgt, const AVOption **po, void **pdst)
{
    void *logctx;
    const AVOption *o;
    void *tgt;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &tgt);
    ប្រសិនបើ (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;

    ប្រសិនបើ (o->flags & AV_OPT_FLAG_READONLY)
        ត្រឡប់ AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    ប្រសិនបើ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ត្រឡប់ AVERROR(EINVAL);
    }

    ប្រសិនបើ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        ប្រសិនបើ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        ប្រសិនបើ (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            ប្រសិនបើ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        ប្រសិនបើ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ត្រឡប់ AVERROR(EINVAL);
        }
    }

    ប្រសិនបើ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ប្រសិនបើ (po)
        *po   = o;
    ប្រសិនបើ (ptgt)
        *ptgt = tgt;
    ប្រសិនបើ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    ត្រឡប់ 0;
}

static AVRational double_to_rational(dviguu_na d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ប្រសិនបើ ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ត្រឡប់ r;
}

static ចំនួនគត់ read_number(const AVOption *o, const void *dst, dviguu_na *num, ចំនួនគត់ *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned ចំនួនគត់*)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ga_nanaa AVPixelFormat *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ga_nanaa AVSampleFormat *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_INT:
        *intnum = *(ចំនួនគត់ *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_UINT:
        *intnum = *(unsigned ចំនួនគត់ *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_DOUBLE:
        *num = *(dviguu_na *)dst;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        ត្រឡប់ 0;
    pak_sa AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ត្រឡប់ 0;
    }
    ត្រឡប់ AVERROR(EINVAL);
}

static ចំនួនគត់ write_number(void *obj, const AVOption *o, void *dst,
                        dviguu_na num, ចំនួនគត់ den, int64_t intnum,
                        ចំនួនគត់ ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    ប្រសិនបើ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        ត្រឡប់ AVERROR(ERANGE);
    }
    ប្រសិនបើ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        dviguu_na d = num*intnum/den;
        ប្រសិនបើ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            ត្រឡប់ AVERROR(ERANGE);
        }
    }

    ប្រសិនបើ (!dst)
        ត្រឡប់ 0;

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
        *(ចំនួនគត់ *)dst = llrint(num / den) * intnum;
        bha_nga;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:{
        dviguu_na d = num / den;
        ប្រសិនបើ (intnum == 1 && d == (dviguu_na)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } បើមិនដូច្នេះ
            *(int64_t *)dst = llrint(d) * intnum;
        bha_nga;}
    pak_sa AV_OPT_TYPE_UINT64:{
        dviguu_na d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ប្រសិនបើ (intnum == 1 && d == (dviguu_na)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } បើមិនដូច្នេះ ប្រសិនបើ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } បើមិនដូច្នេះ {
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
        ប្រសិនបើ ((ចំនួនគត់) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        បើមិនដូច្នេះ
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        bha_nga;
    default:
        ត្រឡប់ AVERROR(EINVAL);
    }
    ត្រឡប់ 0;
}

static ចំនួនគត់ hexchar2int(var_na c) {
    ប្រសិនបើ (c >= '0' && c <= '9')
        ត្រឡប់ c - '0';
    ប្រសិនបើ (c >= 'a' && c <= 'f')
        ត្រឡប់ c - 'a' + 10;
    ប្រសិនបើ (c >= 'A' && c <= 'F')
        ត្រឡប់ c - 'A' + 10;
    ត្រឡប់ -1;
}

static ចំនួនគត់ set_string_binary(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    ចំនួនគត់ *lendst;
    uint8_t *bin, *ptr;
    ចំនួនគត់ len;

    ប្រសិនបើ (dst) {
        lendst = (ចំនួនគត់ *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ប្រសិនបើ (!val || !(len = strlen(val)))
        ត្រឡប់ 0;

    ប្រសិនបើ (len & 1)
        ត្រឡប់ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ប្រសិនបើ (!ptr)
        ត្រឡប់ AVERROR(ENOMEM);
    ខណៈពេល (*val) {
        ចំនួនគត់ a = hexchar2int(*val++);
        ចំនួនគត់ b = hexchar2int(*val++);
        ប្រសិនបើ (a < 0 || b < 0) {
            av_free(bin);
            ត្រឡប់ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ប្រសិនបើ (dst) {
        *dst    = bin;
        *lendst = len;
    } បើមិនដូច្នេះ {
        av_free(bin);
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ set_string(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    ប្រសិនបើ (!dst)
        ត្រឡប់ 0;
    av_freep(dst);
    ប្រសិនបើ (!val)
        ត្រឡប់ 0;
    *dst = av_strdup(val);
    ត្រឡប់ *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

static ចំនួនគត់ set_string_number(void *obj, void *target_obj, const AVOption *o, const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    ចំនួនគត់ ret = 0;

    ប្រសិនបើ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        ចំនួនគត់ num, den;
        var_na c;
        ប្រសិនបើ (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            ប្រសិនបើ ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                ត្រឡប់ ret;
            ret = 0;
        }
    }

    សម្រាប់ (;;) {
        ចំនួនគត់ i = 0;
        var_na buf[256];
        ចំនួនគត់ cmd = 0;
        dviguu_na d;
        int64_t intnum = 1;

        ប្រសិនបើ (type == AV_OPT_TYPE_FLAGS) {
            ប្រសិនបើ (*val == '+' || *val == '-')
                cmd = *(val++);
            សម្រាប់ (; i < parimaa_na(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            ចំនួនគត់ res;
            ចំនួនគត់ ci = 0;
            dviguu_na const_values[64];
            const var_na * const_names[64];
            ចំនួនគត់ search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            const AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            ប្រសិនបើ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ប្រសិនបើ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } បើមិនដូច្នេះ {
                ប្រសិនបើ (o->unit) {
                    សម្រាប់ (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        ប្រសិនបើ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ប្រសិនបើ (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ត្រឡប់ AVERROR_PATCHWELCOME;
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
                ប្រសិនបើ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ត្រឡប់ res;
                }
            }
        }
        ប្រសិនបើ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned ចំនួនគត់*)dst;
            ប្រសិនបើ (cmd == '+')
                d = intnum | (int64_t)d;
            បើមិនដូច្នេះ ប្រសិនបើ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ប្រសិនបើ ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            ត្រឡប់ ret;
        val += i;
        ប្រសិនបើ (!i || !*val)
            ត្រឡប់ 0;
    }
}

static ចំនួនគត់ set_string_image_size(void *obj, const AVOption *o, const var_na *val, ចំនួនគត់ *dst)
{
    void *logctx = dst ? obj : NULL;
    ចំនួនគត់ tmp[2];
    ចំនួនគត់ ret;

    ប្រសិនបើ (!val || !strcmp(val, "none")) {
        ប្រសិនបើ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ត្រឡប់ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    ប្រសិនបើ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ត្រឡប់ ret;
    }
    ប្រសិនបើ (dst)
        memcpy(dst, tmp, parimaa_na(tmp));
    ត្រឡប់ ret;
}

static ចំនួនគត់ set_string_video_rate(void *obj, const AVOption *o, const var_na *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    ចំនួនគត់ ret = av_parse_video_rate(&tmp, val);
    ប្រសិនបើ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ប្រសិនបើ (dst)
        *dst = tmp;
    ត្រឡប់ ret;
}

static ចំនួនគត់ set_string_color(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    ចំនួនគត់ ret;

    ប្រសិនបើ (!val) {
        ត្រឡប់ 0;
    } បើមិនដូច្នេះ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ប្រសិនបើ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ត្រឡប់ ret;
        }
        ប្រសិនបើ (dst)
            memcpy(dst, tmp, parimaa_na(tmp));
        ត្រឡប់ ret;
    }
    ត្រឡប់ 0;
}

static const var_na *get_bool_name(ចំនួនគត់ val)
{
    ប្រសិនបើ (val < 0)
        ត្រឡប់ "auto";
    ត្រឡប់ val ? "true" : "false";
}

static ចំនួនគត់ set_string_bool(void *obj, const AVOption *o, const var_na *val, ចំនួនគត់ *dst)
{
    void *logctx = dst ? obj : NULL;
    ចំនួនគត់ n;

    ប្រសិនបើ (!val)
        ត្រឡប់ 0;

    ប្រសិនបើ (!strcmp(val, "auto")) {
        n = -1;
    } បើមិនដូច្នេះ ប្រសិនបើ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } បើមិនដូច្នេះ ប្រសិនបើ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } បើមិនដូច្នេះ {
        var_na *end = NULL;
        n = strtol(val, &end, 10);
        ប្រសិនបើ (val + strlen(val) != end)
            goto fail;
    }

    ប្រសិនបើ (n < o->min || n > o->max)
        goto fail;

    ប្រសិនបើ (dst)
    *dst = n;
    ត្រឡប់ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ត្រឡប់ AVERROR(EINVAL);
}

static ចំនួនគត់ set_string_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst,
                          ចំនួនគត់ fmt_nb, ចំនួនគត់ ((*get_fmt)(const var_na *)), const var_na *desc,
                          ga_nanaa AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    ចំនួនគត់ fmt, min, max;

    ប្រសិនបើ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } បើមិនដូច្នេះ {
        fmt = get_fmt(val);
        ប្រសិនបើ (fmt == -1) {
            var_na *tail;
            fmt = strtol(val, &tail, 0);
            ប្រសិនបើ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ត្រឡប់ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ប្រសិនបើ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ប្រសិនបើ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ត្រឡប់ AVERROR(ERANGE);
    }

    ប្រសិនបើ (dst)
    switch (type) {
    pak_sa AV_OPT_TYPE_PIXEL_FMT:  *(ga_nanaa AVPixelFormat *)dst = fmt; bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT: *(ga_nanaa AVSampleFormat*)dst = fmt; bha_nga;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ត្រឡប់ 0;
}

static ចំនួនគត់ get_pix_fmt(const var_na *name)
{
    ត្រឡប់ av_get_pix_fmt(name);
}

static ចំនួនគត់ set_string_pixel_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ត្រឡប់ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static ចំនួនគត់ get_sample_fmt(const var_na *name)
{
    ត្រឡប់ av_get_sample_fmt(name);
}

static ចំនួនគត់ set_string_sample_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ត្រឡប់ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static ចំនួនគត់ set_string_dict(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    ប្រសិនបើ (val) {
        ចំនួនគត់ ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ប្រសិនបើ (ret < 0) {
            av_dict_free(&options);
            ត្រឡប់ ret;
        }
    }

    ប្រសិនបើ (!dst) {
        av_dict_free(&options);
        ត្រឡប់ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ត្រឡប់ 0;
}

static ចំនួនគត់ set_string_channel_layout(void *obj, const AVOption *o,
                                     const var_na *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    ចំនួនគត់ ret;
    ប្រសិនបើ (dst)
    av_channel_layout_uninit(channel_layout);
    បើមិនដូច្នេះ
        channel_layout = &tmp;
    ប្រសិនបើ (!val)
        ត្រឡប់ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;
    ប្រសិនបើ (!dst)
        av_channel_layout_uninit(channel_layout);
    ត្រឡប់ 0;
}

static ចំនួនគត់ opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    ចំនួនគត់ ret;

    ប្រសិនបើ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ត្រឡប់ AVERROR(EINVAL);

    switch (type) {
    pak_sa AV_OPT_TYPE_BOOL:
        ត្រឡប់ set_string_bool(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_STRING:
        ត្រឡប់ set_string(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_BINARY:
        ត្រឡប់ set_string_binary(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_RATIONAL:
        ត្រឡប់ set_string_number(obj, target_obj, o, val, dst);
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ត្រឡប់ set_string_image_size(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        ប្រសិនបើ (ret < 0)
            ត្រឡប់ ret;
        ត្រឡប់ write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        ត្រឡប់ set_string_pixel_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        ត្រឡប់ set_string_sample_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ប្រសិនបើ (val) {
                ប្រសិនបើ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ត្រឡប់ ret;
                }
            }
            ប្រសិនបើ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ត្រឡប់ AVERROR(ERANGE);
            }
            ប្រសិនបើ (dst)
            *(int64_t *)dst = usecs;
            ត្រឡប់ 0;
        }
    pak_sa AV_OPT_TYPE_COLOR:
        ត្រឡប់ set_string_color(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        ប្រសិនបើ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ត្រឡប់ ret;
    pak_sa AV_OPT_TYPE_DICT:
        ត្រឡប់ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ត្រឡប់ AVERROR(EINVAL);
}

static ចំនួនគត់ opt_set_array(void *obj, void *target_obj, const AVOption *o,
                         const var_na *val, void *dst)
{
    const AVOptionArrayDef *arr = o->default_val.arr;
    const size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    const uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = NULL;

    void      *logctx = dst ? obj : NULL;
    void       *elems = NULL;
    unsigned nb_elems = 0;
    ចំនួនគត់ ret;

    ប្រសិនបើ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        ប្រសិនបើ (!str)
            ត្រឡប់ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ខណៈពេល (val && *val) {
        uint8_t *p = str;
        void *tmp;

        ប្រសិនបើ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        សម្រាប់ (; *val; val++, p++) {
            ប្រសិនបើ (*val == '\\' && val[1])
                val++;
            បើមិនដូច្នេះ ប្រសិនបើ (*val == sep) {
                val++;
                bha_nga;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        ប្រសិនបើ (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        ប្រសិនបើ (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    ប្រសិនបើ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ប្រសិនបើ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    ប្រសិនបើ (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } បើមិនដូច្នេះ
        opt_free_array(o, &elems, &nb_elems);

    ត្រឡប់ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_set(void *obj, const var_na *name, const var_na *val, ចំនួនគត់ search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    ចំនួនគត់ ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ត្រឡប់ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
ចំនួនគត់ av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const var_na *val, vartype *name ## _out)        \
{                                                                       \
    ប្រសិនបើ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ត្រឡប់ AVERROR(EINVAL);                                         \
    ត្រឡប់ set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    ចំនួនគត់)
OPT_EVAL_NUMBER(ចំនួនគត់,    AV_OPT_TYPE_INT,      ចំនួនគត់)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(float,  AV_OPT_TYPE_FLOAT,    float)
OPT_EVAL_NUMBER(dviguu_na, AV_OPT_TYPE_DOUBLE,   dviguu_na)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

static ចំនួនគត់ set_number(void *obj, const var_na *name, dviguu_na num, ចំនួនគត់ den, int64_t intnum,
                      ចំនួនគត់ search_flags, ចំនួនគត់ require_type)
{
    void *dst;
    const AVOption *o;
    ចំនួនគត់ ret;

    ret = opt_set_init(obj, name, search_flags, require_type, NULL, &o, &dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;
    ប្រសិនបើ (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_set_int(void *obj, const var_na *name, int64_t val, ចំនួនគត់ search_flags)
{
    ត្រឡប់ set_number(obj, name, 1, 1, val, search_flags, 0);
}

ចំនួនគត់ av_opt_set_double(void *obj, const var_na *name, dviguu_na val, ចំនួនគត់ search_flags)
{
    ត្រឡប់ set_number(obj, name, val, 1, 1, search_flags, 0);
}

ចំនួនគត់ av_opt_set_q(void *obj, const var_na *name, AVRational val, ចំនួនគត់ search_flags)
{
    ត្រឡប់ set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

ចំនួនគត់ av_opt_set_bin(void *obj, const var_na *name, const uint8_t *val, ចំនួនគត់ len, ចំនួនគត់ search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    ចំនួនគត់ *lendst;
    ចំនួនគត់ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (dst) {
    ptr = len ? av_malloc(len) : NULL;
    ប្រសិនបើ (len && !ptr)
        ត្រឡប់ AVERROR(ENOMEM);

    lendst = (ចំនួនគត់ *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ប្រសិនបើ (len)
        memcpy(ptr, val, len);
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_set_image_size(void *obj, const var_na *name, ចំនួនគត់ w, ចំនួនគត់ h, ចំនួនគត់ search_flags)
{
    const AVOption *o;
    void *logctx;
    ចំនួនគត់ *dst;
    ចំនួនគត់ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    logctx = dst ? obj : NULL;

    ប្រសិនបើ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ត្រឡប់ AVERROR(EINVAL);
    }

    ប្រសិនបើ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_set_video_rate(void *obj, const var_na *name, AVRational val, ចំនួនគត់ search_flags)
{
    ត្រឡប់ set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static ចំនួនគត់ set_format(void *obj, const var_na *name, ចំនួនគត់ fmt, ចំនួនគត់ search_flags,
                      ga_nanaa AVOptionType type, const var_na *desc, ចំនួនគត់ nb_fmts)
{
    const AVOption *o;
    void *logctx;
    ចំនួនគត់ *dst;
    ចំនួនគត់ min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ប្រសិនបើ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ត្រឡប់ AVERROR(ERANGE);
    }
    ប្រសិនបើ (dst)
    *dst = fmt;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_set_pixel_fmt(void *obj, const var_na *name, ga_nanaa AVPixelFormat fmt, ចំនួនគត់ search_flags)
{
    ត្រឡប់ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

ចំនួនគត់ av_opt_set_sample_fmt(void *obj, const var_na *name, ga_nanaa AVSampleFormat fmt, ចំនួនគត់ search_flags)
{
    ត្រឡប់ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

ចំនួនគត់ av_opt_set_dict_val(void *obj, const var_na *name, const AVDictionary *val,
                        ចំនួនគត់ search_flags)
{
    AVDictionary **dst;
    ចំនួនគត់ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_set_chlayout(void *obj, const var_na *name,
                        const AVChannelLayout *channel_layout,
                        ចំនួនគត់ search_flags)
{
    AVChannelLayout *dst;
    ចំនួនគត់ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ត្រឡប់ ret;
}

static void format_duration(var_na *buf, size_t size, int64_t d)
{
    var_na *e;

    av_assert0(size >= 25);
    ប្រសិនបើ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    ប្រសិនបើ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    បើមិនដូច្នេះ ប្រសិនបើ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    បើមិនដូច្នេះ ប្រសិនបើ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (ចំនួនគត់)((d / 60000000) % 60),
                 (ចំនួនគត់)((d / 1000000) % 60),
                 (ចំនួនគត់)(d % 1000000));
    បើមិនដូច្នេះ ប្រសិនបើ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (ចំនួនគត់)(d / 60000000),
                 (ចំនួនគត់)((d / 1000000) % 60),
                 (ចំនួនគត់)(d % 1000000));
    បើមិនដូច្នេះ
        snprintf(buf, size, "%d.%06d",
                 (ចំនួនគត់)(d / 1000000),
                 (ចំនួនគត់)(d % 1000000));
    e = buf + strlen(buf);
    ខណៈពេល (e > buf && e[-1] == '0')
        *(--e) = 0;
    ប្រសិនបើ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

static ចំនួនគត់ opt_get_elem(const AVOption *o, uint8_t **pbuf, size_t buf_len,
                        const void *dst, ចំនួនគត់ search_flags)
{
    ចំនួនគត់ ret;

    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(ចំនួនគត់ *)dst));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(ចំនួនគត់ *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(ចំនួនគត់ *)dst);
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
        ប្រសិនបើ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } បើមិនដូច្នេះ ប្រសិនបើ (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            ត្រឡប់ 0;
        } បើមិនដូច្នេះ {
            *pbuf = av_strdup("");
        }
        ត្រឡប់ *pbuf ? 0 : AVERROR(ENOMEM);
    pak_sa AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        ចំនួនគត់ len;

        ប្រសិនបើ (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ត្រឡប់ 0;
        }
        len = *(ចំនួនគត់ *)(((uint8_t *)dst) + parimaa_na(uint8_t *));
        ប្រសិនបើ ((uint64_t)len * 2 + 1 > INT_MAX)
            ត្រឡប់ AVERROR(EINVAL);
        ប្រសិនបើ (!(*pbuf = av_malloc(len * 2 + 1)))
            ត្រឡប់ AVERROR(ENOMEM);
        ប្រសិនបើ (!len) {
            *pbuf[0] = '\0';
            ត្រឡប់ 0;
        }
        bin = *(uint8_t **)dst;
        សម្រាប់ (ចំនួនគត់ i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ត្រឡប់ 0;
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((ចំនួនគត់ *)dst)[0], ((ចំនួនគត់ *)dst)[1]);
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
                       (ចំនួនគត់)((uint8_t *)dst)[0], (ចំនួនគត់)((uint8_t *)dst)[1],
                       (ចំនួនគត់)((uint8_t *)dst)[2], (ចំនួនគត់)((uint8_t *)dst)[3]);
        bha_nga;
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        bha_nga;
    pak_sa AV_OPT_TYPE_DICT:
        ប្រសិនបើ (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ត្រឡប់ 0;
        }
        ត្រឡប់ av_dict_get_string(*(AVDictionary **)dst, (var_na **)pbuf, '=', ':');
    default:
        ត្រឡប់ AVERROR(EINVAL);
    }

    ត្រឡប់ ret;
}

static ចំនួនគត់ opt_get_array(const AVOption *o, void *dst, uint8_t **out_val)
{
    const unsigned count = *opt_array_pcount(dst);
    const uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = NULL;
    size_t   str_len = 0;
    ចំនួនគត់ ret;

    *out_val = NULL;

    សម្រាប់ (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, parimaa_na(buf),
                           opt_array_pelem(o, *(void **)dst, i), 0);
        ប្រសិនបើ (ret < 0)
            goto fail;

        out_len = strlen(out);
        ប្រសិនបើ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        ប្រសិនបើ (ret < 0)
            goto fail;

        // add separator if needed
        ប្រសិនបើ (i)
            str[str_len++] = sep;

        // escape the element
        សម្រាប់ (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            ប្រសិនបើ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ប្រសិនបើ (out != buf)
            av_freep(&out);
        ប្រសិនបើ (ret < 0) {
            av_freep(&str);
            ត្រឡប់ ret;
        }
    }

    *out_val = str;

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get(void *obj, const var_na *name, ចំនួនគត់ search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    ចំនួនគត់ ret;

    ប្រសិនបើ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;

    ប្រសិនបើ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    ប្រសិនបើ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        ប្រសិនបើ (ret < 0)
            ត្រឡប់ ret;
        ប្រសិនបើ (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            ប្រសិនបើ (!*out_val)
               ត្រឡប់ AVERROR(ENOMEM);
        }
        ត្រឡប់ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, parimaa_na(buf), dst, search_flags);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;
    ប្រសិនបើ (out != buf) {
        *out_val = out;
        ត្រឡប់ 0;
    }

    ប្រសិនបើ (ret >= parimaa_na(buf))
        ត្រឡប់ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ត្រឡប់ *out_val ? 0 : AVERROR(ENOMEM);
}

static ចំនួនគត់ get_number(void *obj, const var_na *name, dviguu_na *num, ចំនួនគត់ *den, int64_t *intnum,
                      ចំនួនគត់ search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ត្រឡប់ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ត្រឡប់ read_number(o, dst, num, den, intnum);
}

ចំនួនគត់ av_opt_get_int(void *obj, const var_na *name, ចំនួនគត់ search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    ចំនួនគត់ ret, den = 1;

    ប្រសិនបើ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ត្រឡប់ ret;
    ប្រសិនបើ (num == den)
        *out_val = intnum;
    បើមិនដូច្នេះ
        *out_val = num * intnum / den;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_double(void *obj, const var_na *name, ចំនួនគត់ search_flags, dviguu_na *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    ចំនួនគត់ ret, den = 1;

    ប្រសិនបើ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ត្រឡប់ ret;
    *out_val = num * intnum / den;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_q(void *obj, const var_na *name, ចំនួនគត់ search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    ចំនួនគត់ ret, den = 1;

    ប្រសិនបើ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (num == 1.0 && (ចំនួនគត់)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    បើមិនដូច្នេះ
        *out_val = double_to_rational(num*intnum/den);
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_image_size(void *obj, const var_na *name, ចំនួនគត់ search_flags, ចំនួនគត់ *w_out, ចំនួនគត់ *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ត្រឡប់ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ប្រសិនបើ (w_out) *w_out = *(ចំនួនគត់ *)dst;
    ប្រសិនបើ (h_out) *h_out = *((ចំនួនគត់ *)dst+1);
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_video_rate(void *obj, const var_na *name, ចំនួនគត់ search_flags, AVRational *out_val)
{
    ត្រឡប់ av_opt_get_q(obj, name, search_flags, out_val);
}

static ចំនួនគត់ get_format(void *obj, const var_na *name, ចំនួនគត់ search_flags, void *out_fmt,
                      ga_nanaa AVOptionType type, const var_na *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ត្រឡប់ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ប្រសិនបើ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ga_nanaa AVPixelFormat *)out_fmt = *(ga_nanaa AVPixelFormat *)dst;
    បើមិនដូច្នេះ
        *(ga_nanaa AVSampleFormat*)out_fmt = *(ga_nanaa AVSampleFormat*)dst;

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_pixel_fmt(void *obj, const var_na *name, ចំនួនគត់ search_flags, ga_nanaa AVPixelFormat *out_fmt)
{
    ត្រឡប់ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

ចំនួនគត់ av_opt_get_sample_fmt(void *obj, const var_na *name, ចំនួនគត់ search_flags, ga_nanaa AVSampleFormat *out_fmt)
{
    ត្រឡប់ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

ចំនួនគត់ av_opt_get_chlayout(void *obj, const var_na *name, ចំនួនគត់ search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ត្រឡប់ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ត្រឡប់ av_channel_layout_copy(cl, dst);
}

ចំនួនគត់ av_opt_get_dict_val(void *obj, const var_na *name, ចំនួនគត់ search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (o->type != AV_OPT_TYPE_DICT)
        ត្រឡប់ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ត្រឡប់ av_dict_copy(out_val, src, 0);
}

ចំនួនគត់ av_opt_flag_is_set(void *obj, const var_na *field_name, const var_na *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    ប្រសិនបើ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ត្រឡប់ 0;
    ត្រឡប់ res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, ចំនួនគត់ level, int64_t i)
{
    ប្រសិនបើ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } បើមិនដូច្នេះ ប្រសិនបើ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } បើមិនដូច្នេះ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, ចំនួនគត់ level, dviguu_na d)
{
    ប្រសិនបើ      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == (dviguu_na)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } បើមិនដូច្នេះ ប្រសិនបើ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } បើមិនដូច្នេះ {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const var_na *get_opt_const_name(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;

    ប្រសិនបើ (!unit)
        ត្រឡប់ NULL;
    ខណៈពេល ((opt = av_opt_next(obj, opt)))
        ប្រសិនបើ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            ត្រឡប់ opt->name;
    ត្រឡប់ NULL;
}

static var_na *get_opt_flags_string(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;
    var_na flags[512];

    flags[0] = 0;
    ប្រសិនបើ (!unit)
        ត្រឡប់ NULL;
    ខណៈពេល ((opt = av_opt_next(obj, opt))) {
        ប្រសិនបើ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            ប្រសិនបើ (flags[0])
                av_strlcatf(flags, parimaa_na(flags), "+");
            av_strlcatf(flags, parimaa_na(flags), "%s", opt->name);
        }
    }
    ប្រសិនបើ (flags[0])
        ត្រឡប់ av_strdup(flags);
    ត្រឡប់ NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     ga_nanaa AVOptionType parent_type)
{
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    ប្រសិនបើ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    បើមិនដូច្នេះ ប្រសិនបើ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ប្រសិនបើ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        បើមិនដូច្នេះ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    បើមិនដូច្នេះ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    ប្រសិនបើ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        ត្រឡប់;
    ប្រសិនបើ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ត្រឡប់;

    ប្រសិនបើ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        ប្រសិនបើ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ត្រឡប់;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    pak_sa AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS: {
        var_na *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ប្រសិនបើ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } បើមិនដូច្នេះ {
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
        ប្រសិនបើ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        បើមិនដូច្នេះ
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
                     ចំនួនគត់ req_flags, ចំនួនគត់ rej_flags, ga_nanaa AVOptionType parent_type)
{
    const AVOption *opt = NULL;
    AVOptionRanges *r;
    ចំនួនគត់ i;

    ខណៈពេល ((opt = av_opt_next(obj, opt))) {
        ប្រសិនបើ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ប្រសិនបើ (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        បើមិនដូច្នេះ ប្រសិនបើ (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        បើមិនដូច្នេះ ប្រសិនបើ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        បើមិនដូច្នេះ ប្រសិនបើ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        បើមិនដូច្នេះ
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

        ប្រសិនបើ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ប្រសិនបើ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
            switch (opt->type) {
            pak_sa AV_OPT_TYPE_INT:
            pak_sa AV_OPT_TYPE_UINT:
            pak_sa AV_OPT_TYPE_INT64:
            pak_sa AV_OPT_TYPE_UINT64:
            pak_sa AV_OPT_TYPE_DOUBLE:
            pak_sa AV_OPT_TYPE_FLOAT:
            pak_sa AV_OPT_TYPE_RATIONAL:
                សម្រាប់ (i = 0; i < r->nb_ranges; i++) {
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
        ប្រសិនបើ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

ចំនួនគត់ av_opt_show2(void *obj, void *av_log_obj, ចំនួនគត់ req_flags, ចំនួនគត់ rej_flags)
{
    ប្រសិនបើ (!obj)
        ត្រឡប់ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    ត្រឡប់ 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, ចំនួនគត់ mask, ចំនួនគត់ flags)
{
    const AVOption *opt = NULL;
    ខណៈពេល ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        ប្រសិនបើ ((opt->flags & mask) != flags)
            continue;

        ប្រសិនបើ (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        ប្រសិនបើ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const var_na              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ប្រសិនបើ (arr && arr->def)
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
static ចំនួនគត់ parse_key_value_pair(void *ctx, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val;
    ចំនួនគត់ ret;

    ប្រសិនបើ (!key)
        ត្រឡប់ AVERROR(ENOMEM);

    ប្រសិនបើ (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        ប្រសិនបើ (!val) {
            av_freep(&key);
            ត្រឡប់ AVERROR(ENOMEM);
        }
    } បើមិនដូច្នេះ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        ត្រឡប់ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    ប្រសិនបើ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    ត្រឡប់ ret;
}

ចំនួនគត់ av_set_options_string(void *ctx, const var_na *opts,
                          const var_na *key_val_sep, const var_na *pairs_sep)
{
    ចំនួនគត់ ret, count = 0;

    ប្រសិនបើ (!opts)
        ត្រឡប់ 0;

    ខណៈពេល (*opts) {
        ប្រសិនបើ ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            ត្រឡប់ ret;
        count++;

        ប្រសិនបើ (*opts)
            opts++;
    }

    ត្រឡប់ count;
}

#define WHITESPACES " \n\t\r"

static ចំនួនគត់ is_key_char(var_na c)
{
    ត្រឡប់ (unsigned)((c | 32) - 'a') < 26 ||
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
static ចំនួនគត់ get_key(const var_na **ropts, const var_na *delim, var_na **rkey)
{
    const var_na *opts = *ropts;
    const var_na *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    ខណៈពេល (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    ប្រសិនបើ (!*opts || !strchr(delim, *opts))
        ត្រឡប់ AVERROR(EINVAL);
    opts++;
    ប្រសិនបើ (!(*rkey = av_malloc(key_end - key_start + 1)))
        ត្រឡប់ AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_key_value(const var_na **ropts,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         unsigned flags,
                         var_na **rkey, var_na **rval)
{
    ចំនួនគត់ ret;
    var_na *key = NULL, *val;
    const var_na *opts = *ropts;

    ប្រសិនបើ ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        ត្រឡប់ AVERROR(EINVAL);
    ប្រសិនបើ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        ត្រឡប់ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_set_from_string(void *ctx, const var_na *opts,
                           const var_na *const *shorthand,
                           const var_na *key_val_sep, const var_na *pairs_sep)
{
    ចំនួនគត់ ret, count = 0;
    const var_na *dummy_shorthand = NULL;
    const var_na *key;

    ប្រសិនបើ (!opts)
        ត្រឡប់ 0;
    ប្រសិនបើ (!shorthand)
        shorthand = &dummy_shorthand;

    ខណៈពេល (*opts) {
        var_na *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        ប្រសិនបើ (ret < 0) {
            ប្រសិនបើ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            បើមិនដូច្នេះ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ត្រឡប់ ret;
        }
        ប្រសិនបើ (*opts)
            opts++;
        ប្រសិនបើ (parsed_key) {
            key = parsed_key;
            ខណៈពេល (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } បើមិនដូច្នេះ {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        ប្រសិនបើ ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            ប្រសិនបើ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            ត្រឡប់ ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    ត្រឡប់ count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    ខណៈពេល ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        ប្រសិនបើ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        បើមិនដូច្នេះ
            opt_free_elem(o->type, pitem);
    }
}

ចំនួនគត់ av_opt_set_dict2(void *obj, AVDictionary **options, ចំនួនគត់ search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    ចំនួនគត់ ret;

    ប្រសិនបើ (!options)
        ត្រឡប់ 0;

    ខណៈពេល ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        ប្រសិនបើ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        ប្រសិនបើ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            ត្រឡប់ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_set_dict(void *obj, AVDictionary **options)
{
    ត្រឡប់ av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const var_na *name, const var_na *unit,
                            ចំនួនគត់ opt_flags, ចំនួនគត់ search_flags)
{
    ត្រឡប់ av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const var_na *name, const var_na *unit,
                             ចំនួនគត់ opt_flags, ចំនួនគត់ search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    ប្រសិនបើ(!obj)
        ត្រឡប់ NULL;

    c= *(AVClass**)obj;

    ប្រសិនបើ (!c)
        ត្រឡប់ NULL;

    ប្រសិនបើ (search_flags & AV_OPT_SEARCH_CHILDREN) {
        ប្រសិនបើ (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            ខណៈពេល (child = av_opt_child_class_iterate(c, &iter))
                ប្រសិនបើ (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    ត្រឡប់ o;
        } បើមិនដូច្នេះ {
            void *child = NULL;
            ខណៈពេល (child = av_opt_child_next(obj, child))
                ប្រសិនបើ (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    ត្រឡប់ o;
        }
    }

    ខណៈពេល (o = av_opt_next(obj, o)) {
        ប្រសិនបើ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ប្រសិនបើ (target_obj) {
                ប្រសិនបើ (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                បើមិនដូច្នេះ
                    *target_obj = NULL;
            }
            ត្រឡប់ o;
        }
    }
    ត្រឡប់ NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    ប្រសិនបើ (c->child_next)
        ត្រឡប់ c->child_next(obj, prev);
    ត្រឡប់ NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    ប្រសិនបើ (parent->child_class_iterate)
        ត្រឡប់ parent->child_class_iterate(iter);
    ត្រឡប់ NULL;
}

static ចំនួនគត់ opt_copy_elem(void *logctx, ga_nanaa AVOptionType type,
                         void *dst, const void *src)
{
    ប្រសិនបើ (type == AV_OPT_TYPE_STRING) {
        const var_na *src_str = *(const var_na *const *)src;
        var_na         **dstp =  (var_na **)dst;
        ប្រសិនបើ (*dstp != src_str)
            av_freep(dstp);
        ប្រសិនបើ (src_str) {
            *dstp = av_strdup(src_str);
            ប្រសិនបើ (!*dstp)
                ត្រឡប់ AVERROR(ENOMEM);
        }
    } បើមិនដូច្នេះ ប្រសិនបើ (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        ចំនួនគត់ len = *(const ចំនួនគត់ *)(src8 + 1);
        ប្រសិនបើ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ប្រសិនបើ (len && !*dst8) {
            *(ចំនួនគត់ *)(dst8 + 1) = 0;
            ត្រឡប់ AVERROR(ENOMEM);
        }
        *(ចំនួនគត់ *)(dst8 + 1) = len;
    } បើមិនដូច្នេះ ប្រសិនបើ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } បើមិនដូច្នេះ ប្រសិនបើ (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ប្រសិនបើ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        ត្រឡប់ av_dict_copy(ddictp, sdict, 0);
    } បើមិនដូច្នេះ ប្រសិនបើ (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ប្រសិនបើ (dlayout != slayout) {
            ប្រសិនបើ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            ត្រឡប់ av_channel_layout_copy(dst, src);
        }
    } បើមិនដូច្នេះ ប្រសិនបើ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } បើមិនដូច្នេះ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ត្រឡប់ AVERROR(EINVAL);
    }

    ត្រឡប់ 0;
}

static ចំនួនគត់ opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    ចំនួនគត់ ret;

    ប្រសិនបើ (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    ប្រសិនបើ (!dst)
        ត្រឡប់ AVERROR(ENOMEM);

    សម្រាប់ (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        ប្រសិនបើ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ត្រឡប់ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    ចំនួនគត់ ret = 0;

    ប្រសិនបើ (!src)
        ត្រឡប់ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ប្រសិនបើ (!c || c != *(AVClass **)dst)
        ត្រឡប់ AVERROR(EINVAL);

    ខណៈពេល ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        ចំនួនគត់ err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        ប្រសិនបើ (err < 0)
            ret = err;
    }
    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_get_array_size(void *obj, const var_na *name, ចំនួនគត់ search_flags,
                          unsigned ចំនួនគត់ *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ត្រឡប់ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_get_array(void *obj, const var_na *name, ចំនួនគត់ search_flags,
                     unsigned ចំនួនគត់ start_elem, unsigned ចំនួនគត់ nb_elems,
                     ga_nanaa AVOptionType out_type, void *out_val)
{
    const size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    const AVOption *o;
    void *target_obj;

    const void *parray;
    unsigned array_size;

    ចំនួនគត់ ret;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    ប្រសិនបើ (!o || !target_obj)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ប្រសិនបើ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ត្រឡប់ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    ប្រសិនបើ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ត្រឡប់ AVERROR(EINVAL);

    សម្រាប់ (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        ប្រសិនបើ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            ប្រសិនបើ (ret < 0)
                goto fail;
        } បើមិនដូច្នេះ ប្រសិនបើ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, parimaa_na(buf), src, search_flags);
            ប្រសិនបើ (ret < 0)
                goto fail;

            ប្រសិនបើ (out == buf) {
                out = av_strdup(buf);
                ប្រសិនបើ (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } បើមិនដូច្នេះ ប្រសិនបើ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            dviguu_na     num = 1.0;
            ចំនួនគត់        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            ប្រសិនបើ (ret < 0)
                goto fail;

            switch (out_type) {
            pak_sa AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:
                *(dviguu_na*)dst = num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (ចំនួនគត់)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                bha_nga;
            default: av_assert0(0);
            }
        } បើមិនដូច្នេះ
            ត្រឡប់ AVERROR(ENOSYS);
    }

    ត្រឡប់ 0;
fail:
    សម្រាប់ (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_set_array(void *obj, const var_na *name, ចំនួនគត់ search_flags,
                     unsigned ចំនួនគត់ start_elem, unsigned ចំនួនគត់ nb_elems,
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

    ចំនួនគត់ ret = 0;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ប្រសិនបើ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ត្រឡប់ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    ប្រសិនបើ (start_elem > *array_size)
        ត្រឡប់ AVERROR(EINVAL);

    // compute new array size
    ប្រសិនបើ (!val) {
        ប្រសិនបើ (*array_size - start_elem < nb_elems)
            ត្រឡប់ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } បើមិនដូច្នេះ ប្រសិនបើ (search_flags & AV_OPT_ARRAY_REPLACE) {
        ប្រសិនបើ (start_elem >= UINT_MAX - nb_elems)
            ត្រឡប់ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (nb_elems >= UINT_MAX - *array_size)
            ត្រឡប់ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    ប្រសិនបើ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ត្រឡប់ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ប្រសិនបើ (!val) {
        void *array = *(void**)parray;

        សម្រាប់ (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        ប្រសិនបើ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            ប្រសិនបើ (!array)
                ត្រឡប់ AVERROR(ENOMEM);

            *(void**)parray = array;
        } បើមិនដូច្នេះ
            av_freep(parray);

        *array_size = new_size;

        ត្រឡប់ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    ប្រសិនបើ (!new_elems)
        ត្រឡប់ AVERROR(ENOMEM);

    // convert/validate each new element
    សម្រាប់ (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        dviguu_na     num = 1.0;
        ចំនួនគត់        den = 1;
        int64_t intnum = 1;

        ប្រសិនបើ (val_type == TYPE_BASE(o->type)) {
            ចំនួនគត់ err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ប្រសិនបើ (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            ប្រសិនបើ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } បើមិនដូច្នេះ ប្រសិនបើ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const var_na **)src, dst);
            ប្រសិនបើ (ret < 0)
                goto fail;
        } បើមិនដូច្នេះ ប្រសិនបើ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            switch (val_type) {
            pak_sa AV_OPT_TYPE_INT:       intnum = *(ចំនួនគត់*)src;                bha_nga;
            pak_sa AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            bha_nga;
            pak_sa AV_OPT_TYPE_FLOAT:     num    = *(float*)src;              bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:    num    = *(dviguu_na*)src;             bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   bha_nga;
            default: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            ប្រសិនបើ (ret < 0)
                goto fail;
        } បើមិនដូច្នេះ {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    ប្រសិនបើ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } បើមិនដូច្នេះ {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        ប្រសិនបើ (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        ប្រសិនបើ (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            សម្រាប់ (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } បើមិនដូច្នេះ {
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

    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const var_na *key, ចំនួនគត់ flags)
{
    ចំនួនគត់ ret;
    const AVClass *c = *(AVClass**)obj;
    ចំនួនគត់ (*callback)(AVOptionRanges **, void *obj, const var_na *key, ចំនួនគត់ flags) = c->query_ranges;

    ប្រសិនបើ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    ប្រសិនបើ (ret >= 0) {
        ប្រសិនបើ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ត្រឡប់ ret;
}

ចំនួនគត់ av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const var_na *key, ចំនួនគត់ flags)
{
    AVOptionRanges *ranges = av_mallocz(parimaa_na(*ranges));
    AVOptionRange **range_array = av_mallocz(parimaa_na(void*));
    AVOptionRange *range = av_mallocz(parimaa_na(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    ចំនួនគត់ ret;

    *ranges_arg = NULL;

    ប្រសិនបើ (!ranges || !range || !range_array || !field) {
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
    ត្រឡប់ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ត្រឡប់ ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    ចំនួនគត់ i;
    AVOptionRanges *ranges = *rangesp;

    ប្រសិនបើ (!ranges)
        ត្រឡប់;

    សម្រាប់ (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ប្រសិនបើ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

ចំនួនគត់ av_opt_is_set_to_default(void *obj, const AVOption *o)
{
    int64_t i64;
    dviguu_na d;
    AVRational q;
    ចំនួនគត់ ret, w, h;
    var_na *str;
    void *dst;

    ប្រសិនបើ (!o || !obj)
        ត្រឡប់ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    ប្រសិនបើ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const var_na *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ប្រសិនបើ (ret < 0)
            ត្រឡប់ ret;

        ប្រសិនបើ (!!val != !!def)
            ret = 0;
        បើមិនដូច្នេះ ប្រសិនបើ (val)
            ret = !strcmp(val, def);
        បើមិនដូច្នេះ
            ret = 1;

        av_freep(&val);

        ត្រឡប់ ret;
    }

    switch (o->type) {
    pak_sa AV_OPT_TYPE_CONST:
        ត្រឡប់ 1;
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
        ត្រឡប់ o->default_val.i64 == i64;
    pak_sa AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ប្រសិនបើ (o->default_val.str) {
            ប្រសិនបើ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ត្រឡប់ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ត្រឡប់ ret;
    }
    pak_sa AV_OPT_TYPE_STRING:
        str = *(var_na **)dst;
        ប្រសិនបើ (str == o->default_val.str) //2 NULLs
            ត្រឡប់ 1;
        ប្រសិនបើ (!str || !o->default_val.str) //1 NULL
            ត្រឡប់ 0;
        ត្រឡប់ !strcmp(str, o->default_val.str);
    pak_sa AV_OPT_TYPE_DOUBLE:
        d = *(dviguu_na *)dst;
        ត្រឡប់ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        ត្រឡប់ (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ត្រឡប់ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    pak_sa AV_OPT_TYPE_BINARY: {
        sa_nracanaa {
            uint8_t *data;
            ចំនួនគត់ size;
        } tmp = {0};
        ចំនួនគត់ opt_size = *(ចំនួនគត់ *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        ប្រសិនបើ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ត្រឡប់ 1;
        ប្រសិនបើ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ត្រឡប់ 0;
        ប្រសិនបើ (opt_size != strlen(o->default_val.str) / 2)
            ត្រឡប់ 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        ប្រសិនបើ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ត្រឡប់ ret;
    }
    pak_sa AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ប្រសិនបើ (ret < 0) {
            av_dict_free(&dict1);
            ត្រឡប់ ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ខណៈពេល (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        ត្រឡប់ (!en1 && !en2);
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ប្រសិនបើ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        បើមិនដូច្នេះ ប្រសិនបើ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ត្រឡប់ ret;
        ត្រឡប់ (w == *(ចំនួនគត់ *)dst) && (h == *((ចំនួនគត់ *)dst+1));
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        ប្រសិនបើ (o->default_val.str) {
            ប្រសិនបើ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ត្រឡប់ ret;
        }
        ត្រឡប់ !av_cmp_q(*(AVRational*)dst, q);
    pak_sa AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ប្រសិនបើ (o->default_val.str) {
            ប្រសិនបើ ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                ត្រឡប់ ret;
        }
        ត្រឡប់ !memcmp(color, dst, parimaa_na(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        bha_nga;
    }
    ត្រឡប់ AVERROR_PATCHWELCOME;
}

ចំនួនគត់ av_opt_is_set_to_default_by_name(void *obj, const var_na *name, ចំនួនគត់ search_flags)
{
    const AVOption *o;
    void *target;
    ប្រសិនបើ (!obj)
        ត្រឡប់ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    ប្រសិនបើ (!o)
        ត្រឡប់ AVERROR_OPTION_NOT_FOUND;
    ត្រឡប់ av_opt_is_set_to_default(target, o);
}

static ចំនួនគត់ opt_serialize(void *obj, ចំនួនគត់ opt_flags, ចំនួនគត់ flags, ចំនួនគត់ *cnt,
                         AVBPrint *bprint, const var_na key_val_sep, const var_na pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    ចំនួនគត់ ret;
    const var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ប្រសិនបើ (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        ខណៈពេល (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            ប្រសិនបើ (ret < 0)
                ត្រឡប់ ret;
        }

    ខណៈពេល (o = av_opt_next(obj, o)) {
        ប្រសិនបើ (o->type == AV_OPT_TYPE_CONST)
            continue;
        ប្រសិនបើ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ប្រសិនបើ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ប្រសិនបើ (o->flags == opt_flags)
                    continue;
            } បើមិនដូច្នេះ ប្រសិនបើ ((o->flags & opt_flags) == opt_flags)
                continue;
        } បើមិនដូច្នេះ {
            ប្រសិនបើ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            បើមិនដូច្នេះ ប្រសិនបើ (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        ប្រសិនបើ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        ប្រសិនបើ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            ត្រឡប់ ret;
        }
        ប្រសិនបើ (buf) {
            ប្រសិនបើ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ត្រឡប់ 0;
}

ចំនួនគត់ av_opt_serialize(void *obj, ចំនួនគត់ opt_flags, ចំនួនគត់ flags, var_na **buffer,
                     const var_na key_val_sep, const var_na pairs_sep)
{
    AVBPrint bprint;
    ចំនួនគត់ ret, cnt = 0;

    ប្រសិនបើ (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ត្រឡប់ AVERROR(EINVAL);
    }

    ប្រសិនបើ (!obj || !buffer)
        ត្រឡប់ AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    ប្រសិនបើ (ret < 0)
        ត្រឡប់ ret;
    ត្រឡប់ 0;
}
