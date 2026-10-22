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

स्थिरांक AVOption *av_opt_next(स्थिरांक शून्य *obj, स्थिरांक AVOption *last)
{
    स्थिरांक AVClass *class;
    जर (!obj)
        परत रिक्त;
    class = *(स्थिरांक AVClass**)obj;
    जर (!last && class && class->option && class->option[0].name)
        परत class->option;
    जर (last && last[1].name)
        परत ++last;
    परत रिक्त;
}

स्थिर स्थिरांक संरचना {
    माप_प्रकार      size;
    स्थिरांक अक्षर *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { आकार(अचिन्हित),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { आकार(पूर्णांक),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { आकार(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { आकार(अचिन्हित),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { आकार(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { आकार(द्विगुण),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { आकार(दशांश),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { आकार(अक्षर *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { आकार(AVRational),     "<rational>" },
    [AV_OPT_TYPE_द्विमान]        = { आकार(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { आकार(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { आकार(पूर्णांक[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { आकार(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { आकार(गणना AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { आकार(गणना AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { आकार(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { आकार(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { आकार(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { आकार(पूर्णांक),            "<boolean>" },
};

// option is plain old data
स्थिर पूर्णांक opt_is_pod(गणना AVOptionType type)
{
    निवड (type) {
    स्थिती AV_OPT_TYPE_FLAGS:
    स्थिती AV_OPT_TYPE_INT:
    स्थिती AV_OPT_TYPE_INT64:
    स्थिती AV_OPT_TYPE_DOUBLE:
    स्थिती AV_OPT_TYPE_FLOAT:
    स्थिती AV_OPT_TYPE_RATIONAL:
    स्थिती AV_OPT_TYPE_UINT64:
    स्थिती AV_OPT_TYPE_IMAGE_SIZE:
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
    स्थिती AV_OPT_TYPE_VIDEO_RATE:
    स्थिती AV_OPT_TYPE_DURATION:
    स्थिती AV_OPT_TYPE_COLOR:
    स्थिती AV_OPT_TYPE_BOOL:
    स्थिती AV_OPT_TYPE_UINT:
        परत 1;
    }
    परत 0;
}

स्थिर uint8_t opt_array_sep(स्थिरांक AVOption *o)
{
    स्थिरांक AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    परत (d && d->sep) ? d->sep : ',';
}

स्थिर शून्य *opt_array_pelem(स्थिरांक AVOption *o, शून्य *array, अचिन्हित idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    परत (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

स्थिर अचिन्हित *opt_array_pcount(स्थिरांक शून्य *parray)
{
    परत (अचिन्हित *)((स्थिरांक शून्य * स्थिरांक *)parray + 1);
}

स्थिर शून्य opt_free_elem(गणना AVOptionType type, शून्य *ptr)
{
    निवड (TYPE_BASE(type)) {
    स्थिती AV_OPT_TYPE_STRING:
    स्थिती AV_OPT_TYPE_द्विमान:
        av_freep(ptr);
        थांबा;

    स्थिती AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        थांबा;

    स्थिती AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        थांबा;

    पूर्वनिर्धारित:
        थांबा;
    }
}

स्थिर शून्य opt_free_array(स्थिरांक AVOption *o, शून्य *parray, अचिन्हित *मोजणी)
{
    साठी (अचिन्हित i = 0; i < *मोजणी; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(शून्य **)parray, i));

    av_freep(parray);
    *मोजणी = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
स्थिर पूर्णांक opt_set_init(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags,
                        पूर्णांक require_type,
                        शून्य **ptgt, स्थिरांक AVOption **po, शून्य **pdst)
{
    शून्य *logctx;
    स्थिरांक AVOption *o;
    शून्य *tgt;

    o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &tgt);
    जर (!o || (!tgt && !(शोध_flags & AV_OPT_शोध_FAKE_OBJ)))
        परत AVERROR_OPTION_NOT_FOUND;

    जर (o->flags & AV_OPT_FLAG_READONLY)
        परत AVERROR(EINVAL);

    logctx = tgt ? obj : रिक्त;

    जर (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        परत AVERROR(EINVAL);
    }

    जर (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        अचिन्हित *state_flags = रिक्त;
        स्थिरांक AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(स्थिरांक AVClass**)tgt;
        जर (class->state_flags_offset)
            state_flags = (अचिन्हित*)((uint8_t*)tgt + class->state_flags_offset);

        जर (!state_flags && obj != tgt) {
            class = *(स्थिरांक AVClass**)obj;
            जर (class->state_flags_offset)
                state_flags = (अचिन्हित*)((uint8_t*)obj + class->state_flags_offset);
        }

        जर (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            परत AVERROR(EINVAL);
        }
    }

    जर (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    जर (po)
        *po   = o;
    जर (ptgt)
        *ptgt = tgt;
    जर (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : रिक्त;

    परत 0;
}

स्थिर AVRational double_to_rational(द्विगुण d)
{
     AVRational r = av_d2q(d, 1 << 24);
     जर ((!r.अंक || !r.den) && d)
         r = av_d2q(d, पूर्णांक_उच्च);
     परत r;
}

स्थिर पूर्णांक read_संख्या(स्थिरांक AVOption *o, स्थिरांक शून्य *dst, द्विगुण *अंक, पूर्णांक *den, int64_t *intnum)
{
    निवड (TYPE_BASE(o->type)) {
    स्थिती AV_OPT_TYPE_FLAGS:
        *intnum = *(अचिन्हित पूर्णांक*)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(गणना AVPixelFormat *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(गणना AVSampleFormat *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_BOOL:
    स्थिती AV_OPT_TYPE_INT:
        *intnum = *(पूर्णांक *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_UINT:
        *intnum = *(अचिन्हित पूर्णांक *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_DURATION:
    स्थिती AV_OPT_TYPE_INT64:
    स्थिती AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_FLOAT:
        *अंक = *(दशांश *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_DOUBLE:
        *अंक = *(द्विगुण *)dst;
        परत 0;
    स्थिती AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->अंक;
        *den    = ((AVRational *)dst)->den;
        परत 0;
    स्थिती AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        परत 0;
    }
    परत AVERROR(EINVAL);
}

स्थिर पूर्णांक write_संख्या(शून्य *obj, स्थिरांक AVOption *o, शून्य *dst,
                        द्विगुण अंक, पूर्णांक den, int64_t intnum,
                        पूर्णांक ignore_range)
{
    शून्य *logctx = dst ? obj : रिक्त;
    स्थिरांक गणना AVOptionType type = TYPE_BASE(o->type);

    जर (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < अंक * intnum || o->min * den > अंक * intnum)) {
        अंक = den ? अंक * intnum / den : (अंक && intnum ? अनन्त : न_अंक);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               अंक, o->name, o->min, o->max);
        परत AVERROR(दुस्फल);
    }
    जर (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        द्विगुण d = अंक*intnum/den;
        जर (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   अंक*intnum/den, o->name);
            परत AVERROR(दुस्फल);
        }
    }

    जर (!dst)
        परत 0;

    निवड (type) {
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
        *(गणना AVPixelFormat *)dst = llrint(अंक / den) * intnum;
        थांबा;
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
        *(गणना AVSampleFormat *)dst = llrint(अंक / den) * intnum;
        थांबा;
    स्थिती AV_OPT_TYPE_BOOL:
    स्थिती AV_OPT_TYPE_FLAGS:
    स्थिती AV_OPT_TYPE_INT:
    स्थिती AV_OPT_TYPE_UINT:
        *(पूर्णांक *)dst = llrint(अंक / den) * intnum;
        थांबा;
    स्थिती AV_OPT_TYPE_DURATION:
    स्थिती AV_OPT_TYPE_INT64:{
        द्विगुण d = अंक / den;
        जर (intnum == 1 && d == (द्विगुण)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } अन्यथा
            *(int64_t *)dst = llrint(d) * intnum;
        थांबा;}
    स्थिती AV_OPT_TYPE_UINT64:{
        द्विगुण d = अंक / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        जर (intnum == 1 && d == (द्विगुण)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } अन्यथा जर (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } अन्यथा {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        थांबा;}
    स्थिती AV_OPT_TYPE_FLOAT:
        *(दशांश *)dst = अंक * intnum / den;
        थांबा;
    स्थिती AV_OPT_TYPE_DOUBLE:
        *(द्विगुण    *)dst = अंक * intnum / den;
        थांबा;
    स्थिती AV_OPT_TYPE_RATIONAL:
    स्थिती AV_OPT_TYPE_VIDEO_RATE:
        जर ((पूर्णांक) अंक == अंक)
            *(AVRational *)dst = (AVRational) { अंक *intnum, den };
        अन्यथा
            *(AVRational *)dst = double_to_rational(अंक * intnum / den);
        थांबा;
    पूर्वनिर्धारित:
        परत AVERROR(EINVAL);
    }
    परत 0;
}

स्थिर पूर्णांक hexchar2int(अक्षर c) {
    जर (c >= '0' && c <= '9')
        परत c - '0';
    जर (c >= 'a' && c <= 'f')
        परत c - 'a' + 10;
    जर (c >= 'A' && c <= 'F')
        परत c - 'A' + 10;
    परत -1;
}

स्थिर पूर्णांक set_string_द्विमान(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t **dst)
{
    पूर्णांक *lendst;
    uint8_t *bin, *ptr;
    पूर्णांक len;

    जर (dst) {
        lendst = (पूर्णांक *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    जर (!val || !(len = म_माप(val)))
        परत 0;

    जर (len & 1)
        परत AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    जर (!ptr)
        परत AVERROR(ENOMEM);
    पर्यंत (*val) {
        पूर्णांक a = hexchar2int(*val++);
        पूर्णांक b = hexchar2int(*val++);
        जर (a < 0 || b < 0) {
            av_free(bin);
            परत AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    जर (dst) {
        *dst    = bin;
        *lendst = len;
    } अन्यथा {
        av_free(bin);
    }

    परत 0;
}

स्थिर पूर्णांक set_string(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t **dst)
{
    जर (!dst)
        परत 0;
    av_freep(dst);
    जर (!val)
        परत 0;
    *dst = av_strdup(val);
    परत *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

स्थिर पूर्णांक set_string_संख्या(शून्य *obj, शून्य *target_obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    स्थिरांक गणना AVOptionType type = TYPE_BASE(o->type);
    पूर्णांक ret = 0;

    जर (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        पूर्णांक अंक, den;
        अक्षर c;
        जर (माला_पूछो(val, "%d%*1[:/]%d%c", &अंक, &den, &c) == 2) {
            जर ((ret = write_संख्या(obj, o, dst, 1, den, अंक, 0)) >= 0)
                परत ret;
            ret = 0;
        }
    }

    साठी (;;) {
        पूर्णांक i = 0;
        अक्षर buf[256];
        पूर्णांक cmd = 0;
        द्विगुण d;
        int64_t intnum = 1;

        जर (type == AV_OPT_TYPE_FLAGS) {
            जर (*val == '+' || *val == '-')
                cmd = *(val++);
            साठी (; i < आकार(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            पूर्णांक res;
            पूर्णांक ci = 0;
            द्विगुण const_मूल्ये[64];
            स्थिरांक अक्षर * const_names[64];
            पूर्णांक शोध_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_शोध_CHILDREN : 0;
            स्थिरांक AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, शोध_flags);
            जर (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                जर (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } अन्यथा {
                जर (o->unit) {
                    साठी (o_named = रिक्त; o_named = av_opt_next(target_obj, o_named); ) {
                        जर (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !म_भेद(o_named->unit, o->unit)) {
                            जर (ci + 6 >= FF_ARRAY_ELEMS(const_मूल्ये)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                परत AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_मूल्ये[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_मूल्ये[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_मूल्ये[ci++] = o->max;
                const_names [ci  ] = "min";
                const_मूल्ये[ci++] = o->min;
                const_names [ci  ] = "none";
                const_मूल्ये[ci++] = 0;
                const_names [ci  ] = "all";
                const_मूल्ये[ci++] = ~0;
                const_names [ci] = रिक्त;
                const_मूल्ये[ci] = 0;

                res = av_अभिव्यक्ती_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_मूल्ये, रिक्त, रिक्त, रिक्त, रिक्त, रिक्त, 0, obj);
                जर (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    परत res;
                }
            }
        }
        जर (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(अचिन्हित पूर्णांक*)dst;
            जर (cmd == '+')
                d = intnum | (int64_t)d;
            अन्यथा जर (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        जर ((ret = write_संख्या(obj, o, dst, d, 1, 1, 0)) < 0)
            परत ret;
        val += i;
        जर (!i || !*val)
            परत 0;
    }
}

स्थिर पूर्णांक set_string_image_size(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, पूर्णांक *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णांक tmp[2];
    पूर्णांक ret;

    जर (!val || !म_भेद(val, "none")) {
        जर (dst) {
        dst[0] =
        dst[1] = 0;
        }
        परत 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    जर (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        परत ret;
    }
    जर (dst)
        स_नकल(dst, tmp, आकार(tmp));
    परत ret;
}

स्थिर पूर्णांक set_string_video_rate(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, AVRational *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    AVRational tmp;
    पूर्णांक ret = av_parse_video_rate(&tmp, val);
    जर (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    जर (dst)
        *dst = tmp;
    परत ret;
}

स्थिर पूर्णांक set_string_color(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णांक ret;

    जर (!val) {
        परत 0;
    } अन्यथा {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        जर (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            परत ret;
        }
        जर (dst)
            स_नकल(dst, tmp, आकार(tmp));
        परत ret;
    }
    परत 0;
}

स्थिर स्थिरांक अक्षर *get_bool_name(पूर्णांक val)
{
    जर (val < 0)
        परत "auto";
    परत val ? "true" : "false";
}

स्थिर पूर्णांक set_string_bool(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, पूर्णांक *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णांक n;

    जर (!val)
        परत 0;

    जर (!म_भेद(val, "auto")) {
        n = -1;
    } अन्यथा जर (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } अन्यथा जर (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } अन्यथा {
        अक्षर *end = रिक्त;
        n = म_से_दीर्घ(val, &end, 10);
        जर (val + म_माप(val) != end)
            जा fail;
    }

    जर (n < o->min || n > o->max)
        जा fail;

    जर (dst)
    *dst = n;
    परत 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    परत AVERROR(EINVAL);
}

स्थिर पूर्णांक set_string_fmt(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t *dst,
                          पूर्णांक fmt_nb, पूर्णांक ((*get_fmt)(स्थिरांक अक्षर *)), स्थिरांक अक्षर *desc,
                          गणना AVOptionType type)
{
    शून्य *logctx = dst ? obj : रिक्त;
    पूर्णांक fmt, min, max;

    जर (!val || !म_भेद(val, "none")) {
        fmt = -1;
    } अन्यथा {
        fmt = get_fmt(val);
        जर (fmt == -1) {
            अक्षर *tail;
            fmt = म_से_दीर्घ(val, &tail, 0);
            जर (*tail || (अचिन्हित)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                परत AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    जर(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    जर (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        परत AVERROR(दुस्फल);
    }

    जर (dst)
    निवड (type) {
    स्थिती AV_OPT_TYPE_PIXEL_FMT:  *(गणना AVPixelFormat *)dst = fmt; थांबा;
    स्थिती AV_OPT_TYPE_SAMPLE_FMT: *(गणना AVSampleFormat*)dst = fmt; थांबा;
    पूर्वनिर्धारित: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    परत 0;
}

स्थिर पूर्णांक get_pix_fmt(स्थिरांक अक्षर *name)
{
    परत av_get_pix_fmt(name);
}

स्थिर पूर्णांक set_string_pixel_fmt(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t *dst)
{
    परत set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

स्थिर पूर्णांक get_sample_fmt(स्थिरांक अक्षर *name)
{
    परत av_get_sample_fmt(name);
}

स्थिर पूर्णांक set_string_sample_fmt(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t *dst)
{
    परत set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

स्थिर पूर्णांक set_string_dict(शून्य *obj, स्थिरांक AVOption *o, स्थिरांक अक्षर *val, uint8_t **dst)
{
    AVDictionary *options = रिक्त;

    जर (val) {
        पूर्णांक ret = av_dict_parse_string(&options, val, "=", ":", 0);
        जर (ret < 0) {
            av_dict_free(&options);
            परत ret;
        }
    }

    जर (!dst) {
        av_dict_free(&options);
        परत 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    परत 0;
}

स्थिर पूर्णांक set_string_channel_layout(शून्य *obj, स्थिरांक AVOption *o,
                                     स्थिरांक अक्षर *val, शून्य *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    पूर्णांक ret;
    जर (dst)
    av_channel_layout_uninit(channel_layout);
    अन्यथा
        channel_layout = &tmp;
    जर (!val)
        परत 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    जर (ret < 0)
        परत ret;
    जर (!dst)
        av_channel_layout_uninit(channel_layout);
    परत 0;
}

स्थिर पूर्णांक opt_set_elem(शून्य *obj, शून्य *target_obj, स्थिरांक AVOption *o,
                        स्थिरांक अक्षर *val, शून्य *dst)
{
    शून्य *logctx = dst ? obj : रिक्त;
    स्थिरांक गणना AVOptionType type = TYPE_BASE(o->type);
    पूर्णांक ret;

    जर (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        परत AVERROR(EINVAL);

    निवड (type) {
    स्थिती AV_OPT_TYPE_BOOL:
        परत set_string_bool(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_STRING:
        परत set_string(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_द्विमान:
        परत set_string_द्विमान(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_FLAGS:
    स्थिती AV_OPT_TYPE_INT:
    स्थिती AV_OPT_TYPE_UINT:
    स्थिती AV_OPT_TYPE_INT64:
    स्थिती AV_OPT_TYPE_UINT64:
    स्थिती AV_OPT_TYPE_FLOAT:
    स्थिती AV_OPT_TYPE_DOUBLE:
    स्थिती AV_OPT_TYPE_RATIONAL:
        परत set_string_संख्या(obj, target_obj, o, val, dst);
    स्थिती AV_OPT_TYPE_IMAGE_SIZE:
        परत set_string_image_size(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        जर (ret < 0)
            परत ret;
        परत write_संख्या(obj, o, dst, 1, tmp.den, tmp.अंक, 0);
    }
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
        परत set_string_pixel_fmt(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
        परत set_string_sample_fmt(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            जर (val) {
                जर ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    परत ret;
                }
            }
            जर (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                परत AVERROR(दुस्फल);
            }
            जर (dst)
            *(int64_t *)dst = usecs;
            परत 0;
        }
    स्थिती AV_OPT_TYPE_COLOR:
        परत set_string_color(obj, o, val, dst);
    स्थिती AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        जर (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        परत ret;
    स्थिती AV_OPT_TYPE_DICT:
        परत set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    परत AVERROR(EINVAL);
}

स्थिर पूर्णांक opt_set_array(शून्य *obj, शून्य *target_obj, स्थिरांक AVOption *o,
                         स्थिरांक अक्षर *val, शून्य *dst)
{
    स्थिरांक AVOptionArrayDef *arr = o->default_val.arr;
    स्थिरांक माप_प्रकार      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    स्थिरांक uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = रिक्त;

    शून्य      *logctx = dst ? obj : रिक्त;
    शून्य       *elems = रिक्त;
    अचिन्हित nb_elems = 0;
    पूर्णांक ret;

    जर (val && *val) {
        str = av_malloc(म_माप(val) + 1);
        जर (!str)
            परत AVERROR(ENOMEM);
    }

    // split and unescape the string
    पर्यंत (val && *val) {
        uint8_t *p = str;
        शून्य *tmp;

        जर (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            जा fail;
        }

        साठी (; *val; val++, p++) {
            जर (*val == '\\' && val[1])
                val++;
            अन्यथा जर (*val == sep) {
                val++;
                थांबा;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        जर (!tmp) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        स_रखो(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        जर (ret < 0)
            जा fail;
        nb_elems++;
    }
    av_freep(&str);

    जर (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    जर (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        जा fail;
    }

    जर (dst) {
    *((शून्य **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } अन्यथा
        opt_free_array(o, &elems, &nb_elems);

    परत 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    परत ret;
}

पूर्णांक av_opt_set(शून्य *obj, स्थिरांक अक्षर *name, स्थिरांक अक्षर *val, पूर्णांक शोध_flags)
{
    शून्य *dst, *target_obj;
    स्थिरांक AVOption *o;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, शोध_flags, 0, &target_obj, &o, &dst);
    जर (ret < 0)
        परत ret;

    परत ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_संख्या(name, opttype, vartype)                         \
पूर्णांक av_opt_eval_ ## name(शून्य *obj, स्थिरांक AVOption *o,                  \
                         स्थिरांक अक्षर *val, vartype *name ## _out)        \
{                                                                       \
    जर (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        परत AVERROR(EINVAL);                                         \
    परत set_string_संख्या(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_संख्या(flags,  AV_OPT_TYPE_FLAGS,    पूर्णांक)
OPT_EVAL_संख्या(पूर्णांक,    AV_OPT_TYPE_INT,      पूर्णांक)
OPT_EVAL_संख्या(uint,   AV_OPT_TYPE_UINT,     अचिन्हित)
OPT_EVAL_संख्या(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_संख्या(दशांश,  AV_OPT_TYPE_FLOAT,    दशांश)
OPT_EVAL_संख्या(द्विगुण, AV_OPT_TYPE_DOUBLE,   द्विगुण)
OPT_EVAL_संख्या(q,      AV_OPT_TYPE_RATIONAL, AVRational)

स्थिर पूर्णांक set_संख्या(शून्य *obj, स्थिरांक अक्षर *name, द्विगुण अंक, पूर्णांक den, int64_t intnum,
                      पूर्णांक शोध_flags, पूर्णांक require_type)
{
    शून्य *dst;
    स्थिरांक AVOption *o;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, शोध_flags, require_type, रिक्त, &o, &dst);
    जर (ret < 0)
        परत ret;
    जर (dst)
        ret = write_संख्या(obj, o, dst, अंक, den, intnum, 0);

    परत ret;
}

पूर्णांक av_opt_set_int(शून्य *obj, स्थिरांक अक्षर *name, int64_t val, पूर्णांक शोध_flags)
{
    परत set_संख्या(obj, name, 1, 1, val, शोध_flags, 0);
}

पूर्णांक av_opt_set_double(शून्य *obj, स्थिरांक अक्षर *name, द्विगुण val, पूर्णांक शोध_flags)
{
    परत set_संख्या(obj, name, val, 1, 1, शोध_flags, 0);
}

पूर्णांक av_opt_set_q(शून्य *obj, स्थिरांक अक्षर *name, AVRational val, पूर्णांक शोध_flags)
{
    परत set_संख्या(obj, name, val.अंक, val.den, 1, शोध_flags, 0);
}

पूर्णांक av_opt_set_bin(शून्य *obj, स्थिरांक अक्षर *name, स्थिरांक uint8_t *val, पूर्णांक len, पूर्णांक शोध_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    पूर्णांक *lendst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, शोध_flags, AV_OPT_TYPE_द्विमान,
                       रिक्त, रिक्त, (शून्य**)&dst);
    जर (ret < 0)
        परत ret;

    जर (dst) {
    ptr = len ? av_malloc(len) : रिक्त;
    जर (len && !ptr)
        परत AVERROR(ENOMEM);

    lendst = (पूर्णांक *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    जर (len)
        स_नकल(ptr, val, len);
    }

    परत 0;
}

पूर्णांक av_opt_set_image_size(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक w, पूर्णांक h, पूर्णांक शोध_flags)
{
    स्थिरांक AVOption *o;
    शून्य *logctx;
    पूर्णांक *dst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, शोध_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       रिक्त, &o, (शून्य**)&dst);
    जर (ret < 0)
        परत ret;

    logctx = dst ? obj : रिक्त;

    जर (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        परत AVERROR(EINVAL);
    }

    जर (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    परत 0;
}

पूर्णांक av_opt_set_video_rate(शून्य *obj, स्थिरांक अक्षर *name, AVRational val, पूर्णांक शोध_flags)
{
    परत set_संख्या(obj, name, val.अंक, val.den, 1, शोध_flags, AV_OPT_TYPE_VIDEO_RATE);
}

स्थिर पूर्णांक set_format(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक fmt, पूर्णांक शोध_flags,
                      गणना AVOptionType type, स्थिरांक अक्षर *desc, पूर्णांक nb_fmts)
{
    स्थिरांक AVOption *o;
    शून्य *logctx;
    पूर्णांक *dst;
    पूर्णांक min, max, ret;

    ret = opt_set_init(obj, name, शोध_flags, type, रिक्त, &o, (शून्य**)&dst);
    जर (ret < 0)
        परत ret;

    logctx = dst ? obj : रिक्त;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    जर (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        परत AVERROR(दुस्फल);
    }
    जर (dst)
    *dst = fmt;
    परत 0;
}

पूर्णांक av_opt_set_pixel_fmt(शून्य *obj, स्थिरांक अक्षर *name, गणना AVPixelFormat fmt, पूर्णांक शोध_flags)
{
    परत set_format(obj, name, fmt, शोध_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

पूर्णांक av_opt_set_sample_fmt(शून्य *obj, स्थिरांक अक्षर *name, गणना AVSampleFormat fmt, पूर्णांक शोध_flags)
{
    परत set_format(obj, name, fmt, शोध_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

पूर्णांक av_opt_set_dict_val(शून्य *obj, स्थिरांक अक्षर *name, स्थिरांक AVDictionary *val,
                        पूर्णांक शोध_flags)
{
    AVDictionary **dst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, शोध_flags, AV_OPT_TYPE_DICT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    जर (ret < 0)
        परत ret;

    जर (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    परत ret;
}

पूर्णांक av_opt_set_chlayout(शून्य *obj, स्थिरांक अक्षर *name,
                        स्थिरांक AVChannelLayout *channel_layout,
                        पूर्णांक शोध_flags)
{
    AVChannelLayout *dst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, शोध_flags, AV_OPT_TYPE_CHLAYOUT, रिक्त, रिक्त,
                       (शून्य**)&dst);
    जर (ret < 0)
        परत ret;

    जर (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    परत ret;
}

स्थिर शून्य format_duration(अक्षर *buf, माप_प्रकार size, int64_t d)
{
    अक्षर *e;

    av_assert0(size >= 25);
    जर (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    जर (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    अन्यथा जर (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    अन्यथा जर (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (पूर्णांक)((d / 60000000) % 60),
                 (पूर्णांक)((d / 1000000) % 60),
                 (पूर्णांक)(d % 1000000));
    अन्यथा जर (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (पूर्णांक)(d / 60000000),
                 (पूर्णांक)((d / 1000000) % 60),
                 (पूर्णांक)(d % 1000000));
    अन्यथा
        snprintf(buf, size, "%d.%06d",
                 (पूर्णांक)(d / 1000000),
                 (पूर्णांक)(d % 1000000));
    e = buf + म_माप(buf);
    पर्यंत (e > buf && e[-1] == '0')
        *(--e) = 0;
    जर (e > buf && e[-1] == '.')
        *(--e) = 0;
}

स्थिर पूर्णांक opt_get_elem(स्थिरांक AVOption *o, uint8_t **pbuf, माप_प्रकार buf_len,
                        स्थिरांक शून्य *dst, पूर्णांक शोध_flags)
{
    पूर्णांक ret;

    निवड (TYPE_BASE(o->type)) {
    स्थिती AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(पूर्णांक *)dst));
        थांबा;
    स्थिती AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(पूर्णांक *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(पूर्णांक *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(अचिन्हित *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(दशांश *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(द्विगुण *)dst);
        थांबा;
    स्थिती AV_OPT_TYPE_VIDEO_RATE:
    स्थिती AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->अंक, ((AVRational *)dst)->den);
        थांबा;
    स्थिती AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        थांबा;
    स्थिती AV_OPT_TYPE_STRING:
        जर (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } अन्यथा जर (शोध_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = रिक्त;
            परत 0;
        } अन्यथा {
            *pbuf = av_strdup("");
        }
        परत *pbuf ? 0 : AVERROR(ENOMEM);
    स्थिती AV_OPT_TYPE_द्विमान: {
        स्थिरांक uint8_t *bin;
        पूर्णांक len;

        जर (!*(uint8_t **)dst && (शोध_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            परत 0;
        }
        len = *(पूर्णांक *)(((uint8_t *)dst) + आकार(uint8_t *));
        जर ((uint64_t)len * 2 + 1 > पूर्णांक_उच्च)
            परत AVERROR(EINVAL);
        जर (!(*pbuf = av_malloc(len * 2 + 1)))
            परत AVERROR(ENOMEM);
        जर (!len) {
            *pbuf[0] = '\0';
            परत 0;
        }
        bin = *(uint8_t **)dst;
        साठी (पूर्णांक i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        परत 0;
    }
    स्थिती AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((पूर्णांक *)dst)[0], ((पूर्णांक *)dst)[1]);
        थांबा;
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (अक्षर *)av_x_if_null(av_get_pix_fmt_name(*(गणना AVPixelFormat *)dst), "none"));
        थांबा;
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (अक्षर *)av_x_if_null(av_get_sample_fmt_name(*(गणना AVSampleFormat *)dst), "none"));
        थांबा;
    स्थिती AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = म_माप(*pbuf); // no overflow possible, checked by an assert
        थांबा;
    }
    स्थिती AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (पूर्णांक)((uint8_t *)dst)[0], (पूर्णांक)((uint8_t *)dst)[1],
                       (पूर्णांक)((uint8_t *)dst)[2], (पूर्णांक)((uint8_t *)dst)[3]);
        थांबा;
    स्थिती AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        थांबा;
    स्थिती AV_OPT_TYPE_DICT:
        जर (!*(AVDictionary **)dst && (शोध_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = रिक्त;
            परत 0;
        }
        परत av_dict_get_string(*(AVDictionary **)dst, (अक्षर **)pbuf, '=', ':');
    पूर्वनिर्धारित:
        परत AVERROR(EINVAL);
    }

    परत ret;
}

स्थिर पूर्णांक opt_get_array(स्थिरांक AVOption *o, शून्य *dst, uint8_t **out_val)
{
    स्थिरांक अचिन्हित मोजणी = *opt_array_pcount(dst);
    स्थिरांक uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = रिक्त;
    माप_प्रकार   str_len = 0;
    पूर्णांक ret;

    *out_val = रिक्त;

    साठी (अचिन्हित i = 0; i < मोजणी; i++) {
        uint8_t buf[128], *out = buf;
        माप_प्रकार out_len;

        ret = opt_get_elem(o, &out, आकार(buf),
                           opt_array_pelem(o, *(शून्य **)dst, i), 0);
        जर (ret < 0)
            जा fail;

        out_len = म_माप(out);
        जर (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(दुस्फल);
            जा fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        जर (ret < 0)
            जा fail;

        // add separator if needed
        जर (i)
            str[str_len++] = sep;

        // escape the element
        साठी (अचिन्हित j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            जर (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        जर (out != buf)
            av_freep(&out);
        जर (ret < 0) {
            av_freep(&str);
            परत ret;
        }
    }

    *out_val = str;

    परत 0;
}

पूर्णांक av_opt_get(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, uint8_t **out_val)
{
    शून्य *dst, *target_obj;
    स्थिरांक AVOption *o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    uint8_t *out, buf[128];
    पूर्णांक ret;

    जर (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        परत AVERROR_OPTION_NOT_FOUND;

    जर (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    जर (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        जर (ret < 0)
            परत ret;
        जर (!*out_val && !(शोध_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            जर (!*out_val)
               परत AVERROR(ENOMEM);
        }
        परत 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, आकार(buf), dst, शोध_flags);
    जर (ret < 0)
        परत ret;
    जर (out != buf) {
        *out_val = out;
        परत 0;
    }

    जर (ret >= आकार(buf))
        परत AVERROR(EINVAL);
    *out_val = av_strdup(out);
    परत *out_val ? 0 : AVERROR(ENOMEM);
}

स्थिर पूर्णांक get_संख्या(शून्य *obj, स्थिरांक अक्षर *name, द्विगुण *अंक, पूर्णांक *den, int64_t *intnum,
                      पूर्णांक शोध_flags)
{
    शून्य *dst, *target_obj;
    स्थिरांक AVOption *o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        परत AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    परत read_संख्या(o, dst, अंक, den, intnum);
}

पूर्णांक av_opt_get_int(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    द्विगुण अंक = 1;
    पूर्णांक ret, den = 1;

    जर ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, शोध_flags)) < 0)
        परत ret;
    जर (अंक == den)
        *out_val = intnum;
    अन्यथा
        *out_val = अंक * intnum / den;
    परत 0;
}

पूर्णांक av_opt_get_double(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, द्विगुण *out_val)
{
    int64_t intnum = 1;
    द्विगुण अंक = 1;
    पूर्णांक ret, den = 1;

    जर ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, शोध_flags)) < 0)
        परत ret;
    *out_val = अंक * intnum / den;
    परत 0;
}

पूर्णांक av_opt_get_q(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    द्विगुण अंक = 1;
    पूर्णांक ret, den = 1;

    जर ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, शोध_flags)) < 0)
        परत ret;

    जर (अंक == 1.0 && (पूर्णांक)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    अन्यथा
        *out_val = double_to_rational(अंक*intnum/den);
    परत 0;
}

पूर्णांक av_opt_get_image_size(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, पूर्णांक *w_out, पूर्णांक *h_out)
{
    शून्य *dst, *target_obj;
    स्थिरांक AVOption *o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        परत AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    जर (w_out) *w_out = *(पूर्णांक *)dst;
    जर (h_out) *h_out = *((पूर्णांक *)dst+1);
    परत 0;
}

पूर्णांक av_opt_get_video_rate(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, AVRational *out_val)
{
    परत av_opt_get_q(obj, name, शोध_flags, out_val);
}

स्थिर पूर्णांक get_format(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, शून्य *out_fmt,
                      गणना AVOptionType type, स्थिरांक अक्षर *desc)
{
    शून्य *dst, *target_obj;
    स्थिरांक AVOption *o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        परत AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    जर (type == AV_OPT_TYPE_PIXEL_FMT)
        *(गणना AVPixelFormat *)out_fmt = *(गणना AVPixelFormat *)dst;
    अन्यथा
        *(गणना AVSampleFormat*)out_fmt = *(गणना AVSampleFormat*)dst;

    परत 0;
}

पूर्णांक av_opt_get_pixel_fmt(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, गणना AVPixelFormat *out_fmt)
{
    परत get_format(obj, name, शोध_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

पूर्णांक av_opt_get_sample_fmt(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, गणना AVSampleFormat *out_fmt)
{
    परत get_format(obj, name, शोध_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

पूर्णांक av_opt_get_chlayout(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, AVChannelLayout *cl)
{
    शून्य *dst, *target_obj;
    स्थिरांक AVOption *o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        परत AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    परत av_channel_layout_copy(cl, dst);
}

पूर्णांक av_opt_get_dict_val(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags, AVDictionary **out_val)
{
    शून्य *target_obj;
    AVDictionary *src;
    स्थिरांक AVOption *o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);

    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (o->type != AV_OPT_TYPE_DICT)
        परत AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    परत av_dict_copy(out_val, src, 0);
}

पूर्णांक av_opt_flag_is_set(शून्य *obj, स्थिरांक अक्षर *field_name, स्थिरांक अक्षर *flag_name)
{
    स्थिरांक AVOption *field = av_opt_find(obj, field_name, रिक्त, 0, 0);
    स्थिरांक AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : रिक्त, 0, 0);
    int64_t res;

    जर (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        परत 0;
    परत res & flag->default_val.i64;
}

स्थिर शून्य log_int_मूल्य(शून्य *av_log_obj, पूर्णांक level, int64_t i)
{
    जर (i == पूर्णांक_उच्च) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा जर (i == पूर्णांक_न्यून) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा जर (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा जर (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा जर (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

स्थिर शून्य log_मूल्य(शून्य *av_log_obj, पूर्णांक level, द्विगुण d)
{
    जर      (d == पूर्णांक_उच्च) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा जर (d == पूर्णांक_न्यून) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा जर (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा जर (d == (द्विगुण)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा जर (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा जर (d == भग्न_उच्च) {
        av_log(av_log_obj, level, "FLT_MAX");
    } अन्यथा जर (d == भग्न_न्यून) {
        av_log(av_log_obj, level, "FLT_MIN");
    } अन्यथा जर (d == -भग्न_उच्च) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } अन्यथा जर (d == -भग्न_न्यून) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } अन्यथा जर (d == द्विग_उच्च) {
        av_log(av_log_obj, level, "DBL_MAX");
    } अन्यथा जर (d == द्विग_न्यून) {
        av_log(av_log_obj, level, "DBL_MIN");
    } अन्यथा जर (d == -द्विग_उच्च) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } अन्यथा जर (d == -द्विग_न्यून) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%g", d);
    }
}

स्थिर स्थिरांक अक्षर *get_opt_const_name(शून्य *obj, स्थिरांक अक्षर *unit, int64_t मूल्य)
{
    स्थिरांक AVOption *opt = रिक्त;

    जर (!unit)
        परत रिक्त;
    पर्यंत ((opt = av_opt_next(obj, opt)))
        जर (opt->type == AV_OPT_TYPE_CONST && !म_भेद(opt->unit, unit) &&
            opt->default_val.i64 == मूल्य)
            परत opt->name;
    परत रिक्त;
}

स्थिर अक्षर *get_opt_flags_string(शून्य *obj, स्थिरांक अक्षर *unit, int64_t मूल्य)
{
    स्थिरांक AVOption *opt = रिक्त;
    अक्षर flags[512];

    flags[0] = 0;
    जर (!unit)
        परत रिक्त;
    पर्यंत ((opt = av_opt_next(obj, opt))) {
        जर (opt->type == AV_OPT_TYPE_CONST && !म_भेद(opt->unit, unit) &&
            opt->default_val.i64 & मूल्य) {
            जर (flags[0])
                av_strlcatf(flags, आकार(flags), "+");
            av_strlcatf(flags, आकार(flags), "%s", opt->name);
        }
    }
    जर (flags[0])
        परत av_strdup(flags);
    परत रिक्त;
}

स्थिर शून्य log_type(शून्य *av_log_obj, स्थिरांक AVOption *o,
                     गणना AVOptionType parent_type)
{
    स्थिरांक गणना AVOptionType type = TYPE_BASE(o->type);

    जर (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    अन्यथा जर (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        जर (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        अन्यथा
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    अन्यथा
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

स्थिर शून्य log_default(शून्य *obj, शून्य *av_log_obj, स्थिरांक AVOption *opt)
{
    जर (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_द्विमान)
        परत;
    जर ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        परत;

    जर (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        स्थिरांक AVOptionArrayDef *arr = opt->default_val.arr;
        जर (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        परत;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    निवड (opt->type) {
    स्थिती AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        थांबा;
    स्थिती AV_OPT_TYPE_FLAGS: {
        अक्षर *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        जर (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } अन्यथा {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        थांबा;
    }
    स्थिती AV_OPT_TYPE_DURATION: {
        अक्षर buf[25];
        format_duration(buf, आकार(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        थांबा;
    }
    स्थिती AV_OPT_TYPE_UINT:
    स्थिती AV_OPT_TYPE_INT:
    स्थिती AV_OPT_TYPE_UINT64:
    स्थिती AV_OPT_TYPE_INT64: {
        स्थिरांक अक्षर *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        जर (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        अन्यथा
            log_int_मूल्य(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        थांबा;
    }
    स्थिती AV_OPT_TYPE_DOUBLE:
    स्थिती AV_OPT_TYPE_FLOAT:
        log_मूल्य(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        थांबा;
    स्थिती AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, पूर्णांक_उच्च);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.अंक, q.den); }
        थांबा;
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (अक्षर *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        थांबा;
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (अक्षर *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        थांबा;
    स्थिती AV_OPT_TYPE_COLOR:
    स्थिती AV_OPT_TYPE_IMAGE_SIZE:
    स्थिती AV_OPT_TYPE_STRING:
    स्थिती AV_OPT_TYPE_DICT:
    स्थिती AV_OPT_TYPE_VIDEO_RATE:
    स्थिती AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        थांबा;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

स्थिर शून्य opt_list(शून्य *obj, शून्य *av_log_obj, स्थिरांक अक्षर *unit,
                     पूर्णांक req_flags, पूर्णांक rej_flags, गणना AVOptionType parent_type)
{
    स्थिरांक AVOption *opt = रिक्त;
    AVOptionRanges *r;
    पूर्णांक i;

    पर्यंत ((opt = av_opt_next(obj, opt))) {
        जर (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            सुरूठेवा;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        जर (!unit && opt->type == AV_OPT_TYPE_CONST)
            सुरूठेवा;
        अन्यथा जर (unit && opt->type != AV_OPT_TYPE_CONST)
            सुरूठेवा;
        अन्यथा जर (unit && opt->type == AV_OPT_TYPE_CONST && म_भेद(unit, opt->unit))
            सुरूठेवा;
        अन्यथा जर (unit && opt->type == AV_OPT_TYPE_CONST)
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

        जर (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        जर (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_शोध_FAKE_OBJ) >= 0) {
            निवड (opt->type) {
            स्थिती AV_OPT_TYPE_INT:
            स्थिती AV_OPT_TYPE_UINT:
            स्थिती AV_OPT_TYPE_INT64:
            स्थिती AV_OPT_TYPE_UINT64:
            स्थिती AV_OPT_TYPE_DOUBLE:
            स्थिती AV_OPT_TYPE_FLOAT:
            स्थिती AV_OPT_TYPE_RATIONAL:
                साठी (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_मूल्य(av_log_obj, AV_LOG_INFO, r->range[i]->मूल्य_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_मूल्य(av_log_obj, AV_LOG_INFO, r->range[i]->मूल्य_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                थांबा;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        जर (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

पूर्णांक av_opt_show2(शून्य *obj, शून्य *av_log_obj, पूर्णांक req_flags, पूर्णांक rej_flags)
{
    जर (!obj)
        परत -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, रिक्त, req_flags, rej_flags, -1);

    परत 0;
}

शून्य av_opt_set_defaults(शून्य *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

शून्य av_opt_set_defaults2(शून्य *s, पूर्णांक mask, पूर्णांक flags)
{
    स्थिरांक AVOption *opt = रिक्त;
    पर्यंत ((opt = av_opt_next(s, opt))) {
        शून्य *dst = ((uint8_t*)s) + opt->offset;

        जर ((opt->flags & mask) != flags)
            सुरूठेवा;

        जर (opt->flags & AV_OPT_FLAG_READONLY)
            सुरूठेवा;

        जर (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            स्थिरांक AVOptionArrayDef *arr = opt->default_val.arr;
            स्थिरांक अक्षर              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            जर (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            सुरूठेवा;
        }

        निवड (opt->type) {
            स्थिती AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                थांबा;
            स्थिती AV_OPT_TYPE_BOOL:
            स्थिती AV_OPT_TYPE_FLAGS:
            स्थिती AV_OPT_TYPE_INT:
            स्थिती AV_OPT_TYPE_UINT:
            स्थिती AV_OPT_TYPE_INT64:
            स्थिती AV_OPT_TYPE_UINT64:
            स्थिती AV_OPT_TYPE_DURATION:
            स्थिती AV_OPT_TYPE_PIXEL_FMT:
            स्थिती AV_OPT_TYPE_SAMPLE_FMT:
                write_संख्या(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                थांबा;
            स्थिती AV_OPT_TYPE_DOUBLE:
            स्थिती AV_OPT_TYPE_FLOAT: {
                द्विगुण val;
                val = opt->default_val.dbl;
                write_संख्या(s, opt, dst, val, 1, 1, 1);
            }
            थांबा;
            स्थिती AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, पूर्णांक_उच्च);
                write_संख्या(s, opt, dst, 1, val.den, val.अंक, 1);
            }
            थांबा;
            स्थिती AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                थांबा;
            स्थिती AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                थांबा;
            स्थिती AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                थांबा;
            स्थिती AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                थांबा;
            स्थिती AV_OPT_TYPE_द्विमान:
                set_string_द्विमान(s, opt, opt->default_val.str, dst);
                थांबा;
            स्थिती AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                थांबा;
            स्थिती AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                थांबा;
        पूर्वनिर्धारित:
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
स्थिर पूर्णांक parse_किल्ली_मूल्य_pair(शून्य *ctx, स्थिरांक अक्षर **buf,
                                स्थिरांक अक्षर *किल्ली_val_sep, स्थिरांक अक्षर *pairs_sep)
{
    अक्षर *किल्ली = av_get_token(buf, किल्ली_val_sep);
    अक्षर *val;
    पूर्णांक ret;

    जर (!किल्ली)
        परत AVERROR(ENOMEM);

    जर (*किल्ली && म_अखोज(*buf, किल्ली_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        जर (!val) {
            av_freep(&किल्ली);
            परत AVERROR(ENOMEM);
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", किल्ली);
        av_free(किल्ली);
        परत AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", किल्ली, val);

    ret = av_opt_set(ctx, किल्ली, val, AV_OPT_शोध_CHILDREN);
    जर (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", किल्ली);

    av_free(किल्ली);
    av_free(val);
    परत ret;
}

पूर्णांक av_set_options_string(शून्य *ctx, स्थिरांक अक्षर *opts,
                          स्थिरांक अक्षर *किल्ली_val_sep, स्थिरांक अक्षर *pairs_sep)
{
    पूर्णांक ret, मोजणी = 0;

    जर (!opts)
        परत 0;

    पर्यंत (*opts) {
        जर ((ret = parse_किल्ली_मूल्य_pair(ctx, &opts, किल्ली_val_sep, pairs_sep)) < 0)
            परत ret;
        मोजणी++;

        जर (*opts)
            opts++;
    }

    परत मोजणी;
}

#define WHITESPACES " \n\t\r"

स्थिर पूर्णांक is_किल्ली_char(अक्षर c)
{
    परत (अचिन्हित)((c | 32) - 'a') < 26 ||
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
स्थिर पूर्णांक get_किल्ली(स्थिरांक अक्षर **ropts, स्थिरांक अक्षर *delim, अक्षर **rkey)
{
    स्थिरांक अक्षर *opts = *ropts;
    स्थिरांक अक्षर *किल्ली_start, *किल्ली_end;

    किल्ली_start = opts += म_अखोज(opts, WHITESPACES);
    पर्यंत (is_किल्ली_char(*opts))
        opts++;
    किल्ली_end = opts;
    opts += म_अखोज(opts, WHITESPACES);
    जर (!*opts || !म_अक्षर(delim, *opts))
        परत AVERROR(EINVAL);
    opts++;
    जर (!(*rkey = av_malloc(किल्ली_end - किल्ली_start + 1)))
        परत AVERROR(ENOMEM);
    स_नकल(*rkey, किल्ली_start, किल्ली_end - किल्ली_start);
    (*rkey)[किल्ली_end - किल्ली_start] = 0;
    *ropts = opts;
    परत 0;
}

पूर्णांक av_opt_get_किल्ली_मूल्य(स्थिरांक अक्षर **ropts,
                         स्थिरांक अक्षर *किल्ली_val_sep, स्थिरांक अक्षर *pairs_sep,
                         अचिन्हित flags,
                         अक्षर **rkey, अक्षर **rval)
{
    पूर्णांक ret;
    अक्षर *किल्ली = रिक्त, *val;
    स्थिरांक अक्षर *opts = *ropts;

    जर ((ret = get_किल्ली(&opts, किल्ली_val_sep, &किल्ली)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_किल्ली))
        परत AVERROR(EINVAL);
    जर (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(किल्ली);
        परत AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = किल्ली;
    *rval  = val;
    परत 0;
}

पूर्णांक av_opt_set_from_string(शून्य *ctx, स्थिरांक अक्षर *opts,
                           स्थिरांक अक्षर *स्थिरांक *shorthand,
                           स्थिरांक अक्षर *किल्ली_val_sep, स्थिरांक अक्षर *pairs_sep)
{
    पूर्णांक ret, मोजणी = 0;
    स्थिरांक अक्षर *dummy_shorthand = रिक्त;
    स्थिरांक अक्षर *किल्ली;

    जर (!opts)
        परत 0;
    जर (!shorthand)
        shorthand = &dummy_shorthand;

    पर्यंत (*opts) {
        अक्षर *parsed_किल्ली, *मूल्य;
        ret = av_opt_get_किल्ली_मूल्य(&opts, किल्ली_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_किल्ली : 0,
                                   &parsed_किल्ली, &मूल्य);
        जर (ret < 0) {
            जर (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            अन्यथा
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            परत ret;
        }
        जर (*opts)
            opts++;
        जर (parsed_किल्ली) {
            किल्ली = parsed_किल्ली;
            पर्यंत (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } अन्यथा {
            किल्ली = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", किल्ली, मूल्य);
        जर ((ret = av_opt_set(ctx, किल्ली, मूल्य, 0)) < 0) {
            जर (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", किल्ली);
            av_free(मूल्य);
            av_free(parsed_किल्ली);
            परत ret;
        }

        av_free(मूल्य);
        av_free(parsed_किल्ली);
        मोजणी++;
    }
    परत मोजणी;
}

शून्य av_opt_free(शून्य *obj)
{
    स्थिरांक AVOption *o = रिक्त;
    पर्यंत ((o = av_opt_next(obj, o))) {
        शून्य *pitem = (uint8_t *)obj + o->offset;

        जर (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        अन्यथा
            opt_free_elem(o->type, pitem);
    }
}

पूर्णांक av_opt_set_dict2(शून्य *obj, AVDictionary **options, पूर्णांक शोध_flags)
{
    स्थिरांक AVDictionaryEntry *t = रिक्त;
    AVDictionary    *tmp = रिक्त;
    पूर्णांक ret;

    जर (!options)
        परत 0;

    पर्यंत ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->किल्ली, t->मूल्य, शोध_flags);
        जर (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->किल्ली, t->मूल्य, AV_DICT_MULTIKEY);
        जर (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->किल्ली, t->मूल्य);
            av_dict_free(&tmp);
            परत ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    परत 0;
}

पूर्णांक av_opt_set_dict(शून्य *obj, AVDictionary **options)
{
    परत av_opt_set_dict2(obj, options, 0);
}

स्थिरांक AVOption *av_opt_find(शून्य *obj, स्थिरांक अक्षर *name, स्थिरांक अक्षर *unit,
                            पूर्णांक opt_flags, पूर्णांक शोध_flags)
{
    परत av_opt_find2(obj, name, unit, opt_flags, शोध_flags, रिक्त);
}

स्थिरांक AVOption *av_opt_find2(शून्य *obj, स्थिरांक अक्षर *name, स्थिरांक अक्षर *unit,
                             पूर्णांक opt_flags, पूर्णांक शोध_flags, शून्य **target_obj)
{
    स्थिरांक AVClass  *c;
    स्थिरांक AVOption *o = रिक्त;

    जर(!obj)
        परत रिक्त;

    c= *(AVClass**)obj;

    जर (!c)
        परत रिक्त;

    जर (शोध_flags & AV_OPT_शोध_CHILDREN) {
        जर (शोध_flags & AV_OPT_शोध_FAKE_OBJ) {
            शून्य *iter = रिक्त;
            स्थिरांक AVClass *child;
            पर्यंत (child = av_opt_child_class_iterate(c, &iter))
                जर (o = av_opt_find2(&child, name, unit, opt_flags, शोध_flags, रिक्त))
                    परत o;
        } अन्यथा {
            शून्य *child = रिक्त;
            पर्यंत (child = av_opt_child_next(obj, child))
                जर (o = av_opt_find2(child, name, unit, opt_flags, शोध_flags, target_obj))
                    परत o;
        }
    }

    पर्यंत (o = av_opt_next(obj, o)) {
        जर (!म_भेद(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !म_भेद(o->unit, unit)))) {
            जर (target_obj) {
                जर (!(शोध_flags & AV_OPT_शोध_FAKE_OBJ))
                    *target_obj = obj;
                अन्यथा
                    *target_obj = रिक्त;
            }
            परत o;
        }
    }
    परत रिक्त;
}

शून्य *av_opt_child_next(शून्य *obj, शून्य *prev)
{
    स्थिरांक AVClass *c = *(AVClass **)obj;
    जर (c->child_next)
        परत c->child_next(obj, prev);
    परत रिक्त;
}

स्थिरांक AVClass *av_opt_child_class_iterate(स्थिरांक AVClass *parent, शून्य **iter)
{
    जर (parent->child_class_iterate)
        परत parent->child_class_iterate(iter);
    परत रिक्त;
}

स्थिर पूर्णांक opt_copy_elem(शून्य *logctx, गणना AVOptionType type,
                         शून्य *dst, स्थिरांक शून्य *src)
{
    जर (type == AV_OPT_TYPE_STRING) {
        स्थिरांक अक्षर *src_str = *(स्थिरांक अक्षर *स्थिरांक *)src;
        अक्षर         **dstp =  (अक्षर **)dst;
        जर (*dstp != src_str)
            av_freep(dstp);
        जर (src_str) {
            *dstp = av_strdup(src_str);
            जर (!*dstp)
                परत AVERROR(ENOMEM);
        }
    } अन्यथा जर (type == AV_OPT_TYPE_द्विमान) {
        स्थिरांक uint8_t *स्थिरांक *src8 = (स्थिरांक uint8_t *स्थिरांक *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        पूर्णांक len = *(स्थिरांक पूर्णांक *)(src8 + 1);
        जर (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        जर (len && !*dst8) {
            *(पूर्णांक *)(dst8 + 1) = 0;
            परत AVERROR(ENOMEM);
        }
        *(पूर्णांक *)(dst8 + 1) = len;
    } अन्यथा जर (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } अन्यथा जर (type == AV_OPT_TYPE_DICT) {
        स्थिरांक AVDictionary *sdict = *(स्थिरांक AVDictionary * स्थिरांक *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        जर (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = रिक्त;
        परत av_dict_copy(ddictp, sdict, 0);
    } अन्यथा जर (type == AV_OPT_TYPE_CHLAYOUT) {
        स्थिरांक AVChannelLayout *slayout = (स्थिरांक AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        जर (dlayout != slayout) {
            जर (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = रिक्त;
            परत av_channel_layout_copy(dst, src);
        }
    } अन्यथा जर (opt_is_pod(type)) {
        माप_प्रकार size = opt_type_desc[type].size;
        स_नकल(dst, src, size);
    } अन्यथा {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        परत AVERROR(EINVAL);
    }

    परत 0;
}

स्थिर पूर्णांक opt_copy_array(शून्य *logctx, स्थिरांक AVOption *o,
                          शून्य **pdst, स्थिरांक शून्य * स्थिरांक *psrc)
{
    अचिन्हित nb_elems = *opt_array_pcount(psrc);
    शून्य         *dst = रिक्त;
    पूर्णांक ret;

    जर (*pdst == *psrc) {
        *pdst                   = रिक्त;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    जर (!dst)
        परत AVERROR(ENOMEM);

    साठी (अचिन्हित i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(शून्य**)psrc, i));
        जर (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            परत ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    परत 0;
}

पूर्णांक av_opt_copy(शून्य *dst, स्थिरांक शून्य *src)
{
    स्थिरांक AVOption *o = रिक्त;
    स्थिरांक AVClass *c;
    पूर्णांक ret = 0;

    जर (!src)
        परत AVERROR(EINVAL);

    c = *(AVClass **)src;
    जर (!c || c != *(AVClass **)dst)
        परत AVERROR(EINVAL);

    पर्यंत ((o = av_opt_next(src, o))) {
        शून्य *field_dst = (uint8_t *)dst + o->offset;
        शून्य *field_src = (uint8_t *)src + o->offset;

        पूर्णांक err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        जर (err < 0)
            ret = err;
    }
    परत ret;
}

पूर्णांक av_opt_get_array_size(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags,
                          अचिन्हित पूर्णांक *out_val)
{
    शून्य *target_obj, *parray;
    स्थिरांक AVOption *o;

    o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        परत AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    परत 0;
}

पूर्णांक av_opt_get_array(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags,
                     अचिन्हित पूर्णांक start_elem, अचिन्हित पूर्णांक nb_elems,
                     गणना AVOptionType out_type, शून्य *out_val)
{
    स्थिरांक माप_प्रकार elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    स्थिरांक AVOption *o;
    शून्य *target_obj;

    स्थिरांक शून्य *parray;
    अचिन्हित array_size;

    पूर्णांक ret;

    o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target_obj);
    जर (!o || !target_obj)
        परत AVERROR_OPTION_NOT_FOUND;
    जर (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        परत AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    जर (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        परत AVERROR(EINVAL);

    साठी (अचिन्हित i = 0; i < nb_elems; i++) {
        स्थिरांक शून्य *src = opt_array_pelem(o, *(शून्य**)parray, start_elem + i);
        शून्य       *dst = (uint8_t*)out_val + i * elem_size_out;

        जर (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            जर (ret < 0)
                जा fail;
        } अन्यथा जर (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, आकार(buf), src, शोध_flags);
            जर (ret < 0)
                जा fail;

            जर (out == buf) {
                out = av_strdup(buf);
                जर (!out) {
                    ret = AVERROR(ENOMEM);
                    जा fail;
                }
            }

            *(uint8_t**)dst = out;
        } अन्यथा जर (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            द्विगुण     अंक = 1.0;
            पूर्णांक        den = 1;
            int64_t intnum = 1;

            ret = read_संख्या(o, src, &अंक, &den, &intnum);
            जर (ret < 0)
                जा fail;

            निवड (out_type) {
            स्थिती AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (अंक == den) ?  intnum : अंक * intnum / den;
                थांबा;
            स्थिती AV_OPT_TYPE_DOUBLE:
                *(द्विगुण*)dst = अंक * intnum / den;
                थांबा;
            स्थिती AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (अंक == 1.0 && (पूर्णांक)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(अंक * intnum / den);
                थांबा;
            पूर्वनिर्धारित: av_assert0(0);
            }
        } अन्यथा
            परत AVERROR(ENOSYS);
    }

    परत 0;
fail:
    साठी (अचिन्हित i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    परत ret;
}

पूर्णांक av_opt_set_array(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags,
                     अचिन्हित पूर्णांक start_elem, अचिन्हित पूर्णांक nb_elems,
                     गणना AVOptionType val_type, स्थिरांक शून्य *val)
{
    स्थिरांक माप_प्रकार elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    स्थिरांक AVOption *o;
    स्थिरांक AVOptionArrayDef *arr;
    शून्य *target_obj;

    शून्य *parray;
    शून्य *new_elems;
    अचिन्हित *array_size, new_size;
    माप_प्रकार elem_size;

    पूर्णांक ret = 0;

    ret = opt_set_init(obj, name, शोध_flags, 0, &target_obj, &o, &parray);
    जर (ret < 0)
        परत ret;

    जर (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        परत AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    जर (start_elem > *array_size)
        परत AVERROR(EINVAL);

    // compute new array size
    जर (!val) {
        जर (*array_size - start_elem < nb_elems)
            परत AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } अन्यथा जर (शोध_flags & AV_OPT_ARRAY_REPLACE) {
        जर (start_elem >= अच_पूर्णांक_उच्च - nb_elems)
            परत AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } अन्यथा {
        जर (nb_elems >= अच_पूर्णांक_उच्च - *array_size)
            परत AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    जर (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        परत AVERROR(EINVAL);

    // desired operation is shrinking the array
    जर (!val) {
        शून्य *array = *(शून्य**)parray;

        साठी (अचिन्हित i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        जर (new_size > 0) {
            स_हटाओ(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            जर (!array)
                परत AVERROR(ENOMEM);

            *(शून्य**)parray = array;
        } अन्यथा
            av_freep(parray);

        *array_size = new_size;

        परत 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    जर (!new_elems)
        परत AVERROR(ENOMEM);

    // convert/validate each new element
    साठी (अचिन्हित i = 0; i < nb_elems; i++) {
        शून्य       *dst = opt_array_pelem(o, new_elems, i);
        स्थिरांक शून्य *src = (uint8_t*)val + i * elem_size_val;

        द्विगुण     अंक = 1.0;
        पूर्णांक        den = 1;
        int64_t intnum = 1;

        जर (val_type == TYPE_BASE(o->type)) {
            पूर्णांक err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            जर (ret < 0)
                जा fail;

            // validate the range for numeric options
            err = read_संख्या(o, dst, &अंक, &den, &intnum);
            जर (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < अंक * intnum || o->min * den > अंक * intnum)) {
                अंक = den ? अंक * intnum / den : (अंक && intnum ? अनन्त : न_अंक);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, अंक, o->min, o->max);
                ret = AVERROR(दुस्फल);
                जा fail;
            }
        } अन्यथा जर (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(स्थिरांक अक्षर **)src, dst);
            जर (ret < 0)
                जा fail;
        } अन्यथा जर (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            निवड (val_type) {
            स्थिती AV_OPT_TYPE_INT:       intnum = *(पूर्णांक*)src;                थांबा;
            स्थिती AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            थांबा;
            स्थिती AV_OPT_TYPE_FLOAT:     अंक    = *(दशांश*)src;              थांबा;
            स्थिती AV_OPT_TYPE_DOUBLE:    अंक    = *(द्विगुण*)src;             थांबा;
            स्थिती AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->अंक;
                                        den    = ((AVRational*)src)->den;   थांबा;
            पूर्वनिर्धारित: av_assert0(0);
            }

            ret = write_संख्या(obj, o, dst, अंक, den, intnum, 0);
            जर (ret < 0)
                जा fail;
        } अन्यथा {
            ret = AVERROR(ENOSYS);
            जा fail;
        }
    }

    // commit new elements to the array
    जर (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(शून्य**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = रिक्त;
        nb_elems  = 0;
    } अन्यथा {
        शून्य *array = av_realloc_array(*(शून्य**)parray, new_size, elem_size);
        जर (!array) {
            ret = AVERROR(ENOMEM);
            जा fail;
        }

        जर (शोध_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            साठी (अचिन्हित i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
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

    परत ret;
}

पूर्णांक av_opt_query_ranges(AVOptionRanges **ranges_arg, शून्य *obj, स्थिरांक अक्षर *किल्ली, पूर्णांक flags)
{
    पूर्णांक ret;
    स्थिरांक AVClass *c = *(AVClass**)obj;
    पूर्णांक (*callback)(AVOptionRanges **, शून्य *obj, स्थिरांक अक्षर *किल्ली, पूर्णांक flags) = c->query_ranges;

    जर (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, किल्ली, flags);
    जर (ret >= 0) {
        जर (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    परत ret;
}

पूर्णांक av_opt_query_ranges_default(AVOptionRanges **ranges_arg, शून्य *obj, स्थिरांक अक्षर *किल्ली, पूर्णांक flags)
{
    AVOptionRanges *ranges = av_mallocz(आकार(*ranges));
    AVOptionRange **range_array = av_mallocz(आकार(शून्य*));
    AVOptionRange *range = av_mallocz(आकार(*range));
    स्थिरांक AVOption *field = av_opt_find(obj, किल्ली, रिक्त, 0, flags);
    पूर्णांक ret;

    *ranges_arg = रिक्त;

    जर (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        जा fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->मूल्य_min = field->min;
    range->मूल्य_max = field->max;

    निवड (field->type) {
    स्थिती AV_OPT_TYPE_BOOL:
    स्थिती AV_OPT_TYPE_INT:
    स्थिती AV_OPT_TYPE_UINT:
    स्थिती AV_OPT_TYPE_INT64:
    स्थिती AV_OPT_TYPE_UINT64:
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
    स्थिती AV_OPT_TYPE_FLOAT:
    स्थिती AV_OPT_TYPE_DOUBLE:
    स्थिती AV_OPT_TYPE_DURATION:
    स्थिती AV_OPT_TYPE_COLOR:
        थांबा;
    स्थिती AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->मूल्य_min = -1;
        range->मूल्य_max = पूर्णांक_उच्च;
        थांबा;
    स्थिती AV_OPT_TYPE_RATIONAL:
        range->component_min = पूर्णांक_न्यून;
        range->component_max = पूर्णांक_उच्च;
        थांबा;
    स्थिती AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = पूर्णांक_उच्च/128/8;
        range->मूल्य_min = 0;
        range->मूल्य_max = पूर्णांक_उच्च/8;
        थांबा;
    स्थिती AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = पूर्णांक_उच्च;
        range->मूल्य_min = 1;
        range->मूल्य_max = पूर्णांक_उच्च;
        थांबा;
    पूर्वनिर्धारित:
        ret = AVERROR(ENOSYS);
        जा fail;
    }

    *ranges_arg = ranges;
    परत 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    परत ret;
}

शून्य av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    पूर्णांक i;
    AVOptionRanges *ranges = *rangesp;

    जर (!ranges)
        परत;

    साठी (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        जर (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

पूर्णांक av_opt_is_set_to_default(शून्य *obj, स्थिरांक AVOption *o)
{
    int64_t i64;
    द्विगुण d;
    AVRational q;
    पूर्णांक ret, w, h;
    अक्षर *str;
    शून्य *dst;

    जर (!o || !obj)
        परत AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    जर (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        स्थिरांक अक्षर *def = o->default_val.arr ? o->default_val.arr->def : रिक्त;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        जर (ret < 0)
            परत ret;

        जर (!!val != !!def)
            ret = 0;
        अन्यथा जर (val)
            ret = !म_भेद(val, def);
        अन्यथा
            ret = 1;

        av_freep(&val);

        परत ret;
    }

    निवड (o->type) {
    स्थिती AV_OPT_TYPE_CONST:
        परत 1;
    स्थिती AV_OPT_TYPE_BOOL:
    स्थिती AV_OPT_TYPE_FLAGS:
    स्थिती AV_OPT_TYPE_PIXEL_FMT:
    स्थिती AV_OPT_TYPE_SAMPLE_FMT:
    स्थिती AV_OPT_TYPE_INT:
    स्थिती AV_OPT_TYPE_UINT:
    स्थिती AV_OPT_TYPE_DURATION:
    स्थिती AV_OPT_TYPE_INT64:
    स्थिती AV_OPT_TYPE_UINT64:
        read_संख्या(o, dst, रिक्त, रिक्त, &i64);
        परत o->default_val.i64 == i64;
    स्थिती AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        जर (o->default_val.str) {
            जर ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                परत ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        परत ret;
    }
    स्थिती AV_OPT_TYPE_STRING:
        str = *(अक्षर **)dst;
        जर (str == o->default_val.str) //2 NULLs
            परत 1;
        जर (!str || !o->default_val.str) //1 NULL
            परत 0;
        परत !म_भेद(str, o->default_val.str);
    स्थिती AV_OPT_TYPE_DOUBLE:
        d = *(द्विगुण *)dst;
        परत o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    स्थिती AV_OPT_TYPE_FLOAT:
        d = *(दशांश *)dst;
        परत (दशांश)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    स्थिती AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, पूर्णांक_उच्च);
        परत !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    स्थिती AV_OPT_TYPE_द्विमान: {
        संरचना {
            uint8_t *data;
            पूर्णांक size;
        } tmp = {0};
        पूर्णांक opt_size = *(पूर्णांक *)((शून्य **)dst + 1);
        शून्य *opt_ptr = *(शून्य **)dst;
        जर (!opt_size && (!o->default_val.str || !म_माप(o->default_val.str)))
            परत 1;
        जर (!opt_size ||  !o->default_val.str || !म_माप(o->default_val.str ))
            परत 0;
        जर (opt_size != म_माप(o->default_val.str) / 2)
            परत 0;
        ret = set_string_द्विमान(रिक्त, रिक्त, o->default_val.str, &tmp.data);
        जर (!ret)
            ret = !स_भेद(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        परत ret;
    }
    स्थिती AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = रिक्त;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        स्थिरांक AVDictionaryEntry *en1 = रिक्त;
        स्थिरांक AVDictionaryEntry *en2 = रिक्त;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        जर (ret < 0) {
            av_dict_free(&dict1);
            परत ret;
        }
        करा {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } पर्यंत (en1 && en2 && !म_भेद(en1->किल्ली, en2->किल्ली) && !म_भेद(en1->मूल्य, en2->मूल्य));
        av_dict_free(&dict1);
        परत (!en1 && !en2);
    }
    स्थिती AV_OPT_TYPE_IMAGE_SIZE:
        जर (!o->default_val.str || !म_भेद(o->default_val.str, "none"))
            w = h = 0;
        अन्यथा जर ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            परत ret;
        परत (w == *(पूर्णांक *)dst) && (h == *((पूर्णांक *)dst+1));
    स्थिती AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        जर (o->default_val.str) {
            जर ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                परत ret;
        }
        परत !av_cmp_q(*(AVRational*)dst, q);
    स्थिती AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        जर (o->default_val.str) {
            जर ((ret = av_parse_color(color, o->default_val.str, -1, रिक्त)) < 0)
                परत ret;
        }
        परत !स_भेद(color, dst, आकार(color));
    }
    पूर्वनिर्धारित:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        थांबा;
    }
    परत AVERROR_PATCHWELCOME;
}

पूर्णांक av_opt_is_set_to_default_by_name(शून्य *obj, स्थिरांक अक्षर *name, पूर्णांक शोध_flags)
{
    स्थिरांक AVOption *o;
    शून्य *target;
    जर (!obj)
        परत AVERROR(EINVAL);
    o = av_opt_find2(obj, name, रिक्त, 0, शोध_flags, &target);
    जर (!o)
        परत AVERROR_OPTION_NOT_FOUND;
    परत av_opt_is_set_to_default(target, o);
}

स्थिर पूर्णांक opt_serialize(शून्य *obj, पूर्णांक opt_flags, पूर्णांक flags, पूर्णांक *cnt,
                         AVBPrint *bprint, स्थिरांक अक्षर किल्ली_val_sep, स्थिरांक अक्षर pairs_sep)
{
    स्थिरांक AVOption *o = रिक्त;
    शून्य *child = रिक्त;
    uint8_t *buf;
    पूर्णांक ret;
    स्थिरांक अक्षर special_chars[] = {pairs_sep, किल्ली_val_sep, '\0'};

    जर (flags & AV_OPT_SERIALIZE_शोध_CHILDREN)
        पर्यंत (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                किल्ली_val_sep, pairs_sep);
            जर (ret < 0)
                परत ret;
        }

    पर्यंत (o = av_opt_next(obj, o)) {
        जर (o->type == AV_OPT_TYPE_CONST)
            सुरूठेवा;
        जर ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            जर ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                जर (o->flags == opt_flags)
                    सुरूठेवा;
            } अन्यथा जर ((o->flags & opt_flags) == opt_flags)
                सुरूठेवा;
        } अन्यथा {
            जर ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                सुरूठेवा;
            अन्यथा जर (((o->flags & opt_flags) != opt_flags))
                सुरूठेवा;
        }
        जर (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            सुरूठेवा;
        जर ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, रिक्त);
            परत ret;
        }
        जर (buf) {
            जर ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &किल्ली_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    परत 0;
}

पूर्णांक av_opt_serialize(शून्य *obj, पूर्णांक opt_flags, पूर्णांक flags, अक्षर **buffer,
                     स्थिरांक अक्षर किल्ली_val_sep, स्थिरांक अक्षर pairs_sep)
{
    AVBPrint bprint;
    पूर्णांक ret, cnt = 0;

    जर (pairs_sep == '\0' || किल्ली_val_sep == '\0' || pairs_sep == किल्ली_val_sep ||
        pairs_sep == '\\' || किल्ली_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        परत AVERROR(EINVAL);
    }

    जर (!obj || !buffer)
        परत AVERROR(EINVAL);

    *buffer = रिक्त;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        किल्ली_val_sep, pairs_sep);
    जर (ret < 0)
        परत ret;

    ret = av_bprint_finalize(&bprint, buffer);
    जर (ret < 0)
        परत ret;
    परत 0;
}
