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

#وصف_ڪريو TYPE_بنياد(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ثابت AVOption *av_opt_ايندڙ(ثابت فراغ *obj, ثابت AVOption *آخري)
{
    ثابت AVClass *class;
    إذا (!obj)
        أرجع عدم;
    class = *(ثابت AVClass**)obj;
    إذا (!آخري && class && class->option && class->option[0].name)
        أرجع class->option;
    إذا (آخري && آخري[1].name)
        أرجع ++آخري;
    أرجع عدم;
}

ساكن ثابت بنية {
    size_t      سائيز;
    ثابت حرف *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { حجم(بنانشان),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { حجم(صحيح),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { حجم(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { حجم(بنانشان),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { حجم(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { حجم(مزدوج),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { حجم(عائم),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { حجم(حرف *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { حجم(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ٻٽو]        = { حجم(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { حجم(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_سائيز]    = { حجم(صحيح[2]),         "<image_size>" },
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
    حالة AV_OPT_TYPE_IMAGE_سائيز:
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

ساكن فراغ *opt_array_pelem(ثابت AVOption *o, فراغ *array, بنانشان idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    أرجع (uint8_t *)array + idx * opt_type_desc[TYPE_بنياد(o->type)].سائيز;
}

ساكن بنانشان *opt_array_pcount(ثابت فراغ *parray)
{
    أرجع (بنانشان *)((ثابت فراغ * ثابت *)parray + 1);
}

ساكن فراغ opt_free_elem(تعداد AVOptionType type, فراغ *ptr)
{
    بدل (TYPE_بنياد(type)) {
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_ٻٽو:
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

ساكن فراغ opt_free_array(ثابت AVOption *o, فراغ *parray, بنانشان *ڳڻپ)
{
    لكل (بنانشان i = 0; i < *ڳڻپ; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(فراغ **)parray, i));

    av_freep(parray);
    *ڳڻپ = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ساكن صحيح opt_سيٽ_init(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags,
                        صحيح require_type,
                        فراغ **ptgt, ثابت AVOption **po, فراغ **pdst)
{
    فراغ *logctx;
    ثابت AVOption *o;
    فراغ *tgt;

    o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &tgt);
    إذا (!o || (!tgt && !(ڳولا_flags & AV_OPT_ڳولا_FAKE_OBJ)))
        أرجع AVERROR_OPTION_NOT_مليو;

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
        بنانشان *state_flags = عدم;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        إذا (class->state_flags_وٿي)
            state_flags = (بنانشان*)((uint8_t*)tgt + class->state_flags_وٿي);

        إذا (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            إذا (class->state_flags_وٿي)
                state_flags = (بنانشان*)((uint8_t*)obj + class->state_flags_وٿي);
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
        *pdst = tgt ? ((uint8_t *)tgt) + o->وٿي : عدم;

    أرجع 0;
}

ساكن AVRational double_منزل_rational(مزدوج d)
{
     AVRational r = av_d2q(d, 1 << 24);
     إذا ((!r.انگ || !r.den) && d)
         r = av_d2q(d, وڌ_کان_وڌ_عدد);
     أرجع r;
}

ساكن صحيح read_عدد(ثابت AVOption *o, ثابت فراغ *dst, مزدوج *انگ, صحيح *den, int64_t *intnum)
{
    بدل (TYPE_بنياد(o->type)) {
    حالة AV_OPT_TYPE_FLAGS:
        *intnum = *(بنانشان صحيح*)dst;
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
        *intnum = *(بنانشان صحيح *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_FLOAT:
        *انگ = *(عائم *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_DOUBLE:
        *انگ = *(مزدوج *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->انگ;
        *den    = ((AVRational *)dst)->den;
        أرجع 0;
    حالة AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        أرجع 0;
    }
    أرجع AVERROR(EINVAL);
}

ساكن صحيح write_عدد(فراغ *obj, ثابت AVOption *o, فراغ *dst,
                        مزدوج انگ, صحيح den, int64_t intnum,
                        صحيح ignore_range)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_بنياد(o->type);

    إذا (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < انگ * intnum || o->min * den > انگ * intnum)) {
        انگ = den ? انگ * intnum / den : (انگ && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               انگ, o->name, o->min, o->max);
        أرجع AVERROR(ERANGE);
    }
    إذا (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        مزدوج d = انگ*intnum/den;
        إذا (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   انگ*intnum/den, o->name);
            أرجع AVERROR(ERANGE);
        }
    }

    إذا (!dst)
        أرجع 0;

    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *(تعداد AVPixelFormat *)dst = llrint(انگ / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *(تعداد AVSampleFormat *)dst = llrint(انگ / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
        *(صحيح *)dst = llrint(انگ / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:{
        مزدوج d = انگ / den;
        إذا (intnum == 1 && d == (مزدوج)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } وإلا
            *(int64_t *)dst = llrint(d) * intnum;
        اكسر;}
    حالة AV_OPT_TYPE_UINT64:{
        مزدوج d = انگ / den;
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
        *(عائم *)dst = انگ * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_DOUBLE:
        *(مزدوج    *)dst = انگ * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
    حالة AV_OPT_TYPE_VIDEO_شرح:
        إذا ((صحيح) انگ == انگ)
            *(AVRational *)dst = (AVRational) { انگ *intnum, den };
        وإلا
            *(AVRational *)dst = double_منزل_rational(انگ * intnum / den);
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

ساكن صحيح سيٽ_string_ٻٽو(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحيح *lendst;
    uint8_t *bin, *ptr;
    صحيح len;

    إذا (dst) {
        lendst = (صحيح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    إذا (!val || !(len = لڙي_ڊيگهه(val)))
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

ساكن صحيح سيٽ_string(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    إذا (!dst)
        أرجع 0;
    av_freep(dst);
    إذا (!val)
        أرجع 0;
    *dst = av_strdup(val);
    أرجع *dst ? 0 : AVERROR(ENOMEM);
}

#وصف_ڪريو DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ساكن صحيح سيٽ_string_عدد(فراغ *obj, فراغ *هدف_obj, ثابت AVOption *o, ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_بنياد(o->type);
    صحيح ret = 0;

    إذا (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_شرح) {
        صحيح انگ, den;
        حرف c;
        إذا (لڙي_مان_پڙهو(val, "%d%*1[:/]%d%c", &انگ, &den, &c) == 2) {
            إذا ((ret = write_عدد(obj, o, dst, 1, den, انگ, 0)) >= 0)
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
            مزدوج const_قدرون[64];
            ثابت حرف * const_نالا[64];
            صحيح ڳولا_flags = (o->flags & AV_OPT_FLAG_ٻار_CONSTS) ? AV_OPT_ڳولا_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_ڳوليو(هدف_obj, i ? buf : val, o->unit, 0, ڳولا_flags);
            إذا (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                إذا (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } وإلا {
                إذا (o->unit) {
                    لكل (o_named = عدم; o_named = av_opt_ايندڙ(هدف_obj, o_named); ) {
                        إذا (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            إذا (ci + 6 >= FF_ARRAY_ELEMS(const_قدرون)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                أرجع AVERROR_PATCHWELCOME;
                            }
                            const_نالا [ci  ] = o_named->name;
                            const_قدرون[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_نالا [ci  ] = "default";
                const_قدرون[ci++] = DEFAULT_NUMVAL(o);
                const_نالا [ci  ] = "max";
                const_قدرون[ci++] = o->max;
                const_نالا [ci  ] = "min";
                const_قدرون[ci++] = o->min;
                const_نالا [ci  ] = "none";
                const_قدرون[ci++] = 0;
                const_نالا [ci  ] = "all";
                const_قدرون[ci++] = ~0;
                const_نالا [ci] = عدم;
                const_قدرون[ci] = 0;

                res = av_اظهار_parse_and_eval(&d, i ? buf : val, const_نالا,
                                            const_قدرون, عدم, عدم, عدم, عدم, عدم, 0, obj);
                إذا (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    أرجع res;
                }
            }
        }
        إذا (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(بنانشان صحيح*)dst;
            إذا (cmd == '+')
                d = intnum | (int64_t)d;
            وإلا إذا (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        إذا ((ret = write_عدد(obj, o, dst, d, 1, 1, 0)) < 0)
            أرجع ret;
        val += i;
        إذا (!i || !*val)
            أرجع 0;
    }
}

ساكن صحيح سيٽ_string_image_سائيز(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
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
    ret = av_parse_video_سائيز(&tmp[0], &tmp[1], val);
    إذا (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        أرجع ret;
    }
    إذا (dst)
        يادگيري_نقل(dst, tmp, حجم(tmp));
    أرجع ret;
}

ساكن صحيح سيٽ_string_video_شرح(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
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

ساكن صحيح سيٽ_string_color(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
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
            يادگيري_نقل(dst, tmp, حجم(tmp));
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

ساكن صحيح سيٽ_string_bool(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح n;

    إذا (!val)
        أرجع 0;

    إذا (!strcmp(val, "auto")) {
        n = -1;
    } وإلا إذا (av_ميلاپ_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } وإلا إذا (av_ميلاپ_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } وإلا {
        حرف *پڇاڙي = عدم;
        n = strtol(val, &پڇاڙي, 10);
        إذا (val + لڙي_ڊيگهه(val) != پڇاڙي)
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

ساكن صحيح سيٽ_string_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
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
            حرف *پڇ;
            fmt = strtol(val, &پڇ, 0);
            إذا (*پڇ || (بنانشان)fmt >= fmt_nb) {
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

ساكن صحيح سيٽ_string_pixel_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع سيٽ_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساكن صحيح get_sample_fmt(ثابت حرف *name)
{
    أرجع av_get_sample_fmt(name);
}

ساكن صحيح سيٽ_string_sample_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع سيٽ_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساكن صحيح سيٽ_string_dict(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
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

ساكن صحيح سيٽ_string_channel_layout(فراغ *obj, ثابت AVOption *o,
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

ساكن صحيح opt_سيٽ_elem(فراغ *obj, فراغ *هدف_obj, ثابت AVOption *o,
                        ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_بنياد(o->type);
    صحيح ret;

    إذا (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_سائيز &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        أرجع AVERROR(EINVAL);

    بدل (type) {
    حالة AV_OPT_TYPE_BOOL:
        أرجع سيٽ_string_bool(obj, o, val, dst);
    حالة AV_OPT_TYPE_STRING:
        أرجع سيٽ_string(obj, o, val, dst);
    حالة AV_OPT_TYPE_ٻٽو:
        أرجع سيٽ_string_ٻٽو(obj, o, val, dst);
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_RATIONAL:
        أرجع سيٽ_string_عدد(obj, هدف_obj, o, val, dst);
    حالة AV_OPT_TYPE_IMAGE_سائيز:
        أرجع سيٽ_string_image_سائيز(obj, o, val, dst);
    حالة AV_OPT_TYPE_VIDEO_شرح: {
        AVRational tmp;
        ret = سيٽ_string_video_شرح(obj, o, val, &tmp);
        إذا (ret < 0)
            أرجع ret;
        أرجع write_عدد(obj, o, dst, 1, tmp.den, tmp.انگ, 0);
    }
    حالة AV_OPT_TYPE_PIXEL_FMT:
        أرجع سيٽ_string_pixel_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        أرجع سيٽ_string_sample_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            إذا (val) {
                إذا ((ret = av_parse_وقت(&usecs, val, 1)) < 0) {
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
        أرجع سيٽ_string_color(obj, o, val, dst);
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = سيٽ_string_channel_layout(obj, o, val, dst);
        إذا (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        أرجع ret;
    حالة AV_OPT_TYPE_DICT:
        أرجع سيٽ_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    أرجع AVERROR(EINVAL);
}

ساكن صحيح opt_سيٽ_array(فراغ *obj, فراغ *هدف_obj, ثابت AVOption *o,
                         ثابت حرف *val, فراغ *dst)
{
    ثابت AVOptionArrayDef *arr = o->default_val.arr;
    ثابت size_t      elem_سائيز = opt_type_desc[TYPE_بنياد(o->type)].سائيز;
    ثابت uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = عدم;

    فراغ      *logctx = dst ? obj : عدم;
    فراغ       *elems = عدم;
    بنانشان nb_elems = 0;
    صحيح ret;

    إذا (val && *val) {
        str = av_malloc(لڙي_ڊيگهه(val) + 1);
        إذا (!str)
            أرجع AVERROR(ENOMEM);
    }

    // split and unescape the string
    طالما (val && *val) {
        uint8_t *p = str;
        فراغ *tmp;

        إذا (arr && arr->سائيز_max && nb_elems >= arr->سائيز_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->سائيز_max, o->name);
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

        tmp = av_realloc_array(elems, nb_elems + 1, elem_سائيز);
        إذا (!tmp) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_سائيز);

        ret = opt_سيٽ_elem(obj, هدف_obj, o, str, tmp);
        إذا (ret < 0)
            اذهب fail;
        nb_elems++;
    }
    av_freep(&str);

    إذا (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    إذا (arr && nb_elems < arr->سائيز_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->سائيز_min, o->name);
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

صحيح av_opt_سيٽ(فراغ *obj, ثابت حرف *name, ثابت حرف *val, صحيح ڳولا_flags)
{
    فراغ *dst, *هدف_obj;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, 0, &هدف_obj, &o, &dst);
    إذا (ret < 0)
        أرجع ret;

    أرجع ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_سيٽ_array : opt_سيٽ_elem)(obj, هدف_obj, o, val, dst);
}

#وصف_ڪريو OPT_EVAL_عدد(name, opttype, vartype)                         \
صحيح av_opt_eval_ ## name(فراغ *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## ٻاهريون_3)        \
{                                                                       \
    إذا (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        أرجع AVERROR(EINVAL);                                         \
    أرجع سيٽ_string_عدد(obj, obj, o, val, name ## ٻاهريون_3);           \
}

OPT_EVAL_عدد(flags,  AV_OPT_TYPE_FLAGS,    صحيح)
OPT_EVAL_عدد(صحيح,    AV_OPT_TYPE_INT,      صحيح)
OPT_EVAL_عدد(uint,   AV_OPT_TYPE_UINT,     بنانشان)
OPT_EVAL_عدد(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_عدد(عائم,  AV_OPT_TYPE_FLOAT,    عائم)
OPT_EVAL_عدد(مزدوج, AV_OPT_TYPE_DOUBLE,   مزدوج)
OPT_EVAL_عدد(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ساكن صحيح سيٽ_عدد(فراغ *obj, ثابت حرف *name, مزدوج انگ, صحيح den, int64_t intnum,
                      صحيح ڳولا_flags, صحيح require_type)
{
    فراغ *dst;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, require_type, عدم, &o, &dst);
    إذا (ret < 0)
        أرجع ret;
    إذا (dst)
        ret = write_عدد(obj, o, dst, انگ, den, intnum, 0);

    أرجع ret;
}

صحيح av_opt_سيٽ_int(فراغ *obj, ثابت حرف *name, int64_t val, صحيح ڳولا_flags)
{
    أرجع سيٽ_عدد(obj, name, 1, 1, val, ڳولا_flags, 0);
}

صحيح av_opt_سيٽ_double(فراغ *obj, ثابت حرف *name, مزدوج val, صحيح ڳولا_flags)
{
    أرجع سيٽ_عدد(obj, name, val, 1, 1, ڳولا_flags, 0);
}

صحيح av_opt_سيٽ_q(فراغ *obj, ثابت حرف *name, AVRational val, صحيح ڳولا_flags)
{
    أرجع سيٽ_عدد(obj, name, val.انگ, val.den, 1, ڳولا_flags, 0);
}

صحيح av_opt_سيٽ_bin(فراغ *obj, ثابت حرف *name, ثابت uint8_t *val, صحيح len, صحيح ڳولا_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحيح *lendst;
    صحيح ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, AV_OPT_TYPE_ٻٽو,
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
        يادگيري_نقل(ptr, val, len);
    }

    أرجع 0;
}

صحيح av_opt_سيٽ_image_سائيز(فراغ *obj, ثابت حرف *name, صحيح w, صحيح h, صحيح ڳولا_flags)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, AV_OPT_TYPE_IMAGE_سائيز,
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

صحيح av_opt_سيٽ_video_شرح(فراغ *obj, ثابت حرف *name, AVRational val, صحيح ڳولا_flags)
{
    أرجع سيٽ_عدد(obj, name, val.انگ, val.den, 1, ڳولا_flags, AV_OPT_TYPE_VIDEO_شرح);
}

ساكن صحيح سيٽ_format(فراغ *obj, ثابت حرف *name, صحيح fmt, صحيح ڳولا_flags,
                      تعداد AVOptionType type, ثابت حرف *desc, صحيح nb_fmts)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح min, max, ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, type, عدم, &o, (فراغ**)&dst);
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

صحيح av_opt_سيٽ_pixel_fmt(فراغ *obj, ثابت حرف *name, تعداد AVPixelFormat fmt, صحيح ڳولا_flags)
{
    أرجع سيٽ_format(obj, name, fmt, ڳولا_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحيح av_opt_سيٽ_sample_fmt(فراغ *obj, ثابت حرف *name, تعداد AVSampleFormat fmt, صحيح ڳولا_flags)
{
    أرجع سيٽ_format(obj, name, fmt, ڳولا_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحيح av_opt_سيٽ_dict_val(فراغ *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحيح ڳولا_flags)
{
    AVDictionary **dst;
    صحيح ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, AV_OPT_TYPE_DICT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    أرجع ret;
}

صحيح av_opt_سيٽ_chlayout(فراغ *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحيح ڳولا_flags)
{
    AVChannelLayout *dst;
    صحيح ret;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, AV_OPT_TYPE_CHLAYOUT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    أرجع ret;
}

ساكن فراغ format_duration(حرف *buf, size_t سائيز, int64_t d)
{
    حرف *e;

    av_assert0(سائيز >= 25);
    إذا (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        سائيز--;
        d = -d;
    }
    إذا (d == INT64_MAX)
        snprintf(buf, سائيز, "INT64_MAX");
    وإلا إذا (d == INT64_MIN)
        snprintf(buf, سائيز, "INT64_MIN");
    وإلا إذا (d > (int64_t)3600*1000000)
        snprintf(buf, سائيز, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحيح)((d / 60000000) % 60),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا إذا (d > 60*1000000)
        snprintf(buf, سائيز, "%d:%02d.%06d",
                 (صحيح)(d / 60000000),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا
        snprintf(buf, سائيز, "%d.%06d",
                 (صحيح)(d / 1000000),
                 (صحيح)(d % 1000000));
    e = buf + لڙي_ڊيگهه(buf);
    طالما (e > buf && e[-1] == '0')
        *(--e) = 0;
    إذا (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ساكن صحيح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت فراغ *dst, صحيح ڳولا_flags)
{
    صحيح ret;

    بدل (TYPE_بنياد(o->type)) {
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
        ret = snprintf(*pbuf, buf_len, "%u", *(بنانشان *)dst);
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
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->انگ, ((AVRational *)dst)->den);
        اكسر;
    حالة AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        اكسر;
    حالة AV_OPT_TYPE_STRING:
        إذا (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } وإلا إذا (ڳولا_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = عدم;
            أرجع 0;
        } وإلا {
            *pbuf = av_strdup("");
        }
        أرجع *pbuf ? 0 : AVERROR(ENOMEM);
    حالة AV_OPT_TYPE_ٻٽو: {
        ثابت uint8_t *bin;
        صحيح len;

        إذا (!*(uint8_t **)dst && (ڳولا_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        len = *(صحيح *)(((uint8_t *)dst) + حجم(uint8_t *));
        إذا ((uint64_t)len * 2 + 1 > وڌ_کان_وڌ_عدد)
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
    حالة AV_OPT_TYPE_IMAGE_سائيز:
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
        ret = لڙي_ڊيگهه(*pbuf); // no overflow possible, checked by an assert
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
        إذا (!*(AVDictionary **)dst && (ڳولا_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        أرجع av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    افتراضي:
        أرجع AVERROR(EINVAL);
    }

    أرجع ret;
}

ساكن صحيح opt_get_array(ثابت AVOption *o, فراغ *dst, uint8_t **ٻاهريون_val)
{
    ثابت بنانشان ڳڻپ = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = عدم;
    size_t   str_len = 0;
    صحيح ret;

    *ٻاهريون_val = عدم;

    لكل (بنانشان i = 0; i < ڳڻپ; i++) {
        uint8_t buf[128], *ٻاهريون = buf;
        size_t ٻاهريون_len;

        ret = opt_get_elem(o, &ٻاهريون, حجم(buf),
                           opt_array_pelem(o, *(فراغ **)dst, i), 0);
        إذا (ret < 0)
            اذهب fail;

        ٻاهريون_len = لڙي_ڊيگهه(ٻاهريون);
        إذا (ٻاهريون_len > SIZE_MAX / 2 - !!i ||
            !!i + ٻاهريون_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            اذهب fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + ٻاهريون_len * 2 + !!i);
        إذا (ret < 0)
            اذهب fail;

        // add separator if needed
        إذا (i)
            str[str_len++] = sep;

        // escape the element
        لكل (بنانشان j = 0; j < ٻاهريون_len; j++) {
            uint8_t val = ٻاهريون[j];
            إذا (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        إذا (ٻاهريون != buf)
            av_freep(&ٻاهريون);
        إذا (ret < 0) {
            av_freep(&str);
            أرجع ret;
        }
    }

    *ٻاهريون_val = str;

    أرجع 0;
}

صحيح av_opt_get(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, uint8_t **ٻاهريون_val)
{
    فراغ *dst, *هدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    uint8_t *ٻاهريون, buf[128];
    صحيح ret;

    إذا (!o || !هدف_obj || (o->وٿي<=0 && o->type != AV_OPT_TYPE_CONST))
        أرجع AVERROR_OPTION_NOT_مليو;

    إذا (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)هدف_obj + o->وٿي;

    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, ٻاهريون_val);
        إذا (ret < 0)
            أرجع ret;
        إذا (!*ٻاهريون_val && !(ڳولا_flags & AV_OPT_ALLOW_NULL)) {
            *ٻاهريون_val = av_strdup("");
            إذا (!*ٻاهريون_val)
               أرجع AVERROR(ENOMEM);
        }
        أرجع 0;
    }

    buf[0] = 0;
    ٻاهريون = buf;
    ret = opt_get_elem(o, &ٻاهريون, حجم(buf), dst, ڳولا_flags);
    إذا (ret < 0)
        أرجع ret;
    إذا (ٻاهريون != buf) {
        *ٻاهريون_val = ٻاهريون;
        أرجع 0;
    }

    إذا (ret >= حجم(buf))
        أرجع AVERROR(EINVAL);
    *ٻاهريون_val = av_strdup(ٻاهريون);
    أرجع *ٻاهريون_val ? 0 : AVERROR(ENOMEM);
}

ساكن صحيح get_عدد(فراغ *obj, ثابت حرف *name, مزدوج *انگ, صحيح *den, int64_t *intnum,
                      صحيح ڳولا_flags)
{
    فراغ *dst, *هدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t *)هدف_obj) + o->وٿي;

    أرجع read_عدد(o, dst, انگ, den, intnum);
}

صحيح av_opt_get_int(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, int64_t *ٻاهريون_val)
{
    int64_t intnum = 1;
    مزدوج انگ = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_عدد(obj, name, &انگ, &den, &intnum, ڳولا_flags)) < 0)
        أرجع ret;
    إذا (انگ == den)
        *ٻاهريون_val = intnum;
    وإلا
        *ٻاهريون_val = انگ * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_double(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, مزدوج *ٻاهريون_val)
{
    int64_t intnum = 1;
    مزدوج انگ = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_عدد(obj, name, &انگ, &den, &intnum, ڳولا_flags)) < 0)
        أرجع ret;
    *ٻاهريون_val = انگ * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_q(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, AVRational *ٻاهريون_val)
{
    int64_t intnum = 1;
    مزدوج انگ = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_عدد(obj, name, &انگ, &den, &intnum, ڳولا_flags)) < 0)
        أرجع ret;

    إذا (انگ == 1.0 && (صحيح)intnum == intnum)
        *ٻاهريون_val = (AVRational){intnum, den};
    وإلا
        *ٻاهريون_val = double_منزل_rational(انگ*intnum/den);
    أرجع 0;
}

صحيح av_opt_get_image_سائيز(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, صحيح *w_ٻاهريون, صحيح *h_ٻاهريون)
{
    فراغ *dst, *هدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (o->type != AV_OPT_TYPE_IMAGE_سائيز) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)هدف_obj) + o->وٿي;
    إذا (w_ٻاهريون) *w_ٻاهريون = *(صحيح *)dst;
    إذا (h_ٻاهريون) *h_ٻاهريون = *((صحيح *)dst+1);
    أرجع 0;
}

صحيح av_opt_get_video_شرح(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, AVRational *ٻاهريون_val)
{
    أرجع av_opt_get_q(obj, name, ڳولا_flags, ٻاهريون_val);
}

ساكن صحيح get_format(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, فراغ *ٻاهريون_fmt,
                      تعداد AVOptionType type, ثابت حرف *desc)
{
    فراغ *dst, *هدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)هدف_obj) + o->وٿي;
    إذا (type == AV_OPT_TYPE_PIXEL_FMT)
        *(تعداد AVPixelFormat *)ٻاهريون_fmt = *(تعداد AVPixelFormat *)dst;
    وإلا
        *(تعداد AVSampleFormat*)ٻاهريون_fmt = *(تعداد AVSampleFormat*)dst;

    أرجع 0;
}

صحيح av_opt_get_pixel_fmt(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, تعداد AVPixelFormat *ٻاهريون_fmt)
{
    أرجع get_format(obj, name, ڳولا_flags, ٻاهريون_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحيح av_opt_get_sample_fmt(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, تعداد AVSampleFormat *ٻاهريون_fmt)
{
    أرجع get_format(obj, name, ڳولا_flags, ٻاهريون_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحيح av_opt_get_chlayout(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, AVChannelLayout *cl)
{
    فراغ *dst, *هدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)هدف_obj) + o->وٿي;
    أرجع av_channel_layout_copy(cl, dst);
}

صحيح av_opt_get_dict_val(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags, AVDictionary **ٻاهريون_val)
{
    فراغ *هدف_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);

    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (o->type != AV_OPT_TYPE_DICT)
        أرجع AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)هدف_obj) + o->وٿي);

    أرجع av_dict_copy(ٻاهريون_val, src, 0);
}

صحيح av_opt_flag_is_سيٽ(فراغ *obj, ثابت حرف *ميدان_name, ثابت حرف *flag_name)
{
    ثابت AVOption *ميدان = av_opt_ڳوليو(obj, ميدان_name, عدم, 0, 0);
    ثابت AVOption *flag  = av_opt_ڳوليو(obj, flag_name,
                                        ميدان ? ميدان->unit : عدم, 0, 0);
    int64_t res;

    إذا (!ميدان || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, ميدان_name, 0, &res) < 0)
        أرجع 0;
    أرجع res & flag->default_val.i64;
}

ساكن فراغ log_int_قدر(فراغ *av_log_obj, صحيح level, int64_t i)
{
    إذا (i == وڌ_کان_وڌ_عدد) {
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
    إذا      (d == وڌ_کان_وڌ_عدد) {
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
    طالما ((opt = av_opt_ايندڙ(obj, opt)))
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
    طالما ((opt = av_opt_ايندڙ(obj, opt))) {
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
                     تعداد AVOptionType والد_type)
{
    ثابت تعداد AVOptionType type = TYPE_بنياد(o->type);

    إذا (o->type == AV_OPT_TYPE_CONST && (TYPE_بنياد(والد_type) == AV_OPT_TYPE_INT || TYPE_بنياد(والد_type) == AV_OPT_TYPE_INT64))
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
    إذا (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ٻٽو)
        أرجع;
    إذا ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_سائيز ||
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
        AVRational q = av_d2q(opt->default_val.dbl, وڌ_کان_وڌ_عدد);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.انگ, q.den); }
        اكسر;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_COLOR:
    حالة AV_OPT_TYPE_IMAGE_سائيز:
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
                     صحيح req_flags, صحيح rej_flags, تعداد AVOptionType والد_type)
{
    ثابت AVOption *opt = عدم;
    AVOptionRanges *r;
    صحيح i;

    طالما ((opt = av_opt_ايندڙ(obj, opt))) {
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

        log_type(av_log_obj, opt, والد_type);

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

        إذا (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_ڳولا_FAKE_OBJ) >= 0) {
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

فراغ av_opt_سيٽ_defaults(فراغ *s)
{
    av_opt_سيٽ_defaults2(s, 0, 0);
}

فراغ av_opt_سيٽ_defaults2(فراغ *s, صحيح نقاب_2, صحيح flags)
{
    ثابت AVOption *opt = عدم;
    طالما ((opt = av_opt_ايندڙ(s, opt))) {
        فراغ *dst = ((uint8_t*)s) + opt->وٿي;

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
                opt_سيٽ_array(s, s, opt, arr->def, dst);

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
                write_عدد(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
            حالة AV_OPT_TYPE_FLOAT: {
                مزدوج val;
                val = opt->default_val.dbl;
                write_عدد(s, opt, dst, val, 1, 1, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, وڌ_کان_وڌ_عدد);
                write_عدد(s, opt, dst, 1, val.den, val.انگ, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_COLOR:
                سيٽ_string_color(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_STRING:
                سيٽ_string(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_IMAGE_سائيز:
                سيٽ_string_image_سائيز(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_VIDEO_شرح:
                سيٽ_string_video_شرح(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_ٻٽو:
                سيٽ_string_ٻٽو(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_CHLAYOUT:
                سيٽ_string_channel_layout(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_DICT:
                سيٽ_string_dict(s, opt, opt->default_val.str, dst);
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
ساكن صحيح parse_ڪنجي_قدر_pair(فراغ *ctx, ثابت حرف **buf,
                                ثابت حرف *ڪنجي_val_sep, ثابت حرف *جوڙا_sep)
{
    حرف *ڪنجي = av_get_token(buf, ڪنجي_val_sep);
    حرف *val;
    صحيح ret;

    إذا (!ڪنجي)
        أرجع AVERROR(ENOMEM);

    إذا (*ڪنجي && strspn(*buf, ڪنجي_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوڙا_sep);
        إذا (!val) {
            av_freep(&ڪنجي);
            أرجع AVERROR(ENOMEM);
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", ڪنجي);
        av_free(ڪنجي);
        أرجع AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", ڪنجي, val);

    ret = av_opt_سيٽ(ctx, ڪنجي, val, AV_OPT_ڳولا_CHILDREN);
    إذا (ret == AVERROR_OPTION_NOT_مليو)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", ڪنجي);

    av_free(ڪنجي);
    av_free(val);
    أرجع ret;
}

صحيح av_سيٽ_options_string(فراغ *ctx, ثابت حرف *opts,
                          ثابت حرف *ڪنجي_val_sep, ثابت حرف *جوڙا_sep)
{
    صحيح ret, ڳڻپ = 0;

    إذا (!opts)
        أرجع 0;

    طالما (*opts) {
        إذا ((ret = parse_ڪنجي_قدر_pair(ctx, &opts, ڪنجي_val_sep, جوڙا_sep)) < 0)
            أرجع ret;
        ڳڻپ++;

        إذا (*opts)
            opts++;
    }

    أرجع ڳڻپ;
}

#وصف_ڪريو WHITESPACES " \n\t\r"

ساكن صحيح is_ڪنجي_char(حرف c)
{
    أرجع (بنانشان)((c | 32) - 'a') < 26 ||
           (بنانشان)(c - '0') < 10 ||
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
ساكن صحيح get_ڪنجي(ثابت حرف **ropts, ثابت حرف *delim, حرف **rkey)
{
    ثابت حرف *opts = *ropts;
    ثابت حرف *ڪنجي_شروعات, *ڪنجي_پڇاڙي;

    ڪنجي_شروعات = opts += strspn(opts, WHITESPACES);
    طالما (is_ڪنجي_char(*opts))
        opts++;
    ڪنجي_پڇاڙي = opts;
    opts += strspn(opts, WHITESPACES);
    إذا (!*opts || !strchr(delim, *opts))
        أرجع AVERROR(EINVAL);
    opts++;
    إذا (!(*rkey = av_malloc(ڪنجي_پڇاڙي - ڪنجي_شروعات + 1)))
        أرجع AVERROR(ENOMEM);
    يادگيري_نقل(*rkey, ڪنجي_شروعات, ڪنجي_پڇاڙي - ڪنجي_شروعات);
    (*rkey)[ڪنجي_پڇاڙي - ڪنجي_شروعات] = 0;
    *ropts = opts;
    أرجع 0;
}

صحيح av_opt_get_ڪنجي_قدر(ثابت حرف **ropts,
                         ثابت حرف *ڪنجي_val_sep, ثابت حرف *جوڙا_sep,
                         بنانشان flags,
                         حرف **rkey, حرف **rval)
{
    صحيح ret;
    حرف *ڪنجي = عدم, *val;
    ثابت حرف *opts = *ropts;

    إذا ((ret = get_ڪنجي(&opts, ڪنجي_val_sep, &ڪنجي)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_ڪنجي))
        أرجع AVERROR(EINVAL);
    إذا (!(val = av_get_token(&opts, جوڙا_sep))) {
        av_free(ڪنجي);
        أرجع AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = ڪنجي;
    *rval  = val;
    أرجع 0;
}

صحيح av_opt_سيٽ_from_string(فراغ *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *ڪنجي_val_sep, ثابت حرف *جوڙا_sep)
{
    صحيح ret, ڳڻپ = 0;
    ثابت حرف *dummy_shorthand = عدم;
    ثابت حرف *ڪنجي;

    إذا (!opts)
        أرجع 0;
    إذا (!shorthand)
        shorthand = &dummy_shorthand;

    طالما (*opts) {
        حرف *parsed_ڪنجي, *قدر;
        ret = av_opt_get_ڪنجي_قدر(&opts, ڪنجي_val_sep, جوڙا_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_ڪنجي : 0,
                                   &parsed_ڪنجي, &قدر);
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
        إذا (parsed_ڪنجي) {
            ڪنجي = parsed_ڪنجي;
            طالما (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } وإلا {
            ڪنجي = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", ڪنجي, قدر);
        إذا ((ret = av_opt_سيٽ(ctx, ڪنجي, قدر, 0)) < 0) {
            إذا (ret == AVERROR_OPTION_NOT_مليو)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", ڪنجي);
            av_free(قدر);
            av_free(parsed_ڪنجي);
            أرجع ret;
        }

        av_free(قدر);
        av_free(parsed_ڪنجي);
        ڳڻپ++;
    }
    أرجع ڳڻپ;
}

فراغ av_opt_free(فراغ *obj)
{
    ثابت AVOption *o = عدم;
    طالما ((o = av_opt_ايندڙ(obj, o))) {
        فراغ *pitem = (uint8_t *)obj + o->وٿي;

        إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        وإلا
            opt_free_elem(o->type, pitem);
    }
}

صحيح av_opt_سيٽ_dict2(فراغ *obj, AVDictionary **options, صحيح ڳولا_flags)
{
    ثابت AVDictionary_داخلا *t = عدم;
    AVDictionary    *tmp = عدم;
    صحيح ret;

    إذا (!options)
        أرجع 0;

    طالما ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_سيٽ(obj, t->ڪنجي, t->قدر, ڳولا_flags);
        إذا (ret == AVERROR_OPTION_NOT_مليو)
            ret = av_dict_سيٽ(&tmp, t->ڪنجي, t->قدر, AV_DICT_MULTIKEY);
        إذا (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->ڪنجي, t->قدر);
            av_dict_free(&tmp);
            أرجع ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    أرجع 0;
}

صحيح av_opt_سيٽ_dict(فراغ *obj, AVDictionary **options)
{
    أرجع av_opt_سيٽ_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_ڳوليو(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحيح opt_flags, صحيح ڳولا_flags)
{
    أرجع av_opt_find2(obj, name, unit, opt_flags, ڳولا_flags, عدم);
}

ثابت AVOption *av_opt_find2(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحيح opt_flags, صحيح ڳولا_flags, فراغ **هدف_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = عدم;

    إذا(!obj)
        أرجع عدم;

    c= *(AVClass**)obj;

    إذا (!c)
        أرجع عدم;

    إذا (ڳولا_flags & AV_OPT_ڳولا_CHILDREN) {
        إذا (ڳولا_flags & AV_OPT_ڳولا_FAKE_OBJ) {
            فراغ *iter = عدم;
            ثابت AVClass *ٻار;
            طالما (ٻار = av_opt_ٻار_class_iterate(c, &iter))
                إذا (o = av_opt_find2(&ٻار, name, unit, opt_flags, ڳولا_flags, عدم))
                    أرجع o;
        } وإلا {
            فراغ *ٻار = عدم;
            طالما (ٻار = av_opt_ٻار_ايندڙ(obj, ٻار))
                إذا (o = av_opt_find2(ٻار, name, unit, opt_flags, ڳولا_flags, هدف_obj))
                    أرجع o;
        }
    }

    طالما (o = av_opt_ايندڙ(obj, o)) {
        إذا (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            إذا (هدف_obj) {
                إذا (!(ڳولا_flags & AV_OPT_ڳولا_FAKE_OBJ))
                    *هدف_obj = obj;
                وإلا
                    *هدف_obj = عدم;
            }
            أرجع o;
        }
    }
    أرجع عدم;
}

فراغ *av_opt_ٻار_ايندڙ(فراغ *obj, فراغ *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    إذا (c->ٻار_ايندڙ)
        أرجع c->ٻار_ايندڙ(obj, prev);
    أرجع عدم;
}

ثابت AVClass *av_opt_ٻار_class_iterate(ثابت AVClass *والد, فراغ **iter)
{
    إذا (والد->ٻار_class_iterate)
        أرجع والد->ٻار_class_iterate(iter);
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
    } وإلا إذا (type == AV_OPT_TYPE_ٻٽو) {
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
            إذا (dlayout->ترتيب == AV_CHANNEL_ترتيب_CUSTOM &&
                slayout->ترتيب == AV_CHANNEL_ترتيب_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = عدم;
            أرجع av_channel_layout_copy(dst, src);
        }
    } وإلا إذا (opt_is_pod(type)) {
        size_t سائيز = opt_type_desc[type].سائيز;
        يادگيري_نقل(dst, src, سائيز);
    } وإلا {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        أرجع AVERROR(EINVAL);
    }

    أرجع 0;
}

ساكن صحيح opt_copy_array(فراغ *logctx, ثابت AVOption *o,
                          فراغ **pdst, ثابت فراغ * ثابت *psrc)
{
    بنانشان nb_elems = *opt_array_pcount(psrc);
    فراغ         *dst = عدم;
    صحيح ret;

    إذا (*pdst == *psrc) {
        *pdst                   = عدم;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_بنياد(o->type)].سائيز);
    إذا (!dst)
        أرجع AVERROR(ENOMEM);

    لكل (بنانشان i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_بنياد(o->type),
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

    طالما ((o = av_opt_ايندڙ(src, o))) {
        فراغ *ميدان_dst = (uint8_t *)dst + o->وٿي;
        فراغ *ميدان_src = (uint8_t *)src + o->وٿي;

        صحيح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       ميدان_dst, ميدان_src) :
                  opt_copy_elem (dst, o->type, ميدان_dst, ميدان_src);
        إذا (err < 0)
            ret = err;
    }
    أرجع ret;
}

صحيح av_opt_get_array_سائيز(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags,
                          بنانشان صحيح *ٻاهريون_val)
{
    فراغ *هدف_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray = (uint8_t *)هدف_obj + o->وٿي;
    *ٻاهريون_val = *opt_array_pcount(parray);

    أرجع 0;
}

صحيح av_opt_get_array(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags,
                     بنانشان صحيح شروعات_elem, بنانشان صحيح nb_elems,
                     تعداد AVOptionType ٻاهريون_type, فراغ *ٻاهريون_val)
{
    ثابت size_t elem_سائيز_ٻاهريون = opt_type_desc[TYPE_بنياد(ٻاهريون_type)].سائيز;

    ثابت AVOption *o;
    فراغ *هدف_obj;

    ثابت فراغ *parray;
    بنانشان array_سائيز;

    صحيح ret;

    o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف_obj);
    إذا (!o || !هدف_obj)
        أرجع AVERROR_OPTION_NOT_مليو;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (ٻاهريون_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray     = (uint8_t *)هدف_obj + o->وٿي;
    array_سائيز = *opt_array_pcount(parray);

    إذا (شروعات_elem >= array_سائيز ||
        array_سائيز - شروعات_elem < nb_elems)
        أرجع AVERROR(EINVAL);

    لكل (بنانشان i = 0; i < nb_elems; i++) {
        ثابت فراغ *src = opt_array_pelem(o, *(فراغ**)parray, شروعات_elem + i);
        فراغ       *dst = (uint8_t*)ٻاهريون_val + i * elem_سائيز_ٻاهريون;

        إذا (ٻاهريون_type == TYPE_بنياد(o->type)) {
            ret = opt_copy_elem(obj, ٻاهريون_type, dst, src);
            إذا (ret < 0)
                اذهب fail;
        } وإلا إذا (ٻاهريون_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *ٻاهريون = buf;

            ret = opt_get_elem(o, &ٻاهريون, حجم(buf), src, ڳولا_flags);
            إذا (ret < 0)
                اذهب fail;

            إذا (ٻاهريون == buf) {
                ٻاهريون = av_strdup(buf);
                إذا (!ٻاهريون) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
            }

            *(uint8_t**)dst = ٻاهريون;
        } وإلا إذا (ٻاهريون_type == AV_OPT_TYPE_INT64    ||
                   ٻاهريون_type == AV_OPT_TYPE_DOUBLE   ||
                   ٻاهريون_type == AV_OPT_TYPE_RATIONAL) {
            مزدوج     انگ = 1.0;
            صحيح        den = 1;
            int64_t intnum = 1;

            ret = read_عدد(o, src, &انگ, &den, &intnum);
            إذا (ret < 0)
                اذهب fail;

            بدل (ٻاهريون_type) {
            حالة AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (انگ == den) ?  intnum : انگ * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
                *(مزدوج*)dst = انگ * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (انگ == 1.0 && (صحيح)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_منزل_rational(انگ * intnum / den);
                اكسر;
            افتراضي: av_assert0(0);
            }
        } وإلا
            أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
fail:
    لكل (بنانشان i = 0; i < nb_elems; i++)
        opt_free_elem(ٻاهريون_type, (uint8_t*)ٻاهريون_val + i * elem_سائيز_ٻاهريون);
    أرجع ret;
}

صحيح av_opt_سيٽ_array(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags,
                     بنانشان صحيح شروعات_elem, بنانشان صحيح nb_elems,
                     تعداد AVOptionType val_type, ثابت فراغ *val)
{
    ثابت size_t elem_سائيز_val = opt_type_desc[TYPE_بنياد(val_type)].سائيز;

    ثابت AVOption *o;
    ثابت AVOptionArrayDef *arr;
    فراغ *هدف_obj;

    فراغ *parray;
    فراغ *new_elems;
    بنانشان *array_سائيز, new_سائيز;
    size_t elem_سائيز;

    صحيح ret = 0;

    ret = opt_سيٽ_init(obj, name, ڳولا_flags, 0, &هدف_obj, &o, &parray);
    إذا (ret < 0)
        أرجع ret;

    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_سائيز = opt_array_pcount(parray);
    elem_سائيز  = opt_type_desc[TYPE_بنياد(o->type)].سائيز;

    إذا (شروعات_elem > *array_سائيز)
        أرجع AVERROR(EINVAL);

    // compute new array size
    إذا (!val) {
        إذا (*array_سائيز - شروعات_elem < nb_elems)
            أرجع AVERROR(EINVAL);

        new_سائيز = *array_سائيز - nb_elems;
    } وإلا إذا (ڳولا_flags & AV_OPT_ARRAY_REPLACE) {
        إذا (شروعات_elem >= UINT_MAX - nb_elems)
            أرجع AVERROR(EINVAL);

        new_سائيز = FFMAX(*array_سائيز, شروعات_elem + nb_elems);
    } وإلا {
        إذا (nb_elems >= UINT_MAX - *array_سائيز)
            أرجع AVERROR(EINVAL);

        new_سائيز = *array_سائيز + nb_elems;
    }

    إذا (arr &&
        ((arr->سائيز_max && new_سائيز > arr->سائيز_max) ||
         (arr->سائيز_min && new_سائيز < arr->سائيز_min)))
        أرجع AVERROR(EINVAL);

    // desired operation is shrinking the array
    إذا (!val) {
        فراغ *array = *(فراغ**)parray;

        لكل (بنانشان i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, شروعات_elem + i));
        }

        إذا (new_سائيز > 0) {
            memmove(opt_array_pelem(o, array, شروعات_elem),
                    opt_array_pelem(o, array, شروعات_elem + nb_elems),
                    elem_سائيز * (*array_سائيز - شروعات_elem - nb_elems));

            array = av_realloc_array(array, new_سائيز, elem_سائيز);
            إذا (!array)
                أرجع AVERROR(ENOMEM);

            *(فراغ**)parray = array;
        } وإلا
            av_freep(parray);

        *array_سائيز = new_سائيز;

        أرجع 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_سائيز);
    إذا (!new_elems)
        أرجع AVERROR(ENOMEM);

    // convert/validate each new element
    لكل (بنانشان i = 0; i < nb_elems; i++) {
        فراغ       *dst = opt_array_pelem(o, new_elems, i);
        ثابت فراغ *src = (uint8_t*)val + i * elem_سائيز_val;

        مزدوج     انگ = 1.0;
        صحيح        den = 1;
        int64_t intnum = 1;

        إذا (val_type == TYPE_بنياد(o->type)) {
            صحيح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            إذا (ret < 0)
                اذهب fail;

            // validate the range for numeric options
            err = read_عدد(o, dst, &انگ, &den, &intnum);
            إذا (err >= 0 && TYPE_بنياد(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < انگ * intnum || o->min * den > انگ * intnum)) {
                انگ = den ? انگ * intnum / den : (انگ && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       شروعات_elem + i, o->name, انگ, o->min, o->max);
                ret = AVERROR(ERANGE);
                اذهب fail;
            }
        } وإلا إذا (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_سيٽ_elem(obj, هدف_obj, o, *(ثابت حرف **)src, dst);
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
            حالة AV_OPT_TYPE_FLOAT:     انگ    = *(عائم*)src;              اكسر;
            حالة AV_OPT_TYPE_DOUBLE:    انگ    = *(مزدوج*)src;             اكسر;
            حالة AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->انگ;
                                        den    = ((AVRational*)src)->den;   اكسر;
            افتراضي: av_assert0(0);
            }

            ret = write_عدد(obj, o, dst, انگ, den, intnum, 0);
            إذا (ret < 0)
                اذهب fail;
        } وإلا {
            ret = AVERROR(ENOSYS);
            اذهب fail;
        }
    }

    // commit new elements to the array
    إذا (شروعات_elem == 0 && nb_elems == new_سائيز) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_سائيز);
        *(فراغ**)parray = new_elems;
        *array_سائيز     = nb_elems;

        new_elems = عدم;
        nb_elems  = 0;
    } وإلا {
        فراغ *array = av_realloc_array(*(فراغ**)parray, new_سائيز, elem_سائيز);
        إذا (!array) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }

        إذا (ڳولا_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            لكل (بنانشان i = شروعات_elem; i < FFMIN(شروعات_elem + nb_elems, *array_سائيز); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } وإلا {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, شروعات_elem + nb_elems),
                    opt_array_pelem(o, array, شروعات_elem),
                    elem_سائيز * (*array_سائيز - شروعات_elem));
        }

        يادگيري_نقل((uint8_t*)array + elem_سائيز * شروعات_elem, new_elems, elem_سائيز * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(فراغ**)parray = array;
        *array_سائيز     = new_سائيز;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    أرجع ret;
}

صحيح av_opt_query_ranges(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *ڪنجي, صحيح flags)
{
    صحيح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحيح (*callback)(AVOptionRanges **, فراغ *obj, ثابت حرف *ڪنجي, صحيح flags) = c->query_ranges;

    إذا (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, ڪنجي, flags);
    إذا (ret >= 0) {
        إذا (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    أرجع ret;
}

صحيح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *ڪنجي, صحيح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(فراغ*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *ميدان = av_opt_ڳوليو(obj, ڪنجي, عدم, 0, flags);
    صحيح ret;

    *ranges_arg = عدم;

    إذا (!ranges || !range || !range_array || !ميدان) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->قدر_min = ميدان->min;
    range->قدر_max = ميدان->max;

    بدل (ميدان->type) {
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
        range->قدر_max = وڌ_کان_وڌ_عدد;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = وڌ_کان_وڌ_عدد;
        اكسر;
    حالة AV_OPT_TYPE_IMAGE_سائيز:
        range->component_min = 0;
        range->component_max = وڌ_کان_وڌ_عدد/128/8;
        range->قدر_min = 0;
        range->قدر_max = وڌ_کان_وڌ_عدد/8;
        اكسر;
    حالة AV_OPT_TYPE_VIDEO_شرح:
        range->component_min = 1;
        range->component_max = وڌ_کان_وڌ_عدد;
        range->قدر_min = 1;
        range->قدر_max = وڌ_کان_وڌ_عدد;
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

صحيح av_opt_is_سيٽ_منزل_default(فراغ *obj, ثابت AVOption *o)
{
    int64_t i64;
    مزدوج d;
    AVRational q;
    صحيح ret, w, h;
    حرف *str;
    فراغ *dst;

    إذا (!o || !obj)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->وٿي;

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
        read_عدد(o, dst, عدم, عدم, &i64);
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
        q = av_d2q(o->default_val.dbl, وڌ_کان_وڌ_عدد);
        أرجع !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالة AV_OPT_TYPE_ٻٽو: {
        بنية {
            uint8_t *معلومات;
            صحيح سائيز;
        } tmp = {0};
        صحيح opt_سائيز = *(صحيح *)((فراغ **)dst + 1);
        فراغ *opt_ptr = *(فراغ **)dst;
        إذا (!opt_سائيز && (!o->default_val.str || !لڙي_ڊيگهه(o->default_val.str)))
            أرجع 1;
        إذا (!opt_سائيز ||  !o->default_val.str || !لڙي_ڊيگهه(o->default_val.str ))
            أرجع 0;
        إذا (opt_سائيز != لڙي_ڊيگهه(o->default_val.str) / 2)
            أرجع 0;
        ret = سيٽ_string_ٻٽو(عدم, عدم, o->default_val.str, &tmp.معلومات);
        إذا (!ret)
            ret = !memcmp(opt_ptr, tmp.معلومات, tmp.سائيز);
        av_free(tmp.معلومات);
        أرجع ret;
    }
    حالة AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = عدم;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionary_داخلا *en1 = عدم;
        ثابت AVDictionary_داخلا *en2 = عدم;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        إذا (ret < 0) {
            av_dict_free(&dict1);
            أرجع ret;
        }
        افعل {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } طالما (en1 && en2 && !strcmp(en1->ڪنجي, en2->ڪنجي) && !strcmp(en1->قدر, en2->قدر));
        av_dict_free(&dict1);
        أرجع (!en1 && !en2);
    }
    حالة AV_OPT_TYPE_IMAGE_سائيز:
        إذا (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        وإلا إذا ((ret = av_parse_video_سائيز(&w, &h, o->default_val.str)) < 0)
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

صحيح av_opt_is_سيٽ_منزل_default_by_name(فراغ *obj, ثابت حرف *name, صحيح ڳولا_flags)
{
    ثابت AVOption *o;
    فراغ *هدف;
    إذا (!obj)
        أرجع AVERROR(EINVAL);
    o = av_opt_find2(obj, name, عدم, 0, ڳولا_flags, &هدف);
    إذا (!o)
        أرجع AVERROR_OPTION_NOT_مليو;
    أرجع av_opt_is_سيٽ_منزل_default(هدف, o);
}

ساكن صحيح opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, صحيح *cnt,
                         AVBPrint *bprint, ثابت حرف ڪنجي_val_sep, ثابت حرف جوڙا_sep)
{
    ثابت AVOption *o = عدم;
    فراغ *ٻار = عدم;
    uint8_t *buf;
    صحيح ret;
    ثابت حرف special_chars[] = {جوڙا_sep, ڪنجي_val_sep, '\0'};

    إذا (flags & AV_OPT_SERIALIZE_ڳولا_CHILDREN)
        طالما (ٻار = av_opt_ٻار_ايندڙ(obj, ٻار)) {
            ret = opt_serialize(ٻار, opt_flags, flags, cnt, bprint,
                                ڪنجي_val_sep, جوڙا_sep);
            إذا (ret < 0)
                أرجع ret;
        }

    طالما (o = av_opt_ايندڙ(obj, o)) {
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
        إذا (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_سيٽ_منزل_default(obj, o) > 0)
            استمر;
        إذا ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, عدم);
            أرجع ret;
        }
        إذا (buf) {
            إذا ((*cnt)++)
                av_bprint_append_معلومات(bprint, &جوڙا_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_گهڻائي_BACKSLASH, 0);
            av_bprint_append_معلومات(bprint, &ڪنجي_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_گهڻائي_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    أرجع 0;
}

صحيح av_opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, حرف **بفر,
                     ثابت حرف ڪنجي_val_sep, ثابت حرف جوڙا_sep)
{
    AVBPrint bprint;
    صحيح ret, cnt = 0;

    إذا (جوڙا_sep == '\0' || ڪنجي_val_sep == '\0' || جوڙا_sep == ڪنجي_val_sep ||
        جوڙا_sep == '\\' || ڪنجي_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        أرجع AVERROR(EINVAL);
    }

    إذا (!obj || !بفر)
        أرجع AVERROR(EINVAL);

    *بفر = عدم;
    av_bprint_init(&bprint, 64, AV_BPRINT_سائيز_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        ڪنجي_val_sep, جوڙا_sep);
    إذا (ret < 0)
        أرجع ret;

    ret = av_bprint_finalize(&bprint, بفر);
    إذا (ret < 0)
        أرجع ret;
    أرجع 0;
}
