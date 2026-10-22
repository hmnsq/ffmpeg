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

#समावेश "avutil.h"
#समावेश "avassert.h"
#समावेश "avstring.h"
#समावेश "channel_layout.h"
#समावेश "dict.h"
#समावेश "eval.h"
#समावेश "log.h"
#समावेश "mem.h"
#समावेश "parseutils.h"
#समावेश "pixdesc.h"
#समावेश "mathematics.h"
#समावेश "opt.h"
#समावेश "samplefmt.h"
#समावेश "bprint.h"

#समावेश <float.h>

#घोषणा TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

स्थिर AVOption *av_opt_अग्र(स्थिर व्योम *obj, स्थिर AVOption *last)
{
    स्थिर AVClass *class;
    अगर (!obj)
        वापस शून्य;
    class = *(स्थिर AVClass**)obj;
    अगर (!last && class && class->option && class->option[0].name)
        वापस class->option;
    अगर (last && last[1].name)
        वापस ++last;
    वापस शून्य;
}

अटल स्थिर काष्ठा {
    माप_प्रकार      आकार;
    स्थिर अक्षर *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { माप(अचिन्हित),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { माप(पूर्णांक),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { माप(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { माप(अचिन्हित),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { माप(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { माप(द्विगुन),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { माप(भग्न),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { माप(अक्षर *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { माप(AVRational),     "<rational>" },
    [AV_OPT_TYPE_द्विआधारी]        = { माप(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { माप(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_आकार]    = { माप(पूर्णांक[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { माप(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { माप(क्रमागत AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { माप(क्रमागत AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { माप(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { माप(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { माप(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { माप(पूर्णांक),            "<boolean>" },
};

// option is plain old data
अटल पूर्णांक opt_is_pod(क्रमागत AVOptionType type)
{
    चयन (type) {
    हाल AV_OPT_TYPE_FLAGS:
    हाल AV_OPT_TYPE_INT:
    हाल AV_OPT_TYPE_INT64:
    हाल AV_OPT_TYPE_DOUBLE:
    हाल AV_OPT_TYPE_FLOAT:
    हाल AV_OPT_TYPE_RATIONAL:
    हाल AV_OPT_TYPE_UINT64:
    हाल AV_OPT_TYPE_IMAGE_आकार:
    हाल AV_OPT_TYPE_PIXEL_FMT:
    हाल AV_OPT_TYPE_SAMPLE_FMT:
    हाल AV_OPT_TYPE_VIDEO_RATE:
    हाल AV_OPT_TYPE_DURATION:
    हाल AV_OPT_TYPE_COLOR:
    हाल AV_OPT_TYPE_BOOL:
    हाल AV_OPT_TYPE_UINT:
        वापस 1;
    }
    वापस 0;
}

अटल uint8_t opt_array_sep(स्थिर AVOption *o)
{
    स्थिर AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    वापस (d && d->sep) ? d->sep : ',';
}

अटल व्योम *opt_array_pelem(स्थिर AVOption *o, व्योम *array, अचिन्हित idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    वापस (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].आकार;
}

अटल अचिन्हित *opt_array_pcount(स्थिर व्योम *parray)
{
    वापस (अचिन्हित *)((स्थिर व्योम * स्थिर *)parray + 1);
}

अटल व्योम opt_free_elem(क्रमागत AVOptionType type, व्योम *ptr)
{
    चयन (TYPE_BASE(type)) {
    हाल AV_OPT_TYPE_STRING:
    हाल AV_OPT_TYPE_द्विआधारी:
        av_freep(ptr);
        अवरोध;

    हाल AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        अवरोध;

    हाल AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        अवरोध;

    शेष:
        अवरोध;
    }
}

अटल व्योम opt_free_array(स्थिर AVOption *o, व्योम *parray, अचिन्हित *गिनती)
{
    क्रम (अचिन्हित i = 0; i < *गिनती; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(व्योम **)parray, i));

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
अटल पूर्णांक opt_set_init(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags,
                        पूर्णांक require_type,
                        व्योम **ptgt, स्थिर AVOption **po, व्योम **pdst)
{
    व्योम *logctx;
    स्थिर AVOption *o;
    व्योम *tgt;

    o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &tgt);
    अगर (!o || (!tgt && !(खोज_flags & AV_OPT_खोज_FAKE_OBJ)))
        वापस AVERROR_OPTION_NOT_FOUND;

    अगर (o->flags & AV_OPT_FLAG_READONLY)
        वापस AVERROR(EINVAL);

    logctx = tgt ? obj : शून्य;

    अगर (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        वापस AVERROR(EINVAL);
    }

    अगर (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        अचिन्हित *state_flags = शून्य;
        स्थिर AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(स्थिर AVClass**)tgt;
        अगर (class->state_flags_offset)
            state_flags = (अचिन्हित*)((uint8_t*)tgt + class->state_flags_offset);

        अगर (!state_flags && obj != tgt) {
            class = *(स्थिर AVClass**)obj;
            अगर (class->state_flags_offset)
                state_flags = (अचिन्हित*)((uint8_t*)obj + class->state_flags_offset);
        }

        अगर (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            वापस AVERROR(EINVAL);
        }
    }

    अगर (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    अगर (po)
        *po   = o;
    अगर (ptgt)
        *ptgt = tgt;
    अगर (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : शून्य;

    वापस 0;
}

अटल AVRational double_to_rational(द्विगुन d)
{
     AVRational r = av_d2q(d, 1 << 24);
     अगर ((!r.अंक || !r.den) && d)
         r = av_d2q(d, पूर्णांक_उच्च);
     वापस r;
}

अटल पूर्णांक read_संख्या(स्थिर AVOption *o, स्थिर व्योम *dst, द्विगुन *अंक, पूर्णांक *den, int64_t *intnum)
{
    चयन (TYPE_BASE(o->type)) {
    हाल AV_OPT_TYPE_FLAGS:
        *intnum = *(अचिन्हित पूर्णांक*)dst;
        वापस 0;
    हाल AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(क्रमागत AVPixelFormat *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(क्रमागत AVSampleFormat *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_BOOL:
    हाल AV_OPT_TYPE_INT:
        *intnum = *(पूर्णांक *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_UINT:
        *intnum = *(अचिन्हित पूर्णांक *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_DURATION:
    हाल AV_OPT_TYPE_INT64:
    हाल AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_FLOAT:
        *अंक = *(भग्न *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_DOUBLE:
        *अंक = *(द्विगुन *)dst;
        वापस 0;
    हाल AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->अंक;
        *den    = ((AVRational *)dst)->den;
        वापस 0;
    हाल AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        वापस 0;
    }
    वापस AVERROR(EINVAL);
}

अटल पूर्णांक write_संख्या(व्योम *obj, स्थिर AVOption *o, व्योम *dst,
                        द्विगुन अंक, पूर्णांक den, int64_t intnum,
                        पूर्णांक ignore_range)
{
    व्योम *logctx = dst ? obj : शून्य;
    स्थिर क्रमागत AVOptionType type = TYPE_BASE(o->type);

    अगर (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < अंक * intnum || o->min * den > अंक * intnum)) {
        अंक = den ? अंक * intnum / den : (अंक && intnum ? अनन्त : न_अंक);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               अंक, o->name, o->min, o->max);
        वापस AVERROR(दुस्फल);
    }
    अगर (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        द्विगुन d = अंक*intnum/den;
        अगर (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   अंक*intnum/den, o->name);
            वापस AVERROR(दुस्फल);
        }
    }

    अगर (!dst)
        वापस 0;

    चयन (type) {
    हाल AV_OPT_TYPE_PIXEL_FMT:
        *(क्रमागत AVPixelFormat *)dst = llrint(अंक / den) * intnum;
        अवरोध;
    हाल AV_OPT_TYPE_SAMPLE_FMT:
        *(क्रमागत AVSampleFormat *)dst = llrint(अंक / den) * intnum;
        अवरोध;
    हाल AV_OPT_TYPE_BOOL:
    हाल AV_OPT_TYPE_FLAGS:
    हाल AV_OPT_TYPE_INT:
    हाल AV_OPT_TYPE_UINT:
        *(पूर्णांक *)dst = llrint(अंक / den) * intnum;
        अवरोध;
    हाल AV_OPT_TYPE_DURATION:
    हाल AV_OPT_TYPE_INT64:{
        द्विगुन d = अंक / den;
        अगर (intnum == 1 && d == (द्विगुन)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } अन्यथा
            *(int64_t *)dst = llrint(d) * intnum;
        अवरोध;}
    हाल AV_OPT_TYPE_UINT64:{
        द्विगुन d = अंक / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        अगर (intnum == 1 && d == (द्विगुन)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } अन्यथा अगर (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } अन्यथा {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        अवरोध;}
    हाल AV_OPT_TYPE_FLOAT:
        *(भग्न *)dst = अंक * intnum / den;
        अवरोध;
    हाल AV_OPT_TYPE_DOUBLE:
        *(द्विगुन    *)dst = अंक * intnum / den;
        अवरोध;
    हाल AV_OPT_TYPE_RATIONAL:
    हाल AV_OPT_TYPE_VIDEO_RATE:
        अगर ((पूर्णांक) अंक == अंक)
            *(AVRational *)dst = (AVRational) { अंक *intnum, den };
        अन्यथा
            *(AVRational *)dst = double_to_rational(अंक * intnum / den);
        अवरोध;
    शेष:
        वापस AVERROR(EINVAL);
    }
    वापस 0;
}

अटल पूर्णांक hexchar2int(अक्षर c) {
    अगर (c >= '0' && c <= '9')
        वापस c - '0';
    अगर (c >= 'a' && c <= 'f')
        वापस c - 'a' + 10;
    अगर (c >= 'A' && c <= 'F')
        वापस c - 'A' + 10;
    वापस -1;
}

अटल पूर्णांक set_string_द्विआधारी(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t **dst)
{
    पूर्णांक *lendst;
    uint8_t *bin, *ptr;
    पूर्णांक len;

    अगर (dst) {
        lendst = (पूर्णांक *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    अगर (!val || !(len = म_माप(val)))
        वापस 0;

    अगर (len & 1)
        वापस AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    अगर (!ptr)
        वापस AVERROR(ENOMEM);
    जबतक (*val) {
        पूर्णांक a = hexchar2int(*val++);
        पूर्णांक b = hexchar2int(*val++);
        अगर (a < 0 || b < 0) {
            av_free(bin);
            वापस AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    अगर (dst) {
        *dst    = bin;
        *lendst = len;
    } अन्यथा {
        av_free(bin);
    }

    वापस 0;
}

अटल पूर्णांक set_string(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t **dst)
{
    अगर (!dst)
        वापस 0;
    av_freep(dst);
    अगर (!val)
        वापस 0;
    *dst = av_strdup(val);
    वापस *dst ? 0 : AVERROR(ENOMEM);
}

#घोषणा DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

अटल पूर्णांक set_string_संख्या(व्योम *obj, व्योम *target_obj, स्थिर AVOption *o, स्थिर अक्षर *val, व्योम *dst)
{
    व्योम *logctx = dst ? obj : शून्य;
    स्थिर क्रमागत AVOptionType type = TYPE_BASE(o->type);
    पूर्णांक ret = 0;

    अगर (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        पूर्णांक अंक, den;
        अक्षर c;
        अगर (माला_पूछो(val, "%d%*1[:/]%d%c", &अंक, &den, &c) == 2) {
            अगर ((ret = write_संख्या(obj, o, dst, 1, den, अंक, 0)) >= 0)
                वापस ret;
            ret = 0;
        }
    }

    क्रम (;;) {
        पूर्णांक i = 0;
        अक्षर buf[256];
        पूर्णांक cmd = 0;
        द्विगुन d;
        int64_t intnum = 1;

        अगर (type == AV_OPT_TYPE_FLAGS) {
            अगर (*val == '+' || *val == '-')
                cmd = *(val++);
            क्रम (; i < माप(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            पूर्णांक res;
            पूर्णांक ci = 0;
            द्विगुन const_मूल्यावली[64];
            स्थिर अक्षर * const_names[64];
            पूर्णांक खोज_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_खोज_CHILDREN : 0;
            स्थिर AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, खोज_flags);
            अगर (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                अगर (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } अन्यथा {
                अगर (o->unit) {
                    क्रम (o_named = शून्य; o_named = av_opt_अग्र(target_obj, o_named); ) {
                        अगर (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !म_भेद(o_named->unit, o->unit)) {
                            अगर (ci + 6 >= FF_ARRAY_ELEMS(const_मूल्यावली)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                वापस AVERROR_PATCHWELCOME;
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
                const_names [ci] = शून्य;
                const_मूल्यावली[ci] = 0;

                res = av_व्यंजक_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_मूल्यावली, शून्य, शून्य, शून्य, शून्य, शून्य, 0, obj);
                अगर (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    वापस res;
                }
            }
        }
        अगर (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(अचिन्हित पूर्णांक*)dst;
            अगर (cmd == '+')
                d = intnum | (int64_t)d;
            अन्यथा अगर (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        अगर ((ret = write_संख्या(obj, o, dst, d, 1, 1, 0)) < 0)
            वापस ret;
        val += i;
        अगर (!i || !*val)
            वापस 0;
    }
}

अटल पूर्णांक set_string_image_आकार(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, पूर्णांक *dst)
{
    व्योम *logctx = dst ? obj : शून्य;
    पूर्णांक tmp[2];
    पूर्णांक ret;

    अगर (!val || !म_भेद(val, "none")) {
        अगर (dst) {
        dst[0] =
        dst[1] = 0;
        }
        वापस 0;
    }
    ret = av_parse_video_आकार(&tmp[0], &tmp[1], val);
    अगर (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        वापस ret;
    }
    अगर (dst)
        स_नकल(dst, tmp, माप(tmp));
    वापस ret;
}

अटल पूर्णांक set_string_video_rate(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, AVRational *dst)
{
    व्योम *logctx = dst ? obj : शून्य;
    AVRational tmp;
    पूर्णांक ret = av_parse_video_rate(&tmp, val);
    अगर (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    अगर (dst)
        *dst = tmp;
    वापस ret;
}

अटल पूर्णांक set_string_color(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t *dst)
{
    व्योम *logctx = dst ? obj : शून्य;
    पूर्णांक ret;

    अगर (!val) {
        वापस 0;
    } अन्यथा {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        अगर (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            वापस ret;
        }
        अगर (dst)
            स_नकल(dst, tmp, माप(tmp));
        वापस ret;
    }
    वापस 0;
}

अटल स्थिर अक्षर *get_bool_name(पूर्णांक val)
{
    अगर (val < 0)
        वापस "auto";
    वापस val ? "true" : "false";
}

अटल पूर्णांक set_string_bool(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, पूर्णांक *dst)
{
    व्योम *logctx = dst ? obj : शून्य;
    पूर्णांक n;

    अगर (!val)
        वापस 0;

    अगर (!म_भेद(val, "auto")) {
        n = -1;
    } अन्यथा अगर (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } अन्यथा अगर (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } अन्यथा {
        अक्षर *end = शून्य;
        n = म_से_दीर्घ(val, &end, 10);
        अगर (val + म_माप(val) != end)
            जाओ fail;
    }

    अगर (n < o->min || n > o->max)
        जाओ fail;

    अगर (dst)
    *dst = n;
    वापस 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    वापस AVERROR(EINVAL);
}

अटल पूर्णांक set_string_fmt(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t *dst,
                          पूर्णांक fmt_nb, पूर्णांक ((*get_fmt)(स्थिर अक्षर *)), स्थिर अक्षर *desc,
                          क्रमागत AVOptionType type)
{
    व्योम *logctx = dst ? obj : शून्य;
    पूर्णांक fmt, min, max;

    अगर (!val || !म_भेद(val, "none")) {
        fmt = -1;
    } अन्यथा {
        fmt = get_fmt(val);
        अगर (fmt == -1) {
            अक्षर *पुच्छ;
            fmt = म_से_दीर्घ(val, &पुच्छ, 0);
            अगर (*पुच्छ || (अचिन्हित)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                वापस AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    अगर(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    अगर (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        वापस AVERROR(दुस्फल);
    }

    अगर (dst)
    चयन (type) {
    हाल AV_OPT_TYPE_PIXEL_FMT:  *(क्रमागत AVPixelFormat *)dst = fmt; अवरोध;
    हाल AV_OPT_TYPE_SAMPLE_FMT: *(क्रमागत AVSampleFormat*)dst = fmt; अवरोध;
    शेष: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    वापस 0;
}

अटल पूर्णांक get_pix_fmt(स्थिर अक्षर *name)
{
    वापस av_get_pix_fmt(name);
}

अटल पूर्णांक set_string_pixel_fmt(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t *dst)
{
    वापस set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

अटल पूर्णांक get_sample_fmt(स्थिर अक्षर *name)
{
    वापस av_get_sample_fmt(name);
}

अटल पूर्णांक set_string_sample_fmt(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t *dst)
{
    वापस set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

अटल पूर्णांक set_string_dict(व्योम *obj, स्थिर AVOption *o, स्थिर अक्षर *val, uint8_t **dst)
{
    AVDictionary *options = शून्य;

    अगर (val) {
        पूर्णांक ret = av_dict_parse_string(&options, val, "=", ":", 0);
        अगर (ret < 0) {
            av_dict_free(&options);
            वापस ret;
        }
    }

    अगर (!dst) {
        av_dict_free(&options);
        वापस 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    वापस 0;
}

अटल पूर्णांक set_string_channel_layout(व्योम *obj, स्थिर AVOption *o,
                                     स्थिर अक्षर *val, व्योम *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    पूर्णांक ret;
    अगर (dst)
    av_channel_layout_uninit(channel_layout);
    अन्यथा
        channel_layout = &tmp;
    अगर (!val)
        वापस 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    अगर (ret < 0)
        वापस ret;
    अगर (!dst)
        av_channel_layout_uninit(channel_layout);
    वापस 0;
}

अटल पूर्णांक opt_set_elem(व्योम *obj, व्योम *target_obj, स्थिर AVOption *o,
                        स्थिर अक्षर *val, व्योम *dst)
{
    व्योम *logctx = dst ? obj : शून्य;
    स्थिर क्रमागत AVOptionType type = TYPE_BASE(o->type);
    पूर्णांक ret;

    अगर (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_आकार &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        वापस AVERROR(EINVAL);

    चयन (type) {
    हाल AV_OPT_TYPE_BOOL:
        वापस set_string_bool(obj, o, val, dst);
    हाल AV_OPT_TYPE_STRING:
        वापस set_string(obj, o, val, dst);
    हाल AV_OPT_TYPE_द्विआधारी:
        वापस set_string_द्विआधारी(obj, o, val, dst);
    हाल AV_OPT_TYPE_FLAGS:
    हाल AV_OPT_TYPE_INT:
    हाल AV_OPT_TYPE_UINT:
    हाल AV_OPT_TYPE_INT64:
    हाल AV_OPT_TYPE_UINT64:
    हाल AV_OPT_TYPE_FLOAT:
    हाल AV_OPT_TYPE_DOUBLE:
    हाल AV_OPT_TYPE_RATIONAL:
        वापस set_string_संख्या(obj, target_obj, o, val, dst);
    हाल AV_OPT_TYPE_IMAGE_आकार:
        वापस set_string_image_आकार(obj, o, val, dst);
    हाल AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        अगर (ret < 0)
            वापस ret;
        वापस write_संख्या(obj, o, dst, 1, tmp.den, tmp.अंक, 0);
    }
    हाल AV_OPT_TYPE_PIXEL_FMT:
        वापस set_string_pixel_fmt(obj, o, val, dst);
    हाल AV_OPT_TYPE_SAMPLE_FMT:
        वापस set_string_sample_fmt(obj, o, val, dst);
    हाल AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            अगर (val) {
                अगर ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    वापस ret;
                }
            }
            अगर (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                वापस AVERROR(दुस्फल);
            }
            अगर (dst)
            *(int64_t *)dst = usecs;
            वापस 0;
        }
    हाल AV_OPT_TYPE_COLOR:
        वापस set_string_color(obj, o, val, dst);
    हाल AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        अगर (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        वापस ret;
    हाल AV_OPT_TYPE_DICT:
        वापस set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    वापस AVERROR(EINVAL);
}

अटल पूर्णांक opt_set_array(व्योम *obj, व्योम *target_obj, स्थिर AVOption *o,
                         स्थिर अक्षर *val, व्योम *dst)
{
    स्थिर AVOptionArrayDef *arr = o->default_val.arr;
    स्थिर माप_प्रकार      elem_आकार = opt_type_desc[TYPE_BASE(o->type)].आकार;
    स्थिर uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = शून्य;

    व्योम      *logctx = dst ? obj : शून्य;
    व्योम       *elems = शून्य;
    अचिन्हित nb_elems = 0;
    पूर्णांक ret;

    अगर (val && *val) {
        str = av_malloc(म_माप(val) + 1);
        अगर (!str)
            वापस AVERROR(ENOMEM);
    }

    // split and unescape the string
    जबतक (val && *val) {
        uint8_t *p = str;
        व्योम *tmp;

        अगर (arr && arr->आकार_max && nb_elems >= arr->आकार_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->आकार_max, o->name);
            ret = AVERROR(EINVAL);
            जाओ fail;
        }

        क्रम (; *val; val++, p++) {
            अगर (*val == '\\' && val[1])
                val++;
            अन्यथा अगर (*val == sep) {
                val++;
                अवरोध;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_आकार);
        अगर (!tmp) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        स_रखो(tmp, 0, elem_आकार);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        अगर (ret < 0)
            जाओ fail;
        nb_elems++;
    }
    av_freep(&str);

    अगर (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    अगर (arr && nb_elems < arr->आकार_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->आकार_min, o->name);
        ret = AVERROR(EINVAL);
        जाओ fail;
    }

    अगर (dst) {
    *((व्योम **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } अन्यथा
        opt_free_array(o, &elems, &nb_elems);

    वापस 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    वापस ret;
}

पूर्णांक av_opt_set(व्योम *obj, स्थिर अक्षर *name, स्थिर अक्षर *val, पूर्णांक खोज_flags)
{
    व्योम *dst, *target_obj;
    स्थिर AVOption *o;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, खोज_flags, 0, &target_obj, &o, &dst);
    अगर (ret < 0)
        वापस ret;

    वापस ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#घोषणा OPT_EVAL_संख्या(name, opttype, vartype)                         \
पूर्णांक av_opt_eval_ ## name(व्योम *obj, स्थिर AVOption *o,                  \
                         स्थिर अक्षर *val, vartype *name ## _out)        \
{                                                                       \
    अगर (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        वापस AVERROR(EINVAL);                                         \
    वापस set_string_संख्या(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_संख्या(flags,  AV_OPT_TYPE_FLAGS,    पूर्णांक)
OPT_EVAL_संख्या(पूर्णांक,    AV_OPT_TYPE_INT,      पूर्णांक)
OPT_EVAL_संख्या(uint,   AV_OPT_TYPE_UINT,     अचिन्हित)
OPT_EVAL_संख्या(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_संख्या(भग्न,  AV_OPT_TYPE_FLOAT,    भग्न)
OPT_EVAL_संख्या(द्विगुन, AV_OPT_TYPE_DOUBLE,   द्विगुन)
OPT_EVAL_संख्या(q,      AV_OPT_TYPE_RATIONAL, AVRational)

अटल पूर्णांक set_संख्या(व्योम *obj, स्थिर अक्षर *name, द्विगुन अंक, पूर्णांक den, int64_t intnum,
                      पूर्णांक खोज_flags, पूर्णांक require_type)
{
    व्योम *dst;
    स्थिर AVOption *o;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, खोज_flags, require_type, शून्य, &o, &dst);
    अगर (ret < 0)
        वापस ret;
    अगर (dst)
        ret = write_संख्या(obj, o, dst, अंक, den, intnum, 0);

    वापस ret;
}

पूर्णांक av_opt_set_int(व्योम *obj, स्थिर अक्षर *name, int64_t val, पूर्णांक खोज_flags)
{
    वापस set_संख्या(obj, name, 1, 1, val, खोज_flags, 0);
}

पूर्णांक av_opt_set_double(व्योम *obj, स्थिर अक्षर *name, द्विगुन val, पूर्णांक खोज_flags)
{
    वापस set_संख्या(obj, name, val, 1, 1, खोज_flags, 0);
}

पूर्णांक av_opt_set_q(व्योम *obj, स्थिर अक्षर *name, AVRational val, पूर्णांक खोज_flags)
{
    वापस set_संख्या(obj, name, val.अंक, val.den, 1, खोज_flags, 0);
}

पूर्णांक av_opt_set_bin(व्योम *obj, स्थिर अक्षर *name, स्थिर uint8_t *val, पूर्णांक len, पूर्णांक खोज_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    पूर्णांक *lendst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_द्विआधारी,
                       शून्य, शून्य, (व्योम**)&dst);
    अगर (ret < 0)
        वापस ret;

    अगर (dst) {
    ptr = len ? av_malloc(len) : शून्य;
    अगर (len && !ptr)
        वापस AVERROR(ENOMEM);

    lendst = (पूर्णांक *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    अगर (len)
        स_नकल(ptr, val, len);
    }

    वापस 0;
}

पूर्णांक av_opt_set_image_आकार(व्योम *obj, स्थिर अक्षर *name, पूर्णांक w, पूर्णांक h, पूर्णांक खोज_flags)
{
    स्थिर AVOption *o;
    व्योम *logctx;
    पूर्णांक *dst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_IMAGE_आकार,
                       शून्य, &o, (व्योम**)&dst);
    अगर (ret < 0)
        वापस ret;

    logctx = dst ? obj : शून्य;

    अगर (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        वापस AVERROR(EINVAL);
    }

    अगर (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    वापस 0;
}

पूर्णांक av_opt_set_video_rate(व्योम *obj, स्थिर अक्षर *name, AVRational val, पूर्णांक खोज_flags)
{
    वापस set_संख्या(obj, name, val.अंक, val.den, 1, खोज_flags, AV_OPT_TYPE_VIDEO_RATE);
}

अटल पूर्णांक set_format(व्योम *obj, स्थिर अक्षर *name, पूर्णांक fmt, पूर्णांक खोज_flags,
                      क्रमागत AVOptionType type, स्थिर अक्षर *desc, पूर्णांक nb_fmts)
{
    स्थिर AVOption *o;
    व्योम *logctx;
    पूर्णांक *dst;
    पूर्णांक min, max, ret;

    ret = opt_set_init(obj, name, खोज_flags, type, शून्य, &o, (व्योम**)&dst);
    अगर (ret < 0)
        वापस ret;

    logctx = dst ? obj : शून्य;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    अगर (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        वापस AVERROR(दुस्फल);
    }
    अगर (dst)
    *dst = fmt;
    वापस 0;
}

पूर्णांक av_opt_set_pixel_fmt(व्योम *obj, स्थिर अक्षर *name, क्रमागत AVPixelFormat fmt, पूर्णांक खोज_flags)
{
    वापस set_format(obj, name, fmt, खोज_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

पूर्णांक av_opt_set_sample_fmt(व्योम *obj, स्थिर अक्षर *name, क्रमागत AVSampleFormat fmt, पूर्णांक खोज_flags)
{
    वापस set_format(obj, name, fmt, खोज_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

पूर्णांक av_opt_set_dict_val(व्योम *obj, स्थिर अक्षर *name, स्थिर AVDictionary *val,
                        पूर्णांक खोज_flags)
{
    AVDictionary **dst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_DICT, शून्य, शून्य,
                       (व्योम**)&dst);
    अगर (ret < 0)
        वापस ret;

    अगर (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    वापस ret;
}

पूर्णांक av_opt_set_chlayout(व्योम *obj, स्थिर अक्षर *name,
                        स्थिर AVChannelLayout *channel_layout,
                        पूर्णांक खोज_flags)
{
    AVChannelLayout *dst;
    पूर्णांक ret;

    ret = opt_set_init(obj, name, खोज_flags, AV_OPT_TYPE_CHLAYOUT, शून्य, शून्य,
                       (व्योम**)&dst);
    अगर (ret < 0)
        वापस ret;

    अगर (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    वापस ret;
}

अटल व्योम format_duration(अक्षर *buf, माप_प्रकार आकार, int64_t d)
{
    अक्षर *e;

    av_assert0(आकार >= 25);
    अगर (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        आकार--;
        d = -d;
    }
    अगर (d == INT64_MAX)
        snprintf(buf, आकार, "INT64_MAX");
    अन्यथा अगर (d == INT64_MIN)
        snprintf(buf, आकार, "INT64_MIN");
    अन्यथा अगर (d > (int64_t)3600*1000000)
        snprintf(buf, आकार, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (पूर्णांक)((d / 60000000) % 60),
                 (पूर्णांक)((d / 1000000) % 60),
                 (पूर्णांक)(d % 1000000));
    अन्यथा अगर (d > 60*1000000)
        snprintf(buf, आकार, "%d:%02d.%06d",
                 (पूर्णांक)(d / 60000000),
                 (पूर्णांक)((d / 1000000) % 60),
                 (पूर्णांक)(d % 1000000));
    अन्यथा
        snprintf(buf, आकार, "%d.%06d",
                 (पूर्णांक)(d / 1000000),
                 (पूर्णांक)(d % 1000000));
    e = buf + म_माप(buf);
    जबतक (e > buf && e[-1] == '0')
        *(--e) = 0;
    अगर (e > buf && e[-1] == '.')
        *(--e) = 0;
}

अटल पूर्णांक opt_get_elem(स्थिर AVOption *o, uint8_t **pbuf, माप_प्रकार buf_len,
                        स्थिर व्योम *dst, पूर्णांक खोज_flags)
{
    पूर्णांक ret;

    चयन (TYPE_BASE(o->type)) {
    हाल AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(पूर्णांक *)dst));
        अवरोध;
    हाल AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(पूर्णांक *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(पूर्णांक *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(अचिन्हित *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(भग्न *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(द्विगुन *)dst);
        अवरोध;
    हाल AV_OPT_TYPE_VIDEO_RATE:
    हाल AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->अंक, ((AVRational *)dst)->den);
        अवरोध;
    हाल AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        अवरोध;
    हाल AV_OPT_TYPE_STRING:
        अगर (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } अन्यथा अगर (खोज_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = शून्य;
            वापस 0;
        } अन्यथा {
            *pbuf = av_strdup("");
        }
        वापस *pbuf ? 0 : AVERROR(ENOMEM);
    हाल AV_OPT_TYPE_द्विआधारी: {
        स्थिर uint8_t *bin;
        पूर्णांक len;

        अगर (!*(uint8_t **)dst && (खोज_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = शून्य;
            वापस 0;
        }
        len = *(पूर्णांक *)(((uint8_t *)dst) + माप(uint8_t *));
        अगर ((uint64_t)len * 2 + 1 > पूर्णांक_उच्च)
            वापस AVERROR(EINVAL);
        अगर (!(*pbuf = av_malloc(len * 2 + 1)))
            वापस AVERROR(ENOMEM);
        अगर (!len) {
            *pbuf[0] = '\0';
            वापस 0;
        }
        bin = *(uint8_t **)dst;
        क्रम (पूर्णांक i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        वापस 0;
    }
    हाल AV_OPT_TYPE_IMAGE_आकार:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((पूर्णांक *)dst)[0], ((पूर्णांक *)dst)[1]);
        अवरोध;
    हाल AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (अक्षर *)av_x_if_null(av_get_pix_fmt_name(*(क्रमागत AVPixelFormat *)dst), "none"));
        अवरोध;
    हाल AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (अक्षर *)av_x_if_null(av_get_sample_fmt_name(*(क्रमागत AVSampleFormat *)dst), "none"));
        अवरोध;
    हाल AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = म_माप(*pbuf); // no overflow possible, checked by an assert
        अवरोध;
    }
    हाल AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (पूर्णांक)((uint8_t *)dst)[0], (पूर्णांक)((uint8_t *)dst)[1],
                       (पूर्णांक)((uint8_t *)dst)[2], (पूर्णांक)((uint8_t *)dst)[3]);
        अवरोध;
    हाल AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        अवरोध;
    हाल AV_OPT_TYPE_DICT:
        अगर (!*(AVDictionary **)dst && (खोज_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = शून्य;
            वापस 0;
        }
        वापस av_dict_get_string(*(AVDictionary **)dst, (अक्षर **)pbuf, '=', ':');
    शेष:
        वापस AVERROR(EINVAL);
    }

    वापस ret;
}

अटल पूर्णांक opt_get_array(स्थिर AVOption *o, व्योम *dst, uint8_t **out_val)
{
    स्थिर अचिन्हित गिनती = *opt_array_pcount(dst);
    स्थिर uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = शून्य;
    माप_प्रकार   str_len = 0;
    पूर्णांक ret;

    *out_val = शून्य;

    क्रम (अचिन्हित i = 0; i < गिनती; i++) {
        uint8_t buf[128], *out = buf;
        माप_प्रकार out_len;

        ret = opt_get_elem(o, &out, माप(buf),
                           opt_array_pelem(o, *(व्योम **)dst, i), 0);
        अगर (ret < 0)
            जाओ fail;

        out_len = म_माप(out);
        अगर (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(दुस्फल);
            जाओ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        अगर (ret < 0)
            जाओ fail;

        // add separator if needed
        अगर (i)
            str[str_len++] = sep;

        // escape the element
        क्रम (अचिन्हित j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            अगर (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        अगर (out != buf)
            av_freep(&out);
        अगर (ret < 0) {
            av_freep(&str);
            वापस ret;
        }
    }

    *out_val = str;

    वापस 0;
}

पूर्णांक av_opt_get(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, uint8_t **out_val)
{
    व्योम *dst, *target_obj;
    स्थिर AVOption *o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    uint8_t *out, buf[128];
    पूर्णांक ret;

    अगर (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        वापस AVERROR_OPTION_NOT_FOUND;

    अगर (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    अगर (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        अगर (ret < 0)
            वापस ret;
        अगर (!*out_val && !(खोज_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            अगर (!*out_val)
               वापस AVERROR(ENOMEM);
        }
        वापस 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, माप(buf), dst, खोज_flags);
    अगर (ret < 0)
        वापस ret;
    अगर (out != buf) {
        *out_val = out;
        वापस 0;
    }

    अगर (ret >= माप(buf))
        वापस AVERROR(EINVAL);
    *out_val = av_strdup(out);
    वापस *out_val ? 0 : AVERROR(ENOMEM);
}

अटल पूर्णांक get_संख्या(व्योम *obj, स्थिर अक्षर *name, द्विगुन *अंक, पूर्णांक *den, int64_t *intnum,
                      पूर्णांक खोज_flags)
{
    व्योम *dst, *target_obj;
    स्थिर AVOption *o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        वापस AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    वापस read_संख्या(o, dst, अंक, den, intnum);
}

पूर्णांक av_opt_get_int(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    द्विगुन अंक = 1;
    पूर्णांक ret, den = 1;

    अगर ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, खोज_flags)) < 0)
        वापस ret;
    अगर (अंक == den)
        *out_val = intnum;
    अन्यथा
        *out_val = अंक * intnum / den;
    वापस 0;
}

पूर्णांक av_opt_get_double(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, द्विगुन *out_val)
{
    int64_t intnum = 1;
    द्विगुन अंक = 1;
    पूर्णांक ret, den = 1;

    अगर ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, खोज_flags)) < 0)
        वापस ret;
    *out_val = अंक * intnum / den;
    वापस 0;
}

पूर्णांक av_opt_get_q(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    द्विगुन अंक = 1;
    पूर्णांक ret, den = 1;

    अगर ((ret = get_संख्या(obj, name, &अंक, &den, &intnum, खोज_flags)) < 0)
        वापस ret;

    अगर (अंक == 1.0 && (पूर्णांक)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    अन्यथा
        *out_val = double_to_rational(अंक*intnum/den);
    वापस 0;
}

पूर्णांक av_opt_get_image_आकार(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, पूर्णांक *w_out, पूर्णांक *h_out)
{
    व्योम *dst, *target_obj;
    स्थिर AVOption *o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (o->type != AV_OPT_TYPE_IMAGE_आकार) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        वापस AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    अगर (w_out) *w_out = *(पूर्णांक *)dst;
    अगर (h_out) *h_out = *((पूर्णांक *)dst+1);
    वापस 0;
}

पूर्णांक av_opt_get_video_rate(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, AVRational *out_val)
{
    वापस av_opt_get_q(obj, name, खोज_flags, out_val);
}

अटल पूर्णांक get_format(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, व्योम *out_fmt,
                      क्रमागत AVOptionType type, स्थिर अक्षर *desc)
{
    व्योम *dst, *target_obj;
    स्थिर AVOption *o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        वापस AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    अगर (type == AV_OPT_TYPE_PIXEL_FMT)
        *(क्रमागत AVPixelFormat *)out_fmt = *(क्रमागत AVPixelFormat *)dst;
    अन्यथा
        *(क्रमागत AVSampleFormat*)out_fmt = *(क्रमागत AVSampleFormat*)dst;

    वापस 0;
}

पूर्णांक av_opt_get_pixel_fmt(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, क्रमागत AVPixelFormat *out_fmt)
{
    वापस get_format(obj, name, खोज_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

पूर्णांक av_opt_get_sample_fmt(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, क्रमागत AVSampleFormat *out_fmt)
{
    वापस get_format(obj, name, खोज_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

पूर्णांक av_opt_get_chlayout(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, AVChannelLayout *cl)
{
    व्योम *dst, *target_obj;
    स्थिर AVOption *o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        वापस AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    वापस av_channel_layout_copy(cl, dst);
}

पूर्णांक av_opt_get_dict_val(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags, AVDictionary **out_val)
{
    व्योम *target_obj;
    AVDictionary *src;
    स्थिर AVOption *o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);

    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (o->type != AV_OPT_TYPE_DICT)
        वापस AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    वापस av_dict_copy(out_val, src, 0);
}

पूर्णांक av_opt_flag_is_set(व्योम *obj, स्थिर अक्षर *field_name, स्थिर अक्षर *flag_name)
{
    स्थिर AVOption *field = av_opt_find(obj, field_name, शून्य, 0, 0);
    स्थिर AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : शून्य, 0, 0);
    int64_t res;

    अगर (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        वापस 0;
    वापस res & flag->default_val.i64;
}

अटल व्योम log_int_मूल्य(व्योम *av_log_obj, पूर्णांक level, int64_t i)
{
    अगर (i == पूर्णांक_उच्च) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा अगर (i == पूर्णांक_न्यून) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा अगर (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा अगर (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा अगर (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

अटल व्योम log_मूल्य(व्योम *av_log_obj, पूर्णांक level, द्विगुन d)
{
    अगर      (d == पूर्णांक_उच्च) {
        av_log(av_log_obj, level, "INT_MAX");
    } अन्यथा अगर (d == पूर्णांक_न्यून) {
        av_log(av_log_obj, level, "INT_MIN");
    } अन्यथा अगर (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } अन्यथा अगर (d == (द्विगुन)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } अन्यथा अगर (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } अन्यथा अगर (d == भग्न_उच्च) {
        av_log(av_log_obj, level, "FLT_MAX");
    } अन्यथा अगर (d == भग्न_न्यून) {
        av_log(av_log_obj, level, "FLT_MIN");
    } अन्यथा अगर (d == -भग्न_उच्च) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } अन्यथा अगर (d == -भग्न_न्यून) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } अन्यथा अगर (d == द्विग_उच्च) {
        av_log(av_log_obj, level, "DBL_MAX");
    } अन्यथा अगर (d == द्विग_न्यून) {
        av_log(av_log_obj, level, "DBL_MIN");
    } अन्यथा अगर (d == -द्विग_उच्च) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } अन्यथा अगर (d == -द्विग_न्यून) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } अन्यथा {
        av_log(av_log_obj, level, "%g", d);
    }
}

अटल स्थिर अक्षर *get_opt_const_name(व्योम *obj, स्थिर अक्षर *unit, int64_t मूल्य)
{
    स्थिर AVOption *opt = शून्य;

    अगर (!unit)
        वापस शून्य;
    जबतक ((opt = av_opt_अग्र(obj, opt)))
        अगर (opt->type == AV_OPT_TYPE_CONST && !म_भेद(opt->unit, unit) &&
            opt->default_val.i64 == मूल्य)
            वापस opt->name;
    वापस शून्य;
}

अटल अक्षर *get_opt_flags_string(व्योम *obj, स्थिर अक्षर *unit, int64_t मूल्य)
{
    स्थिर AVOption *opt = शून्य;
    अक्षर flags[512];

    flags[0] = 0;
    अगर (!unit)
        वापस शून्य;
    जबतक ((opt = av_opt_अग्र(obj, opt))) {
        अगर (opt->type == AV_OPT_TYPE_CONST && !म_भेद(opt->unit, unit) &&
            opt->default_val.i64 & मूल्य) {
            अगर (flags[0])
                av_strlcatf(flags, माप(flags), "+");
            av_strlcatf(flags, माप(flags), "%s", opt->name);
        }
    }
    अगर (flags[0])
        वापस av_strdup(flags);
    वापस शून्य;
}

अटल व्योम log_type(व्योम *av_log_obj, स्थिर AVOption *o,
                     क्रमागत AVOptionType parent_type)
{
    स्थिर क्रमागत AVOptionType type = TYPE_BASE(o->type);

    अगर (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    अन्यथा अगर (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        अगर (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        अन्यथा
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    अन्यथा
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

अटल व्योम log_default(व्योम *obj, व्योम *av_log_obj, स्थिर AVOption *opt)
{
    अगर (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_द्विआधारी)
        वापस;
    अगर ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_आकार ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        वापस;

    अगर (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        स्थिर AVOptionArrayDef *arr = opt->default_val.arr;
        अगर (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        वापस;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    चयन (opt->type) {
    हाल AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        अवरोध;
    हाल AV_OPT_TYPE_FLAGS: {
        अक्षर *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        अगर (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } अन्यथा {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        अवरोध;
    }
    हाल AV_OPT_TYPE_DURATION: {
        अक्षर buf[25];
        format_duration(buf, माप(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        अवरोध;
    }
    हाल AV_OPT_TYPE_UINT:
    हाल AV_OPT_TYPE_INT:
    हाल AV_OPT_TYPE_UINT64:
    हाल AV_OPT_TYPE_INT64: {
        स्थिर अक्षर *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        अगर (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        अन्यथा
            log_int_मूल्य(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        अवरोध;
    }
    हाल AV_OPT_TYPE_DOUBLE:
    हाल AV_OPT_TYPE_FLOAT:
        log_मूल्य(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        अवरोध;
    हाल AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, पूर्णांक_उच्च);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.अंक, q.den); }
        अवरोध;
    हाल AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (अक्षर *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        अवरोध;
    हाल AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (अक्षर *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        अवरोध;
    हाल AV_OPT_TYPE_COLOR:
    हाल AV_OPT_TYPE_IMAGE_आकार:
    हाल AV_OPT_TYPE_STRING:
    हाल AV_OPT_TYPE_DICT:
    हाल AV_OPT_TYPE_VIDEO_RATE:
    हाल AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        अवरोध;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

अटल व्योम opt_list(व्योम *obj, व्योम *av_log_obj, स्थिर अक्षर *unit,
                     पूर्णांक req_flags, पूर्णांक rej_flags, क्रमागत AVOptionType parent_type)
{
    स्थिर AVOption *opt = शून्य;
    AVOptionRanges *r;
    पूर्णांक i;

    जबतक ((opt = av_opt_अग्र(obj, opt))) {
        अगर (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            जारी;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        अगर (!unit && opt->type == AV_OPT_TYPE_CONST)
            जारी;
        अन्यथा अगर (unit && opt->type != AV_OPT_TYPE_CONST)
            जारी;
        अन्यथा अगर (unit && opt->type == AV_OPT_TYPE_CONST && म_भेद(unit, opt->unit))
            जारी;
        अन्यथा अगर (unit && opt->type == AV_OPT_TYPE_CONST)
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

        अगर (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        अगर (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_खोज_FAKE_OBJ) >= 0) {
            चयन (opt->type) {
            हाल AV_OPT_TYPE_INT:
            हाल AV_OPT_TYPE_UINT:
            हाल AV_OPT_TYPE_INT64:
            हाल AV_OPT_TYPE_UINT64:
            हाल AV_OPT_TYPE_DOUBLE:
            हाल AV_OPT_TYPE_FLOAT:
            हाल AV_OPT_TYPE_RATIONAL:
                क्रम (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_मूल्य(av_log_obj, AV_LOG_INFO, r->range[i]->मूल्य_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_मूल्य(av_log_obj, AV_LOG_INFO, r->range[i]->मूल्य_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                अवरोध;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        अगर (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

पूर्णांक av_opt_show2(व्योम *obj, व्योम *av_log_obj, पूर्णांक req_flags, पूर्णांक rej_flags)
{
    अगर (!obj)
        वापस -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, शून्य, req_flags, rej_flags, -1);

    वापस 0;
}

व्योम av_opt_set_defaults(व्योम *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

व्योम av_opt_set_defaults2(व्योम *s, पूर्णांक mask, पूर्णांक flags)
{
    स्थिर AVOption *opt = शून्य;
    जबतक ((opt = av_opt_अग्र(s, opt))) {
        व्योम *dst = ((uint8_t*)s) + opt->offset;

        अगर ((opt->flags & mask) != flags)
            जारी;

        अगर (opt->flags & AV_OPT_FLAG_READONLY)
            जारी;

        अगर (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            स्थिर AVOptionArrayDef *arr = opt->default_val.arr;
            स्थिर अक्षर              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            अगर (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            जारी;
        }

        चयन (opt->type) {
            हाल AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                अवरोध;
            हाल AV_OPT_TYPE_BOOL:
            हाल AV_OPT_TYPE_FLAGS:
            हाल AV_OPT_TYPE_INT:
            हाल AV_OPT_TYPE_UINT:
            हाल AV_OPT_TYPE_INT64:
            हाल AV_OPT_TYPE_UINT64:
            हाल AV_OPT_TYPE_DURATION:
            हाल AV_OPT_TYPE_PIXEL_FMT:
            हाल AV_OPT_TYPE_SAMPLE_FMT:
                write_संख्या(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                अवरोध;
            हाल AV_OPT_TYPE_DOUBLE:
            हाल AV_OPT_TYPE_FLOAT: {
                द्विगुन val;
                val = opt->default_val.dbl;
                write_संख्या(s, opt, dst, val, 1, 1, 1);
            }
            अवरोध;
            हाल AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, पूर्णांक_उच्च);
                write_संख्या(s, opt, dst, 1, val.den, val.अंक, 1);
            }
            अवरोध;
            हाल AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                अवरोध;
            हाल AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                अवरोध;
            हाल AV_OPT_TYPE_IMAGE_आकार:
                set_string_image_आकार(s, opt, opt->default_val.str, dst);
                अवरोध;
            हाल AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                अवरोध;
            हाल AV_OPT_TYPE_द्विआधारी:
                set_string_द्विआधारी(s, opt, opt->default_val.str, dst);
                अवरोध;
            हाल AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                अवरोध;
            हाल AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                अवरोध;
        शेष:
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
अटल पूर्णांक parse_कुंजी_मूल्य_pair(व्योम *ctx, स्थिर अक्षर **buf,
                                स्थिर अक्षर *कुंजी_val_sep, स्थिर अक्षर *pairs_sep)
{
    अक्षर *कुंजी = av_get_token(buf, कुंजी_val_sep);
    अक्षर *val;
    पूर्णांक ret;

    अगर (!कुंजी)
        वापस AVERROR(ENOMEM);

    अगर (*कुंजी && म_अखोज(*buf, कुंजी_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        अगर (!val) {
            av_freep(&कुंजी);
            वापस AVERROR(ENOMEM);
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", कुंजी);
        av_free(कुंजी);
        वापस AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", कुंजी, val);

    ret = av_opt_set(ctx, कुंजी, val, AV_OPT_खोज_CHILDREN);
    अगर (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", कुंजी);

    av_free(कुंजी);
    av_free(val);
    वापस ret;
}

पूर्णांक av_set_options_string(व्योम *ctx, स्थिर अक्षर *opts,
                          स्थिर अक्षर *कुंजी_val_sep, स्थिर अक्षर *pairs_sep)
{
    पूर्णांक ret, गिनती = 0;

    अगर (!opts)
        वापस 0;

    जबतक (*opts) {
        अगर ((ret = parse_कुंजी_मूल्य_pair(ctx, &opts, कुंजी_val_sep, pairs_sep)) < 0)
            वापस ret;
        गिनती++;

        अगर (*opts)
            opts++;
    }

    वापस गिनती;
}

#घोषणा WHITESPACES " \n\t\r"

अटल पूर्णांक is_कुंजी_char(अक्षर c)
{
    वापस (अचिन्हित)((c | 32) - 'a') < 26 ||
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
अटल पूर्णांक get_कुंजी(स्थिर अक्षर **ropts, स्थिर अक्षर *delim, अक्षर **rkey)
{
    स्थिर अक्षर *opts = *ropts;
    स्थिर अक्षर *कुंजी_start, *कुंजी_end;

    कुंजी_start = opts += म_अखोज(opts, WHITESPACES);
    जबतक (is_कुंजी_char(*opts))
        opts++;
    कुंजी_end = opts;
    opts += म_अखोज(opts, WHITESPACES);
    अगर (!*opts || !म_अक्षर(delim, *opts))
        वापस AVERROR(EINVAL);
    opts++;
    अगर (!(*rkey = av_malloc(कुंजी_end - कुंजी_start + 1)))
        वापस AVERROR(ENOMEM);
    स_नकल(*rkey, कुंजी_start, कुंजी_end - कुंजी_start);
    (*rkey)[कुंजी_end - कुंजी_start] = 0;
    *ropts = opts;
    वापस 0;
}

पूर्णांक av_opt_get_कुंजी_मूल्य(स्थिर अक्षर **ropts,
                         स्थिर अक्षर *कुंजी_val_sep, स्थिर अक्षर *pairs_sep,
                         अचिन्हित flags,
                         अक्षर **rkey, अक्षर **rval)
{
    पूर्णांक ret;
    अक्षर *कुंजी = शून्य, *val;
    स्थिर अक्षर *opts = *ropts;

    अगर ((ret = get_कुंजी(&opts, कुंजी_val_sep, &कुंजी)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_कुंजी))
        वापस AVERROR(EINVAL);
    अगर (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(कुंजी);
        वापस AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = कुंजी;
    *rval  = val;
    वापस 0;
}

पूर्णांक av_opt_set_from_string(व्योम *ctx, स्थिर अक्षर *opts,
                           स्थिर अक्षर *स्थिर *shorthand,
                           स्थिर अक्षर *कुंजी_val_sep, स्थिर अक्षर *pairs_sep)
{
    पूर्णांक ret, गिनती = 0;
    स्थिर अक्षर *dummy_shorthand = शून्य;
    स्थिर अक्षर *कुंजी;

    अगर (!opts)
        वापस 0;
    अगर (!shorthand)
        shorthand = &dummy_shorthand;

    जबतक (*opts) {
        अक्षर *parsed_कुंजी, *मूल्य;
        ret = av_opt_get_कुंजी_मूल्य(&opts, कुंजी_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_कुंजी : 0,
                                   &parsed_कुंजी, &मूल्य);
        अगर (ret < 0) {
            अगर (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            अन्यथा
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            वापस ret;
        }
        अगर (*opts)
            opts++;
        अगर (parsed_कुंजी) {
            कुंजी = parsed_कुंजी;
            जबतक (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } अन्यथा {
            कुंजी = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", कुंजी, मूल्य);
        अगर ((ret = av_opt_set(ctx, कुंजी, मूल्य, 0)) < 0) {
            अगर (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", कुंजी);
            av_free(मूल्य);
            av_free(parsed_कुंजी);
            वापस ret;
        }

        av_free(मूल्य);
        av_free(parsed_कुंजी);
        गिनती++;
    }
    वापस गिनती;
}

व्योम av_opt_free(व्योम *obj)
{
    स्थिर AVOption *o = शून्य;
    जबतक ((o = av_opt_अग्र(obj, o))) {
        व्योम *pitem = (uint8_t *)obj + o->offset;

        अगर (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        अन्यथा
            opt_free_elem(o->type, pitem);
    }
}

पूर्णांक av_opt_set_dict2(व्योम *obj, AVDictionary **options, पूर्णांक खोज_flags)
{
    स्थिर AVDictionaryEntry *t = शून्य;
    AVDictionary    *tmp = शून्य;
    पूर्णांक ret;

    अगर (!options)
        वापस 0;

    जबतक ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->कुंजी, t->मूल्य, खोज_flags);
        अगर (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->कुंजी, t->मूल्य, AV_DICT_MULTIKEY);
        अगर (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->कुंजी, t->मूल्य);
            av_dict_free(&tmp);
            वापस ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    वापस 0;
}

पूर्णांक av_opt_set_dict(व्योम *obj, AVDictionary **options)
{
    वापस av_opt_set_dict2(obj, options, 0);
}

स्थिर AVOption *av_opt_find(व्योम *obj, स्थिर अक्षर *name, स्थिर अक्षर *unit,
                            पूर्णांक opt_flags, पूर्णांक खोज_flags)
{
    वापस av_opt_find2(obj, name, unit, opt_flags, खोज_flags, शून्य);
}

स्थिर AVOption *av_opt_find2(व्योम *obj, स्थिर अक्षर *name, स्थिर अक्षर *unit,
                             पूर्णांक opt_flags, पूर्णांक खोज_flags, व्योम **target_obj)
{
    स्थिर AVClass  *c;
    स्थिर AVOption *o = शून्य;

    अगर(!obj)
        वापस शून्य;

    c= *(AVClass**)obj;

    अगर (!c)
        वापस शून्य;

    अगर (खोज_flags & AV_OPT_खोज_CHILDREN) {
        अगर (खोज_flags & AV_OPT_खोज_FAKE_OBJ) {
            व्योम *iter = शून्य;
            स्थिर AVClass *child;
            जबतक (child = av_opt_child_class_iterate(c, &iter))
                अगर (o = av_opt_find2(&child, name, unit, opt_flags, खोज_flags, शून्य))
                    वापस o;
        } अन्यथा {
            व्योम *child = शून्य;
            जबतक (child = av_opt_child_अग्र(obj, child))
                अगर (o = av_opt_find2(child, name, unit, opt_flags, खोज_flags, target_obj))
                    वापस o;
        }
    }

    जबतक (o = av_opt_अग्र(obj, o)) {
        अगर (!म_भेद(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !म_भेद(o->unit, unit)))) {
            अगर (target_obj) {
                अगर (!(खोज_flags & AV_OPT_खोज_FAKE_OBJ))
                    *target_obj = obj;
                अन्यथा
                    *target_obj = शून्य;
            }
            वापस o;
        }
    }
    वापस शून्य;
}

व्योम *av_opt_child_अग्र(व्योम *obj, व्योम *पूर्व)
{
    स्थिर AVClass *c = *(AVClass **)obj;
    अगर (c->child_अग्र)
        वापस c->child_अग्र(obj, पूर्व);
    वापस शून्य;
}

स्थिर AVClass *av_opt_child_class_iterate(स्थिर AVClass *parent, व्योम **iter)
{
    अगर (parent->child_class_iterate)
        वापस parent->child_class_iterate(iter);
    वापस शून्य;
}

अटल पूर्णांक opt_copy_elem(व्योम *logctx, क्रमागत AVOptionType type,
                         व्योम *dst, स्थिर व्योम *src)
{
    अगर (type == AV_OPT_TYPE_STRING) {
        स्थिर अक्षर *src_str = *(स्थिर अक्षर *स्थिर *)src;
        अक्षर         **dstp =  (अक्षर **)dst;
        अगर (*dstp != src_str)
            av_freep(dstp);
        अगर (src_str) {
            *dstp = av_strdup(src_str);
            अगर (!*dstp)
                वापस AVERROR(ENOMEM);
        }
    } अन्यथा अगर (type == AV_OPT_TYPE_द्विआधारी) {
        स्थिर uint8_t *स्थिर *src8 = (स्थिर uint8_t *स्थिर *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        पूर्णांक len = *(स्थिर पूर्णांक *)(src8 + 1);
        अगर (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        अगर (len && !*dst8) {
            *(पूर्णांक *)(dst8 + 1) = 0;
            वापस AVERROR(ENOMEM);
        }
        *(पूर्णांक *)(dst8 + 1) = len;
    } अन्यथा अगर (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } अन्यथा अगर (type == AV_OPT_TYPE_DICT) {
        स्थिर AVDictionary *sdict = *(स्थिर AVDictionary * स्थिर *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        अगर (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = शून्य;
        वापस av_dict_copy(ddictp, sdict, 0);
    } अन्यथा अगर (type == AV_OPT_TYPE_CHLAYOUT) {
        स्थिर AVChannelLayout *slayout = (स्थिर AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        अगर (dlayout != slayout) {
            अगर (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = शून्य;
            वापस av_channel_layout_copy(dst, src);
        }
    } अन्यथा अगर (opt_is_pod(type)) {
        माप_प्रकार आकार = opt_type_desc[type].आकार;
        स_नकल(dst, src, आकार);
    } अन्यथा {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        वापस AVERROR(EINVAL);
    }

    वापस 0;
}

अटल पूर्णांक opt_copy_array(व्योम *logctx, स्थिर AVOption *o,
                          व्योम **pdst, स्थिर व्योम * स्थिर *psrc)
{
    अचिन्हित nb_elems = *opt_array_pcount(psrc);
    व्योम         *dst = शून्य;
    पूर्णांक ret;

    अगर (*pdst == *psrc) {
        *pdst                   = शून्य;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].आकार);
    अगर (!dst)
        वापस AVERROR(ENOMEM);

    क्रम (अचिन्हित i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(व्योम**)psrc, i));
        अगर (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            वापस ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    वापस 0;
}

पूर्णांक av_opt_copy(व्योम *dst, स्थिर व्योम *src)
{
    स्थिर AVOption *o = शून्य;
    स्थिर AVClass *c;
    पूर्णांक ret = 0;

    अगर (!src)
        वापस AVERROR(EINVAL);

    c = *(AVClass **)src;
    अगर (!c || c != *(AVClass **)dst)
        वापस AVERROR(EINVAL);

    जबतक ((o = av_opt_अग्र(src, o))) {
        व्योम *field_dst = (uint8_t *)dst + o->offset;
        व्योम *field_src = (uint8_t *)src + o->offset;

        पूर्णांक err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        अगर (err < 0)
            ret = err;
    }
    वापस ret;
}

पूर्णांक av_opt_get_array_आकार(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags,
                          अचिन्हित पूर्णांक *out_val)
{
    व्योम *target_obj, *parray;
    स्थिर AVOption *o;

    o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        वापस AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    वापस 0;
}

पूर्णांक av_opt_get_array(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags,
                     अचिन्हित पूर्णांक start_elem, अचिन्हित पूर्णांक nb_elems,
                     क्रमागत AVOptionType out_type, व्योम *out_val)
{
    स्थिर माप_प्रकार elem_आकार_out = opt_type_desc[TYPE_BASE(out_type)].आकार;

    स्थिर AVOption *o;
    व्योम *target_obj;

    स्थिर व्योम *parray;
    अचिन्हित array_आकार;

    पूर्णांक ret;

    o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target_obj);
    अगर (!o || !target_obj)
        वापस AVERROR_OPTION_NOT_FOUND;
    अगर (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        वापस AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_आकार = *opt_array_pcount(parray);

    अगर (start_elem >= array_आकार ||
        array_आकार - start_elem < nb_elems)
        वापस AVERROR(EINVAL);

    क्रम (अचिन्हित i = 0; i < nb_elems; i++) {
        स्थिर व्योम *src = opt_array_pelem(o, *(व्योम**)parray, start_elem + i);
        व्योम       *dst = (uint8_t*)out_val + i * elem_आकार_out;

        अगर (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            अगर (ret < 0)
                जाओ fail;
        } अन्यथा अगर (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, माप(buf), src, खोज_flags);
            अगर (ret < 0)
                जाओ fail;

            अगर (out == buf) {
                out = av_strdup(buf);
                अगर (!out) {
                    ret = AVERROR(ENOMEM);
                    जाओ fail;
                }
            }

            *(uint8_t**)dst = out;
        } अन्यथा अगर (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            द्विगुन     अंक = 1.0;
            पूर्णांक        den = 1;
            int64_t intnum = 1;

            ret = read_संख्या(o, src, &अंक, &den, &intnum);
            अगर (ret < 0)
                जाओ fail;

            चयन (out_type) {
            हाल AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (अंक == den) ?  intnum : अंक * intnum / den;
                अवरोध;
            हाल AV_OPT_TYPE_DOUBLE:
                *(द्विगुन*)dst = अंक * intnum / den;
                अवरोध;
            हाल AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (अंक == 1.0 && (पूर्णांक)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(अंक * intnum / den);
                अवरोध;
            शेष: av_assert0(0);
            }
        } अन्यथा
            वापस AVERROR(ENOSYS);
    }

    वापस 0;
fail:
    क्रम (अचिन्हित i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_आकार_out);
    वापस ret;
}

पूर्णांक av_opt_set_array(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags,
                     अचिन्हित पूर्णांक start_elem, अचिन्हित पूर्णांक nb_elems,
                     क्रमागत AVOptionType val_type, स्थिर व्योम *val)
{
    स्थिर माप_प्रकार elem_आकार_val = opt_type_desc[TYPE_BASE(val_type)].आकार;

    स्थिर AVOption *o;
    स्थिर AVOptionArrayDef *arr;
    व्योम *target_obj;

    व्योम *parray;
    व्योम *new_elems;
    अचिन्हित *array_आकार, new_आकार;
    माप_प्रकार elem_आकार;

    पूर्णांक ret = 0;

    ret = opt_set_init(obj, name, खोज_flags, 0, &target_obj, &o, &parray);
    अगर (ret < 0)
        वापस ret;

    अगर (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        वापस AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_आकार = opt_array_pcount(parray);
    elem_आकार  = opt_type_desc[TYPE_BASE(o->type)].आकार;

    अगर (start_elem > *array_आकार)
        वापस AVERROR(EINVAL);

    // compute new array size
    अगर (!val) {
        अगर (*array_आकार - start_elem < nb_elems)
            वापस AVERROR(EINVAL);

        new_आकार = *array_आकार - nb_elems;
    } अन्यथा अगर (खोज_flags & AV_OPT_ARRAY_REPLACE) {
        अगर (start_elem >= अच_पूर्णांक_उच्च - nb_elems)
            वापस AVERROR(EINVAL);

        new_आकार = FFMAX(*array_आकार, start_elem + nb_elems);
    } अन्यथा {
        अगर (nb_elems >= अच_पूर्णांक_उच्च - *array_आकार)
            वापस AVERROR(EINVAL);

        new_आकार = *array_आकार + nb_elems;
    }

    अगर (arr &&
        ((arr->आकार_max && new_आकार > arr->आकार_max) ||
         (arr->आकार_min && new_आकार < arr->आकार_min)))
        वापस AVERROR(EINVAL);

    // desired operation is shrinking the array
    अगर (!val) {
        व्योम *array = *(व्योम**)parray;

        क्रम (अचिन्हित i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        अगर (new_आकार > 0) {
            स_हटाओ(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_आकार * (*array_आकार - start_elem - nb_elems));

            array = av_realloc_array(array, new_आकार, elem_आकार);
            अगर (!array)
                वापस AVERROR(ENOMEM);

            *(व्योम**)parray = array;
        } अन्यथा
            av_freep(parray);

        *array_आकार = new_आकार;

        वापस 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_आकार);
    अगर (!new_elems)
        वापस AVERROR(ENOMEM);

    // convert/validate each new element
    क्रम (अचिन्हित i = 0; i < nb_elems; i++) {
        व्योम       *dst = opt_array_pelem(o, new_elems, i);
        स्थिर व्योम *src = (uint8_t*)val + i * elem_आकार_val;

        द्विगुन     अंक = 1.0;
        पूर्णांक        den = 1;
        int64_t intnum = 1;

        अगर (val_type == TYPE_BASE(o->type)) {
            पूर्णांक err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            अगर (ret < 0)
                जाओ fail;

            // validate the range for numeric options
            err = read_संख्या(o, dst, &अंक, &den, &intnum);
            अगर (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < अंक * intnum || o->min * den > अंक * intnum)) {
                अंक = den ? अंक * intnum / den : (अंक && intnum ? अनन्त : न_अंक);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, अंक, o->min, o->max);
                ret = AVERROR(दुस्फल);
                जाओ fail;
            }
        } अन्यथा अगर (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(स्थिर अक्षर **)src, dst);
            अगर (ret < 0)
                जाओ fail;
        } अन्यथा अगर (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            चयन (val_type) {
            हाल AV_OPT_TYPE_INT:       intnum = *(पूर्णांक*)src;                अवरोध;
            हाल AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            अवरोध;
            हाल AV_OPT_TYPE_FLOAT:     अंक    = *(भग्न*)src;              अवरोध;
            हाल AV_OPT_TYPE_DOUBLE:    अंक    = *(द्विगुन*)src;             अवरोध;
            हाल AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->अंक;
                                        den    = ((AVRational*)src)->den;   अवरोध;
            शेष: av_assert0(0);
            }

            ret = write_संख्या(obj, o, dst, अंक, den, intnum, 0);
            अगर (ret < 0)
                जाओ fail;
        } अन्यथा {
            ret = AVERROR(ENOSYS);
            जाओ fail;
        }
    }

    // commit new elements to the array
    अगर (start_elem == 0 && nb_elems == new_आकार) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_आकार);
        *(व्योम**)parray = new_elems;
        *array_आकार     = nb_elems;

        new_elems = शून्य;
        nb_elems  = 0;
    } अन्यथा {
        व्योम *array = av_realloc_array(*(व्योम**)parray, new_आकार, elem_आकार);
        अगर (!array) {
            ret = AVERROR(ENOMEM);
            जाओ fail;
        }

        अगर (खोज_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            क्रम (अचिन्हित i = start_elem; i < FFMIN(start_elem + nb_elems, *array_आकार); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } अन्यथा {
            // shift existing elements to the end
            स_हटाओ(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_आकार * (*array_आकार - start_elem));
        }

        स_नकल((uint8_t*)array + elem_आकार * start_elem, new_elems, elem_आकार * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(व्योम**)parray = array;
        *array_आकार     = new_आकार;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    वापस ret;
}

पूर्णांक av_opt_query_ranges(AVOptionRanges **ranges_arg, व्योम *obj, स्थिर अक्षर *कुंजी, पूर्णांक flags)
{
    पूर्णांक ret;
    स्थिर AVClass *c = *(AVClass**)obj;
    पूर्णांक (*callback)(AVOptionRanges **, व्योम *obj, स्थिर अक्षर *कुंजी, पूर्णांक flags) = c->query_ranges;

    अगर (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, कुंजी, flags);
    अगर (ret >= 0) {
        अगर (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    वापस ret;
}

पूर्णांक av_opt_query_ranges_default(AVOptionRanges **ranges_arg, व्योम *obj, स्थिर अक्षर *कुंजी, पूर्णांक flags)
{
    AVOptionRanges *ranges = av_mallocz(माप(*ranges));
    AVOptionRange **range_array = av_mallocz(माप(व्योम*));
    AVOptionRange *range = av_mallocz(माप(*range));
    स्थिर AVOption *field = av_opt_find(obj, कुंजी, शून्य, 0, flags);
    पूर्णांक ret;

    *ranges_arg = शून्य;

    अगर (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->मूल्य_min = field->min;
    range->मूल्य_max = field->max;

    चयन (field->type) {
    हाल AV_OPT_TYPE_BOOL:
    हाल AV_OPT_TYPE_INT:
    हाल AV_OPT_TYPE_UINT:
    हाल AV_OPT_TYPE_INT64:
    हाल AV_OPT_TYPE_UINT64:
    हाल AV_OPT_TYPE_PIXEL_FMT:
    हाल AV_OPT_TYPE_SAMPLE_FMT:
    हाल AV_OPT_TYPE_FLOAT:
    हाल AV_OPT_TYPE_DOUBLE:
    हाल AV_OPT_TYPE_DURATION:
    हाल AV_OPT_TYPE_COLOR:
        अवरोध;
    हाल AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->मूल्य_min = -1;
        range->मूल्य_max = पूर्णांक_उच्च;
        अवरोध;
    हाल AV_OPT_TYPE_RATIONAL:
        range->component_min = पूर्णांक_न्यून;
        range->component_max = पूर्णांक_उच्च;
        अवरोध;
    हाल AV_OPT_TYPE_IMAGE_आकार:
        range->component_min = 0;
        range->component_max = पूर्णांक_उच्च/128/8;
        range->मूल्य_min = 0;
        range->मूल्य_max = पूर्णांक_उच्च/8;
        अवरोध;
    हाल AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = पूर्णांक_उच्च;
        range->मूल्य_min = 1;
        range->मूल्य_max = पूर्णांक_उच्च;
        अवरोध;
    शेष:
        ret = AVERROR(ENOSYS);
        जाओ fail;
    }

    *ranges_arg = ranges;
    वापस 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    वापस ret;
}

व्योम av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    पूर्णांक i;
    AVOptionRanges *ranges = *rangesp;

    अगर (!ranges)
        वापस;

    क्रम (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        अगर (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

पूर्णांक av_opt_is_set_to_default(व्योम *obj, स्थिर AVOption *o)
{
    int64_t i64;
    द्विगुन d;
    AVRational q;
    पूर्णांक ret, w, h;
    अक्षर *str;
    व्योम *dst;

    अगर (!o || !obj)
        वापस AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    अगर (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        स्थिर अक्षर *def = o->default_val.arr ? o->default_val.arr->def : शून्य;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        अगर (ret < 0)
            वापस ret;

        अगर (!!val != !!def)
            ret = 0;
        अन्यथा अगर (val)
            ret = !म_भेद(val, def);
        अन्यथा
            ret = 1;

        av_freep(&val);

        वापस ret;
    }

    चयन (o->type) {
    हाल AV_OPT_TYPE_CONST:
        वापस 1;
    हाल AV_OPT_TYPE_BOOL:
    हाल AV_OPT_TYPE_FLAGS:
    हाल AV_OPT_TYPE_PIXEL_FMT:
    हाल AV_OPT_TYPE_SAMPLE_FMT:
    हाल AV_OPT_TYPE_INT:
    हाल AV_OPT_TYPE_UINT:
    हाल AV_OPT_TYPE_DURATION:
    हाल AV_OPT_TYPE_INT64:
    हाल AV_OPT_TYPE_UINT64:
        read_संख्या(o, dst, शून्य, शून्य, &i64);
        वापस o->default_val.i64 == i64;
    हाल AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        अगर (o->default_val.str) {
            अगर ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                वापस ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        वापस ret;
    }
    हाल AV_OPT_TYPE_STRING:
        str = *(अक्षर **)dst;
        अगर (str == o->default_val.str) //2 NULLs
            वापस 1;
        अगर (!str || !o->default_val.str) //1 NULL
            वापस 0;
        वापस !म_भेद(str, o->default_val.str);
    हाल AV_OPT_TYPE_DOUBLE:
        d = *(द्विगुन *)dst;
        वापस o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    हाल AV_OPT_TYPE_FLOAT:
        d = *(भग्न *)dst;
        वापस (भग्न)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    हाल AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, पूर्णांक_उच्च);
        वापस !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    हाल AV_OPT_TYPE_द्विआधारी: {
        काष्ठा {
            uint8_t *तथ्य;
            पूर्णांक आकार;
        } tmp = {0};
        पूर्णांक opt_आकार = *(पूर्णांक *)((व्योम **)dst + 1);
        व्योम *opt_ptr = *(व्योम **)dst;
        अगर (!opt_आकार && (!o->default_val.str || !म_माप(o->default_val.str)))
            वापस 1;
        अगर (!opt_आकार ||  !o->default_val.str || !म_माप(o->default_val.str ))
            वापस 0;
        अगर (opt_आकार != म_माप(o->default_val.str) / 2)
            वापस 0;
        ret = set_string_द्विआधारी(शून्य, शून्य, o->default_val.str, &tmp.तथ्य);
        अगर (!ret)
            ret = !स_भेद(opt_ptr, tmp.तथ्य, tmp.आकार);
        av_free(tmp.तथ्य);
        वापस ret;
    }
    हाल AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = शून्य;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        स्थिर AVDictionaryEntry *en1 = शून्य;
        स्थिर AVDictionaryEntry *en2 = शून्य;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        अगर (ret < 0) {
            av_dict_free(&dict1);
            वापस ret;
        }
        करो {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } जबतक (en1 && en2 && !म_भेद(en1->कुंजी, en2->कुंजी) && !म_भेद(en1->मूल्य, en2->मूल्य));
        av_dict_free(&dict1);
        वापस (!en1 && !en2);
    }
    हाल AV_OPT_TYPE_IMAGE_आकार:
        अगर (!o->default_val.str || !म_भेद(o->default_val.str, "none"))
            w = h = 0;
        अन्यथा अगर ((ret = av_parse_video_आकार(&w, &h, o->default_val.str)) < 0)
            वापस ret;
        वापस (w == *(पूर्णांक *)dst) && (h == *((पूर्णांक *)dst+1));
    हाल AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        अगर (o->default_val.str) {
            अगर ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                वापस ret;
        }
        वापस !av_cmp_q(*(AVRational*)dst, q);
    हाल AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        अगर (o->default_val.str) {
            अगर ((ret = av_parse_color(color, o->default_val.str, -1, शून्य)) < 0)
                वापस ret;
        }
        वापस !स_भेद(color, dst, माप(color));
    }
    शेष:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        अवरोध;
    }
    वापस AVERROR_PATCHWELCOME;
}

पूर्णांक av_opt_is_set_to_default_by_name(व्योम *obj, स्थिर अक्षर *name, पूर्णांक खोज_flags)
{
    स्थिर AVOption *o;
    व्योम *target;
    अगर (!obj)
        वापस AVERROR(EINVAL);
    o = av_opt_find2(obj, name, शून्य, 0, खोज_flags, &target);
    अगर (!o)
        वापस AVERROR_OPTION_NOT_FOUND;
    वापस av_opt_is_set_to_default(target, o);
}

अटल पूर्णांक opt_serialize(व्योम *obj, पूर्णांक opt_flags, पूर्णांक flags, पूर्णांक *cnt,
                         AVBPrint *bprint, स्थिर अक्षर कुंजी_val_sep, स्थिर अक्षर pairs_sep)
{
    स्थिर AVOption *o = शून्य;
    व्योम *child = शून्य;
    uint8_t *buf;
    पूर्णांक ret;
    स्थिर अक्षर special_chars[] = {pairs_sep, कुंजी_val_sep, '\0'};

    अगर (flags & AV_OPT_SERIALIZE_खोज_CHILDREN)
        जबतक (child = av_opt_child_अग्र(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                कुंजी_val_sep, pairs_sep);
            अगर (ret < 0)
                वापस ret;
        }

    जबतक (o = av_opt_अग्र(obj, o)) {
        अगर (o->type == AV_OPT_TYPE_CONST)
            जारी;
        अगर ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            अगर ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                अगर (o->flags == opt_flags)
                    जारी;
            } अन्यथा अगर ((o->flags & opt_flags) == opt_flags)
                जारी;
        } अन्यथा {
            अगर ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                जारी;
            अन्यथा अगर (((o->flags & opt_flags) != opt_flags))
                जारी;
        }
        अगर (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            जारी;
        अगर ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, शून्य);
            वापस ret;
        }
        अगर (buf) {
            अगर ((*cnt)++)
                av_bprint_append_तथ्य(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_तथ्य(bprint, &कुंजी_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    वापस 0;
}

पूर्णांक av_opt_serialize(व्योम *obj, पूर्णांक opt_flags, पूर्णांक flags, अक्षर **बफर,
                     स्थिर अक्षर कुंजी_val_sep, स्थिर अक्षर pairs_sep)
{
    AVBPrint bprint;
    पूर्णांक ret, cnt = 0;

    अगर (pairs_sep == '\0' || कुंजी_val_sep == '\0' || pairs_sep == कुंजी_val_sep ||
        pairs_sep == '\\' || कुंजी_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        वापस AVERROR(EINVAL);
    }

    अगर (!obj || !बफर)
        वापस AVERROR(EINVAL);

    *बफर = शून्य;
    av_bprint_init(&bprint, 64, AV_BPRINT_आकार_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        कुंजी_val_sep, pairs_sep);
    अगर (ret < 0)
        वापस ret;

    ret = av_bprint_finalize(&bprint, बफर);
    अगर (ret < 0)
        वापस ret;
    वापस 0;
}
