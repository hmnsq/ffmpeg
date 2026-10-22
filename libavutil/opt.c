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

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ध्रुव AVOption *av_opt_next(ध्रुव शून्य *obj, ध्रुव AVOption *last)
{
    ध्रुव AVClass *class;
    यदि (!obj)
        प्रत्यागम रिक्त;
    class = *(ध्रुव AVClass**)obj;
    यदि (!last && class && class->option && class->option[0].name)
        प्रत्यागम class->option;
    यदि (last && last[1].name)
        प्रत्यागम ++last;
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव संरचना {
    माप_प्रकार      size;
    ध्रुव वर्ण *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { परिमाण(अचिन्हित),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { परिमाण(पूर्णाङ्क),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { परिमाण(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { परिमाण(अचिन्हित),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { परिमाण(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { परिमाण(द्विगुण),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { परिमाण(भिन्न),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { परिमाण(वर्ण *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { परिमाण(AVRational),     "<rational>" },
    [AV_OPT_TYPE_द्विआधारी]        = { परिमाण(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { परिमाण(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { परिमाण(पूर्णाङ्क[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { परिमाण(AVRational),     "<video_rate>" },
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
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
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

स्थिर शून्य *opt_array_pelem(ध्रुव AVOption *o, शून्य *array, अचिन्हित idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    प्रत्यागम (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

स्थिर अचिन्हित *opt_array_pcount(ध्रुव शून्य *parray)
{
    प्रत्यागम (अचिन्हित *)((ध्रुव शून्य * ध्रुव *)parray + 1);
}

स्थिर शून्य opt_free_elem(गणना AVOptionType type, शून्य *ptr)
{
    विकल्प (TYPE_BASE(type)) {
    पक्ष AV_OPT_TYPE_STRING:
    पक्ष AV_OPT_TYPE_द्विआधारी:
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

स्थिर शून्य opt_free_array(ध्रुव AVOption *o, शून्य *parray, अचिन्हित *गिनती)
{
    प्रति (अचिन्हित i = 0; i < *गिनती; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(शून्य **)parray, i));

    av_freep(parray);
    *गिनती = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
स्थिर पूर्णाङ्क opt_set_init(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags,
                        पूर्णाङ्क require_type,
                        शून्य **ptgt, ध्रुव AVOption **po, शून्य **pdst)
{
    शून्य *logctx;
    ध्रुव AVOption *o;
    शून्य *tgt;

    o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &tgt);
    यदि (!o || (!tgt && !(खोज_flags & AV_OPT_खोज_FAKE_OBJ)))
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;

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
        अचिन्हित *state_flags = रिक्त;
        ध्रुव AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ध्रुव AVClass**)tgt;
        यदि (class->state_flags_offset)
            state_flags = (अचिन्हित*)((uint8_t*)tgt + class->state_flags_offset);

        यदि (!state_flags && obj != tgt) {
            class = *(ध्रुव AVClass**)obj;
            यदि (class->state_flags_offset)
                state_flags = (अचिन्हित*)((uint8_t*)obj + class->state_flags_offset);
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
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : रिक्त;

    प्रत्यागम 0;
}

स्थिर AVRational double_to_rational(द्विगुण d)
{
     AVRational r = av_d2q(d, 1 << 24);
     यदि ((!r.अंक || !r.den) && d)
         r = av_d2q(d, पूर्णांक_उच्च);
     प्रत्यागम r;
}

स्थिर पूर्णाङ्क read_संख्या(ध्रुव AVOption *o, ध्रुव शून्य *dst, द्विगुण *अंक, पूर्णाङ्क *den, int64_t *intnum)
{
    विकल्प (TYPE_BASE(o->type)) {
    पक्ष AV_OPT_TYPE_FLAGS:
        *intnum = *(अचिन्हित पूर्णाङ्क*)dst;
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
        *intnum = *(अचिन्हित पूर्णाङ्क *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_FLOAT:
        *अंक = *(भिन्न *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_DOUBLE:
        *अंक = *(द्विगुण *)dst;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->अंक;
        *den    = ((AVRational *)dst)->den;
        प्रत्यागम 0;
    पक्ष AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        प्रत्यागम 0;
    }
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क write_संख्या(शून्य *obj, ध्रुव AVOption *o, शून्य *dst,
                        द्विगुण अंक, पूर्णाङ्क den, int64_t intnum,
                        पूर्णाङ्क ignore_range)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);

    यदि (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < अंक * intnum || o->min * den > अंक * intnum)) {
        अंक = den ? अंक * intnum / den : (अंक && intnum ? अनन्त : न_अंक);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               अंक, o->name, o->min, o->max);
        प्रत्यागम AVERROR(दुस्फल);
    }
    यदि (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        द्विगुण d = अंक*intnum/den;
        यदि (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   अंक*intnum/den, o->name);
            प्रत्यागम AVERROR(दुस्फल);
        }
    }

    यदि (!dst)
        प्रत्यागम 0;

    विकल्प (type) {
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        *(गणना AVPixelFormat *)dst = llrint(अंक / den) * intnum;
        भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        *(गणना AVSampleFormat *)dst = llrint(अंक / den) * intnum;
        भङ्ग;
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
        *(पूर्णाङ्क *)dst = llrint(अंक / den) * intnum;
        भङ्ग;
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_INT64:{
        द्विगुण d = अंक / den;
        यदि (intnum == 1 && d == (द्विगुण)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } अन्यथा
            *(int64_t *)dst = llrint(d) * intnum;
        भङ्ग;}
    पक्ष AV_OPT_TYPE_UINT64:{
        द्विगुण d = अंक / den;
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
        *(भिन्न *)dst = अंक * intnum / den;
        भङ्ग;
    पक्ष AV_OPT_TYPE_DOUBLE:
        *(द्विगुण    *)dst = अंक * intnum / den;
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL:
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
        यदि ((पूर्णाङ्क) अंक == अंक)
            *(AVRational *)dst = (AVRational) { अंक *intnum, den };
        अन्यथा
            *(AVRational *)dst = double_to_rational(अंक * intnum / den);
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

स्थिर पूर्णाङ्क set_string_द्विआधारी(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    पूर्णाङ्क *lendst;
    uint8_t *bin, *ptr;
    पूर्णाङ्क len;

    यदि (dst) {
        lendst = (पूर्णाङ्क *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    यदि (!val || !(len = म_माप(val)))
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

स्थिर पूर्णाङ्क set_string(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    यदि (!dst)
        प्रत्यागम 0;
    av_freep(dst);
    यदि (!val)
        प्रत्यागम 0;
    *dst = av_strdup(val);
    प्रत्यागम *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

स्थिर पूर्णाङ्क set_string_संख्या(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);
    पूर्णाङ्क ret = 0;

    यदि (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        पूर्णाङ्क अंक, den;
        वर्ण c;
        यदि (माला_पूछो(val, "%d%*1[:/]%d%c", &अंक, &den, &c) == 2) {
            यदि ((ret = write_संख्या(obj, o, dst, 1, den, अंक, 0)) >= 0)
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
            द्विगुण const_मूल्यावली[64];
            ध्रुव वर्ण * const_names[64];
            पूर्णाङ्क खोज_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_खोज_CHILDREN : 0;
            ध्रुव AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, खोज_flags);
            यदि (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                यदि (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } अन्यथा {
                यदि (o->unit) {
                    प्रति (o_named = रिक्त; o_named = av_opt_next(target_obj, o_named); ) {
                        यदि (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !म_भेद(o_named->unit, o->unit)) {
                            यदि (ci + 6 >= FF_ARRAY_ELEMS(const_मूल्यावली)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                प्रत्यागम AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_मूल्यावली[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_मूल्यावली[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_मूल्यावली[ci++] = o->max;
                const_names [ci  ] = "min";
                const_मूल्यावली[ci++] = o->min;
                const_names [ci  ] = "none";
                const_मूल्यावली[ci++] = 0;
                const_names [ci  ] = "all";
                const_मूल्यावली[ci++] = ~0;
                const_names [ci] = रिक्त;
                const_मूल्यावली[ci] = 0;

                res = av_व्यंजक_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_मूल्यावली, रिक्त, रिक्त, रिक्त, रिक्त, रिक्त, 0, obj);
                यदि (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    प्रत्यागम res;
                }
            }
        }
        यदि (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(अचिन्हित पूर्णाङ्क*)dst;
            यदि (cmd == '+')
                d = intnum | (int64_t)d;
            अन्यथा यदि (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        यदि ((ret = write_संख्या(obj, o, dst, d, 1, 1, 0)) < 0)
            प्रत्यागम ret;
        val += i;
        यदि (!i || !*val)
            प्रत्यागम 0;
    }
}

स्थिर पूर्णाङ्क set_string_image_size(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, पूर्णाङ्क *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क tmp[2];
    पूर्णाङ्क ret;

    यदि (!val || !म_भेद(val, "none")) {
        यदि (dst) {
        dst[0] =
        dst[1] = 0;
        }
        प्रत्यागम 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    यदि (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        प्रत्यागम ret;
    }
    यदि (dst)
        स_नकल(dst, tmp, परिमाण(tmp));
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क set_string_video_rate(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, AVRational *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    AVRational tmp;
    पूर्णाङ्क ret = av_parse_video_rate(&tmp, val);
    यदि (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    यदि (dst)
        *dst = tmp;
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क set_string_color(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
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
            स_नकल(dst, tmp, परिमाण(tmp));
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

स्थिर पूर्णाङ्क set_string_bool(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, पूर्णाङ्क *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क n;

    यदि (!val)
        प्रत्यागम 0;

    यदि (!म_भेद(val, "auto")) {
        n = -1;
    } अन्यथा यदि (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } अन्यथा यदि (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } अन्यथा {
        वर्ण *end = रिक्त;
        n = म_से_दीर्घ(val, &end, 10);
        यदि (val + म_माप(val) != end)
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

स्थिर पूर्णाङ्क set_string_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst,
                          पूर्णाङ्क fmt_nb, पूर्णाङ्क ((*get_fmt)(ध्रुव वर्ण *)), ध्रुव वर्ण *desc,
                          गणना AVOptionType type)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क fmt, min, max;

    यदि (!val || !म_भेद(val, "none")) {
        fmt = -1;
    } अन्यथा {
        fmt = get_fmt(val);
        यदि (fmt == -1) {
            वर्ण *tail;
            fmt = म_से_दीर्घ(val, &tail, 0);
            यदि (*tail || (अचिन्हित)fmt >= fmt_nb) {
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
        प्रत्यागम AVERROR(दुस्फल);
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

स्थिर पूर्णाङ्क set_string_pixel_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    प्रत्यागम set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

स्थिर पूर्णाङ्क get_sample_fmt(ध्रुव वर्ण *name)
{
    प्रत्यागम av_get_sample_fmt(name);
}

स्थिर पूर्णाङ्क set_string_sample_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    प्रत्यागम set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

स्थिर पूर्णाङ्क set_string_dict(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
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

स्थिर पूर्णाङ्क set_string_channel_layout(शून्य *obj, ध्रुव AVOption *o,
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

स्थिर पूर्णाङ्क opt_set_elem(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o,
                        ध्रुव वर्ण *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);
    पूर्णाङ्क ret;

    यदि (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        प्रत्यागम AVERROR(EINVAL);

    विकल्प (type) {
    पक्ष AV_OPT_TYPE_BOOL:
        प्रत्यागम set_string_bool(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_STRING:
        प्रत्यागम set_string(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_द्विआधारी:
        प्रत्यागम set_string_द्विआधारी(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
    पक्ष AV_OPT_TYPE_FLOAT:
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_RATIONAL:
        प्रत्यागम set_string_संख्या(obj, target_obj, o, val, dst);
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
        प्रत्यागम set_string_image_size(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        यदि (ret < 0)
            प्रत्यागम ret;
        प्रत्यागम write_संख्या(obj, o, dst, 1, tmp.den, tmp.अंक, 0);
    }
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        प्रत्यागम set_string_pixel_fmt(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        प्रत्यागम set_string_sample_fmt(obj, o, val, dst);
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
                प्रत्यागम AVERROR(दुस्फल);
            }
            यदि (dst)
            *(int64_t *)dst = usecs;
            प्रत्यागम 0;
        }
    पक्ष AV_OPT_TYPE_COLOR:
        प्रत्यागम set_string_color(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        यदि (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        प्रत्यागम ret;
    पक्ष AV_OPT_TYPE_DICT:
        प्रत्यागम set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क opt_set_array(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o,
                         ध्रुव वर्ण *val, शून्य *dst)
{
    ध्रुव AVOptionArrayDef *arr = o->default_val.arr;
    ध्रुव माप_प्रकार      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ध्रुव uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = रिक्त;

    शून्य      *logctx = dst ? obj : रिक्त;
    शून्य       *elems = रिक्त;
    अचिन्हित nb_elems = 0;
    पूर्णाङ्क ret;

    यदि (val && *val) {
        str = av_malloc(म_माप(val) + 1);
        यदि (!str)
            प्रत्यागम AVERROR(ENOMEM);
    }

    // split and unescape the string
    यावत् (val && *val) {
        uint8_t *p = str;
        शून्य *tmp;

        यदि (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
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

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        यदि (!tmp) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        स_रखो(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        यदि (ret < 0)
            गच्छ fail;
        nb_elems++;
    }
    av_freep(&str);

    यदि (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    यदि (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
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

पूर्णाङ्क av_opt_set(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *val, पूर्णाङ्क खोज_flags)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, खोज_flags, 0, &target_obj, &o, &dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    प्रत्यागम ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_संख्या(name, opttype, vartype)                         \
पूर्णाङ्क av_opt_eval_ ## name(शून्य *obj, ध्रुव AVOption *o,                  \
                         ध्रुव वर्ण *val, vartype *name ## _out)        \
{                                                                       \
    यदि (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        प्रत्यागम AVERROR(EINVAL);                                         \
    प्रत्यागम set_string_संख्या(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_संख्या(flags,  AV_OPT_TYPE_FLAGS,    पूर्णाङ्क)
OPT_EVAL_संख्या(पूर्णाङ्क,    AV_OPT_TYPE_INT,      पूर्णाङ्क)
OPT_EVAL_संख्या(uint,   AV_OPT_TYPE_UINT,     अचिन्हित)
OPT_EVAL_संख्या(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_संख्या(भिन्न,  AV_OPT_TYPE_FLOAT,    भिन्न)
OPT_EVAL_संख्या(द्विगुण, AV_OPT_TYPE_DOUBLE,   द्विगुण)
OPT_EVAL_संख्या(q,      AV_OPT_TYPE_RATIONAL, AVRational)

स्थिर पूर्णाङ्क set_संख्या(शून्य *obj, ध्रुव वर्ण *name, द्विगुण अंक, पूर्णाङ्क den, int64_t intnum,
                      पूर्णाङ्क खोज_flags, पूर्णाङ्क require_type)
{
    शून्य *dst;
    ध्रुव AVOption *o;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, खोज_flags, require_type, रिक्त, &o, &dst);
    यदि (ret < 0)
        प्रत्यागम ret;
    यदि (dst)
        ret = write_संख्या(obj, o, dst, अंक, den, intnum, 0);

    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_set_int(शून्य *obj, ध्रुव वर्ण *name, int64_t val, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम set_संख्या(obj, name, 1, 1, val, खोज_flags, 0);
}

पूर्णाङ्क av_opt_set_double(शून्य *obj, ध्रुव वर्ण *name, द्विगुण val, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम set_संख्या(obj, name, val, 1, 1, खोज_flags, 0);
}

पूर्णाङ्क av_opt_set_q(शून्य *obj, ध्रुव वर्ण *name, AVRational val, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम set_संख्या(obj, name, val.अंक, val.den, 1, खोज_flags, 0);
}

पूर्णाङ्क av_opt_set_bin(शून्य *obj, ध्रुव वर्ण *name, ध्रुव uint8_t *val, पूर्णाङ्क len, पूर्णाङ्क खोज_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    पूर्णाङ्क *lendst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_द्विआधारी,
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
        स_नकल(ptr, val, len);
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_set_image_size(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क खोज_flags)
{
    ध्रुव AVOption *o;
    शून्य *logctx;
    पूर्णाङ्क *dst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_IMAGE_SIZE,
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

पूर्णाङ्क av_opt_set_video_rate(शून्य *obj, ध्रुव वर्ण *name, AVRational val, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम set_संख्या(obj, name, val.अंक, val.den, 1, खोज_flags, AV_OPT_TYPE_VIDEO_RATE);
}

स्थिर पूर्णाङ्क set_format(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क fmt, पूर्णाङ्क खोज_flags,
                      गणना AVOptionType type, ध्रुव वर्ण *desc, पूर्णाङ्क nb_fmts)
{
    ध्रुव AVOption *o;
    शून्य *logctx;
    पूर्णाङ्क *dst;
    पूर्णाङ्क min, max, ret;

    ret = opt_set_init(obj, name, खोज_flags, type, रिक्त, &o, (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    logctx = dst ? obj : रिक्त;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    यदि (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        प्रत्यागम AVERROR(दुस्फल);
    }
    यदि (dst)
    *dst = fmt;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_set_pixel_fmt(शून्य *obj, ध्रुव वर्ण *name, गणना AVPixelFormat fmt, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम set_format(obj, name, fmt, खोज_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

पूर्णाङ्क av_opt_set_sample_fmt(शून्य *obj, ध्रुव वर्ण *name, गणना AVSampleFormat fmt, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम set_format(obj, name, fmt, खोज_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

पूर्णाङ्क av_opt_set_dict_val(शून्य *obj, ध्रुव वर्ण *name, ध्रुव AVDictionary *val,
                        पूर्णाङ्क खोज_flags)
{
    AVDictionary **dst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_DICT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_set_chlayout(शून्य *obj, ध्रुव वर्ण *name,
                        ध्रुव AVChannelLayout *channel_layout,
                        पूर्णाङ्क खोज_flags)
{
    AVChannelLayout *dst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_CHLAYOUT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    प्रत्यागम ret;
}

स्थिर शून्य format_duration(वर्ण *buf, माप_प्रकार size, int64_t d)
{
    वर्ण *e;

    av_assert0(size >= 25);
    यदि (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    यदि (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    अन्यथा यदि (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    अन्यथा यदि (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (पूर्णाङ्क)((d / 60000000) % 60),
                 (पूर्णाङ्क)((d / 1000000) % 60),
                 (पूर्णाङ्क)(d % 1000000));
    अन्यथा यदि (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (पूर्णाङ्क)(d / 60000000),
                 (पूर्णाङ्क)((d / 1000000) % 60),
                 (पूर्णाङ्क)(d % 1000000));
    अन्यथा
        snprintf(buf, size, "%d.%06d",
                 (पूर्णाङ्क)(d / 1000000),
                 (पूर्णाङ्क)(d % 1000000));
    e = buf + म_माप(buf);
    यावत् (e > buf && e[-1] == '0')
        *(--e) = 0;
    यदि (e > buf && e[-1] == '.')
        *(--e) = 0;
}

स्थिर पूर्णाङ्क opt_get_elem(ध्रुव AVOption *o, uint8_t **pbuf, माप_प्रकार buf_len,
                        ध्रुव शून्य *dst, पूर्णाङ्क खोज_flags)
{
    पूर्णाङ्क ret;

    विकल्प (TYPE_BASE(o->type)) {
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
        ret = snprintf(*pbuf, buf_len, "%u", *(अचिन्हित *)dst);
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
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
    पक्ष AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->अंक, ((AVRational *)dst)->den);
        भङ्ग;
    पक्ष AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        भङ्ग;
    पक्ष AV_OPT_TYPE_STRING:
        यदि (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } अन्यथा यदि (खोज_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = रिक्त;
            प्रत्यागम 0;
        } अन्यथा {
            *pbuf = av_strdup("");
        }
        प्रत्यागम *pbuf ? 0 : AVERROR(ENOMEM);
    पक्ष AV_OPT_TYPE_द्विआधारी: {
        ध्रुव uint8_t *bin;
        पूर्णाङ्क len;

        यदि (!*(uint8_t **)dst && (खोज_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            प्रत्यागम 0;
        }
        len = *(पूर्णाङ्क *)(((uint8_t *)dst) + परिमाण(uint8_t *));
        यदि ((uint64_t)len * 2 + 1 > पूर्णांक_उच्च)
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
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
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
        ret = म_माप(*pbuf); // no overflow possible, checked by an assert
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
        यदि (!*(AVDictionary **)dst && (खोज_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            प्रत्यागम 0;
        }
        प्रत्यागम av_dict_get_string(*(AVDictionary **)dst, (वर्ण **)pbuf, '=', ':');
    स्वभाव:
        प्रत्यागम AVERROR(EINVAL);
    }

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क opt_get_array(ध्रुव AVOption *o, शून्य *dst, uint8_t **out_val)
{
    ध्रुव अचिन्हित गिनती = *opt_array_pcount(dst);
    ध्रुव uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = रिक्त;
    माप_प्रकार   str_len = 0;
    पूर्णाङ्क ret;

    *out_val = रिक्त;

    प्रति (अचिन्हित i = 0; i < गिनती; i++) {
        uint8_t buf[128], *out = buf;
        माप_प्रकार out_len;

        ret = opt_get_elem(o, &out, परिमाण(buf),
                           opt_array_pelem(o, *(शून्य **)dst, i), 0);
        यदि (ret < 0)
            गच्छ fail;

        out_len = म_माप(out);
        यदि (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(दुस्फल);
            गच्छ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        यदि (ret < 0)
            गच्छ fail;

        // add separator if needed
        यदि (i)
            str[str_len++] = sep;

        // escape the element
        प्रति (अचिन्हित j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            यदि (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        यदि (out != buf)
            av_freep(&out);
        यदि (ret < 0) {
            av_freep(&str);
            प्रत्यागम ret;
        }
    }

    *out_val = str;

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, uint8_t **out_val)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    uint8_t *out, buf[128];
    पूर्णाङ्क ret;

    यदि (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;

    यदि (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        यदि (ret < 0)
            प्रत्यागम ret;
        यदि (!*out_val && !(खोज_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            यदि (!*out_val)
               प्रत्यागम AVERROR(ENOMEM);
        }
        प्रत्यागम 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, परिमाण(buf), dst, खोज_flags);
    यदि (ret < 0)
        प्रत्यागम ret;
    यदि (out != buf) {
        *out_val = out;
        प्रत्यागम 0;
    }

    यदि (ret >= परिमाण(buf))
        प्रत्यागम AVERROR(EINVAL);
    *out_val = av_strdup(out);
    प्रत्यागम *out_val ? 0 : AVERROR(ENOMEM);
}

स्थिर पूर्णाङ्क get_संख्या(शून्य *obj, ध्रुव वर्ण *name, द्विगुण *अंक, पूर्णाङ्क *den, int64_t *intnum,
                      पूर्णाङ्क खोज_flags)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        प्रत्यागम AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    प्रत्यागम read_संख्या(o, dst, अंक, den, intnum);
}

पूर्णाङ्क av_opt_get_int(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    द्विगुण अंक = 1;
    पूर्णाङ्क ret, den = 1;

    यदि ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, खोज_flags)) < 0)
        प्रत्यागम ret;
    यदि (अंक == den)
        *out_val = intnum;
    अन्यथा
        *out_val = अंक * intnum / den;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_double(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, द्विगुण *out_val)
{
    int64_t intnum = 1;
    द्विगुण अंक = 1;
    पूर्णाङ्क ret, den = 1;

    यदि ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, खोज_flags)) < 0)
        प्रत्यागम ret;
    *out_val = अंक * intnum / den;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_q(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    द्विगुण अंक = 1;
    पूर्णाङ्क ret, den = 1;

    यदि ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, खोज_flags)) < 0)
        प्रत्यागम ret;

    यदि (अंक == 1.0 && (पूर्णाङ्क)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    अन्यथा
        *out_val = double_to_rational(अंक*intnum/den);
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_image_size(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, पूर्णाङ्क *w_out, पूर्णाङ्क *h_out)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        प्रत्यागम AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    यदि (w_out) *w_out = *(पूर्णाङ्क *)dst;
    यदि (h_out) *h_out = *((पूर्णाङ्क *)dst+1);
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_video_rate(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, AVRational *out_val)
{
    प्रत्यागम av_opt_get_q(obj, name, खोज_flags, out_val);
}

स्थिर पूर्णाङ्क get_format(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, शून्य *out_fmt,
                      गणना AVOptionType type, ध्रुव वर्ण *desc)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        प्रत्यागम AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    यदि (type == AV_OPT_TYPE_PIXEL_FMT)
        *(गणना AVPixelFormat *)out_fmt = *(गणना AVPixelFormat *)dst;
    अन्यथा
        *(गणना AVSampleFormat*)out_fmt = *(गणना AVSampleFormat*)dst;

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_pixel_fmt(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, गणना AVPixelFormat *out_fmt)
{
    प्रत्यागम get_format(obj, name, खोज_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

पूर्णाङ्क av_opt_get_sample_fmt(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, गणना AVSampleFormat *out_fmt)
{
    प्रत्यागम get_format(obj, name, खोज_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

पूर्णाङ्क av_opt_get_chlayout(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, AVChannelLayout *cl)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        प्रत्यागम AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    प्रत्यागम av_channel_layout_copy(cl, dst);
}

पूर्णाङ्क av_opt_get_dict_val(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags, AVDictionary **out_val)
{
    शून्य *target_obj;
    AVDictionary *src;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);

    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (o->type != AV_OPT_TYPE_DICT)
        प्रत्यागम AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    प्रत्यागम av_dict_copy(out_val, src, 0);
}

पूर्णाङ्क av_opt_flag_is_set(शून्य *obj, ध्रुव वर्ण *field_name, ध्रुव वर्ण *flag_name)
{
    ध्रुव AVOption *field = av_opt_find(obj, field_name, रिक्त, 0, 0);
    ध्रुव AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : रिक्त, 0, 0);
    int64_t res;

    यदि (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        प्रत्यागम 0;
    प्रत्यागम res & flag->default_val.i64;
}

स्थिर शून्य log_int_मूल्य(शून्य *av_log_obj, पूर्णाङ्क level, int64_t i)
{
    यदि (i == पूर्णांक_उच्च) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा यदि (i == पूर्णांक_न्यून) {
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

स्थिर शून्य log_मूल्य(शून्य *av_log_obj, पूर्णाङ्क level, द्विगुण d)
{
    यदि      (d == पूर्णांक_उच्च) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा यदि (d == पूर्णांक_न्यून) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा यदि (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा यदि (d == (द्विगुण)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा यदि (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा यदि (d == भग्न_उच्च) {
        av_log(av_log_obj, level, "FLT_MAX");
    } अन्यथा यदि (d == भग्न_न्यून) {
        av_log(av_log_obj, level, "FLT_MIN");
    } अन्यथा यदि (d == -भग्न_उच्च) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } अन्यथा यदि (d == -भग्न_न्यून) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } अन्यथा यदि (d == द्विग_उच्च) {
        av_log(av_log_obj, level, "DBL_MAX");
    } अन्यथा यदि (d == द्विग_न्यून) {
        av_log(av_log_obj, level, "DBL_MIN");
    } अन्यथा यदि (d == -द्विग_उच्च) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } अन्यथा यदि (d == -द्विग_न्यून) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%g", d);
    }
}

स्थिर ध्रुव वर्ण *get_opt_const_name(शून्य *obj, ध्रुव वर्ण *unit, int64_t मूल्य)
{
    ध्रुव AVOption *opt = रिक्त;

    यदि (!unit)
        प्रत्यागम रिक्त;
    यावत् ((opt = av_opt_next(obj, opt)))
        यदि (opt->type == AV_OPT_TYPE_CONST && !म_भेद(opt->unit, unit) &&
            opt->default_val.i64 == मूल्य)
            प्रत्यागम opt->name;
    प्रत्यागम रिक्त;
}

स्थिर वर्ण *get_opt_flags_string(शून्य *obj, ध्रुव वर्ण *unit, int64_t मूल्य)
{
    ध्रुव AVOption *opt = रिक्त;
    वर्ण flags[512];

    flags[0] = 0;
    यदि (!unit)
        प्रत्यागम रिक्त;
    यावत् ((opt = av_opt_next(obj, opt))) {
        यदि (opt->type == AV_OPT_TYPE_CONST && !म_भेद(opt->unit, unit) &&
            opt->default_val.i64 & मूल्य) {
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
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);

    यदि (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
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
    यदि (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_द्विआधारी)
        प्रत्यागम;
    यदि ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
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
            log_int_मूल्य(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        भङ्ग;
    }
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_FLOAT:
        log_मूल्य(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, पूर्णांक_उच्च);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.अंक, q.den); }
        भङ्ग;
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (वर्ण *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (वर्ण *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        भङ्ग;
    पक्ष AV_OPT_TYPE_COLOR:
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
    पक्ष AV_OPT_TYPE_STRING:
    पक्ष AV_OPT_TYPE_DICT:
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
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

    यावत् ((opt = av_opt_next(obj, opt))) {
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
        अन्यथा यदि (unit && opt->type == AV_OPT_TYPE_CONST && म_भेद(unit, opt->unit))
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

        यदि (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_खोज_FAKE_OBJ) >= 0) {
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
                    log_मूल्य(av_log_obj, AV_LOG_INFO, r->range[i]->मूल्य_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_मूल्य(av_log_obj, AV_LOG_INFO, r->range[i]->मूल्य_max);
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

शून्य av_opt_set_defaults(शून्य *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

शून्य av_opt_set_defaults2(शून्य *s, पूर्णाङ्क mask, पूर्णाङ्क flags)
{
    ध्रुव AVOption *opt = रिक्त;
    यावत् ((opt = av_opt_next(s, opt))) {
        शून्य *dst = ((uint8_t*)s) + opt->offset;

        यदि ((opt->flags & mask) != flags)
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
                opt_set_array(s, s, opt, arr->def, dst);

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
                write_संख्या(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:
            पक्ष AV_OPT_TYPE_FLOAT: {
                द्विगुण val;
                val = opt->default_val.dbl;
                write_संख्या(s, opt, dst, val, 1, 1, 1);
            }
            भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, पूर्णांक_उच्च);
                write_संख्या(s, opt, dst, 1, val.den, val.अंक, 1);
            }
            भङ्ग;
            पक्ष AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_द्विआधारी:
                set_string_द्विआधारी(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                भङ्ग;
            पक्ष AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
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
स्थिर पूर्णाङ्क parse_कुंजी_मूल्य_pair(शून्य *ctx, ध्रुव वर्ण **buf,
                                ध्रुव वर्ण *कुंजी_val_sep, ध्रुव वर्ण *pairs_sep)
{
    वर्ण *कुंजी = av_get_token(buf, कुंजी_val_sep);
    वर्ण *val;
    पूर्णाङ्क ret;

    यदि (!कुंजी)
        प्रत्यागम AVERROR(ENOMEM);

    यदि (*कुंजी && म_अखोज(*buf, कुंजी_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        यदि (!val) {
            av_freep(&कुंजी);
            प्रत्यागम AVERROR(ENOMEM);
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", कुंजी);
        av_free(कुंजी);
        प्रत्यागम AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", कुंजी, val);

    ret = av_opt_set(ctx, कुंजी, val, AV_OPT_खोज_CHILDREN);
    यदि (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", कुंजी);

    av_free(कुंजी);
    av_free(val);
    प्रत्यागम ret;
}

पूर्णाङ्क av_set_options_string(शून्य *ctx, ध्रुव वर्ण *opts,
                          ध्रुव वर्ण *कुंजी_val_sep, ध्रुव वर्ण *pairs_sep)
{
    पूर्णाङ्क ret, गिनती = 0;

    यदि (!opts)
        प्रत्यागम 0;

    यावत् (*opts) {
        यदि ((ret = parse_कुंजी_मूल्य_pair(ctx, &opts, कुंजी_val_sep, pairs_sep)) < 0)
            प्रत्यागम ret;
        गिनती++;

        यदि (*opts)
            opts++;
    }

    प्रत्यागम गिनती;
}

#define WHITESPACES " \n\t\r"

स्थिर पूर्णाङ्क is_कुंजी_char(वर्ण c)
{
    प्रत्यागम (अचिन्हित)((c | 32) - 'a') < 26 ||
           (अचिन्हित)(c - '0') < 10 ||
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
स्थिर पूर्णाङ्क get_कुंजी(ध्रुव वर्ण **ropts, ध्रुव वर्ण *delim, वर्ण **rkey)
{
    ध्रुव वर्ण *opts = *ropts;
    ध्रुव वर्ण *कुंजी_start, *कुंजी_end;

    कुंजी_start = opts += म_अखोज(opts, WHITESPACES);
    यावत् (is_कुंजी_char(*opts))
        opts++;
    कुंजी_end = opts;
    opts += म_अखोज(opts, WHITESPACES);
    यदि (!*opts || !म_अक्षर(delim, *opts))
        प्रत्यागम AVERROR(EINVAL);
    opts++;
    यदि (!(*rkey = av_malloc(कुंजी_end - कुंजी_start + 1)))
        प्रत्यागम AVERROR(ENOMEM);
    स_नकल(*rkey, कुंजी_start, कुंजी_end - कुंजी_start);
    (*rkey)[कुंजी_end - कुंजी_start] = 0;
    *ropts = opts;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_कुंजी_मूल्य(ध्रुव वर्ण **ropts,
                         ध्रुव वर्ण *कुंजी_val_sep, ध्रुव वर्ण *pairs_sep,
                         अचिन्हित flags,
                         वर्ण **rkey, वर्ण **rval)
{
    पूर्णाङ्क ret;
    वर्ण *कुंजी = रिक्त, *val;
    ध्रुव वर्ण *opts = *ropts;

    यदि ((ret = get_कुंजी(&opts, कुंजी_val_sep, &कुंजी)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_कुंजी))
        प्रत्यागम AVERROR(EINVAL);
    यदि (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(कुंजी);
        प्रत्यागम AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = कुंजी;
    *rval  = val;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_set_from_string(शून्य *ctx, ध्रुव वर्ण *opts,
                           ध्रुव वर्ण *ध्रुव *shorthand,
                           ध्रुव वर्ण *कुंजी_val_sep, ध्रुव वर्ण *pairs_sep)
{
    पूर्णाङ्क ret, गिनती = 0;
    ध्रुव वर्ण *dummy_shorthand = रिक्त;
    ध्रुव वर्ण *कुंजी;

    यदि (!opts)
        प्रत्यागम 0;
    यदि (!shorthand)
        shorthand = &dummy_shorthand;

    यावत् (*opts) {
        वर्ण *parsed_कुंजी, *मूल्य;
        ret = av_opt_get_कुंजी_मूल्य(&opts, कुंजी_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_कुंजी : 0,
                                   &parsed_कुंजी, &मूल्य);
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
        यदि (parsed_कुंजी) {
            कुंजी = parsed_कुंजी;
            यावत् (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } अन्यथा {
            कुंजी = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", कुंजी, मूल्य);
        यदि ((ret = av_opt_set(ctx, कुंजी, मूल्य, 0)) < 0) {
            यदि (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", कुंजी);
            av_free(मूल्य);
            av_free(parsed_कुंजी);
            प्रत्यागम ret;
        }

        av_free(मूल्य);
        av_free(parsed_कुंजी);
        गिनती++;
    }
    प्रत्यागम गिनती;
}

शून्य av_opt_free(शून्य *obj)
{
    ध्रुव AVOption *o = रिक्त;
    यावत् ((o = av_opt_next(obj, o))) {
        शून्य *pitem = (uint8_t *)obj + o->offset;

        यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        अन्यथा
            opt_free_elem(o->type, pitem);
    }
}

पूर्णाङ्क av_opt_set_dict2(शून्य *obj, AVDictionary **options, पूर्णाङ्क खोज_flags)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;
    AVDictionary    *tmp = रिक्त;
    पूर्णाङ्क ret;

    यदि (!options)
        प्रत्यागम 0;

    यावत् ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->कुंजी, t->मूल्य, खोज_flags);
        यदि (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->कुंजी, t->मूल्य, AV_DICT_MULTIKEY);
        यदि (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->कुंजी, t->मूल्य);
            av_dict_free(&tmp);
            प्रत्यागम ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_set_dict(शून्य *obj, AVDictionary **options)
{
    प्रत्यागम av_opt_set_dict2(obj, options, 0);
}

ध्रुव AVOption *av_opt_find(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *unit,
                            पूर्णाङ्क opt_flags, पूर्णाङ्क खोज_flags)
{
    प्रत्यागम av_opt_find2(obj, name, unit, opt_flags, खोज_flags, रिक्त);
}

ध्रुव AVOption *av_opt_find2(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *unit,
                             पूर्णाङ्क opt_flags, पूर्णाङ्क खोज_flags, शून्य **target_obj)
{
    ध्रुव AVClass  *c;
    ध्रुव AVOption *o = रिक्त;

    यदि(!obj)
        प्रत्यागम रिक्त;

    c= *(AVClass**)obj;

    यदि (!c)
        प्रत्यागम रिक्त;

    यदि (खोज_flags & AV_OPT_खोज_CHILDREN) {
        यदि (खोज_flags & AV_OPT_खोज_FAKE_OBJ) {
            शून्य *iter = रिक्त;
            ध्रुव AVClass *child;
            यावत् (child = av_opt_child_class_iterate(c, &iter))
                यदि (o = av_opt_find2(&child, name, unit, opt_flags, खोज_flags, रिक्त))
                    प्रत्यागम o;
        } अन्यथा {
            शून्य *child = रिक्त;
            यावत् (child = av_opt_child_next(obj, child))
                यदि (o = av_opt_find2(child, name, unit, opt_flags, खोज_flags, target_obj))
                    प्रत्यागम o;
        }
    }

    यावत् (o = av_opt_next(obj, o)) {
        यदि (!म_भेद(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !म_भेद(o->unit, unit)))) {
            यदि (target_obj) {
                यदि (!(खोज_flags & AV_OPT_खोज_FAKE_OBJ))
                    *target_obj = obj;
                अन्यथा
                    *target_obj = रिक्त;
            }
            प्रत्यागम o;
        }
    }
    प्रत्यागम रिक्त;
}

शून्य *av_opt_child_next(शून्य *obj, शून्य *prev)
{
    ध्रुव AVClass *c = *(AVClass **)obj;
    यदि (c->child_next)
        प्रत्यागम c->child_next(obj, prev);
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
    } अन्यथा यदि (type == AV_OPT_TYPE_द्विआधारी) {
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
            यदि (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = रिक्त;
            प्रत्यागम av_channel_layout_copy(dst, src);
        }
    } अन्यथा यदि (opt_is_pod(type)) {
        माप_प्रकार size = opt_type_desc[type].size;
        स_नकल(dst, src, size);
    } अन्यथा {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        प्रत्यागम AVERROR(EINVAL);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क opt_copy_array(शून्य *logctx, ध्रुव AVOption *o,
                          शून्य **pdst, ध्रुव शून्य * ध्रुव *psrc)
{
    अचिन्हित nb_elems = *opt_array_pcount(psrc);
    शून्य         *dst = रिक्त;
    पूर्णाङ्क ret;

    यदि (*pdst == *psrc) {
        *pdst                   = रिक्त;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    यदि (!dst)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (अचिन्हित i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
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

    यावत् ((o = av_opt_next(src, o))) {
        शून्य *field_dst = (uint8_t *)dst + o->offset;
        शून्य *field_src = (uint8_t *)src + o->offset;

        पूर्णाङ्क err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        यदि (err < 0)
            ret = err;
    }
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_get_array_size(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags,
                          अचिन्हित पूर्णाङ्क *out_val)
{
    शून्य *target_obj, *parray;
    ध्रुव AVOption *o;

    o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        प्रत्यागम AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_get_array(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags,
                     अचिन्हित पूर्णाङ्क start_elem, अचिन्हित पूर्णाङ्क nb_elems,
                     गणना AVOptionType out_type, शून्य *out_val)
{
    ध्रुव माप_प्रकार elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ध्रुव AVOption *o;
    शून्य *target_obj;

    ध्रुव शून्य *parray;
    अचिन्हित array_size;

    पूर्णाङ्क ret;

    o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target_obj);
    यदि (!o || !target_obj)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    यदि (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        प्रत्यागम AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    यदि (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (अचिन्हित i = 0; i < nb_elems; i++) {
        ध्रुव शून्य *src = opt_array_pelem(o, *(शून्य**)parray, start_elem + i);
        शून्य       *dst = (uint8_t*)out_val + i * elem_size_out;

        यदि (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            यदि (ret < 0)
                गच्छ fail;
        } अन्यथा यदि (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, परिमाण(buf), src, खोज_flags);
            यदि (ret < 0)
                गच्छ fail;

            यदि (out == buf) {
                out = av_strdup(buf);
                यदि (!out) {
                    ret = AVERROR(ENOMEM);
                    गच्छ fail;
                }
            }

            *(uint8_t**)dst = out;
        } अन्यथा यदि (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            द्विगुण     अंक = 1.0;
            पूर्णाङ्क        den = 1;
            int64_t intnum = 1;

            ret = read_संख्या(o, src, &अंक, &den, &intnum);
            यदि (ret < 0)
                गच्छ fail;

            विकल्प (out_type) {
            पक्ष AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (अंक == den) ?  intnum : अंक * intnum / den;
                भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:
                *(द्विगुण*)dst = अंक * intnum / den;
                भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (अंक == 1.0 && (पूर्णाङ्क)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(अंक * intnum / den);
                भङ्ग;
            स्वभाव: av_assert0(0);
            }
        } अन्यथा
            प्रत्यागम AVERROR(ENOSYS);
    }

    प्रत्यागम 0;
fail:
    प्रति (अचिन्हित i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_set_array(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags,
                     अचिन्हित पूर्णाङ्क start_elem, अचिन्हित पूर्णाङ्क nb_elems,
                     गणना AVOptionType val_type, ध्रुव शून्य *val)
{
    ध्रुव माप_प्रकार elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ध्रुव AVOption *o;
    ध्रुव AVOptionArrayDef *arr;
    शून्य *target_obj;

    शून्य *parray;
    शून्य *new_elems;
    अचिन्हित *array_size, new_size;
    माप_प्रकार elem_size;

    पूर्णाङ्क ret = 0;

    ret = opt_set_init(obj, name, खोज_flags, 0, &target_obj, &o, &parray);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        प्रत्यागम AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    यदि (start_elem > *array_size)
        प्रत्यागम AVERROR(EINVAL);

    // compute new array size
    यदि (!val) {
        यदि (*array_size - start_elem < nb_elems)
            प्रत्यागम AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } अन्यथा यदि (खोज_flags & AV_OPT_ARRAY_REPLACE) {
        यदि (start_elem >= अच_पूर्णांक_उच्च - nb_elems)
            प्रत्यागम AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } अन्यथा {
        यदि (nb_elems >= अच_पूर्णांक_उच्च - *array_size)
            प्रत्यागम AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    यदि (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        प्रत्यागम AVERROR(EINVAL);

    // desired operation is shrinking the array
    यदि (!val) {
        शून्य *array = *(शून्य**)parray;

        प्रति (अचिन्हित i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        यदि (new_size > 0) {
            स_हटाओ(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            यदि (!array)
                प्रत्यागम AVERROR(ENOMEM);

            *(शून्य**)parray = array;
        } अन्यथा
            av_freep(parray);

        *array_size = new_size;

        प्रत्यागम 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    यदि (!new_elems)
        प्रत्यागम AVERROR(ENOMEM);

    // convert/validate each new element
    प्रति (अचिन्हित i = 0; i < nb_elems; i++) {
        शून्य       *dst = opt_array_pelem(o, new_elems, i);
        ध्रुव शून्य *src = (uint8_t*)val + i * elem_size_val;

        द्विगुण     अंक = 1.0;
        पूर्णाङ्क        den = 1;
        int64_t intnum = 1;

        यदि (val_type == TYPE_BASE(o->type)) {
            पूर्णाङ्क err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            यदि (ret < 0)
                गच्छ fail;

            // validate the range for numeric options
            err = read_संख्या(o, dst, &अंक, &den, &intnum);
            यदि (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < अंक * intnum || o->min * den > अंक * intnum)) {
                अंक = den ? अंक * intnum / den : (अंक && intnum ? अनन्त : न_अंक);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, अंक, o->min, o->max);
                ret = AVERROR(दुस्फल);
                गच्छ fail;
            }
        } अन्यथा यदि (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ध्रुव वर्ण **)src, dst);
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
            पक्ष AV_OPT_TYPE_FLOAT:     अंक    = *(भिन्न*)src;              भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:    अंक    = *(द्विगुण*)src;             भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->अंक;
                                        den    = ((AVRational*)src)->den;   भङ्ग;
            स्वभाव: av_assert0(0);
            }

            ret = write_संख्या(obj, o, dst, अंक, den, intnum, 0);
            यदि (ret < 0)
                गच्छ fail;
        } अन्यथा {
            ret = AVERROR(ENOSYS);
            गच्छ fail;
        }
    }

    // commit new elements to the array
    यदि (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(शून्य**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = रिक्त;
        nb_elems  = 0;
    } अन्यथा {
        शून्य *array = av_realloc_array(*(शून्य**)parray, new_size, elem_size);
        यदि (!array) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }

        यदि (खोज_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            प्रति (अचिन्हित i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } अन्यथा {
            // shift existing elements to the end
            स_हटाओ(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        स_नकल((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(शून्य**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_query_ranges(AVOptionRanges **ranges_arg, शून्य *obj, ध्रुव वर्ण *कुंजी, पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;
    ध्रुव AVClass *c = *(AVClass**)obj;
    पूर्णाङ्क (*callback)(AVOptionRanges **, शून्य *obj, ध्रुव वर्ण *कुंजी, पूर्णाङ्क flags) = c->query_ranges;

    यदि (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, कुंजी, flags);
    यदि (ret >= 0) {
        यदि (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    प्रत्यागम ret;
}

पूर्णाङ्क av_opt_query_ranges_default(AVOptionRanges **ranges_arg, शून्य *obj, ध्रुव वर्ण *कुंजी, पूर्णाङ्क flags)
{
    AVOptionRanges *ranges = av_mallocz(परिमाण(*ranges));
    AVOptionRange **range_array = av_mallocz(परिमाण(शून्य*));
    AVOptionRange *range = av_mallocz(परिमाण(*range));
    ध्रुव AVOption *field = av_opt_find(obj, कुंजी, रिक्त, 0, flags);
    पूर्णाङ्क ret;

    *ranges_arg = रिक्त;

    यदि (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->मूल्य_min = field->min;
    range->मूल्य_max = field->max;

    विकल्प (field->type) {
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
        range->मूल्य_min = -1;
        range->मूल्य_max = पूर्णांक_उच्च;
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL:
        range->component_min = पूर्णांक_न्यून;
        range->component_max = पूर्णांक_उच्च;
        भङ्ग;
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = पूर्णांक_उच्च/128/8;
        range->मूल्य_min = 0;
        range->मूल्य_max = पूर्णांक_उच्च/8;
        भङ्ग;
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = पूर्णांक_उच्च;
        range->मूल्य_min = 1;
        range->मूल्य_max = पूर्णांक_उच्च;
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

पूर्णाङ्क av_opt_is_set_to_default(शून्य *obj, ध्रुव AVOption *o)
{
    int64_t i64;
    द्विगुण d;
    AVRational q;
    पूर्णाङ्क ret, w, h;
    वर्ण *str;
    शून्य *dst;

    यदि (!o || !obj)
        प्रत्यागम AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    यदि (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ध्रुव वर्ण *def = o->default_val.arr ? o->default_val.arr->def : रिक्त;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        यदि (ret < 0)
            प्रत्यागम ret;

        यदि (!!val != !!def)
            ret = 0;
        अन्यथा यदि (val)
            ret = !म_भेद(val, def);
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
        read_संख्या(o, dst, रिक्त, रिक्त, &i64);
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
        प्रत्यागम !म_भेद(str, o->default_val.str);
    पक्ष AV_OPT_TYPE_DOUBLE:
        d = *(द्विगुण *)dst;
        प्रत्यागम o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    पक्ष AV_OPT_TYPE_FLOAT:
        d = *(भिन्न *)dst;
        प्रत्यागम (भिन्न)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    पक्ष AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, पूर्णांक_उच्च);
        प्रत्यागम !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    पक्ष AV_OPT_TYPE_द्विआधारी: {
        संरचना {
            uint8_t *data;
            पूर्णाङ्क size;
        } tmp = {0};
        पूर्णाङ्क opt_size = *(पूर्णाङ्क *)((शून्य **)dst + 1);
        शून्य *opt_ptr = *(शून्य **)dst;
        यदि (!opt_size && (!o->default_val.str || !म_माप(o->default_val.str)))
            प्रत्यागम 1;
        यदि (!opt_size ||  !o->default_val.str || !म_माप(o->default_val.str ))
            प्रत्यागम 0;
        यदि (opt_size != म_माप(o->default_val.str) / 2)
            प्रत्यागम 0;
        ret = set_string_द्विआधारी(रिक्त, रिक्त, o->default_val.str, &tmp.data);
        यदि (!ret)
            ret = !स_भेद(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        प्रत्यागम ret;
    }
    पक्ष AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = रिक्त;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ध्रुव AVDictionaryEntry *en1 = रिक्त;
        ध्रुव AVDictionaryEntry *en2 = रिक्त;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        यदि (ret < 0) {
            av_dict_free(&dict1);
            प्रत्यागम ret;
        }
        कुरु {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } यावत् (en1 && en2 && !म_भेद(en1->कुंजी, en2->कुंजी) && !म_भेद(en1->मूल्य, en2->मूल्य));
        av_dict_free(&dict1);
        प्रत्यागम (!en1 && !en2);
    }
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
        यदि (!o->default_val.str || !म_भेद(o->default_val.str, "none"))
            w = h = 0;
        अन्यथा यदि ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            प्रत्यागम ret;
        प्रत्यागम (w == *(पूर्णाङ्क *)dst) && (h == *((पूर्णाङ्क *)dst+1));
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        यदि (o->default_val.str) {
            यदि ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                प्रत्यागम ret;
        }
        प्रत्यागम !av_cmp_q(*(AVRational*)dst, q);
    पक्ष AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        यदि (o->default_val.str) {
            यदि ((ret = av_parse_color(color, o->default_val.str, -1, रिक्त)) < 0)
                प्रत्यागम ret;
        }
        प्रत्यागम !स_भेद(color, dst, परिमाण(color));
    }
    स्वभाव:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        भङ्ग;
    }
    प्रत्यागम AVERROR_PATCHWELCOME;
}

पूर्णाङ्क av_opt_is_set_to_default_by_name(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क खोज_flags)
{
    ध्रुव AVOption *o;
    शून्य *target;
    यदि (!obj)
        प्रत्यागम AVERROR(EINVAL);
    o = av_opt_find2(obj, name, रिक्त, 0, खोज_flags, &target);
    यदि (!o)
        प्रत्यागम AVERROR_OPTION_NOT_FOUND;
    प्रत्यागम av_opt_is_set_to_default(target, o);
}

स्थिर पूर्णाङ्क opt_serialize(शून्य *obj, पूर्णाङ्क opt_flags, पूर्णाङ्क flags, पूर्णाङ्क *cnt,
                         AVBPrint *bprint, ध्रुव वर्ण कुंजी_val_sep, ध्रुव वर्ण pairs_sep)
{
    ध्रुव AVOption *o = रिक्त;
    शून्य *child = रिक्त;
    uint8_t *buf;
    पूर्णाङ्क ret;
    ध्रुव वर्ण special_chars[] = {pairs_sep, कुंजी_val_sep, '\0'};

    यदि (flags & AV_OPT_SERIALIZE_खोज_CHILDREN)
        यावत् (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                कुंजी_val_sep, pairs_sep);
            यदि (ret < 0)
                प्रत्यागम ret;
        }

    यावत् (o = av_opt_next(obj, o)) {
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
        यदि (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            अनुवर्त;
        यदि ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, रिक्त);
            प्रत्यागम ret;
        }
        यदि (buf) {
            यदि ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &कुंजी_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_opt_serialize(शून्य *obj, पूर्णाङ्क opt_flags, पूर्णाङ्क flags, वर्ण **buffer,
                     ध्रुव वर्ण कुंजी_val_sep, ध्रुव वर्ण pairs_sep)
{
    AVBPrint bprint;
    पूर्णाङ्क ret, cnt = 0;

    यदि (pairs_sep == '\0' || कुंजी_val_sep == '\0' || pairs_sep == कुंजी_val_sep ||
        pairs_sep == '\\' || कुंजी_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि (!obj || !buffer)
        प्रत्यागम AVERROR(EINVAL);

    *buffer = रिक्त;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        कुंजी_val_sep, pairs_sep);
    यदि (ret < 0)
        प्रत्यागम ret;

    ret = av_bprint_finalize(&bprint, buffer);
    यदि (ret < 0)
        प्रत्यागम ret;
    प्रत्यागम 0;
}
