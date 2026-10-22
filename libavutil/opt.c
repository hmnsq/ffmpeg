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

#شامل "avutil.h"
#شامل "avassert.h"
#شامل "avstring.h"
#شامل "channel_layout.h"
#شامل "dict.h"
#شامل "eval.h"
#شامل "log.h"
#شامل "mem.h"
#شامل "parseutils.h"
#شامل "pixdesc.h"
#شامل "mathematics.h"
#شامل "opt.h"
#شامل "samplefmt.h"
#شامل "bprint.h"

#شامل <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ثابت AVOption *av_opt_next(ثابت تهی *obj, ثابت AVOption *last)
{
    ثابت AVClass *class;
    اگر (!obj)
        بازگشت پوچ;
    class = *(ثابت AVClass**)obj;
    اگر (!last && class && class->option && class->option[0].name)
        بازگشت class->option;
    اگر (last && last[1].name)
        بازگشت ++last;
    بازگشت پوچ;
}

ایستا ثابت ساختار {
    size_t      size;
    ثابت نویسه *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { اندازه(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { اندازه(صحیح),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { اندازه(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { اندازه(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { اندازه(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { اندازه(دوگانه),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { اندازه(اعشاری),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { اندازه(نویسه *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { اندازه(AVRational),     "<rational>" },
    [AV_OPT_TYPE_دودویی]        = { اندازه(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { اندازه(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { اندازه(صحیح[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { اندازه(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { اندازه(شمارش AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { اندازه(شمارش AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { اندازه(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { اندازه(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { اندازه(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { اندازه(صحیح),            "<boolean>" },
};

// option is plain old data
ایستا صحیح opt_is_pod(شمارش AVOptionType type)
{
    انتخاب (type) {
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_FLOAT:
    حالت AV_OPT_TYPE_RATIONAL:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_IMAGE_SIZE:
    حالت AV_OPT_TYPE_PIXEL_FMT:
    حالت AV_OPT_TYPE_SAMPLE_FMT:
    حالت AV_OPT_TYPE_VIDEO_RATE:
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_COLOR:
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_UINT:
        بازگشت 1;
    }
    بازگشت 0;
}

ایستا uint8_t opt_array_sep(ثابت AVOption *o)
{
    ثابت AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    بازگشت (d && d->sep) ? d->sep : ',';
}

ایستا تهی *opt_array_pelem(ثابت AVOption *o, تهی *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    بازگشت (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

ایستا unsigned *opt_array_pcount(ثابت تهی *parray)
{
    بازگشت (unsigned *)((ثابت تهی * ثابت *)parray + 1);
}

ایستا تهی opt_free_elem(شمارش AVOptionType type, تهی *ptr)
{
    انتخاب (TYPE_BASE(type)) {
    حالت AV_OPT_TYPE_STRING:
    حالت AV_OPT_TYPE_دودویی:
        av_freep(ptr);
        بشکن;

    حالت AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        بشکن;

    حالت AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        بشکن;

    پیشفرض:
        بشکن;
    }
}

ایستا تهی opt_free_array(ثابت AVOption *o, تهی *parray, unsigned *شمار)
{
    برای (unsigned i = 0; i < *شمار; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(تهی **)parray, i));

    av_freep(parray);
    *شمار = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ایستا صحیح opt_set_init(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags,
                        صحیح require_type,
                        تهی **ptgt, ثابت AVOption **po, تهی **pdst)
{
    تهی *logctx;
    ثابت AVOption *o;
    تهی *tgt;

    o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &tgt);
    اگر (!o || (!tgt && !(جستجو_flags & AV_OPT_جستجو_FAKE_OBJ)))
        بازگشت AVERROR_OPTION_NOT_FOUND;

    اگر (o->flags & AV_OPT_FLAG_READONLY)
        بازگشت AVERROR(EINVAL);

    logctx = tgt ? obj : پوچ;

    اگر (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        بازگشت AVERROR(EINVAL);
    }

    اگر (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = پوچ;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        اگر (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        اگر (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            اگر (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        اگر (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            بازگشت AVERROR(EINVAL);
        }
    }

    اگر (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    اگر (po)
        *po   = o;
    اگر (ptgt)
        *ptgt = tgt;
    اگر (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : پوچ;

    بازگشت 0;
}

ایستا AVRational double_to_rational(دوگانه d)
{
     AVRational r = av_d2q(d, 1 << 24);
     اگر ((!r.رقم || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     بازگشت r;
}

ایستا صحیح read_عدد(ثابت AVOption *o, ثابت تهی *dst, دوگانه *رقم, صحیح *den, int64_t *intnum)
{
    انتخاب (TYPE_BASE(o->type)) {
    حالت AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned صحیح*)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(شمارش AVPixelFormat *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(شمارش AVSampleFormat *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_INT:
        *intnum = *(صحیح *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_UINT:
        *intnum = *(unsigned صحیح *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_FLOAT:
        *رقم = *(اعشاری *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_DOUBLE:
        *رقم = *(دوگانه *)dst;
        بازگشت 0;
    حالت AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->رقم;
        *den    = ((AVRational *)dst)->den;
        بازگشت 0;
    حالت AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        بازگشت 0;
    }
    بازگشت AVERROR(EINVAL);
}

ایستا صحیح write_عدد(تهی *obj, ثابت AVOption *o, تهی *dst,
                        دوگانه رقم, صحیح den, int64_t intnum,
                        صحیح ignore_range)
{
    تهی *logctx = dst ? obj : پوچ;
    ثابت شمارش AVOptionType type = TYPE_BASE(o->type);

    اگر (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < رقم * intnum || o->min * den > رقم * intnum)) {
        رقم = den ? رقم * intnum / den : (رقم && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               رقم, o->name, o->min, o->max);
        بازگشت AVERROR(ERANGE);
    }
    اگر (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        دوگانه d = رقم*intnum/den;
        اگر (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   رقم*intnum/den, o->name);
            بازگشت AVERROR(ERANGE);
        }
    }

    اگر (!dst)
        بازگشت 0;

    انتخاب (type) {
    حالت AV_OPT_TYPE_PIXEL_FMT:
        *(شمارش AVPixelFormat *)dst = llrint(رقم / den) * intnum;
        بشکن;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        *(شمارش AVSampleFormat *)dst = llrint(رقم / den) * intnum;
        بشکن;
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
        *(صحیح *)dst = llrint(رقم / den) * intnum;
        بشکن;
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_INT64:{
        دوگانه d = رقم / den;
        اگر (intnum == 1 && d == (دوگانه)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } وگرنه
            *(int64_t *)dst = llrint(d) * intnum;
        بشکن;}
    حالت AV_OPT_TYPE_UINT64:{
        دوگانه d = رقم / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        اگر (intnum == 1 && d == (دوگانه)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } وگرنه اگر (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } وگرنه {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        بشکن;}
    حالت AV_OPT_TYPE_FLOAT:
        *(اعشاری *)dst = رقم * intnum / den;
        بشکن;
    حالت AV_OPT_TYPE_DOUBLE:
        *(دوگانه    *)dst = رقم * intnum / den;
        بشکن;
    حالت AV_OPT_TYPE_RATIONAL:
    حالت AV_OPT_TYPE_VIDEO_RATE:
        اگر ((صحیح) رقم == رقم)
            *(AVRational *)dst = (AVRational) { رقم *intnum, den };
        وگرنه
            *(AVRational *)dst = double_to_rational(رقم * intnum / den);
        بشکن;
    پیشفرض:
        بازگشت AVERROR(EINVAL);
    }
    بازگشت 0;
}

ایستا صحیح hexchar2int(نویسه c) {
    اگر (c >= '0' && c <= '9')
        بازگشت c - '0';
    اگر (c >= 'a' && c <= 'f')
        بازگشت c - 'a' + 10;
    اگر (c >= 'A' && c <= 'F')
        بازگشت c - 'A' + 10;
    بازگشت -1;
}

ایستا صحیح set_string_دودویی(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t **dst)
{
    صحیح *lendst;
    uint8_t *bin, *ptr;
    صحیح len;

    اگر (dst) {
        lendst = (صحیح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    اگر (!val || !(len = strlen(val)))
        بازگشت 0;

    اگر (len & 1)
        بازگشت AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    اگر (!ptr)
        بازگشت AVERROR(ENOMEM);
    وقتی (*val) {
        صحیح a = hexchar2int(*val++);
        صحیح b = hexchar2int(*val++);
        اگر (a < 0 || b < 0) {
            av_free(bin);
            بازگشت AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    اگر (dst) {
        *dst    = bin;
        *lendst = len;
    } وگرنه {
        av_free(bin);
    }

    بازگشت 0;
}

ایستا صحیح set_string(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t **dst)
{
    اگر (!dst)
        بازگشت 0;
    av_freep(dst);
    اگر (!val)
        بازگشت 0;
    *dst = av_strdup(val);
    بازگشت *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ایستا صحیح set_string_عدد(تهی *obj, تهی *target_obj, ثابت AVOption *o, ثابت نویسه *val, تهی *dst)
{
    تهی *logctx = dst ? obj : پوچ;
    ثابت شمارش AVOptionType type = TYPE_BASE(o->type);
    صحیح ret = 0;

    اگر (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        صحیح رقم, den;
        نویسه c;
        اگر (sscanf(val, "%d%*1[:/]%d%c", &رقم, &den, &c) == 2) {
            اگر ((ret = write_عدد(obj, o, dst, 1, den, رقم, 0)) >= 0)
                بازگشت ret;
            ret = 0;
        }
    }

    برای (;;) {
        صحیح i = 0;
        نویسه buf[256];
        صحیح cmd = 0;
        دوگانه d;
        int64_t intnum = 1;

        اگر (type == AV_OPT_TYPE_FLAGS) {
            اگر (*val == '+' || *val == '-')
                cmd = *(val++);
            برای (; i < اندازه(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            صحیح res;
            صحیح ci = 0;
            دوگانه const_مقادیر[64];
            ثابت نویسه * const_names[64];
            صحیح جستجو_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_جستجو_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, جستجو_flags);
            اگر (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                اگر (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } وگرنه {
                اگر (o->unit) {
                    برای (o_named = پوچ; o_named = av_opt_next(target_obj, o_named); ) {
                        اگر (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            اگر (ci + 6 >= FF_ARRAY_ELEMS(const_مقادیر)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                بازگشت AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_مقادیر[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_مقادیر[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_مقادیر[ci++] = o->max;
                const_names [ci  ] = "min";
                const_مقادیر[ci++] = o->min;
                const_names [ci  ] = "none";
                const_مقادیر[ci++] = 0;
                const_names [ci  ] = "all";
                const_مقادیر[ci++] = ~0;
                const_names [ci] = پوچ;
                const_مقادیر[ci] = 0;

                res = av_عبارت_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_مقادیر, پوچ, پوچ, پوچ, پوچ, پوچ, 0, obj);
                اگر (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    بازگشت res;
                }
            }
        }
        اگر (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned صحیح*)dst;
            اگر (cmd == '+')
                d = intnum | (int64_t)d;
            وگرنه اگر (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        اگر ((ret = write_عدد(obj, o, dst, d, 1, 1, 0)) < 0)
            بازگشت ret;
        val += i;
        اگر (!i || !*val)
            بازگشت 0;
    }
}

ایستا صحیح set_string_image_size(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, صحیح *dst)
{
    تهی *logctx = dst ? obj : پوچ;
    صحیح tmp[2];
    صحیح ret;

    اگر (!val || !strcmp(val, "none")) {
        اگر (dst) {
        dst[0] =
        dst[1] = 0;
        }
        بازگشت 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    اگر (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        بازگشت ret;
    }
    اگر (dst)
        memcpy(dst, tmp, اندازه(tmp));
    بازگشت ret;
}

ایستا صحیح set_string_video_rate(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, AVRational *dst)
{
    تهی *logctx = dst ? obj : پوچ;
    AVRational tmp;
    صحیح ret = av_parse_video_rate(&tmp, val);
    اگر (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    اگر (dst)
        *dst = tmp;
    بازگشت ret;
}

ایستا صحیح set_string_color(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t *dst)
{
    تهی *logctx = dst ? obj : پوچ;
    صحیح ret;

    اگر (!val) {
        بازگشت 0;
    } وگرنه {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        اگر (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            بازگشت ret;
        }
        اگر (dst)
            memcpy(dst, tmp, اندازه(tmp));
        بازگشت ret;
    }
    بازگشت 0;
}

ایستا ثابت نویسه *get_bool_name(صحیح val)
{
    اگر (val < 0)
        بازگشت "auto";
    بازگشت val ? "true" : "false";
}

ایستا صحیح set_string_bool(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, صحیح *dst)
{
    تهی *logctx = dst ? obj : پوچ;
    صحیح n;

    اگر (!val)
        بازگشت 0;

    اگر (!strcmp(val, "auto")) {
        n = -1;
    } وگرنه اگر (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } وگرنه اگر (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } وگرنه {
        نویسه *end = پوچ;
        n = strtol(val, &end, 10);
        اگر (val + strlen(val) != end)
            برو fail;
    }

    اگر (n < o->min || n > o->max)
        برو fail;

    اگر (dst)
    *dst = n;
    بازگشت 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    بازگشت AVERROR(EINVAL);
}

ایستا صحیح set_string_fmt(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t *dst,
                          صحیح fmt_nb, صحیح ((*get_fmt)(ثابت نویسه *)), ثابت نویسه *desc,
                          شمارش AVOptionType type)
{
    تهی *logctx = dst ? obj : پوچ;
    صحیح fmt, min, max;

    اگر (!val || !strcmp(val, "none")) {
        fmt = -1;
    } وگرنه {
        fmt = get_fmt(val);
        اگر (fmt == -1) {
            نویسه *tail;
            fmt = strtol(val, &tail, 0);
            اگر (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                بازگشت AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    اگر(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    اگر (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        بازگشت AVERROR(ERANGE);
    }

    اگر (dst)
    انتخاب (type) {
    حالت AV_OPT_TYPE_PIXEL_FMT:  *(شمارش AVPixelFormat *)dst = fmt; بشکن;
    حالت AV_OPT_TYPE_SAMPLE_FMT: *(شمارش AVSampleFormat*)dst = fmt; بشکن;
    پیشفرض: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    بازگشت 0;
}

ایستا صحیح get_pix_fmt(ثابت نویسه *name)
{
    بازگشت av_get_pix_fmt(name);
}

ایستا صحیح set_string_pixel_fmt(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t *dst)
{
    بازگشت set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ایستا صحیح get_sample_fmt(ثابت نویسه *name)
{
    بازگشت av_get_sample_fmt(name);
}

ایستا صحیح set_string_sample_fmt(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t *dst)
{
    بازگشت set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ایستا صحیح set_string_dict(تهی *obj, ثابت AVOption *o, ثابت نویسه *val, uint8_t **dst)
{
    AVDictionary *options = پوچ;

    اگر (val) {
        صحیح ret = av_dict_parse_string(&options, val, "=", ":", 0);
        اگر (ret < 0) {
            av_dict_free(&options);
            بازگشت ret;
        }
    }

    اگر (!dst) {
        av_dict_free(&options);
        بازگشت 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    بازگشت 0;
}

ایستا صحیح set_string_channel_layout(تهی *obj, ثابت AVOption *o,
                                     ثابت نویسه *val, تهی *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    صحیح ret;
    اگر (dst)
    av_channel_layout_uninit(channel_layout);
    وگرنه
        channel_layout = &tmp;
    اگر (!val)
        بازگشت 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    اگر (ret < 0)
        بازگشت ret;
    اگر (!dst)
        av_channel_layout_uninit(channel_layout);
    بازگشت 0;
}

ایستا صحیح opt_set_elem(تهی *obj, تهی *target_obj, ثابت AVOption *o,
                        ثابت نویسه *val, تهی *dst)
{
    تهی *logctx = dst ? obj : پوچ;
    ثابت شمارش AVOptionType type = TYPE_BASE(o->type);
    صحیح ret;

    اگر (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        بازگشت AVERROR(EINVAL);

    انتخاب (type) {
    حالت AV_OPT_TYPE_BOOL:
        بازگشت set_string_bool(obj, o, val, dst);
    حالت AV_OPT_TYPE_STRING:
        بازگشت set_string(obj, o, val, dst);
    حالت AV_OPT_TYPE_دودویی:
        بازگشت set_string_دودویی(obj, o, val, dst);
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_FLOAT:
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_RATIONAL:
        بازگشت set_string_عدد(obj, target_obj, o, val, dst);
    حالت AV_OPT_TYPE_IMAGE_SIZE:
        بازگشت set_string_image_size(obj, o, val, dst);
    حالت AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        اگر (ret < 0)
            بازگشت ret;
        بازگشت write_عدد(obj, o, dst, 1, tmp.den, tmp.رقم, 0);
    }
    حالت AV_OPT_TYPE_PIXEL_FMT:
        بازگشت set_string_pixel_fmt(obj, o, val, dst);
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        بازگشت set_string_sample_fmt(obj, o, val, dst);
    حالت AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            اگر (val) {
                اگر ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    بازگشت ret;
                }
            }
            اگر (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                بازگشت AVERROR(ERANGE);
            }
            اگر (dst)
            *(int64_t *)dst = usecs;
            بازگشت 0;
        }
    حالت AV_OPT_TYPE_COLOR:
        بازگشت set_string_color(obj, o, val, dst);
    حالت AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        اگر (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        بازگشت ret;
    حالت AV_OPT_TYPE_DICT:
        بازگشت set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    بازگشت AVERROR(EINVAL);
}

ایستا صحیح opt_set_array(تهی *obj, تهی *target_obj, ثابت AVOption *o,
                         ثابت نویسه *val, تهی *dst)
{
    ثابت AVOptionArrayDef *arr = o->default_val.arr;
    ثابت size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    ثابت uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = پوچ;

    تهی      *logctx = dst ? obj : پوچ;
    تهی       *elems = پوچ;
    unsigned nb_elems = 0;
    صحیح ret;

    اگر (val && *val) {
        str = av_malloc(strlen(val) + 1);
        اگر (!str)
            بازگشت AVERROR(ENOMEM);
    }

    // split and unescape the string
    وقتی (val && *val) {
        uint8_t *p = str;
        تهی *tmp;

        اگر (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            برو fail;
        }

        برای (; *val; val++, p++) {
            اگر (*val == '\\' && val[1])
                val++;
            وگرنه اگر (*val == sep) {
                val++;
                بشکن;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        اگر (!tmp) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        اگر (ret < 0)
            برو fail;
        nb_elems++;
    }
    av_freep(&str);

    اگر (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    اگر (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        برو fail;
    }

    اگر (dst) {
    *((تهی **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } وگرنه
        opt_free_array(o, &elems, &nb_elems);

    بازگشت 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    بازگشت ret;
}

صحیح av_opt_set(تهی *obj, ثابت نویسه *name, ثابت نویسه *val, صحیح جستجو_flags)
{
    تهی *dst, *target_obj;
    ثابت AVOption *o;
    صحیح ret;

    ret = opt_set_init(obj, name, جستجو_flags, 0, &target_obj, &o, &dst);
    اگر (ret < 0)
        بازگشت ret;

    بازگشت ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_عدد(name, opttype, vartype)                         \
صحیح av_opt_eval_ ## name(تهی *obj, ثابت AVOption *o,                  \
                         ثابت نویسه *val, vartype *name ## _out)        \
{                                                                       \
    اگر (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        بازگشت AVERROR(EINVAL);                                         \
    بازگشت set_string_عدد(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_عدد(flags,  AV_OPT_TYPE_FLAGS,    صحیح)
OPT_EVAL_عدد(صحیح,    AV_OPT_TYPE_INT,      صحیح)
OPT_EVAL_عدد(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_عدد(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_عدد(اعشاری,  AV_OPT_TYPE_FLOAT,    اعشاری)
OPT_EVAL_عدد(دوگانه, AV_OPT_TYPE_DOUBLE,   دوگانه)
OPT_EVAL_عدد(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ایستا صحیح set_عدد(تهی *obj, ثابت نویسه *name, دوگانه رقم, صحیح den, int64_t intnum,
                      صحیح جستجو_flags, صحیح require_type)
{
    تهی *dst;
    ثابت AVOption *o;
    صحیح ret;

    ret = opt_set_init(obj, name, جستجو_flags, require_type, پوچ, &o, &dst);
    اگر (ret < 0)
        بازگشت ret;
    اگر (dst)
        ret = write_عدد(obj, o, dst, رقم, den, intnum, 0);

    بازگشت ret;
}

صحیح av_opt_set_int(تهی *obj, ثابت نویسه *name, int64_t val, صحیح جستجو_flags)
{
    بازگشت set_عدد(obj, name, 1, 1, val, جستجو_flags, 0);
}

صحیح av_opt_set_double(تهی *obj, ثابت نویسه *name, دوگانه val, صحیح جستجو_flags)
{
    بازگشت set_عدد(obj, name, val, 1, 1, جستجو_flags, 0);
}

صحیح av_opt_set_q(تهی *obj, ثابت نویسه *name, AVRational val, صحیح جستجو_flags)
{
    بازگشت set_عدد(obj, name, val.رقم, val.den, 1, جستجو_flags, 0);
}

صحیح av_opt_set_bin(تهی *obj, ثابت نویسه *name, ثابت uint8_t *val, صحیح len, صحیح جستجو_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحیح *lendst;
    صحیح ret;

    ret = opt_set_init(obj, name, جستجو_flags, AV_OPT_TYPE_دودویی,
                       پوچ, پوچ, (تهی**)&dst);
    اگر (ret < 0)
        بازگشت ret;

    اگر (dst) {
    ptr = len ? av_malloc(len) : پوچ;
    اگر (len && !ptr)
        بازگشت AVERROR(ENOMEM);

    lendst = (صحیح *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    اگر (len)
        memcpy(ptr, val, len);
    }

    بازگشت 0;
}

صحیح av_opt_set_image_size(تهی *obj, ثابت نویسه *name, صحیح w, صحیح h, صحیح جستجو_flags)
{
    ثابت AVOption *o;
    تهی *logctx;
    صحیح *dst;
    صحیح ret;

    ret = opt_set_init(obj, name, جستجو_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       پوچ, &o, (تهی**)&dst);
    اگر (ret < 0)
        بازگشت ret;

    logctx = dst ? obj : پوچ;

    اگر (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        بازگشت AVERROR(EINVAL);
    }

    اگر (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    بازگشت 0;
}

صحیح av_opt_set_video_rate(تهی *obj, ثابت نویسه *name, AVRational val, صحیح جستجو_flags)
{
    بازگشت set_عدد(obj, name, val.رقم, val.den, 1, جستجو_flags, AV_OPT_TYPE_VIDEO_RATE);
}

ایستا صحیح set_format(تهی *obj, ثابت نویسه *name, صحیح fmt, صحیح جستجو_flags,
                      شمارش AVOptionType type, ثابت نویسه *desc, صحیح nb_fmts)
{
    ثابت AVOption *o;
    تهی *logctx;
    صحیح *dst;
    صحیح min, max, ret;

    ret = opt_set_init(obj, name, جستجو_flags, type, پوچ, &o, (تهی**)&dst);
    اگر (ret < 0)
        بازگشت ret;

    logctx = dst ? obj : پوچ;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    اگر (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        بازگشت AVERROR(ERANGE);
    }
    اگر (dst)
    *dst = fmt;
    بازگشت 0;
}

صحیح av_opt_set_pixel_fmt(تهی *obj, ثابت نویسه *name, شمارش AVPixelFormat fmt, صحیح جستجو_flags)
{
    بازگشت set_format(obj, name, fmt, جستجو_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحیح av_opt_set_sample_fmt(تهی *obj, ثابت نویسه *name, شمارش AVSampleFormat fmt, صحیح جستجو_flags)
{
    بازگشت set_format(obj, name, fmt, جستجو_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحیح av_opt_set_dict_val(تهی *obj, ثابت نویسه *name, ثابت AVDictionary *val,
                        صحیح جستجو_flags)
{
    AVDictionary **dst;
    صحیح ret;

    ret = opt_set_init(obj, name, جستجو_flags, AV_OPT_TYPE_DICT, پوچ, پوچ,
                       (تهی**)&dst);
    اگر (ret < 0)
        بازگشت ret;

    اگر (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    بازگشت ret;
}

صحیح av_opt_set_chlayout(تهی *obj, ثابت نویسه *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحیح جستجو_flags)
{
    AVChannelLayout *dst;
    صحیح ret;

    ret = opt_set_init(obj, name, جستجو_flags, AV_OPT_TYPE_CHLAYOUT, پوچ, پوچ,
                       (تهی**)&dst);
    اگر (ret < 0)
        بازگشت ret;

    اگر (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    بازگشت ret;
}

ایستا تهی format_duration(نویسه *buf, size_t size, int64_t d)
{
    نویسه *e;

    av_assert0(size >= 25);
    اگر (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    اگر (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    وگرنه اگر (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    وگرنه اگر (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحیح)((d / 60000000) % 60),
                 (صحیح)((d / 1000000) % 60),
                 (صحیح)(d % 1000000));
    وگرنه اگر (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (صحیح)(d / 60000000),
                 (صحیح)((d / 1000000) % 60),
                 (صحیح)(d % 1000000));
    وگرنه
        snprintf(buf, size, "%d.%06d",
                 (صحیح)(d / 1000000),
                 (صحیح)(d % 1000000));
    e = buf + strlen(buf);
    وقتی (e > buf && e[-1] == '0')
        *(--e) = 0;
    اگر (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ایستا صحیح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت تهی *dst, صحیح جستجو_flags)
{
    صحیح ret;

    انتخاب (TYPE_BASE(o->type)) {
    حالت AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(صحیح *)dst));
        بشکن;
    حالت AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(صحیح *)dst);
        بشکن;
    حالت AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(صحیح *)dst);
        بشکن;
    حالت AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        بشکن;
    حالت AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        بشکن;
    حالت AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        بشکن;
    حالت AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(اعشاری *)dst);
        بشکن;
    حالت AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(دوگانه *)dst);
        بشکن;
    حالت AV_OPT_TYPE_VIDEO_RATE:
    حالت AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->رقم, ((AVRational *)dst)->den);
        بشکن;
    حالت AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        بشکن;
    حالت AV_OPT_TYPE_STRING:
        اگر (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } وگرنه اگر (جستجو_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = پوچ;
            بازگشت 0;
        } وگرنه {
            *pbuf = av_strdup("");
        }
        بازگشت *pbuf ? 0 : AVERROR(ENOMEM);
    حالت AV_OPT_TYPE_دودویی: {
        ثابت uint8_t *bin;
        صحیح len;

        اگر (!*(uint8_t **)dst && (جستجو_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = پوچ;
            بازگشت 0;
        }
        len = *(صحیح *)(((uint8_t *)dst) + اندازه(uint8_t *));
        اگر ((uint64_t)len * 2 + 1 > INT_MAX)
            بازگشت AVERROR(EINVAL);
        اگر (!(*pbuf = av_malloc(len * 2 + 1)))
            بازگشت AVERROR(ENOMEM);
        اگر (!len) {
            *pbuf[0] = '\0';
            بازگشت 0;
        }
        bin = *(uint8_t **)dst;
        برای (صحیح i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        بازگشت 0;
    }
    حالت AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((صحیح *)dst)[0], ((صحیح *)dst)[1]);
        بشکن;
    حالت AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (نویسه *)av_x_if_null(av_get_pix_fmt_name(*(شمارش AVPixelFormat *)dst), "none"));
        بشکن;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (نویسه *)av_x_if_null(av_get_sample_fmt_name(*(شمارش AVSampleFormat *)dst), "none"));
        بشکن;
    حالت AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        بشکن;
    }
    حالت AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (صحیح)((uint8_t *)dst)[0], (صحیح)((uint8_t *)dst)[1],
                       (صحیح)((uint8_t *)dst)[2], (صحیح)((uint8_t *)dst)[3]);
        بشکن;
    حالت AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        بشکن;
    حالت AV_OPT_TYPE_DICT:
        اگر (!*(AVDictionary **)dst && (جستجو_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = پوچ;
            بازگشت 0;
        }
        بازگشت av_dict_get_string(*(AVDictionary **)dst, (نویسه **)pbuf, '=', ':');
    پیشفرض:
        بازگشت AVERROR(EINVAL);
    }

    بازگشت ret;
}

ایستا صحیح opt_get_array(ثابت AVOption *o, تهی *dst, uint8_t **out_val)
{
    ثابت unsigned شمار = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = پوچ;
    size_t   str_len = 0;
    صحیح ret;

    *out_val = پوچ;

    برای (unsigned i = 0; i < شمار; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, اندازه(buf),
                           opt_array_pelem(o, *(تهی **)dst, i), 0);
        اگر (ret < 0)
            برو fail;

        out_len = strlen(out);
        اگر (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            برو fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        اگر (ret < 0)
            برو fail;

        // add separator if needed
        اگر (i)
            str[str_len++] = sep;

        // escape the element
        برای (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            اگر (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        اگر (out != buf)
            av_freep(&out);
        اگر (ret < 0) {
            av_freep(&str);
            بازگشت ret;
        }
    }

    *out_val = str;

    بازگشت 0;
}

صحیح av_opt_get(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, uint8_t **out_val)
{
    تهی *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    uint8_t *out, buf[128];
    صحیح ret;

    اگر (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        بازگشت AVERROR_OPTION_NOT_FOUND;

    اگر (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        اگر (ret < 0)
            بازگشت ret;
        اگر (!*out_val && !(جستجو_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            اگر (!*out_val)
               بازگشت AVERROR(ENOMEM);
        }
        بازگشت 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, اندازه(buf), dst, جستجو_flags);
    اگر (ret < 0)
        بازگشت ret;
    اگر (out != buf) {
        *out_val = out;
        بازگشت 0;
    }

    اگر (ret >= اندازه(buf))
        بازگشت AVERROR(EINVAL);
    *out_val = av_strdup(out);
    بازگشت *out_val ? 0 : AVERROR(ENOMEM);
}

ایستا صحیح get_عدد(تهی *obj, ثابت نویسه *name, دوگانه *رقم, صحیح *den, int64_t *intnum,
                      صحیح جستجو_flags)
{
    تهی *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        بازگشت AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    بازگشت read_عدد(o, dst, رقم, den, intnum);
}

صحیح av_opt_get_int(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    دوگانه رقم = 1;
    صحیح ret, den = 1;

    اگر ((ret = get_عدد(obj, name, &رقم, &den, &intnum, جستجو_flags)) < 0)
        بازگشت ret;
    اگر (رقم == den)
        *out_val = intnum;
    وگرنه
        *out_val = رقم * intnum / den;
    بازگشت 0;
}

صحیح av_opt_get_double(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, دوگانه *out_val)
{
    int64_t intnum = 1;
    دوگانه رقم = 1;
    صحیح ret, den = 1;

    اگر ((ret = get_عدد(obj, name, &رقم, &den, &intnum, جستجو_flags)) < 0)
        بازگشت ret;
    *out_val = رقم * intnum / den;
    بازگشت 0;
}

صحیح av_opt_get_q(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    دوگانه رقم = 1;
    صحیح ret, den = 1;

    اگر ((ret = get_عدد(obj, name, &رقم, &den, &intnum, جستجو_flags)) < 0)
        بازگشت ret;

    اگر (رقم == 1.0 && (صحیح)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    وگرنه
        *out_val = double_to_rational(رقم*intnum/den);
    بازگشت 0;
}

صحیح av_opt_get_image_size(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, صحیح *w_out, صحیح *h_out)
{
    تهی *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        بازگشت AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    اگر (w_out) *w_out = *(صحیح *)dst;
    اگر (h_out) *h_out = *((صحیح *)dst+1);
    بازگشت 0;
}

صحیح av_opt_get_video_rate(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, AVRational *out_val)
{
    بازگشت av_opt_get_q(obj, name, جستجو_flags, out_val);
}

ایستا صحیح get_format(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, تهی *out_fmt,
                      شمارش AVOptionType type, ثابت نویسه *desc)
{
    تهی *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        بازگشت AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    اگر (type == AV_OPT_TYPE_PIXEL_FMT)
        *(شمارش AVPixelFormat *)out_fmt = *(شمارش AVPixelFormat *)dst;
    وگرنه
        *(شمارش AVSampleFormat*)out_fmt = *(شمارش AVSampleFormat*)dst;

    بازگشت 0;
}

صحیح av_opt_get_pixel_fmt(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, شمارش AVPixelFormat *out_fmt)
{
    بازگشت get_format(obj, name, جستجو_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحیح av_opt_get_sample_fmt(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, شمارش AVSampleFormat *out_fmt)
{
    بازگشت get_format(obj, name, جستجو_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحیح av_opt_get_chlayout(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, AVChannelLayout *cl)
{
    تهی *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        بازگشت AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    بازگشت av_channel_layout_copy(cl, dst);
}

صحیح av_opt_get_dict_val(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags, AVDictionary **out_val)
{
    تهی *target_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);

    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (o->type != AV_OPT_TYPE_DICT)
        بازگشت AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    بازگشت av_dict_copy(out_val, src, 0);
}

صحیح av_opt_flag_is_set(تهی *obj, ثابت نویسه *field_name, ثابت نویسه *flag_name)
{
    ثابت AVOption *field = av_opt_find(obj, field_name, پوچ, 0, 0);
    ثابت AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : پوچ, 0, 0);
    int64_t res;

    اگر (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        بازگشت 0;
    بازگشت res & flag->default_val.i64;
}

ایستا تهی log_int_مقدار(تهی *av_log_obj, صحیح level, int64_t i)
{
    اگر (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } وگرنه اگر (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } وگرنه اگر (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } وگرنه اگر (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } وگرنه اگر (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } وگرنه {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ایستا تهی log_مقدار(تهی *av_log_obj, صحیح level, دوگانه d)
{
    اگر      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } وگرنه اگر (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } وگرنه اگر (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } وگرنه اگر (d == (دوگانه)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } وگرنه اگر (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } وگرنه اگر (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } وگرنه اگر (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } وگرنه اگر (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } وگرنه اگر (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } وگرنه اگر (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } وگرنه اگر (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } وگرنه اگر (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } وگرنه اگر (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } وگرنه {
        av_log(av_log_obj, level, "%g", d);
    }
}

ایستا ثابت نویسه *get_opt_const_name(تهی *obj, ثابت نویسه *unit, int64_t مقدار)
{
    ثابت AVOption *opt = پوچ;

    اگر (!unit)
        بازگشت پوچ;
    وقتی ((opt = av_opt_next(obj, opt)))
        اگر (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == مقدار)
            بازگشت opt->name;
    بازگشت پوچ;
}

ایستا نویسه *get_opt_flags_string(تهی *obj, ثابت نویسه *unit, int64_t مقدار)
{
    ثابت AVOption *opt = پوچ;
    نویسه flags[512];

    flags[0] = 0;
    اگر (!unit)
        بازگشت پوچ;
    وقتی ((opt = av_opt_next(obj, opt))) {
        اگر (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & مقدار) {
            اگر (flags[0])
                av_strlcatf(flags, اندازه(flags), "+");
            av_strlcatf(flags, اندازه(flags), "%s", opt->name);
        }
    }
    اگر (flags[0])
        بازگشت av_strdup(flags);
    بازگشت پوچ;
}

ایستا تهی log_type(تهی *av_log_obj, ثابت AVOption *o,
                     شمارش AVOptionType parent_type)
{
    ثابت شمارش AVOptionType type = TYPE_BASE(o->type);

    اگر (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    وگرنه اگر (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        وگرنه
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    وگرنه
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ایستا تهی log_default(تهی *obj, تهی *av_log_obj, ثابت AVOption *opt)
{
    اگر (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_دودویی)
        بازگشت;
    اگر ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        بازگشت;

    اگر (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت AVOptionArrayDef *arr = opt->default_val.arr;
        اگر (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        بازگشت;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    انتخاب (opt->type) {
    حالت AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        بشکن;
    حالت AV_OPT_TYPE_FLAGS: {
        نویسه *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        اگر (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } وگرنه {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        بشکن;
    }
    حالت AV_OPT_TYPE_DURATION: {
        نویسه buf[25];
        format_duration(buf, اندازه(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        بشکن;
    }
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_INT64: {
        ثابت نویسه *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        اگر (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        وگرنه
            log_int_مقدار(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        بشکن;
    }
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_FLOAT:
        log_مقدار(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        بشکن;
    حالت AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.رقم, q.den); }
        بشکن;
    حالت AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (نویسه *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        بشکن;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (نویسه *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        بشکن;
    حالت AV_OPT_TYPE_COLOR:
    حالت AV_OPT_TYPE_IMAGE_SIZE:
    حالت AV_OPT_TYPE_STRING:
    حالت AV_OPT_TYPE_DICT:
    حالت AV_OPT_TYPE_VIDEO_RATE:
    حالت AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        بشکن;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ایستا تهی opt_list(تهی *obj, تهی *av_log_obj, ثابت نویسه *unit,
                     صحیح req_flags, صحیح rej_flags, شمارش AVOptionType parent_type)
{
    ثابت AVOption *opt = پوچ;
    AVOptionRanges *r;
    صحیح i;

    وقتی ((opt = av_opt_next(obj, opt))) {
        اگر (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            ادامه;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        اگر (!unit && opt->type == AV_OPT_TYPE_CONST)
            ادامه;
        وگرنه اگر (unit && opt->type != AV_OPT_TYPE_CONST)
            ادامه;
        وگرنه اگر (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            ادامه;
        وگرنه اگر (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        وگرنه
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

        اگر (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        اگر (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_جستجو_FAKE_OBJ) >= 0) {
            انتخاب (opt->type) {
            حالت AV_OPT_TYPE_INT:
            حالت AV_OPT_TYPE_UINT:
            حالت AV_OPT_TYPE_INT64:
            حالت AV_OPT_TYPE_UINT64:
            حالت AV_OPT_TYPE_DOUBLE:
            حالت AV_OPT_TYPE_FLOAT:
            حالت AV_OPT_TYPE_RATIONAL:
                برای (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_مقدار(av_log_obj, AV_LOG_INFO, r->range[i]->مقدار_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_مقدار(av_log_obj, AV_LOG_INFO, r->range[i]->مقدار_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                بشکن;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        اگر (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

صحیح av_opt_show2(تهی *obj, تهی *av_log_obj, صحیح req_flags, صحیح rej_flags)
{
    اگر (!obj)
        بازگشت -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, پوچ, req_flags, rej_flags, -1);

    بازگشت 0;
}

تهی av_opt_set_defaults(تهی *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

تهی av_opt_set_defaults2(تهی *s, صحیح mask, صحیح flags)
{
    ثابت AVOption *opt = پوچ;
    وقتی ((opt = av_opt_next(s, opt))) {
        تهی *dst = ((uint8_t*)s) + opt->offset;

        اگر ((opt->flags & mask) != flags)
            ادامه;

        اگر (opt->flags & AV_OPT_FLAG_READONLY)
            ادامه;

        اگر (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ثابت AVOptionArrayDef *arr = opt->default_val.arr;
            ثابت نویسه              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            اگر (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            ادامه;
        }

        انتخاب (opt->type) {
            حالت AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                بشکن;
            حالت AV_OPT_TYPE_BOOL:
            حالت AV_OPT_TYPE_FLAGS:
            حالت AV_OPT_TYPE_INT:
            حالت AV_OPT_TYPE_UINT:
            حالت AV_OPT_TYPE_INT64:
            حالت AV_OPT_TYPE_UINT64:
            حالت AV_OPT_TYPE_DURATION:
            حالت AV_OPT_TYPE_PIXEL_FMT:
            حالت AV_OPT_TYPE_SAMPLE_FMT:
                write_عدد(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                بشکن;
            حالت AV_OPT_TYPE_DOUBLE:
            حالت AV_OPT_TYPE_FLOAT: {
                دوگانه val;
                val = opt->default_val.dbl;
                write_عدد(s, opt, dst, val, 1, 1, 1);
            }
            بشکن;
            حالت AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_عدد(s, opt, dst, 1, val.den, val.رقم, 1);
            }
            بشکن;
            حالت AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                بشکن;
            حالت AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                بشکن;
            حالت AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                بشکن;
            حالت AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                بشکن;
            حالت AV_OPT_TYPE_دودویی:
                set_string_دودویی(s, opt, opt->default_val.str, dst);
                بشکن;
            حالت AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                بشکن;
            حالت AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                بشکن;
        پیشفرض:
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
ایستا صحیح parse_کلید_مقدار_pair(تهی *ctx, ثابت نویسه **buf,
                                ثابت نویسه *کلید_val_sep, ثابت نویسه *pairs_sep)
{
    نویسه *کلید = av_get_token(buf, کلید_val_sep);
    نویسه *val;
    صحیح ret;

    اگر (!کلید)
        بازگشت AVERROR(ENOMEM);

    اگر (*کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        اگر (!val) {
            av_freep(&کلید);
            بازگشت AVERROR(ENOMEM);
        }
    } وگرنه {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", کلید);
        av_free(کلید);
        بازگشت AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", کلید, val);

    ret = av_opt_set(ctx, کلید, val, AV_OPT_جستجو_CHILDREN);
    اگر (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", کلید);

    av_free(کلید);
    av_free(val);
    بازگشت ret;
}

صحیح av_set_options_string(تهی *ctx, ثابت نویسه *opts,
                          ثابت نویسه *کلید_val_sep, ثابت نویسه *pairs_sep)
{
    صحیح ret, شمار = 0;

    اگر (!opts)
        بازگشت 0;

    وقتی (*opts) {
        اگر ((ret = parse_کلید_مقدار_pair(ctx, &opts, کلید_val_sep, pairs_sep)) < 0)
            بازگشت ret;
        شمار++;

        اگر (*opts)
            opts++;
    }

    بازگشت شمار;
}

#define WHITESPACES " \n\t\r"

ایستا صحیح is_کلید_char(نویسه c)
{
    بازگشت (unsigned)((c | 32) - 'a') < 26 ||
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
ایستا صحیح get_کلید(ثابت نویسه **ropts, ثابت نویسه *delim, نویسه **rkey)
{
    ثابت نویسه *opts = *ropts;
    ثابت نویسه *کلید_start, *کلید_end;

    کلید_start = opts += strspn(opts, WHITESPACES);
    وقتی (is_کلید_char(*opts))
        opts++;
    کلید_end = opts;
    opts += strspn(opts, WHITESPACES);
    اگر (!*opts || !strchr(delim, *opts))
        بازگشت AVERROR(EINVAL);
    opts++;
    اگر (!(*rkey = av_malloc(کلید_end - کلید_start + 1)))
        بازگشت AVERROR(ENOMEM);
    memcpy(*rkey, کلید_start, کلید_end - کلید_start);
    (*rkey)[کلید_end - کلید_start] = 0;
    *ropts = opts;
    بازگشت 0;
}

صحیح av_opt_get_کلید_مقدار(ثابت نویسه **ropts,
                         ثابت نویسه *کلید_val_sep, ثابت نویسه *pairs_sep,
                         unsigned flags,
                         نویسه **rkey, نویسه **rval)
{
    صحیح ret;
    نویسه *کلید = پوچ, *val;
    ثابت نویسه *opts = *ropts;

    اگر ((ret = get_کلید(&opts, کلید_val_sep, &کلید)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_کلید))
        بازگشت AVERROR(EINVAL);
    اگر (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(کلید);
        بازگشت AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = کلید;
    *rval  = val;
    بازگشت 0;
}

صحیح av_opt_set_from_string(تهی *ctx, ثابت نویسه *opts,
                           ثابت نویسه *ثابت *shorthand,
                           ثابت نویسه *کلید_val_sep, ثابت نویسه *pairs_sep)
{
    صحیح ret, شمار = 0;
    ثابت نویسه *dummy_shorthand = پوچ;
    ثابت نویسه *کلید;

    اگر (!opts)
        بازگشت 0;
    اگر (!shorthand)
        shorthand = &dummy_shorthand;

    وقتی (*opts) {
        نویسه *parsed_کلید, *مقدار;
        ret = av_opt_get_کلید_مقدار(&opts, کلید_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_کلید : 0,
                                   &parsed_کلید, &مقدار);
        اگر (ret < 0) {
            اگر (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            وگرنه
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            بازگشت ret;
        }
        اگر (*opts)
            opts++;
        اگر (parsed_کلید) {
            کلید = parsed_کلید;
            وقتی (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } وگرنه {
            کلید = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", کلید, مقدار);
        اگر ((ret = av_opt_set(ctx, کلید, مقدار, 0)) < 0) {
            اگر (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", کلید);
            av_free(مقدار);
            av_free(parsed_کلید);
            بازگشت ret;
        }

        av_free(مقدار);
        av_free(parsed_کلید);
        شمار++;
    }
    بازگشت شمار;
}

تهی av_opt_free(تهی *obj)
{
    ثابت AVOption *o = پوچ;
    وقتی ((o = av_opt_next(obj, o))) {
        تهی *pitem = (uint8_t *)obj + o->offset;

        اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        وگرنه
            opt_free_elem(o->type, pitem);
    }
}

صحیح av_opt_set_dict2(تهی *obj, AVDictionary **options, صحیح جستجو_flags)
{
    ثابت AVDictionaryEntry *t = پوچ;
    AVDictionary    *tmp = پوچ;
    صحیح ret;

    اگر (!options)
        بازگشت 0;

    وقتی ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->کلید, t->مقدار, جستجو_flags);
        اگر (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->کلید, t->مقدار, AV_DICT_MULTIKEY);
        اگر (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->کلید, t->مقدار);
            av_dict_free(&tmp);
            بازگشت ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    بازگشت 0;
}

صحیح av_opt_set_dict(تهی *obj, AVDictionary **options)
{
    بازگشت av_opt_set_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_find(تهی *obj, ثابت نویسه *name, ثابت نویسه *unit,
                            صحیح opt_flags, صحیح جستجو_flags)
{
    بازگشت av_opt_find2(obj, name, unit, opt_flags, جستجو_flags, پوچ);
}

ثابت AVOption *av_opt_find2(تهی *obj, ثابت نویسه *name, ثابت نویسه *unit,
                             صحیح opt_flags, صحیح جستجو_flags, تهی **target_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = پوچ;

    اگر(!obj)
        بازگشت پوچ;

    c= *(AVClass**)obj;

    اگر (!c)
        بازگشت پوچ;

    اگر (جستجو_flags & AV_OPT_جستجو_CHILDREN) {
        اگر (جستجو_flags & AV_OPT_جستجو_FAKE_OBJ) {
            تهی *iter = پوچ;
            ثابت AVClass *child;
            وقتی (child = av_opt_child_class_iterate(c, &iter))
                اگر (o = av_opt_find2(&child, name, unit, opt_flags, جستجو_flags, پوچ))
                    بازگشت o;
        } وگرنه {
            تهی *child = پوچ;
            وقتی (child = av_opt_child_next(obj, child))
                اگر (o = av_opt_find2(child, name, unit, opt_flags, جستجو_flags, target_obj))
                    بازگشت o;
        }
    }

    وقتی (o = av_opt_next(obj, o)) {
        اگر (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            اگر (target_obj) {
                اگر (!(جستجو_flags & AV_OPT_جستجو_FAKE_OBJ))
                    *target_obj = obj;
                وگرنه
                    *target_obj = پوچ;
            }
            بازگشت o;
        }
    }
    بازگشت پوچ;
}

تهی *av_opt_child_next(تهی *obj, تهی *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    اگر (c->child_next)
        بازگشت c->child_next(obj, prev);
    بازگشت پوچ;
}

ثابت AVClass *av_opt_child_class_iterate(ثابت AVClass *parent, تهی **iter)
{
    اگر (parent->child_class_iterate)
        بازگشت parent->child_class_iterate(iter);
    بازگشت پوچ;
}

ایستا صحیح opt_copy_elem(تهی *logctx, شمارش AVOptionType type,
                         تهی *dst, ثابت تهی *src)
{
    اگر (type == AV_OPT_TYPE_STRING) {
        ثابت نویسه *src_str = *(ثابت نویسه *ثابت *)src;
        نویسه         **dstp =  (نویسه **)dst;
        اگر (*dstp != src_str)
            av_freep(dstp);
        اگر (src_str) {
            *dstp = av_strdup(src_str);
            اگر (!*dstp)
                بازگشت AVERROR(ENOMEM);
        }
    } وگرنه اگر (type == AV_OPT_TYPE_دودویی) {
        ثابت uint8_t *ثابت *src8 = (ثابت uint8_t *ثابت *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        صحیح len = *(ثابت صحیح *)(src8 + 1);
        اگر (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        اگر (len && !*dst8) {
            *(صحیح *)(dst8 + 1) = 0;
            بازگشت AVERROR(ENOMEM);
        }
        *(صحیح *)(dst8 + 1) = len;
    } وگرنه اگر (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } وگرنه اگر (type == AV_OPT_TYPE_DICT) {
        ثابت AVDictionary *sdict = *(ثابت AVDictionary * ثابت *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        اگر (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = پوچ;
        بازگشت av_dict_copy(ddictp, sdict, 0);
    } وگرنه اگر (type == AV_OPT_TYPE_CHLAYOUT) {
        ثابت AVChannelLayout *slayout = (ثابت AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        اگر (dlayout != slayout) {
            اگر (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = پوچ;
            بازگشت av_channel_layout_copy(dst, src);
        }
    } وگرنه اگر (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } وگرنه {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        بازگشت AVERROR(EINVAL);
    }

    بازگشت 0;
}

ایستا صحیح opt_copy_array(تهی *logctx, ثابت AVOption *o,
                          تهی **pdst, ثابت تهی * ثابت *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    تهی         *dst = پوچ;
    صحیح ret;

    اگر (*pdst == *psrc) {
        *pdst                   = پوچ;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    اگر (!dst)
        بازگشت AVERROR(ENOMEM);

    برای (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(تهی**)psrc, i));
        اگر (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            بازگشت ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    بازگشت 0;
}

صحیح av_opt_copy(تهی *dst, ثابت تهی *src)
{
    ثابت AVOption *o = پوچ;
    ثابت AVClass *c;
    صحیح ret = 0;

    اگر (!src)
        بازگشت AVERROR(EINVAL);

    c = *(AVClass **)src;
    اگر (!c || c != *(AVClass **)dst)
        بازگشت AVERROR(EINVAL);

    وقتی ((o = av_opt_next(src, o))) {
        تهی *field_dst = (uint8_t *)dst + o->offset;
        تهی *field_src = (uint8_t *)src + o->offset;

        صحیح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        اگر (err < 0)
            ret = err;
    }
    بازگشت ret;
}

صحیح av_opt_get_array_size(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags,
                          unsigned صحیح *out_val)
{
    تهی *target_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        بازگشت AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    بازگشت 0;
}

صحیح av_opt_get_array(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags,
                     unsigned صحیح start_elem, unsigned صحیح nb_elems,
                     شمارش AVOptionType out_type, تهی *out_val)
{
    ثابت size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ثابت AVOption *o;
    تهی *target_obj;

    ثابت تهی *parray;
    unsigned array_size;

    صحیح ret;

    o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target_obj);
    اگر (!o || !target_obj)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    اگر (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        بازگشت AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    اگر (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        بازگشت AVERROR(EINVAL);

    برای (unsigned i = 0; i < nb_elems; i++) {
        ثابت تهی *src = opt_array_pelem(o, *(تهی**)parray, start_elem + i);
        تهی       *dst = (uint8_t*)out_val + i * elem_size_out;

        اگر (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            اگر (ret < 0)
                برو fail;
        } وگرنه اگر (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, اندازه(buf), src, جستجو_flags);
            اگر (ret < 0)
                برو fail;

            اگر (out == buf) {
                out = av_strdup(buf);
                اگر (!out) {
                    ret = AVERROR(ENOMEM);
                    برو fail;
                }
            }

            *(uint8_t**)dst = out;
        } وگرنه اگر (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            دوگانه     رقم = 1.0;
            صحیح        den = 1;
            int64_t intnum = 1;

            ret = read_عدد(o, src, &رقم, &den, &intnum);
            اگر (ret < 0)
                برو fail;

            انتخاب (out_type) {
            حالت AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (رقم == den) ?  intnum : رقم * intnum / den;
                بشکن;
            حالت AV_OPT_TYPE_DOUBLE:
                *(دوگانه*)dst = رقم * intnum / den;
                بشکن;
            حالت AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (رقم == 1.0 && (صحیح)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(رقم * intnum / den);
                بشکن;
            پیشفرض: av_assert0(0);
            }
        } وگرنه
            بازگشت AVERROR(ENOSYS);
    }

    بازگشت 0;
fail:
    برای (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    بازگشت ret;
}

صحیح av_opt_set_array(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags,
                     unsigned صحیح start_elem, unsigned صحیح nb_elems,
                     شمارش AVOptionType val_type, ثابت تهی *val)
{
    ثابت size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    ثابت AVOption *o;
    ثابت AVOptionArrayDef *arr;
    تهی *target_obj;

    تهی *parray;
    تهی *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    صحیح ret = 0;

    ret = opt_set_init(obj, name, جستجو_flags, 0, &target_obj, &o, &parray);
    اگر (ret < 0)
        بازگشت ret;

    اگر (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        بازگشت AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    اگر (start_elem > *array_size)
        بازگشت AVERROR(EINVAL);

    // compute new array size
    اگر (!val) {
        اگر (*array_size - start_elem < nb_elems)
            بازگشت AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } وگرنه اگر (جستجو_flags & AV_OPT_ARRAY_REPLACE) {
        اگر (start_elem >= UINT_MAX - nb_elems)
            بازگشت AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } وگرنه {
        اگر (nb_elems >= UINT_MAX - *array_size)
            بازگشت AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    اگر (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        بازگشت AVERROR(EINVAL);

    // desired operation is shrinking the array
    اگر (!val) {
        تهی *array = *(تهی**)parray;

        برای (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        اگر (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            اگر (!array)
                بازگشت AVERROR(ENOMEM);

            *(تهی**)parray = array;
        } وگرنه
            av_freep(parray);

        *array_size = new_size;

        بازگشت 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    اگر (!new_elems)
        بازگشت AVERROR(ENOMEM);

    // convert/validate each new element
    برای (unsigned i = 0; i < nb_elems; i++) {
        تهی       *dst = opt_array_pelem(o, new_elems, i);
        ثابت تهی *src = (uint8_t*)val + i * elem_size_val;

        دوگانه     رقم = 1.0;
        صحیح        den = 1;
        int64_t intnum = 1;

        اگر (val_type == TYPE_BASE(o->type)) {
            صحیح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            اگر (ret < 0)
                برو fail;

            // validate the range for numeric options
            err = read_عدد(o, dst, &رقم, &den, &intnum);
            اگر (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < رقم * intnum || o->min * den > رقم * intnum)) {
                رقم = den ? رقم * intnum / den : (رقم && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, رقم, o->min, o->max);
                ret = AVERROR(ERANGE);
                برو fail;
            }
        } وگرنه اگر (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ثابت نویسه **)src, dst);
            اگر (ret < 0)
                برو fail;
        } وگرنه اگر (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            انتخاب (val_type) {
            حالت AV_OPT_TYPE_INT:       intnum = *(صحیح*)src;                بشکن;
            حالت AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            بشکن;
            حالت AV_OPT_TYPE_FLOAT:     رقم    = *(اعشاری*)src;              بشکن;
            حالت AV_OPT_TYPE_DOUBLE:    رقم    = *(دوگانه*)src;             بشکن;
            حالت AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->رقم;
                                        den    = ((AVRational*)src)->den;   بشکن;
            پیشفرض: av_assert0(0);
            }

            ret = write_عدد(obj, o, dst, رقم, den, intnum, 0);
            اگر (ret < 0)
                برو fail;
        } وگرنه {
            ret = AVERROR(ENOSYS);
            برو fail;
        }
    }

    // commit new elements to the array
    اگر (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(تهی**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = پوچ;
        nb_elems  = 0;
    } وگرنه {
        تهی *array = av_realloc_array(*(تهی**)parray, new_size, elem_size);
        اگر (!array) {
            ret = AVERROR(ENOMEM);
            برو fail;
        }

        اگر (جستجو_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            برای (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } وگرنه {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(تهی**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    بازگشت ret;
}

صحیح av_opt_query_ranges(AVOptionRanges **ranges_arg, تهی *obj, ثابت نویسه *کلید, صحیح flags)
{
    صحیح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحیح (*callback)(AVOptionRanges **, تهی *obj, ثابت نویسه *کلید, صحیح flags) = c->query_ranges;

    اگر (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, کلید, flags);
    اگر (ret >= 0) {
        اگر (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    بازگشت ret;
}

صحیح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, تهی *obj, ثابت نویسه *کلید, صحیح flags)
{
    AVOptionRanges *ranges = av_mallocz(اندازه(*ranges));
    AVOptionRange **range_array = av_mallocz(اندازه(تهی*));
    AVOptionRange *range = av_mallocz(اندازه(*range));
    ثابت AVOption *field = av_opt_find(obj, کلید, پوچ, 0, flags);
    صحیح ret;

    *ranges_arg = پوچ;

    اگر (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->مقدار_min = field->min;
    range->مقدار_max = field->max;

    انتخاب (field->type) {
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_PIXEL_FMT:
    حالت AV_OPT_TYPE_SAMPLE_FMT:
    حالت AV_OPT_TYPE_FLOAT:
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_COLOR:
        بشکن;
    حالت AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->مقدار_min = -1;
        range->مقدار_max = INT_MAX;
        بشکن;
    حالت AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        بشکن;
    حالت AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->مقدار_min = 0;
        range->مقدار_max = INT_MAX/8;
        بشکن;
    حالت AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->مقدار_min = 1;
        range->مقدار_max = INT_MAX;
        بشکن;
    پیشفرض:
        ret = AVERROR(ENOSYS);
        برو fail;
    }

    *ranges_arg = ranges;
    بازگشت 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    بازگشت ret;
}

تهی av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    صحیح i;
    AVOptionRanges *ranges = *rangesp;

    اگر (!ranges)
        بازگشت;

    برای (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        اگر (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

صحیح av_opt_is_set_to_default(تهی *obj, ثابت AVOption *o)
{
    int64_t i64;
    دوگانه d;
    AVRational q;
    صحیح ret, w, h;
    نویسه *str;
    تهی *dst;

    اگر (!o || !obj)
        بازگشت AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت نویسه *def = o->default_val.arr ? o->default_val.arr->def : پوچ;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        اگر (ret < 0)
            بازگشت ret;

        اگر (!!val != !!def)
            ret = 0;
        وگرنه اگر (val)
            ret = !strcmp(val, def);
        وگرنه
            ret = 1;

        av_freep(&val);

        بازگشت ret;
    }

    انتخاب (o->type) {
    حالت AV_OPT_TYPE_CONST:
        بازگشت 1;
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_PIXEL_FMT:
    حالت AV_OPT_TYPE_SAMPLE_FMT:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
        read_عدد(o, dst, پوچ, پوچ, &i64);
        بازگشت o->default_val.i64 == i64;
    حالت AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        اگر (o->default_val.str) {
            اگر ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                بازگشت ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        بازگشت ret;
    }
    حالت AV_OPT_TYPE_STRING:
        str = *(نویسه **)dst;
        اگر (str == o->default_val.str) //2 NULLs
            بازگشت 1;
        اگر (!str || !o->default_val.str) //1 NULL
            بازگشت 0;
        بازگشت !strcmp(str, o->default_val.str);
    حالت AV_OPT_TYPE_DOUBLE:
        d = *(دوگانه *)dst;
        بازگشت o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالت AV_OPT_TYPE_FLOAT:
        d = *(اعشاری *)dst;
        بازگشت (اعشاری)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالت AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        بازگشت !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالت AV_OPT_TYPE_دودویی: {
        ساختار {
            uint8_t *data;
            صحیح size;
        } tmp = {0};
        صحیح opt_size = *(صحیح *)((تهی **)dst + 1);
        تهی *opt_ptr = *(تهی **)dst;
        اگر (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            بازگشت 1;
        اگر (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            بازگشت 0;
        اگر (opt_size != strlen(o->default_val.str) / 2)
            بازگشت 0;
        ret = set_string_دودویی(پوچ, پوچ, o->default_val.str, &tmp.data);
        اگر (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        بازگشت ret;
    }
    حالت AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = پوچ;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionaryEntry *en1 = پوچ;
        ثابت AVDictionaryEntry *en2 = پوچ;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        اگر (ret < 0) {
            av_dict_free(&dict1);
            بازگشت ret;
        }
        انجامبده {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } وقتی (en1 && en2 && !strcmp(en1->کلید, en2->کلید) && !strcmp(en1->مقدار, en2->مقدار));
        av_dict_free(&dict1);
        بازگشت (!en1 && !en2);
    }
    حالت AV_OPT_TYPE_IMAGE_SIZE:
        اگر (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        وگرنه اگر ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            بازگشت ret;
        بازگشت (w == *(صحیح *)dst) && (h == *((صحیح *)dst+1));
    حالت AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        اگر (o->default_val.str) {
            اگر ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                بازگشت ret;
        }
        بازگشت !av_cmp_q(*(AVRational*)dst, q);
    حالت AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        اگر (o->default_val.str) {
            اگر ((ret = av_parse_color(color, o->default_val.str, -1, پوچ)) < 0)
                بازگشت ret;
        }
        بازگشت !memcmp(color, dst, اندازه(color));
    }
    پیشفرض:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        بشکن;
    }
    بازگشت AVERROR_PATCHWELCOME;
}

صحیح av_opt_is_set_to_default_by_name(تهی *obj, ثابت نویسه *name, صحیح جستجو_flags)
{
    ثابت AVOption *o;
    تهی *target;
    اگر (!obj)
        بازگشت AVERROR(EINVAL);
    o = av_opt_find2(obj, name, پوچ, 0, جستجو_flags, &target);
    اگر (!o)
        بازگشت AVERROR_OPTION_NOT_FOUND;
    بازگشت av_opt_is_set_to_default(target, o);
}

ایستا صحیح opt_serialize(تهی *obj, صحیح opt_flags, صحیح flags, صحیح *cnt,
                         AVBPrint *bprint, ثابت نویسه کلید_val_sep, ثابت نویسه pairs_sep)
{
    ثابت AVOption *o = پوچ;
    تهی *child = پوچ;
    uint8_t *buf;
    صحیح ret;
    ثابت نویسه special_chars[] = {pairs_sep, کلید_val_sep, '\0'};

    اگر (flags & AV_OPT_SERIALIZE_جستجو_CHILDREN)
        وقتی (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                کلید_val_sep, pairs_sep);
            اگر (ret < 0)
                بازگشت ret;
        }

    وقتی (o = av_opt_next(obj, o)) {
        اگر (o->type == AV_OPT_TYPE_CONST)
            ادامه;
        اگر ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            اگر ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                اگر (o->flags == opt_flags)
                    ادامه;
            } وگرنه اگر ((o->flags & opt_flags) == opt_flags)
                ادامه;
        } وگرنه {
            اگر ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                ادامه;
            وگرنه اگر (((o->flags & opt_flags) != opt_flags))
                ادامه;
        }
        اگر (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            ادامه;
        اگر ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, پوچ);
            بازگشت ret;
        }
        اگر (buf) {
            اگر ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &کلید_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    بازگشت 0;
}

صحیح av_opt_serialize(تهی *obj, صحیح opt_flags, صحیح flags, نویسه **buffer,
                     ثابت نویسه کلید_val_sep, ثابت نویسه pairs_sep)
{
    AVBPrint bprint;
    صحیح ret, cnt = 0;

    اگر (pairs_sep == '\0' || کلید_val_sep == '\0' || pairs_sep == کلید_val_sep ||
        pairs_sep == '\\' || کلید_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        بازگشت AVERROR(EINVAL);
    }

    اگر (!obj || !buffer)
        بازگشت AVERROR(EINVAL);

    *buffer = پوچ;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        کلید_val_sep, pairs_sep);
    اگر (ret < 0)
        بازگشت ret;

    ret = av_bprint_finalize(&bprint, buffer);
    اگر (ret < 0)
        بازگشت ret;
    بازگشت 0;
}
