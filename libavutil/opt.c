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

#ضمن "avutil.h"
#ضمن "avassert.h"
#ضمن "avstring.h"
#ضمن "channel_layout.h"
#ضمن "dict.h"
#ضمن "eval.h"
#ضمن "log.h"
#ضمن "mem.h"
#ضمن "parseutils.h"
#ضمن "pixdesc.h"
#ضمن "mathematics.h"
#ضمن "opt.h"
#ضمن "samplefmt.h"
#ضمن "bprint.h"

#ضمن <float.h>

#تعریف_کرو TYPE_ادھار(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ثابت AVOption *av_opt_اگلا(ثابت فراغ *obj, ثابت AVOption *آخری)
{
    ثابت AVClass *class;
    إذا (!obj)
        أرجع عدم;
    class = *(ثابت AVClass**)obj;
    إذا (!آخری && class && class->option && class->option[0].name)
        أرجع class->option;
    إذا (آخری && آخری[1].name)
        أرجع ++آخری;
    أرجع عدم;
}

ساكن ثابت بنية {
    size_t      ناپ;
    ثابت حرف *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { حجم(بنانشانی),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { حجم(صحيح),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { حجم(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { حجم(بنانشانی),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { حجم(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { حجم(مزدوج),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { حجم(عائم),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { حجم(حرف *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { حجم(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ثنائی]        = { حجم(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { حجم(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_ناپ]    = { حجم(صحيح[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_شرح]    = { حجم(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { حجم(تعداد AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { حجم(تعداد AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { حجم(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { حجم(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { حجم(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { حجم(صحيح),            "<boolean>" },
};

// option is plain old data
ساكن صحيح opt_is_pod(تعداد AVOptionType type)
{
    بدل (type) {
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_RATIONAL:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_IMAGE_ناپ:
    حالة AV_OPT_TYPE_PIXEL_FMT:
    حالة AV_OPT_TYPE_SAMPLE_FMT:
    حالة AV_OPT_TYPE_VIDEO_شرح:
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_COLOR:
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_UINT:
        أرجع 1;
    }
    أرجع 0;
}

ساكن uint8_t opt_array_sep(ثابت AVOption *o)
{
    ثابت AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    أرجع (d && d->sep) ? d->sep : ',';
}

ساكن فراغ *opt_array_pelem(ثابت AVOption *o, فراغ *array, بنانشانی idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    أرجع (uint8_t *)array + idx * opt_type_desc[TYPE_ادھار(o->type)].ناپ;
}

ساكن بنانشانی *opt_array_pcount(ثابت فراغ *parray)
{
    أرجع (بنانشانی *)((ثابت فراغ * ثابت *)parray + 1);
}

ساكن فراغ opt_free_elem(تعداد AVOptionType type, فراغ *ptr)
{
    بدل (TYPE_ادھار(type)) {
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_ثنائی:
        av_freep(ptr);
        اكسر;

    حالة AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        اكسر;

    حالة AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        اكسر;

    افتراضي:
        اكسر;
    }
}

ساكن فراغ opt_free_array(ثابت AVOption *o, فراغ *parray, بنانشانی *گنتی)
{
    لكل (بنانشانی i = 0; i < *گنتی; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(فراغ **)parray, i));

    av_freep(parray);
    *گنتی = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ساكن صحيح opt_سیٹ_init(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags,
                        صحيح require_type,
                        فراغ **ptgt, ثابت AVOption **po, فراغ **pdst)
{
    فراغ *logctx;
    ثابت AVOption *o;
    فراغ *tgt;

    o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &tgt);
    إذا (!o || (!tgt && !(تلاش_flags & AV_OPT_تلاش_FAKE_OBJ)))
        أرجع AVERROR_OPTION_NOT_لبھیا;

    إذا (o->flags & AV_OPT_FLAG_READONLY)
        أرجع AVERROR(EINVAL);

    logctx = tgt ? obj : عدم;

    إذا (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        أرجع AVERROR(EINVAL);
    }

    إذا (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        بنانشانی *state_flags = عدم;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        إذا (class->state_flags_وتھ)
            state_flags = (بنانشانی*)((uint8_t*)tgt + class->state_flags_وتھ);

        إذا (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            إذا (class->state_flags_وتھ)
                state_flags = (بنانشانی*)((uint8_t*)obj + class->state_flags_وتھ);
        }

        إذا (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            أرجع AVERROR(EINVAL);
        }
    }

    إذا (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    إذا (po)
        *po   = o;
    إذا (ptgt)
        *ptgt = tgt;
    إذا (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->وتھ : عدم;

    أرجع 0;
}

ساكن AVRational double_منزل_rational(مزدوج d)
{
     AVRational r = av_d2q(d, 1 << 24);
     إذا ((!r.عدد || !r.den) && d)
         r = av_d2q(d, ودھ_توں_ودھ_عدد);
     أرجع r;
}

ساكن صحيح read_نمبر(ثابت AVOption *o, ثابت فراغ *dst, مزدوج *عدد, صحيح *den, int64_t *intnum)
{
    بدل (TYPE_ادھار(o->type)) {
    حالة AV_OPT_TYPE_FLAGS:
        *intnum = *(بنانشانی صحيح*)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(تعداد AVPixelFormat *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(تعداد AVSampleFormat *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_INT:
        *intnum = *(صحيح *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_UINT:
        *intnum = *(بنانشانی صحيح *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_FLOAT:
        *عدد = *(عائم *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_DOUBLE:
        *عدد = *(مزدوج *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->عدد;
        *den    = ((AVRational *)dst)->den;
        أرجع 0;
    حالة AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        أرجع 0;
    }
    أرجع AVERROR(EINVAL);
}

ساكن صحيح write_نمبر(فراغ *obj, ثابت AVOption *o, فراغ *dst,
                        مزدوج عدد, صحيح den, int64_t intnum,
                        صحيح ignore_range)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_ادھار(o->type);

    إذا (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < عدد * intnum || o->min * den > عدد * intnum)) {
        عدد = den ? عدد * intnum / den : (عدد && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               عدد, o->name, o->min, o->max);
        أرجع AVERROR(ERANGE);
    }
    إذا (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        مزدوج d = عدد*intnum/den;
        إذا (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   عدد*intnum/den, o->name);
            أرجع AVERROR(ERANGE);
        }
    }

    إذا (!dst)
        أرجع 0;

    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *(تعداد AVPixelFormat *)dst = llrint(عدد / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *(تعداد AVSampleFormat *)dst = llrint(عدد / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
        *(صحيح *)dst = llrint(عدد / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:{
        مزدوج d = عدد / den;
        إذا (intnum == 1 && d == (مزدوج)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } وإلا
            *(int64_t *)dst = llrint(d) * intnum;
        اكسر;}
    حالة AV_OPT_TYPE_UINT64:{
        مزدوج d = عدد / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        إذا (intnum == 1 && d == (مزدوج)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } وإلا إذا (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } وإلا {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        اكسر;}
    حالة AV_OPT_TYPE_FLOAT:
        *(عائم *)dst = عدد * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_DOUBLE:
        *(مزدوج    *)dst = عدد * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
    حالة AV_OPT_TYPE_VIDEO_شرح:
        إذا ((صحيح) عدد == عدد)
            *(AVRational *)dst = (AVRational) { عدد *intnum, den };
        وإلا
            *(AVRational *)dst = double_منزل_rational(عدد * intnum / den);
        اكسر;
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
    أرجع 0;
}

ساكن صحيح hexchar2int(حرف c) {
    إذا (c >= '0' && c <= '9')
        أرجع c - '0';
    إذا (c >= 'a' && c <= 'f')
        أرجع c - 'a' + 10;
    إذا (c >= 'A' && c <= 'F')
        أرجع c - 'A' + 10;
    أرجع -1;
}

ساكن صحيح سیٹ_string_ثنائی(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحيح *lendst;
    uint8_t *bin, *ptr;
    صحيح len;

    إذا (dst) {
        lendst = (صحيح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    إذا (!val || !(len = لڑی_لمبائی(val)))
        أرجع 0;

    إذا (len & 1)
        أرجع AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    إذا (!ptr)
        أرجع AVERROR(ENOMEM);
    طالما (*val) {
        صحيح a = hexchar2int(*val++);
        صحيح b = hexchar2int(*val++);
        إذا (a < 0 || b < 0) {
            av_free(bin);
            أرجع AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    إذا (dst) {
        *dst    = bin;
        *lendst = len;
    } وإلا {
        av_free(bin);
    }

    أرجع 0;
}

ساكن صحيح سیٹ_string(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    إذا (!dst)
        أرجع 0;
    av_freep(dst);
    إذا (!val)
        أرجع 0;
    *dst = av_strdup(val);
    أرجع *dst ? 0 : AVERROR(ENOMEM);
}

#تعریف_کرو DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ساكن صحيح سیٹ_string_نمبر(فراغ *obj, فراغ *نشانہ_obj, ثابت AVOption *o, ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_ادھار(o->type);
    صحيح ret = 0;

    إذا (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_شرح) {
        صحيح عدد, den;
        حرف c;
        إذا (لڑی_توں_پڑھو(val, "%d%*1[:/]%d%c", &عدد, &den, &c) == 2) {
            إذا ((ret = write_نمبر(obj, o, dst, 1, den, عدد, 0)) >= 0)
                أرجع ret;
            ret = 0;
        }
    }

    لكل (;;) {
        صحيح i = 0;
        حرف buf[256];
        صحيح cmd = 0;
        مزدوج d;
        int64_t intnum = 1;

        إذا (type == AV_OPT_TYPE_FLAGS) {
            إذا (*val == '+' || *val == '-')
                cmd = *(val++);
            لكل (; i < حجم(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            صحيح res;
            صحيح ci = 0;
            مزدوج const_اقدار[64];
            ثابت حرف * const_ناں[64];
            صحيح تلاش_flags = (o->flags & AV_OPT_FLAG_بچہ_CONSTS) ? AV_OPT_تلاش_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_لبھو(نشانہ_obj, i ? buf : val, o->unit, 0, تلاش_flags);
            إذا (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                إذا (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } وإلا {
                إذا (o->unit) {
                    لكل (o_named = عدم; o_named = av_opt_اگلا(نشانہ_obj, o_named); ) {
                        إذا (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            إذا (ci + 6 >= FF_ARRAY_ELEMS(const_اقدار)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                أرجع AVERROR_PATCHWELCOME;
                            }
                            const_ناں [ci  ] = o_named->name;
                            const_اقدار[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_ناں [ci  ] = "default";
                const_اقدار[ci++] = DEFAULT_NUMVAL(o);
                const_ناں [ci  ] = "max";
                const_اقدار[ci++] = o->max;
                const_ناں [ci  ] = "min";
                const_اقدار[ci++] = o->min;
                const_ناں [ci  ] = "none";
                const_اقدار[ci++] = 0;
                const_ناں [ci  ] = "all";
                const_اقدار[ci++] = ~0;
                const_ناں [ci] = عدم;
                const_اقدار[ci] = 0;

                res = av_اظہاریہ_parse_and_eval(&d, i ? buf : val, const_ناں,
                                            const_اقدار, عدم, عدم, عدم, عدم, عدم, 0, obj);
                إذا (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    أرجع res;
                }
            }
        }
        إذا (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(بنانشانی صحيح*)dst;
            إذا (cmd == '+')
                d = intnum | (int64_t)d;
            وإلا إذا (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        إذا ((ret = write_نمبر(obj, o, dst, d, 1, 1, 0)) < 0)
            أرجع ret;
        val += i;
        إذا (!i || !*val)
            أرجع 0;
    }
}

ساكن صحيح سیٹ_string_image_ناپ(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح tmp[2];
    صحيح ret;

    إذا (!val || !strcmp(val, "none")) {
        إذا (dst) {
        dst[0] =
        dst[1] = 0;
        }
        أرجع 0;
    }
    ret = av_parse_video_ناپ(&tmp[0], &tmp[1], val);
    إذا (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        أرجع ret;
    }
    إذا (dst)
        حافظہ_نقل(dst, tmp, حجم(tmp));
    أرجع ret;
}

ساكن صحيح سیٹ_string_video_شرح(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    AVRational tmp;
    صحيح ret = av_parse_video_شرح(&tmp, val);
    إذا (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    إذا (dst)
        *dst = tmp;
    أرجع ret;
}

ساكن صحيح سیٹ_string_color(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح ret;

    إذا (!val) {
        أرجع 0;
    } وإلا {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        إذا (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            أرجع ret;
        }
        إذا (dst)
            حافظہ_نقل(dst, tmp, حجم(tmp));
        أرجع ret;
    }
    أرجع 0;
}

ساكن ثابت حرف *get_bool_name(صحيح val)
{
    إذا (val < 0)
        أرجع "auto";
    أرجع val ? "true" : "false";
}

ساكن صحيح سیٹ_string_bool(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح n;

    إذا (!val)
        أرجع 0;

    إذا (!strcmp(val, "auto")) {
        n = -1;
    } وإلا إذا (av_میل_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } وإلا إذا (av_میل_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } وإلا {
        حرف *سرا = عدم;
        n = strtol(val, &سرا, 10);
        إذا (val + لڑی_لمبائی(val) != سرا)
            اذهب fail;
    }

    إذا (n < o->min || n > o->max)
        اذهب fail;

    إذا (dst)
    *dst = n;
    أرجع 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    أرجع AVERROR(EINVAL);
}

ساكن صحيح سیٹ_string_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
                          صحيح fmt_nb, صحيح ((*get_fmt)(ثابت حرف *)), ثابت حرف *desc,
                          تعداد AVOptionType type)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح fmt, min, max;

    إذا (!val || !strcmp(val, "none")) {
        fmt = -1;
    } وإلا {
        fmt = get_fmt(val);
        إذا (fmt == -1) {
            حرف *پوچھ;
            fmt = strtol(val, &پوچھ, 0);
            إذا (*پوچھ || (بنانشانی)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                أرجع AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    إذا(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    إذا (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        أرجع AVERROR(ERANGE);
    }

    إذا (dst)
    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:  *(تعداد AVPixelFormat *)dst = fmt; اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT: *(تعداد AVSampleFormat*)dst = fmt; اكسر;
    افتراضي: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    أرجع 0;
}

ساكن صحيح get_pix_fmt(ثابت حرف *name)
{
    أرجع av_get_pix_fmt(name);
}

ساكن صحيح سیٹ_string_pixel_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع سیٹ_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساكن صحيح get_sample_fmt(ثابت حرف *name)
{
    أرجع av_get_sample_fmt(name);
}

ساكن صحيح سیٹ_string_sample_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع سیٹ_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساكن صحيح سیٹ_string_dict(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    AVDictionary *options = عدم;

    إذا (val) {
        صحيح ret = av_dict_parse_string(&options, val, "=", ":", 0);
        إذا (ret < 0) {
            av_dict_free(&options);
            أرجع ret;
        }
    }

    إذا (!dst) {
        av_dict_free(&options);
        أرجع 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    أرجع 0;
}

ساكن صحيح سیٹ_string_channel_layout(فراغ *obj, ثابت AVOption *o,
                                     ثابت حرف *val, فراغ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    صحيح ret;
    إذا (dst)
    av_channel_layout_uninit(channel_layout);
    وإلا
        channel_layout = &tmp;
    إذا (!val)
        أرجع 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    إذا (ret < 0)
        أرجع ret;
    إذا (!dst)
        av_channel_layout_uninit(channel_layout);
    أرجع 0;
}

ساكن صحيح opt_سیٹ_elem(فراغ *obj, فراغ *نشانہ_obj, ثابت AVOption *o,
                        ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_ادھار(o->type);
    صحيح ret;

    إذا (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_ناپ &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        أرجع AVERROR(EINVAL);

    بدل (type) {
    حالة AV_OPT_TYPE_BOOL:
        أرجع سیٹ_string_bool(obj, o, val, dst);
    حالة AV_OPT_TYPE_STRING:
        أرجع سیٹ_string(obj, o, val, dst);
    حالة AV_OPT_TYPE_ثنائی:
        أرجع سیٹ_string_ثنائی(obj, o, val, dst);
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_RATIONAL:
        أرجع سیٹ_string_نمبر(obj, نشانہ_obj, o, val, dst);
    حالة AV_OPT_TYPE_IMAGE_ناپ:
        أرجع سیٹ_string_image_ناپ(obj, o, val, dst);
    حالة AV_OPT_TYPE_VIDEO_شرح: {
        AVRational tmp;
        ret = سیٹ_string_video_شرح(obj, o, val, &tmp);
        إذا (ret < 0)
            أرجع ret;
        أرجع write_نمبر(obj, o, dst, 1, tmp.den, tmp.عدد, 0);
    }
    حالة AV_OPT_TYPE_PIXEL_FMT:
        أرجع سیٹ_string_pixel_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        أرجع سیٹ_string_sample_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            إذا (val) {
                إذا ((ret = av_parse_ویلا(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    أرجع ret;
                }
            }
            إذا (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                أرجع AVERROR(ERANGE);
            }
            إذا (dst)
            *(int64_t *)dst = usecs;
            أرجع 0;
        }
    حالة AV_OPT_TYPE_COLOR:
        أرجع سیٹ_string_color(obj, o, val, dst);
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = سیٹ_string_channel_layout(obj, o, val, dst);
        إذا (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        أرجع ret;
    حالة AV_OPT_TYPE_DICT:
        أرجع سیٹ_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    أرجع AVERROR(EINVAL);
}

ساكن صحيح opt_سیٹ_array(فراغ *obj, فراغ *نشانہ_obj, ثابت AVOption *o,
                         ثابت حرف *val, فراغ *dst)
{
    ثابت AVOptionArrayDef *arr = o->default_val.arr;
    ثابت size_t      elem_ناپ = opt_type_desc[TYPE_ادھار(o->type)].ناپ;
    ثابت uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = عدم;

    فراغ      *logctx = dst ? obj : عدم;
    فراغ       *elems = عدم;
    بنانشانی nb_elems = 0;
    صحيح ret;

    إذا (val && *val) {
        str = av_malloc(لڑی_لمبائی(val) + 1);
        إذا (!str)
            أرجع AVERROR(ENOMEM);
    }

    // split and unescape the string
    طالما (val && *val) {
        uint8_t *p = str;
        فراغ *tmp;

        إذا (arr && arr->ناپ_max && nb_elems >= arr->ناپ_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->ناپ_max, o->name);
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        لكل (; *val; val++, p++) {
            إذا (*val == '\\' && val[1])
                val++;
            وإلا إذا (*val == sep) {
                val++;
                اكسر;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_ناپ);
        إذا (!tmp) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_ناپ);

        ret = opt_سیٹ_elem(obj, نشانہ_obj, o, str, tmp);
        إذا (ret < 0)
            اذهب fail;
        nb_elems++;
    }
    av_freep(&str);

    إذا (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    إذا (arr && nb_elems < arr->ناپ_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->ناپ_min, o->name);
        ret = AVERROR(EINVAL);
        اذهب fail;
    }

    إذا (dst) {
    *((فراغ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } وإلا
        opt_free_array(o, &elems, &nb_elems);

    أرجع 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    أرجع ret;
}

صحيح av_opt_سیٹ(فراغ *obj, ثابت حرف *name, ثابت حرف *val, صحيح تلاش_flags)
{
    فراغ *dst, *نشانہ_obj;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, 0, &نشانہ_obj, &o, &dst);
    إذا (ret < 0)
        أرجع ret;

    أرجع ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_سیٹ_array : opt_سیٹ_elem)(obj, نشانہ_obj, o, val, dst);
}

#تعریف_کرو OPT_EVAL_نمبر(name, opttype, vartype)                         \
صحيح av_opt_eval_ ## name(فراغ *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## باہرلا_3)        \
{                                                                       \
    إذا (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        أرجع AVERROR(EINVAL);                                         \
    أرجع سیٹ_string_نمبر(obj, obj, o, val, name ## باہرلا_3);           \
}

OPT_EVAL_نمبر(flags,  AV_OPT_TYPE_FLAGS,    صحيح)
OPT_EVAL_نمبر(صحيح,    AV_OPT_TYPE_INT,      صحيح)
OPT_EVAL_نمبر(uint,   AV_OPT_TYPE_UINT,     بنانشانی)
OPT_EVAL_نمبر(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_نمبر(عائم,  AV_OPT_TYPE_FLOAT,    عائم)
OPT_EVAL_نمبر(مزدوج, AV_OPT_TYPE_DOUBLE,   مزدوج)
OPT_EVAL_نمبر(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ساكن صحيح سیٹ_نمبر(فراغ *obj, ثابت حرف *name, مزدوج عدد, صحيح den, int64_t intnum,
                      صحيح تلاش_flags, صحيح require_type)
{
    فراغ *dst;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, require_type, عدم, &o, &dst);
    إذا (ret < 0)
        أرجع ret;
    إذا (dst)
        ret = write_نمبر(obj, o, dst, عدد, den, intnum, 0);

    أرجع ret;
}

صحيح av_opt_سیٹ_int(فراغ *obj, ثابت حرف *name, int64_t val, صحيح تلاش_flags)
{
    أرجع سیٹ_نمبر(obj, name, 1, 1, val, تلاش_flags, 0);
}

صحيح av_opt_سیٹ_double(فراغ *obj, ثابت حرف *name, مزدوج val, صحيح تلاش_flags)
{
    أرجع سیٹ_نمبر(obj, name, val, 1, 1, تلاش_flags, 0);
}

صحيح av_opt_سیٹ_q(فراغ *obj, ثابت حرف *name, AVRational val, صحيح تلاش_flags)
{
    أرجع سیٹ_نمبر(obj, name, val.عدد, val.den, 1, تلاش_flags, 0);
}

صحيح av_opt_سیٹ_bin(فراغ *obj, ثابت حرف *name, ثابت uint8_t *val, صحيح len, صحيح تلاش_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحيح *lendst;
    صحيح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_ثنائی,
                       عدم, عدم, (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst) {
    ptr = len ? av_malloc(len) : عدم;
    إذا (len && !ptr)
        أرجع AVERROR(ENOMEM);

    lendst = (صحيح *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    إذا (len)
        حافظہ_نقل(ptr, val, len);
    }

    أرجع 0;
}

صحيح av_opt_سیٹ_image_ناپ(فراغ *obj, ثابت حرف *name, صحيح w, صحيح h, صحيح تلاش_flags)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_IMAGE_ناپ,
                       عدم, &o, (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    logctx = dst ? obj : عدم;

    إذا (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        أرجع AVERROR(EINVAL);
    }

    إذا (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    أرجع 0;
}

صحيح av_opt_سیٹ_video_شرح(فراغ *obj, ثابت حرف *name, AVRational val, صحيح تلاش_flags)
{
    أرجع سیٹ_نمبر(obj, name, val.عدد, val.den, 1, تلاش_flags, AV_OPT_TYPE_VIDEO_شرح);
}

ساكن صحيح سیٹ_format(فراغ *obj, ثابت حرف *name, صحيح fmt, صحيح تلاش_flags,
                      تعداد AVOptionType type, ثابت حرف *desc, صحيح nb_fmts)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح min, max, ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, type, عدم, &o, (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    logctx = dst ? obj : عدم;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    إذا (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        أرجع AVERROR(ERANGE);
    }
    إذا (dst)
    *dst = fmt;
    أرجع 0;
}

صحيح av_opt_سیٹ_pixel_fmt(فراغ *obj, ثابت حرف *name, تعداد AVPixelFormat fmt, صحيح تلاش_flags)
{
    أرجع سیٹ_format(obj, name, fmt, تلاش_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحيح av_opt_سیٹ_sample_fmt(فراغ *obj, ثابت حرف *name, تعداد AVSampleFormat fmt, صحيح تلاش_flags)
{
    أرجع سیٹ_format(obj, name, fmt, تلاش_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحيح av_opt_سیٹ_dict_val(فراغ *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحيح تلاش_flags)
{
    AVDictionary **dst;
    صحيح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_DICT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    أرجع ret;
}

صحيح av_opt_سیٹ_chlayout(فراغ *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحيح تلاش_flags)
{
    AVChannelLayout *dst;
    صحيح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_CHLAYOUT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    أرجع ret;
}

ساكن فراغ format_duration(حرف *buf, size_t ناپ, int64_t d)
{
    حرف *e;

    av_assert0(ناپ >= 25);
    إذا (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        ناپ--;
        d = -d;
    }
    إذا (d == INT64_MAX)
        snprintf(buf, ناپ, "INT64_MAX");
    وإلا إذا (d == INT64_MIN)
        snprintf(buf, ناپ, "INT64_MIN");
    وإلا إذا (d > (int64_t)3600*1000000)
        snprintf(buf, ناپ, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحيح)((d / 60000000) % 60),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا إذا (d > 60*1000000)
        snprintf(buf, ناپ, "%d:%02d.%06d",
                 (صحيح)(d / 60000000),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا
        snprintf(buf, ناپ, "%d.%06d",
                 (صحيح)(d / 1000000),
                 (صحيح)(d % 1000000));
    e = buf + لڑی_لمبائی(buf);
    طالما (e > buf && e[-1] == '0')
        *(--e) = 0;
    إذا (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ساكن صحيح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت فراغ *dst, صحيح تلاش_flags)
{
    صحيح ret;

    بدل (TYPE_ادھار(o->type)) {
    حالة AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(صحيح *)dst));
        اكسر;
    حالة AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(صحيح *)dst);
        اكسر;
    حالة AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(صحيح *)dst);
        اكسر;
    حالة AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(بنانشانی *)dst);
        اكسر;
    حالة AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        اكسر;
    حالة AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        اكسر;
    حالة AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(عائم *)dst);
        اكسر;
    حالة AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(مزدوج *)dst);
        اكسر;
    حالة AV_OPT_TYPE_VIDEO_شرح:
    حالة AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->عدد, ((AVRational *)dst)->den);
        اكسر;
    حالة AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        اكسر;
    حالة AV_OPT_TYPE_STRING:
        إذا (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } وإلا إذا (تلاش_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = عدم;
            أرجع 0;
        } وإلا {
            *pbuf = av_strdup("");
        }
        أرجع *pbuf ? 0 : AVERROR(ENOMEM);
    حالة AV_OPT_TYPE_ثنائی: {
        ثابت uint8_t *bin;
        صحيح len;

        إذا (!*(uint8_t **)dst && (تلاش_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        len = *(صحيح *)(((uint8_t *)dst) + حجم(uint8_t *));
        إذا ((uint64_t)len * 2 + 1 > ودھ_توں_ودھ_عدد)
            أرجع AVERROR(EINVAL);
        إذا (!(*pbuf = av_malloc(len * 2 + 1)))
            أرجع AVERROR(ENOMEM);
        إذا (!len) {
            *pbuf[0] = '\0';
            أرجع 0;
        }
        bin = *(uint8_t **)dst;
        لكل (صحيح i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        أرجع 0;
    }
    حالة AV_OPT_TYPE_IMAGE_ناپ:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((صحيح *)dst)[0], ((صحيح *)dst)[1]);
        اكسر;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(*(تعداد AVPixelFormat *)dst), "none"));
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(*(تعداد AVSampleFormat *)dst), "none"));
        اكسر;
    حالة AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = لڑی_لمبائی(*pbuf); // no overflow possible, checked by an assert
        اكسر;
    }
    حالة AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (صحيح)((uint8_t *)dst)[0], (صحيح)((uint8_t *)dst)[1],
                       (صحيح)((uint8_t *)dst)[2], (صحيح)((uint8_t *)dst)[3]);
        اكسر;
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        اكسر;
    حالة AV_OPT_TYPE_DICT:
        إذا (!*(AVDictionary **)dst && (تلاش_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        أرجع av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    افتراضي:
        أرجع AVERROR(EINVAL);
    }

    أرجع ret;
}

ساكن صحيح opt_get_array(ثابت AVOption *o, فراغ *dst, uint8_t **باہرلا_val)
{
    ثابت بنانشانی گنتی = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = عدم;
    size_t   str_len = 0;
    صحيح ret;

    *باہرلا_val = عدم;

    لكل (بنانشانی i = 0; i < گنتی; i++) {
        uint8_t buf[128], *باہرلا = buf;
        size_t باہرلا_len;

        ret = opt_get_elem(o, &باہرلا, حجم(buf),
                           opt_array_pelem(o, *(فراغ **)dst, i), 0);
        إذا (ret < 0)
            اذهب fail;

        باہرلا_len = لڑی_لمبائی(باہرلا);
        إذا (باہرلا_len > SIZE_MAX / 2 - !!i ||
            !!i + باہرلا_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            اذهب fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + باہرلا_len * 2 + !!i);
        إذا (ret < 0)
            اذهب fail;

        // add separator if needed
        إذا (i)
            str[str_len++] = sep;

        // escape the element
        لكل (بنانشانی j = 0; j < باہرلا_len; j++) {
            uint8_t val = باہرلا[j];
            إذا (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        إذا (باہرلا != buf)
            av_freep(&باہرلا);
        إذا (ret < 0) {
            av_freep(&str);
            أرجع ret;
        }
    }

    *باہرلا_val = str;

    أرجع 0;
}

صحيح av_opt_get(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, uint8_t **باہرلا_val)
{
    فراغ *dst, *نشانہ_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    uint8_t *باہرلا, buf[128];
    صحيح ret;

    إذا (!o || !نشانہ_obj || (o->وتھ<=0 && o->type != AV_OPT_TYPE_CONST))
        أرجع AVERROR_OPTION_NOT_لبھیا;

    إذا (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)نشانہ_obj + o->وتھ;

    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, باہرلا_val);
        إذا (ret < 0)
            أرجع ret;
        إذا (!*باہرلا_val && !(تلاش_flags & AV_OPT_ALLOW_NULL)) {
            *باہرلا_val = av_strdup("");
            إذا (!*باہرلا_val)
               أرجع AVERROR(ENOMEM);
        }
        أرجع 0;
    }

    buf[0] = 0;
    باہرلا = buf;
    ret = opt_get_elem(o, &باہرلا, حجم(buf), dst, تلاش_flags);
    إذا (ret < 0)
        أرجع ret;
    إذا (باہرلا != buf) {
        *باہرلا_val = باہرلا;
        أرجع 0;
    }

    إذا (ret >= حجم(buf))
        أرجع AVERROR(EINVAL);
    *باہرلا_val = av_strdup(باہرلا);
    أرجع *باہرلا_val ? 0 : AVERROR(ENOMEM);
}

ساكن صحيح get_نمبر(فراغ *obj, ثابت حرف *name, مزدوج *عدد, صحيح *den, int64_t *intnum,
                      صحيح تلاش_flags)
{
    فراغ *dst, *نشانہ_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t *)نشانہ_obj) + o->وتھ;

    أرجع read_نمبر(o, dst, عدد, den, intnum);
}

صحيح av_opt_get_int(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, int64_t *باہرلا_val)
{
    int64_t intnum = 1;
    مزدوج عدد = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_نمبر(obj, name, &عدد, &den, &intnum, تلاش_flags)) < 0)
        أرجع ret;
    إذا (عدد == den)
        *باہرلا_val = intnum;
    وإلا
        *باہرلا_val = عدد * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_double(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, مزدوج *باہرلا_val)
{
    int64_t intnum = 1;
    مزدوج عدد = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_نمبر(obj, name, &عدد, &den, &intnum, تلاش_flags)) < 0)
        أرجع ret;
    *باہرلا_val = عدد * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_q(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, AVRational *باہرلا_val)
{
    int64_t intnum = 1;
    مزدوج عدد = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_نمبر(obj, name, &عدد, &den, &intnum, تلاش_flags)) < 0)
        أرجع ret;

    إذا (عدد == 1.0 && (صحيح)intnum == intnum)
        *باہرلا_val = (AVRational){intnum, den};
    وإلا
        *باہرلا_val = double_منزل_rational(عدد*intnum/den);
    أرجع 0;
}

صحيح av_opt_get_image_ناپ(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, صحيح *w_باہرلا, صحيح *h_باہرلا)
{
    فراغ *dst, *نشانہ_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (o->type != AV_OPT_TYPE_IMAGE_ناپ) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)نشانہ_obj) + o->وتھ;
    إذا (w_باہرلا) *w_باہرلا = *(صحيح *)dst;
    إذا (h_باہرلا) *h_باہرلا = *((صحيح *)dst+1);
    أرجع 0;
}

صحيح av_opt_get_video_شرح(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, AVRational *باہرلا_val)
{
    أرجع av_opt_get_q(obj, name, تلاش_flags, باہرلا_val);
}

ساكن صحيح get_format(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, فراغ *باہرلا_fmt,
                      تعداد AVOptionType type, ثابت حرف *desc)
{
    فراغ *dst, *نشانہ_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)نشانہ_obj) + o->وتھ;
    إذا (type == AV_OPT_TYPE_PIXEL_FMT)
        *(تعداد AVPixelFormat *)باہرلا_fmt = *(تعداد AVPixelFormat *)dst;
    وإلا
        *(تعداد AVSampleFormat*)باہرلا_fmt = *(تعداد AVSampleFormat*)dst;

    أرجع 0;
}

صحيح av_opt_get_pixel_fmt(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, تعداد AVPixelFormat *باہرلا_fmt)
{
    أرجع get_format(obj, name, تلاش_flags, باہرلا_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحيح av_opt_get_sample_fmt(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, تعداد AVSampleFormat *باہرلا_fmt)
{
    أرجع get_format(obj, name, تلاش_flags, باہرلا_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحيح av_opt_get_chlayout(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, AVChannelLayout *cl)
{
    فراغ *dst, *نشانہ_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)نشانہ_obj) + o->وتھ;
    أرجع av_channel_layout_copy(cl, dst);
}

صحيح av_opt_get_dict_val(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags, AVDictionary **باہرلا_val)
{
    فراغ *نشانہ_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);

    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (o->type != AV_OPT_TYPE_DICT)
        أرجع AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)نشانہ_obj) + o->وتھ);

    أرجع av_dict_copy(باہرلا_val, src, 0);
}

صحيح av_opt_flag_is_سیٹ(فراغ *obj, ثابت حرف *میدان_name, ثابت حرف *flag_name)
{
    ثابت AVOption *میدان = av_opt_لبھو(obj, میدان_name, عدم, 0, 0);
    ثابت AVOption *flag  = av_opt_لبھو(obj, flag_name,
                                        میدان ? میدان->unit : عدم, 0, 0);
    int64_t res;

    إذا (!میدان || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, میدان_name, 0, &res) < 0)
        أرجع 0;
    أرجع res & flag->default_val.i64;
}

ساكن فراغ log_int_قدر(فراغ *av_log_obj, صحيح level, int64_t i)
{
    إذا (i == ودھ_توں_ودھ_عدد) {
        av_log(av_log_obj, level, "INT_MAX");
    } وإلا إذا (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } وإلا إذا (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } وإلا إذا (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } وإلا إذا (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } وإلا {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ساكن فراغ log_قدر(فراغ *av_log_obj, صحيح level, مزدوج d)
{
    إذا      (d == ودھ_توں_ودھ_عدد) {
        av_log(av_log_obj, level, "INT_MAX");
    } وإلا إذا (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } وإلا إذا (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } وإلا إذا (d == (مزدوج)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } وإلا إذا (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } وإلا إذا (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } وإلا إذا (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } وإلا إذا (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } وإلا إذا (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } وإلا إذا (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } وإلا إذا (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } وإلا إذا (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } وإلا إذا (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } وإلا {
        av_log(av_log_obj, level, "%g", d);
    }
}

ساكن ثابت حرف *get_opt_const_name(فراغ *obj, ثابت حرف *unit, int64_t قدر)
{
    ثابت AVOption *opt = عدم;

    إذا (!unit)
        أرجع عدم;
    طالما ((opt = av_opt_اگلا(obj, opt)))
        إذا (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == قدر)
            أرجع opt->name;
    أرجع عدم;
}

ساكن حرف *get_opt_flags_string(فراغ *obj, ثابت حرف *unit, int64_t قدر)
{
    ثابت AVOption *opt = عدم;
    حرف flags[512];

    flags[0] = 0;
    إذا (!unit)
        أرجع عدم;
    طالما ((opt = av_opt_اگلا(obj, opt))) {
        إذا (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & قدر) {
            إذا (flags[0])
                av_strlcatf(flags, حجم(flags), "+");
            av_strlcatf(flags, حجم(flags), "%s", opt->name);
        }
    }
    إذا (flags[0])
        أرجع av_strdup(flags);
    أرجع عدم;
}

ساكن فراغ log_type(فراغ *av_log_obj, ثابت AVOption *o,
                     تعداد AVOptionType ماپا_type)
{
    ثابت تعداد AVOptionType type = TYPE_ادھار(o->type);

    إذا (o->type == AV_OPT_TYPE_CONST && (TYPE_ادھار(ماپا_type) == AV_OPT_TYPE_INT || TYPE_ادھار(ماپا_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    وإلا إذا (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        وإلا
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    وإلا
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ساكن فراغ log_default(فراغ *obj, فراغ *av_log_obj, ثابت AVOption *opt)
{
    إذا (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ثنائی)
        أرجع;
    إذا ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_ناپ ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_شرح) &&
        !opt->default_val.str)
        أرجع;

    إذا (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت AVOptionArrayDef *arr = opt->default_val.arr;
        إذا (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        أرجع;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    بدل (opt->type) {
    حالة AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        اكسر;
    حالة AV_OPT_TYPE_FLAGS: {
        حرف *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        إذا (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } وإلا {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        اكسر;
    }
    حالة AV_OPT_TYPE_DURATION: {
        حرف buf[25];
        format_duration(buf, حجم(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        اكسر;
    }
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_INT64: {
        ثابت حرف *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        إذا (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        وإلا
            log_int_قدر(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        اكسر;
    }
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_FLOAT:
        log_قدر(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, ودھ_توں_ودھ_عدد);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.عدد, q.den); }
        اكسر;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_COLOR:
    حالة AV_OPT_TYPE_IMAGE_ناپ:
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_DICT:
    حالة AV_OPT_TYPE_VIDEO_شرح:
    حالة AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        اكسر;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ساكن فراغ opt_list(فراغ *obj, فراغ *av_log_obj, ثابت حرف *unit,
                     صحيح req_flags, صحيح rej_flags, تعداد AVOptionType ماپا_type)
{
    ثابت AVOption *opt = عدم;
    AVOptionRanges *r;
    صحيح i;

    طالما ((opt = av_opt_اگلا(obj, opt))) {
        إذا (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            استمر;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        إذا (!unit && opt->type == AV_OPT_TYPE_CONST)
            استمر;
        وإلا إذا (unit && opt->type != AV_OPT_TYPE_CONST)
            استمر;
        وإلا إذا (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            استمر;
        وإلا إذا (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        وإلا
            av_log(av_log_obj, AV_LOG_INFO, "  %s%-17s ",
                   (opt->flags & AV_OPT_FLAG_FILTERING_PARAM) ? " " : "-",
                   opt->name);

        log_type(av_log_obj, opt, ماپا_type);

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

        إذا (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        إذا (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_تلاش_FAKE_OBJ) >= 0) {
            بدل (opt->type) {
            حالة AV_OPT_TYPE_INT:
            حالة AV_OPT_TYPE_UINT:
            حالة AV_OPT_TYPE_INT64:
            حالة AV_OPT_TYPE_UINT64:
            حالة AV_OPT_TYPE_DOUBLE:
            حالة AV_OPT_TYPE_FLOAT:
            حالة AV_OPT_TYPE_RATIONAL:
                لكل (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_قدر(av_log_obj, AV_LOG_INFO, r->range[i]->قدر_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_قدر(av_log_obj, AV_LOG_INFO, r->range[i]->قدر_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                اكسر;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        إذا (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

صحيح av_opt_show2(فراغ *obj, فراغ *av_log_obj, صحيح req_flags, صحيح rej_flags)
{
    إذا (!obj)
        أرجع -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, عدم, req_flags, rej_flags, -1);

    أرجع 0;
}

فراغ av_opt_سیٹ_defaults(فراغ *s)
{
    av_opt_سیٹ_defaults2(s, 0, 0);
}

فراغ av_opt_سیٹ_defaults2(فراغ *s, صحيح نقاب_2, صحيح flags)
{
    ثابت AVOption *opt = عدم;
    طالما ((opt = av_opt_اگلا(s, opt))) {
        فراغ *dst = ((uint8_t*)s) + opt->وتھ;

        إذا ((opt->flags & نقاب_2) != flags)
            استمر;

        إذا (opt->flags & AV_OPT_FLAG_READONLY)
            استمر;

        إذا (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ثابت AVOptionArrayDef *arr = opt->default_val.arr;
            ثابت حرف              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            إذا (arr && arr->def)
                opt_سیٹ_array(s, s, opt, arr->def, dst);

            استمر;
        }

        بدل (opt->type) {
            حالة AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                اكسر;
            حالة AV_OPT_TYPE_BOOL:
            حالة AV_OPT_TYPE_FLAGS:
            حالة AV_OPT_TYPE_INT:
            حالة AV_OPT_TYPE_UINT:
            حالة AV_OPT_TYPE_INT64:
            حالة AV_OPT_TYPE_UINT64:
            حالة AV_OPT_TYPE_DURATION:
            حالة AV_OPT_TYPE_PIXEL_FMT:
            حالة AV_OPT_TYPE_SAMPLE_FMT:
                write_نمبر(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
            حالة AV_OPT_TYPE_FLOAT: {
                مزدوج val;
                val = opt->default_val.dbl;
                write_نمبر(s, opt, dst, val, 1, 1, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, ودھ_توں_ودھ_عدد);
                write_نمبر(s, opt, dst, 1, val.den, val.عدد, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_COLOR:
                سیٹ_string_color(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_STRING:
                سیٹ_string(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_IMAGE_ناپ:
                سیٹ_string_image_ناپ(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_VIDEO_شرح:
                سیٹ_string_video_شرح(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_ثنائی:
                سیٹ_string_ثنائی(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_CHLAYOUT:
                سیٹ_string_channel_layout(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_DICT:
                سیٹ_string_dict(s, opt, opt->default_val.str, dst);
                اكسر;
        افتراضي:
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
ساكن صحيح parse_کلید_قدر_pair(فراغ *ctx, ثابت حرف **buf,
                                ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep)
{
    حرف *کلید = av_get_token(buf, کلید_val_sep);
    حرف *val;
    صحيح ret;

    إذا (!کلید)
        أرجع AVERROR(ENOMEM);

    إذا (*کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوڑے_sep);
        إذا (!val) {
            av_freep(&کلید);
            أرجع AVERROR(ENOMEM);
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", کلید);
        av_free(کلید);
        أرجع AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", کلید, val);

    ret = av_opt_سیٹ(ctx, کلید, val, AV_OPT_تلاش_CHILDREN);
    إذا (ret == AVERROR_OPTION_NOT_لبھیا)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", کلید);

    av_free(کلید);
    av_free(val);
    أرجع ret;
}

صحيح av_سیٹ_options_string(فراغ *ctx, ثابت حرف *opts,
                          ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep)
{
    صحيح ret, گنتی = 0;

    إذا (!opts)
        أرجع 0;

    طالما (*opts) {
        إذا ((ret = parse_کلید_قدر_pair(ctx, &opts, کلید_val_sep, جوڑے_sep)) < 0)
            أرجع ret;
        گنتی++;

        إذا (*opts)
            opts++;
    }

    أرجع گنتی;
}

#تعریف_کرو WHITESPACES " \n\t\r"

ساكن صحيح is_کلید_char(حرف c)
{
    أرجع (بنانشانی)((c | 32) - 'a') < 26 ||
           (بنانشانی)(c - '0') < 10 ||
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
ساكن صحيح get_کلید(ثابت حرف **ropts, ثابت حرف *delim, حرف **rkey)
{
    ثابت حرف *opts = *ropts;
    ثابت حرف *کلید_شروع, *کلید_سرا;

    کلید_شروع = opts += strspn(opts, WHITESPACES);
    طالما (is_کلید_char(*opts))
        opts++;
    کلید_سرا = opts;
    opts += strspn(opts, WHITESPACES);
    إذا (!*opts || !strchr(delim, *opts))
        أرجع AVERROR(EINVAL);
    opts++;
    إذا (!(*rkey = av_malloc(کلید_سرا - کلید_شروع + 1)))
        أرجع AVERROR(ENOMEM);
    حافظہ_نقل(*rkey, کلید_شروع, کلید_سرا - کلید_شروع);
    (*rkey)[کلید_سرا - کلید_شروع] = 0;
    *ropts = opts;
    أرجع 0;
}

صحيح av_opt_get_کلید_قدر(ثابت حرف **ropts,
                         ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep,
                         بنانشانی flags,
                         حرف **rkey, حرف **rval)
{
    صحيح ret;
    حرف *کلید = عدم, *val;
    ثابت حرف *opts = *ropts;

    إذا ((ret = get_کلید(&opts, کلید_val_sep, &کلید)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_کلید))
        أرجع AVERROR(EINVAL);
    إذا (!(val = av_get_token(&opts, جوڑے_sep))) {
        av_free(کلید);
        أرجع AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = کلید;
    *rval  = val;
    أرجع 0;
}

صحيح av_opt_سیٹ_from_string(فراغ *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep)
{
    صحيح ret, گنتی = 0;
    ثابت حرف *dummy_shorthand = عدم;
    ثابت حرف *کلید;

    إذا (!opts)
        أرجع 0;
    إذا (!shorthand)
        shorthand = &dummy_shorthand;

    طالما (*opts) {
        حرف *parsed_کلید, *قدر;
        ret = av_opt_get_کلید_قدر(&opts, کلید_val_sep, جوڑے_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_کلید : 0,
                                   &parsed_کلید, &قدر);
        إذا (ret < 0) {
            إذا (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            وإلا
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            أرجع ret;
        }
        إذا (*opts)
            opts++;
        إذا (parsed_کلید) {
            کلید = parsed_کلید;
            طالما (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } وإلا {
            کلید = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", کلید, قدر);
        إذا ((ret = av_opt_سیٹ(ctx, کلید, قدر, 0)) < 0) {
            إذا (ret == AVERROR_OPTION_NOT_لبھیا)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", کلید);
            av_free(قدر);
            av_free(parsed_کلید);
            أرجع ret;
        }

        av_free(قدر);
        av_free(parsed_کلید);
        گنتی++;
    }
    أرجع گنتی;
}

فراغ av_opt_free(فراغ *obj)
{
    ثابت AVOption *o = عدم;
    طالما ((o = av_opt_اگلا(obj, o))) {
        فراغ *pitem = (uint8_t *)obj + o->وتھ;

        إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        وإلا
            opt_free_elem(o->type, pitem);
    }
}

صحيح av_opt_سیٹ_dict2(فراغ *obj, AVDictionary **options, صحيح تلاش_flags)
{
    ثابت AVDictionary_اندراج *t = عدم;
    AVDictionary    *tmp = عدم;
    صحيح ret;

    إذا (!options)
        أرجع 0;

    طالما ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_سیٹ(obj, t->کلید, t->قدر, تلاش_flags);
        إذا (ret == AVERROR_OPTION_NOT_لبھیا)
            ret = av_dict_سیٹ(&tmp, t->کلید, t->قدر, AV_DICT_MULTIKEY);
        إذا (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->کلید, t->قدر);
            av_dict_free(&tmp);
            أرجع ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    أرجع 0;
}

صحيح av_opt_سیٹ_dict(فراغ *obj, AVDictionary **options)
{
    أرجع av_opt_سیٹ_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_لبھو(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحيح opt_flags, صحيح تلاش_flags)
{
    أرجع av_opt_find2(obj, name, unit, opt_flags, تلاش_flags, عدم);
}

ثابت AVOption *av_opt_find2(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحيح opt_flags, صحيح تلاش_flags, فراغ **نشانہ_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = عدم;

    إذا(!obj)
        أرجع عدم;

    c= *(AVClass**)obj;

    إذا (!c)
        أرجع عدم;

    إذا (تلاش_flags & AV_OPT_تلاش_CHILDREN) {
        إذا (تلاش_flags & AV_OPT_تلاش_FAKE_OBJ) {
            فراغ *iter = عدم;
            ثابت AVClass *بچہ;
            طالما (بچہ = av_opt_بچہ_class_iterate(c, &iter))
                إذا (o = av_opt_find2(&بچہ, name, unit, opt_flags, تلاش_flags, عدم))
                    أرجع o;
        } وإلا {
            فراغ *بچہ = عدم;
            طالما (بچہ = av_opt_بچہ_اگلا(obj, بچہ))
                إذا (o = av_opt_find2(بچہ, name, unit, opt_flags, تلاش_flags, نشانہ_obj))
                    أرجع o;
        }
    }

    طالما (o = av_opt_اگلا(obj, o)) {
        إذا (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            إذا (نشانہ_obj) {
                إذا (!(تلاش_flags & AV_OPT_تلاش_FAKE_OBJ))
                    *نشانہ_obj = obj;
                وإلا
                    *نشانہ_obj = عدم;
            }
            أرجع o;
        }
    }
    أرجع عدم;
}

فراغ *av_opt_بچہ_اگلا(فراغ *obj, فراغ *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    إذا (c->بچہ_اگلا)
        أرجع c->بچہ_اگلا(obj, prev);
    أرجع عدم;
}

ثابت AVClass *av_opt_بچہ_class_iterate(ثابت AVClass *ماپا, فراغ **iter)
{
    إذا (ماپا->بچہ_class_iterate)
        أرجع ماپا->بچہ_class_iterate(iter);
    أرجع عدم;
}

ساكن صحيح opt_copy_elem(فراغ *logctx, تعداد AVOptionType type,
                         فراغ *dst, ثابت فراغ *src)
{
    إذا (type == AV_OPT_TYPE_STRING) {
        ثابت حرف *src_str = *(ثابت حرف *ثابت *)src;
        حرف         **dstp =  (حرف **)dst;
        إذا (*dstp != src_str)
            av_freep(dstp);
        إذا (src_str) {
            *dstp = av_strdup(src_str);
            إذا (!*dstp)
                أرجع AVERROR(ENOMEM);
        }
    } وإلا إذا (type == AV_OPT_TYPE_ثنائی) {
        ثابت uint8_t *ثابت *src8 = (ثابت uint8_t *ثابت *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        صحيح len = *(ثابت صحيح *)(src8 + 1);
        إذا (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        إذا (len && !*dst8) {
            *(صحيح *)(dst8 + 1) = 0;
            أرجع AVERROR(ENOMEM);
        }
        *(صحيح *)(dst8 + 1) = len;
    } وإلا إذا (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } وإلا إذا (type == AV_OPT_TYPE_DICT) {
        ثابت AVDictionary *sdict = *(ثابت AVDictionary * ثابت *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        إذا (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = عدم;
        أرجع av_dict_copy(ddictp, sdict, 0);
    } وإلا إذا (type == AV_OPT_TYPE_CHLAYOUT) {
        ثابت AVChannelLayout *slayout = (ثابت AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        إذا (dlayout != slayout) {
            إذا (dlayout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                slayout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = عدم;
            أرجع av_channel_layout_copy(dst, src);
        }
    } وإلا إذا (opt_is_pod(type)) {
        size_t ناپ = opt_type_desc[type].ناپ;
        حافظہ_نقل(dst, src, ناپ);
    } وإلا {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        أرجع AVERROR(EINVAL);
    }

    أرجع 0;
}

ساكن صحيح opt_copy_array(فراغ *logctx, ثابت AVOption *o,
                          فراغ **pdst, ثابت فراغ * ثابت *psrc)
{
    بنانشانی nb_elems = *opt_array_pcount(psrc);
    فراغ         *dst = عدم;
    صحيح ret;

    إذا (*pdst == *psrc) {
        *pdst                   = عدم;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_ادھار(o->type)].ناپ);
    إذا (!dst)
        أرجع AVERROR(ENOMEM);

    لكل (بنانشانی i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_ادھار(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(فراغ**)psrc, i));
        إذا (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            أرجع ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    أرجع 0;
}

صحيح av_opt_copy(فراغ *dst, ثابت فراغ *src)
{
    ثابت AVOption *o = عدم;
    ثابت AVClass *c;
    صحيح ret = 0;

    إذا (!src)
        أرجع AVERROR(EINVAL);

    c = *(AVClass **)src;
    إذا (!c || c != *(AVClass **)dst)
        أرجع AVERROR(EINVAL);

    طالما ((o = av_opt_اگلا(src, o))) {
        فراغ *میدان_dst = (uint8_t *)dst + o->وتھ;
        فراغ *میدان_src = (uint8_t *)src + o->وتھ;

        صحيح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       میدان_dst, میدان_src) :
                  opt_copy_elem (dst, o->type, میدان_dst, میدان_src);
        إذا (err < 0)
            ret = err;
    }
    أرجع ret;
}

صحيح av_opt_get_array_ناپ(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags,
                          بنانشانی صحيح *باہرلا_val)
{
    فراغ *نشانہ_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray = (uint8_t *)نشانہ_obj + o->وتھ;
    *باہرلا_val = *opt_array_pcount(parray);

    أرجع 0;
}

صحيح av_opt_get_array(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags,
                     بنانشانی صحيح شروع_elem, بنانشانی صحيح nb_elems,
                     تعداد AVOptionType باہرلا_type, فراغ *باہرلا_val)
{
    ثابت size_t elem_ناپ_باہرلا = opt_type_desc[TYPE_ادھار(باہرلا_type)].ناپ;

    ثابت AVOption *o;
    فراغ *نشانہ_obj;

    ثابت فراغ *parray;
    بنانشانی array_ناپ;

    صحيح ret;

    o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ_obj);
    إذا (!o || !نشانہ_obj)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (باہرلا_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray     = (uint8_t *)نشانہ_obj + o->وتھ;
    array_ناپ = *opt_array_pcount(parray);

    إذا (شروع_elem >= array_ناپ ||
        array_ناپ - شروع_elem < nb_elems)
        أرجع AVERROR(EINVAL);

    لكل (بنانشانی i = 0; i < nb_elems; i++) {
        ثابت فراغ *src = opt_array_pelem(o, *(فراغ**)parray, شروع_elem + i);
        فراغ       *dst = (uint8_t*)باہرلا_val + i * elem_ناپ_باہرلا;

        إذا (باہرلا_type == TYPE_ادھار(o->type)) {
            ret = opt_copy_elem(obj, باہرلا_type, dst, src);
            إذا (ret < 0)
                اذهب fail;
        } وإلا إذا (باہرلا_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *باہرلا = buf;

            ret = opt_get_elem(o, &باہرلا, حجم(buf), src, تلاش_flags);
            إذا (ret < 0)
                اذهب fail;

            إذا (باہرلا == buf) {
                باہرلا = av_strdup(buf);
                إذا (!باہرلا) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
            }

            *(uint8_t**)dst = باہرلا;
        } وإلا إذا (باہرلا_type == AV_OPT_TYPE_INT64    ||
                   باہرلا_type == AV_OPT_TYPE_DOUBLE   ||
                   باہرلا_type == AV_OPT_TYPE_RATIONAL) {
            مزدوج     عدد = 1.0;
            صحيح        den = 1;
            int64_t intnum = 1;

            ret = read_نمبر(o, src, &عدد, &den, &intnum);
            إذا (ret < 0)
                اذهب fail;

            بدل (باہرلا_type) {
            حالة AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (عدد == den) ?  intnum : عدد * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
                *(مزدوج*)dst = عدد * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (عدد == 1.0 && (صحيح)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_منزل_rational(عدد * intnum / den);
                اكسر;
            افتراضي: av_assert0(0);
            }
        } وإلا
            أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
fail:
    لكل (بنانشانی i = 0; i < nb_elems; i++)
        opt_free_elem(باہرلا_type, (uint8_t*)باہرلا_val + i * elem_ناپ_باہرلا);
    أرجع ret;
}

صحيح av_opt_سیٹ_array(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags,
                     بنانشانی صحيح شروع_elem, بنانشانی صحيح nb_elems,
                     تعداد AVOptionType val_type, ثابت فراغ *val)
{
    ثابت size_t elem_ناپ_val = opt_type_desc[TYPE_ادھار(val_type)].ناپ;

    ثابت AVOption *o;
    ثابت AVOptionArrayDef *arr;
    فراغ *نشانہ_obj;

    فراغ *parray;
    فراغ *new_elems;
    بنانشانی *array_ناپ, new_ناپ;
    size_t elem_ناپ;

    صحيح ret = 0;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, 0, &نشانہ_obj, &o, &parray);
    إذا (ret < 0)
        أرجع ret;

    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_ناپ = opt_array_pcount(parray);
    elem_ناپ  = opt_type_desc[TYPE_ادھار(o->type)].ناپ;

    إذا (شروع_elem > *array_ناپ)
        أرجع AVERROR(EINVAL);

    // compute new array size
    إذا (!val) {
        إذا (*array_ناپ - شروع_elem < nb_elems)
            أرجع AVERROR(EINVAL);

        new_ناپ = *array_ناپ - nb_elems;
    } وإلا إذا (تلاش_flags & AV_OPT_ARRAY_REPLACE) {
        إذا (شروع_elem >= UINT_MAX - nb_elems)
            أرجع AVERROR(EINVAL);

        new_ناپ = FFMAX(*array_ناپ, شروع_elem + nb_elems);
    } وإلا {
        إذا (nb_elems >= UINT_MAX - *array_ناپ)
            أرجع AVERROR(EINVAL);

        new_ناپ = *array_ناپ + nb_elems;
    }

    إذا (arr &&
        ((arr->ناپ_max && new_ناپ > arr->ناپ_max) ||
         (arr->ناپ_min && new_ناپ < arr->ناپ_min)))
        أرجع AVERROR(EINVAL);

    // desired operation is shrinking the array
    إذا (!val) {
        فراغ *array = *(فراغ**)parray;

        لكل (بنانشانی i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, شروع_elem + i));
        }

        إذا (new_ناپ > 0) {
            memmove(opt_array_pelem(o, array, شروع_elem),
                    opt_array_pelem(o, array, شروع_elem + nb_elems),
                    elem_ناپ * (*array_ناپ - شروع_elem - nb_elems));

            array = av_realloc_array(array, new_ناپ, elem_ناپ);
            إذا (!array)
                أرجع AVERROR(ENOMEM);

            *(فراغ**)parray = array;
        } وإلا
            av_freep(parray);

        *array_ناپ = new_ناپ;

        أرجع 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_ناپ);
    إذا (!new_elems)
        أرجع AVERROR(ENOMEM);

    // convert/validate each new element
    لكل (بنانشانی i = 0; i < nb_elems; i++) {
        فراغ       *dst = opt_array_pelem(o, new_elems, i);
        ثابت فراغ *src = (uint8_t*)val + i * elem_ناپ_val;

        مزدوج     عدد = 1.0;
        صحيح        den = 1;
        int64_t intnum = 1;

        إذا (val_type == TYPE_ادھار(o->type)) {
            صحيح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            إذا (ret < 0)
                اذهب fail;

            // validate the range for numeric options
            err = read_نمبر(o, dst, &عدد, &den, &intnum);
            إذا (err >= 0 && TYPE_ادھار(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < عدد * intnum || o->min * den > عدد * intnum)) {
                عدد = den ? عدد * intnum / den : (عدد && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       شروع_elem + i, o->name, عدد, o->min, o->max);
                ret = AVERROR(ERANGE);
                اذهب fail;
            }
        } وإلا إذا (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_سیٹ_elem(obj, نشانہ_obj, o, *(ثابت حرف **)src, dst);
            إذا (ret < 0)
                اذهب fail;
        } وإلا إذا (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            بدل (val_type) {
            حالة AV_OPT_TYPE_INT:       intnum = *(صحيح*)src;                اكسر;
            حالة AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            اكسر;
            حالة AV_OPT_TYPE_FLOAT:     عدد    = *(عائم*)src;              اكسر;
            حالة AV_OPT_TYPE_DOUBLE:    عدد    = *(مزدوج*)src;             اكسر;
            حالة AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->عدد;
                                        den    = ((AVRational*)src)->den;   اكسر;
            افتراضي: av_assert0(0);
            }

            ret = write_نمبر(obj, o, dst, عدد, den, intnum, 0);
            إذا (ret < 0)
                اذهب fail;
        } وإلا {
            ret = AVERROR(ENOSYS);
            اذهب fail;
        }
    }

    // commit new elements to the array
    إذا (شروع_elem == 0 && nb_elems == new_ناپ) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_ناپ);
        *(فراغ**)parray = new_elems;
        *array_ناپ     = nb_elems;

        new_elems = عدم;
        nb_elems  = 0;
    } وإلا {
        فراغ *array = av_realloc_array(*(فراغ**)parray, new_ناپ, elem_ناپ);
        إذا (!array) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }

        إذا (تلاش_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            لكل (بنانشانی i = شروع_elem; i < FFMIN(شروع_elem + nb_elems, *array_ناپ); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } وإلا {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, شروع_elem + nb_elems),
                    opt_array_pelem(o, array, شروع_elem),
                    elem_ناپ * (*array_ناپ - شروع_elem));
        }

        حافظہ_نقل((uint8_t*)array + elem_ناپ * شروع_elem, new_elems, elem_ناپ * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(فراغ**)parray = array;
        *array_ناپ     = new_ناپ;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    أرجع ret;
}

صحيح av_opt_query_ranges(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *کلید, صحيح flags)
{
    صحيح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحيح (*callback)(AVOptionRanges **, فراغ *obj, ثابت حرف *کلید, صحيح flags) = c->query_ranges;

    إذا (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, کلید, flags);
    إذا (ret >= 0) {
        إذا (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    أرجع ret;
}

صحيح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *کلید, صحيح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(فراغ*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *میدان = av_opt_لبھو(obj, کلید, عدم, 0, flags);
    صحيح ret;

    *ranges_arg = عدم;

    إذا (!ranges || !range || !range_array || !میدان) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->قدر_min = میدان->min;
    range->قدر_max = میدان->max;

    بدل (میدان->type) {
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_PIXEL_FMT:
    حالة AV_OPT_TYPE_SAMPLE_FMT:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_COLOR:
        اكسر;
    حالة AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->قدر_min = -1;
        range->قدر_max = ودھ_توں_ودھ_عدد;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = ودھ_توں_ودھ_عدد;
        اكسر;
    حالة AV_OPT_TYPE_IMAGE_ناپ:
        range->component_min = 0;
        range->component_max = ودھ_توں_ودھ_عدد/128/8;
        range->قدر_min = 0;
        range->قدر_max = ودھ_توں_ودھ_عدد/8;
        اكسر;
    حالة AV_OPT_TYPE_VIDEO_شرح:
        range->component_min = 1;
        range->component_max = ودھ_توں_ودھ_عدد;
        range->قدر_min = 1;
        range->قدر_max = ودھ_توں_ودھ_عدد;
        اكسر;
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    *ranges_arg = ranges;
    أرجع 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    أرجع ret;
}

فراغ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    صحيح i;
    AVOptionRanges *ranges = *rangesp;

    إذا (!ranges)
        أرجع;

    لكل (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        إذا (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

صحيح av_opt_is_سیٹ_منزل_default(فراغ *obj, ثابت AVOption *o)
{
    int64_t i64;
    مزدوج d;
    AVRational q;
    صحيح ret, w, h;
    حرف *str;
    فراغ *dst;

    إذا (!o || !obj)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->وتھ;

    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت حرف *def = o->default_val.arr ? o->default_val.arr->def : عدم;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        إذا (ret < 0)
            أرجع ret;

        إذا (!!val != !!def)
            ret = 0;
        وإلا إذا (val)
            ret = !strcmp(val, def);
        وإلا
            ret = 1;

        av_freep(&val);

        أرجع ret;
    }

    بدل (o->type) {
    حالة AV_OPT_TYPE_CONST:
        أرجع 1;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_PIXEL_FMT:
    حالة AV_OPT_TYPE_SAMPLE_FMT:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        read_نمبر(o, dst, عدم, عدم, &i64);
        أرجع o->default_val.i64 == i64;
    حالة AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        إذا (o->default_val.str) {
            إذا ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                أرجع ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        أرجع ret;
    }
    حالة AV_OPT_TYPE_STRING:
        str = *(حرف **)dst;
        إذا (str == o->default_val.str) //2 NULLs
            أرجع 1;
        إذا (!str || !o->default_val.str) //1 NULL
            أرجع 0;
        أرجع !strcmp(str, o->default_val.str);
    حالة AV_OPT_TYPE_DOUBLE:
        d = *(مزدوج *)dst;
        أرجع o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالة AV_OPT_TYPE_FLOAT:
        d = *(عائم *)dst;
        أرجع (عائم)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, ودھ_توں_ودھ_عدد);
        أرجع !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالة AV_OPT_TYPE_ثنائی: {
        بنية {
            uint8_t *انکڑے;
            صحيح ناپ;
        } tmp = {0};
        صحيح opt_ناپ = *(صحيح *)((فراغ **)dst + 1);
        فراغ *opt_ptr = *(فراغ **)dst;
        إذا (!opt_ناپ && (!o->default_val.str || !لڑی_لمبائی(o->default_val.str)))
            أرجع 1;
        إذا (!opt_ناپ ||  !o->default_val.str || !لڑی_لمبائی(o->default_val.str ))
            أرجع 0;
        إذا (opt_ناپ != لڑی_لمبائی(o->default_val.str) / 2)
            أرجع 0;
        ret = سیٹ_string_ثنائی(عدم, عدم, o->default_val.str, &tmp.انکڑے);
        إذا (!ret)
            ret = !memcmp(opt_ptr, tmp.انکڑے, tmp.ناپ);
        av_free(tmp.انکڑے);
        أرجع ret;
    }
    حالة AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = عدم;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionary_اندراج *en1 = عدم;
        ثابت AVDictionary_اندراج *en2 = عدم;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        إذا (ret < 0) {
            av_dict_free(&dict1);
            أرجع ret;
        }
        افعل {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } طالما (en1 && en2 && !strcmp(en1->کلید, en2->کلید) && !strcmp(en1->قدر, en2->قدر));
        av_dict_free(&dict1);
        أرجع (!en1 && !en2);
    }
    حالة AV_OPT_TYPE_IMAGE_ناپ:
        إذا (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        وإلا إذا ((ret = av_parse_video_ناپ(&w, &h, o->default_val.str)) < 0)
            أرجع ret;
        أرجع (w == *(صحيح *)dst) && (h == *((صحيح *)dst+1));
    حالة AV_OPT_TYPE_VIDEO_شرح:
        q = (AVRational){0, 0};
        إذا (o->default_val.str) {
            إذا ((ret = av_parse_video_شرح(&q, o->default_val.str)) < 0)
                أرجع ret;
        }
        أرجع !av_cmp_q(*(AVRational*)dst, q);
    حالة AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        إذا (o->default_val.str) {
            إذا ((ret = av_parse_color(color, o->default_val.str, -1, عدم)) < 0)
                أرجع ret;
        }
        أرجع !memcmp(color, dst, حجم(color));
    }
    افتراضي:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        اكسر;
    }
    أرجع AVERROR_PATCHWELCOME;
}

صحيح av_opt_is_سیٹ_منزل_default_by_name(فراغ *obj, ثابت حرف *name, صحيح تلاش_flags)
{
    ثابت AVOption *o;
    فراغ *نشانہ;
    إذا (!obj)
        أرجع AVERROR(EINVAL);
    o = av_opt_find2(obj, name, عدم, 0, تلاش_flags, &نشانہ);
    إذا (!o)
        أرجع AVERROR_OPTION_NOT_لبھیا;
    أرجع av_opt_is_سیٹ_منزل_default(نشانہ, o);
}

ساكن صحيح opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, صحيح *cnt,
                         AVBPrint *bprint, ثابت حرف کلید_val_sep, ثابت حرف جوڑے_sep)
{
    ثابت AVOption *o = عدم;
    فراغ *بچہ = عدم;
    uint8_t *buf;
    صحيح ret;
    ثابت حرف special_chars[] = {جوڑے_sep, کلید_val_sep, '\0'};

    إذا (flags & AV_OPT_SERIALIZE_تلاش_CHILDREN)
        طالما (بچہ = av_opt_بچہ_اگلا(obj, بچہ)) {
            ret = opt_serialize(بچہ, opt_flags, flags, cnt, bprint,
                                کلید_val_sep, جوڑے_sep);
            إذا (ret < 0)
                أرجع ret;
        }

    طالما (o = av_opt_اگلا(obj, o)) {
        إذا (o->type == AV_OPT_TYPE_CONST)
            استمر;
        إذا ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            إذا ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                إذا (o->flags == opt_flags)
                    استمر;
            } وإلا إذا ((o->flags & opt_flags) == opt_flags)
                استمر;
        } وإلا {
            إذا ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                استمر;
            وإلا إذا (((o->flags & opt_flags) != opt_flags))
                استمر;
        }
        إذا (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_سیٹ_منزل_default(obj, o) > 0)
            استمر;
        إذا ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, عدم);
            أرجع ret;
        }
        إذا (buf) {
            إذا ((*cnt)++)
                av_bprint_append_انکڑے(bprint, &جوڑے_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
            av_bprint_append_انکڑے(bprint, &کلید_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    أرجع 0;
}

صحيح av_opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, حرف **بفر,
                     ثابت حرف کلید_val_sep, ثابت حرف جوڑے_sep)
{
    AVBPrint bprint;
    صحيح ret, cnt = 0;

    إذا (جوڑے_sep == '\0' || کلید_val_sep == '\0' || جوڑے_sep == کلید_val_sep ||
        جوڑے_sep == '\\' || کلید_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        أرجع AVERROR(EINVAL);
    }

    إذا (!obj || !بفر)
        أرجع AVERROR(EINVAL);

    *بفر = عدم;
    av_bprint_init(&bprint, 64, AV_BPRINT_ناپ_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        کلید_val_sep, جوڑے_sep);
    إذا (ret < 0)
        أرجع ret;

    ret = av_bprint_finalize(&bprint, بفر);
    إذا (ret < 0)
        أرجع ret;
    أرجع 0;
}
