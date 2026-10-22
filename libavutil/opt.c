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

#अन्तर्भाव "avutil.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "channel_layout.h"
#अन्तर्भाव "dict.h"
#अन्तर्भाव "eval.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "parseutils.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "mathematics.h"
#अन्तर्भाव "opt.h"
#अन्तर्भाव "samplefmt.h"
#अन्तर्भाव "bprint.h"

#अन्तर्भाव <float.h>

#परिभाषय TYPE_आधारः(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ध्रुव AVOption *av_opt_अग्र(ध्रुव शून्य *obj, ध्रुव AVOption *चरमः)
{
    ध्रुव AVClass *class;
    यदि (!obj)
        प्रत्यागम रिक्त;
    class = *(ध्रुव AVClass**)obj;
    यदि (!चरमः && class && class->option && class->option[0].name)
        प्रत्यागम class->option;
    यदि (चरमः && चरमः[1].name)
        प्रत्यागम ++चरमः;
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव संरचना {
    size_t      आकार;
    ध्रुव वर्ण *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { परिमाण(अचिह्नित),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { परिमाण(पूर्णाङ्क),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { परिमाण(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { परिमाण(अचिह्नित),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { परिमाण(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { परिमाण(द्विगुण),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { परिमाण(भिन्न),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { परिमाण(वर्ण *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { परिमाण(AVRational),     "<rational>" },
    [AV_OPT_TYPE_द्विमान]        = { परिमाण(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { परिमाण(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_आकार]    = { परिमाण(पूर्णाङ्क[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_दरः]    = { परिमाण(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { परिमाण(गणना AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { परिमाण(गणना AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { परिमाण(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { परिमाण(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { परिमाण(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { परिमाण(पूर्णाङ्क),            "<boolean>" },
};

// option is plain old data
स्थिर पूर्णाङ्क opt_is_pod(गणना AVOptionType type)
{
    विकल्प (type) {
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_FLOAT:
    पक्ष AV_OPT_TYPE_RATIONAL:
    पक्ष AV_OPT_TYPE_UINT64:
    पक्ष AV_OPT_TYPE_IMAGE_आकार:
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
    पक्ष AV_OPT_TYPE_VIDEO_दरः:
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_COLOR:
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_UINT:
        प्रत्यागम 1;
    }
    प्रत्यागम 0;
}

स्थिर uint8_t opt_array_sep(ध्रुव AVOption *o)
{
    ध्रुव AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    प्रत्यागम (d && d->sep) ? d->sep : ',';
}

स्थिर शून्य *opt_array_pelem(ध्रुव AVOption *o, शून्य *array, अचिह्नित idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    प्रत्यागम (uint8_t *)array + idx * opt_type_desc[TYPE_आधारः(o->type)].आकार;
}

स्थिर अचिह्नित *opt_array_pcount(ध्रुव शून्य *parray)
{
    प्रत्यागम (अचिह्नित *)((ध्रुव शून्य * ध्रुव *)parray + 1);
}

स्थिर शून्य opt_free_elem(गणना AVOptionType type, शून्य *ptr)
{
    विकल्प (TYPE_आधारः(type)) {
    पक्ष AV_OPT_TYPE_STRING:
    पक्ष AV_OPT_TYPE_द्विमान:
        av_freep(ptr);
        भङ्ग;

    पक्ष AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        भङ्ग;

    पक्ष AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        भङ्ग;

    स्वभाव:
        भङ्ग;
    }
}

स्थिर शून्य opt_free_array(ध्रुव AVOption *o, शून्य *parray, अचिह्नित *गणनम्)
{
    प्रति (अचिह्नित i = 0; i < *गणनम्; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(शून्य **)parray, i));

    av_freep(parray);
    *गणनम् = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
स्थिर पूर्णाङ्क opt_समुच्चयः_init(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                        पूर्णाङ्क require_type,
                        शून्य **ptgt, ध्रुव AVOption **po, शून्य **pdst)
{
    शून्य *logctx;
    ध्रुव AVOption *o;
    शून्य *tgt;

    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &tgt);
    यदि (!o || (!tgt && !(अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_FAKE_OBJ)))
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;

    यदि (o->flags & AV_OPT_FLAG_READONLY)
        प्रत्यागम AVERROR(EINVAL);

    logctx = tgt ? obj : रिक्त;

    यदि (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        अचिह्नित *state_flags = रिक्त;
        ध्रुव AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ध्रुव AVClass**)tgt;
        यदि (class->state_flags_विस्थापनम्)
            state_flags = (अचिह्नित*)((uint8_t*)tgt + class->state_flags_विस्थापनम्);

        यदि (!state_flags && obj != tgt) {
            class = *(ध्रुव AVClass**)obj;
            यदि (class->state_flags_विस्थापनम्)
                state_flags = (अचिह्नित*)((uint8_t*)obj + class->state_flags_विस्थापनम्);
        }

        यदि (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            प्रत्यागम AVERROR(EINVAL);
        }
    }

    यदि (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    यदि (po)
        *po   = o;
    यदि (ptgt)
        *ptgt = tgt;
    यदि (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->विस्थापनम् : रिक्त;

    प्रत्यागम 0;
}

स्थिर AVRational double_गन्तव्यम्_rational(द्विगुण d)
{
     AVRational r = av_d2q(d, 1 << 24);
     यदि ((!r.अङ्कः || !r.den) && d)
         r = av_d2q(d, अधिकतम_पूर्णाङ्कः);
     प्रत्यागम r;
}

स्थिर पूर्णाङ्क read_सङ्ख्या(ध्रुव AVOption *o, ध्रुव शून्य *dst, द्विगुण *अङ्कः, पूर्णाङ्क *den, int64_t *intnum)
{
    विकल्प (TYPE_आधारः(o->type)) {
    पक्ष AV_OPT_TYPE_FLAGS:
        *intnum = *(अचिह्नित पूर्णाङ्क*)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(गणना AVPixelFormat *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(गणना AVSampleFormat *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_INT:
        *intnum = *(पूर्णाङ्क *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_UINT:
        *intnum = *(अचिह्नित पूर्णाङ्क *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_FLOAT:
        *अङ्कः = *(भिन्न *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_DOUBLE:
        *अङ्कः = *(द्विगुण *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->अङ्कः;
        *den    = ((AVRational *)dst)->den;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        प्रत्यागम 0;
    }
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क write_सङ्ख्या(शून्य *obj, ध्रुव AVOption *o, शून्य *dst,
                        द्विगुण अङ्कः, पूर्णाङ्क den, int64_t intnum,
                        पूर्णाङ्क ignore_range)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_आधारः(o->type);

    यदि (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < अङ्कः * intnum || o->min * den > अङ्कः * intnum)) {
        अङ्कः = den ? अङ्कः * intnum / den : (अङ्कः && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               अङ्कः, o->name, o->min, o->max);
        प्रत्यागम AVERROR(ERANGE);
    }
    यदि (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        द्विगुण d = अङ्कः*intnum/den;
        यदि (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   अङ्कः*intnum/den, o->name);
            प्रत्यागम AVERROR(ERANGE);
        }
    }

    यदि (!dst)
        प्रत्यागम 0;

    विकल्प (type) {
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        *(गणना AVPixelFormat *)dst = llrint(अङ्कः / den) * intnum;
        भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        *(गणना AVSampleFormat *)dst = llrint(अङ्कः / den) * intnum;
        भङ्ग;
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
        *(पूर्णाङ्क *)dst = llrint(अङ्कः / den) * intnum;
        भङ्ग;
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_INT64:{
        द्विगुण d = अङ्कः / den;
        यदि (intnum == 1 && d == (द्विगुण)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } अन्यथा
            *(int64_t *)dst = llrint(d) * intnum;
        भङ्ग;}
    पक्ष AV_OPT_TYPE_UINT64:{
        द्विगुण d = अङ्कः / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        यदि (intnum == 1 && d == (द्विगुण)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } अन्यथा यदि (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } अन्यथा {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        भङ्ग;}
    पक्ष AV_OPT_TYPE_FLOAT:
        *(भिन्न *)dst = अङ्कः * intnum / den;
        भङ्ग;
    पक्ष AV_OPT_TYPE_DOUBLE:
        *(द्विगुण    *)dst = अङ्कः * intnum / den;
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL:
    पक्ष AV_OPT_TYPE_VIDEO_दरः:
        यदि ((पूर्णाङ्क) अङ्कः == अङ्कः)
            *(AVRational *)dst = (AVRational) { अङ्कः *intnum, den };
        अन्यथा
            *(AVRational *)dst = double_गन्तव्यम्_rational(अङ्कः * intnum / den);
        भङ्ग;
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क hexchar2int(वर्ण c) {
    यदि (c >= '0' && c <= '9')
        प्रत्यागम c - '0';
    यदि (c >= 'a' && c <= 'f')
        प्रत्यागम c - 'a' + 10;
    यदि (c >= 'A' && c <= 'F')
        प्रत्यागम c - 'A' + 10;
    प्रत्यागम -1;
}

स्थिर पूर्णाङ्क समुच्चयः_string_द्विमान(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    पूर्णाङ्क *lendst;
    uint8_t *bin, *ptr;
    पूर्णाङ्क len;

    यदि (dst) {
        lendst = (पूर्णाङ्क *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    यदि (!val || !(len = वाक्यदैर्घ्यम्(val)))
        प्रत्यागम 0;

    यदि (len & 1)
        प्रत्यागम AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    यदि (!ptr)
        प्रत्यागम AVERROR(ENOMEM);
    यावत् (*val) {
        पूर्णाङ्क a = hexchar2int(*val++);
        पूर्णाङ्क b = hexchar2int(*val++);
        यदि (a < 0 || b < 0) {
            av_free(bin);
            प्रत्यागम AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    यदि (dst) {
        *dst    = bin;
        *lendst = len;
    } अन्यथा {
        av_free(bin);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क समुच्चयः_string(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    यदि (!dst)
        प्रत्यागम 0;
    av_freep(dst);
    यदि (!val)
        प्रत्यागम 0;
    *dst = av_strdup(val);
    प्रत्यागम *dst ? 0 : AVERROR(ENOMEM);
}

#परिभाषय DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

स्थिर पूर्णाङ्क समुच्चयः_string_सङ्ख्या(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_आधारः(o->type);
    पूर्णाङ्क ret = 0;

    यदि (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_दरः) {
        पूर्णाङ्क अङ्कः, den;
        वर्ण c;
        यदि (वाक्यात्_पठ(val, "%d%*1[:/]%d%c", &अङ्कः, &den, &c) == 2) {
            यदि ((ret = write_सङ्ख्या(obj, o, dst, 1, den, अङ्कः, 0)) >= 0)
                प्रत्यागम ret;
            ret = 0;
        }
    }

    प्रति (;;) {
        पूर्णाङ्क i = 0;
        वर्ण buf[256];
        पूर्णाङ्क cmd = 0;
        द्विगुण d;
        int64_t intnum = 1;

        यदि (type == AV_OPT_TYPE_FLAGS) {
            यदि (*val == '+' || *val == '-')
                cmd = *(val++);
            प्रति (; i < परिमाण(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            पूर्णाङ्क res;
            पूर्णाङ्क ci = 0;
            द्विगुण const_मानानि[64];
            ध्रुव वर्ण * const_नामानि[64];
            पूर्णाङ्क अन्वेषणम्_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_अन्वेषणम्_CHILDREN : 0;
            ध्रुव AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, अन्वेषणम्_flags);
            यदि (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                यदि (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } अन्यथा {
                यदि (o->unit) {
                    प्रति (o_named = रिक्त; o_named = av_opt_अग्र(target_obj, o_named); ) {
                        यदि (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !वाक्यं_तुलय(o_named->unit, o->unit)) {
                            यदि (ci + 6 >= FF_ARRAY_ELEMS(const_मानानि)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                प्रत्यागम AVERROR_PATCHWELCOME;
                            }
                            const_नामानि [ci  ] = o_named->name;
                            const_मानानि[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_नामानि [ci  ] = "default";
                const_मानानि[ci++] = DEFAULT_NUMVAL(o);
                const_नामानि [ci  ] = "max";
                const_मानानि[ci++] = o->max;
                const_नामानि [ci  ] = "min";
                const_मानानि[ci++] = o->min;
                const_नामानि [ci  ] = "none";
                const_मानानि[ci++] = 0;
                const_नामानि [ci  ] = "all";
                const_मानानि[ci++] = ~0;
                const_नामानि [ci] = रिक्त;
                const_मानानि[ci] = 0;

                res = av_व्यञ्जकम्_parse_and_eval(&d, i ? buf : val, const_नामानि,
                                            const_मानानि, रिक्त, रिक्त, रिक्त, रिक्त, रिक्त, 0, obj);
                यदि (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    प्रत्यागम res;
                }
            }
        }
        यदि (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(अचिह्नित पूर्णाङ्क*)dst;
            यदि (cmd == '+')
                d = intnum | (int64_t)d;
            अन्यथा यदि (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        यदि ((ret = write_सङ्ख्या(obj, o, dst, d, 1, 1, 0)) < 0)
            प्रत्यागम ret;
        val += i;
        यदि (!i || !*val)
            प्रत्यागम 0;
    }
}

स्थिर पूर्णाङ्क समुच्चयः_string_image_आकार(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, पूर्णाङ्क *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क tmp[2];
    पूर्णाङ्क ret;

    यदि (!val || !वाक्यं_तुलय(val, "none")) {
        यदि (dst) {
        dst[0] =
        dst[1] = 0;
        }
        प्रत्यागम 0;
    }
    ret = av_parse_video_आकार(&tmp[0], &tmp[1], val);
    यदि (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        प्रत्यागम ret;
    }
    यदि (dst)
        स्मृतिं_प्रतिलिख(dst, tmp, परिमाण(tmp));
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क समुच्चयः_string_video_दरः(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, AVRational *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    AVRational tmp;
    पूर्णाङ्क ret = av_parse_video_दरः(&tmp, val);
    यदि (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    यदि (dst)
        *dst = tmp;
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क समुच्चयः_string_color(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क ret;

    यदि (!val) {
        प्रत्यागम 0;
    } अन्यथा {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        यदि (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            प्रत्यागम ret;
        }
        यदि (dst)
            स्मृतिं_प्रतिलिख(dst, tmp, परिमाण(tmp));
        प्रत्यागम ret;
    }
    प्रत्यागम 0;
}

स्थिर ध्रुव वर्ण *get_bool_name(पूर्णाङ्क val)
{
    यदि (val < 0)
        प्रत्यागम "auto";
    प्रत्यागम val ? "true" : "false";
}

स्थिर पूर्णाङ्क समुच्चयः_string_bool(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, पूर्णाङ्क *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क n;

    यदि (!val)
        प्रत्यागम 0;

    यदि (!वाक्यं_तुलय(val, "auto")) {
        n = -1;
    } अन्यथा यदि (av_मेलनम्_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } अन्यथा यदि (av_मेलनम्_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } अन्यथा {
        वर्ण *अन्तः_2 = रिक्त;
        n = strtol(val, &अन्तः_2, 10);
        यदि (val + वाक्यदैर्घ्यम्(val) != अन्तः_2)
            गच्छ fail;
    }

    यदि (n < o->min || n > o->max)
        गच्छ fail;

    यदि (dst)
    *dst = n;
    प्रत्यागम 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क समुच्चयः_string_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst,
                          पूर्णाङ्क fmt_nb, पूर्णाङ्क ((*get_fmt)(ध्रुव वर्ण *)), ध्रुव वर्ण *desc,
                          गणना AVOptionType type)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क fmt, min, max;

    यदि (!val || !वाक्यं_तुलय(val, "none")) {
        fmt = -1;
    } अन्यथा {
        fmt = get_fmt(val);
        यदि (fmt == -1) {
            वर्ण *पुच्छ;
            fmt = strtol(val, &पुच्छ, 0);
            यदि (*पुच्छ || (अचिह्नित)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                प्रत्यागम AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    यदि(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    यदि (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        प्रत्यागम AVERROR(ERANGE);
    }

    यदि (dst)
    विकल्प (type) {
    पक्ष AV_OPT_TYPE_PIXEL_FMT:  *(गणना AVPixelFormat *)dst = fmt; भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT: *(गणना AVSampleFormat*)dst = fmt; भङ्ग;
    स्वभाव: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क get_pix_fmt(ध्रुव वर्ण *name)
{
    प्रत्यागम av_get_pix_fmt(name);
}

स्थिर पूर्णाङ्क समुच्चयः_string_pixel_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    प्रत्यागम समुच्चयः_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

स्थिर पूर्णाङ्क get_sample_fmt(ध्रुव वर्ण *name)
{
    प्रत्यागम av_get_sample_fmt(name);
}

स्थिर पूर्णाङ्क समुच्चयः_string_sample_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    प्रत्यागम समुच्चयः_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

स्थिर पूर्णाङ्क समुच्चयः_string_dict(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    AVDictionary *options = रिक्त;

    यदि (val) {
        पूर्णाङ्क ret = av_dict_parse_string(&options, val, "=", ":", 0);
        यदि (ret < 0) {
            av_dict_free(&options);
            प्रत्यागम ret;
        }
    }

    यदि (!dst) {
        av_dict_free(&options);
        प्रत्यागम 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क समुच्चयः_string_channel_layout(शून्य *obj, ध्रुव AVOption *o,
                                     ध्रुव वर्ण *val, शून्य *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    पूर्णाङ्क ret;
    यदि (dst)
    av_channel_layout_uninit(channel_layout);
    अन्यथा
        channel_layout = &tmp;
    यदि (!val)
        प्रत्यागम 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    यदि (ret < 0)
        प्रत्यागम ret;
    यदि (!dst)
        av_channel_layout_uninit(channel_layout);
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opt_समुच्चयः_elem(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o,
                        ध्रुव वर्ण *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_आधारः(o->type);
    पूर्णाङ्क ret;

    यदि (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_आकार &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        प्रत्यागम AVERROR(EINVAL);

    विकल्प (type) {
    पक्ष AV_OPT_TYPE_BOOL:
        प्रत्यागम समुच्चयः_string_bool(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_STRING:
        प्रत्यागम समुच्चयः_string(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_द्विमान:
        प्रत्यागम समुच्चयः_string_द्विमान(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
    पक्ष AV_OPT_TYPE_FLOAT:
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_RATIONAL:
        प्रत्यागम समुच्चयः_string_सङ्ख्या(obj, target_obj, o, val, dst);
    पक्ष AV_OPT_TYPE_IMAGE_आकार:
        प्रत्यागम समुच्चयः_string_image_आकार(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_VIDEO_दरः: {
        AVRational tmp;
        ret = समुच्चयः_string_video_दरः(obj, o, val, &tmp);
        यदि (ret < 0)
            प्रत्यागम ret;
        प्रत्यागम write_सङ्ख्या(obj, o, dst, 1, tmp.den, tmp.अङ्कः, 0);
    }
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        प्रत्यागम समुच्चयः_string_pixel_fmt(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        प्रत्यागम समुच्चयः_string_sample_fmt(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            यदि (val) {
                यदि ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    प्रत्यागम ret;
                }
            }
            यदि (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                प्रत्यागम AVERROR(ERANGE);
            }
            यदि (dst)
            *(int64_t *)dst = usecs;
            प्रत्यागम 0;
        }
    पक्ष AV_OPT_TYPE_COLOR:
        प्रत्यागम समुच्चयः_string_color(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_CHLAYOUT:
        ret = समुच्चयः_string_channel_layout(obj, o, val, dst);
        यदि (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        प्रत्यागम ret;
    पक्ष AV_OPT_TYPE_DICT:
        प्रत्यागम समुच्चयः_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क opt_समुच्चयः_array(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o,
                         ध्रुव वर्ण *val, शून्य *dst)
{
    ध्रुव AVOptionArrayDef *arr = o->default_val.arr;
    ध्रुव size_t      elem_आकार = opt_type_desc[TYPE_आधारः(o->type)].आकार;
    ध्रुव uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = रिक्त;

    शून्य      *logctx = dst ? obj : रिक्त;
    शून्य       *elems = रिक्त;
    अचिह्नित nb_elems = 0;
    पूर्णाङ्क ret;

    यदि (val && *val) {
        str = av_malloc(वाक्यदैर्घ्यम्(val) + 1);
        यदि (!str)
            प्रत्यागम AVERROR(ENOMEM);
    }

    // split and unescape the string
    यावत् (val && *val) {
        uint8_t *p = str;
        शून्य *tmp;

        यदि (arr && arr->आकार_max && nb_elems >= arr->आकार_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->आकार_max, o->name);
            ret = AVERROR(EINVAL);
            गच्छ fail;
        }

        प्रति (; *val; val++, p++) {
            यदि (*val == '\\' && val[1])
                val++;
            अन्यथा यदि (*val == sep) {
                val++;
                भङ्ग;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_आकार);
        यदि (!tmp) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        स्मृतिं_पूरय(tmp, 0, elem_आकार);

        ret = opt_समुच्चयः_elem(obj, target_obj, o, str, tmp);
        यदि (ret < 0)
            गच्छ fail;
        nb_elems++;
    }
    av_freep(&str);

    यदि (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    यदि (arr && nb_elems < arr->आकार_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->आकार_min, o->name);
        ret = AVERROR(EINVAL);
        गच्छ fail;
    }

    यदि (dst) {
    *((शून्य **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } अन्यथा
        opt_free_array(o, &elems, &nb_elems);

    प्रत्यागम 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_समुच्चयः(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *val, पूर्णाङ्क अन्वेषणम्_flags)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o;
    पूर्णाङ्क ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, 0, &target_obj, &o, &dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    प्रत्यागम ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_समुच्चयः_array : opt_समुच्चयः_elem)(obj, target_obj, o, val, dst);
}

#परिभाषय OPT_EVAL_सङ्ख्या(name, opttype, vartype)                         \
पूर्णाङ्क av_opt_eval_ ## name(शून्य *obj, ध्रुव AVOption *o,                  \
                         ध्रुव वर्ण *val, vartype *name ## बहिर्गमनम्_3)        \
{                                                                       \
    यदि (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        प्रत्यागम AVERROR(EINVAL);                                         \
    प्रत्यागम समुच्चयः_string_सङ्ख्या(obj, obj, o, val, name ## बहिर्गमनम्_3);           \
}

OPT_EVAL_सङ्ख्या(flags,  AV_OPT_TYPE_FLAGS,    पूर्णाङ्क)
OPT_EVAL_सङ्ख्या(पूर्णाङ्क,    AV_OPT_TYPE_INT,      पूर्णाङ्क)
OPT_EVAL_सङ्ख्या(uint,   AV_OPT_TYPE_UINT,     अचिह्नित)
OPT_EVAL_सङ्ख्या(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_सङ्ख्या(भिन्न,  AV_OPT_TYPE_FLOAT,    भिन्न)
OPT_EVAL_सङ्ख्या(द्विगुण, AV_OPT_TYPE_DOUBLE,   द्विगुण)
OPT_EVAL_सङ्ख्या(q,      AV_OPT_TYPE_RATIONAL, AVRational)

स्थिर पूर्णाङ्क समुच्चयः_सङ्ख्या(शून्य *obj, ध्रुव वर्ण *name, द्विगुण अङ्कः, पूर्णाङ्क den, int64_t intnum,
                      पूर्णाङ्क अन्वेषणम्_flags, पूर्णाङ्क require_type)
{
    शून्य *dst;
    ध्रुव AVOption *o;
    पूर्णाङ्क ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, require_type, रिक्त, &o, &dst);
    यदि (ret < 0)
        प्रत्यागम ret;
    यदि (dst)
        ret = write_सङ्ख्या(obj, o, dst, अङ्कः, den, intnum, 0);

    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_समुच्चयः_int(शून्य *obj, ध्रुव वर्ण *name, int64_t val, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम समुच्चयः_सङ्ख्या(obj, name, 1, 1, val, अन्वेषणम्_flags, 0);
}

पूर्णाङ्क av_opt_समुच्चयः_double(शून्य *obj, ध्रुव वर्ण *name, द्विगुण val, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम समुच्चयः_सङ्ख्या(obj, name, val, 1, 1, अन्वेषणम्_flags, 0);
}

पूर्णाङ्क av_opt_समुच्चयः_q(शून्य *obj, ध्रुव वर्ण *name, AVRational val, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम समुच्चयः_सङ्ख्या(obj, name, val.अङ्कः, val.den, 1, अन्वेषणम्_flags, 0);
}

पूर्णाङ्क av_opt_समुच्चयः_bin(शून्य *obj, ध्रुव वर्ण *name, ध्रुव uint8_t *val, पूर्णाङ्क len, पूर्णाङ्क अन्वेषणम्_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    पूर्णाङ्क *lendst;
    पूर्णाङ्क ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_द्विमान,
                       रिक्त, रिक्त, (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (dst) {
    ptr = len ? av_malloc(len) : रिक्त;
    यदि (len && !ptr)
        प्रत्यागम AVERROR(ENOMEM);

    lendst = (पूर्णाङ्क *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    यदि (len)
        स्मृतिं_प्रतिलिख(ptr, val, len);
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_समुच्चयः_image_आकार(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क अन्वेषणम्_flags)
{
    ध्रुव AVOption *o;
    शून्य *logctx;
    पूर्णाङ्क *dst;
    पूर्णाङ्क ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_IMAGE_आकार,
                       रिक्त, &o, (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    logctx = dst ? obj : रिक्त;

    यदि (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_समुच्चयः_video_दरः(शून्य *obj, ध्रुव वर्ण *name, AVRational val, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम समुच्चयः_सङ्ख्या(obj, name, val.अङ्कः, val.den, 1, अन्वेषणम्_flags, AV_OPT_TYPE_VIDEO_दरः);
}

स्थिर पूर्णाङ्क समुच्चयः_format(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क fmt, पूर्णाङ्क अन्वेषणम्_flags,
                      गणना AVOptionType type, ध्रुव वर्ण *desc, पूर्णाङ्क nb_fmts)
{
    ध्रुव AVOption *o;
    शून्य *logctx;
    पूर्णाङ्क *dst;
    पूर्णाङ्क min, max, ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, type, रिक्त, &o, (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    logctx = dst ? obj : रिक्त;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    यदि (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        प्रत्यागम AVERROR(ERANGE);
    }
    यदि (dst)
    *dst = fmt;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_समुच्चयः_pixel_fmt(शून्य *obj, ध्रुव वर्ण *name, गणना AVPixelFormat fmt, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम समुच्चयः_format(obj, name, fmt, अन्वेषणम्_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

पूर्णाङ्क av_opt_समुच्चयः_sample_fmt(शून्य *obj, ध्रुव वर्ण *name, गणना AVSampleFormat fmt, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम समुच्चयः_format(obj, name, fmt, अन्वेषणम्_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

पूर्णाङ्क av_opt_समुच्चयः_dict_val(शून्य *obj, ध्रुव वर्ण *name, ध्रुव AVDictionary *val,
                        पूर्णाङ्क अन्वेषणम्_flags)
{
    AVDictionary **dst;
    पूर्णाङ्क ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_DICT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_समुच्चयः_chlayout(शून्य *obj, ध्रुव वर्ण *name,
                        ध्रुव AVChannelLayout *channel_layout,
                        पूर्णाङ्क अन्वेषणम्_flags)
{
    AVChannelLayout *dst;
    पूर्णाङ्क ret;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_CHLAYOUT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    प्रत्यागम ret;
}

स्थिर शून्य format_duration(वर्ण *buf, size_t आकार, int64_t d)
{
    वर्ण *e;

    av_assert0(आकार >= 25);
    यदि (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        आकार--;
        d = -d;
    }
    यदि (d == INT64_MAX)
        snprintf(buf, आकार, "INT64_MAX");
    अन्यथा यदि (d == INT64_MIN)
        snprintf(buf, आकार, "INT64_MIN");
    अन्यथा यदि (d > (int64_t)3600*1000000)
        snprintf(buf, आकार, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (पूर्णाङ्क)((d / 60000000) % 60),
                 (पूर्णाङ्क)((d / 1000000) % 60),
                 (पूर्णाङ्क)(d % 1000000));
    अन्यथा यदि (d > 60*1000000)
        snprintf(buf, आकार, "%d:%02d.%06d",
                 (पूर्णाङ्क)(d / 60000000),
                 (पूर्णाङ्क)((d / 1000000) % 60),
                 (पूर्णाङ्क)(d % 1000000));
    अन्यथा
        snprintf(buf, आकार, "%d.%06d",
                 (पूर्णाङ्क)(d / 1000000),
                 (पूर्णाङ्क)(d % 1000000));
    e = buf + वाक्यदैर्घ्यम्(buf);
    यावत् (e > buf && e[-1] == '0')
        *(--e) = 0;
    यदि (e > buf && e[-1] == '.')
        *(--e) = 0;
}

स्थिर पूर्णाङ्क opt_get_elem(ध्रुव AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ध्रुव शून्य *dst, पूर्णाङ्क अन्वेषणम्_flags)
{
    पूर्णाङ्क ret;

    विकल्प (TYPE_आधारः(o->type)) {
    पक्ष AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(पूर्णाङ्क *)dst));
        भङ्ग;
    पक्ष AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(पूर्णाङ्क *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(पूर्णाङ्क *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(अचिह्नित *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(भिन्न *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(द्विगुण *)dst);
        भङ्ग;
    पक्ष AV_OPT_TYPE_VIDEO_दरः:
    पक्ष AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->अङ्कः, ((AVRational *)dst)->den);
        भङ्ग;
    पक्ष AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        भङ्ग;
    पक्ष AV_OPT_TYPE_STRING:
        यदि (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } अन्यथा यदि (अन्वेषणम्_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = रिक्त;
            प्रत्यागम 0;
        } अन्यथा {
            *pbuf = av_strdup("");
        }
        प्रत्यागम *pbuf ? 0 : AVERROR(ENOMEM);
    पक्ष AV_OPT_TYPE_द्विमान: {
        ध्रुव uint8_t *bin;
        पूर्णाङ्क len;

        यदि (!*(uint8_t **)dst && (अन्वेषणम्_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            प्रत्यागम 0;
        }
        len = *(पूर्णाङ्क *)(((uint8_t *)dst) + परिमाण(uint8_t *));
        यदि ((uint64_t)len * 2 + 1 > अधिकतम_पूर्णाङ्कः)
            प्रत्यागम AVERROR(EINVAL);
        यदि (!(*pbuf = av_malloc(len * 2 + 1)))
            प्रत्यागम AVERROR(ENOMEM);
        यदि (!len) {
            *pbuf[0] = '\0';
            प्रत्यागम 0;
        }
        bin = *(uint8_t **)dst;
        प्रति (पूर्णाङ्क i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        प्रत्यागम 0;
    }
    पक्ष AV_OPT_TYPE_IMAGE_आकार:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((पूर्णाङ्क *)dst)[0], ((पूर्णाङ्क *)dst)[1]);
        भङ्ग;
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (वर्ण *)av_x_if_null(av_get_pix_fmt_name(*(गणना AVPixelFormat *)dst), "none"));
        भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (वर्ण *)av_x_if_null(av_get_sample_fmt_name(*(गणना AVSampleFormat *)dst), "none"));
        भङ्ग;
    पक्ष AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = वाक्यदैर्घ्यम्(*pbuf); // no overflow possible, checked by an assert
        भङ्ग;
    }
    पक्ष AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (पूर्णाङ्क)((uint8_t *)dst)[0], (पूर्णाङ्क)((uint8_t *)dst)[1],
                       (पूर्णाङ्क)((uint8_t *)dst)[2], (पूर्णाङ्क)((uint8_t *)dst)[3]);
        भङ्ग;
    पक्ष AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        भङ्ग;
    पक्ष AV_OPT_TYPE_DICT:
        यदि (!*(AVDictionary **)dst && (अन्वेषणम्_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            प्रत्यागम 0;
        }
        प्रत्यागम av_dict_get_string(*(AVDictionary **)dst, (वर्ण **)pbuf, '=', ':');
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क opt_get_array(ध्रुव AVOption *o, शून्य *dst, uint8_t **बहिर्गमनम्_val)
{
    ध्रुव अचिह्नित गणनम् = *opt_array_pcount(dst);
    ध्रुव uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = रिक्त;
    size_t   str_len = 0;
    पूर्णाङ्क ret;

    *बहिर्गमनम्_val = रिक्त;

    प्रति (अचिह्नित i = 0; i < गणनम्; i++) {
        uint8_t buf[128], *बहिर्गमनम् = buf;
        size_t बहिर्गमनम्_len;

        ret = opt_get_elem(o, &बहिर्गमनम्, परिमाण(buf),
                           opt_array_pelem(o, *(शून्य **)dst, i), 0);
        यदि (ret < 0)
            गच्छ fail;

        बहिर्गमनम्_len = वाक्यदैर्घ्यम्(बहिर्गमनम्);
        यदि (बहिर्गमनम्_len > SIZE_MAX / 2 - !!i ||
            !!i + बहिर्गमनम्_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            गच्छ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + बहिर्गमनम्_len * 2 + !!i);
        यदि (ret < 0)
            गच्छ fail;

        // add separator if needed
        यदि (i)
            str[str_len++] = sep;

        // escape the element
        प्रति (अचिह्नित j = 0; j < बहिर्गमनम्_len; j++) {
            uint8_t val = बहिर्गमनम्[j];
            यदि (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        यदि (बहिर्गमनम् != buf)
            av_freep(&बहिर्गमनम्);
        यदि (ret < 0) {
            av_freep(&str);
            प्रत्यागम ret;
        }
    }

    *बहिर्गमनम्_val = str;

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, uint8_t **बहिर्गमनम्_val)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    uint8_t *बहिर्गमनम्, buf[128];
    पूर्णाङ्क ret;

    यदि (!o || !target_obj || (o->विस्थापनम्<=0 && o->type != AV_OPT_TYPE_CONST))
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;

    यदि (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->विस्थापनम्;

    यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, बहिर्गमनम्_val);
        यदि (ret < 0)
            प्रत्यागम ret;
        यदि (!*बहिर्गमनम्_val && !(अन्वेषणम्_flags & AV_OPT_ALLOW_NULL)) {
            *बहिर्गमनम्_val = av_strdup("");
            यदि (!*बहिर्गमनम्_val)
               प्रत्यागम AVERROR(ENOMEM);
        }
        प्रत्यागम 0;
    }

    buf[0] = 0;
    बहिर्गमनम् = buf;
    ret = opt_get_elem(o, &बहिर्गमनम्, परिमाण(buf), dst, अन्वेषणम्_flags);
    यदि (ret < 0)
        प्रत्यागम ret;
    यदि (बहिर्गमनम् != buf) {
        *बहिर्गमनम्_val = बहिर्गमनम्;
        प्रत्यागम 0;
    }

    यदि (ret >= परिमाण(buf))
        प्रत्यागम AVERROR(EINVAL);
    *बहिर्गमनम्_val = av_strdup(बहिर्गमनम्);
    प्रत्यागम *बहिर्गमनम्_val ? 0 : AVERROR(ENOMEM);
}

स्थिर पूर्णाङ्क get_सङ्ख्या(शून्य *obj, ध्रुव वर्ण *name, द्विगुण *अङ्कः, पूर्णाङ्क *den, int64_t *intnum,
                      पूर्णाङ्क अन्वेषणम्_flags)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        प्रत्यागम AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->विस्थापनम्;

    प्रत्यागम read_सङ्ख्या(o, dst, अङ्कः, den, intnum);
}

पूर्णाङ्क av_opt_get_int(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, int64_t *बहिर्गमनम्_val)
{
    int64_t intnum = 1;
    द्विगुण अङ्कः = 1;
    पूर्णाङ्क ret, den = 1;

    यदि ((ret = get_सङ्ख्या(obj, name, &अङ्कः, &den, &intnum, अन्वेषणम्_flags)) < 0)
        प्रत्यागम ret;
    यदि (अङ्कः == den)
        *बहिर्गमनम्_val = intnum;
    अन्यथा
        *बहिर्गमनम्_val = अङ्कः * intnum / den;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_double(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, द्विगुण *बहिर्गमनम्_val)
{
    int64_t intnum = 1;
    द्विगुण अङ्कः = 1;
    पूर्णाङ्क ret, den = 1;

    यदि ((ret = get_सङ्ख्या(obj, name, &अङ्कः, &den, &intnum, अन्वेषणम्_flags)) < 0)
        प्रत्यागम ret;
    *बहिर्गमनम्_val = अङ्कः * intnum / den;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_q(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVRational *बहिर्गमनम्_val)
{
    int64_t intnum = 1;
    द्विगुण अङ्कः = 1;
    पूर्णाङ्क ret, den = 1;

    यदि ((ret = get_सङ्ख्या(obj, name, &अङ्कः, &den, &intnum, अन्वेषणम्_flags)) < 0)
        प्रत्यागम ret;

    यदि (अङ्कः == 1.0 && (पूर्णाङ्क)intnum == intnum)
        *बहिर्गमनम्_val = (AVRational){intnum, den};
    अन्यथा
        *बहिर्गमनम्_val = double_गन्तव्यम्_rational(अङ्कः*intnum/den);
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_image_आकार(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, पूर्णाङ्क *w_बहिर्गमनम्, पूर्णाङ्क *h_बहिर्गमनम्)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (o->type != AV_OPT_TYPE_IMAGE_आकार) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        प्रत्यागम AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->विस्थापनम्;
    यदि (w_बहिर्गमनम्) *w_बहिर्गमनम् = *(पूर्णाङ्क *)dst;
    यदि (h_बहिर्गमनम्) *h_बहिर्गमनम् = *((पूर्णाङ्क *)dst+1);
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_video_दरः(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVRational *बहिर्गमनम्_val)
{
    प्रत्यागम av_opt_get_q(obj, name, अन्वेषणम्_flags, बहिर्गमनम्_val);
}

स्थिर पूर्णाङ्क get_format(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, शून्य *बहिर्गमनम्_fmt,
                      गणना AVOptionType type, ध्रुव वर्ण *desc)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        प्रत्यागम AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->विस्थापनम्;
    यदि (type == AV_OPT_TYPE_PIXEL_FMT)
        *(गणना AVPixelFormat *)बहिर्गमनम्_fmt = *(गणना AVPixelFormat *)dst;
    अन्यथा
        *(गणना AVSampleFormat*)बहिर्गमनम्_fmt = *(गणना AVSampleFormat*)dst;

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_pixel_fmt(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, गणना AVPixelFormat *बहिर्गमनम्_fmt)
{
    प्रत्यागम get_format(obj, name, अन्वेषणम्_flags, बहिर्गमनम्_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

पूर्णाङ्क av_opt_get_sample_fmt(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, गणना AVSampleFormat *बहिर्गमनम्_fmt)
{
    प्रत्यागम get_format(obj, name, अन्वेषणम्_flags, बहिर्गमनम्_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

पूर्णाङ्क av_opt_get_chlayout(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVChannelLayout *cl)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        प्रत्यागम AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->विस्थापनम्;
    प्रत्यागम av_channel_layout_copy(cl, dst);
}

पूर्णाङ्क av_opt_get_dict_val(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVDictionary **बहिर्गमनम्_val)
{
    शून्य *target_obj;
    AVDictionary *src;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);

    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (o->type != AV_OPT_TYPE_DICT)
        प्रत्यागम AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->विस्थापनम्);

    प्रत्यागम av_dict_copy(बहिर्गमनम्_val, src, 0);
}

पूर्णाङ्क av_opt_flag_is_समुच्चयः(शून्य *obj, ध्रुव वर्ण *क्षेत्रम्_name, ध्रुव वर्ण *flag_name)
{
    ध्रुव AVOption *क्षेत्रम् = av_opt_find(obj, क्षेत्रम्_name, रिक्त, 0, 0);
    ध्रुव AVOption *flag  = av_opt_find(obj, flag_name,
                                        क्षेत्रम् ? क्षेत्रम्->unit : रिक्त, 0, 0);
    int64_t res;

    यदि (!क्षेत्रम् || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, क्षेत्रम्_name, 0, &res) < 0)
        प्रत्यागम 0;
    प्रत्यागम res & flag->default_val.i64;
}

स्थिर शून्य log_int_मानम्(शून्य *av_log_obj, पूर्णाङ्क level, int64_t i)
{
    यदि (i == अधिकतम_पूर्णाङ्कः) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा यदि (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा यदि (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा यदि (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा यदि (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

स्थिर शून्य log_मानम्(शून्य *av_log_obj, पूर्णाङ्क level, द्विगुण d)
{
    यदि      (d == अधिकतम_पूर्णाङ्कः) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा यदि (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा यदि (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा यदि (d == (द्विगुण)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा यदि (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा यदि (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } अन्यथा यदि (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } अन्यथा यदि (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } अन्यथा यदि (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } अन्यथा यदि (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } अन्यथा यदि (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } अन्यथा यदि (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } अन्यथा यदि (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%g", d);
    }
}

स्थिर ध्रुव वर्ण *get_opt_const_name(शून्य *obj, ध्रुव वर्ण *unit, int64_t मानम्)
{
    ध्रुव AVOption *opt = रिक्त;

    यदि (!unit)
        प्रत्यागम रिक्त;
    यावत् ((opt = av_opt_अग्र(obj, opt)))
        यदि (opt->type == AV_OPT_TYPE_CONST && !वाक्यं_तुलय(opt->unit, unit) &&
            opt->default_val.i64 == मानम्)
            प्रत्यागम opt->name;
    प्रत्यागम रिक्त;
}

स्थिर वर्ण *get_opt_flags_string(शून्य *obj, ध्रुव वर्ण *unit, int64_t मानम्)
{
    ध्रुव AVOption *opt = रिक्त;
    वर्ण flags[512];

    flags[0] = 0;
    यदि (!unit)
        प्रत्यागम रिक्त;
    यावत् ((opt = av_opt_अग्र(obj, opt))) {
        यदि (opt->type == AV_OPT_TYPE_CONST && !वाक्यं_तुलय(opt->unit, unit) &&
            opt->default_val.i64 & मानम्) {
            यदि (flags[0])
                av_strlcatf(flags, परिमाण(flags), "+");
            av_strlcatf(flags, परिमाण(flags), "%s", opt->name);
        }
    }
    यदि (flags[0])
        प्रत्यागम av_strdup(flags);
    प्रत्यागम रिक्त;
}

स्थिर शून्य log_type(शून्य *av_log_obj, ध्रुव AVOption *o,
                     गणना AVOptionType parent_type)
{
    ध्रुव गणना AVOptionType type = TYPE_आधारः(o->type);

    यदि (o->type == AV_OPT_TYPE_CONST && (TYPE_आधारः(parent_type) == AV_OPT_TYPE_INT || TYPE_आधारः(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    अन्यथा यदि (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        अन्यथा
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    अन्यथा
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

स्थिर शून्य log_default(शून्य *obj, शून्य *av_log_obj, ध्रुव AVOption *opt)
{
    यदि (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_द्विमान)
        प्रत्यागम;
    यदि ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_आकार ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_दरः) &&
        !opt->default_val.str)
        प्रत्यागम;

    यदि (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ध्रुव AVOptionArrayDef *arr = opt->default_val.arr;
        यदि (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        प्रत्यागम;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    विकल्प (opt->type) {
    पक्ष AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        भङ्ग;
    पक्ष AV_OPT_TYPE_FLAGS: {
        वर्ण *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        यदि (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } अन्यथा {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        भङ्ग;
    }
    पक्ष AV_OPT_TYPE_DURATION: {
        वर्ण buf[25];
        format_duration(buf, परिमाण(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        भङ्ग;
    }
    पक्ष AV_OPT_TYPE_UINT:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT64:
    पक्ष AV_OPT_TYPE_INT64: {
        ध्रुव वर्ण *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        यदि (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        अन्यथा
            log_int_मानम्(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        भङ्ग;
    }
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_FLOAT:
        log_मानम्(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, अधिकतम_पूर्णाङ्कः);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.अङ्कः, q.den); }
        भङ्ग;
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (वर्ण *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (वर्ण *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        भङ्ग;
    पक्ष AV_OPT_TYPE_COLOR:
    पक्ष AV_OPT_TYPE_IMAGE_आकार:
    पक्ष AV_OPT_TYPE_STRING:
    पक्ष AV_OPT_TYPE_DICT:
    पक्ष AV_OPT_TYPE_VIDEO_दरः:
    पक्ष AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        भङ्ग;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

स्थिर शून्य opt_list(शून्य *obj, शून्य *av_log_obj, ध्रुव वर्ण *unit,
                     पूर्णाङ्क req_flags, पूर्णाङ्क rej_flags, गणना AVOptionType parent_type)
{
    ध्रुव AVOption *opt = रिक्त;
    AVOptionRanges *r;
    पूर्णाङ्क i;

    यावत् ((opt = av_opt_अग्र(obj, opt))) {
        यदि (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            अनुवर्त;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        यदि (!unit && opt->type == AV_OPT_TYPE_CONST)
            अनुवर्त;
        अन्यथा यदि (unit && opt->type != AV_OPT_TYPE_CONST)
            अनुवर्त;
        अन्यथा यदि (unit && opt->type == AV_OPT_TYPE_CONST && वाक्यं_तुलय(unit, opt->unit))
            अनुवर्त;
        अन्यथा यदि (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        अन्यथा
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

        यदि (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        यदि (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_अन्वेषणम्_FAKE_OBJ) >= 0) {
            विकल्प (opt->type) {
            पक्ष AV_OPT_TYPE_INT:
            पक्ष AV_OPT_TYPE_UINT:
            पक्ष AV_OPT_TYPE_INT64:
            पक्ष AV_OPT_TYPE_UINT64:
            पक्ष AV_OPT_TYPE_DOUBLE:
            पक्ष AV_OPT_TYPE_FLOAT:
            पक्ष AV_OPT_TYPE_RATIONAL:
                प्रति (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_मानम्(av_log_obj, AV_LOG_INFO, r->range[i]->मानम्_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_मानम्(av_log_obj, AV_LOG_INFO, r->range[i]->मानम्_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                भङ्ग;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        यदि (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

पूर्णाङ्क av_opt_show2(शून्य *obj, शून्य *av_log_obj, पूर्णाङ्क req_flags, पूर्णाङ्क rej_flags)
{
    यदि (!obj)
        प्रत्यागम -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, रिक्त, req_flags, rej_flags, -1);

    प्रत्यागम 0;
}

शून्य av_opt_समुच्चयः_defaults(शून्य *s)
{
    av_opt_समुच्चयः_defaults2(s, 0, 0);
}

शून्य av_opt_समुच्चयः_defaults2(शून्य *s, पूर्णाङ्क आवरणम्_2, पूर्णाङ्क flags)
{
    ध्रुव AVOption *opt = रिक्त;
    यावत् ((opt = av_opt_अग्र(s, opt))) {
        शून्य *dst = ((uint8_t*)s) + opt->विस्थापनम्;

        यदि ((opt->flags & आवरणम्_2) != flags)
            अनुवर्त;

        यदि (opt->flags & AV_OPT_FLAG_READONLY)
            अनुवर्त;

        यदि (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ध्रुव AVOptionArrayDef *arr = opt->default_val.arr;
            ध्रुव वर्ण              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            यदि (arr && arr->def)
                opt_समुच्चयः_array(s, s, opt, arr->def, dst);

            अनुवर्त;
        }

        विकल्प (opt->type) {
            पक्ष AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                भङ्ग;
            पक्ष AV_OPT_TYPE_BOOL:
            पक्ष AV_OPT_TYPE_FLAGS:
            पक्ष AV_OPT_TYPE_INT:
            पक्ष AV_OPT_TYPE_UINT:
            पक्ष AV_OPT_TYPE_INT64:
            पक्ष AV_OPT_TYPE_UINT64:
            पक्ष AV_OPT_TYPE_DURATION:
            पक्ष AV_OPT_TYPE_PIXEL_FMT:
            पक्ष AV_OPT_TYPE_SAMPLE_FMT:
                write_सङ्ख्या(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:
            पक्ष AV_OPT_TYPE_FLOAT: {
                द्विगुण val;
                val = opt->default_val.dbl;
                write_सङ्ख्या(s, opt, dst, val, 1, 1, 1);
            }
            भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, अधिकतम_पूर्णाङ्कः);
                write_सङ्ख्या(s, opt, dst, 1, val.den, val.अङ्कः, 1);
            }
            भङ्ग;
            पक्ष AV_OPT_TYPE_COLOR:
                समुच्चयः_string_color(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_STRING:
                समुच्चयः_string(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_IMAGE_आकार:
                समुच्चयः_string_image_आकार(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_VIDEO_दरः:
                समुच्चयः_string_video_दरः(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_द्विमान:
                समुच्चयः_string_द्विमान(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_CHLAYOUT:
                समुच्चयः_string_channel_layout(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_DICT:
                समुच्चयः_string_dict(s, opt, opt->default_val.str, dst);
                भङ्ग;
        स्वभाव:
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
स्थिर पूर्णाङ्क parse_कुञ्चिका_मानम्_pair(शून्य *ctx, ध्रुव वर्ण **buf,
                                ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *युग्मानि_sep)
{
    वर्ण *कुञ्चिका = av_get_token(buf, कुञ्चिका_val_sep);
    वर्ण *val;
    पूर्णाङ्क ret;

    यदि (!कुञ्चिका)
        प्रत्यागम AVERROR(ENOMEM);

    यदि (*कुञ्चिका && strspn(*buf, कुञ्चिका_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, युग्मानि_sep);
        यदि (!val) {
            av_freep(&कुञ्चिका);
            प्रत्यागम AVERROR(ENOMEM);
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", कुञ्चिका);
        av_free(कुञ्चिका);
        प्रत्यागम AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", कुञ्चिका, val);

    ret = av_opt_समुच्चयः(ctx, कुञ्चिका, val, AV_OPT_अन्वेषणम्_CHILDREN);
    यदि (ret == AVERROR_OPTION_NOT_प्राप्तम्)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", कुञ्चिका);

    av_free(कुञ्चिका);
    av_free(val);
    प्रत्यागम ret;
}

पूर्णाङ्क av_समुच्चयः_options_string(शून्य *ctx, ध्रुव वर्ण *opts,
                          ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *युग्मानि_sep)
{
    पूर्णाङ्क ret, गणनम् = 0;

    यदि (!opts)
        प्रत्यागम 0;

    यावत् (*opts) {
        यदि ((ret = parse_कुञ्चिका_मानम्_pair(ctx, &opts, कुञ्चिका_val_sep, युग्मानि_sep)) < 0)
            प्रत्यागम ret;
        गणनम्++;

        यदि (*opts)
            opts++;
    }

    प्रत्यागम गणनम्;
}

#परिभाषय WHITESPACES " \n\t\r"

स्थिर पूर्णाङ्क is_कुञ्चिका_char(वर्ण c)
{
    प्रत्यागम (अचिह्नित)((c | 32) - 'a') < 26 ||
           (अचिह्नित)(c - '0') < 10 ||
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
स्थिर पूर्णाङ्क get_कुञ्चिका(ध्रुव वर्ण **ropts, ध्रुव वर्ण *delim, वर्ण **rkey)
{
    ध्रुव वर्ण *opts = *ropts;
    ध्रुव वर्ण *कुञ्चिका_start, *कुञ्चिका_अन्तः;

    कुञ्चिका_start = opts += strspn(opts, WHITESPACES);
    यावत् (is_कुञ्चिका_char(*opts))
        opts++;
    कुञ्चिका_अन्तः = opts;
    opts += strspn(opts, WHITESPACES);
    यदि (!*opts || !strchr(delim, *opts))
        प्रत्यागम AVERROR(EINVAL);
    opts++;
    यदि (!(*rkey = av_malloc(कुञ्चिका_अन्तः - कुञ्चिका_start + 1)))
        प्रत्यागम AVERROR(ENOMEM);
    स्मृतिं_प्रतिलिख(*rkey, कुञ्चिका_start, कुञ्चिका_अन्तः - कुञ्चिका_start);
    (*rkey)[कुञ्चिका_अन्तः - कुञ्चिका_start] = 0;
    *ropts = opts;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_कुञ्चिका_मानम्(ध्रुव वर्ण **ropts,
                         ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *युग्मानि_sep,
                         अचिह्नित flags,
                         वर्ण **rkey, वर्ण **rval)
{
    पूर्णाङ्क ret;
    वर्ण *कुञ्चिका = रिक्त, *val;
    ध्रुव वर्ण *opts = *ropts;

    यदि ((ret = get_कुञ्चिका(&opts, कुञ्चिका_val_sep, &कुञ्चिका)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_कुञ्चिका))
        प्रत्यागम AVERROR(EINVAL);
    यदि (!(val = av_get_token(&opts, युग्मानि_sep))) {
        av_free(कुञ्चिका);
        प्रत्यागम AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = कुञ्चिका;
    *rval  = val;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_समुच्चयः_from_string(शून्य *ctx, ध्रुव वर्ण *opts,
                           ध्रुव वर्ण *ध्रुव *shorthand,
                           ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *युग्मानि_sep)
{
    पूर्णाङ्क ret, गणनम् = 0;
    ध्रुव वर्ण *dummy_shorthand = रिक्त;
    ध्रुव वर्ण *कुञ्चिका;

    यदि (!opts)
        प्रत्यागम 0;
    यदि (!shorthand)
        shorthand = &dummy_shorthand;

    यावत् (*opts) {
        वर्ण *parsed_कुञ्चिका, *मानम्;
        ret = av_opt_get_कुञ्चिका_मानम्(&opts, कुञ्चिका_val_sep, युग्मानि_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_कुञ्चिका : 0,
                                   &parsed_कुञ्चिका, &मानम्);
        यदि (ret < 0) {
            यदि (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            अन्यथा
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            प्रत्यागम ret;
        }
        यदि (*opts)
            opts++;
        यदि (parsed_कुञ्चिका) {
            कुञ्चिका = parsed_कुञ्चिका;
            यावत् (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } अन्यथा {
            कुञ्चिका = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", कुञ्चिका, मानम्);
        यदि ((ret = av_opt_समुच्चयः(ctx, कुञ्चिका, मानम्, 0)) < 0) {
            यदि (ret == AVERROR_OPTION_NOT_प्राप्तम्)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", कुञ्चिका);
            av_free(मानम्);
            av_free(parsed_कुञ्चिका);
            प्रत्यागम ret;
        }

        av_free(मानम्);
        av_free(parsed_कुञ्चिका);
        गणनम्++;
    }
    प्रत्यागम गणनम्;
}

शून्य av_opt_free(शून्य *obj)
{
    ध्रुव AVOption *o = रिक्त;
    यावत् ((o = av_opt_अग्र(obj, o))) {
        शून्य *pitem = (uint8_t *)obj + o->विस्थापनम्;

        यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        अन्यथा
            opt_free_elem(o->type, pitem);
    }
}

पूर्णाङ्क av_opt_समुच्चयः_dict2(शून्य *obj, AVDictionary **options, पूर्णाङ्क अन्वेषणम्_flags)
{
    ध्रुव AVDictionary_प्रविष्टिः *t = रिक्त;
    AVDictionary    *tmp = रिक्त;
    पूर्णाङ्क ret;

    यदि (!options)
        प्रत्यागम 0;

    यावत् ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_समुच्चयः(obj, t->कुञ्चिका, t->मानम्, अन्वेषणम्_flags);
        यदि (ret == AVERROR_OPTION_NOT_प्राप्तम्)
            ret = av_dict_समुच्चयः(&tmp, t->कुञ्चिका, t->मानम्, AV_DICT_MULTIKEY);
        यदि (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->कुञ्चिका, t->मानम्);
            av_dict_free(&tmp);
            प्रत्यागम ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_समुच्चयः_dict(शून्य *obj, AVDictionary **options)
{
    प्रत्यागम av_opt_समुच्चयः_dict2(obj, options, 0);
}

ध्रुव AVOption *av_opt_find(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *unit,
                            पूर्णाङ्क opt_flags, पूर्णाङ्क अन्वेषणम्_flags)
{
    प्रत्यागम av_opt_find2(obj, name, unit, opt_flags, अन्वेषणम्_flags, रिक्त);
}

ध्रुव AVOption *av_opt_find2(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *unit,
                             पूर्णाङ्क opt_flags, पूर्णाङ्क अन्वेषणम्_flags, शून्य **target_obj)
{
    ध्रुव AVClass  *c;
    ध्रुव AVOption *o = रिक्त;

    यदि(!obj)
        प्रत्यागम रिक्त;

    c= *(AVClass**)obj;

    यदि (!c)
        प्रत्यागम रिक्त;

    यदि (अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_CHILDREN) {
        यदि (अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_FAKE_OBJ) {
            शून्य *iter = रिक्त;
            ध्रुव AVClass *child;
            यावत् (child = av_opt_child_class_iterate(c, &iter))
                यदि (o = av_opt_find2(&child, name, unit, opt_flags, अन्वेषणम्_flags, रिक्त))
                    प्रत्यागम o;
        } अन्यथा {
            शून्य *child = रिक्त;
            यावत् (child = av_opt_child_अग्र(obj, child))
                यदि (o = av_opt_find2(child, name, unit, opt_flags, अन्वेषणम्_flags, target_obj))
                    प्रत्यागम o;
        }
    }

    यावत् (o = av_opt_अग्र(obj, o)) {
        यदि (!वाक्यं_तुलय(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !वाक्यं_तुलय(o->unit, unit)))) {
            यदि (target_obj) {
                यदि (!(अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_FAKE_OBJ))
                    *target_obj = obj;
                अन्यथा
                    *target_obj = रिक्त;
            }
            प्रत्यागम o;
        }
    }
    प्रत्यागम रिक्त;
}

शून्य *av_opt_child_अग्र(शून्य *obj, शून्य *पूर्व)
{
    ध्रुव AVClass *c = *(AVClass **)obj;
    यदि (c->child_अग्र)
        प्रत्यागम c->child_अग्र(obj, पूर्व);
    प्रत्यागम रिक्त;
}

ध्रुव AVClass *av_opt_child_class_iterate(ध्रुव AVClass *parent, शून्य **iter)
{
    यदि (parent->child_class_iterate)
        प्रत्यागम parent->child_class_iterate(iter);
    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क opt_copy_elem(शून्य *logctx, गणना AVOptionType type,
                         शून्य *dst, ध्रुव शून्य *src)
{
    यदि (type == AV_OPT_TYPE_STRING) {
        ध्रुव वर्ण *src_str = *(ध्रुव वर्ण *ध्रुव *)src;
        वर्ण         **dstp =  (वर्ण **)dst;
        यदि (*dstp != src_str)
            av_freep(dstp);
        यदि (src_str) {
            *dstp = av_strdup(src_str);
            यदि (!*dstp)
                प्रत्यागम AVERROR(ENOMEM);
        }
    } अन्यथा यदि (type == AV_OPT_TYPE_द्विमान) {
        ध्रुव uint8_t *ध्रुव *src8 = (ध्रुव uint8_t *ध्रुव *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        पूर्णाङ्क len = *(ध्रुव पूर्णाङ्क *)(src8 + 1);
        यदि (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        यदि (len && !*dst8) {
            *(पूर्णाङ्क *)(dst8 + 1) = 0;
            प्रत्यागम AVERROR(ENOMEM);
        }
        *(पूर्णाङ्क *)(dst8 + 1) = len;
    } अन्यथा यदि (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } अन्यथा यदि (type == AV_OPT_TYPE_DICT) {
        ध्रुव AVDictionary *sdict = *(ध्रुव AVDictionary * ध्रुव *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        यदि (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = रिक्त;
        प्रत्यागम av_dict_copy(ddictp, sdict, 0);
    } अन्यथा यदि (type == AV_OPT_TYPE_CHLAYOUT) {
        ध्रुव AVChannelLayout *slayout = (ध्रुव AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        यदि (dlayout != slayout) {
            यदि (dlayout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM &&
                slayout->क्रमः == AV_CHANNEL_क्रमः_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = रिक्त;
            प्रत्यागम av_channel_layout_copy(dst, src);
        }
    } अन्यथा यदि (opt_is_pod(type)) {
        size_t आकार = opt_type_desc[type].आकार;
        स्मृतिं_प्रतिलिख(dst, src, आकार);
    } अन्यथा {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        प्रत्यागम AVERROR(EINVAL);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opt_copy_array(शून्य *logctx, ध्रुव AVOption *o,
                          शून्य **pdst, ध्रुव शून्य * ध्रुव *psrc)
{
    अचिह्नित nb_elems = *opt_array_pcount(psrc);
    शून्य         *dst = रिक्त;
    पूर्णाङ्क ret;

    यदि (*pdst == *psrc) {
        *pdst                   = रिक्त;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_आधारः(o->type)].आकार);
    यदि (!dst)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (अचिह्नित i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_आधारः(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(शून्य**)psrc, i));
        यदि (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            प्रत्यागम ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_copy(शून्य *dst, ध्रुव शून्य *src)
{
    ध्रुव AVOption *o = रिक्त;
    ध्रुव AVClass *c;
    पूर्णाङ्क ret = 0;

    यदि (!src)
        प्रत्यागम AVERROR(EINVAL);

    c = *(AVClass **)src;
    यदि (!c || c != *(AVClass **)dst)
        प्रत्यागम AVERROR(EINVAL);

    यावत् ((o = av_opt_अग्र(src, o))) {
        शून्य *क्षेत्रम्_dst = (uint8_t *)dst + o->विस्थापनम्;
        शून्य *क्षेत्रम्_src = (uint8_t *)src + o->विस्थापनम्;

        पूर्णाङ्क err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       क्षेत्रम्_dst, क्षेत्रम्_src) :
                  opt_copy_elem (dst, o->type, क्षेत्रम्_dst, क्षेत्रम्_src);
        यदि (err < 0)
            ret = err;
    }
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_get_array_आकार(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                          अचिह्नित पूर्णाङ्क *बहिर्गमनम्_val)
{
    शून्य *target_obj, *parray;
    ध्रुव AVOption *o;

    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        प्रत्यागम AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->विस्थापनम्;
    *बहिर्गमनम्_val = *opt_array_pcount(parray);

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_array(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                     अचिह्नित पूर्णाङ्क start_elem, अचिह्नित पूर्णाङ्क nb_elems,
                     गणना AVOptionType बहिर्गमनम्_type, शून्य *बहिर्गमनम्_val)
{
    ध्रुव size_t elem_आकार_बहिर्गमनम् = opt_type_desc[TYPE_आधारः(बहिर्गमनम्_type)].आकार;

    ध्रुव AVOption *o;
    शून्य *target_obj;

    ध्रुव शून्य *parray;
    अचिह्नित array_आकार;

    पूर्णाङ्क ret;

    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    यदि (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (बहिर्गमनम्_type & AV_OPT_TYPE_FLAG_ARRAY))
        प्रत्यागम AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->विस्थापनम्;
    array_आकार = *opt_array_pcount(parray);

    यदि (start_elem >= array_आकार ||
        array_आकार - start_elem < nb_elems)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (अचिह्नित i = 0; i < nb_elems; i++) {
        ध्रुव शून्य *src = opt_array_pelem(o, *(शून्य**)parray, start_elem + i);
        शून्य       *dst = (uint8_t*)बहिर्गमनम्_val + i * elem_आकार_बहिर्गमनम्;

        यदि (बहिर्गमनम्_type == TYPE_आधारः(o->type)) {
            ret = opt_copy_elem(obj, बहिर्गमनम्_type, dst, src);
            यदि (ret < 0)
                गच्छ fail;
        } अन्यथा यदि (बहिर्गमनम्_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *बहिर्गमनम् = buf;

            ret = opt_get_elem(o, &बहिर्गमनम्, परिमाण(buf), src, अन्वेषणम्_flags);
            यदि (ret < 0)
                गच्छ fail;

            यदि (बहिर्गमनम् == buf) {
                बहिर्गमनम् = av_strdup(buf);
                यदि (!बहिर्गमनम्) {
                    ret = AVERROR(ENOMEM);
                    गच्छ fail;
                }
            }

            *(uint8_t**)dst = बहिर्गमनम्;
        } अन्यथा यदि (बहिर्गमनम्_type == AV_OPT_TYPE_INT64    ||
                   बहिर्गमनम्_type == AV_OPT_TYPE_DOUBLE   ||
                   बहिर्गमनम्_type == AV_OPT_TYPE_RATIONAL) {
            द्विगुण     अङ्कः = 1.0;
            पूर्णाङ्क        den = 1;
            int64_t intnum = 1;

            ret = read_सङ्ख्या(o, src, &अङ्कः, &den, &intnum);
            यदि (ret < 0)
                गच्छ fail;

            विकल्प (बहिर्गमनम्_type) {
            पक्ष AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (अङ्कः == den) ?  intnum : अङ्कः * intnum / den;
                भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:
                *(द्विगुण*)dst = अङ्कः * intnum / den;
                भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (अङ्कः == 1.0 && (पूर्णाङ्क)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_गन्तव्यम्_rational(अङ्कः * intnum / den);
                भङ्ग;
            स्वभाव: av_assert0(0);
            }
        } अन्यथा
            प्रत्यागम AVERROR(ENOSYS);
    }

    प्रत्यागम 0;
fail:
    प्रति (अचिह्नित i = 0; i < nb_elems; i++)
        opt_free_elem(बहिर्गमनम्_type, (uint8_t*)बहिर्गमनम्_val + i * elem_आकार_बहिर्गमनम्);
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_समुच्चयः_array(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                     अचिह्नित पूर्णाङ्क start_elem, अचिह्नित पूर्णाङ्क nb_elems,
                     गणना AVOptionType val_type, ध्रुव शून्य *val)
{
    ध्रुव size_t elem_आकार_val = opt_type_desc[TYPE_आधारः(val_type)].आकार;

    ध्रुव AVOption *o;
    ध्रुव AVOptionArrayDef *arr;
    शून्य *target_obj;

    शून्य *parray;
    शून्य *new_elems;
    अचिह्नित *array_आकार, new_आकार;
    size_t elem_आकार;

    पूर्णाङ्क ret = 0;

    ret = opt_समुच्चयः_init(obj, name, अन्वेषणम्_flags, 0, &target_obj, &o, &parray);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        प्रत्यागम AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_आकार = opt_array_pcount(parray);
    elem_आकार  = opt_type_desc[TYPE_आधारः(o->type)].आकार;

    यदि (start_elem > *array_आकार)
        प्रत्यागम AVERROR(EINVAL);

    // compute new array size
    यदि (!val) {
        यदि (*array_आकार - start_elem < nb_elems)
            प्रत्यागम AVERROR(EINVAL);

        new_आकार = *array_आकार - nb_elems;
    } अन्यथा यदि (अन्वेषणम्_flags & AV_OPT_ARRAY_REPLACE) {
        यदि (start_elem >= UINT_MAX - nb_elems)
            प्रत्यागम AVERROR(EINVAL);

        new_आकार = FFMAX(*array_आकार, start_elem + nb_elems);
    } अन्यथा {
        यदि (nb_elems >= UINT_MAX - *array_आकार)
            प्रत्यागम AVERROR(EINVAL);

        new_आकार = *array_आकार + nb_elems;
    }

    यदि (arr &&
        ((arr->आकार_max && new_आकार > arr->आकार_max) ||
         (arr->आकार_min && new_आकार < arr->आकार_min)))
        प्रत्यागम AVERROR(EINVAL);

    // desired operation is shrinking the array
    यदि (!val) {
        शून्य *array = *(शून्य**)parray;

        प्रति (अचिह्नित i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        यदि (new_आकार > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_आकार * (*array_आकार - start_elem - nb_elems));

            array = av_realloc_array(array, new_आकार, elem_आकार);
            यदि (!array)
                प्रत्यागम AVERROR(ENOMEM);

            *(शून्य**)parray = array;
        } अन्यथा
            av_freep(parray);

        *array_आकार = new_आकार;

        प्रत्यागम 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_आकार);
    यदि (!new_elems)
        प्रत्यागम AVERROR(ENOMEM);

    // convert/validate each new element
    प्रति (अचिह्नित i = 0; i < nb_elems; i++) {
        शून्य       *dst = opt_array_pelem(o, new_elems, i);
        ध्रुव शून्य *src = (uint8_t*)val + i * elem_आकार_val;

        द्विगुण     अङ्कः = 1.0;
        पूर्णाङ्क        den = 1;
        int64_t intnum = 1;

        यदि (val_type == TYPE_आधारः(o->type)) {
            पूर्णाङ्क err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            यदि (ret < 0)
                गच्छ fail;

            // validate the range for numeric options
            err = read_सङ्ख्या(o, dst, &अङ्कः, &den, &intnum);
            यदि (err >= 0 && TYPE_आधारः(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < अङ्कः * intnum || o->min * den > अङ्कः * intnum)) {
                अङ्कः = den ? अङ्कः * intnum / den : (अङ्कः && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, अङ्कः, o->min, o->max);
                ret = AVERROR(ERANGE);
                गच्छ fail;
            }
        } अन्यथा यदि (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_समुच्चयः_elem(obj, target_obj, o, *(ध्रुव वर्ण **)src, dst);
            यदि (ret < 0)
                गच्छ fail;
        } अन्यथा यदि (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            विकल्प (val_type) {
            पक्ष AV_OPT_TYPE_INT:       intnum = *(पूर्णाङ्क*)src;                भङ्ग;
            पक्ष AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            भङ्ग;
            पक्ष AV_OPT_TYPE_FLOAT:     अङ्कः    = *(भिन्न*)src;              भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:    अङ्कः    = *(द्विगुण*)src;             भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->अङ्कः;
                                        den    = ((AVRational*)src)->den;   भङ्ग;
            स्वभाव: av_assert0(0);
            }

            ret = write_सङ्ख्या(obj, o, dst, अङ्कः, den, intnum, 0);
            यदि (ret < 0)
                गच्छ fail;
        } अन्यथा {
            ret = AVERROR(ENOSYS);
            गच्छ fail;
        }
    }

    // commit new elements to the array
    यदि (start_elem == 0 && nb_elems == new_आकार) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_आकार);
        *(शून्य**)parray = new_elems;
        *array_आकार     = nb_elems;

        new_elems = रिक्त;
        nb_elems  = 0;
    } अन्यथा {
        शून्य *array = av_realloc_array(*(शून्य**)parray, new_आकार, elem_आकार);
        यदि (!array) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }

        यदि (अन्वेषणम्_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            प्रति (अचिह्नित i = start_elem; i < FFMIN(start_elem + nb_elems, *array_आकार); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } अन्यथा {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_आकार * (*array_आकार - start_elem));
        }

        स्मृतिं_प्रतिलिख((uint8_t*)array + elem_आकार * start_elem, new_elems, elem_आकार * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(शून्य**)parray = array;
        *array_आकार     = new_आकार;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_query_ranges(AVOptionRanges **ranges_arg, शून्य *obj, ध्रुव वर्ण *कुञ्चिका, पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;
    ध्रुव AVClass *c = *(AVClass**)obj;
    पूर्णाङ्क (*callback)(AVOptionRanges **, शून्य *obj, ध्रुव वर्ण *कुञ्चिका, पूर्णाङ्क flags) = c->query_ranges;

    यदि (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, कुञ्चिका, flags);
    यदि (ret >= 0) {
        यदि (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_query_ranges_default(AVOptionRanges **ranges_arg, शून्य *obj, ध्रुव वर्ण *कुञ्चिका, पूर्णाङ्क flags)
{
    AVOptionRanges *ranges = av_mallocz(परिमाण(*ranges));
    AVOptionRange **range_array = av_mallocz(परिमाण(शून्य*));
    AVOptionRange *range = av_mallocz(परिमाण(*range));
    ध्रुव AVOption *क्षेत्रम् = av_opt_find(obj, कुञ्चिका, रिक्त, 0, flags);
    पूर्णाङ्क ret;

    *ranges_arg = रिक्त;

    यदि (!ranges || !range || !range_array || !क्षेत्रम्) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->मानम्_min = क्षेत्रम्->min;
    range->मानम्_max = क्षेत्रम्->max;

    विकल्प (क्षेत्रम्->type) {
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
    पक्ष AV_OPT_TYPE_FLOAT:
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_COLOR:
        भङ्ग;
    पक्ष AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->मानम्_min = -1;
        range->मानम्_max = अधिकतम_पूर्णाङ्कः;
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = अधिकतम_पूर्णाङ्कः;
        भङ्ग;
    पक्ष AV_OPT_TYPE_IMAGE_आकार:
        range->component_min = 0;
        range->component_max = अधिकतम_पूर्णाङ्कः/128/8;
        range->मानम्_min = 0;
        range->मानम्_max = अधिकतम_पूर्णाङ्कः/8;
        भङ्ग;
    पक्ष AV_OPT_TYPE_VIDEO_दरः:
        range->component_min = 1;
        range->component_max = अधिकतम_पूर्णाङ्कः;
        range->मानम्_min = 1;
        range->मानम्_max = अधिकतम_पूर्णाङ्कः;
        भङ्ग;
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    *ranges_arg = ranges;
    प्रत्यागम 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    प्रत्यागम ret;
}

शून्य av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    पूर्णाङ्क i;
    AVOptionRanges *ranges = *rangesp;

    यदि (!ranges)
        प्रत्यागम;

    प्रति (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        यदि (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

पूर्णाङ्क av_opt_is_समुच्चयः_गन्तव्यम्_default(शून्य *obj, ध्रुव AVOption *o)
{
    int64_t i64;
    द्विगुण d;
    AVRational q;
    पूर्णाङ्क ret, w, h;
    वर्ण *str;
    शून्य *dst;

    यदि (!o || !obj)
        प्रत्यागम AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->विस्थापनम्;

    यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ध्रुव वर्ण *def = o->default_val.arr ? o->default_val.arr->def : रिक्त;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        यदि (ret < 0)
            प्रत्यागम ret;

        यदि (!!val != !!def)
            ret = 0;
        अन्यथा यदि (val)
            ret = !वाक्यं_तुलय(val, def);
        अन्यथा
            ret = 1;

        av_freep(&val);

        प्रत्यागम ret;
    }

    विकल्प (o->type) {
    पक्ष AV_OPT_TYPE_CONST:
        प्रत्यागम 1;
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
        read_सङ्ख्या(o, dst, रिक्त, रिक्त, &i64);
        प्रत्यागम o->default_val.i64 == i64;
    पक्ष AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        यदि (o->default_val.str) {
            यदि ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                प्रत्यागम ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        प्रत्यागम ret;
    }
    पक्ष AV_OPT_TYPE_STRING:
        str = *(वर्ण **)dst;
        यदि (str == o->default_val.str) //2 NULLs
            प्रत्यागम 1;
        यदि (!str || !o->default_val.str) //1 NULL
            प्रत्यागम 0;
        प्रत्यागम !वाक्यं_तुलय(str, o->default_val.str);
    पक्ष AV_OPT_TYPE_DOUBLE:
        d = *(द्विगुण *)dst;
        प्रत्यागम o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    पक्ष AV_OPT_TYPE_FLOAT:
        d = *(भिन्न *)dst;
        प्रत्यागम (भिन्न)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    पक्ष AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, अधिकतम_पूर्णाङ्कः);
        प्रत्यागम !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    पक्ष AV_OPT_TYPE_द्विमान: {
        संरचना {
            uint8_t *दत्त;
            पूर्णाङ्क आकार;
        } tmp = {0};
        पूर्णाङ्क opt_आकार = *(पूर्णाङ्क *)((शून्य **)dst + 1);
        शून्य *opt_ptr = *(शून्य **)dst;
        यदि (!opt_आकार && (!o->default_val.str || !वाक्यदैर्घ्यम्(o->default_val.str)))
            प्रत्यागम 1;
        यदि (!opt_आकार ||  !o->default_val.str || !वाक्यदैर्घ्यम्(o->default_val.str ))
            प्रत्यागम 0;
        यदि (opt_आकार != वाक्यदैर्घ्यम्(o->default_val.str) / 2)
            प्रत्यागम 0;
        ret = समुच्चयः_string_द्विमान(रिक्त, रिक्त, o->default_val.str, &tmp.दत्त);
        यदि (!ret)
            ret = !memcmp(opt_ptr, tmp.दत्त, tmp.आकार);
        av_free(tmp.दत्त);
        प्रत्यागम ret;
    }
    पक्ष AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = रिक्त;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ध्रुव AVDictionary_प्रविष्टिः *en1 = रिक्त;
        ध्रुव AVDictionary_प्रविष्टिः *en2 = रिक्त;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        यदि (ret < 0) {
            av_dict_free(&dict1);
            प्रत्यागम ret;
        }
        कुरु {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } यावत् (en1 && en2 && !वाक्यं_तुलय(en1->कुञ्चिका, en2->कुञ्चिका) && !वाक्यं_तुलय(en1->मानम्, en2->मानम्));
        av_dict_free(&dict1);
        प्रत्यागम (!en1 && !en2);
    }
    पक्ष AV_OPT_TYPE_IMAGE_आकार:
        यदि (!o->default_val.str || !वाक्यं_तुलय(o->default_val.str, "none"))
            w = h = 0;
        अन्यथा यदि ((ret = av_parse_video_आकार(&w, &h, o->default_val.str)) < 0)
            प्रत्यागम ret;
        प्रत्यागम (w == *(पूर्णाङ्क *)dst) && (h == *((पूर्णाङ्क *)dst+1));
    पक्ष AV_OPT_TYPE_VIDEO_दरः:
        q = (AVRational){0, 0};
        यदि (o->default_val.str) {
            यदि ((ret = av_parse_video_दरः(&q, o->default_val.str)) < 0)
                प्रत्यागम ret;
        }
        प्रत्यागम !av_cmp_q(*(AVRational*)dst, q);
    पक्ष AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        यदि (o->default_val.str) {
            यदि ((ret = av_parse_color(color, o->default_val.str, -1, रिक्त)) < 0)
                प्रत्यागम ret;
        }
        प्रत्यागम !memcmp(color, dst, परिमाण(color));
    }
    स्वभाव:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        भङ्ग;
    }
    प्रत्यागम AVERROR_PATCHWELCOME;
}

पूर्णाङ्क av_opt_is_समुच्चयः_गन्तव्यम्_default_by_name(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags)
{
    ध्रुव AVOption *o;
    शून्य *target;
    यदि (!obj)
        प्रत्यागम AVERROR(EINVAL);
    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target);
    यदि (!o)
        प्रत्यागम AVERROR_OPTION_NOT_प्राप्तम्;
    प्रत्यागम av_opt_is_समुच्चयः_गन्तव्यम्_default(target, o);
}

स्थिर पूर्णाङ्क opt_serialize(शून्य *obj, पूर्णाङ्क opt_flags, पूर्णाङ्क flags, पूर्णाङ्क *cnt,
                         AVBPrint *bprint, ध्रुव वर्ण कुञ्चिका_val_sep, ध्रुव वर्ण युग्मानि_sep)
{
    ध्रुव AVOption *o = रिक्त;
    शून्य *child = रिक्त;
    uint8_t *buf;
    पूर्णाङ्क ret;
    ध्रुव वर्ण special_chars[] = {युग्मानि_sep, कुञ्चिका_val_sep, '\0'};

    यदि (flags & AV_OPT_SERIALIZE_अन्वेषणम्_CHILDREN)
        यावत् (child = av_opt_child_अग्र(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                कुञ्चिका_val_sep, युग्मानि_sep);
            यदि (ret < 0)
                प्रत्यागम ret;
        }

    यावत् (o = av_opt_अग्र(obj, o)) {
        यदि (o->type == AV_OPT_TYPE_CONST)
            अनुवर्त;
        यदि ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            यदि ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                यदि (o->flags == opt_flags)
                    अनुवर्त;
            } अन्यथा यदि ((o->flags & opt_flags) == opt_flags)
                अनुवर्त;
        } अन्यथा {
            यदि ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                अनुवर्त;
            अन्यथा यदि (((o->flags & opt_flags) != opt_flags))
                अनुवर्त;
        }
        यदि (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_समुच्चयः_गन्तव्यम्_default(obj, o) > 0)
            अनुवर्त;
        यदि ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, रिक्त);
            प्रत्यागम ret;
        }
        यदि (buf) {
            यदि ((*cnt)++)
                av_bprint_append_दत्त(bprint, &युग्मानि_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_बहुलकम्_BACKSLASH, 0);
            av_bprint_append_दत्त(bprint, &कुञ्चिका_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_बहुलकम्_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_serialize(शून्य *obj, पूर्णाङ्क opt_flags, पूर्णाङ्क flags, वर्ण **बफर,
                     ध्रुव वर्ण कुञ्चिका_val_sep, ध्रुव वर्ण युग्मानि_sep)
{
    AVBPrint bprint;
    पूर्णाङ्क ret, cnt = 0;

    यदि (युग्मानि_sep == '\0' || कुञ्चिका_val_sep == '\0' || युग्मानि_sep == कुञ्चिका_val_sep ||
        युग्मानि_sep == '\\' || कुञ्चिका_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (!obj || !बफर)
        प्रत्यागम AVERROR(EINVAL);

    *बफर = रिक्त;
    av_bprint_init(&bprint, 64, AV_BPRINT_आकार_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        कुञ्चिका_val_sep, युग्मानि_sep);
    यदि (ret < 0)
        प्रत्यागम ret;

    ret = av_bprint_finalize(&bprint, बफर);
    यदि (ret < 0)
        प्रत्यागम ret;
    प्रत्यागम 0;
}
