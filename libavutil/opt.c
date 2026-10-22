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

#അന്തര്ഭാവ "avutil.h"
#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "channel_layout.h"
#അന്തര്ഭാവ "dict.h"
#അന്തര്ഭാവ "eval.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "parseutils.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "mathematics.h"
#അന്തര്ഭാവ "opt.h"
#അന്തര്ഭാവ "samplefmt.h"
#അന്തര്ഭാവ "bprint.h"

#അന്തര്ഭാവ <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

സ്ഥിരം AVOption *av_opt_next(സ്ഥിരം ശൂന്യം *obj, സ്ഥിരം AVOption *last)
{
    സ്ഥിരം AVClass *class;
    എങ്കിൽ (!obj)
        തിരികെ ശൂന്യ;
    class = *(സ്ഥിരം AVClass**)obj;
    എങ്കിൽ (!last && class && class->option && class->option[0].name)
        തിരികെ class->option;
    എങ്കിൽ (last && last[1].name)
        തിരികെ ++last;
    തിരികെ ശൂന്യ;
}

സ്ഥിതം സ്ഥിരം ഘടന {
    size_t      size;
    സ്ഥിരം അക്ഷരം *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { വലുപ്പം(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { വലുപ്പം(പൂർണ്ണസംഖ്യ),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { വലുപ്പം(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { വലുപ്പം(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { വലുപ്പം(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { വലുപ്പം(ഇരട്ട),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { വലുപ്പം(ദശാംശം),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { വലുപ്പം(അക്ഷരം *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { വലുപ്പം(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ദ്വിമാന]        = { വലുപ്പം(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { വലുപ്പം(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { വലുപ്പം(പൂർണ്ണസംഖ്യ[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { വലുപ്പം(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { വലുപ്പം(എണ്ണൽ AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { വലുപ്പം(എണ്ണൽ AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { വലുപ്പം(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { വലുപ്പം(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { വലുപ്പം(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { വലുപ്പം(പൂർണ്ണസംഖ്യ),            "<boolean>" },
};

// option is plain old data
സ്ഥിതം പൂർണ്ണസംഖ്യ opt_is_pod(എണ്ണൽ AVOptionType type)
{
    തിരഞ്ഞെടുപ്പ് (type) {
    അവസ്ഥ AV_OPT_TYPE_FLAGS:
    അവസ്ഥ AV_OPT_TYPE_INT:
    അവസ്ഥ AV_OPT_TYPE_INT64:
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
    അവസ്ഥ AV_OPT_TYPE_RATIONAL:
    അവസ്ഥ AV_OPT_TYPE_UINT64:
    അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
    അവസ്ഥ AV_OPT_TYPE_DURATION:
    അവസ്ഥ AV_OPT_TYPE_COLOR:
    അവസ്ഥ AV_OPT_TYPE_BOOL:
    അവസ്ഥ AV_OPT_TYPE_UINT:
        തിരികെ 1;
    }
    തിരികെ 0;
}

സ്ഥിതം uint8_t opt_array_sep(സ്ഥിരം AVOption *o)
{
    സ്ഥിരം AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    തിരികെ (d && d->sep) ? d->sep : ',';
}

സ്ഥിതം ശൂന്യം *opt_array_pelem(സ്ഥിരം AVOption *o, ശൂന്യം *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    തിരികെ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

സ്ഥിതം unsigned *opt_array_pcount(സ്ഥിരം ശൂന്യം *parray)
{
    തിരികെ (unsigned *)((സ്ഥിരം ശൂന്യം * സ്ഥിരം *)parray + 1);
}

സ്ഥിതം ശൂന്യം opt_free_elem(എണ്ണൽ AVOptionType type, ശൂന്യം *ptr)
{
    തിരഞ്ഞെടുപ്പ് (TYPE_BASE(type)) {
    അവസ്ഥ AV_OPT_TYPE_STRING:
    അവസ്ഥ AV_OPT_TYPE_ദ്വിമാന:
        av_freep(ptr);
        നിർത്തുക;

    അവസ്ഥ AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        നിർത്തുക;

    അവസ്ഥ AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
}

സ്ഥിതം ശൂന്യം opt_free_array(സ്ഥിരം AVOption *o, ശൂന്യം *parray, unsigned *എണ്ണം)
{
    വേണ്ടി (unsigned i = 0; i < *എണ്ണം; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(ശൂന്യം **)parray, i));

    av_freep(parray);
    *എണ്ണം = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
സ്ഥിതം പൂർണ്ണസംഖ്യ opt_set_init(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags,
                        പൂർണ്ണസംഖ്യ require_type,
                        ശൂന്യം **ptgt, സ്ഥിരം AVOption **po, ശൂന്യം **pdst)
{
    ശൂന്യം *logctx;
    സ്ഥിരം AVOption *o;
    ശൂന്യം *tgt;

    o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &tgt);
    എങ്കിൽ (!o || (!tgt && !(തിരയൽ_flags & AV_OPT_തിരയൽ_FAKE_OBJ)))
        തിരികെ AVERROR_OPTION_NOT_FOUND;

    എങ്കിൽ (o->flags & AV_OPT_FLAG_READONLY)
        തിരികെ AVERROR(EINVAL);

    logctx = tgt ? obj : ശൂന്യ;

    എങ്കിൽ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = ശൂന്യ;
        സ്ഥിരം AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(സ്ഥിരം AVClass**)tgt;
        എങ്കിൽ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        എങ്കിൽ (!state_flags && obj != tgt) {
            class = *(സ്ഥിരം AVClass**)obj;
            എങ്കിൽ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        എങ്കിൽ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            തിരികെ AVERROR(EINVAL);
        }
    }

    എങ്കിൽ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    എങ്കിൽ (po)
        *po   = o;
    എങ്കിൽ (ptgt)
        *ptgt = tgt;
    എങ്കിൽ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : ശൂന്യ;

    തിരികെ 0;
}

സ്ഥിതം AVRational double_to_rational(ഇരട്ട d)
{
     AVRational r = av_d2q(d, 1 << 24);
     എങ്കിൽ ((!r.അക്കം || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     തിരികെ r;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ read_സംഖ്യ(സ്ഥിരം AVOption *o, സ്ഥിരം ശൂന്യം *dst, ഇരട്ട *അക്കം, പൂർണ്ണസംഖ്യ *den, int64_t *intnum)
{
    തിരഞ്ഞെടുപ്പ് (TYPE_BASE(o->type)) {
    അവസ്ഥ AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned പൂർണ്ണസംഖ്യ*)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(എണ്ണൽ AVPixelFormat *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(എണ്ണൽ AVSampleFormat *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_BOOL:
    അവസ്ഥ AV_OPT_TYPE_INT:
        *intnum = *(പൂർണ്ണസംഖ്യ *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_UINT:
        *intnum = *(unsigned പൂർണ്ണസംഖ്യ *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_DURATION:
    അവസ്ഥ AV_OPT_TYPE_INT64:
    അവസ്ഥ AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
        *അക്കം = *(ദശാംശം *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
        *അക്കം = *(ഇരട്ട *)dst;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->അക്കം;
        *den    = ((AVRational *)dst)->den;
        തിരികെ 0;
    അവസ്ഥ AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        തിരികെ 0;
    }
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ write_സംഖ്യ(ശൂന്യം *obj, സ്ഥിരം AVOption *o, ശൂന്യം *dst,
                        ഇരട്ട അക്കം, പൂർണ്ണസംഖ്യ den, int64_t intnum,
                        പൂർണ്ണസംഖ്യ ignore_range)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    സ്ഥിരം എണ്ണൽ AVOptionType type = TYPE_BASE(o->type);

    എങ്കിൽ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < അക്കം * intnum || o->min * den > അക്കം * intnum)) {
        അക്കം = den ? അക്കം * intnum / den : (അക്കം && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               അക്കം, o->name, o->min, o->max);
        തിരികെ AVERROR(ERANGE);
    }
    എങ്കിൽ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        ഇരട്ട d = അക്കം*intnum/den;
        എങ്കിൽ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   അക്കം*intnum/den, o->name);
            തിരികെ AVERROR(ERANGE);
        }
    }

    എങ്കിൽ (!dst)
        തിരികെ 0;

    തിരഞ്ഞെടുപ്പ് (type) {
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
        *(എണ്ണൽ AVPixelFormat *)dst = llrint(അക്കം / den) * intnum;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
        *(എണ്ണൽ AVSampleFormat *)dst = llrint(അക്കം / den) * intnum;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_BOOL:
    അവസ്ഥ AV_OPT_TYPE_FLAGS:
    അവസ്ഥ AV_OPT_TYPE_INT:
    അവസ്ഥ AV_OPT_TYPE_UINT:
        *(പൂർണ്ണസംഖ്യ *)dst = llrint(അക്കം / den) * intnum;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_DURATION:
    അവസ്ഥ AV_OPT_TYPE_INT64:{
        ഇരട്ട d = അക്കം / den;
        എങ്കിൽ (intnum == 1 && d == (ഇരട്ട)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } അല്ലെങ്കിൽ
            *(int64_t *)dst = llrint(d) * intnum;
        നിർത്തുക;}
    അവസ്ഥ AV_OPT_TYPE_UINT64:{
        ഇരട്ട d = അക്കം / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        എങ്കിൽ (intnum == 1 && d == (ഇരട്ട)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } അല്ലെങ്കിൽ എങ്കിൽ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } അല്ലെങ്കിൽ {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        നിർത്തുക;}
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
        *(ദശാംശം *)dst = അക്കം * intnum / den;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
        *(ഇരട്ട    *)dst = അക്കം * intnum / den;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_RATIONAL:
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
        എങ്കിൽ ((പൂർണ്ണസംഖ്യ) അക്കം == അക്കം)
            *(AVRational *)dst = (AVRational) { അക്കം *intnum, den };
        അല്ലെങ്കിൽ
            *(AVRational *)dst = double_to_rational(അക്കം * intnum / den);
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(EINVAL);
    }
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ hexchar2int(അക്ഷരം c) {
    എങ്കിൽ (c >= '0' && c <= '9')
        തിരികെ c - '0';
    എങ്കിൽ (c >= 'a' && c <= 'f')
        തിരികെ c - 'a' + 10;
    എങ്കിൽ (c >= 'A' && c <= 'F')
        തിരികെ c - 'A' + 10;
    തിരികെ -1;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_ദ്വിമാന(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t **dst)
{
    പൂർണ്ണസംഖ്യ *lendst;
    uint8_t *bin, *ptr;
    പൂർണ്ണസംഖ്യ len;

    എങ്കിൽ (dst) {
        lendst = (പൂർണ്ണസംഖ്യ *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    എങ്കിൽ (!val || !(len = strlen(val)))
        തിരികെ 0;

    എങ്കിൽ (len & 1)
        തിരികെ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    എങ്കിൽ (!ptr)
        തിരികെ AVERROR(ENOMEM);
    ആകുമ്പോൾ (*val) {
        പൂർണ്ണസംഖ്യ a = hexchar2int(*val++);
        പൂർണ്ണസംഖ്യ b = hexchar2int(*val++);
        എങ്കിൽ (a < 0 || b < 0) {
            av_free(bin);
            തിരികെ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    എങ്കിൽ (dst) {
        *dst    = bin;
        *lendst = len;
    } അല്ലെങ്കിൽ {
        av_free(bin);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t **dst)
{
    എങ്കിൽ (!dst)
        തിരികെ 0;
    av_freep(dst);
    എങ്കിൽ (!val)
        തിരികെ 0;
    *dst = av_strdup(val);
    തിരികെ *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_സംഖ്യ(ശൂന്യം *obj, ശൂന്യം *target_obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, ശൂന്യം *dst)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    സ്ഥിരം എണ്ണൽ AVOptionType type = TYPE_BASE(o->type);
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        പൂർണ്ണസംഖ്യ അക്കം, den;
        അക്ഷരം c;
        എങ്കിൽ (sscanf(val, "%d%*1[:/]%d%c", &അക്കം, &den, &c) == 2) {
            എങ്കിൽ ((ret = write_സംഖ്യ(obj, o, dst, 1, den, അക്കം, 0)) >= 0)
                തിരികെ ret;
            ret = 0;
        }
    }

    വേണ്ടി (;;) {
        പൂർണ്ണസംഖ്യ i = 0;
        അക്ഷരം buf[256];
        പൂർണ്ണസംഖ്യ cmd = 0;
        ഇരട്ട d;
        int64_t intnum = 1;

        എങ്കിൽ (type == AV_OPT_TYPE_FLAGS) {
            എങ്കിൽ (*val == '+' || *val == '-')
                cmd = *(val++);
            വേണ്ടി (; i < വലുപ്പം(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            പൂർണ്ണസംഖ്യ res;
            പൂർണ്ണസംഖ്യ ci = 0;
            ഇരട്ട const_മൂല്യങ്ങൾ[64];
            സ്ഥിരം അക്ഷരം * const_names[64];
            പൂർണ്ണസംഖ്യ തിരയൽ_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_തിരയൽ_CHILDREN : 0;
            സ്ഥിരം AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, തിരയൽ_flags);
            എങ്കിൽ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                എങ്കിൽ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } അല്ലെങ്കിൽ {
                എങ്കിൽ (o->unit) {
                    വേണ്ടി (o_named = ശൂന്യ; o_named = av_opt_next(target_obj, o_named); ) {
                        എങ്കിൽ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            എങ്കിൽ (ci + 6 >= FF_ARRAY_ELEMS(const_മൂല്യങ്ങൾ)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                തിരികെ AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_മൂല്യങ്ങൾ[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_മൂല്യങ്ങൾ[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_മൂല്യങ്ങൾ[ci++] = o->max;
                const_names [ci  ] = "min";
                const_മൂല്യങ്ങൾ[ci++] = o->min;
                const_names [ci  ] = "none";
                const_മൂല്യങ്ങൾ[ci++] = 0;
                const_names [ci  ] = "all";
                const_മൂല്യങ്ങൾ[ci++] = ~0;
                const_names [ci] = ശൂന്യ;
                const_മൂല്യങ്ങൾ[ci] = 0;

                res = av_വ്യഞ്ജകം_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_മൂല്യങ്ങൾ, ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ, 0, obj);
                എങ്കിൽ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    തിരികെ res;
                }
            }
        }
        എങ്കിൽ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned പൂർണ്ണസംഖ്യ*)dst;
            എങ്കിൽ (cmd == '+')
                d = intnum | (int64_t)d;
            അല്ലെങ്കിൽ എങ്കിൽ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        എങ്കിൽ ((ret = write_സംഖ്യ(obj, o, dst, d, 1, 1, 0)) < 0)
            തിരികെ ret;
        val += i;
        എങ്കിൽ (!i || !*val)
            തിരികെ 0;
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_image_size(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, പൂർണ്ണസംഖ്യ *dst)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    പൂർണ്ണസംഖ്യ tmp[2];
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!val || !strcmp(val, "none")) {
        എങ്കിൽ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        തിരികെ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    എങ്കിൽ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        തിരികെ ret;
    }
    എങ്കിൽ (dst)
        memcpy(dst, tmp, വലുപ്പം(tmp));
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_video_rate(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, AVRational *dst)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    AVRational tmp;
    പൂർണ്ണസംഖ്യ ret = av_parse_video_rate(&tmp, val);
    എങ്കിൽ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    എങ്കിൽ (dst)
        *dst = tmp;
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_color(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t *dst)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!val) {
        തിരികെ 0;
    } അല്ലെങ്കിൽ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        എങ്കിൽ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            തിരികെ ret;
        }
        എങ്കിൽ (dst)
            memcpy(dst, tmp, വലുപ്പം(tmp));
        തിരികെ ret;
    }
    തിരികെ 0;
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *get_bool_name(പൂർണ്ണസംഖ്യ val)
{
    എങ്കിൽ (val < 0)
        തിരികെ "auto";
    തിരികെ val ? "true" : "false";
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_bool(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, പൂർണ്ണസംഖ്യ *dst)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    പൂർണ്ണസംഖ്യ n;

    എങ്കിൽ (!val)
        തിരികെ 0;

    എങ്കിൽ (!strcmp(val, "auto")) {
        n = -1;
    } അല്ലെങ്കിൽ എങ്കിൽ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } അല്ലെങ്കിൽ എങ്കിൽ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } അല്ലെങ്കിൽ {
        അക്ഷരം *end = ശൂന്യ;
        n = strtol(val, &end, 10);
        എങ്കിൽ (val + strlen(val) != end)
            പോകുക fail;
    }

    എങ്കിൽ (n < o->min || n > o->max)
        പോകുക fail;

    എങ്കിൽ (dst)
    *dst = n;
    തിരികെ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_fmt(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t *dst,
                          പൂർണ്ണസംഖ്യ fmt_nb, പൂർണ്ണസംഖ്യ ((*get_fmt)(സ്ഥിരം അക്ഷരം *)), സ്ഥിരം അക്ഷരം *desc,
                          എണ്ണൽ AVOptionType type)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    പൂർണ്ണസംഖ്യ fmt, min, max;

    എങ്കിൽ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } അല്ലെങ്കിൽ {
        fmt = get_fmt(val);
        എങ്കിൽ (fmt == -1) {
            അക്ഷരം *tail;
            fmt = strtol(val, &tail, 0);
            എങ്കിൽ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                തിരികെ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    എങ്കിൽ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    എങ്കിൽ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        തിരികെ AVERROR(ERANGE);
    }

    എങ്കിൽ (dst)
    തിരഞ്ഞെടുപ്പ് (type) {
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:  *(എണ്ണൽ AVPixelFormat *)dst = fmt; നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT: *(എണ്ണൽ AVSampleFormat*)dst = fmt; നിർത്തുക;
    സ്ഥിരസ്ഥിതി: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ get_pix_fmt(സ്ഥിരം അക്ഷരം *name)
{
    തിരികെ av_get_pix_fmt(name);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_pixel_fmt(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t *dst)
{
    തിരികെ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ get_sample_fmt(സ്ഥിരം അക്ഷരം *name)
{
    തിരികെ av_get_sample_fmt(name);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_sample_fmt(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t *dst)
{
    തിരികെ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_dict(ശൂന്യം *obj, സ്ഥിരം AVOption *o, സ്ഥിരം അക്ഷരം *val, uint8_t **dst)
{
    AVDictionary *options = ശൂന്യ;

    എങ്കിൽ (val) {
        പൂർണ്ണസംഖ്യ ret = av_dict_parse_string(&options, val, "=", ":", 0);
        എങ്കിൽ (ret < 0) {
            av_dict_free(&options);
            തിരികെ ret;
        }
    }

    എങ്കിൽ (!dst) {
        av_dict_free(&options);
        തിരികെ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_string_channel_layout(ശൂന്യം *obj, സ്ഥിരം AVOption *o,
                                     സ്ഥിരം അക്ഷരം *val, ശൂന്യം *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    പൂർണ്ണസംഖ്യ ret;
    എങ്കിൽ (dst)
    av_channel_layout_uninit(channel_layout);
    അല്ലെങ്കിൽ
        channel_layout = &tmp;
    എങ്കിൽ (!val)
        തിരികെ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    എങ്കിൽ (!dst)
        av_channel_layout_uninit(channel_layout);
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_set_elem(ശൂന്യം *obj, ശൂന്യം *target_obj, സ്ഥിരം AVOption *o,
                        സ്ഥിരം അക്ഷരം *val, ശൂന്യം *dst)
{
    ശൂന്യം *logctx = dst ? obj : ശൂന്യ;
    സ്ഥിരം എണ്ണൽ AVOptionType type = TYPE_BASE(o->type);
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        തിരികെ AVERROR(EINVAL);

    തിരഞ്ഞെടുപ്പ് (type) {
    അവസ്ഥ AV_OPT_TYPE_BOOL:
        തിരികെ set_string_bool(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_STRING:
        തിരികെ set_string(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_ദ്വിമാന:
        തിരികെ set_string_ദ്വിമാന(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_FLAGS:
    അവസ്ഥ AV_OPT_TYPE_INT:
    അവസ്ഥ AV_OPT_TYPE_UINT:
    അവസ്ഥ AV_OPT_TYPE_INT64:
    അവസ്ഥ AV_OPT_TYPE_UINT64:
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
    അവസ്ഥ AV_OPT_TYPE_RATIONAL:
        തിരികെ set_string_സംഖ്യ(obj, target_obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
        തിരികെ set_string_image_size(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
        തിരികെ write_സംഖ്യ(obj, o, dst, 1, tmp.den, tmp.അക്കം, 0);
    }
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
        തിരികെ set_string_pixel_fmt(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
        തിരികെ set_string_sample_fmt(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            എങ്കിൽ (val) {
                എങ്കിൽ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    തിരികെ ret;
                }
            }
            എങ്കിൽ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                തിരികെ AVERROR(ERANGE);
            }
            എങ്കിൽ (dst)
            *(int64_t *)dst = usecs;
            തിരികെ 0;
        }
    അവസ്ഥ AV_OPT_TYPE_COLOR:
        തിരികെ set_string_color(obj, o, val, dst);
    അവസ്ഥ AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        എങ്കിൽ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        തിരികെ ret;
    അവസ്ഥ AV_OPT_TYPE_DICT:
        തിരികെ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_set_array(ശൂന്യം *obj, ശൂന്യം *target_obj, സ്ഥിരം AVOption *o,
                         സ്ഥിരം അക്ഷരം *val, ശൂന്യം *dst)
{
    സ്ഥിരം AVOptionArrayDef *arr = o->default_val.arr;
    സ്ഥിരം size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    സ്ഥിരം uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ശൂന്യ;

    ശൂന്യം      *logctx = dst ? obj : ശൂന്യ;
    ശൂന്യം       *elems = ശൂന്യ;
    unsigned nb_elems = 0;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        എങ്കിൽ (!str)
            തിരികെ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ആകുമ്പോൾ (val && *val) {
        uint8_t *p = str;
        ശൂന്യം *tmp;

        എങ്കിൽ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            പോകുക fail;
        }

        വേണ്ടി (; *val; val++, p++) {
            എങ്കിൽ (*val == '\\' && val[1])
                val++;
            അല്ലെങ്കിൽ എങ്കിൽ (*val == sep) {
                val++;
                നിർത്തുക;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        എങ്കിൽ (!tmp) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        എങ്കിൽ (ret < 0)
            പോകുക fail;
        nb_elems++;
    }
    av_freep(&str);

    എങ്കിൽ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    എങ്കിൽ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        പോകുക fail;
    }

    എങ്കിൽ (dst) {
    *((ശൂന്യം **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } അല്ലെങ്കിൽ
        opt_free_array(o, &elems, &nb_elems);

    തിരികെ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_set(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *val, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    ശൂന്യം *dst, *target_obj;
    സ്ഥിരം AVOption *o;
    പൂർണ്ണസംഖ്യ ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, 0, &target_obj, &o, &dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    തിരികെ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_സംഖ്യ(name, opttype, vartype)                         \
പൂർണ്ണസംഖ്യ av_opt_eval_ ## name(ശൂന്യം *obj, സ്ഥിരം AVOption *o,                  \
                         സ്ഥിരം അക്ഷരം *val, vartype *name ## _out)        \
{                                                                       \
    എങ്കിൽ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        തിരികെ AVERROR(EINVAL);                                         \
    തിരികെ set_string_സംഖ്യ(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_സംഖ്യ(flags,  AV_OPT_TYPE_FLAGS,    പൂർണ്ണസംഖ്യ)
OPT_EVAL_സംഖ്യ(പൂർണ്ണസംഖ്യ,    AV_OPT_TYPE_INT,      പൂർണ്ണസംഖ്യ)
OPT_EVAL_സംഖ്യ(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_സംഖ്യ(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_സംഖ്യ(ദശാംശം,  AV_OPT_TYPE_FLOAT,    ദശാംശം)
OPT_EVAL_സംഖ്യ(ഇരട്ട, AV_OPT_TYPE_DOUBLE,   ഇരട്ട)
OPT_EVAL_സംഖ്യ(q,      AV_OPT_TYPE_RATIONAL, AVRational)

സ്ഥിതം പൂർണ്ണസംഖ്യ set_സംഖ്യ(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, ഇരട്ട അക്കം, പൂർണ്ണസംഖ്യ den, int64_t intnum,
                      പൂർണ്ണസംഖ്യ തിരയൽ_flags, പൂർണ്ണസംഖ്യ require_type)
{
    ശൂന്യം *dst;
    സ്ഥിരം AVOption *o;
    പൂർണ്ണസംഖ്യ ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, require_type, ശൂന്യ, &o, &dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    എങ്കിൽ (dst)
        ret = write_സംഖ്യ(obj, o, dst, അക്കം, den, intnum, 0);

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_set_int(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, int64_t val, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ set_സംഖ്യ(obj, name, 1, 1, val, തിരയൽ_flags, 0);
}

പൂർണ്ണസംഖ്യ av_opt_set_double(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, ഇരട്ട val, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ set_സംഖ്യ(obj, name, val, 1, 1, തിരയൽ_flags, 0);
}

പൂർണ്ണസംഖ്യ av_opt_set_q(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, AVRational val, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ set_സംഖ്യ(obj, name, val.അക്കം, val.den, 1, തിരയൽ_flags, 0);
}

പൂർണ്ണസംഖ്യ av_opt_set_bin(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം uint8_t *val, പൂർണ്ണസംഖ്യ len, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    പൂർണ്ണസംഖ്യ *lendst;
    പൂർണ്ണസംഖ്യ ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, AV_OPT_TYPE_ദ്വിമാന,
                       ശൂന്യ, ശൂന്യ, (ശൂന്യം**)&dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    എങ്കിൽ (dst) {
    ptr = len ? av_malloc(len) : ശൂന്യ;
    എങ്കിൽ (len && !ptr)
        തിരികെ AVERROR(ENOMEM);

    lendst = (പൂർണ്ണസംഖ്യ *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    എങ്കിൽ (len)
        memcpy(ptr, val, len);
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_set_image_size(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    സ്ഥിരം AVOption *o;
    ശൂന്യം *logctx;
    പൂർണ്ണസംഖ്യ *dst;
    പൂർണ്ണസംഖ്യ ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       ശൂന്യ, &o, (ശൂന്യം**)&dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    logctx = dst ? obj : ശൂന്യ;

    എങ്കിൽ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_set_video_rate(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, AVRational val, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ set_സംഖ്യ(obj, name, val.അക്കം, val.den, 1, തിരയൽ_flags, AV_OPT_TYPE_VIDEO_RATE);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ set_format(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ fmt, പൂർണ്ണസംഖ്യ തിരയൽ_flags,
                      എണ്ണൽ AVOptionType type, സ്ഥിരം അക്ഷരം *desc, പൂർണ്ണസംഖ്യ nb_fmts)
{
    സ്ഥിരം AVOption *o;
    ശൂന്യം *logctx;
    പൂർണ്ണസംഖ്യ *dst;
    പൂർണ്ണസംഖ്യ min, max, ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, type, ശൂന്യ, &o, (ശൂന്യം**)&dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    logctx = dst ? obj : ശൂന്യ;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    എങ്കിൽ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        തിരികെ AVERROR(ERANGE);
    }
    എങ്കിൽ (dst)
    *dst = fmt;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_set_pixel_fmt(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, എണ്ണൽ AVPixelFormat fmt, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ set_format(obj, name, fmt, തിരയൽ_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

പൂർണ്ണസംഖ്യ av_opt_set_sample_fmt(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, എണ്ണൽ AVSampleFormat fmt, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ set_format(obj, name, fmt, തിരയൽ_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

പൂർണ്ണസംഖ്യ av_opt_set_dict_val(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം AVDictionary *val,
                        പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    AVDictionary **dst;
    പൂർണ്ണസംഖ്യ ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, AV_OPT_TYPE_DICT, ശൂന്യ, ശൂന്യ,
                       (ശൂന്യം**)&dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    എങ്കിൽ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_set_chlayout(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name,
                        സ്ഥിരം AVChannelLayout *channel_layout,
                        പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    AVChannelLayout *dst;
    പൂർണ്ണസംഖ്യ ret;

    ret = opt_set_init(obj, name, തിരയൽ_flags, AV_OPT_TYPE_CHLAYOUT, ശൂന്യ, ശൂന്യ,
                       (ശൂന്യം**)&dst);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    എങ്കിൽ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    തിരികെ ret;
}

സ്ഥിതം ശൂന്യം format_duration(അക്ഷരം *buf, size_t size, int64_t d)
{
    അക്ഷരം *e;

    av_assert0(size >= 25);
    എങ്കിൽ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    എങ്കിൽ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    അല്ലെങ്കിൽ എങ്കിൽ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    അല്ലെങ്കിൽ എങ്കിൽ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (പൂർണ്ണസംഖ്യ)((d / 60000000) % 60),
                 (പൂർണ്ണസംഖ്യ)((d / 1000000) % 60),
                 (പൂർണ്ണസംഖ്യ)(d % 1000000));
    അല്ലെങ്കിൽ എങ്കിൽ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (പൂർണ്ണസംഖ്യ)(d / 60000000),
                 (പൂർണ്ണസംഖ്യ)((d / 1000000) % 60),
                 (പൂർണ്ണസംഖ്യ)(d % 1000000));
    അല്ലെങ്കിൽ
        snprintf(buf, size, "%d.%06d",
                 (പൂർണ്ണസംഖ്യ)(d / 1000000),
                 (പൂർണ്ണസംഖ്യ)(d % 1000000));
    e = buf + strlen(buf);
    ആകുമ്പോൾ (e > buf && e[-1] == '0')
        *(--e) = 0;
    എങ്കിൽ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_get_elem(സ്ഥിരം AVOption *o, uint8_t **pbuf, size_t buf_len,
                        സ്ഥിരം ശൂന്യം *dst, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    പൂർണ്ണസംഖ്യ ret;

    തിരഞ്ഞെടുപ്പ് (TYPE_BASE(o->type)) {
    അവസ്ഥ AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(പൂർണ്ണസംഖ്യ *)dst));
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(പൂർണ്ണസംഖ്യ *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(പൂർണ്ണസംഖ്യ *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(ദശാംശം *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(ഇരട്ട *)dst);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
    അവസ്ഥ AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->അക്കം, ((AVRational *)dst)->den);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_STRING:
        എങ്കിൽ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } അല്ലെങ്കിൽ എങ്കിൽ (തിരയൽ_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ശൂന്യ;
            തിരികെ 0;
        } അല്ലെങ്കിൽ {
            *pbuf = av_strdup("");
        }
        തിരികെ *pbuf ? 0 : AVERROR(ENOMEM);
    അവസ്ഥ AV_OPT_TYPE_ദ്വിമാന: {
        സ്ഥിരം uint8_t *bin;
        പൂർണ്ണസംഖ്യ len;

        എങ്കിൽ (!*(uint8_t **)dst && (തിരയൽ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ശൂന്യ;
            തിരികെ 0;
        }
        len = *(പൂർണ്ണസംഖ്യ *)(((uint8_t *)dst) + വലുപ്പം(uint8_t *));
        എങ്കിൽ ((uint64_t)len * 2 + 1 > INT_MAX)
            തിരികെ AVERROR(EINVAL);
        എങ്കിൽ (!(*pbuf = av_malloc(len * 2 + 1)))
            തിരികെ AVERROR(ENOMEM);
        എങ്കിൽ (!len) {
            *pbuf[0] = '\0';
            തിരികെ 0;
        }
        bin = *(uint8_t **)dst;
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        തിരികെ 0;
    }
    അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((പൂർണ്ണസംഖ്യ *)dst)[0], ((പൂർണ്ണസംഖ്യ *)dst)[1]);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (അക്ഷരം *)av_x_if_null(av_get_pix_fmt_name(*(എണ്ണൽ AVPixelFormat *)dst), "none"));
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (അക്ഷരം *)av_x_if_null(av_get_sample_fmt_name(*(എണ്ണൽ AVSampleFormat *)dst), "none"));
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        നിർത്തുക;
    }
    അവസ്ഥ AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (പൂർണ്ണസംഖ്യ)((uint8_t *)dst)[0], (പൂർണ്ണസംഖ്യ)((uint8_t *)dst)[1],
                       (പൂർണ്ണസംഖ്യ)((uint8_t *)dst)[2], (പൂർണ്ണസംഖ്യ)((uint8_t *)dst)[3]);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_DICT:
        എങ്കിൽ (!*(AVDictionary **)dst && (തിരയൽ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ശൂന്യ;
            തിരികെ 0;
        }
        തിരികെ av_dict_get_string(*(AVDictionary **)dst, (അക്ഷരം **)pbuf, '=', ':');
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(EINVAL);
    }

    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_get_array(സ്ഥിരം AVOption *o, ശൂന്യം *dst, uint8_t **out_val)
{
    സ്ഥിരം unsigned എണ്ണം = *opt_array_pcount(dst);
    സ്ഥിരം uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ശൂന്യ;
    size_t   str_len = 0;
    പൂർണ്ണസംഖ്യ ret;

    *out_val = ശൂന്യ;

    വേണ്ടി (unsigned i = 0; i < എണ്ണം; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, വലുപ്പം(buf),
                           opt_array_pelem(o, *(ശൂന്യം **)dst, i), 0);
        എങ്കിൽ (ret < 0)
            പോകുക fail;

        out_len = strlen(out);
        എങ്കിൽ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            പോകുക fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        എങ്കിൽ (ret < 0)
            പോകുക fail;

        // add separator if needed
        എങ്കിൽ (i)
            str[str_len++] = sep;

        // escape the element
        വേണ്ടി (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            എങ്കിൽ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        എങ്കിൽ (out != buf)
            av_freep(&out);
        എങ്കിൽ (ret < 0) {
            av_freep(&str);
            തിരികെ ret;
        }
    }

    *out_val = str;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, uint8_t **out_val)
{
    ശൂന്യം *dst, *target_obj;
    സ്ഥിരം AVOption *o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    uint8_t *out, buf[128];
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        തിരികെ AVERROR_OPTION_NOT_FOUND;

    എങ്കിൽ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    എങ്കിൽ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
        എങ്കിൽ (!*out_val && !(തിരയൽ_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            എങ്കിൽ (!*out_val)
               തിരികെ AVERROR(ENOMEM);
        }
        തിരികെ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, വലുപ്പം(buf), dst, തിരയൽ_flags);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    എങ്കിൽ (out != buf) {
        *out_val = out;
        തിരികെ 0;
    }

    എങ്കിൽ (ret >= വലുപ്പം(buf))
        തിരികെ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    തിരികെ *out_val ? 0 : AVERROR(ENOMEM);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ get_സംഖ്യ(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, ഇരട്ട *അക്കം, പൂർണ്ണസംഖ്യ *den, int64_t *intnum,
                      പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    ശൂന്യം *dst, *target_obj;
    സ്ഥിരം AVOption *o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        തിരികെ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    തിരികെ read_സംഖ്യ(o, dst, അക്കം, den, intnum);
}

പൂർണ്ണസംഖ്യ av_opt_get_int(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    ഇരട്ട അക്കം = 1;
    പൂർണ്ണസംഖ്യ ret, den = 1;

    എങ്കിൽ ((ret = get_സംഖ്യ(obj, name, &അക്കം, &den, &intnum, തിരയൽ_flags)) < 0)
        തിരികെ ret;
    എങ്കിൽ (അക്കം == den)
        *out_val = intnum;
    അല്ലെങ്കിൽ
        *out_val = അക്കം * intnum / den;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_double(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, ഇരട്ട *out_val)
{
    int64_t intnum = 1;
    ഇരട്ട അക്കം = 1;
    പൂർണ്ണസംഖ്യ ret, den = 1;

    എങ്കിൽ ((ret = get_സംഖ്യ(obj, name, &അക്കം, &den, &intnum, തിരയൽ_flags)) < 0)
        തിരികെ ret;
    *out_val = അക്കം * intnum / den;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_q(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    ഇരട്ട അക്കം = 1;
    പൂർണ്ണസംഖ്യ ret, den = 1;

    എങ്കിൽ ((ret = get_സംഖ്യ(obj, name, &അക്കം, &den, &intnum, തിരയൽ_flags)) < 0)
        തിരികെ ret;

    എങ്കിൽ (അക്കം == 1.0 && (പൂർണ്ണസംഖ്യ)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    അല്ലെങ്കിൽ
        *out_val = double_to_rational(അക്കം*intnum/den);
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_image_size(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, പൂർണ്ണസംഖ്യ *w_out, പൂർണ്ണസംഖ്യ *h_out)
{
    ശൂന്യം *dst, *target_obj;
    സ്ഥിരം AVOption *o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        തിരികെ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    എങ്കിൽ (w_out) *w_out = *(പൂർണ്ണസംഖ്യ *)dst;
    എങ്കിൽ (h_out) *h_out = *((പൂർണ്ണസംഖ്യ *)dst+1);
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_video_rate(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, AVRational *out_val)
{
    തിരികെ av_opt_get_q(obj, name, തിരയൽ_flags, out_val);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ get_format(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, ശൂന്യം *out_fmt,
                      എണ്ണൽ AVOptionType type, സ്ഥിരം അക്ഷരം *desc)
{
    ശൂന്യം *dst, *target_obj;
    സ്ഥിരം AVOption *o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        തിരികെ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    എങ്കിൽ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(എണ്ണൽ AVPixelFormat *)out_fmt = *(എണ്ണൽ AVPixelFormat *)dst;
    അല്ലെങ്കിൽ
        *(എണ്ണൽ AVSampleFormat*)out_fmt = *(എണ്ണൽ AVSampleFormat*)dst;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_pixel_fmt(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, എണ്ണൽ AVPixelFormat *out_fmt)
{
    തിരികെ get_format(obj, name, തിരയൽ_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

പൂർണ്ണസംഖ്യ av_opt_get_sample_fmt(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, എണ്ണൽ AVSampleFormat *out_fmt)
{
    തിരികെ get_format(obj, name, തിരയൽ_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

പൂർണ്ണസംഖ്യ av_opt_get_chlayout(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, AVChannelLayout *cl)
{
    ശൂന്യം *dst, *target_obj;
    സ്ഥിരം AVOption *o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        തിരികെ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    തിരികെ av_channel_layout_copy(cl, dst);
}

പൂർണ്ണസംഖ്യ av_opt_get_dict_val(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags, AVDictionary **out_val)
{
    ശൂന്യം *target_obj;
    AVDictionary *src;
    സ്ഥിരം AVOption *o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);

    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (o->type != AV_OPT_TYPE_DICT)
        തിരികെ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    തിരികെ av_dict_copy(out_val, src, 0);
}

പൂർണ്ണസംഖ്യ av_opt_flag_is_set(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *field_name, സ്ഥിരം അക്ഷരം *flag_name)
{
    സ്ഥിരം AVOption *field = av_opt_find(obj, field_name, ശൂന്യ, 0, 0);
    സ്ഥിരം AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : ശൂന്യ, 0, 0);
    int64_t res;

    എങ്കിൽ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        തിരികെ 0;
    തിരികെ res & flag->default_val.i64;
}

സ്ഥിതം ശൂന്യം log_int_മൂല്യം(ശൂന്യം *av_log_obj, പൂർണ്ണസംഖ്യ level, int64_t i)
{
    എങ്കിൽ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } അല്ലെങ്കിൽ എങ്കിൽ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } അല്ലെങ്കിൽ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

സ്ഥിതം ശൂന്യം log_മൂല്യം(ശൂന്യം *av_log_obj, പൂർണ്ണസംഖ്യ level, ഇരട്ട d)
{
    എങ്കിൽ      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == (ഇരട്ട)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } അല്ലെങ്കിൽ എങ്കിൽ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } അല്ലെങ്കിൽ {
        av_log(av_log_obj, level, "%g", d);
    }
}

സ്ഥിതം സ്ഥിരം അക്ഷരം *get_opt_const_name(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *unit, int64_t മൂല്യം)
{
    സ്ഥിരം AVOption *opt = ശൂന്യ;

    എങ്കിൽ (!unit)
        തിരികെ ശൂന്യ;
    ആകുമ്പോൾ ((opt = av_opt_next(obj, opt)))
        എങ്കിൽ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == മൂല്യം)
            തിരികെ opt->name;
    തിരികെ ശൂന്യ;
}

സ്ഥിതം അക്ഷരം *get_opt_flags_string(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *unit, int64_t മൂല്യം)
{
    സ്ഥിരം AVOption *opt = ശൂന്യ;
    അക്ഷരം flags[512];

    flags[0] = 0;
    എങ്കിൽ (!unit)
        തിരികെ ശൂന്യ;
    ആകുമ്പോൾ ((opt = av_opt_next(obj, opt))) {
        എങ്കിൽ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & മൂല്യം) {
            എങ്കിൽ (flags[0])
                av_strlcatf(flags, വലുപ്പം(flags), "+");
            av_strlcatf(flags, വലുപ്പം(flags), "%s", opt->name);
        }
    }
    എങ്കിൽ (flags[0])
        തിരികെ av_strdup(flags);
    തിരികെ ശൂന്യ;
}

സ്ഥിതം ശൂന്യം log_type(ശൂന്യം *av_log_obj, സ്ഥിരം AVOption *o,
                     എണ്ണൽ AVOptionType parent_type)
{
    സ്ഥിരം എണ്ണൽ AVOptionType type = TYPE_BASE(o->type);

    എങ്കിൽ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    അല്ലെങ്കിൽ എങ്കിൽ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        എങ്കിൽ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        അല്ലെങ്കിൽ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    അല്ലെങ്കിൽ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

സ്ഥിതം ശൂന്യം log_default(ശൂന്യം *obj, ശൂന്യം *av_log_obj, സ്ഥിരം AVOption *opt)
{
    എങ്കിൽ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ദ്വിമാന)
        തിരികെ;
    എങ്കിൽ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        തിരികെ;

    എങ്കിൽ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        സ്ഥിരം AVOptionArrayDef *arr = opt->default_val.arr;
        എങ്കിൽ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        തിരികെ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    തിരഞ്ഞെടുപ്പ് (opt->type) {
    അവസ്ഥ AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_FLAGS: {
        അക്ഷരം *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        എങ്കിൽ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } അല്ലെങ്കിൽ {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        നിർത്തുക;
    }
    അവസ്ഥ AV_OPT_TYPE_DURATION: {
        അക്ഷരം buf[25];
        format_duration(buf, വലുപ്പം(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        നിർത്തുക;
    }
    അവസ്ഥ AV_OPT_TYPE_UINT:
    അവസ്ഥ AV_OPT_TYPE_INT:
    അവസ്ഥ AV_OPT_TYPE_UINT64:
    അവസ്ഥ AV_OPT_TYPE_INT64: {
        സ്ഥിരം അക്ഷരം *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        എങ്കിൽ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        അല്ലെങ്കിൽ
            log_int_മൂല്യം(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        നിർത്തുക;
    }
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
        log_മൂല്യം(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.അക്കം, q.den); }
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (അക്ഷരം *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (അക്ഷരം *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_COLOR:
    അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
    അവസ്ഥ AV_OPT_TYPE_STRING:
    അവസ്ഥ AV_OPT_TYPE_DICT:
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
    അവസ്ഥ AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        നിർത്തുക;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

സ്ഥിതം ശൂന്യം opt_list(ശൂന്യം *obj, ശൂന്യം *av_log_obj, സ്ഥിരം അക്ഷരം *unit,
                     പൂർണ്ണസംഖ്യ req_flags, പൂർണ്ണസംഖ്യ rej_flags, എണ്ണൽ AVOptionType parent_type)
{
    സ്ഥിരം AVOption *opt = ശൂന്യ;
    AVOptionRanges *r;
    പൂർണ്ണസംഖ്യ i;

    ആകുമ്പോൾ ((opt = av_opt_next(obj, opt))) {
        എങ്കിൽ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            തുടരുക;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        എങ്കിൽ (!unit && opt->type == AV_OPT_TYPE_CONST)
            തുടരുക;
        അല്ലെങ്കിൽ എങ്കിൽ (unit && opt->type != AV_OPT_TYPE_CONST)
            തുടരുക;
        അല്ലെങ്കിൽ എങ്കിൽ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            തുടരുക;
        അല്ലെങ്കിൽ എങ്കിൽ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        അല്ലെങ്കിൽ
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

        എങ്കിൽ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        എങ്കിൽ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_തിരയൽ_FAKE_OBJ) >= 0) {
            തിരഞ്ഞെടുപ്പ് (opt->type) {
            അവസ്ഥ AV_OPT_TYPE_INT:
            അവസ്ഥ AV_OPT_TYPE_UINT:
            അവസ്ഥ AV_OPT_TYPE_INT64:
            അവസ്ഥ AV_OPT_TYPE_UINT64:
            അവസ്ഥ AV_OPT_TYPE_DOUBLE:
            അവസ്ഥ AV_OPT_TYPE_FLOAT:
            അവസ്ഥ AV_OPT_TYPE_RATIONAL:
                വേണ്ടി (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_മൂല്യം(av_log_obj, AV_LOG_INFO, r->range[i]->മൂല്യം_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_മൂല്യം(av_log_obj, AV_LOG_INFO, r->range[i]->മൂല്യം_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                നിർത്തുക;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        എങ്കിൽ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

പൂർണ്ണസംഖ്യ av_opt_show2(ശൂന്യം *obj, ശൂന്യം *av_log_obj, പൂർണ്ണസംഖ്യ req_flags, പൂർണ്ണസംഖ്യ rej_flags)
{
    എങ്കിൽ (!obj)
        തിരികെ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ശൂന്യ, req_flags, rej_flags, -1);

    തിരികെ 0;
}

ശൂന്യം av_opt_set_defaults(ശൂന്യം *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

ശൂന്യം av_opt_set_defaults2(ശൂന്യം *s, പൂർണ്ണസംഖ്യ mask, പൂർണ്ണസംഖ്യ flags)
{
    സ്ഥിരം AVOption *opt = ശൂന്യ;
    ആകുമ്പോൾ ((opt = av_opt_next(s, opt))) {
        ശൂന്യം *dst = ((uint8_t*)s) + opt->offset;

        എങ്കിൽ ((opt->flags & mask) != flags)
            തുടരുക;

        എങ്കിൽ (opt->flags & AV_OPT_FLAG_READONLY)
            തുടരുക;

        എങ്കിൽ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            സ്ഥിരം AVOptionArrayDef *arr = opt->default_val.arr;
            സ്ഥിരം അക്ഷരം              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            എങ്കിൽ (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            തുടരുക;
        }

        തിരഞ്ഞെടുപ്പ് (opt->type) {
            അവസ്ഥ AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_BOOL:
            അവസ്ഥ AV_OPT_TYPE_FLAGS:
            അവസ്ഥ AV_OPT_TYPE_INT:
            അവസ്ഥ AV_OPT_TYPE_UINT:
            അവസ്ഥ AV_OPT_TYPE_INT64:
            അവസ്ഥ AV_OPT_TYPE_UINT64:
            അവസ്ഥ AV_OPT_TYPE_DURATION:
            അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
            അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
                write_സംഖ്യ(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_DOUBLE:
            അവസ്ഥ AV_OPT_TYPE_FLOAT: {
                ഇരട്ട val;
                val = opt->default_val.dbl;
                write_സംഖ്യ(s, opt, dst, val, 1, 1, 1);
            }
            നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_സംഖ്യ(s, opt, dst, 1, val.den, val.അക്കം, 1);
            }
            നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_ദ്വിമാന:
                set_string_ദ്വിമാന(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
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
സ്ഥിതം പൂർണ്ണസംഖ്യ parse_താക്കോൽ_മൂല്യം_pair(ശൂന്യം *ctx, സ്ഥിരം അക്ഷരം **buf,
                                സ്ഥിരം അക്ഷരം *താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം *pairs_sep)
{
    അക്ഷരം *താക്കോൽ = av_get_token(buf, താക്കോൽ_val_sep);
    അക്ഷരം *val;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!താക്കോൽ)
        തിരികെ AVERROR(ENOMEM);

    എങ്കിൽ (*താക്കോൽ && strspn(*buf, താക്കോൽ_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        എങ്കിൽ (!val) {
            av_freep(&താക്കോൽ);
            തിരികെ AVERROR(ENOMEM);
        }
    } അല്ലെങ്കിൽ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", താക്കോൽ);
        av_free(താക്കോൽ);
        തിരികെ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", താക്കോൽ, val);

    ret = av_opt_set(ctx, താക്കോൽ, val, AV_OPT_തിരയൽ_CHILDREN);
    എങ്കിൽ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", താക്കോൽ);

    av_free(താക്കോൽ);
    av_free(val);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_set_options_string(ശൂന്യം *ctx, സ്ഥിരം അക്ഷരം *opts,
                          സ്ഥിരം അക്ഷരം *താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം *pairs_sep)
{
    പൂർണ്ണസംഖ്യ ret, എണ്ണം = 0;

    എങ്കിൽ (!opts)
        തിരികെ 0;

    ആകുമ്പോൾ (*opts) {
        എങ്കിൽ ((ret = parse_താക്കോൽ_മൂല്യം_pair(ctx, &opts, താക്കോൽ_val_sep, pairs_sep)) < 0)
            തിരികെ ret;
        എണ്ണം++;

        എങ്കിൽ (*opts)
            opts++;
    }

    തിരികെ എണ്ണം;
}

#define WHITESPACES " \n\t\r"

സ്ഥിതം പൂർണ്ണസംഖ്യ is_താക്കോൽ_char(അക്ഷരം c)
{
    തിരികെ (unsigned)((c | 32) - 'a') < 26 ||
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
സ്ഥിതം പൂർണ്ണസംഖ്യ get_താക്കോൽ(സ്ഥിരം അക്ഷരം **ropts, സ്ഥിരം അക്ഷരം *delim, അക്ഷരം **rkey)
{
    സ്ഥിരം അക്ഷരം *opts = *ropts;
    സ്ഥിരം അക്ഷരം *താക്കോൽ_start, *താക്കോൽ_end;

    താക്കോൽ_start = opts += strspn(opts, WHITESPACES);
    ആകുമ്പോൾ (is_താക്കോൽ_char(*opts))
        opts++;
    താക്കോൽ_end = opts;
    opts += strspn(opts, WHITESPACES);
    എങ്കിൽ (!*opts || !strchr(delim, *opts))
        തിരികെ AVERROR(EINVAL);
    opts++;
    എങ്കിൽ (!(*rkey = av_malloc(താക്കോൽ_end - താക്കോൽ_start + 1)))
        തിരികെ AVERROR(ENOMEM);
    memcpy(*rkey, താക്കോൽ_start, താക്കോൽ_end - താക്കോൽ_start);
    (*rkey)[താക്കോൽ_end - താക്കോൽ_start] = 0;
    *ropts = opts;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_താക്കോൽ_മൂല്യം(സ്ഥിരം അക്ഷരം **ropts,
                         സ്ഥിരം അക്ഷരം *താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം *pairs_sep,
                         unsigned flags,
                         അക്ഷരം **rkey, അക്ഷരം **rval)
{
    പൂർണ്ണസംഖ്യ ret;
    അക്ഷരം *താക്കോൽ = ശൂന്യ, *val;
    സ്ഥിരം അക്ഷരം *opts = *ropts;

    എങ്കിൽ ((ret = get_താക്കോൽ(&opts, താക്കോൽ_val_sep, &താക്കോൽ)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_താക്കോൽ))
        തിരികെ AVERROR(EINVAL);
    എങ്കിൽ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(താക്കോൽ);
        തിരികെ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = താക്കോൽ;
    *rval  = val;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_set_from_string(ശൂന്യം *ctx, സ്ഥിരം അക്ഷരം *opts,
                           സ്ഥിരം അക്ഷരം *സ്ഥിരം *shorthand,
                           സ്ഥിരം അക്ഷരം *താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം *pairs_sep)
{
    പൂർണ്ണസംഖ്യ ret, എണ്ണം = 0;
    സ്ഥിരം അക്ഷരം *dummy_shorthand = ശൂന്യ;
    സ്ഥിരം അക്ഷരം *താക്കോൽ;

    എങ്കിൽ (!opts)
        തിരികെ 0;
    എങ്കിൽ (!shorthand)
        shorthand = &dummy_shorthand;

    ആകുമ്പോൾ (*opts) {
        അക്ഷരം *parsed_താക്കോൽ, *മൂല്യം;
        ret = av_opt_get_താക്കോൽ_മൂല്യം(&opts, താക്കോൽ_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_താക്കോൽ : 0,
                                   &parsed_താക്കോൽ, &മൂല്യം);
        എങ്കിൽ (ret < 0) {
            എങ്കിൽ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            അല്ലെങ്കിൽ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            തിരികെ ret;
        }
        എങ്കിൽ (*opts)
            opts++;
        എങ്കിൽ (parsed_താക്കോൽ) {
            താക്കോൽ = parsed_താക്കോൽ;
            ആകുമ്പോൾ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } അല്ലെങ്കിൽ {
            താക്കോൽ = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", താക്കോൽ, മൂല്യം);
        എങ്കിൽ ((ret = av_opt_set(ctx, താക്കോൽ, മൂല്യം, 0)) < 0) {
            എങ്കിൽ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", താക്കോൽ);
            av_free(മൂല്യം);
            av_free(parsed_താക്കോൽ);
            തിരികെ ret;
        }

        av_free(മൂല്യം);
        av_free(parsed_താക്കോൽ);
        എണ്ണം++;
    }
    തിരികെ എണ്ണം;
}

ശൂന്യം av_opt_free(ശൂന്യം *obj)
{
    സ്ഥിരം AVOption *o = ശൂന്യ;
    ആകുമ്പോൾ ((o = av_opt_next(obj, o))) {
        ശൂന്യം *pitem = (uint8_t *)obj + o->offset;

        എങ്കിൽ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        അല്ലെങ്കിൽ
            opt_free_elem(o->type, pitem);
    }
}

പൂർണ്ണസംഖ്യ av_opt_set_dict2(ശൂന്യം *obj, AVDictionary **options, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    സ്ഥിരം AVDictionaryEntry *t = ശൂന്യ;
    AVDictionary    *tmp = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!options)
        തിരികെ 0;

    ആകുമ്പോൾ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->താക്കോൽ, t->മൂല്യം, തിരയൽ_flags);
        എങ്കിൽ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->താക്കോൽ, t->മൂല്യം, AV_DICT_MULTIKEY);
        എങ്കിൽ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->താക്കോൽ, t->മൂല്യം);
            av_dict_free(&tmp);
            തിരികെ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_set_dict(ശൂന്യം *obj, AVDictionary **options)
{
    തിരികെ av_opt_set_dict2(obj, options, 0);
}

സ്ഥിരം AVOption *av_opt_find(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *unit,
                            പൂർണ്ണസംഖ്യ opt_flags, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    തിരികെ av_opt_find2(obj, name, unit, opt_flags, തിരയൽ_flags, ശൂന്യ);
}

സ്ഥിരം AVOption *av_opt_find2(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, സ്ഥിരം അക്ഷരം *unit,
                             പൂർണ്ണസംഖ്യ opt_flags, പൂർണ്ണസംഖ്യ തിരയൽ_flags, ശൂന്യം **target_obj)
{
    സ്ഥിരം AVClass  *c;
    സ്ഥിരം AVOption *o = ശൂന്യ;

    എങ്കിൽ(!obj)
        തിരികെ ശൂന്യ;

    c= *(AVClass**)obj;

    എങ്കിൽ (!c)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (തിരയൽ_flags & AV_OPT_തിരയൽ_CHILDREN) {
        എങ്കിൽ (തിരയൽ_flags & AV_OPT_തിരയൽ_FAKE_OBJ) {
            ശൂന്യം *iter = ശൂന്യ;
            സ്ഥിരം AVClass *child;
            ആകുമ്പോൾ (child = av_opt_child_class_iterate(c, &iter))
                എങ്കിൽ (o = av_opt_find2(&child, name, unit, opt_flags, തിരയൽ_flags, ശൂന്യ))
                    തിരികെ o;
        } അല്ലെങ്കിൽ {
            ശൂന്യം *child = ശൂന്യ;
            ആകുമ്പോൾ (child = av_opt_child_next(obj, child))
                എങ്കിൽ (o = av_opt_find2(child, name, unit, opt_flags, തിരയൽ_flags, target_obj))
                    തിരികെ o;
        }
    }

    ആകുമ്പോൾ (o = av_opt_next(obj, o)) {
        എങ്കിൽ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            എങ്കിൽ (target_obj) {
                എങ്കിൽ (!(തിരയൽ_flags & AV_OPT_തിരയൽ_FAKE_OBJ))
                    *target_obj = obj;
                അല്ലെങ്കിൽ
                    *target_obj = ശൂന്യ;
            }
            തിരികെ o;
        }
    }
    തിരികെ ശൂന്യ;
}

ശൂന്യം *av_opt_child_next(ശൂന്യം *obj, ശൂന്യം *prev)
{
    സ്ഥിരം AVClass *c = *(AVClass **)obj;
    എങ്കിൽ (c->child_next)
        തിരികെ c->child_next(obj, prev);
    തിരികെ ശൂന്യ;
}

സ്ഥിരം AVClass *av_opt_child_class_iterate(സ്ഥിരം AVClass *parent, ശൂന്യം **iter)
{
    എങ്കിൽ (parent->child_class_iterate)
        തിരികെ parent->child_class_iterate(iter);
    തിരികെ ശൂന്യ;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_copy_elem(ശൂന്യം *logctx, എണ്ണൽ AVOptionType type,
                         ശൂന്യം *dst, സ്ഥിരം ശൂന്യം *src)
{
    എങ്കിൽ (type == AV_OPT_TYPE_STRING) {
        സ്ഥിരം അക്ഷരം *src_str = *(സ്ഥിരം അക്ഷരം *സ്ഥിരം *)src;
        അക്ഷരം         **dstp =  (അക്ഷരം **)dst;
        എങ്കിൽ (*dstp != src_str)
            av_freep(dstp);
        എങ്കിൽ (src_str) {
            *dstp = av_strdup(src_str);
            എങ്കിൽ (!*dstp)
                തിരികെ AVERROR(ENOMEM);
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (type == AV_OPT_TYPE_ദ്വിമാന) {
        സ്ഥിരം uint8_t *സ്ഥിരം *src8 = (സ്ഥിരം uint8_t *സ്ഥിരം *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        പൂർണ്ണസംഖ്യ len = *(സ്ഥിരം പൂർണ്ണസംഖ്യ *)(src8 + 1);
        എങ്കിൽ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        എങ്കിൽ (len && !*dst8) {
            *(പൂർണ്ണസംഖ്യ *)(dst8 + 1) = 0;
            തിരികെ AVERROR(ENOMEM);
        }
        *(പൂർണ്ണസംഖ്യ *)(dst8 + 1) = len;
    } അല്ലെങ്കിൽ എങ്കിൽ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } അല്ലെങ്കിൽ എങ്കിൽ (type == AV_OPT_TYPE_DICT) {
        സ്ഥിരം AVDictionary *sdict = *(സ്ഥിരം AVDictionary * സ്ഥിരം *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        എങ്കിൽ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ശൂന്യ;
        തിരികെ av_dict_copy(ddictp, sdict, 0);
    } അല്ലെങ്കിൽ എങ്കിൽ (type == AV_OPT_TYPE_CHLAYOUT) {
        സ്ഥിരം AVChannelLayout *slayout = (സ്ഥിരം AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        എങ്കിൽ (dlayout != slayout) {
            എങ്കിൽ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ശൂന്യ;
            തിരികെ av_channel_layout_copy(dst, src);
        }
    } അല്ലെങ്കിൽ എങ്കിൽ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } അല്ലെങ്കിൽ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        തിരികെ AVERROR(EINVAL);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_copy_array(ശൂന്യം *logctx, സ്ഥിരം AVOption *o,
                          ശൂന്യം **pdst, സ്ഥിരം ശൂന്യം * സ്ഥിരം *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    ശൂന്യം         *dst = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (*pdst == *psrc) {
        *pdst                   = ശൂന്യ;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    എങ്കിൽ (!dst)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(ശൂന്യം**)psrc, i));
        എങ്കിൽ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            തിരികെ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_copy(ശൂന്യം *dst, സ്ഥിരം ശൂന്യം *src)
{
    സ്ഥിരം AVOption *o = ശൂന്യ;
    സ്ഥിരം AVClass *c;
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (!src)
        തിരികെ AVERROR(EINVAL);

    c = *(AVClass **)src;
    എങ്കിൽ (!c || c != *(AVClass **)dst)
        തിരികെ AVERROR(EINVAL);

    ആകുമ്പോൾ ((o = av_opt_next(src, o))) {
        ശൂന്യം *field_dst = (uint8_t *)dst + o->offset;
        ശൂന്യം *field_src = (uint8_t *)src + o->offset;

        പൂർണ്ണസംഖ്യ err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        എങ്കിൽ (err < 0)
            ret = err;
    }
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_get_array_size(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags,
                          unsigned പൂർണ്ണസംഖ്യ *out_val)
{
    ശൂന്യം *target_obj, *parray;
    സ്ഥിരം AVOption *o;

    o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        തിരികെ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_get_array(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags,
                     unsigned പൂർണ്ണസംഖ്യ start_elem, unsigned പൂർണ്ണസംഖ്യ nb_elems,
                     എണ്ണൽ AVOptionType out_type, ശൂന്യം *out_val)
{
    സ്ഥിരം size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    സ്ഥിരം AVOption *o;
    ശൂന്യം *target_obj;

    സ്ഥിരം ശൂന്യം *parray;
    unsigned array_size;

    പൂർണ്ണസംഖ്യ ret;

    o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target_obj);
    എങ്കിൽ (!o || !target_obj)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    എങ്കിൽ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        തിരികെ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    എങ്കിൽ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (unsigned i = 0; i < nb_elems; i++) {
        സ്ഥിരം ശൂന്യം *src = opt_array_pelem(o, *(ശൂന്യം**)parray, start_elem + i);
        ശൂന്യം       *dst = (uint8_t*)out_val + i * elem_size_out;

        എങ്കിൽ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            എങ്കിൽ (ret < 0)
                പോകുക fail;
        } അല്ലെങ്കിൽ എങ്കിൽ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, വലുപ്പം(buf), src, തിരയൽ_flags);
            എങ്കിൽ (ret < 0)
                പോകുക fail;

            എങ്കിൽ (out == buf) {
                out = av_strdup(buf);
                എങ്കിൽ (!out) {
                    ret = AVERROR(ENOMEM);
                    പോകുക fail;
                }
            }

            *(uint8_t**)dst = out;
        } അല്ലെങ്കിൽ എങ്കിൽ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            ഇരട്ട     അക്കം = 1.0;
            പൂർണ്ണസംഖ്യ        den = 1;
            int64_t intnum = 1;

            ret = read_സംഖ്യ(o, src, &അക്കം, &den, &intnum);
            എങ്കിൽ (ret < 0)
                പോകുക fail;

            തിരഞ്ഞെടുപ്പ് (out_type) {
            അവസ്ഥ AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (അക്കം == den) ?  intnum : അക്കം * intnum / den;
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_DOUBLE:
                *(ഇരട്ട*)dst = അക്കം * intnum / den;
                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (അക്കം == 1.0 && (പൂർണ്ണസംഖ്യ)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(അക്കം * intnum / den);
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി: av_assert0(0);
            }
        } അല്ലെങ്കിൽ
            തിരികെ AVERROR(ENOSYS);
    }

    തിരികെ 0;
fail:
    വേണ്ടി (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_set_array(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags,
                     unsigned പൂർണ്ണസംഖ്യ start_elem, unsigned പൂർണ്ണസംഖ്യ nb_elems,
                     എണ്ണൽ AVOptionType val_type, സ്ഥിരം ശൂന്യം *val)
{
    സ്ഥിരം size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    സ്ഥിരം AVOption *o;
    സ്ഥിരം AVOptionArrayDef *arr;
    ശൂന്യം *target_obj;

    ശൂന്യം *parray;
    ശൂന്യം *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    പൂർണ്ണസംഖ്യ ret = 0;

    ret = opt_set_init(obj, name, തിരയൽ_flags, 0, &target_obj, &o, &parray);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    എങ്കിൽ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        തിരികെ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    എങ്കിൽ (start_elem > *array_size)
        തിരികെ AVERROR(EINVAL);

    // compute new array size
    എങ്കിൽ (!val) {
        എങ്കിൽ (*array_size - start_elem < nb_elems)
            തിരികെ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } അല്ലെങ്കിൽ എങ്കിൽ (തിരയൽ_flags & AV_OPT_ARRAY_REPLACE) {
        എങ്കിൽ (start_elem >= UINT_MAX - nb_elems)
            തിരികെ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (nb_elems >= UINT_MAX - *array_size)
            തിരികെ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    എങ്കിൽ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        തിരികെ AVERROR(EINVAL);

    // desired operation is shrinking the array
    എങ്കിൽ (!val) {
        ശൂന്യം *array = *(ശൂന്യം**)parray;

        വേണ്ടി (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        എങ്കിൽ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            എങ്കിൽ (!array)
                തിരികെ AVERROR(ENOMEM);

            *(ശൂന്യം**)parray = array;
        } അല്ലെങ്കിൽ
            av_freep(parray);

        *array_size = new_size;

        തിരികെ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    എങ്കിൽ (!new_elems)
        തിരികെ AVERROR(ENOMEM);

    // convert/validate each new element
    വേണ്ടി (unsigned i = 0; i < nb_elems; i++) {
        ശൂന്യം       *dst = opt_array_pelem(o, new_elems, i);
        സ്ഥിരം ശൂന്യം *src = (uint8_t*)val + i * elem_size_val;

        ഇരട്ട     അക്കം = 1.0;
        പൂർണ്ണസംഖ്യ        den = 1;
        int64_t intnum = 1;

        എങ്കിൽ (val_type == TYPE_BASE(o->type)) {
            പൂർണ്ണസംഖ്യ err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            എങ്കിൽ (ret < 0)
                പോകുക fail;

            // validate the range for numeric options
            err = read_സംഖ്യ(o, dst, &അക്കം, &den, &intnum);
            എങ്കിൽ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < അക്കം * intnum || o->min * den > അക്കം * intnum)) {
                അക്കം = den ? അക്കം * intnum / den : (അക്കം && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, അക്കം, o->min, o->max);
                ret = AVERROR(ERANGE);
                പോകുക fail;
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(സ്ഥിരം അക്ഷരം **)src, dst);
            എങ്കിൽ (ret < 0)
                പോകുക fail;
        } അല്ലെങ്കിൽ എങ്കിൽ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            തിരഞ്ഞെടുപ്പ് (val_type) {
            അവസ്ഥ AV_OPT_TYPE_INT:       intnum = *(പൂർണ്ണസംഖ്യ*)src;                നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_FLOAT:     അക്കം    = *(ദശാംശം*)src;              നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_DOUBLE:    അക്കം    = *(ഇരട്ട*)src;             നിർത്തുക;
            അവസ്ഥ AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->അക്കം;
                                        den    = ((AVRational*)src)->den;   നിർത്തുക;
            സ്ഥിരസ്ഥിതി: av_assert0(0);
            }

            ret = write_സംഖ്യ(obj, o, dst, അക്കം, den, intnum, 0);
            എങ്കിൽ (ret < 0)
                പോകുക fail;
        } അല്ലെങ്കിൽ {
            ret = AVERROR(ENOSYS);
            പോകുക fail;
        }
    }

    // commit new elements to the array
    എങ്കിൽ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(ശൂന്യം**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = ശൂന്യ;
        nb_elems  = 0;
    } അല്ലെങ്കിൽ {
        ശൂന്യം *array = av_realloc_array(*(ശൂന്യം**)parray, new_size, elem_size);
        എങ്കിൽ (!array) {
            ret = AVERROR(ENOMEM);
            പോകുക fail;
        }

        എങ്കിൽ (തിരയൽ_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            വേണ്ടി (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } അല്ലെങ്കിൽ {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(ശൂന്യം**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_query_ranges(AVOptionRanges **ranges_arg, ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *താക്കോൽ, പൂർണ്ണസംഖ്യ flags)
{
    പൂർണ്ണസംഖ്യ ret;
    സ്ഥിരം AVClass *c = *(AVClass**)obj;
    പൂർണ്ണസംഖ്യ (*callback)(AVOptionRanges **, ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *താക്കോൽ, പൂർണ്ണസംഖ്യ flags) = c->query_ranges;

    എങ്കിൽ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, താക്കോൽ, flags);
    എങ്കിൽ (ret >= 0) {
        എങ്കിൽ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_opt_query_ranges_default(AVOptionRanges **ranges_arg, ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *താക്കോൽ, പൂർണ്ണസംഖ്യ flags)
{
    AVOptionRanges *ranges = av_mallocz(വലുപ്പം(*ranges));
    AVOptionRange **range_array = av_mallocz(വലുപ്പം(ശൂന്യം*));
    AVOptionRange *range = av_mallocz(വലുപ്പം(*range));
    സ്ഥിരം AVOption *field = av_opt_find(obj, താക്കോൽ, ശൂന്യ, 0, flags);
    പൂർണ്ണസംഖ്യ ret;

    *ranges_arg = ശൂന്യ;

    എങ്കിൽ (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->മൂല്യം_min = field->min;
    range->മൂല്യം_max = field->max;

    തിരഞ്ഞെടുപ്പ് (field->type) {
    അവസ്ഥ AV_OPT_TYPE_BOOL:
    അവസ്ഥ AV_OPT_TYPE_INT:
    അവസ്ഥ AV_OPT_TYPE_UINT:
    അവസ്ഥ AV_OPT_TYPE_INT64:
    അവസ്ഥ AV_OPT_TYPE_UINT64:
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
    അവസ്ഥ AV_OPT_TYPE_DURATION:
    അവസ്ഥ AV_OPT_TYPE_COLOR:
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->മൂല്യം_min = -1;
        range->മൂല്യം_max = INT_MAX;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->മൂല്യം_min = 0;
        range->മൂല്യം_max = INT_MAX/8;
        നിർത്തുക;
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->മൂല്യം_min = 1;
        range->മൂല്യം_max = INT_MAX;
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        ret = AVERROR(ENOSYS);
        പോകുക fail;
    }

    *ranges_arg = ranges;
    തിരികെ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    തിരികെ ret;
}

ശൂന്യം av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    പൂർണ്ണസംഖ്യ i;
    AVOptionRanges *ranges = *rangesp;

    എങ്കിൽ (!ranges)
        തിരികെ;

    വേണ്ടി (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        എങ്കിൽ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

പൂർണ്ണസംഖ്യ av_opt_is_set_to_default(ശൂന്യം *obj, സ്ഥിരം AVOption *o)
{
    int64_t i64;
    ഇരട്ട d;
    AVRational q;
    പൂർണ്ണസംഖ്യ ret, w, h;
    അക്ഷരം *str;
    ശൂന്യം *dst;

    എങ്കിൽ (!o || !obj)
        തിരികെ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    എങ്കിൽ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        സ്ഥിരം അക്ഷരം *def = o->default_val.arr ? o->default_val.arr->def : ശൂന്യ;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        എങ്കിൽ (!!val != !!def)
            ret = 0;
        അല്ലെങ്കിൽ എങ്കിൽ (val)
            ret = !strcmp(val, def);
        അല്ലെങ്കിൽ
            ret = 1;

        av_freep(&val);

        തിരികെ ret;
    }

    തിരഞ്ഞെടുപ്പ് (o->type) {
    അവസ്ഥ AV_OPT_TYPE_CONST:
        തിരികെ 1;
    അവസ്ഥ AV_OPT_TYPE_BOOL:
    അവസ്ഥ AV_OPT_TYPE_FLAGS:
    അവസ്ഥ AV_OPT_TYPE_PIXEL_FMT:
    അവസ്ഥ AV_OPT_TYPE_SAMPLE_FMT:
    അവസ്ഥ AV_OPT_TYPE_INT:
    അവസ്ഥ AV_OPT_TYPE_UINT:
    അവസ്ഥ AV_OPT_TYPE_DURATION:
    അവസ്ഥ AV_OPT_TYPE_INT64:
    അവസ്ഥ AV_OPT_TYPE_UINT64:
        read_സംഖ്യ(o, dst, ശൂന്യ, ശൂന്യ, &i64);
        തിരികെ o->default_val.i64 == i64;
    അവസ്ഥ AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        എങ്കിൽ (o->default_val.str) {
            എങ്കിൽ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                തിരികെ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        തിരികെ ret;
    }
    അവസ്ഥ AV_OPT_TYPE_STRING:
        str = *(അക്ഷരം **)dst;
        എങ്കിൽ (str == o->default_val.str) //2 NULLs
            തിരികെ 1;
        എങ്കിൽ (!str || !o->default_val.str) //1 NULL
            തിരികെ 0;
        തിരികെ !strcmp(str, o->default_val.str);
    അവസ്ഥ AV_OPT_TYPE_DOUBLE:
        d = *(ഇരട്ട *)dst;
        തിരികെ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    അവസ്ഥ AV_OPT_TYPE_FLOAT:
        d = *(ദശാംശം *)dst;
        തിരികെ (ദശാംശം)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    അവസ്ഥ AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        തിരികെ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    അവസ്ഥ AV_OPT_TYPE_ദ്വിമാന: {
        ഘടന {
            uint8_t *data;
            പൂർണ്ണസംഖ്യ size;
        } tmp = {0};
        പൂർണ്ണസംഖ്യ opt_size = *(പൂർണ്ണസംഖ്യ *)((ശൂന്യം **)dst + 1);
        ശൂന്യം *opt_ptr = *(ശൂന്യം **)dst;
        എങ്കിൽ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            തിരികെ 1;
        എങ്കിൽ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            തിരികെ 0;
        എങ്കിൽ (opt_size != strlen(o->default_val.str) / 2)
            തിരികെ 0;
        ret = set_string_ദ്വിമാന(ശൂന്യ, ശൂന്യ, o->default_val.str, &tmp.data);
        എങ്കിൽ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        തിരികെ ret;
    }
    അവസ്ഥ AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ശൂന്യ;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        സ്ഥിരം AVDictionaryEntry *en1 = ശൂന്യ;
        സ്ഥിരം AVDictionaryEntry *en2 = ശൂന്യ;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        എങ്കിൽ (ret < 0) {
            av_dict_free(&dict1);
            തിരികെ ret;
        }
        ചെയ്യുക {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ആകുമ്പോൾ (en1 && en2 && !strcmp(en1->താക്കോൽ, en2->താക്കോൽ) && !strcmp(en1->മൂല്യം, en2->മൂല്യം));
        av_dict_free(&dict1);
        തിരികെ (!en1 && !en2);
    }
    അവസ്ഥ AV_OPT_TYPE_IMAGE_SIZE:
        എങ്കിൽ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        അല്ലെങ്കിൽ എങ്കിൽ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            തിരികെ ret;
        തിരികെ (w == *(പൂർണ്ണസംഖ്യ *)dst) && (h == *((പൂർണ്ണസംഖ്യ *)dst+1));
    അവസ്ഥ AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        എങ്കിൽ (o->default_val.str) {
            എങ്കിൽ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                തിരികെ ret;
        }
        തിരികെ !av_cmp_q(*(AVRational*)dst, q);
    അവസ്ഥ AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        എങ്കിൽ (o->default_val.str) {
            എങ്കിൽ ((ret = av_parse_color(color, o->default_val.str, -1, ശൂന്യ)) < 0)
                തിരികെ ret;
        }
        തിരികെ !memcmp(color, dst, വലുപ്പം(color));
    }
    സ്ഥിരസ്ഥിതി:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        നിർത്തുക;
    }
    തിരികെ AVERROR_PATCHWELCOME;
}

പൂർണ്ണസംഖ്യ av_opt_is_set_to_default_by_name(ശൂന്യം *obj, സ്ഥിരം അക്ഷരം *name, പൂർണ്ണസംഖ്യ തിരയൽ_flags)
{
    സ്ഥിരം AVOption *o;
    ശൂന്യം *target;
    എങ്കിൽ (!obj)
        തിരികെ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ശൂന്യ, 0, തിരയൽ_flags, &target);
    എങ്കിൽ (!o)
        തിരികെ AVERROR_OPTION_NOT_FOUND;
    തിരികെ av_opt_is_set_to_default(target, o);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ opt_serialize(ശൂന്യം *obj, പൂർണ്ണസംഖ്യ opt_flags, പൂർണ്ണസംഖ്യ flags, പൂർണ്ണസംഖ്യ *cnt,
                         AVBPrint *bprint, സ്ഥിരം അക്ഷരം താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം pairs_sep)
{
    സ്ഥിരം AVOption *o = ശൂന്യ;
    ശൂന്യം *child = ശൂന്യ;
    uint8_t *buf;
    പൂർണ്ണസംഖ്യ ret;
    സ്ഥിരം അക്ഷരം special_chars[] = {pairs_sep, താക്കോൽ_val_sep, '\0'};

    എങ്കിൽ (flags & AV_OPT_SERIALIZE_തിരയൽ_CHILDREN)
        ആകുമ്പോൾ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                താക്കോൽ_val_sep, pairs_sep);
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
        }

    ആകുമ്പോൾ (o = av_opt_next(obj, o)) {
        എങ്കിൽ (o->type == AV_OPT_TYPE_CONST)
            തുടരുക;
        എങ്കിൽ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            എങ്കിൽ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                എങ്കിൽ (o->flags == opt_flags)
                    തുടരുക;
            } അല്ലെങ്കിൽ എങ്കിൽ ((o->flags & opt_flags) == opt_flags)
                തുടരുക;
        } അല്ലെങ്കിൽ {
            എങ്കിൽ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                തുടരുക;
            അല്ലെങ്കിൽ എങ്കിൽ (((o->flags & opt_flags) != opt_flags))
                തുടരുക;
        }
        എങ്കിൽ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            തുടരുക;
        എങ്കിൽ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ശൂന്യ);
            തിരികെ ret;
        }
        എങ്കിൽ (buf) {
            എങ്കിൽ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &താക്കോൽ_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_opt_serialize(ശൂന്യം *obj, പൂർണ്ണസംഖ്യ opt_flags, പൂർണ്ണസംഖ്യ flags, അക്ഷരം **buffer,
                     സ്ഥിരം അക്ഷരം താക്കോൽ_val_sep, സ്ഥിരം അക്ഷരം pairs_sep)
{
    AVBPrint bprint;
    പൂർണ്ണസംഖ്യ ret, cnt = 0;

    എങ്കിൽ (pairs_sep == '\0' || താക്കോൽ_val_sep == '\0' || pairs_sep == താക്കോൽ_val_sep ||
        pairs_sep == '\\' || താക്കോൽ_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        തിരികെ AVERROR(EINVAL);
    }

    എങ്കിൽ (!obj || !buffer)
        തിരികെ AVERROR(EINVAL);

    *buffer = ശൂന്യ;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        താക്കോൽ_val_sep, pairs_sep);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
    തിരികെ 0;
}
