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

#ವ್ಯಾಖ್ಯಾನಿಸು TYPE_ತಳ(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ಸ್ಥಿರಾಂಕ AVOption *av_opt_ಮುಂದಿನ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *ಕೊನೆಯ)
{
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ಆದರೆ (!obj)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    class = *(ಸ್ಥಿರಾಂಕ AVClass**)obj;
    ಆದರೆ (!ಕೊನೆಯ && class && class->option && class->option[0].name)
        ಹಿಂತಿರುಗಿ class->option;
    ಆದರೆ (ಕೊನೆಯ && ಕೊನೆಯ[1].name)
        ಹಿಂತಿರುಗಿ ++ಕೊನೆಯ;
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    size_t      ಗಾತ್ರ_2;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { ಗಾತ್ರ(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { ಗಾತ್ರ(ಚಿಹ್ನೆರಹಿತ),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { ಗಾತ್ರ(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { ಗಾತ್ರ(ದ್ವಿಗುಣ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { ಗಾತ್ರ(ದಶಮಾಂಶ),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { ಗಾತ್ರ(ಅಕ್ಷರ *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { ಗಾತ್ರ(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ದ್ವಿಮಾನ]        = { ಗಾತ್ರ(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { ಗಾತ್ರ(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_ಗಾತ್ರ]    = { ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_ದರ]    = { ಗಾತ್ರ(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { ಗಾತ್ರ(ಎಣಿಕೆ AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { ಗಾತ್ರ(ಎಣಿಕೆ AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { ಗಾತ್ರ(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { ಗಾತ್ರ(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { ಗಾತ್ರ(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ),            "<boolean>" },
};

// option is plain old data
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_is_pod(ಎಣಿಕೆ AVOptionType type)
{
    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
    ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR:
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
        ಹಿಂತಿರುಗಿ 1;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ uint8_t opt_array_sep(ಸ್ಥಿರಾಂಕ AVOption *o)
{
    ಸ್ಥಿರಾಂಕ AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ಹಿಂತಿರುಗಿ (d && d->sep) ? d->sep : ',';
}

ಸ್ಥಿರ ಶೂನ್ಯ *opt_array_pelem(ಸ್ಥಿರಾಂಕ AVOption *o, ಶೂನ್ಯ *array, ಚಿಹ್ನೆರಹಿತ idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ಹಿಂತಿರುಗಿ (uint8_t *)array + idx * opt_type_desc[TYPE_ತಳ(o->type)].ಗಾತ್ರ_2;
}

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ *opt_array_pcount(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *parray)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ *)((ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ *)parray + 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ opt_free_elem(ಎಣಿಕೆ AVOptionType type, ಶೂನ್ಯ *ptr)
{
    ಆಯ್ಕೆ (TYPE_ತಳ(type)) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
    ಸ್ಥಿತಿ AV_OPT_TYPE_ದ್ವಿಮಾನ:
        av_freep(ptr);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        ನಿಲ್ಲಿಸು;

    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ opt_free_array(ಸ್ಥಿರಾಂಕ AVOption *o, ಶೂನ್ಯ *parray, ಚಿಹ್ನೆರಹಿತ *ಎಣಿಕೆ_2)
{
    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < *ಎಣಿಕೆ_2; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(ಶೂನ್ಯ **)parray, i));

    av_freep(parray);
    *ಎಣಿಕೆ_2 = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_ಗಣ_init(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags,
                        ಪೂರ್ಣಾಂಕ require_type,
                        ಶೂನ್ಯ **ptgt, ಸ್ಥಿರಾಂಕ AVOption **po, ಶೂನ್ಯ **pdst)
{
    ಶೂನ್ಯ *logctx;
    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಶೂನ್ಯ *tgt;

    o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &tgt);
    ಆದರೆ (!o || (!tgt && !(ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_FAKE_OBJ)))
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;

    ಆದರೆ (o->flags & AV_OPT_FLAG_READONLY)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    logctx = tgt ? obj : ಖಾಲಿ;

    ಆದರೆ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        ಚಿಹ್ನೆರಹಿತ *state_flags = ಖಾಲಿ;
        ಸ್ಥಿರಾಂಕ AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ಸ್ಥಿರಾಂಕ AVClass**)tgt;
        ಆದರೆ (class->state_flags_ಸ್ಥಾನಾಂತರ)
            state_flags = (ಚಿಹ್ನೆರಹಿತ*)((uint8_t*)tgt + class->state_flags_ಸ್ಥಾನಾಂತರ);

        ಆದರೆ (!state_flags && obj != tgt) {
            class = *(ಸ್ಥಿರಾಂಕ AVClass**)obj;
            ಆದರೆ (class->state_flags_ಸ್ಥಾನಾಂತರ)
                state_flags = (ಚಿಹ್ನೆರಹಿತ*)((uint8_t*)obj + class->state_flags_ಸ್ಥಾನಾಂತರ);
        }

        ಆದರೆ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಆದರೆ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ಆದರೆ (po)
        *po   = o;
    ಆದರೆ (ptgt)
        *ptgt = tgt;
    ಆದರೆ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->ಸ್ಥಾನಾಂತರ : ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ AVRational double_ಗಮ್ಯ_rational(ದ್ವಿಗುಣ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ಆದರೆ ((!r.ಅಂಕೆ || !r.den) && d)
         r = av_d2q(d, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
     ಹಿಂತಿರುಗಿ r;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ read_ಸಂಖ್ಯೆ(ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *dst, ದ್ವಿಗುಣ *ಅಂಕೆ, ಪೂರ್ಣಾಂಕ *den, int64_t *intnum)
{
    ಆಯ್ಕೆ (TYPE_ತಳ(o->type)) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
        *intnum = *(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ*)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ಎಣಿಕೆ AVPixelFormat *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ಎಣಿಕೆ AVSampleFormat *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
        *intnum = *(ಪೂರ್ಣಾಂಕ *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
        *intnum = *(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
        *ಅಂಕೆ = *(ದಶಮಾಂಶ *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
        *ಅಂಕೆ = *(ದ್ವಿಗುಣ *)dst;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->ಅಂಕೆ;
        *den    = ((AVRational *)dst)->den;
        ಹಿಂತಿರುಗಿ 0;
    ಸ್ಥಿತಿ AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ಹಿಂತಿರುಗಿ 0;
    }
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ write_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಶೂನ್ಯ *dst,
                        ದ್ವಿಗುಣ ಅಂಕೆ, ಪೂರ್ಣಾಂಕ den, int64_t intnum,
                        ಪೂರ್ಣಾಂಕ ignore_range)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVOptionType type = TYPE_ತಳ(o->type);

    ಆದರೆ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < ಅಂಕೆ * intnum || o->min * den > ಅಂಕೆ * intnum)) {
        ಅಂಕೆ = den ? ಅಂಕೆ * intnum / den : (ಅಂಕೆ && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               ಅಂಕೆ, o->name, o->min, o->max);
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    }
    ಆದರೆ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        ದ್ವಿಗುಣ d = ಅಂಕೆ*intnum/den;
        ಆದರೆ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   ಅಂಕೆ*intnum/den, o->name);
            ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
        }
    }

    ಆದರೆ (!dst)
        ಹಿಂತಿರುಗಿ 0;

    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
        *(ಎಣಿಕೆ AVPixelFormat *)dst = llrint(ಅಂಕೆ / den) * intnum;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
        *(ಎಣಿಕೆ AVSampleFormat *)dst = llrint(ಅಂಕೆ / den) * intnum;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
        *(ಪೂರ್ಣಾಂಕ *)dst = llrint(ಅಂಕೆ / den) * intnum;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:{
        ದ್ವಿಗುಣ d = ಅಂಕೆ / den;
        ಆದರೆ (intnum == 1 && d == (ದ್ವಿಗುಣ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ಇಲ್ಲದಿದ್ದರೆ
            *(int64_t *)dst = llrint(d) * intnum;
        ನಿಲ್ಲಿಸು;}
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:{
        ದ್ವಿಗುಣ d = ಅಂಕೆ / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ಆದರೆ (intnum == 1 && d == (ದ್ವಿಗುಣ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        ನಿಲ್ಲಿಸು;}
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
        *(ದಶಮಾಂಶ *)dst = ಅಂಕೆ * intnum / den;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
        *(ದ್ವಿಗುಣ    *)dst = ಅಂಕೆ * intnum / den;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
        ಆದರೆ ((ಪೂರ್ಣಾಂಕ) ಅಂಕೆ == ಅಂಕೆ)
            *(AVRational *)dst = (AVRational) { ಅಂಕೆ *intnum, den };
        ಇಲ್ಲದಿದ್ದರೆ
            *(AVRational *)dst = double_ಗಮ್ಯ_rational(ಅಂಕೆ * intnum / den);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ hexchar2int(ಅಕ್ಷರ c) {
    ಆದರೆ (c >= '0' && c <= '9')
        ಹಿಂತಿರುಗಿ c - '0';
    ಆದರೆ (c >= 'a' && c <= 'f')
        ಹಿಂತಿರುಗಿ c - 'a' + 10;
    ಆದರೆ (c >= 'A' && c <= 'F')
        ಹಿಂತಿರುಗಿ c - 'A' + 10;
    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_ದ್ವಿಮಾನ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t **dst)
{
    ಪೂರ್ಣಾಂಕ *lendst;
    uint8_t *bin, *ptr;
    ಪೂರ್ಣಾಂಕ len;

    ಆದರೆ (dst) {
        lendst = (ಪೂರ್ಣಾಂಕ *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ಆದರೆ (!val || !(len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(val)))
        ಹಿಂತಿರುಗಿ 0;

    ಆದರೆ (len & 1)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ಆದರೆ (!ptr)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಆಗ (*val) {
        ಪೂರ್ಣಾಂಕ a = hexchar2int(*val++);
        ಪೂರ್ಣಾಂಕ b = hexchar2int(*val++);
        ಆದರೆ (a < 0 || b < 0) {
            av_free(bin);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ಆದರೆ (dst) {
        *dst    = bin;
        *lendst = len;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_free(bin);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t **dst)
{
    ಆದರೆ (!dst)
        ಹಿಂತಿರುಗಿ 0;
    av_freep(dst);
    ಆದರೆ (!val)
        ಹಿಂತಿರುಗಿ 0;
    *dst = av_strdup(val);
    ಹಿಂತಿರುಗಿ *dst ? 0 : AVERROR(ENOMEM);
}

#ವ್ಯಾಖ್ಯಾನಿಸು DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *ಗುರಿ_obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಶೂನ್ಯ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVOptionType type = TYPE_ತಳ(o->type);
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_ದರ) {
        ಪೂರ್ಣಾಂಕ ಅಂಕೆ, den;
        ಅಕ್ಷರ c;
        ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಓದು(val, "%d%*1[:/]%d%c", &ಅಂಕೆ, &den, &c) == 2) {
            ಆದರೆ ((ret = write_ಸಂಖ್ಯೆ(obj, o, dst, 1, den, ಅಂಕೆ, 0)) >= 0)
                ಹಿಂತಿರುಗಿ ret;
            ret = 0;
        }
    }

    ಗಾಗಿ (;;) {
        ಪೂರ್ಣಾಂಕ i = 0;
        ಅಕ್ಷರ buf[256];
        ಪೂರ್ಣಾಂಕ cmd = 0;
        ದ್ವಿಗುಣ d;
        int64_t intnum = 1;

        ಆದರೆ (type == AV_OPT_TYPE_FLAGS) {
            ಆದರೆ (*val == '+' || *val == '-')
                cmd = *(val++);
            ಗಾಗಿ (; i < ಗಾತ್ರ(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            ಪೂರ್ಣಾಂಕ res;
            ಪೂರ್ಣಾಂಕ ci = 0;
            ದ್ವಿಗುಣ const_ಮೌಲ್ಯಗಳು[64];
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * const_ಹೆಸರುಗಳು[64];
            ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags = (o->flags & AV_OPT_FLAG_ಮಗು_CONSTS) ? AV_OPT_ಹುಡುಕು_CHILDREN : 0;
            ಸ್ಥಿರಾಂಕ AVOption *o_named = av_opt_ಕಂಡುಹಿಡಿ(ಗುರಿ_obj, i ? buf : val, o->unit, 0, ಹುಡುಕು_flags);
            ಆದರೆ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ಆದರೆ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (o->unit) {
                    ಗಾಗಿ (o_named = ಖಾಲಿ; o_named = av_opt_ಮುಂದಿನ(ಗುರಿ_obj, o_named); ) {
                        ಆದರೆ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ಆದರೆ (ci + 6 >= FF_ARRAY_ELEMS(const_ಮೌಲ್ಯಗಳು)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ಹಿಂತಿರುಗಿ AVERROR_PATCHWELCOME;
                            }
                            const_ಹೆಸರುಗಳು [ci  ] = o_named->name;
                            const_ಮೌಲ್ಯಗಳು[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_ಹೆಸರುಗಳು [ci  ] = "default";
                const_ಮೌಲ್ಯಗಳು[ci++] = DEFAULT_NUMVAL(o);
                const_ಹೆಸರುಗಳು [ci  ] = "max";
                const_ಮೌಲ್ಯಗಳು[ci++] = o->max;
                const_ಹೆಸರುಗಳು [ci  ] = "min";
                const_ಮೌಲ್ಯಗಳು[ci++] = o->min;
                const_ಹೆಸರುಗಳು [ci  ] = "none";
                const_ಮೌಲ್ಯಗಳು[ci++] = 0;
                const_ಹೆಸರುಗಳು [ci  ] = "all";
                const_ಮೌಲ್ಯಗಳು[ci++] = ~0;
                const_ಹೆಸರುಗಳು [ci] = ಖಾಲಿ;
                const_ಮೌಲ್ಯಗಳು[ci] = 0;

                res = av_ಅಭಿವ್ಯಕ್ತಿ_parse_and_eval(&d, i ? buf : val, const_ಹೆಸರುಗಳು,
                                            const_ಮೌಲ್ಯಗಳು, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, 0, obj);
                ಆದರೆ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ಹಿಂತಿರುಗಿ res;
                }
            }
        }
        ಆದರೆ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ*)dst;
            ಆದರೆ (cmd == '+')
                d = intnum | (int64_t)d;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ಆದರೆ ((ret = write_ಸಂಖ್ಯೆ(obj, o, dst, d, 1, 1, 0)) < 0)
            ಹಿಂತಿರುಗಿ ret;
        val += i;
        ಆದರೆ (!i || !*val)
            ಹಿಂತಿರುಗಿ 0;
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_image_ಗಾತ್ರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಪೂರ್ಣಾಂಕ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ tmp[2];
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!val || !strcmp(val, "none")) {
        ಆದರೆ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ಹಿಂತಿರುಗಿ 0;
    }
    ret = av_parse_video_ಗಾತ್ರ(&tmp[0], &tmp[1], val);
    ಆದರೆ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ಹಿಂತಿರುಗಿ ret;
    }
    ಆದರೆ (dst)
        ಸ್ಮರಣೆ_ನಕಲು(dst, tmp, ಗಾತ್ರ(tmp));
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_video_ದರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, AVRational *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    AVRational tmp;
    ಪೂರ್ಣಾಂಕ ret = av_parse_video_ದರ(&tmp, val);
    ಆದರೆ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ಆದರೆ (dst)
        *dst = tmp;
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_color(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!val) {
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ಆದರೆ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ಹಿಂತಿರುಗಿ ret;
        }
        ಆದರೆ (dst)
            ಸ್ಮರಣೆ_ನಕಲು(dst, tmp, ಗಾತ್ರ(tmp));
        ಹಿಂತಿರುಗಿ ret;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *get_bool_name(ಪೂರ್ಣಾಂಕ val)
{
    ಆದರೆ (val < 0)
        ಹಿಂತಿರುಗಿ "auto";
    ಹಿಂತಿರುಗಿ val ? "true" : "false";
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_bool(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಪೂರ್ಣಾಂಕ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ n;

    ಆದರೆ (!val)
        ಹಿಂತಿರುಗಿ 0;

    ಆದರೆ (!strcmp(val, "auto")) {
        n = -1;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (av_ಹೊಂದಿಕೆ_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (av_ಹೊಂದಿಕೆ_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಅಕ್ಷರ *ಕೊನೆ = ಖಾಲಿ;
        n = strtol(val, &ಕೊನೆ, 10);
        ಆದರೆ (val + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(val) != ಕೊನೆ)
            ಹೋಗು fail;
    }

    ಆದರೆ (n < o->min || n > o->max)
        ಹೋಗು fail;

    ಆದರೆ (dst)
    *dst = n;
    ಹಿಂತಿರುಗಿ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t *dst,
                          ಪೂರ್ಣಾಂಕ fmt_nb, ಪೂರ್ಣಾಂಕ ((*get_fmt)(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)), ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desc,
                          ಎಣಿಕೆ AVOptionType type)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ fmt, min, max;

    ಆದರೆ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ಇಲ್ಲದಿದ್ದರೆ {
        fmt = get_fmt(val);
        ಆದರೆ (fmt == -1) {
            ಅಕ್ಷರ *ಬಾಲ;
            fmt = strtol(val, &ಬಾಲ, 0);
            ಆದರೆ (*ಬಾಲ || (ಚಿಹ್ನೆರಹಿತ)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ಆದರೆ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ಆದರೆ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    }

    ಆದರೆ (dst)
    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:  *(ಎಣಿಕೆ AVPixelFormat *)dst = fmt; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT: *(ಎಣಿಕೆ AVSampleFormat*)dst = fmt; ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_pix_fmt(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಹಿಂತಿರುಗಿ av_get_pix_fmt(name);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_pixel_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t *dst)
{
    ಹಿಂತಿರುಗಿ ಗಣ_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_sample_fmt(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಹಿಂತಿರುಗಿ av_get_sample_fmt(name);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_sample_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t *dst)
{
    ಹಿಂತಿರುಗಿ ಗಣ_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_dict(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, uint8_t **dst)
{
    AVDictionary *options = ಖಾಲಿ;

    ಆದರೆ (val) {
        ಪೂರ್ಣಾಂಕ ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ಆದರೆ (ret < 0) {
            av_dict_free(&options);
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    ಆದರೆ (!dst) {
        av_dict_free(&options);
        ಹಿಂತಿರುಗಿ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_string_channel_layout(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o,
                                     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಶೂನ್ಯ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    ಪೂರ್ಣಾಂಕ ret;
    ಆದರೆ (dst)
    av_channel_layout_uninit(channel_layout);
    ಇಲ್ಲದಿದ್ದರೆ
        channel_layout = &tmp;
    ಆದರೆ (!val)
        ಹಿಂತಿರುಗಿ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ (!dst)
        av_channel_layout_uninit(channel_layout);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_ಗಣ_elem(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *ಗುರಿ_obj, ಸ್ಥಿರಾಂಕ AVOption *o,
                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಶೂನ್ಯ *dst)
{
    ಶೂನ್ಯ *logctx = dst ? obj : ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVOptionType type = TYPE_ತಳ(o->type);
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_ಗಾತ್ರ &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
        ಹಿಂತಿರುಗಿ ಗಣ_string_bool(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
        ಹಿಂತಿರುಗಿ ಗಣ_string(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_ದ್ವಿಮಾನ:
        ಹಿಂತಿರುಗಿ ಗಣ_string_ದ್ವಿಮಾನ(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
        ಹಿಂತಿರುಗಿ ಗಣ_string_ಸಂಖ್ಯೆ(obj, ಗುರಿ_obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
        ಹಿಂತಿರುಗಿ ಗಣ_string_image_ಗಾತ್ರ(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ: {
        AVRational tmp;
        ret = ಗಣ_string_video_ದರ(obj, o, val, &tmp);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
        ಹಿಂತಿರುಗಿ write_ಸಂಖ್ಯೆ(obj, o, dst, 1, tmp.den, tmp.ಅಂಕೆ, 0);
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
        ಹಿಂತಿರುಗಿ ಗಣ_string_pixel_fmt(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
        ಹಿಂತಿರುಗಿ ಗಣ_string_sample_fmt(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ಆದರೆ (val) {
                ಆದರೆ ((ret = av_parse_ಸಮಯ(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ಹಿಂತಿರುಗಿ ret;
                }
            }
            ಆದರೆ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
            }
            ಆದರೆ (dst)
            *(int64_t *)dst = usecs;
            ಹಿಂತಿರುಗಿ 0;
        }
    ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR:
        ಹಿಂತಿರುಗಿ ಗಣ_string_color(obj, o, val, dst);
    ಸ್ಥಿತಿ AV_OPT_TYPE_CHLAYOUT:
        ret = ಗಣ_string_channel_layout(obj, o, val, dst);
        ಆದರೆ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ಹಿಂತಿರುಗಿ ret;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DICT:
        ಹಿಂತಿರುಗಿ ಗಣ_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_ಗಣ_array(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *ಗುರಿ_obj, ಸ್ಥಿರಾಂಕ AVOption *o,
                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಶೂನ್ಯ *dst)
{
    ಸ್ಥಿರಾಂಕ AVOptionArrayDef *arr = o->default_val.arr;
    ಸ್ಥಿರಾಂಕ size_t      elem_ಗಾತ್ರ = opt_type_desc[TYPE_ತಳ(o->type)].ಗಾತ್ರ_2;
    ಸ್ಥಿರಾಂಕ uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ಖಾಲಿ;

    ಶೂನ್ಯ      *logctx = dst ? obj : ಖಾಲಿ;
    ಶೂನ್ಯ       *elems = ಖಾಲಿ;
    ಚಿಹ್ನೆರಹಿತ nb_elems = 0;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (val && *val) {
        str = av_malloc(ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(val) + 1);
        ಆದರೆ (!str)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ಆಗ (val && *val) {
        uint8_t *p = str;
        ಶೂನ್ಯ *tmp;

        ಆದರೆ (arr && arr->ಗಾತ್ರ_max && nb_elems >= arr->ಗಾತ್ರ_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->ಗಾತ್ರ_max, o->name);
            ret = AVERROR(EINVAL);
            ಹೋಗು fail;
        }

        ಗಾಗಿ (; *val; val++, p++) {
            ಆದರೆ (*val == '\\' && val[1])
                val++;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*val == sep) {
                val++;
                ನಿಲ್ಲಿಸು;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_ಗಾತ್ರ);
        ಆದರೆ (!tmp) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_ಗಾತ್ರ);

        ret = opt_ಗಣ_elem(obj, ಗುರಿ_obj, o, str, tmp);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
        nb_elems++;
    }
    av_freep(&str);

    ಆದರೆ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ಆದರೆ (arr && nb_elems < arr->ಗಾತ್ರ_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->ಗಾತ್ರ_min, o->name);
        ret = AVERROR(EINVAL);
        ಹೋಗು fail;
    }

    ಆದರೆ (dst) {
    *((ಶೂನ್ಯ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ಇಲ್ಲದಿದ್ದರೆ
        opt_free_array(o, &elems, &nb_elems);

    ಹಿಂತಿರುಗಿ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಶೂನ್ಯ *dst, *ಗುರಿ_obj;
    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಪೂರ್ಣಾಂಕ ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, 0, &ಗುರಿ_obj, &o, &dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಹಿಂತಿರುಗಿ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_ಗಣ_array : opt_ಗಣ_elem)(obj, ಗುರಿ_obj, o, val, dst);
}

#ವ್ಯಾಖ್ಯಾನಿಸು OPT_EVAL_ಸಂಖ್ಯೆ(name, opttype, vartype)                         \
ಪೂರ್ಣಾಂಕ av_opt_eval_ ## name(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o,                  \
                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *val, vartype *name ## ಹೊರಹೋಗು_3)        \
{                                                                       \
    ಆದರೆ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);                                         \
    ಹಿಂತಿರುಗಿ ಗಣ_string_ಸಂಖ್ಯೆ(obj, obj, o, val, name ## ಹೊರಹೋಗು_3);           \
}

OPT_EVAL_ಸಂಖ್ಯೆ(flags,  AV_OPT_TYPE_FLAGS,    ಪೂರ್ಣಾಂಕ)
OPT_EVAL_ಸಂಖ್ಯೆ(ಪೂರ್ಣಾಂಕ,    AV_OPT_TYPE_INT,      ಪೂರ್ಣಾಂಕ)
OPT_EVAL_ಸಂಖ್ಯೆ(uint,   AV_OPT_TYPE_UINT,     ಚಿಹ್ನೆರಹಿತ)
OPT_EVAL_ಸಂಖ್ಯೆ(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_ಸಂಖ್ಯೆ(ದಶಮಾಂಶ,  AV_OPT_TYPE_FLOAT,    ದಶಮಾಂಶ)
OPT_EVAL_ಸಂಖ್ಯೆ(ದ್ವಿಗುಣ, AV_OPT_TYPE_DOUBLE,   ದ್ವಿಗುಣ)
OPT_EVAL_ಸಂಖ್ಯೆ(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ದ್ವಿಗುಣ ಅಂಕೆ, ಪೂರ್ಣಾಂಕ den, int64_t intnum,
                      ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ಪೂರ್ಣಾಂಕ require_type)
{
    ಶೂನ್ಯ *dst;
    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಪೂರ್ಣಾಂಕ ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, require_type, ಖಾಲಿ, &o, &dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ (dst)
        ret = write_ಸಂಖ್ಯೆ(obj, o, dst, ಅಂಕೆ, den, intnum, 0);

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_int(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, int64_t val, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ ಗಣ_ಸಂಖ್ಯೆ(obj, name, 1, 1, val, ಹುಡುಕು_flags, 0);
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_double(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ದ್ವಿಗುಣ val, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ ಗಣ_ಸಂಖ್ಯೆ(obj, name, val, 1, 1, ಹುಡುಕು_flags, 0);
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_q(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, AVRational val, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ ಗಣ_ಸಂಖ್ಯೆ(obj, name, val.ಅಂಕೆ, val.den, 1, ಹುಡುಕು_flags, 0);
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_bin(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ uint8_t *val, ಪೂರ್ಣಾಂಕ len, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    ಪೂರ್ಣಾಂಕ *lendst;
    ಪೂರ್ಣಾಂಕ ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_ದ್ವಿಮಾನ,
                       ಖಾಲಿ, ಖಾಲಿ, (ಶೂನ್ಯ**)&dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (dst) {
    ptr = len ? av_malloc(len) : ಖಾಲಿ;
    ಆದರೆ (len && !ptr)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    lendst = (ಪೂರ್ಣಾಂಕ *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ಆದರೆ (len)
        ಸ್ಮರಣೆ_ನಕಲು(ptr, val, len);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_image_ಗಾತ್ರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಶೂನ್ಯ *logctx;
    ಪೂರ್ಣಾಂಕ *dst;
    ಪೂರ್ಣಾಂಕ ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_IMAGE_ಗಾತ್ರ,
                       ಖಾಲಿ, &o, (ಶೂನ್ಯ**)&dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    logctx = dst ? obj : ಖಾಲಿ;

    ಆದರೆ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_video_ದರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, AVRational val, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ ಗಣ_ಸಂಖ್ಯೆ(obj, name, val.ಅಂಕೆ, val.den, 1, ಹುಡುಕು_flags, AV_OPT_TYPE_VIDEO_ದರ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಣ_format(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ fmt, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags,
                      ಎಣಿಕೆ AVOptionType type, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desc, ಪೂರ್ಣಾಂಕ nb_fmts)
{
    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಶೂನ್ಯ *logctx;
    ಪೂರ್ಣಾಂಕ *dst;
    ಪೂರ್ಣಾಂಕ min, max, ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, type, ಖಾಲಿ, &o, (ಶೂನ್ಯ**)&dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    logctx = dst ? obj : ಖಾಲಿ;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ಆದರೆ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
    }
    ಆದರೆ (dst)
    *dst = fmt;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_pixel_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಎಣಿಕೆ AVPixelFormat fmt, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ ಗಣ_format(obj, name, fmt, ಹುಡುಕು_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_sample_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಎಣಿಕೆ AVSampleFormat fmt, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ ಗಣ_format(obj, name, fmt, ಹುಡುಕು_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_dict_val(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ AVDictionary *val,
                        ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    AVDictionary **dst;
    ಪೂರ್ಣಾಂಕ ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_DICT, ಖಾಲಿ, ಖಾಲಿ,
                       (ಶೂನ್ಯ**)&dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_chlayout(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name,
                        ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                        ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    AVChannelLayout *dst;
    ಪೂರ್ಣಾಂಕ ret;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, AV_OPT_TYPE_CHLAYOUT, ಖಾಲಿ, ಖಾಲಿ,
                       (ಶೂನ್ಯ**)&dst);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ format_duration(ಅಕ್ಷರ *buf, size_t ಗಾತ್ರ_2, int64_t d)
{
    ಅಕ್ಷರ *e;

    av_assert0(ಗಾತ್ರ_2 >= 25);
    ಆದರೆ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        ಗಾತ್ರ_2--;
        d = -d;
    }
    ಆದರೆ (d == INT64_MAX)
        snprintf(buf, ಗಾತ್ರ_2, "INT64_MAX");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == INT64_MIN)
        snprintf(buf, ಗಾತ್ರ_2, "INT64_MIN");
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d > (int64_t)3600*1000000)
        snprintf(buf, ಗಾತ್ರ_2, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (ಪೂರ್ಣಾಂಕ)((d / 60000000) % 60),
                 (ಪೂರ್ಣಾಂಕ)((d / 1000000) % 60),
                 (ಪೂರ್ಣಾಂಕ)(d % 1000000));
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d > 60*1000000)
        snprintf(buf, ಗಾತ್ರ_2, "%d:%02d.%06d",
                 (ಪೂರ್ಣಾಂಕ)(d / 60000000),
                 (ಪೂರ್ಣಾಂಕ)((d / 1000000) % 60),
                 (ಪೂರ್ಣಾಂಕ)(d % 1000000));
    ಇಲ್ಲದಿದ್ದರೆ
        snprintf(buf, ಗಾತ್ರ_2, "%d.%06d",
                 (ಪೂರ್ಣಾಂಕ)(d / 1000000),
                 (ಪೂರ್ಣಾಂಕ)(d % 1000000));
    e = buf + ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(buf);
    ಆಗ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ಆದರೆ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_get_elem(ಸ್ಥಿರಾಂಕ AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *dst, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಪೂರ್ಣಾಂಕ ret;

    ಆಯ್ಕೆ (TYPE_ತಳ(o->type)) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(ಪೂರ್ಣಾಂಕ *)dst));
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(ಪೂರ್ಣಾಂಕ *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(ಪೂರ್ಣಾಂಕ *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(ಚಿಹ್ನೆರಹಿತ *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(ದಶಮಾಂಶ *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(ದ್ವಿಗುಣ *)dst);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->ಅಂಕೆ, ((AVRational *)dst)->den);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
        ಆದರೆ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ಖಾಲಿ;
            ಹಿಂತಿರುಗಿ 0;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *pbuf = av_strdup("");
        }
        ಹಿಂತಿರುಗಿ *pbuf ? 0 : AVERROR(ENOMEM);
    ಸ್ಥಿತಿ AV_OPT_TYPE_ದ್ವಿಮಾನ: {
        ಸ್ಥಿರಾಂಕ uint8_t *bin;
        ಪೂರ್ಣಾಂಕ len;

        ಆದರೆ (!*(uint8_t **)dst && (ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ಖಾಲಿ;
            ಹಿಂತಿರುಗಿ 0;
        }
        len = *(ಪೂರ್ಣಾಂಕ *)(((uint8_t *)dst) + ಗಾತ್ರ(uint8_t *));
        ಆದರೆ ((uint64_t)len * 2 + 1 > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        ಆದರೆ (!(*pbuf = av_malloc(len * 2 + 1)))
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        ಆದರೆ (!len) {
            *pbuf[0] = '\0';
            ಹಿಂತಿರುಗಿ 0;
        }
        bin = *(uint8_t **)dst;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ಹಿಂತಿರುಗಿ 0;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((ಪೂರ್ಣಾಂಕ *)dst)[0], ((ಪೂರ್ಣಾಂಕ *)dst)[1]);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ಅಕ್ಷರ *)av_x_if_null(av_get_pix_fmt_name(*(ಎಣಿಕೆ AVPixelFormat *)dst), "none"));
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ಅಕ್ಷರ *)av_x_if_null(av_get_sample_fmt_name(*(ಎಣಿಕೆ AVSampleFormat *)dst), "none"));
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(*pbuf); // no overflow possible, checked by an assert
        ನಿಲ್ಲಿಸು;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (ಪೂರ್ಣಾಂಕ)((uint8_t *)dst)[0], (ಪೂರ್ಣಾಂಕ)((uint8_t *)dst)[1],
                       (ಪೂರ್ಣಾಂಕ)((uint8_t *)dst)[2], (ಪೂರ್ಣಾಂಕ)((uint8_t *)dst)[3]);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_DICT:
        ಆದರೆ (!*(AVDictionary **)dst && (ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ಖಾಲಿ;
            ಹಿಂತಿರುಗಿ 0;
        }
        ಹಿಂತಿರುಗಿ av_dict_get_string(*(AVDictionary **)dst, (ಅಕ್ಷರ **)pbuf, '=', ':');
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_get_array(ಸ್ಥಿರಾಂಕ AVOption *o, ಶೂನ್ಯ *dst, uint8_t **ಹೊರಹೋಗು_val)
{
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಎಣಿಕೆ_2 = *opt_array_pcount(dst);
    ಸ್ಥಿರಾಂಕ uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ಖಾಲಿ;
    size_t   str_len = 0;
    ಪೂರ್ಣಾಂಕ ret;

    *ಹೊರಹೋಗು_val = ಖಾಲಿ;

    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < ಎಣಿಕೆ_2; i++) {
        uint8_t buf[128], *ಹೊರಹೋಗು = buf;
        size_t ಹೊರಹೋಗು_len;

        ret = opt_get_elem(o, &ಹೊರಹೋಗು, ಗಾತ್ರ(buf),
                           opt_array_pelem(o, *(ಶೂನ್ಯ **)dst, i), 0);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;

        ಹೊರಹೋಗು_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಹೊರಹೋಗು);
        ಆದರೆ (ಹೊರಹೋಗು_len > SIZE_MAX / 2 - !!i ||
            !!i + ಹೊರಹೋಗು_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            ಹೋಗು fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + ಹೊರಹೋಗು_len * 2 + !!i);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;

        // add separator if needed
        ಆದರೆ (i)
            str[str_len++] = sep;

        // escape the element
        ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ j = 0; j < ಹೊರಹೋಗು_len; j++) {
            uint8_t val = ಹೊರಹೋಗು[j];
            ಆದರೆ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ಆದರೆ (ಹೊರಹೋಗು != buf)
            av_freep(&ಹೊರಹೋಗು);
        ಆದರೆ (ret < 0) {
            av_freep(&str);
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    *ಹೊರಹೋಗು_val = str;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, uint8_t **ಹೊರಹೋಗು_val)
{
    ಶೂನ್ಯ *dst, *ಗುರಿ_obj;
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    uint8_t *ಹೊರಹೋಗು, buf[128];
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!o || !ಗುರಿ_obj || (o->ಸ್ಥಾನಾಂತರ<=0 && o->type != AV_OPT_TYPE_CONST))
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;

    ಆದರೆ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)ಗುರಿ_obj + o->ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, ಹೊರಹೋಗು_val);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
        ಆದರೆ (!*ಹೊರಹೋಗು_val && !(ಹುಡುಕು_flags & AV_OPT_ALLOW_NULL)) {
            *ಹೊರಹೋಗು_val = av_strdup("");
            ಆದರೆ (!*ಹೊರಹೋಗು_val)
               ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ಹಿಂತಿರುಗಿ 0;
    }

    buf[0] = 0;
    ಹೊರಹೋಗು = buf;
    ret = opt_get_elem(o, &ಹೊರಹೋಗು, ಗಾತ್ರ(buf), dst, ಹುಡುಕು_flags);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ (ಹೊರಹೋಗು != buf) {
        *ಹೊರಹೋಗು_val = ಹೊರಹೋಗು;
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (ret >= ಗಾತ್ರ(buf))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    *ಹೊರಹೋಗು_val = av_strdup(ಹೊರಹೋಗು);
    ಹಿಂತಿರುಗಿ *ಹೊರಹೋಗು_val ? 0 : AVERROR(ENOMEM);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_ಸಂಖ್ಯೆ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ದ್ವಿಗುಣ *ಅಂಕೆ, ಪೂರ್ಣಾಂಕ *den, int64_t *intnum,
                      ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಶೂನ್ಯ *dst, *ಗುರಿ_obj;
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    dst = ((uint8_t *)ಗುರಿ_obj) + o->ಸ್ಥಾನಾಂತರ;

    ಹಿಂತಿರುಗಿ read_ಸಂಖ್ಯೆ(o, dst, ಅಂಕೆ, den, intnum);
}

ಪೂರ್ಣಾಂಕ av_opt_get_int(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, int64_t *ಹೊರಹೋಗು_val)
{
    int64_t intnum = 1;
    ದ್ವಿಗುಣ ಅಂಕೆ = 1;
    ಪೂರ್ಣಾಂಕ ret, den = 1;

    ಆದರೆ ((ret = get_ಸಂಖ್ಯೆ(obj, name, &ಅಂಕೆ, &den, &intnum, ಹುಡುಕು_flags)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆದರೆ (ಅಂಕೆ == den)
        *ಹೊರಹೋಗು_val = intnum;
    ಇಲ್ಲದಿದ್ದರೆ
        *ಹೊರಹೋಗು_val = ಅಂಕೆ * intnum / den;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_double(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ದ್ವಿಗುಣ *ಹೊರಹೋಗು_val)
{
    int64_t intnum = 1;
    ದ್ವಿಗುಣ ಅಂಕೆ = 1;
    ಪೂರ್ಣಾಂಕ ret, den = 1;

    ಆದರೆ ((ret = get_ಸಂಖ್ಯೆ(obj, name, &ಅಂಕೆ, &den, &intnum, ಹುಡುಕು_flags)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    *ಹೊರಹೋಗು_val = ಅಂಕೆ * intnum / den;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_q(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, AVRational *ಹೊರಹೋಗು_val)
{
    int64_t intnum = 1;
    ದ್ವಿಗುಣ ಅಂಕೆ = 1;
    ಪೂರ್ಣಾಂಕ ret, den = 1;

    ಆದರೆ ((ret = get_ಸಂಖ್ಯೆ(obj, name, &ಅಂಕೆ, &den, &intnum, ಹುಡುಕು_flags)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (ಅಂಕೆ == 1.0 && (ಪೂರ್ಣಾಂಕ)intnum == intnum)
        *ಹೊರಹೋಗು_val = (AVRational){intnum, den};
    ಇಲ್ಲದಿದ್ದರೆ
        *ಹೊರಹೋಗು_val = double_ಗಮ್ಯ_rational(ಅಂಕೆ*intnum/den);
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_image_ಗಾತ್ರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ಪೂರ್ಣಾಂಕ *w_ಹೊರಹೋಗು, ಪೂರ್ಣಾಂಕ *h_ಹೊರಹೋಗು)
{
    ಶೂನ್ಯ *dst, *ಗುರಿ_obj;
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (o->type != AV_OPT_TYPE_IMAGE_ಗಾತ್ರ) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ಗುರಿ_obj) + o->ಸ್ಥಾನಾಂತರ;
    ಆದರೆ (w_ಹೊರಹೋಗು) *w_ಹೊರಹೋಗು = *(ಪೂರ್ಣಾಂಕ *)dst;
    ಆದರೆ (h_ಹೊರಹೋಗು) *h_ಹೊರಹೋಗು = *((ಪೂರ್ಣಾಂಕ *)dst+1);
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_video_ದರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, AVRational *ಹೊರಹೋಗು_val)
{
    ಹಿಂತಿರುಗಿ av_opt_get_q(obj, name, ಹುಡುಕು_flags, ಹೊರಹೋಗು_val);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_format(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ಶೂನ್ಯ *ಹೊರಹೋಗು_fmt,
                      ಎಣಿಕೆ AVOptionType type, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *desc)
{
    ಶೂನ್ಯ *dst, *ಗುರಿ_obj;
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ಗುರಿ_obj) + o->ಸ್ಥಾನಾಂತರ;
    ಆದರೆ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ಎಣಿಕೆ AVPixelFormat *)ಹೊರಹೋಗು_fmt = *(ಎಣಿಕೆ AVPixelFormat *)dst;
    ಇಲ್ಲದಿದ್ದರೆ
        *(ಎಣಿಕೆ AVSampleFormat*)ಹೊರಹೋಗು_fmt = *(ಎಣಿಕೆ AVSampleFormat*)dst;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_pixel_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ಎಣಿಕೆ AVPixelFormat *ಹೊರಹೋಗು_fmt)
{
    ಹಿಂತಿರುಗಿ get_format(obj, name, ಹುಡುಕು_flags, ಹೊರಹೋಗು_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

ಪೂರ್ಣಾಂಕ av_opt_get_sample_fmt(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ಎಣಿಕೆ AVSampleFormat *ಹೊರಹೋಗು_fmt)
{
    ಹಿಂತಿರುಗಿ get_format(obj, name, ಹುಡುಕು_flags, ಹೊರಹೋಗು_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

ಪೂರ್ಣಾಂಕ av_opt_get_chlayout(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, AVChannelLayout *cl)
{
    ಶೂನ್ಯ *dst, *ಗುರಿ_obj;
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ಗುರಿ_obj) + o->ಸ್ಥಾನಾಂತರ;
    ಹಿಂತಿರುಗಿ av_channel_layout_copy(cl, dst);
}

ಪೂರ್ಣಾಂಕ av_opt_get_dict_val(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, AVDictionary **ಹೊರಹೋಗು_val)
{
    ಶೂನ್ಯ *ಗುರಿ_obj;
    AVDictionary *src;
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);

    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (o->type != AV_OPT_TYPE_DICT)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)ಗುರಿ_obj) + o->ಸ್ಥಾನಾಂತರ);

    ಹಿಂತಿರುಗಿ av_dict_copy(ಹೊರಹೋಗು_val, src, 0);
}

ಪೂರ್ಣಾಂಕ av_opt_flag_is_ಗಣ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕ್ಷೇತ್ರ_name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *flag_name)
{
    ಸ್ಥಿರಾಂಕ AVOption *ಕ್ಷೇತ್ರ = av_opt_ಕಂಡುಹಿಡಿ(obj, ಕ್ಷೇತ್ರ_name, ಖಾಲಿ, 0, 0);
    ಸ್ಥಿರಾಂಕ AVOption *flag  = av_opt_ಕಂಡುಹಿಡಿ(obj, flag_name,
                                        ಕ್ಷೇತ್ರ ? ಕ್ಷೇತ್ರ->unit : ಖಾಲಿ, 0, 0);
    int64_t res;

    ಆದರೆ (!ಕ್ಷೇತ್ರ || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, ಕ್ಷೇತ್ರ_name, 0, &res) < 0)
        ಹಿಂತಿರುಗಿ 0;
    ಹಿಂತಿರುಗಿ res & flag->default_val.i64;
}

ಸ್ಥಿರ ಶೂನ್ಯ log_int_ಮೌಲ್ಯ(ಶೂನ್ಯ *av_log_obj, ಪೂರ್ಣಾಂಕ level, int64_t i)
{
    ಆದರೆ (i == ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ) {
        av_log(av_log_obj, level, "INT_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ log_ಮೌಲ್ಯ(ಶೂನ್ಯ *av_log_obj, ಪೂರ್ಣಾಂಕ level, ದ್ವಿಗುಣ d)
{
    ಆದರೆ      (d == ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ) {
        av_log(av_log_obj, level, "INT_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == (ದ್ವಿಗುಣ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(av_log_obj, level, "%g", d);
    }
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *get_opt_const_name(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *unit, int64_t ಮೌಲ್ಯ)
{
    ಸ್ಥಿರಾಂಕ AVOption *opt = ಖಾಲಿ;

    ಆದರೆ (!unit)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆಗ ((opt = av_opt_ಮುಂದಿನ(obj, opt)))
        ಆದರೆ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == ಮೌಲ್ಯ)
            ಹಿಂತಿರುಗಿ opt->name;
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಅಕ್ಷರ *get_opt_flags_string(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *unit, int64_t ಮೌಲ್ಯ)
{
    ಸ್ಥಿರಾಂಕ AVOption *opt = ಖಾಲಿ;
    ಅಕ್ಷರ flags[512];

    flags[0] = 0;
    ಆದರೆ (!unit)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆಗ ((opt = av_opt_ಮುಂದಿನ(obj, opt))) {
        ಆದರೆ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & ಮೌಲ್ಯ) {
            ಆದರೆ (flags[0])
                av_strlcatf(flags, ಗಾತ್ರ(flags), "+");
            av_strlcatf(flags, ಗಾತ್ರ(flags), "%s", opt->name);
        }
    }
    ಆದರೆ (flags[0])
        ಹಿಂತಿರುಗಿ av_strdup(flags);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ log_type(ಶೂನ್ಯ *av_log_obj, ಸ್ಥಿರಾಂಕ AVOption *o,
                     ಎಣಿಕೆ AVOptionType ಪೋಷಕ_type)
{
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVOptionType type = TYPE_ತಳ(o->type);

    ಆದರೆ (o->type == AV_OPT_TYPE_CONST && (TYPE_ತಳ(ಪೋಷಕ_type) == AV_OPT_TYPE_INT || TYPE_ತಳ(ಪೋಷಕ_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ಆದರೆ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ಇಲ್ಲದಿದ್ದರೆ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ಸ್ಥಿರ ಶೂನ್ಯ log_default(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *av_log_obj, ಸ್ಥಿರಾಂಕ AVOption *opt)
{
    ಆದರೆ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ದ್ವಿಮಾನ)
        ಹಿಂತಿರುಗಿ;
    ಆದರೆ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_ಗಾತ್ರ ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_ದರ) &&
        !opt->default_val.str)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ಸ್ಥಿರಾಂಕ AVOptionArrayDef *arr = opt->default_val.arr;
        ಆದರೆ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ಹಿಂತಿರುಗಿ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    ಆಯ್ಕೆ (opt->type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS: {
        ಅಕ್ಷರ *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ಆದರೆ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ಇಲ್ಲದಿದ್ದರೆ {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        ನಿಲ್ಲಿಸು;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION: {
        ಅಕ್ಷರ buf[25];
        format_duration(buf, ಗಾತ್ರ(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        ನಿಲ್ಲಿಸು;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64: {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        ಆದರೆ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ಇಲ್ಲದಿದ್ದರೆ
            log_int_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        ನಿಲ್ಲಿಸು;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
        log_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.ಅಂಕೆ, q.den); }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ಅಕ್ಷರ *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ಅಕ್ಷರ *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR:
    ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
    ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DICT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
    ಸ್ಥಿತಿ AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        ನಿಲ್ಲಿಸು;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ಸ್ಥಿರ ಶೂನ್ಯ opt_list(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *av_log_obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *unit,
                     ಪೂರ್ಣಾಂಕ req_flags, ಪೂರ್ಣಾಂಕ rej_flags, ಎಣಿಕೆ AVOptionType ಪೋಷಕ_type)
{
    ಸ್ಥಿರಾಂಕ AVOption *opt = ಖಾಲಿ;
    AVOptionRanges *r;
    ಪೂರ್ಣಾಂಕ i;

    ಆಗ ((opt = av_opt_ಮುಂದಿನ(obj, opt))) {
        ಆದರೆ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            ಮುಂದುವರಿ;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ಆದರೆ (!unit && opt->type == AV_OPT_TYPE_CONST)
            ಮುಂದುವರಿ;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (unit && opt->type != AV_OPT_TYPE_CONST)
            ಮುಂದುವರಿ;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            ಮುಂದುವರಿ;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ಇಲ್ಲದಿದ್ದರೆ
            av_log(av_log_obj, AV_LOG_INFO, "  %s%-17s ",
                   (opt->flags & AV_OPT_FLAG_FILTERING_PARAM) ? " " : "-",
                   opt->name);

        log_type(av_log_obj, opt, ಪೋಷಕ_type);

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

        ಆದರೆ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ಆದರೆ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_ಹುಡುಕು_FAKE_OBJ) >= 0) {
            ಆಯ್ಕೆ (opt->type) {
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
            ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
            ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
            ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
            ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
            ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
                ಗಾಗಿ (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, r->range[i]->ಮೌಲ್ಯ_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_ಮೌಲ್ಯ(av_log_obj, AV_LOG_INFO, r->range[i]->ಮೌಲ್ಯ_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                ನಿಲ್ಲಿಸು;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        ಆದರೆ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

ಪೂರ್ಣಾಂಕ av_opt_show2(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *av_log_obj, ಪೂರ್ಣಾಂಕ req_flags, ಪೂರ್ಣಾಂಕ rej_flags)
{
    ಆದರೆ (!obj)
        ಹಿಂತಿರುಗಿ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ಖಾಲಿ, req_flags, rej_flags, -1);

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_opt_ಗಣ_defaults(ಶೂನ್ಯ *s)
{
    av_opt_ಗಣ_defaults2(s, 0, 0);
}

ಶೂನ್ಯ av_opt_ಗಣ_defaults2(ಶೂನ್ಯ *s, ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_2, ಪೂರ್ಣಾಂಕ flags)
{
    ಸ್ಥಿರಾಂಕ AVOption *opt = ಖಾಲಿ;
    ಆಗ ((opt = av_opt_ಮುಂದಿನ(s, opt))) {
        ಶೂನ್ಯ *dst = ((uint8_t*)s) + opt->ಸ್ಥಾನಾಂತರ;

        ಆದರೆ ((opt->flags & ಮುಖವಾಡ_2) != flags)
            ಮುಂದುವರಿ;

        ಆದರೆ (opt->flags & AV_OPT_FLAG_READONLY)
            ಮುಂದುವರಿ;

        ಆದರೆ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ಸ್ಥಿರಾಂಕ AVOptionArrayDef *arr = opt->default_val.arr;
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ಆದರೆ (arr && arr->def)
                opt_ಗಣ_array(s, s, opt, arr->def, dst);

            ಮುಂದುವರಿ;
        }

        ಆಯ್ಕೆ (opt->type) {
            ಸ್ಥಿತಿ AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
            ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
            ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
            ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
            ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
            ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
            ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
                write_ಸಂಖ್ಯೆ(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
            ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT: {
                ದ್ವಿಗುಣ val;
                val = opt->default_val.dbl;
                write_ಸಂಖ್ಯೆ(s, opt, dst, val, 1, 1, 1);
            }
            ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
                write_ಸಂಖ್ಯೆ(s, opt, dst, 1, val.den, val.ಅಂಕೆ, 1);
            }
            ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR:
                ಗಣ_string_color(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
                ಗಣ_string(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
                ಗಣ_string_image_ಗಾತ್ರ(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
                ಗಣ_string_video_ದರ(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_ದ್ವಿಮಾನ:
                ಗಣ_string_ದ್ವಿಮಾನ(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_CHLAYOUT:
                ಗಣ_string_channel_layout(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_DICT:
                ಗಣ_string_dict(s, opt, opt->default_val.str, dst);
                ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
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
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(ಶೂನ್ಯ *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **buf,
                                ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಜೋಡಿಗಳು_sep)
{
    ಅಕ್ಷರ *ಕೀಲಿ = av_get_token(buf, ಕೀಲಿ_val_sep);
    ಅಕ್ಷರ *val;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!ಕೀಲಿ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆದರೆ (*ಕೀಲಿ && strspn(*buf, ಕೀಲಿ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, ಜೋಡಿಗಳು_sep);
        ಆದರೆ (!val) {
            av_freep(&ಕೀಲಿ);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", ಕೀಲಿ);
        av_free(ಕೀಲಿ);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", ಕೀಲಿ, val);

    ret = av_opt_ಗಣ(ctx, ಕೀಲಿ, val, AV_OPT_ಹುಡುಕು_CHILDREN);
    ಆದರೆ (ret == AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", ಕೀಲಿ);

    av_free(ಕೀಲಿ);
    av_free(val);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_ಗಣ_options_string(ಶೂನ್ಯ *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *opts,
                          ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಜೋಡಿಗಳು_sep)
{
    ಪೂರ್ಣಾಂಕ ret, ಎಣಿಕೆ_2 = 0;

    ಆದರೆ (!opts)
        ಹಿಂತಿರುಗಿ 0;

    ಆಗ (*opts) {
        ಆದರೆ ((ret = parse_ಕೀಲಿ_ಮೌಲ್ಯ_pair(ctx, &opts, ಕೀಲಿ_val_sep, ಜೋಡಿಗಳು_sep)) < 0)
            ಹಿಂತಿರುಗಿ ret;
        ಎಣಿಕೆ_2++;

        ಆದರೆ (*opts)
            opts++;
    }

    ಹಿಂತಿರುಗಿ ಎಣಿಕೆ_2;
}

#ವ್ಯಾಖ್ಯಾನಿಸು WHITESPACES " \n\t\r"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ is_ಕೀಲಿ_char(ಅಕ್ಷರ c)
{
    ಹಿಂತಿರುಗಿ (ಚಿಹ್ನೆರಹಿತ)((c | 32) - 'a') < 26 ||
           (ಚಿಹ್ನೆರಹಿತ)(c - '0') < 10 ||
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
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_ಕೀಲಿ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **ropts, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *delim, ಅಕ್ಷರ **rkey)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *opts = *ropts;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_ಆರಂಭ, *ಕೀಲಿ_ಕೊನೆ;

    ಕೀಲಿ_ಆರಂಭ = opts += strspn(opts, WHITESPACES);
    ಆಗ (is_ಕೀಲಿ_char(*opts))
        opts++;
    ಕೀಲಿ_ಕೊನೆ = opts;
    opts += strspn(opts, WHITESPACES);
    ಆದರೆ (!*opts || !strchr(delim, *opts))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    opts++;
    ಆದರೆ (!(*rkey = av_malloc(ಕೀಲಿ_ಕೊನೆ - ಕೀಲಿ_ಆರಂಭ + 1)))
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಸ್ಮರಣೆ_ನಕಲು(*rkey, ಕೀಲಿ_ಆರಂಭ, ಕೀಲಿ_ಕೊನೆ - ಕೀಲಿ_ಆರಂಭ);
    (*rkey)[ಕೀಲಿ_ಕೊನೆ - ಕೀಲಿ_ಆರಂಭ] = 0;
    *ropts = opts;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_ಕೀಲಿ_ಮೌಲ್ಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **ropts,
                         ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಜೋಡಿಗಳು_sep,
                         ಚಿಹ್ನೆರಹಿತ flags,
                         ಅಕ್ಷರ **rkey, ಅಕ್ಷರ **rval)
{
    ಪೂರ್ಣಾಂಕ ret;
    ಅಕ್ಷರ *ಕೀಲಿ = ಖಾಲಿ, *val;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *opts = *ropts;

    ಆದರೆ ((ret = get_ಕೀಲಿ(&opts, ಕೀಲಿ_val_sep, &ಕೀಲಿ)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_ಕೀಲಿ))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಆದರೆ (!(val = av_get_token(&opts, ಜೋಡಿಗಳು_sep))) {
        av_free(ಕೀಲಿ);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = ಕೀಲಿ;
    *rval  = val;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_from_string(ಶೂನ್ಯ *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *opts,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *shorthand,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಜೋಡಿಗಳು_sep)
{
    ಪೂರ್ಣಾಂಕ ret, ಎಣಿಕೆ_2 = 0;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *dummy_shorthand = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ;

    ಆದರೆ (!opts)
        ಹಿಂತಿರುಗಿ 0;
    ಆದರೆ (!shorthand)
        shorthand = &dummy_shorthand;

    ಆಗ (*opts) {
        ಅಕ್ಷರ *parsed_ಕೀಲಿ, *ಮೌಲ್ಯ;
        ret = av_opt_get_ಕೀಲಿ_ಮೌಲ್ಯ(&opts, ಕೀಲಿ_val_sep, ಜೋಡಿಗಳು_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_ಕೀಲಿ : 0,
                                   &parsed_ಕೀಲಿ, &ಮೌಲ್ಯ);
        ಆದರೆ (ret < 0) {
            ಆದರೆ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ಇಲ್ಲದಿದ್ದರೆ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ಹಿಂತಿರುಗಿ ret;
        }
        ಆದರೆ (*opts)
            opts++;
        ಆದರೆ (parsed_ಕೀಲಿ) {
            ಕೀಲಿ = parsed_ಕೀಲಿ;
            ಆಗ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಕೀಲಿ = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", ಕೀಲಿ, ಮೌಲ್ಯ);
        ಆದರೆ ((ret = av_opt_ಗಣ(ctx, ಕೀಲಿ, ಮೌಲ್ಯ, 0)) < 0) {
            ಆದರೆ (ret == AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", ಕೀಲಿ);
            av_free(ಮೌಲ್ಯ);
            av_free(parsed_ಕೀಲಿ);
            ಹಿಂತಿರುಗಿ ret;
        }

        av_free(ಮೌಲ್ಯ);
        av_free(parsed_ಕೀಲಿ);
        ಎಣಿಕೆ_2++;
    }
    ಹಿಂತಿರುಗಿ ಎಣಿಕೆ_2;
}

ಶೂನ್ಯ av_opt_free(ಶೂನ್ಯ *obj)
{
    ಸ್ಥಿರಾಂಕ AVOption *o = ಖಾಲಿ;
    ಆಗ ((o = av_opt_ಮುಂದಿನ(obj, o))) {
        ಶೂನ್ಯ *pitem = (uint8_t *)obj + o->ಸ್ಥಾನಾಂತರ;

        ಆದರೆ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ಇಲ್ಲದಿದ್ದರೆ
            opt_free_elem(o->type, pitem);
    }
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_dict2(ಶೂನ್ಯ *obj, AVDictionary **options, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *t = ಖಾಲಿ;
    AVDictionary    *tmp = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!options)
        ಹಿಂತಿರುಗಿ 0;

    ಆಗ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_ಗಣ(obj, t->ಕೀಲಿ, t->ಮೌಲ್ಯ, ಹುಡುಕು_flags);
        ಆದರೆ (ret == AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು)
            ret = av_dict_ಗಣ(&tmp, t->ಕೀಲಿ, t->ಮೌಲ್ಯ, AV_DICT_MULTIKEY);
        ಆದರೆ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->ಕೀಲಿ, t->ಮೌಲ್ಯ);
            av_dict_free(&tmp);
            ಹಿಂತಿರುಗಿ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_dict(ಶೂನ್ಯ *obj, AVDictionary **options)
{
    ಹಿಂತಿರುಗಿ av_opt_ಗಣ_dict2(obj, options, 0);
}

ಸ್ಥಿರಾಂಕ AVOption *av_opt_ಕಂಡುಹಿಡಿ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *unit,
                            ಪೂರ್ಣಾಂಕ opt_flags, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಹಿಂತಿರುಗಿ av_opt_find2(obj, name, unit, opt_flags, ಹುಡುಕು_flags, ಖಾಲಿ);
}

ಸ್ಥಿರಾಂಕ AVOption *av_opt_find2(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *unit,
                             ಪೂರ್ಣಾಂಕ opt_flags, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags, ಶೂನ್ಯ **ಗುರಿ_obj)
{
    ಸ್ಥಿರಾಂಕ AVClass  *c;
    ಸ್ಥಿರಾಂಕ AVOption *o = ಖಾಲಿ;

    ಆದರೆ(!obj)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    c= *(AVClass**)obj;

    ಆದರೆ (!c)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_CHILDREN) {
        ಆದರೆ (ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_FAKE_OBJ) {
            ಶೂನ್ಯ *iter = ಖಾಲಿ;
            ಸ್ಥಿರಾಂಕ AVClass *ಮಗು;
            ಆಗ (ಮಗು = av_opt_ಮಗು_class_iterate(c, &iter))
                ಆದರೆ (o = av_opt_find2(&ಮಗು, name, unit, opt_flags, ಹುಡುಕು_flags, ಖಾಲಿ))
                    ಹಿಂತಿರುಗಿ o;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಶೂನ್ಯ *ಮಗು = ಖಾಲಿ;
            ಆಗ (ಮಗು = av_opt_ಮಗು_ಮುಂದಿನ(obj, ಮಗು))
                ಆದರೆ (o = av_opt_find2(ಮಗು, name, unit, opt_flags, ಹುಡುಕು_flags, ಗುರಿ_obj))
                    ಹಿಂತಿರುಗಿ o;
        }
    }

    ಆಗ (o = av_opt_ಮುಂದಿನ(obj, o)) {
        ಆದರೆ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ಆದರೆ (ಗುರಿ_obj) {
                ಆದರೆ (!(ಹುಡುಕು_flags & AV_OPT_ಹುಡುಕು_FAKE_OBJ))
                    *ಗುರಿ_obj = obj;
                ಇಲ್ಲದಿದ್ದರೆ
                    *ಗುರಿ_obj = ಖಾಲಿ;
            }
            ಹಿಂತಿರುಗಿ o;
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ *av_opt_ಮಗು_ಮುಂದಿನ(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *prev)
{
    ಸ್ಥಿರಾಂಕ AVClass *c = *(AVClass **)obj;
    ಆದರೆ (c->ಮಗು_ಮುಂದಿನ)
        ಹಿಂತಿರುಗಿ c->ಮಗು_ಮುಂದಿನ(obj, prev);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರಾಂಕ AVClass *av_opt_ಮಗು_class_iterate(ಸ್ಥಿರಾಂಕ AVClass *ಪೋಷಕ, ಶೂನ್ಯ **iter)
{
    ಆದರೆ (ಪೋಷಕ->ಮಗು_class_iterate)
        ಹಿಂತಿರುಗಿ ಪೋಷಕ->ಮಗು_class_iterate(iter);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_copy_elem(ಶೂನ್ಯ *logctx, ಎಣಿಕೆ AVOptionType type,
                         ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src)
{
    ಆದರೆ (type == AV_OPT_TYPE_STRING) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *src_str = *(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ *)src;
        ಅಕ್ಷರ         **dstp =  (ಅಕ್ಷರ **)dst;
        ಆದರೆ (*dstp != src_str)
            av_freep(dstp);
        ಆದರೆ (src_str) {
            *dstp = av_strdup(src_str);
            ಆದರೆ (!*dstp)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type == AV_OPT_TYPE_ದ್ವಿಮಾನ) {
        ಸ್ಥಿರಾಂಕ uint8_t *ಸ್ಥಿರಾಂಕ *src8 = (ಸ್ಥಿರಾಂಕ uint8_t *ಸ್ಥಿರಾಂಕ *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        ಪೂರ್ಣಾಂಕ len = *(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *)(src8 + 1);
        ಆದರೆ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ಆದರೆ (len && !*dst8) {
            *(ಪೂರ್ಣಾಂಕ *)(dst8 + 1) = 0;
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        *(ಪೂರ್ಣಾಂಕ *)(dst8 + 1) = len;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type == AV_OPT_TYPE_DICT) {
        ಸ್ಥಿರಾಂಕ AVDictionary *sdict = *(ಸ್ಥಿರಾಂಕ AVDictionary * ಸ್ಥಿರಾಂಕ *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ಆದರೆ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ಖಾಲಿ;
        ಹಿಂತಿರುಗಿ av_dict_copy(ddictp, sdict, 0);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type == AV_OPT_TYPE_CHLAYOUT) {
        ಸ್ಥಿರಾಂಕ AVChannelLayout *slayout = (ಸ್ಥಿರಾಂಕ AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ಆದರೆ (dlayout != slayout) {
            ಆದರೆ (dlayout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM &&
                slayout->ಕ್ರಮ == AV_CHANNEL_ಕ್ರಮ_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ಖಾಲಿ;
            ಹಿಂತಿರುಗಿ av_channel_layout_copy(dst, src);
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (opt_is_pod(type)) {
        size_t ಗಾತ್ರ_2 = opt_type_desc[type].ಗಾತ್ರ_2;
        ಸ್ಮರಣೆ_ನಕಲು(dst, src, ಗಾತ್ರ_2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_copy_array(ಶೂನ್ಯ *logctx, ಸ್ಥಿರಾಂಕ AVOption *o,
                          ಶೂನ್ಯ **pdst, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ *psrc)
{
    ಚಿಹ್ನೆರಹಿತ nb_elems = *opt_array_pcount(psrc);
    ಶೂನ್ಯ         *dst = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (*pdst == *psrc) {
        *pdst                   = ಖಾಲಿ;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_ತಳ(o->type)].ಗಾತ್ರ_2);
    ಆದರೆ (!dst)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_ತಳ(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(ಶೂನ್ಯ**)psrc, i));
        ಆದರೆ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_copy(ಶೂನ್ಯ *dst, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src)
{
    ಸ್ಥಿರಾಂಕ AVOption *o = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ AVClass *c;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (!src)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ಆದರೆ (!c || c != *(AVClass **)dst)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆಗ ((o = av_opt_ಮುಂದಿನ(src, o))) {
        ಶೂನ್ಯ *ಕ್ಷೇತ್ರ_dst = (uint8_t *)dst + o->ಸ್ಥಾನಾಂತರ;
        ಶೂನ್ಯ *ಕ್ಷೇತ್ರ_src = (uint8_t *)src + o->ಸ್ಥಾನಾಂತರ;

        ಪೂರ್ಣಾಂಕ err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       ಕ್ಷೇತ್ರ_dst, ಕ್ಷೇತ್ರ_src) :
                  opt_copy_elem (dst, o->type, ಕ್ಷೇತ್ರ_dst, ಕ್ಷೇತ್ರ_src);
        ಆದರೆ (err < 0)
            ret = err;
    }
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_get_array_ಗಾತ್ರ(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags,
                          ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಹೊರಹೋಗು_val)
{
    ಶೂನ್ಯ *ಗುರಿ_obj, *parray;
    ಸ್ಥಿರಾಂಕ AVOption *o;

    o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    parray = (uint8_t *)ಗುರಿ_obj + o->ಸ್ಥಾನಾಂತರ;
    *ಹೊರಹೋಗು_val = *opt_array_pcount(parray);

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_get_array(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags,
                     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಆರಂಭ_elem, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_elems,
                     ಎಣಿಕೆ AVOptionType ಹೊರಹೋಗು_type, ಶೂನ್ಯ *ಹೊರಹೋಗು_val)
{
    ಸ್ಥಿರಾಂಕ size_t elem_ಗಾತ್ರ_ಹೊರಹೋಗು = opt_type_desc[TYPE_ತಳ(ಹೊರಹೋಗು_type)].ಗಾತ್ರ_2;

    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಶೂನ್ಯ *ಗುರಿ_obj;

    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *parray;
    ಚಿಹ್ನೆರಹಿತ array_ಗಾತ್ರ;

    ಪೂರ್ಣಾಂಕ ret;

    o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ_obj);
    ಆದರೆ (!o || !ಗುರಿ_obj)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಆದರೆ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (ಹೊರಹೋಗು_type & AV_OPT_TYPE_FLAG_ARRAY))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    parray     = (uint8_t *)ಗುರಿ_obj + o->ಸ್ಥಾನಾಂತರ;
    array_ಗಾತ್ರ = *opt_array_pcount(parray);

    ಆದರೆ (ಆರಂಭ_elem >= array_ಗಾತ್ರ ||
        array_ಗಾತ್ರ - ಆರಂಭ_elem < nb_elems)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < nb_elems; i++) {
        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src = opt_array_pelem(o, *(ಶೂನ್ಯ**)parray, ಆರಂಭ_elem + i);
        ಶೂನ್ಯ       *dst = (uint8_t*)ಹೊರಹೋಗು_val + i * elem_ಗಾತ್ರ_ಹೊರಹೋಗು;

        ಆದರೆ (ಹೊರಹೋಗು_type == TYPE_ತಳ(o->type)) {
            ret = opt_copy_elem(obj, ಹೊರಹೋಗು_type, dst, src);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹೊರಹೋಗು_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *ಹೊರಹೋಗು = buf;

            ret = opt_get_elem(o, &ಹೊರಹೋಗು, ಗಾತ್ರ(buf), src, ಹುಡುಕು_flags);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;

            ಆದರೆ (ಹೊರಹೋಗು == buf) {
                ಹೊರಹೋಗು = av_strdup(buf);
                ಆದರೆ (!ಹೊರಹೋಗು) {
                    ret = AVERROR(ENOMEM);
                    ಹೋಗು fail;
                }
            }

            *(uint8_t**)dst = ಹೊರಹೋಗು;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹೊರಹೋಗು_type == AV_OPT_TYPE_INT64    ||
                   ಹೊರಹೋಗು_type == AV_OPT_TYPE_DOUBLE   ||
                   ಹೊರಹೋಗು_type == AV_OPT_TYPE_RATIONAL) {
            ದ್ವಿಗುಣ     ಅಂಕೆ = 1.0;
            ಪೂರ್ಣಾಂಕ        den = 1;
            int64_t intnum = 1;

            ret = read_ಸಂಖ್ಯೆ(o, src, &ಅಂಕೆ, &den, &intnum);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;

            ಆಯ್ಕೆ (ಹೊರಹೋಗು_type) {
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (ಅಂಕೆ == den) ?  intnum : ಅಂಕೆ * intnum / den;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
                *(ದ್ವಿಗುಣ*)dst = ಅಂಕೆ * intnum / den;
                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (ಅಂಕೆ == 1.0 && (ಪೂರ್ಣಾಂಕ)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_ಗಮ್ಯ_rational(ಅಂಕೆ * intnum / den);
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ: av_assert0(0);
            }
        } ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಹಿಂತಿರುಗಿ 0;
fail:
    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < nb_elems; i++)
        opt_free_elem(ಹೊರಹೋಗು_type, (uint8_t*)ಹೊರಹೋಗು_val + i * elem_ಗಾತ್ರ_ಹೊರಹೋಗು);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_ಗಣ_array(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags,
                     ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಆರಂಭ_elem, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_elems,
                     ಎಣಿಕೆ AVOptionType val_type, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *val)
{
    ಸ್ಥಿರಾಂಕ size_t elem_ಗಾತ್ರ_val = opt_type_desc[TYPE_ತಳ(val_type)].ಗಾತ್ರ_2;

    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಸ್ಥಿರಾಂಕ AVOptionArrayDef *arr;
    ಶೂನ್ಯ *ಗುರಿ_obj;

    ಶೂನ್ಯ *parray;
    ಶೂನ್ಯ *new_elems;
    ಚಿಹ್ನೆರಹಿತ *array_ಗಾತ್ರ, new_ಗಾತ್ರ;
    size_t elem_ಗಾತ್ರ;

    ಪೂರ್ಣಾಂಕ ret = 0;

    ret = opt_ಗಣ_init(obj, name, ಹುಡುಕು_flags, 0, &ಗುರಿ_obj, &o, &parray);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_ಗಾತ್ರ = opt_array_pcount(parray);
    elem_ಗಾತ್ರ  = opt_type_desc[TYPE_ತಳ(o->type)].ಗಾತ್ರ_2;

    ಆದರೆ (ಆರಂಭ_elem > *array_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    // compute new array size
    ಆದರೆ (!val) {
        ಆದರೆ (*array_ಗಾತ್ರ - ಆರಂಭ_elem < nb_elems)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        new_ಗಾತ್ರ = *array_ಗಾತ್ರ - nb_elems;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹುಡುಕು_flags & AV_OPT_ARRAY_REPLACE) {
        ಆದರೆ (ಆರಂಭ_elem >= UINT_MAX - nb_elems)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        new_ಗಾತ್ರ = FFMAX(*array_ಗಾತ್ರ, ಆರಂಭ_elem + nb_elems);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (nb_elems >= UINT_MAX - *array_ಗಾತ್ರ)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

        new_ಗಾತ್ರ = *array_ಗಾತ್ರ + nb_elems;
    }

    ಆದರೆ (arr &&
        ((arr->ಗಾತ್ರ_max && new_ಗಾತ್ರ > arr->ಗಾತ್ರ_max) ||
         (arr->ಗಾತ್ರ_min && new_ಗಾತ್ರ < arr->ಗಾತ್ರ_min)))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ಆದರೆ (!val) {
        ಶೂನ್ಯ *array = *(ಶೂನ್ಯ**)parray;

        ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, ಆರಂಭ_elem + i));
        }

        ಆದರೆ (new_ಗಾತ್ರ > 0) {
            memmove(opt_array_pelem(o, array, ಆರಂಭ_elem),
                    opt_array_pelem(o, array, ಆರಂಭ_elem + nb_elems),
                    elem_ಗಾತ್ರ * (*array_ಗಾತ್ರ - ಆರಂಭ_elem - nb_elems));

            array = av_realloc_array(array, new_ಗಾತ್ರ, elem_ಗಾತ್ರ);
            ಆದರೆ (!array)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

            *(ಶೂನ್ಯ**)parray = array;
        } ಇಲ್ಲದಿದ್ದರೆ
            av_freep(parray);

        *array_ಗಾತ್ರ = new_ಗಾತ್ರ;

        ಹಿಂತಿರುಗಿ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_ಗಾತ್ರ);
    ಆದರೆ (!new_elems)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    // convert/validate each new element
    ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < nb_elems; i++) {
        ಶೂನ್ಯ       *dst = opt_array_pelem(o, new_elems, i);
        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src = (uint8_t*)val + i * elem_ಗಾತ್ರ_val;

        ದ್ವಿಗುಣ     ಅಂಕೆ = 1.0;
        ಪೂರ್ಣಾಂಕ        den = 1;
        int64_t intnum = 1;

        ಆದರೆ (val_type == TYPE_ತಳ(o->type)) {
            ಪೂರ್ಣಾಂಕ err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;

            // validate the range for numeric options
            err = read_ಸಂಖ್ಯೆ(o, dst, &ಅಂಕೆ, &den, &intnum);
            ಆದರೆ (err >= 0 && TYPE_ತಳ(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < ಅಂಕೆ * intnum || o->min * den > ಅಂಕೆ * intnum)) {
                ಅಂಕೆ = den ? ಅಂಕೆ * intnum / den : (ಅಂಕೆ && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       ಆರಂಭ_elem + i, o->name, ಅಂಕೆ, o->min, o->max);
                ret = AVERROR(ERANGE);
                ಹೋಗು fail;
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_ಗಣ_elem(obj, ಗುರಿ_obj, o, *(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ **)src, dst);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            ಆಯ್ಕೆ (val_type) {
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT:       intnum = *(ಪೂರ್ಣಾಂಕ*)src;                ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:     ಅಂಕೆ    = *(ದಶಮಾಂಶ*)src;              ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:    ಅಂಕೆ    = *(ದ್ವಿಗುಣ*)src;             ನಿಲ್ಲಿಸು;
            ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->ಅಂಕೆ;
                                        den    = ((AVRational*)src)->den;   ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ: av_assert0(0);
            }

            ret = write_ಸಂಖ್ಯೆ(obj, o, dst, ಅಂಕೆ, den, intnum, 0);
            ಆದರೆ (ret < 0)
                ಹೋಗು fail;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ret = AVERROR(ENOSYS);
            ಹೋಗು fail;
        }
    }

    // commit new elements to the array
    ಆದರೆ (ಆರಂಭ_elem == 0 && nb_elems == new_ಗಾತ್ರ) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_ಗಾತ್ರ);
        *(ಶೂನ್ಯ**)parray = new_elems;
        *array_ಗಾತ್ರ     = nb_elems;

        new_elems = ಖಾಲಿ;
        nb_elems  = 0;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಶೂನ್ಯ *array = av_realloc_array(*(ಶೂನ್ಯ**)parray, new_ಗಾತ್ರ, elem_ಗಾತ್ರ);
        ಆದರೆ (!array) {
            ret = AVERROR(ENOMEM);
            ಹೋಗು fail;
        }

        ಆದರೆ (ಹುಡುಕು_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = ಆರಂಭ_elem; i < FFMIN(ಆರಂಭ_elem + nb_elems, *array_ಗಾತ್ರ); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ಇಲ್ಲದಿದ್ದರೆ {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, ಆರಂಭ_elem + nb_elems),
                    opt_array_pelem(o, array, ಆರಂಭ_elem),
                    elem_ಗಾತ್ರ * (*array_ಗಾತ್ರ - ಆರಂಭ_elem));
        }

        ಸ್ಮರಣೆ_ನಕಲು((uint8_t*)array + elem_ಗಾತ್ರ * ಆರಂಭ_elem, new_elems, elem_ಗಾತ್ರ * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(ಶೂನ್ಯ**)parray = array;
        *array_ಗಾತ್ರ     = new_ಗಾತ್ರ;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_query_ranges(AVOptionRanges **ranges_arg, ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ ret;
    ಸ್ಥಿರಾಂಕ AVClass *c = *(AVClass**)obj;
    ಪೂರ್ಣಾಂಕ (*callback)(AVOptionRanges **, ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ flags) = c->query_ranges;

    ಆದರೆ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, ಕೀಲಿ, flags);
    ಆದರೆ (ret >= 0) {
        ಆದರೆ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_opt_query_ranges_default(AVOptionRanges **ranges_arg, ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ flags)
{
    AVOptionRanges *ranges = av_mallocz(ಗಾತ್ರ(*ranges));
    AVOptionRange **range_array = av_mallocz(ಗಾತ್ರ(ಶೂನ್ಯ*));
    AVOptionRange *range = av_mallocz(ಗಾತ್ರ(*range));
    ಸ್ಥಿರಾಂಕ AVOption *ಕ್ಷೇತ್ರ = av_opt_ಕಂಡುಹಿಡಿ(obj, ಕೀಲಿ, ಖಾಲಿ, 0, flags);
    ಪೂರ್ಣಾಂಕ ret;

    *ranges_arg = ಖಾಲಿ;

    ಆದರೆ (!ranges || !range || !range_array || !ಕ್ಷೇತ್ರ) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->ಮೌಲ್ಯ_min = ಕ್ಷೇತ್ರ->min;
    range->ಮೌಲ್ಯ_max = ಕ್ಷೇತ್ರ->max;

    ಆಯ್ಕೆ (ಕ್ಷೇತ್ರ->type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
    ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR:
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->ಮೌಲ್ಯ_min = -1;
        range->ಮೌಲ್ಯ_max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
        range->component_min = 0;
        range->component_max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ/128/8;
        range->ಮೌಲ್ಯ_min = 0;
        range->ಮೌಲ್ಯ_max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ/8;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
        range->component_min = 1;
        range->component_max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
        range->ಮೌಲ್ಯ_min = 1;
        range->ಮೌಲ್ಯ_max = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ret = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }

    *ranges_arg = ranges;
    ಹಿಂತಿರುಗಿ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    ಪೂರ್ಣಾಂಕ i;
    AVOptionRanges *ranges = *rangesp;

    ಆದರೆ (!ranges)
        ಹಿಂತಿರುಗಿ;

    ಗಾಗಿ (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ಆದರೆ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

ಪೂರ್ಣಾಂಕ av_opt_is_ಗಣ_ಗಮ್ಯ_default(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ AVOption *o)
{
    int64_t i64;
    ದ್ವಿಗುಣ d;
    AVRational q;
    ಪೂರ್ಣಾಂಕ ret, w, h;
    ಅಕ್ಷರ *str;
    ಶೂನ್ಯ *dst;

    ಆದರೆ (!o || !obj)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *def = o->default_val.arr ? o->default_val.arr->def : ಖಾಲಿ;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        ಆದರೆ (!!val != !!def)
            ret = 0;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (val)
            ret = !strcmp(val, def);
        ಇಲ್ಲದಿದ್ದರೆ
            ret = 1;

        av_freep(&val);

        ಹಿಂತಿರುಗಿ ret;
    }

    ಆಯ್ಕೆ (o->type) {
    ಸ್ಥಿತಿ AV_OPT_TYPE_CONST:
        ಹಿಂತಿರುಗಿ 1;
    ಸ್ಥಿತಿ AV_OPT_TYPE_BOOL:
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLAGS:
    ಸ್ಥಿತಿ AV_OPT_TYPE_PIXEL_FMT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_SAMPLE_FMT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT:
    ಸ್ಥಿತಿ AV_OPT_TYPE_DURATION:
    ಸ್ಥಿತಿ AV_OPT_TYPE_INT64:
    ಸ್ಥಿತಿ AV_OPT_TYPE_UINT64:
        read_ಸಂಖ್ಯೆ(o, dst, ಖಾಲಿ, ಖಾಲಿ, &i64);
        ಹಿಂತಿರುಗಿ o->default_val.i64 == i64;
    ಸ್ಥಿತಿ AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ಆದರೆ (o->default_val.str) {
            ಆದರೆ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ಹಿಂತಿರುಗಿ ret;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_STRING:
        str = *(ಅಕ್ಷರ **)dst;
        ಆದರೆ (str == o->default_val.str) //2 NULLs
            ಹಿಂತಿರುಗಿ 1;
        ಆದರೆ (!str || !o->default_val.str) //1 NULL
            ಹಿಂತಿರುಗಿ 0;
        ಹಿಂತಿರುಗಿ !strcmp(str, o->default_val.str);
    ಸ್ಥಿತಿ AV_OPT_TYPE_DOUBLE:
        d = *(ದ್ವಿಗುಣ *)dst;
        ಹಿಂತಿರುಗಿ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ಸ್ಥಿತಿ AV_OPT_TYPE_FLOAT:
        d = *(ದಶಮಾಂಶ *)dst;
        ಹಿಂತಿರುಗಿ (ದಶಮಾಂಶ)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ಸ್ಥಿತಿ AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        ಹಿಂತಿರುಗಿ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_ದ್ವಿಮಾನ: {
        ರಚನೆ {
            uint8_t *ದತ್ತಾಂಶ;
            ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;
        } tmp = {0};
        ಪೂರ್ಣಾಂಕ opt_ಗಾತ್ರ = *(ಪೂರ್ಣಾಂಕ *)((ಶೂನ್ಯ **)dst + 1);
        ಶೂನ್ಯ *opt_ptr = *(ಶೂನ್ಯ **)dst;
        ಆದರೆ (!opt_ಗಾತ್ರ && (!o->default_val.str || !ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(o->default_val.str)))
            ಹಿಂತಿರುಗಿ 1;
        ಆದರೆ (!opt_ಗಾತ್ರ ||  !o->default_val.str || !ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(o->default_val.str ))
            ಹಿಂತಿರುಗಿ 0;
        ಆದರೆ (opt_ಗಾತ್ರ != ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(o->default_val.str) / 2)
            ಹಿಂತಿರುಗಿ 0;
        ret = ಗಣ_string_ದ್ವಿಮಾನ(ಖಾಲಿ, ಖಾಲಿ, o->default_val.str, &tmp.ದತ್ತಾಂಶ);
        ಆದರೆ (!ret)
            ret = !memcmp(opt_ptr, tmp.ದತ್ತಾಂಶ, tmp.ಗಾತ್ರ_2);
        av_free(tmp.ದತ್ತಾಂಶ);
        ಹಿಂತಿರುಗಿ ret;
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ಖಾಲಿ;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *en1 = ಖಾಲಿ;
        ಸ್ಥಿರಾಂಕ AVDictionary_ನಮೂದು *en2 = ಖಾಲಿ;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ಆದರೆ (ret < 0) {
            av_dict_free(&dict1);
            ಹಿಂತಿರುಗಿ ret;
        }
        ಮಾಡು {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ಆಗ (en1 && en2 && !strcmp(en1->ಕೀಲಿ, en2->ಕೀಲಿ) && !strcmp(en1->ಮೌಲ್ಯ, en2->ಮೌಲ್ಯ));
        av_dict_free(&dict1);
        ಹಿಂತಿರುಗಿ (!en1 && !en2);
    }
    ಸ್ಥಿತಿ AV_OPT_TYPE_IMAGE_ಗಾತ್ರ:
        ಆದರೆ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ret = av_parse_video_ಗಾತ್ರ(&w, &h, o->default_val.str)) < 0)
            ಹಿಂತಿರುಗಿ ret;
        ಹಿಂತಿರುಗಿ (w == *(ಪೂರ್ಣಾಂಕ *)dst) && (h == *((ಪೂರ್ಣಾಂಕ *)dst+1));
    ಸ್ಥಿತಿ AV_OPT_TYPE_VIDEO_ದರ:
        q = (AVRational){0, 0};
        ಆದರೆ (o->default_val.str) {
            ಆದರೆ ((ret = av_parse_video_ದರ(&q, o->default_val.str)) < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
        ಹಿಂತಿರುಗಿ !av_cmp_q(*(AVRational*)dst, q);
    ಸ್ಥಿತಿ AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ಆದರೆ (o->default_val.str) {
            ಆದರೆ ((ret = av_parse_color(color, o->default_val.str, -1, ಖಾಲಿ)) < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
        ಹಿಂತಿರುಗಿ !memcmp(color, dst, ಗಾತ್ರ(color));
    }
    ಪೂರ್ವನಿಯೋಜಿತ:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ AVERROR_PATCHWELCOME;
}

ಪೂರ್ಣಾಂಕ av_opt_is_ಗಣ_ಗಮ್ಯ_default_by_name(ಶೂನ್ಯ *obj, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, ಪೂರ್ಣಾಂಕ ಹುಡುಕು_flags)
{
    ಸ್ಥಿರಾಂಕ AVOption *o;
    ಶೂನ್ಯ *ಗುರಿ;
    ಆದರೆ (!obj)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ಖಾಲಿ, 0, ಹುಡುಕು_flags, &ಗುರಿ);
    ಆದರೆ (!o)
        ಹಿಂತಿರುಗಿ AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು;
    ಹಿಂತಿರುಗಿ av_opt_is_ಗಣ_ಗಮ್ಯ_default(ಗುರಿ, o);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ opt_serialize(ಶೂನ್ಯ *obj, ಪೂರ್ಣಾಂಕ opt_flags, ಪೂರ್ಣಾಂಕ flags, ಪೂರ್ಣಾಂಕ *cnt,
                         AVBPrint *bprint, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಜೋಡಿಗಳು_sep)
{
    ಸ್ಥಿರಾಂಕ AVOption *o = ಖಾಲಿ;
    ಶೂನ್ಯ *ಮಗು = ಖಾಲಿ;
    uint8_t *buf;
    ಪೂರ್ಣಾಂಕ ret;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ special_chars[] = {ಜೋಡಿಗಳು_sep, ಕೀಲಿ_val_sep, '\0'};

    ಆದರೆ (flags & AV_OPT_SERIALIZE_ಹುಡುಕು_CHILDREN)
        ಆಗ (ಮಗು = av_opt_ಮಗು_ಮುಂದಿನ(obj, ಮಗು)) {
            ret = opt_serialize(ಮಗು, opt_flags, flags, cnt, bprint,
                                ಕೀಲಿ_val_sep, ಜೋಡಿಗಳು_sep);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        }

    ಆಗ (o = av_opt_ಮುಂದಿನ(obj, o)) {
        ಆದರೆ (o->type == AV_OPT_TYPE_CONST)
            ಮುಂದುವರಿ;
        ಆದರೆ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ಆದರೆ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ಆದರೆ (o->flags == opt_flags)
                    ಮುಂದುವರಿ;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((o->flags & opt_flags) == opt_flags)
                ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಆದರೆ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                ಮುಂದುವರಿ;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (((o->flags & opt_flags) != opt_flags))
                ಮುಂದುವರಿ;
        }
        ಆದರೆ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_ಗಣ_ಗಮ್ಯ_default(obj, o) > 0)
            ಮುಂದುವರಿ;
        ಆದರೆ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ಖಾಲಿ);
            ಹಿಂತಿರುಗಿ ret;
        }
        ಆದರೆ (buf) {
            ಆದರೆ ((*cnt)++)
                av_bprint_append_ದತ್ತಾಂಶ(bprint, &ಜೋಡಿಗಳು_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_ಬಹುಲಕ_BACKSLASH, 0);
            av_bprint_append_ದತ್ತಾಂಶ(bprint, &ಕೀಲಿ_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_ಬಹುಲಕ_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_opt_serialize(ಶೂನ್ಯ *obj, ಪೂರ್ಣಾಂಕ opt_flags, ಪೂರ್ಣಾಂಕ flags, ಅಕ್ಷರ **ಬಫರ್,
                     ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಕೀಲಿ_val_sep, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ ಜೋಡಿಗಳು_sep)
{
    AVBPrint bprint;
    ಪೂರ್ಣಾಂಕ ret, cnt = 0;

    ಆದರೆ (ಜೋಡಿಗಳು_sep == '\0' || ಕೀಲಿ_val_sep == '\0' || ಜೋಡಿಗಳು_sep == ಕೀಲಿ_val_sep ||
        ಜೋಡಿಗಳು_sep == '\\' || ಕೀಲಿ_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ (!obj || !ಬಫರ್)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    *ಬಫರ್ = ಖಾಲಿ;
    av_bprint_init(&bprint, 64, AV_BPRINT_ಗಾತ್ರ_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        ಕೀಲಿ_val_sep, ಜೋಡಿಗಳು_sep);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ret = av_bprint_finalize(&bprint, ಬಫರ್);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಹಿಂತಿರುಗಿ 0;
}
