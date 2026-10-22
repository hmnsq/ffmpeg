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

#ଅନ୍ତର୍ଭାଵ "avutil.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "channel_layout.h"
#ଅନ୍ତର୍ଭାଵ "dict.h"
#ଅନ୍ତର୍ଭାଵ "eval.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "parseutils.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "mathematics.h"
#ଅନ୍ତର୍ଭାଵ "opt.h"
#ଅନ୍ତର୍ଭାଵ "samplefmt.h"
#ଅନ୍ତର୍ଭାଵ "bprint.h"

#ଅନ୍ତର୍ଭାଵ <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ଅଚଳ AVOption *av_opt_next(ଅଚଳ ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *last)
{
    ଅଚଳ AVClass *class;
    ଯଦି (!obj)
        ଫେରନ୍ତୁ ଖାଲି;
    class = *(ଅଚଳ AVClass**)obj;
    ଯଦି (!last && class && class->option && class->option[0].name)
        ଫେରନ୍ତୁ class->option;
    ଯଦି (last && last[1].name)
        ଫେରନ୍ତୁ ++last;
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    size_t      size;
    ଅଚଳ ଅକ୍ଷର *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { ଆକାର(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { ଆକାର(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { ଆକାର(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { ଆକାର(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { ଆକାର(ଦ୍ୱିଗୁଣ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { ଆକାର(ଦଶମିକ),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { ଆକାର(ଅକ୍ଷର *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { ଆକାର(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ଦ୍ୱିମିକ]        = { ଆକାର(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { ଆକାର(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { ଆକାର(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { ଆକାର(ଗଣନା AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { ଆକାର(ଗଣନା AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { ଆକାର(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { ଆକାର(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { ଆକାର(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { ଆକାର(ପୂର୍ଣ୍ଣସଂଖ୍ୟା),            "<boolean>" },
};

// option is plain old data
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_is_pod(ଗଣନା AVOptionType type)
{
    ବାଛ (type) {
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
    ସ୍ଥିତି AV_OPT_TYPE_INT64:
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
    ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
    ସ୍ଥିତି AV_OPT_TYPE_DURATION:
    ସ୍ଥିତି AV_OPT_TYPE_COLOR:
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
        ଫେରନ୍ତୁ 1;
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର uint8_t opt_array_sep(ଅଚଳ AVOption *o)
{
    ଅଚଳ AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ଫେରନ୍ତୁ (d && d->sep) ? d->sep : ',';
}

ସ୍ଥିର ଶୂନ୍ୟ *opt_array_pelem(ଅଚଳ AVOption *o, ଶୂନ୍ୟ *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ଫେରନ୍ତୁ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

ସ୍ଥିର unsigned *opt_array_pcount(ଅଚଳ ଶୂନ୍ୟ *parray)
{
    ଫେରନ୍ତୁ (unsigned *)((ଅଚଳ ଶୂନ୍ୟ * ଅଚଳ *)parray + 1);
}

ସ୍ଥିର ଶୂନ୍ୟ opt_free_elem(ଗଣନା AVOptionType type, ଶୂନ୍ୟ *ptr)
{
    ବାଛ (TYPE_BASE(type)) {
    ସ୍ଥିତି AV_OPT_TYPE_STRING:
    ସ୍ଥିତି AV_OPT_TYPE_ଦ୍ୱିମିକ:
        av_freep(ptr);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ opt_free_array(ଅଚଳ AVOption *o, ଶୂନ୍ୟ *parray, unsigned *ଗଣନା_2)
{
    ପାଇଁ (unsigned i = 0; i < *ଗଣନା_2; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(ଶୂନ୍ୟ **)parray, i));

    av_freep(parray);
    *ଗଣନା_2 = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_set_init(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା require_type,
                        ଶୂନ୍ୟ **ptgt, ଅଚଳ AVOption **po, ଶୂନ୍ୟ **pdst)
{
    ଶୂନ୍ୟ *logctx;
    ଅଚଳ AVOption *o;
    ଶୂନ୍ୟ *tgt;

    o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &tgt);
    ଯଦି (!o || (!tgt && !(ସନ୍ଧାନ_flags & AV_OPT_ସନ୍ଧାନ_FAKE_OBJ)))
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;

    ଯଦି (o->flags & AV_OPT_FLAG_READONLY)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    logctx = tgt ? obj : ଖାଲି;

    ଯଦି (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = ଖାଲି;
        ଅଚଳ AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ଅଚଳ AVClass**)tgt;
        ଯଦି (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        ଯଦି (!state_flags && obj != tgt) {
            class = *(ଅଚଳ AVClass**)obj;
            ଯଦି (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        ଯଦି (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    ଯଦି (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ଯଦି (po)
        *po   = o;
    ଯଦି (ptgt)
        *ptgt = tgt;
    ଯଦି (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : ଖାଲି;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର AVRational double_to_rational(ଦ୍ୱିଗୁଣ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ଯଦି ((!r.ଅଙ୍କ || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ଫେରନ୍ତୁ r;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା read_ସଂଖ୍ୟା(ଅଚଳ AVOption *o, ଅଚଳ ଶୂନ୍ୟ *dst, ଦ୍ୱିଗୁଣ *ଅଙ୍କ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *den, int64_t *intnum)
{
    ବାଛ (TYPE_BASE(o->type)) {
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା*)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ଗଣନା AVPixelFormat *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ଗଣନା AVSampleFormat *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
        *intnum = *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
        *intnum = *(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_DURATION:
    ସ୍ଥିତି AV_OPT_TYPE_INT64:
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
        *ଅଙ୍କ = *(ଦଶମିକ *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
        *ଅଙ୍କ = *(ଦ୍ୱିଗୁଣ *)dst;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->ଅଙ୍କ;
        *den    = ((AVRational *)dst)->den;
        ଫେରନ୍ତୁ 0;
    ସ୍ଥିତି AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ଫେରନ୍ତୁ 0;
    }
    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା write_ସଂଖ୍ୟା(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଶୂନ୍ୟ *dst,
                        ଦ୍ୱିଗୁଣ ଅଙ୍କ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା den, int64_t intnum,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ignore_range)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ଅଚଳ ଗଣନା AVOptionType type = TYPE_BASE(o->type);

    ଯଦି (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < ଅଙ୍କ * intnum || o->min * den > ଅଙ୍କ * intnum)) {
        ଅଙ୍କ = den ? ଅଙ୍କ * intnum / den : (ଅଙ୍କ && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               ଅଙ୍କ, o->name, o->min, o->max);
        ଫେରନ୍ତୁ AVERROR(ERANGE);
    }
    ଯଦି (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        ଦ୍ୱିଗୁଣ d = ଅଙ୍କ*intnum/den;
        ଯଦି (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   ଅଙ୍କ*intnum/den, o->name);
            ଫେରନ୍ତୁ AVERROR(ERANGE);
        }
    }

    ଯଦି (!dst)
        ଫେରନ୍ତୁ 0;

    ବାଛ (type) {
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
        *(ଗଣନା AVPixelFormat *)dst = llrint(ଅଙ୍କ / den) * intnum;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
        *(ଗଣନା AVSampleFormat *)dst = llrint(ଅଙ୍କ / den) * intnum;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
        *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst = llrint(ଅଙ୍କ / den) * intnum;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_DURATION:
    ସ୍ଥିତି AV_OPT_TYPE_INT64:{
        ଦ୍ୱିଗୁଣ d = ଅଙ୍କ / den;
        ଯଦି (intnum == 1 && d == (ଦ୍ୱିଗୁଣ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ଅନ୍ୟଥା
            *(int64_t *)dst = llrint(d) * intnum;
        ଭାଙ୍ଗ;}
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:{
        ଦ୍ୱିଗୁଣ d = ଅଙ୍କ / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ଯଦି (intnum == 1 && d == (ଦ୍ୱିଗୁଣ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ଅନ୍ୟଥା ଯଦି (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ଅନ୍ୟଥା {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        ଭାଙ୍ଗ;}
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
        *(ଦଶମିକ *)dst = ଅଙ୍କ * intnum / den;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
        *(ଦ୍ୱିଗୁଣ    *)dst = ଅଙ୍କ * intnum / den;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
        ଯଦି ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା) ଅଙ୍କ == ଅଙ୍କ)
            *(AVRational *)dst = (AVRational) { ଅଙ୍କ *intnum, den };
        ଅନ୍ୟଥା
            *(AVRational *)dst = double_to_rational(ଅଙ୍କ * intnum / den);
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା hexchar2int(ଅକ୍ଷର c) {
    ଯଦି (c >= '0' && c <= '9')
        ଫେରନ୍ତୁ c - '0';
    ଯଦି (c >= 'a' && c <= 'f')
        ଫେରନ୍ତୁ c - 'a' + 10;
    ଯଦି (c >= 'A' && c <= 'F')
        ଫେରନ୍ତୁ c - 'A' + 10;
    ଫେରନ୍ତୁ -1;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_ଦ୍ୱିମିକ(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t **dst)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *lendst;
    uint8_t *bin, *ptr;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା len;

    ଯଦି (dst) {
        lendst = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ଯଦି (!val || !(len = strlen(val)))
        ଫେରନ୍ତୁ 0;

    ଯଦି (len & 1)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ଯଦି (!ptr)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    ଯେତେବେଳେ (*val) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା a = hexchar2int(*val++);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା b = hexchar2int(*val++);
        ଯଦି (a < 0 || b < 0) {
            av_free(bin);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ଯଦି (dst) {
        *dst    = bin;
        *lendst = len;
    } ଅନ୍ୟଥା {
        av_free(bin);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t **dst)
{
    ଯଦି (!dst)
        ଫେରନ୍ତୁ 0;
    av_freep(dst);
    ଯଦି (!val)
        ଫେରନ୍ତୁ 0;
    *dst = av_strdup(val);
    ଫେରନ୍ତୁ *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_ସଂଖ୍ୟା(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *target_obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, ଶୂନ୍ୟ *dst)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ଅଚଳ ଗଣନା AVOptionType type = TYPE_BASE(o->type);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ, den;
        ଅକ୍ଷର c;
        ଯଦି (sscanf(val, "%d%*1[:/]%d%c", &ଅଙ୍କ, &den, &c) == 2) {
            ଯଦି ((ret = write_ସଂଖ୍ୟା(obj, o, dst, 1, den, ଅଙ୍କ, 0)) >= 0)
                ଫେରନ୍ତୁ ret;
            ret = 0;
        }
    }

    ପାଇଁ (;;) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0;
        ଅକ୍ଷର buf[256];
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା cmd = 0;
        ଦ୍ୱିଗୁଣ d;
        int64_t intnum = 1;

        ଯଦି (type == AV_OPT_TYPE_FLAGS) {
            ଯଦି (*val == '+' || *val == '-')
                cmd = *(val++);
            ପାଇଁ (; i < ଆକାର(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା res;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ci = 0;
            ଦ୍ୱିଗୁଣ const_ମୂଲ୍ୟଗୁଡ଼ିକ[64];
            ଅଚଳ ଅକ୍ଷର * const_names[64];
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_ସନ୍ଧାନ_CHILDREN : 0;
            ଅଚଳ AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, ସନ୍ଧାନ_flags);
            ଯଦି (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ଯଦି (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ଅନ୍ୟଥା {
                ଯଦି (o->unit) {
                    ପାଇଁ (o_named = ଖାଲି; o_named = av_opt_next(target_obj, o_named); ) {
                        ଯଦି (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ଯଦି (ci + 6 >= FF_ARRAY_ELEMS(const_ମୂଲ୍ୟଗୁଡ଼ିକ)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ଫେରନ୍ତୁ AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci++] = o->max;
                const_names [ci  ] = "min";
                const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci++] = o->min;
                const_names [ci  ] = "none";
                const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci++] = 0;
                const_names [ci  ] = "all";
                const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci++] = ~0;
                const_names [ci] = ଖାଲି;
                const_ମୂଲ୍ୟଗୁଡ଼ିକ[ci] = 0;

                res = av_ପଦସମଷ୍ଟି_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_ମୂଲ୍ୟଗୁଡ଼ିକ, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, 0, obj);
                ଯଦି (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ଫେରନ୍ତୁ res;
                }
            }
        }
        ଯଦି (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା*)dst;
            ଯଦି (cmd == '+')
                d = intnum | (int64_t)d;
            ଅନ୍ୟଥା ଯଦି (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ଯଦି ((ret = write_ସଂଖ୍ୟା(obj, o, dst, d, 1, 1, 0)) < 0)
            ଫେରନ୍ତୁ ret;
        val += i;
        ଯଦି (!i || !*val)
            ଫେରନ୍ତୁ 0;
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_image_size(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା tmp[2];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!val || !strcmp(val, "none")) {
        ଯଦି (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ଫେରନ୍ତୁ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    ଯଦି (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ଫେରନ୍ତୁ ret;
    }
    ଯଦି (dst)
        memcpy(dst, tmp, ଆକାର(tmp));
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_video_rate(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, AVRational *dst)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    AVRational tmp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_parse_video_rate(&tmp, val);
    ଯଦି (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ଯଦି (dst)
        *dst = tmp;
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_color(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t *dst)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!val) {
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ଯଦି (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ଫେରନ୍ତୁ ret;
        }
        ଯଦି (dst)
            memcpy(dst, tmp, ଆକାର(tmp));
        ଫେରନ୍ତୁ ret;
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *get_bool_name(ପୂର୍ଣ୍ଣସଂଖ୍ୟା val)
{
    ଯଦି (val < 0)
        ଫେରନ୍ତୁ "auto";
    ଫେରନ୍ତୁ val ? "true" : "false";
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_bool(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା n;

    ଯଦି (!val)
        ଫେରନ୍ତୁ 0;

    ଯଦି (!strcmp(val, "auto")) {
        n = -1;
    } ଅନ୍ୟଥା ଯଦି (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ଅନ୍ୟଥା ଯଦି (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ଅନ୍ୟଥା {
        ଅକ୍ଷର *end = ଖାଲି;
        n = strtol(val, &end, 10);
        ଯଦି (val + strlen(val) != end)
            ଯାଅ fail;
    }

    ଯଦି (n < o->min || n > o->max)
        ଯାଅ fail;

    ଯଦି (dst)
    *dst = n;
    ଫେରନ୍ତୁ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t *dst,
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା fmt_nb, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ((*get_fmt)(ଅଚଳ ଅକ୍ଷର *)), ଅଚଳ ଅକ୍ଷର *desc,
                          ଗଣନା AVOptionType type)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fmt, min, max;

    ଯଦି (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ଅନ୍ୟଥା {
        fmt = get_fmt(val);
        ଯଦି (fmt == -1) {
            ଅକ୍ଷର *tail;
            fmt = strtol(val, &tail, 0);
            ଯଦି (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ଯଦି(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ଯଦି (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ଫେରନ୍ତୁ AVERROR(ERANGE);
    }

    ଯଦି (dst)
    ବାଛ (type) {
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:  *(ଗଣନା AVPixelFormat *)dst = fmt; ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT: *(ଗଣନା AVSampleFormat*)dst = fmt; ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_pix_fmt(ଅଚଳ ଅକ୍ଷର *name)
{
    ଫେରନ୍ତୁ av_get_pix_fmt(name);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_pixel_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t *dst)
{
    ଫେରନ୍ତୁ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_sample_fmt(ଅଚଳ ଅକ୍ଷର *name)
{
    ଫେରନ୍ତୁ av_get_sample_fmt(name);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_sample_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t *dst)
{
    ଫେରନ୍ତୁ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_dict(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o, ଅଚଳ ଅକ୍ଷର *val, uint8_t **dst)
{
    AVDictionary *options = ଖାଲି;

    ଯଦି (val) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ଯଦି (ret < 0) {
            av_dict_free(&options);
            ଫେରନ୍ତୁ ret;
        }
    }

    ଯଦି (!dst) {
        av_dict_free(&options);
        ଫେରନ୍ତୁ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_string_channel_layout(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o,
                                     ଅଚଳ ଅକ୍ଷର *val, ଶୂନ୍ୟ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ଯଦି (dst)
    av_channel_layout_uninit(channel_layout);
    ଅନ୍ୟଥା
        channel_layout = &tmp;
    ଯଦି (!val)
        ଫେରନ୍ତୁ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ଯଦି (!dst)
        av_channel_layout_uninit(channel_layout);
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_set_elem(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *target_obj, ଅଚଳ AVOption *o,
                        ଅଚଳ ଅକ୍ଷର *val, ଶୂନ୍ୟ *dst)
{
    ଶୂନ୍ୟ *logctx = dst ? obj : ଖାଲି;
    ଅଚଳ ଗଣନା AVOptionType type = TYPE_BASE(o->type);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ବାଛ (type) {
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
        ଫେରନ୍ତୁ set_string_bool(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_STRING:
        ଫେରନ୍ତୁ set_string(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_ଦ୍ୱିମିକ:
        ଫେରନ୍ତୁ set_string_ଦ୍ୱିମିକ(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
    ସ୍ଥିତି AV_OPT_TYPE_INT64:
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
        ଫେରନ୍ତୁ set_string_ସଂଖ୍ୟା(obj, target_obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
        ଫେରନ୍ତୁ set_string_image_size(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
        ଫେରନ୍ତୁ write_ସଂଖ୍ୟା(obj, o, dst, 1, tmp.den, tmp.ଅଙ୍କ, 0);
    }
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
        ଫେରନ୍ତୁ set_string_pixel_fmt(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
        ଫେରନ୍ତୁ set_string_sample_fmt(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ଯଦି (val) {
                ଯଦି ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ଫେରନ୍ତୁ ret;
                }
            }
            ଯଦି (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ଫେରନ୍ତୁ AVERROR(ERANGE);
            }
            ଯଦି (dst)
            *(int64_t *)dst = usecs;
            ଫେରନ୍ତୁ 0;
        }
    ସ୍ଥିତି AV_OPT_TYPE_COLOR:
        ଫେରନ୍ତୁ set_string_color(obj, o, val, dst);
    ସ୍ଥିତି AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        ଯଦି (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ଫେରନ୍ତୁ ret;
    ସ୍ଥିତି AV_OPT_TYPE_DICT:
        ଫେରନ୍ତୁ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_set_array(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *target_obj, ଅଚଳ AVOption *o,
                         ଅଚଳ ଅକ୍ଷର *val, ଶୂନ୍ୟ *dst)
{
    ଅଚଳ AVOptionArrayDef *arr = o->default_val.arr;
    ଅଚଳ size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ଅଚଳ uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ଖାଲି;

    ଶୂନ୍ୟ      *logctx = dst ? obj : ଖାଲି;
    ଶୂନ୍ୟ       *elems = ଖାଲି;
    unsigned nb_elems = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (val && *val) {
        str = av_malloc(strlen(val) + 1);
        ଯଦି (!str)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ଯେତେବେଳେ (val && *val) {
        uint8_t *p = str;
        ଶୂନ୍ୟ *tmp;

        ଯଦି (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            ଯାଅ fail;
        }

        ପାଇଁ (; *val; val++, p++) {
            ଯଦି (*val == '\\' && val[1])
                val++;
            ଅନ୍ୟଥା ଯଦି (*val == sep) {
                val++;
                ଭାଙ୍ଗ;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        ଯଦି (!tmp) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        ଯଦି (ret < 0)
            ଯାଅ fail;
        nb_elems++;
    }
    av_freep(&str);

    ଯଦି (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ଯଦି (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        ଯାଅ fail;
    }

    ଯଦି (dst) {
    *((ଶୂନ୍ୟ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ଅନ୍ୟଥା
        opt_free_array(o, &elems, &nb_elems);

    ଫେରନ୍ତୁ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଶୂନ୍ୟ *dst, *target_obj;
    ଅଚଳ AVOption *o;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, 0, &target_obj, &o, &dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଫେରନ୍ତୁ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_ସଂଖ୍ୟା(name, opttype, vartype)                         \
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_eval_ ## name(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o,                  \
                         ଅଚଳ ଅକ୍ଷର *val, vartype *name ## _out)        \
{                                                                       \
    ଯଦି (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ଫେରନ୍ତୁ AVERROR(EINVAL);                                         \
    ଫେରନ୍ତୁ set_string_ସଂଖ୍ୟା(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_ସଂଖ୍ୟା(flags,  AV_OPT_TYPE_FLAGS,    ପୂର୍ଣ୍ଣସଂଖ୍ୟା)
OPT_EVAL_ସଂଖ୍ୟା(ପୂର୍ଣ୍ଣସଂଖ୍ୟା,    AV_OPT_TYPE_INT,      ପୂର୍ଣ୍ଣସଂଖ୍ୟା)
OPT_EVAL_ସଂଖ୍ୟା(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_ସଂଖ୍ୟା(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_ସଂଖ୍ୟା(ଦଶମିକ,  AV_OPT_TYPE_FLOAT,    ଦଶମିକ)
OPT_EVAL_ସଂଖ୍ୟା(ଦ୍ୱିଗୁଣ, AV_OPT_TYPE_DOUBLE,   ଦ୍ୱିଗୁଣ)
OPT_EVAL_ସଂଖ୍ୟା(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_ସଂଖ୍ୟା(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଦ୍ୱିଗୁଣ ଅଙ୍କ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା den, int64_t intnum,
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା require_type)
{
    ଶୂନ୍ୟ *dst;
    ଅଚଳ AVOption *o;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, require_type, ଖାଲି, &o, &dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ଯଦି (dst)
        ret = write_ସଂଖ୍ୟା(obj, o, dst, ଅଙ୍କ, den, intnum, 0);

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_int(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, int64_t val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ set_ସଂଖ୍ୟା(obj, name, 1, 1, val, ସନ୍ଧାନ_flags, 0);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_double(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଦ୍ୱିଗୁଣ val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ set_ସଂଖ୍ୟା(obj, name, val, 1, 1, ସନ୍ଧାନ_flags, 0);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_q(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, AVRational val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ set_ସଂଖ୍ୟା(obj, name, val.ଅଙ୍କ, val.den, 1, ସନ୍ଧାନ_flags, 0);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_bin(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ uint8_t *val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *lendst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, AV_OPT_TYPE_ଦ୍ୱିମିକ,
                       ଖାଲି, ଖାଲି, (ଶୂନ୍ୟ**)&dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (dst) {
    ptr = len ? av_malloc(len) : ଖାଲି;
    ଯଦି (len && !ptr)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    lendst = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ଯଦି (len)
        memcpy(ptr, val, len);
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_image_size(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଅଚଳ AVOption *o;
    ଶୂନ୍ୟ *logctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       ଖାଲି, &o, (ଶୂନ୍ୟ**)&dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    logctx = dst ? obj : ଖାଲି;

    ଯଦି (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_video_rate(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, AVRational val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ set_ସଂଖ୍ୟା(obj, name, val.ଅଙ୍କ, val.den, 1, ସନ୍ଧାନ_flags, AV_OPT_TYPE_VIDEO_RATE);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା set_format(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags,
                      ଗଣନା AVOptionType type, ଅଚଳ ଅକ୍ଷର *desc, ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_fmts)
{
    ଅଚଳ AVOption *o;
    ଶୂନ୍ୟ *logctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା min, max, ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, type, ଖାଲି, &o, (ଶୂନ୍ୟ**)&dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    logctx = dst ? obj : ଖାଲି;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ଯଦି (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ଫେରନ୍ତୁ AVERROR(ERANGE);
    }
    ଯଦି (dst)
    *dst = fmt;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_pixel_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଗଣନା AVPixelFormat fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ set_format(obj, name, fmt, ସନ୍ଧାନ_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_sample_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଗଣନା AVSampleFormat fmt, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ set_format(obj, name, fmt, ସନ୍ଧାନ_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_dict_val(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ AVDictionary *val,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    AVDictionary **dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, AV_OPT_TYPE_DICT, ଖାଲି, ଖାଲି,
                       (ଶୂନ୍ୟ**)&dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_chlayout(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name,
                        ଅଚଳ AVChannelLayout *channel_layout,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    AVChannelLayout *dst;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, AV_OPT_TYPE_CHLAYOUT, ଖାଲି, ଖାଲି,
                       (ଶୂନ୍ୟ**)&dst);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ଶୂନ୍ୟ format_duration(ଅକ୍ଷର *buf, size_t size, int64_t d)
{
    ଅକ୍ଷର *e;

    av_assert0(size >= 25);
    ଯଦି (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    ଯଦି (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    ଅନ୍ୟଥା ଯଦି (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    ଅନ୍ୟଥା ଯଦି (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((d / 60000000) % 60),
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((d / 1000000) % 60),
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(d % 1000000));
    ଅନ୍ୟଥା ଯଦି (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(d / 60000000),
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((d / 1000000) % 60),
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(d % 1000000));
    ଅନ୍ୟଥା
        snprintf(buf, size, "%d.%06d",
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(d / 1000000),
                 (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(d % 1000000));
    e = buf + strlen(buf);
    ଯେତେବେଳେ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ଯଦି (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_get_elem(ଅଚଳ AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ଅଚଳ ଶୂନ୍ୟ *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ବାଛ (TYPE_BASE(o->type)) {
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst));
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(ଦଶମିକ *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(ଦ୍ୱିଗୁଣ *)dst);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->ଅଙ୍କ, ((AVRational *)dst)->den);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_STRING:
        ଯଦି (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ଅନ୍ୟଥା ଯଦି (ସନ୍ଧାନ_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ଖାଲି;
            ଫେରନ୍ତୁ 0;
        } ଅନ୍ୟଥା {
            *pbuf = av_strdup("");
        }
        ଫେରନ୍ତୁ *pbuf ? 0 : AVERROR(ENOMEM);
    ସ୍ଥିତି AV_OPT_TYPE_ଦ୍ୱିମିକ: {
        ଅଚଳ uint8_t *bin;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା len;

        ଯଦି (!*(uint8_t **)dst && (ସନ୍ଧାନ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ଖାଲି;
            ଫେରନ୍ତୁ 0;
        }
        len = *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)(((uint8_t *)dst) + ଆକାର(uint8_t *));
        ଯଦି ((uint64_t)len * 2 + 1 > INT_MAX)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        ଯଦି (!(*pbuf = av_malloc(len * 2 + 1)))
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        ଯଦି (!len) {
            *pbuf[0] = '\0';
            ଫେରନ୍ତୁ 0;
        }
        bin = *(uint8_t **)dst;
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ଫେରନ୍ତୁ 0;
    }
    ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst)[0], ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst)[1]);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ଅକ୍ଷର *)av_x_if_null(av_get_pix_fmt_name(*(ଗଣନା AVPixelFormat *)dst), "none"));
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (ଅକ୍ଷର *)av_x_if_null(av_get_sample_fmt_name(*(ଗଣନା AVSampleFormat *)dst), "none"));
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        ଭାଙ୍ଗ;
    }
    ସ୍ଥିତି AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((uint8_t *)dst)[0], (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((uint8_t *)dst)[1],
                       (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((uint8_t *)dst)[2], (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)((uint8_t *)dst)[3]);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_DICT:
        ଯଦି (!*(AVDictionary **)dst && (ସନ୍ଧାନ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ଖାଲି;
            ଫେରନ୍ତୁ 0;
        }
        ଫେରନ୍ତୁ av_dict_get_string(*(AVDictionary **)dst, (ଅକ୍ଷର **)pbuf, '=', ':');
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_get_array(ଅଚଳ AVOption *o, ଶୂନ୍ୟ *dst, uint8_t **out_val)
{
    ଅଚଳ unsigned ଗଣନା_2 = *opt_array_pcount(dst);
    ଅଚଳ uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ଖାଲି;
    size_t   str_len = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    *out_val = ଖାଲି;

    ପାଇଁ (unsigned i = 0; i < ଗଣନା_2; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, ଆକାର(buf),
                           opt_array_pelem(o, *(ଶୂନ୍ୟ **)dst, i), 0);
        ଯଦି (ret < 0)
            ଯାଅ fail;

        out_len = strlen(out);
        ଯଦି (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            ଯାଅ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        ଯଦି (ret < 0)
            ଯାଅ fail;

        // add separator if needed
        ଯଦି (i)
            str[str_len++] = sep;

        // escape the element
        ପାଇଁ (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            ଯଦି (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ଯଦି (out != buf)
            av_freep(&out);
        ଯଦି (ret < 0) {
            av_freep(&str);
            ଫେରନ୍ତୁ ret;
        }
    }

    *out_val = str;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, uint8_t **out_val)
{
    ଶୂନ୍ୟ *dst, *target_obj;
    ଅଚଳ AVOption *o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    uint8_t *out, buf[128];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;

    ଯଦି (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    ଯଦି (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
        ଯଦି (!*out_val && !(ସନ୍ଧାନ_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            ଯଦି (!*out_val)
               ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        ଫେରନ୍ତୁ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, ଆକାର(buf), dst, ସନ୍ଧାନ_flags);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ଯଦି (out != buf) {
        *out_val = out;
        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (ret >= ଆକାର(buf))
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ଫେରନ୍ତୁ *out_val ? 0 : AVERROR(ENOMEM);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_ସଂଖ୍ୟା(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଦ୍ୱିଗୁଣ *ଅଙ୍କ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *den, int64_t *intnum,
                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଶୂନ୍ୟ *dst, *target_obj;
    ଅଚଳ AVOption *o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ଫେରନ୍ତୁ read_ସଂଖ୍ୟା(o, dst, ଅଙ୍କ, den, intnum);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_int(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    ଦ୍ୱିଗୁଣ ଅଙ୍କ = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, den = 1;

    ଯଦି ((ret = get_ସଂଖ୍ୟା(obj, name, &ଅଙ୍କ, &den, &intnum, ସନ୍ଧାନ_flags)) < 0)
        ଫେରନ୍ତୁ ret;
    ଯଦି (ଅଙ୍କ == den)
        *out_val = intnum;
    ଅନ୍ୟଥା
        *out_val = ଅଙ୍କ * intnum / den;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_double(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ଦ୍ୱିଗୁଣ *out_val)
{
    int64_t intnum = 1;
    ଦ୍ୱିଗୁଣ ଅଙ୍କ = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, den = 1;

    ଯଦି ((ret = get_ସଂଖ୍ୟା(obj, name, &ଅଙ୍କ, &den, &intnum, ସନ୍ଧାନ_flags)) < 0)
        ଫେରନ୍ତୁ ret;
    *out_val = ଅଙ୍କ * intnum / den;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_q(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    ଦ୍ୱିଗୁଣ ଅଙ୍କ = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, den = 1;

    ଯଦି ((ret = get_ସଂଖ୍ୟା(obj, name, &ଅଙ୍କ, &den, &intnum, ସନ୍ଧାନ_flags)) < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (ଅଙ୍କ == 1.0 && (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    ଅନ୍ୟଥା
        *out_val = double_to_rational(ଅଙ୍କ*intnum/den);
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_image_size(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *w_out, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *h_out)
{
    ଶୂନ୍ୟ *dst, *target_obj;
    ଅଚଳ AVOption *o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ଯଦି (w_out) *w_out = *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst;
    ଯଦି (h_out) *h_out = *((ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst+1);
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_video_rate(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, AVRational *out_val)
{
    ଫେରନ୍ତୁ av_opt_get_q(obj, name, ସନ୍ଧାନ_flags, out_val);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_format(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ଶୂନ୍ୟ *out_fmt,
                      ଗଣନା AVOptionType type, ଅଚଳ ଅକ୍ଷର *desc)
{
    ଶୂନ୍ୟ *dst, *target_obj;
    ଅଚଳ AVOption *o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ଯଦି (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ଗଣନା AVPixelFormat *)out_fmt = *(ଗଣନା AVPixelFormat *)dst;
    ଅନ୍ୟଥା
        *(ଗଣନା AVSampleFormat*)out_fmt = *(ଗଣନା AVSampleFormat*)dst;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_pixel_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ଗଣନା AVPixelFormat *out_fmt)
{
    ଫେରନ୍ତୁ get_format(obj, name, ସନ୍ଧାନ_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_sample_fmt(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ଗଣନା AVSampleFormat *out_fmt)
{
    ଫେରନ୍ତୁ get_format(obj, name, ସନ୍ଧାନ_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_chlayout(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, AVChannelLayout *cl)
{
    ଶୂନ୍ୟ *dst, *target_obj;
    ଅଚଳ AVOption *o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ଫେରନ୍ତୁ av_channel_layout_copy(cl, dst);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_dict_val(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, AVDictionary **out_val)
{
    ଶୂନ୍ୟ *target_obj;
    AVDictionary *src;
    ଅଚଳ AVOption *o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);

    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (o->type != AV_OPT_TYPE_DICT)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ଫେରନ୍ତୁ av_dict_copy(out_val, src, 0);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_flag_is_set(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *field_name, ଅଚଳ ଅକ୍ଷର *flag_name)
{
    ଅଚଳ AVOption *field = av_opt_find(obj, field_name, ଖାଲି, 0, 0);
    ଅଚଳ AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : ଖାଲି, 0, 0);
    int64_t res;

    ଯଦି (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ଫେରନ୍ତୁ 0;
    ଫେରନ୍ତୁ res & flag->default_val.i64;
}

ସ୍ଥିର ଶୂନ୍ୟ log_int_ମୂଲ୍ୟ(ଶୂନ୍ୟ *av_log_obj, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, int64_t i)
{
    ଯଦି (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ଅନ୍ୟଥା ଯଦି (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ଅନ୍ୟଥା ଯଦି (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ଅନ୍ୟଥା ଯଦି (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ଅନ୍ୟଥା ଯଦି (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ଅନ୍ୟଥା {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ log_ମୂଲ୍ୟ(ଶୂନ୍ୟ *av_log_obj, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଦ୍ୱିଗୁଣ d)
{
    ଯଦି      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ଅନ୍ୟଥା ଯଦି (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == (ଦ୍ୱିଗୁଣ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ଅନ୍ୟଥା ଯଦି (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ଅନ୍ୟଥା ଯଦି (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ଅନ୍ୟଥା ଯଦି (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ଅନ୍ୟଥା ଯଦି (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ଅନ୍ୟଥା ଯଦି (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ଅନ୍ୟଥା {
        av_log(av_log_obj, level, "%g", d);
    }
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *get_opt_const_name(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *unit, int64_t ମୂଲ୍ୟ)
{
    ଅଚଳ AVOption *opt = ଖାଲି;

    ଯଦି (!unit)
        ଫେରନ୍ତୁ ଖାଲି;
    ଯେତେବେଳେ ((opt = av_opt_next(obj, opt)))
        ଯଦି (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == ମୂଲ୍ୟ)
            ଫେରନ୍ତୁ opt->name;
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଅକ୍ଷର *get_opt_flags_string(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *unit, int64_t ମୂଲ୍ୟ)
{
    ଅଚଳ AVOption *opt = ଖାଲି;
    ଅକ୍ଷର flags[512];

    flags[0] = 0;
    ଯଦି (!unit)
        ଫେରନ୍ତୁ ଖାଲି;
    ଯେତେବେଳେ ((opt = av_opt_next(obj, opt))) {
        ଯଦି (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & ମୂଲ୍ୟ) {
            ଯଦି (flags[0])
                av_strlcatf(flags, ଆକାର(flags), "+");
            av_strlcatf(flags, ଆକାର(flags), "%s", opt->name);
        }
    }
    ଯଦି (flags[0])
        ଫେରନ୍ତୁ av_strdup(flags);
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ log_type(ଶୂନ୍ୟ *av_log_obj, ଅଚଳ AVOption *o,
                     ଗଣନା AVOptionType parent_type)
{
    ଅଚଳ ଗଣନା AVOptionType type = TYPE_BASE(o->type);

    ଯଦି (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ଅନ୍ୟଥା ଯଦି (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ଯଦି (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ଅନ୍ୟଥା
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ଅନ୍ୟଥା
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ସ୍ଥିର ଶୂନ୍ୟ log_default(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *av_log_obj, ଅଚଳ AVOption *opt)
{
    ଯଦି (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ଦ୍ୱିମିକ)
        ଫେରନ୍ତୁ;
    ଯଦି ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ଫେରନ୍ତୁ;

    ଯଦି (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ଅଚଳ AVOptionArrayDef *arr = opt->default_val.arr;
        ଯଦି (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ଫେରନ୍ତୁ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    ବାଛ (opt->type) {
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS: {
        ଅକ୍ଷର *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ଯଦି (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ଅନ୍ୟଥା {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        ଭାଙ୍ଗ;
    }
    ସ୍ଥିତି AV_OPT_TYPE_DURATION: {
        ଅକ୍ଷର buf[25];
        format_duration(buf, ଆକାର(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        ଭାଙ୍ଗ;
    }
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
    ସ୍ଥିତି AV_OPT_TYPE_INT64: {
        ଅଚଳ ଅକ୍ଷର *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        ଯଦି (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ଅନ୍ୟଥା
            log_int_ମୂଲ୍ୟ(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        ଭାଙ୍ଗ;
    }
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
        log_ମୂଲ୍ୟ(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.ଅଙ୍କ, q.den); }
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ଅକ୍ଷର *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (ଅକ୍ଷର *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_COLOR:
    ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
    ସ୍ଥିତି AV_OPT_TYPE_STRING:
    ସ୍ଥିତି AV_OPT_TYPE_DICT:
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
    ସ୍ଥିତି AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        ଭାଙ୍ଗ;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ସ୍ଥିର ଶୂନ୍ୟ opt_list(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *av_log_obj, ଅଚଳ ଅକ୍ଷର *unit,
                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା req_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rej_flags, ଗଣନା AVOptionType parent_type)
{
    ଅଚଳ AVOption *opt = ଖାଲି;
    AVOptionRanges *r;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯେତେବେଳେ ((opt = av_opt_next(obj, opt))) {
        ଯଦି (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            ଜାରି;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ଯଦି (!unit && opt->type == AV_OPT_TYPE_CONST)
            ଜାରି;
        ଅନ୍ୟଥା ଯଦି (unit && opt->type != AV_OPT_TYPE_CONST)
            ଜାରି;
        ଅନ୍ୟଥା ଯଦି (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            ଜାରି;
        ଅନ୍ୟଥା ଯଦି (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ଅନ୍ୟଥା
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

        ଯଦି (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ଯଦି (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_ସନ୍ଧାନ_FAKE_OBJ) >= 0) {
            ବାଛ (opt->type) {
            ସ୍ଥିତି AV_OPT_TYPE_INT:
            ସ୍ଥିତି AV_OPT_TYPE_UINT:
            ସ୍ଥିତି AV_OPT_TYPE_INT64:
            ସ୍ଥିତି AV_OPT_TYPE_UINT64:
            ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
            ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
            ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
                ପାଇଁ (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_ମୂଲ୍ୟ(av_log_obj, AV_LOG_INFO, r->range[i]->ମୂଲ୍ୟ_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_ମୂଲ୍ୟ(av_log_obj, AV_LOG_INFO, r->range[i]->ମୂଲ୍ୟ_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                ଭାଙ୍ଗ;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        ଯଦି (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_show2(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *av_log_obj, ପୂର୍ଣ୍ଣସଂଖ୍ୟା req_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rej_flags)
{
    ଯଦି (!obj)
        ଫେରନ୍ତୁ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ଖାଲି, req_flags, rej_flags, -1);

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_opt_set_defaults(ଶୂନ୍ୟ *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

ଶୂନ୍ୟ av_opt_set_defaults2(ଶୂନ୍ୟ *s, ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଅଚଳ AVOption *opt = ଖାଲି;
    ଯେତେବେଳେ ((opt = av_opt_next(s, opt))) {
        ଶୂନ୍ୟ *dst = ((uint8_t*)s) + opt->offset;

        ଯଦି ((opt->flags & mask) != flags)
            ଜାରି;

        ଯଦି (opt->flags & AV_OPT_FLAG_READONLY)
            ଜାରି;

        ଯଦି (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ଅଚଳ AVOptionArrayDef *arr = opt->default_val.arr;
            ଅଚଳ ଅକ୍ଷର              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ଯଦି (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            ଜାରି;
        }

        ବାଛ (opt->type) {
            ସ୍ଥିତି AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_BOOL:
            ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
            ସ୍ଥିତି AV_OPT_TYPE_INT:
            ସ୍ଥିତି AV_OPT_TYPE_UINT:
            ସ୍ଥିତି AV_OPT_TYPE_INT64:
            ସ୍ଥିତି AV_OPT_TYPE_UINT64:
            ସ୍ଥିତି AV_OPT_TYPE_DURATION:
            ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
            ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
                write_ସଂଖ୍ୟା(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
            ସ୍ଥିତି AV_OPT_TYPE_FLOAT: {
                ଦ୍ୱିଗୁଣ val;
                val = opt->default_val.dbl;
                write_ସଂଖ୍ୟା(s, opt, dst, val, 1, 1, 1);
            }
            ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_ସଂଖ୍ୟା(s, opt, dst, 1, val.den, val.ଅଙ୍କ, 1);
            }
            ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_ଦ୍ୱିମିକ:
                set_string_ଦ୍ୱିମିକ(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
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
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_ଚାବି_ମୂଲ୍ୟ_pair(ଶୂନ୍ୟ *ctx, ଅଚଳ ଅକ୍ଷର **buf,
                                ଅଚଳ ଅକ୍ଷର *ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର *pairs_sep)
{
    ଅକ୍ଷର *ଚାବି = av_get_token(buf, ଚାବି_val_sep);
    ଅକ୍ଷର *val;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!ଚାବି)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯଦି (*ଚାବି && strspn(*buf, ଚାବି_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        ଯଦି (!val) {
            av_freep(&ଚାବି);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
    } ଅନ୍ୟଥା {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", ଚାବି);
        av_free(ଚାବି);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", ଚାବି, val);

    ret = av_opt_set(ctx, ଚାବି, val, AV_OPT_ସନ୍ଧାନ_CHILDREN);
    ଯଦି (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", ଚାବି);

    av_free(ଚାବି);
    av_free(val);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_set_options_string(ଶୂନ୍ୟ *ctx, ଅଚଳ ଅକ୍ଷର *opts,
                          ଅଚଳ ଅକ୍ଷର *ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର *pairs_sep)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, ଗଣନା_2 = 0;

    ଯଦି (!opts)
        ଫେରନ୍ତୁ 0;

    ଯେତେବେଳେ (*opts) {
        ଯଦି ((ret = parse_ଚାବି_ମୂଲ୍ୟ_pair(ctx, &opts, ଚାବି_val_sep, pairs_sep)) < 0)
            ଫେରନ୍ତୁ ret;
        ଗଣନା_2++;

        ଯଦି (*opts)
            opts++;
    }

    ଫେରନ୍ତୁ ଗଣନା_2;
}

#define WHITESPACES " \n\t\r"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_ଚାବି_char(ଅକ୍ଷର c)
{
    ଫେରନ୍ତୁ (unsigned)((c | 32) - 'a') < 26 ||
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
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_ଚାବି(ଅଚଳ ଅକ୍ଷର **ropts, ଅଚଳ ଅକ୍ଷର *delim, ଅକ୍ଷର **rkey)
{
    ଅଚଳ ଅକ୍ଷର *opts = *ropts;
    ଅଚଳ ଅକ୍ଷର *ଚାବି_start, *ଚାବି_end;

    ଚାବି_start = opts += strspn(opts, WHITESPACES);
    ଯେତେବେଳେ (is_ଚାବି_char(*opts))
        opts++;
    ଚାବି_end = opts;
    opts += strspn(opts, WHITESPACES);
    ଯଦି (!*opts || !strchr(delim, *opts))
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    opts++;
    ଯଦି (!(*rkey = av_malloc(ଚାବି_end - ଚାବି_start + 1)))
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    memcpy(*rkey, ଚାବି_start, ଚାବି_end - ଚାବି_start);
    (*rkey)[ଚାବି_end - ଚାବି_start] = 0;
    *ropts = opts;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_ଚାବି_ମୂଲ୍ୟ(ଅଚଳ ଅକ୍ଷର **ropts,
                         ଅଚଳ ଅକ୍ଷର *ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର *pairs_sep,
                         unsigned flags,
                         ଅକ୍ଷର **rkey, ଅକ୍ଷର **rval)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ଅକ୍ଷର *ଚାବି = ଖାଲି, *val;
    ଅଚଳ ଅକ୍ଷର *opts = *ropts;

    ଯଦି ((ret = get_ଚାବି(&opts, ଚାବି_val_sep, &ଚାବି)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_ଚାବି))
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଯଦି (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(ଚାବି);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = ଚାବି;
    *rval  = val;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_from_string(ଶୂନ୍ୟ *ctx, ଅଚଳ ଅକ୍ଷର *opts,
                           ଅଚଳ ଅକ୍ଷର *ଅଚଳ *shorthand,
                           ଅଚଳ ଅକ୍ଷର *ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର *pairs_sep)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, ଗଣନା_2 = 0;
    ଅଚଳ ଅକ୍ଷର *dummy_shorthand = ଖାଲି;
    ଅଚଳ ଅକ୍ଷର *ଚାବି;

    ଯଦି (!opts)
        ଫେରନ୍ତୁ 0;
    ଯଦି (!shorthand)
        shorthand = &dummy_shorthand;

    ଯେତେବେଳେ (*opts) {
        ଅକ୍ଷର *parsed_ଚାବି, *ମୂଲ୍ୟ;
        ret = av_opt_get_ଚାବି_ମୂଲ୍ୟ(&opts, ଚାବି_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_ଚାବି : 0,
                                   &parsed_ଚାବି, &ମୂଲ୍ୟ);
        ଯଦି (ret < 0) {
            ଯଦି (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ଅନ୍ୟଥା
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ଫେରନ୍ତୁ ret;
        }
        ଯଦି (*opts)
            opts++;
        ଯଦି (parsed_ଚାବି) {
            ଚାବି = parsed_ଚାବି;
            ଯେତେବେଳେ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ଅନ୍ୟଥା {
            ଚାବି = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", ଚାବି, ମୂଲ୍ୟ);
        ଯଦି ((ret = av_opt_set(ctx, ଚାବି, ମୂଲ୍ୟ, 0)) < 0) {
            ଯଦି (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", ଚାବି);
            av_free(ମୂଲ୍ୟ);
            av_free(parsed_ଚାବି);
            ଫେରନ୍ତୁ ret;
        }

        av_free(ମୂଲ୍ୟ);
        av_free(parsed_ଚାବି);
        ଗଣନା_2++;
    }
    ଫେରନ୍ତୁ ଗଣନା_2;
}

ଶୂନ୍ୟ av_opt_free(ଶୂନ୍ୟ *obj)
{
    ଅଚଳ AVOption *o = ଖାଲି;
    ଯେତେବେଳେ ((o = av_opt_next(obj, o))) {
        ଶୂନ୍ୟ *pitem = (uint8_t *)obj + o->offset;

        ଯଦି (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ଅନ୍ୟଥା
            opt_free_elem(o->type, pitem);
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_dict2(ଶୂନ୍ୟ *obj, AVDictionary **options, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଅଚଳ AVDictionaryEntry *t = ଖାଲି;
    AVDictionary    *tmp = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!options)
        ଫେରନ୍ତୁ 0;

    ଯେତେବେଳେ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->ଚାବି, t->ମୂଲ୍ୟ, ସନ୍ଧାନ_flags);
        ଯଦି (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->ଚାବି, t->ମୂଲ୍ୟ, AV_DICT_MULTIKEY);
        ଯଦି (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->ଚାବି, t->ମୂଲ୍ୟ);
            av_dict_free(&tmp);
            ଫେରନ୍ତୁ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_dict(ଶୂନ୍ୟ *obj, AVDictionary **options)
{
    ଫେରନ୍ତୁ av_opt_set_dict2(obj, options, 0);
}

ଅଚଳ AVOption *av_opt_find(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *unit,
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଫେରନ୍ତୁ av_opt_find2(obj, name, unit, opt_flags, ସନ୍ଧାନ_flags, ଖାଲି);
}

ଅଚଳ AVOption *av_opt_find2(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ଅଚଳ ଅକ୍ଷର *unit,
                             ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags, ଶୂନ୍ୟ **target_obj)
{
    ଅଚଳ AVClass  *c;
    ଅଚଳ AVOption *o = ଖାଲି;

    ଯଦି(!obj)
        ଫେରନ୍ତୁ ଖାଲି;

    c= *(AVClass**)obj;

    ଯଦି (!c)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (ସନ୍ଧାନ_flags & AV_OPT_ସନ୍ଧାନ_CHILDREN) {
        ଯଦି (ସନ୍ଧାନ_flags & AV_OPT_ସନ୍ଧାନ_FAKE_OBJ) {
            ଶୂନ୍ୟ *iter = ଖାଲି;
            ଅଚଳ AVClass *child;
            ଯେତେବେଳେ (child = av_opt_child_class_iterate(c, &iter))
                ଯଦି (o = av_opt_find2(&child, name, unit, opt_flags, ସନ୍ଧାନ_flags, ଖାଲି))
                    ଫେରନ୍ତୁ o;
        } ଅନ୍ୟଥା {
            ଶୂନ୍ୟ *child = ଖାଲି;
            ଯେତେବେଳେ (child = av_opt_child_next(obj, child))
                ଯଦି (o = av_opt_find2(child, name, unit, opt_flags, ସନ୍ଧାନ_flags, target_obj))
                    ଫେରନ୍ତୁ o;
        }
    }

    ଯେତେବେଳେ (o = av_opt_next(obj, o)) {
        ଯଦି (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ଯଦି (target_obj) {
                ଯଦି (!(ସନ୍ଧାନ_flags & AV_OPT_ସନ୍ଧାନ_FAKE_OBJ))
                    *target_obj = obj;
                ଅନ୍ୟଥା
                    *target_obj = ଖାଲି;
            }
            ଫେରନ୍ତୁ o;
        }
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ *av_opt_child_next(ଶୂନ୍ୟ *obj, ଶୂନ୍ୟ *prev)
{
    ଅଚଳ AVClass *c = *(AVClass **)obj;
    ଯଦି (c->child_next)
        ଫେରନ୍ତୁ c->child_next(obj, prev);
    ଫେରନ୍ତୁ ଖାଲି;
}

ଅଚଳ AVClass *av_opt_child_class_iterate(ଅଚଳ AVClass *parent, ଶୂନ୍ୟ **iter)
{
    ଯଦି (parent->child_class_iterate)
        ଫେରନ୍ତୁ parent->child_class_iterate(iter);
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_copy_elem(ଶୂନ୍ୟ *logctx, ଗଣନା AVOptionType type,
                         ଶୂନ୍ୟ *dst, ଅଚଳ ଶୂନ୍ୟ *src)
{
    ଯଦି (type == AV_OPT_TYPE_STRING) {
        ଅଚଳ ଅକ୍ଷର *src_str = *(ଅଚଳ ଅକ୍ଷର *ଅଚଳ *)src;
        ଅକ୍ଷର         **dstp =  (ଅକ୍ଷର **)dst;
        ଯଦି (*dstp != src_str)
            av_freep(dstp);
        ଯଦି (src_str) {
            *dstp = av_strdup(src_str);
            ଯଦି (!*dstp)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
    } ଅନ୍ୟଥା ଯଦି (type == AV_OPT_TYPE_ଦ୍ୱିମିକ) {
        ଅଚଳ uint8_t *ଅଚଳ *src8 = (ଅଚଳ uint8_t *ଅଚଳ *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = *(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)(src8 + 1);
        ଯଦି (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ଯଦି (len && !*dst8) {
            *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)(dst8 + 1) = 0;
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)(dst8 + 1) = len;
    } ଅନ୍ୟଥା ଯଦି (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ଅନ୍ୟଥା ଯଦି (type == AV_OPT_TYPE_DICT) {
        ଅଚଳ AVDictionary *sdict = *(ଅଚଳ AVDictionary * ଅଚଳ *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ଯଦି (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ଖାଲି;
        ଫେରନ୍ତୁ av_dict_copy(ddictp, sdict, 0);
    } ଅନ୍ୟଥା ଯଦି (type == AV_OPT_TYPE_CHLAYOUT) {
        ଅଚଳ AVChannelLayout *slayout = (ଅଚଳ AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ଯଦି (dlayout != slayout) {
            ଯଦି (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ଖାଲି;
            ଫେରନ୍ତୁ av_channel_layout_copy(dst, src);
        }
    } ଅନ୍ୟଥା ଯଦି (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } ଅନ୍ୟଥା {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_copy_array(ଶୂନ୍ୟ *logctx, ଅଚଳ AVOption *o,
                          ଶୂନ୍ୟ **pdst, ଅଚଳ ଶୂନ୍ୟ * ଅଚଳ *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    ଶୂନ୍ୟ         *dst = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (*pdst == *psrc) {
        *pdst                   = ଖାଲି;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    ଯଦି (!dst)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(ଶୂନ୍ୟ**)psrc, i));
        ଯଦି (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ଫେରନ୍ତୁ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_copy(ଶୂନ୍ୟ *dst, ଅଚଳ ଶୂନ୍ୟ *src)
{
    ଅଚଳ AVOption *o = ଖାଲି;
    ଅଚଳ AVClass *c;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (!src)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ଯଦି (!c || c != *(AVClass **)dst)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯେତେବେଳେ ((o = av_opt_next(src, o))) {
        ଶୂନ୍ୟ *field_dst = (uint8_t *)dst + o->offset;
        ଶୂନ୍ୟ *field_src = (uint8_t *)src + o->offset;

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        ଯଦି (err < 0)
            ret = err;
    }
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_array_size(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags,
                          unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *out_val)
{
    ଶୂନ୍ୟ *target_obj, *parray;
    ଅଚଳ AVOption *o;

    o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_get_array(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags,
                     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା start_elem, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_elems,
                     ଗଣନା AVOptionType out_type, ଶୂନ୍ୟ *out_val)
{
    ଅଚଳ size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ଅଚଳ AVOption *o;
    ଶୂନ୍ୟ *target_obj;

    ଅଚଳ ଶୂନ୍ୟ *parray;
    unsigned array_size;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target_obj);
    ଯଦି (!o || !target_obj)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଯଦି (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    ଯଦି (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (unsigned i = 0; i < nb_elems; i++) {
        ଅଚଳ ଶୂନ୍ୟ *src = opt_array_pelem(o, *(ଶୂନ୍ୟ**)parray, start_elem + i);
        ଶୂନ୍ୟ       *dst = (uint8_t*)out_val + i * elem_size_out;

        ଯଦି (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            ଯଦି (ret < 0)
                ଯାଅ fail;
        } ଅନ୍ୟଥା ଯଦି (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, ଆକାର(buf), src, ସନ୍ଧାନ_flags);
            ଯଦି (ret < 0)
                ଯାଅ fail;

            ଯଦି (out == buf) {
                out = av_strdup(buf);
                ଯଦି (!out) {
                    ret = AVERROR(ENOMEM);
                    ଯାଅ fail;
                }
            }

            *(uint8_t**)dst = out;
        } ଅନ୍ୟଥା ଯଦି (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            ଦ୍ୱିଗୁଣ     ଅଙ୍କ = 1.0;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା        den = 1;
            int64_t intnum = 1;

            ret = read_ସଂଖ୍ୟା(o, src, &ଅଙ୍କ, &den, &intnum);
            ଯଦି (ret < 0)
                ଯାଅ fail;

            ବାଛ (out_type) {
            ସ୍ଥିତି AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (ଅଙ୍କ == den) ?  intnum : ଅଙ୍କ * intnum / den;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
                *(ଦ୍ୱିଗୁଣ*)dst = ଅଙ୍କ * intnum / den;
                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (ଅଙ୍କ == 1.0 && (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(ଅଙ୍କ * intnum / den);
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ: av_assert0(0);
            }
        } ଅନ୍ୟଥା
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ଫେରନ୍ତୁ 0;
fail:
    ପାଇଁ (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_set_array(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags,
                     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା start_elem, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_elems,
                     ଗଣନା AVOptionType val_type, ଅଚଳ ଶୂନ୍ୟ *val)
{
    ଅଚଳ size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ଅଚଳ AVOption *o;
    ଅଚଳ AVOptionArrayDef *arr;
    ଶୂନ୍ୟ *target_obj;

    ଶୂନ୍ୟ *parray;
    ଶୂନ୍ୟ *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ret = opt_set_init(obj, name, ସନ୍ଧାନ_flags, 0, &target_obj, &o, &parray);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    ଯଦି (start_elem > *array_size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    // compute new array size
    ଯଦି (!val) {
        ଯଦି (*array_size - start_elem < nb_elems)
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } ଅନ୍ୟଥା ଯଦି (ସନ୍ଧାନ_flags & AV_OPT_ARRAY_REPLACE) {
        ଯଦି (start_elem >= UINT_MAX - nb_elems)
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } ଅନ୍ୟଥା {
        ଯଦି (nb_elems >= UINT_MAX - *array_size)
            ଫେରନ୍ତୁ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    ଯଦି (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ଯଦି (!val) {
        ଶୂନ୍ୟ *array = *(ଶୂନ୍ୟ**)parray;

        ପାଇଁ (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        ଯଦି (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            ଯଦି (!array)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);

            *(ଶୂନ୍ୟ**)parray = array;
        } ଅନ୍ୟଥା
            av_freep(parray);

        *array_size = new_size;

        ଫେରନ୍ତୁ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    ଯଦି (!new_elems)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    // convert/validate each new element
    ପାଇଁ (unsigned i = 0; i < nb_elems; i++) {
        ଶୂନ୍ୟ       *dst = opt_array_pelem(o, new_elems, i);
        ଅଚଳ ଶୂନ୍ୟ *src = (uint8_t*)val + i * elem_size_val;

        ଦ୍ୱିଗୁଣ     ଅଙ୍କ = 1.0;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା        den = 1;
        int64_t intnum = 1;

        ଯଦି (val_type == TYPE_BASE(o->type)) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ଯଦି (ret < 0)
                ଯାଅ fail;

            // validate the range for numeric options
            err = read_ସଂଖ୍ୟା(o, dst, &ଅଙ୍କ, &den, &intnum);
            ଯଦି (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < ଅଙ୍କ * intnum || o->min * den > ଅଙ୍କ * intnum)) {
                ଅଙ୍କ = den ? ଅଙ୍କ * intnum / den : (ଅଙ୍କ && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, ଅଙ୍କ, o->min, o->max);
                ret = AVERROR(ERANGE);
                ଯାଅ fail;
            }
        } ଅନ୍ୟଥା ଯଦି (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ଅଚଳ ଅକ୍ଷର **)src, dst);
            ଯଦି (ret < 0)
                ଯାଅ fail;
        } ଅନ୍ୟଥା ଯଦି (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            ବାଛ (val_type) {
            ସ୍ଥିତି AV_OPT_TYPE_INT:       intnum = *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା*)src;                ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_FLOAT:     ଅଙ୍କ    = *(ଦଶମିକ*)src;              ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:    ଅଙ୍କ    = *(ଦ୍ୱିଗୁଣ*)src;             ଭାଙ୍ଗ;
            ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->ଅଙ୍କ;
                                        den    = ((AVRational*)src)->den;   ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ: av_assert0(0);
            }

            ret = write_ସଂଖ୍ୟା(obj, o, dst, ଅଙ୍କ, den, intnum, 0);
            ଯଦି (ret < 0)
                ଯାଅ fail;
        } ଅନ୍ୟଥା {
            ret = AVERROR(ENOSYS);
            ଯାଅ fail;
        }
    }

    // commit new elements to the array
    ଯଦି (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(ଶୂନ୍ୟ**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = ଖାଲି;
        nb_elems  = 0;
    } ଅନ୍ୟଥା {
        ଶୂନ୍ୟ *array = av_realloc_array(*(ଶୂନ୍ୟ**)parray, new_size, elem_size);
        ଯଦି (!array) {
            ret = AVERROR(ENOMEM);
            ଯାଅ fail;
        }

        ଯଦି (ସନ୍ଧାନ_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            ପାଇଁ (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ଅନ୍ୟଥା {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(ଶୂନ୍ୟ**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_query_ranges(AVOptionRanges **ranges_arg, ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ଅଚଳ AVClass *c = *(AVClass**)obj;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା (*callback)(AVOptionRanges **, ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags) = c->query_ranges;

    ଯଦି (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, ଚାବି, flags);
    ଯଦି (ret >= 0) {
        ଯଦି (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_query_ranges_default(AVOptionRanges **ranges_arg, ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVOptionRanges *ranges = av_mallocz(ଆକାର(*ranges));
    AVOptionRange **range_array = av_mallocz(ଆକାର(ଶୂନ୍ୟ*));
    AVOptionRange *range = av_mallocz(ଆକାର(*range));
    ଅଚଳ AVOption *field = av_opt_find(obj, ଚାବି, ଖାଲି, 0, flags);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    *ranges_arg = ଖାଲି;

    ଯଦି (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->ମୂଲ୍ୟ_min = field->min;
    range->ମୂଲ୍ୟ_max = field->max;

    ବାଛ (field->type) {
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
    ସ୍ଥିତି AV_OPT_TYPE_INT64:
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
    ସ୍ଥିତି AV_OPT_TYPE_DURATION:
    ସ୍ଥିତି AV_OPT_TYPE_COLOR:
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->ମୂଲ୍ୟ_min = -1;
        range->ମୂଲ୍ୟ_max = INT_MAX;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->ମୂଲ୍ୟ_min = 0;
        range->ମୂଲ୍ୟ_max = INT_MAX/8;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->ମୂଲ୍ୟ_min = 1;
        range->ମୂଲ୍ୟ_max = INT_MAX;
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ret = AVERROR(ENOSYS);
        ଯାଅ fail;
    }

    *ranges_arg = ranges;
    ଫେରନ୍ତୁ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    AVOptionRanges *ranges = *rangesp;

    ଯଦି (!ranges)
        ଫେରନ୍ତୁ;

    ପାଇଁ (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ଯଦି (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_is_set_to_default(ଶୂନ୍ୟ *obj, ଅଚଳ AVOption *o)
{
    int64_t i64;
    ଦ୍ୱିଗୁଣ d;
    AVRational q;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, w, h;
    ଅକ୍ଷର *str;
    ଶୂନ୍ୟ *dst;

    ଯଦି (!o || !obj)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    ଯଦି (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ଅଚଳ ଅକ୍ଷର *def = o->default_val.arr ? o->default_val.arr->def : ଖାଲି;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        ଯଦି (!!val != !!def)
            ret = 0;
        ଅନ୍ୟଥା ଯଦି (val)
            ret = !strcmp(val, def);
        ଅନ୍ୟଥା
            ret = 1;

        av_freep(&val);

        ଫେରନ୍ତୁ ret;
    }

    ବାଛ (o->type) {
    ସ୍ଥିତି AV_OPT_TYPE_CONST:
        ଫେରନ୍ତୁ 1;
    ସ୍ଥିତି AV_OPT_TYPE_BOOL:
    ସ୍ଥିତି AV_OPT_TYPE_FLAGS:
    ସ୍ଥିତି AV_OPT_TYPE_PIXEL_FMT:
    ସ୍ଥିତି AV_OPT_TYPE_SAMPLE_FMT:
    ସ୍ଥିତି AV_OPT_TYPE_INT:
    ସ୍ଥିତି AV_OPT_TYPE_UINT:
    ସ୍ଥିତି AV_OPT_TYPE_DURATION:
    ସ୍ଥିତି AV_OPT_TYPE_INT64:
    ସ୍ଥିତି AV_OPT_TYPE_UINT64:
        read_ସଂଖ୍ୟା(o, dst, ଖାଲି, ଖାଲି, &i64);
        ଫେରନ୍ତୁ o->default_val.i64 == i64;
    ସ୍ଥିତି AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ଯଦି (o->default_val.str) {
            ଯଦି ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ଫେରନ୍ତୁ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ଫେରନ୍ତୁ ret;
    }
    ସ୍ଥିତି AV_OPT_TYPE_STRING:
        str = *(ଅକ୍ଷର **)dst;
        ଯଦି (str == o->default_val.str) //2 NULLs
            ଫେରନ୍ତୁ 1;
        ଯଦି (!str || !o->default_val.str) //1 NULL
            ଫେରନ୍ତୁ 0;
        ଫେରନ୍ତୁ !strcmp(str, o->default_val.str);
    ସ୍ଥିତି AV_OPT_TYPE_DOUBLE:
        d = *(ଦ୍ୱିଗୁଣ *)dst;
        ଫେରନ୍ତୁ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ସ୍ଥିତି AV_OPT_TYPE_FLOAT:
        d = *(ଦଶମିକ *)dst;
        ଫେରନ୍ତୁ (ଦଶମିକ)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    ସ୍ଥିତି AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ଫେରନ୍ତୁ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    ସ୍ଥିତି AV_OPT_TYPE_ଦ୍ୱିମିକ: {
        ସଂରଚନା {
            uint8_t *data;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;
        } tmp = {0};
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_size = *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)((ଶୂନ୍ୟ **)dst + 1);
        ଶୂନ୍ୟ *opt_ptr = *(ଶୂନ୍ୟ **)dst;
        ଯଦି (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ଫେରନ୍ତୁ 1;
        ଯଦି (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ଫେରନ୍ତୁ 0;
        ଯଦି (opt_size != strlen(o->default_val.str) / 2)
            ଫେରନ୍ତୁ 0;
        ret = set_string_ଦ୍ୱିମିକ(ଖାଲି, ଖାଲି, o->default_val.str, &tmp.data);
        ଯଦି (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ଫେରନ୍ତୁ ret;
    }
    ସ୍ଥିତି AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ଖାଲି;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ଅଚଳ AVDictionaryEntry *en1 = ଖାଲି;
        ଅଚଳ AVDictionaryEntry *en2 = ଖାଲି;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ଯଦି (ret < 0) {
            av_dict_free(&dict1);
            ଫେରନ୍ତୁ ret;
        }
        କର {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ଯେତେବେଳେ (en1 && en2 && !strcmp(en1->ଚାବି, en2->ଚାବି) && !strcmp(en1->ମୂଲ୍ୟ, en2->ମୂଲ୍ୟ));
        av_dict_free(&dict1);
        ଫେରନ୍ତୁ (!en1 && !en2);
    }
    ସ୍ଥିତି AV_OPT_TYPE_IMAGE_SIZE:
        ଯଦି (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ଅନ୍ୟଥା ଯଦି ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ଫେରନ୍ତୁ ret;
        ଫେରନ୍ତୁ (w == *(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst) && (h == *((ପୂର୍ଣ୍ଣସଂଖ୍ୟା *)dst+1));
    ସ୍ଥିତି AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        ଯଦି (o->default_val.str) {
            ଯଦି ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ଫେରନ୍ତୁ ret;
        }
        ଫେରନ୍ତୁ !av_cmp_q(*(AVRational*)dst, q);
    ସ୍ଥିତି AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ଯଦି (o->default_val.str) {
            ଯଦି ((ret = av_parse_color(color, o->default_val.str, -1, ଖାଲି)) < 0)
                ଫେରନ୍ତୁ ret;
        }
        ଫେରନ୍ତୁ !memcmp(color, dst, ଆକାର(color));
    }
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ AVERROR_PATCHWELCOME;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_is_set_to_default_by_name(ଶୂନ୍ୟ *obj, ଅଚଳ ଅକ୍ଷର *name, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ସନ୍ଧାନ_flags)
{
    ଅଚଳ AVOption *o;
    ଶୂନ୍ୟ *target;
    ଯଦି (!obj)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ଖାଲି, 0, ସନ୍ଧାନ_flags, &target);
    ଯଦି (!o)
        ଫେରନ୍ତୁ AVERROR_OPTION_NOT_FOUND;
    ଫେରନ୍ତୁ av_opt_is_set_to_default(target, o);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_serialize(ଶୂନ୍ୟ *obj, ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *cnt,
                         AVBPrint *bprint, ଅଚଳ ଅକ୍ଷର ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର pairs_sep)
{
    ଅଚଳ AVOption *o = ଖାଲି;
    ଶୂନ୍ୟ *child = ଖାଲି;
    uint8_t *buf;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ଅଚଳ ଅକ୍ଷର special_chars[] = {pairs_sep, ଚାବି_val_sep, '\0'};

    ଯଦି (flags & AV_OPT_SERIALIZE_ସନ୍ଧାନ_CHILDREN)
        ଯେତେବେଳେ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                ଚାବି_val_sep, pairs_sep);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        }

    ଯେତେବେଳେ (o = av_opt_next(obj, o)) {
        ଯଦି (o->type == AV_OPT_TYPE_CONST)
            ଜାରି;
        ଯଦି ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ଯଦି ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ଯଦି (o->flags == opt_flags)
                    ଜାରି;
            } ଅନ୍ୟଥା ଯଦି ((o->flags & opt_flags) == opt_flags)
                ଜାରି;
        } ଅନ୍ୟଥା {
            ଯଦି ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                ଜାରି;
            ଅନ୍ୟଥା ଯଦି (((o->flags & opt_flags) != opt_flags))
                ଜାରି;
        }
        ଯଦି (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            ଜାରି;
        ଯଦି ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ଖାଲି);
            ଫେରନ୍ତୁ ret;
        }
        ଯଦି (buf) {
            ଯଦି ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &ଚାବି_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_opt_serialize(ଶୂନ୍ୟ *obj, ପୂର୍ଣ୍ଣସଂଖ୍ୟା opt_flags, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags, ଅକ୍ଷର **buffer,
                     ଅଚଳ ଅକ୍ଷର ଚାବି_val_sep, ଅଚଳ ଅକ୍ଷର pairs_sep)
{
    AVBPrint bprint;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, cnt = 0;

    ଯଦି (pairs_sep == '\0' || ଚାବି_val_sep == '\0' || pairs_sep == ଚାବି_val_sep ||
        pairs_sep == '\\' || ଚାବି_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି (!obj || !buffer)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    *buffer = ଖାଲି;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        ଚାବି_val_sep, pairs_sep);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
    ଫେରନ୍ତୁ 0;
}
