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

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ثابت AVOption *av_opt_next(ثابت فراغ *obj, ثابت AVOption *last)
{
    ثابت AVClass *class;
    إذا (!obj)
        إرجاع عدم;
    class = *(ثابت AVClass**)obj;
    إذا (!last && class && class->option && class->option[0].name)
        إرجاع class->option;
    إذا (last && last[1].name)
        إرجاع ++last;
    إرجاع عدم;
}

ساكن ثابت بنية {
    size_t      size;
    ثابت حرف *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { حجم(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { حجم(صحيح),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { حجم(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { حجم(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { حجم(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { حجم(مزدوج),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { حجم(عائم),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { حجم(حرف *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { حجم(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ثنائي]        = { حجم(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { حجم(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { حجم(صحيح[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { حجم(AVRational),     "<video_rate>" },
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
    حالة AV_OPT_TYPE_IMAGE_SIZE:
    حالة AV_OPT_TYPE_PIXEL_FMT:
    حالة AV_OPT_TYPE_SAMPLE_FMT:
    حالة AV_OPT_TYPE_VIDEO_RATE:
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_COLOR:
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_UINT:
        إرجاع 1;
    }
    إرجاع 0;
}

ساكن uint8_t opt_array_sep(ثابت AVOption *o)
{
    ثابت AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    إرجاع (d && d->sep) ? d->sep : ',';
}

ساكن فراغ *opt_array_pelem(ثابت AVOption *o, فراغ *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    إرجاع (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

ساكن unsigned *opt_array_pcount(ثابت فراغ *parray)
{
    إرجاع (unsigned *)((ثابت فراغ * ثابت *)parray + 1);
}

ساكن فراغ opt_free_elem(تعداد AVOptionType type, فراغ *ptr)
{
    بدل (TYPE_BASE(type)) {
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_ثنائي:
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

ساكن فراغ opt_free_array(ثابت AVOption *o, فراغ *parray, unsigned *تعداد_2)
{
    لكل (unsigned i = 0; i < *تعداد_2; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(فراغ **)parray, i));

    av_freep(parray);
    *تعداد_2 = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ساكن صحيح opt_set_init(فراغ *obj, ثابت حرف *name, صحيح بحث_flags,
                        صحيح require_type,
                        فراغ **ptgt, ثابت AVOption **po, فراغ **pdst)
{
    فراغ *logctx;
    ثابت AVOption *o;
    فراغ *tgt;

    o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &tgt);
    إذا (!o || (!tgt && !(بحث_flags & AV_OPT_بحث_FAKE_OBJ)))
        إرجاع AVERROR_OPTION_NOT_FOUND;

    إذا (o->flags & AV_OPT_FLAG_READONLY)
        إرجاع AVERROR(EINVAL);

    logctx = tgt ? obj : عدم;

    إذا (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        إرجاع AVERROR(EINVAL);
    }

    إذا (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = عدم;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        إذا (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        إذا (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            إذا (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        إذا (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            إرجاع AVERROR(EINVAL);
        }
    }

    إذا (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    إذا (po)
        *po   = o;
    إذا (ptgt)
        *ptgt = tgt;
    إذا (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : عدم;

    إرجاع 0;
}

ساكن AVRational double_to_rational(مزدوج d)
{
     AVRational r = av_d2q(d, 1 << 24);
     إذا ((!r.رقم || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     إرجاع r;
}

ساكن صحيح read_العدد(ثابت AVOption *o, ثابت فراغ *dst, مزدوج *رقم, صحيح *den, int64_t *intnum)
{
    بدل (TYPE_BASE(o->type)) {
    حالة AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned صحيح*)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(تعداد AVPixelFormat *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(تعداد AVSampleFormat *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_INT:
        *intnum = *(صحيح *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_UINT:
        *intnum = *(unsigned صحيح *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_FLOAT:
        *رقم = *(عائم *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_DOUBLE:
        *رقم = *(مزدوج *)dst;
        إرجاع 0;
    حالة AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->رقم;
        *den    = ((AVRational *)dst)->den;
        إرجاع 0;
    حالة AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        إرجاع 0;
    }
    إرجاع AVERROR(EINVAL);
}

ساكن صحيح write_العدد(فراغ *obj, ثابت AVOption *o, فراغ *dst,
                        مزدوج رقم, صحيح den, int64_t intnum,
                        صحيح ignore_range)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);

    إذا (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < رقم * intnum || o->min * den > رقم * intnum)) {
        رقم = den ? رقم * intnum / den : (رقم && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               رقم, o->name, o->min, o->max);
        إرجاع AVERROR(ERANGE);
    }
    إذا (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        مزدوج d = رقم*intnum/den;
        إذا (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   رقم*intnum/den, o->name);
            إرجاع AVERROR(ERANGE);
        }
    }

    إذا (!dst)
        إرجاع 0;

    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *(تعداد AVPixelFormat *)dst = llrint(رقم / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *(تعداد AVSampleFormat *)dst = llrint(رقم / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
        *(صحيح *)dst = llrint(رقم / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:{
        مزدوج d = رقم / den;
        إذا (intnum == 1 && d == (مزدوج)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } وإلا
            *(int64_t *)dst = llrint(d) * intnum;
        اكسر;}
    حالة AV_OPT_TYPE_UINT64:{
        مزدوج d = رقم / den;
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
        *(عائم *)dst = رقم * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_DOUBLE:
        *(مزدوج    *)dst = رقم * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
    حالة AV_OPT_TYPE_VIDEO_RATE:
        إذا ((صحيح) رقم == رقم)
            *(AVRational *)dst = (AVRational) { رقم *intnum, den };
        وإلا
            *(AVRational *)dst = double_to_rational(رقم * intnum / den);
        اكسر;
    افتراضي:
        إرجاع AVERROR(EINVAL);
    }
    إرجاع 0;
}

ساكن صحيح hexchar2int(حرف c) {
    إذا (c >= '0' && c <= '9')
        إرجاع c - '0';
    إذا (c >= 'a' && c <= 'f')
        إرجاع c - 'a' + 10;
    إذا (c >= 'A' && c <= 'F')
        إرجاع c - 'A' + 10;
    إرجاع -1;
}

ساكن صحيح set_string_ثنائي(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحيح *lendst;
    uint8_t *bin, *ptr;
    صحيح len;

    إذا (dst) {
        lendst = (صحيح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    إذا (!val || !(len = strlen(val)))
        إرجاع 0;

    إذا (len & 1)
        إرجاع AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    إذا (!ptr)
        إرجاع AVERROR(ENOMEM);
    بينما (*val) {
        صحيح a = hexchar2int(*val++);
        صحيح b = hexchar2int(*val++);
        إذا (a < 0 || b < 0) {
            av_free(bin);
            إرجاع AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    إذا (dst) {
        *dst    = bin;
        *lendst = len;
    } وإلا {
        av_free(bin);
    }

    إرجاع 0;
}

ساكن صحيح set_string(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    إذا (!dst)
        إرجاع 0;
    av_freep(dst);
    إذا (!val)
        إرجاع 0;
    *dst = av_strdup(val);
    إرجاع *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ساكن صحيح set_string_العدد(فراغ *obj, فراغ *target_obj, ثابت AVOption *o, ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);
    صحيح ret = 0;

    إذا (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        صحيح رقم, den;
        حرف c;
        إذا (sscanf(val, "%d%*1[:/]%d%c", &رقم, &den, &c) == 2) {
            إذا ((ret = write_العدد(obj, o, dst, 1, den, رقم, 0)) >= 0)
                إرجاع ret;
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
            مزدوج const_قيم[64];
            ثابت حرف * const_names[64];
            صحيح بحث_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_بحث_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, بحث_flags);
            إذا (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                إذا (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } وإلا {
                إذا (o->unit) {
                    لكل (o_named = عدم; o_named = av_opt_next(target_obj, o_named); ) {
                        إذا (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            إذا (ci + 6 >= FF_ARRAY_ELEMS(const_قيم)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                إرجاع AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_قيم[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_قيم[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_قيم[ci++] = o->max;
                const_names [ci  ] = "min";
                const_قيم[ci++] = o->min;
                const_names [ci  ] = "none";
                const_قيم[ci++] = 0;
                const_names [ci  ] = "all";
                const_قيم[ci++] = ~0;
                const_names [ci] = عدم;
                const_قيم[ci] = 0;

                res = av_تعبير_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_قيم, عدم, عدم, عدم, عدم, عدم, 0, obj);
                إذا (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    إرجاع res;
                }
            }
        }
        إذا (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned صحيح*)dst;
            إذا (cmd == '+')
                d = intnum | (int64_t)d;
            وإلا إذا (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        إذا ((ret = write_العدد(obj, o, dst, d, 1, 1, 0)) < 0)
            إرجاع ret;
        val += i;
        إذا (!i || !*val)
            إرجاع 0;
    }
}

ساكن صحيح set_string_image_size(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح tmp[2];
    صحيح ret;

    إذا (!val || !strcmp(val, "none")) {
        إذا (dst) {
        dst[0] =
        dst[1] = 0;
        }
        إرجاع 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    إذا (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        إرجاع ret;
    }
    إذا (dst)
        memcpy(dst, tmp, حجم(tmp));
    إرجاع ret;
}

ساكن صحيح set_string_video_rate(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    AVRational tmp;
    صحيح ret = av_parse_video_rate(&tmp, val);
    إذا (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    إذا (dst)
        *dst = tmp;
    إرجاع ret;
}

ساكن صحيح set_string_color(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح ret;

    إذا (!val) {
        إرجاع 0;
    } وإلا {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        إذا (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            إرجاع ret;
        }
        إذا (dst)
            memcpy(dst, tmp, حجم(tmp));
        إرجاع ret;
    }
    إرجاع 0;
}

ساكن ثابت حرف *get_bool_name(صحيح val)
{
    إذا (val < 0)
        إرجاع "auto";
    إرجاع val ? "true" : "false";
}

ساكن صحيح set_string_bool(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح n;

    إذا (!val)
        إرجاع 0;

    إذا (!strcmp(val, "auto")) {
        n = -1;
    } وإلا إذا (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } وإلا إذا (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } وإلا {
        حرف *end = عدم;
        n = strtol(val, &end, 10);
        إذا (val + strlen(val) != end)
            اذهب fail;
    }

    إذا (n < o->min || n > o->max)
        اذهب fail;

    إذا (dst)
    *dst = n;
    إرجاع 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    إرجاع AVERROR(EINVAL);
}

ساكن صحيح set_string_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
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
            حرف *tail;
            fmt = strtol(val, &tail, 0);
            إذا (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                إرجاع AVERROR(EINVAL);
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
        إرجاع AVERROR(ERANGE);
    }

    إذا (dst)
    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:  *(تعداد AVPixelFormat *)dst = fmt; اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT: *(تعداد AVSampleFormat*)dst = fmt; اكسر;
    افتراضي: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    إرجاع 0;
}

ساكن صحيح get_pix_fmt(ثابت حرف *name)
{
    إرجاع av_get_pix_fmt(name);
}

ساكن صحيح set_string_pixel_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    إرجاع set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساكن صحيح get_sample_fmt(ثابت حرف *name)
{
    إرجاع av_get_sample_fmt(name);
}

ساكن صحيح set_string_sample_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    إرجاع set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساكن صحيح set_string_dict(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    AVDictionary *options = عدم;

    إذا (val) {
        صحيح ret = av_dict_parse_string(&options, val, "=", ":", 0);
        إذا (ret < 0) {
            av_dict_free(&options);
            إرجاع ret;
        }
    }

    إذا (!dst) {
        av_dict_free(&options);
        إرجاع 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    إرجاع 0;
}

ساكن صحيح set_string_channel_layout(فراغ *obj, ثابت AVOption *o,
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
        إرجاع 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    إذا (ret < 0)
        إرجاع ret;
    إذا (!dst)
        av_channel_layout_uninit(channel_layout);
    إرجاع 0;
}

ساكن صحيح opt_set_elem(فراغ *obj, فراغ *target_obj, ثابت AVOption *o,
                        ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);
    صحيح ret;

    إذا (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        إرجاع AVERROR(EINVAL);

    بدل (type) {
    حالة AV_OPT_TYPE_BOOL:
        إرجاع set_string_bool(obj, o, val, dst);
    حالة AV_OPT_TYPE_STRING:
        إرجاع set_string(obj, o, val, dst);
    حالة AV_OPT_TYPE_ثنائي:
        إرجاع set_string_ثنائي(obj, o, val, dst);
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_RATIONAL:
        إرجاع set_string_العدد(obj, target_obj, o, val, dst);
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        إرجاع set_string_image_size(obj, o, val, dst);
    حالة AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        إذا (ret < 0)
            إرجاع ret;
        إرجاع write_العدد(obj, o, dst, 1, tmp.den, tmp.رقم, 0);
    }
    حالة AV_OPT_TYPE_PIXEL_FMT:
        إرجاع set_string_pixel_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        إرجاع set_string_sample_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            إذا (val) {
                إذا ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    إرجاع ret;
                }
            }
            إذا (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                إرجاع AVERROR(ERANGE);
            }
            إذا (dst)
            *(int64_t *)dst = usecs;
            إرجاع 0;
        }
    حالة AV_OPT_TYPE_COLOR:
        إرجاع set_string_color(obj, o, val, dst);
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        إذا (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        إرجاع ret;
    حالة AV_OPT_TYPE_DICT:
        إرجاع set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    إرجاع AVERROR(EINVAL);
}

ساكن صحيح opt_set_array(فراغ *obj, فراغ *target_obj, ثابت AVOption *o,
                         ثابت حرف *val, فراغ *dst)
{
    ثابت AVOptionArrayDef *arr = o->default_val.arr;
    ثابت size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ثابت uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = عدم;

    فراغ      *logctx = dst ? obj : عدم;
    فراغ       *elems = عدم;
    unsigned nb_elems = 0;
    صحيح ret;

    إذا (val && *val) {
        str = av_malloc(strlen(val) + 1);
        إذا (!str)
            إرجاع AVERROR(ENOMEM);
    }

    // split and unescape the string
    بينما (val && *val) {
        uint8_t *p = str;
        فراغ *tmp;

        إذا (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
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

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        إذا (!tmp) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        إذا (ret < 0)
            اذهب fail;
        nb_elems++;
    }
    av_freep(&str);

    إذا (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    إذا (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        اذهب fail;
    }

    إذا (dst) {
    *((فراغ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } وإلا
        opt_free_array(o, &elems, &nb_elems);

    إرجاع 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    إرجاع ret;
}

صحيح av_opt_set(فراغ *obj, ثابت حرف *name, ثابت حرف *val, صحيح بحث_flags)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_set_init(obj, name, بحث_flags, 0, &target_obj, &o, &dst);
    إذا (ret < 0)
        إرجاع ret;

    إرجاع ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_العدد(name, opttype, vartype)                         \
صحيح av_opt_eval_ ## name(فراغ *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## _out)        \
{                                                                       \
    إذا (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        إرجاع AVERROR(EINVAL);                                         \
    إرجاع set_string_العدد(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_العدد(flags,  AV_OPT_TYPE_FLAGS,    صحيح)
OPT_EVAL_العدد(صحيح,    AV_OPT_TYPE_INT,      صحيح)
OPT_EVAL_العدد(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_العدد(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_العدد(عائم,  AV_OPT_TYPE_FLOAT,    عائم)
OPT_EVAL_العدد(مزدوج, AV_OPT_TYPE_DOUBLE,   مزدوج)
OPT_EVAL_العدد(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ساكن صحيح set_العدد(فراغ *obj, ثابت حرف *name, مزدوج رقم, صحيح den, int64_t intnum,
                      صحيح بحث_flags, صحيح require_type)
{
    فراغ *dst;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_set_init(obj, name, بحث_flags, require_type, عدم, &o, &dst);
    إذا (ret < 0)
        إرجاع ret;
    إذا (dst)
        ret = write_العدد(obj, o, dst, رقم, den, intnum, 0);

    إرجاع ret;
}

صحيح av_opt_set_int(فراغ *obj, ثابت حرف *name, int64_t val, صحيح بحث_flags)
{
    إرجاع set_العدد(obj, name, 1, 1, val, بحث_flags, 0);
}

صحيح av_opt_set_double(فراغ *obj, ثابت حرف *name, مزدوج val, صحيح بحث_flags)
{
    إرجاع set_العدد(obj, name, val, 1, 1, بحث_flags, 0);
}

صحيح av_opt_set_q(فراغ *obj, ثابت حرف *name, AVRational val, صحيح بحث_flags)
{
    إرجاع set_العدد(obj, name, val.رقم, val.den, 1, بحث_flags, 0);
}

صحيح av_opt_set_bin(فراغ *obj, ثابت حرف *name, ثابت uint8_t *val, صحيح len, صحيح بحث_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحيح *lendst;
    صحيح ret;

    ret = opt_set_init(obj, name, بحث_flags, AV_OPT_TYPE_ثنائي,
                       عدم, عدم, (فراغ**)&dst);
    إذا (ret < 0)
        إرجاع ret;

    إذا (dst) {
    ptr = len ? av_malloc(len) : عدم;
    إذا (len && !ptr)
        إرجاع AVERROR(ENOMEM);

    lendst = (صحيح *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    إذا (len)
        memcpy(ptr, val, len);
    }

    إرجاع 0;
}

صحيح av_opt_set_image_size(فراغ *obj, ثابت حرف *name, صحيح w, صحيح h, صحيح بحث_flags)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح ret;

    ret = opt_set_init(obj, name, بحث_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       عدم, &o, (فراغ**)&dst);
    إذا (ret < 0)
        إرجاع ret;

    logctx = dst ? obj : عدم;

    إذا (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        إرجاع AVERROR(EINVAL);
    }

    إذا (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    إرجاع 0;
}

صحيح av_opt_set_video_rate(فراغ *obj, ثابت حرف *name, AVRational val, صحيح بحث_flags)
{
    إرجاع set_العدد(obj, name, val.رقم, val.den, 1, بحث_flags, AV_OPT_TYPE_VIDEO_RATE);
}

ساكن صحيح set_format(فراغ *obj, ثابت حرف *name, صحيح fmt, صحيح بحث_flags,
                      تعداد AVOptionType type, ثابت حرف *desc, صحيح nb_fmts)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح min, max, ret;

    ret = opt_set_init(obj, name, بحث_flags, type, عدم, &o, (فراغ**)&dst);
    إذا (ret < 0)
        إرجاع ret;

    logctx = dst ? obj : عدم;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    إذا (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        إرجاع AVERROR(ERANGE);
    }
    إذا (dst)
    *dst = fmt;
    إرجاع 0;
}

صحيح av_opt_set_pixel_fmt(فراغ *obj, ثابت حرف *name, تعداد AVPixelFormat fmt, صحيح بحث_flags)
{
    إرجاع set_format(obj, name, fmt, بحث_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحيح av_opt_set_sample_fmt(فراغ *obj, ثابت حرف *name, تعداد AVSampleFormat fmt, صحيح بحث_flags)
{
    إرجاع set_format(obj, name, fmt, بحث_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحيح av_opt_set_dict_val(فراغ *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحيح بحث_flags)
{
    AVDictionary **dst;
    صحيح ret;

    ret = opt_set_init(obj, name, بحث_flags, AV_OPT_TYPE_DICT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        إرجاع ret;

    إذا (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    إرجاع ret;
}

صحيح av_opt_set_chlayout(فراغ *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحيح بحث_flags)
{
    AVChannelLayout *dst;
    صحيح ret;

    ret = opt_set_init(obj, name, بحث_flags, AV_OPT_TYPE_CHLAYOUT, عدم, عدم,
                       (فراغ**)&dst);
    إذا (ret < 0)
        إرجاع ret;

    إذا (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    إرجاع ret;
}

ساكن فراغ format_duration(حرف *buf, size_t size, int64_t d)
{
    حرف *e;

    av_assert0(size >= 25);
    إذا (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    إذا (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    وإلا إذا (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    وإلا إذا (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحيح)((d / 60000000) % 60),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا إذا (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (صحيح)(d / 60000000),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا
        snprintf(buf, size, "%d.%06d",
                 (صحيح)(d / 1000000),
                 (صحيح)(d % 1000000));
    e = buf + strlen(buf);
    بينما (e > buf && e[-1] == '0')
        *(--e) = 0;
    إذا (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ساكن صحيح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت فراغ *dst, صحيح بحث_flags)
{
    صحيح ret;

    بدل (TYPE_BASE(o->type)) {
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
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
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
    حالة AV_OPT_TYPE_VIDEO_RATE:
    حالة AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->رقم, ((AVRational *)dst)->den);
        اكسر;
    حالة AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        اكسر;
    حالة AV_OPT_TYPE_STRING:
        إذا (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } وإلا إذا (بحث_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = عدم;
            إرجاع 0;
        } وإلا {
            *pbuf = av_strdup("");
        }
        إرجاع *pbuf ? 0 : AVERROR(ENOMEM);
    حالة AV_OPT_TYPE_ثنائي: {
        ثابت uint8_t *bin;
        صحيح len;

        إذا (!*(uint8_t **)dst && (بحث_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            إرجاع 0;
        }
        len = *(صحيح *)(((uint8_t *)dst) + حجم(uint8_t *));
        إذا ((uint64_t)len * 2 + 1 > INT_MAX)
            إرجاع AVERROR(EINVAL);
        إذا (!(*pbuf = av_malloc(len * 2 + 1)))
            إرجاع AVERROR(ENOMEM);
        إذا (!len) {
            *pbuf[0] = '\0';
            إرجاع 0;
        }
        bin = *(uint8_t **)dst;
        لكل (صحيح i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        إرجاع 0;
    }
    حالة AV_OPT_TYPE_IMAGE_SIZE:
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
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
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
        إذا (!*(AVDictionary **)dst && (بحث_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            إرجاع 0;
        }
        إرجاع av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    افتراضي:
        إرجاع AVERROR(EINVAL);
    }

    إرجاع ret;
}

ساكن صحيح opt_get_array(ثابت AVOption *o, فراغ *dst, uint8_t **out_val)
{
    ثابت unsigned تعداد_2 = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = عدم;
    size_t   str_len = 0;
    صحيح ret;

    *out_val = عدم;

    لكل (unsigned i = 0; i < تعداد_2; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, حجم(buf),
                           opt_array_pelem(o, *(فراغ **)dst, i), 0);
        إذا (ret < 0)
            اذهب fail;

        out_len = strlen(out);
        إذا (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            اذهب fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        إذا (ret < 0)
            اذهب fail;

        // add separator if needed
        إذا (i)
            str[str_len++] = sep;

        // escape the element
        لكل (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            إذا (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        إذا (out != buf)
            av_freep(&out);
        إذا (ret < 0) {
            av_freep(&str);
            إرجاع ret;
        }
    }

    *out_val = str;

    إرجاع 0;
}

صحيح av_opt_get(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, uint8_t **out_val)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    uint8_t *out, buf[128];
    صحيح ret;

    إذا (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        إرجاع AVERROR_OPTION_NOT_FOUND;

    إذا (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        إذا (ret < 0)
            إرجاع ret;
        إذا (!*out_val && !(بحث_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            إذا (!*out_val)
               إرجاع AVERROR(ENOMEM);
        }
        إرجاع 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, حجم(buf), dst, بحث_flags);
    إذا (ret < 0)
        إرجاع ret;
    إذا (out != buf) {
        *out_val = out;
        إرجاع 0;
    }

    إذا (ret >= حجم(buf))
        إرجاع AVERROR(EINVAL);
    *out_val = av_strdup(out);
    إرجاع *out_val ? 0 : AVERROR(ENOMEM);
}

ساكن صحيح get_العدد(فراغ *obj, ثابت حرف *name, مزدوج *رقم, صحيح *den, int64_t *intnum,
                      صحيح بحث_flags)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        إرجاع AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    إرجاع read_العدد(o, dst, رقم, den, intnum);
}

صحيح av_opt_get_int(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    مزدوج رقم = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_العدد(obj, name, &رقم, &den, &intnum, بحث_flags)) < 0)
        إرجاع ret;
    إذا (رقم == den)
        *out_val = intnum;
    وإلا
        *out_val = رقم * intnum / den;
    إرجاع 0;
}

صحيح av_opt_get_double(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, مزدوج *out_val)
{
    int64_t intnum = 1;
    مزدوج رقم = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_العدد(obj, name, &رقم, &den, &intnum, بحث_flags)) < 0)
        إرجاع ret;
    *out_val = رقم * intnum / den;
    إرجاع 0;
}

صحيح av_opt_get_q(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    مزدوج رقم = 1;
    صحيح ret, den = 1;

    إذا ((ret = get_العدد(obj, name, &رقم, &den, &intnum, بحث_flags)) < 0)
        إرجاع ret;

    إذا (رقم == 1.0 && (صحيح)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    وإلا
        *out_val = double_to_rational(رقم*intnum/den);
    إرجاع 0;
}

صحيح av_opt_get_image_size(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, صحيح *w_out, صحيح *h_out)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        إرجاع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    إذا (w_out) *w_out = *(صحيح *)dst;
    إذا (h_out) *h_out = *((صحيح *)dst+1);
    إرجاع 0;
}

صحيح av_opt_get_video_rate(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, AVRational *out_val)
{
    إرجاع av_opt_get_q(obj, name, بحث_flags, out_val);
}

ساكن صحيح get_format(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, فراغ *out_fmt,
                      تعداد AVOptionType type, ثابت حرف *desc)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        إرجاع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    إذا (type == AV_OPT_TYPE_PIXEL_FMT)
        *(تعداد AVPixelFormat *)out_fmt = *(تعداد AVPixelFormat *)dst;
    وإلا
        *(تعداد AVSampleFormat*)out_fmt = *(تعداد AVSampleFormat*)dst;

    إرجاع 0;
}

صحيح av_opt_get_pixel_fmt(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, تعداد AVPixelFormat *out_fmt)
{
    إرجاع get_format(obj, name, بحث_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحيح av_opt_get_sample_fmt(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, تعداد AVSampleFormat *out_fmt)
{
    إرجاع get_format(obj, name, بحث_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحيح av_opt_get_chlayout(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, AVChannelLayout *cl)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        إرجاع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    إرجاع av_channel_layout_copy(cl, dst);
}

صحيح av_opt_get_dict_val(فراغ *obj, ثابت حرف *name, صحيح بحث_flags, AVDictionary **out_val)
{
    فراغ *target_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);

    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (o->type != AV_OPT_TYPE_DICT)
        إرجاع AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    إرجاع av_dict_copy(out_val, src, 0);
}

صحيح av_opt_flag_is_set(فراغ *obj, ثابت حرف *field_name, ثابت حرف *flag_name)
{
    ثابت AVOption *field = av_opt_find(obj, field_name, عدم, 0, 0);
    ثابت AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : عدم, 0, 0);
    int64_t res;

    إذا (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        إرجاع 0;
    إرجاع res & flag->default_val.i64;
}

ساكن فراغ log_int_قيمة(فراغ *av_log_obj, صحيح level, int64_t i)
{
    إذا (i == INT_MAX) {
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

ساكن فراغ log_قيمة(فراغ *av_log_obj, صحيح level, مزدوج d)
{
    إذا      (d == INT_MAX) {
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

ساكن ثابت حرف *get_opt_const_name(فراغ *obj, ثابت حرف *unit, int64_t قيمة)
{
    ثابت AVOption *opt = عدم;

    إذا (!unit)
        إرجاع عدم;
    بينما ((opt = av_opt_next(obj, opt)))
        إذا (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == قيمة)
            إرجاع opt->name;
    إرجاع عدم;
}

ساكن حرف *get_opt_flags_string(فراغ *obj, ثابت حرف *unit, int64_t قيمة)
{
    ثابت AVOption *opt = عدم;
    حرف flags[512];

    flags[0] = 0;
    إذا (!unit)
        إرجاع عدم;
    بينما ((opt = av_opt_next(obj, opt))) {
        إذا (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & قيمة) {
            إذا (flags[0])
                av_strlcatf(flags, حجم(flags), "+");
            av_strlcatf(flags, حجم(flags), "%s", opt->name);
        }
    }
    إذا (flags[0])
        إرجاع av_strdup(flags);
    إرجاع عدم;
}

ساكن فراغ log_type(فراغ *av_log_obj, ثابت AVOption *o,
                     تعداد AVOptionType parent_type)
{
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);

    إذا (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
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
    إذا (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ثنائي)
        إرجاع;
    إذا ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        إرجاع;

    إذا (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت AVOptionArrayDef *arr = opt->default_val.arr;
        إذا (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        إرجاع;
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
            log_int_قيمة(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        اكسر;
    }
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_FLOAT:
        log_قيمة(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.رقم, q.den); }
        اكسر;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        اكسر;
    حالة AV_OPT_TYPE_COLOR:
    حالة AV_OPT_TYPE_IMAGE_SIZE:
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_DICT:
    حالة AV_OPT_TYPE_VIDEO_RATE:
    حالة AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        اكسر;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ساكن فراغ opt_list(فراغ *obj, فراغ *av_log_obj, ثابت حرف *unit,
                     صحيح req_flags, صحيح rej_flags, تعداد AVOptionType parent_type)
{
    ثابت AVOption *opt = عدم;
    AVOptionRanges *r;
    صحيح i;

    بينما ((opt = av_opt_next(obj, opt))) {
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

        إذا (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        إذا (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_بحث_FAKE_OBJ) >= 0) {
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
                    log_قيمة(av_log_obj, AV_LOG_INFO, r->range[i]->قيمة_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_قيمة(av_log_obj, AV_LOG_INFO, r->range[i]->قيمة_max);
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
        إرجاع -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, عدم, req_flags, rej_flags, -1);

    إرجاع 0;
}

فراغ av_opt_set_defaults(فراغ *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

فراغ av_opt_set_defaults2(فراغ *s, صحيح mask, صحيح flags)
{
    ثابت AVOption *opt = عدم;
    بينما ((opt = av_opt_next(s, opt))) {
        فراغ *dst = ((uint8_t*)s) + opt->offset;

        إذا ((opt->flags & mask) != flags)
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
                opt_set_array(s, s, opt, arr->def, dst);

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
                write_العدد(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
            حالة AV_OPT_TYPE_FLOAT: {
                مزدوج val;
                val = opt->default_val.dbl;
                write_العدد(s, opt, dst, val, 1, 1, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_العدد(s, opt, dst, 1, val.den, val.رقم, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_ثنائي:
                set_string_ثنائي(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                اكسر;
            حالة AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
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
ساكن صحيح parse_مفتاح_قيمة_pair(فراغ *ctx, ثابت حرف **buf,
                                ثابت حرف *مفتاح_val_sep, ثابت حرف *pairs_sep)
{
    حرف *مفتاح = av_get_token(buf, مفتاح_val_sep);
    حرف *val;
    صحيح ret;

    إذا (!مفتاح)
        إرجاع AVERROR(ENOMEM);

    إذا (*مفتاح && strspn(*buf, مفتاح_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        إذا (!val) {
            av_freep(&مفتاح);
            إرجاع AVERROR(ENOMEM);
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", مفتاح);
        av_free(مفتاح);
        إرجاع AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", مفتاح, val);

    ret = av_opt_set(ctx, مفتاح, val, AV_OPT_بحث_CHILDREN);
    إذا (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", مفتاح);

    av_free(مفتاح);
    av_free(val);
    إرجاع ret;
}

صحيح av_set_options_string(فراغ *ctx, ثابت حرف *opts,
                          ثابت حرف *مفتاح_val_sep, ثابت حرف *pairs_sep)
{
    صحيح ret, تعداد_2 = 0;

    إذا (!opts)
        إرجاع 0;

    بينما (*opts) {
        إذا ((ret = parse_مفتاح_قيمة_pair(ctx, &opts, مفتاح_val_sep, pairs_sep)) < 0)
            إرجاع ret;
        تعداد_2++;

        إذا (*opts)
            opts++;
    }

    إرجاع تعداد_2;
}

#define WHITESPACES " \n\t\r"

ساكن صحيح is_مفتاح_char(حرف c)
{
    إرجاع (unsigned)((c | 32) - 'a') < 26 ||
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
ساكن صحيح get_مفتاح(ثابت حرف **ropts, ثابت حرف *delim, حرف **rkey)
{
    ثابت حرف *opts = *ropts;
    ثابت حرف *مفتاح_start, *مفتاح_end;

    مفتاح_start = opts += strspn(opts, WHITESPACES);
    بينما (is_مفتاح_char(*opts))
        opts++;
    مفتاح_end = opts;
    opts += strspn(opts, WHITESPACES);
    إذا (!*opts || !strchr(delim, *opts))
        إرجاع AVERROR(EINVAL);
    opts++;
    إذا (!(*rkey = av_malloc(مفتاح_end - مفتاح_start + 1)))
        إرجاع AVERROR(ENOMEM);
    memcpy(*rkey, مفتاح_start, مفتاح_end - مفتاح_start);
    (*rkey)[مفتاح_end - مفتاح_start] = 0;
    *ropts = opts;
    إرجاع 0;
}

صحيح av_opt_get_مفتاح_قيمة(ثابت حرف **ropts,
                         ثابت حرف *مفتاح_val_sep, ثابت حرف *pairs_sep,
                         unsigned flags,
                         حرف **rkey, حرف **rval)
{
    صحيح ret;
    حرف *مفتاح = عدم, *val;
    ثابت حرف *opts = *ropts;

    إذا ((ret = get_مفتاح(&opts, مفتاح_val_sep, &مفتاح)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_مفتاح))
        إرجاع AVERROR(EINVAL);
    إذا (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(مفتاح);
        إرجاع AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = مفتاح;
    *rval  = val;
    إرجاع 0;
}

صحيح av_opt_set_from_string(فراغ *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *مفتاح_val_sep, ثابت حرف *pairs_sep)
{
    صحيح ret, تعداد_2 = 0;
    ثابت حرف *dummy_shorthand = عدم;
    ثابت حرف *مفتاح;

    إذا (!opts)
        إرجاع 0;
    إذا (!shorthand)
        shorthand = &dummy_shorthand;

    بينما (*opts) {
        حرف *parsed_مفتاح, *قيمة;
        ret = av_opt_get_مفتاح_قيمة(&opts, مفتاح_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_مفتاح : 0,
                                   &parsed_مفتاح, &قيمة);
        إذا (ret < 0) {
            إذا (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            وإلا
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            إرجاع ret;
        }
        إذا (*opts)
            opts++;
        إذا (parsed_مفتاح) {
            مفتاح = parsed_مفتاح;
            بينما (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } وإلا {
            مفتاح = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", مفتاح, قيمة);
        إذا ((ret = av_opt_set(ctx, مفتاح, قيمة, 0)) < 0) {
            إذا (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", مفتاح);
            av_free(قيمة);
            av_free(parsed_مفتاح);
            إرجاع ret;
        }

        av_free(قيمة);
        av_free(parsed_مفتاح);
        تعداد_2++;
    }
    إرجاع تعداد_2;
}

فراغ av_opt_free(فراغ *obj)
{
    ثابت AVOption *o = عدم;
    بينما ((o = av_opt_next(obj, o))) {
        فراغ *pitem = (uint8_t *)obj + o->offset;

        إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        وإلا
            opt_free_elem(o->type, pitem);
    }
}

صحيح av_opt_set_dict2(فراغ *obj, AVDictionary **options, صحيح بحث_flags)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVDictionary    *tmp = عدم;
    صحيح ret;

    إذا (!options)
        إرجاع 0;

    بينما ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->مفتاح, t->قيمة, بحث_flags);
        إذا (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->مفتاح, t->قيمة, AV_DICT_MULTIKEY);
        إذا (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->مفتاح, t->قيمة);
            av_dict_free(&tmp);
            إرجاع ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    إرجاع 0;
}

صحيح av_opt_set_dict(فراغ *obj, AVDictionary **options)
{
    إرجاع av_opt_set_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_find(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحيح opt_flags, صحيح بحث_flags)
{
    إرجاع av_opt_find2(obj, name, unit, opt_flags, بحث_flags, عدم);
}

ثابت AVOption *av_opt_find2(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحيح opt_flags, صحيح بحث_flags, فراغ **target_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = عدم;

    إذا(!obj)
        إرجاع عدم;

    c= *(AVClass**)obj;

    إذا (!c)
        إرجاع عدم;

    إذا (بحث_flags & AV_OPT_بحث_CHILDREN) {
        إذا (بحث_flags & AV_OPT_بحث_FAKE_OBJ) {
            فراغ *iter = عدم;
            ثابت AVClass *child;
            بينما (child = av_opt_child_class_iterate(c, &iter))
                إذا (o = av_opt_find2(&child, name, unit, opt_flags, بحث_flags, عدم))
                    إرجاع o;
        } وإلا {
            فراغ *child = عدم;
            بينما (child = av_opt_child_next(obj, child))
                إذا (o = av_opt_find2(child, name, unit, opt_flags, بحث_flags, target_obj))
                    إرجاع o;
        }
    }

    بينما (o = av_opt_next(obj, o)) {
        إذا (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            إذا (target_obj) {
                إذا (!(بحث_flags & AV_OPT_بحث_FAKE_OBJ))
                    *target_obj = obj;
                وإلا
                    *target_obj = عدم;
            }
            إرجاع o;
        }
    }
    إرجاع عدم;
}

فراغ *av_opt_child_next(فراغ *obj, فراغ *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    إذا (c->child_next)
        إرجاع c->child_next(obj, prev);
    إرجاع عدم;
}

ثابت AVClass *av_opt_child_class_iterate(ثابت AVClass *parent, فراغ **iter)
{
    إذا (parent->child_class_iterate)
        إرجاع parent->child_class_iterate(iter);
    إرجاع عدم;
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
                إرجاع AVERROR(ENOMEM);
        }
    } وإلا إذا (type == AV_OPT_TYPE_ثنائي) {
        ثابت uint8_t *ثابت *src8 = (ثابت uint8_t *ثابت *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        صحيح len = *(ثابت صحيح *)(src8 + 1);
        إذا (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        إذا (len && !*dst8) {
            *(صحيح *)(dst8 + 1) = 0;
            إرجاع AVERROR(ENOMEM);
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
        إرجاع av_dict_copy(ddictp, sdict, 0);
    } وإلا إذا (type == AV_OPT_TYPE_CHLAYOUT) {
        ثابت AVChannelLayout *slayout = (ثابت AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        إذا (dlayout != slayout) {
            إذا (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = عدم;
            إرجاع av_channel_layout_copy(dst, src);
        }
    } وإلا إذا (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } وإلا {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        إرجاع AVERROR(EINVAL);
    }

    إرجاع 0;
}

ساكن صحيح opt_copy_array(فراغ *logctx, ثابت AVOption *o,
                          فراغ **pdst, ثابت فراغ * ثابت *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    فراغ         *dst = عدم;
    صحيح ret;

    إذا (*pdst == *psrc) {
        *pdst                   = عدم;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    إذا (!dst)
        إرجاع AVERROR(ENOMEM);

    لكل (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(فراغ**)psrc, i));
        إذا (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            إرجاع ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    إرجاع 0;
}

صحيح av_opt_copy(فراغ *dst, ثابت فراغ *src)
{
    ثابت AVOption *o = عدم;
    ثابت AVClass *c;
    صحيح ret = 0;

    إذا (!src)
        إرجاع AVERROR(EINVAL);

    c = *(AVClass **)src;
    إذا (!c || c != *(AVClass **)dst)
        إرجاع AVERROR(EINVAL);

    بينما ((o = av_opt_next(src, o))) {
        فراغ *field_dst = (uint8_t *)dst + o->offset;
        فراغ *field_src = (uint8_t *)src + o->offset;

        صحيح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        إذا (err < 0)
            ret = err;
    }
    إرجاع ret;
}

صحيح av_opt_get_array_size(فراغ *obj, ثابت حرف *name, صحيح بحث_flags,
                          unsigned صحيح *out_val)
{
    فراغ *target_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        إرجاع AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    إرجاع 0;
}

صحيح av_opt_get_array(فراغ *obj, ثابت حرف *name, صحيح بحث_flags,
                     unsigned صحيح start_elem, unsigned صحيح nb_elems,
                     تعداد AVOptionType out_type, فراغ *out_val)
{
    ثابت size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ثابت AVOption *o;
    فراغ *target_obj;

    ثابت فراغ *parray;
    unsigned array_size;

    صحيح ret;

    o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target_obj);
    إذا (!o || !target_obj)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        إرجاع AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    إذا (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        إرجاع AVERROR(EINVAL);

    لكل (unsigned i = 0; i < nb_elems; i++) {
        ثابت فراغ *src = opt_array_pelem(o, *(فراغ**)parray, start_elem + i);
        فراغ       *dst = (uint8_t*)out_val + i * elem_size_out;

        إذا (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            إذا (ret < 0)
                اذهب fail;
        } وإلا إذا (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, حجم(buf), src, بحث_flags);
            إذا (ret < 0)
                اذهب fail;

            إذا (out == buf) {
                out = av_strdup(buf);
                إذا (!out) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
            }

            *(uint8_t**)dst = out;
        } وإلا إذا (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            مزدوج     رقم = 1.0;
            صحيح        den = 1;
            int64_t intnum = 1;

            ret = read_العدد(o, src, &رقم, &den, &intnum);
            إذا (ret < 0)
                اذهب fail;

            بدل (out_type) {
            حالة AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (رقم == den) ?  intnum : رقم * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
                *(مزدوج*)dst = رقم * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (رقم == 1.0 && (صحيح)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(رقم * intnum / den);
                اكسر;
            افتراضي: av_assert0(0);
            }
        } وإلا
            إرجاع AVERROR(ENOSYS);
    }

    إرجاع 0;
fail:
    لكل (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    إرجاع ret;
}

صحيح av_opt_set_array(فراغ *obj, ثابت حرف *name, صحيح بحث_flags,
                     unsigned صحيح start_elem, unsigned صحيح nb_elems,
                     تعداد AVOptionType val_type, ثابت فراغ *val)
{
    ثابت size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ثابت AVOption *o;
    ثابت AVOptionArrayDef *arr;
    فراغ *target_obj;

    فراغ *parray;
    فراغ *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    صحيح ret = 0;

    ret = opt_set_init(obj, name, بحث_flags, 0, &target_obj, &o, &parray);
    إذا (ret < 0)
        إرجاع ret;

    إذا (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        إرجاع AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    إذا (start_elem > *array_size)
        إرجاع AVERROR(EINVAL);

    // compute new array size
    إذا (!val) {
        إذا (*array_size - start_elem < nb_elems)
            إرجاع AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } وإلا إذا (بحث_flags & AV_OPT_ARRAY_REPLACE) {
        إذا (start_elem >= UINT_MAX - nb_elems)
            إرجاع AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } وإلا {
        إذا (nb_elems >= UINT_MAX - *array_size)
            إرجاع AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    إذا (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        إرجاع AVERROR(EINVAL);

    // desired operation is shrinking the array
    إذا (!val) {
        فراغ *array = *(فراغ**)parray;

        لكل (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        إذا (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            إذا (!array)
                إرجاع AVERROR(ENOMEM);

            *(فراغ**)parray = array;
        } وإلا
            av_freep(parray);

        *array_size = new_size;

        إرجاع 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    إذا (!new_elems)
        إرجاع AVERROR(ENOMEM);

    // convert/validate each new element
    لكل (unsigned i = 0; i < nb_elems; i++) {
        فراغ       *dst = opt_array_pelem(o, new_elems, i);
        ثابت فراغ *src = (uint8_t*)val + i * elem_size_val;

        مزدوج     رقم = 1.0;
        صحيح        den = 1;
        int64_t intnum = 1;

        إذا (val_type == TYPE_BASE(o->type)) {
            صحيح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            إذا (ret < 0)
                اذهب fail;

            // validate the range for numeric options
            err = read_العدد(o, dst, &رقم, &den, &intnum);
            إذا (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < رقم * intnum || o->min * den > رقم * intnum)) {
                رقم = den ? رقم * intnum / den : (رقم && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, رقم, o->min, o->max);
                ret = AVERROR(ERANGE);
                اذهب fail;
            }
        } وإلا إذا (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ثابت حرف **)src, dst);
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
            حالة AV_OPT_TYPE_FLOAT:     رقم    = *(عائم*)src;              اكسر;
            حالة AV_OPT_TYPE_DOUBLE:    رقم    = *(مزدوج*)src;             اكسر;
            حالة AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->رقم;
                                        den    = ((AVRational*)src)->den;   اكسر;
            افتراضي: av_assert0(0);
            }

            ret = write_العدد(obj, o, dst, رقم, den, intnum, 0);
            إذا (ret < 0)
                اذهب fail;
        } وإلا {
            ret = AVERROR(ENOSYS);
            اذهب fail;
        }
    }

    // commit new elements to the array
    إذا (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(فراغ**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = عدم;
        nb_elems  = 0;
    } وإلا {
        فراغ *array = av_realloc_array(*(فراغ**)parray, new_size, elem_size);
        إذا (!array) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }

        إذا (بحث_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            لكل (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } وإلا {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(فراغ**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    إرجاع ret;
}

صحيح av_opt_query_ranges(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *مفتاح, صحيح flags)
{
    صحيح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحيح (*callback)(AVOptionRanges **, فراغ *obj, ثابت حرف *مفتاح, صحيح flags) = c->query_ranges;

    إذا (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, مفتاح, flags);
    إذا (ret >= 0) {
        إذا (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    إرجاع ret;
}

صحيح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *مفتاح, صحيح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(فراغ*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *field = av_opt_find(obj, مفتاح, عدم, 0, flags);
    صحيح ret;

    *ranges_arg = عدم;

    إذا (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->قيمة_min = field->min;
    range->قيمة_max = field->max;

    بدل (field->type) {
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
        range->قيمة_min = -1;
        range->قيمة_max = INT_MAX;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        اكسر;
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->قيمة_min = 0;
        range->قيمة_max = INT_MAX/8;
        اكسر;
    حالة AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->قيمة_min = 1;
        range->قيمة_max = INT_MAX;
        اكسر;
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    *ranges_arg = ranges;
    إرجاع 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    إرجاع ret;
}

فراغ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    صحيح i;
    AVOptionRanges *ranges = *rangesp;

    إذا (!ranges)
        إرجاع;

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

صحيح av_opt_is_set_to_default(فراغ *obj, ثابت AVOption *o)
{
    int64_t i64;
    مزدوج d;
    AVRational q;
    صحيح ret, w, h;
    حرف *str;
    فراغ *dst;

    إذا (!o || !obj)
        إرجاع AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    إذا (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت حرف *def = o->default_val.arr ? o->default_val.arr->def : عدم;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        إذا (ret < 0)
            إرجاع ret;

        إذا (!!val != !!def)
            ret = 0;
        وإلا إذا (val)
            ret = !strcmp(val, def);
        وإلا
            ret = 1;

        av_freep(&val);

        إرجاع ret;
    }

    بدل (o->type) {
    حالة AV_OPT_TYPE_CONST:
        إرجاع 1;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_PIXEL_FMT:
    حالة AV_OPT_TYPE_SAMPLE_FMT:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        read_العدد(o, dst, عدم, عدم, &i64);
        إرجاع o->default_val.i64 == i64;
    حالة AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        إذا (o->default_val.str) {
            إذا ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                إرجاع ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        إرجاع ret;
    }
    حالة AV_OPT_TYPE_STRING:
        str = *(حرف **)dst;
        إذا (str == o->default_val.str) //2 NULLs
            إرجاع 1;
        إذا (!str || !o->default_val.str) //1 NULL
            إرجاع 0;
        إرجاع !strcmp(str, o->default_val.str);
    حالة AV_OPT_TYPE_DOUBLE:
        d = *(مزدوج *)dst;
        إرجاع o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالة AV_OPT_TYPE_FLOAT:
        d = *(عائم *)dst;
        إرجاع (عائم)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        إرجاع !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالة AV_OPT_TYPE_ثنائي: {
        بنية {
            uint8_t *data;
            صحيح size;
        } tmp = {0};
        صحيح opt_size = *(صحيح *)((فراغ **)dst + 1);
        فراغ *opt_ptr = *(فراغ **)dst;
        إذا (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            إرجاع 1;
        إذا (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            إرجاع 0;
        إذا (opt_size != strlen(o->default_val.str) / 2)
            إرجاع 0;
        ret = set_string_ثنائي(عدم, عدم, o->default_val.str, &tmp.data);
        إذا (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        إرجاع ret;
    }
    حالة AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = عدم;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionaryEntry *en1 = عدم;
        ثابت AVDictionaryEntry *en2 = عدم;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        إذا (ret < 0) {
            av_dict_free(&dict1);
            إرجاع ret;
        }
        افعل {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } بينما (en1 && en2 && !strcmp(en1->مفتاح, en2->مفتاح) && !strcmp(en1->قيمة, en2->قيمة));
        av_dict_free(&dict1);
        إرجاع (!en1 && !en2);
    }
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        إذا (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        وإلا إذا ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            إرجاع ret;
        إرجاع (w == *(صحيح *)dst) && (h == *((صحيح *)dst+1));
    حالة AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        إذا (o->default_val.str) {
            إذا ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                إرجاع ret;
        }
        إرجاع !av_cmp_q(*(AVRational*)dst, q);
    حالة AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        إذا (o->default_val.str) {
            إذا ((ret = av_parse_color(color, o->default_val.str, -1, عدم)) < 0)
                إرجاع ret;
        }
        إرجاع !memcmp(color, dst, حجم(color));
    }
    افتراضي:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        اكسر;
    }
    إرجاع AVERROR_PATCHWELCOME;
}

صحيح av_opt_is_set_to_default_by_name(فراغ *obj, ثابت حرف *name, صحيح بحث_flags)
{
    ثابت AVOption *o;
    فراغ *target;
    إذا (!obj)
        إرجاع AVERROR(EINVAL);
    o = av_opt_find2(obj, name, عدم, 0, بحث_flags, &target);
    إذا (!o)
        إرجاع AVERROR_OPTION_NOT_FOUND;
    إرجاع av_opt_is_set_to_default(target, o);
}

ساكن صحيح opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, صحيح *cnt,
                         AVBPrint *bprint, ثابت حرف مفتاح_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVOption *o = عدم;
    فراغ *child = عدم;
    uint8_t *buf;
    صحيح ret;
    ثابت حرف special_chars[] = {pairs_sep, مفتاح_val_sep, '\0'};

    إذا (flags & AV_OPT_SERIALIZE_بحث_CHILDREN)
        بينما (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                مفتاح_val_sep, pairs_sep);
            إذا (ret < 0)
                إرجاع ret;
        }

    بينما (o = av_opt_next(obj, o)) {
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
        إذا (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            استمر;
        إذا ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, عدم);
            إرجاع ret;
        }
        إذا (buf) {
            إذا ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &مفتاح_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    إرجاع 0;
}

صحيح av_opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, حرف **buffer,
                     ثابت حرف مفتاح_val_sep, ثابت حرف pairs_sep)
{
    AVBPrint bprint;
    صحيح ret, cnt = 0;

    إذا (pairs_sep == '\0' || مفتاح_val_sep == '\0' || pairs_sep == مفتاح_val_sep ||
        pairs_sep == '\\' || مفتاح_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        إرجاع AVERROR(EINVAL);
    }

    إذا (!obj || !buffer)
        إرجاع AVERROR(EINVAL);

    *buffer = عدم;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        مفتاح_val_sep, pairs_sep);
    إذا (ret < 0)
        إرجاع ret;

    ret = av_bprint_finalize(&bprint, buffer);
    إذا (ret < 0)
        إرجاع ret;
    إرجاع 0;
}
