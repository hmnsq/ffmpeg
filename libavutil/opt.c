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

#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "channel_layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dict.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eval.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "parseutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "opt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "samplefmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bprint.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <float.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TYPE_ਅਧਾਰ(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ਅਚਲ AVOption *av_opt_ਅਗਲਾ(ਅਚਲ ਖਾਲੀ *obj, ਅਚਲ AVOption *ਆਖਰੀ)
{
    ਅਚਲ AVClass *class;
    ਜੇ (!obj)
        ਵਾਪਸ ਨਿਰਾ;
    class = *(ਅਚਲ AVClass**)obj;
    ਜੇ (!ਆਖਰੀ && class && class->option && class->option[0].name)
        ਵਾਪਸ class->option;
    ਜੇ (ਆਖਰੀ && ਆਖਰੀ[1].name)
        ਵਾਪਸ ++ਆਖਰੀ;
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    size_t      ਮਾਪ;
    ਅਚਲ ਅੱਖਰ *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { ਆਕਾਰ(ਬਿਨਾਨਿਸ਼ਾਨੀ),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { ਆਕਾਰ(ਪੂਰਨ),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { ਆਕਾਰ(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { ਆਕਾਰ(ਬਿਨਾਨਿਸ਼ਾਨੀ),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { ਆਕਾਰ(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { ਆਕਾਰ(ਦੁੱਗਣਾ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { ਆਕਾਰ(ਦਸ਼ਮਲਵ),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { ਆਕਾਰ(ਅੱਖਰ *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { ਆਕਾਰ(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ਦੁਆਧਾਰੀ]        = { ਆਕਾਰ(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { ਆਕਾਰ(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_ਮਾਪ]    = { ਆਕਾਰ(ਪੂਰਨ[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_ਦਰ]    = { ਆਕਾਰ(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { ਆਕਾਰ(ਗਿਣਤੀ AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { ਆਕਾਰ(ਗਿਣਤੀ AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { ਆਕਾਰ(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { ਆਕਾਰ(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { ਆਕਾਰ(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { ਆਕਾਰ(ਪੂਰਨ),            "<boolean>" },
};

// option is plain old data
ਸਥਿਰ ਪੂਰਨ opt_is_pod(ਗਿਣਤੀ AVOptionType type)
{
    ਚੋਣ (type) {
    ਹਾਲਤ AV_OPT_TYPE_FLAGS:
    ਹਾਲਤ AV_OPT_TYPE_INT:
    ਹਾਲਤ AV_OPT_TYPE_INT64:
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
    ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
    ਹਾਲਤ AV_OPT_TYPE_DURATION:
    ਹਾਲਤ AV_OPT_TYPE_COLOR:
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
    ਹਾਲਤ AV_OPT_TYPE_UINT:
        ਵਾਪਸ 1;
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ uint8_t opt_array_sep(ਅਚਲ AVOption *o)
{
    ਅਚਲ AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ਵਾਪਸ (d && d->sep) ? d->sep : ',';
}

ਸਥਿਰ ਖਾਲੀ *opt_array_pelem(ਅਚਲ AVOption *o, ਖਾਲੀ *array, ਬਿਨਾਨਿਸ਼ਾਨੀ idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ਵਾਪਸ (uint8_t *)array + idx * opt_type_desc[TYPE_ਅਧਾਰ(o->type)].ਮਾਪ;
}

ਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ *opt_array_pcount(ਅਚਲ ਖਾਲੀ *parray)
{
    ਵਾਪਸ (ਬਿਨਾਨਿਸ਼ਾਨੀ *)((ਅਚਲ ਖਾਲੀ * ਅਚਲ *)parray + 1);
}

ਸਥਿਰ ਖਾਲੀ opt_free_elem(ਗਿਣਤੀ AVOptionType type, ਖਾਲੀ *ptr)
{
    ਚੋਣ (TYPE_ਅਧਾਰ(type)) {
    ਹਾਲਤ AV_OPT_TYPE_STRING:
    ਹਾਲਤ AV_OPT_TYPE_ਦੁਆਧਾਰੀ:
        av_freep(ptr);
        ਰੋਕੋ;

    ਹਾਲਤ AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        ਰੋਕੋ;

    ਹਾਲਤ AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        ਰੋਕੋ;

    ਮੂਲ:
        ਰੋਕੋ;
    }
}

ਸਥਿਰ ਖਾਲੀ opt_free_array(ਅਚਲ AVOption *o, ਖਾਲੀ *parray, ਬਿਨਾਨਿਸ਼ਾਨੀ *ਗਿਣਤੀ_2)
{
    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < *ਗਿਣਤੀ_2; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(ਖਾਲੀ **)parray, i));

    av_freep(parray);
    *ਗਿਣਤੀ_2 = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ਸਥਿਰ ਪੂਰਨ opt_ਸੈੱਟ_init(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags,
                        ਪੂਰਨ require_type,
                        ਖਾਲੀ **ptgt, ਅਚਲ AVOption **po, ਖਾਲੀ **pdst)
{
    ਖਾਲੀ *logctx;
    ਅਚਲ AVOption *o;
    ਖਾਲੀ *tgt;

    o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &tgt);
    ਜੇ (!o || (!tgt && !(ਖੋਜ_flags & AV_OPT_ਖੋਜ_FAKE_OBJ)))
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;

    ਜੇ (o->flags & AV_OPT_FLAG_READONLY)
        ਵਾਪਸ AVERROR(EINVAL);

    logctx = tgt ? obj : ਨਿਰਾ;

    ਜੇ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ *state_flags = ਨਿਰਾ;
        ਅਚਲ AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ਅਚਲ AVClass**)tgt;
        ਜੇ (class->state_flags_ਵਿੱਥ)
            state_flags = (ਬਿਨਾਨਿਸ਼ਾਨੀ*)((uint8_t*)tgt + class->state_flags_ਵਿੱਥ);

        ਜੇ (!state_flags && obj != tgt) {
            class = *(ਅਚਲ AVClass**)obj;
            ਜੇ (class->state_flags_ਵਿੱਥ)
                state_flags = (ਬਿਨਾਨਿਸ਼ਾਨੀ*)((uint8_t*)obj + class->state_flags_ਵਿੱਥ);
        }

        ਜੇ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ਵਾਪਸ AVERROR(EINVAL);
        }
    }

    ਜੇ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ਜੇ (po)
        *po   = o;
    ਜੇ (ptgt)
        *ptgt = tgt;
    ਜੇ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->ਵਿੱਥ : ਨਿਰਾ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ AVRational double_ਮੰਜ਼ਿਲ_rational(ਦੁੱਗਣਾ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ਜੇ ((!r.ਅੰਕ || !r.den) && d)
         r = av_d2q(d, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
     ਵਾਪਸ r;
}

ਸਥਿਰ ਪੂਰਨ read_ਸੰਖਿਆ(ਅਚਲ AVOption *o, ਅਚਲ ਖਾਲੀ *dst, ਦੁੱਗਣਾ *ਅੰਕ, ਪੂਰਨ *den, int64_t *intnum)
{
    ਚੋਣ (TYPE_ਅਧਾਰ(o->type)) {
    ਹਾਲਤ AV_OPT_TYPE_FLAGS:
        *intnum = *(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ*)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ਗਿਣਤੀ AVPixelFormat *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ਗਿਣਤੀ AVSampleFormat *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
    ਹਾਲਤ AV_OPT_TYPE_INT:
        *intnum = *(ਪੂਰਨ *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_UINT:
        *intnum = *(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_DURATION:
    ਹਾਲਤ AV_OPT_TYPE_INT64:
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
        *ਅੰਕ = *(ਦਸ਼ਮਲਵ *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
        *ਅੰਕ = *(ਦੁੱਗਣਾ *)dst;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->ਅੰਕ;
        *den    = ((AVRational *)dst)->den;
        ਵਾਪਸ 0;
    ਹਾਲਤ AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ਵਾਪਸ 0;
    }
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਪੂਰਨ write_ਸੰਖਿਆ(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਖਾਲੀ *dst,
                        ਦੁੱਗਣਾ ਅੰਕ, ਪੂਰਨ den, int64_t intnum,
                        ਪੂਰਨ ignore_range)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਅਚਲ ਗਿਣਤੀ AVOptionType type = TYPE_ਅਧਾਰ(o->type);

    ਜੇ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < ਅੰਕ * intnum || o->min * den > ਅੰਕ * intnum)) {
        ਅੰਕ = den ? ਅੰਕ * intnum / den : (ਅੰਕ && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               ਅੰਕ, o->name, o->min, o->max);
        ਵਾਪਸ AVERROR(ERANGE);
    }
    ਜੇ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        ਦੁੱਗਣਾ d = ਅੰਕ*intnum/den;
        ਜੇ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   ਅੰਕ*intnum/den, o->name);
            ਵਾਪਸ AVERROR(ERANGE);
        }
    }

    ਜੇ (!dst)
        ਵਾਪਸ 0;

    ਚੋਣ (type) {
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
        *(ਗਿਣਤੀ AVPixelFormat *)dst = llrint(ਅੰਕ / den) * intnum;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
        *(ਗਿਣਤੀ AVSampleFormat *)dst = llrint(ਅੰਕ / den) * intnum;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
    ਹਾਲਤ AV_OPT_TYPE_FLAGS:
    ਹਾਲਤ AV_OPT_TYPE_INT:
    ਹਾਲਤ AV_OPT_TYPE_UINT:
        *(ਪੂਰਨ *)dst = llrint(ਅੰਕ / den) * intnum;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_DURATION:
    ਹਾਲਤ AV_OPT_TYPE_INT64:{
        ਦੁੱਗਣਾ d = ਅੰਕ / den;
        ਜੇ (intnum == 1 && d == (ਦੁੱਗਣਾ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ਨਹੀਂਤਾਂ
            *(int64_t *)dst = llrint(d) * intnum;
        ਰੋਕੋ;}
    ਹਾਲਤ AV_OPT_TYPE_UINT64:{
        ਦੁੱਗਣਾ d = ਅੰਕ / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ਜੇ (intnum == 1 && d == (ਦੁੱਗਣਾ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ਨਹੀਂਤਾਂ ਜੇ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ਨਹੀਂਤਾਂ {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        ਰੋਕੋ;}
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
        *(ਦਸ਼ਮਲਵ *)dst = ਅੰਕ * intnum / den;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
        *(ਦੁੱਗਣਾ    *)dst = ਅੰਕ * intnum / den;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
        ਜੇ ((ਪੂਰਨ) ਅੰਕ == ਅੰਕ)
            *(AVRational *)dst = (AVRational) { ਅੰਕ *intnum, den };
        ਨਹੀਂਤਾਂ
            *(AVRational *)dst = double_ਮੰਜ਼ਿਲ_rational(ਅੰਕ * intnum / den);
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ hexchar2int(ਅੱਖਰ c) {
    ਜੇ (c >= '0' && c <= '9')
        ਵਾਪਸ c - '0';
    ਜੇ (c >= 'a' && c <= 'f')
        ਵਾਪਸ c - 'a' + 10;
    ਜੇ (c >= 'A' && c <= 'F')
        ਵਾਪਸ c - 'A' + 10;
    ਵਾਪਸ -1;
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_ਦੁਆਧਾਰੀ(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t **dst)
{
    ਪੂਰਨ *lendst;
    uint8_t *bin, *ptr;
    ਪੂਰਨ len;

    ਜੇ (dst) {
        lendst = (ਪੂਰਨ *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ਜੇ (!val || !(len = ਲੜੀ_ਲੰਬਾਈ(val)))
        ਵਾਪਸ 0;

    ਜੇ (len & 1)
        ਵਾਪਸ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ਜੇ (!ptr)
        ਵਾਪਸ AVERROR(ENOMEM);
    ਜਦੋਂ (*val) {
        ਪੂਰਨ a = hexchar2int(*val++);
        ਪੂਰਨ b = hexchar2int(*val++);
        ਜੇ (a < 0 || b < 0) {
            av_free(bin);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ਜੇ (dst) {
        *dst    = bin;
        *lendst = len;
    } ਨਹੀਂਤਾਂ {
        av_free(bin);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t **dst)
{
    ਜੇ (!dst)
        ਵਾਪਸ 0;
    av_freep(dst);
    ਜੇ (!val)
        ਵਾਪਸ 0;
    *dst = av_strdup(val);
    ਵਾਪਸ *dst ? 0 : AVERROR(ENOMEM);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_ਸੰਖਿਆ(ਖਾਲੀ *obj, ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, ਖਾਲੀ *dst)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਅਚਲ ਗਿਣਤੀ AVOptionType type = TYPE_ਅਧਾਰ(o->type);
    ਪੂਰਨ ret = 0;

    ਜੇ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_ਦਰ) {
        ਪੂਰਨ ਅੰਕ, den;
        ਅੱਖਰ c;
        ਜੇ (ਲੜੀ_ਤੋਂ_ਪੜ੍ਹੋ(val, "%d%*1[:/]%d%c", &ਅੰਕ, &den, &c) == 2) {
            ਜੇ ((ret = write_ਸੰਖਿਆ(obj, o, dst, 1, den, ਅੰਕ, 0)) >= 0)
                ਵਾਪਸ ret;
            ret = 0;
        }
    }

    ਲਈ (;;) {
        ਪੂਰਨ i = 0;
        ਅੱਖਰ buf[256];
        ਪੂਰਨ cmd = 0;
        ਦੁੱਗਣਾ d;
        int64_t intnum = 1;

        ਜੇ (type == AV_OPT_TYPE_FLAGS) {
            ਜੇ (*val == '+' || *val == '-')
                cmd = *(val++);
            ਲਈ (; i < ਆਕਾਰ(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            ਪੂਰਨ res;
            ਪੂਰਨ ci = 0;
            ਦੁੱਗਣਾ const_ਮੁੱਲਾਂ[64];
            ਅਚਲ ਅੱਖਰ * const_ਨਾਂ[64];
            ਪੂਰਨ ਖੋਜ_flags = (o->flags & AV_OPT_FLAG_ਬੱਚਾ_CONSTS) ? AV_OPT_ਖੋਜ_CHILDREN : 0;
            ਅਚਲ AVOption *o_named = av_opt_ਲੱਭੋ(ਨਿਸ਼ਾਨਾ_obj, i ? buf : val, o->unit, 0, ਖੋਜ_flags);
            ਜੇ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ਜੇ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ਨਹੀਂਤਾਂ {
                ਜੇ (o->unit) {
                    ਲਈ (o_named = ਨਿਰਾ; o_named = av_opt_ਅਗਲਾ(ਨਿਸ਼ਾਨਾ_obj, o_named); ) {
                        ਜੇ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ਜੇ (ci + 6 >= FF_ARRAY_ELEMS(const_ਮੁੱਲਾਂ)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ਵਾਪਸ AVERROR_PATCHWELCOME;
                            }
                            const_ਨਾਂ [ci  ] = o_named->name;
                            const_ਮੁੱਲਾਂ[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_ਨਾਂ [ci  ] = "default";
                const_ਮੁੱਲਾਂ[ci++] = DEFAULT_NUMVAL(o);
                const_ਨਾਂ [ci  ] = "max";
                const_ਮੁੱਲਾਂ[ci++] = o->max;
                const_ਨਾਂ [ci  ] = "min";
                const_ਮੁੱਲਾਂ[ci++] = o->min;
                const_ਨਾਂ [ci  ] = "none";
                const_ਮੁੱਲਾਂ[ci++] = 0;
                const_ਨਾਂ [ci  ] = "all";
                const_ਮੁੱਲਾਂ[ci++] = ~0;
                const_ਨਾਂ [ci] = ਨਿਰਾ;
                const_ਮੁੱਲਾਂ[ci] = 0;

                res = av_ਵਿਅੰਜਕ_parse_and_eval(&d, i ? buf : val, const_ਨਾਂ,
                                            const_ਮੁੱਲਾਂ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, 0, obj);
                ਜੇ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ਵਾਪਸ res;
                }
            }
        }
        ਜੇ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ*)dst;
            ਜੇ (cmd == '+')
                d = intnum | (int64_t)d;
            ਨਹੀਂਤਾਂ ਜੇ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ਜੇ ((ret = write_ਸੰਖਿਆ(obj, o, dst, d, 1, 1, 0)) < 0)
            ਵਾਪਸ ret;
        val += i;
        ਜੇ (!i || !*val)
            ਵਾਪਸ 0;
    }
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_image_ਮਾਪ(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, ਪੂਰਨ *dst)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਪੂਰਨ tmp[2];
    ਪੂਰਨ ret;

    ਜੇ (!val || !strcmp(val, "none")) {
        ਜੇ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ਵਾਪਸ 0;
    }
    ret = av_parse_video_ਮਾਪ(&tmp[0], &tmp[1], val);
    ਜੇ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ਵਾਪਸ ret;
    }
    ਜੇ (dst)
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, tmp, ਆਕਾਰ(tmp));
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_video_ਦਰ(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, AVRational *dst)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    AVRational tmp;
    ਪੂਰਨ ret = av_parse_video_ਦਰ(&tmp, val);
    ਜੇ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ਜੇ (dst)
        *dst = tmp;
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_color(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t *dst)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਜੇ (!val) {
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ਜੇ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ਵਾਪਸ ret;
        }
        ਜੇ (dst)
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, tmp, ਆਕਾਰ(tmp));
        ਵਾਪਸ ret;
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *get_bool_name(ਪੂਰਨ val)
{
    ਜੇ (val < 0)
        ਵਾਪਸ "auto";
    ਵਾਪਸ val ? "true" : "false";
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_bool(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, ਪੂਰਨ *dst)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਪੂਰਨ n;

    ਜੇ (!val)
        ਵਾਪਸ 0;

    ਜੇ (!strcmp(val, "auto")) {
        n = -1;
    } ਨਹੀਂਤਾਂ ਜੇ (av_ਮੇਲ_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ਨਹੀਂਤਾਂ ਜੇ (av_ਮੇਲ_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ਨਹੀਂਤਾਂ {
        ਅੱਖਰ *ਸਿਰਾ = ਨਿਰਾ;
        n = strtol(val, &ਸਿਰਾ, 10);
        ਜੇ (val + ਲੜੀ_ਲੰਬਾਈ(val) != ਸਿਰਾ)
            ਜਾਓ fail;
    }

    ਜੇ (n < o->min || n > o->max)
        ਜਾਓ fail;

    ਜੇ (dst)
    *dst = n;
    ਵਾਪਸ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_fmt(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t *dst,
                          ਪੂਰਨ fmt_nb, ਪੂਰਨ ((*get_fmt)(ਅਚਲ ਅੱਖਰ *)), ਅਚਲ ਅੱਖਰ *desc,
                          ਗਿਣਤੀ AVOptionType type)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਪੂਰਨ fmt, min, max;

    ਜੇ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ਨਹੀਂਤਾਂ {
        fmt = get_fmt(val);
        ਜੇ (fmt == -1) {
            ਅੱਖਰ *ਪੂਛ;
            fmt = strtol(val, &ਪੂਛ, 0);
            ਜੇ (*ਪੂਛ || (ਬਿਨਾਨਿਸ਼ਾਨੀ)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ਵਾਪਸ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ਜੇ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ਜੇ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ਵਾਪਸ AVERROR(ERANGE);
    }

    ਜੇ (dst)
    ਚੋਣ (type) {
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:  *(ਗਿਣਤੀ AVPixelFormat *)dst = fmt; ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT: *(ਗਿਣਤੀ AVSampleFormat*)dst = fmt; ਰੋਕੋ;
    ਮੂਲ: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ get_pix_fmt(ਅਚਲ ਅੱਖਰ *name)
{
    ਵਾਪਸ av_get_pix_fmt(name);
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_pixel_fmt(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t *dst)
{
    ਵਾਪਸ ਸੈੱਟ_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ਸਥਿਰ ਪੂਰਨ get_sample_fmt(ਅਚਲ ਅੱਖਰ *name)
{
    ਵਾਪਸ av_get_sample_fmt(name);
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_sample_fmt(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t *dst)
{
    ਵਾਪਸ ਸੈੱਟ_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_dict(ਖਾਲੀ *obj, ਅਚਲ AVOption *o, ਅਚਲ ਅੱਖਰ *val, uint8_t **dst)
{
    AVDictionary *options = ਨਿਰਾ;

    ਜੇ (val) {
        ਪੂਰਨ ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ਜੇ (ret < 0) {
            av_dict_free(&options);
            ਵਾਪਸ ret;
        }
    }

    ਜੇ (!dst) {
        av_dict_free(&options);
        ਵਾਪਸ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_string_channel_layout(ਖਾਲੀ *obj, ਅਚਲ AVOption *o,
                                     ਅਚਲ ਅੱਖਰ *val, ਖਾਲੀ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    ਪੂਰਨ ret;
    ਜੇ (dst)
    av_channel_layout_uninit(channel_layout);
    ਨਹੀਂਤਾਂ
        channel_layout = &tmp;
    ਜੇ (!val)
        ਵਾਪਸ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ਜੇ (!dst)
        av_channel_layout_uninit(channel_layout);
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opt_ਸੈੱਟ_elem(ਖਾਲੀ *obj, ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj, ਅਚਲ AVOption *o,
                        ਅਚਲ ਅੱਖਰ *val, ਖਾਲੀ *dst)
{
    ਖਾਲੀ *logctx = dst ? obj : ਨਿਰਾ;
    ਅਚਲ ਗਿਣਤੀ AVOptionType type = TYPE_ਅਧਾਰ(o->type);
    ਪੂਰਨ ret;

    ਜੇ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_ਮਾਪ &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ਵਾਪਸ AVERROR(EINVAL);

    ਚੋਣ (type) {
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
        ਵਾਪਸ ਸੈੱਟ_string_bool(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_STRING:
        ਵਾਪਸ ਸੈੱਟ_string(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_ਦੁਆਧਾਰੀ:
        ਵਾਪਸ ਸੈੱਟ_string_ਦੁਆਧਾਰੀ(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_FLAGS:
    ਹਾਲਤ AV_OPT_TYPE_INT:
    ਹਾਲਤ AV_OPT_TYPE_UINT:
    ਹਾਲਤ AV_OPT_TYPE_INT64:
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
        ਵਾਪਸ ਸੈੱਟ_string_ਸੰਖਿਆ(obj, ਨਿਸ਼ਾਨਾ_obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
        ਵਾਪਸ ਸੈੱਟ_string_image_ਮਾਪ(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ: {
        AVRational tmp;
        ret = ਸੈੱਟ_string_video_ਦਰ(obj, o, val, &tmp);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
        ਵਾਪਸ write_ਸੰਖਿਆ(obj, o, dst, 1, tmp.den, tmp.ਅੰਕ, 0);
    }
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
        ਵਾਪਸ ਸੈੱਟ_string_pixel_fmt(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
        ਵਾਪਸ ਸੈੱਟ_string_sample_fmt(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ਜੇ (val) {
                ਜੇ ((ret = av_parse_ਸਮਾਂ(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ਵਾਪਸ ret;
                }
            }
            ਜੇ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ਵਾਪਸ AVERROR(ERANGE);
            }
            ਜੇ (dst)
            *(int64_t *)dst = usecs;
            ਵਾਪਸ 0;
        }
    ਹਾਲਤ AV_OPT_TYPE_COLOR:
        ਵਾਪਸ ਸੈੱਟ_string_color(obj, o, val, dst);
    ਹਾਲਤ AV_OPT_TYPE_CHLAYOUT:
        ret = ਸੈੱਟ_string_channel_layout(obj, o, val, dst);
        ਜੇ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ਵਾਪਸ ret;
    ਹਾਲਤ AV_OPT_TYPE_DICT:
        ਵਾਪਸ ਸੈੱਟ_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ ਪੂਰਨ opt_ਸੈੱਟ_array(ਖਾਲੀ *obj, ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj, ਅਚਲ AVOption *o,
                         ਅਚਲ ਅੱਖਰ *val, ਖਾਲੀ *dst)
{
    ਅਚਲ AVOptionArrayDef *arr = o->default_val.arr;
    ਅਚਲ size_t      elem_ਮਾਪ = opt_type_desc[TYPE_ਅਧਾਰ(o->type)].ਮਾਪ;
    ਅਚਲ uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ਨਿਰਾ;

    ਖਾਲੀ      *logctx = dst ? obj : ਨਿਰਾ;
    ਖਾਲੀ       *elems = ਨਿਰਾ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ nb_elems = 0;
    ਪੂਰਨ ret;

    ਜੇ (val && *val) {
        str = av_malloc(ਲੜੀ_ਲੰਬਾਈ(val) + 1);
        ਜੇ (!str)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ਜਦੋਂ (val && *val) {
        uint8_t *p = str;
        ਖਾਲੀ *tmp;

        ਜੇ (arr && arr->ਮਾਪ_max && nb_elems >= arr->ਮਾਪ_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->ਮਾਪ_max, o->name);
            ret = AVERROR(EINVAL);
            ਜਾਓ fail;
        }

        ਲਈ (; *val; val++, p++) {
            ਜੇ (*val == '\\' && val[1])
                val++;
            ਨਹੀਂਤਾਂ ਜੇ (*val == sep) {
                val++;
                ਰੋਕੋ;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_ਮਾਪ);
        ਜੇ (!tmp) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_ਮਾਪ);

        ret = opt_ਸੈੱਟ_elem(obj, ਨਿਸ਼ਾਨਾ_obj, o, str, tmp);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
        nb_elems++;
    }
    av_freep(&str);

    ਜੇ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ਜੇ (arr && nb_elems < arr->ਮਾਪ_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->ਮਾਪ_min, o->name);
        ret = AVERROR(EINVAL);
        ਜਾਓ fail;
    }

    ਜੇ (dst) {
    *((ਖਾਲੀ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ਨਹੀਂਤਾਂ
        opt_free_array(o, &elems, &nb_elems);

    ਵਾਪਸ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_ਸੈੱਟ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *val, ਪੂਰਨ ਖੋਜ_flags)
{
    ਖਾਲੀ *dst, *ਨਿਸ਼ਾਨਾ_obj;
    ਅਚਲ AVOption *o;
    ਪੂਰਨ ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, 0, &ਨਿਸ਼ਾਨਾ_obj, &o, &dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਵਾਪਸ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_ਸੈੱਟ_array : opt_ਸੈੱਟ_elem)(obj, ਨਿਸ਼ਾਨਾ_obj, o, val, dst);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OPT_EVAL_ਸੰਖਿਆ(name, opttype, vartype)                         \
ਪੂਰਨ av_opt_eval_ ## name(ਖਾਲੀ *obj, ਅਚਲ AVOption *o,                  \
                         ਅਚਲ ਅੱਖਰ *val, vartype *name ## ਬਾਹਰਲਾ_3)        \
{                                                                       \
    ਜੇ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ਵਾਪਸ AVERROR(EINVAL);                                         \
    ਵਾਪਸ ਸੈੱਟ_string_ਸੰਖਿਆ(obj, obj, o, val, name ## ਬਾਹਰਲਾ_3);           \
}

OPT_EVAL_ਸੰਖਿਆ(flags,  AV_OPT_TYPE_FLAGS,    ਪੂਰਨ)
OPT_EVAL_ਸੰਖਿਆ(ਪੂਰਨ,    AV_OPT_TYPE_INT,      ਪੂਰਨ)
OPT_EVAL_ਸੰਖਿਆ(uint,   AV_OPT_TYPE_UINT,     ਬਿਨਾਨਿਸ਼ਾਨੀ)
OPT_EVAL_ਸੰਖਿਆ(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_ਸੰਖਿਆ(ਦਸ਼ਮਲਵ,  AV_OPT_TYPE_FLOAT,    ਦਸ਼ਮਲਵ)
OPT_EVAL_ਸੰਖਿਆ(ਦੁੱਗਣਾ, AV_OPT_TYPE_DOUBLE,   ਦੁੱਗਣਾ)
OPT_EVAL_ਸੰਖਿਆ(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_ਸੰਖਿਆ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਦੁੱਗਣਾ ਅੰਕ, ਪੂਰਨ den, int64_t intnum,
                      ਪੂਰਨ ਖੋਜ_flags, ਪੂਰਨ require_type)
{
    ਖਾਲੀ *dst;
    ਅਚਲ AVOption *o;
    ਪੂਰਨ ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, require_type, ਨਿਰਾ, &o, &dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ਜੇ (dst)
        ret = write_ਸੰਖਿਆ(obj, o, dst, ਅੰਕ, den, intnum, 0);

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_int(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, int64_t val, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ ਸੈੱਟ_ਸੰਖਿਆ(obj, name, 1, 1, val, ਖੋਜ_flags, 0);
}

ਪੂਰਨ av_opt_ਸੈੱਟ_double(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਦੁੱਗਣਾ val, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ ਸੈੱਟ_ਸੰਖਿਆ(obj, name, val, 1, 1, ਖੋਜ_flags, 0);
}

ਪੂਰਨ av_opt_ਸੈੱਟ_q(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, AVRational val, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ ਸੈੱਟ_ਸੰਖਿਆ(obj, name, val.ਅੰਕ, val.den, 1, ਖੋਜ_flags, 0);
}

ਪੂਰਨ av_opt_ਸੈੱਟ_bin(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ uint8_t *val, ਪੂਰਨ len, ਪੂਰਨ ਖੋਜ_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    ਪੂਰਨ *lendst;
    ਪੂਰਨ ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, AV_OPT_TYPE_ਦੁਆਧਾਰੀ,
                       ਨਿਰਾ, ਨਿਰਾ, (ਖਾਲੀ**)&dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (dst) {
    ptr = len ? av_malloc(len) : ਨਿਰਾ;
    ਜੇ (len && !ptr)
        ਵਾਪਸ AVERROR(ENOMEM);

    lendst = (ਪੂਰਨ *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ਜੇ (len)
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(ptr, val, len);
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_image_ਮਾਪ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਖੋਜ_flags)
{
    ਅਚਲ AVOption *o;
    ਖਾਲੀ *logctx;
    ਪੂਰਨ *dst;
    ਪੂਰਨ ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, AV_OPT_TYPE_IMAGE_ਮਾਪ,
                       ਨਿਰਾ, &o, (ਖਾਲੀ**)&dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    logctx = dst ? obj : ਨਿਰਾ;

    ਜੇ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_video_ਦਰ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, AVRational val, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ ਸੈੱਟ_ਸੰਖਿਆ(obj, name, val.ਅੰਕ, val.den, 1, ਖੋਜ_flags, AV_OPT_TYPE_VIDEO_ਦਰ);
}

ਸਥਿਰ ਪੂਰਨ ਸੈੱਟ_format(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ fmt, ਪੂਰਨ ਖੋਜ_flags,
                      ਗਿਣਤੀ AVOptionType type, ਅਚਲ ਅੱਖਰ *desc, ਪੂਰਨ nb_fmts)
{
    ਅਚਲ AVOption *o;
    ਖਾਲੀ *logctx;
    ਪੂਰਨ *dst;
    ਪੂਰਨ min, max, ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, type, ਨਿਰਾ, &o, (ਖਾਲੀ**)&dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    logctx = dst ? obj : ਨਿਰਾ;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ਜੇ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ਵਾਪਸ AVERROR(ERANGE);
    }
    ਜੇ (dst)
    *dst = fmt;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_pixel_fmt(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਗਿਣਤੀ AVPixelFormat fmt, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ ਸੈੱਟ_format(obj, name, fmt, ਖੋਜ_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

ਪੂਰਨ av_opt_ਸੈੱਟ_sample_fmt(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਗਿਣਤੀ AVSampleFormat fmt, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ ਸੈੱਟ_format(obj, name, fmt, ਖੋਜ_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

ਪੂਰਨ av_opt_ਸੈੱਟ_dict_val(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ AVDictionary *val,
                        ਪੂਰਨ ਖੋਜ_flags)
{
    AVDictionary **dst;
    ਪੂਰਨ ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, AV_OPT_TYPE_DICT, ਨਿਰਾ, ਨਿਰਾ,
                       (ਖਾਲੀ**)&dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_chlayout(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name,
                        ਅਚਲ AVChannelLayout *channel_layout,
                        ਪੂਰਨ ਖੋਜ_flags)
{
    AVChannelLayout *dst;
    ਪੂਰਨ ret;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, AV_OPT_TYPE_CHLAYOUT, ਨਿਰਾ, ਨਿਰਾ,
                       (ਖਾਲੀ**)&dst);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਖਾਲੀ format_duration(ਅੱਖਰ *buf, size_t ਮਾਪ, int64_t d)
{
    ਅੱਖਰ *e;

    av_assert0(ਮਾਪ >= 25);
    ਜੇ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        ਮਾਪ--;
        d = -d;
    }
    ਜੇ (d == INT64_MAX)
        snprintf(buf, ਮਾਪ, "INT64_MAX");
    ਨਹੀਂਤਾਂ ਜੇ (d == INT64_MIN)
        snprintf(buf, ਮਾਪ, "INT64_MIN");
    ਨਹੀਂਤਾਂ ਜੇ (d > (int64_t)3600*1000000)
        snprintf(buf, ਮਾਪ, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (ਪੂਰਨ)((d / 60000000) % 60),
                 (ਪੂਰਨ)((d / 1000000) % 60),
                 (ਪੂਰਨ)(d % 1000000));
    ਨਹੀਂਤਾਂ ਜੇ (d > 60*1000000)
        snprintf(buf, ਮਾਪ, "%d:%02d.%06d",
                 (ਪੂਰਨ)(d / 60000000),
                 (ਪੂਰਨ)((d / 1000000) % 60),
                 (ਪੂਰਨ)(d % 1000000));
    ਨਹੀਂਤਾਂ
        snprintf(buf, ਮਾਪ, "%d.%06d",
                 (ਪੂਰਨ)(d / 1000000),
                 (ਪੂਰਨ)(d % 1000000));
    e = buf + ਲੜੀ_ਲੰਬਾਈ(buf);
    ਜਦੋਂ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ਜੇ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ਸਥਿਰ ਪੂਰਨ opt_get_elem(ਅਚਲ AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ਅਚਲ ਖਾਲੀ *dst, ਪੂਰਨ ਖੋਜ_flags)
{
    ਪੂਰਨ ret;

    ਚੋਣ (TYPE_ਅਧਾਰ(o->type)) {
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(ਪੂਰਨ *)dst));
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(ਪੂਰਨ *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(ਪੂਰਨ *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(ਬਿਨਾਨਿਸ਼ਾਨੀ *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(ਦਸ਼ਮਲਵ *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(ਦੁੱਗਣਾ *)dst);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->ਅੰਕ, ((AVRational *)dst)->den);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_STRING:
        ਜੇ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ਨਹੀਂਤਾਂ ਜੇ (ਖੋਜ_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ਨਿਰਾ;
            ਵਾਪਸ 0;
        } ਨਹੀਂਤਾਂ {
            *pbuf = av_strdup("");
        }
        ਵਾਪਸ *pbuf ? 0 : AVERROR(ENOMEM);
    ਹਾਲਤ AV_OPT_TYPE_ਦੁਆਧਾਰੀ: {
        ਅਚਲ uint8_t *bin;
        ਪੂਰਨ len;

        ਜੇ (!*(uint8_t **)dst && (ਖੋਜ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ਨਿਰਾ;
            ਵਾਪਸ 0;
        }
        len = *(ਪੂਰਨ *)(((uint8_t *)dst) + ਆਕਾਰ(uint8_t *));
        ਜੇ ((uint64_t)len * 2 + 1 > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
            ਵਾਪਸ AVERROR(EINVAL);
        ਜੇ (!(*pbuf = av_malloc(len * 2 + 1)))
            ਵਾਪਸ AVERROR(ENOMEM);
        ਜੇ (!len) {
            *pbuf[0] = '\0';
            ਵਾਪਸ 0;
        }
        bin = *(uint8_t **)dst;
        ਲਈ (ਪੂਰਨ i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ਵਾਪਸ 0;
    }
    ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((ਪੂਰਨ *)dst)[0], ((ਪੂਰਨ *)dst)[1]);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ਅੱਖਰ *)av_x_if_null(av_get_pix_fmt_name(*(ਗਿਣਤੀ AVPixelFormat *)dst), "none"));
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ਅੱਖਰ *)av_x_if_null(av_get_sample_fmt_name(*(ਗਿਣਤੀ AVSampleFormat *)dst), "none"));
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = ਲੜੀ_ਲੰਬਾਈ(*pbuf); // no overflow possible, checked by an assert
        ਰੋਕੋ;
    }
    ਹਾਲਤ AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (ਪੂਰਨ)((uint8_t *)dst)[0], (ਪੂਰਨ)((uint8_t *)dst)[1],
                       (ਪੂਰਨ)((uint8_t *)dst)[2], (ਪੂਰਨ)((uint8_t *)dst)[3]);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_DICT:
        ਜੇ (!*(AVDictionary **)dst && (ਖੋਜ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ਨਿਰਾ;
            ਵਾਪਸ 0;
        }
        ਵਾਪਸ av_dict_get_string(*(AVDictionary **)dst, (ਅੱਖਰ **)pbuf, '=', ':');
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ opt_get_array(ਅਚਲ AVOption *o, ਖਾਲੀ *dst, uint8_t **ਬਾਹਰਲਾ_val)
{
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਗਿਣਤੀ_2 = *opt_array_pcount(dst);
    ਅਚਲ uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ਨਿਰਾ;
    size_t   str_len = 0;
    ਪੂਰਨ ret;

    *ਬਾਹਰਲਾ_val = ਨਿਰਾ;

    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < ਗਿਣਤੀ_2; i++) {
        uint8_t buf[128], *ਬਾਹਰਲਾ = buf;
        size_t ਬਾਹਰਲਾ_len;

        ret = opt_get_elem(o, &ਬਾਹਰਲਾ, ਆਕਾਰ(buf),
                           opt_array_pelem(o, *(ਖਾਲੀ **)dst, i), 0);
        ਜੇ (ret < 0)
            ਜਾਓ fail;

        ਬਾਹਰਲਾ_len = ਲੜੀ_ਲੰਬਾਈ(ਬਾਹਰਲਾ);
        ਜੇ (ਬਾਹਰਲਾ_len > SIZE_MAX / 2 - !!i ||
            !!i + ਬਾਹਰਲਾ_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            ਜਾਓ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + ਬਾਹਰਲਾ_len * 2 + !!i);
        ਜੇ (ret < 0)
            ਜਾਓ fail;

        // add separator if needed
        ਜੇ (i)
            str[str_len++] = sep;

        // escape the element
        ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ j = 0; j < ਬਾਹਰਲਾ_len; j++) {
            uint8_t val = ਬਾਹਰਲਾ[j];
            ਜੇ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ਜੇ (ਬਾਹਰਲਾ != buf)
            av_freep(&ਬਾਹਰਲਾ);
        ਜੇ (ret < 0) {
            av_freep(&str);
            ਵਾਪਸ ret;
        }
    }

    *ਬਾਹਰਲਾ_val = str;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, uint8_t **ਬਾਹਰਲਾ_val)
{
    ਖਾਲੀ *dst, *ਨਿਸ਼ਾਨਾ_obj;
    ਅਚਲ AVOption *o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    uint8_t *ਬਾਹਰਲਾ, buf[128];
    ਪੂਰਨ ret;

    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj || (o->ਵਿੱਥ<=0 && o->type != AV_OPT_TYPE_CONST))
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;

    ਜੇ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)ਨਿਸ਼ਾਨਾ_obj + o->ਵਿੱਥ;

    ਜੇ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, ਬਾਹਰਲਾ_val);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
        ਜੇ (!*ਬਾਹਰਲਾ_val && !(ਖੋਜ_flags & AV_OPT_ALLOW_NULL)) {
            *ਬਾਹਰਲਾ_val = av_strdup("");
            ਜੇ (!*ਬਾਹਰਲਾ_val)
               ਵਾਪਸ AVERROR(ENOMEM);
        }
        ਵਾਪਸ 0;
    }

    buf[0] = 0;
    ਬਾਹਰਲਾ = buf;
    ret = opt_get_elem(o, &ਬਾਹਰਲਾ, ਆਕਾਰ(buf), dst, ਖੋਜ_flags);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ਜੇ (ਬਾਹਰਲਾ != buf) {
        *ਬਾਹਰਲਾ_val = ਬਾਹਰਲਾ;
        ਵਾਪਸ 0;
    }

    ਜੇ (ret >= ਆਕਾਰ(buf))
        ਵਾਪਸ AVERROR(EINVAL);
    *ਬਾਹਰਲਾ_val = av_strdup(ਬਾਹਰਲਾ);
    ਵਾਪਸ *ਬਾਹਰਲਾ_val ? 0 : AVERROR(ENOMEM);
}

ਸਥਿਰ ਪੂਰਨ get_ਸੰਖਿਆ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਦੁੱਗਣਾ *ਅੰਕ, ਪੂਰਨ *den, int64_t *intnum,
                      ਪੂਰਨ ਖੋਜ_flags)
{
    ਖਾਲੀ *dst, *ਨਿਸ਼ਾਨਾ_obj;
    ਅਚਲ AVOption *o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ਵਾਪਸ AVERROR(EINVAL);

    dst = ((uint8_t *)ਨਿਸ਼ਾਨਾ_obj) + o->ਵਿੱਥ;

    ਵਾਪਸ read_ਸੰਖਿਆ(o, dst, ਅੰਕ, den, intnum);
}

ਪੂਰਨ av_opt_get_int(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, int64_t *ਬਾਹਰਲਾ_val)
{
    int64_t intnum = 1;
    ਦੁੱਗਣਾ ਅੰਕ = 1;
    ਪੂਰਨ ret, den = 1;

    ਜੇ ((ret = get_ਸੰਖਿਆ(obj, name, &ਅੰਕ, &den, &intnum, ਖੋਜ_flags)) < 0)
        ਵਾਪਸ ret;
    ਜੇ (ਅੰਕ == den)
        *ਬਾਹਰਲਾ_val = intnum;
    ਨਹੀਂਤਾਂ
        *ਬਾਹਰਲਾ_val = ਅੰਕ * intnum / den;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_double(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, ਦੁੱਗਣਾ *ਬਾਹਰਲਾ_val)
{
    int64_t intnum = 1;
    ਦੁੱਗਣਾ ਅੰਕ = 1;
    ਪੂਰਨ ret, den = 1;

    ਜੇ ((ret = get_ਸੰਖਿਆ(obj, name, &ਅੰਕ, &den, &intnum, ਖੋਜ_flags)) < 0)
        ਵਾਪਸ ret;
    *ਬਾਹਰਲਾ_val = ਅੰਕ * intnum / den;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_q(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, AVRational *ਬਾਹਰਲਾ_val)
{
    int64_t intnum = 1;
    ਦੁੱਗਣਾ ਅੰਕ = 1;
    ਪੂਰਨ ret, den = 1;

    ਜੇ ((ret = get_ਸੰਖਿਆ(obj, name, &ਅੰਕ, &den, &intnum, ਖੋਜ_flags)) < 0)
        ਵਾਪਸ ret;

    ਜੇ (ਅੰਕ == 1.0 && (ਪੂਰਨ)intnum == intnum)
        *ਬਾਹਰਲਾ_val = (AVRational){intnum, den};
    ਨਹੀਂਤਾਂ
        *ਬਾਹਰਲਾ_val = double_ਮੰਜ਼ਿਲ_rational(ਅੰਕ*intnum/den);
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_image_ਮਾਪ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, ਪੂਰਨ *w_ਬਾਹਰਲਾ, ਪੂਰਨ *h_ਬਾਹਰਲਾ)
{
    ਖਾਲੀ *dst, *ਨਿਸ਼ਾਨਾ_obj;
    ਅਚਲ AVOption *o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (o->type != AV_OPT_TYPE_IMAGE_ਮਾਪ) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ਨਿਸ਼ਾਨਾ_obj) + o->ਵਿੱਥ;
    ਜੇ (w_ਬਾਹਰਲਾ) *w_ਬਾਹਰਲਾ = *(ਪੂਰਨ *)dst;
    ਜੇ (h_ਬਾਹਰਲਾ) *h_ਬਾਹਰਲਾ = *((ਪੂਰਨ *)dst+1);
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_video_ਦਰ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, AVRational *ਬਾਹਰਲਾ_val)
{
    ਵਾਪਸ av_opt_get_q(obj, name, ਖੋਜ_flags, ਬਾਹਰਲਾ_val);
}

ਸਥਿਰ ਪੂਰਨ get_format(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, ਖਾਲੀ *ਬਾਹਰਲਾ_fmt,
                      ਗਿਣਤੀ AVOptionType type, ਅਚਲ ਅੱਖਰ *desc)
{
    ਖਾਲੀ *dst, *ਨਿਸ਼ਾਨਾ_obj;
    ਅਚਲ AVOption *o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ਨਿਸ਼ਾਨਾ_obj) + o->ਵਿੱਥ;
    ਜੇ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ਗਿਣਤੀ AVPixelFormat *)ਬਾਹਰਲਾ_fmt = *(ਗਿਣਤੀ AVPixelFormat *)dst;
    ਨਹੀਂਤਾਂ
        *(ਗਿਣਤੀ AVSampleFormat*)ਬਾਹਰਲਾ_fmt = *(ਗਿਣਤੀ AVSampleFormat*)dst;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_pixel_fmt(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, ਗਿਣਤੀ AVPixelFormat *ਬਾਹਰਲਾ_fmt)
{
    ਵਾਪਸ get_format(obj, name, ਖੋਜ_flags, ਬਾਹਰਲਾ_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

ਪੂਰਨ av_opt_get_sample_fmt(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, ਗਿਣਤੀ AVSampleFormat *ਬਾਹਰਲਾ_fmt)
{
    ਵਾਪਸ get_format(obj, name, ਖੋਜ_flags, ਬਾਹਰਲਾ_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

ਪੂਰਨ av_opt_get_chlayout(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, AVChannelLayout *cl)
{
    ਖਾਲੀ *dst, *ਨਿਸ਼ਾਨਾ_obj;
    ਅਚਲ AVOption *o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ਨਿਸ਼ਾਨਾ_obj) + o->ਵਿੱਥ;
    ਵਾਪਸ av_channel_layout_copy(cl, dst);
}

ਪੂਰਨ av_opt_get_dict_val(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags, AVDictionary **ਬਾਹਰਲਾ_val)
{
    ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj;
    AVDictionary *src;
    ਅਚਲ AVOption *o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);

    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (o->type != AV_OPT_TYPE_DICT)
        ਵਾਪਸ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)ਨਿਸ਼ਾਨਾ_obj) + o->ਵਿੱਥ);

    ਵਾਪਸ av_dict_copy(ਬਾਹਰਲਾ_val, src, 0);
}

ਪੂਰਨ av_opt_flag_is_ਸੈੱਟ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *ਖੇਤਰ_name, ਅਚਲ ਅੱਖਰ *flag_name)
{
    ਅਚਲ AVOption *ਖੇਤਰ = av_opt_ਲੱਭੋ(obj, ਖੇਤਰ_name, ਨਿਰਾ, 0, 0);
    ਅਚਲ AVOption *flag  = av_opt_ਲੱਭੋ(obj, flag_name,
                                        ਖੇਤਰ ? ਖੇਤਰ->unit : ਨਿਰਾ, 0, 0);
    int64_t res;

    ਜੇ (!ਖੇਤਰ || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, ਖੇਤਰ_name, 0, &res) < 0)
        ਵਾਪਸ 0;
    ਵਾਪਸ res & flag->default_val.i64;
}

ਸਥਿਰ ਖਾਲੀ log_int_ਮੁੱਲ(ਖਾਲੀ *av_log_obj, ਪੂਰਨ level, int64_t i)
{
    ਜੇ (i == ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) {
        av_log(av_log_obj, level, "INT_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ਨਹੀਂਤਾਂ ਜੇ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ਨਹੀਂਤਾਂ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ਸਥਿਰ ਖਾਲੀ log_ਮੁੱਲ(ਖਾਲੀ *av_log_obj, ਪੂਰਨ level, ਦੁੱਗਣਾ d)
{
    ਜੇ      (d == ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) {
        av_log(av_log_obj, level, "INT_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ਨਹੀਂਤਾਂ ਜੇ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == (ਦੁੱਗਣਾ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ਨਹੀਂਤਾਂ ਜੇ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ਨਹੀਂਤਾਂ ਜੇ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ਨਹੀਂਤਾਂ ਜੇ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ਨਹੀਂਤਾਂ ਜੇ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ਨਹੀਂਤਾਂ ਜੇ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ਨਹੀਂਤਾਂ {
        av_log(av_log_obj, level, "%g", d);
    }
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *get_opt_const_name(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *unit, int64_t ਮੁੱਲ)
{
    ਅਚਲ AVOption *opt = ਨਿਰਾ;

    ਜੇ (!unit)
        ਵਾਪਸ ਨਿਰਾ;
    ਜਦੋਂ ((opt = av_opt_ਅਗਲਾ(obj, opt)))
        ਜੇ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == ਮੁੱਲ)
            ਵਾਪਸ opt->name;
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅੱਖਰ *get_opt_flags_string(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *unit, int64_t ਮੁੱਲ)
{
    ਅਚਲ AVOption *opt = ਨਿਰਾ;
    ਅੱਖਰ flags[512];

    flags[0] = 0;
    ਜੇ (!unit)
        ਵਾਪਸ ਨਿਰਾ;
    ਜਦੋਂ ((opt = av_opt_ਅਗਲਾ(obj, opt))) {
        ਜੇ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & ਮੁੱਲ) {
            ਜੇ (flags[0])
                av_strlcatf(flags, ਆਕਾਰ(flags), "+");
            av_strlcatf(flags, ਆਕਾਰ(flags), "%s", opt->name);
        }
    }
    ਜੇ (flags[0])
        ਵਾਪਸ av_strdup(flags);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ log_type(ਖਾਲੀ *av_log_obj, ਅਚਲ AVOption *o,
                     ਗਿਣਤੀ AVOptionType ਮਾਪਾ_type)
{
    ਅਚਲ ਗਿਣਤੀ AVOptionType type = TYPE_ਅਧਾਰ(o->type);

    ਜੇ (o->type == AV_OPT_TYPE_CONST && (TYPE_ਅਧਾਰ(ਮਾਪਾ_type) == AV_OPT_TYPE_INT || TYPE_ਅਧਾਰ(ਮਾਪਾ_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ਨਹੀਂਤਾਂ ਜੇ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ਜੇ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ਨਹੀਂਤਾਂ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ਨਹੀਂਤਾਂ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ਸਥਿਰ ਖਾਲੀ log_default(ਖਾਲੀ *obj, ਖਾਲੀ *av_log_obj, ਅਚਲ AVOption *opt)
{
    ਜੇ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ਦੁਆਧਾਰੀ)
        ਵਾਪਸ;
    ਜੇ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_ਮਾਪ ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_ਦਰ) &&
        !opt->default_val.str)
        ਵਾਪਸ;

    ਜੇ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ਅਚਲ AVOptionArrayDef *arr = opt->default_val.arr;
        ਜੇ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ਵਾਪਸ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    ਚੋਣ (opt->type) {
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_FLAGS: {
        ਅੱਖਰ *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ਜੇ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ਨਹੀਂਤਾਂ {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        ਰੋਕੋ;
    }
    ਹਾਲਤ AV_OPT_TYPE_DURATION: {
        ਅੱਖਰ buf[25];
        format_duration(buf, ਆਕਾਰ(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        ਰੋਕੋ;
    }
    ਹਾਲਤ AV_OPT_TYPE_UINT:
    ਹਾਲਤ AV_OPT_TYPE_INT:
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
    ਹਾਲਤ AV_OPT_TYPE_INT64: {
        ਅਚਲ ਅੱਖਰ *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        ਜੇ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ਨਹੀਂਤਾਂ
            log_int_ਮੁੱਲ(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        ਰੋਕੋ;
    }
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
        log_ਮੁੱਲ(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.ਅੰਕ, q.den); }
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ਅੱਖਰ *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ਅੱਖਰ *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_COLOR:
    ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
    ਹਾਲਤ AV_OPT_TYPE_STRING:
    ਹਾਲਤ AV_OPT_TYPE_DICT:
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
    ਹਾਲਤ AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        ਰੋਕੋ;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ਸਥਿਰ ਖਾਲੀ opt_list(ਖਾਲੀ *obj, ਖਾਲੀ *av_log_obj, ਅਚਲ ਅੱਖਰ *unit,
                     ਪੂਰਨ req_flags, ਪੂਰਨ rej_flags, ਗਿਣਤੀ AVOptionType ਮਾਪਾ_type)
{
    ਅਚਲ AVOption *opt = ਨਿਰਾ;
    AVOptionRanges *r;
    ਪੂਰਨ i;

    ਜਦੋਂ ((opt = av_opt_ਅਗਲਾ(obj, opt))) {
        ਜੇ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            ਜਾਰੀ;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ਜੇ (!unit && opt->type == AV_OPT_TYPE_CONST)
            ਜਾਰੀ;
        ਨਹੀਂਤਾਂ ਜੇ (unit && opt->type != AV_OPT_TYPE_CONST)
            ਜਾਰੀ;
        ਨਹੀਂਤਾਂ ਜੇ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            ਜਾਰੀ;
        ਨਹੀਂਤਾਂ ਜੇ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ਨਹੀਂਤਾਂ
            av_log(av_log_obj, AV_LOG_INFO, "  %s%-17s ",
                   (opt->flags & AV_OPT_FLAG_FILTERING_PARAM) ? " " : "-",
                   opt->name);

        log_type(av_log_obj, opt, ਮਾਪਾ_type);

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

        ਜੇ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ਜੇ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_ਖੋਜ_FAKE_OBJ) >= 0) {
            ਚੋਣ (opt->type) {
            ਹਾਲਤ AV_OPT_TYPE_INT:
            ਹਾਲਤ AV_OPT_TYPE_UINT:
            ਹਾਲਤ AV_OPT_TYPE_INT64:
            ਹਾਲਤ AV_OPT_TYPE_UINT64:
            ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
            ਹਾਲਤ AV_OPT_TYPE_FLOAT:
            ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
                ਲਈ (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_ਮੁੱਲ(av_log_obj, AV_LOG_INFO, r->range[i]->ਮੁੱਲ_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_ਮੁੱਲ(av_log_obj, AV_LOG_INFO, r->range[i]->ਮੁੱਲ_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                ਰੋਕੋ;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        ਜੇ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

ਪੂਰਨ av_opt_show2(ਖਾਲੀ *obj, ਖਾਲੀ *av_log_obj, ਪੂਰਨ req_flags, ਪੂਰਨ rej_flags)
{
    ਜੇ (!obj)
        ਵਾਪਸ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ਨਿਰਾ, req_flags, rej_flags, -1);

    ਵਾਪਸ 0;
}

ਖਾਲੀ av_opt_ਸੈੱਟ_defaults(ਖਾਲੀ *s)
{
    av_opt_ਸੈੱਟ_defaults2(s, 0, 0);
}

ਖਾਲੀ av_opt_ਸੈੱਟ_defaults2(ਖਾਲੀ *s, ਪੂਰਨ ਨਕਾਬ_2, ਪੂਰਨ flags)
{
    ਅਚਲ AVOption *opt = ਨਿਰਾ;
    ਜਦੋਂ ((opt = av_opt_ਅਗਲਾ(s, opt))) {
        ਖਾਲੀ *dst = ((uint8_t*)s) + opt->ਵਿੱਥ;

        ਜੇ ((opt->flags & ਨਕਾਬ_2) != flags)
            ਜਾਰੀ;

        ਜੇ (opt->flags & AV_OPT_FLAG_READONLY)
            ਜਾਰੀ;

        ਜੇ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ਅਚਲ AVOptionArrayDef *arr = opt->default_val.arr;
            ਅਚਲ ਅੱਖਰ              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ਜੇ (arr && arr->def)
                opt_ਸੈੱਟ_array(s, s, opt, arr->def, dst);

            ਜਾਰੀ;
        }

        ਚੋਣ (opt->type) {
            ਹਾਲਤ AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_BOOL:
            ਹਾਲਤ AV_OPT_TYPE_FLAGS:
            ਹਾਲਤ AV_OPT_TYPE_INT:
            ਹਾਲਤ AV_OPT_TYPE_UINT:
            ਹਾਲਤ AV_OPT_TYPE_INT64:
            ਹਾਲਤ AV_OPT_TYPE_UINT64:
            ਹਾਲਤ AV_OPT_TYPE_DURATION:
            ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
            ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
                write_ਸੰਖਿਆ(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
            ਹਾਲਤ AV_OPT_TYPE_FLOAT: {
                ਦੁੱਗਣਾ val;
                val = opt->default_val.dbl;
                write_ਸੰਖਿਆ(s, opt, dst, val, 1, 1, 1);
            }
            ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
                write_ਸੰਖਿਆ(s, opt, dst, 1, val.den, val.ਅੰਕ, 1);
            }
            ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_COLOR:
                ਸੈੱਟ_string_color(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_STRING:
                ਸੈੱਟ_string(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
                ਸੈੱਟ_string_image_ਮਾਪ(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
                ਸੈੱਟ_string_video_ਦਰ(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_ਦੁਆਧਾਰੀ:
                ਸੈੱਟ_string_ਦੁਆਧਾਰੀ(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_CHLAYOUT:
                ਸੈੱਟ_string_channel_layout(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_DICT:
                ਸੈੱਟ_string_dict(s, opt, opt->default_val.str, dst);
                ਰੋਕੋ;
        ਮੂਲ:
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
ਸਥਿਰ ਪੂਰਨ parse_ਕੁੰਜੀ_ਮੁੱਲ_pair(ਖਾਲੀ *ctx, ਅਚਲ ਅੱਖਰ **buf,
                                ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ *ਜੋੜੇ_sep)
{
    ਅੱਖਰ *ਕੁੰਜੀ = av_get_token(buf, ਕੁੰਜੀ_val_sep);
    ਅੱਖਰ *val;
    ਪੂਰਨ ret;

    ਜੇ (!ਕੁੰਜੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜੇ (*ਕੁੰਜੀ && strspn(*buf, ਕੁੰਜੀ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, ਜੋੜੇ_sep);
        ਜੇ (!val) {
            av_freep(&ਕੁੰਜੀ);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
    } ਨਹੀਂਤਾਂ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", ਕੁੰਜੀ);
        av_free(ਕੁੰਜੀ);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", ਕੁੰਜੀ, val);

    ret = av_opt_ਸੈੱਟ(ctx, ਕੁੰਜੀ, val, AV_OPT_ਖੋਜ_CHILDREN);
    ਜੇ (ret == AVERROR_OPTION_NOT_ਮਿਲਿਆ)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", ਕੁੰਜੀ);

    av_free(ਕੁੰਜੀ);
    av_free(val);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_ਸੈੱਟ_options_string(ਖਾਲੀ *ctx, ਅਚਲ ਅੱਖਰ *opts,
                          ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ *ਜੋੜੇ_sep)
{
    ਪੂਰਨ ret, ਗਿਣਤੀ_2 = 0;

    ਜੇ (!opts)
        ਵਾਪਸ 0;

    ਜਦੋਂ (*opts) {
        ਜੇ ((ret = parse_ਕੁੰਜੀ_ਮੁੱਲ_pair(ctx, &opts, ਕੁੰਜੀ_val_sep, ਜੋੜੇ_sep)) < 0)
            ਵਾਪਸ ret;
        ਗਿਣਤੀ_2++;

        ਜੇ (*opts)
            opts++;
    }

    ਵਾਪਸ ਗਿਣਤੀ_2;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WHITESPACES " \n\t\r"

ਸਥਿਰ ਪੂਰਨ is_ਕੁੰਜੀ_char(ਅੱਖਰ c)
{
    ਵਾਪਸ (ਬਿਨਾਨਿਸ਼ਾਨੀ)((c | 32) - 'a') < 26 ||
           (ਬਿਨਾਨਿਸ਼ਾਨੀ)(c - '0') < 10 ||
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
ਸਥਿਰ ਪੂਰਨ get_ਕੁੰਜੀ(ਅਚਲ ਅੱਖਰ **ropts, ਅਚਲ ਅੱਖਰ *delim, ਅੱਖਰ **rkey)
{
    ਅਚਲ ਅੱਖਰ *opts = *ropts;
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_ਸ਼ੁਰੂ, *ਕੁੰਜੀ_ਸਿਰਾ;

    ਕੁੰਜੀ_ਸ਼ੁਰੂ = opts += strspn(opts, WHITESPACES);
    ਜਦੋਂ (is_ਕੁੰਜੀ_char(*opts))
        opts++;
    ਕੁੰਜੀ_ਸਿਰਾ = opts;
    opts += strspn(opts, WHITESPACES);
    ਜੇ (!*opts || !strchr(delim, *opts))
        ਵਾਪਸ AVERROR(EINVAL);
    opts++;
    ਜੇ (!(*rkey = av_malloc(ਕੁੰਜੀ_ਸਿਰਾ - ਕੁੰਜੀ_ਸ਼ੁਰੂ + 1)))
        ਵਾਪਸ AVERROR(ENOMEM);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(*rkey, ਕੁੰਜੀ_ਸ਼ੁਰੂ, ਕੁੰਜੀ_ਸਿਰਾ - ਕੁੰਜੀ_ਸ਼ੁਰੂ);
    (*rkey)[ਕੁੰਜੀ_ਸਿਰਾ - ਕੁੰਜੀ_ਸ਼ੁਰੂ] = 0;
    *ropts = opts;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_ਕੁੰਜੀ_ਮੁੱਲ(ਅਚਲ ਅੱਖਰ **ropts,
                         ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ *ਜੋੜੇ_sep,
                         ਬਿਨਾਨਿਸ਼ਾਨੀ flags,
                         ਅੱਖਰ **rkey, ਅੱਖਰ **rval)
{
    ਪੂਰਨ ret;
    ਅੱਖਰ *ਕੁੰਜੀ = ਨਿਰਾ, *val;
    ਅਚਲ ਅੱਖਰ *opts = *ropts;

    ਜੇ ((ret = get_ਕੁੰਜੀ(&opts, ਕੁੰਜੀ_val_sep, &ਕੁੰਜੀ)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_ਕੁੰਜੀ))
        ਵਾਪਸ AVERROR(EINVAL);
    ਜੇ (!(val = av_get_token(&opts, ਜੋੜੇ_sep))) {
        av_free(ਕੁੰਜੀ);
        ਵਾਪਸ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = ਕੁੰਜੀ;
    *rval  = val;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_from_string(ਖਾਲੀ *ctx, ਅਚਲ ਅੱਖਰ *opts,
                           ਅਚਲ ਅੱਖਰ *ਅਚਲ *shorthand,
                           ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ *ਜੋੜੇ_sep)
{
    ਪੂਰਨ ret, ਗਿਣਤੀ_2 = 0;
    ਅਚਲ ਅੱਖਰ *dummy_shorthand = ਨਿਰਾ;
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ;

    ਜੇ (!opts)
        ਵਾਪਸ 0;
    ਜੇ (!shorthand)
        shorthand = &dummy_shorthand;

    ਜਦੋਂ (*opts) {
        ਅੱਖਰ *parsed_ਕੁੰਜੀ, *ਮੁੱਲ;
        ret = av_opt_get_ਕੁੰਜੀ_ਮੁੱਲ(&opts, ਕੁੰਜੀ_val_sep, ਜੋੜੇ_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_ਕੁੰਜੀ : 0,
                                   &parsed_ਕੁੰਜੀ, &ਮੁੱਲ);
        ਜੇ (ret < 0) {
            ਜੇ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ਨਹੀਂਤਾਂ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ਵਾਪਸ ret;
        }
        ਜੇ (*opts)
            opts++;
        ਜੇ (parsed_ਕੁੰਜੀ) {
            ਕੁੰਜੀ = parsed_ਕੁੰਜੀ;
            ਜਦੋਂ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ਨਹੀਂਤਾਂ {
            ਕੁੰਜੀ = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", ਕੁੰਜੀ, ਮੁੱਲ);
        ਜੇ ((ret = av_opt_ਸੈੱਟ(ctx, ਕੁੰਜੀ, ਮੁੱਲ, 0)) < 0) {
            ਜੇ (ret == AVERROR_OPTION_NOT_ਮਿਲਿਆ)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", ਕੁੰਜੀ);
            av_free(ਮੁੱਲ);
            av_free(parsed_ਕੁੰਜੀ);
            ਵਾਪਸ ret;
        }

        av_free(ਮੁੱਲ);
        av_free(parsed_ਕੁੰਜੀ);
        ਗਿਣਤੀ_2++;
    }
    ਵਾਪਸ ਗਿਣਤੀ_2;
}

ਖਾਲੀ av_opt_free(ਖਾਲੀ *obj)
{
    ਅਚਲ AVOption *o = ਨਿਰਾ;
    ਜਦੋਂ ((o = av_opt_ਅਗਲਾ(obj, o))) {
        ਖਾਲੀ *pitem = (uint8_t *)obj + o->ਵਿੱਥ;

        ਜੇ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ਨਹੀਂਤਾਂ
            opt_free_elem(o->type, pitem);
    }
}

ਪੂਰਨ av_opt_ਸੈੱਟ_dict2(ਖਾਲੀ *obj, AVDictionary **options, ਪੂਰਨ ਖੋਜ_flags)
{
    ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *t = ਨਿਰਾ;
    AVDictionary    *tmp = ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਜੇ (!options)
        ਵਾਪਸ 0;

    ਜਦੋਂ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_ਸੈੱਟ(obj, t->ਕੁੰਜੀ, t->ਮੁੱਲ, ਖੋਜ_flags);
        ਜੇ (ret == AVERROR_OPTION_NOT_ਮਿਲਿਆ)
            ret = av_dict_ਸੈੱਟ(&tmp, t->ਕੁੰਜੀ, t->ਮੁੱਲ, AV_DICT_MULTIKEY);
        ਜੇ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->ਕੁੰਜੀ, t->ਮੁੱਲ);
            av_dict_free(&tmp);
            ਵਾਪਸ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_dict(ਖਾਲੀ *obj, AVDictionary **options)
{
    ਵਾਪਸ av_opt_ਸੈੱਟ_dict2(obj, options, 0);
}

ਅਚਲ AVOption *av_opt_ਲੱਭੋ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *unit,
                            ਪੂਰਨ opt_flags, ਪੂਰਨ ਖੋਜ_flags)
{
    ਵਾਪਸ av_opt_find2(obj, name, unit, opt_flags, ਖੋਜ_flags, ਨਿਰਾ);
}

ਅਚਲ AVOption *av_opt_find2(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਅਚਲ ਅੱਖਰ *unit,
                             ਪੂਰਨ opt_flags, ਪੂਰਨ ਖੋਜ_flags, ਖਾਲੀ **ਨਿਸ਼ਾਨਾ_obj)
{
    ਅਚਲ AVClass  *c;
    ਅਚਲ AVOption *o = ਨਿਰਾ;

    ਜੇ(!obj)
        ਵਾਪਸ ਨਿਰਾ;

    c= *(AVClass**)obj;

    ਜੇ (!c)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (ਖੋਜ_flags & AV_OPT_ਖੋਜ_CHILDREN) {
        ਜੇ (ਖੋਜ_flags & AV_OPT_ਖੋਜ_FAKE_OBJ) {
            ਖਾਲੀ *iter = ਨਿਰਾ;
            ਅਚਲ AVClass *ਬੱਚਾ;
            ਜਦੋਂ (ਬੱਚਾ = av_opt_ਬੱਚਾ_class_iterate(c, &iter))
                ਜੇ (o = av_opt_find2(&ਬੱਚਾ, name, unit, opt_flags, ਖੋਜ_flags, ਨਿਰਾ))
                    ਵਾਪਸ o;
        } ਨਹੀਂਤਾਂ {
            ਖਾਲੀ *ਬੱਚਾ = ਨਿਰਾ;
            ਜਦੋਂ (ਬੱਚਾ = av_opt_ਬੱਚਾ_ਅਗਲਾ(obj, ਬੱਚਾ))
                ਜੇ (o = av_opt_find2(ਬੱਚਾ, name, unit, opt_flags, ਖੋਜ_flags, ਨਿਸ਼ਾਨਾ_obj))
                    ਵਾਪਸ o;
        }
    }

    ਜਦੋਂ (o = av_opt_ਅਗਲਾ(obj, o)) {
        ਜੇ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ਜੇ (ਨਿਸ਼ਾਨਾ_obj) {
                ਜੇ (!(ਖੋਜ_flags & AV_OPT_ਖੋਜ_FAKE_OBJ))
                    *ਨਿਸ਼ਾਨਾ_obj = obj;
                ਨਹੀਂਤਾਂ
                    *ਨਿਸ਼ਾਨਾ_obj = ਨਿਰਾ;
            }
            ਵਾਪਸ o;
        }
    }
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ *av_opt_ਬੱਚਾ_ਅਗਲਾ(ਖਾਲੀ *obj, ਖਾਲੀ *prev)
{
    ਅਚਲ AVClass *c = *(AVClass **)obj;
    ਜੇ (c->ਬੱਚਾ_ਅਗਲਾ)
        ਵਾਪਸ c->ਬੱਚਾ_ਅਗਲਾ(obj, prev);
    ਵਾਪਸ ਨਿਰਾ;
}

ਅਚਲ AVClass *av_opt_ਬੱਚਾ_class_iterate(ਅਚਲ AVClass *ਮਾਪਾ, ਖਾਲੀ **iter)
{
    ਜੇ (ਮਾਪਾ->ਬੱਚਾ_class_iterate)
        ਵਾਪਸ ਮਾਪਾ->ਬੱਚਾ_class_iterate(iter);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ opt_copy_elem(ਖਾਲੀ *logctx, ਗਿਣਤੀ AVOptionType type,
                         ਖਾਲੀ *dst, ਅਚਲ ਖਾਲੀ *src)
{
    ਜੇ (type == AV_OPT_TYPE_STRING) {
        ਅਚਲ ਅੱਖਰ *src_str = *(ਅਚਲ ਅੱਖਰ *ਅਚਲ *)src;
        ਅੱਖਰ         **dstp =  (ਅੱਖਰ **)dst;
        ਜੇ (*dstp != src_str)
            av_freep(dstp);
        ਜੇ (src_str) {
            *dstp = av_strdup(src_str);
            ਜੇ (!*dstp)
                ਵਾਪਸ AVERROR(ENOMEM);
        }
    } ਨਹੀਂਤਾਂ ਜੇ (type == AV_OPT_TYPE_ਦੁਆਧਾਰੀ) {
        ਅਚਲ uint8_t *ਅਚਲ *src8 = (ਅਚਲ uint8_t *ਅਚਲ *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        ਪੂਰਨ len = *(ਅਚਲ ਪੂਰਨ *)(src8 + 1);
        ਜੇ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ਜੇ (len && !*dst8) {
            *(ਪੂਰਨ *)(dst8 + 1) = 0;
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        *(ਪੂਰਨ *)(dst8 + 1) = len;
    } ਨਹੀਂਤਾਂ ਜੇ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ਨਹੀਂਤਾਂ ਜੇ (type == AV_OPT_TYPE_DICT) {
        ਅਚਲ AVDictionary *sdict = *(ਅਚਲ AVDictionary * ਅਚਲ *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ਜੇ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ਨਿਰਾ;
        ਵਾਪਸ av_dict_copy(ddictp, sdict, 0);
    } ਨਹੀਂਤਾਂ ਜੇ (type == AV_OPT_TYPE_CHLAYOUT) {
        ਅਚਲ AVChannelLayout *slayout = (ਅਚਲ AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ਜੇ (dlayout != slayout) {
            ਜੇ (dlayout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM &&
                slayout->ਕ੍ਰਮ == AV_CHANNEL_ਕ੍ਰਮ_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ਨਿਰਾ;
            ਵਾਪਸ av_channel_layout_copy(dst, src);
        }
    } ਨਹੀਂਤਾਂ ਜੇ (opt_is_pod(type)) {
        size_t ਮਾਪ = opt_type_desc[type].ਮਾਪ;
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, src, ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ opt_copy_array(ਖਾਲੀ *logctx, ਅਚਲ AVOption *o,
                          ਖਾਲੀ **pdst, ਅਚਲ ਖਾਲੀ * ਅਚਲ *psrc)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ nb_elems = *opt_array_pcount(psrc);
    ਖਾਲੀ         *dst = ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਜੇ (*pdst == *psrc) {
        *pdst                   = ਨਿਰਾ;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_ਅਧਾਰ(o->type)].ਮਾਪ);
    ਜੇ (!dst)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_ਅਧਾਰ(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(ਖਾਲੀ**)psrc, i));
        ਜੇ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ਵਾਪਸ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_copy(ਖਾਲੀ *dst, ਅਚਲ ਖਾਲੀ *src)
{
    ਅਚਲ AVOption *o = ਨਿਰਾ;
    ਅਚਲ AVClass *c;
    ਪੂਰਨ ret = 0;

    ਜੇ (!src)
        ਵਾਪਸ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ਜੇ (!c || c != *(AVClass **)dst)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜਦੋਂ ((o = av_opt_ਅਗਲਾ(src, o))) {
        ਖਾਲੀ *ਖੇਤਰ_dst = (uint8_t *)dst + o->ਵਿੱਥ;
        ਖਾਲੀ *ਖੇਤਰ_src = (uint8_t *)src + o->ਵਿੱਥ;

        ਪੂਰਨ err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       ਖੇਤਰ_dst, ਖੇਤਰ_src) :
                  opt_copy_elem (dst, o->type, ਖੇਤਰ_dst, ਖੇਤਰ_src);
        ਜੇ (err < 0)
            ret = err;
    }
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_get_array_ਮਾਪ(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags,
                          ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਬਾਹਰਲਾ_val)
{
    ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj, *parray;
    ਅਚਲ AVOption *o;

    o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ਵਾਪਸ AVERROR(EINVAL);

    parray = (uint8_t *)ਨਿਸ਼ਾਨਾ_obj + o->ਵਿੱਥ;
    *ਬਾਹਰਲਾ_val = *opt_array_pcount(parray);

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_get_array(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags,
                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸ਼ੁਰੂ_elem, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_elems,
                     ਗਿਣਤੀ AVOptionType ਬਾਹਰਲਾ_type, ਖਾਲੀ *ਬਾਹਰਲਾ_val)
{
    ਅਚਲ size_t elem_ਮਾਪ_ਬਾਹਰਲਾ = opt_type_desc[TYPE_ਅਧਾਰ(ਬਾਹਰਲਾ_type)].ਮਾਪ;

    ਅਚਲ AVOption *o;
    ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj;

    ਅਚਲ ਖਾਲੀ *parray;
    ਬਿਨਾਨਿਸ਼ਾਨੀ array_ਮਾਪ;

    ਪੂਰਨ ret;

    o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ_obj);
    ਜੇ (!o || !ਨਿਸ਼ਾਨਾ_obj)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਜੇ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (ਬਾਹਰਲਾ_type & AV_OPT_TYPE_FLAG_ARRAY))
        ਵਾਪਸ AVERROR(EINVAL);

    parray     = (uint8_t *)ਨਿਸ਼ਾਨਾ_obj + o->ਵਿੱਥ;
    array_ਮਾਪ = *opt_array_pcount(parray);

    ਜੇ (ਸ਼ੁਰੂ_elem >= array_ਮਾਪ ||
        array_ਮਾਪ - ਸ਼ੁਰੂ_elem < nb_elems)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < nb_elems; i++) {
        ਅਚਲ ਖਾਲੀ *src = opt_array_pelem(o, *(ਖਾਲੀ**)parray, ਸ਼ੁਰੂ_elem + i);
        ਖਾਲੀ       *dst = (uint8_t*)ਬਾਹਰਲਾ_val + i * elem_ਮਾਪ_ਬਾਹਰਲਾ;

        ਜੇ (ਬਾਹਰਲਾ_type == TYPE_ਅਧਾਰ(o->type)) {
            ret = opt_copy_elem(obj, ਬਾਹਰਲਾ_type, dst, src);
            ਜੇ (ret < 0)
                ਜਾਓ fail;
        } ਨਹੀਂਤਾਂ ਜੇ (ਬਾਹਰਲਾ_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *ਬਾਹਰਲਾ = buf;

            ret = opt_get_elem(o, &ਬਾਹਰਲਾ, ਆਕਾਰ(buf), src, ਖੋਜ_flags);
            ਜੇ (ret < 0)
                ਜਾਓ fail;

            ਜੇ (ਬਾਹਰਲਾ == buf) {
                ਬਾਹਰਲਾ = av_strdup(buf);
                ਜੇ (!ਬਾਹਰਲਾ) {
                    ret = AVERROR(ENOMEM);
                    ਜਾਓ fail;
                }
            }

            *(uint8_t**)dst = ਬਾਹਰਲਾ;
        } ਨਹੀਂਤਾਂ ਜੇ (ਬਾਹਰਲਾ_type == AV_OPT_TYPE_INT64    ||
                   ਬਾਹਰਲਾ_type == AV_OPT_TYPE_DOUBLE   ||
                   ਬਾਹਰਲਾ_type == AV_OPT_TYPE_RATIONAL) {
            ਦੁੱਗਣਾ     ਅੰਕ = 1.0;
            ਪੂਰਨ        den = 1;
            int64_t intnum = 1;

            ret = read_ਸੰਖਿਆ(o, src, &ਅੰਕ, &den, &intnum);
            ਜੇ (ret < 0)
                ਜਾਓ fail;

            ਚੋਣ (ਬਾਹਰਲਾ_type) {
            ਹਾਲਤ AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (ਅੰਕ == den) ?  intnum : ਅੰਕ * intnum / den;
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
                *(ਦੁੱਗਣਾ*)dst = ਅੰਕ * intnum / den;
                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (ਅੰਕ == 1.0 && (ਪੂਰਨ)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_ਮੰਜ਼ਿਲ_rational(ਅੰਕ * intnum / den);
                ਰੋਕੋ;
            ਮੂਲ: av_assert0(0);
            }
        } ਨਹੀਂਤਾਂ
            ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਵਾਪਸ 0;
fail:
    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < nb_elems; i++)
        opt_free_elem(ਬਾਹਰਲਾ_type, (uint8_t*)ਬਾਹਰਲਾ_val + i * elem_ਮਾਪ_ਬਾਹਰਲਾ);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_ਸੈੱਟ_array(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags,
                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਸ਼ੁਰੂ_elem, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_elems,
                     ਗਿਣਤੀ AVOptionType val_type, ਅਚਲ ਖਾਲੀ *val)
{
    ਅਚਲ size_t elem_ਮਾਪ_val = opt_type_desc[TYPE_ਅਧਾਰ(val_type)].ਮਾਪ;

    ਅਚਲ AVOption *o;
    ਅਚਲ AVOptionArrayDef *arr;
    ਖਾਲੀ *ਨਿਸ਼ਾਨਾ_obj;

    ਖਾਲੀ *parray;
    ਖਾਲੀ *new_elems;
    ਬਿਨਾਨਿਸ਼ਾਨੀ *array_ਮਾਪ, new_ਮਾਪ;
    size_t elem_ਮਾਪ;

    ਪੂਰਨ ret = 0;

    ret = opt_ਸੈੱਟ_init(obj, name, ਖੋਜ_flags, 0, &ਨਿਸ਼ਾਨਾ_obj, &o, &parray);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ਵਾਪਸ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_ਮਾਪ = opt_array_pcount(parray);
    elem_ਮਾਪ  = opt_type_desc[TYPE_ਅਧਾਰ(o->type)].ਮਾਪ;

    ਜੇ (ਸ਼ੁਰੂ_elem > *array_ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    // compute new array size
    ਜੇ (!val) {
        ਜੇ (*array_ਮਾਪ - ਸ਼ੁਰੂ_elem < nb_elems)
            ਵਾਪਸ AVERROR(EINVAL);

        new_ਮਾਪ = *array_ਮਾਪ - nb_elems;
    } ਨਹੀਂਤਾਂ ਜੇ (ਖੋਜ_flags & AV_OPT_ARRAY_REPLACE) {
        ਜੇ (ਸ਼ੁਰੂ_elem >= UINT_MAX - nb_elems)
            ਵਾਪਸ AVERROR(EINVAL);

        new_ਮਾਪ = FFMAX(*array_ਮਾਪ, ਸ਼ੁਰੂ_elem + nb_elems);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (nb_elems >= UINT_MAX - *array_ਮਾਪ)
            ਵਾਪਸ AVERROR(EINVAL);

        new_ਮਾਪ = *array_ਮਾਪ + nb_elems;
    }

    ਜੇ (arr &&
        ((arr->ਮਾਪ_max && new_ਮਾਪ > arr->ਮਾਪ_max) ||
         (arr->ਮਾਪ_min && new_ਮਾਪ < arr->ਮਾਪ_min)))
        ਵਾਪਸ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ਜੇ (!val) {
        ਖਾਲੀ *array = *(ਖਾਲੀ**)parray;

        ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, ਸ਼ੁਰੂ_elem + i));
        }

        ਜੇ (new_ਮਾਪ > 0) {
            memmove(opt_array_pelem(o, array, ਸ਼ੁਰੂ_elem),
                    opt_array_pelem(o, array, ਸ਼ੁਰੂ_elem + nb_elems),
                    elem_ਮਾਪ * (*array_ਮਾਪ - ਸ਼ੁਰੂ_elem - nb_elems));

            array = av_realloc_array(array, new_ਮਾਪ, elem_ਮਾਪ);
            ਜੇ (!array)
                ਵਾਪਸ AVERROR(ENOMEM);

            *(ਖਾਲੀ**)parray = array;
        } ਨਹੀਂਤਾਂ
            av_freep(parray);

        *array_ਮਾਪ = new_ਮਾਪ;

        ਵਾਪਸ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_ਮਾਪ);
    ਜੇ (!new_elems)
        ਵਾਪਸ AVERROR(ENOMEM);

    // convert/validate each new element
    ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < nb_elems; i++) {
        ਖਾਲੀ       *dst = opt_array_pelem(o, new_elems, i);
        ਅਚਲ ਖਾਲੀ *src = (uint8_t*)val + i * elem_ਮਾਪ_val;

        ਦੁੱਗਣਾ     ਅੰਕ = 1.0;
        ਪੂਰਨ        den = 1;
        int64_t intnum = 1;

        ਜੇ (val_type == TYPE_ਅਧਾਰ(o->type)) {
            ਪੂਰਨ err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ਜੇ (ret < 0)
                ਜਾਓ fail;

            // validate the range for numeric options
            err = read_ਸੰਖਿਆ(o, dst, &ਅੰਕ, &den, &intnum);
            ਜੇ (err >= 0 && TYPE_ਅਧਾਰ(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < ਅੰਕ * intnum || o->min * den > ਅੰਕ * intnum)) {
                ਅੰਕ = den ? ਅੰਕ * intnum / den : (ਅੰਕ && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       ਸ਼ੁਰੂ_elem + i, o->name, ਅੰਕ, o->min, o->max);
                ret = AVERROR(ERANGE);
                ਜਾਓ fail;
            }
        } ਨਹੀਂਤਾਂ ਜੇ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_ਸੈੱਟ_elem(obj, ਨਿਸ਼ਾਨਾ_obj, o, *(ਅਚਲ ਅੱਖਰ **)src, dst);
            ਜੇ (ret < 0)
                ਜਾਓ fail;
        } ਨਹੀਂਤਾਂ ਜੇ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            ਚੋਣ (val_type) {
            ਹਾਲਤ AV_OPT_TYPE_INT:       intnum = *(ਪੂਰਨ*)src;                ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_FLOAT:     ਅੰਕ    = *(ਦਸ਼ਮਲਵ*)src;              ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_DOUBLE:    ਅੰਕ    = *(ਦੁੱਗਣਾ*)src;             ਰੋਕੋ;
            ਹਾਲਤ AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->ਅੰਕ;
                                        den    = ((AVRational*)src)->den;   ਰੋਕੋ;
            ਮੂਲ: av_assert0(0);
            }

            ret = write_ਸੰਖਿਆ(obj, o, dst, ਅੰਕ, den, intnum, 0);
            ਜੇ (ret < 0)
                ਜਾਓ fail;
        } ਨਹੀਂਤਾਂ {
            ret = AVERROR(ENOSYS);
            ਜਾਓ fail;
        }
    }

    // commit new elements to the array
    ਜੇ (ਸ਼ੁਰੂ_elem == 0 && nb_elems == new_ਮਾਪ) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_ਮਾਪ);
        *(ਖਾਲੀ**)parray = new_elems;
        *array_ਮਾਪ     = nb_elems;

        new_elems = ਨਿਰਾ;
        nb_elems  = 0;
    } ਨਹੀਂਤਾਂ {
        ਖਾਲੀ *array = av_realloc_array(*(ਖਾਲੀ**)parray, new_ਮਾਪ, elem_ਮਾਪ);
        ਜੇ (!array) {
            ret = AVERROR(ENOMEM);
            ਜਾਓ fail;
        }

        ਜੇ (ਖੋਜ_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = ਸ਼ੁਰੂ_elem; i < FFMIN(ਸ਼ੁਰੂ_elem + nb_elems, *array_ਮਾਪ); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ਨਹੀਂਤਾਂ {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, ਸ਼ੁਰੂ_elem + nb_elems),
                    opt_array_pelem(o, array, ਸ਼ੁਰੂ_elem),
                    elem_ਮਾਪ * (*array_ਮਾਪ - ਸ਼ੁਰੂ_elem));
        }

        ਸਮ੍ਰਿਤੀ_ਨਕਲ((uint8_t*)array + elem_ਮਾਪ * ਸ਼ੁਰੂ_elem, new_elems, elem_ਮਾਪ * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(ਖਾਲੀ**)parray = array;
        *array_ਮਾਪ     = new_ਮਾਪ;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_query_ranges(AVOptionRanges **ranges_arg, ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ flags)
{
    ਪੂਰਨ ret;
    ਅਚਲ AVClass *c = *(AVClass**)obj;
    ਪੂਰਨ (*callback)(AVOptionRanges **, ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ flags) = c->query_ranges;

    ਜੇ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, ਕੁੰਜੀ, flags);
    ਜੇ (ret >= 0) {
        ਜੇ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_opt_query_ranges_default(AVOptionRanges **ranges_arg, ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ, ਪੂਰਨ flags)
{
    AVOptionRanges *ranges = av_mallocz(ਆਕਾਰ(*ranges));
    AVOptionRange **range_array = av_mallocz(ਆਕਾਰ(ਖਾਲੀ*));
    AVOptionRange *range = av_mallocz(ਆਕਾਰ(*range));
    ਅਚਲ AVOption *ਖੇਤਰ = av_opt_ਲੱਭੋ(obj, ਕੁੰਜੀ, ਨਿਰਾ, 0, flags);
    ਪੂਰਨ ret;

    *ranges_arg = ਨਿਰਾ;

    ਜੇ (!ranges || !range || !range_array || !ਖੇਤਰ) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->ਮੁੱਲ_min = ਖੇਤਰ->min;
    range->ਮੁੱਲ_max = ਖੇਤਰ->max;

    ਚੋਣ (ਖੇਤਰ->type) {
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
    ਹਾਲਤ AV_OPT_TYPE_INT:
    ਹਾਲਤ AV_OPT_TYPE_UINT:
    ਹਾਲਤ AV_OPT_TYPE_INT64:
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
    ਹਾਲਤ AV_OPT_TYPE_DURATION:
    ਹਾਲਤ AV_OPT_TYPE_COLOR:
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->ਮੁੱਲ_min = -1;
        range->ਮੁੱਲ_max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
        range->component_min = 0;
        range->component_max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ/128/8;
        range->ਮੁੱਲ_min = 0;
        range->ਮੁੱਲ_max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ/8;
        ਰੋਕੋ;
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
        range->component_min = 1;
        range->component_max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
        range->ਮੁੱਲ_min = 1;
        range->ਮੁੱਲ_max = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;
        ਰੋਕੋ;
    ਮੂਲ:
        ret = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }

    *ranges_arg = ranges;
    ਵਾਪਸ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ਵਾਪਸ ret;
}

ਖਾਲੀ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    ਪੂਰਨ i;
    AVOptionRanges *ranges = *rangesp;

    ਜੇ (!ranges)
        ਵਾਪਸ;

    ਲਈ (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ਜੇ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

ਪੂਰਨ av_opt_is_ਸੈੱਟ_ਮੰਜ਼ਿਲ_default(ਖਾਲੀ *obj, ਅਚਲ AVOption *o)
{
    int64_t i64;
    ਦੁੱਗਣਾ d;
    AVRational q;
    ਪੂਰਨ ret, w, h;
    ਅੱਖਰ *str;
    ਖਾਲੀ *dst;

    ਜੇ (!o || !obj)
        ਵਾਪਸ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->ਵਿੱਥ;

    ਜੇ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ਅਚਲ ਅੱਖਰ *def = o->default_val.arr ? o->default_val.arr->def : ਨਿਰਾ;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        ਜੇ (!!val != !!def)
            ret = 0;
        ਨਹੀਂਤਾਂ ਜੇ (val)
            ret = !strcmp(val, def);
        ਨਹੀਂਤਾਂ
            ret = 1;

        av_freep(&val);

        ਵਾਪਸ ret;
    }

    ਚੋਣ (o->type) {
    ਹਾਲਤ AV_OPT_TYPE_CONST:
        ਵਾਪਸ 1;
    ਹਾਲਤ AV_OPT_TYPE_BOOL:
    ਹਾਲਤ AV_OPT_TYPE_FLAGS:
    ਹਾਲਤ AV_OPT_TYPE_PIXEL_FMT:
    ਹਾਲਤ AV_OPT_TYPE_SAMPLE_FMT:
    ਹਾਲਤ AV_OPT_TYPE_INT:
    ਹਾਲਤ AV_OPT_TYPE_UINT:
    ਹਾਲਤ AV_OPT_TYPE_DURATION:
    ਹਾਲਤ AV_OPT_TYPE_INT64:
    ਹਾਲਤ AV_OPT_TYPE_UINT64:
        read_ਸੰਖਿਆ(o, dst, ਨਿਰਾ, ਨਿਰਾ, &i64);
        ਵਾਪਸ o->default_val.i64 == i64;
    ਹਾਲਤ AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ਜੇ (o->default_val.str) {
            ਜੇ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ਵਾਪਸ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ਵਾਪਸ ret;
    }
    ਹਾਲਤ AV_OPT_TYPE_STRING:
        str = *(ਅੱਖਰ **)dst;
        ਜੇ (str == o->default_val.str) //2 NULLs
            ਵਾਪਸ 1;
        ਜੇ (!str || !o->default_val.str) //1 NULL
            ਵਾਪਸ 0;
        ਵਾਪਸ !strcmp(str, o->default_val.str);
    ਹਾਲਤ AV_OPT_TYPE_DOUBLE:
        d = *(ਦੁੱਗਣਾ *)dst;
        ਵਾਪਸ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ਹਾਲਤ AV_OPT_TYPE_FLOAT:
        d = *(ਦਸ਼ਮਲਵ *)dst;
        ਵਾਪਸ (ਦਸ਼ਮਲਵ)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ਹਾਲਤ AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        ਵਾਪਸ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    ਹਾਲਤ AV_OPT_TYPE_ਦੁਆਧਾਰੀ: {
        ਬਣਤਰ {
            uint8_t *ਅੰਕੜੇ;
            ਪੂਰਨ ਮਾਪ;
        } tmp = {0};
        ਪੂਰਨ opt_ਮਾਪ = *(ਪੂਰਨ *)((ਖਾਲੀ **)dst + 1);
        ਖਾਲੀ *opt_ptr = *(ਖਾਲੀ **)dst;
        ਜੇ (!opt_ਮਾਪ && (!o->default_val.str || !ਲੜੀ_ਲੰਬਾਈ(o->default_val.str)))
            ਵਾਪਸ 1;
        ਜੇ (!opt_ਮਾਪ ||  !o->default_val.str || !ਲੜੀ_ਲੰਬਾਈ(o->default_val.str ))
            ਵਾਪਸ 0;
        ਜੇ (opt_ਮਾਪ != ਲੜੀ_ਲੰਬਾਈ(o->default_val.str) / 2)
            ਵਾਪਸ 0;
        ret = ਸੈੱਟ_string_ਦੁਆਧਾਰੀ(ਨਿਰਾ, ਨਿਰਾ, o->default_val.str, &tmp.ਅੰਕੜੇ);
        ਜੇ (!ret)
            ret = !memcmp(opt_ptr, tmp.ਅੰਕੜੇ, tmp.ਮਾਪ);
        av_free(tmp.ਅੰਕੜੇ);
        ਵਾਪਸ ret;
    }
    ਹਾਲਤ AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ਨਿਰਾ;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *en1 = ਨਿਰਾ;
        ਅਚਲ AVDictionary_ਇੰਦਰਾਜ *en2 = ਨਿਰਾ;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ਜੇ (ret < 0) {
            av_dict_free(&dict1);
            ਵਾਪਸ ret;
        }
        ਕਰੋ {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ਜਦੋਂ (en1 && en2 && !strcmp(en1->ਕੁੰਜੀ, en2->ਕੁੰਜੀ) && !strcmp(en1->ਮੁੱਲ, en2->ਮੁੱਲ));
        av_dict_free(&dict1);
        ਵਾਪਸ (!en1 && !en2);
    }
    ਹਾਲਤ AV_OPT_TYPE_IMAGE_ਮਾਪ:
        ਜੇ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ਨਹੀਂਤਾਂ ਜੇ ((ret = av_parse_video_ਮਾਪ(&w, &h, o->default_val.str)) < 0)
            ਵਾਪਸ ret;
        ਵਾਪਸ (w == *(ਪੂਰਨ *)dst) && (h == *((ਪੂਰਨ *)dst+1));
    ਹਾਲਤ AV_OPT_TYPE_VIDEO_ਦਰ:
        q = (AVRational){0, 0};
        ਜੇ (o->default_val.str) {
            ਜੇ ((ret = av_parse_video_ਦਰ(&q, o->default_val.str)) < 0)
                ਵਾਪਸ ret;
        }
        ਵਾਪਸ !av_cmp_q(*(AVRational*)dst, q);
    ਹਾਲਤ AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ਜੇ (o->default_val.str) {
            ਜੇ ((ret = av_parse_color(color, o->default_val.str, -1, ਨਿਰਾ)) < 0)
                ਵਾਪਸ ret;
        }
        ਵਾਪਸ !memcmp(color, dst, ਆਕਾਰ(color));
    }
    ਮੂਲ:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        ਰੋਕੋ;
    }
    ਵਾਪਸ AVERROR_PATCHWELCOME;
}

ਪੂਰਨ av_opt_is_ਸੈੱਟ_ਮੰਜ਼ਿਲ_default_by_name(ਖਾਲੀ *obj, ਅਚਲ ਅੱਖਰ *name, ਪੂਰਨ ਖੋਜ_flags)
{
    ਅਚਲ AVOption *o;
    ਖਾਲੀ *ਨਿਸ਼ਾਨਾ;
    ਜੇ (!obj)
        ਵਾਪਸ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ਨਿਰਾ, 0, ਖੋਜ_flags, &ਨਿਸ਼ਾਨਾ);
    ਜੇ (!o)
        ਵਾਪਸ AVERROR_OPTION_NOT_ਮਿਲਿਆ;
    ਵਾਪਸ av_opt_is_ਸੈੱਟ_ਮੰਜ਼ਿਲ_default(ਨਿਸ਼ਾਨਾ, o);
}

ਸਥਿਰ ਪੂਰਨ opt_serialize(ਖਾਲੀ *obj, ਪੂਰਨ opt_flags, ਪੂਰਨ flags, ਪੂਰਨ *cnt,
                         AVBPrint *bprint, ਅਚਲ ਅੱਖਰ ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ ਜੋੜੇ_sep)
{
    ਅਚਲ AVOption *o = ਨਿਰਾ;
    ਖਾਲੀ *ਬੱਚਾ = ਨਿਰਾ;
    uint8_t *buf;
    ਪੂਰਨ ret;
    ਅਚਲ ਅੱਖਰ special_chars[] = {ਜੋੜੇ_sep, ਕੁੰਜੀ_val_sep, '\0'};

    ਜੇ (flags & AV_OPT_SERIALIZE_ਖੋਜ_CHILDREN)
        ਜਦੋਂ (ਬੱਚਾ = av_opt_ਬੱਚਾ_ਅਗਲਾ(obj, ਬੱਚਾ)) {
            ret = opt_serialize(ਬੱਚਾ, opt_flags, flags, cnt, bprint,
                                ਕੁੰਜੀ_val_sep, ਜੋੜੇ_sep);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        }

    ਜਦੋਂ (o = av_opt_ਅਗਲਾ(obj, o)) {
        ਜੇ (o->type == AV_OPT_TYPE_CONST)
            ਜਾਰੀ;
        ਜੇ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ਜੇ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ਜੇ (o->flags == opt_flags)
                    ਜਾਰੀ;
            } ਨਹੀਂਤਾਂ ਜੇ ((o->flags & opt_flags) == opt_flags)
                ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ {
            ਜੇ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                ਜਾਰੀ;
            ਨਹੀਂਤਾਂ ਜੇ (((o->flags & opt_flags) != opt_flags))
                ਜਾਰੀ;
        }
        ਜੇ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_ਸੈੱਟ_ਮੰਜ਼ਿਲ_default(obj, o) > 0)
            ਜਾਰੀ;
        ਜੇ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ਨਿਰਾ);
            ਵਾਪਸ ret;
        }
        ਜੇ (buf) {
            ਜੇ ((*cnt)++)
                av_bprint_append_ਅੰਕੜੇ(bprint, &ਜੋੜੇ_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_ਬਹੁਲਕ_BACKSLASH, 0);
            av_bprint_append_ਅੰਕੜੇ(bprint, &ਕੁੰਜੀ_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_ਬਹੁਲਕ_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_opt_serialize(ਖਾਲੀ *obj, ਪੂਰਨ opt_flags, ਪੂਰਨ flags, ਅੱਖਰ **ਬਫਰ,
                     ਅਚਲ ਅੱਖਰ ਕੁੰਜੀ_val_sep, ਅਚਲ ਅੱਖਰ ਜੋੜੇ_sep)
{
    AVBPrint bprint;
    ਪੂਰਨ ret, cnt = 0;

    ਜੇ (ਜੋੜੇ_sep == '\0' || ਕੁੰਜੀ_val_sep == '\0' || ਜੋੜੇ_sep == ਕੁੰਜੀ_val_sep ||
        ਜੋੜੇ_sep == '\\' || ਕੁੰਜੀ_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ (!obj || !ਬਫਰ)
        ਵਾਪਸ AVERROR(EINVAL);

    *ਬਫਰ = ਨਿਰਾ;
    av_bprint_init(&bprint, 64, AV_BPRINT_ਮਾਪ_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        ਕੁੰਜੀ_val_sep, ਜੋੜੇ_sep);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ret = av_bprint_finalize(&bprint, ਬਫਰ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
    ਵਾਪਸ 0;
}
