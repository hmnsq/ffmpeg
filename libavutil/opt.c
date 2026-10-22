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
    सचे (!obj)
        पटिनिवत्त रिक्त;
    class = *(ध्रुव AVClass**)obj;
    सचे (!last && class && class->option && class->option[0].name)
        पटिनिवत्त class->option;
    सचे (last && last[1].name)
        पटिनिवत्त ++last;
    पटिनिवत्त रिक्त;
}

स्थिर ध्रुव संरचना {
    size_t      size;
    ध्रुव वर्ण *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { परिमाण(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { परिमाण(पूर्णाङ्क),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { परिमाण(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { परिमाण(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { परिमाण(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { परिमाण(द्विगुण),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { परिमाण(भिन्न),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { परिमाण(वर्ण *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { परिमाण(AVRational),     "<rational>" },
    [AV_OPT_TYPE_द्विमान]        = { परिमाण(uint8_t *),      "<binary>" },
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
        पटिनिवत्त 1;
    }
    पटिनिवत्त 0;
}

स्थिर uint8_t opt_array_sep(ध्रुव AVOption *o)
{
    ध्रुव AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    पटिनिवत्त (d && d->sep) ? d->sep : ',';
}

स्थिर शून्य *opt_array_pelem(ध्रुव AVOption *o, शून्य *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    पटिनिवत्त (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

स्थिर unsigned *opt_array_pcount(ध्रुव शून्य *parray)
{
    पटिनिवत्त (unsigned *)((ध्रुव शून्य * ध्रुव *)parray + 1);
}

स्थिर शून्य opt_free_elem(गणना AVOptionType type, शून्य *ptr)
{
    विकल्प (TYPE_BASE(type)) {
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

स्थिर शून्य opt_free_array(ध्रुव AVOption *o, शून्य *parray, unsigned *गणनम्)
{
    अत्थाय (unsigned i = 0; i < *गणनम्; i++)
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
स्थिर पूर्णाङ्क opt_set_init(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                        पूर्णाङ्क require_type,
                        शून्य **ptgt, ध्रुव AVOption **po, शून्य **pdst)
{
    शून्य *logctx;
    ध्रुव AVOption *o;
    शून्य *tgt;

    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &tgt);
    सचे (!o || (!tgt && !(अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_FAKE_OBJ)))
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;

    सचे (o->flags & AV_OPT_FLAG_READONLY)
        पटिनिवत्त AVERROR(EINVAL);

    logctx = tgt ? obj : रिक्त;

    सचे (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        पटिनिवत्त AVERROR(EINVAL);
    }

    सचे (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = रिक्त;
        ध्रुव AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ध्रुव AVClass**)tgt;
        सचे (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        सचे (!state_flags && obj != tgt) {
            class = *(ध्रुव AVClass**)obj;
            सचे (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        सचे (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            पटिनिवत्त AVERROR(EINVAL);
        }
    }

    सचे (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    सचे (po)
        *po   = o;
    सचे (ptgt)
        *ptgt = tgt;
    सचे (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : रिक्त;

    पटिनिवत्त 0;
}

स्थिर AVRational double_to_rational(द्विगुण d)
{
     AVRational r = av_d2q(d, 1 << 24);
     सचे ((!r.अङ्कः || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     पटिनिवत्त r;
}

स्थिर पूर्णाङ्क read_सङ्ख्या(ध्रुव AVOption *o, ध्रुव शून्य *dst, द्विगुण *अङ्कः, पूर्णाङ्क *den, int64_t *intnum)
{
    विकल्प (TYPE_BASE(o->type)) {
    पक्ष AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned पूर्णाङ्क*)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(गणना AVPixelFormat *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(गणना AVSampleFormat *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_BOOL:
    पक्ष AV_OPT_TYPE_INT:
        *intnum = *(पूर्णाङ्क *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_UINT:
        *intnum = *(unsigned पूर्णाङ्क *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_DURATION:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_FLOAT:
        *अङ्कः = *(भिन्न *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_DOUBLE:
        *अङ्कः = *(द्विगुण *)dst;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->अङ्कः;
        *den    = ((AVRational *)dst)->den;
        पटिनिवत्त 0;
    पक्ष AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        पटिनिवत्त 0;
    }
    पटिनिवत्त AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क write_सङ्ख्या(शून्य *obj, ध्रुव AVOption *o, शून्य *dst,
                        द्विगुण अङ्कः, पूर्णाङ्क den, int64_t intnum,
                        पूर्णाङ्क ignore_range)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);

    सचे (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < अङ्कः * intnum || o->min * den > अङ्कः * intnum)) {
        अङ्कः = den ? अङ्कः * intnum / den : (अङ्कः && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               अङ्कः, o->name, o->min, o->max);
        पटिनिवत्त AVERROR(ERANGE);
    }
    सचे (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        द्विगुण d = अङ्कः*intnum/den;
        सचे (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   अङ्कः*intnum/den, o->name);
            पटिनिवत्त AVERROR(ERANGE);
        }
    }

    सचे (!dst)
        पटिनिवत्त 0;

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
        सचे (intnum == 1 && d == (द्विगुण)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } अञ्ञथा
            *(int64_t *)dst = llrint(d) * intnum;
        भङ्ग;}
    पक्ष AV_OPT_TYPE_UINT64:{
        द्विगुण d = अङ्कः / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        सचे (intnum == 1 && d == (द्विगुण)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } अञ्ञथा सचे (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } अञ्ञथा {
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
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
        सचे ((पूर्णाङ्क) अङ्कः == अङ्कः)
            *(AVRational *)dst = (AVRational) { अङ्कः *intnum, den };
        अञ्ञथा
            *(AVRational *)dst = double_to_rational(अङ्कः * intnum / den);
        भङ्ग;
    स्वभाव:
        पटिनिवत्त AVERROR(EINVAL);
    }
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क hexchar2int(वर्ण c) {
    सचे (c >= '0' && c <= '9')
        पटिनिवत्त c - '0';
    सचे (c >= 'a' && c <= 'f')
        पटिनिवत्त c - 'a' + 10;
    सचे (c >= 'A' && c <= 'F')
        पटिनिवत्त c - 'A' + 10;
    पटिनिवत्त -1;
}

स्थिर पूर्णाङ्क set_string_द्विमान(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    पूर्णाङ्क *lendst;
    uint8_t *bin, *ptr;
    पूर्णाङ्क len;

    सचे (dst) {
        lendst = (पूर्णाङ्क *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    सचे (!val || !(len = strlen(val)))
        पटिनिवत्त 0;

    सचे (len & 1)
        पटिनिवत्त AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    सचे (!ptr)
        पटिनिवत्त AVERROR(ENOMEM);
    याव (*val) {
        पूर्णाङ्क a = hexchar2int(*val++);
        पूर्णाङ्क b = hexchar2int(*val++);
        सचे (a < 0 || b < 0) {
            av_free(bin);
            पटिनिवत्त AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    सचे (dst) {
        *dst    = bin;
        *lendst = len;
    } अञ्ञथा {
        av_free(bin);
    }

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क set_string(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    सचे (!dst)
        पटिनिवत्त 0;
    av_freep(dst);
    सचे (!val)
        पटिनिवत्त 0;
    *dst = av_strdup(val);
    पटिनिवत्त *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

स्थिर पूर्णाङ्क set_string_सङ्ख्या(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);
    पूर्णाङ्क ret = 0;

    सचे (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        पूर्णाङ्क अङ्कः, den;
        वर्ण c;
        सचे (sscanf(val, "%d%*1[:/]%d%c", &अङ्कः, &den, &c) == 2) {
            सचे ((ret = write_सङ्ख्या(obj, o, dst, 1, den, अङ्कः, 0)) >= 0)
                पटिनिवत्त ret;
            ret = 0;
        }
    }

    अत्थाय (;;) {
        पूर्णाङ्क i = 0;
        वर्ण buf[256];
        पूर्णाङ्क cmd = 0;
        द्विगुण d;
        int64_t intnum = 1;

        सचे (type == AV_OPT_TYPE_FLAGS) {
            सचे (*val == '+' || *val == '-')
                cmd = *(val++);
            अत्थाय (; i < परिमाण(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            पूर्णाङ्क res;
            पूर्णाङ्क ci = 0;
            द्विगुण const_मानानि[64];
            ध्रुव वर्ण * const_names[64];
            पूर्णाङ्क अन्वेषणम्_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_अन्वेषणम्_CHILDREN : 0;
            ध्रुव AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, अन्वेषणम्_flags);
            सचे (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                सचे (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } अञ्ञथा {
                सचे (o->unit) {
                    अत्थाय (o_named = रिक्त; o_named = av_opt_next(target_obj, o_named); ) {
                        सचे (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            सचे (ci + 6 >= FF_ARRAY_ELEMS(const_मानानि)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                पटिनिवत्त AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_मानानि[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_मानानि[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_मानानि[ci++] = o->max;
                const_names [ci  ] = "min";
                const_मानानि[ci++] = o->min;
                const_names [ci  ] = "none";
                const_मानानि[ci++] = 0;
                const_names [ci  ] = "all";
                const_मानानि[ci++] = ~0;
                const_names [ci] = रिक्त;
                const_मानानि[ci] = 0;

                res = av_व्यञ्जकम्_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_मानानि, रिक्त, रिक्त, रिक्त, रिक्त, रिक्त, 0, obj);
                सचे (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    पटिनिवत्त res;
                }
            }
        }
        सचे (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned पूर्णाङ्क*)dst;
            सचे (cmd == '+')
                d = intnum | (int64_t)d;
            अञ्ञथा सचे (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        सचे ((ret = write_सङ्ख्या(obj, o, dst, d, 1, 1, 0)) < 0)
            पटिनिवत्त ret;
        val += i;
        सचे (!i || !*val)
            पटिनिवत्त 0;
    }
}

स्थिर पूर्णाङ्क set_string_image_size(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, पूर्णाङ्क *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क tmp[2];
    पूर्णाङ्क ret;

    सचे (!val || !strcmp(val, "none")) {
        सचे (dst) {
        dst[0] =
        dst[1] = 0;
        }
        पटिनिवत्त 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    सचे (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        पटिनिवत्त ret;
    }
    सचे (dst)
        memcpy(dst, tmp, परिमाण(tmp));
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क set_string_video_rate(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, AVRational *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    AVRational tmp;
    पूर्णाङ्क ret = av_parse_video_rate(&tmp, val);
    सचे (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    सचे (dst)
        *dst = tmp;
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क set_string_color(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क ret;

    सचे (!val) {
        पटिनिवत्त 0;
    } अञ्ञथा {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        सचे (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            पटिनिवत्त ret;
        }
        सचे (dst)
            memcpy(dst, tmp, परिमाण(tmp));
        पटिनिवत्त ret;
    }
    पटिनिवत्त 0;
}

स्थिर ध्रुव वर्ण *get_bool_name(पूर्णाङ्क val)
{
    सचे (val < 0)
        पटिनिवत्त "auto";
    पटिनिवत्त val ? "true" : "false";
}

स्थिर पूर्णाङ्क set_string_bool(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, पूर्णाङ्क *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क n;

    सचे (!val)
        पटिनिवत्त 0;

    सचे (!strcmp(val, "auto")) {
        n = -1;
    } अञ्ञथा सचे (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } अञ्ञथा सचे (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } अञ्ञथा {
        वर्ण *end = रिक्त;
        n = strtol(val, &end, 10);
        सचे (val + strlen(val) != end)
            गच्छ fail;
    }

    सचे (n < o->min || n > o->max)
        गच्छ fail;

    सचे (dst)
    *dst = n;
    पटिनिवत्त 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    पटिनिवत्त AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क set_string_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst,
                          पूर्णाङ्क fmt_nb, पूर्णाङ्क ((*get_fmt)(ध्रुव वर्ण *)), ध्रुव वर्ण *desc,
                          गणना AVOptionType type)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णाङ्क fmt, min, max;

    सचे (!val || !strcmp(val, "none")) {
        fmt = -1;
    } अञ्ञथा {
        fmt = get_fmt(val);
        सचे (fmt == -1) {
            वर्ण *tail;
            fmt = strtol(val, &tail, 0);
            सचे (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                पटिनिवत्त AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    सचे(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    सचे (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        पटिनिवत्त AVERROR(ERANGE);
    }

    सचे (dst)
    विकल्प (type) {
    पक्ष AV_OPT_TYPE_PIXEL_FMT:  *(गणना AVPixelFormat *)dst = fmt; भङ्ग;
    पक्ष AV_OPT_TYPE_SAMPLE_FMT: *(गणना AVSampleFormat*)dst = fmt; भङ्ग;
    स्वभाव: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क get_pix_fmt(ध्रुव वर्ण *name)
{
    पटिनिवत्त av_get_pix_fmt(name);
}

स्थिर पूर्णाङ्क set_string_pixel_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    पटिनिवत्त set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

स्थिर पूर्णाङ्क get_sample_fmt(ध्रुव वर्ण *name)
{
    पटिनिवत्त av_get_sample_fmt(name);
}

स्थिर पूर्णाङ्क set_string_sample_fmt(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t *dst)
{
    पटिनिवत्त set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

स्थिर पूर्णाङ्क set_string_dict(शून्य *obj, ध्रुव AVOption *o, ध्रुव वर्ण *val, uint8_t **dst)
{
    AVDictionary *options = रिक्त;

    सचे (val) {
        पूर्णाङ्क ret = av_dict_parse_string(&options, val, "=", ":", 0);
        सचे (ret < 0) {
            av_dict_free(&options);
            पटिनिवत्त ret;
        }
    }

    सचे (!dst) {
        av_dict_free(&options);
        पटिनिवत्त 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क set_string_channel_layout(शून्य *obj, ध्रुव AVOption *o,
                                     ध्रुव वर्ण *val, शून्य *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    पूर्णाङ्क ret;
    सचे (dst)
    av_channel_layout_uninit(channel_layout);
    अञ्ञथा
        channel_layout = &tmp;
    सचे (!val)
        पटिनिवत्त 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    सचे (ret < 0)
        पटिनिवत्त ret;
    सचे (!dst)
        av_channel_layout_uninit(channel_layout);
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क opt_set_elem(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o,
                        ध्रुव वर्ण *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);
    पूर्णाङ्क ret;

    सचे (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        पटिनिवत्त AVERROR(EINVAL);

    विकल्प (type) {
    पक्ष AV_OPT_TYPE_BOOL:
        पटिनिवत्त set_string_bool(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_STRING:
        पटिनिवत्त set_string(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_द्विमान:
        पटिनिवत्त set_string_द्विमान(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_FLAGS:
    पक्ष AV_OPT_TYPE_INT:
    पक्ष AV_OPT_TYPE_UINT:
    पक्ष AV_OPT_TYPE_INT64:
    पक्ष AV_OPT_TYPE_UINT64:
    पक्ष AV_OPT_TYPE_FLOAT:
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_RATIONAL:
        पटिनिवत्त set_string_सङ्ख्या(obj, target_obj, o, val, dst);
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
        पटिनिवत्त set_string_image_size(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        सचे (ret < 0)
            पटिनिवत्त ret;
        पटिनिवत्त write_सङ्ख्या(obj, o, dst, 1, tmp.den, tmp.अङ्कः, 0);
    }
    पक्ष AV_OPT_TYPE_PIXEL_FMT:
        पटिनिवत्त set_string_pixel_fmt(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_SAMPLE_FMT:
        पटिनिवत्त set_string_sample_fmt(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            सचे (val) {
                सचे ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    पटिनिवत्त ret;
                }
            }
            सचे (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                पटिनिवत्त AVERROR(ERANGE);
            }
            सचे (dst)
            *(int64_t *)dst = usecs;
            पटिनिवत्त 0;
        }
    पक्ष AV_OPT_TYPE_COLOR:
        पटिनिवत्त set_string_color(obj, o, val, dst);
    पक्ष AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        सचे (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        पटिनिवत्त ret;
    पक्ष AV_OPT_TYPE_DICT:
        पटिनिवत्त set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    पटिनिवत्त AVERROR(EINVAL);
}

स्थिर पूर्णाङ्क opt_set_array(शून्य *obj, शून्य *target_obj, ध्रुव AVOption *o,
                         ध्रुव वर्ण *val, शून्य *dst)
{
    ध्रुव AVOptionArrayDef *arr = o->default_val.arr;
    ध्रुव size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ध्रुव uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = रिक्त;

    शून्य      *logctx = dst ? obj : रिक्त;
    शून्य       *elems = रिक्त;
    unsigned nb_elems = 0;
    पूर्णाङ्क ret;

    सचे (val && *val) {
        str = av_malloc(strlen(val) + 1);
        सचे (!str)
            पटिनिवत्त AVERROR(ENOMEM);
    }

    // split and unescape the string
    याव (val && *val) {
        uint8_t *p = str;
        शून्य *tmp;

        सचे (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            गच्छ fail;
        }

        अत्थाय (; *val; val++, p++) {
            सचे (*val == '\\' && val[1])
                val++;
            अञ्ञथा सचे (*val == sep) {
                val++;
                भङ्ग;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        सचे (!tmp) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        सचे (ret < 0)
            गच्छ fail;
        nb_elems++;
    }
    av_freep(&str);

    सचे (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    सचे (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        गच्छ fail;
    }

    सचे (dst) {
    *((शून्य **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } अञ्ञथा
        opt_free_array(o, &elems, &nb_elems);

    पटिनिवत्त 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_set(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *val, पूर्णाङ्क अन्वेषणम्_flags)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, 0, &target_obj, &o, &dst);
    सचे (ret < 0)
        पटिनिवत्त ret;

    पटिनिवत्त ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_सङ्ख्या(name, opttype, vartype)                         \
पूर्णाङ्क av_opt_eval_ ## name(शून्य *obj, ध्रुव AVOption *o,                  \
                         ध्रुव वर्ण *val, vartype *name ## _out)        \
{                                                                       \
    सचे (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        पटिनिवत्त AVERROR(EINVAL);                                         \
    पटिनिवत्त set_string_सङ्ख्या(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_सङ्ख्या(flags,  AV_OPT_TYPE_FLAGS,    पूर्णाङ्क)
OPT_EVAL_सङ्ख्या(पूर्णाङ्क,    AV_OPT_TYPE_INT,      पूर्णाङ्क)
OPT_EVAL_सङ्ख्या(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_सङ्ख्या(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_सङ्ख्या(भिन्न,  AV_OPT_TYPE_FLOAT,    भिन्न)
OPT_EVAL_सङ्ख्या(द्विगुण, AV_OPT_TYPE_DOUBLE,   द्विगुण)
OPT_EVAL_सङ्ख्या(q,      AV_OPT_TYPE_RATIONAL, AVRational)

स्थिर पूर्णाङ्क set_सङ्ख्या(शून्य *obj, ध्रुव वर्ण *name, द्विगुण अङ्कः, पूर्णाङ्क den, int64_t intnum,
                      पूर्णाङ्क अन्वेषणम्_flags, पूर्णाङ्क require_type)
{
    शून्य *dst;
    ध्रुव AVOption *o;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, require_type, रिक्त, &o, &dst);
    सचे (ret < 0)
        पटिनिवत्त ret;
    सचे (dst)
        ret = write_सङ्ख्या(obj, o, dst, अङ्कः, den, intnum, 0);

    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_set_int(शून्य *obj, ध्रुव वर्ण *name, int64_t val, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त set_सङ्ख्या(obj, name, 1, 1, val, अन्वेषणम्_flags, 0);
}

पूर्णाङ्क av_opt_set_double(शून्य *obj, ध्रुव वर्ण *name, द्विगुण val, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त set_सङ्ख्या(obj, name, val, 1, 1, अन्वेषणम्_flags, 0);
}

पूर्णाङ्क av_opt_set_q(शून्य *obj, ध्रुव वर्ण *name, AVRational val, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त set_सङ्ख्या(obj, name, val.अङ्कः, val.den, 1, अन्वेषणम्_flags, 0);
}

पूर्णाङ्क av_opt_set_bin(शून्य *obj, ध्रुव वर्ण *name, ध्रुव uint8_t *val, पूर्णाङ्क len, पूर्णाङ्क अन्वेषणम्_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    पूर्णाङ्क *lendst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_द्विमान,
                       रिक्त, रिक्त, (शून्य**)&dst);
    सचे (ret < 0)
        पटिनिवत्त ret;

    सचे (dst) {
    ptr = len ? av_malloc(len) : रिक्त;
    सचे (len && !ptr)
        पटिनिवत्त AVERROR(ENOMEM);

    lendst = (पूर्णाङ्क *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    सचे (len)
        memcpy(ptr, val, len);
    }

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_set_image_size(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क अन्वेषणम्_flags)
{
    ध्रुव AVOption *o;
    शून्य *logctx;
    पूर्णाङ्क *dst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       रिक्त, &o, (शून्य**)&dst);
    सचे (ret < 0)
        पटिनिवत्त ret;

    logctx = dst ? obj : रिक्त;

    सचे (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        पटिनिवत्त AVERROR(EINVAL);
    }

    सचे (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_set_video_rate(शून्य *obj, ध्रुव वर्ण *name, AVRational val, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त set_सङ्ख्या(obj, name, val.अङ्कः, val.den, 1, अन्वेषणम्_flags, AV_OPT_TYPE_VIDEO_RATE);
}

स्थिर पूर्णाङ्क set_format(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क fmt, पूर्णाङ्क अन्वेषणम्_flags,
                      गणना AVOptionType type, ध्रुव वर्ण *desc, पूर्णाङ्क nb_fmts)
{
    ध्रुव AVOption *o;
    शून्य *logctx;
    पूर्णाङ्क *dst;
    पूर्णाङ्क min, max, ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, type, रिक्त, &o, (शून्य**)&dst);
    सचे (ret < 0)
        पटिनिवत्त ret;

    logctx = dst ? obj : रिक्त;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    सचे (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        पटिनिवत्त AVERROR(ERANGE);
    }
    सचे (dst)
    *dst = fmt;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_set_pixel_fmt(शून्य *obj, ध्रुव वर्ण *name, गणना AVPixelFormat fmt, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त set_format(obj, name, fmt, अन्वेषणम्_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

पूर्णाङ्क av_opt_set_sample_fmt(शून्य *obj, ध्रुव वर्ण *name, गणना AVSampleFormat fmt, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त set_format(obj, name, fmt, अन्वेषणम्_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

पूर्णाङ्क av_opt_set_dict_val(शून्य *obj, ध्रुव वर्ण *name, ध्रुव AVDictionary *val,
                        पूर्णाङ्क अन्वेषणम्_flags)
{
    AVDictionary **dst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_DICT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    सचे (ret < 0)
        पटिनिवत्त ret;

    सचे (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_set_chlayout(शून्य *obj, ध्रुव वर्ण *name,
                        ध्रुव AVChannelLayout *channel_layout,
                        पूर्णाङ्क अन्वेषणम्_flags)
{
    AVChannelLayout *dst;
    पूर्णाङ्क ret;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, AV_OPT_TYPE_CHLAYOUT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    सचे (ret < 0)
        पटिनिवत्त ret;

    सचे (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    पटिनिवत्त ret;
}

स्थिर शून्य format_duration(वर्ण *buf, size_t size, int64_t d)
{
    वर्ण *e;

    av_assert0(size >= 25);
    सचे (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    सचे (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    अञ्ञथा सचे (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    अञ्ञथा सचे (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (पूर्णाङ्क)((d / 60000000) % 60),
                 (पूर्णाङ्क)((d / 1000000) % 60),
                 (पूर्णाङ्क)(d % 1000000));
    अञ्ञथा सचे (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (पूर्णाङ्क)(d / 60000000),
                 (पूर्णाङ्क)((d / 1000000) % 60),
                 (पूर्णाङ्क)(d % 1000000));
    अञ्ञथा
        snprintf(buf, size, "%d.%06d",
                 (पूर्णाङ्क)(d / 1000000),
                 (पूर्णाङ्क)(d % 1000000));
    e = buf + strlen(buf);
    याव (e > buf && e[-1] == '0')
        *(--e) = 0;
    सचे (e > buf && e[-1] == '.')
        *(--e) = 0;
}

स्थिर पूर्णाङ्क opt_get_elem(ध्रुव AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ध्रुव शून्य *dst, पूर्णाङ्क अन्वेषणम्_flags)
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
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
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
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->अङ्कः, ((AVRational *)dst)->den);
        भङ्ग;
    पक्ष AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        भङ्ग;
    पक्ष AV_OPT_TYPE_STRING:
        सचे (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } अञ्ञथा सचे (अन्वेषणम्_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = रिक्त;
            पटिनिवत्त 0;
        } अञ्ञथा {
            *pbuf = av_strdup("");
        }
        पटिनिवत्त *pbuf ? 0 : AVERROR(ENOMEM);
    पक्ष AV_OPT_TYPE_द्विमान: {
        ध्रुव uint8_t *bin;
        पूर्णाङ्क len;

        सचे (!*(uint8_t **)dst && (अन्वेषणम्_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            पटिनिवत्त 0;
        }
        len = *(पूर्णाङ्क *)(((uint8_t *)dst) + परिमाण(uint8_t *));
        सचे ((uint64_t)len * 2 + 1 > INT_MAX)
            पटिनिवत्त AVERROR(EINVAL);
        सचे (!(*pbuf = av_malloc(len * 2 + 1)))
            पटिनिवत्त AVERROR(ENOMEM);
        सचे (!len) {
            *pbuf[0] = '\0';
            पटिनिवत्त 0;
        }
        bin = *(uint8_t **)dst;
        अत्थाय (पूर्णाङ्क i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        पटिनिवत्त 0;
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
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
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
        सचे (!*(AVDictionary **)dst && (अन्वेषणम्_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            पटिनिवत्त 0;
        }
        पटिनिवत्त av_dict_get_string(*(AVDictionary **)dst, (वर्ण **)pbuf, '=', ':');
    स्वभाव:
        पटिनिवत्त AVERROR(EINVAL);
    }

    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क opt_get_array(ध्रुव AVOption *o, शून्य *dst, uint8_t **out_val)
{
    ध्रुव unsigned गणनम् = *opt_array_pcount(dst);
    ध्रुव uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = रिक्त;
    size_t   str_len = 0;
    पूर्णाङ्क ret;

    *out_val = रिक्त;

    अत्थाय (unsigned i = 0; i < गणनम्; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, परिमाण(buf),
                           opt_array_pelem(o, *(शून्य **)dst, i), 0);
        सचे (ret < 0)
            गच्छ fail;

        out_len = strlen(out);
        सचे (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            गच्छ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        सचे (ret < 0)
            गच्छ fail;

        // add separator if needed
        सचे (i)
            str[str_len++] = sep;

        // escape the element
        अत्थाय (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            सचे (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        सचे (out != buf)
            av_freep(&out);
        सचे (ret < 0) {
            av_freep(&str);
            पटिनिवत्त ret;
        }
    }

    *out_val = str;

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, uint8_t **out_val)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    uint8_t *out, buf[128];
    पूर्णाङ्क ret;

    सचे (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;

    सचे (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    सचे (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        सचे (ret < 0)
            पटिनिवत्त ret;
        सचे (!*out_val && !(अन्वेषणम्_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            सचे (!*out_val)
               पटिनिवत्त AVERROR(ENOMEM);
        }
        पटिनिवत्त 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, परिमाण(buf), dst, अन्वेषणम्_flags);
    सचे (ret < 0)
        पटिनिवत्त ret;
    सचे (out != buf) {
        *out_val = out;
        पटिनिवत्त 0;
    }

    सचे (ret >= परिमाण(buf))
        पटिनिवत्त AVERROR(EINVAL);
    *out_val = av_strdup(out);
    पटिनिवत्त *out_val ? 0 : AVERROR(ENOMEM);
}

स्थिर पूर्णाङ्क get_सङ्ख्या(शून्य *obj, ध्रुव वर्ण *name, द्विगुण *अङ्कः, पूर्णाङ्क *den, int64_t *intnum,
                      पूर्णाङ्क अन्वेषणम्_flags)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        पटिनिवत्त AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    पटिनिवत्त read_सङ्ख्या(o, dst, अङ्कः, den, intnum);
}

पूर्णाङ्क av_opt_get_int(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    द्विगुण अङ्कः = 1;
    पूर्णाङ्क ret, den = 1;

    सचे ((ret = get_सङ्ख्या(obj, name, &अङ्कः, &den, &intnum, अन्वेषणम्_flags)) < 0)
        पटिनिवत्त ret;
    सचे (अङ्कः == den)
        *out_val = intnum;
    अञ्ञथा
        *out_val = अङ्कः * intnum / den;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_double(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, द्विगुण *out_val)
{
    int64_t intnum = 1;
    द्विगुण अङ्कः = 1;
    पूर्णाङ्क ret, den = 1;

    सचे ((ret = get_सङ्ख्या(obj, name, &अङ्कः, &den, &intnum, अन्वेषणम्_flags)) < 0)
        पटिनिवत्त ret;
    *out_val = अङ्कः * intnum / den;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_q(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    द्विगुण अङ्कः = 1;
    पूर्णाङ्क ret, den = 1;

    सचे ((ret = get_सङ्ख्या(obj, name, &अङ्कः, &den, &intnum, अन्वेषणम्_flags)) < 0)
        पटिनिवत्त ret;

    सचे (अङ्कः == 1.0 && (पूर्णाङ्क)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    अञ्ञथा
        *out_val = double_to_rational(अङ्कः*intnum/den);
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_image_size(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, पूर्णाङ्क *w_out, पूर्णाङ्क *h_out)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        पटिनिवत्त AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    सचे (w_out) *w_out = *(पूर्णाङ्क *)dst;
    सचे (h_out) *h_out = *((पूर्णाङ्क *)dst+1);
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_video_rate(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVRational *out_val)
{
    पटिनिवत्त av_opt_get_q(obj, name, अन्वेषणम्_flags, out_val);
}

स्थिर पूर्णाङ्क get_format(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, शून्य *out_fmt,
                      गणना AVOptionType type, ध्रुव वर्ण *desc)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        पटिनिवत्त AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    सचे (type == AV_OPT_TYPE_PIXEL_FMT)
        *(गणना AVPixelFormat *)out_fmt = *(गणना AVPixelFormat *)dst;
    अञ्ञथा
        *(गणना AVSampleFormat*)out_fmt = *(गणना AVSampleFormat*)dst;

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_pixel_fmt(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, गणना AVPixelFormat *out_fmt)
{
    पटिनिवत्त get_format(obj, name, अन्वेषणम्_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

पूर्णाङ्क av_opt_get_sample_fmt(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, गणना AVSampleFormat *out_fmt)
{
    पटिनिवत्त get_format(obj, name, अन्वेषणम्_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

पूर्णाङ्क av_opt_get_chlayout(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVChannelLayout *cl)
{
    शून्य *dst, *target_obj;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        पटिनिवत्त AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    पटिनिवत्त av_channel_layout_copy(cl, dst);
}

पूर्णाङ्क av_opt_get_dict_val(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags, AVDictionary **out_val)
{
    शून्य *target_obj;
    AVDictionary *src;
    ध्रुव AVOption *o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);

    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (o->type != AV_OPT_TYPE_DICT)
        पटिनिवत्त AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    पटिनिवत्त av_dict_copy(out_val, src, 0);
}

पूर्णाङ्क av_opt_flag_is_set(शून्य *obj, ध्रुव वर्ण *field_name, ध्रुव वर्ण *flag_name)
{
    ध्रुव AVOption *field = av_opt_find(obj, field_name, रिक्त, 0, 0);
    ध्रुव AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : रिक्त, 0, 0);
    int64_t res;

    सचे (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        पटिनिवत्त 0;
    पटिनिवत्त res & flag->default_val.i64;
}

स्थिर शून्य log_int_मानम्(शून्य *av_log_obj, पूर्णाङ्क level, int64_t i)
{
    सचे (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } अञ्ञथा सचे (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } अञ्ञथा सचे (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अञ्ञथा सचे (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अञ्ञथा सचे (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अञ्ञथा {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

स्थिर शून्य log_मानम्(शून्य *av_log_obj, पूर्णाङ्क level, द्विगुण d)
{
    सचे      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } अञ्ञथा सचे (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } अञ्ञथा सचे (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अञ्ञथा सचे (d == (द्विगुण)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अञ्ञथा सचे (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अञ्ञथा सचे (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } अञ्ञथा सचे (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } अञ्ञथा सचे (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } अञ्ञथा सचे (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } अञ्ञथा सचे (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } अञ्ञथा सचे (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } अञ्ञथा सचे (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } अञ्ञथा सचे (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } अञ्ञथा {
        av_log(av_log_obj, level, "%g", d);
    }
}

स्थिर ध्रुव वर्ण *get_opt_const_name(शून्य *obj, ध्रुव वर्ण *unit, int64_t मानम्)
{
    ध्रुव AVOption *opt = रिक्त;

    सचे (!unit)
        पटिनिवत्त रिक्त;
    याव ((opt = av_opt_next(obj, opt)))
        सचे (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == मानम्)
            पटिनिवत्त opt->name;
    पटिनिवत्त रिक्त;
}

स्थिर वर्ण *get_opt_flags_string(शून्य *obj, ध्रुव वर्ण *unit, int64_t मानम्)
{
    ध्रुव AVOption *opt = रिक्त;
    वर्ण flags[512];

    flags[0] = 0;
    सचे (!unit)
        पटिनिवत्त रिक्त;
    याव ((opt = av_opt_next(obj, opt))) {
        सचे (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & मानम्) {
            सचे (flags[0])
                av_strlcatf(flags, परिमाण(flags), "+");
            av_strlcatf(flags, परिमाण(flags), "%s", opt->name);
        }
    }
    सचे (flags[0])
        पटिनिवत्त av_strdup(flags);
    पटिनिवत्त रिक्त;
}

स्थिर शून्य log_type(शून्य *av_log_obj, ध्रुव AVOption *o,
                     गणना AVOptionType parent_type)
{
    ध्रुव गणना AVOptionType type = TYPE_BASE(o->type);

    सचे (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    अञ्ञथा सचे (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        सचे (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        अञ्ञथा
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    अञ्ञथा
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

स्थिर शून्य log_default(शून्य *obj, शून्य *av_log_obj, ध्रुव AVOption *opt)
{
    सचे (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_द्विमान)
        पटिनिवत्त;
    सचे ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        पटिनिवत्त;

    सचे (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ध्रुव AVOptionArrayDef *arr = opt->default_val.arr;
        सचे (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        पटिनिवत्त;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    विकल्प (opt->type) {
    पक्ष AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        भङ्ग;
    पक्ष AV_OPT_TYPE_FLAGS: {
        वर्ण *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        सचे (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } अञ्ञथा {
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
        सचे (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        अञ्ञथा
            log_int_मानम्(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        भङ्ग;
    }
    पक्ष AV_OPT_TYPE_DOUBLE:
    पक्ष AV_OPT_TYPE_FLOAT:
        log_मानम्(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.अङ्कः, q.den); }
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

    याव ((opt = av_opt_next(obj, opt))) {
        सचे (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            अनुवर्त;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        सचे (!unit && opt->type == AV_OPT_TYPE_CONST)
            अनुवर्त;
        अञ्ञथा सचे (unit && opt->type != AV_OPT_TYPE_CONST)
            अनुवर्त;
        अञ्ञथा सचे (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            अनुवर्त;
        अञ्ञथा सचे (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        अञ्ञथा
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

        सचे (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        सचे (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_अन्वेषणम्_FAKE_OBJ) >= 0) {
            विकल्प (opt->type) {
            पक्ष AV_OPT_TYPE_INT:
            पक्ष AV_OPT_TYPE_UINT:
            पक्ष AV_OPT_TYPE_INT64:
            पक्ष AV_OPT_TYPE_UINT64:
            पक्ष AV_OPT_TYPE_DOUBLE:
            पक्ष AV_OPT_TYPE_FLOAT:
            पक्ष AV_OPT_TYPE_RATIONAL:
                अत्थाय (i = 0; i < r->nb_ranges; i++) {
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
        सचे (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

पूर्णाङ्क av_opt_show2(शून्य *obj, शून्य *av_log_obj, पूर्णाङ्क req_flags, पूर्णाङ्क rej_flags)
{
    सचे (!obj)
        पटिनिवत्त -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, रिक्त, req_flags, rej_flags, -1);

    पटिनिवत्त 0;
}

शून्य av_opt_set_defaults(शून्य *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

शून्य av_opt_set_defaults2(शून्य *s, पूर्णाङ्क mask, पूर्णाङ्क flags)
{
    ध्रुव AVOption *opt = रिक्त;
    याव ((opt = av_opt_next(s, opt))) {
        शून्य *dst = ((uint8_t*)s) + opt->offset;

        सचे ((opt->flags & mask) != flags)
            अनुवर्त;

        सचे (opt->flags & AV_OPT_FLAG_READONLY)
            अनुवर्त;

        सचे (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ध्रुव AVOptionArrayDef *arr = opt->default_val.arr;
            ध्रुव वर्ण              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            सचे (arr && arr->def)
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
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_सङ्ख्या(s, opt, dst, 1, val.den, val.अङ्कः, 1);
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
            पक्ष AV_OPT_TYPE_द्विमान:
                set_string_द्विमान(s, opt, opt->default_val.str, dst);
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
स्थिर पूर्णाङ्क parse_कुञ्चिका_मानम्_pair(शून्य *ctx, ध्रुव वर्ण **buf,
                                ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *pairs_sep)
{
    वर्ण *कुञ्चिका = av_get_token(buf, कुञ्चिका_val_sep);
    वर्ण *val;
    पूर्णाङ्क ret;

    सचे (!कुञ्चिका)
        पटिनिवत्त AVERROR(ENOMEM);

    सचे (*कुञ्चिका && strspn(*buf, कुञ्चिका_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        सचे (!val) {
            av_freep(&कुञ्चिका);
            पटिनिवत्त AVERROR(ENOMEM);
        }
    } अञ्ञथा {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", कुञ्चिका);
        av_free(कुञ्चिका);
        पटिनिवत्त AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", कुञ्चिका, val);

    ret = av_opt_set(ctx, कुञ्चिका, val, AV_OPT_अन्वेषणम्_CHILDREN);
    सचे (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", कुञ्चिका);

    av_free(कुञ्चिका);
    av_free(val);
    पटिनिवत्त ret;
}

पूर्णाङ्क av_set_options_string(शून्य *ctx, ध्रुव वर्ण *opts,
                          ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *pairs_sep)
{
    पूर्णाङ्क ret, गणनम् = 0;

    सचे (!opts)
        पटिनिवत्त 0;

    याव (*opts) {
        सचे ((ret = parse_कुञ्चिका_मानम्_pair(ctx, &opts, कुञ्चिका_val_sep, pairs_sep)) < 0)
            पटिनिवत्त ret;
        गणनम्++;

        सचे (*opts)
            opts++;
    }

    पटिनिवत्त गणनम्;
}

#define WHITESPACES " \n\t\r"

स्थिर पूर्णाङ्क is_कुञ्चिका_char(वर्ण c)
{
    पटिनिवत्त (unsigned)((c | 32) - 'a') < 26 ||
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
स्थिर पूर्णाङ्क get_कुञ्चिका(ध्रुव वर्ण **ropts, ध्रुव वर्ण *delim, वर्ण **rkey)
{
    ध्रुव वर्ण *opts = *ropts;
    ध्रुव वर्ण *कुञ्चिका_start, *कुञ्चिका_end;

    कुञ्चिका_start = opts += strspn(opts, WHITESPACES);
    याव (is_कुञ्चिका_char(*opts))
        opts++;
    कुञ्चिका_end = opts;
    opts += strspn(opts, WHITESPACES);
    सचे (!*opts || !strchr(delim, *opts))
        पटिनिवत्त AVERROR(EINVAL);
    opts++;
    सचे (!(*rkey = av_malloc(कुञ्चिका_end - कुञ्चिका_start + 1)))
        पटिनिवत्त AVERROR(ENOMEM);
    memcpy(*rkey, कुञ्चिका_start, कुञ्चिका_end - कुञ्चिका_start);
    (*rkey)[कुञ्चिका_end - कुञ्चिका_start] = 0;
    *ropts = opts;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_कुञ्चिका_मानम्(ध्रुव वर्ण **ropts,
                         ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *pairs_sep,
                         unsigned flags,
                         वर्ण **rkey, वर्ण **rval)
{
    पूर्णाङ्क ret;
    वर्ण *कुञ्चिका = रिक्त, *val;
    ध्रुव वर्ण *opts = *ropts;

    सचे ((ret = get_कुञ्चिका(&opts, कुञ्चिका_val_sep, &कुञ्चिका)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_कुञ्चिका))
        पटिनिवत्त AVERROR(EINVAL);
    सचे (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(कुञ्चिका);
        पटिनिवत्त AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = कुञ्चिका;
    *rval  = val;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_set_from_string(शून्य *ctx, ध्रुव वर्ण *opts,
                           ध्रुव वर्ण *ध्रुव *shorthand,
                           ध्रुव वर्ण *कुञ्चिका_val_sep, ध्रुव वर्ण *pairs_sep)
{
    पूर्णाङ्क ret, गणनम् = 0;
    ध्रुव वर्ण *dummy_shorthand = रिक्त;
    ध्रुव वर्ण *कुञ्चिका;

    सचे (!opts)
        पटिनिवत्त 0;
    सचे (!shorthand)
        shorthand = &dummy_shorthand;

    याव (*opts) {
        वर्ण *parsed_कुञ्चिका, *मानम्;
        ret = av_opt_get_कुञ्चिका_मानम्(&opts, कुञ्चिका_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_कुञ्चिका : 0,
                                   &parsed_कुञ्चिका, &मानम्);
        सचे (ret < 0) {
            सचे (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            अञ्ञथा
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            पटिनिवत्त ret;
        }
        सचे (*opts)
            opts++;
        सचे (parsed_कुञ्चिका) {
            कुञ्चिका = parsed_कुञ्चिका;
            याव (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } अञ्ञथा {
            कुञ्चिका = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", कुञ्चिका, मानम्);
        सचे ((ret = av_opt_set(ctx, कुञ्चिका, मानम्, 0)) < 0) {
            सचे (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", कुञ्चिका);
            av_free(मानम्);
            av_free(parsed_कुञ्चिका);
            पटिनिवत्त ret;
        }

        av_free(मानम्);
        av_free(parsed_कुञ्चिका);
        गणनम्++;
    }
    पटिनिवत्त गणनम्;
}

शून्य av_opt_free(शून्य *obj)
{
    ध्रुव AVOption *o = रिक्त;
    याव ((o = av_opt_next(obj, o))) {
        शून्य *pitem = (uint8_t *)obj + o->offset;

        सचे (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        अञ्ञथा
            opt_free_elem(o->type, pitem);
    }
}

पूर्णाङ्क av_opt_set_dict2(शून्य *obj, AVDictionary **options, पूर्णाङ्क अन्वेषणम्_flags)
{
    ध्रुव AVDictionaryEntry *t = रिक्त;
    AVDictionary    *tmp = रिक्त;
    पूर्णाङ्क ret;

    सचे (!options)
        पटिनिवत्त 0;

    याव ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->कुञ्चिका, t->मानम्, अन्वेषणम्_flags);
        सचे (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->कुञ्चिका, t->मानम्, AV_DICT_MULTIKEY);
        सचे (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->कुञ्चिका, t->मानम्);
            av_dict_free(&tmp);
            पटिनिवत्त ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_set_dict(शून्य *obj, AVDictionary **options)
{
    पटिनिवत्त av_opt_set_dict2(obj, options, 0);
}

ध्रुव AVOption *av_opt_find(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *unit,
                            पूर्णाङ्क opt_flags, पूर्णाङ्क अन्वेषणम्_flags)
{
    पटिनिवत्त av_opt_find2(obj, name, unit, opt_flags, अन्वेषणम्_flags, रिक्त);
}

ध्रुव AVOption *av_opt_find2(शून्य *obj, ध्रुव वर्ण *name, ध्रुव वर्ण *unit,
                             पूर्णाङ्क opt_flags, पूर्णाङ्क अन्वेषणम्_flags, शून्य **target_obj)
{
    ध्रुव AVClass  *c;
    ध्रुव AVOption *o = रिक्त;

    सचे(!obj)
        पटिनिवत्त रिक्त;

    c= *(AVClass**)obj;

    सचे (!c)
        पटिनिवत्त रिक्त;

    सचे (अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_CHILDREN) {
        सचे (अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_FAKE_OBJ) {
            शून्य *iter = रिक्त;
            ध्रुव AVClass *child;
            याव (child = av_opt_child_class_iterate(c, &iter))
                सचे (o = av_opt_find2(&child, name, unit, opt_flags, अन्वेषणम्_flags, रिक्त))
                    पटिनिवत्त o;
        } अञ्ञथा {
            शून्य *child = रिक्त;
            याव (child = av_opt_child_next(obj, child))
                सचे (o = av_opt_find2(child, name, unit, opt_flags, अन्वेषणम्_flags, target_obj))
                    पटिनिवत्त o;
        }
    }

    याव (o = av_opt_next(obj, o)) {
        सचे (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            सचे (target_obj) {
                सचे (!(अन्वेषणम्_flags & AV_OPT_अन्वेषणम्_FAKE_OBJ))
                    *target_obj = obj;
                अञ्ञथा
                    *target_obj = रिक्त;
            }
            पटिनिवत्त o;
        }
    }
    पटिनिवत्त रिक्त;
}

शून्य *av_opt_child_next(शून्य *obj, शून्य *prev)
{
    ध्रुव AVClass *c = *(AVClass **)obj;
    सचे (c->child_next)
        पटिनिवत्त c->child_next(obj, prev);
    पटिनिवत्त रिक्त;
}

ध्रुव AVClass *av_opt_child_class_iterate(ध्रुव AVClass *parent, शून्य **iter)
{
    सचे (parent->child_class_iterate)
        पटिनिवत्त parent->child_class_iterate(iter);
    पटिनिवत्त रिक्त;
}

स्थिर पूर्णाङ्क opt_copy_elem(शून्य *logctx, गणना AVOptionType type,
                         शून्य *dst, ध्रुव शून्य *src)
{
    सचे (type == AV_OPT_TYPE_STRING) {
        ध्रुव वर्ण *src_str = *(ध्रुव वर्ण *ध्रुव *)src;
        वर्ण         **dstp =  (वर्ण **)dst;
        सचे (*dstp != src_str)
            av_freep(dstp);
        सचे (src_str) {
            *dstp = av_strdup(src_str);
            सचे (!*dstp)
                पटिनिवत्त AVERROR(ENOMEM);
        }
    } अञ्ञथा सचे (type == AV_OPT_TYPE_द्विमान) {
        ध्रुव uint8_t *ध्रुव *src8 = (ध्रुव uint8_t *ध्रुव *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        पूर्णाङ्क len = *(ध्रुव पूर्णाङ्क *)(src8 + 1);
        सचे (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        सचे (len && !*dst8) {
            *(पूर्णाङ्क *)(dst8 + 1) = 0;
            पटिनिवत्त AVERROR(ENOMEM);
        }
        *(पूर्णाङ्क *)(dst8 + 1) = len;
    } अञ्ञथा सचे (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } अञ्ञथा सचे (type == AV_OPT_TYPE_DICT) {
        ध्रुव AVDictionary *sdict = *(ध्रुव AVDictionary * ध्रुव *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        सचे (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = रिक्त;
        पटिनिवत्त av_dict_copy(ddictp, sdict, 0);
    } अञ्ञथा सचे (type == AV_OPT_TYPE_CHLAYOUT) {
        ध्रुव AVChannelLayout *slayout = (ध्रुव AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        सचे (dlayout != slayout) {
            सचे (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = रिक्त;
            पटिनिवत्त av_channel_layout_copy(dst, src);
        }
    } अञ्ञथा सचे (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } अञ्ञथा {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        पटिनिवत्त AVERROR(EINVAL);
    }

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क opt_copy_array(शून्य *logctx, ध्रुव AVOption *o,
                          शून्य **pdst, ध्रुव शून्य * ध्रुव *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    शून्य         *dst = रिक्त;
    पूर्णाङ्क ret;

    सचे (*pdst == *psrc) {
        *pdst                   = रिक्त;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    सचे (!dst)
        पटिनिवत्त AVERROR(ENOMEM);

    अत्थाय (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(शून्य**)psrc, i));
        सचे (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            पटिनिवत्त ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_copy(शून्य *dst, ध्रुव शून्य *src)
{
    ध्रुव AVOption *o = रिक्त;
    ध्रुव AVClass *c;
    पूर्णाङ्क ret = 0;

    सचे (!src)
        पटिनिवत्त AVERROR(EINVAL);

    c = *(AVClass **)src;
    सचे (!c || c != *(AVClass **)dst)
        पटिनिवत्त AVERROR(EINVAL);

    याव ((o = av_opt_next(src, o))) {
        शून्य *field_dst = (uint8_t *)dst + o->offset;
        शून्य *field_src = (uint8_t *)src + o->offset;

        पूर्णाङ्क err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        सचे (err < 0)
            ret = err;
    }
    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_get_array_size(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                          unsigned पूर्णाङ्क *out_val)
{
    शून्य *target_obj, *parray;
    ध्रुव AVOption *o;

    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        पटिनिवत्त AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_get_array(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                     unsigned पूर्णाङ्क start_elem, unsigned पूर्णाङ्क nb_elems,
                     गणना AVOptionType out_type, शून्य *out_val)
{
    ध्रुव size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ध्रुव AVOption *o;
    शून्य *target_obj;

    ध्रुव शून्य *parray;
    unsigned array_size;

    पूर्णाङ्क ret;

    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target_obj);
    सचे (!o || !target_obj)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    सचे (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        पटिनिवत्त AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    सचे (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        पटिनिवत्त AVERROR(EINVAL);

    अत्थाय (unsigned i = 0; i < nb_elems; i++) {
        ध्रुव शून्य *src = opt_array_pelem(o, *(शून्य**)parray, start_elem + i);
        शून्य       *dst = (uint8_t*)out_val + i * elem_size_out;

        सचे (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            सचे (ret < 0)
                गच्छ fail;
        } अञ्ञथा सचे (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, परिमाण(buf), src, अन्वेषणम्_flags);
            सचे (ret < 0)
                गच्छ fail;

            सचे (out == buf) {
                out = av_strdup(buf);
                सचे (!out) {
                    ret = AVERROR(ENOMEM);
                    गच्छ fail;
                }
            }

            *(uint8_t**)dst = out;
        } अञ्ञथा सचे (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            द्विगुण     अङ्कः = 1.0;
            पूर्णाङ्क        den = 1;
            int64_t intnum = 1;

            ret = read_सङ्ख्या(o, src, &अङ्कः, &den, &intnum);
            सचे (ret < 0)
                गच्छ fail;

            विकल्प (out_type) {
            पक्ष AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (अङ्कः == den) ?  intnum : अङ्कः * intnum / den;
                भङ्ग;
            पक्ष AV_OPT_TYPE_DOUBLE:
                *(द्विगुण*)dst = अङ्कः * intnum / den;
                भङ्ग;
            पक्ष AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (अङ्कः == 1.0 && (पूर्णाङ्क)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(अङ्कः * intnum / den);
                भङ्ग;
            स्वभाव: av_assert0(0);
            }
        } अञ्ञथा
            पटिनिवत्त AVERROR(ENOSYS);
    }

    पटिनिवत्त 0;
fail:
    अत्थाय (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_set_array(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags,
                     unsigned पूर्णाङ्क start_elem, unsigned पूर्णाङ्क nb_elems,
                     गणना AVOptionType val_type, ध्रुव शून्य *val)
{
    ध्रुव size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ध्रुव AVOption *o;
    ध्रुव AVOptionArrayDef *arr;
    शून्य *target_obj;

    शून्य *parray;
    शून्य *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    पूर्णाङ्क ret = 0;

    ret = opt_set_init(obj, name, अन्वेषणम्_flags, 0, &target_obj, &o, &parray);
    सचे (ret < 0)
        पटिनिवत्त ret;

    सचे (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        पटिनिवत्त AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    सचे (start_elem > *array_size)
        पटिनिवत्त AVERROR(EINVAL);

    // compute new array size
    सचे (!val) {
        सचे (*array_size - start_elem < nb_elems)
            पटिनिवत्त AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } अञ्ञथा सचे (अन्वेषणम्_flags & AV_OPT_ARRAY_REPLACE) {
        सचे (start_elem >= UINT_MAX - nb_elems)
            पटिनिवत्त AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } अञ्ञथा {
        सचे (nb_elems >= UINT_MAX - *array_size)
            पटिनिवत्त AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    सचे (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        पटिनिवत्त AVERROR(EINVAL);

    // desired operation is shrinking the array
    सचे (!val) {
        शून्य *array = *(शून्य**)parray;

        अत्थाय (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        सचे (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            सचे (!array)
                पटिनिवत्त AVERROR(ENOMEM);

            *(शून्य**)parray = array;
        } अञ्ञथा
            av_freep(parray);

        *array_size = new_size;

        पटिनिवत्त 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    सचे (!new_elems)
        पटिनिवत्त AVERROR(ENOMEM);

    // convert/validate each new element
    अत्थाय (unsigned i = 0; i < nb_elems; i++) {
        शून्य       *dst = opt_array_pelem(o, new_elems, i);
        ध्रुव शून्य *src = (uint8_t*)val + i * elem_size_val;

        द्विगुण     अङ्कः = 1.0;
        पूर्णाङ्क        den = 1;
        int64_t intnum = 1;

        सचे (val_type == TYPE_BASE(o->type)) {
            पूर्णाङ्क err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            सचे (ret < 0)
                गच्छ fail;

            // validate the range for numeric options
            err = read_सङ्ख्या(o, dst, &अङ्कः, &den, &intnum);
            सचे (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < अङ्कः * intnum || o->min * den > अङ्कः * intnum)) {
                अङ्कः = den ? अङ्कः * intnum / den : (अङ्कः && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, अङ्कः, o->min, o->max);
                ret = AVERROR(ERANGE);
                गच्छ fail;
            }
        } अञ्ञथा सचे (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ध्रुव वर्ण **)src, dst);
            सचे (ret < 0)
                गच्छ fail;
        } अञ्ञथा सचे (val_type == AV_OPT_TYPE_INT ||
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
            सचे (ret < 0)
                गच्छ fail;
        } अञ्ञथा {
            ret = AVERROR(ENOSYS);
            गच्छ fail;
        }
    }

    // commit new elements to the array
    सचे (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(शून्य**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = रिक्त;
        nb_elems  = 0;
    } अञ्ञथा {
        शून्य *array = av_realloc_array(*(शून्य**)parray, new_size, elem_size);
        सचे (!array) {
            ret = AVERROR(ENOMEM);
            गच्छ fail;
        }

        सचे (अन्वेषणम्_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            अत्थाय (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } अञ्ञथा {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(शून्य**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_query_ranges(AVOptionRanges **ranges_arg, शून्य *obj, ध्रुव वर्ण *कुञ्चिका, पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;
    ध्रुव AVClass *c = *(AVClass**)obj;
    पूर्णाङ्क (*callback)(AVOptionRanges **, शून्य *obj, ध्रुव वर्ण *कुञ्चिका, पूर्णाङ्क flags) = c->query_ranges;

    सचे (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, कुञ्चिका, flags);
    सचे (ret >= 0) {
        सचे (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    पटिनिवत्त ret;
}

पूर्णाङ्क av_opt_query_ranges_default(AVOptionRanges **ranges_arg, शून्य *obj, ध्रुव वर्ण *कुञ्चिका, पूर्णाङ्क flags)
{
    AVOptionRanges *ranges = av_mallocz(परिमाण(*ranges));
    AVOptionRange **range_array = av_mallocz(परिमाण(शून्य*));
    AVOptionRange *range = av_mallocz(परिमाण(*range));
    ध्रुव AVOption *field = av_opt_find(obj, कुञ्चिका, रिक्त, 0, flags);
    पूर्णाङ्क ret;

    *ranges_arg = रिक्त;

    सचे (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->मानम्_min = field->min;
    range->मानम्_max = field->max;

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
        range->मानम्_min = -1;
        range->मानम्_max = INT_MAX;
        भङ्ग;
    पक्ष AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        भङ्ग;
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->मानम्_min = 0;
        range->मानम्_max = INT_MAX/8;
        भङ्ग;
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->मानम्_min = 1;
        range->मानम्_max = INT_MAX;
        भङ्ग;
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    *ranges_arg = ranges;
    पटिनिवत्त 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    पटिनिवत्त ret;
}

शून्य av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    पूर्णाङ्क i;
    AVOptionRanges *ranges = *rangesp;

    सचे (!ranges)
        पटिनिवत्त;

    अत्थाय (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        सचे (range) {
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

    सचे (!o || !obj)
        पटिनिवत्त AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    सचे (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ध्रुव वर्ण *def = o->default_val.arr ? o->default_val.arr->def : रिक्त;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        सचे (ret < 0)
            पटिनिवत्त ret;

        सचे (!!val != !!def)
            ret = 0;
        अञ्ञथा सचे (val)
            ret = !strcmp(val, def);
        अञ्ञथा
            ret = 1;

        av_freep(&val);

        पटिनिवत्त ret;
    }

    विकल्प (o->type) {
    पक्ष AV_OPT_TYPE_CONST:
        पटिनिवत्त 1;
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
        पटिनिवत्त o->default_val.i64 == i64;
    पक्ष AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        सचे (o->default_val.str) {
            सचे ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                पटिनिवत्त ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        पटिनिवत्त ret;
    }
    पक्ष AV_OPT_TYPE_STRING:
        str = *(वर्ण **)dst;
        सचे (str == o->default_val.str) //2 NULLs
            पटिनिवत्त 1;
        सचे (!str || !o->default_val.str) //1 NULL
            पटिनिवत्त 0;
        पटिनिवत्त !strcmp(str, o->default_val.str);
    पक्ष AV_OPT_TYPE_DOUBLE:
        d = *(द्विगुण *)dst;
        पटिनिवत्त o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    पक्ष AV_OPT_TYPE_FLOAT:
        d = *(भिन्न *)dst;
        पटिनिवत्त (भिन्न)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    पक्ष AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        पटिनिवत्त !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    पक्ष AV_OPT_TYPE_द्विमान: {
        संरचना {
            uint8_t *data;
            पूर्णाङ्क size;
        } tmp = {0};
        पूर्णाङ्क opt_size = *(पूर्णाङ्क *)((शून्य **)dst + 1);
        शून्य *opt_ptr = *(शून्य **)dst;
        सचे (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            पटिनिवत्त 1;
        सचे (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            पटिनिवत्त 0;
        सचे (opt_size != strlen(o->default_val.str) / 2)
            पटिनिवत्त 0;
        ret = set_string_द्विमान(रिक्त, रिक्त, o->default_val.str, &tmp.data);
        सचे (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        पटिनिवत्त ret;
    }
    पक्ष AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = रिक्त;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ध्रुव AVDictionaryEntry *en1 = रिक्त;
        ध्रुव AVDictionaryEntry *en2 = रिक्त;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        सचे (ret < 0) {
            av_dict_free(&dict1);
            पटिनिवत्त ret;
        }
        करोहि {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } याव (en1 && en2 && !strcmp(en1->कुञ्चिका, en2->कुञ्चिका) && !strcmp(en1->मानम्, en2->मानम्));
        av_dict_free(&dict1);
        पटिनिवत्त (!en1 && !en2);
    }
    पक्ष AV_OPT_TYPE_IMAGE_SIZE:
        सचे (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        अञ्ञथा सचे ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            पटिनिवत्त ret;
        पटिनिवत्त (w == *(पूर्णाङ्क *)dst) && (h == *((पूर्णाङ्क *)dst+1));
    पक्ष AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        सचे (o->default_val.str) {
            सचे ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                पटिनिवत्त ret;
        }
        पटिनिवत्त !av_cmp_q(*(AVRational*)dst, q);
    पक्ष AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        सचे (o->default_val.str) {
            सचे ((ret = av_parse_color(color, o->default_val.str, -1, रिक्त)) < 0)
                पटिनिवत्त ret;
        }
        पटिनिवत्त !memcmp(color, dst, परिमाण(color));
    }
    स्वभाव:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        भङ्ग;
    }
    पटिनिवत्त AVERROR_PATCHWELCOME;
}

पूर्णाङ्क av_opt_is_set_to_default_by_name(शून्य *obj, ध्रुव वर्ण *name, पूर्णाङ्क अन्वेषणम्_flags)
{
    ध्रुव AVOption *o;
    शून्य *target;
    सचे (!obj)
        पटिनिवत्त AVERROR(EINVAL);
    o = av_opt_find2(obj, name, रिक्त, 0, अन्वेषणम्_flags, &target);
    सचे (!o)
        पटिनिवत्त AVERROR_OPTION_NOT_FOUND;
    पटिनिवत्त av_opt_is_set_to_default(target, o);
}

स्थिर पूर्णाङ्क opt_serialize(शून्य *obj, पूर्णाङ्क opt_flags, पूर्णाङ्क flags, पूर्णाङ्क *cnt,
                         AVBPrint *bprint, ध्रुव वर्ण कुञ्चिका_val_sep, ध्रुव वर्ण pairs_sep)
{
    ध्रुव AVOption *o = रिक्त;
    शून्य *child = रिक्त;
    uint8_t *buf;
    पूर्णाङ्क ret;
    ध्रुव वर्ण special_chars[] = {pairs_sep, कुञ्चिका_val_sep, '\0'};

    सचे (flags & AV_OPT_SERIALIZE_अन्वेषणम्_CHILDREN)
        याव (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                कुञ्चिका_val_sep, pairs_sep);
            सचे (ret < 0)
                पटिनिवत्त ret;
        }

    याव (o = av_opt_next(obj, o)) {
        सचे (o->type == AV_OPT_TYPE_CONST)
            अनुवर्त;
        सचे ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            सचे ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                सचे (o->flags == opt_flags)
                    अनुवर्त;
            } अञ्ञथा सचे ((o->flags & opt_flags) == opt_flags)
                अनुवर्त;
        } अञ्ञथा {
            सचे ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                अनुवर्त;
            अञ्ञथा सचे (((o->flags & opt_flags) != opt_flags))
                अनुवर्त;
        }
        सचे (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            अनुवर्त;
        सचे ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, रिक्त);
            पटिनिवत्त ret;
        }
        सचे (buf) {
            सचे ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &कुञ्चिका_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    पटिनिवत्त 0;
}

पूर्णाङ्क av_opt_serialize(शून्य *obj, पूर्णाङ्क opt_flags, पूर्णाङ्क flags, वर्ण **buffer,
                     ध्रुव वर्ण कुञ्चिका_val_sep, ध्रुव वर्ण pairs_sep)
{
    AVBPrint bprint;
    पूर्णाङ्क ret, cnt = 0;

    सचे (pairs_sep == '\0' || कुञ्चिका_val_sep == '\0' || pairs_sep == कुञ्चिका_val_sep ||
        pairs_sep == '\\' || कुञ्चिका_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        पटिनिवत्त AVERROR(EINVAL);
    }

    सचे (!obj || !buffer)
        पटिनिवत्त AVERROR(EINVAL);

    *buffer = रिक्त;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        कुञ्चिका_val_sep, pairs_sep);
    सचे (ret < 0)
        पटिनिवत्त ret;

    ret = av_bprint_finalize(&bprint, buffer);
    सचे (ret < 0)
        पटिनिवत्त ret;
    पटिनिवत्त 0;
}
