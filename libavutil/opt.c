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

#అన్తర్భావ "avutil.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "channel_layout.h"
#అన్తర్భావ "dict.h"
#అన్తర్భావ "eval.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "parseutils.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "mathematics.h"
#అన్తర్భావ "opt.h"
#అన్తర్భావ "samplefmt.h"
#అన్తర్భావ "bprint.h"

#అన్తర్భావ <float.h>

#నిర్వచించు TYPE_పునాది(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

స్థిరరాశి AVOption *av_opt_తదుపరి(స్థిరరాశి శూన్య *obj, స్థిరరాశి AVOption *చివరి)
{
    స్థిరరాశి AVClass *class;
    ఒకవేళ (!obj)
        తిరిగి ఖాళీ;
    class = *(స్థిరరాశి AVClass**)obj;
    ఒకవేళ (!చివరి && class && class->option && class->option[0].name)
        తిరిగి class->option;
    ఒకవేళ (చివరి && చివరి[1].name)
        తిరిగి ++చివరి;
    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి నిర్మాణం {
    size_t      కొలత;
    స్థిరరాశి అక్షరం *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { పరిమాణం(గుర్తులేని),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { పరిమాణం(పూర్ణాంకం),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { పరిమాణం(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { పరిమాణం(గుర్తులేని),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { పరిమాణం(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { పరిమాణం(ద్విగుణ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { పరిమాణం(దశాంశం),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { పరిమాణం(అక్షరం *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { పరిమాణం(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ద్విమాన]        = { పరిమాణం(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { పరిమాణం(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_కొలత]    = { పరిమాణం(పూర్ణాంకం[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_రేటు]    = { పరిమాణం(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { పరిమాణం(గణన AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { పరిమాణం(గణన AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { పరిమాణం(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { పరిమాణం(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { పరిమాణం(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { పరిమాణం(పూర్ణాంకం),            "<boolean>" },
};

// option is plain old data
స్థిర పూర్ణాంకం opt_is_pod(గణన AVOptionType type)
{
    ఎంపిక (type) {
    స్థితి AV_OPT_TYPE_FLAGS:
    స్థితి AV_OPT_TYPE_INT:
    స్థితి AV_OPT_TYPE_INT64:
    స్థితి AV_OPT_TYPE_DOUBLE:
    స్థితి AV_OPT_TYPE_FLOAT:
    స్థితి AV_OPT_TYPE_RATIONAL:
    స్థితి AV_OPT_TYPE_UINT64:
    స్థితి AV_OPT_TYPE_IMAGE_కొలత:
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
    స్థితి AV_OPT_TYPE_VIDEO_రేటు:
    స్థితి AV_OPT_TYPE_DURATION:
    స్థితి AV_OPT_TYPE_COLOR:
    స్థితి AV_OPT_TYPE_BOOL:
    స్థితి AV_OPT_TYPE_UINT:
        తిరిగి 1;
    }
    తిరిగి 0;
}

స్థిర uint8_t opt_array_sep(స్థిరరాశి AVOption *o)
{
    స్థిరరాశి AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    తిరిగి (d && d->sep) ? d->sep : ',';
}

స్థిర శూన్య *opt_array_pelem(స్థిరరాశి AVOption *o, శూన్య *array, గుర్తులేని idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    తిరిగి (uint8_t *)array + idx * opt_type_desc[TYPE_పునాది(o->type)].కొలత;
}

స్థిర గుర్తులేని *opt_array_pcount(స్థిరరాశి శూన్య *parray)
{
    తిరిగి (గుర్తులేని *)((స్థిరరాశి శూన్య * స్థిరరాశి *)parray + 1);
}

స్థిర శూన్య opt_free_elem(గణన AVOptionType type, శూన్య *ptr)
{
    ఎంపిక (TYPE_పునాది(type)) {
    స్థితి AV_OPT_TYPE_STRING:
    స్థితి AV_OPT_TYPE_ద్విమాన:
        av_freep(ptr);
        ఆపు;

    స్థితి AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        ఆపు;

    స్థితి AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        ఆపు;

    అప్రమేయ:
        ఆపు;
    }
}

స్థిర శూన్య opt_free_array(స్థిరరాశి AVOption *o, శూన్య *parray, గుర్తులేని *లెక్క)
{
    కొరకు (గుర్తులేని i = 0; i < *లెక్క; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(శూన్య **)parray, i));

    av_freep(parray);
    *లెక్క = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
స్థిర పూర్ణాంకం opt_సమితి_init(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags,
                        పూర్ణాంకం require_type,
                        శూన్య **ptgt, స్థిరరాశి AVOption **po, శూన్య **pdst)
{
    శూన్య *logctx;
    స్థిరరాశి AVOption *o;
    శూన్య *tgt;

    o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &tgt);
    ఒకవేళ (!o || (!tgt && !(శోధన_flags & AV_OPT_శోధన_FAKE_OBJ)))
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;

    ఒకవేళ (o->flags & AV_OPT_FLAG_READONLY)
        తిరిగి AVERROR(EINVAL);

    logctx = tgt ? obj : ఖాళీ;

    ఒకవేళ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        గుర్తులేని *state_flags = ఖాళీ;
        స్థిరరాశి AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(స్థిరరాశి AVClass**)tgt;
        ఒకవేళ (class->state_flags_స్థానభ్రంశం)
            state_flags = (గుర్తులేని*)((uint8_t*)tgt + class->state_flags_స్థానభ్రంశం);

        ఒకవేళ (!state_flags && obj != tgt) {
            class = *(స్థిరరాశి AVClass**)obj;
            ఒకవేళ (class->state_flags_స్థానభ్రంశం)
                state_flags = (గుర్తులేని*)((uint8_t*)obj + class->state_flags_స్థానభ్రంశం);
        }

        ఒకవేళ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            తిరిగి AVERROR(EINVAL);
        }
    }

    ఒకవేళ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ఒకవేళ (po)
        *po   = o;
    ఒకవేళ (ptgt)
        *ptgt = tgt;
    ఒకవేళ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->స్థానభ్రంశం : ఖాళీ;

    తిరిగి 0;
}

స్థిర AVRational double_గమ్యం_rational(ద్విగుణ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ఒకవేళ ((!r.అంకె || !r.den) && d)
         r = av_d2q(d, గరిష్ఠ_పూర్ణాంకం);
     తిరిగి r;
}

స్థిర పూర్ణాంకం read_సంఖ్య(స్థిరరాశి AVOption *o, స్థిరరాశి శూన్య *dst, ద్విగుణ *అంకె, పూర్ణాంకం *den, int64_t *intnum)
{
    ఎంపిక (TYPE_పునాది(o->type)) {
    స్థితి AV_OPT_TYPE_FLAGS:
        *intnum = *(గుర్తులేని పూర్ణాంకం*)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(గణన AVPixelFormat *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(గణన AVSampleFormat *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_BOOL:
    స్థితి AV_OPT_TYPE_INT:
        *intnum = *(పూర్ణాంకం *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_UINT:
        *intnum = *(గుర్తులేని పూర్ణాంకం *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_DURATION:
    స్థితి AV_OPT_TYPE_INT64:
    స్థితి AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_FLOAT:
        *అంకె = *(దశాంశం *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_DOUBLE:
        *అంకె = *(ద్విగుణ *)dst;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->అంకె;
        *den    = ((AVRational *)dst)->den;
        తిరిగి 0;
    స్థితి AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        తిరిగి 0;
    }
    తిరిగి AVERROR(EINVAL);
}

స్థిర పూర్ణాంకం write_సంఖ్య(శూన్య *obj, స్థిరరాశి AVOption *o, శూన్య *dst,
                        ద్విగుణ అంకె, పూర్ణాంకం den, int64_t intnum,
                        పూర్ణాంకం ignore_range)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    స్థిరరాశి గణన AVOptionType type = TYPE_పునాది(o->type);

    ఒకవేళ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < అంకె * intnum || o->min * den > అంకె * intnum)) {
        అంకె = den ? అంకె * intnum / den : (అంకె && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               అంకె, o->name, o->min, o->max);
        తిరిగి AVERROR(ERANGE);
    }
    ఒకవేళ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        ద్విగుణ d = అంకె*intnum/den;
        ఒకవేళ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   అంకె*intnum/den, o->name);
            తిరిగి AVERROR(ERANGE);
        }
    }

    ఒకవేళ (!dst)
        తిరిగి 0;

    ఎంపిక (type) {
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
        *(గణన AVPixelFormat *)dst = llrint(అంకె / den) * intnum;
        ఆపు;
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
        *(గణన AVSampleFormat *)dst = llrint(అంకె / den) * intnum;
        ఆపు;
    స్థితి AV_OPT_TYPE_BOOL:
    స్థితి AV_OPT_TYPE_FLAGS:
    స్థితి AV_OPT_TYPE_INT:
    స్థితి AV_OPT_TYPE_UINT:
        *(పూర్ణాంకం *)dst = llrint(అంకె / den) * intnum;
        ఆపు;
    స్థితి AV_OPT_TYPE_DURATION:
    స్థితి AV_OPT_TYPE_INT64:{
        ద్విగుణ d = అంకె / den;
        ఒకవేళ (intnum == 1 && d == (ద్విగుణ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } లేకపోతే
            *(int64_t *)dst = llrint(d) * intnum;
        ఆపు;}
    స్థితి AV_OPT_TYPE_UINT64:{
        ద్విగుణ d = అంకె / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ఒకవేళ (intnum == 1 && d == (ద్విగుణ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } లేకపోతే ఒకవేళ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } లేకపోతే {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        ఆపు;}
    స్థితి AV_OPT_TYPE_FLOAT:
        *(దశాంశం *)dst = అంకె * intnum / den;
        ఆపు;
    స్థితి AV_OPT_TYPE_DOUBLE:
        *(ద్విగుణ    *)dst = అంకె * intnum / den;
        ఆపు;
    స్థితి AV_OPT_TYPE_RATIONAL:
    స్థితి AV_OPT_TYPE_VIDEO_రేటు:
        ఒకవేళ ((పూర్ణాంకం) అంకె == అంకె)
            *(AVRational *)dst = (AVRational) { అంకె *intnum, den };
        లేకపోతే
            *(AVRational *)dst = double_గమ్యం_rational(అంకె * intnum / den);
        ఆపు;
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }
    తిరిగి 0;
}

స్థిర పూర్ణాంకం hexchar2int(అక్షరం c) {
    ఒకవేళ (c >= '0' && c <= '9')
        తిరిగి c - '0';
    ఒకవేళ (c >= 'a' && c <= 'f')
        తిరిగి c - 'a' + 10;
    ఒకవేళ (c >= 'A' && c <= 'F')
        తిరిగి c - 'A' + 10;
    తిరిగి -1;
}

స్థిర పూర్ణాంకం సమితి_string_ద్విమాన(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t **dst)
{
    పూర్ణాంకం *lendst;
    uint8_t *bin, *ptr;
    పూర్ణాంకం len;

    ఒకవేళ (dst) {
        lendst = (పూర్ణాంకం *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ఒకవేళ (!val || !(len = అక్షరశ్రేణి_పొడవు(val)))
        తిరిగి 0;

    ఒకవేళ (len & 1)
        తిరిగి AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ఒకవేళ (!ptr)
        తిరిగి AVERROR(ENOMEM);
    అయితే (*val) {
        పూర్ణాంకం a = hexchar2int(*val++);
        పూర్ణాంకం b = hexchar2int(*val++);
        ఒకవేళ (a < 0 || b < 0) {
            av_free(bin);
            తిరిగి AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ఒకవేళ (dst) {
        *dst    = bin;
        *lendst = len;
    } లేకపోతే {
        av_free(bin);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం సమితి_string(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t **dst)
{
    ఒకవేళ (!dst)
        తిరిగి 0;
    av_freep(dst);
    ఒకవేళ (!val)
        తిరిగి 0;
    *dst = av_strdup(val);
    తిరిగి *dst ? 0 : AVERROR(ENOMEM);
}

#నిర్వచించు DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

స్థిర పూర్ణాంకం సమితి_string_సంఖ్య(శూన్య *obj, శూన్య *లక్ష్యం_obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, శూన్య *dst)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    స్థిరరాశి గణన AVOptionType type = TYPE_పునాది(o->type);
    పూర్ణాంకం ret = 0;

    ఒకవేళ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_రేటు) {
        పూర్ణాంకం అంకె, den;
        అక్షరం c;
        ఒకవేళ (అక్షరశ్రేణి_చదువు(val, "%d%*1[:/]%d%c", &అంకె, &den, &c) == 2) {
            ఒకవేళ ((ret = write_సంఖ్య(obj, o, dst, 1, den, అంకె, 0)) >= 0)
                తిరిగి ret;
            ret = 0;
        }
    }

    కొరకు (;;) {
        పూర్ణాంకం i = 0;
        అక్షరం buf[256];
        పూర్ణాంకం cmd = 0;
        ద్విగుణ d;
        int64_t intnum = 1;

        ఒకవేళ (type == AV_OPT_TYPE_FLAGS) {
            ఒకవేళ (*val == '+' || *val == '-')
                cmd = *(val++);
            కొరకు (; i < పరిమాణం(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            పూర్ణాంకం res;
            పూర్ణాంకం ci = 0;
            ద్విగుణ const_విలువలు[64];
            స్థిరరాశి అక్షరం * const_పేర్లు[64];
            పూర్ణాంకం శోధన_flags = (o->flags & AV_OPT_FLAG_బిడ్డ_CONSTS) ? AV_OPT_శోధన_CHILDREN : 0;
            స్థిరరాశి AVOption *o_named = av_opt_కనుగొను(లక్ష్యం_obj, i ? buf : val, o->unit, 0, శోధన_flags);
            ఒకవేళ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ఒకవేళ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } లేకపోతే {
                ఒకవేళ (o->unit) {
                    కొరకు (o_named = ఖాళీ; o_named = av_opt_తదుపరి(లక్ష్యం_obj, o_named); ) {
                        ఒకవేళ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ఒకవేళ (ci + 6 >= FF_ARRAY_ELEMS(const_విలువలు)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                తిరిగి AVERROR_PATCHWELCOME;
                            }
                            const_పేర్లు [ci  ] = o_named->name;
                            const_విలువలు[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_పేర్లు [ci  ] = "default";
                const_విలువలు[ci++] = DEFAULT_NUMVAL(o);
                const_పేర్లు [ci  ] = "max";
                const_విలువలు[ci++] = o->max;
                const_పేర్లు [ci  ] = "min";
                const_విలువలు[ci++] = o->min;
                const_పేర్లు [ci  ] = "none";
                const_విలువలు[ci++] = 0;
                const_పేర్లు [ci  ] = "all";
                const_విలువలు[ci++] = ~0;
                const_పేర్లు [ci] = ఖాళీ;
                const_విలువలు[ci] = 0;

                res = av_సమాసం_parse_and_eval(&d, i ? buf : val, const_పేర్లు,
                                            const_విలువలు, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, 0, obj);
                ఒకవేళ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    తిరిగి res;
                }
            }
        }
        ఒకవేళ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(గుర్తులేని పూర్ణాంకం*)dst;
            ఒకవేళ (cmd == '+')
                d = intnum | (int64_t)d;
            లేకపోతే ఒకవేళ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ఒకవేళ ((ret = write_సంఖ్య(obj, o, dst, d, 1, 1, 0)) < 0)
            తిరిగి ret;
        val += i;
        ఒకవేళ (!i || !*val)
            తిరిగి 0;
    }
}

స్థిర పూర్ణాంకం సమితి_string_image_కొలత(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, పూర్ణాంకం *dst)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    పూర్ణాంకం tmp[2];
    పూర్ణాంకం ret;

    ఒకవేళ (!val || !strcmp(val, "none")) {
        ఒకవేళ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        తిరిగి 0;
    }
    ret = av_parse_video_కొలత(&tmp[0], &tmp[1], val);
    ఒకవేళ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        తిరిగి ret;
    }
    ఒకవేళ (dst)
        జ్ఞాపకం_నకలు(dst, tmp, పరిమాణం(tmp));
    తిరిగి ret;
}

స్థిర పూర్ణాంకం సమితి_string_video_రేటు(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, AVRational *dst)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    AVRational tmp;
    పూర్ణాంకం ret = av_parse_video_రేటు(&tmp, val);
    ఒకవేళ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ఒకవేళ (dst)
        *dst = tmp;
    తిరిగి ret;
}

స్థిర పూర్ణాంకం సమితి_string_color(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t *dst)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    పూర్ణాంకం ret;

    ఒకవేళ (!val) {
        తిరిగి 0;
    } లేకపోతే {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ఒకవేళ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            తిరిగి ret;
        }
        ఒకవేళ (dst)
            జ్ఞాపకం_నకలు(dst, tmp, పరిమాణం(tmp));
        తిరిగి ret;
    }
    తిరిగి 0;
}

స్థిర స్థిరరాశి అక్షరం *get_bool_name(పూర్ణాంకం val)
{
    ఒకవేళ (val < 0)
        తిరిగి "auto";
    తిరిగి val ? "true" : "false";
}

స్థిర పూర్ణాంకం సమితి_string_bool(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, పూర్ణాంకం *dst)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    పూర్ణాంకం n;

    ఒకవేళ (!val)
        తిరిగి 0;

    ఒకవేళ (!strcmp(val, "auto")) {
        n = -1;
    } లేకపోతే ఒకవేళ (av_సరిపోలిక_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } లేకపోతే ఒకవేళ (av_సరిపోలిక_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } లేకపోతే {
        అక్షరం *చివర = ఖాళీ;
        n = strtol(val, &చివర, 10);
        ఒకవేళ (val + అక్షరశ్రేణి_పొడవు(val) != చివర)
            వెళ్ళు fail;
    }

    ఒకవేళ (n < o->min || n > o->max)
        వెళ్ళు fail;

    ఒకవేళ (dst)
    *dst = n;
    తిరిగి 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    తిరిగి AVERROR(EINVAL);
}

స్థిర పూర్ణాంకం సమితి_string_fmt(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t *dst,
                          పూర్ణాంకం fmt_nb, పూర్ణాంకం ((*get_fmt)(స్థిరరాశి అక్షరం *)), స్థిరరాశి అక్షరం *desc,
                          గణన AVOptionType type)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    పూర్ణాంకం fmt, min, max;

    ఒకవేళ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } లేకపోతే {
        fmt = get_fmt(val);
        ఒకవేళ (fmt == -1) {
            అక్షరం *తోక;
            fmt = strtol(val, &తోక, 0);
            ఒకవేళ (*తోక || (గుర్తులేని)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                తిరిగి AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ఒకవేళ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ఒకవేళ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        తిరిగి AVERROR(ERANGE);
    }

    ఒకవేళ (dst)
    ఎంపిక (type) {
    స్థితి AV_OPT_TYPE_PIXEL_FMT:  *(గణన AVPixelFormat *)dst = fmt; ఆపు;
    స్థితి AV_OPT_TYPE_SAMPLE_FMT: *(గణన AVSampleFormat*)dst = fmt; ఆపు;
    అప్రమేయ: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    తిరిగి 0;
}

స్థిర పూర్ణాంకం get_pix_fmt(స్థిరరాశి అక్షరం *name)
{
    తిరిగి av_get_pix_fmt(name);
}

స్థిర పూర్ణాంకం సమితి_string_pixel_fmt(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t *dst)
{
    తిరిగి సమితి_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

స్థిర పూర్ణాంకం get_sample_fmt(స్థిరరాశి అక్షరం *name)
{
    తిరిగి av_get_sample_fmt(name);
}

స్థిర పూర్ణాంకం సమితి_string_sample_fmt(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t *dst)
{
    తిరిగి సమితి_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

స్థిర పూర్ణాంకం సమితి_string_dict(శూన్య *obj, స్థిరరాశి AVOption *o, స్థిరరాశి అక్షరం *val, uint8_t **dst)
{
    AVDictionary *options = ఖాళీ;

    ఒకవేళ (val) {
        పూర్ణాంకం ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ఒకవేళ (ret < 0) {
            av_dict_free(&options);
            తిరిగి ret;
        }
    }

    ఒకవేళ (!dst) {
        av_dict_free(&options);
        తిరిగి 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం సమితి_string_channel_layout(శూన్య *obj, స్థిరరాశి AVOption *o,
                                     స్థిరరాశి అక్షరం *val, శూన్య *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    పూర్ణాంకం ret;
    ఒకవేళ (dst)
    av_channel_layout_uninit(channel_layout);
    లేకపోతే
        channel_layout = &tmp;
    ఒకవేళ (!val)
        తిరిగి 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    ఒకవేళ (!dst)
        av_channel_layout_uninit(channel_layout);
    తిరిగి 0;
}

స్థిర పూర్ణాంకం opt_సమితి_elem(శూన్య *obj, శూన్య *లక్ష్యం_obj, స్థిరరాశి AVOption *o,
                        స్థిరరాశి అక్షరం *val, శూన్య *dst)
{
    శూన్య *logctx = dst ? obj : ఖాళీ;
    స్థిరరాశి గణన AVOptionType type = TYPE_పునాది(o->type);
    పూర్ణాంకం ret;

    ఒకవేళ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_కొలత &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        తిరిగి AVERROR(EINVAL);

    ఎంపిక (type) {
    స్థితి AV_OPT_TYPE_BOOL:
        తిరిగి సమితి_string_bool(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_STRING:
        తిరిగి సమితి_string(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_ద్విమాన:
        తిరిగి సమితి_string_ద్విమాన(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_FLAGS:
    స్థితి AV_OPT_TYPE_INT:
    స్థితి AV_OPT_TYPE_UINT:
    స్థితి AV_OPT_TYPE_INT64:
    స్థితి AV_OPT_TYPE_UINT64:
    స్థితి AV_OPT_TYPE_FLOAT:
    స్థితి AV_OPT_TYPE_DOUBLE:
    స్థితి AV_OPT_TYPE_RATIONAL:
        తిరిగి సమితి_string_సంఖ్య(obj, లక్ష్యం_obj, o, val, dst);
    స్థితి AV_OPT_TYPE_IMAGE_కొలత:
        తిరిగి సమితి_string_image_కొలత(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_VIDEO_రేటు: {
        AVRational tmp;
        ret = సమితి_string_video_రేటు(obj, o, val, &tmp);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
        తిరిగి write_సంఖ్య(obj, o, dst, 1, tmp.den, tmp.అంకె, 0);
    }
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
        తిరిగి సమితి_string_pixel_fmt(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
        తిరిగి సమితి_string_sample_fmt(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ఒకవేళ (val) {
                ఒకవేళ ((ret = av_parse_సమయం(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    తిరిగి ret;
                }
            }
            ఒకవేళ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                తిరిగి AVERROR(ERANGE);
            }
            ఒకవేళ (dst)
            *(int64_t *)dst = usecs;
            తిరిగి 0;
        }
    స్థితి AV_OPT_TYPE_COLOR:
        తిరిగి సమితి_string_color(obj, o, val, dst);
    స్థితి AV_OPT_TYPE_CHLAYOUT:
        ret = సమితి_string_channel_layout(obj, o, val, dst);
        ఒకవేళ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        తిరిగి ret;
    స్థితి AV_OPT_TYPE_DICT:
        తిరిగి సమితి_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    తిరిగి AVERROR(EINVAL);
}

స్థిర పూర్ణాంకం opt_సమితి_array(శూన్య *obj, శూన్య *లక్ష్యం_obj, స్థిరరాశి AVOption *o,
                         స్థిరరాశి అక్షరం *val, శూన్య *dst)
{
    స్థిరరాశి AVOptionArrayDef *arr = o->default_val.arr;
    స్థిరరాశి size_t      elem_కొలత = opt_type_desc[TYPE_పునాది(o->type)].కొలత;
    స్థిరరాశి uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ఖాళీ;

    శూన్య      *logctx = dst ? obj : ఖాళీ;
    శూన్య       *elems = ఖాళీ;
    గుర్తులేని nb_elems = 0;
    పూర్ణాంకం ret;

    ఒకవేళ (val && *val) {
        str = av_malloc(అక్షరశ్రేణి_పొడవు(val) + 1);
        ఒకవేళ (!str)
            తిరిగి AVERROR(ENOMEM);
    }

    // split and unescape the string
    అయితే (val && *val) {
        uint8_t *p = str;
        శూన్య *tmp;

        ఒకవేళ (arr && arr->కొలత_max && nb_elems >= arr->కొలత_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->కొలత_max, o->name);
            ret = AVERROR(EINVAL);
            వెళ్ళు fail;
        }

        కొరకు (; *val; val++, p++) {
            ఒకవేళ (*val == '\\' && val[1])
                val++;
            లేకపోతే ఒకవేళ (*val == sep) {
                val++;
                ఆపు;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_కొలత);
        ఒకవేళ (!tmp) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_కొలత);

        ret = opt_సమితి_elem(obj, లక్ష్యం_obj, o, str, tmp);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
        nb_elems++;
    }
    av_freep(&str);

    ఒకవేళ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ఒకవేళ (arr && nb_elems < arr->కొలత_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->కొలత_min, o->name);
        ret = AVERROR(EINVAL);
        వెళ్ళు fail;
    }

    ఒకవేళ (dst) {
    *((శూన్య **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } లేకపోతే
        opt_free_array(o, &elems, &nb_elems);

    తిరిగి 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    తిరిగి ret;
}

పూర్ణాంకం av_opt_సమితి(శూన్య *obj, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *val, పూర్ణాంకం శోధన_flags)
{
    శూన్య *dst, *లక్ష్యం_obj;
    స్థిరరాశి AVOption *o;
    పూర్ణాంకం ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, 0, &లక్ష్యం_obj, &o, &dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    తిరిగి ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_సమితి_array : opt_సమితి_elem)(obj, లక్ష్యం_obj, o, val, dst);
}

#నిర్వచించు OPT_EVAL_సంఖ్య(name, opttype, vartype)                         \
పూర్ణాంకం av_opt_eval_ ## name(శూన్య *obj, స్థిరరాశి AVOption *o,                  \
                         స్థిరరాశి అక్షరం *val, vartype *name ## బహిర్గతం_3)        \
{                                                                       \
    ఒకవేళ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        తిరిగి AVERROR(EINVAL);                                         \
    తిరిగి సమితి_string_సంఖ్య(obj, obj, o, val, name ## బహిర్గతం_3);           \
}

OPT_EVAL_సంఖ్య(flags,  AV_OPT_TYPE_FLAGS,    పూర్ణాంకం)
OPT_EVAL_సంఖ్య(పూర్ణాంకం,    AV_OPT_TYPE_INT,      పూర్ణాంకం)
OPT_EVAL_సంఖ్య(uint,   AV_OPT_TYPE_UINT,     గుర్తులేని)
OPT_EVAL_సంఖ్య(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_సంఖ్య(దశాంశం,  AV_OPT_TYPE_FLOAT,    దశాంశం)
OPT_EVAL_సంఖ్య(ద్విగుణ, AV_OPT_TYPE_DOUBLE,   ద్విగుణ)
OPT_EVAL_సంఖ్య(q,      AV_OPT_TYPE_RATIONAL, AVRational)

స్థిర పూర్ణాంకం సమితి_సంఖ్య(శూన్య *obj, స్థిరరాశి అక్షరం *name, ద్విగుణ అంకె, పూర్ణాంకం den, int64_t intnum,
                      పూర్ణాంకం శోధన_flags, పూర్ణాంకం require_type)
{
    శూన్య *dst;
    స్థిరరాశి AVOption *o;
    పూర్ణాంకం ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, require_type, ఖాళీ, &o, &dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    ఒకవేళ (dst)
        ret = write_సంఖ్య(obj, o, dst, అంకె, den, intnum, 0);

    తిరిగి ret;
}

పూర్ణాంకం av_opt_సమితి_int(శూన్య *obj, స్థిరరాశి అక్షరం *name, int64_t val, పూర్ణాంకం శోధన_flags)
{
    తిరిగి సమితి_సంఖ్య(obj, name, 1, 1, val, శోధన_flags, 0);
}

పూర్ణాంకం av_opt_సమితి_double(శూన్య *obj, స్థిరరాశి అక్షరం *name, ద్విగుణ val, పూర్ణాంకం శోధన_flags)
{
    తిరిగి సమితి_సంఖ్య(obj, name, val, 1, 1, శోధన_flags, 0);
}

పూర్ణాంకం av_opt_సమితి_q(శూన్య *obj, స్థిరరాశి అక్షరం *name, AVRational val, పూర్ణాంకం శోధన_flags)
{
    తిరిగి సమితి_సంఖ్య(obj, name, val.అంకె, val.den, 1, శోధన_flags, 0);
}

పూర్ణాంకం av_opt_సమితి_bin(శూన్య *obj, స్థిరరాశి అక్షరం *name, స్థిరరాశి uint8_t *val, పూర్ణాంకం len, పూర్ణాంకం శోధన_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    పూర్ణాంకం *lendst;
    పూర్ణాంకం ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, AV_OPT_TYPE_ద్విమాన,
                       ఖాళీ, ఖాళీ, (శూన్య**)&dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (dst) {
    ptr = len ? av_malloc(len) : ఖాళీ;
    ఒకవేళ (len && !ptr)
        తిరిగి AVERROR(ENOMEM);

    lendst = (పూర్ణాంకం *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ఒకవేళ (len)
        జ్ఞాపకం_నకలు(ptr, val, len);
    }

    తిరిగి 0;
}

పూర్ణాంకం av_opt_సమితి_image_కొలత(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం శోధన_flags)
{
    స్థిరరాశి AVOption *o;
    శూన్య *logctx;
    పూర్ణాంకం *dst;
    పూర్ణాంకం ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, AV_OPT_TYPE_IMAGE_కొలత,
                       ఖాళీ, &o, (శూన్య**)&dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    logctx = dst ? obj : ఖాళీ;

    ఒకవేళ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    తిరిగి 0;
}

పూర్ణాంకం av_opt_సమితి_video_రేటు(శూన్య *obj, స్థిరరాశి అక్షరం *name, AVRational val, పూర్ణాంకం శోధన_flags)
{
    తిరిగి సమితి_సంఖ్య(obj, name, val.అంకె, val.den, 1, శోధన_flags, AV_OPT_TYPE_VIDEO_రేటు);
}

స్థిర పూర్ణాంకం సమితి_format(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం fmt, పూర్ణాంకం శోధన_flags,
                      గణన AVOptionType type, స్థిరరాశి అక్షరం *desc, పూర్ణాంకం nb_fmts)
{
    స్థిరరాశి AVOption *o;
    శూన్య *logctx;
    పూర్ణాంకం *dst;
    పూర్ణాంకం min, max, ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, type, ఖాళీ, &o, (శూన్య**)&dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    logctx = dst ? obj : ఖాళీ;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ఒకవేళ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        తిరిగి AVERROR(ERANGE);
    }
    ఒకవేళ (dst)
    *dst = fmt;
    తిరిగి 0;
}

పూర్ణాంకం av_opt_సమితి_pixel_fmt(శూన్య *obj, స్థిరరాశి అక్షరం *name, గణన AVPixelFormat fmt, పూర్ణాంకం శోధన_flags)
{
    తిరిగి సమితి_format(obj, name, fmt, శోధన_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

పూర్ణాంకం av_opt_సమితి_sample_fmt(శూన్య *obj, స్థిరరాశి అక్షరం *name, గణన AVSampleFormat fmt, పూర్ణాంకం శోధన_flags)
{
    తిరిగి సమితి_format(obj, name, fmt, శోధన_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

పూర్ణాంకం av_opt_సమితి_dict_val(శూన్య *obj, స్థిరరాశి అక్షరం *name, స్థిరరాశి AVDictionary *val,
                        పూర్ణాంకం శోధన_flags)
{
    AVDictionary **dst;
    పూర్ణాంకం ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, AV_OPT_TYPE_DICT, ఖాళీ, ఖాళీ,
                       (శూన్య**)&dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    తిరిగి ret;
}

పూర్ణాంకం av_opt_సమితి_chlayout(శూన్య *obj, స్థిరరాశి అక్షరం *name,
                        స్థిరరాశి AVChannelLayout *channel_layout,
                        పూర్ణాంకం శోధన_flags)
{
    AVChannelLayout *dst;
    పూర్ణాంకం ret;

    ret = opt_సమితి_init(obj, name, శోధన_flags, AV_OPT_TYPE_CHLAYOUT, ఖాళీ, ఖాళీ,
                       (శూన్య**)&dst);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    తిరిగి ret;
}

స్థిర శూన్య format_duration(అక్షరం *buf, size_t కొలత, int64_t d)
{
    అక్షరం *e;

    av_assert0(కొలత >= 25);
    ఒకవేళ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        కొలత--;
        d = -d;
    }
    ఒకవేళ (d == INT64_MAX)
        snprintf(buf, కొలత, "INT64_MAX");
    లేకపోతే ఒకవేళ (d == INT64_MIN)
        snprintf(buf, కొలత, "INT64_MIN");
    లేకపోతే ఒకవేళ (d > (int64_t)3600*1000000)
        snprintf(buf, కొలత, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (పూర్ణాంకం)((d / 60000000) % 60),
                 (పూర్ణాంకం)((d / 1000000) % 60),
                 (పూర్ణాంకం)(d % 1000000));
    లేకపోతే ఒకవేళ (d > 60*1000000)
        snprintf(buf, కొలత, "%d:%02d.%06d",
                 (పూర్ణాంకం)(d / 60000000),
                 (పూర్ణాంకం)((d / 1000000) % 60),
                 (పూర్ణాంకం)(d % 1000000));
    లేకపోతే
        snprintf(buf, కొలత, "%d.%06d",
                 (పూర్ణాంకం)(d / 1000000),
                 (పూర్ణాంకం)(d % 1000000));
    e = buf + అక్షరశ్రేణి_పొడవు(buf);
    అయితే (e > buf && e[-1] == '0')
        *(--e) = 0;
    ఒకవేళ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

స్థిర పూర్ణాంకం opt_get_elem(స్థిరరాశి AVOption *o, uint8_t **pbuf, size_t buf_len,
                        స్థిరరాశి శూన్య *dst, పూర్ణాంకం శోధన_flags)
{
    పూర్ణాంకం ret;

    ఎంపిక (TYPE_పునాది(o->type)) {
    స్థితి AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(పూర్ణాంకం *)dst));
        ఆపు;
    స్థితి AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(పూర్ణాంకం *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(పూర్ణాంకం *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(గుర్తులేని *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(దశాంశం *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(ద్విగుణ *)dst);
        ఆపు;
    స్థితి AV_OPT_TYPE_VIDEO_రేటు:
    స్థితి AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->అంకె, ((AVRational *)dst)->den);
        ఆపు;
    స్థితి AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        ఆపు;
    స్థితి AV_OPT_TYPE_STRING:
        ఒకవేళ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } లేకపోతే ఒకవేళ (శోధన_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ఖాళీ;
            తిరిగి 0;
        } లేకపోతే {
            *pbuf = av_strdup("");
        }
        తిరిగి *pbuf ? 0 : AVERROR(ENOMEM);
    స్థితి AV_OPT_TYPE_ద్విమాన: {
        స్థిరరాశి uint8_t *bin;
        పూర్ణాంకం len;

        ఒకవేళ (!*(uint8_t **)dst && (శోధన_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ఖాళీ;
            తిరిగి 0;
        }
        len = *(పూర్ణాంకం *)(((uint8_t *)dst) + పరిమాణం(uint8_t *));
        ఒకవేళ ((uint64_t)len * 2 + 1 > గరిష్ఠ_పూర్ణాంకం)
            తిరిగి AVERROR(EINVAL);
        ఒకవేళ (!(*pbuf = av_malloc(len * 2 + 1)))
            తిరిగి AVERROR(ENOMEM);
        ఒకవేళ (!len) {
            *pbuf[0] = '\0';
            తిరిగి 0;
        }
        bin = *(uint8_t **)dst;
        కొరకు (పూర్ణాంకం i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        తిరిగి 0;
    }
    స్థితి AV_OPT_TYPE_IMAGE_కొలత:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((పూర్ణాంకం *)dst)[0], ((పూర్ణాంకం *)dst)[1]);
        ఆపు;
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (అక్షరం *)av_x_if_null(av_get_pix_fmt_name(*(గణన AVPixelFormat *)dst), "none"));
        ఆపు;
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (అక్షరం *)av_x_if_null(av_get_sample_fmt_name(*(గణన AVSampleFormat *)dst), "none"));
        ఆపు;
    స్థితి AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = అక్షరశ్రేణి_పొడవు(*pbuf); // no overflow possible, checked by an assert
        ఆపు;
    }
    స్థితి AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (పూర్ణాంకం)((uint8_t *)dst)[0], (పూర్ణాంకం)((uint8_t *)dst)[1],
                       (పూర్ణాంకం)((uint8_t *)dst)[2], (పూర్ణాంకం)((uint8_t *)dst)[3]);
        ఆపు;
    స్థితి AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        ఆపు;
    స్థితి AV_OPT_TYPE_DICT:
        ఒకవేళ (!*(AVDictionary **)dst && (శోధన_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ఖాళీ;
            తిరిగి 0;
        }
        తిరిగి av_dict_get_string(*(AVDictionary **)dst, (అక్షరం **)pbuf, '=', ':');
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }

    తిరిగి ret;
}

స్థిర పూర్ణాంకం opt_get_array(స్థిరరాశి AVOption *o, శూన్య *dst, uint8_t **బహిర్గతం_val)
{
    స్థిరరాశి గుర్తులేని లెక్క = *opt_array_pcount(dst);
    స్థిరరాశి uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ఖాళీ;
    size_t   str_len = 0;
    పూర్ణాంకం ret;

    *బహిర్గతం_val = ఖాళీ;

    కొరకు (గుర్తులేని i = 0; i < లెక్క; i++) {
        uint8_t buf[128], *బహిర్గతం = buf;
        size_t బహిర్గతం_len;

        ret = opt_get_elem(o, &బహిర్గతం, పరిమాణం(buf),
                           opt_array_pelem(o, *(శూన్య **)dst, i), 0);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;

        బహిర్గతం_len = అక్షరశ్రేణి_పొడవు(బహిర్గతం);
        ఒకవేళ (బహిర్గతం_len > SIZE_MAX / 2 - !!i ||
            !!i + బహిర్గతం_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            వెళ్ళు fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + బహిర్గతం_len * 2 + !!i);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;

        // add separator if needed
        ఒకవేళ (i)
            str[str_len++] = sep;

        // escape the element
        కొరకు (గుర్తులేని j = 0; j < బహిర్గతం_len; j++) {
            uint8_t val = బహిర్గతం[j];
            ఒకవేళ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ఒకవేళ (బహిర్గతం != buf)
            av_freep(&బహిర్గతం);
        ఒకవేళ (ret < 0) {
            av_freep(&str);
            తిరిగి ret;
        }
    }

    *బహిర్గతం_val = str;

    తిరిగి 0;
}

పూర్ణాంకం av_opt_get(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, uint8_t **బహిర్గతం_val)
{
    శూన్య *dst, *లక్ష్యం_obj;
    స్థిరరాశి AVOption *o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    uint8_t *బహిర్గతం, buf[128];
    పూర్ణాంకం ret;

    ఒకవేళ (!o || !లక్ష్యం_obj || (o->స్థానభ్రంశం<=0 && o->type != AV_OPT_TYPE_CONST))
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;

    ఒకవేళ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)లక్ష్యం_obj + o->స్థానభ్రంశం;

    ఒకవేళ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, బహిర్గతం_val);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
        ఒకవేళ (!*బహిర్గతం_val && !(శోధన_flags & AV_OPT_ALLOW_NULL)) {
            *బహిర్గతం_val = av_strdup("");
            ఒకవేళ (!*బహిర్గతం_val)
               తిరిగి AVERROR(ENOMEM);
        }
        తిరిగి 0;
    }

    buf[0] = 0;
    బహిర్గతం = buf;
    ret = opt_get_elem(o, &బహిర్గతం, పరిమాణం(buf), dst, శోధన_flags);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    ఒకవేళ (బహిర్గతం != buf) {
        *బహిర్గతం_val = బహిర్గతం;
        తిరిగి 0;
    }

    ఒకవేళ (ret >= పరిమాణం(buf))
        తిరిగి AVERROR(EINVAL);
    *బహిర్గతం_val = av_strdup(బహిర్గతం);
    తిరిగి *బహిర్గతం_val ? 0 : AVERROR(ENOMEM);
}

స్థిర పూర్ణాంకం get_సంఖ్య(శూన్య *obj, స్థిరరాశి అక్షరం *name, ద్విగుణ *అంకె, పూర్ణాంకం *den, int64_t *intnum,
                      పూర్ణాంకం శోధన_flags)
{
    శూన్య *dst, *లక్ష్యం_obj;
    స్థిరరాశి AVOption *o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        తిరిగి AVERROR(EINVAL);

    dst = ((uint8_t *)లక్ష్యం_obj) + o->స్థానభ్రంశం;

    తిరిగి read_సంఖ్య(o, dst, అంకె, den, intnum);
}

పూర్ణాంకం av_opt_get_int(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, int64_t *బహిర్గతం_val)
{
    int64_t intnum = 1;
    ద్విగుణ అంకె = 1;
    పూర్ణాంకం ret, den = 1;

    ఒకవేళ ((ret = get_సంఖ్య(obj, name, &అంకె, &den, &intnum, శోధన_flags)) < 0)
        తిరిగి ret;
    ఒకవేళ (అంకె == den)
        *బహిర్గతం_val = intnum;
    లేకపోతే
        *బహిర్గతం_val = అంకె * intnum / den;
    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_double(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, ద్విగుణ *బహిర్గతం_val)
{
    int64_t intnum = 1;
    ద్విగుణ అంకె = 1;
    పూర్ణాంకం ret, den = 1;

    ఒకవేళ ((ret = get_సంఖ్య(obj, name, &అంకె, &den, &intnum, శోధన_flags)) < 0)
        తిరిగి ret;
    *బహిర్గతం_val = అంకె * intnum / den;
    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_q(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, AVRational *బహిర్గతం_val)
{
    int64_t intnum = 1;
    ద్విగుణ అంకె = 1;
    పూర్ణాంకం ret, den = 1;

    ఒకవేళ ((ret = get_సంఖ్య(obj, name, &అంకె, &den, &intnum, శోధన_flags)) < 0)
        తిరిగి ret;

    ఒకవేళ (అంకె == 1.0 && (పూర్ణాంకం)intnum == intnum)
        *బహిర్గతం_val = (AVRational){intnum, den};
    లేకపోతే
        *బహిర్గతం_val = double_గమ్యం_rational(అంకె*intnum/den);
    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_image_కొలత(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, పూర్ణాంకం *w_బహిర్గతం, పూర్ణాంకం *h_బహిర్గతం)
{
    శూన్య *dst, *లక్ష్యం_obj;
    స్థిరరాశి AVOption *o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (o->type != AV_OPT_TYPE_IMAGE_కొలత) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        తిరిగి AVERROR(EINVAL);
    }

    dst = ((uint8_t*)లక్ష్యం_obj) + o->స్థానభ్రంశం;
    ఒకవేళ (w_బహిర్గతం) *w_బహిర్గతం = *(పూర్ణాంకం *)dst;
    ఒకవేళ (h_బహిర్గతం) *h_బహిర్గతం = *((పూర్ణాంకం *)dst+1);
    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_video_రేటు(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, AVRational *బహిర్గతం_val)
{
    తిరిగి av_opt_get_q(obj, name, శోధన_flags, బహిర్గతం_val);
}

స్థిర పూర్ణాంకం get_format(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, శూన్య *బహిర్గతం_fmt,
                      గణన AVOptionType type, స్థిరరాశి అక్షరం *desc)
{
    శూన్య *dst, *లక్ష్యం_obj;
    స్థిరరాశి AVOption *o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        తిరిగి AVERROR(EINVAL);
    }

    dst = ((uint8_t*)లక్ష్యం_obj) + o->స్థానభ్రంశం;
    ఒకవేళ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(గణన AVPixelFormat *)బహిర్గతం_fmt = *(గణన AVPixelFormat *)dst;
    లేకపోతే
        *(గణన AVSampleFormat*)బహిర్గతం_fmt = *(గణన AVSampleFormat*)dst;

    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_pixel_fmt(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, గణన AVPixelFormat *బహిర్గతం_fmt)
{
    తిరిగి get_format(obj, name, శోధన_flags, బహిర్గతం_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

పూర్ణాంకం av_opt_get_sample_fmt(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, గణన AVSampleFormat *బహిర్గతం_fmt)
{
    తిరిగి get_format(obj, name, శోధన_flags, బహిర్గతం_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

పూర్ణాంకం av_opt_get_chlayout(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, AVChannelLayout *cl)
{
    శూన్య *dst, *లక్ష్యం_obj;
    స్థిరరాశి AVOption *o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        తిరిగి AVERROR(EINVAL);
    }

    dst = ((uint8_t*)లక్ష్యం_obj) + o->స్థానభ్రంశం;
    తిరిగి av_channel_layout_copy(cl, dst);
}

పూర్ణాంకం av_opt_get_dict_val(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags, AVDictionary **బహిర్గతం_val)
{
    శూన్య *లక్ష్యం_obj;
    AVDictionary *src;
    స్థిరరాశి AVOption *o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);

    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (o->type != AV_OPT_TYPE_DICT)
        తిరిగి AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)లక్ష్యం_obj) + o->స్థానభ్రంశం);

    తిరిగి av_dict_copy(బహిర్గతం_val, src, 0);
}

పూర్ణాంకం av_opt_flag_is_సమితి(శూన్య *obj, స్థిరరాశి అక్షరం *క్షేత్రం_name, స్థిరరాశి అక్షరం *flag_name)
{
    స్థిరరాశి AVOption *క్షేత్రం = av_opt_కనుగొను(obj, క్షేత్రం_name, ఖాళీ, 0, 0);
    స్థిరరాశి AVOption *flag  = av_opt_కనుగొను(obj, flag_name,
                                        క్షేత్రం ? క్షేత్రం->unit : ఖాళీ, 0, 0);
    int64_t res;

    ఒకవేళ (!క్షేత్రం || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, క్షేత్రం_name, 0, &res) < 0)
        తిరిగి 0;
    తిరిగి res & flag->default_val.i64;
}

స్థిర శూన్య log_int_విలువ(శూన్య *av_log_obj, పూర్ణాంకం level, int64_t i)
{
    ఒకవేళ (i == గరిష్ఠ_పూర్ణాంకం) {
        av_log(av_log_obj, level, "INT_MAX");
    } లేకపోతే ఒకవేళ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } లేకపోతే ఒకవేళ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } లేకపోతే ఒకవేళ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } లేకపోతే ఒకవేళ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } లేకపోతే {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

స్థిర శూన్య log_విలువ(శూన్య *av_log_obj, పూర్ణాంకం level, ద్విగుణ d)
{
    ఒకవేళ      (d == గరిష్ఠ_పూర్ణాంకం) {
        av_log(av_log_obj, level, "INT_MAX");
    } లేకపోతే ఒకవేళ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } లేకపోతే ఒకవేళ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } లేకపోతే ఒకవేళ (d == (ద్విగుణ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } లేకపోతే ఒకవేళ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } లేకపోతే ఒకవేళ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } లేకపోతే ఒకవేళ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } లేకపోతే ఒకవేళ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } లేకపోతే ఒకవేళ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } లేకపోతే ఒకవేళ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } లేకపోతే ఒకవేళ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } లేకపోతే ఒకవేళ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } లేకపోతే ఒకవేళ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } లేకపోతే {
        av_log(av_log_obj, level, "%g", d);
    }
}

స్థిర స్థిరరాశి అక్షరం *get_opt_const_name(శూన్య *obj, స్థిరరాశి అక్షరం *unit, int64_t విలువ)
{
    స్థిరరాశి AVOption *opt = ఖాళీ;

    ఒకవేళ (!unit)
        తిరిగి ఖాళీ;
    అయితే ((opt = av_opt_తదుపరి(obj, opt)))
        ఒకవేళ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == విలువ)
            తిరిగి opt->name;
    తిరిగి ఖాళీ;
}

స్థిర అక్షరం *get_opt_flags_string(శూన్య *obj, స్థిరరాశి అక్షరం *unit, int64_t విలువ)
{
    స్థిరరాశి AVOption *opt = ఖాళీ;
    అక్షరం flags[512];

    flags[0] = 0;
    ఒకవేళ (!unit)
        తిరిగి ఖాళీ;
    అయితే ((opt = av_opt_తదుపరి(obj, opt))) {
        ఒకవేళ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & విలువ) {
            ఒకవేళ (flags[0])
                av_strlcatf(flags, పరిమాణం(flags), "+");
            av_strlcatf(flags, పరిమాణం(flags), "%s", opt->name);
        }
    }
    ఒకవేళ (flags[0])
        తిరిగి av_strdup(flags);
    తిరిగి ఖాళీ;
}

స్థిర శూన్య log_type(శూన్య *av_log_obj, స్థిరరాశి AVOption *o,
                     గణన AVOptionType మాతృ_type)
{
    స్థిరరాశి గణన AVOptionType type = TYPE_పునాది(o->type);

    ఒకవేళ (o->type == AV_OPT_TYPE_CONST && (TYPE_పునాది(మాతృ_type) == AV_OPT_TYPE_INT || TYPE_పునాది(మాతృ_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    లేకపోతే ఒకవేళ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ఒకవేళ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        లేకపోతే
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    లేకపోతే
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

స్థిర శూన్య log_default(శూన్య *obj, శూన్య *av_log_obj, స్థిరరాశి AVOption *opt)
{
    ఒకవేళ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ద్విమాన)
        తిరిగి;
    ఒకవేళ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_కొలత ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_రేటు) &&
        !opt->default_val.str)
        తిరిగి;

    ఒకవేళ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        స్థిరరాశి AVOptionArrayDef *arr = opt->default_val.arr;
        ఒకవేళ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        తిరిగి;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    ఎంపిక (opt->type) {
    స్థితి AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        ఆపు;
    స్థితి AV_OPT_TYPE_FLAGS: {
        అక్షరం *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ఒకవేళ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } లేకపోతే {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        ఆపు;
    }
    స్థితి AV_OPT_TYPE_DURATION: {
        అక్షరం buf[25];
        format_duration(buf, పరిమాణం(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        ఆపు;
    }
    స్థితి AV_OPT_TYPE_UINT:
    స్థితి AV_OPT_TYPE_INT:
    స్థితి AV_OPT_TYPE_UINT64:
    స్థితి AV_OPT_TYPE_INT64: {
        స్థిరరాశి అక్షరం *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        ఒకవేళ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        లేకపోతే
            log_int_విలువ(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        ఆపు;
    }
    స్థితి AV_OPT_TYPE_DOUBLE:
    స్థితి AV_OPT_TYPE_FLOAT:
        log_విలువ(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        ఆపు;
    స్థితి AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, గరిష్ఠ_పూర్ణాంకం);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.అంకె, q.den); }
        ఆపు;
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (అక్షరం *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        ఆపు;
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (అక్షరం *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        ఆపు;
    స్థితి AV_OPT_TYPE_COLOR:
    స్థితి AV_OPT_TYPE_IMAGE_కొలత:
    స్థితి AV_OPT_TYPE_STRING:
    స్థితి AV_OPT_TYPE_DICT:
    స్థితి AV_OPT_TYPE_VIDEO_రేటు:
    స్థితి AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        ఆపు;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

స్థిర శూన్య opt_list(శూన్య *obj, శూన్య *av_log_obj, స్థిరరాశి అక్షరం *unit,
                     పూర్ణాంకం req_flags, పూర్ణాంకం rej_flags, గణన AVOptionType మాతృ_type)
{
    స్థిరరాశి AVOption *opt = ఖాళీ;
    AVOptionRanges *r;
    పూర్ణాంకం i;

    అయితే ((opt = av_opt_తదుపరి(obj, opt))) {
        ఒకవేళ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            కొనసాగు;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ఒకవేళ (!unit && opt->type == AV_OPT_TYPE_CONST)
            కొనసాగు;
        లేకపోతే ఒకవేళ (unit && opt->type != AV_OPT_TYPE_CONST)
            కొనసాగు;
        లేకపోతే ఒకవేళ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            కొనసాగు;
        లేకపోతే ఒకవేళ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        లేకపోతే
            av_log(av_log_obj, AV_LOG_INFO, "  %s%-17s ",
                   (opt->flags & AV_OPT_FLAG_FILTERING_PARAM) ? " " : "-",
                   opt->name);

        log_type(av_log_obj, opt, మాతృ_type);

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

        ఒకవేళ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ఒకవేళ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_శోధన_FAKE_OBJ) >= 0) {
            ఎంపిక (opt->type) {
            స్థితి AV_OPT_TYPE_INT:
            స్థితి AV_OPT_TYPE_UINT:
            స్థితి AV_OPT_TYPE_INT64:
            స్థితి AV_OPT_TYPE_UINT64:
            స్థితి AV_OPT_TYPE_DOUBLE:
            స్థితి AV_OPT_TYPE_FLOAT:
            స్థితి AV_OPT_TYPE_RATIONAL:
                కొరకు (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_విలువ(av_log_obj, AV_LOG_INFO, r->range[i]->విలువ_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_విలువ(av_log_obj, AV_LOG_INFO, r->range[i]->విలువ_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                ఆపు;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        ఒకవేళ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

పూర్ణాంకం av_opt_show2(శూన్య *obj, శూన్య *av_log_obj, పూర్ణాంకం req_flags, పూర్ణాంకం rej_flags)
{
    ఒకవేళ (!obj)
        తిరిగి -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ఖాళీ, req_flags, rej_flags, -1);

    తిరిగి 0;
}

శూన్య av_opt_సమితి_defaults(శూన్య *s)
{
    av_opt_సమితి_defaults2(s, 0, 0);
}

శూన్య av_opt_సమితి_defaults2(శూన్య *s, పూర్ణాంకం ముసుగు_2, పూర్ణాంకం flags)
{
    స్థిరరాశి AVOption *opt = ఖాళీ;
    అయితే ((opt = av_opt_తదుపరి(s, opt))) {
        శూన్య *dst = ((uint8_t*)s) + opt->స్థానభ్రంశం;

        ఒకవేళ ((opt->flags & ముసుగు_2) != flags)
            కొనసాగు;

        ఒకవేళ (opt->flags & AV_OPT_FLAG_READONLY)
            కొనసాగు;

        ఒకవేళ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            స్థిరరాశి AVOptionArrayDef *arr = opt->default_val.arr;
            స్థిరరాశి అక్షరం              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ఒకవేళ (arr && arr->def)
                opt_సమితి_array(s, s, opt, arr->def, dst);

            కొనసాగు;
        }

        ఎంపిక (opt->type) {
            స్థితి AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                ఆపు;
            స్థితి AV_OPT_TYPE_BOOL:
            స్థితి AV_OPT_TYPE_FLAGS:
            స్థితి AV_OPT_TYPE_INT:
            స్థితి AV_OPT_TYPE_UINT:
            స్థితి AV_OPT_TYPE_INT64:
            స్థితి AV_OPT_TYPE_UINT64:
            స్థితి AV_OPT_TYPE_DURATION:
            స్థితి AV_OPT_TYPE_PIXEL_FMT:
            స్థితి AV_OPT_TYPE_SAMPLE_FMT:
                write_సంఖ్య(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                ఆపు;
            స్థితి AV_OPT_TYPE_DOUBLE:
            స్థితి AV_OPT_TYPE_FLOAT: {
                ద్విగుణ val;
                val = opt->default_val.dbl;
                write_సంఖ్య(s, opt, dst, val, 1, 1, 1);
            }
            ఆపు;
            స్థితి AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, గరిష్ఠ_పూర్ణాంకం);
                write_సంఖ్య(s, opt, dst, 1, val.den, val.అంకె, 1);
            }
            ఆపు;
            స్థితి AV_OPT_TYPE_COLOR:
                సమితి_string_color(s, opt, opt->default_val.str, dst);
                ఆపు;
            స్థితి AV_OPT_TYPE_STRING:
                సమితి_string(s, opt, opt->default_val.str, dst);
                ఆపు;
            స్థితి AV_OPT_TYPE_IMAGE_కొలత:
                సమితి_string_image_కొలత(s, opt, opt->default_val.str, dst);
                ఆపు;
            స్థితి AV_OPT_TYPE_VIDEO_రేటు:
                సమితి_string_video_రేటు(s, opt, opt->default_val.str, dst);
                ఆపు;
            స్థితి AV_OPT_TYPE_ద్విమాన:
                సమితి_string_ద్విమాన(s, opt, opt->default_val.str, dst);
                ఆపు;
            స్థితి AV_OPT_TYPE_CHLAYOUT:
                సమితి_string_channel_layout(s, opt, opt->default_val.str, dst);
                ఆపు;
            స్థితి AV_OPT_TYPE_DICT:
                సమితి_string_dict(s, opt, opt->default_val.str, dst);
                ఆపు;
        అప్రమేయ:
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
స్థిర పూర్ణాంకం parse_కీలకం_విలువ_pair(శూన్య *ctx, స్థిరరాశి అక్షరం **buf,
                                స్థిరరాశి అక్షరం *కీలకం_val_sep, స్థిరరాశి అక్షరం *జతలు_sep)
{
    అక్షరం *కీలకం = av_get_token(buf, కీలకం_val_sep);
    అక్షరం *val;
    పూర్ణాంకం ret;

    ఒకవేళ (!కీలకం)
        తిరిగి AVERROR(ENOMEM);

    ఒకవేళ (*కీలకం && strspn(*buf, కీలకం_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, జతలు_sep);
        ఒకవేళ (!val) {
            av_freep(&కీలకం);
            తిరిగి AVERROR(ENOMEM);
        }
    } లేకపోతే {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", కీలకం);
        av_free(కీలకం);
        తిరిగి AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", కీలకం, val);

    ret = av_opt_సమితి(ctx, కీలకం, val, AV_OPT_శోధన_CHILDREN);
    ఒకవేళ (ret == AVERROR_OPTION_NOT_దొరికింది)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", కీలకం);

    av_free(కీలకం);
    av_free(val);
    తిరిగి ret;
}

పూర్ణాంకం av_సమితి_options_string(శూన్య *ctx, స్థిరరాశి అక్షరం *opts,
                          స్థిరరాశి అక్షరం *కీలకం_val_sep, స్థిరరాశి అక్షరం *జతలు_sep)
{
    పూర్ణాంకం ret, లెక్క = 0;

    ఒకవేళ (!opts)
        తిరిగి 0;

    అయితే (*opts) {
        ఒకవేళ ((ret = parse_కీలకం_విలువ_pair(ctx, &opts, కీలకం_val_sep, జతలు_sep)) < 0)
            తిరిగి ret;
        లెక్క++;

        ఒకవేళ (*opts)
            opts++;
    }

    తిరిగి లెక్క;
}

#నిర్వచించు WHITESPACES " \n\t\r"

స్థిర పూర్ణాంకం is_కీలకం_char(అక్షరం c)
{
    తిరిగి (గుర్తులేని)((c | 32) - 'a') < 26 ||
           (గుర్తులేని)(c - '0') < 10 ||
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
స్థిర పూర్ణాంకం get_కీలకం(స్థిరరాశి అక్షరం **ropts, స్థిరరాశి అక్షరం *delim, అక్షరం **rkey)
{
    స్థిరరాశి అక్షరం *opts = *ropts;
    స్థిరరాశి అక్షరం *కీలకం_ప్రారంభం, *కీలకం_చివర;

    కీలకం_ప్రారంభం = opts += strspn(opts, WHITESPACES);
    అయితే (is_కీలకం_char(*opts))
        opts++;
    కీలకం_చివర = opts;
    opts += strspn(opts, WHITESPACES);
    ఒకవేళ (!*opts || !strchr(delim, *opts))
        తిరిగి AVERROR(EINVAL);
    opts++;
    ఒకవేళ (!(*rkey = av_malloc(కీలకం_చివర - కీలకం_ప్రారంభం + 1)))
        తిరిగి AVERROR(ENOMEM);
    జ్ఞాపకం_నకలు(*rkey, కీలకం_ప్రారంభం, కీలకం_చివర - కీలకం_ప్రారంభం);
    (*rkey)[కీలకం_చివర - కీలకం_ప్రారంభం] = 0;
    *ropts = opts;
    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_కీలకం_విలువ(స్థిరరాశి అక్షరం **ropts,
                         స్థిరరాశి అక్షరం *కీలకం_val_sep, స్థిరరాశి అక్షరం *జతలు_sep,
                         గుర్తులేని flags,
                         అక్షరం **rkey, అక్షరం **rval)
{
    పూర్ణాంకం ret;
    అక్షరం *కీలకం = ఖాళీ, *val;
    స్థిరరాశి అక్షరం *opts = *ropts;

    ఒకవేళ ((ret = get_కీలకం(&opts, కీలకం_val_sep, &కీలకం)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_కీలకం))
        తిరిగి AVERROR(EINVAL);
    ఒకవేళ (!(val = av_get_token(&opts, జతలు_sep))) {
        av_free(కీలకం);
        తిరిగి AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = కీలకం;
    *rval  = val;
    తిరిగి 0;
}

పూర్ణాంకం av_opt_సమితి_from_string(శూన్య *ctx, స్థిరరాశి అక్షరం *opts,
                           స్థిరరాశి అక్షరం *స్థిరరాశి *shorthand,
                           స్థిరరాశి అక్షరం *కీలకం_val_sep, స్థిరరాశి అక్షరం *జతలు_sep)
{
    పూర్ణాంకం ret, లెక్క = 0;
    స్థిరరాశి అక్షరం *dummy_shorthand = ఖాళీ;
    స్థిరరాశి అక్షరం *కీలకం;

    ఒకవేళ (!opts)
        తిరిగి 0;
    ఒకవేళ (!shorthand)
        shorthand = &dummy_shorthand;

    అయితే (*opts) {
        అక్షరం *parsed_కీలకం, *విలువ;
        ret = av_opt_get_కీలకం_విలువ(&opts, కీలకం_val_sep, జతలు_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_కీలకం : 0,
                                   &parsed_కీలకం, &విలువ);
        ఒకవేళ (ret < 0) {
            ఒకవేళ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            లేకపోతే
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            తిరిగి ret;
        }
        ఒకవేళ (*opts)
            opts++;
        ఒకవేళ (parsed_కీలకం) {
            కీలకం = parsed_కీలకం;
            అయితే (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } లేకపోతే {
            కీలకం = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", కీలకం, విలువ);
        ఒకవేళ ((ret = av_opt_సమితి(ctx, కీలకం, విలువ, 0)) < 0) {
            ఒకవేళ (ret == AVERROR_OPTION_NOT_దొరికింది)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", కీలకం);
            av_free(విలువ);
            av_free(parsed_కీలకం);
            తిరిగి ret;
        }

        av_free(విలువ);
        av_free(parsed_కీలకం);
        లెక్క++;
    }
    తిరిగి లెక్క;
}

శూన్య av_opt_free(శూన్య *obj)
{
    స్థిరరాశి AVOption *o = ఖాళీ;
    అయితే ((o = av_opt_తదుపరి(obj, o))) {
        శూన్య *pitem = (uint8_t *)obj + o->స్థానభ్రంశం;

        ఒకవేళ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        లేకపోతే
            opt_free_elem(o->type, pitem);
    }
}

పూర్ణాంకం av_opt_సమితి_dict2(శూన్య *obj, AVDictionary **options, పూర్ణాంకం శోధన_flags)
{
    స్థిరరాశి AVDictionary_నమోదు *t = ఖాళీ;
    AVDictionary    *tmp = ఖాళీ;
    పూర్ణాంకం ret;

    ఒకవేళ (!options)
        తిరిగి 0;

    అయితే ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_సమితి(obj, t->కీలకం, t->విలువ, శోధన_flags);
        ఒకవేళ (ret == AVERROR_OPTION_NOT_దొరికింది)
            ret = av_dict_సమితి(&tmp, t->కీలకం, t->విలువ, AV_DICT_MULTIKEY);
        ఒకవేళ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->కీలకం, t->విలువ);
            av_dict_free(&tmp);
            తిరిగి ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    తిరిగి 0;
}

పూర్ణాంకం av_opt_సమితి_dict(శూన్య *obj, AVDictionary **options)
{
    తిరిగి av_opt_సమితి_dict2(obj, options, 0);
}

స్థిరరాశి AVOption *av_opt_కనుగొను(శూన్య *obj, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *unit,
                            పూర్ణాంకం opt_flags, పూర్ణాంకం శోధన_flags)
{
    తిరిగి av_opt_find2(obj, name, unit, opt_flags, శోధన_flags, ఖాళీ);
}

స్థిరరాశి AVOption *av_opt_find2(శూన్య *obj, స్థిరరాశి అక్షరం *name, స్థిరరాశి అక్షరం *unit,
                             పూర్ణాంకం opt_flags, పూర్ణాంకం శోధన_flags, శూన్య **లక్ష్యం_obj)
{
    స్థిరరాశి AVClass  *c;
    స్థిరరాశి AVOption *o = ఖాళీ;

    ఒకవేళ(!obj)
        తిరిగి ఖాళీ;

    c= *(AVClass**)obj;

    ఒకవేళ (!c)
        తిరిగి ఖాళీ;

    ఒకవేళ (శోధన_flags & AV_OPT_శోధన_CHILDREN) {
        ఒకవేళ (శోధన_flags & AV_OPT_శోధన_FAKE_OBJ) {
            శూన్య *iter = ఖాళీ;
            స్థిరరాశి AVClass *బిడ్డ;
            అయితే (బిడ్డ = av_opt_బిడ్డ_class_iterate(c, &iter))
                ఒకవేళ (o = av_opt_find2(&బిడ్డ, name, unit, opt_flags, శోధన_flags, ఖాళీ))
                    తిరిగి o;
        } లేకపోతే {
            శూన్య *బిడ్డ = ఖాళీ;
            అయితే (బిడ్డ = av_opt_బిడ్డ_తదుపరి(obj, బిడ్డ))
                ఒకవేళ (o = av_opt_find2(బిడ్డ, name, unit, opt_flags, శోధన_flags, లక్ష్యం_obj))
                    తిరిగి o;
        }
    }

    అయితే (o = av_opt_తదుపరి(obj, o)) {
        ఒకవేళ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ఒకవేళ (లక్ష్యం_obj) {
                ఒకవేళ (!(శోధన_flags & AV_OPT_శోధన_FAKE_OBJ))
                    *లక్ష్యం_obj = obj;
                లేకపోతే
                    *లక్ష్యం_obj = ఖాళీ;
            }
            తిరిగి o;
        }
    }
    తిరిగి ఖాళీ;
}

శూన్య *av_opt_బిడ్డ_తదుపరి(శూన్య *obj, శూన్య *prev)
{
    స్థిరరాశి AVClass *c = *(AVClass **)obj;
    ఒకవేళ (c->బిడ్డ_తదుపరి)
        తిరిగి c->బిడ్డ_తదుపరి(obj, prev);
    తిరిగి ఖాళీ;
}

స్థిరరాశి AVClass *av_opt_బిడ్డ_class_iterate(స్థిరరాశి AVClass *మాతృ, శూన్య **iter)
{
    ఒకవేళ (మాతృ->బిడ్డ_class_iterate)
        తిరిగి మాతృ->బిడ్డ_class_iterate(iter);
    తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం opt_copy_elem(శూన్య *logctx, గణన AVOptionType type,
                         శూన్య *dst, స్థిరరాశి శూన్య *src)
{
    ఒకవేళ (type == AV_OPT_TYPE_STRING) {
        స్థిరరాశి అక్షరం *src_str = *(స్థిరరాశి అక్షరం *స్థిరరాశి *)src;
        అక్షరం         **dstp =  (అక్షరం **)dst;
        ఒకవేళ (*dstp != src_str)
            av_freep(dstp);
        ఒకవేళ (src_str) {
            *dstp = av_strdup(src_str);
            ఒకవేళ (!*dstp)
                తిరిగి AVERROR(ENOMEM);
        }
    } లేకపోతే ఒకవేళ (type == AV_OPT_TYPE_ద్విమాన) {
        స్థిరరాశి uint8_t *స్థిరరాశి *src8 = (స్థిరరాశి uint8_t *స్థిరరాశి *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        పూర్ణాంకం len = *(స్థిరరాశి పూర్ణాంకం *)(src8 + 1);
        ఒకవేళ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ఒకవేళ (len && !*dst8) {
            *(పూర్ణాంకం *)(dst8 + 1) = 0;
            తిరిగి AVERROR(ENOMEM);
        }
        *(పూర్ణాంకం *)(dst8 + 1) = len;
    } లేకపోతే ఒకవేళ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } లేకపోతే ఒకవేళ (type == AV_OPT_TYPE_DICT) {
        స్థిరరాశి AVDictionary *sdict = *(స్థిరరాశి AVDictionary * స్థిరరాశి *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ఒకవేళ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ఖాళీ;
        తిరిగి av_dict_copy(ddictp, sdict, 0);
    } లేకపోతే ఒకవేళ (type == AV_OPT_TYPE_CHLAYOUT) {
        స్థిరరాశి AVChannelLayout *slayout = (స్థిరరాశి AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ఒకవేళ (dlayout != slayout) {
            ఒకవేళ (dlayout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM &&
                slayout->క్రమం == AV_CHANNEL_క్రమం_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ఖాళీ;
            తిరిగి av_channel_layout_copy(dst, src);
        }
    } లేకపోతే ఒకవేళ (opt_is_pod(type)) {
        size_t కొలత = opt_type_desc[type].కొలత;
        జ్ఞాపకం_నకలు(dst, src, కొలత);
    } లేకపోతే {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        తిరిగి AVERROR(EINVAL);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం opt_copy_array(శూన్య *logctx, స్థిరరాశి AVOption *o,
                          శూన్య **pdst, స్థిరరాశి శూన్య * స్థిరరాశి *psrc)
{
    గుర్తులేని nb_elems = *opt_array_pcount(psrc);
    శూన్య         *dst = ఖాళీ;
    పూర్ణాంకం ret;

    ఒకవేళ (*pdst == *psrc) {
        *pdst                   = ఖాళీ;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_పునాది(o->type)].కొలత);
    ఒకవేళ (!dst)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (గుర్తులేని i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_పునాది(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(శూన్య**)psrc, i));
        ఒకవేళ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            తిరిగి ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    తిరిగి 0;
}

పూర్ణాంకం av_opt_copy(శూన్య *dst, స్థిరరాశి శూన్య *src)
{
    స్థిరరాశి AVOption *o = ఖాళీ;
    స్థిరరాశి AVClass *c;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (!src)
        తిరిగి AVERROR(EINVAL);

    c = *(AVClass **)src;
    ఒకవేళ (!c || c != *(AVClass **)dst)
        తిరిగి AVERROR(EINVAL);

    అయితే ((o = av_opt_తదుపరి(src, o))) {
        శూన్య *క్షేత్రం_dst = (uint8_t *)dst + o->స్థానభ్రంశం;
        శూన్య *క్షేత్రం_src = (uint8_t *)src + o->స్థానభ్రంశం;

        పూర్ణాంకం err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       క్షేత్రం_dst, క్షేత్రం_src) :
                  opt_copy_elem (dst, o->type, క్షేత్రం_dst, క్షేత్రం_src);
        ఒకవేళ (err < 0)
            ret = err;
    }
    తిరిగి ret;
}

పూర్ణాంకం av_opt_get_array_కొలత(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags,
                          గుర్తులేని పూర్ణాంకం *బహిర్గతం_val)
{
    శూన్య *లక్ష్యం_obj, *parray;
    స్థిరరాశి AVOption *o;

    o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        తిరిగి AVERROR(EINVAL);

    parray = (uint8_t *)లక్ష్యం_obj + o->స్థానభ్రంశం;
    *బహిర్గతం_val = *opt_array_pcount(parray);

    తిరిగి 0;
}

పూర్ణాంకం av_opt_get_array(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags,
                     గుర్తులేని పూర్ణాంకం ప్రారంభం_elem, గుర్తులేని పూర్ణాంకం nb_elems,
                     గణన AVOptionType బహిర్గతం_type, శూన్య *బహిర్గతం_val)
{
    స్థిరరాశి size_t elem_కొలత_బహిర్గతం = opt_type_desc[TYPE_పునాది(బహిర్గతం_type)].కొలత;

    స్థిరరాశి AVOption *o;
    శూన్య *లక్ష్యం_obj;

    స్థిరరాశి శూన్య *parray;
    గుర్తులేని array_కొలత;

    పూర్ణాంకం ret;

    o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం_obj);
    ఒకవేళ (!o || !లక్ష్యం_obj)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    ఒకవేళ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (బహిర్గతం_type & AV_OPT_TYPE_FLAG_ARRAY))
        తిరిగి AVERROR(EINVAL);

    parray     = (uint8_t *)లక్ష్యం_obj + o->స్థానభ్రంశం;
    array_కొలత = *opt_array_pcount(parray);

    ఒకవేళ (ప్రారంభం_elem >= array_కొలత ||
        array_కొలత - ప్రారంభం_elem < nb_elems)
        తిరిగి AVERROR(EINVAL);

    కొరకు (గుర్తులేని i = 0; i < nb_elems; i++) {
        స్థిరరాశి శూన్య *src = opt_array_pelem(o, *(శూన్య**)parray, ప్రారంభం_elem + i);
        శూన్య       *dst = (uint8_t*)బహిర్గతం_val + i * elem_కొలత_బహిర్గతం;

        ఒకవేళ (బహిర్గతం_type == TYPE_పునాది(o->type)) {
            ret = opt_copy_elem(obj, బహిర్గతం_type, dst, src);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;
        } లేకపోతే ఒకవేళ (బహిర్గతం_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *బహిర్గతం = buf;

            ret = opt_get_elem(o, &బహిర్గతం, పరిమాణం(buf), src, శోధన_flags);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;

            ఒకవేళ (బహిర్గతం == buf) {
                బహిర్గతం = av_strdup(buf);
                ఒకవేళ (!బహిర్గతం) {
                    ret = AVERROR(ENOMEM);
                    వెళ్ళు fail;
                }
            }

            *(uint8_t**)dst = బహిర్గతం;
        } లేకపోతే ఒకవేళ (బహిర్గతం_type == AV_OPT_TYPE_INT64    ||
                   బహిర్గతం_type == AV_OPT_TYPE_DOUBLE   ||
                   బహిర్గతం_type == AV_OPT_TYPE_RATIONAL) {
            ద్విగుణ     అంకె = 1.0;
            పూర్ణాంకం        den = 1;
            int64_t intnum = 1;

            ret = read_సంఖ్య(o, src, &అంకె, &den, &intnum);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;

            ఎంపిక (బహిర్గతం_type) {
            స్థితి AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (అంకె == den) ?  intnum : అంకె * intnum / den;
                ఆపు;
            స్థితి AV_OPT_TYPE_DOUBLE:
                *(ద్విగుణ*)dst = అంకె * intnum / den;
                ఆపు;
            స్థితి AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (అంకె == 1.0 && (పూర్ణాంకం)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_గమ్యం_rational(అంకె * intnum / den);
                ఆపు;
            అప్రమేయ: av_assert0(0);
            }
        } లేకపోతే
            తిరిగి AVERROR(ENOSYS);
    }

    తిరిగి 0;
fail:
    కొరకు (గుర్తులేని i = 0; i < nb_elems; i++)
        opt_free_elem(బహిర్గతం_type, (uint8_t*)బహిర్గతం_val + i * elem_కొలత_బహిర్గతం);
    తిరిగి ret;
}

పూర్ణాంకం av_opt_సమితి_array(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags,
                     గుర్తులేని పూర్ణాంకం ప్రారంభం_elem, గుర్తులేని పూర్ణాంకం nb_elems,
                     గణన AVOptionType val_type, స్థిరరాశి శూన్య *val)
{
    స్థిరరాశి size_t elem_కొలత_val = opt_type_desc[TYPE_పునాది(val_type)].కొలత;

    స్థిరరాశి AVOption *o;
    స్థిరరాశి AVOptionArrayDef *arr;
    శూన్య *లక్ష్యం_obj;

    శూన్య *parray;
    శూన్య *new_elems;
    గుర్తులేని *array_కొలత, new_కొలత;
    size_t elem_కొలత;

    పూర్ణాంకం ret = 0;

    ret = opt_సమితి_init(obj, name, శోధన_flags, 0, &లక్ష్యం_obj, &o, &parray);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        తిరిగి AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_కొలత = opt_array_pcount(parray);
    elem_కొలత  = opt_type_desc[TYPE_పునాది(o->type)].కొలత;

    ఒకవేళ (ప్రారంభం_elem > *array_కొలత)
        తిరిగి AVERROR(EINVAL);

    // compute new array size
    ఒకవేళ (!val) {
        ఒకవేళ (*array_కొలత - ప్రారంభం_elem < nb_elems)
            తిరిగి AVERROR(EINVAL);

        new_కొలత = *array_కొలత - nb_elems;
    } లేకపోతే ఒకవేళ (శోధన_flags & AV_OPT_ARRAY_REPLACE) {
        ఒకవేళ (ప్రారంభం_elem >= UINT_MAX - nb_elems)
            తిరిగి AVERROR(EINVAL);

        new_కొలత = FFMAX(*array_కొలత, ప్రారంభం_elem + nb_elems);
    } లేకపోతే {
        ఒకవేళ (nb_elems >= UINT_MAX - *array_కొలత)
            తిరిగి AVERROR(EINVAL);

        new_కొలత = *array_కొలత + nb_elems;
    }

    ఒకవేళ (arr &&
        ((arr->కొలత_max && new_కొలత > arr->కొలత_max) ||
         (arr->కొలత_min && new_కొలత < arr->కొలత_min)))
        తిరిగి AVERROR(EINVAL);

    // desired operation is shrinking the array
    ఒకవేళ (!val) {
        శూన్య *array = *(శూన్య**)parray;

        కొరకు (గుర్తులేని i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, ప్రారంభం_elem + i));
        }

        ఒకవేళ (new_కొలత > 0) {
            memmove(opt_array_pelem(o, array, ప్రారంభం_elem),
                    opt_array_pelem(o, array, ప్రారంభం_elem + nb_elems),
                    elem_కొలత * (*array_కొలత - ప్రారంభం_elem - nb_elems));

            array = av_realloc_array(array, new_కొలత, elem_కొలత);
            ఒకవేళ (!array)
                తిరిగి AVERROR(ENOMEM);

            *(శూన్య**)parray = array;
        } లేకపోతే
            av_freep(parray);

        *array_కొలత = new_కొలత;

        తిరిగి 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_కొలత);
    ఒకవేళ (!new_elems)
        తిరిగి AVERROR(ENOMEM);

    // convert/validate each new element
    కొరకు (గుర్తులేని i = 0; i < nb_elems; i++) {
        శూన్య       *dst = opt_array_pelem(o, new_elems, i);
        స్థిరరాశి శూన్య *src = (uint8_t*)val + i * elem_కొలత_val;

        ద్విగుణ     అంకె = 1.0;
        పూర్ణాంకం        den = 1;
        int64_t intnum = 1;

        ఒకవేళ (val_type == TYPE_పునాది(o->type)) {
            పూర్ణాంకం err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;

            // validate the range for numeric options
            err = read_సంఖ్య(o, dst, &అంకె, &den, &intnum);
            ఒకవేళ (err >= 0 && TYPE_పునాది(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < అంకె * intnum || o->min * den > అంకె * intnum)) {
                అంకె = den ? అంకె * intnum / den : (అంకె && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       ప్రారంభం_elem + i, o->name, అంకె, o->min, o->max);
                ret = AVERROR(ERANGE);
                వెళ్ళు fail;
            }
        } లేకపోతే ఒకవేళ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_సమితి_elem(obj, లక్ష్యం_obj, o, *(స్థిరరాశి అక్షరం **)src, dst);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;
        } లేకపోతే ఒకవేళ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            ఎంపిక (val_type) {
            స్థితి AV_OPT_TYPE_INT:       intnum = *(పూర్ణాంకం*)src;                ఆపు;
            స్థితి AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            ఆపు;
            స్థితి AV_OPT_TYPE_FLOAT:     అంకె    = *(దశాంశం*)src;              ఆపు;
            స్థితి AV_OPT_TYPE_DOUBLE:    అంకె    = *(ద్విగుణ*)src;             ఆపు;
            స్థితి AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->అంకె;
                                        den    = ((AVRational*)src)->den;   ఆపు;
            అప్రమేయ: av_assert0(0);
            }

            ret = write_సంఖ్య(obj, o, dst, అంకె, den, intnum, 0);
            ఒకవేళ (ret < 0)
                వెళ్ళు fail;
        } లేకపోతే {
            ret = AVERROR(ENOSYS);
            వెళ్ళు fail;
        }
    }

    // commit new elements to the array
    ఒకవేళ (ప్రారంభం_elem == 0 && nb_elems == new_కొలత) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_కొలత);
        *(శూన్య**)parray = new_elems;
        *array_కొలత     = nb_elems;

        new_elems = ఖాళీ;
        nb_elems  = 0;
    } లేకపోతే {
        శూన్య *array = av_realloc_array(*(శూన్య**)parray, new_కొలత, elem_కొలత);
        ఒకవేళ (!array) {
            ret = AVERROR(ENOMEM);
            వెళ్ళు fail;
        }

        ఒకవేళ (శోధన_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            కొరకు (గుర్తులేని i = ప్రారంభం_elem; i < FFMIN(ప్రారంభం_elem + nb_elems, *array_కొలత); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } లేకపోతే {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, ప్రారంభం_elem + nb_elems),
                    opt_array_pelem(o, array, ప్రారంభం_elem),
                    elem_కొలత * (*array_కొలత - ప్రారంభం_elem));
        }

        జ్ఞాపకం_నకలు((uint8_t*)array + elem_కొలత * ప్రారంభం_elem, new_elems, elem_కొలత * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(శూన్య**)parray = array;
        *array_కొలత     = new_కొలత;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    తిరిగి ret;
}

పూర్ణాంకం av_opt_query_ranges(AVOptionRanges **ranges_arg, శూన్య *obj, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం flags)
{
    పూర్ణాంకం ret;
    స్థిరరాశి AVClass *c = *(AVClass**)obj;
    పూర్ణాంకం (*callback)(AVOptionRanges **, శూన్య *obj, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం flags) = c->query_ranges;

    ఒకవేళ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, కీలకం, flags);
    ఒకవేళ (ret >= 0) {
        ఒకవేళ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    తిరిగి ret;
}

పూర్ణాంకం av_opt_query_ranges_default(AVOptionRanges **ranges_arg, శూన్య *obj, స్థిరరాశి అక్షరం *కీలకం, పూర్ణాంకం flags)
{
    AVOptionRanges *ranges = av_mallocz(పరిమాణం(*ranges));
    AVOptionRange **range_array = av_mallocz(పరిమాణం(శూన్య*));
    AVOptionRange *range = av_mallocz(పరిమాణం(*range));
    స్థిరరాశి AVOption *క్షేత్రం = av_opt_కనుగొను(obj, కీలకం, ఖాళీ, 0, flags);
    పూర్ణాంకం ret;

    *ranges_arg = ఖాళీ;

    ఒకవేళ (!ranges || !range || !range_array || !క్షేత్రం) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->విలువ_min = క్షేత్రం->min;
    range->విలువ_max = క్షేత్రం->max;

    ఎంపిక (క్షేత్రం->type) {
    స్థితి AV_OPT_TYPE_BOOL:
    స్థితి AV_OPT_TYPE_INT:
    స్థితి AV_OPT_TYPE_UINT:
    స్థితి AV_OPT_TYPE_INT64:
    స్థితి AV_OPT_TYPE_UINT64:
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
    స్థితి AV_OPT_TYPE_FLOAT:
    స్థితి AV_OPT_TYPE_DOUBLE:
    స్థితి AV_OPT_TYPE_DURATION:
    స్థితి AV_OPT_TYPE_COLOR:
        ఆపు;
    స్థితి AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->విలువ_min = -1;
        range->విలువ_max = గరిష్ఠ_పూర్ణాంకం;
        ఆపు;
    స్థితి AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = గరిష్ఠ_పూర్ణాంకం;
        ఆపు;
    స్థితి AV_OPT_TYPE_IMAGE_కొలత:
        range->component_min = 0;
        range->component_max = గరిష్ఠ_పూర్ణాంకం/128/8;
        range->విలువ_min = 0;
        range->విలువ_max = గరిష్ఠ_పూర్ణాంకం/8;
        ఆపు;
    స్థితి AV_OPT_TYPE_VIDEO_రేటు:
        range->component_min = 1;
        range->component_max = గరిష్ఠ_పూర్ణాంకం;
        range->విలువ_min = 1;
        range->విలువ_max = గరిష్ఠ_పూర్ణాంకం;
        ఆపు;
    అప్రమేయ:
        ret = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }

    *ranges_arg = ranges;
    తిరిగి 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    తిరిగి ret;
}

శూన్య av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    పూర్ణాంకం i;
    AVOptionRanges *ranges = *rangesp;

    ఒకవేళ (!ranges)
        తిరిగి;

    కొరకు (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ఒకవేళ (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

పూర్ణాంకం av_opt_is_సమితి_గమ్యం_default(శూన్య *obj, స్థిరరాశి AVOption *o)
{
    int64_t i64;
    ద్విగుణ d;
    AVRational q;
    పూర్ణాంకం ret, w, h;
    అక్షరం *str;
    శూన్య *dst;

    ఒకవేళ (!o || !obj)
        తిరిగి AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->స్థానభ్రంశం;

    ఒకవేళ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        స్థిరరాశి అక్షరం *def = o->default_val.arr ? o->default_val.arr->def : ఖాళీ;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        ఒకవేళ (!!val != !!def)
            ret = 0;
        లేకపోతే ఒకవేళ (val)
            ret = !strcmp(val, def);
        లేకపోతే
            ret = 1;

        av_freep(&val);

        తిరిగి ret;
    }

    ఎంపిక (o->type) {
    స్థితి AV_OPT_TYPE_CONST:
        తిరిగి 1;
    స్థితి AV_OPT_TYPE_BOOL:
    స్థితి AV_OPT_TYPE_FLAGS:
    స్థితి AV_OPT_TYPE_PIXEL_FMT:
    స్థితి AV_OPT_TYPE_SAMPLE_FMT:
    స్థితి AV_OPT_TYPE_INT:
    స్థితి AV_OPT_TYPE_UINT:
    స్థితి AV_OPT_TYPE_DURATION:
    స్థితి AV_OPT_TYPE_INT64:
    స్థితి AV_OPT_TYPE_UINT64:
        read_సంఖ్య(o, dst, ఖాళీ, ఖాళీ, &i64);
        తిరిగి o->default_val.i64 == i64;
    స్థితి AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ఒకవేళ (o->default_val.str) {
            ఒకవేళ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                తిరిగి ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        తిరిగి ret;
    }
    స్థితి AV_OPT_TYPE_STRING:
        str = *(అక్షరం **)dst;
        ఒకవేళ (str == o->default_val.str) //2 NULLs
            తిరిగి 1;
        ఒకవేళ (!str || !o->default_val.str) //1 NULL
            తిరిగి 0;
        తిరిగి !strcmp(str, o->default_val.str);
    స్థితి AV_OPT_TYPE_DOUBLE:
        d = *(ద్విగుణ *)dst;
        తిరిగి o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    స్థితి AV_OPT_TYPE_FLOAT:
        d = *(దశాంశం *)dst;
        తిరిగి (దశాంశం)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    స్థితి AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, గరిష్ఠ_పూర్ణాంకం);
        తిరిగి !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    స్థితి AV_OPT_TYPE_ద్విమాన: {
        నిర్మాణం {
            uint8_t *దత్తాంశం;
            పూర్ణాంకం కొలత;
        } tmp = {0};
        పూర్ణాంకం opt_కొలత = *(పూర్ణాంకం *)((శూన్య **)dst + 1);
        శూన్య *opt_ptr = *(శూన్య **)dst;
        ఒకవేళ (!opt_కొలత && (!o->default_val.str || !అక్షరశ్రేణి_పొడవు(o->default_val.str)))
            తిరిగి 1;
        ఒకవేళ (!opt_కొలత ||  !o->default_val.str || !అక్షరశ్రేణి_పొడవు(o->default_val.str ))
            తిరిగి 0;
        ఒకవేళ (opt_కొలత != అక్షరశ్రేణి_పొడవు(o->default_val.str) / 2)
            తిరిగి 0;
        ret = సమితి_string_ద్విమాన(ఖాళీ, ఖాళీ, o->default_val.str, &tmp.దత్తాంశం);
        ఒకవేళ (!ret)
            ret = !memcmp(opt_ptr, tmp.దత్తాంశం, tmp.కొలత);
        av_free(tmp.దత్తాంశం);
        తిరిగి ret;
    }
    స్థితి AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ఖాళీ;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        స్థిరరాశి AVDictionary_నమోదు *en1 = ఖాళీ;
        స్థిరరాశి AVDictionary_నమోదు *en2 = ఖాళీ;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ఒకవేళ (ret < 0) {
            av_dict_free(&dict1);
            తిరిగి ret;
        }
        చేయి {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } అయితే (en1 && en2 && !strcmp(en1->కీలకం, en2->కీలకం) && !strcmp(en1->విలువ, en2->విలువ));
        av_dict_free(&dict1);
        తిరిగి (!en1 && !en2);
    }
    స్థితి AV_OPT_TYPE_IMAGE_కొలత:
        ఒకవేళ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        లేకపోతే ఒకవేళ ((ret = av_parse_video_కొలత(&w, &h, o->default_val.str)) < 0)
            తిరిగి ret;
        తిరిగి (w == *(పూర్ణాంకం *)dst) && (h == *((పూర్ణాంకం *)dst+1));
    స్థితి AV_OPT_TYPE_VIDEO_రేటు:
        q = (AVRational){0, 0};
        ఒకవేళ (o->default_val.str) {
            ఒకవేళ ((ret = av_parse_video_రేటు(&q, o->default_val.str)) < 0)
                తిరిగి ret;
        }
        తిరిగి !av_cmp_q(*(AVRational*)dst, q);
    స్థితి AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ఒకవేళ (o->default_val.str) {
            ఒకవేళ ((ret = av_parse_color(color, o->default_val.str, -1, ఖాళీ)) < 0)
                తిరిగి ret;
        }
        తిరిగి !memcmp(color, dst, పరిమాణం(color));
    }
    అప్రమేయ:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        ఆపు;
    }
    తిరిగి AVERROR_PATCHWELCOME;
}

పూర్ణాంకం av_opt_is_సమితి_గమ్యం_default_by_name(శూన్య *obj, స్థిరరాశి అక్షరం *name, పూర్ణాంకం శోధన_flags)
{
    స్థిరరాశి AVOption *o;
    శూన్య *లక్ష్యం;
    ఒకవేళ (!obj)
        తిరిగి AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ఖాళీ, 0, శోధన_flags, &లక్ష్యం);
    ఒకవేళ (!o)
        తిరిగి AVERROR_OPTION_NOT_దొరికింది;
    తిరిగి av_opt_is_సమితి_గమ్యం_default(లక్ష్యం, o);
}

స్థిర పూర్ణాంకం opt_serialize(శూన్య *obj, పూర్ణాంకం opt_flags, పూర్ణాంకం flags, పూర్ణాంకం *cnt,
                         AVBPrint *bprint, స్థిరరాశి అక్షరం కీలకం_val_sep, స్థిరరాశి అక్షరం జతలు_sep)
{
    స్థిరరాశి AVOption *o = ఖాళీ;
    శూన్య *బిడ్డ = ఖాళీ;
    uint8_t *buf;
    పూర్ణాంకం ret;
    స్థిరరాశి అక్షరం special_chars[] = {జతలు_sep, కీలకం_val_sep, '\0'};

    ఒకవేళ (flags & AV_OPT_SERIALIZE_శోధన_CHILDREN)
        అయితే (బిడ్డ = av_opt_బిడ్డ_తదుపరి(obj, బిడ్డ)) {
            ret = opt_serialize(బిడ్డ, opt_flags, flags, cnt, bprint,
                                కీలకం_val_sep, జతలు_sep);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        }

    అయితే (o = av_opt_తదుపరి(obj, o)) {
        ఒకవేళ (o->type == AV_OPT_TYPE_CONST)
            కొనసాగు;
        ఒకవేళ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ఒకవేళ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ఒకవేళ (o->flags == opt_flags)
                    కొనసాగు;
            } లేకపోతే ఒకవేళ ((o->flags & opt_flags) == opt_flags)
                కొనసాగు;
        } లేకపోతే {
            ఒకవేళ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                కొనసాగు;
            లేకపోతే ఒకవేళ (((o->flags & opt_flags) != opt_flags))
                కొనసాగు;
        }
        ఒకవేళ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_సమితి_గమ్యం_default(obj, o) > 0)
            కొనసాగు;
        ఒకవేళ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ఖాళీ);
            తిరిగి ret;
        }
        ఒకవేళ (buf) {
            ఒకవేళ ((*cnt)++)
                av_bprint_append_దత్తాంశం(bprint, &జతలు_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_బహుళకం_BACKSLASH, 0);
            av_bprint_append_దత్తాంశం(bprint, &కీలకం_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_బహుళకం_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    తిరిగి 0;
}

పూర్ణాంకం av_opt_serialize(శూన్య *obj, పూర్ణాంకం opt_flags, పూర్ణాంకం flags, అక్షరం **బఫరు,
                     స్థిరరాశి అక్షరం కీలకం_val_sep, స్థిరరాశి అక్షరం జతలు_sep)
{
    AVBPrint bprint;
    పూర్ణాంకం ret, cnt = 0;

    ఒకవేళ (జతలు_sep == '\0' || కీలకం_val_sep == '\0' || జతలు_sep == కీలకం_val_sep ||
        జతలు_sep == '\\' || కీలకం_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ (!obj || !బఫరు)
        తిరిగి AVERROR(EINVAL);

    *బఫరు = ఖాళీ;
    av_bprint_init(&bprint, 64, AV_BPRINT_కొలత_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        కీలకం_val_sep, జతలు_sep);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ret = av_bprint_finalize(&bprint, బఫరు);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
    తిరిగి 0;
}
