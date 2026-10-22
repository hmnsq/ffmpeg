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

#تعریف_کړه TYPE_بنسټ(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ثابت AVOption *av_opt_بل(ثابت فراغ *obj, ثابت AVOption *وروستی)
{
    ثابت AVClass *class;
    إذا (!obj)
        أرجع عدم;
    class = *(ثابت AVClass**)obj;
    إذا (!وروستی && class && class->option && class->option[0].name)
        أرجع class->option;
    إذا (وروستی && وروستی[1].name)
        أرجع ++وروستی;
    أرجع عدم;
}

ساكن ثابت بنية {
    size_t      اندازه;
    ثابت حرف *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { حجم(بینښه),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { حجم(صحيح),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { حجم(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { حجم(بینښه),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { حجم(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { حجم(مزدوج),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { حجم(عائم),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { حجم(حرف *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { حجم(AVRational),     "<rational>" },
    [AV_OPT_TYPE_دوګونی]        = { حجم(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { حجم(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_اندازه]    = { حجم(صحيح[2]),         "<image_size>" },
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
    حالة AV_OPT_TYPE_IMAGE_اندازه:
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

ساكن فراغ *opt_array_pelem(ثابت AVOption *o, فراغ *array, بینښه idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    أرجع (uint8_t *)array + idx * opt_type_desc[TYPE_بنسټ(o->type)].اندازه;
}

ساكن بینښه *opt_array_pcount(ثابت فراغ *parray)
{
    أرجع (بینښه *)((ثابت فراغ * ثابت *)parray + 1);
}

ساكن فراغ opt_free_elem(تعداد AVOptionType type, فراغ *ptr)
{
    بدل (TYPE_بنسټ(type)) {
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_دوګونی:
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

ساكن فراغ opt_free_array(ثابت AVOption *o, فراغ *parray, بینښه *شمېر)
{
    لكل (بینښه i = 0; i < *شمېر; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(فراغ **)parray, i));

    av_freep(parray);
    *شمېر = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ساكن صحيح opt_سېټ_init(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags,
                        صحيح require_type,
                        فراغ **ptgt, ثابت AVOption **po, فراغ **pdst)
{
    فراغ *logctx;
    ثابت AVOption *o;
    فراغ *tgt;

    o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &tgt);
    إذا (!o || (!tgt && !(پلټنه_flags & AV_OPT_پلټنه_FAKE_OBJ)))
        أرجع AVERROR_OPTION_NOT_وموندل;

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
        بینښه *state_flags = عدم;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        إذا (class->state_flags_دننه_واټن)
            state_flags = (بینښه*)((uint8_t*)tgt + class->state_flags_دننه_واټن);

        إذا (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            إذا (class->state_flags_دننه_واټن)
                state_flags = (بینښه*)((uint8_t*)obj + class->state_flags_دننه_واټن);
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
        *pdst = tgt ? ((uint8_t *)tgt) + o->دننه_واټن : عدم;

    أرجع 0;
}

ساكن AVRational double_منزل_rational(مزدوج d)
{
     AVRational r = av_d2q(d, 1 << 24);
     إذا ((!r.عدد || !r.den) && d)
         r = av_d2q(d, لوی_عدد);
     أرجع r;
}

ساكن صحيح read_شمېره(ثابت AVOption *o, ثابت فراغ *dst, مزدوج *عدد, صحيح *den, int64_t *intnum)
{
    بدل (TYPE_بنسټ(o->type)) {
    حالة AV_OPT_TYPE_FLAGS:
        *intnum = *(بینښه صحيح*)dst;
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
        *intnum = *(بینښه صحيح *)dst;
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

ساكن صحيح write_شمېره(فراغ *obj, ثابت AVOption *o, فراغ *dst,
                        مزدوج عدد, صحيح den, int64_t intnum,
                        صحيح ignore_range)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_بنسټ(o->type);

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

ساكن صحيح سېټ_string_دوګونی(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحيح *lendst;
    uint8_t *bin, *ptr;
    صحيح len;

    إذا (dst) {
        lendst = (صحيح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    إذا (!val || !(len = مزي_اوږدوالی(val)))
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

ساكن صحيح سېټ_string(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    إذا (!dst)
        أرجع 0;
    av_freep(dst);
    إذا (!val)
        أرجع 0;
    *dst = av_strdup(val);
    أرجع *dst ? 0 : AVERROR(ENOMEM);
}

#تعریف_کړه DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ساكن صحيح سېټ_string_شمېره(فراغ *obj, فراغ *موخه_obj, ثابت AVOption *o, ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_بنسټ(o->type);
    صحيح ret = 0;

    إذا (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_شرح) {
        صحيح عدد, den;
        حرف c;
        إذا (له_مزي_ولوله(val, "%d%*1[:/]%d%c", &عدد, &den, &c) == 2) {
            إذا ((ret = write_شمېره(obj, o, dst, 1, den, عدد, 0)) >= 0)
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
            مزدوج const_ارزښتونه[64];
            ثابت حرف * const_نومونه[64];
            صحيح پلټنه_flags = (o->flags & AV_OPT_FLAG_ماشوم_CONSTS) ? AV_OPT_پلټنه_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_پیدا_کړه(موخه_obj, i ? buf : val, o->unit, 0, پلټنه_flags);
            إذا (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                إذا (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } وإلا {
                إذا (o->unit) {
                    لكل (o_named = عدم; o_named = av_opt_بل(موخه_obj, o_named); ) {
                        إذا (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            إذا (ci + 6 >= FF_ARRAY_ELEMS(const_ارزښتونه)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                أرجع AVERROR_PATCHWELCOME;
                            }
                            const_نومونه [ci  ] = o_named->name;
                            const_ارزښتونه[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_نومونه [ci  ] = "default";
                const_ارزښتونه[ci++] = DEFAULT_NUMVAL(o);
                const_نومونه [ci  ] = "max";
                const_ارزښتونه[ci++] = o->max;
                const_نومونه [ci  ] = "min";
                const_ارزښتونه[ci++] = o->min;
                const_نومونه [ci  ] = "none";
                const_ارزښتونه[ci++] = 0;
                const_نومونه [ci  ] = "all";
                const_ارزښتونه[ci++] = ~0;
                const_نومونه [ci] = عدم;
                const_ارزښتونه[ci] = 0;

                res = av_بیان_parse_and_eval(&d, i ? buf : val, const_نومونه,
                                            const_ارزښتونه, عدم, عدم, عدم, عدم, عدم, 0, obj);
                إذا (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    أرجع res;
                }
            }
        }
        إذا (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(بینښه صحيح*)dst;
            إذا (cmd == '+')
                d = intnum | (int64_t)d;
            وإلا إذا (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        إذا ((ret = write_شمېره(obj, o, dst, d, 1, 1, 0)) < 0)
            أرجع ret;
        val += i;
        إذا (!i || !*val)
            أرجع 0;
    }
}

ساكن صحيح سېټ_string_image_اندازه(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
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
    ret = av_parse_video_اندازه(&tmp[0], &tmp[1], val);
    إذا (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        أرجع ret;
    }
    إذا (dst)
        حافظه_نقل(dst, tmp, حجم(tmp));
    أرجع ret;
}

ساكن صحيح سېټ_string_video_شرح(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
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

ساكن صحيح سېټ_string_color(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
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
            حافظه_نقل(dst, tmp, حجم(tmp));
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

ساكن صحيح سېټ_string_bool(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح n;

    إذا (!val)
        أرجع 0;

    إذا (!strcmp(val, "auto")) {
        n = -1;
    } وإلا إذا (av_سمون_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } وإلا إذا (av_سمون_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } وإلا {
        حرف *پای_ټکی = عدم;
        n = strtol(val, &پای_ټکی, 10);
        إذا (val + مزي_اوږدوالی(val) != پای_ټکی)
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

ساكن صحيح سېټ_string_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
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
            حرف *لکۍ;
            fmt = strtol(val, &لکۍ, 0);
            إذا (*لکۍ || (بینښه)fmt >= fmt_nb) {
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

ساكن صحيح سېټ_string_pixel_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع سېټ_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساكن صحيح get_sample_fmt(ثابت حرف *name)
{
    أرجع av_get_sample_fmt(name);
}

ساكن صحيح سېټ_string_sample_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع سېټ_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساكن صحيح سېټ_string_dict(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
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

ساكن صحيح سېټ_string_channel_layout(فراغ *obj, ثابت AVOption *o,
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

ساكن صحيح opt_سېټ_elem(فراغ *obj, فراغ *موخه_obj, ثابت AVOption *o,
                        ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_بنسټ(o->type);
    صحيح ret;

    إذا (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_اندازه &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        أرجع AVERROR(EINVAL);

    بدل (type) {
    حالة AV_OPT_TYPE_BOOL:
        أرجع سېټ_string_bool(obj, o, val, dst);
    حالة AV_OPT_TYPE_STRING:
        أرجع سېټ_string(obj, o, val, dst);
    حالة AV_OPT_TYPE_دوګونی:
        أرجع سېټ_string_دوګونی(obj, o, val, dst);
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_RATIONAL:
        أرجع سېټ_string_شمېره(obj, موخه_obj, o, val, dst);
    حالة AV_OPT_TYPE_IMAGE_اندازه:
        أرجع سېټ_string_image_اندازه(obj, o, val, dst);
    حالة AV_OPT_TYPE_VIDEO_شرح: {
        AVRational tmp;
        ret = سېټ_string_video_شرح(obj, o, val, &tmp);
        إذا (ret < 0)
            أرجع ret;
        أرجع write_شمېره(obj, o, dst, 1, tmp.den, tmp.عدد, 0);
    }
    حالة AV_OPT_TYPE_PIXEL_FMT:
        أرجع سېټ_string_pixel_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        أرجع سېټ_string_sample_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            إذا (val) {
                إذا ((ret = av_parse_وخت(&usecs, val, 1)) < 0) {
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
        أرجع سېټ_string_color(obj, o, val, dst);
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = سېټ_string_channel_layout(obj, o, val, dst);
        إذا (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        أرجع ret;
    حالة AV_OPT_TYPE_DICT:
        أرجع سېټ_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    أرجع AVERROR(EINVAL);
}

ساكن صحيح opt_سېټ_array(فراغ *obj, فراغ *موخه_obj, ثابت AVOption *o,
                         ثابت حرف *val, فراغ *dst)
{
    ثابت AVOptionArrayDef *arr = o->default_val.arr;
    ثابت size_t      elem_اندازه = opt_type_desc[TYPE_بنسټ(o->type)].اندازه;
    ثابت uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = عدم;

    فراغ      *logctx = dst ? obj : عدم;
    فراغ       *elems = عدم;
    بینښه nb_elems = 0;
    صحيح ret;

    إذا (val && *val) {
        str = av_malloc(مزي_اوږدوالی(val) + 1);
        إذا (!str)
            أرجع AVERROR(ENOMEM);
    }

    // split and unescape the string
    طالما (val && *val) {
        uint8_t *p = str;
        فراغ *tmp;

        إذا (arr && arr->اندازه_max && nb_elems >= arr->اندازه_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->اندازه_max, o->name);
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

        tmp = av_realloc_array(elems, nb_elems + 1, elem_اندازه);
        إذا (!tmp) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_اندازه);

        ret = opt_سېټ_elem(obj, موخه_obj, o, str, tmp);
        إذا (ret < 0)
            اذهب fail;
        nb_elems++;
    }
    av_freep(&str);

    إذا (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    إذا (arr && nb_elems < arr->اندازه_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->اندازه_min, o->name);
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

صحيح av_opt_سېټ(فراغ *obj, ثابت حرف *name, ثابت حرف *val, صحيح پلټنه_flags)
{
    فراغ *dst, *موخه_obj;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, 0, &موخه_obj, &o, &dst);
    إذا (ret < 0)
        أرجع ret;

    أرجع ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_سېټ_array : opt_سېټ_elem)(obj, موخه_obj, o, val, dst);
}

#تعریف_کړه OPT_EVAL_شمېره(name, opttype, vartype)                         \
صحيح av_opt_eval_ ## name(فراغ *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## بهر_3)        \
{                                                                       \
    إذا (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        أرجع AVERROR(EINVAL);                                         \
    أرجع سېټ_string_شمېره(obj, obj, o, val, name ## بهر_3);           \
}

OPT_EVAL_شمېره(flags,  AV_OPT_TYPE_FLAGS,    صحيح)
OPT_EVAL_شمېره(صحيح,    AV_OPT_TYPE_INT,      صحيح)
OPT_EVAL_شمېره(uint,   AV_OPT_TYPE_UINT,     بینښه)
OPT_EVAL_شمېره(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_شمېره(عائم,  AV_OPT_TYPE_FLOAT,    عائم)
OPT_EVAL_شمېره(مزدوج, AV_OPT_TYPE_DOUBLE,   مزدوج)
OPT_EVAL_شمېره(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ساكن صحيح سېټ_شمېره(فراغ *obj, ثابت حرف *name, مزدوج عدد, صحيح den, int64_t intnum,
                      صحيح پلټنه_flags, صحيح require_type)
{
    فراغ *dst;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, require_type, عدم, &o, &dst);
    إذا (ret < 0)
        أرجع ret;
    إذا (dst)
        ret = write_شمېره(obj, o, dst, عدد, den, intnum, 0);

    أرجع ret;
}

صحيح av_opt_سېټ_int(فراغ *obj, ثابت حرف *name, int64_t val, صحيح پلټنه_flags)
{
    أرجع سېټ_شمېره(obj, name, 1, 1, val, پلټنه_flags, 0);
}

صحيح av_opt_سېټ_double(فراغ *obj, ثابت حرف *name, مزدوج val, صحيح پلټنه_flags)
{
    أرجع سېټ_شمېره(obj, name, val, 1, 1, پلټنه_flags, 0);
}

صحيح av_opt_سېټ_q(فراغ *obj, ثابت حرف *name, AVRational val, صحيح پلټنه_flags)
{
    أرجع سېټ_شمېره(obj, name, val.عدد, val.den, 1, پلټنه_flags, 0);
}

صحيح av_opt_سېټ_bin(فراغ *obj, ثابت حرف *name, ثابت uint8_t *val, صحيح len, صحيح پلټنه_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحيح *lendst;
    صحيح ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, AV_OPT_TYPE_دوګونی,
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
        حافظه_نقل(ptr, val, len);
    }

    أرجع 0;
}

صحيح av_opt_سېټ_image_اندازه(فراغ *obj, ثابت حرف *name, صحيح w, صحيح h, صحيح پلټنه_flags)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, AV_OPT_TYPE_IMAGE_اندازه,
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

صحيح av_opt_سېټ_video_شرح(فراغ *obj, ثابت حرف *name, AVRational val, صحيح پلټنه_flags)
{
    أرجع سېټ_شمېره(obj, name, val.عدد, val.den, 1, پلټنه_flags, AV_OPT_TYPE_VIDEO_شرح);
}

ساكن صحيح سېټ_format(فراغ *obj, ثابت حرف *name, صحيح fmt, صحيح پلټنه_flags,
                      تعداد AVOptionType type, ثابت حرف *desc, صحيح nb_fmts)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح min, max, ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, type, عدم, &o, (فراغ**)&dst);
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

صحيح av_opt_سېټ_pixel_fmt(فراغ *obj, ثابت حرف *name, تعداد AVPixelFormat fmt, صحيح پلټنه_flags)
{
    أرجع سېټ_format(obj, name, fmt, پلټنه_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحيح av_opt_سېټ_sample_fmt(فراغ *obj, ثابت حرف *name, تعداد AVSampleFormat fmt, صحيح پلټنه_flags)
{
    أرجع سېټ_format(obj, name, fmt, پلټنه_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحيح av_opt_سېټ_dict_val(فراغ *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحيح پلټنه_flags)
{
    AVDictionary **dst;
    صحيح ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, AV_OPT_TYPE_DICT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    أرجع ret;
}

صحيح av_opt_سېټ_chlayout(فراغ *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحيح پلټنه_flags)
{
    AVChannelLayout *dst;
    صحيح ret;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, AV_OPT_TYPE_CHLAYOUT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        أرجع ret;

    إذا (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    أرجع ret;
}

ساكن فراغ format_duration(حرف *buf, size_t اندازه, int64_t d)
{
    حرف *e;

    av_assert0(اندازه >= 25);
    إذا (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        اندازه--;
        d = -d;
    }
    إذا (d == INT64_MAX)
        snprintf(buf, اندازه, "INT64_MAX");
    وإلا إذا (d == INT64_MIN)
        snprintf(buf, اندازه, "INT64_MIN");
    وإلا إذا (d > (int64_t)3600*1000000)
        snprintf(buf, اندازه, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحيح)((d / 60000000) % 60),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا إذا (d > 60*1000000)
        snprintf(buf, اندازه, "%d:%02d.%06d",
                 (صحيح)(d / 60000000),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا
        snprintf(buf, اندازه, "%d.%06d",
                 (صحيح)(d / 1000000),
                 (صحيح)(d % 1000000));
    e = buf + مزي_اوږدوالی(buf);
    طالما (e > buf && e[-1] == '0')
        *(--e) = 0;
    إذا (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ساكن صحيح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت فراغ *dst, صحيح پلټنه_flags)
{
    صحيح ret;

    بدل (TYPE_بنسټ(o->type)) {
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
        ret = snprintf(*pbuf, buf_len, "%u", *(بینښه *)dst);
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
        } وإلا إذا (پلټنه_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = عدم;
            أرجع 0;
        } وإلا {
            *pbuf = av_strdup("");
        }
        أرجع *pbuf ? 0 : AVERROR(ENOMEM);
    حالة AV_OPT_TYPE_دوګونی: {
        ثابت uint8_t *bin;
        صحيح len;

        إذا (!*(uint8_t **)dst && (پلټنه_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        len = *(صحيح *)(((uint8_t *)dst) + حجم(uint8_t *));
        إذا ((uint64_t)len * 2 + 1 > لوی_عدد)
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
    حالة AV_OPT_TYPE_IMAGE_اندازه:
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
        ret = مزي_اوږدوالی(*pbuf); // no overflow possible, checked by an assert
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
        إذا (!*(AVDictionary **)dst && (پلټنه_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        أرجع av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    افتراضي:
        أرجع AVERROR(EINVAL);
    }

    أرجع ret;
}

ساكن صحيح opt_get_array(ثابت AVOption *o, فراغ *dst, uint8_t **بهر_val)
{
    ثابت بینښه شمېر = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = عدم;
    size_t   str_len = 0;
    صحيح ret;

    *بهر_val = عدم;

    لكل (بینښه i = 0; i < شمېر; i++) {
        uint8_t buf[128], *بهر = buf;
        size_t بهر_len;

        ret = opt_get_elem(o, &بهر, حجم(buf),
                           opt_array_pelem(o, *(فراغ **)dst, i), 0);
        إذا (ret < 0)
            اذهب fail;

        بهر_len = مزي_اوږدوالی(بهر);
        إذا (بهر_len > SIZE_MAX / 2 - !!i ||
            !!i + بهر_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            اذهب fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + بهر_len * 2 + !!i);
        إذا (ret < 0)
            اذهب fail;

        // add separator if needed
        إذا (i)
            str[str_len++] = sep;

        // escape the element
        لكل (بینښه j = 0; j < بهر_len; j++) {
            uint8_t val = بهر[j];
            إذا (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        إذا (بهر != buf)
            av_freep(&بهر);
        إذا (ret < 0) {
            av_freep(&str);
            أرجع ret;
        }
    }

    *بهر_val = str;

    أرجع 0;
}

صحيح av_opt_get(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, uint8_t **بهر_val)
{
    فراغ *dst, *موخه_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    uint8_t *بهر, buf[128];
    صحيح ret;

    إذا (!o || !موخه_obj || (o->دننه_واټن<=0 && o->type != AV_OPT_TYPE_CONST))
        أرجع AVERROR_OPTION_NOT_وموندل;

    إذا (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)موخه_obj + o->دننه_واټن;

    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, بهر_val);
        إذا (ret < 0)
            أرجع ret;
        إذا (!*بهر_val && !(پلټنه_flags & AV_OPT_ALLOW_NULL)) {
            *بهر_val = av_strdup("");
            إذا (!*بهر_val)
               أرجع AVERROR(ENOMEM);
        }
        أرجع 0;
    }

    buf[0] = 0;
    بهر = buf;
    ret = opt_get_elem(o, &بهر, حجم(buf), dst, پلټنه_flags);
    إذا (ret < 0)
        أرجع ret;
    إذا (بهر != buf) {
        *بهر_val = بهر;
        أرجع 0;
    }

    إذا (ret >= حجم(buf))
        أرجع AVERROR(EINVAL);
    *بهر_val = av_strdup(بهر);
    أرجع *بهر_val ? 0 : AVERROR(ENOMEM);
}

ساكن صحيح get_شمېره(فراغ *obj, ثابت حرف *name, مزدوج *عدد, صحيح *den, int64_t *intnum,
                      صحيح پلټنه_flags)
{
    فراغ *dst, *موخه_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t *)موخه_obj) + o->دننه_واټن;

    أرجع read_شمېره(o, dst, عدد, den, intnum);
}

صحيح av_opt_get_int(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, int64_t *بهر_val)
{
    int64_t intnum = 1;
    مزدوج عدد = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_شمېره(obj, name, &عدد, &den, &intnum, پلټنه_flags)) < 0)
        أرجع ret;
    إذا (عدد == den)
        *بهر_val = intnum;
    وإلا
        *بهر_val = عدد * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_double(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, مزدوج *بهر_val)
{
    int64_t intnum = 1;
    مزدوج عدد = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_شمېره(obj, name, &عدد, &den, &intnum, پلټنه_flags)) < 0)
        أرجع ret;
    *بهر_val = عدد * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_q(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, AVRational *بهر_val)
{
    int64_t intnum = 1;
    مزدوج عدد = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_شمېره(obj, name, &عدد, &den, &intnum, پلټنه_flags)) < 0)
        أرجع ret;

    إذا (عدد == 1.0 && (صحيح)intnum == intnum)
        *بهر_val = (AVRational){intnum, den};
    وإلا
        *بهر_val = double_منزل_rational(عدد*intnum/den);
    أرجع 0;
}

صحيح av_opt_get_image_اندازه(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, صحيح *w_بهر, صحيح *h_بهر)
{
    فراغ *dst, *موخه_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (o->type != AV_OPT_TYPE_IMAGE_اندازه) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)موخه_obj) + o->دننه_واټن;
    إذا (w_بهر) *w_بهر = *(صحيح *)dst;
    إذا (h_بهر) *h_بهر = *((صحيح *)dst+1);
    أرجع 0;
}

صحيح av_opt_get_video_شرح(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, AVRational *بهر_val)
{
    أرجع av_opt_get_q(obj, name, پلټنه_flags, بهر_val);
}

ساكن صحيح get_format(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, فراغ *بهر_fmt,
                      تعداد AVOptionType type, ثابت حرف *desc)
{
    فراغ *dst, *موخه_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)موخه_obj) + o->دننه_واټن;
    إذا (type == AV_OPT_TYPE_PIXEL_FMT)
        *(تعداد AVPixelFormat *)بهر_fmt = *(تعداد AVPixelFormat *)dst;
    وإلا
        *(تعداد AVSampleFormat*)بهر_fmt = *(تعداد AVSampleFormat*)dst;

    أرجع 0;
}

صحيح av_opt_get_pixel_fmt(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, تعداد AVPixelFormat *بهر_fmt)
{
    أرجع get_format(obj, name, پلټنه_flags, بهر_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحيح av_opt_get_sample_fmt(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, تعداد AVSampleFormat *بهر_fmt)
{
    أرجع get_format(obj, name, پلټنه_flags, بهر_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحيح av_opt_get_chlayout(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, AVChannelLayout *cl)
{
    فراغ *dst, *موخه_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)موخه_obj) + o->دننه_واټن;
    أرجع av_channel_layout_copy(cl, dst);
}

صحيح av_opt_get_dict_val(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags, AVDictionary **بهر_val)
{
    فراغ *موخه_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);

    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (o->type != AV_OPT_TYPE_DICT)
        أرجع AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)موخه_obj) + o->دننه_واټن);

    أرجع av_dict_copy(بهر_val, src, 0);
}

صحيح av_opt_flag_is_سېټ(فراغ *obj, ثابت حرف *ډګر_name, ثابت حرف *flag_name)
{
    ثابت AVOption *ډګر = av_opt_پیدا_کړه(obj, ډګر_name, عدم, 0, 0);
    ثابت AVOption *flag  = av_opt_پیدا_کړه(obj, flag_name,
                                        ډګر ? ډګر->unit : عدم, 0, 0);
    int64_t res;

    إذا (!ډګر || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, ډګر_name, 0, &res) < 0)
        أرجع 0;
    أرجع res & flag->default_val.i64;
}

ساكن فراغ log_int_ارزښت(فراغ *av_log_obj, صحيح level, int64_t i)
{
    إذا (i == لوی_عدد) {
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

ساكن فراغ log_ارزښت(فراغ *av_log_obj, صحيح level, مزدوج d)
{
    إذا      (d == لوی_عدد) {
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

ساكن ثابت حرف *get_opt_const_name(فراغ *obj, ثابت حرف *unit, int64_t ارزښت)
{
    ثابت AVOption *opt = عدم;

    إذا (!unit)
        أرجع عدم;
    طالما ((opt = av_opt_بل(obj, opt)))
        إذا (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == ارزښت)
            أرجع opt->name;
    أرجع عدم;
}

ساكن حرف *get_opt_flags_string(فراغ *obj, ثابت حرف *unit, int64_t ارزښت)
{
    ثابت AVOption *opt = عدم;
    حرف flags[512];

    flags[0] = 0;
    إذا (!unit)
        أرجع عدم;
    طالما ((opt = av_opt_بل(obj, opt))) {
        إذا (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & ارزښت) {
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
                     تعداد AVOptionType پلار_type)
{
    ثابت تعداد AVOptionType type = TYPE_بنسټ(o->type);

    إذا (o->type == AV_OPT_TYPE_CONST && (TYPE_بنسټ(پلار_type) == AV_OPT_TYPE_INT || TYPE_بنسټ(پلار_type) == AV_OPT_TYPE_INT64))
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
    إذا (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_دوګونی)
        أرجع;
    إذا ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_اندازه ||
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
            log_int_ارزښت(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        اكسر;
    }
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_FLOAT:
        log_ارزښت(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, لوی_عدد);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.عدد, q.den); }
        اكسر;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_COLOR:
    حالة AV_OPT_TYPE_IMAGE_اندازه:
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
                     صحيح req_flags, صحيح rej_flags, تعداد AVOptionType پلار_type)
{
    ثابت AVOption *opt = عدم;
    AVOptionRanges *r;
    صحيح i;

    طالما ((opt = av_opt_بل(obj, opt))) {
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

        log_type(av_log_obj, opt, پلار_type);

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

        إذا (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_پلټنه_FAKE_OBJ) >= 0) {
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
                    log_ارزښت(av_log_obj, AV_LOG_INFO, r->range[i]->ارزښت_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_ارزښت(av_log_obj, AV_LOG_INFO, r->range[i]->ارزښت_max);
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

فراغ av_opt_سېټ_defaults(فراغ *s)
{
    av_opt_سېټ_defaults2(s, 0, 0);
}

فراغ av_opt_سېټ_defaults2(فراغ *s, صحيح ماسک_2, صحيح flags)
{
    ثابت AVOption *opt = عدم;
    طالما ((opt = av_opt_بل(s, opt))) {
        فراغ *dst = ((uint8_t*)s) + opt->دننه_واټن;

        إذا ((opt->flags & ماسک_2) != flags)
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
                opt_سېټ_array(s, s, opt, arr->def, dst);

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
                write_شمېره(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
            حالة AV_OPT_TYPE_FLOAT: {
                مزدوج val;
                val = opt->default_val.dbl;
                write_شمېره(s, opt, dst, val, 1, 1, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, لوی_عدد);
                write_شمېره(s, opt, dst, 1, val.den, val.عدد, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_COLOR:
                سېټ_string_color(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_STRING:
                سېټ_string(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_IMAGE_اندازه:
                سېټ_string_image_اندازه(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_VIDEO_شرح:
                سېټ_string_video_شرح(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_دوګونی:
                سېټ_string_دوګونی(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_CHLAYOUT:
                سېټ_string_channel_layout(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_DICT:
                سېټ_string_dict(s, opt, opt->default_val.str, dst);
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
ساكن صحيح parse_کلی_ارزښت_pair(فراغ *ctx, ثابت حرف **buf,
                                ثابت حرف *کلی_val_sep, ثابت حرف *جوړې_sep)
{
    حرف *کلی = av_get_token(buf, کلی_val_sep);
    حرف *val;
    صحيح ret;

    إذا (!کلی)
        أرجع AVERROR(ENOMEM);

    إذا (*کلی && strspn(*buf, کلی_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوړې_sep);
        إذا (!val) {
            av_freep(&کلی);
            أرجع AVERROR(ENOMEM);
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", کلی);
        av_free(کلی);
        أرجع AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", کلی, val);

    ret = av_opt_سېټ(ctx, کلی, val, AV_OPT_پلټنه_CHILDREN);
    إذا (ret == AVERROR_OPTION_NOT_وموندل)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", کلی);

    av_free(کلی);
    av_free(val);
    أرجع ret;
}

صحيح av_سېټ_options_string(فراغ *ctx, ثابت حرف *opts,
                          ثابت حرف *کلی_val_sep, ثابت حرف *جوړې_sep)
{
    صحيح ret, شمېر = 0;

    إذا (!opts)
        أرجع 0;

    طالما (*opts) {
        إذا ((ret = parse_کلی_ارزښت_pair(ctx, &opts, کلی_val_sep, جوړې_sep)) < 0)
            أرجع ret;
        شمېر++;

        إذا (*opts)
            opts++;
    }

    أرجع شمېر;
}

#تعریف_کړه WHITESPACES " \n\t\r"

ساكن صحيح is_کلی_char(حرف c)
{
    أرجع (بینښه)((c | 32) - 'a') < 26 ||
           (بینښه)(c - '0') < 10 ||
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
ساكن صحيح get_کلی(ثابت حرف **ropts, ثابت حرف *delim, حرف **rkey)
{
    ثابت حرف *opts = *ropts;
    ثابت حرف *کلی_پیل, *کلی_پای_ټکی;

    کلی_پیل = opts += strspn(opts, WHITESPACES);
    طالما (is_کلی_char(*opts))
        opts++;
    کلی_پای_ټکی = opts;
    opts += strspn(opts, WHITESPACES);
    إذا (!*opts || !strchr(delim, *opts))
        أرجع AVERROR(EINVAL);
    opts++;
    إذا (!(*rkey = av_malloc(کلی_پای_ټکی - کلی_پیل + 1)))
        أرجع AVERROR(ENOMEM);
    حافظه_نقل(*rkey, کلی_پیل, کلی_پای_ټکی - کلی_پیل);
    (*rkey)[کلی_پای_ټکی - کلی_پیل] = 0;
    *ropts = opts;
    أرجع 0;
}

صحيح av_opt_get_کلی_ارزښت(ثابت حرف **ropts,
                         ثابت حرف *کلی_val_sep, ثابت حرف *جوړې_sep,
                         بینښه flags,
                         حرف **rkey, حرف **rval)
{
    صحيح ret;
    حرف *کلی = عدم, *val;
    ثابت حرف *opts = *ropts;

    إذا ((ret = get_کلی(&opts, کلی_val_sep, &کلی)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_کلی))
        أرجع AVERROR(EINVAL);
    إذا (!(val = av_get_token(&opts, جوړې_sep))) {
        av_free(کلی);
        أرجع AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = کلی;
    *rval  = val;
    أرجع 0;
}

صحيح av_opt_سېټ_from_string(فراغ *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *کلی_val_sep, ثابت حرف *جوړې_sep)
{
    صحيح ret, شمېر = 0;
    ثابت حرف *dummy_shorthand = عدم;
    ثابت حرف *کلی;

    إذا (!opts)
        أرجع 0;
    إذا (!shorthand)
        shorthand = &dummy_shorthand;

    طالما (*opts) {
        حرف *parsed_کلی, *ارزښت;
        ret = av_opt_get_کلی_ارزښت(&opts, کلی_val_sep, جوړې_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_کلی : 0,
                                   &parsed_کلی, &ارزښت);
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
        إذا (parsed_کلی) {
            کلی = parsed_کلی;
            طالما (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } وإلا {
            کلی = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", کلی, ارزښت);
        إذا ((ret = av_opt_سېټ(ctx, کلی, ارزښت, 0)) < 0) {
            إذا (ret == AVERROR_OPTION_NOT_وموندل)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", کلی);
            av_free(ارزښت);
            av_free(parsed_کلی);
            أرجع ret;
        }

        av_free(ارزښت);
        av_free(parsed_کلی);
        شمېر++;
    }
    أرجع شمېر;
}

فراغ av_opt_free(فراغ *obj)
{
    ثابت AVOption *o = عدم;
    طالما ((o = av_opt_بل(obj, o))) {
        فراغ *pitem = (uint8_t *)obj + o->دننه_واټن;

        إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        وإلا
            opt_free_elem(o->type, pitem);
    }
}

صحيح av_opt_سېټ_dict2(فراغ *obj, AVDictionary **options, صحيح پلټنه_flags)
{
    ثابت AVDictionary_ثبت *t = عدم;
    AVDictionary    *tmp = عدم;
    صحيح ret;

    إذا (!options)
        أرجع 0;

    طالما ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_سېټ(obj, t->کلی, t->ارزښت, پلټنه_flags);
        إذا (ret == AVERROR_OPTION_NOT_وموندل)
            ret = av_dict_سېټ(&tmp, t->کلی, t->ارزښت, AV_DICT_MULTIKEY);
        إذا (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->کلی, t->ارزښت);
            av_dict_free(&tmp);
            أرجع ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    أرجع 0;
}

صحيح av_opt_سېټ_dict(فراغ *obj, AVDictionary **options)
{
    أرجع av_opt_سېټ_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_پیدا_کړه(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحيح opt_flags, صحيح پلټنه_flags)
{
    أرجع av_opt_find2(obj, name, unit, opt_flags, پلټنه_flags, عدم);
}

ثابت AVOption *av_opt_find2(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحيح opt_flags, صحيح پلټنه_flags, فراغ **موخه_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = عدم;

    إذا(!obj)
        أرجع عدم;

    c= *(AVClass**)obj;

    إذا (!c)
        أرجع عدم;

    إذا (پلټنه_flags & AV_OPT_پلټنه_CHILDREN) {
        إذا (پلټنه_flags & AV_OPT_پلټنه_FAKE_OBJ) {
            فراغ *iter = عدم;
            ثابت AVClass *ماشوم;
            طالما (ماشوم = av_opt_ماشوم_class_iterate(c, &iter))
                إذا (o = av_opt_find2(&ماشوم, name, unit, opt_flags, پلټنه_flags, عدم))
                    أرجع o;
        } وإلا {
            فراغ *ماشوم = عدم;
            طالما (ماشوم = av_opt_ماشوم_بل(obj, ماشوم))
                إذا (o = av_opt_find2(ماشوم, name, unit, opt_flags, پلټنه_flags, موخه_obj))
                    أرجع o;
        }
    }

    طالما (o = av_opt_بل(obj, o)) {
        إذا (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            إذا (موخه_obj) {
                إذا (!(پلټنه_flags & AV_OPT_پلټنه_FAKE_OBJ))
                    *موخه_obj = obj;
                وإلا
                    *موخه_obj = عدم;
            }
            أرجع o;
        }
    }
    أرجع عدم;
}

فراغ *av_opt_ماشوم_بل(فراغ *obj, فراغ *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    إذا (c->ماشوم_بل)
        أرجع c->ماشوم_بل(obj, prev);
    أرجع عدم;
}

ثابت AVClass *av_opt_ماشوم_class_iterate(ثابت AVClass *پلار, فراغ **iter)
{
    إذا (پلار->ماشوم_class_iterate)
        أرجع پلار->ماشوم_class_iterate(iter);
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
    } وإلا إذا (type == AV_OPT_TYPE_دوګونی) {
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
        size_t اندازه = opt_type_desc[type].اندازه;
        حافظه_نقل(dst, src, اندازه);
    } وإلا {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        أرجع AVERROR(EINVAL);
    }

    أرجع 0;
}

ساكن صحيح opt_copy_array(فراغ *logctx, ثابت AVOption *o,
                          فراغ **pdst, ثابت فراغ * ثابت *psrc)
{
    بینښه nb_elems = *opt_array_pcount(psrc);
    فراغ         *dst = عدم;
    صحيح ret;

    إذا (*pdst == *psrc) {
        *pdst                   = عدم;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_بنسټ(o->type)].اندازه);
    إذا (!dst)
        أرجع AVERROR(ENOMEM);

    لكل (بینښه i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_بنسټ(o->type),
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

    طالما ((o = av_opt_بل(src, o))) {
        فراغ *ډګر_dst = (uint8_t *)dst + o->دننه_واټن;
        فراغ *ډګر_src = (uint8_t *)src + o->دننه_واټن;

        صحيح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       ډګر_dst, ډګر_src) :
                  opt_copy_elem (dst, o->type, ډګر_dst, ډګر_src);
        إذا (err < 0)
            ret = err;
    }
    أرجع ret;
}

صحيح av_opt_get_array_اندازه(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags,
                          بینښه صحيح *بهر_val)
{
    فراغ *موخه_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray = (uint8_t *)موخه_obj + o->دننه_واټن;
    *بهر_val = *opt_array_pcount(parray);

    أرجع 0;
}

صحيح av_opt_get_array(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags,
                     بینښه صحيح پیل_elem, بینښه صحيح nb_elems,
                     تعداد AVOptionType بهر_type, فراغ *بهر_val)
{
    ثابت size_t elem_اندازه_بهر = opt_type_desc[TYPE_بنسټ(بهر_type)].اندازه;

    ثابت AVOption *o;
    فراغ *موخه_obj;

    ثابت فراغ *parray;
    بینښه array_اندازه;

    صحيح ret;

    o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه_obj);
    إذا (!o || !موخه_obj)
        أرجع AVERROR_OPTION_NOT_وموندل;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (بهر_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray     = (uint8_t *)موخه_obj + o->دننه_واټن;
    array_اندازه = *opt_array_pcount(parray);

    إذا (پیل_elem >= array_اندازه ||
        array_اندازه - پیل_elem < nb_elems)
        أرجع AVERROR(EINVAL);

    لكل (بینښه i = 0; i < nb_elems; i++) {
        ثابت فراغ *src = opt_array_pelem(o, *(فراغ**)parray, پیل_elem + i);
        فراغ       *dst = (uint8_t*)بهر_val + i * elem_اندازه_بهر;

        إذا (بهر_type == TYPE_بنسټ(o->type)) {
            ret = opt_copy_elem(obj, بهر_type, dst, src);
            إذا (ret < 0)
                اذهب fail;
        } وإلا إذا (بهر_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *بهر = buf;

            ret = opt_get_elem(o, &بهر, حجم(buf), src, پلټنه_flags);
            إذا (ret < 0)
                اذهب fail;

            إذا (بهر == buf) {
                بهر = av_strdup(buf);
                إذا (!بهر) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
            }

            *(uint8_t**)dst = بهر;
        } وإلا إذا (بهر_type == AV_OPT_TYPE_INT64    ||
                   بهر_type == AV_OPT_TYPE_DOUBLE   ||
                   بهر_type == AV_OPT_TYPE_RATIONAL) {
            مزدوج     عدد = 1.0;
            صحيح        den = 1;
            int64_t intnum = 1;

            ret = read_شمېره(o, src, &عدد, &den, &intnum);
            إذا (ret < 0)
                اذهب fail;

            بدل (بهر_type) {
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
    لكل (بینښه i = 0; i < nb_elems; i++)
        opt_free_elem(بهر_type, (uint8_t*)بهر_val + i * elem_اندازه_بهر);
    أرجع ret;
}

صحيح av_opt_سېټ_array(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags,
                     بینښه صحيح پیل_elem, بینښه صحيح nb_elems,
                     تعداد AVOptionType val_type, ثابت فراغ *val)
{
    ثابت size_t elem_اندازه_val = opt_type_desc[TYPE_بنسټ(val_type)].اندازه;

    ثابت AVOption *o;
    ثابت AVOptionArrayDef *arr;
    فراغ *موخه_obj;

    فراغ *parray;
    فراغ *new_elems;
    بینښه *array_اندازه, new_اندازه;
    size_t elem_اندازه;

    صحيح ret = 0;

    ret = opt_سېټ_init(obj, name, پلټنه_flags, 0, &موخه_obj, &o, &parray);
    إذا (ret < 0)
        أرجع ret;

    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_اندازه = opt_array_pcount(parray);
    elem_اندازه  = opt_type_desc[TYPE_بنسټ(o->type)].اندازه;

    إذا (پیل_elem > *array_اندازه)
        أرجع AVERROR(EINVAL);

    // compute new array size
    إذا (!val) {
        إذا (*array_اندازه - پیل_elem < nb_elems)
            أرجع AVERROR(EINVAL);

        new_اندازه = *array_اندازه - nb_elems;
    } وإلا إذا (پلټنه_flags & AV_OPT_ARRAY_REPLACE) {
        إذا (پیل_elem >= UINT_MAX - nb_elems)
            أرجع AVERROR(EINVAL);

        new_اندازه = FFMAX(*array_اندازه, پیل_elem + nb_elems);
    } وإلا {
        إذا (nb_elems >= UINT_MAX - *array_اندازه)
            أرجع AVERROR(EINVAL);

        new_اندازه = *array_اندازه + nb_elems;
    }

    إذا (arr &&
        ((arr->اندازه_max && new_اندازه > arr->اندازه_max) ||
         (arr->اندازه_min && new_اندازه < arr->اندازه_min)))
        أرجع AVERROR(EINVAL);

    // desired operation is shrinking the array
    إذا (!val) {
        فراغ *array = *(فراغ**)parray;

        لكل (بینښه i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, پیل_elem + i));
        }

        إذا (new_اندازه > 0) {
            memmove(opt_array_pelem(o, array, پیل_elem),
                    opt_array_pelem(o, array, پیل_elem + nb_elems),
                    elem_اندازه * (*array_اندازه - پیل_elem - nb_elems));

            array = av_realloc_array(array, new_اندازه, elem_اندازه);
            إذا (!array)
                أرجع AVERROR(ENOMEM);

            *(فراغ**)parray = array;
        } وإلا
            av_freep(parray);

        *array_اندازه = new_اندازه;

        أرجع 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_اندازه);
    إذا (!new_elems)
        أرجع AVERROR(ENOMEM);

    // convert/validate each new element
    لكل (بینښه i = 0; i < nb_elems; i++) {
        فراغ       *dst = opt_array_pelem(o, new_elems, i);
        ثابت فراغ *src = (uint8_t*)val + i * elem_اندازه_val;

        مزدوج     عدد = 1.0;
        صحيح        den = 1;
        int64_t intnum = 1;

        إذا (val_type == TYPE_بنسټ(o->type)) {
            صحيح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            إذا (ret < 0)
                اذهب fail;

            // validate the range for numeric options
            err = read_شمېره(o, dst, &عدد, &den, &intnum);
            إذا (err >= 0 && TYPE_بنسټ(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < عدد * intnum || o->min * den > عدد * intnum)) {
                عدد = den ? عدد * intnum / den : (عدد && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       پیل_elem + i, o->name, عدد, o->min, o->max);
                ret = AVERROR(ERANGE);
                اذهب fail;
            }
        } وإلا إذا (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_سېټ_elem(obj, موخه_obj, o, *(ثابت حرف **)src, dst);
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

            ret = write_شمېره(obj, o, dst, عدد, den, intnum, 0);
            إذا (ret < 0)
                اذهب fail;
        } وإلا {
            ret = AVERROR(ENOSYS);
            اذهب fail;
        }
    }

    // commit new elements to the array
    إذا (پیل_elem == 0 && nb_elems == new_اندازه) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_اندازه);
        *(فراغ**)parray = new_elems;
        *array_اندازه     = nb_elems;

        new_elems = عدم;
        nb_elems  = 0;
    } وإلا {
        فراغ *array = av_realloc_array(*(فراغ**)parray, new_اندازه, elem_اندازه);
        إذا (!array) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }

        إذا (پلټنه_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            لكل (بینښه i = پیل_elem; i < FFMIN(پیل_elem + nb_elems, *array_اندازه); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } وإلا {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, پیل_elem + nb_elems),
                    opt_array_pelem(o, array, پیل_elem),
                    elem_اندازه * (*array_اندازه - پیل_elem));
        }

        حافظه_نقل((uint8_t*)array + elem_اندازه * پیل_elem, new_elems, elem_اندازه * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(فراغ**)parray = array;
        *array_اندازه     = new_اندازه;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    أرجع ret;
}

صحيح av_opt_query_ranges(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *کلی, صحيح flags)
{
    صحيح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحيح (*callback)(AVOptionRanges **, فراغ *obj, ثابت حرف *کلی, صحيح flags) = c->query_ranges;

    إذا (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, کلی, flags);
    إذا (ret >= 0) {
        إذا (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    أرجع ret;
}

صحيح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *کلی, صحيح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(فراغ*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *ډګر = av_opt_پیدا_کړه(obj, کلی, عدم, 0, flags);
    صحيح ret;

    *ranges_arg = عدم;

    إذا (!ranges || !range || !range_array || !ډګر) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->ارزښت_min = ډګر->min;
    range->ارزښت_max = ډګر->max;

    بدل (ډګر->type) {
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
        range->ارزښت_min = -1;
        range->ارزښت_max = لوی_عدد;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = لوی_عدد;
        اكسر;
    حالة AV_OPT_TYPE_IMAGE_اندازه:
        range->component_min = 0;
        range->component_max = لوی_عدد/128/8;
        range->ارزښت_min = 0;
        range->ارزښت_max = لوی_عدد/8;
        اكسر;
    حالة AV_OPT_TYPE_VIDEO_شرح:
        range->component_min = 1;
        range->component_max = لوی_عدد;
        range->ارزښت_min = 1;
        range->ارزښت_max = لوی_عدد;
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

صحيح av_opt_is_سېټ_منزل_default(فراغ *obj, ثابت AVOption *o)
{
    int64_t i64;
    مزدوج d;
    AVRational q;
    صحيح ret, w, h;
    حرف *str;
    فراغ *dst;

    إذا (!o || !obj)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->دننه_واټن;

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
        read_شمېره(o, dst, عدم, عدم, &i64);
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
        q = av_d2q(o->default_val.dbl, لوی_عدد);
        أرجع !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالة AV_OPT_TYPE_دوګونی: {
        بنية {
            uint8_t *معلومات;
            صحيح اندازه;
        } tmp = {0};
        صحيح opt_اندازه = *(صحيح *)((فراغ **)dst + 1);
        فراغ *opt_ptr = *(فراغ **)dst;
        إذا (!opt_اندازه && (!o->default_val.str || !مزي_اوږدوالی(o->default_val.str)))
            أرجع 1;
        إذا (!opt_اندازه ||  !o->default_val.str || !مزي_اوږدوالی(o->default_val.str ))
            أرجع 0;
        إذا (opt_اندازه != مزي_اوږدوالی(o->default_val.str) / 2)
            أرجع 0;
        ret = سېټ_string_دوګونی(عدم, عدم, o->default_val.str, &tmp.معلومات);
        إذا (!ret)
            ret = !memcmp(opt_ptr, tmp.معلومات, tmp.اندازه);
        av_free(tmp.معلومات);
        أرجع ret;
    }
    حالة AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = عدم;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionary_ثبت *en1 = عدم;
        ثابت AVDictionary_ثبت *en2 = عدم;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        إذا (ret < 0) {
            av_dict_free(&dict1);
            أرجع ret;
        }
        افعل {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } طالما (en1 && en2 && !strcmp(en1->کلی, en2->کلی) && !strcmp(en1->ارزښت, en2->ارزښت));
        av_dict_free(&dict1);
        أرجع (!en1 && !en2);
    }
    حالة AV_OPT_TYPE_IMAGE_اندازه:
        إذا (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        وإلا إذا ((ret = av_parse_video_اندازه(&w, &h, o->default_val.str)) < 0)
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

صحيح av_opt_is_سېټ_منزل_default_by_name(فراغ *obj, ثابت حرف *name, صحيح پلټنه_flags)
{
    ثابت AVOption *o;
    فراغ *موخه;
    إذا (!obj)
        أرجع AVERROR(EINVAL);
    o = av_opt_find2(obj, name, عدم, 0, پلټنه_flags, &موخه);
    إذا (!o)
        أرجع AVERROR_OPTION_NOT_وموندل;
    أرجع av_opt_is_سېټ_منزل_default(موخه, o);
}

ساكن صحيح opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, صحيح *cnt,
                         AVBPrint *bprint, ثابت حرف کلی_val_sep, ثابت حرف جوړې_sep)
{
    ثابت AVOption *o = عدم;
    فراغ *ماشوم = عدم;
    uint8_t *buf;
    صحيح ret;
    ثابت حرف special_chars[] = {جوړې_sep, کلی_val_sep, '\0'};

    إذا (flags & AV_OPT_SERIALIZE_پلټنه_CHILDREN)
        طالما (ماشوم = av_opt_ماشوم_بل(obj, ماشوم)) {
            ret = opt_serialize(ماشوم, opt_flags, flags, cnt, bprint,
                                کلی_val_sep, جوړې_sep);
            إذا (ret < 0)
                أرجع ret;
        }

    طالما (o = av_opt_بل(obj, o)) {
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
        إذا (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_سېټ_منزل_default(obj, o) > 0)
            استمر;
        إذا ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, عدم);
            أرجع ret;
        }
        إذا (buf) {
            إذا ((*cnt)++)
                av_bprint_append_معلومات(bprint, &جوړې_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_ډېرپېښ_BACKSLASH, 0);
            av_bprint_append_معلومات(bprint, &کلی_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_ډېرپېښ_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    أرجع 0;
}

صحيح av_opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, حرف **بفر,
                     ثابت حرف کلی_val_sep, ثابت حرف جوړې_sep)
{
    AVBPrint bprint;
    صحيح ret, cnt = 0;

    إذا (جوړې_sep == '\0' || کلی_val_sep == '\0' || جوړې_sep == کلی_val_sep ||
        جوړې_sep == '\\' || کلی_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        أرجع AVERROR(EINVAL);
    }

    إذا (!obj || !بفر)
        أرجع AVERROR(EINVAL);

    *بفر = عدم;
    av_bprint_init(&bprint, 64, AV_BPRINT_اندازه_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        کلی_val_sep, جوړې_sep);
    إذا (ret < 0)
        أرجع ret;

    ret = av_bprint_finalize(&bprint, بفر);
    إذا (ret < 0)
        أرجع ret;
    أرجع 0;
}
