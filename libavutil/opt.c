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

#অন্তর্ভাব "avutil.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "channel_layout.h"
#অন্তর্ভাব "dict.h"
#অন্তর্ভাব "eval.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "parseutils.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "mathematics.h"
#অন্তর্ভাব "opt.h"
#অন্তর্ভাব "samplefmt.h"
#অন্তর্ভাব "bprint.h"

#অন্তর্ভাব <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ধ্রুব AVOption *av_opt_next(ধ্রুব শূন্য *obj, ধ্রুব AVOption *last)
{
    ধ্রুব AVClass *class;
    যদি (!obj)
        প্রত্যাগম রিক্ত;
    class = *(ধ্রুব AVClass**)obj;
    যদি (!last && class && class->option && class->option[0].name)
        প্রত্যাগম class->option;
    যদি (last && last[1].name)
        প্রত্যাগম ++last;
    প্রত্যাগম রিক্ত;
}

স্থির ধ্রুব সংরচনা {
    size_t      size;
    ধ্রুব বর্ণ *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { পরিমাণ(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { পরিমাণ(পূর্ণাঙ্ক),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { পরিমাণ(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { পরিমাণ(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { পরিমাণ(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { পরিমাণ(দ্বিগুণ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { পরিমাণ(ভিন্ন),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { পরিমাণ(বর্ণ *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { পরিমাণ(AVRational),     "<rational>" },
    [AV_OPT_TYPE_দ্বিমিক]        = { পরিমাণ(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { পরিমাণ(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { পরিমাণ(পূর্ণাঙ্ক[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { পরিমাণ(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { পরিমাণ(গণনা AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { পরিমাণ(গণনা AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { পরিমাণ(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { পরিমাণ(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { পরিমাণ(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { পরিমাণ(পূর্ণাঙ্ক),            "<boolean>" },
};

// option is plain old data
স্থির পূর্ণাঙ্ক opt_is_pod(গণনা AVOptionType type)
{
    বিকল্প (type) {
    পক্ষ AV_OPT_TYPE_FLAGS:
    পক্ষ AV_OPT_TYPE_INT:
    পক্ষ AV_OPT_TYPE_INT64:
    পক্ষ AV_OPT_TYPE_DOUBLE:
    পক্ষ AV_OPT_TYPE_FLOAT:
    পক্ষ AV_OPT_TYPE_RATIONAL:
    পক্ষ AV_OPT_TYPE_UINT64:
    পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
    পক্ষ AV_OPT_TYPE_VIDEO_RATE:
    পক্ষ AV_OPT_TYPE_DURATION:
    পক্ষ AV_OPT_TYPE_COLOR:
    পক্ষ AV_OPT_TYPE_BOOL:
    পক্ষ AV_OPT_TYPE_UINT:
        প্রত্যাগম 1;
    }
    প্রত্যাগম 0;
}

স্থির uint8_t opt_array_sep(ধ্রুব AVOption *o)
{
    ধ্রুব AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    প্রত্যাগম (d && d->sep) ? d->sep : ',';
}

স্থির শূন্য *opt_array_pelem(ধ্রুব AVOption *o, শূন্য *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    প্রত্যাগম (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

স্থির unsigned *opt_array_pcount(ধ্রুব শূন্য *parray)
{
    প্রত্যাগম (unsigned *)((ধ্রুব শূন্য * ধ্রুব *)parray + 1);
}

স্থির শূন্য opt_free_elem(গণনা AVOptionType type, শূন্য *ptr)
{
    বিকল্প (TYPE_BASE(type)) {
    পক্ষ AV_OPT_TYPE_STRING:
    পক্ষ AV_OPT_TYPE_দ্বিমিক:
        av_freep(ptr);
        ভঙ্গ;

    পক্ষ AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        ভঙ্গ;

    পক্ষ AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        ভঙ্গ;

    স্বভাব:
        ভঙ্গ;
    }
}

স্থির শূন্য opt_free_array(ধ্রুব AVOption *o, শূন্য *parray, unsigned *গুনতি)
{
    প্রতি (unsigned i = 0; i < *গুনতি; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(শূন্য **)parray, i));

    av_freep(parray);
    *গুনতি = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
স্থির পূর্ণাঙ্ক opt_set_init(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags,
                        পূর্ণাঙ্ক require_type,
                        শূন্য **ptgt, ধ্রুব AVOption **po, শূন্য **pdst)
{
    শূন্য *logctx;
    ধ্রুব AVOption *o;
    শূন্য *tgt;

    o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &tgt);
    যদি (!o || (!tgt && !(অনুসন্ধান_flags & AV_OPT_অনুসন্ধান_FAKE_OBJ)))
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;

    যদি (o->flags & AV_OPT_FLAG_READONLY)
        প্রত্যাগম AVERROR(EINVAL);

    logctx = tgt ? obj : রিক্ত;

    যদি (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        প্রত্যাগম AVERROR(EINVAL);
    }

    যদি (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = রিক্ত;
        ধ্রুব AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ধ্রুব AVClass**)tgt;
        যদি (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        যদি (!state_flags && obj != tgt) {
            class = *(ধ্রুব AVClass**)obj;
            যদি (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        যদি (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            প্রত্যাগম AVERROR(EINVAL);
        }
    }

    যদি (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    যদি (po)
        *po   = o;
    যদি (ptgt)
        *ptgt = tgt;
    যদি (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : রিক্ত;

    প্রত্যাগম 0;
}

স্থির AVRational double_to_rational(দ্বিগুণ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     যদি ((!r.অঙ্ক || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     প্রত্যাগম r;
}

স্থির পূর্ণাঙ্ক read_সংখ্যা(ধ্রুব AVOption *o, ধ্রুব শূন্য *dst, দ্বিগুণ *অঙ্ক, পূর্ণাঙ্ক *den, int64_t *intnum)
{
    বিকল্প (TYPE_BASE(o->type)) {
    পক্ষ AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned পূর্ণাঙ্ক*)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(গণনা AVPixelFormat *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(গণনা AVSampleFormat *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_BOOL:
    পক্ষ AV_OPT_TYPE_INT:
        *intnum = *(পূর্ণাঙ্ক *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_UINT:
        *intnum = *(unsigned পূর্ণাঙ্ক *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_DURATION:
    পক্ষ AV_OPT_TYPE_INT64:
    পক্ষ AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_FLOAT:
        *অঙ্ক = *(ভিন্ন *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_DOUBLE:
        *অঙ্ক = *(দ্বিগুণ *)dst;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->অঙ্ক;
        *den    = ((AVRational *)dst)->den;
        প্রত্যাগম 0;
    পক্ষ AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        প্রত্যাগম 0;
    }
    প্রত্যাগম AVERROR(EINVAL);
}

স্থির পূর্ণাঙ্ক write_সংখ্যা(শূন্য *obj, ধ্রুব AVOption *o, শূন্য *dst,
                        দ্বিগুণ অঙ্ক, পূর্ণাঙ্ক den, int64_t intnum,
                        পূর্ণাঙ্ক ignore_range)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    ধ্রুব গণনা AVOptionType type = TYPE_BASE(o->type);

    যদি (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < অঙ্ক * intnum || o->min * den > অঙ্ক * intnum)) {
        অঙ্ক = den ? অঙ্ক * intnum / den : (অঙ্ক && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               অঙ্ক, o->name, o->min, o->max);
        প্রত্যাগম AVERROR(ERANGE);
    }
    যদি (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        দ্বিগুণ d = অঙ্ক*intnum/den;
        যদি (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   অঙ্ক*intnum/den, o->name);
            প্রত্যাগম AVERROR(ERANGE);
        }
    }

    যদি (!dst)
        প্রত্যাগম 0;

    বিকল্প (type) {
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
        *(গণনা AVPixelFormat *)dst = llrint(অঙ্ক / den) * intnum;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
        *(গণনা AVSampleFormat *)dst = llrint(অঙ্ক / den) * intnum;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_BOOL:
    পক্ষ AV_OPT_TYPE_FLAGS:
    পক্ষ AV_OPT_TYPE_INT:
    পক্ষ AV_OPT_TYPE_UINT:
        *(পূর্ণাঙ্ক *)dst = llrint(অঙ্ক / den) * intnum;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_DURATION:
    পক্ষ AV_OPT_TYPE_INT64:{
        দ্বিগুণ d = অঙ্ক / den;
        যদি (intnum == 1 && d == (দ্বিগুণ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } অন্যথা
            *(int64_t *)dst = llrint(d) * intnum;
        ভঙ্গ;}
    পক্ষ AV_OPT_TYPE_UINT64:{
        দ্বিগুণ d = অঙ্ক / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        যদি (intnum == 1 && d == (দ্বিগুণ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } অন্যথা যদি (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } অন্যথা {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        ভঙ্গ;}
    পক্ষ AV_OPT_TYPE_FLOAT:
        *(ভিন্ন *)dst = অঙ্ক * intnum / den;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_DOUBLE:
        *(দ্বিগুণ    *)dst = অঙ্ক * intnum / den;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_RATIONAL:
    পক্ষ AV_OPT_TYPE_VIDEO_RATE:
        যদি ((পূর্ণাঙ্ক) অঙ্ক == অঙ্ক)
            *(AVRational *)dst = (AVRational) { অঙ্ক *intnum, den };
        অন্যথা
            *(AVRational *)dst = double_to_rational(অঙ্ক * intnum / den);
        ভঙ্গ;
    স্বভাব:
        প্রত্যাগম AVERROR(EINVAL);
    }
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক hexchar2int(বর্ণ c) {
    যদি (c >= '0' && c <= '9')
        প্রত্যাগম c - '0';
    যদি (c >= 'a' && c <= 'f')
        প্রত্যাগম c - 'a' + 10;
    যদি (c >= 'A' && c <= 'F')
        প্রত্যাগম c - 'A' + 10;
    প্রত্যাগম -1;
}

স্থির পূর্ণাঙ্ক set_string_দ্বিমিক(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t **dst)
{
    পূর্ণাঙ্ক *lendst;
    uint8_t *bin, *ptr;
    পূর্ণাঙ্ক len;

    যদি (dst) {
        lendst = (পূর্ণাঙ্ক *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    যদি (!val || !(len = strlen(val)))
        প্রত্যাগম 0;

    যদি (len & 1)
        প্রত্যাগম AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    যদি (!ptr)
        প্রত্যাগম AVERROR(ENOMEM);
    যাবত্ (*val) {
        পূর্ণাঙ্ক a = hexchar2int(*val++);
        পূর্ণাঙ্ক b = hexchar2int(*val++);
        যদি (a < 0 || b < 0) {
            av_free(bin);
            প্রত্যাগম AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    যদি (dst) {
        *dst    = bin;
        *lendst = len;
    } অন্যথা {
        av_free(bin);
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক set_string(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t **dst)
{
    যদি (!dst)
        প্রত্যাগম 0;
    av_freep(dst);
    যদি (!val)
        প্রত্যাগম 0;
    *dst = av_strdup(val);
    প্রত্যাগম *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

স্থির পূর্ণাঙ্ক set_string_সংখ্যা(শূন্য *obj, শূন্য *target_obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, শূন্য *dst)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    ধ্রুব গণনা AVOptionType type = TYPE_BASE(o->type);
    পূর্ণাঙ্ক ret = 0;

    যদি (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        পূর্ণাঙ্ক অঙ্ক, den;
        বর্ণ c;
        যদি (sscanf(val, "%d%*1[:/]%d%c", &অঙ্ক, &den, &c) == 2) {
            যদি ((ret = write_সংখ্যা(obj, o, dst, 1, den, অঙ্ক, 0)) >= 0)
                প্রত্যাগম ret;
            ret = 0;
        }
    }

    প্রতি (;;) {
        পূর্ণাঙ্ক i = 0;
        বর্ণ buf[256];
        পূর্ণাঙ্ক cmd = 0;
        দ্বিগুণ d;
        int64_t intnum = 1;

        যদি (type == AV_OPT_TYPE_FLAGS) {
            যদি (*val == '+' || *val == '-')
                cmd = *(val++);
            প্রতি (; i < পরিমাণ(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            পূর্ণাঙ্ক res;
            পূর্ণাঙ্ক ci = 0;
            দ্বিগুণ const_মানসমূহ[64];
            ধ্রুব বর্ণ * const_names[64];
            পূর্ণাঙ্ক অনুসন্ধান_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_অনুসন্ধান_CHILDREN : 0;
            ধ্রুব AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, অনুসন্ধান_flags);
            যদি (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                যদি (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } অন্যথা {
                যদি (o->unit) {
                    প্রতি (o_named = রিক্ত; o_named = av_opt_next(target_obj, o_named); ) {
                        যদি (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            যদি (ci + 6 >= FF_ARRAY_ELEMS(const_মানসমূহ)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                প্রত্যাগম AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_মানসমূহ[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_মানসমূহ[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_মানসমূহ[ci++] = o->max;
                const_names [ci  ] = "min";
                const_মানসমূহ[ci++] = o->min;
                const_names [ci  ] = "none";
                const_মানসমূহ[ci++] = 0;
                const_names [ci  ] = "all";
                const_মানসমূহ[ci++] = ~0;
                const_names [ci] = রিক্ত;
                const_মানসমূহ[ci] = 0;

                res = av_রাশিমালা_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_মানসমূহ, রিক্ত, রিক্ত, রিক্ত, রিক্ত, রিক্ত, 0, obj);
                যদি (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    প্রত্যাগম res;
                }
            }
        }
        যদি (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned পূর্ণাঙ্ক*)dst;
            যদি (cmd == '+')
                d = intnum | (int64_t)d;
            অন্যথা যদি (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        যদি ((ret = write_সংখ্যা(obj, o, dst, d, 1, 1, 0)) < 0)
            প্রত্যাগম ret;
        val += i;
        যদি (!i || !*val)
            প্রত্যাগম 0;
    }
}

স্থির পূর্ণাঙ্ক set_string_image_size(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, পূর্ণাঙ্ক *dst)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    পূর্ণাঙ্ক tmp[2];
    পূর্ণাঙ্ক ret;

    যদি (!val || !strcmp(val, "none")) {
        যদি (dst) {
        dst[0] =
        dst[1] = 0;
        }
        প্রত্যাগম 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    যদি (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        প্রত্যাগম ret;
    }
    যদি (dst)
        memcpy(dst, tmp, পরিমাণ(tmp));
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক set_string_video_rate(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, AVRational *dst)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    AVRational tmp;
    পূর্ণাঙ্ক ret = av_parse_video_rate(&tmp, val);
    যদি (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    যদি (dst)
        *dst = tmp;
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক set_string_color(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t *dst)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    পূর্ণাঙ্ক ret;

    যদি (!val) {
        প্রত্যাগম 0;
    } অন্যথা {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        যদি (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            প্রত্যাগম ret;
        }
        যদি (dst)
            memcpy(dst, tmp, পরিমাণ(tmp));
        প্রত্যাগম ret;
    }
    প্রত্যাগম 0;
}

স্থির ধ্রুব বর্ণ *get_bool_name(পূর্ণাঙ্ক val)
{
    যদি (val < 0)
        প্রত্যাগম "auto";
    প্রত্যাগম val ? "true" : "false";
}

স্থির পূর্ণাঙ্ক set_string_bool(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, পূর্ণাঙ্ক *dst)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    পূর্ণাঙ্ক n;

    যদি (!val)
        প্রত্যাগম 0;

    যদি (!strcmp(val, "auto")) {
        n = -1;
    } অন্যথা যদি (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } অন্যথা যদি (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } অন্যথা {
        বর্ণ *end = রিক্ত;
        n = strtol(val, &end, 10);
        যদি (val + strlen(val) != end)
            গচ্ছ fail;
    }

    যদি (n < o->min || n > o->max)
        গচ্ছ fail;

    যদি (dst)
    *dst = n;
    প্রত্যাগম 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    প্রত্যাগম AVERROR(EINVAL);
}

স্থির পূর্ণাঙ্ক set_string_fmt(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t *dst,
                          পূর্ণাঙ্ক fmt_nb, পূর্ণাঙ্ক ((*get_fmt)(ধ্রুব বর্ণ *)), ধ্রুব বর্ণ *desc,
                          গণনা AVOptionType type)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    পূর্ণাঙ্ক fmt, min, max;

    যদি (!val || !strcmp(val, "none")) {
        fmt = -1;
    } অন্যথা {
        fmt = get_fmt(val);
        যদি (fmt == -1) {
            বর্ণ *tail;
            fmt = strtol(val, &tail, 0);
            যদি (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                প্রত্যাগম AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    যদি(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    যদি (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        প্রত্যাগম AVERROR(ERANGE);
    }

    যদি (dst)
    বিকল্প (type) {
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:  *(গণনা AVPixelFormat *)dst = fmt; ভঙ্গ;
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT: *(গণনা AVSampleFormat*)dst = fmt; ভঙ্গ;
    স্বভাব: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক get_pix_fmt(ধ্রুব বর্ণ *name)
{
    প্রত্যাগম av_get_pix_fmt(name);
}

স্থির পূর্ণাঙ্ক set_string_pixel_fmt(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t *dst)
{
    প্রত্যাগম set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

স্থির পূর্ণাঙ্ক get_sample_fmt(ধ্রুব বর্ণ *name)
{
    প্রত্যাগম av_get_sample_fmt(name);
}

স্থির পূর্ণাঙ্ক set_string_sample_fmt(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t *dst)
{
    প্রত্যাগম set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

স্থির পূর্ণাঙ্ক set_string_dict(শূন্য *obj, ধ্রুব AVOption *o, ধ্রুব বর্ণ *val, uint8_t **dst)
{
    AVDictionary *options = রিক্ত;

    যদি (val) {
        পূর্ণাঙ্ক ret = av_dict_parse_string(&options, val, "=", ":", 0);
        যদি (ret < 0) {
            av_dict_free(&options);
            প্রত্যাগম ret;
        }
    }

    যদি (!dst) {
        av_dict_free(&options);
        প্রত্যাগম 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক set_string_channel_layout(শূন্য *obj, ধ্রুব AVOption *o,
                                     ধ্রুব বর্ণ *val, শূন্য *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    পূর্ণাঙ্ক ret;
    যদি (dst)
    av_channel_layout_uninit(channel_layout);
    অন্যথা
        channel_layout = &tmp;
    যদি (!val)
        প্রত্যাগম 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    যদি (ret < 0)
        প্রত্যাগম ret;
    যদি (!dst)
        av_channel_layout_uninit(channel_layout);
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opt_set_elem(শূন্য *obj, শূন্য *target_obj, ধ্রুব AVOption *o,
                        ধ্রুব বর্ণ *val, শূন্য *dst)
{
    শূন্য *logctx = dst ? obj : রিক্ত;
    ধ্রুব গণনা AVOptionType type = TYPE_BASE(o->type);
    পূর্ণাঙ্ক ret;

    যদি (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        প্রত্যাগম AVERROR(EINVAL);

    বিকল্প (type) {
    পক্ষ AV_OPT_TYPE_BOOL:
        প্রত্যাগম set_string_bool(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_STRING:
        প্রত্যাগম set_string(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_দ্বিমিক:
        প্রত্যাগম set_string_দ্বিমিক(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_FLAGS:
    পক্ষ AV_OPT_TYPE_INT:
    পক্ষ AV_OPT_TYPE_UINT:
    পক্ষ AV_OPT_TYPE_INT64:
    পক্ষ AV_OPT_TYPE_UINT64:
    পক্ষ AV_OPT_TYPE_FLOAT:
    পক্ষ AV_OPT_TYPE_DOUBLE:
    পক্ষ AV_OPT_TYPE_RATIONAL:
        প্রত্যাগম set_string_সংখ্যা(obj, target_obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
        প্রত্যাগম set_string_image_size(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        যদি (ret < 0)
            প্রত্যাগম ret;
        প্রত্যাগম write_সংখ্যা(obj, o, dst, 1, tmp.den, tmp.অঙ্ক, 0);
    }
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
        প্রত্যাগম set_string_pixel_fmt(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
        প্রত্যাগম set_string_sample_fmt(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            যদি (val) {
                যদি ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    প্রত্যাগম ret;
                }
            }
            যদি (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                প্রত্যাগম AVERROR(ERANGE);
            }
            যদি (dst)
            *(int64_t *)dst = usecs;
            প্রত্যাগম 0;
        }
    পক্ষ AV_OPT_TYPE_COLOR:
        প্রত্যাগম set_string_color(obj, o, val, dst);
    পক্ষ AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        যদি (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        প্রত্যাগম ret;
    পক্ষ AV_OPT_TYPE_DICT:
        প্রত্যাগম set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    প্রত্যাগম AVERROR(EINVAL);
}

স্থির পূর্ণাঙ্ক opt_set_array(শূন্য *obj, শূন্য *target_obj, ধ্রুব AVOption *o,
                         ধ্রুব বর্ণ *val, শূন্য *dst)
{
    ধ্রুব AVOptionArrayDef *arr = o->default_val.arr;
    ধ্রুব size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ধ্রুব uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = রিক্ত;

    শূন্য      *logctx = dst ? obj : রিক্ত;
    শূন্য       *elems = রিক্ত;
    unsigned nb_elems = 0;
    পূর্ণাঙ্ক ret;

    যদি (val && *val) {
        str = av_malloc(strlen(val) + 1);
        যদি (!str)
            প্রত্যাগম AVERROR(ENOMEM);
    }

    // split and unescape the string
    যাবত্ (val && *val) {
        uint8_t *p = str;
        শূন্য *tmp;

        যদি (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            গচ্ছ fail;
        }

        প্রতি (; *val; val++, p++) {
            যদি (*val == '\\' && val[1])
                val++;
            অন্যথা যদি (*val == sep) {
                val++;
                ভঙ্গ;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        যদি (!tmp) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        যদি (ret < 0)
            গচ্ছ fail;
        nb_elems++;
    }
    av_freep(&str);

    যদি (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    যদি (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        গচ্ছ fail;
    }

    যদি (dst) {
    *((শূন্য **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } অন্যথা
        opt_free_array(o, &elems, &nb_elems);

    প্রত্যাগম 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_set(শূন্য *obj, ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *val, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    শূন্য *dst, *target_obj;
    ধ্রুব AVOption *o;
    পূর্ণাঙ্ক ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, 0, &target_obj, &o, &dst);
    যদি (ret < 0)
        প্রত্যাগম ret;

    প্রত্যাগম ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_সংখ্যা(name, opttype, vartype)                         \
পূর্ণাঙ্ক av_opt_eval_ ## name(শূন্য *obj, ধ্রুব AVOption *o,                  \
                         ধ্রুব বর্ণ *val, vartype *name ## _out)        \
{                                                                       \
    যদি (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        প্রত্যাগম AVERROR(EINVAL);                                         \
    প্রত্যাগম set_string_সংখ্যা(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_সংখ্যা(flags,  AV_OPT_TYPE_FLAGS,    পূর্ণাঙ্ক)
OPT_EVAL_সংখ্যা(পূর্ণাঙ্ক,    AV_OPT_TYPE_INT,      পূর্ণাঙ্ক)
OPT_EVAL_সংখ্যা(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_সংখ্যা(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_সংখ্যা(ভিন্ন,  AV_OPT_TYPE_FLOAT,    ভিন্ন)
OPT_EVAL_সংখ্যা(দ্বিগুণ, AV_OPT_TYPE_DOUBLE,   দ্বিগুণ)
OPT_EVAL_সংখ্যা(q,      AV_OPT_TYPE_RATIONAL, AVRational)

স্থির পূর্ণাঙ্ক set_সংখ্যা(শূন্য *obj, ধ্রুব বর্ণ *name, দ্বিগুণ অঙ্ক, পূর্ণাঙ্ক den, int64_t intnum,
                      পূর্ণাঙ্ক অনুসন্ধান_flags, পূর্ণাঙ্ক require_type)
{
    শূন্য *dst;
    ধ্রুব AVOption *o;
    পূর্ণাঙ্ক ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, require_type, রিক্ত, &o, &dst);
    যদি (ret < 0)
        প্রত্যাগম ret;
    যদি (dst)
        ret = write_সংখ্যা(obj, o, dst, অঙ্ক, den, intnum, 0);

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_set_int(শূন্য *obj, ধ্রুব বর্ণ *name, int64_t val, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম set_সংখ্যা(obj, name, 1, 1, val, অনুসন্ধান_flags, 0);
}

পূর্ণাঙ্ক av_opt_set_double(শূন্য *obj, ধ্রুব বর্ণ *name, দ্বিগুণ val, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম set_সংখ্যা(obj, name, val, 1, 1, অনুসন্ধান_flags, 0);
}

পূর্ণাঙ্ক av_opt_set_q(শূন্য *obj, ধ্রুব বর্ণ *name, AVRational val, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম set_সংখ্যা(obj, name, val.অঙ্ক, val.den, 1, অনুসন্ধান_flags, 0);
}

পূর্ণাঙ্ক av_opt_set_bin(শূন্য *obj, ধ্রুব বর্ণ *name, ধ্রুব uint8_t *val, পূর্ণাঙ্ক len, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    পূর্ণাঙ্ক *lendst;
    পূর্ণাঙ্ক ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, AV_OPT_TYPE_দ্বিমিক,
                       রিক্ত, রিক্ত, (শূন্য**)&dst);
    যদি (ret < 0)
        প্রত্যাগম ret;

    যদি (dst) {
    ptr = len ? av_malloc(len) : রিক্ত;
    যদি (len && !ptr)
        প্রত্যাগম AVERROR(ENOMEM);

    lendst = (পূর্ণাঙ্ক *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    যদি (len)
        memcpy(ptr, val, len);
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_set_image_size(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক w, পূর্ণাঙ্ক h, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    ধ্রুব AVOption *o;
    শূন্য *logctx;
    পূর্ণাঙ্ক *dst;
    পূর্ণাঙ্ক ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       রিক্ত, &o, (শূন্য**)&dst);
    যদি (ret < 0)
        প্রত্যাগম ret;

    logctx = dst ? obj : রিক্ত;

    যদি (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        প্রত্যাগম AVERROR(EINVAL);
    }

    যদি (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_set_video_rate(শূন্য *obj, ধ্রুব বর্ণ *name, AVRational val, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম set_সংখ্যা(obj, name, val.অঙ্ক, val.den, 1, অনুসন্ধান_flags, AV_OPT_TYPE_VIDEO_RATE);
}

স্থির পূর্ণাঙ্ক set_format(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক fmt, পূর্ণাঙ্ক অনুসন্ধান_flags,
                      গণনা AVOptionType type, ধ্রুব বর্ণ *desc, পূর্ণাঙ্ক nb_fmts)
{
    ধ্রুব AVOption *o;
    শূন্য *logctx;
    পূর্ণাঙ্ক *dst;
    পূর্ণাঙ্ক min, max, ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, type, রিক্ত, &o, (শূন্য**)&dst);
    যদি (ret < 0)
        প্রত্যাগম ret;

    logctx = dst ? obj : রিক্ত;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    যদি (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        প্রত্যাগম AVERROR(ERANGE);
    }
    যদি (dst)
    *dst = fmt;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_set_pixel_fmt(শূন্য *obj, ধ্রুব বর্ণ *name, গণনা AVPixelFormat fmt, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম set_format(obj, name, fmt, অনুসন্ধান_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

পূর্ণাঙ্ক av_opt_set_sample_fmt(শূন্য *obj, ধ্রুব বর্ণ *name, গণনা AVSampleFormat fmt, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম set_format(obj, name, fmt, অনুসন্ধান_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

পূর্ণাঙ্ক av_opt_set_dict_val(শূন্য *obj, ধ্রুব বর্ণ *name, ধ্রুব AVDictionary *val,
                        পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    AVDictionary **dst;
    পূর্ণাঙ্ক ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, AV_OPT_TYPE_DICT, রিক্ত, রিক্ত,
                       (শূন্য**)&dst);
    যদি (ret < 0)
        প্রত্যাগম ret;

    যদি (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_set_chlayout(শূন্য *obj, ধ্রুব বর্ণ *name,
                        ধ্রুব AVChannelLayout *channel_layout,
                        পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    AVChannelLayout *dst;
    পূর্ণাঙ্ক ret;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, AV_OPT_TYPE_CHLAYOUT, রিক্ত, রিক্ত,
                       (শূন্য**)&dst);
    যদি (ret < 0)
        প্রত্যাগম ret;

    যদি (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    প্রত্যাগম ret;
}

স্থির শূন্য format_duration(বর্ণ *buf, size_t size, int64_t d)
{
    বর্ণ *e;

    av_assert0(size >= 25);
    যদি (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    যদি (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    অন্যথা যদি (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    অন্যথা যদি (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (পূর্ণাঙ্ক)((d / 60000000) % 60),
                 (পূর্ণাঙ্ক)((d / 1000000) % 60),
                 (পূর্ণাঙ্ক)(d % 1000000));
    অন্যথা যদি (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (পূর্ণাঙ্ক)(d / 60000000),
                 (পূর্ণাঙ্ক)((d / 1000000) % 60),
                 (পূর্ণাঙ্ক)(d % 1000000));
    অন্যথা
        snprintf(buf, size, "%d.%06d",
                 (পূর্ণাঙ্ক)(d / 1000000),
                 (পূর্ণাঙ্ক)(d % 1000000));
    e = buf + strlen(buf);
    যাবত্ (e > buf && e[-1] == '0')
        *(--e) = 0;
    যদি (e > buf && e[-1] == '.')
        *(--e) = 0;
}

স্থির পূর্ণাঙ্ক opt_get_elem(ধ্রুব AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ধ্রুব শূন্য *dst, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    পূর্ণাঙ্ক ret;

    বিকল্প (TYPE_BASE(o->type)) {
    পক্ষ AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(পূর্ণাঙ্ক *)dst));
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(পূর্ণাঙ্ক *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(পূর্ণাঙ্ক *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(ভিন্ন *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(দ্বিগুণ *)dst);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_VIDEO_RATE:
    পক্ষ AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->অঙ্ক, ((AVRational *)dst)->den);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_STRING:
        যদি (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } অন্যথা যদি (অনুসন্ধান_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = রিক্ত;
            প্রত্যাগম 0;
        } অন্যথা {
            *pbuf = av_strdup("");
        }
        প্রত্যাগম *pbuf ? 0 : AVERROR(ENOMEM);
    পক্ষ AV_OPT_TYPE_দ্বিমিক: {
        ধ্রুব uint8_t *bin;
        পূর্ণাঙ্ক len;

        যদি (!*(uint8_t **)dst && (অনুসন্ধান_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = রিক্ত;
            প্রত্যাগম 0;
        }
        len = *(পূর্ণাঙ্ক *)(((uint8_t *)dst) + পরিমাণ(uint8_t *));
        যদি ((uint64_t)len * 2 + 1 > INT_MAX)
            প্রত্যাগম AVERROR(EINVAL);
        যদি (!(*pbuf = av_malloc(len * 2 + 1)))
            প্রত্যাগম AVERROR(ENOMEM);
        যদি (!len) {
            *pbuf[0] = '\0';
            প্রত্যাগম 0;
        }
        bin = *(uint8_t **)dst;
        প্রতি (পূর্ণাঙ্ক i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        প্রত্যাগম 0;
    }
    পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((পূর্ণাঙ্ক *)dst)[0], ((পূর্ণাঙ্ক *)dst)[1]);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (বর্ণ *)av_x_if_null(av_get_pix_fmt_name(*(গণনা AVPixelFormat *)dst), "none"));
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (বর্ণ *)av_x_if_null(av_get_sample_fmt_name(*(গণনা AVSampleFormat *)dst), "none"));
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        ভঙ্গ;
    }
    পক্ষ AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (পূর্ণাঙ্ক)((uint8_t *)dst)[0], (পূর্ণাঙ্ক)((uint8_t *)dst)[1],
                       (পূর্ণাঙ্ক)((uint8_t *)dst)[2], (পূর্ণাঙ্ক)((uint8_t *)dst)[3]);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_DICT:
        যদি (!*(AVDictionary **)dst && (অনুসন্ধান_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = রিক্ত;
            প্রত্যাগম 0;
        }
        প্রত্যাগম av_dict_get_string(*(AVDictionary **)dst, (বর্ণ **)pbuf, '=', ':');
    স্বভাব:
        প্রত্যাগম AVERROR(EINVAL);
    }

    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক opt_get_array(ধ্রুব AVOption *o, শূন্য *dst, uint8_t **out_val)
{
    ধ্রুব unsigned গুনতি = *opt_array_pcount(dst);
    ধ্রুব uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = রিক্ত;
    size_t   str_len = 0;
    পূর্ণাঙ্ক ret;

    *out_val = রিক্ত;

    প্রতি (unsigned i = 0; i < গুনতি; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, পরিমাণ(buf),
                           opt_array_pelem(o, *(শূন্য **)dst, i), 0);
        যদি (ret < 0)
            গচ্ছ fail;

        out_len = strlen(out);
        যদি (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            গচ্ছ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        যদি (ret < 0)
            গচ্ছ fail;

        // add separator if needed
        যদি (i)
            str[str_len++] = sep;

        // escape the element
        প্রতি (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            যদি (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        যদি (out != buf)
            av_freep(&out);
        যদি (ret < 0) {
            av_freep(&str);
            প্রত্যাগম ret;
        }
    }

    *out_val = str;

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, uint8_t **out_val)
{
    শূন্য *dst, *target_obj;
    ধ্রুব AVOption *o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    uint8_t *out, buf[128];
    পূর্ণাঙ্ক ret;

    যদি (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;

    যদি (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    যদি (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        যদি (ret < 0)
            প্রত্যাগম ret;
        যদি (!*out_val && !(অনুসন্ধান_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            যদি (!*out_val)
               প্রত্যাগম AVERROR(ENOMEM);
        }
        প্রত্যাগম 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, পরিমাণ(buf), dst, অনুসন্ধান_flags);
    যদি (ret < 0)
        প্রত্যাগম ret;
    যদি (out != buf) {
        *out_val = out;
        প্রত্যাগম 0;
    }

    যদি (ret >= পরিমাণ(buf))
        প্রত্যাগম AVERROR(EINVAL);
    *out_val = av_strdup(out);
    প্রত্যাগম *out_val ? 0 : AVERROR(ENOMEM);
}

স্থির পূর্ণাঙ্ক get_সংখ্যা(শূন্য *obj, ধ্রুব বর্ণ *name, দ্বিগুণ *অঙ্ক, পূর্ণাঙ্ক *den, int64_t *intnum,
                      পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    শূন্য *dst, *target_obj;
    ধ্রুব AVOption *o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        প্রত্যাগম AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    প্রত্যাগম read_সংখ্যা(o, dst, অঙ্ক, den, intnum);
}

পূর্ণাঙ্ক av_opt_get_int(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    দ্বিগুণ অঙ্ক = 1;
    পূর্ণাঙ্ক ret, den = 1;

    যদি ((ret = get_সংখ্যা(obj, name, &অঙ্ক, &den, &intnum, অনুসন্ধান_flags)) < 0)
        প্রত্যাগম ret;
    যদি (অঙ্ক == den)
        *out_val = intnum;
    অন্যথা
        *out_val = অঙ্ক * intnum / den;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_double(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, দ্বিগুণ *out_val)
{
    int64_t intnum = 1;
    দ্বিগুণ অঙ্ক = 1;
    পূর্ণাঙ্ক ret, den = 1;

    যদি ((ret = get_সংখ্যা(obj, name, &অঙ্ক, &den, &intnum, অনুসন্ধান_flags)) < 0)
        প্রত্যাগম ret;
    *out_val = অঙ্ক * intnum / den;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_q(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    দ্বিগুণ অঙ্ক = 1;
    পূর্ণাঙ্ক ret, den = 1;

    যদি ((ret = get_সংখ্যা(obj, name, &অঙ্ক, &den, &intnum, অনুসন্ধান_flags)) < 0)
        প্রত্যাগম ret;

    যদি (অঙ্ক == 1.0 && (পূর্ণাঙ্ক)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    অন্যথা
        *out_val = double_to_rational(অঙ্ক*intnum/den);
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_image_size(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, পূর্ণাঙ্ক *w_out, পূর্ণাঙ্ক *h_out)
{
    শূন্য *dst, *target_obj;
    ধ্রুব AVOption *o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        প্রত্যাগম AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    যদি (w_out) *w_out = *(পূর্ণাঙ্ক *)dst;
    যদি (h_out) *h_out = *((পূর্ণাঙ্ক *)dst+1);
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_video_rate(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, AVRational *out_val)
{
    প্রত্যাগম av_opt_get_q(obj, name, অনুসন্ধান_flags, out_val);
}

স্থির পূর্ণাঙ্ক get_format(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, শূন্য *out_fmt,
                      গণনা AVOptionType type, ধ্রুব বর্ণ *desc)
{
    শূন্য *dst, *target_obj;
    ধ্রুব AVOption *o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        প্রত্যাগম AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    যদি (type == AV_OPT_TYPE_PIXEL_FMT)
        *(গণনা AVPixelFormat *)out_fmt = *(গণনা AVPixelFormat *)dst;
    অন্যথা
        *(গণনা AVSampleFormat*)out_fmt = *(গণনা AVSampleFormat*)dst;

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_pixel_fmt(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, গণনা AVPixelFormat *out_fmt)
{
    প্রত্যাগম get_format(obj, name, অনুসন্ধান_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

পূর্ণাঙ্ক av_opt_get_sample_fmt(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, গণনা AVSampleFormat *out_fmt)
{
    প্রত্যাগম get_format(obj, name, অনুসন্ধান_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

পূর্ণাঙ্ক av_opt_get_chlayout(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, AVChannelLayout *cl)
{
    শূন্য *dst, *target_obj;
    ধ্রুব AVOption *o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        প্রত্যাগম AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    প্রত্যাগম av_channel_layout_copy(cl, dst);
}

পূর্ণাঙ্ক av_opt_get_dict_val(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags, AVDictionary **out_val)
{
    শূন্য *target_obj;
    AVDictionary *src;
    ধ্রুব AVOption *o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);

    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (o->type != AV_OPT_TYPE_DICT)
        প্রত্যাগম AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    প্রত্যাগম av_dict_copy(out_val, src, 0);
}

পূর্ণাঙ্ক av_opt_flag_is_set(শূন্য *obj, ধ্রুব বর্ণ *field_name, ধ্রুব বর্ণ *flag_name)
{
    ধ্রুব AVOption *field = av_opt_find(obj, field_name, রিক্ত, 0, 0);
    ধ্রুব AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : রিক্ত, 0, 0);
    int64_t res;

    যদি (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        প্রত্যাগম 0;
    প্রত্যাগম res & flag->default_val.i64;
}

স্থির শূন্য log_int_মান(শূন্য *av_log_obj, পূর্ণাঙ্ক level, int64_t i)
{
    যদি (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } অন্যথা যদি (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } অন্যথা যদি (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } অন্যথা যদি (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } অন্যথা যদি (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } অন্যথা {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

স্থির শূন্য log_মান(শূন্য *av_log_obj, পূর্ণাঙ্ক level, দ্বিগুণ d)
{
    যদি      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } অন্যথা যদি (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } অন্যথা যদি (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } অন্যথা যদি (d == (দ্বিগুণ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } অন্যথা যদি (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } অন্যথা যদি (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } অন্যথা যদি (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } অন্যথা যদি (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } অন্যথা যদি (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } অন্যথা যদি (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } অন্যথা যদি (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } অন্যথা যদি (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } অন্যথা যদি (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } অন্যথা {
        av_log(av_log_obj, level, "%g", d);
    }
}

স্থির ধ্রুব বর্ণ *get_opt_const_name(শূন্য *obj, ধ্রুব বর্ণ *unit, int64_t মান)
{
    ধ্রুব AVOption *opt = রিক্ত;

    যদি (!unit)
        প্রত্যাগম রিক্ত;
    যাবত্ ((opt = av_opt_next(obj, opt)))
        যদি (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == মান)
            প্রত্যাগম opt->name;
    প্রত্যাগম রিক্ত;
}

স্থির বর্ণ *get_opt_flags_string(শূন্য *obj, ধ্রুব বর্ণ *unit, int64_t মান)
{
    ধ্রুব AVOption *opt = রিক্ত;
    বর্ণ flags[512];

    flags[0] = 0;
    যদি (!unit)
        প্রত্যাগম রিক্ত;
    যাবত্ ((opt = av_opt_next(obj, opt))) {
        যদি (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & মান) {
            যদি (flags[0])
                av_strlcatf(flags, পরিমাণ(flags), "+");
            av_strlcatf(flags, পরিমাণ(flags), "%s", opt->name);
        }
    }
    যদি (flags[0])
        প্রত্যাগম av_strdup(flags);
    প্রত্যাগম রিক্ত;
}

স্থির শূন্য log_type(শূন্য *av_log_obj, ধ্রুব AVOption *o,
                     গণনা AVOptionType parent_type)
{
    ধ্রুব গণনা AVOptionType type = TYPE_BASE(o->type);

    যদি (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    অন্যথা যদি (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        যদি (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        অন্যথা
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    অন্যথা
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

স্থির শূন্য log_default(শূন্য *obj, শূন্য *av_log_obj, ধ্রুব AVOption *opt)
{
    যদি (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_দ্বিমিক)
        প্রত্যাগম;
    যদি ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        প্রত্যাগম;

    যদি (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ধ্রুব AVOptionArrayDef *arr = opt->default_val.arr;
        যদি (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        প্রত্যাগম;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    বিকল্প (opt->type) {
    পক্ষ AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_FLAGS: {
        বর্ণ *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        যদি (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } অন্যথা {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        ভঙ্গ;
    }
    পক্ষ AV_OPT_TYPE_DURATION: {
        বর্ণ buf[25];
        format_duration(buf, পরিমাণ(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        ভঙ্গ;
    }
    পক্ষ AV_OPT_TYPE_UINT:
    পক্ষ AV_OPT_TYPE_INT:
    পক্ষ AV_OPT_TYPE_UINT64:
    পক্ষ AV_OPT_TYPE_INT64: {
        ধ্রুব বর্ণ *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        যদি (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        অন্যথা
            log_int_মান(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        ভঙ্গ;
    }
    পক্ষ AV_OPT_TYPE_DOUBLE:
    পক্ষ AV_OPT_TYPE_FLOAT:
        log_মান(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.অঙ্ক, q.den); }
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (বর্ণ *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (বর্ণ *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_COLOR:
    পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
    পক্ষ AV_OPT_TYPE_STRING:
    পক্ষ AV_OPT_TYPE_DICT:
    পক্ষ AV_OPT_TYPE_VIDEO_RATE:
    পক্ষ AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        ভঙ্গ;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

স্থির শূন্য opt_list(শূন্য *obj, শূন্য *av_log_obj, ধ্রুব বর্ণ *unit,
                     পূর্ণাঙ্ক req_flags, পূর্ণাঙ্ক rej_flags, গণনা AVOptionType parent_type)
{
    ধ্রুব AVOption *opt = রিক্ত;
    AVOptionRanges *r;
    পূর্ণাঙ্ক i;

    যাবত্ ((opt = av_opt_next(obj, opt))) {
        যদি (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            অনুবর্ত;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        যদি (!unit && opt->type == AV_OPT_TYPE_CONST)
            অনুবর্ত;
        অন্যথা যদি (unit && opt->type != AV_OPT_TYPE_CONST)
            অনুবর্ত;
        অন্যথা যদি (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            অনুবর্ত;
        অন্যথা যদি (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        অন্যথা
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

        যদি (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        যদি (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_অনুসন্ধান_FAKE_OBJ) >= 0) {
            বিকল্প (opt->type) {
            পক্ষ AV_OPT_TYPE_INT:
            পক্ষ AV_OPT_TYPE_UINT:
            পক্ষ AV_OPT_TYPE_INT64:
            পক্ষ AV_OPT_TYPE_UINT64:
            পক্ষ AV_OPT_TYPE_DOUBLE:
            পক্ষ AV_OPT_TYPE_FLOAT:
            পক্ষ AV_OPT_TYPE_RATIONAL:
                প্রতি (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_মান(av_log_obj, AV_LOG_INFO, r->range[i]->মান_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_মান(av_log_obj, AV_LOG_INFO, r->range[i]->মান_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                ভঙ্গ;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        যদি (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

পূর্ণাঙ্ক av_opt_show2(শূন্য *obj, শূন্য *av_log_obj, পূর্ণাঙ্ক req_flags, পূর্ণাঙ্ক rej_flags)
{
    যদি (!obj)
        প্রত্যাগম -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, রিক্ত, req_flags, rej_flags, -1);

    প্রত্যাগম 0;
}

শূন্য av_opt_set_defaults(শূন্য *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

শূন্য av_opt_set_defaults2(শূন্য *s, পূর্ণাঙ্ক mask, পূর্ণাঙ্ক flags)
{
    ধ্রুব AVOption *opt = রিক্ত;
    যাবত্ ((opt = av_opt_next(s, opt))) {
        শূন্য *dst = ((uint8_t*)s) + opt->offset;

        যদি ((opt->flags & mask) != flags)
            অনুবর্ত;

        যদি (opt->flags & AV_OPT_FLAG_READONLY)
            অনুবর্ত;

        যদি (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ধ্রুব AVOptionArrayDef *arr = opt->default_val.arr;
            ধ্রুব বর্ণ              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            যদি (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            অনুবর্ত;
        }

        বিকল্প (opt->type) {
            পক্ষ AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_BOOL:
            পক্ষ AV_OPT_TYPE_FLAGS:
            পক্ষ AV_OPT_TYPE_INT:
            পক্ষ AV_OPT_TYPE_UINT:
            পক্ষ AV_OPT_TYPE_INT64:
            পক্ষ AV_OPT_TYPE_UINT64:
            পক্ষ AV_OPT_TYPE_DURATION:
            পক্ষ AV_OPT_TYPE_PIXEL_FMT:
            পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
                write_সংখ্যা(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_DOUBLE:
            পক্ষ AV_OPT_TYPE_FLOAT: {
                দ্বিগুণ val;
                val = opt->default_val.dbl;
                write_সংখ্যা(s, opt, dst, val, 1, 1, 1);
            }
            ভঙ্গ;
            পক্ষ AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_সংখ্যা(s, opt, dst, 1, val.den, val.অঙ্ক, 1);
            }
            ভঙ্গ;
            পক্ষ AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_দ্বিমিক:
                set_string_দ্বিমিক(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                ভঙ্গ;
        স্বভাব:
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
স্থির পূর্ণাঙ্ক parse_চাবি_মান_pair(শূন্য *ctx, ধ্রুব বর্ণ **buf,
                                ধ্রুব বর্ণ *চাবি_val_sep, ধ্রুব বর্ণ *pairs_sep)
{
    বর্ণ *চাবি = av_get_token(buf, চাবি_val_sep);
    বর্ণ *val;
    পূর্ণাঙ্ক ret;

    যদি (!চাবি)
        প্রত্যাগম AVERROR(ENOMEM);

    যদি (*চাবি && strspn(*buf, চাবি_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        যদি (!val) {
            av_freep(&চাবি);
            প্রত্যাগম AVERROR(ENOMEM);
        }
    } অন্যথা {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", চাবি);
        av_free(চাবি);
        প্রত্যাগম AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", চাবি, val);

    ret = av_opt_set(ctx, চাবি, val, AV_OPT_অনুসন্ধান_CHILDREN);
    যদি (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", চাবি);

    av_free(চাবি);
    av_free(val);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_set_options_string(শূন্য *ctx, ধ্রুব বর্ণ *opts,
                          ধ্রুব বর্ণ *চাবি_val_sep, ধ্রুব বর্ণ *pairs_sep)
{
    পূর্ণাঙ্ক ret, গুনতি = 0;

    যদি (!opts)
        প্রত্যাগম 0;

    যাবত্ (*opts) {
        যদি ((ret = parse_চাবি_মান_pair(ctx, &opts, চাবি_val_sep, pairs_sep)) < 0)
            প্রত্যাগম ret;
        গুনতি++;

        যদি (*opts)
            opts++;
    }

    প্রত্যাগম গুনতি;
}

#define WHITESPACES " \n\t\r"

স্থির পূর্ণাঙ্ক is_চাবি_char(বর্ণ c)
{
    প্রত্যাগম (unsigned)((c | 32) - 'a') < 26 ||
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
স্থির পূর্ণাঙ্ক get_চাবি(ধ্রুব বর্ণ **ropts, ধ্রুব বর্ণ *delim, বর্ণ **rkey)
{
    ধ্রুব বর্ণ *opts = *ropts;
    ধ্রুব বর্ণ *চাবি_start, *চাবি_end;

    চাবি_start = opts += strspn(opts, WHITESPACES);
    যাবত্ (is_চাবি_char(*opts))
        opts++;
    চাবি_end = opts;
    opts += strspn(opts, WHITESPACES);
    যদি (!*opts || !strchr(delim, *opts))
        প্রত্যাগম AVERROR(EINVAL);
    opts++;
    যদি (!(*rkey = av_malloc(চাবি_end - চাবি_start + 1)))
        প্রত্যাগম AVERROR(ENOMEM);
    memcpy(*rkey, চাবি_start, চাবি_end - চাবি_start);
    (*rkey)[চাবি_end - চাবি_start] = 0;
    *ropts = opts;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_চাবি_মান(ধ্রুব বর্ণ **ropts,
                         ধ্রুব বর্ণ *চাবি_val_sep, ধ্রুব বর্ণ *pairs_sep,
                         unsigned flags,
                         বর্ণ **rkey, বর্ণ **rval)
{
    পূর্ণাঙ্ক ret;
    বর্ণ *চাবি = রিক্ত, *val;
    ধ্রুব বর্ণ *opts = *ropts;

    যদি ((ret = get_চাবি(&opts, চাবি_val_sep, &চাবি)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_চাবি))
        প্রত্যাগম AVERROR(EINVAL);
    যদি (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(চাবি);
        প্রত্যাগম AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = চাবি;
    *rval  = val;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_set_from_string(শূন্য *ctx, ধ্রুব বর্ণ *opts,
                           ধ্রুব বর্ণ *ধ্রুব *shorthand,
                           ধ্রুব বর্ণ *চাবি_val_sep, ধ্রুব বর্ণ *pairs_sep)
{
    পূর্ণাঙ্ক ret, গুনতি = 0;
    ধ্রুব বর্ণ *dummy_shorthand = রিক্ত;
    ধ্রুব বর্ণ *চাবি;

    যদি (!opts)
        প্রত্যাগম 0;
    যদি (!shorthand)
        shorthand = &dummy_shorthand;

    যাবত্ (*opts) {
        বর্ণ *parsed_চাবি, *মান;
        ret = av_opt_get_চাবি_মান(&opts, চাবি_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_চাবি : 0,
                                   &parsed_চাবি, &মান);
        যদি (ret < 0) {
            যদি (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            অন্যথা
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            প্রত্যাগম ret;
        }
        যদি (*opts)
            opts++;
        যদি (parsed_চাবি) {
            চাবি = parsed_চাবি;
            যাবত্ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } অন্যথা {
            চাবি = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", চাবি, মান);
        যদি ((ret = av_opt_set(ctx, চাবি, মান, 0)) < 0) {
            যদি (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", চাবি);
            av_free(মান);
            av_free(parsed_চাবি);
            প্রত্যাগম ret;
        }

        av_free(মান);
        av_free(parsed_চাবি);
        গুনতি++;
    }
    প্রত্যাগম গুনতি;
}

শূন্য av_opt_free(শূন্য *obj)
{
    ধ্রুব AVOption *o = রিক্ত;
    যাবত্ ((o = av_opt_next(obj, o))) {
        শূন্য *pitem = (uint8_t *)obj + o->offset;

        যদি (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        অন্যথা
            opt_free_elem(o->type, pitem);
    }
}

পূর্ণাঙ্ক av_opt_set_dict2(শূন্য *obj, AVDictionary **options, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    ধ্রুব AVDictionaryEntry *t = রিক্ত;
    AVDictionary    *tmp = রিক্ত;
    পূর্ণাঙ্ক ret;

    যদি (!options)
        প্রত্যাগম 0;

    যাবত্ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->চাবি, t->মান, অনুসন্ধান_flags);
        যদি (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->চাবি, t->মান, AV_DICT_MULTIKEY);
        যদি (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->চাবি, t->মান);
            av_dict_free(&tmp);
            প্রত্যাগম ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_set_dict(শূন্য *obj, AVDictionary **options)
{
    প্রত্যাগম av_opt_set_dict2(obj, options, 0);
}

ধ্রুব AVOption *av_opt_find(শূন্য *obj, ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *unit,
                            পূর্ণাঙ্ক opt_flags, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    প্রত্যাগম av_opt_find2(obj, name, unit, opt_flags, অনুসন্ধান_flags, রিক্ত);
}

ধ্রুব AVOption *av_opt_find2(শূন্য *obj, ধ্রুব বর্ণ *name, ধ্রুব বর্ণ *unit,
                             পূর্ণাঙ্ক opt_flags, পূর্ণাঙ্ক অনুসন্ধান_flags, শূন্য **target_obj)
{
    ধ্রুব AVClass  *c;
    ধ্রুব AVOption *o = রিক্ত;

    যদি(!obj)
        প্রত্যাগম রিক্ত;

    c= *(AVClass**)obj;

    যদি (!c)
        প্রত্যাগম রিক্ত;

    যদি (অনুসন্ধান_flags & AV_OPT_অনুসন্ধান_CHILDREN) {
        যদি (অনুসন্ধান_flags & AV_OPT_অনুসন্ধান_FAKE_OBJ) {
            শূন্য *iter = রিক্ত;
            ধ্রুব AVClass *child;
            যাবত্ (child = av_opt_child_class_iterate(c, &iter))
                যদি (o = av_opt_find2(&child, name, unit, opt_flags, অনুসন্ধান_flags, রিক্ত))
                    প্রত্যাগম o;
        } অন্যথা {
            শূন্য *child = রিক্ত;
            যাবত্ (child = av_opt_child_next(obj, child))
                যদি (o = av_opt_find2(child, name, unit, opt_flags, অনুসন্ধান_flags, target_obj))
                    প্রত্যাগম o;
        }
    }

    যাবত্ (o = av_opt_next(obj, o)) {
        যদি (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            যদি (target_obj) {
                যদি (!(অনুসন্ধান_flags & AV_OPT_অনুসন্ধান_FAKE_OBJ))
                    *target_obj = obj;
                অন্যথা
                    *target_obj = রিক্ত;
            }
            প্রত্যাগম o;
        }
    }
    প্রত্যাগম রিক্ত;
}

শূন্য *av_opt_child_next(শূন্য *obj, শূন্য *prev)
{
    ধ্রুব AVClass *c = *(AVClass **)obj;
    যদি (c->child_next)
        প্রত্যাগম c->child_next(obj, prev);
    প্রত্যাগম রিক্ত;
}

ধ্রুব AVClass *av_opt_child_class_iterate(ধ্রুব AVClass *parent, শূন্য **iter)
{
    যদি (parent->child_class_iterate)
        প্রত্যাগম parent->child_class_iterate(iter);
    প্রত্যাগম রিক্ত;
}

স্থির পূর্ণাঙ্ক opt_copy_elem(শূন্য *logctx, গণনা AVOptionType type,
                         শূন্য *dst, ধ্রুব শূন্য *src)
{
    যদি (type == AV_OPT_TYPE_STRING) {
        ধ্রুব বর্ণ *src_str = *(ধ্রুব বর্ণ *ধ্রুব *)src;
        বর্ণ         **dstp =  (বর্ণ **)dst;
        যদি (*dstp != src_str)
            av_freep(dstp);
        যদি (src_str) {
            *dstp = av_strdup(src_str);
            যদি (!*dstp)
                প্রত্যাগম AVERROR(ENOMEM);
        }
    } অন্যথা যদি (type == AV_OPT_TYPE_দ্বিমিক) {
        ধ্রুব uint8_t *ধ্রুব *src8 = (ধ্রুব uint8_t *ধ্রুব *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        পূর্ণাঙ্ক len = *(ধ্রুব পূর্ণাঙ্ক *)(src8 + 1);
        যদি (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        যদি (len && !*dst8) {
            *(পূর্ণাঙ্ক *)(dst8 + 1) = 0;
            প্রত্যাগম AVERROR(ENOMEM);
        }
        *(পূর্ণাঙ্ক *)(dst8 + 1) = len;
    } অন্যথা যদি (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } অন্যথা যদি (type == AV_OPT_TYPE_DICT) {
        ধ্রুব AVDictionary *sdict = *(ধ্রুব AVDictionary * ধ্রুব *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        যদি (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = রিক্ত;
        প্রত্যাগম av_dict_copy(ddictp, sdict, 0);
    } অন্যথা যদি (type == AV_OPT_TYPE_CHLAYOUT) {
        ধ্রুব AVChannelLayout *slayout = (ধ্রুব AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        যদি (dlayout != slayout) {
            যদি (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = রিক্ত;
            প্রত্যাগম av_channel_layout_copy(dst, src);
        }
    } অন্যথা যদি (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } অন্যথা {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        প্রত্যাগম AVERROR(EINVAL);
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক opt_copy_array(শূন্য *logctx, ধ্রুব AVOption *o,
                          শূন্য **pdst, ধ্রুব শূন্য * ধ্রুব *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    শূন্য         *dst = রিক্ত;
    পূর্ণাঙ্ক ret;

    যদি (*pdst == *psrc) {
        *pdst                   = রিক্ত;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    যদি (!dst)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(শূন্য**)psrc, i));
        যদি (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            প্রত্যাগম ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_copy(শূন্য *dst, ধ্রুব শূন্য *src)
{
    ধ্রুব AVOption *o = রিক্ত;
    ধ্রুব AVClass *c;
    পূর্ণাঙ্ক ret = 0;

    যদি (!src)
        প্রত্যাগম AVERROR(EINVAL);

    c = *(AVClass **)src;
    যদি (!c || c != *(AVClass **)dst)
        প্রত্যাগম AVERROR(EINVAL);

    যাবত্ ((o = av_opt_next(src, o))) {
        শূন্য *field_dst = (uint8_t *)dst + o->offset;
        শূন্য *field_src = (uint8_t *)src + o->offset;

        পূর্ণাঙ্ক err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        যদি (err < 0)
            ret = err;
    }
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_get_array_size(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags,
                          unsigned পূর্ণাঙ্ক *out_val)
{
    শূন্য *target_obj, *parray;
    ধ্রুব AVOption *o;

    o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        প্রত্যাগম AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_get_array(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags,
                     unsigned পূর্ণাঙ্ক start_elem, unsigned পূর্ণাঙ্ক nb_elems,
                     গণনা AVOptionType out_type, শূন্য *out_val)
{
    ধ্রুব size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ধ্রুব AVOption *o;
    শূন্য *target_obj;

    ধ্রুব শূন্য *parray;
    unsigned array_size;

    পূর্ণাঙ্ক ret;

    o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target_obj);
    যদি (!o || !target_obj)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    যদি (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        প্রত্যাগম AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    যদি (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        প্রত্যাগম AVERROR(EINVAL);

    প্রতি (unsigned i = 0; i < nb_elems; i++) {
        ধ্রুব শূন্য *src = opt_array_pelem(o, *(শূন্য**)parray, start_elem + i);
        শূন্য       *dst = (uint8_t*)out_val + i * elem_size_out;

        যদি (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            যদি (ret < 0)
                গচ্ছ fail;
        } অন্যথা যদি (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, পরিমাণ(buf), src, অনুসন্ধান_flags);
            যদি (ret < 0)
                গচ্ছ fail;

            যদি (out == buf) {
                out = av_strdup(buf);
                যদি (!out) {
                    ret = AVERROR(ENOMEM);
                    গচ্ছ fail;
                }
            }

            *(uint8_t**)dst = out;
        } অন্যথা যদি (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            দ্বিগুণ     অঙ্ক = 1.0;
            পূর্ণাঙ্ক        den = 1;
            int64_t intnum = 1;

            ret = read_সংখ্যা(o, src, &অঙ্ক, &den, &intnum);
            যদি (ret < 0)
                গচ্ছ fail;

            বিকল্প (out_type) {
            পক্ষ AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (অঙ্ক == den) ?  intnum : অঙ্ক * intnum / den;
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_DOUBLE:
                *(দ্বিগুণ*)dst = অঙ্ক * intnum / den;
                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (অঙ্ক == 1.0 && (পূর্ণাঙ্ক)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(অঙ্ক * intnum / den);
                ভঙ্গ;
            স্বভাব: av_assert0(0);
            }
        } অন্যথা
            প্রত্যাগম AVERROR(ENOSYS);
    }

    প্রত্যাগম 0;
fail:
    প্রতি (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_set_array(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags,
                     unsigned পূর্ণাঙ্ক start_elem, unsigned পূর্ণাঙ্ক nb_elems,
                     গণনা AVOptionType val_type, ধ্রুব শূন্য *val)
{
    ধ্রুব size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ধ্রুব AVOption *o;
    ধ্রুব AVOptionArrayDef *arr;
    শূন্য *target_obj;

    শূন্য *parray;
    শূন্য *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    পূর্ণাঙ্ক ret = 0;

    ret = opt_set_init(obj, name, অনুসন্ধান_flags, 0, &target_obj, &o, &parray);
    যদি (ret < 0)
        প্রত্যাগম ret;

    যদি (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        প্রত্যাগম AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    যদি (start_elem > *array_size)
        প্রত্যাগম AVERROR(EINVAL);

    // compute new array size
    যদি (!val) {
        যদি (*array_size - start_elem < nb_elems)
            প্রত্যাগম AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } অন্যথা যদি (অনুসন্ধান_flags & AV_OPT_ARRAY_REPLACE) {
        যদি (start_elem >= UINT_MAX - nb_elems)
            প্রত্যাগম AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } অন্যথা {
        যদি (nb_elems >= UINT_MAX - *array_size)
            প্রত্যাগম AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    যদি (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        প্রত্যাগম AVERROR(EINVAL);

    // desired operation is shrinking the array
    যদি (!val) {
        শূন্য *array = *(শূন্য**)parray;

        প্রতি (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        যদি (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            যদি (!array)
                প্রত্যাগম AVERROR(ENOMEM);

            *(শূন্য**)parray = array;
        } অন্যথা
            av_freep(parray);

        *array_size = new_size;

        প্রত্যাগম 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    যদি (!new_elems)
        প্রত্যাগম AVERROR(ENOMEM);

    // convert/validate each new element
    প্রতি (unsigned i = 0; i < nb_elems; i++) {
        শূন্য       *dst = opt_array_pelem(o, new_elems, i);
        ধ্রুব শূন্য *src = (uint8_t*)val + i * elem_size_val;

        দ্বিগুণ     অঙ্ক = 1.0;
        পূর্ণাঙ্ক        den = 1;
        int64_t intnum = 1;

        যদি (val_type == TYPE_BASE(o->type)) {
            পূর্ণাঙ্ক err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            যদি (ret < 0)
                গচ্ছ fail;

            // validate the range for numeric options
            err = read_সংখ্যা(o, dst, &অঙ্ক, &den, &intnum);
            যদি (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < অঙ্ক * intnum || o->min * den > অঙ্ক * intnum)) {
                অঙ্ক = den ? অঙ্ক * intnum / den : (অঙ্ক && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, অঙ্ক, o->min, o->max);
                ret = AVERROR(ERANGE);
                গচ্ছ fail;
            }
        } অন্যথা যদি (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ধ্রুব বর্ণ **)src, dst);
            যদি (ret < 0)
                গচ্ছ fail;
        } অন্যথা যদি (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            বিকল্প (val_type) {
            পক্ষ AV_OPT_TYPE_INT:       intnum = *(পূর্ণাঙ্ক*)src;                ভঙ্গ;
            পক্ষ AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            ভঙ্গ;
            পক্ষ AV_OPT_TYPE_FLOAT:     অঙ্ক    = *(ভিন্ন*)src;              ভঙ্গ;
            পক্ষ AV_OPT_TYPE_DOUBLE:    অঙ্ক    = *(দ্বিগুণ*)src;             ভঙ্গ;
            পক্ষ AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->অঙ্ক;
                                        den    = ((AVRational*)src)->den;   ভঙ্গ;
            স্বভাব: av_assert0(0);
            }

            ret = write_সংখ্যা(obj, o, dst, অঙ্ক, den, intnum, 0);
            যদি (ret < 0)
                গচ্ছ fail;
        } অন্যথা {
            ret = AVERROR(ENOSYS);
            গচ্ছ fail;
        }
    }

    // commit new elements to the array
    যদি (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(শূন্য**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = রিক্ত;
        nb_elems  = 0;
    } অন্যথা {
        শূন্য *array = av_realloc_array(*(শূন্য**)parray, new_size, elem_size);
        যদি (!array) {
            ret = AVERROR(ENOMEM);
            গচ্ছ fail;
        }

        যদি (অনুসন্ধান_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            প্রতি (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } অন্যথা {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(শূন্য**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_query_ranges(AVOptionRanges **ranges_arg, শূন্য *obj, ধ্রুব বর্ণ *চাবি, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক ret;
    ধ্রুব AVClass *c = *(AVClass**)obj;
    পূর্ণাঙ্ক (*callback)(AVOptionRanges **, শূন্য *obj, ধ্রুব বর্ণ *চাবি, পূর্ণাঙ্ক flags) = c->query_ranges;

    যদি (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, চাবি, flags);
    যদি (ret >= 0) {
        যদি (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_opt_query_ranges_default(AVOptionRanges **ranges_arg, শূন্য *obj, ধ্রুব বর্ণ *চাবি, পূর্ণাঙ্ক flags)
{
    AVOptionRanges *ranges = av_mallocz(পরিমাণ(*ranges));
    AVOptionRange **range_array = av_mallocz(পরিমাণ(শূন্য*));
    AVOptionRange *range = av_mallocz(পরিমাণ(*range));
    ধ্রুব AVOption *field = av_opt_find(obj, চাবি, রিক্ত, 0, flags);
    পূর্ণাঙ্ক ret;

    *ranges_arg = রিক্ত;

    যদি (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->মান_min = field->min;
    range->মান_max = field->max;

    বিকল্প (field->type) {
    পক্ষ AV_OPT_TYPE_BOOL:
    পক্ষ AV_OPT_TYPE_INT:
    পক্ষ AV_OPT_TYPE_UINT:
    পক্ষ AV_OPT_TYPE_INT64:
    পক্ষ AV_OPT_TYPE_UINT64:
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
    পক্ষ AV_OPT_TYPE_FLOAT:
    পক্ষ AV_OPT_TYPE_DOUBLE:
    পক্ষ AV_OPT_TYPE_DURATION:
    পক্ষ AV_OPT_TYPE_COLOR:
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->মান_min = -1;
        range->মান_max = INT_MAX;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->মান_min = 0;
        range->মান_max = INT_MAX/8;
        ভঙ্গ;
    পক্ষ AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->মান_min = 1;
        range->মান_max = INT_MAX;
        ভঙ্গ;
    স্বভাব:
        ret = AVERROR(ENOSYS);
        গচ্ছ fail;
    }

    *ranges_arg = ranges;
    প্রত্যাগম 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    প্রত্যাগম ret;
}

শূন্য av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    পূর্ণাঙ্ক i;
    AVOptionRanges *ranges = *rangesp;

    যদি (!ranges)
        প্রত্যাগম;

    প্রতি (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        যদি (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

পূর্ণাঙ্ক av_opt_is_set_to_default(শূন্য *obj, ধ্রুব AVOption *o)
{
    int64_t i64;
    দ্বিগুণ d;
    AVRational q;
    পূর্ণাঙ্ক ret, w, h;
    বর্ণ *str;
    শূন্য *dst;

    যদি (!o || !obj)
        প্রত্যাগম AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    যদি (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ধ্রুব বর্ণ *def = o->default_val.arr ? o->default_val.arr->def : রিক্ত;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        যদি (ret < 0)
            প্রত্যাগম ret;

        যদি (!!val != !!def)
            ret = 0;
        অন্যথা যদি (val)
            ret = !strcmp(val, def);
        অন্যথা
            ret = 1;

        av_freep(&val);

        প্রত্যাগম ret;
    }

    বিকল্প (o->type) {
    পক্ষ AV_OPT_TYPE_CONST:
        প্রত্যাগম 1;
    পক্ষ AV_OPT_TYPE_BOOL:
    পক্ষ AV_OPT_TYPE_FLAGS:
    পক্ষ AV_OPT_TYPE_PIXEL_FMT:
    পক্ষ AV_OPT_TYPE_SAMPLE_FMT:
    পক্ষ AV_OPT_TYPE_INT:
    পক্ষ AV_OPT_TYPE_UINT:
    পক্ষ AV_OPT_TYPE_DURATION:
    পক্ষ AV_OPT_TYPE_INT64:
    পক্ষ AV_OPT_TYPE_UINT64:
        read_সংখ্যা(o, dst, রিক্ত, রিক্ত, &i64);
        প্রত্যাগম o->default_val.i64 == i64;
    পক্ষ AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        যদি (o->default_val.str) {
            যদি ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                প্রত্যাগম ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        প্রত্যাগম ret;
    }
    পক্ষ AV_OPT_TYPE_STRING:
        str = *(বর্ণ **)dst;
        যদি (str == o->default_val.str) //2 NULLs
            প্রত্যাগম 1;
        যদি (!str || !o->default_val.str) //1 NULL
            প্রত্যাগম 0;
        প্রত্যাগম !strcmp(str, o->default_val.str);
    পক্ষ AV_OPT_TYPE_DOUBLE:
        d = *(দ্বিগুণ *)dst;
        প্রত্যাগম o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    পক্ষ AV_OPT_TYPE_FLOAT:
        d = *(ভিন্ন *)dst;
        প্রত্যাগম (ভিন্ন)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    পক্ষ AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        প্রত্যাগম !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    পক্ষ AV_OPT_TYPE_দ্বিমিক: {
        সংরচনা {
            uint8_t *data;
            পূর্ণাঙ্ক size;
        } tmp = {0};
        পূর্ণাঙ্ক opt_size = *(পূর্ণাঙ্ক *)((শূন্য **)dst + 1);
        শূন্য *opt_ptr = *(শূন্য **)dst;
        যদি (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            প্রত্যাগম 1;
        যদি (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            প্রত্যাগম 0;
        যদি (opt_size != strlen(o->default_val.str) / 2)
            প্রত্যাগম 0;
        ret = set_string_দ্বিমিক(রিক্ত, রিক্ত, o->default_val.str, &tmp.data);
        যদি (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        প্রত্যাগম ret;
    }
    পক্ষ AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = রিক্ত;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ধ্রুব AVDictionaryEntry *en1 = রিক্ত;
        ধ্রুব AVDictionaryEntry *en2 = রিক্ত;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        যদি (ret < 0) {
            av_dict_free(&dict1);
            প্রত্যাগম ret;
        }
        কুরু {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } যাবত্ (en1 && en2 && !strcmp(en1->চাবি, en2->চাবি) && !strcmp(en1->মান, en2->মান));
        av_dict_free(&dict1);
        প্রত্যাগম (!en1 && !en2);
    }
    পক্ষ AV_OPT_TYPE_IMAGE_SIZE:
        যদি (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        অন্যথা যদি ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            প্রত্যাগম ret;
        প্রত্যাগম (w == *(পূর্ণাঙ্ক *)dst) && (h == *((পূর্ণাঙ্ক *)dst+1));
    পক্ষ AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        যদি (o->default_val.str) {
            যদি ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                প্রত্যাগম ret;
        }
        প্রত্যাগম !av_cmp_q(*(AVRational*)dst, q);
    পক্ষ AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        যদি (o->default_val.str) {
            যদি ((ret = av_parse_color(color, o->default_val.str, -1, রিক্ত)) < 0)
                প্রত্যাগম ret;
        }
        প্রত্যাগম !memcmp(color, dst, পরিমাণ(color));
    }
    স্বভাব:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        ভঙ্গ;
    }
    প্রত্যাগম AVERROR_PATCHWELCOME;
}

পূর্ণাঙ্ক av_opt_is_set_to_default_by_name(শূন্য *obj, ধ্রুব বর্ণ *name, পূর্ণাঙ্ক অনুসন্ধান_flags)
{
    ধ্রুব AVOption *o;
    শূন্য *target;
    যদি (!obj)
        প্রত্যাগম AVERROR(EINVAL);
    o = av_opt_find2(obj, name, রিক্ত, 0, অনুসন্ধান_flags, &target);
    যদি (!o)
        প্রত্যাগম AVERROR_OPTION_NOT_FOUND;
    প্রত্যাগম av_opt_is_set_to_default(target, o);
}

স্থির পূর্ণাঙ্ক opt_serialize(শূন্য *obj, পূর্ণাঙ্ক opt_flags, পূর্ণাঙ্ক flags, পূর্ণাঙ্ক *cnt,
                         AVBPrint *bprint, ধ্রুব বর্ণ চাবি_val_sep, ধ্রুব বর্ণ pairs_sep)
{
    ধ্রুব AVOption *o = রিক্ত;
    শূন্য *child = রিক্ত;
    uint8_t *buf;
    পূর্ণাঙ্ক ret;
    ধ্রুব বর্ণ special_chars[] = {pairs_sep, চাবি_val_sep, '\0'};

    যদি (flags & AV_OPT_SERIALIZE_অনুসন্ধান_CHILDREN)
        যাবত্ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                চাবি_val_sep, pairs_sep);
            যদি (ret < 0)
                প্রত্যাগম ret;
        }

    যাবত্ (o = av_opt_next(obj, o)) {
        যদি (o->type == AV_OPT_TYPE_CONST)
            অনুবর্ত;
        যদি ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            যদি ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                যদি (o->flags == opt_flags)
                    অনুবর্ত;
            } অন্যথা যদি ((o->flags & opt_flags) == opt_flags)
                অনুবর্ত;
        } অন্যথা {
            যদি ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                অনুবর্ত;
            অন্যথা যদি (((o->flags & opt_flags) != opt_flags))
                অনুবর্ত;
        }
        যদি (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            অনুবর্ত;
        যদি ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, রিক্ত);
            প্রত্যাগম ret;
        }
        যদি (buf) {
            যদি ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &চাবি_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_opt_serialize(শূন্য *obj, পূর্ণাঙ্ক opt_flags, পূর্ণাঙ্ক flags, বর্ণ **buffer,
                     ধ্রুব বর্ণ চাবি_val_sep, ধ্রুব বর্ণ pairs_sep)
{
    AVBPrint bprint;
    পূর্ণাঙ্ক ret, cnt = 0;

    যদি (pairs_sep == '\0' || চাবি_val_sep == '\0' || pairs_sep == চাবি_val_sep ||
        pairs_sep == '\\' || চাবি_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        প্রত্যাগম AVERROR(EINVAL);
    }

    যদি (!obj || !buffer)
        প্রত্যাগম AVERROR(EINVAL);

    *buffer = রিক্ত;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        চাবি_val_sep, pairs_sep);
    যদি (ret < 0)
        প্রত্যাগম ret;

    ret = av_bprint_finalize(&bprint, buffer);
    যদি (ret < 0)
        প্রত্যাগম ret;
    প্রত্যাগম 0;
}
