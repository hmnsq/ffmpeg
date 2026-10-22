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

#அந்தர்பாவ "avutil.h"
#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "channel_layout.h"
#அந்தர்பாவ "dict.h"
#அந்தர்பாவ "eval.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "parseutils.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "mathematics.h"
#அந்தர்பாவ "opt.h"
#அந்தர்பாவ "samplefmt.h"
#அந்தர்பாவ "bprint.h"

#அந்தர்பாவ <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

மாறிலி AVOption *av_opt_next(மாறிலி வெறுமை *obj, மாறிலி AVOption *last)
{
    மாறிலி AVClass *class;
    எனில் (!obj)
        திரும்பு வெற்று;
    class = *(மாறிலி AVClass**)obj;
    எனில் (!last && class && class->option && class->option[0].name)
        திரும்பு class->option;
    எனில் (last && last[1].name)
        திரும்பு ++last;
    திரும்பு வெற்று;
}

நிலையான மாறிலி கட்டமைப்பு {
    size_t      size;
    மாறிலி எழுத்து *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { அளவு(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { அளவு(முழு),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { அளவு(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { அளவு(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { அளவு(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { அளவு(இரட்டை),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { அளவு(தசம),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { அளவு(எழுத்து *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { அளவு(AVRational),     "<rational>" },
    [AV_OPT_TYPE_இருமம்]        = { அளவு(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { அளவு(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { அளவு(முழு[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { அளவு(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { அளவு(எண்ணிக்கை AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { அளவு(எண்ணிக்கை AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { அளவு(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { அளவு(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { அளவு(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { அளவு(முழு),            "<boolean>" },
};

// option is plain old data
நிலையான முழு opt_is_pod(எண்ணிக்கை AVOptionType type)
{
    தேர்வு (type) {
    நிலை AV_OPT_TYPE_FLAGS:
    நிலை AV_OPT_TYPE_INT:
    நிலை AV_OPT_TYPE_INT64:
    நிலை AV_OPT_TYPE_DOUBLE:
    நிலை AV_OPT_TYPE_FLOAT:
    நிலை AV_OPT_TYPE_RATIONAL:
    நிலை AV_OPT_TYPE_UINT64:
    நிலை AV_OPT_TYPE_IMAGE_SIZE:
    நிலை AV_OPT_TYPE_PIXEL_FMT:
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
    நிலை AV_OPT_TYPE_VIDEO_RATE:
    நிலை AV_OPT_TYPE_DURATION:
    நிலை AV_OPT_TYPE_COLOR:
    நிலை AV_OPT_TYPE_BOOL:
    நிலை AV_OPT_TYPE_UINT:
        திரும்பு 1;
    }
    திரும்பு 0;
}

நிலையான uint8_t opt_array_sep(மாறிலி AVOption *o)
{
    மாறிலி AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    திரும்பு (d && d->sep) ? d->sep : ',';
}

நிலையான வெறுமை *opt_array_pelem(மாறிலி AVOption *o, வெறுமை *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    திரும்பு (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

நிலையான unsigned *opt_array_pcount(மாறிலி வெறுமை *parray)
{
    திரும்பு (unsigned *)((மாறிலி வெறுமை * மாறிலி *)parray + 1);
}

நிலையான வெறுமை opt_free_elem(எண்ணிக்கை AVOptionType type, வெறுமை *ptr)
{
    தேர்வு (TYPE_BASE(type)) {
    நிலை AV_OPT_TYPE_STRING:
    நிலை AV_OPT_TYPE_இருமம்:
        av_freep(ptr);
        நிறுத்து;

    நிலை AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        நிறுத்து;

    நிலை AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        நிறுத்து;

    இயல்பு:
        நிறுத்து;
    }
}

நிலையான வெறுமை opt_free_array(மாறிலி AVOption *o, வெறுமை *parray, unsigned *மொத்தம்)
{
    க்கு (unsigned i = 0; i < *மொத்தம்; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(வெறுமை **)parray, i));

    av_freep(parray);
    *மொத்தம் = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
நிலையான முழு opt_set_init(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags,
                        முழு require_type,
                        வெறுமை **ptgt, மாறிலி AVOption **po, வெறுமை **pdst)
{
    வெறுமை *logctx;
    மாறிலி AVOption *o;
    வெறுமை *tgt;

    o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &tgt);
    எனில் (!o || (!tgt && !(தேடல்_flags & AV_OPT_தேடல்_FAKE_OBJ)))
        திரும்பு AVERROR_OPTION_NOT_FOUND;

    எனில் (o->flags & AV_OPT_FLAG_READONLY)
        திரும்பு AVERROR(EINVAL);

    logctx = tgt ? obj : வெற்று;

    எனில் (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        திரும்பு AVERROR(EINVAL);
    }

    எனில் (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = வெற்று;
        மாறிலி AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(மாறிலி AVClass**)tgt;
        எனில் (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        எனில் (!state_flags && obj != tgt) {
            class = *(மாறிலி AVClass**)obj;
            எனில் (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        எனில் (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            திரும்பு AVERROR(EINVAL);
        }
    }

    எனில் (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    எனில் (po)
        *po   = o;
    எனில் (ptgt)
        *ptgt = tgt;
    எனில் (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : வெற்று;

    திரும்பு 0;
}

நிலையான AVRational double_to_rational(இரட்டை d)
{
     AVRational r = av_d2q(d, 1 << 24);
     எனில் ((!r.இலக்கம் || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     திரும்பு r;
}

நிலையான முழு read_எண்(மாறிலி AVOption *o, மாறிலி வெறுமை *dst, இரட்டை *இலக்கம், முழு *den, int64_t *intnum)
{
    தேர்வு (TYPE_BASE(o->type)) {
    நிலை AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned முழு*)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(எண்ணிக்கை AVPixelFormat *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(எண்ணிக்கை AVSampleFormat *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_BOOL:
    நிலை AV_OPT_TYPE_INT:
        *intnum = *(முழு *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_UINT:
        *intnum = *(unsigned முழு *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_DURATION:
    நிலை AV_OPT_TYPE_INT64:
    நிலை AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_FLOAT:
        *இலக்கம் = *(தசம *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_DOUBLE:
        *இலக்கம் = *(இரட்டை *)dst;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->இலக்கம்;
        *den    = ((AVRational *)dst)->den;
        திரும்பு 0;
    நிலை AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        திரும்பு 0;
    }
    திரும்பு AVERROR(EINVAL);
}

நிலையான முழு write_எண்(வெறுமை *obj, மாறிலி AVOption *o, வெறுமை *dst,
                        இரட்டை இலக்கம், முழு den, int64_t intnum,
                        முழு ignore_range)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    மாறிலி எண்ணிக்கை AVOptionType type = TYPE_BASE(o->type);

    எனில் (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < இலக்கம் * intnum || o->min * den > இலக்கம் * intnum)) {
        இலக்கம் = den ? இலக்கம் * intnum / den : (இலக்கம் && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               இலக்கம், o->name, o->min, o->max);
        திரும்பு AVERROR(ERANGE);
    }
    எனில் (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        இரட்டை d = இலக்கம்*intnum/den;
        எனில் (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   இலக்கம்*intnum/den, o->name);
            திரும்பு AVERROR(ERANGE);
        }
    }

    எனில் (!dst)
        திரும்பு 0;

    தேர்வு (type) {
    நிலை AV_OPT_TYPE_PIXEL_FMT:
        *(எண்ணிக்கை AVPixelFormat *)dst = llrint(இலக்கம் / den) * intnum;
        நிறுத்து;
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
        *(எண்ணிக்கை AVSampleFormat *)dst = llrint(இலக்கம் / den) * intnum;
        நிறுத்து;
    நிலை AV_OPT_TYPE_BOOL:
    நிலை AV_OPT_TYPE_FLAGS:
    நிலை AV_OPT_TYPE_INT:
    நிலை AV_OPT_TYPE_UINT:
        *(முழு *)dst = llrint(இலக்கம் / den) * intnum;
        நிறுத்து;
    நிலை AV_OPT_TYPE_DURATION:
    நிலை AV_OPT_TYPE_INT64:{
        இரட்டை d = இலக்கம் / den;
        எனில் (intnum == 1 && d == (இரட்டை)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } இல்லையெனில்
            *(int64_t *)dst = llrint(d) * intnum;
        நிறுத்து;}
    நிலை AV_OPT_TYPE_UINT64:{
        இரட்டை d = இலக்கம் / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        எனில் (intnum == 1 && d == (இரட்டை)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } இல்லையெனில் எனில் (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } இல்லையெனில் {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        நிறுத்து;}
    நிலை AV_OPT_TYPE_FLOAT:
        *(தசம *)dst = இலக்கம் * intnum / den;
        நிறுத்து;
    நிலை AV_OPT_TYPE_DOUBLE:
        *(இரட்டை    *)dst = இலக்கம் * intnum / den;
        நிறுத்து;
    நிலை AV_OPT_TYPE_RATIONAL:
    நிலை AV_OPT_TYPE_VIDEO_RATE:
        எனில் ((முழு) இலக்கம் == இலக்கம்)
            *(AVRational *)dst = (AVRational) { இலக்கம் *intnum, den };
        இல்லையெனில்
            *(AVRational *)dst = double_to_rational(இலக்கம் * intnum / den);
        நிறுத்து;
    இயல்பு:
        திரும்பு AVERROR(EINVAL);
    }
    திரும்பு 0;
}

நிலையான முழு hexchar2int(எழுத்து c) {
    எனில் (c >= '0' && c <= '9')
        திரும்பு c - '0';
    எனில் (c >= 'a' && c <= 'f')
        திரும்பு c - 'a' + 10;
    எனில் (c >= 'A' && c <= 'F')
        திரும்பு c - 'A' + 10;
    திரும்பு -1;
}

நிலையான முழு set_string_இருமம்(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t **dst)
{
    முழு *lendst;
    uint8_t *bin, *ptr;
    முழு len;

    எனில் (dst) {
        lendst = (முழு *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    எனில் (!val || !(len = strlen(val)))
        திரும்பு 0;

    எனில் (len & 1)
        திரும்பு AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    எனில் (!ptr)
        திரும்பு AVERROR(ENOMEM);
    போது (*val) {
        முழு a = hexchar2int(*val++);
        முழு b = hexchar2int(*val++);
        எனில் (a < 0 || b < 0) {
            av_free(bin);
            திரும்பு AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    எனில் (dst) {
        *dst    = bin;
        *lendst = len;
    } இல்லையெனில் {
        av_free(bin);
    }

    திரும்பு 0;
}

நிலையான முழு set_string(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t **dst)
{
    எனில் (!dst)
        திரும்பு 0;
    av_freep(dst);
    எனில் (!val)
        திரும்பு 0;
    *dst = av_strdup(val);
    திரும்பு *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

நிலையான முழு set_string_எண்(வெறுமை *obj, வெறுமை *target_obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, வெறுமை *dst)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    மாறிலி எண்ணிக்கை AVOptionType type = TYPE_BASE(o->type);
    முழு ret = 0;

    எனில் (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        முழு இலக்கம், den;
        எழுத்து c;
        எனில் (sscanf(val, "%d%*1[:/]%d%c", &இலக்கம், &den, &c) == 2) {
            எனில் ((ret = write_எண்(obj, o, dst, 1, den, இலக்கம், 0)) >= 0)
                திரும்பு ret;
            ret = 0;
        }
    }

    க்கு (;;) {
        முழு i = 0;
        எழுத்து buf[256];
        முழு cmd = 0;
        இரட்டை d;
        int64_t intnum = 1;

        எனில் (type == AV_OPT_TYPE_FLAGS) {
            எனில் (*val == '+' || *val == '-')
                cmd = *(val++);
            க்கு (; i < அளவு(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            முழு res;
            முழு ci = 0;
            இரட்டை const_மதிப்புகள்[64];
            மாறிலி எழுத்து * const_names[64];
            முழு தேடல்_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_தேடல்_CHILDREN : 0;
            மாறிலி AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, தேடல்_flags);
            எனில் (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                எனில் (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } இல்லையெனில் {
                எனில் (o->unit) {
                    க்கு (o_named = வெற்று; o_named = av_opt_next(target_obj, o_named); ) {
                        எனில் (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            எனில் (ci + 6 >= FF_ARRAY_ELEMS(const_மதிப்புகள்)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                திரும்பு AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_மதிப்புகள்[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_மதிப்புகள்[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_மதிப்புகள்[ci++] = o->max;
                const_names [ci  ] = "min";
                const_மதிப்புகள்[ci++] = o->min;
                const_names [ci  ] = "none";
                const_மதிப்புகள்[ci++] = 0;
                const_names [ci  ] = "all";
                const_மதிப்புகள்[ci++] = ~0;
                const_names [ci] = வெற்று;
                const_மதிப்புகள்[ci] = 0;

                res = av_கோவை_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_மதிப்புகள், வெற்று, வெற்று, வெற்று, வெற்று, வெற்று, 0, obj);
                எனில் (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    திரும்பு res;
                }
            }
        }
        எனில் (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned முழு*)dst;
            எனில் (cmd == '+')
                d = intnum | (int64_t)d;
            இல்லையெனில் எனில் (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        எனில் ((ret = write_எண்(obj, o, dst, d, 1, 1, 0)) < 0)
            திரும்பு ret;
        val += i;
        எனில் (!i || !*val)
            திரும்பு 0;
    }
}

நிலையான முழு set_string_image_size(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, முழு *dst)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    முழு tmp[2];
    முழு ret;

    எனில் (!val || !strcmp(val, "none")) {
        எனில் (dst) {
        dst[0] =
        dst[1] = 0;
        }
        திரும்பு 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    எனில் (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        திரும்பு ret;
    }
    எனில் (dst)
        memcpy(dst, tmp, அளவு(tmp));
    திரும்பு ret;
}

நிலையான முழு set_string_video_rate(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, AVRational *dst)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    AVRational tmp;
    முழு ret = av_parse_video_rate(&tmp, val);
    எனில் (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    எனில் (dst)
        *dst = tmp;
    திரும்பு ret;
}

நிலையான முழு set_string_color(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t *dst)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    முழு ret;

    எனில் (!val) {
        திரும்பு 0;
    } இல்லையெனில் {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        எனில் (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            திரும்பு ret;
        }
        எனில் (dst)
            memcpy(dst, tmp, அளவு(tmp));
        திரும்பு ret;
    }
    திரும்பு 0;
}

நிலையான மாறிலி எழுத்து *get_bool_name(முழு val)
{
    எனில் (val < 0)
        திரும்பு "auto";
    திரும்பு val ? "true" : "false";
}

நிலையான முழு set_string_bool(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, முழு *dst)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    முழு n;

    எனில் (!val)
        திரும்பு 0;

    எனில் (!strcmp(val, "auto")) {
        n = -1;
    } இல்லையெனில் எனில் (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } இல்லையெனில் எனில் (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } இல்லையெனில் {
        எழுத்து *end = வெற்று;
        n = strtol(val, &end, 10);
        எனில் (val + strlen(val) != end)
            செல் fail;
    }

    எனில் (n < o->min || n > o->max)
        செல் fail;

    எனில் (dst)
    *dst = n;
    திரும்பு 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    திரும்பு AVERROR(EINVAL);
}

நிலையான முழு set_string_fmt(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t *dst,
                          முழு fmt_nb, முழு ((*get_fmt)(மாறிலி எழுத்து *)), மாறிலி எழுத்து *desc,
                          எண்ணிக்கை AVOptionType type)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    முழு fmt, min, max;

    எனில் (!val || !strcmp(val, "none")) {
        fmt = -1;
    } இல்லையெனில் {
        fmt = get_fmt(val);
        எனில் (fmt == -1) {
            எழுத்து *tail;
            fmt = strtol(val, &tail, 0);
            எனில் (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                திரும்பு AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    எனில்(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    எனில் (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        திரும்பு AVERROR(ERANGE);
    }

    எனில் (dst)
    தேர்வு (type) {
    நிலை AV_OPT_TYPE_PIXEL_FMT:  *(எண்ணிக்கை AVPixelFormat *)dst = fmt; நிறுத்து;
    நிலை AV_OPT_TYPE_SAMPLE_FMT: *(எண்ணிக்கை AVSampleFormat*)dst = fmt; நிறுத்து;
    இயல்பு: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    திரும்பு 0;
}

நிலையான முழு get_pix_fmt(மாறிலி எழுத்து *name)
{
    திரும்பு av_get_pix_fmt(name);
}

நிலையான முழு set_string_pixel_fmt(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t *dst)
{
    திரும்பு set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

நிலையான முழு get_sample_fmt(மாறிலி எழுத்து *name)
{
    திரும்பு av_get_sample_fmt(name);
}

நிலையான முழு set_string_sample_fmt(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t *dst)
{
    திரும்பு set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

நிலையான முழு set_string_dict(வெறுமை *obj, மாறிலி AVOption *o, மாறிலி எழுத்து *val, uint8_t **dst)
{
    AVDictionary *options = வெற்று;

    எனில் (val) {
        முழு ret = av_dict_parse_string(&options, val, "=", ":", 0);
        எனில் (ret < 0) {
            av_dict_free(&options);
            திரும்பு ret;
        }
    }

    எனில் (!dst) {
        av_dict_free(&options);
        திரும்பு 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    திரும்பு 0;
}

நிலையான முழு set_string_channel_layout(வெறுமை *obj, மாறிலி AVOption *o,
                                     மாறிலி எழுத்து *val, வெறுமை *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    முழு ret;
    எனில் (dst)
    av_channel_layout_uninit(channel_layout);
    இல்லையெனில்
        channel_layout = &tmp;
    எனில் (!val)
        திரும்பு 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    எனில் (ret < 0)
        திரும்பு ret;
    எனில் (!dst)
        av_channel_layout_uninit(channel_layout);
    திரும்பு 0;
}

நிலையான முழு opt_set_elem(வெறுமை *obj, வெறுமை *target_obj, மாறிலி AVOption *o,
                        மாறிலி எழுத்து *val, வெறுமை *dst)
{
    வெறுமை *logctx = dst ? obj : வெற்று;
    மாறிலி எண்ணிக்கை AVOptionType type = TYPE_BASE(o->type);
    முழு ret;

    எனில் (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        திரும்பு AVERROR(EINVAL);

    தேர்வு (type) {
    நிலை AV_OPT_TYPE_BOOL:
        திரும்பு set_string_bool(obj, o, val, dst);
    நிலை AV_OPT_TYPE_STRING:
        திரும்பு set_string(obj, o, val, dst);
    நிலை AV_OPT_TYPE_இருமம்:
        திரும்பு set_string_இருமம்(obj, o, val, dst);
    நிலை AV_OPT_TYPE_FLAGS:
    நிலை AV_OPT_TYPE_INT:
    நிலை AV_OPT_TYPE_UINT:
    நிலை AV_OPT_TYPE_INT64:
    நிலை AV_OPT_TYPE_UINT64:
    நிலை AV_OPT_TYPE_FLOAT:
    நிலை AV_OPT_TYPE_DOUBLE:
    நிலை AV_OPT_TYPE_RATIONAL:
        திரும்பு set_string_எண்(obj, target_obj, o, val, dst);
    நிலை AV_OPT_TYPE_IMAGE_SIZE:
        திரும்பு set_string_image_size(obj, o, val, dst);
    நிலை AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        எனில் (ret < 0)
            திரும்பு ret;
        திரும்பு write_எண்(obj, o, dst, 1, tmp.den, tmp.இலக்கம், 0);
    }
    நிலை AV_OPT_TYPE_PIXEL_FMT:
        திரும்பு set_string_pixel_fmt(obj, o, val, dst);
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
        திரும்பு set_string_sample_fmt(obj, o, val, dst);
    நிலை AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            எனில் (val) {
                எனில் ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    திரும்பு ret;
                }
            }
            எனில் (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                திரும்பு AVERROR(ERANGE);
            }
            எனில் (dst)
            *(int64_t *)dst = usecs;
            திரும்பு 0;
        }
    நிலை AV_OPT_TYPE_COLOR:
        திரும்பு set_string_color(obj, o, val, dst);
    நிலை AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        எனில் (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        திரும்பு ret;
    நிலை AV_OPT_TYPE_DICT:
        திரும்பு set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    திரும்பு AVERROR(EINVAL);
}

நிலையான முழு opt_set_array(வெறுமை *obj, வெறுமை *target_obj, மாறிலி AVOption *o,
                         மாறிலி எழுத்து *val, வெறுமை *dst)
{
    மாறிலி AVOptionArrayDef *arr = o->default_val.arr;
    மாறிலி size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    மாறிலி uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = வெற்று;

    வெறுமை      *logctx = dst ? obj : வெற்று;
    வெறுமை       *elems = வெற்று;
    unsigned nb_elems = 0;
    முழு ret;

    எனில் (val && *val) {
        str = av_malloc(strlen(val) + 1);
        எனில் (!str)
            திரும்பு AVERROR(ENOMEM);
    }

    // split and unescape the string
    போது (val && *val) {
        uint8_t *p = str;
        வெறுமை *tmp;

        எனில் (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            செல் fail;
        }

        க்கு (; *val; val++, p++) {
            எனில் (*val == '\\' && val[1])
                val++;
            இல்லையெனில் எனில் (*val == sep) {
                val++;
                நிறுத்து;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        எனில் (!tmp) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        எனில் (ret < 0)
            செல் fail;
        nb_elems++;
    }
    av_freep(&str);

    எனில் (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    எனில் (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        செல் fail;
    }

    எனில் (dst) {
    *((வெறுமை **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } இல்லையெனில்
        opt_free_array(o, &elems, &nb_elems);

    திரும்பு 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    திரும்பு ret;
}

முழு av_opt_set(வெறுமை *obj, மாறிலி எழுத்து *name, மாறிலி எழுத்து *val, முழு தேடல்_flags)
{
    வெறுமை *dst, *target_obj;
    மாறிலி AVOption *o;
    முழு ret;

    ret = opt_set_init(obj, name, தேடல்_flags, 0, &target_obj, &o, &dst);
    எனில் (ret < 0)
        திரும்பு ret;

    திரும்பு ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_எண்(name, opttype, vartype)                         \
முழு av_opt_eval_ ## name(வெறுமை *obj, மாறிலி AVOption *o,                  \
                         மாறிலி எழுத்து *val, vartype *name ## _out)        \
{                                                                       \
    எனில் (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        திரும்பு AVERROR(EINVAL);                                         \
    திரும்பு set_string_எண்(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_எண்(flags,  AV_OPT_TYPE_FLAGS,    முழு)
OPT_EVAL_எண்(முழு,    AV_OPT_TYPE_INT,      முழு)
OPT_EVAL_எண்(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_எண்(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_எண்(தசம,  AV_OPT_TYPE_FLOAT,    தசம)
OPT_EVAL_எண்(இரட்டை, AV_OPT_TYPE_DOUBLE,   இரட்டை)
OPT_EVAL_எண்(q,      AV_OPT_TYPE_RATIONAL, AVRational)

நிலையான முழு set_எண்(வெறுமை *obj, மாறிலி எழுத்து *name, இரட்டை இலக்கம், முழு den, int64_t intnum,
                      முழு தேடல்_flags, முழு require_type)
{
    வெறுமை *dst;
    மாறிலி AVOption *o;
    முழு ret;

    ret = opt_set_init(obj, name, தேடல்_flags, require_type, வெற்று, &o, &dst);
    எனில் (ret < 0)
        திரும்பு ret;
    எனில் (dst)
        ret = write_எண்(obj, o, dst, இலக்கம், den, intnum, 0);

    திரும்பு ret;
}

முழு av_opt_set_int(வெறுமை *obj, மாறிலி எழுத்து *name, int64_t val, முழு தேடல்_flags)
{
    திரும்பு set_எண்(obj, name, 1, 1, val, தேடல்_flags, 0);
}

முழு av_opt_set_double(வெறுமை *obj, மாறிலி எழுத்து *name, இரட்டை val, முழு தேடல்_flags)
{
    திரும்பு set_எண்(obj, name, val, 1, 1, தேடல்_flags, 0);
}

முழு av_opt_set_q(வெறுமை *obj, மாறிலி எழுத்து *name, AVRational val, முழு தேடல்_flags)
{
    திரும்பு set_எண்(obj, name, val.இலக்கம், val.den, 1, தேடல்_flags, 0);
}

முழு av_opt_set_bin(வெறுமை *obj, மாறிலி எழுத்து *name, மாறிலி uint8_t *val, முழு len, முழு தேடல்_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    முழு *lendst;
    முழு ret;

    ret = opt_set_init(obj, name, தேடல்_flags, AV_OPT_TYPE_இருமம்,
                       வெற்று, வெற்று, (வெறுமை**)&dst);
    எனில் (ret < 0)
        திரும்பு ret;

    எனில் (dst) {
    ptr = len ? av_malloc(len) : வெற்று;
    எனில் (len && !ptr)
        திரும்பு AVERROR(ENOMEM);

    lendst = (முழு *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    எனில் (len)
        memcpy(ptr, val, len);
    }

    திரும்பு 0;
}

முழு av_opt_set_image_size(வெறுமை *obj, மாறிலி எழுத்து *name, முழு w, முழு h, முழு தேடல்_flags)
{
    மாறிலி AVOption *o;
    வெறுமை *logctx;
    முழு *dst;
    முழு ret;

    ret = opt_set_init(obj, name, தேடல்_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       வெற்று, &o, (வெறுமை**)&dst);
    எனில் (ret < 0)
        திரும்பு ret;

    logctx = dst ? obj : வெற்று;

    எனில் (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        திரும்பு AVERROR(EINVAL);
    }

    எனில் (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    திரும்பு 0;
}

முழு av_opt_set_video_rate(வெறுமை *obj, மாறிலி எழுத்து *name, AVRational val, முழு தேடல்_flags)
{
    திரும்பு set_எண்(obj, name, val.இலக்கம், val.den, 1, தேடல்_flags, AV_OPT_TYPE_VIDEO_RATE);
}

நிலையான முழு set_format(வெறுமை *obj, மாறிலி எழுத்து *name, முழு fmt, முழு தேடல்_flags,
                      எண்ணிக்கை AVOptionType type, மாறிலி எழுத்து *desc, முழு nb_fmts)
{
    மாறிலி AVOption *o;
    வெறுமை *logctx;
    முழு *dst;
    முழு min, max, ret;

    ret = opt_set_init(obj, name, தேடல்_flags, type, வெற்று, &o, (வெறுமை**)&dst);
    எனில் (ret < 0)
        திரும்பு ret;

    logctx = dst ? obj : வெற்று;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    எனில் (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        திரும்பு AVERROR(ERANGE);
    }
    எனில் (dst)
    *dst = fmt;
    திரும்பு 0;
}

முழு av_opt_set_pixel_fmt(வெறுமை *obj, மாறிலி எழுத்து *name, எண்ணிக்கை AVPixelFormat fmt, முழு தேடல்_flags)
{
    திரும்பு set_format(obj, name, fmt, தேடல்_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

முழு av_opt_set_sample_fmt(வெறுமை *obj, மாறிலி எழுத்து *name, எண்ணிக்கை AVSampleFormat fmt, முழு தேடல்_flags)
{
    திரும்பு set_format(obj, name, fmt, தேடல்_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

முழு av_opt_set_dict_val(வெறுமை *obj, மாறிலி எழுத்து *name, மாறிலி AVDictionary *val,
                        முழு தேடல்_flags)
{
    AVDictionary **dst;
    முழு ret;

    ret = opt_set_init(obj, name, தேடல்_flags, AV_OPT_TYPE_DICT, வெற்று, வெற்று,
                       (வெறுமை**)&dst);
    எனில் (ret < 0)
        திரும்பு ret;

    எனில் (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    திரும்பு ret;
}

முழு av_opt_set_chlayout(வெறுமை *obj, மாறிலி எழுத்து *name,
                        மாறிலி AVChannelLayout *channel_layout,
                        முழு தேடல்_flags)
{
    AVChannelLayout *dst;
    முழு ret;

    ret = opt_set_init(obj, name, தேடல்_flags, AV_OPT_TYPE_CHLAYOUT, வெற்று, வெற்று,
                       (வெறுமை**)&dst);
    எனில் (ret < 0)
        திரும்பு ret;

    எனில் (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    திரும்பு ret;
}

நிலையான வெறுமை format_duration(எழுத்து *buf, size_t size, int64_t d)
{
    எழுத்து *e;

    av_assert0(size >= 25);
    எனில் (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    எனில் (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    இல்லையெனில் எனில் (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    இல்லையெனில் எனில் (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (முழு)((d / 60000000) % 60),
                 (முழு)((d / 1000000) % 60),
                 (முழு)(d % 1000000));
    இல்லையெனில் எனில் (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (முழு)(d / 60000000),
                 (முழு)((d / 1000000) % 60),
                 (முழு)(d % 1000000));
    இல்லையெனில்
        snprintf(buf, size, "%d.%06d",
                 (முழு)(d / 1000000),
                 (முழு)(d % 1000000));
    e = buf + strlen(buf);
    போது (e > buf && e[-1] == '0')
        *(--e) = 0;
    எனில் (e > buf && e[-1] == '.')
        *(--e) = 0;
}

நிலையான முழு opt_get_elem(மாறிலி AVOption *o, uint8_t **pbuf, size_t buf_len,
                        மாறிலி வெறுமை *dst, முழு தேடல்_flags)
{
    முழு ret;

    தேர்வு (TYPE_BASE(o->type)) {
    நிலை AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(முழு *)dst));
        நிறுத்து;
    நிலை AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(முழு *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(முழு *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(தசம *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(இரட்டை *)dst);
        நிறுத்து;
    நிலை AV_OPT_TYPE_VIDEO_RATE:
    நிலை AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->இலக்கம், ((AVRational *)dst)->den);
        நிறுத்து;
    நிலை AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        நிறுத்து;
    நிலை AV_OPT_TYPE_STRING:
        எனில் (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } இல்லையெனில் எனில் (தேடல்_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = வெற்று;
            திரும்பு 0;
        } இல்லையெனில் {
            *pbuf = av_strdup("");
        }
        திரும்பு *pbuf ? 0 : AVERROR(ENOMEM);
    நிலை AV_OPT_TYPE_இருமம்: {
        மாறிலி uint8_t *bin;
        முழு len;

        எனில் (!*(uint8_t **)dst && (தேடல்_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = வெற்று;
            திரும்பு 0;
        }
        len = *(முழு *)(((uint8_t *)dst) + அளவு(uint8_t *));
        எனில் ((uint64_t)len * 2 + 1 > INT_MAX)
            திரும்பு AVERROR(EINVAL);
        எனில் (!(*pbuf = av_malloc(len * 2 + 1)))
            திரும்பு AVERROR(ENOMEM);
        எனில் (!len) {
            *pbuf[0] = '\0';
            திரும்பு 0;
        }
        bin = *(uint8_t **)dst;
        க்கு (முழு i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        திரும்பு 0;
    }
    நிலை AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((முழு *)dst)[0], ((முழு *)dst)[1]);
        நிறுத்து;
    நிலை AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (எழுத்து *)av_x_if_null(av_get_pix_fmt_name(*(எண்ணிக்கை AVPixelFormat *)dst), "none"));
        நிறுத்து;
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (எழுத்து *)av_x_if_null(av_get_sample_fmt_name(*(எண்ணிக்கை AVSampleFormat *)dst), "none"));
        நிறுத்து;
    நிலை AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        நிறுத்து;
    }
    நிலை AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (முழு)((uint8_t *)dst)[0], (முழு)((uint8_t *)dst)[1],
                       (முழு)((uint8_t *)dst)[2], (முழு)((uint8_t *)dst)[3]);
        நிறுத்து;
    நிலை AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        நிறுத்து;
    நிலை AV_OPT_TYPE_DICT:
        எனில் (!*(AVDictionary **)dst && (தேடல்_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = வெற்று;
            திரும்பு 0;
        }
        திரும்பு av_dict_get_string(*(AVDictionary **)dst, (எழுத்து **)pbuf, '=', ':');
    இயல்பு:
        திரும்பு AVERROR(EINVAL);
    }

    திரும்பு ret;
}

நிலையான முழு opt_get_array(மாறிலி AVOption *o, வெறுமை *dst, uint8_t **out_val)
{
    மாறிலி unsigned மொத்தம் = *opt_array_pcount(dst);
    மாறிலி uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = வெற்று;
    size_t   str_len = 0;
    முழு ret;

    *out_val = வெற்று;

    க்கு (unsigned i = 0; i < மொத்தம்; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, அளவு(buf),
                           opt_array_pelem(o, *(வெறுமை **)dst, i), 0);
        எனில் (ret < 0)
            செல் fail;

        out_len = strlen(out);
        எனில் (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            செல் fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        எனில் (ret < 0)
            செல் fail;

        // add separator if needed
        எனில் (i)
            str[str_len++] = sep;

        // escape the element
        க்கு (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            எனில் (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        எனில் (out != buf)
            av_freep(&out);
        எனில் (ret < 0) {
            av_freep(&str);
            திரும்பு ret;
        }
    }

    *out_val = str;

    திரும்பு 0;
}

முழு av_opt_get(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, uint8_t **out_val)
{
    வெறுமை *dst, *target_obj;
    மாறிலி AVOption *o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    uint8_t *out, buf[128];
    முழு ret;

    எனில் (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        திரும்பு AVERROR_OPTION_NOT_FOUND;

    எனில் (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    எனில் (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        எனில் (ret < 0)
            திரும்பு ret;
        எனில் (!*out_val && !(தேடல்_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            எனில் (!*out_val)
               திரும்பு AVERROR(ENOMEM);
        }
        திரும்பு 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, அளவு(buf), dst, தேடல்_flags);
    எனில் (ret < 0)
        திரும்பு ret;
    எனில் (out != buf) {
        *out_val = out;
        திரும்பு 0;
    }

    எனில் (ret >= அளவு(buf))
        திரும்பு AVERROR(EINVAL);
    *out_val = av_strdup(out);
    திரும்பு *out_val ? 0 : AVERROR(ENOMEM);
}

நிலையான முழு get_எண்(வெறுமை *obj, மாறிலி எழுத்து *name, இரட்டை *இலக்கம், முழு *den, int64_t *intnum,
                      முழு தேடல்_flags)
{
    வெறுமை *dst, *target_obj;
    மாறிலி AVOption *o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        திரும்பு AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    திரும்பு read_எண்(o, dst, இலக்கம், den, intnum);
}

முழு av_opt_get_int(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    இரட்டை இலக்கம் = 1;
    முழு ret, den = 1;

    எனில் ((ret = get_எண்(obj, name, &இலக்கம், &den, &intnum, தேடல்_flags)) < 0)
        திரும்பு ret;
    எனில் (இலக்கம் == den)
        *out_val = intnum;
    இல்லையெனில்
        *out_val = இலக்கம் * intnum / den;
    திரும்பு 0;
}

முழு av_opt_get_double(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, இரட்டை *out_val)
{
    int64_t intnum = 1;
    இரட்டை இலக்கம் = 1;
    முழு ret, den = 1;

    எனில் ((ret = get_எண்(obj, name, &இலக்கம், &den, &intnum, தேடல்_flags)) < 0)
        திரும்பு ret;
    *out_val = இலக்கம் * intnum / den;
    திரும்பு 0;
}

முழு av_opt_get_q(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    இரட்டை இலக்கம் = 1;
    முழு ret, den = 1;

    எனில் ((ret = get_எண்(obj, name, &இலக்கம், &den, &intnum, தேடல்_flags)) < 0)
        திரும்பு ret;

    எனில் (இலக்கம் == 1.0 && (முழு)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    இல்லையெனில்
        *out_val = double_to_rational(இலக்கம்*intnum/den);
    திரும்பு 0;
}

முழு av_opt_get_image_size(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, முழு *w_out, முழு *h_out)
{
    வெறுமை *dst, *target_obj;
    மாறிலி AVOption *o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        திரும்பு AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    எனில் (w_out) *w_out = *(முழு *)dst;
    எனில் (h_out) *h_out = *((முழு *)dst+1);
    திரும்பு 0;
}

முழு av_opt_get_video_rate(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, AVRational *out_val)
{
    திரும்பு av_opt_get_q(obj, name, தேடல்_flags, out_val);
}

நிலையான முழு get_format(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, வெறுமை *out_fmt,
                      எண்ணிக்கை AVOptionType type, மாறிலி எழுத்து *desc)
{
    வெறுமை *dst, *target_obj;
    மாறிலி AVOption *o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        திரும்பு AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    எனில் (type == AV_OPT_TYPE_PIXEL_FMT)
        *(எண்ணிக்கை AVPixelFormat *)out_fmt = *(எண்ணிக்கை AVPixelFormat *)dst;
    இல்லையெனில்
        *(எண்ணிக்கை AVSampleFormat*)out_fmt = *(எண்ணிக்கை AVSampleFormat*)dst;

    திரும்பு 0;
}

முழு av_opt_get_pixel_fmt(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, எண்ணிக்கை AVPixelFormat *out_fmt)
{
    திரும்பு get_format(obj, name, தேடல்_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

முழு av_opt_get_sample_fmt(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, எண்ணிக்கை AVSampleFormat *out_fmt)
{
    திரும்பு get_format(obj, name, தேடல்_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

முழு av_opt_get_chlayout(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, AVChannelLayout *cl)
{
    வெறுமை *dst, *target_obj;
    மாறிலி AVOption *o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        திரும்பு AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    திரும்பு av_channel_layout_copy(cl, dst);
}

முழு av_opt_get_dict_val(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags, AVDictionary **out_val)
{
    வெறுமை *target_obj;
    AVDictionary *src;
    மாறிலி AVOption *o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);

    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (o->type != AV_OPT_TYPE_DICT)
        திரும்பு AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    திரும்பு av_dict_copy(out_val, src, 0);
}

முழு av_opt_flag_is_set(வெறுமை *obj, மாறிலி எழுத்து *field_name, மாறிலி எழுத்து *flag_name)
{
    மாறிலி AVOption *field = av_opt_find(obj, field_name, வெற்று, 0, 0);
    மாறிலி AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : வெற்று, 0, 0);
    int64_t res;

    எனில் (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        திரும்பு 0;
    திரும்பு res & flag->default_val.i64;
}

நிலையான வெறுமை log_int_மதிப்பு(வெறுமை *av_log_obj, முழு level, int64_t i)
{
    எனில் (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } இல்லையெனில் எனில் (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } இல்லையெனில் எனில் (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } இல்லையெனில் எனில் (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } இல்லையெனில் எனில் (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } இல்லையெனில் {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

நிலையான வெறுமை log_மதிப்பு(வெறுமை *av_log_obj, முழு level, இரட்டை d)
{
    எனில்      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } இல்லையெனில் எனில் (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } இல்லையெனில் எனில் (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } இல்லையெனில் எனில் (d == (இரட்டை)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } இல்லையெனில் எனில் (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } இல்லையெனில் எனில் (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } இல்லையெனில் எனில் (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } இல்லையெனில் எனில் (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } இல்லையெனில் எனில் (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } இல்லையெனில் எனில் (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } இல்லையெனில் எனில் (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } இல்லையெனில் எனில் (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } இல்லையெனில் எனில் (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } இல்லையெனில் {
        av_log(av_log_obj, level, "%g", d);
    }
}

நிலையான மாறிலி எழுத்து *get_opt_const_name(வெறுமை *obj, மாறிலி எழுத்து *unit, int64_t மதிப்பு)
{
    மாறிலி AVOption *opt = வெற்று;

    எனில் (!unit)
        திரும்பு வெற்று;
    போது ((opt = av_opt_next(obj, opt)))
        எனில் (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == மதிப்பு)
            திரும்பு opt->name;
    திரும்பு வெற்று;
}

நிலையான எழுத்து *get_opt_flags_string(வெறுமை *obj, மாறிலி எழுத்து *unit, int64_t மதிப்பு)
{
    மாறிலி AVOption *opt = வெற்று;
    எழுத்து flags[512];

    flags[0] = 0;
    எனில் (!unit)
        திரும்பு வெற்று;
    போது ((opt = av_opt_next(obj, opt))) {
        எனில் (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & மதிப்பு) {
            எனில் (flags[0])
                av_strlcatf(flags, அளவு(flags), "+");
            av_strlcatf(flags, அளவு(flags), "%s", opt->name);
        }
    }
    எனில் (flags[0])
        திரும்பு av_strdup(flags);
    திரும்பு வெற்று;
}

நிலையான வெறுமை log_type(வெறுமை *av_log_obj, மாறிலி AVOption *o,
                     எண்ணிக்கை AVOptionType parent_type)
{
    மாறிலி எண்ணிக்கை AVOptionType type = TYPE_BASE(o->type);

    எனில் (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    இல்லையெனில் எனில் (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        எனில் (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        இல்லையெனில்
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    இல்லையெனில்
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

நிலையான வெறுமை log_default(வெறுமை *obj, வெறுமை *av_log_obj, மாறிலி AVOption *opt)
{
    எனில் (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_இருமம்)
        திரும்பு;
    எனில் ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        திரும்பு;

    எனில் (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        மாறிலி AVOptionArrayDef *arr = opt->default_val.arr;
        எனில் (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        திரும்பு;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    தேர்வு (opt->type) {
    நிலை AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        நிறுத்து;
    நிலை AV_OPT_TYPE_FLAGS: {
        எழுத்து *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        எனில் (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } இல்லையெனில் {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        நிறுத்து;
    }
    நிலை AV_OPT_TYPE_DURATION: {
        எழுத்து buf[25];
        format_duration(buf, அளவு(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        நிறுத்து;
    }
    நிலை AV_OPT_TYPE_UINT:
    நிலை AV_OPT_TYPE_INT:
    நிலை AV_OPT_TYPE_UINT64:
    நிலை AV_OPT_TYPE_INT64: {
        மாறிலி எழுத்து *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        எனில் (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        இல்லையெனில்
            log_int_மதிப்பு(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        நிறுத்து;
    }
    நிலை AV_OPT_TYPE_DOUBLE:
    நிலை AV_OPT_TYPE_FLOAT:
        log_மதிப்பு(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        நிறுத்து;
    நிலை AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.இலக்கம், q.den); }
        நிறுத்து;
    நிலை AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (எழுத்து *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        நிறுத்து;
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (எழுத்து *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        நிறுத்து;
    நிலை AV_OPT_TYPE_COLOR:
    நிலை AV_OPT_TYPE_IMAGE_SIZE:
    நிலை AV_OPT_TYPE_STRING:
    நிலை AV_OPT_TYPE_DICT:
    நிலை AV_OPT_TYPE_VIDEO_RATE:
    நிலை AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        நிறுத்து;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

நிலையான வெறுமை opt_list(வெறுமை *obj, வெறுமை *av_log_obj, மாறிலி எழுத்து *unit,
                     முழு req_flags, முழு rej_flags, எண்ணிக்கை AVOptionType parent_type)
{
    மாறிலி AVOption *opt = வெற்று;
    AVOptionRanges *r;
    முழு i;

    போது ((opt = av_opt_next(obj, opt))) {
        எனில் (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            தொடர்;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        எனில் (!unit && opt->type == AV_OPT_TYPE_CONST)
            தொடர்;
        இல்லையெனில் எனில் (unit && opt->type != AV_OPT_TYPE_CONST)
            தொடர்;
        இல்லையெனில் எனில் (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            தொடர்;
        இல்லையெனில் எனில் (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        இல்லையெனில்
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

        எனில் (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        எனில் (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_தேடல்_FAKE_OBJ) >= 0) {
            தேர்வு (opt->type) {
            நிலை AV_OPT_TYPE_INT:
            நிலை AV_OPT_TYPE_UINT:
            நிலை AV_OPT_TYPE_INT64:
            நிலை AV_OPT_TYPE_UINT64:
            நிலை AV_OPT_TYPE_DOUBLE:
            நிலை AV_OPT_TYPE_FLOAT:
            நிலை AV_OPT_TYPE_RATIONAL:
                க்கு (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_மதிப்பு(av_log_obj, AV_LOG_INFO, r->range[i]->மதிப்பு_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_மதிப்பு(av_log_obj, AV_LOG_INFO, r->range[i]->மதிப்பு_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                நிறுத்து;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        எனில் (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

முழு av_opt_show2(வெறுமை *obj, வெறுமை *av_log_obj, முழு req_flags, முழு rej_flags)
{
    எனில் (!obj)
        திரும்பு -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, வெற்று, req_flags, rej_flags, -1);

    திரும்பு 0;
}

வெறுமை av_opt_set_defaults(வெறுமை *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

வெறுமை av_opt_set_defaults2(வெறுமை *s, முழு mask, முழு flags)
{
    மாறிலி AVOption *opt = வெற்று;
    போது ((opt = av_opt_next(s, opt))) {
        வெறுமை *dst = ((uint8_t*)s) + opt->offset;

        எனில் ((opt->flags & mask) != flags)
            தொடர்;

        எனில் (opt->flags & AV_OPT_FLAG_READONLY)
            தொடர்;

        எனில் (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            மாறிலி AVOptionArrayDef *arr = opt->default_val.arr;
            மாறிலி எழுத்து              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            எனில் (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            தொடர்;
        }

        தேர்வு (opt->type) {
            நிலை AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                நிறுத்து;
            நிலை AV_OPT_TYPE_BOOL:
            நிலை AV_OPT_TYPE_FLAGS:
            நிலை AV_OPT_TYPE_INT:
            நிலை AV_OPT_TYPE_UINT:
            நிலை AV_OPT_TYPE_INT64:
            நிலை AV_OPT_TYPE_UINT64:
            நிலை AV_OPT_TYPE_DURATION:
            நிலை AV_OPT_TYPE_PIXEL_FMT:
            நிலை AV_OPT_TYPE_SAMPLE_FMT:
                write_எண்(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                நிறுத்து;
            நிலை AV_OPT_TYPE_DOUBLE:
            நிலை AV_OPT_TYPE_FLOAT: {
                இரட்டை val;
                val = opt->default_val.dbl;
                write_எண்(s, opt, dst, val, 1, 1, 1);
            }
            நிறுத்து;
            நிலை AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_எண்(s, opt, dst, 1, val.den, val.இலக்கம், 1);
            }
            நிறுத்து;
            நிலை AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                நிறுத்து;
            நிலை AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                நிறுத்து;
            நிலை AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                நிறுத்து;
            நிலை AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                நிறுத்து;
            நிலை AV_OPT_TYPE_இருமம்:
                set_string_இருமம்(s, opt, opt->default_val.str, dst);
                நிறுத்து;
            நிலை AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                நிறுத்து;
            நிலை AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                நிறுத்து;
        இயல்பு:
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
நிலையான முழு parse_சாவி_மதிப்பு_pair(வெறுமை *ctx, மாறிலி எழுத்து **buf,
                                மாறிலி எழுத்து *சாவி_val_sep, மாறிலி எழுத்து *pairs_sep)
{
    எழுத்து *சாவி = av_get_token(buf, சாவி_val_sep);
    எழுத்து *val;
    முழு ret;

    எனில் (!சாவி)
        திரும்பு AVERROR(ENOMEM);

    எனில் (*சாவி && strspn(*buf, சாவி_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        எனில் (!val) {
            av_freep(&சாவி);
            திரும்பு AVERROR(ENOMEM);
        }
    } இல்லையெனில் {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", சாவி);
        av_free(சாவி);
        திரும்பு AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", சாவி, val);

    ret = av_opt_set(ctx, சாவி, val, AV_OPT_தேடல்_CHILDREN);
    எனில் (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", சாவி);

    av_free(சாவி);
    av_free(val);
    திரும்பு ret;
}

முழு av_set_options_string(வெறுமை *ctx, மாறிலி எழுத்து *opts,
                          மாறிலி எழுத்து *சாவி_val_sep, மாறிலி எழுத்து *pairs_sep)
{
    முழு ret, மொத்தம் = 0;

    எனில் (!opts)
        திரும்பு 0;

    போது (*opts) {
        எனில் ((ret = parse_சாவி_மதிப்பு_pair(ctx, &opts, சாவி_val_sep, pairs_sep)) < 0)
            திரும்பு ret;
        மொத்தம்++;

        எனில் (*opts)
            opts++;
    }

    திரும்பு மொத்தம்;
}

#define WHITESPACES " \n\t\r"

நிலையான முழு is_சாவி_char(எழுத்து c)
{
    திரும்பு (unsigned)((c | 32) - 'a') < 26 ||
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
நிலையான முழு get_சாவி(மாறிலி எழுத்து **ropts, மாறிலி எழுத்து *delim, எழுத்து **rkey)
{
    மாறிலி எழுத்து *opts = *ropts;
    மாறிலி எழுத்து *சாவி_start, *சாவி_end;

    சாவி_start = opts += strspn(opts, WHITESPACES);
    போது (is_சாவி_char(*opts))
        opts++;
    சாவி_end = opts;
    opts += strspn(opts, WHITESPACES);
    எனில் (!*opts || !strchr(delim, *opts))
        திரும்பு AVERROR(EINVAL);
    opts++;
    எனில் (!(*rkey = av_malloc(சாவி_end - சாவி_start + 1)))
        திரும்பு AVERROR(ENOMEM);
    memcpy(*rkey, சாவி_start, சாவி_end - சாவி_start);
    (*rkey)[சாவி_end - சாவி_start] = 0;
    *ropts = opts;
    திரும்பு 0;
}

முழு av_opt_get_சாவி_மதிப்பு(மாறிலி எழுத்து **ropts,
                         மாறிலி எழுத்து *சாவி_val_sep, மாறிலி எழுத்து *pairs_sep,
                         unsigned flags,
                         எழுத்து **rkey, எழுத்து **rval)
{
    முழு ret;
    எழுத்து *சாவி = வெற்று, *val;
    மாறிலி எழுத்து *opts = *ropts;

    எனில் ((ret = get_சாவி(&opts, சாவி_val_sep, &சாவி)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_சாவி))
        திரும்பு AVERROR(EINVAL);
    எனில் (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(சாவி);
        திரும்பு AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = சாவி;
    *rval  = val;
    திரும்பு 0;
}

முழு av_opt_set_from_string(வெறுமை *ctx, மாறிலி எழுத்து *opts,
                           மாறிலி எழுத்து *மாறிலி *shorthand,
                           மாறிலி எழுத்து *சாவி_val_sep, மாறிலி எழுத்து *pairs_sep)
{
    முழு ret, மொத்தம் = 0;
    மாறிலி எழுத்து *dummy_shorthand = வெற்று;
    மாறிலி எழுத்து *சாவி;

    எனில் (!opts)
        திரும்பு 0;
    எனில் (!shorthand)
        shorthand = &dummy_shorthand;

    போது (*opts) {
        எழுத்து *parsed_சாவி, *மதிப்பு;
        ret = av_opt_get_சாவி_மதிப்பு(&opts, சாவி_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_சாவி : 0,
                                   &parsed_சாவி, &மதிப்பு);
        எனில் (ret < 0) {
            எனில் (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            இல்லையெனில்
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            திரும்பு ret;
        }
        எனில் (*opts)
            opts++;
        எனில் (parsed_சாவி) {
            சாவி = parsed_சாவி;
            போது (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } இல்லையெனில் {
            சாவி = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", சாவி, மதிப்பு);
        எனில் ((ret = av_opt_set(ctx, சாவி, மதிப்பு, 0)) < 0) {
            எனில் (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", சாவி);
            av_free(மதிப்பு);
            av_free(parsed_சாவி);
            திரும்பு ret;
        }

        av_free(மதிப்பு);
        av_free(parsed_சாவி);
        மொத்தம்++;
    }
    திரும்பு மொத்தம்;
}

வெறுமை av_opt_free(வெறுமை *obj)
{
    மாறிலி AVOption *o = வெற்று;
    போது ((o = av_opt_next(obj, o))) {
        வெறுமை *pitem = (uint8_t *)obj + o->offset;

        எனில் (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        இல்லையெனில்
            opt_free_elem(o->type, pitem);
    }
}

முழு av_opt_set_dict2(வெறுமை *obj, AVDictionary **options, முழு தேடல்_flags)
{
    மாறிலி AVDictionaryEntry *t = வெற்று;
    AVDictionary    *tmp = வெற்று;
    முழு ret;

    எனில் (!options)
        திரும்பு 0;

    போது ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->சாவி, t->மதிப்பு, தேடல்_flags);
        எனில் (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->சாவி, t->மதிப்பு, AV_DICT_MULTIKEY);
        எனில் (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->சாவி, t->மதிப்பு);
            av_dict_free(&tmp);
            திரும்பு ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    திரும்பு 0;
}

முழு av_opt_set_dict(வெறுமை *obj, AVDictionary **options)
{
    திரும்பு av_opt_set_dict2(obj, options, 0);
}

மாறிலி AVOption *av_opt_find(வெறுமை *obj, மாறிலி எழுத்து *name, மாறிலி எழுத்து *unit,
                            முழு opt_flags, முழு தேடல்_flags)
{
    திரும்பு av_opt_find2(obj, name, unit, opt_flags, தேடல்_flags, வெற்று);
}

மாறிலி AVOption *av_opt_find2(வெறுமை *obj, மாறிலி எழுத்து *name, மாறிலி எழுத்து *unit,
                             முழு opt_flags, முழு தேடல்_flags, வெறுமை **target_obj)
{
    மாறிலி AVClass  *c;
    மாறிலி AVOption *o = வெற்று;

    எனில்(!obj)
        திரும்பு வெற்று;

    c= *(AVClass**)obj;

    எனில் (!c)
        திரும்பு வெற்று;

    எனில் (தேடல்_flags & AV_OPT_தேடல்_CHILDREN) {
        எனில் (தேடல்_flags & AV_OPT_தேடல்_FAKE_OBJ) {
            வெறுமை *iter = வெற்று;
            மாறிலி AVClass *child;
            போது (child = av_opt_child_class_iterate(c, &iter))
                எனில் (o = av_opt_find2(&child, name, unit, opt_flags, தேடல்_flags, வெற்று))
                    திரும்பு o;
        } இல்லையெனில் {
            வெறுமை *child = வெற்று;
            போது (child = av_opt_child_next(obj, child))
                எனில் (o = av_opt_find2(child, name, unit, opt_flags, தேடல்_flags, target_obj))
                    திரும்பு o;
        }
    }

    போது (o = av_opt_next(obj, o)) {
        எனில் (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            எனில் (target_obj) {
                எனில் (!(தேடல்_flags & AV_OPT_தேடல்_FAKE_OBJ))
                    *target_obj = obj;
                இல்லையெனில்
                    *target_obj = வெற்று;
            }
            திரும்பு o;
        }
    }
    திரும்பு வெற்று;
}

வெறுமை *av_opt_child_next(வெறுமை *obj, வெறுமை *prev)
{
    மாறிலி AVClass *c = *(AVClass **)obj;
    எனில் (c->child_next)
        திரும்பு c->child_next(obj, prev);
    திரும்பு வெற்று;
}

மாறிலி AVClass *av_opt_child_class_iterate(மாறிலி AVClass *parent, வெறுமை **iter)
{
    எனில் (parent->child_class_iterate)
        திரும்பு parent->child_class_iterate(iter);
    திரும்பு வெற்று;
}

நிலையான முழு opt_copy_elem(வெறுமை *logctx, எண்ணிக்கை AVOptionType type,
                         வெறுமை *dst, மாறிலி வெறுமை *src)
{
    எனில் (type == AV_OPT_TYPE_STRING) {
        மாறிலி எழுத்து *src_str = *(மாறிலி எழுத்து *மாறிலி *)src;
        எழுத்து         **dstp =  (எழுத்து **)dst;
        எனில் (*dstp != src_str)
            av_freep(dstp);
        எனில் (src_str) {
            *dstp = av_strdup(src_str);
            எனில் (!*dstp)
                திரும்பு AVERROR(ENOMEM);
        }
    } இல்லையெனில் எனில் (type == AV_OPT_TYPE_இருமம்) {
        மாறிலி uint8_t *மாறிலி *src8 = (மாறிலி uint8_t *மாறிலி *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        முழு len = *(மாறிலி முழு *)(src8 + 1);
        எனில் (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        எனில் (len && !*dst8) {
            *(முழு *)(dst8 + 1) = 0;
            திரும்பு AVERROR(ENOMEM);
        }
        *(முழு *)(dst8 + 1) = len;
    } இல்லையெனில் எனில் (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } இல்லையெனில் எனில் (type == AV_OPT_TYPE_DICT) {
        மாறிலி AVDictionary *sdict = *(மாறிலி AVDictionary * மாறிலி *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        எனில் (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = வெற்று;
        திரும்பு av_dict_copy(ddictp, sdict, 0);
    } இல்லையெனில் எனில் (type == AV_OPT_TYPE_CHLAYOUT) {
        மாறிலி AVChannelLayout *slayout = (மாறிலி AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        எனில் (dlayout != slayout) {
            எனில் (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = வெற்று;
            திரும்பு av_channel_layout_copy(dst, src);
        }
    } இல்லையெனில் எனில் (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } இல்லையெனில் {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        திரும்பு AVERROR(EINVAL);
    }

    திரும்பு 0;
}

நிலையான முழு opt_copy_array(வெறுமை *logctx, மாறிலி AVOption *o,
                          வெறுமை **pdst, மாறிலி வெறுமை * மாறிலி *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    வெறுமை         *dst = வெற்று;
    முழு ret;

    எனில் (*pdst == *psrc) {
        *pdst                   = வெற்று;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    எனில் (!dst)
        திரும்பு AVERROR(ENOMEM);

    க்கு (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(வெறுமை**)psrc, i));
        எனில் (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            திரும்பு ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    திரும்பு 0;
}

முழு av_opt_copy(வெறுமை *dst, மாறிலி வெறுமை *src)
{
    மாறிலி AVOption *o = வெற்று;
    மாறிலி AVClass *c;
    முழு ret = 0;

    எனில் (!src)
        திரும்பு AVERROR(EINVAL);

    c = *(AVClass **)src;
    எனில் (!c || c != *(AVClass **)dst)
        திரும்பு AVERROR(EINVAL);

    போது ((o = av_opt_next(src, o))) {
        வெறுமை *field_dst = (uint8_t *)dst + o->offset;
        வெறுமை *field_src = (uint8_t *)src + o->offset;

        முழு err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        எனில் (err < 0)
            ret = err;
    }
    திரும்பு ret;
}

முழு av_opt_get_array_size(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags,
                          unsigned முழு *out_val)
{
    வெறுமை *target_obj, *parray;
    மாறிலி AVOption *o;

    o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        திரும்பு AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    திரும்பு 0;
}

முழு av_opt_get_array(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags,
                     unsigned முழு start_elem, unsigned முழு nb_elems,
                     எண்ணிக்கை AVOptionType out_type, வெறுமை *out_val)
{
    மாறிலி size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    மாறிலி AVOption *o;
    வெறுமை *target_obj;

    மாறிலி வெறுமை *parray;
    unsigned array_size;

    முழு ret;

    o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target_obj);
    எனில் (!o || !target_obj)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    எனில் (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        திரும்பு AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    எனில் (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        திரும்பு AVERROR(EINVAL);

    க்கு (unsigned i = 0; i < nb_elems; i++) {
        மாறிலி வெறுமை *src = opt_array_pelem(o, *(வெறுமை**)parray, start_elem + i);
        வெறுமை       *dst = (uint8_t*)out_val + i * elem_size_out;

        எனில் (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            எனில் (ret < 0)
                செல் fail;
        } இல்லையெனில் எனில் (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, அளவு(buf), src, தேடல்_flags);
            எனில் (ret < 0)
                செல் fail;

            எனில் (out == buf) {
                out = av_strdup(buf);
                எனில் (!out) {
                    ret = AVERROR(ENOMEM);
                    செல் fail;
                }
            }

            *(uint8_t**)dst = out;
        } இல்லையெனில் எனில் (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            இரட்டை     இலக்கம் = 1.0;
            முழு        den = 1;
            int64_t intnum = 1;

            ret = read_எண்(o, src, &இலக்கம், &den, &intnum);
            எனில் (ret < 0)
                செல் fail;

            தேர்வு (out_type) {
            நிலை AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (இலக்கம் == den) ?  intnum : இலக்கம் * intnum / den;
                நிறுத்து;
            நிலை AV_OPT_TYPE_DOUBLE:
                *(இரட்டை*)dst = இலக்கம் * intnum / den;
                நிறுத்து;
            நிலை AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (இலக்கம் == 1.0 && (முழு)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(இலக்கம் * intnum / den);
                நிறுத்து;
            இயல்பு: av_assert0(0);
            }
        } இல்லையெனில்
            திரும்பு AVERROR(ENOSYS);
    }

    திரும்பு 0;
fail:
    க்கு (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    திரும்பு ret;
}

முழு av_opt_set_array(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags,
                     unsigned முழு start_elem, unsigned முழு nb_elems,
                     எண்ணிக்கை AVOptionType val_type, மாறிலி வெறுமை *val)
{
    மாறிலி size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    மாறிலி AVOption *o;
    மாறிலி AVOptionArrayDef *arr;
    வெறுமை *target_obj;

    வெறுமை *parray;
    வெறுமை *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    முழு ret = 0;

    ret = opt_set_init(obj, name, தேடல்_flags, 0, &target_obj, &o, &parray);
    எனில் (ret < 0)
        திரும்பு ret;

    எனில் (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        திரும்பு AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    எனில் (start_elem > *array_size)
        திரும்பு AVERROR(EINVAL);

    // compute new array size
    எனில் (!val) {
        எனில் (*array_size - start_elem < nb_elems)
            திரும்பு AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } இல்லையெனில் எனில் (தேடல்_flags & AV_OPT_ARRAY_REPLACE) {
        எனில் (start_elem >= UINT_MAX - nb_elems)
            திரும்பு AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } இல்லையெனில் {
        எனில் (nb_elems >= UINT_MAX - *array_size)
            திரும்பு AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    எனில் (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        திரும்பு AVERROR(EINVAL);

    // desired operation is shrinking the array
    எனில் (!val) {
        வெறுமை *array = *(வெறுமை**)parray;

        க்கு (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        எனில் (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            எனில் (!array)
                திரும்பு AVERROR(ENOMEM);

            *(வெறுமை**)parray = array;
        } இல்லையெனில்
            av_freep(parray);

        *array_size = new_size;

        திரும்பு 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    எனில் (!new_elems)
        திரும்பு AVERROR(ENOMEM);

    // convert/validate each new element
    க்கு (unsigned i = 0; i < nb_elems; i++) {
        வெறுமை       *dst = opt_array_pelem(o, new_elems, i);
        மாறிலி வெறுமை *src = (uint8_t*)val + i * elem_size_val;

        இரட்டை     இலக்கம் = 1.0;
        முழு        den = 1;
        int64_t intnum = 1;

        எனில் (val_type == TYPE_BASE(o->type)) {
            முழு err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            எனில் (ret < 0)
                செல் fail;

            // validate the range for numeric options
            err = read_எண்(o, dst, &இலக்கம், &den, &intnum);
            எனில் (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < இலக்கம் * intnum || o->min * den > இலக்கம் * intnum)) {
                இலக்கம் = den ? இலக்கம் * intnum / den : (இலக்கம் && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, இலக்கம், o->min, o->max);
                ret = AVERROR(ERANGE);
                செல் fail;
            }
        } இல்லையெனில் எனில் (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(மாறிலி எழுத்து **)src, dst);
            எனில் (ret < 0)
                செல் fail;
        } இல்லையெனில் எனில் (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            தேர்வு (val_type) {
            நிலை AV_OPT_TYPE_INT:       intnum = *(முழு*)src;                நிறுத்து;
            நிலை AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            நிறுத்து;
            நிலை AV_OPT_TYPE_FLOAT:     இலக்கம்    = *(தசம*)src;              நிறுத்து;
            நிலை AV_OPT_TYPE_DOUBLE:    இலக்கம்    = *(இரட்டை*)src;             நிறுத்து;
            நிலை AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->இலக்கம்;
                                        den    = ((AVRational*)src)->den;   நிறுத்து;
            இயல்பு: av_assert0(0);
            }

            ret = write_எண்(obj, o, dst, இலக்கம், den, intnum, 0);
            எனில் (ret < 0)
                செல் fail;
        } இல்லையெனில் {
            ret = AVERROR(ENOSYS);
            செல் fail;
        }
    }

    // commit new elements to the array
    எனில் (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(வெறுமை**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = வெற்று;
        nb_elems  = 0;
    } இல்லையெனில் {
        வெறுமை *array = av_realloc_array(*(வெறுமை**)parray, new_size, elem_size);
        எனில் (!array) {
            ret = AVERROR(ENOMEM);
            செல் fail;
        }

        எனில் (தேடல்_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            க்கு (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } இல்லையெனில் {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(வெறுமை**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    திரும்பு ret;
}

முழு av_opt_query_ranges(AVOptionRanges **ranges_arg, வெறுமை *obj, மாறிலி எழுத்து *சாவி, முழு flags)
{
    முழு ret;
    மாறிலி AVClass *c = *(AVClass**)obj;
    முழு (*callback)(AVOptionRanges **, வெறுமை *obj, மாறிலி எழுத்து *சாவி, முழு flags) = c->query_ranges;

    எனில் (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, சாவி, flags);
    எனில் (ret >= 0) {
        எனில் (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    திரும்பு ret;
}

முழு av_opt_query_ranges_default(AVOptionRanges **ranges_arg, வெறுமை *obj, மாறிலி எழுத்து *சாவி, முழு flags)
{
    AVOptionRanges *ranges = av_mallocz(அளவு(*ranges));
    AVOptionRange **range_array = av_mallocz(அளவு(வெறுமை*));
    AVOptionRange *range = av_mallocz(அளவு(*range));
    மாறிலி AVOption *field = av_opt_find(obj, சாவி, வெற்று, 0, flags);
    முழு ret;

    *ranges_arg = வெற்று;

    எனில் (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->மதிப்பு_min = field->min;
    range->மதிப்பு_max = field->max;

    தேர்வு (field->type) {
    நிலை AV_OPT_TYPE_BOOL:
    நிலை AV_OPT_TYPE_INT:
    நிலை AV_OPT_TYPE_UINT:
    நிலை AV_OPT_TYPE_INT64:
    நிலை AV_OPT_TYPE_UINT64:
    நிலை AV_OPT_TYPE_PIXEL_FMT:
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
    நிலை AV_OPT_TYPE_FLOAT:
    நிலை AV_OPT_TYPE_DOUBLE:
    நிலை AV_OPT_TYPE_DURATION:
    நிலை AV_OPT_TYPE_COLOR:
        நிறுத்து;
    நிலை AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->மதிப்பு_min = -1;
        range->மதிப்பு_max = INT_MAX;
        நிறுத்து;
    நிலை AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        நிறுத்து;
    நிலை AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->மதிப்பு_min = 0;
        range->மதிப்பு_max = INT_MAX/8;
        நிறுத்து;
    நிலை AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->மதிப்பு_min = 1;
        range->மதிப்பு_max = INT_MAX;
        நிறுத்து;
    இயல்பு:
        ret = AVERROR(ENOSYS);
        செல் fail;
    }

    *ranges_arg = ranges;
    திரும்பு 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    திரும்பு ret;
}

வெறுமை av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    முழு i;
    AVOptionRanges *ranges = *rangesp;

    எனில் (!ranges)
        திரும்பு;

    க்கு (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        எனில் (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

முழு av_opt_is_set_to_default(வெறுமை *obj, மாறிலி AVOption *o)
{
    int64_t i64;
    இரட்டை d;
    AVRational q;
    முழு ret, w, h;
    எழுத்து *str;
    வெறுமை *dst;

    எனில் (!o || !obj)
        திரும்பு AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    எனில் (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        மாறிலி எழுத்து *def = o->default_val.arr ? o->default_val.arr->def : வெற்று;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        எனில் (ret < 0)
            திரும்பு ret;

        எனில் (!!val != !!def)
            ret = 0;
        இல்லையெனில் எனில் (val)
            ret = !strcmp(val, def);
        இல்லையெனில்
            ret = 1;

        av_freep(&val);

        திரும்பு ret;
    }

    தேர்வு (o->type) {
    நிலை AV_OPT_TYPE_CONST:
        திரும்பு 1;
    நிலை AV_OPT_TYPE_BOOL:
    நிலை AV_OPT_TYPE_FLAGS:
    நிலை AV_OPT_TYPE_PIXEL_FMT:
    நிலை AV_OPT_TYPE_SAMPLE_FMT:
    நிலை AV_OPT_TYPE_INT:
    நிலை AV_OPT_TYPE_UINT:
    நிலை AV_OPT_TYPE_DURATION:
    நிலை AV_OPT_TYPE_INT64:
    நிலை AV_OPT_TYPE_UINT64:
        read_எண்(o, dst, வெற்று, வெற்று, &i64);
        திரும்பு o->default_val.i64 == i64;
    நிலை AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        எனில் (o->default_val.str) {
            எனில் ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                திரும்பு ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        திரும்பு ret;
    }
    நிலை AV_OPT_TYPE_STRING:
        str = *(எழுத்து **)dst;
        எனில் (str == o->default_val.str) //2 NULLs
            திரும்பு 1;
        எனில் (!str || !o->default_val.str) //1 NULL
            திரும்பு 0;
        திரும்பு !strcmp(str, o->default_val.str);
    நிலை AV_OPT_TYPE_DOUBLE:
        d = *(இரட்டை *)dst;
        திரும்பு o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    நிலை AV_OPT_TYPE_FLOAT:
        d = *(தசம *)dst;
        திரும்பு (தசம)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    நிலை AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        திரும்பு !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    நிலை AV_OPT_TYPE_இருமம்: {
        கட்டமைப்பு {
            uint8_t *data;
            முழு size;
        } tmp = {0};
        முழு opt_size = *(முழு *)((வெறுமை **)dst + 1);
        வெறுமை *opt_ptr = *(வெறுமை **)dst;
        எனில் (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            திரும்பு 1;
        எனில் (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            திரும்பு 0;
        எனில் (opt_size != strlen(o->default_val.str) / 2)
            திரும்பு 0;
        ret = set_string_இருமம்(வெற்று, வெற்று, o->default_val.str, &tmp.data);
        எனில் (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        திரும்பு ret;
    }
    நிலை AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = வெற்று;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        மாறிலி AVDictionaryEntry *en1 = வெற்று;
        மாறிலி AVDictionaryEntry *en2 = வெற்று;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        எனில் (ret < 0) {
            av_dict_free(&dict1);
            திரும்பு ret;
        }
        செய் {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } போது (en1 && en2 && !strcmp(en1->சாவி, en2->சாவி) && !strcmp(en1->மதிப்பு, en2->மதிப்பு));
        av_dict_free(&dict1);
        திரும்பு (!en1 && !en2);
    }
    நிலை AV_OPT_TYPE_IMAGE_SIZE:
        எனில் (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        இல்லையெனில் எனில் ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            திரும்பு ret;
        திரும்பு (w == *(முழு *)dst) && (h == *((முழு *)dst+1));
    நிலை AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        எனில் (o->default_val.str) {
            எனில் ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                திரும்பு ret;
        }
        திரும்பு !av_cmp_q(*(AVRational*)dst, q);
    நிலை AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        எனில் (o->default_val.str) {
            எனில் ((ret = av_parse_color(color, o->default_val.str, -1, வெற்று)) < 0)
                திரும்பு ret;
        }
        திரும்பு !memcmp(color, dst, அளவு(color));
    }
    இயல்பு:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        நிறுத்து;
    }
    திரும்பு AVERROR_PATCHWELCOME;
}

முழு av_opt_is_set_to_default_by_name(வெறுமை *obj, மாறிலி எழுத்து *name, முழு தேடல்_flags)
{
    மாறிலி AVOption *o;
    வெறுமை *target;
    எனில் (!obj)
        திரும்பு AVERROR(EINVAL);
    o = av_opt_find2(obj, name, வெற்று, 0, தேடல்_flags, &target);
    எனில் (!o)
        திரும்பு AVERROR_OPTION_NOT_FOUND;
    திரும்பு av_opt_is_set_to_default(target, o);
}

நிலையான முழு opt_serialize(வெறுமை *obj, முழு opt_flags, முழு flags, முழு *cnt,
                         AVBPrint *bprint, மாறிலி எழுத்து சாவி_val_sep, மாறிலி எழுத்து pairs_sep)
{
    மாறிலி AVOption *o = வெற்று;
    வெறுமை *child = வெற்று;
    uint8_t *buf;
    முழு ret;
    மாறிலி எழுத்து special_chars[] = {pairs_sep, சாவி_val_sep, '\0'};

    எனில் (flags & AV_OPT_SERIALIZE_தேடல்_CHILDREN)
        போது (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                சாவி_val_sep, pairs_sep);
            எனில் (ret < 0)
                திரும்பு ret;
        }

    போது (o = av_opt_next(obj, o)) {
        எனில் (o->type == AV_OPT_TYPE_CONST)
            தொடர்;
        எனில் ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            எனில் ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                எனில் (o->flags == opt_flags)
                    தொடர்;
            } இல்லையெனில் எனில் ((o->flags & opt_flags) == opt_flags)
                தொடர்;
        } இல்லையெனில் {
            எனில் ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                தொடர்;
            இல்லையெனில் எனில் (((o->flags & opt_flags) != opt_flags))
                தொடர்;
        }
        எனில் (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            தொடர்;
        எனில் ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, வெற்று);
            திரும்பு ret;
        }
        எனில் (buf) {
            எனில் ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &சாவி_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    திரும்பு 0;
}

முழு av_opt_serialize(வெறுமை *obj, முழு opt_flags, முழு flags, எழுத்து **buffer,
                     மாறிலி எழுத்து சாவி_val_sep, மாறிலி எழுத்து pairs_sep)
{
    AVBPrint bprint;
    முழு ret, cnt = 0;

    எனில் (pairs_sep == '\0' || சாவி_val_sep == '\0' || pairs_sep == சாவி_val_sep ||
        pairs_sep == '\\' || சாவி_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        திரும்பு AVERROR(EINVAL);
    }

    எனில் (!obj || !buffer)
        திரும்பு AVERROR(EINVAL);

    *buffer = வெற்று;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        சாவி_val_sep, pairs_sep);
    எனில் (ret < 0)
        திரும்பு ret;

    ret = av_bprint_finalize(&bprint, buffer);
    எனில் (ret < 0)
        திரும்பு ret;
    திரும்பு 0;
}
