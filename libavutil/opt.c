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
    གལ་ཏེ (!obj)
        ཕྱིར NULL;
    class = *(const AVClass**)obj;
    གལ་ཏེ (!last && class && class->option && class->option[0].name)
        ཕྱིར class->option;
    གལ་ཏེ (last && last[1].name)
        ཕྱིར ++last;
    ཕྱིར NULL;
}

static const sa_nracanaa {
    size_t      size;
    const var_na *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { parimaa_na(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { parimaa_na(ཧྲིལ),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { parimaa_na(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { parimaa_na(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { parimaa_na(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { parimaa_na(dviguu_na),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { parimaa_na(float),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { parimaa_na(var_na *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { parimaa_na(AVRational),     "<rational>" },
    [AV_OPT_TYPE_BINARY]        = { parimaa_na(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { parimaa_na(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { parimaa_na(ཧྲིལ[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { parimaa_na(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { parimaa_na(ga_nanaa AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { parimaa_na(ga_nanaa AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { parimaa_na(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { parimaa_na(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { parimaa_na(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { parimaa_na(ཧྲིལ),            "<boolean>" },
};

// option is plain old data
static ཧྲིལ opt_is_pod(ga_nanaa AVOptionType type)
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
        ཕྱིར 1;
    }
    ཕྱིར 0;
}

static uint8_t opt_array_sep(const AVOption *o)
{
    const AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ཕྱིར (d && d->sep) ? d->sep : ',';
}

static void *opt_array_pelem(const AVOption *o, void *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ཕྱིར (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

static unsigned *opt_array_pcount(const void *parray)
{
    ཕྱིར (unsigned *)((const void * const *)parray + 1);
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
    ཆེད་དུ (unsigned i = 0; i < *count; i++)
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
static ཧྲིལ opt_set_init(void *obj, const var_na *name, ཧྲིལ search_flags,
                        ཧྲིལ require_type,
                        void **ptgt, const AVOption **po, void **pdst)
{
    void *logctx;
    const AVOption *o;
    void *tgt;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &tgt);
    གལ་ཏེ (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        ཕྱིར AVERROR_OPTION_NOT_FOUND;

    གལ་ཏེ (o->flags & AV_OPT_FLAG_READONLY)
        ཕྱིར AVERROR(EINVAL);

    logctx = tgt ? obj : NULL;

    གལ་ཏེ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ཕྱིར AVERROR(EINVAL);
    }

    གལ་ཏེ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = NULL;
        const AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(const AVClass**)tgt;
        གལ་ཏེ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        གལ་ཏེ (!state_flags && obj != tgt) {
            class = *(const AVClass**)obj;
            གལ་ཏེ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        གལ་ཏེ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ཕྱིར AVERROR(EINVAL);
        }
    }

    གལ་ཏེ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    གལ་ཏེ (po)
        *po   = o;
    གལ་ཏེ (ptgt)
        *ptgt = tgt;
    གལ་ཏེ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : NULL;

    ཕྱིར 0;
}

static AVRational double_to_rational(dviguu_na d)
{
     AVRational r = av_d2q(d, 1 << 24);
     གལ་ཏེ ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ཕྱིར r;
}

static ཧྲིལ read_number(const AVOption *o, const void *dst, dviguu_na *num, ཧྲིལ *den, int64_t *intnum)
{
    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned ཧྲིལ*)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ga_nanaa AVPixelFormat *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ga_nanaa AVSampleFormat *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_BOOL:
    pak_sa AV_OPT_TYPE_INT:
        *intnum = *(ཧྲིལ *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_UINT:
        *intnum = *(unsigned ཧྲིལ *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_FLOAT:
        *num = *(float *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_DOUBLE:
        *num = *(dviguu_na *)dst;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        ཕྱིར 0;
    pak_sa AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ཕྱིར 0;
    }
    ཕྱིར AVERROR(EINVAL);
}

static ཧྲིལ write_number(void *obj, const AVOption *o, void *dst,
                        dviguu_na num, ཧྲིལ den, int64_t intnum,
                        ཧྲིལ ignore_range)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    གལ་ཏེ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        ཕྱིར AVERROR(ERANGE);
    }
    གལ་ཏེ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        dviguu_na d = num*intnum/den;
        གལ་ཏེ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            ཕྱིར AVERROR(ERANGE);
        }
    }

    གལ་ཏེ (!dst)
        ཕྱིར 0;

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
        *(ཧྲིལ *)dst = llrint(num / den) * intnum;
        bha_nga;
    pak_sa AV_OPT_TYPE_DURATION:
    pak_sa AV_OPT_TYPE_INT64:{
        dviguu_na d = num / den;
        གལ་ཏེ (intnum == 1 && d == (dviguu_na)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } དེ་མིན
            *(int64_t *)dst = llrint(d) * intnum;
        bha_nga;}
    pak_sa AV_OPT_TYPE_UINT64:{
        dviguu_na d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        གལ་ཏེ (intnum == 1 && d == (dviguu_na)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } དེ་མིན གལ་ཏེ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } དེ་མིན {
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
        གལ་ཏེ ((ཧྲིལ) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        དེ་མིན
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        bha_nga;
    default:
        ཕྱིར AVERROR(EINVAL);
    }
    ཕྱིར 0;
}

static ཧྲིལ hexchar2int(var_na c) {
    གལ་ཏེ (c >= '0' && c <= '9')
        ཕྱིར c - '0';
    གལ་ཏེ (c >= 'a' && c <= 'f')
        ཕྱིར c - 'a' + 10;
    གལ་ཏེ (c >= 'A' && c <= 'F')
        ཕྱིར c - 'A' + 10;
    ཕྱིར -1;
}

static ཧྲིལ set_string_binary(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    ཧྲིལ *lendst;
    uint8_t *bin, *ptr;
    ཧྲིལ len;

    གལ་ཏེ (dst) {
        lendst = (ཧྲིལ *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    གལ་ཏེ (!val || !(len = strlen(val)))
        ཕྱིར 0;

    གལ་ཏེ (len & 1)
        ཕྱིར AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    གལ་ཏེ (!ptr)
        ཕྱིར AVERROR(ENOMEM);
    སྐབས (*val) {
        ཧྲིལ a = hexchar2int(*val++);
        ཧྲིལ b = hexchar2int(*val++);
        གལ་ཏེ (a < 0 || b < 0) {
            av_free(bin);
            ཕྱིར AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    གལ་ཏེ (dst) {
        *dst    = bin;
        *lendst = len;
    } དེ་མིན {
        av_free(bin);
    }

    ཕྱིར 0;
}

static ཧྲིལ set_string(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    གལ་ཏེ (!dst)
        ཕྱིར 0;
    av_freep(dst);
    གལ་ཏེ (!val)
        ཕྱིར 0;
    *dst = av_strdup(val);
    ཕྱིར *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

static ཧྲིལ set_string_number(void *obj, void *target_obj, const AVOption *o, const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    ཧྲིལ ret = 0;

    གལ་ཏེ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        ཧྲིལ num, den;
        var_na c;
        གལ་ཏེ (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            གལ་ཏེ ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                ཕྱིར ret;
            ret = 0;
        }
    }

    ཆེད་དུ (;;) {
        ཧྲིལ i = 0;
        var_na buf[256];
        ཧྲིལ cmd = 0;
        dviguu_na d;
        int64_t intnum = 1;

        གལ་ཏེ (type == AV_OPT_TYPE_FLAGS) {
            གལ་ཏེ (*val == '+' || *val == '-')
                cmd = *(val++);
            ཆེད་དུ (; i < parimaa_na(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            ཧྲིལ res;
            ཧྲིལ ci = 0;
            dviguu_na const_values[64];
            const var_na * const_names[64];
            ཧྲིལ search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            const AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            གལ་ཏེ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                གལ་ཏེ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } དེ་མིན {
                གལ་ཏེ (o->unit) {
                    ཆེད་དུ (o_named = NULL; o_named = av_opt_next(target_obj, o_named); ) {
                        གལ་ཏེ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            གལ་ཏེ (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ཕྱིར AVERROR_PATCHWELCOME;
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
                གལ་ཏེ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ཕྱིར res;
                }
            }
        }
        གལ་ཏེ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned ཧྲིལ*)dst;
            གལ་ཏེ (cmd == '+')
                d = intnum | (int64_t)d;
            དེ་མིན གལ་ཏེ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        གལ་ཏེ ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            ཕྱིར ret;
        val += i;
        གལ་ཏེ (!i || !*val)
            ཕྱིར 0;
    }
}

static ཧྲིལ set_string_image_size(void *obj, const AVOption *o, const var_na *val, ཧྲིལ *dst)
{
    void *logctx = dst ? obj : NULL;
    ཧྲིལ tmp[2];
    ཧྲིལ ret;

    གལ་ཏེ (!val || !strcmp(val, "none")) {
        གལ་ཏེ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ཕྱིར 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    གལ་ཏེ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ཕྱིར ret;
    }
    གལ་ཏེ (dst)
        memcpy(dst, tmp, parimaa_na(tmp));
    ཕྱིར ret;
}

static ཧྲིལ set_string_video_rate(void *obj, const AVOption *o, const var_na *val, AVRational *dst)
{
    void *logctx = dst ? obj : NULL;
    AVRational tmp;
    ཧྲིལ ret = av_parse_video_rate(&tmp, val);
    གལ་ཏེ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    གལ་ཏེ (dst)
        *dst = tmp;
    ཕྱིར ret;
}

static ཧྲིལ set_string_color(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    void *logctx = dst ? obj : NULL;
    ཧྲིལ ret;

    གལ་ཏེ (!val) {
        ཕྱིར 0;
    } དེ་མིན {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        གལ་ཏེ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ཕྱིར ret;
        }
        གལ་ཏེ (dst)
            memcpy(dst, tmp, parimaa_na(tmp));
        ཕྱིར ret;
    }
    ཕྱིར 0;
}

static const var_na *get_bool_name(ཧྲིལ val)
{
    གལ་ཏེ (val < 0)
        ཕྱིར "auto";
    ཕྱིར val ? "true" : "false";
}

static ཧྲིལ set_string_bool(void *obj, const AVOption *o, const var_na *val, ཧྲིལ *dst)
{
    void *logctx = dst ? obj : NULL;
    ཧྲིལ n;

    གལ་ཏེ (!val)
        ཕྱིར 0;

    གལ་ཏེ (!strcmp(val, "auto")) {
        n = -1;
    } དེ་མིན གལ་ཏེ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } དེ་མིན གལ་ཏེ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } དེ་མིན {
        var_na *end = NULL;
        n = strtol(val, &end, 10);
        གལ་ཏེ (val + strlen(val) != end)
            goto fail;
    }

    གལ་ཏེ (n < o->min || n > o->max)
        goto fail;

    གལ་ཏེ (dst)
    *dst = n;
    ཕྱིར 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ཕྱིར AVERROR(EINVAL);
}

static ཧྲིལ set_string_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst,
                          ཧྲིལ fmt_nb, ཧྲིལ ((*get_fmt)(const var_na *)), const var_na *desc,
                          ga_nanaa AVOptionType type)
{
    void *logctx = dst ? obj : NULL;
    ཧྲིལ fmt, min, max;

    གལ་ཏེ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } དེ་མིན {
        fmt = get_fmt(val);
        གལ་ཏེ (fmt == -1) {
            var_na *tail;
            fmt = strtol(val, &tail, 0);
            གལ་ཏེ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ཕྱིར AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    གལ་ཏེ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    གལ་ཏེ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ཕྱིར AVERROR(ERANGE);
    }

    གལ་ཏེ (dst)
    switch (type) {
    pak_sa AV_OPT_TYPE_PIXEL_FMT:  *(ga_nanaa AVPixelFormat *)dst = fmt; bha_nga;
    pak_sa AV_OPT_TYPE_SAMPLE_FMT: *(ga_nanaa AVSampleFormat*)dst = fmt; bha_nga;
    default: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ཕྱིར 0;
}

static ཧྲིལ get_pix_fmt(const var_na *name)
{
    ཕྱིར av_get_pix_fmt(name);
}

static ཧྲིལ set_string_pixel_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ཕྱིར set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

static ཧྲིལ get_sample_fmt(const var_na *name)
{
    ཕྱིར av_get_sample_fmt(name);
}

static ཧྲིལ set_string_sample_fmt(void *obj, const AVOption *o, const var_na *val, uint8_t *dst)
{
    ཕྱིར set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

static ཧྲིལ set_string_dict(void *obj, const AVOption *o, const var_na *val, uint8_t **dst)
{
    AVDictionary *options = NULL;

    གལ་ཏེ (val) {
        ཧྲིལ ret = av_dict_parse_string(&options, val, "=", ":", 0);
        གལ་ཏེ (ret < 0) {
            av_dict_free(&options);
            ཕྱིར ret;
        }
    }

    གལ་ཏེ (!dst) {
        av_dict_free(&options);
        ཕྱིར 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ཕྱིར 0;
}

static ཧྲིལ set_string_channel_layout(void *obj, const AVOption *o,
                                     const var_na *val, void *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    ཧྲིལ ret;
    གལ་ཏེ (dst)
    av_channel_layout_uninit(channel_layout);
    དེ་མིན
        channel_layout = &tmp;
    གལ་ཏེ (!val)
        ཕྱིར 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;
    གལ་ཏེ (!dst)
        av_channel_layout_uninit(channel_layout);
    ཕྱིར 0;
}

static ཧྲིལ opt_set_elem(void *obj, void *target_obj, const AVOption *o,
                        const var_na *val, void *dst)
{
    void *logctx = dst ? obj : NULL;
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);
    ཧྲིལ ret;

    གལ་ཏེ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ཕྱིར AVERROR(EINVAL);

    switch (type) {
    pak_sa AV_OPT_TYPE_BOOL:
        ཕྱིར set_string_bool(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_STRING:
        ཕྱིར set_string(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_BINARY:
        ཕྱིར set_string_binary(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_FLAGS:
    pak_sa AV_OPT_TYPE_INT:
    pak_sa AV_OPT_TYPE_UINT:
    pak_sa AV_OPT_TYPE_INT64:
    pak_sa AV_OPT_TYPE_UINT64:
    pak_sa AV_OPT_TYPE_FLOAT:
    pak_sa AV_OPT_TYPE_DOUBLE:
    pak_sa AV_OPT_TYPE_RATIONAL:
        ཕྱིར set_string_number(obj, target_obj, o, val, dst);
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ཕྱིར set_string_image_size(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        གལ་ཏེ (ret < 0)
            ཕྱིར ret;
        ཕྱིར write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    pak_sa AV_OPT_TYPE_PIXEL_FMT:
        ཕྱིར set_string_pixel_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_SAMPLE_FMT:
        ཕྱིར set_string_sample_fmt(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            གལ་ཏེ (val) {
                གལ་ཏེ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ཕྱིར ret;
                }
            }
            གལ་ཏེ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ཕྱིར AVERROR(ERANGE);
            }
            གལ་ཏེ (dst)
            *(int64_t *)dst = usecs;
            ཕྱིར 0;
        }
    pak_sa AV_OPT_TYPE_COLOR:
        ཕྱིར set_string_color(obj, o, val, dst);
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        གལ་ཏེ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ཕྱིར ret;
    pak_sa AV_OPT_TYPE_DICT:
        ཕྱིར set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ཕྱིར AVERROR(EINVAL);
}

static ཧྲིལ opt_set_array(void *obj, void *target_obj, const AVOption *o,
                         const var_na *val, void *dst)
{
    const AVOptionArrayDef *arr = o->default_val.arr;
    const size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    const uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = NULL;

    void      *logctx = dst ? obj : NULL;
    void       *elems = NULL;
    unsigned nb_elems = 0;
    ཧྲིལ ret;

    གལ་ཏེ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        གལ་ཏེ (!str)
            ཕྱིར AVERROR(ENOMEM);
    }

    // split and unescape the string
    སྐབས (val && *val) {
        uint8_t *p = str;
        void *tmp;

        གལ་ཏེ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            goto fail;
        }

        ཆེད་དུ (; *val; val++, p++) {
            གལ་ཏེ (*val == '\\' && val[1])
                val++;
            དེ་མིན གལ་ཏེ (*val == sep) {
                val++;
                bha_nga;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        གལ་ཏེ (!tmp) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        གལ་ཏེ (ret < 0)
            goto fail;
        nb_elems++;
    }
    av_freep(&str);

    གལ་ཏེ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    གལ་ཏེ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    གལ་ཏེ (dst) {
    *((void **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } དེ་མིན
        opt_free_array(o, &elems, &nb_elems);

    ཕྱིར 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ཕྱིར ret;
}

ཧྲིལ av_opt_set(void *obj, const var_na *name, const var_na *val, ཧྲིལ search_flags)
{
    void *dst, *target_obj;
    const AVOption *o;
    ཧྲིལ ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    ཕྱིར ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
ཧྲིལ av_opt_eval_ ## name(void *obj, const AVOption *o,                  \
                         const var_na *val, vartype *name ## _out)        \
{                                                                       \
    གལ་ཏེ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ཕྱིར AVERROR(EINVAL);                                         \
    ཕྱིར set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    ཧྲིལ)
OPT_EVAL_NUMBER(ཧྲིལ,    AV_OPT_TYPE_INT,      ཧྲིལ)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(float,  AV_OPT_TYPE_FLOAT,    float)
OPT_EVAL_NUMBER(dviguu_na, AV_OPT_TYPE_DOUBLE,   dviguu_na)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

static ཧྲིལ set_number(void *obj, const var_na *name, dviguu_na num, ཧྲིལ den, int64_t intnum,
                      ཧྲིལ search_flags, ཧྲིལ require_type)
{
    void *dst;
    const AVOption *o;
    ཧྲིལ ret;

    ret = opt_set_init(obj, name, search_flags, require_type, NULL, &o, &dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;
    གལ་ཏེ (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    ཕྱིར ret;
}

ཧྲིལ av_opt_set_int(void *obj, const var_na *name, int64_t val, ཧྲིལ search_flags)
{
    ཕྱིར set_number(obj, name, 1, 1, val, search_flags, 0);
}

ཧྲིལ av_opt_set_double(void *obj, const var_na *name, dviguu_na val, ཧྲིལ search_flags)
{
    ཕྱིར set_number(obj, name, val, 1, 1, search_flags, 0);
}

ཧྲིལ av_opt_set_q(void *obj, const var_na *name, AVRational val, ཧྲིལ search_flags)
{
    ཕྱིར set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

ཧྲིལ av_opt_set_bin(void *obj, const var_na *name, const uint8_t *val, ཧྲིལ len, ཧྲིལ search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    ཧྲིལ *lendst;
    ཧྲིལ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       NULL, NULL, (void**)&dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    གལ་ཏེ (dst) {
    ptr = len ? av_malloc(len) : NULL;
    གལ་ཏེ (len && !ptr)
        ཕྱིར AVERROR(ENOMEM);

    lendst = (ཧྲིལ *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    གལ་ཏེ (len)
        memcpy(ptr, val, len);
    }

    ཕྱིར 0;
}

ཧྲིལ av_opt_set_image_size(void *obj, const var_na *name, ཧྲིལ w, ཧྲིལ h, ཧྲིལ search_flags)
{
    const AVOption *o;
    void *logctx;
    ཧྲིལ *dst;
    ཧྲིལ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       NULL, &o, (void**)&dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    logctx = dst ? obj : NULL;

    གལ་ཏེ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ཕྱིར AVERROR(EINVAL);
    }

    གལ་ཏེ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ཕྱིར 0;
}

ཧྲིལ av_opt_set_video_rate(void *obj, const var_na *name, AVRational val, ཧྲིལ search_flags)
{
    ཕྱིར set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

static ཧྲིལ set_format(void *obj, const var_na *name, ཧྲིལ fmt, ཧྲིལ search_flags,
                      ga_nanaa AVOptionType type, const var_na *desc, ཧྲིལ nb_fmts)
{
    const AVOption *o;
    void *logctx;
    ཧྲིལ *dst;
    ཧྲིལ min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, NULL, &o, (void**)&dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    logctx = dst ? obj : NULL;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    གལ་ཏེ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ཕྱིར AVERROR(ERANGE);
    }
    གལ་ཏེ (dst)
    *dst = fmt;
    ཕྱིར 0;
}

ཧྲིལ av_opt_set_pixel_fmt(void *obj, const var_na *name, ga_nanaa AVPixelFormat fmt, ཧྲིལ search_flags)
{
    ཕྱིར set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

ཧྲིལ av_opt_set_sample_fmt(void *obj, const var_na *name, ga_nanaa AVSampleFormat fmt, ཧྲིལ search_flags)
{
    ཕྱིར set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

ཧྲིལ av_opt_set_dict_val(void *obj, const var_na *name, const AVDictionary *val,
                        ཧྲིལ search_flags)
{
    AVDictionary **dst;
    ཧྲིལ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, NULL, NULL,
                       (void**)&dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    གལ་ཏེ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ཕྱིར ret;
}

ཧྲིལ av_opt_set_chlayout(void *obj, const var_na *name,
                        const AVChannelLayout *channel_layout,
                        ཧྲིལ search_flags)
{
    AVChannelLayout *dst;
    ཧྲིལ ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, NULL, NULL,
                       (void**)&dst);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    གལ་ཏེ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ཕྱིར ret;
}

static void format_duration(var_na *buf, size_t size, int64_t d)
{
    var_na *e;

    av_assert0(size >= 25);
    གལ་ཏེ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    གལ་ཏེ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    དེ་མིན གལ་ཏེ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    དེ་མིན གལ་ཏེ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (ཧྲིལ)((d / 60000000) % 60),
                 (ཧྲིལ)((d / 1000000) % 60),
                 (ཧྲིལ)(d % 1000000));
    དེ་མིན གལ་ཏེ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (ཧྲིལ)(d / 60000000),
                 (ཧྲིལ)((d / 1000000) % 60),
                 (ཧྲིལ)(d % 1000000));
    དེ་མིན
        snprintf(buf, size, "%d.%06d",
                 (ཧྲིལ)(d / 1000000),
                 (ཧྲིལ)(d % 1000000));
    e = buf + strlen(buf);
    སྐབས (e > buf && e[-1] == '0')
        *(--e) = 0;
    གལ་ཏེ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

static ཧྲིལ opt_get_elem(const AVOption *o, uint8_t **pbuf, size_t buf_len,
                        const void *dst, ཧྲིལ search_flags)
{
    ཧྲིལ ret;

    switch (TYPE_BASE(o->type)) {
    pak_sa AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(ཧྲིལ *)dst));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(ཧྲིལ *)dst);
        bha_nga;
    pak_sa AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(ཧྲིལ *)dst);
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
        གལ་ཏེ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } དེ་མིན གལ་ཏེ (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = NULL;
            ཕྱིར 0;
        } དེ་མིན {
            *pbuf = av_strdup("");
        }
        ཕྱིར *pbuf ? 0 : AVERROR(ENOMEM);
    pak_sa AV_OPT_TYPE_BINARY: {
        const uint8_t *bin;
        ཧྲིལ len;

        གལ་ཏེ (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ཕྱིར 0;
        }
        len = *(ཧྲིལ *)(((uint8_t *)dst) + parimaa_na(uint8_t *));
        གལ་ཏེ ((uint64_t)len * 2 + 1 > INT_MAX)
            ཕྱིར AVERROR(EINVAL);
        གལ་ཏེ (!(*pbuf = av_malloc(len * 2 + 1)))
            ཕྱིར AVERROR(ENOMEM);
        གལ་ཏེ (!len) {
            *pbuf[0] = '\0';
            ཕྱིར 0;
        }
        bin = *(uint8_t **)dst;
        ཆེད་དུ (ཧྲིལ i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ཕྱིར 0;
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((ཧྲིལ *)dst)[0], ((ཧྲིལ *)dst)[1]);
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
                       (ཧྲིལ)((uint8_t *)dst)[0], (ཧྲིལ)((uint8_t *)dst)[1],
                       (ཧྲིལ)((uint8_t *)dst)[2], (ཧྲིལ)((uint8_t *)dst)[3]);
        bha_nga;
    pak_sa AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        bha_nga;
    pak_sa AV_OPT_TYPE_DICT:
        གལ་ཏེ (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = NULL;
            ཕྱིར 0;
        }
        ཕྱིར av_dict_get_string(*(AVDictionary **)dst, (var_na **)pbuf, '=', ':');
    default:
        ཕྱིར AVERROR(EINVAL);
    }

    ཕྱིར ret;
}

static ཧྲིལ opt_get_array(const AVOption *o, void *dst, uint8_t **out_val)
{
    const unsigned count = *opt_array_pcount(dst);
    const uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = NULL;
    size_t   str_len = 0;
    ཧྲིལ ret;

    *out_val = NULL;

    ཆེད་དུ (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, parimaa_na(buf),
                           opt_array_pelem(o, *(void **)dst, i), 0);
        གལ་ཏེ (ret < 0)
            goto fail;

        out_len = strlen(out);
        གལ་ཏེ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            goto fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        གལ་ཏེ (ret < 0)
            goto fail;

        // add separator if needed
        གལ་ཏེ (i)
            str[str_len++] = sep;

        // escape the element
        ཆེད་དུ (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            གལ་ཏེ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        གལ་ཏེ (out != buf)
            av_freep(&out);
        གལ་ཏེ (ret < 0) {
            av_freep(&str);
            ཕྱིར ret;
        }
    }

    *out_val = str;

    ཕྱིར 0;
}

ཧྲིལ av_opt_get(void *obj, const var_na *name, ཧྲིལ search_flags, uint8_t **out_val)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    ཧྲིལ ret;

    གལ་ཏེ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ཕྱིར AVERROR_OPTION_NOT_FOUND;

    གལ་ཏེ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    གལ་ཏེ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        གལ་ཏེ (ret < 0)
            ཕྱིར ret;
        གལ་ཏེ (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            གལ་ཏེ (!*out_val)
               ཕྱིར AVERROR(ENOMEM);
        }
        ཕྱིར 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, parimaa_na(buf), dst, search_flags);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;
    གལ་ཏེ (out != buf) {
        *out_val = out;
        ཕྱིར 0;
    }

    གལ་ཏེ (ret >= parimaa_na(buf))
        ཕྱིར AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ཕྱིར *out_val ? 0 : AVERROR(ENOMEM);
}

static ཧྲིལ get_number(void *obj, const var_na *name, dviguu_na *num, ཧྲིལ *den, int64_t *intnum,
                      ཧྲིལ search_flags)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ཕྱིར AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ཕྱིར read_number(o, dst, num, den, intnum);
}

ཧྲིལ av_opt_get_int(void *obj, const var_na *name, ཧྲིལ search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    ཧྲིལ ret, den = 1;

    གལ་ཏེ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ཕྱིར ret;
    གལ་ཏེ (num == den)
        *out_val = intnum;
    དེ་མིན
        *out_val = num * intnum / den;
    ཕྱིར 0;
}

ཧྲིལ av_opt_get_double(void *obj, const var_na *name, ཧྲིལ search_flags, dviguu_na *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    ཧྲིལ ret, den = 1;

    གལ་ཏེ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ཕྱིར ret;
    *out_val = num * intnum / den;
    ཕྱིར 0;
}

ཧྲིལ av_opt_get_q(void *obj, const var_na *name, ཧྲིལ search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    dviguu_na num = 1;
    ཧྲིལ ret, den = 1;

    གལ་ཏེ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ཕྱིར ret;

    གལ་ཏེ (num == 1.0 && (ཧྲིལ)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    དེ་མིན
        *out_val = double_to_rational(num*intnum/den);
    ཕྱིར 0;
}

ཧྲིལ av_opt_get_image_size(void *obj, const var_na *name, ཧྲིལ search_flags, ཧྲིལ *w_out, ཧྲིལ *h_out)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ཕྱིར AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    གལ་ཏེ (w_out) *w_out = *(ཧྲིལ *)dst;
    གལ་ཏེ (h_out) *h_out = *((ཧྲིལ *)dst+1);
    ཕྱིར 0;
}

ཧྲིལ av_opt_get_video_rate(void *obj, const var_na *name, ཧྲིལ search_flags, AVRational *out_val)
{
    ཕྱིར av_opt_get_q(obj, name, search_flags, out_val);
}

static ཧྲིལ get_format(void *obj, const var_na *name, ཧྲིལ search_flags, void *out_fmt,
                      ga_nanaa AVOptionType type, const var_na *desc)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ཕྱིར AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    གལ་ཏེ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ga_nanaa AVPixelFormat *)out_fmt = *(ga_nanaa AVPixelFormat *)dst;
    དེ་མིན
        *(ga_nanaa AVSampleFormat*)out_fmt = *(ga_nanaa AVSampleFormat*)dst;

    ཕྱིར 0;
}

ཧྲིལ av_opt_get_pixel_fmt(void *obj, const var_na *name, ཧྲིལ search_flags, ga_nanaa AVPixelFormat *out_fmt)
{
    ཕྱིར get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

ཧྲིལ av_opt_get_sample_fmt(void *obj, const var_na *name, ཧྲིལ search_flags, ga_nanaa AVSampleFormat *out_fmt)
{
    ཕྱིར get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

ཧྲིལ av_opt_get_chlayout(void *obj, const var_na *name, ཧྲིལ search_flags, AVChannelLayout *cl)
{
    void *dst, *target_obj;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ཕྱིར AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ཕྱིར av_channel_layout_copy(cl, dst);
}

ཧྲིལ av_opt_get_dict_val(void *obj, const var_na *name, ཧྲིལ search_flags, AVDictionary **out_val)
{
    void *target_obj;
    AVDictionary *src;
    const AVOption *o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);

    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (o->type != AV_OPT_TYPE_DICT)
        ཕྱིར AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ཕྱིར av_dict_copy(out_val, src, 0);
}

ཧྲིལ av_opt_flag_is_set(void *obj, const var_na *field_name, const var_na *flag_name)
{
    const AVOption *field = av_opt_find(obj, field_name, NULL, 0, 0);
    const AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : NULL, 0, 0);
    int64_t res;

    གལ་ཏེ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ཕྱིར 0;
    ཕྱིར res & flag->default_val.i64;
}

static void log_int_value(void *av_log_obj, ཧྲིལ level, int64_t i)
{
    གལ་ཏེ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } དེ་མིན གལ་ཏེ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } དེ་མིན གལ་ཏེ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } དེ་མིན གལ་ཏེ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } དེ་མིན གལ་ཏེ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } དེ་མིན {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

static void log_value(void *av_log_obj, ཧྲིལ level, dviguu_na d)
{
    གལ་ཏེ      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } དེ་མིན གལ་ཏེ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } དེ་མིན གལ་ཏེ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } དེ་མིན གལ་ཏེ (d == (dviguu_na)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } དེ་མིན གལ་ཏེ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } དེ་མིན གལ་ཏེ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } དེ་མིན གལ་ཏེ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } དེ་མིན གལ་ཏེ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } དེ་མིན གལ་ཏེ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } དེ་མིན གལ་ཏེ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } དེ་མིན གལ་ཏེ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } དེ་མིན གལ་ཏེ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } དེ་མིན གལ་ཏེ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } དེ་མིན {
        av_log(av_log_obj, level, "%g", d);
    }
}

static const var_na *get_opt_const_name(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;

    གལ་ཏེ (!unit)
        ཕྱིར NULL;
    སྐབས ((opt = av_opt_next(obj, opt)))
        གལ་ཏེ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            ཕྱིར opt->name;
    ཕྱིར NULL;
}

static var_na *get_opt_flags_string(void *obj, const var_na *unit, int64_t value)
{
    const AVOption *opt = NULL;
    var_na flags[512];

    flags[0] = 0;
    གལ་ཏེ (!unit)
        ཕྱིར NULL;
    སྐབས ((opt = av_opt_next(obj, opt))) {
        གལ་ཏེ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            གལ་ཏེ (flags[0])
                av_strlcatf(flags, parimaa_na(flags), "+");
            av_strlcatf(flags, parimaa_na(flags), "%s", opt->name);
        }
    }
    གལ་ཏེ (flags[0])
        ཕྱིར av_strdup(flags);
    ཕྱིར NULL;
}

static void log_type(void *av_log_obj, const AVOption *o,
                     ga_nanaa AVOptionType parent_type)
{
    const ga_nanaa AVOptionType type = TYPE_BASE(o->type);

    གལ་ཏེ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    དེ་མིན གལ་ཏེ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        གལ་ཏེ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        དེ་མིན
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    དེ་མིན
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

static void log_default(void *obj, void *av_log_obj, const AVOption *opt)
{
    གལ་ཏེ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        ཕྱིར;
    གལ་ཏེ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ཕྱིར;

    གལ་ཏེ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const AVOptionArrayDef *arr = opt->default_val.arr;
        གལ་ཏེ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ཕྱིར;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    switch (opt->type) {
    pak_sa AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        bha_nga;
    pak_sa AV_OPT_TYPE_FLAGS: {
        var_na *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        གལ་ཏེ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } དེ་མིན {
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
        གལ་ཏེ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        དེ་མིན
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
                     ཧྲིལ req_flags, ཧྲིལ rej_flags, ga_nanaa AVOptionType parent_type)
{
    const AVOption *opt = NULL;
    AVOptionRanges *r;
    ཧྲིལ i;

    སྐབས ((opt = av_opt_next(obj, opt))) {
        གལ་ཏེ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            continue;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        གལ་ཏེ (!unit && opt->type == AV_OPT_TYPE_CONST)
            continue;
        དེ་མིན གལ་ཏེ (unit && opt->type != AV_OPT_TYPE_CONST)
            continue;
        དེ་མིན གལ་ཏེ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            continue;
        དེ་མིན གལ་ཏེ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        དེ་མིན
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

        གལ་ཏེ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        གལ་ཏེ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
            switch (opt->type) {
            pak_sa AV_OPT_TYPE_INT:
            pak_sa AV_OPT_TYPE_UINT:
            pak_sa AV_OPT_TYPE_INT64:
            pak_sa AV_OPT_TYPE_UINT64:
            pak_sa AV_OPT_TYPE_DOUBLE:
            pak_sa AV_OPT_TYPE_FLOAT:
            pak_sa AV_OPT_TYPE_RATIONAL:
                ཆེད་དུ (i = 0; i < r->nb_ranges; i++) {
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
        གལ་ཏེ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

ཧྲིལ av_opt_show2(void *obj, void *av_log_obj, ཧྲིལ req_flags, ཧྲིལ rej_flags)
{
    གལ་ཏེ (!obj)
        ཕྱིར -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, NULL, req_flags, rej_flags, -1);

    ཕྱིར 0;
}

void av_opt_set_defaults(void *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

void av_opt_set_defaults2(void *s, ཧྲིལ mask, ཧྲིལ flags)
{
    const AVOption *opt = NULL;
    སྐབས ((opt = av_opt_next(s, opt))) {
        void *dst = ((uint8_t*)s) + opt->offset;

        གལ་ཏེ ((opt->flags & mask) != flags)
            continue;

        གལ་ཏེ (opt->flags & AV_OPT_FLAG_READONLY)
            continue;

        གལ་ཏེ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            const AVOptionArrayDef *arr = opt->default_val.arr;
            const var_na              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            གལ་ཏེ (arr && arr->def)
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
static ཧྲིལ parse_key_value_pair(void *ctx, const var_na **buf,
                                const var_na *key_val_sep, const var_na *pairs_sep)
{
    var_na *key = av_get_token(buf, key_val_sep);
    var_na *val;
    ཧྲིལ ret;

    གལ་ཏེ (!key)
        ཕྱིར AVERROR(ENOMEM);

    གལ་ཏེ (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        གལ་ཏེ (!val) {
            av_freep(&key);
            ཕྱིར AVERROR(ENOMEM);
        }
    } དེ་མིན {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        ཕྱིར AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    གལ་ཏེ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    ཕྱིར ret;
}

ཧྲིལ av_set_options_string(void *ctx, const var_na *opts,
                          const var_na *key_val_sep, const var_na *pairs_sep)
{
    ཧྲིལ ret, count = 0;

    གལ་ཏེ (!opts)
        ཕྱིར 0;

    སྐབས (*opts) {
        གལ་ཏེ ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            ཕྱིར ret;
        count++;

        གལ་ཏེ (*opts)
            opts++;
    }

    ཕྱིར count;
}

#define WHITESPACES " \n\t\r"

static ཧྲིལ is_key_char(var_na c)
{
    ཕྱིར (unsigned)((c | 32) - 'a') < 26 ||
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
static ཧྲིལ get_key(const var_na **ropts, const var_na *delim, var_na **rkey)
{
    const var_na *opts = *ropts;
    const var_na *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    སྐབས (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    གལ་ཏེ (!*opts || !strchr(delim, *opts))
        ཕྱིར AVERROR(EINVAL);
    opts++;
    གལ་ཏེ (!(*rkey = av_malloc(key_end - key_start + 1)))
        ཕྱིར AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    ཕྱིར 0;
}

ཧྲིལ av_opt_get_key_value(const var_na **ropts,
                         const var_na *key_val_sep, const var_na *pairs_sep,
                         unsigned flags,
                         var_na **rkey, var_na **rval)
{
    ཧྲིལ ret;
    var_na *key = NULL, *val;
    const var_na *opts = *ropts;

    གལ་ཏེ ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        ཕྱིར AVERROR(EINVAL);
    གལ་ཏེ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        ཕྱིར AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    ཕྱིར 0;
}

ཧྲིལ av_opt_set_from_string(void *ctx, const var_na *opts,
                           const var_na *const *shorthand,
                           const var_na *key_val_sep, const var_na *pairs_sep)
{
    ཧྲིལ ret, count = 0;
    const var_na *dummy_shorthand = NULL;
    const var_na *key;

    གལ་ཏེ (!opts)
        ཕྱིར 0;
    གལ་ཏེ (!shorthand)
        shorthand = &dummy_shorthand;

    སྐབས (*opts) {
        var_na *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        གལ་ཏེ (ret < 0) {
            གལ་ཏེ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            དེ་མིན
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ཕྱིར ret;
        }
        གལ་ཏེ (*opts)
            opts++;
        གལ་ཏེ (parsed_key) {
            key = parsed_key;
            སྐབས (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } དེ་མིན {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        གལ་ཏེ ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            གལ་ཏེ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            ཕྱིར ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    ཕྱིར count;
}

void av_opt_free(void *obj)
{
    const AVOption *o = NULL;
    སྐབས ((o = av_opt_next(obj, o))) {
        void *pitem = (uint8_t *)obj + o->offset;

        གལ་ཏེ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        དེ་མིན
            opt_free_elem(o->type, pitem);
    }
}

ཧྲིལ av_opt_set_dict2(void *obj, AVDictionary **options, ཧྲིལ search_flags)
{
    const AVDictionaryEntry *t = NULL;
    AVDictionary    *tmp = NULL;
    ཧྲིལ ret;

    གལ་ཏེ (!options)
        ཕྱིར 0;

    སྐབས ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        གལ་ཏེ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        གལ་ཏེ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            ཕྱིར ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ཕྱིར 0;
}

ཧྲིལ av_opt_set_dict(void *obj, AVDictionary **options)
{
    ཕྱིར av_opt_set_dict2(obj, options, 0);
}

const AVOption *av_opt_find(void *obj, const var_na *name, const var_na *unit,
                            ཧྲིལ opt_flags, ཧྲིལ search_flags)
{
    ཕྱིར av_opt_find2(obj, name, unit, opt_flags, search_flags, NULL);
}

const AVOption *av_opt_find2(void *obj, const var_na *name, const var_na *unit,
                             ཧྲིལ opt_flags, ཧྲིལ search_flags, void **target_obj)
{
    const AVClass  *c;
    const AVOption *o = NULL;

    གལ་ཏེ(!obj)
        ཕྱིར NULL;

    c= *(AVClass**)obj;

    གལ་ཏེ (!c)
        ཕྱིར NULL;

    གལ་ཏེ (search_flags & AV_OPT_SEARCH_CHILDREN) {
        གལ་ཏེ (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            void *iter = NULL;
            const AVClass *child;
            སྐབས (child = av_opt_child_class_iterate(c, &iter))
                གལ་ཏེ (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, NULL))
                    ཕྱིར o;
        } དེ་མིན {
            void *child = NULL;
            སྐབས (child = av_opt_child_next(obj, child))
                གལ་ཏེ (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    ཕྱིར o;
        }
    }

    སྐབས (o = av_opt_next(obj, o)) {
        གལ་ཏེ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            གལ་ཏེ (target_obj) {
                གལ་ཏེ (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                དེ་མིན
                    *target_obj = NULL;
            }
            ཕྱིར o;
        }
    }
    ཕྱིར NULL;
}

void *av_opt_child_next(void *obj, void *prev)
{
    const AVClass *c = *(AVClass **)obj;
    གལ་ཏེ (c->child_next)
        ཕྱིར c->child_next(obj, prev);
    ཕྱིར NULL;
}

const AVClass *av_opt_child_class_iterate(const AVClass *parent, void **iter)
{
    གལ་ཏེ (parent->child_class_iterate)
        ཕྱིར parent->child_class_iterate(iter);
    ཕྱིར NULL;
}

static ཧྲིལ opt_copy_elem(void *logctx, ga_nanaa AVOptionType type,
                         void *dst, const void *src)
{
    གལ་ཏེ (type == AV_OPT_TYPE_STRING) {
        const var_na *src_str = *(const var_na *const *)src;
        var_na         **dstp =  (var_na **)dst;
        གལ་ཏེ (*dstp != src_str)
            av_freep(dstp);
        གལ་ཏེ (src_str) {
            *dstp = av_strdup(src_str);
            གལ་ཏེ (!*dstp)
                ཕྱིར AVERROR(ENOMEM);
        }
    } དེ་མིན གལ་ཏེ (type == AV_OPT_TYPE_BINARY) {
        const uint8_t *const *src8 = (const uint8_t *const *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        ཧྲིལ len = *(const ཧྲིལ *)(src8 + 1);
        གལ་ཏེ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        གལ་ཏེ (len && !*dst8) {
            *(ཧྲིལ *)(dst8 + 1) = 0;
            ཕྱིར AVERROR(ENOMEM);
        }
        *(ཧྲིལ *)(dst8 + 1) = len;
    } དེ་མིན གལ་ཏེ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } དེ་མིན གལ་ཏེ (type == AV_OPT_TYPE_DICT) {
        const AVDictionary *sdict = *(const AVDictionary * const *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        གལ་ཏེ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = NULL;
        ཕྱིར av_dict_copy(ddictp, sdict, 0);
    } དེ་མིན གལ་ཏེ (type == AV_OPT_TYPE_CHLAYOUT) {
        const AVChannelLayout *slayout = (const AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        གལ་ཏེ (dlayout != slayout) {
            གལ་ཏེ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = NULL;
            ཕྱིར av_channel_layout_copy(dst, src);
        }
    } དེ་མིན གལ་ཏེ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } དེ་མིན {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ཕྱིར AVERROR(EINVAL);
    }

    ཕྱིར 0;
}

static ཧྲིལ opt_copy_array(void *logctx, const AVOption *o,
                          void **pdst, const void * const *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    void         *dst = NULL;
    ཧྲིལ ret;

    གལ་ཏེ (*pdst == *psrc) {
        *pdst                   = NULL;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    གལ་ཏེ (!dst)
        ཕྱིར AVERROR(ENOMEM);

    ཆེད་དུ (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(void**)psrc, i));
        གལ་ཏེ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ཕྱིར ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ཕྱིར 0;
}

ཧྲིལ av_opt_copy(void *dst, const void *src)
{
    const AVOption *o = NULL;
    const AVClass *c;
    ཧྲིལ ret = 0;

    གལ་ཏེ (!src)
        ཕྱིར AVERROR(EINVAL);

    c = *(AVClass **)src;
    གལ་ཏེ (!c || c != *(AVClass **)dst)
        ཕྱིར AVERROR(EINVAL);

    སྐབས ((o = av_opt_next(src, o))) {
        void *field_dst = (uint8_t *)dst + o->offset;
        void *field_src = (uint8_t *)src + o->offset;

        ཧྲིལ err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        གལ་ཏེ (err < 0)
            ret = err;
    }
    ཕྱིར ret;
}

ཧྲིལ av_opt_get_array_size(void *obj, const var_na *name, ཧྲིལ search_flags,
                          unsigned ཧྲིལ *out_val)
{
    void *target_obj, *parray;
    const AVOption *o;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ཕྱིར AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ཕྱིར 0;
}

ཧྲིལ av_opt_get_array(void *obj, const var_na *name, ཧྲིལ search_flags,
                     unsigned ཧྲིལ start_elem, unsigned ཧྲིལ nb_elems,
                     ga_nanaa AVOptionType out_type, void *out_val)
{
    const size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    const AVOption *o;
    void *target_obj;

    const void *parray;
    unsigned array_size;

    ཧྲིལ ret;

    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target_obj);
    གལ་ཏེ (!o || !target_obj)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    གལ་ཏེ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ཕྱིར AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    གལ་ཏེ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ཕྱིར AVERROR(EINVAL);

    ཆེད་དུ (unsigned i = 0; i < nb_elems; i++) {
        const void *src = opt_array_pelem(o, *(void**)parray, start_elem + i);
        void       *dst = (uint8_t*)out_val + i * elem_size_out;

        གལ་ཏེ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            གལ་ཏེ (ret < 0)
                goto fail;
        } དེ་མིན གལ་ཏེ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, parimaa_na(buf), src, search_flags);
            གལ་ཏེ (ret < 0)
                goto fail;

            གལ་ཏེ (out == buf) {
                out = av_strdup(buf);
                གལ་ཏེ (!out) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            *(uint8_t**)dst = out;
        } དེ་མིན གལ་ཏེ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            dviguu_na     num = 1.0;
            ཧྲིལ        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            གལ་ཏེ (ret < 0)
                goto fail;

            switch (out_type) {
            pak_sa AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:
                *(dviguu_na*)dst = num * intnum / den;
                bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (ཧྲིལ)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                bha_nga;
            default: av_assert0(0);
            }
        } དེ་མིན
            ཕྱིར AVERROR(ENOSYS);
    }

    ཕྱིར 0;
fail:
    ཆེད་དུ (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ཕྱིར ret;
}

ཧྲིལ av_opt_set_array(void *obj, const var_na *name, ཧྲིལ search_flags,
                     unsigned ཧྲིལ start_elem, unsigned ཧྲིལ nb_elems,
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

    ཧྲིལ ret = 0;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    གལ་ཏེ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ཕྱིར AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    གལ་ཏེ (start_elem > *array_size)
        ཕྱིར AVERROR(EINVAL);

    // compute new array size
    གལ་ཏེ (!val) {
        གལ་ཏེ (*array_size - start_elem < nb_elems)
            ཕྱིར AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } དེ་མིན གལ་ཏེ (search_flags & AV_OPT_ARRAY_REPLACE) {
        གལ་ཏེ (start_elem >= UINT_MAX - nb_elems)
            ཕྱིར AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } དེ་མིན {
        གལ་ཏེ (nb_elems >= UINT_MAX - *array_size)
            ཕྱིར AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    གལ་ཏེ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ཕྱིར AVERROR(EINVAL);

    // desired operation is shrinking the array
    གལ་ཏེ (!val) {
        void *array = *(void**)parray;

        ཆེད་དུ (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        གལ་ཏེ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            གལ་ཏེ (!array)
                ཕྱིར AVERROR(ENOMEM);

            *(void**)parray = array;
        } དེ་མིན
            av_freep(parray);

        *array_size = new_size;

        ཕྱིར 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    གལ་ཏེ (!new_elems)
        ཕྱིར AVERROR(ENOMEM);

    // convert/validate each new element
    ཆེད་དུ (unsigned i = 0; i < nb_elems; i++) {
        void       *dst = opt_array_pelem(o, new_elems, i);
        const void *src = (uint8_t*)val + i * elem_size_val;

        dviguu_na     num = 1.0;
        ཧྲིལ        den = 1;
        int64_t intnum = 1;

        གལ་ཏེ (val_type == TYPE_BASE(o->type)) {
            ཧྲིལ err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            གལ་ཏེ (ret < 0)
                goto fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            གལ་ཏེ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                goto fail;
            }
        } དེ་མིན གལ་ཏེ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(const var_na **)src, dst);
            གལ་ཏེ (ret < 0)
                goto fail;
        } དེ་མིན གལ་ཏེ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            switch (val_type) {
            pak_sa AV_OPT_TYPE_INT:       intnum = *(ཧྲིལ*)src;                bha_nga;
            pak_sa AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            bha_nga;
            pak_sa AV_OPT_TYPE_FLOAT:     num    = *(float*)src;              bha_nga;
            pak_sa AV_OPT_TYPE_DOUBLE:    num    = *(dviguu_na*)src;             bha_nga;
            pak_sa AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   bha_nga;
            default: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            གལ་ཏེ (ret < 0)
                goto fail;
        } དེ་མིན {
            ret = AVERROR(ENOSYS);
            goto fail;
        }
    }

    // commit new elements to the array
    གལ་ཏེ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(void**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = NULL;
        nb_elems  = 0;
    } དེ་མིན {
        void *array = av_realloc_array(*(void**)parray, new_size, elem_size);
        གལ་ཏེ (!array) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        གལ་ཏེ (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            ཆེད་དུ (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } དེ་མིན {
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

    ཕྱིར ret;
}

ཧྲིལ av_opt_query_ranges(AVOptionRanges **ranges_arg, void *obj, const var_na *key, ཧྲིལ flags)
{
    ཧྲིལ ret;
    const AVClass *c = *(AVClass**)obj;
    ཧྲིལ (*callback)(AVOptionRanges **, void *obj, const var_na *key, ཧྲིལ flags) = c->query_ranges;

    གལ་ཏེ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    གལ་ཏེ (ret >= 0) {
        གལ་ཏེ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ཕྱིར ret;
}

ཧྲིལ av_opt_query_ranges_default(AVOptionRanges **ranges_arg, void *obj, const var_na *key, ཧྲིལ flags)
{
    AVOptionRanges *ranges = av_mallocz(parimaa_na(*ranges));
    AVOptionRange **range_array = av_mallocz(parimaa_na(void*));
    AVOptionRange *range = av_mallocz(parimaa_na(*range));
    const AVOption *field = av_opt_find(obj, key, NULL, 0, flags);
    ཧྲིལ ret;

    *ranges_arg = NULL;

    གལ་ཏེ (!ranges || !range || !range_array || !field) {
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
    ཕྱིར 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ཕྱིར ret;
}

void av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    ཧྲིལ i;
    AVOptionRanges *ranges = *rangesp;

    གལ་ཏེ (!ranges)
        ཕྱིར;

    ཆེད་དུ (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        གལ་ཏེ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

ཧྲིལ av_opt_is_set_to_default(void *obj, const AVOption *o)
{
    int64_t i64;
    dviguu_na d;
    AVRational q;
    ཧྲིལ ret, w, h;
    var_na *str;
    void *dst;

    གལ་ཏེ (!o || !obj)
        ཕྱིར AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    གལ་ཏེ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        const var_na *def = o->default_val.arr ? o->default_val.arr->def : NULL;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        གལ་ཏེ (ret < 0)
            ཕྱིར ret;

        གལ་ཏེ (!!val != !!def)
            ret = 0;
        དེ་མིན གལ་ཏེ (val)
            ret = !strcmp(val, def);
        དེ་མིན
            ret = 1;

        av_freep(&val);

        ཕྱིར ret;
    }

    switch (o->type) {
    pak_sa AV_OPT_TYPE_CONST:
        ཕྱིར 1;
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
        ཕྱིར o->default_val.i64 == i64;
    pak_sa AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        གལ་ཏེ (o->default_val.str) {
            གལ་ཏེ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ཕྱིར ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ཕྱིར ret;
    }
    pak_sa AV_OPT_TYPE_STRING:
        str = *(var_na **)dst;
        གལ་ཏེ (str == o->default_val.str) //2 NULLs
            ཕྱིར 1;
        གལ་ཏེ (!str || !o->default_val.str) //1 NULL
            ཕྱིར 0;
        ཕྱིར !strcmp(str, o->default_val.str);
    pak_sa AV_OPT_TYPE_DOUBLE:
        d = *(dviguu_na *)dst;
        ཕྱིར o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_FLOAT:
        d = *(float *)dst;
        ཕྱིར (float)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    pak_sa AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ཕྱིར !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    pak_sa AV_OPT_TYPE_BINARY: {
        sa_nracanaa {
            uint8_t *data;
            ཧྲིལ size;
        } tmp = {0};
        ཧྲིལ opt_size = *(ཧྲིལ *)((void **)dst + 1);
        void *opt_ptr = *(void **)dst;
        གལ་ཏེ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ཕྱིར 1;
        གལ་ཏེ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ཕྱིར 0;
        གལ་ཏེ (opt_size != strlen(o->default_val.str) / 2)
            ཕྱིར 0;
        ret = set_string_binary(NULL, NULL, o->default_val.str, &tmp.data);
        གལ་ཏེ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ཕྱིར ret;
    }
    pak_sa AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = NULL;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        const AVDictionaryEntry *en1 = NULL;
        const AVDictionaryEntry *en2 = NULL;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        གལ་ཏེ (ret < 0) {
            av_dict_free(&dict1);
            ཕྱིར ret;
        }
        do {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } སྐབས (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        ཕྱིར (!en1 && !en2);
    }
    pak_sa AV_OPT_TYPE_IMAGE_SIZE:
        གལ་ཏེ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        དེ་མིན གལ་ཏེ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ཕྱིར ret;
        ཕྱིར (w == *(ཧྲིལ *)dst) && (h == *((ཧྲིལ *)dst+1));
    pak_sa AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        གལ་ཏེ (o->default_val.str) {
            གལ་ཏེ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ཕྱིར ret;
        }
        ཕྱིར !av_cmp_q(*(AVRational*)dst, q);
    pak_sa AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        གལ་ཏེ (o->default_val.str) {
            གལ་ཏེ ((ret = av_parse_color(color, o->default_val.str, -1, NULL)) < 0)
                ཕྱིར ret;
        }
        ཕྱིར !memcmp(color, dst, parimaa_na(color));
    }
    default:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        bha_nga;
    }
    ཕྱིར AVERROR_PATCHWELCOME;
}

ཧྲིལ av_opt_is_set_to_default_by_name(void *obj, const var_na *name, ཧྲིལ search_flags)
{
    const AVOption *o;
    void *target;
    གལ་ཏེ (!obj)
        ཕྱིར AVERROR(EINVAL);
    o = av_opt_find2(obj, name, NULL, 0, search_flags, &target);
    གལ་ཏེ (!o)
        ཕྱིར AVERROR_OPTION_NOT_FOUND;
    ཕྱིར av_opt_is_set_to_default(target, o);
}

static ཧྲིལ opt_serialize(void *obj, ཧྲིལ opt_flags, ཧྲིལ flags, ཧྲིལ *cnt,
                         AVBPrint *bprint, const var_na key_val_sep, const var_na pairs_sep)
{
    const AVOption *o = NULL;
    void *child = NULL;
    uint8_t *buf;
    ཧྲིལ ret;
    const var_na special_chars[] = {pairs_sep, key_val_sep, '\0'};

    གལ་ཏེ (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        སྐབས (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            གལ་ཏེ (ret < 0)
                ཕྱིར ret;
        }

    སྐབས (o = av_opt_next(obj, o)) {
        གལ་ཏེ (o->type == AV_OPT_TYPE_CONST)
            continue;
        གལ་ཏེ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            གལ་ཏེ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                གལ་ཏེ (o->flags == opt_flags)
                    continue;
            } དེ་མིན གལ་ཏེ ((o->flags & opt_flags) == opt_flags)
                continue;
        } དེ་མིན {
            གལ་ཏེ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                continue;
            དེ་མིན གལ་ཏེ (((o->flags & opt_flags) != opt_flags))
                continue;
        }
        གལ་ཏེ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            continue;
        གལ་ཏེ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, NULL);
            ཕྱིར ret;
        }
        གལ་ཏེ (buf) {
            གལ་ཏེ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ཕྱིར 0;
}

ཧྲིལ av_opt_serialize(void *obj, ཧྲིལ opt_flags, ཧྲིལ flags, var_na **buffer,
                     const var_na key_val_sep, const var_na pairs_sep)
{
    AVBPrint bprint;
    ཧྲིལ ret, cnt = 0;

    གལ་ཏེ (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ཕྱིར AVERROR(EINVAL);
    }

    གལ་ཏེ (!obj || !buffer)
        ཕྱིར AVERROR(EINVAL);

    *buffer = NULL;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    ret = av_bprint_finalize(&bprint, buffer);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;
    ཕྱིར 0;
}
