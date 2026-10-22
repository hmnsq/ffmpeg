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

#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "channel_layout.h"
#ಅನ್ತರ್ಭಾವ "dict.h"
#ಅನ್ತರ್ಭಾವ "eval.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "parseutils.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"
#ಅನ್ತರ್ಭಾವ "opt.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"
#ಅನ್ತರ್ಭಾವ "bprint.h"

#ಅನ್ತರ್ಭಾವ <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ಧ್ರುವ AVOption *av_opt_next(ಧ್ರುವ ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *last)
{
    ಧ್ರುವ AVClass *class;
    ಯದಿ (!obj)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    class = *(ಧ್ರುವ AVClass**)obj;
    ಯದಿ (!last && class && class->option && class->option[0].name)
        ಪ್ರತ್ಯಾಗಮ class->option;
    ಯದಿ (last && last[1].name)
        ಪ್ರತ್ಯಾಗಮ ++last;
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    size_t      size;
    ಧ್ರುವ ವರ್ಣ *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { ಪರಿಮಾಣ(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { ಪರಿಮಾಣ(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { ಪರಿಮಾಣ(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { ಪರಿಮಾಣ(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { ಪರಿಮಾಣ(ದ್ವಿಗುಣ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { ಪರಿಮಾಣ(ಭಿನ್ನ),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { ಪರಿಮಾಣ(ವರ್ಣ *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { ಪರಿಮಾಣ(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ದ್ವಿಮಾನ]        = { ಪರಿಮಾಣ(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { ಪರಿಮಾಣ(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { ಪರಿಮಾಣ(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { ಪರಿಮಾಣ(ಗಣನಾ AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { ಪರಿಮಾಣ(ಗಣನಾ AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { ಪರಿಮಾಣ(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { ಪರಿಮಾಣ(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { ಪರಿಮಾಣ(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ),            "<boolean>" },
};

// option is plain old data
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_is_pod(ಗಣನಾ AVOptionType type)
{
    ವಿಕಲ್ಪ (type) {
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
    ಪಕ್ಷ AV_OPT_TYPE_INT64:
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
    ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
    ಪಕ್ಷ AV_OPT_TYPE_DURATION:
    ಪಕ್ಷ AV_OPT_TYPE_COLOR:
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ uint8_t opt_array_sep(ಧ್ರುವ AVOption *o)
{
    ಧ್ರುವ AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ಪ್ರತ್ಯಾಗಮ (d && d->sep) ? d->sep : ',';
}

ಸ್ಥಿರ ಶೂನ್ಯ *opt_array_pelem(ಧ್ರುವ AVOption *o, ಶೂನ್ಯ *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ಪ್ರತ್ಯಾಗಮ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

ಸ್ಥಿರ unsigned *opt_array_pcount(ಧ್ರುವ ಶೂನ್ಯ *parray)
{
    ಪ್ರತ್ಯಾಗಮ (unsigned *)((ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ *)parray + 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ opt_free_elem(ಗಣನಾ AVOptionType type, ಶೂನ್ಯ *ptr)
{
    ವಿಕಲ್ಪ (TYPE_BASE(type)) {
    ಪಕ್ಷ AV_OPT_TYPE_STRING:
    ಪಕ್ಷ AV_OPT_TYPE_ದ್ವಿಮಾನ:
        av_freep(ptr);
        ಭಙ್ಗ;

    ಪಕ್ಷ AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        ಭಙ್ಗ;

    ಪಕ್ಷ AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        ಭಙ್ಗ;

    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ opt_free_array(ಧ್ರುವ AVOption *o, ಶೂನ್ಯ *parray, unsigned *ಎಣಿಕೆ)
{
    ಪ್ರತಿ (unsigned i = 0; i < *ಎಣಿಕೆ; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(ಶೂನ್ಯ **)parray, i));

    av_freep(parray);
    *ಎಣಿಕೆ = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_set_init(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags,
                        ಪೂರ್ಣಾಙ್ಕ require_type,
                        ಶೂನ್ಯ **ptgt, ಧ್ರುವ AVOption **po, ಶೂನ್ಯ **pdst)
{
    ಶೂನ್ಯ *logctx;
    ಧ್ರುವ AVOption *o;
    ಶೂನ್ಯ *tgt;

    o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &tgt);
    ಯದಿ (!o || (!tgt && !(ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_FAKE_OBJ)))
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;

    ಯದಿ (o->flags & AV_OPT_FLAG_READONLY)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    logctx = tgt ? obj : ರಿಕ್ತ;

    ಯದಿ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = ರಿಕ್ತ;
        ಧ್ರುವ AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ಧ್ರುವ AVClass**)tgt;
        ಯದಿ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        ಯದಿ (!state_flags && obj != tgt) {
            class = *(ಧ್ರುವ AVClass**)obj;
            ಯದಿ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        ಯದಿ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    ಯದಿ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ಯದಿ (po)
        *po   = o;
    ಯದಿ (ptgt)
        *ptgt = tgt;
    ಯದಿ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ AVRational double_to_rational(ದ್ವಿಗುಣ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ಯದಿ ((!r.ಅಂಕೆ || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ಪ್ರತ್ಯಾಗಮ r;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ read_ಸಂಖ್ಯೆ(ಧ್ರುವ AVOption *o, ಧ್ರುವ ಶೂನ್ಯ *dst, ದ್ವಿಗುಣ *ಅಂಕೆ, ಪೂರ್ಣಾಙ್ಕ *den, int64_t *intnum)
{
    ವಿಕಲ್ಪ (TYPE_BASE(o->type)) {
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned ಪೂರ್ಣಾಙ್ಕ*)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ಗಣನಾ AVPixelFormat *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ಗಣನಾ AVSampleFormat *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
        *intnum = *(ಪೂರ್ಣಾಙ್ಕ *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
        *intnum = *(unsigned ಪೂರ್ಣಾಙ್ಕ *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_DURATION:
    ಪಕ್ಷ AV_OPT_TYPE_INT64:
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
        *ಅಂಕೆ = *(ಭಿನ್ನ *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
        *ಅಂಕೆ = *(ದ್ವಿಗುಣ *)dst;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->ಅಂಕೆ;
        *den    = ((AVRational *)dst)->den;
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪಕ್ಷ AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ write_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಶೂನ್ಯ *dst,
                        ದ್ವಿಗುಣ ಅಂಕೆ, ಪೂರ್ಣಾಙ್ಕ den, int64_t intnum,
                        ಪೂರ್ಣಾಙ್ಕ ignore_range)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಧ್ರುವ ಗಣನಾ AVOptionType type = TYPE_BASE(o->type);

    ಯದಿ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < ಅಂಕೆ * intnum || o->min * den > ಅಂಕೆ * intnum)) {
        ಅಂಕೆ = den ? ಅಂಕೆ * intnum / den : (ಅಂಕೆ && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               ಅಂಕೆ, o->name, o->min, o->max);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
    }
    ಯದಿ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        ದ್ವಿಗುಣ d = ಅಂಕೆ*intnum/den;
        ಯದಿ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   ಅಂಕೆ*intnum/den, o->name);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
        }
    }

    ಯದಿ (!dst)
        ಪ್ರತ್ಯಾಗಮ 0;

    ವಿಕಲ್ಪ (type) {
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
        *(ಗಣನಾ AVPixelFormat *)dst = llrint(ಅಂಕೆ / den) * intnum;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
        *(ಗಣನಾ AVSampleFormat *)dst = llrint(ಅಂಕೆ / den) * intnum;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
        *(ಪೂರ್ಣಾಙ್ಕ *)dst = llrint(ಅಂಕೆ / den) * intnum;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_DURATION:
    ಪಕ್ಷ AV_OPT_TYPE_INT64:{
        ದ್ವಿಗುಣ d = ಅಂಕೆ / den;
        ಯದಿ (intnum == 1 && d == (ದ್ವಿಗುಣ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ಅನ್ಯಥಾ
            *(int64_t *)dst = llrint(d) * intnum;
        ಭಙ್ಗ;}
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:{
        ದ್ವಿಗುಣ d = ಅಂಕೆ / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ಯದಿ (intnum == 1 && d == (ದ್ವಿಗುಣ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ಅನ್ಯಥಾ ಯದಿ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ಅನ್ಯಥಾ {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        ಭಙ್ಗ;}
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
        *(ಭಿನ್ನ *)dst = ಅಂಕೆ * intnum / den;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
        *(ದ್ವಿಗುಣ    *)dst = ಅಂಕೆ * intnum / den;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
        ಯದಿ ((ಪೂರ್ಣಾಙ್ಕ) ಅಂಕೆ == ಅಂಕೆ)
            *(AVRational *)dst = (AVRational) { ಅಂಕೆ *intnum, den };
        ಅನ್ಯಥಾ
            *(AVRational *)dst = double_to_rational(ಅಂಕೆ * intnum / den);
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ hexchar2int(ವರ್ಣ c) {
    ಯದಿ (c >= '0' && c <= '9')
        ಪ್ರತ್ಯಾಗಮ c - '0';
    ಯದಿ (c >= 'a' && c <= 'f')
        ಪ್ರತ್ಯಾಗಮ c - 'a' + 10;
    ಯದಿ (c >= 'A' && c <= 'F')
        ಪ್ರತ್ಯಾಗಮ c - 'A' + 10;
    ಪ್ರತ್ಯಾಗಮ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_ದ್ವಿಮಾನ(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t **dst)
{
    ಪೂರ್ಣಾಙ್ಕ *lendst;
    uint8_t *bin, *ptr;
    ಪೂರ್ಣಾಙ್ಕ len;

    ಯದಿ (dst) {
        lendst = (ಪೂರ್ಣಾಙ್ಕ *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ಯದಿ (!val || !(len = strlen(val)))
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯದಿ (len & 1)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ಯದಿ (!ptr)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    ಯಾವತ್ (*val) {
        ಪೂರ್ಣಾಙ್ಕ a = hexchar2int(*val++);
        ಪೂರ್ಣಾಙ್ಕ b = hexchar2int(*val++);
        ಯದಿ (a < 0 || b < 0) {
            av_free(bin);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ಯದಿ (dst) {
        *dst    = bin;
        *lendst = len;
    } ಅನ್ಯಥಾ {
        av_free(bin);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t **dst)
{
    ಯದಿ (!dst)
        ಪ್ರತ್ಯಾಗಮ 0;
    av_freep(dst);
    ಯದಿ (!val)
        ಪ್ರತ್ಯಾಗಮ 0;
    *dst = av_strdup(val);
    ಪ್ರತ್ಯಾಗಮ *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *target_obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, ಶೂನ್ಯ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಧ್ರುವ ಗಣನಾ AVOptionType type = TYPE_BASE(o->type);
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ, den;
        ವರ್ಣ c;
        ಯದಿ (sscanf(val, "%d%*1[:/]%d%c", &ಅಂಕೆ, &den, &c) == 2) {
            ಯದಿ ((ret = write_ಸಂಖ್ಯೆ(obj, o, dst, 1, den, ಅಂಕೆ, 0)) >= 0)
                ಪ್ರತ್ಯಾಗಮ ret;
            ret = 0;
        }
    }

    ಪ್ರತಿ (;;) {
        ಪೂರ್ಣಾಙ್ಕ i = 0;
        ವರ್ಣ buf[256];
        ಪೂರ್ಣಾಙ್ಕ cmd = 0;
        ದ್ವಿಗುಣ d;
        int64_t intnum = 1;

        ಯದಿ (type == AV_OPT_TYPE_FLAGS) {
            ಯದಿ (*val == '+' || *val == '-')
                cmd = *(val++);
            ಪ್ರತಿ (; i < ಪರಿಮಾಣ(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            ಪೂರ್ಣಾಙ್ಕ res;
            ಪೂರ್ಣಾಙ್ಕ ci = 0;
            ದ್ವಿಗುಣ const_ಮೌಲ್ಯಗಳು[64];
            ಧ್ರುವ ವರ್ಣ * const_names[64];
            ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_ಹುಡುಕು_CHILDREN : 0;
            ಧ್ರುವ AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, ಹುಡುಕು_flags);
            ಯದಿ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ಯದಿ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ಅನ್ಯಥಾ {
                ಯದಿ (o->unit) {
                    ಪ್ರತಿ (o_named = ರಿಕ್ತ; o_named = av_opt_next(target_obj, o_named); ) {
                        ಯದಿ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ಯದಿ (ci + 6 >= FF_ARRAY_ELEMS(const_ಮೌಲ್ಯಗಳು)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ಪ್ರತ್ಯಾಗಮ AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_ಮೌಲ್ಯಗಳು[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_ಮೌಲ್ಯಗಳು[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_ಮೌಲ್ಯಗಳು[ci++] = o->max;
                const_names [ci  ] = "min";
                const_ಮೌಲ್ಯಗಳು[ci++] = o->min;
                const_names [ci  ] = "none";
                const_ಮೌಲ್ಯಗಳು[ci++] = 0;
                const_names [ci  ] = "all";
                const_ಮೌಲ್ಯಗಳು[ci++] = ~0;
                const_names [ci] = ರಿಕ್ತ;
                const_ಮೌಲ್ಯಗಳು[ci] = 0;

                res = av_ಅಭಿವ್ಯಕ್ತಿ_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_ಮೌಲ್ಯಗಳು, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, 0, obj);
                ಯದಿ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ಪ್ರತ್ಯಾಗಮ res;
                }
            }
        }
        ಯದಿ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned ಪೂರ್ಣಾಙ್ಕ*)dst;
            ಯದಿ (cmd == '+')
                d = intnum | (int64_t)d;
            ಅನ್ಯಥಾ ಯದಿ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ಯದಿ ((ret = write_ಸಂಖ್ಯೆ(obj, o, dst, d, 1, 1, 0)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        val += i;
        ಯದಿ (!i || !*val)
            ಪ್ರತ್ಯಾಗಮ 0;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_image_size(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, ಪೂರ್ಣಾಙ್ಕ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ tmp[2];
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!val || !strcmp(val, "none")) {
        ಯದಿ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    ಯದಿ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    ಯದಿ (dst)
        memcpy(dst, tmp, ಪರಿಮಾಣ(tmp));
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_video_rate(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, AVRational *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    AVRational tmp;
    ಪೂರ್ಣಾಙ್ಕ ret = av_parse_video_rate(&tmp, val);
    ಯದಿ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ಯದಿ (dst)
        *dst = tmp;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_color(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!val) {
        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ಯದಿ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಯದಿ (dst)
            memcpy(dst, tmp, ಪರಿಮಾಣ(tmp));
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *get_bool_name(ಪೂರ್ಣಾಙ್ಕ val)
{
    ಯದಿ (val < 0)
        ಪ್ರತ್ಯಾಗಮ "auto";
    ಪ್ರತ್ಯಾಗಮ val ? "true" : "false";
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_bool(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, ಪೂರ್ಣಾಙ್ಕ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ n;

    ಯದಿ (!val)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯದಿ (!strcmp(val, "auto")) {
        n = -1;
    } ಅನ್ಯಥಾ ಯದಿ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ಅನ್ಯಥಾ ಯದಿ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ಅನ್ಯಥಾ {
        ವರ್ಣ *end = ರಿಕ್ತ;
        n = strtol(val, &end, 10);
        ಯದಿ (val + strlen(val) != end)
            ಗಚ್ಛ fail;
    }

    ಯದಿ (n < o->min || n > o->max)
        ಗಚ್ಛ fail;

    ಯದಿ (dst)
    *dst = n;
    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t *dst,
                          ಪೂರ್ಣಾಙ್ಕ fmt_nb, ಪೂರ್ಣಾಙ್ಕ ((*get_fmt)(ಧ್ರುವ ವರ್ಣ *)), ಧ್ರುವ ವರ್ಣ *desc,
                          ಗಣನಾ AVOptionType type)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ fmt, min, max;

    ಯದಿ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ಅನ್ಯಥಾ {
        fmt = get_fmt(val);
        ಯದಿ (fmt == -1) {
            ವರ್ಣ *tail;
            fmt = strtol(val, &tail, 0);
            ಯದಿ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ಯದಿ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ಯದಿ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
    }

    ಯದಿ (dst)
    ವಿಕಲ್ಪ (type) {
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:  *(ಗಣನಾ AVPixelFormat *)dst = fmt; ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT: *(ಗಣನಾ AVSampleFormat*)dst = fmt; ಭಙ್ಗ;
    ಸ್ವಭಾವ: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_pix_fmt(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪ್ರತ್ಯಾಗಮ av_get_pix_fmt(name);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_pixel_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t *dst)
{
    ಪ್ರತ್ಯಾಗಮ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_sample_fmt(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪ್ರತ್ಯಾಗಮ av_get_sample_fmt(name);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_sample_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t *dst)
{
    ಪ್ರತ್ಯಾಗಮ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_dict(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o, ಧ್ರುವ ವರ್ಣ *val, uint8_t **dst)
{
    AVDictionary *options = ರಿಕ್ತ;

    ಯದಿ (val) {
        ಪೂರ್ಣಾಙ್ಕ ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ಯದಿ (ret < 0) {
            av_dict_free(&options);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    ಯದಿ (!dst) {
        av_dict_free(&options);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_string_channel_layout(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o,
                                     ಧ್ರುವ ವರ್ಣ *val, ಶೂನ್ಯ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಯದಿ (dst)
    av_channel_layout_uninit(channel_layout);
    ಅನ್ಯಥಾ
        channel_layout = &tmp;
    ಯದಿ (!val)
        ಪ್ರತ್ಯಾಗಮ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯದಿ (!dst)
        av_channel_layout_uninit(channel_layout);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_set_elem(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *target_obj, ಧ್ರುವ AVOption *o,
                        ಧ್ರುವ ವರ್ಣ *val, ಶೂನ್ಯ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ರಿಕ್ತ;
    ಧ್ರುವ ಗಣನಾ AVOptionType type = TYPE_BASE(o->type);
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ವಿಕಲ್ಪ (type) {
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
        ಪ್ರತ್ಯಾಗಮ set_string_bool(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_STRING:
        ಪ್ರತ್ಯಾಗಮ set_string(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_ದ್ವಿಮಾನ:
        ಪ್ರತ್ಯಾಗಮ set_string_ದ್ವಿಮಾನ(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
    ಪಕ್ಷ AV_OPT_TYPE_INT64:
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
        ಪ್ರತ್ಯಾಗಮ set_string_ಸಂಖ್ಯೆ(obj, target_obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
        ಪ್ರತ್ಯಾಗಮ set_string_image_size(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        ಪ್ರತ್ಯಾಗಮ write_ಸಂಖ್ಯೆ(obj, o, dst, 1, tmp.den, tmp.ಅಂಕೆ, 0);
    }
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
        ಪ್ರತ್ಯಾಗಮ set_string_pixel_fmt(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
        ಪ್ರತ್ಯಾಗಮ set_string_sample_fmt(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ಯದಿ (val) {
                ಯದಿ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ಪ್ರತ್ಯಾಗಮ ret;
                }
            }
            ಯದಿ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
            }
            ಯದಿ (dst)
            *(int64_t *)dst = usecs;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    ಪಕ್ಷ AV_OPT_TYPE_COLOR:
        ಪ್ರತ್ಯಾಗಮ set_string_color(obj, o, val, dst);
    ಪಕ್ಷ AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        ಯದಿ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ಪ್ರತ್ಯಾಗಮ ret;
    ಪಕ್ಷ AV_OPT_TYPE_DICT:
        ಪ್ರತ್ಯಾಗಮ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_set_array(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *target_obj, ಧ್ರುವ AVOption *o,
                         ಧ್ರುವ ವರ್ಣ *val, ಶೂನ್ಯ *dst)
{
    ಧ್ರುವ AVOptionArrayDef *arr = o->default_val.arr;
    ಧ್ರುವ size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ಧ್ರುವ uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ರಿಕ್ತ;

    ಶೂನ್ಯ      *logctx = dst ? obj : ರಿಕ್ತ;
    ಶೂನ್ಯ       *elems = ರಿಕ್ತ;
    unsigned nb_elems = 0;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        ಯದಿ (!str)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ಯಾವತ್ (val && *val) {
        uint8_t *p = str;
        ಶೂನ್ಯ *tmp;

        ಯದಿ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            ಗಚ್ಛ fail;
        }

        ಪ್ರತಿ (; *val; val++, p++) {
            ಯದಿ (*val == '\\' && val[1])
                val++;
            ಅನ್ಯಥಾ ಯದಿ (*val == sep) {
                val++;
                ಭಙ್ಗ;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        ಯದಿ (!tmp) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;
        nb_elems++;
    }
    av_freep(&str);

    ಯದಿ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ಯದಿ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        ಗಚ್ಛ fail;
    }

    ಯದಿ (dst) {
    *((ಶೂನ್ಯ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ಅನ್ಯಥಾ
        opt_free_array(o, &elems, &nb_elems);

    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *val, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಶೂನ್ಯ *dst, *target_obj;
    ಧ್ರುವ AVOption *o;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, 0, &target_obj, &o, &dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಪ್ರತ್ಯಾಗಮ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_ಸಂಖ್ಯೆ(name, opttype, vartype)                         \
ಪೂರ್ಣಾಙ್ಕ av_opt_eval_ ## name(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o,                  \
                         ಧ್ರುವ ವರ್ಣ *val, vartype *name ## _out)        \
{                                                                       \
    ಯದಿ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);                                         \
    ಪ್ರತ್ಯಾಗಮ set_string_ಸಂಖ್ಯೆ(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_ಸಂಖ್ಯೆ(flags,  AV_OPT_TYPE_FLAGS,    ಪೂರ್ಣಾಙ್ಕ)
OPT_EVAL_ಸಂಖ್ಯೆ(ಪೂರ್ಣಾಙ್ಕ,    AV_OPT_TYPE_INT,      ಪೂರ್ಣಾಙ್ಕ)
OPT_EVAL_ಸಂಖ್ಯೆ(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_ಸಂಖ್ಯೆ(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_ಸಂಖ್ಯೆ(ಭಿನ್ನ,  AV_OPT_TYPE_FLOAT,    ಭಿನ್ನ)
OPT_EVAL_ಸಂಖ್ಯೆ(ದ್ವಿಗುಣ, AV_OPT_TYPE_DOUBLE,   ದ್ವಿಗುಣ)
OPT_EVAL_ಸಂಖ್ಯೆ(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ದ್ವಿಗುಣ ಅಂಕೆ, ಪೂರ್ಣಾಙ್ಕ den, int64_t intnum,
                      ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ಪೂರ್ಣಾಙ್ಕ require_type)
{
    ಶೂನ್ಯ *dst;
    ಧ್ರುವ AVOption *o;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, require_type, ರಿಕ್ತ, &o, &dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯದಿ (dst)
        ret = write_ಸಂಖ್ಯೆ(obj, o, dst, ಅಂಕೆ, den, intnum, 0);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_int(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, int64_t val, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ set_ಸಂಖ್ಯೆ(obj, name, 1, 1, val, ಹುಡುಕು_flags, 0);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_double(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ದ್ವಿಗುಣ val, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ set_ಸಂಖ್ಯೆ(obj, name, val, 1, 1, ಹುಡುಕು_flags, 0);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_q(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, AVRational val, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ set_ಸಂಖ್ಯೆ(obj, name, val.ಅಂಕೆ, val.den, 1, ಹುಡುಕು_flags, 0);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_bin(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ uint8_t *val, ಪೂರ್ಣಾಙ್ಕ len, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    ಪೂರ್ಣಾಙ್ಕ *lendst;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_ದ್ವಿಮಾನ,
                       ರಿಕ್ತ, ರಿಕ್ತ, (ಶೂನ್ಯ**)&dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (dst) {
    ptr = len ? av_malloc(len) : ರಿಕ್ತ;
    ಯದಿ (len && !ptr)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    lendst = (ಪೂರ್ಣಾಙ್ಕ *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ಯದಿ (len)
        memcpy(ptr, val, len);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_image_size(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಧ್ರುವ AVOption *o;
    ಶೂನ್ಯ *logctx;
    ಪೂರ್ಣಾಙ್ಕ *dst;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       ರಿಕ್ತ, &o, (ಶೂನ್ಯ**)&dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    logctx = dst ? obj : ರಿಕ್ತ;

    ಯದಿ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_video_rate(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, AVRational val, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ set_ಸಂಖ್ಯೆ(obj, name, val.ಅಂಕೆ, val.den, 1, ಹುಡುಕು_flags, AV_OPT_TYPE_VIDEO_RATE);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ set_format(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ fmt, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags,
                      ಗಣನಾ AVOptionType type, ಧ್ರುವ ವರ್ಣ *desc, ಪೂರ್ಣಾಙ್ಕ nb_fmts)
{
    ಧ್ರುವ AVOption *o;
    ಶೂನ್ಯ *logctx;
    ಪೂರ್ಣಾಙ್ಕ *dst;
    ಪೂರ್ಣಾಙ್ಕ min, max, ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, type, ರಿಕ್ತ, &o, (ಶೂನ್ಯ**)&dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    logctx = dst ? obj : ರಿಕ್ತ;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ಯದಿ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ERANGE);
    }
    ಯದಿ (dst)
    *dst = fmt;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_pixel_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಗಣನಾ AVPixelFormat fmt, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ set_format(obj, name, fmt, ಹುಡುಕು_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_sample_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಗಣನಾ AVSampleFormat fmt, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ set_format(obj, name, fmt, ಹುಡುಕು_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_dict_val(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ AVDictionary *val,
                        ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    AVDictionary **dst;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_DICT, ರಿಕ್ತ, ರಿಕ್ತ,
                       (ಶೂನ್ಯ**)&dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_chlayout(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name,
                        ಧ್ರುವ AVChannelLayout *channel_layout,
                        ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    AVChannelLayout *dst;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_CHLAYOUT, ರಿಕ್ತ, ರಿಕ್ತ,
                       (ಶೂನ್ಯ**)&dst);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ format_duration(ವರ್ಣ *buf, size_t size, int64_t d)
{
    ವರ್ಣ *e;

    av_assert0(size >= 25);
    ಯದಿ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    ಯದಿ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    ಅನ್ಯಥಾ ಯದಿ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    ಅನ್ಯಥಾ ಯದಿ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (ಪೂರ್ಣಾಙ್ಕ)((d / 60000000) % 60),
                 (ಪೂರ್ಣಾಙ್ಕ)((d / 1000000) % 60),
                 (ಪೂರ್ಣಾಙ್ಕ)(d % 1000000));
    ಅನ್ಯಥಾ ಯದಿ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (ಪೂರ್ಣಾಙ್ಕ)(d / 60000000),
                 (ಪೂರ್ಣಾಙ್ಕ)((d / 1000000) % 60),
                 (ಪೂರ್ಣಾಙ್ಕ)(d % 1000000));
    ಅನ್ಯಥಾ
        snprintf(buf, size, "%d.%06d",
                 (ಪೂರ್ಣಾಙ್ಕ)(d / 1000000),
                 (ಪೂರ್ಣಾಙ್ಕ)(d % 1000000));
    e = buf + strlen(buf);
    ಯಾವತ್ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ಯದಿ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_get_elem(ಧ್ರುವ AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ಧ್ರುವ ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪೂರ್ಣಾಙ್ಕ ret;

    ವಿಕಲ್ಪ (TYPE_BASE(o->type)) {
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(ಪೂರ್ಣಾಙ್ಕ *)dst));
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(ಪೂರ್ಣಾಙ್ಕ *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(ಪೂರ್ಣಾಙ್ಕ *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(ಭಿನ್ನ *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(ದ್ವಿಗುಣ *)dst);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->ಅಂಕೆ, ((AVRational *)dst)->den);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_STRING:
        ಯದಿ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ಅನ್ಯಥಾ ಯದಿ (ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ರಿಕ್ತ;
            ಪ್ರತ್ಯಾಗಮ 0;
        } ಅನ್ಯಥಾ {
            *pbuf = av_strdup("");
        }
        ಪ್ರತ್ಯಾಗಮ *pbuf ? 0 : AVERROR(ENOMEM);
    ಪಕ್ಷ AV_OPT_TYPE_ದ್ವಿಮಾನ: {
        ಧ್ರುವ uint8_t *bin;
        ಪೂರ್ಣಾಙ್ಕ len;

        ಯದಿ (!*(uint8_t **)dst && (ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ರಿಕ್ತ;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        len = *(ಪೂರ್ಣಾಙ್ಕ *)(((uint8_t *)dst) + ಪರಿಮಾಣ(uint8_t *));
        ಯದಿ ((uint64_t)len * 2 + 1 > INT_MAX)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        ಯದಿ (!(*pbuf = av_malloc(len * 2 + 1)))
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        ಯದಿ (!len) {
            *pbuf[0] = '\0';
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        bin = *(uint8_t **)dst;
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((ಪೂರ್ಣಾಙ್ಕ *)dst)[0], ((ಪೂರ್ಣಾಙ್ಕ *)dst)[1]);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ವರ್ಣ *)av_x_if_null(av_get_pix_fmt_name(*(ಗಣನಾ AVPixelFormat *)dst), "none"));
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ವರ್ಣ *)av_x_if_null(av_get_sample_fmt_name(*(ಗಣನಾ AVSampleFormat *)dst), "none"));
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        ಭಙ್ಗ;
    }
    ಪಕ್ಷ AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (ಪೂರ್ಣಾಙ್ಕ)((uint8_t *)dst)[0], (ಪೂರ್ಣಾಙ್ಕ)((uint8_t *)dst)[1],
                       (ಪೂರ್ಣಾಙ್ಕ)((uint8_t *)dst)[2], (ಪೂರ್ಣಾಙ್ಕ)((uint8_t *)dst)[3]);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_DICT:
        ಯದಿ (!*(AVDictionary **)dst && (ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ರಿಕ್ತ;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
        ಪ್ರತ್ಯಾಗಮ av_dict_get_string(*(AVDictionary **)dst, (ವರ್ಣ **)pbuf, '=', ':');
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_get_array(ಧ್ರುವ AVOption *o, ಶೂನ್ಯ *dst, uint8_t **out_val)
{
    ಧ್ರುವ unsigned ಎಣಿಕೆ = *opt_array_pcount(dst);
    ಧ್ರುವ uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ರಿಕ್ತ;
    size_t   str_len = 0;
    ಪೂರ್ಣಾಙ್ಕ ret;

    *out_val = ರಿಕ್ತ;

    ಪ್ರತಿ (unsigned i = 0; i < ಎಣಿಕೆ; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, ಪರಿಮಾಣ(buf),
                           opt_array_pelem(o, *(ಶೂನ್ಯ **)dst, i), 0);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;

        out_len = strlen(out);
        ಯದಿ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            ಗಚ್ಛ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;

        // add separator if needed
        ಯದಿ (i)
            str[str_len++] = sep;

        // escape the element
        ಪ್ರತಿ (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            ಯದಿ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ಯದಿ (out != buf)
            av_freep(&out);
        ಯದಿ (ret < 0) {
            av_freep(&str);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    *out_val = str;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, uint8_t **out_val)
{
    ಶೂನ್ಯ *dst, *target_obj;
    ಧ್ರುವ AVOption *o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    uint8_t *out, buf[128];
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;

    ಯದಿ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    ಯದಿ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        ಯದಿ (!*out_val && !(ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            ಯದಿ (!*out_val)
               ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, ಪರಿಮಾಣ(buf), dst, ಹುಡುಕು_flags);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯದಿ (out != buf) {
        *out_val = out;
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (ret >= ಪರಿಮಾಣ(buf))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ಪ್ರತ್ಯಾಗಮ *out_val ? 0 : AVERROR(ENOMEM);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ದ್ವಿಗುಣ *ಅಂಕೆ, ಪೂರ್ಣಾಙ್ಕ *den, int64_t *intnum,
                      ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಶೂನ್ಯ *dst, *target_obj;
    ಧ್ರುವ AVOption *o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ಪ್ರತ್ಯಾಗಮ read_ಸಂಖ್ಯೆ(o, dst, ಅಂಕೆ, den, intnum);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_int(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    ದ್ವಿಗುಣ ಅಂಕೆ = 1;
    ಪೂರ್ಣಾಙ್ಕ ret, den = 1;

    ಯದಿ ((ret = get_ಸಂಖ್ಯೆ(obj, name, &ಅಂಕೆ, &den, &intnum, ಹುಡುಕು_flags)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯದಿ (ಅಂಕೆ == den)
        *out_val = intnum;
    ಅನ್ಯಥಾ
        *out_val = ಅಂಕೆ * intnum / den;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_double(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ದ್ವಿಗುಣ *out_val)
{
    int64_t intnum = 1;
    ದ್ವಿಗುಣ ಅಂಕೆ = 1;
    ಪೂರ್ಣಾಙ್ಕ ret, den = 1;

    ಯದಿ ((ret = get_ಸಂಖ್ಯೆ(obj, name, &ಅಂಕೆ, &den, &intnum, ಹುಡುಕು_flags)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    *out_val = ಅಂಕೆ * intnum / den;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_q(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    ದ್ವಿಗುಣ ಅಂಕೆ = 1;
    ಪೂರ್ಣಾಙ್ಕ ret, den = 1;

    ಯದಿ ((ret = get_ಸಂಖ್ಯೆ(obj, name, &ಅಂಕೆ, &den, &intnum, ಹುಡುಕು_flags)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (ಅಂಕೆ == 1.0 && (ಪೂರ್ಣಾಙ್ಕ)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    ಅನ್ಯಥಾ
        *out_val = double_to_rational(ಅಂಕೆ*intnum/den);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_image_size(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ಪೂರ್ಣಾಙ್ಕ *w_out, ಪೂರ್ಣಾಙ್ಕ *h_out)
{
    ಶೂನ್ಯ *dst, *target_obj;
    ಧ್ರುವ AVOption *o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ಯದಿ (w_out) *w_out = *(ಪೂರ್ಣಾಙ್ಕ *)dst;
    ಯದಿ (h_out) *h_out = *((ಪೂರ್ಣಾಙ್ಕ *)dst+1);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_video_rate(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, AVRational *out_val)
{
    ಪ್ರತ್ಯಾಗಮ av_opt_get_q(obj, name, ಹುಡುಕು_flags, out_val);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_format(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ಶೂನ್ಯ *out_fmt,
                      ಗಣನಾ AVOptionType type, ಧ್ರುವ ವರ್ಣ *desc)
{
    ಶೂನ್ಯ *dst, *target_obj;
    ಧ್ರುವ AVOption *o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ಯದಿ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ಗಣನಾ AVPixelFormat *)out_fmt = *(ಗಣನಾ AVPixelFormat *)dst;
    ಅನ್ಯಥಾ
        *(ಗಣನಾ AVSampleFormat*)out_fmt = *(ಗಣನಾ AVSampleFormat*)dst;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_pixel_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ಗಣನಾ AVPixelFormat *out_fmt)
{
    ಪ್ರತ್ಯಾಗಮ get_format(obj, name, ಹುಡುಕು_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_sample_fmt(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ಗಣನಾ AVSampleFormat *out_fmt)
{
    ಪ್ರತ್ಯಾಗಮ get_format(obj, name, ಹುಡುಕು_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_chlayout(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, AVChannelLayout *cl)
{
    ಶೂನ್ಯ *dst, *target_obj;
    ಧ್ರುವ AVOption *o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ಪ್ರತ್ಯಾಗಮ av_channel_layout_copy(cl, dst);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_dict_val(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, AVDictionary **out_val)
{
    ಶೂನ್ಯ *target_obj;
    AVDictionary *src;
    ಧ್ರುವ AVOption *o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);

    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (o->type != AV_OPT_TYPE_DICT)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ಪ್ರತ್ಯಾಗಮ av_dict_copy(out_val, src, 0);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_flag_is_set(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *field_name, ಧ್ರುವ ವರ್ಣ *flag_name)
{
    ಧ್ರುವ AVOption *field = av_opt_find(obj, field_name, ರಿಕ್ತ, 0, 0);
    ಧ್ರುವ AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : ರಿಕ್ತ, 0, 0);
    int64_t res;

    ಯದಿ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ಪ್ರತ್ಯಾಗಮ 0;
    ಪ್ರತ್ಯಾಗಮ res & flag->default_val.i64;
}

ಸ್ಥಿರ ಶೂನ್ಯ log_int_ಮೌಲ್ಯ(ಶೂನ್ಯ *av_log_obj, ಪೂರ್ಣಾಙ್ಕ level, int64_t i)
{
    ಯದಿ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ಅನ್ಯಥಾ ಯದಿ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ಅನ್ಯಥಾ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ log_ಮೌಲ್ಯ(ಶೂನ್ಯ *av_log_obj, ಪೂರ್ಣಾಙ್ಕ level, ದ್ವಿಗುಣ d)
{
    ಯದಿ      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ಅನ್ಯಥಾ ಯದಿ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == (ದ್ವಿಗುಣ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ಅನ್ಯಥಾ ಯದಿ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ಅನ್ಯಥಾ ಯದಿ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ಅನ್ಯಥಾ ಯದಿ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ಅನ್ಯಥಾ ಯದಿ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ಅನ್ಯಥಾ ಯದಿ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ಅನ್ಯಥಾ {
        av_log(av_log_obj, level, "%g", d);
    }
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *get_opt_const_name(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *unit, int64_t ಮೌಲ್ಯ)
{
    ಧ್ರುವ AVOption *opt = ರಿಕ್ತ;

    ಯದಿ (!unit)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಯಾವತ್ ((opt = av_opt_next(obj, opt)))
        ಯದಿ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == ಮೌಲ್ಯ)
            ಪ್ರತ್ಯಾಗಮ opt->name;
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ವರ್ಣ *get_opt_flags_string(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *unit, int64_t ಮೌಲ್ಯ)
{
    ಧ್ರುವ AVOption *opt = ರಿಕ್ತ;
    ವರ್ಣ flags[512];

    flags[0] = 0;
    ಯದಿ (!unit)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಯಾವತ್ ((opt = av_opt_next(obj, opt))) {
        ಯದಿ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & ಮೌಲ್ಯ) {
            ಯದಿ (flags[0])
                av_strlcatf(flags, ಪರಿಮಾಣ(flags), "+");
            av_strlcatf(flags, ಪರಿಮಾಣ(flags), "%s", opt->name);
        }
    }
    ಯದಿ (flags[0])
        ಪ್ರತ್ಯಾಗಮ av_strdup(flags);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ log_type(ಶೂನ್ಯ *av_log_obj, ಧ್ರುವ AVOption *o,
                     ಗಣನಾ AVOptionType parent_type)
{
    ಧ್ರುವ ಗಣನಾ AVOptionType type = TYPE_BASE(o->type);

    ಯದಿ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ಅನ್ಯಥಾ ಯದಿ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ಯದಿ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ಅನ್ಯಥಾ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ಅನ್ಯಥಾ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ಸ್ಥಿರ ಶೂನ್ಯ log_default(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *av_log_obj, ಧ್ರುವ AVOption *opt)
{
    ಯದಿ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ದ್ವಿಮಾನ)
        ಪ್ರತ್ಯಾಗಮ;
    ಯದಿ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ಧ್ರುವ AVOptionArrayDef *arr = opt->default_val.arr;
        ಯದಿ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ಪ್ರತ್ಯಾಗಮ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    ವಿಕಲ್ಪ (opt->type) {
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS: {
        ವರ್ಣ *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ಯದಿ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ಅನ್ಯಥಾ {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        ಭಙ್ಗ;
    }
    ಪಕ್ಷ AV_OPT_TYPE_DURATION: {
        ವರ್ಣ buf[25];
        format_duration(buf, ಪರಿಮಾಣ(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        ಭಙ್ಗ;
    }
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
    ಪಕ್ಷ AV_OPT_TYPE_INT64: {
        ಧ್ರುವ ವರ್ಣ *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        ಯದಿ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ಅನ್ಯಥಾ
            log_int_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        ಭಙ್ಗ;
    }
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
        log_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.ಅಂಕೆ, q.den); }
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ವರ್ಣ *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ವರ್ಣ *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_COLOR:
    ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
    ಪಕ್ಷ AV_OPT_TYPE_STRING:
    ಪಕ್ಷ AV_OPT_TYPE_DICT:
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
    ಪಕ್ಷ AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        ಭಙ್ಗ;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ಸ್ಥಿರ ಶೂನ್ಯ opt_list(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *av_log_obj, ಧ್ರುವ ವರ್ಣ *unit,
                     ಪೂರ್ಣಾಙ್ಕ req_flags, ಪೂರ್ಣಾಙ್ಕ rej_flags, ಗಣನಾ AVOptionType parent_type)
{
    ಧ್ರುವ AVOption *opt = ರಿಕ್ತ;
    AVOptionRanges *r;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯಾವತ್ ((opt = av_opt_next(obj, opt))) {
        ಯದಿ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            ಅನುವರ್ತ;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ಯದಿ (!unit && opt->type == AV_OPT_TYPE_CONST)
            ಅನುವರ್ತ;
        ಅನ್ಯಥಾ ಯದಿ (unit && opt->type != AV_OPT_TYPE_CONST)
            ಅನುವರ್ತ;
        ಅನ್ಯಥಾ ಯದಿ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            ಅನುವರ್ತ;
        ಅನ್ಯಥಾ ಯದಿ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ಅನ್ಯಥಾ
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

        ಯದಿ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ಯದಿ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_ಹುಡುಕು_FAKE_OBJ) >= 0) {
            ವಿಕಲ್ಪ (opt->type) {
            ಪಕ್ಷ AV_OPT_TYPE_INT:
            ಪಕ್ಷ AV_OPT_TYPE_UINT:
            ಪಕ್ಷ AV_OPT_TYPE_INT64:
            ಪಕ್ಷ AV_OPT_TYPE_UINT64:
            ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
            ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
            ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
                ಪ್ರತಿ (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, r->range[i]->ಮೌಲ್ಯ_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, r->range[i]->ಮೌಲ್ಯ_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                ಭಙ್ಗ;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        ಯದಿ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

ಪೂರ್ಣಾಙ್ಕ av_opt_show2(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *av_log_obj, ಪೂರ್ಣಾಙ್ಕ req_flags, ಪೂರ್ಣಾಙ್ಕ rej_flags)
{
    ಯದಿ (!obj)
        ಪ್ರತ್ಯಾಗಮ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ರಿಕ್ತ, req_flags, rej_flags, -1);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_opt_set_defaults(ಶೂನ್ಯ *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

ಶೂನ್ಯ av_opt_set_defaults2(ಶೂನ್ಯ *s, ಪೂರ್ಣಾಙ್ಕ mask, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಧ್ರುವ AVOption *opt = ರಿಕ್ತ;
    ಯಾವತ್ ((opt = av_opt_next(s, opt))) {
        ಶೂನ್ಯ *dst = ((uint8_t*)s) + opt->offset;

        ಯದಿ ((opt->flags & mask) != flags)
            ಅನುವರ್ತ;

        ಯದಿ (opt->flags & AV_OPT_FLAG_READONLY)
            ಅನುವರ್ತ;

        ಯದಿ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ಧ್ರುವ AVOptionArrayDef *arr = opt->default_val.arr;
            ಧ್ರುವ ವರ್ಣ              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ಯದಿ (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            ಅನುವರ್ತ;
        }

        ವಿಕಲ್ಪ (opt->type) {
            ಪಕ್ಷ AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_BOOL:
            ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
            ಪಕ್ಷ AV_OPT_TYPE_INT:
            ಪಕ್ಷ AV_OPT_TYPE_UINT:
            ಪಕ್ಷ AV_OPT_TYPE_INT64:
            ಪಕ್ಷ AV_OPT_TYPE_UINT64:
            ಪಕ್ಷ AV_OPT_TYPE_DURATION:
            ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
            ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
                write_ಸಂಖ್ಯೆ(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
            ಪಕ್ಷ AV_OPT_TYPE_FLOAT: {
                ದ್ವಿಗುಣ val;
                val = opt->default_val.dbl;
                write_ಸಂಖ್ಯೆ(s, opt, dst, val, 1, 1, 1);
            }
            ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_ಸಂಖ್ಯೆ(s, opt, dst, 1, val.den, val.ಅಂಕೆ, 1);
            }
            ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_ದ್ವಿಮಾನ:
                set_string_ದ್ವಿಮಾನ(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                ಭಙ್ಗ;
        ಸ್ವಭಾವ:
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
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(ಶೂನ್ಯ *ctx, ಧ್ರುವ ವರ್ಣ **buf,
                                ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ *pairs_sep)
{
    ವರ್ಣ *ಕೀಲಿ = av_get_token(buf, ಕೀಲಿ_val_sep);
    ವರ್ಣ *val;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!ಕೀಲಿ)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯದಿ (*ಕೀಲಿ && strspn(*buf, ಕೀಲಿ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        ಯದಿ (!val) {
            av_freep(&ಕೀಲಿ);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
    } ಅನ್ಯಥಾ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", ಕೀಲಿ);
        av_free(ಕೀಲಿ);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", ಕೀಲಿ, val);

    ret = av_opt_set(ctx, ಕೀಲಿ, val, AV_OPT_ಹುಡುಕು_CHILDREN);
    ಯದಿ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", ಕೀಲಿ);

    av_free(ಕೀಲಿ);
    av_free(val);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_set_options_string(ಶೂನ್ಯ *ctx, ಧ್ರುವ ವರ್ಣ *opts,
                          ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ *pairs_sep)
{
    ಪೂರ್ಣಾಙ್ಕ ret, ಎಣಿಕೆ = 0;

    ಯದಿ (!opts)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯಾವತ್ (*opts) {
        ಯದಿ ((ret = parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(ctx, &opts, ಕೀಲಿ_val_sep, pairs_sep)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        ಎಣಿಕೆ++;

        ಯದಿ (*opts)
            opts++;
    }

    ಪ್ರತ್ಯಾಗಮ ಎಣಿಕೆ;
}

#define WHITESPACES " \n\t\r"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ is_ಕೀಲಿ_char(ವರ್ಣ c)
{
    ಪ್ರತ್ಯಾಗಮ (unsigned)((c | 32) - 'a') < 26 ||
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
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_ಕೀಲಿ(ಧ್ರುವ ವರ್ಣ **ropts, ಧ್ರುವ ವರ್ಣ *delim, ವರ್ಣ **rkey)
{
    ಧ್ರುವ ವರ್ಣ *opts = *ropts;
    ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_start, *ಕೀಲಿ_end;

    ಕೀಲಿ_start = opts += strspn(opts, WHITESPACES);
    ಯಾವತ್ (is_ಕೀಲಿ_char(*opts))
        opts++;
    ಕೀಲಿ_end = opts;
    opts += strspn(opts, WHITESPACES);
    ಯದಿ (!*opts || !strchr(delim, *opts))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    opts++;
    ಯದಿ (!(*rkey = av_malloc(ಕೀಲಿ_end - ಕೀಲಿ_start + 1)))
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    memcpy(*rkey, ಕೀಲಿ_start, ಕೀಲಿ_end - ಕೀಲಿ_start);
    (*rkey)[ಕೀಲಿ_end - ಕೀಲಿ_start] = 0;
    *ropts = opts;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_ಕೀಲಿ_ಮೌಲ್ಯ(ಧ್ರುವ ವರ್ಣ **ropts,
                         ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ *pairs_sep,
                         unsigned flags,
                         ವರ್ಣ **rkey, ವರ್ಣ **rval)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    ವರ್ಣ *ಕೀಲಿ = ರಿಕ್ತ, *val;
    ಧ್ರುವ ವರ್ಣ *opts = *ropts;

    ಯದಿ ((ret = get_ಕೀಲಿ(&opts, ಕೀಲಿ_val_sep, &ಕೀಲಿ)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_ಕೀಲಿ))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಯದಿ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(ಕೀಲಿ);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = ಕೀಲಿ;
    *rval  = val;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_from_string(ಶೂನ್ಯ *ctx, ಧ್ರುವ ವರ್ಣ *opts,
                           ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *shorthand,
                           ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ *pairs_sep)
{
    ಪೂರ್ಣಾಙ್ಕ ret, ಎಣಿಕೆ = 0;
    ಧ್ರುವ ವರ್ಣ *dummy_shorthand = ರಿಕ್ತ;
    ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ;

    ಯದಿ (!opts)
        ಪ್ರತ್ಯಾಗಮ 0;
    ಯದಿ (!shorthand)
        shorthand = &dummy_shorthand;

    ಯಾವತ್ (*opts) {
        ವರ್ಣ *parsed_ಕೀಲಿ, *ಮೌಲ್ಯ;
        ret = av_opt_get_ಕೀಲಿ_ಮೌಲ್ಯ(&opts, ಕೀಲಿ_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_ಕೀಲಿ : 0,
                                   &parsed_ಕೀಲಿ, &ಮೌಲ್ಯ);
        ಯದಿ (ret < 0) {
            ಯದಿ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ಅನ್ಯಥಾ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಯದಿ (*opts)
            opts++;
        ಯದಿ (parsed_ಕೀಲಿ) {
            ಕೀಲಿ = parsed_ಕೀಲಿ;
            ಯಾವತ್ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ಅನ್ಯಥಾ {
            ಕೀಲಿ = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", ಕೀಲಿ, ಮೌಲ್ಯ);
        ಯದಿ ((ret = av_opt_set(ctx, ಕೀಲಿ, ಮೌಲ್ಯ, 0)) < 0) {
            ಯದಿ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", ಕೀಲಿ);
            av_free(ಮೌಲ್ಯ);
            av_free(parsed_ಕೀಲಿ);
            ಪ್ರತ್ಯಾಗಮ ret;
        }

        av_free(ಮೌಲ್ಯ);
        av_free(parsed_ಕೀಲಿ);
        ಎಣಿಕೆ++;
    }
    ಪ್ರತ್ಯಾಗಮ ಎಣಿಕೆ;
}

ಶೂನ್ಯ av_opt_free(ಶೂನ್ಯ *obj)
{
    ಧ್ರುವ AVOption *o = ರಿಕ್ತ;
    ಯಾವತ್ ((o = av_opt_next(obj, o))) {
        ಶೂನ್ಯ *pitem = (uint8_t *)obj + o->offset;

        ಯದಿ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ಅನ್ಯಥಾ
            opt_free_elem(o->type, pitem);
    }
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_dict2(ಶೂನ್ಯ *obj, AVDictionary **options, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಧ್ರುವ AVDictionaryEntry *t = ರಿಕ್ತ;
    AVDictionary    *tmp = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!options)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯಾವತ್ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->ಕೀಲಿ, t->ಮೌಲ್ಯ, ಹುಡುಕು_flags);
        ಯದಿ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->ಕೀಲಿ, t->ಮೌಲ್ಯ, AV_DICT_MULTIKEY);
        ಯದಿ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->ಕೀಲಿ, t->ಮೌಲ್ಯ);
            av_dict_free(&tmp);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_dict(ಶೂನ್ಯ *obj, AVDictionary **options)
{
    ಪ್ರತ್ಯಾಗಮ av_opt_set_dict2(obj, options, 0);
}

ಧ್ರುವ AVOption *av_opt_find(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *unit,
                            ಪೂರ್ಣಾಙ್ಕ opt_flags, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಪ್ರತ್ಯಾಗಮ av_opt_find2(obj, name, unit, opt_flags, ಹುಡುಕು_flags, ರಿಕ್ತ);
}

ಧ್ರುವ AVOption *av_opt_find2(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಧ್ರುವ ವರ್ಣ *unit,
                             ಪೂರ್ಣಾಙ್ಕ opt_flags, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags, ಶೂನ್ಯ **target_obj)
{
    ಧ್ರುವ AVClass  *c;
    ಧ್ರುವ AVOption *o = ರಿಕ್ತ;

    ಯದಿ(!obj)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    c= *(AVClass**)obj;

    ಯದಿ (!c)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_CHILDREN) {
        ಯದಿ (ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_FAKE_OBJ) {
            ಶೂನ್ಯ *iter = ರಿಕ್ತ;
            ಧ್ರುವ AVClass *child;
            ಯಾವತ್ (child = av_opt_child_class_iterate(c, &iter))
                ಯದಿ (o = av_opt_find2(&child, name, unit, opt_flags, ಹುಡುಕು_flags, ರಿಕ್ತ))
                    ಪ್ರತ್ಯಾಗಮ o;
        } ಅನ್ಯಥಾ {
            ಶೂನ್ಯ *child = ರಿಕ್ತ;
            ಯಾವತ್ (child = av_opt_child_next(obj, child))
                ಯದಿ (o = av_opt_find2(child, name, unit, opt_flags, ಹುಡುಕು_flags, target_obj))
                    ಪ್ರತ್ಯಾಗಮ o;
        }
    }

    ಯಾವತ್ (o = av_opt_next(obj, o)) {
        ಯದಿ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ಯದಿ (target_obj) {
                ಯದಿ (!(ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_FAKE_OBJ))
                    *target_obj = obj;
                ಅನ್ಯಥಾ
                    *target_obj = ರಿಕ್ತ;
            }
            ಪ್ರತ್ಯಾಗಮ o;
        }
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಶೂನ್ಯ *av_opt_child_next(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *prev)
{
    ಧ್ರುವ AVClass *c = *(AVClass **)obj;
    ಯದಿ (c->child_next)
        ಪ್ರತ್ಯಾಗಮ c->child_next(obj, prev);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಧ್ರುವ AVClass *av_opt_child_class_iterate(ಧ್ರುವ AVClass *parent, ಶೂನ್ಯ **iter)
{
    ಯದಿ (parent->child_class_iterate)
        ಪ್ರತ್ಯಾಗಮ parent->child_class_iterate(iter);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_copy_elem(ಶೂನ್ಯ *logctx, ಗಣನಾ AVOptionType type,
                         ಶೂನ್ಯ *dst, ಧ್ರುವ ಶೂನ್ಯ *src)
{
    ಯದಿ (type == AV_OPT_TYPE_STRING) {
        ಧ್ರುವ ವರ್ಣ *src_str = *(ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ *)src;
        ವರ್ಣ         **dstp =  (ವರ್ಣ **)dst;
        ಯದಿ (*dstp != src_str)
            av_freep(dstp);
        ಯದಿ (src_str) {
            *dstp = av_strdup(src_str);
            ಯದಿ (!*dstp)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
    } ಅನ್ಯಥಾ ಯದಿ (type == AV_OPT_TYPE_ದ್ವಿಮಾನ) {
        ಧ್ರುವ uint8_t *ಧ್ರುವ *src8 = (ಧ್ರುವ uint8_t *ಧ್ರುವ *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        ಪೂರ್ಣಾಙ್ಕ len = *(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *)(src8 + 1);
        ಯದಿ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ಯದಿ (len && !*dst8) {
            *(ಪೂರ್ಣಾಙ್ಕ *)(dst8 + 1) = 0;
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        *(ಪೂರ್ಣಾಙ್ಕ *)(dst8 + 1) = len;
    } ಅನ್ಯಥಾ ಯದಿ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ಅನ್ಯಥಾ ಯದಿ (type == AV_OPT_TYPE_DICT) {
        ಧ್ರುವ AVDictionary *sdict = *(ಧ್ರುವ AVDictionary * ಧ್ರುವ *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ಯದಿ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ರಿಕ್ತ;
        ಪ್ರತ್ಯಾಗಮ av_dict_copy(ddictp, sdict, 0);
    } ಅನ್ಯಥಾ ಯದಿ (type == AV_OPT_TYPE_CHLAYOUT) {
        ಧ್ರುವ AVChannelLayout *slayout = (ಧ್ರುವ AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ಯದಿ (dlayout != slayout) {
            ಯದಿ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ರಿಕ್ತ;
            ಪ್ರತ್ಯಾಗಮ av_channel_layout_copy(dst, src);
        }
    } ಅನ್ಯಥಾ ಯದಿ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } ಅನ್ಯಥಾ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_copy_array(ಶೂನ್ಯ *logctx, ಧ್ರುವ AVOption *o,
                          ಶೂನ್ಯ **pdst, ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    ಶೂನ್ಯ         *dst = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (*pdst == *psrc) {
        *pdst                   = ರಿಕ್ತ;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    ಯದಿ (!dst)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(ಶೂನ್ಯ**)psrc, i));
        ಯದಿ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_copy(ಶೂನ್ಯ *dst, ಧ್ರುವ ಶೂನ್ಯ *src)
{
    ಧ್ರುವ AVOption *o = ರಿಕ್ತ;
    ಧ್ರುವ AVClass *c;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (!src)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ಯದಿ (!c || c != *(AVClass **)dst)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯಾವತ್ ((o = av_opt_next(src, o))) {
        ಶೂನ್ಯ *field_dst = (uint8_t *)dst + o->offset;
        ಶೂನ್ಯ *field_src = (uint8_t *)src + o->offset;

        ಪೂರ್ಣಾಙ್ಕ err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        ಯದಿ (err < 0)
            ret = err;
    }
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_array_size(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags,
                          unsigned ಪೂರ್ಣಾಙ್ಕ *out_val)
{
    ಶೂನ್ಯ *target_obj, *parray;
    ಧ್ರುವ AVOption *o;

    o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_get_array(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags,
                     unsigned ಪೂರ್ಣಾಙ್ಕ start_elem, unsigned ಪೂರ್ಣಾಙ್ಕ nb_elems,
                     ಗಣನಾ AVOptionType out_type, ಶೂನ್ಯ *out_val)
{
    ಧ್ರುವ size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ಧ್ರುವ AVOption *o;
    ಶೂನ್ಯ *target_obj;

    ಧ್ರುವ ಶೂನ್ಯ *parray;
    unsigned array_size;

    ಪೂರ್ಣಾಙ್ಕ ret;

    o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target_obj);
    ಯದಿ (!o || !target_obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಯದಿ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    ಯದಿ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (unsigned i = 0; i < nb_elems; i++) {
        ಧ್ರುವ ಶೂನ್ಯ *src = opt_array_pelem(o, *(ಶೂನ್ಯ**)parray, start_elem + i);
        ಶೂನ್ಯ       *dst = (uint8_t*)out_val + i * elem_size_out;

        ಯದಿ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;
        } ಅನ್ಯಥಾ ಯದಿ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, ಪರಿಮಾಣ(buf), src, ಹುಡುಕು_flags);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;

            ಯದಿ (out == buf) {
                out = av_strdup(buf);
                ಯದಿ (!out) {
                    ret = AVERROR(ENOMEM);
                    ಗಚ್ಛ fail;
                }
            }

            *(uint8_t**)dst = out;
        } ಅನ್ಯಥಾ ಯದಿ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            ದ್ವಿಗುಣ     ಅಂಕೆ = 1.0;
            ಪೂರ್ಣಾಙ್ಕ        den = 1;
            int64_t intnum = 1;

            ret = read_ಸಂಖ್ಯೆ(o, src, &ಅಂಕೆ, &den, &intnum);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;

            ವಿಕಲ್ಪ (out_type) {
            ಪಕ್ಷ AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (ಅಂಕೆ == den) ?  intnum : ಅಂಕೆ * intnum / den;
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
                *(ದ್ವಿಗುಣ*)dst = ಅಂಕೆ * intnum / den;
                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (ಅಂಕೆ == 1.0 && (ಪೂರ್ಣಾಙ್ಕ)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(ಅಂಕೆ * intnum / den);
                ಭಙ್ಗ;
            ಸ್ವಭಾವ: av_assert0(0);
            }
        } ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    ಪ್ರತಿ (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_set_array(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags,
                     unsigned ಪೂರ್ಣಾಙ್ಕ start_elem, unsigned ಪೂರ್ಣಾಙ್ಕ nb_elems,
                     ಗಣನಾ AVOptionType val_type, ಧ್ರುವ ಶೂನ್ಯ *val)
{
    ಧ್ರುವ size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ಧ್ರುವ AVOption *o;
    ಧ್ರುವ AVOptionArrayDef *arr;
    ಶೂನ್ಯ *target_obj;

    ಶೂನ್ಯ *parray;
    ಶೂನ್ಯ *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ret = opt_set_init(obj, name, ಹುಡುಕು_flags, 0, &target_obj, &o, &parray);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಯದಿ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    ಯದಿ (start_elem > *array_size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    // compute new array size
    ಯದಿ (!val) {
        ಯದಿ (*array_size - start_elem < nb_elems)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } ಅನ್ಯಥಾ ಯದಿ (ಹುಡುಕು_flags & AV_OPT_ARRAY_REPLACE) {
        ಯದಿ (start_elem >= UINT_MAX - nb_elems)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } ಅನ್ಯಥಾ {
        ಯದಿ (nb_elems >= UINT_MAX - *array_size)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    ಯದಿ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ಯದಿ (!val) {
        ಶೂನ್ಯ *array = *(ಶೂನ್ಯ**)parray;

        ಪ್ರತಿ (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        ಯದಿ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            ಯದಿ (!array)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

            *(ಶೂನ್ಯ**)parray = array;
        } ಅನ್ಯಥಾ
            av_freep(parray);

        *array_size = new_size;

        ಪ್ರತ್ಯಾಗಮ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    ಯದಿ (!new_elems)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    // convert/validate each new element
    ಪ್ರತಿ (unsigned i = 0; i < nb_elems; i++) {
        ಶೂನ್ಯ       *dst = opt_array_pelem(o, new_elems, i);
        ಧ್ರುವ ಶೂನ್ಯ *src = (uint8_t*)val + i * elem_size_val;

        ದ್ವಿಗುಣ     ಅಂಕೆ = 1.0;
        ಪೂರ್ಣಾಙ್ಕ        den = 1;
        int64_t intnum = 1;

        ಯದಿ (val_type == TYPE_BASE(o->type)) {
            ಪೂರ್ಣಾಙ್ಕ err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;

            // validate the range for numeric options
            err = read_ಸಂಖ್ಯೆ(o, dst, &ಅಂಕೆ, &den, &intnum);
            ಯದಿ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < ಅಂಕೆ * intnum || o->min * den > ಅಂಕೆ * intnum)) {
                ಅಂಕೆ = den ? ಅಂಕೆ * intnum / den : (ಅಂಕೆ && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, ಅಂಕೆ, o->min, o->max);
                ret = AVERROR(ERANGE);
                ಗಚ್ಛ fail;
            }
        } ಅನ್ಯಥಾ ಯದಿ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ಧ್ರುವ ವರ್ಣ **)src, dst);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;
        } ಅನ್ಯಥಾ ಯದಿ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            ವಿಕಲ್ಪ (val_type) {
            ಪಕ್ಷ AV_OPT_TYPE_INT:       intnum = *(ಪೂರ್ಣಾಙ್ಕ*)src;                ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_FLOAT:     ಅಂಕೆ    = *(ಭಿನ್ನ*)src;              ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:    ಅಂಕೆ    = *(ದ್ವಿಗುಣ*)src;             ಭಙ್ಗ;
            ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->ಅಂಕೆ;
                                        den    = ((AVRational*)src)->den;   ಭಙ್ಗ;
            ಸ್ವಭಾವ: av_assert0(0);
            }

            ret = write_ಸಂಖ್ಯೆ(obj, o, dst, ಅಂಕೆ, den, intnum, 0);
            ಯದಿ (ret < 0)
                ಗಚ್ಛ fail;
        } ಅನ್ಯಥಾ {
            ret = AVERROR(ENOSYS);
            ಗಚ್ಛ fail;
        }
    }

    // commit new elements to the array
    ಯದಿ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(ಶೂನ್ಯ**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = ರಿಕ್ತ;
        nb_elems  = 0;
    } ಅನ್ಯಥಾ {
        ಶೂನ್ಯ *array = av_realloc_array(*(ಶೂನ್ಯ**)parray, new_size, elem_size);
        ಯದಿ (!array) {
            ret = AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }

        ಯದಿ (ಹುಡುಕು_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            ಪ್ರತಿ (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ಅನ್ಯಥಾ {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(ಶೂನ್ಯ**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_query_ranges(AVOptionRanges **ranges_arg, ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಧ್ರುವ AVClass *c = *(AVClass**)obj;
    ಪೂರ್ಣಾಙ್ಕ (*callback)(AVOptionRanges **, ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ flags) = c->query_ranges;

    ಯದಿ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, ಕೀಲಿ, flags);
    ಯದಿ (ret >= 0) {
        ಯದಿ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_query_ranges_default(AVOptionRanges **ranges_arg, ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVOptionRanges *ranges = av_mallocz(ಪರಿಮಾಣ(*ranges));
    AVOptionRange **range_array = av_mallocz(ಪರಿಮಾಣ(ಶೂನ್ಯ*));
    AVOptionRange *range = av_mallocz(ಪರಿಮಾಣ(*range));
    ಧ್ರುವ AVOption *field = av_opt_find(obj, ಕೀಲಿ, ರಿಕ್ತ, 0, flags);
    ಪೂರ್ಣಾಙ್ಕ ret;

    *ranges_arg = ರಿಕ್ತ;

    ಯದಿ (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->ಮೌಲ್ಯ_min = field->min;
    range->ಮೌಲ್ಯ_max = field->max;

    ವಿಕಲ್ಪ (field->type) {
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
    ಪಕ್ಷ AV_OPT_TYPE_INT64:
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
    ಪಕ್ಷ AV_OPT_TYPE_DURATION:
    ಪಕ್ಷ AV_OPT_TYPE_COLOR:
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->ಮೌಲ್ಯ_min = -1;
        range->ಮೌಲ್ಯ_max = INT_MAX;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->ಮೌಲ್ಯ_min = 0;
        range->ಮೌಲ್ಯ_max = INT_MAX/8;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->ಮೌಲ್ಯ_min = 1;
        range->ಮೌಲ್ಯ_max = INT_MAX;
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        ret = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }

    *ranges_arg = ranges;
    ಪ್ರತ್ಯಾಗಮ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    AVOptionRanges *ranges = *rangesp;

    ಯದಿ (!ranges)
        ಪ್ರತ್ಯಾಗಮ;

    ಪ್ರತಿ (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ಯದಿ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

ಪೂರ್ಣಾಙ್ಕ av_opt_is_set_to_default(ಶೂನ್ಯ *obj, ಧ್ರುವ AVOption *o)
{
    int64_t i64;
    ದ್ವಿಗುಣ d;
    AVRational q;
    ಪೂರ್ಣಾಙ್ಕ ret, w, h;
    ವರ್ಣ *str;
    ಶೂನ್ಯ *dst;

    ಯದಿ (!o || !obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    ಯದಿ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ಧ್ರುವ ವರ್ಣ *def = o->default_val.arr ? o->default_val.arr->def : ರಿಕ್ತ;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        ಯದಿ (!!val != !!def)
            ret = 0;
        ಅನ್ಯಥಾ ಯದಿ (val)
            ret = !strcmp(val, def);
        ಅನ್ಯಥಾ
            ret = 1;

        av_freep(&val);

        ಪ್ರತ್ಯಾಗಮ ret;
    }

    ವಿಕಲ್ಪ (o->type) {
    ಪಕ್ಷ AV_OPT_TYPE_CONST:
        ಪ್ರತ್ಯಾಗಮ 1;
    ಪಕ್ಷ AV_OPT_TYPE_BOOL:
    ಪಕ್ಷ AV_OPT_TYPE_FLAGS:
    ಪಕ್ಷ AV_OPT_TYPE_PIXEL_FMT:
    ಪಕ್ಷ AV_OPT_TYPE_SAMPLE_FMT:
    ಪಕ್ಷ AV_OPT_TYPE_INT:
    ಪಕ್ಷ AV_OPT_TYPE_UINT:
    ಪಕ್ಷ AV_OPT_TYPE_DURATION:
    ಪಕ್ಷ AV_OPT_TYPE_INT64:
    ಪಕ್ಷ AV_OPT_TYPE_UINT64:
        read_ಸಂಖ್ಯೆ(o, dst, ರಿಕ್ತ, ರಿಕ್ತ, &i64);
        ಪ್ರತ್ಯಾಗಮ o->default_val.i64 == i64;
    ಪಕ್ಷ AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ಯದಿ (o->default_val.str) {
            ಯದಿ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    ಪಕ್ಷ AV_OPT_TYPE_STRING:
        str = *(ವರ್ಣ **)dst;
        ಯದಿ (str == o->default_val.str) //2 NULLs
            ಪ್ರತ್ಯಾಗಮ 1;
        ಯದಿ (!str || !o->default_val.str) //1 NULL
            ಪ್ರತ್ಯಾಗಮ 0;
        ಪ್ರತ್ಯಾಗಮ !strcmp(str, o->default_val.str);
    ಪಕ್ಷ AV_OPT_TYPE_DOUBLE:
        d = *(ದ್ವಿಗುಣ *)dst;
        ಪ್ರತ್ಯಾಗಮ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ಪಕ್ಷ AV_OPT_TYPE_FLOAT:
        d = *(ಭಿನ್ನ *)dst;
        ಪ್ರತ್ಯಾಗಮ (ಭಿನ್ನ)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ಪಕ್ಷ AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ಪ್ರತ್ಯಾಗಮ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    ಪಕ್ಷ AV_OPT_TYPE_ದ್ವಿಮಾನ: {
        ಸಂರಚನಾ {
            uint8_t *data;
            ಪೂರ್ಣಾಙ್ಕ size;
        } tmp = {0};
        ಪೂರ್ಣಾಙ್ಕ opt_size = *(ಪೂರ್ಣಾಙ್ಕ *)((ಶೂನ್ಯ **)dst + 1);
        ಶೂನ್ಯ *opt_ptr = *(ಶೂನ್ಯ **)dst;
        ಯದಿ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ಪ್ರತ್ಯಾಗಮ 1;
        ಯದಿ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ಪ್ರತ್ಯಾಗಮ 0;
        ಯದಿ (opt_size != strlen(o->default_val.str) / 2)
            ಪ್ರತ್ಯಾಗಮ 0;
        ret = set_string_ದ್ವಿಮಾನ(ರಿಕ್ತ, ರಿಕ್ತ, o->default_val.str, &tmp.data);
        ಯದಿ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    ಪಕ್ಷ AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ರಿಕ್ತ;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ಧ್ರುವ AVDictionaryEntry *en1 = ರಿಕ್ತ;
        ಧ್ರುವ AVDictionaryEntry *en2 = ರಿಕ್ತ;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ಯದಿ (ret < 0) {
            av_dict_free(&dict1);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಕುರು {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ಯಾವತ್ (en1 && en2 && !strcmp(en1->ಕೀಲಿ, en2->ಕೀಲಿ) && !strcmp(en1->ಮೌಲ್ಯ, en2->ಮೌಲ್ಯ));
        av_dict_free(&dict1);
        ಪ್ರತ್ಯಾಗಮ (!en1 && !en2);
    }
    ಪಕ್ಷ AV_OPT_TYPE_IMAGE_SIZE:
        ಯದಿ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ಅನ್ಯಥಾ ಯದಿ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        ಪ್ರತ್ಯಾಗಮ (w == *(ಪೂರ್ಣಾಙ್ಕ *)dst) && (h == *((ಪೂರ್ಣಾಙ್ಕ *)dst+1));
    ಪಕ್ಷ AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        ಯದಿ (o->default_val.str) {
            ಯದಿ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಪ್ರತ್ಯಾಗಮ !av_cmp_q(*(AVRational*)dst, q);
    ಪಕ್ಷ AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ಯದಿ (o->default_val.str) {
            ಯದಿ ((ret = av_parse_color(color, o->default_val.str, -1, ರಿಕ್ತ)) < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಪ್ರತ್ಯಾಗಮ !memcmp(color, dst, ಪರಿಮಾಣ(color));
    }
    ಸ್ವಭಾವ:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ AVERROR_PATCHWELCOME;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_is_set_to_default_by_name(ಶೂನ್ಯ *obj, ಧ್ರುವ ವರ್ಣ *name, ಪೂರ್ಣಾಙ್ಕ ಹುಡುಕು_flags)
{
    ಧ್ರುವ AVOption *o;
    ಶೂನ್ಯ *target;
    ಯದಿ (!obj)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ರಿಕ್ತ, 0, ಹುಡುಕು_flags, &target);
    ಯದಿ (!o)
        ಪ್ರತ್ಯಾಗಮ AVERROR_OPTION_NOT_FOUND;
    ಪ್ರತ್ಯಾಗಮ av_opt_is_set_to_default(target, o);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ opt_serialize(ಶೂನ್ಯ *obj, ಪೂರ್ಣಾಙ್ಕ opt_flags, ಪೂರ್ಣಾಙ್ಕ flags, ಪೂರ್ಣಾಙ್ಕ *cnt,
                         AVBPrint *bprint, ಧ್ರುವ ವರ್ಣ ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ pairs_sep)
{
    ಧ್ರುವ AVOption *o = ರಿಕ್ತ;
    ಶೂನ್ಯ *child = ರಿಕ್ತ;
    uint8_t *buf;
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಧ್ರುವ ವರ್ಣ special_chars[] = {pairs_sep, ಕೀಲಿ_val_sep, '\0'};

    ಯದಿ (flags & AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN)
        ಯಾವತ್ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                ಕೀಲಿ_val_sep, pairs_sep);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }

    ಯಾವತ್ (o = av_opt_next(obj, o)) {
        ಯದಿ (o->type == AV_OPT_TYPE_CONST)
            ಅನುವರ್ತ;
        ಯದಿ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ಯದಿ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ಯದಿ (o->flags == opt_flags)
                    ಅನುವರ್ತ;
            } ಅನ್ಯಥಾ ಯದಿ ((o->flags & opt_flags) == opt_flags)
                ಅನುವರ್ತ;
        } ಅನ್ಯಥಾ {
            ಯದಿ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                ಅನುವರ್ತ;
            ಅನ್ಯಥಾ ಯದಿ (((o->flags & opt_flags) != opt_flags))
                ಅನುವರ್ತ;
        }
        ಯದಿ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            ಅನುವರ್ತ;
        ಯದಿ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ರಿಕ್ತ);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        ಯದಿ (buf) {
            ಯದಿ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &ಕೀಲಿ_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_opt_serialize(ಶೂನ್ಯ *obj, ಪೂರ್ಣಾಙ್ಕ opt_flags, ಪೂರ್ಣಾಙ್ಕ flags, ವರ್ಣ **buffer,
                     ಧ್ರುವ ವರ್ಣ ಕೀಲಿ_val_sep, ಧ್ರುವ ವರ್ಣ pairs_sep)
{
    AVBPrint bprint;
    ಪೂರ್ಣಾಙ್ಕ ret, cnt = 0;

    ಯದಿ (pairs_sep == '\0' || ಕೀಲಿ_val_sep == '\0' || pairs_sep == ಕೀಲಿ_val_sep ||
        pairs_sep == '\\' || ಕೀಲಿ_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    ಯದಿ (!obj || !buffer)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    *buffer = ರಿಕ್ತ;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        ಕೀಲಿ_val_sep, pairs_sep);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಪ್ರತ್ಯಾಗಮ 0;
}
