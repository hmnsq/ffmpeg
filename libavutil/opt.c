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
    ܐܢ (!obj)
        ܦܢܐ عدم;
    class = *(ثابت AVClass**)obj;
    ܐܢ (!last && class && class->option && class->option[0].name)
        ܦܢܐ class->option;
    ܐܢ (last && last[1].name)
        ܦܢܐ ++last;
    ܦܢܐ عدم;
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
    [AV_OPT_TYPE_BINARY]        = { حجم(uint8_t *),      "<binary>" },
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
        ܦܢܐ 1;
    }
    ܦܢܐ 0;
}

ساكن uint8_t opt_array_sep(ثابت AVOption *o)
{
    ثابت AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ܦܢܐ (d && d->sep) ? d->sep : ',';
}

ساكن فراغ *opt_array_pelem(ثابت AVOption *o, فراغ *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    ܦܢܐ (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

ساكن unsigned *opt_array_pcount(ثابت فراغ *parray)
{
    ܦܢܐ (unsigned *)((ثابت فراغ * ثابت *)parray + 1);
}

ساكن فراغ opt_free_elem(تعداد AVOptionType type, فراغ *ptr)
{
    بدل (TYPE_BASE(type)) {
    حالة AV_OPT_TYPE_STRING:
    حالة AV_OPT_TYPE_BINARY:
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

ساكن فراغ opt_free_array(ثابت AVOption *o, فراغ *parray, unsigned *count)
{
    لكل (unsigned i = 0; i < *count; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(فراغ **)parray, i));

    av_freep(parray);
    *count = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
ساكن صحيح opt_set_init(فراغ *obj, ثابت حرف *name, صحيح search_flags,
                        صحيح require_type,
                        فراغ **ptgt, ثابت AVOption **po, فراغ **pdst)
{
    فراغ *logctx;
    ثابت AVOption *o;
    فراغ *tgt;

    o = av_opt_find2(obj, name, عدم, 0, search_flags, &tgt);
    ܐܢ (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;

    ܐܢ (o->flags & AV_OPT_FLAG_READONLY)
        ܦܢܐ AVERROR(EINVAL);

    logctx = tgt ? obj : عدم;

    ܐܢ (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        ܦܢܐ AVERROR(EINVAL);
    }

    ܐܢ (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = عدم;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        ܐܢ (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        ܐܢ (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            ܐܢ (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        ܐܢ (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            ܦܢܐ AVERROR(EINVAL);
        }
    }

    ܐܢ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    ܐܢ (po)
        *po   = o;
    ܐܢ (ptgt)
        *ptgt = tgt;
    ܐܢ (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : عدم;

    ܦܢܐ 0;
}

ساكن AVRational double_to_rational(مزدوج d)
{
     AVRational r = av_d2q(d, 1 << 24);
     ܐܢ ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     ܦܢܐ r;
}

ساكن صحيح read_number(ثابت AVOption *o, ثابت فراغ *dst, مزدوج *num, صحيح *den, int64_t *intnum)
{
    بدل (TYPE_BASE(o->type)) {
    حالة AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned صحيح*)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(تعداد AVPixelFormat *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(تعداد AVSampleFormat *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_INT:
        *intnum = *(صحيح *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_UINT:
        *intnum = *(unsigned صحيح *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_FLOAT:
        *num = *(عائم *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_DOUBLE:
        *num = *(مزدوج *)dst;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        ܦܢܐ 0;
    حالة AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        ܦܢܐ 0;
    }
    ܦܢܐ AVERROR(EINVAL);
}

ساكن صحيح write_number(فراغ *obj, ثابت AVOption *o, فراغ *dst,
                        مزدوج num, صحيح den, int64_t intnum,
                        صحيح ignore_range)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);

    ܐܢ (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        ܦܢܐ AVERROR(ERANGE);
    }
    ܐܢ (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        مزدوج d = num*intnum/den;
        ܐܢ (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            ܦܢܐ AVERROR(ERANGE);
        }
    }

    ܐܢ (!dst)
        ܦܢܐ 0;

    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:
        *(تعداد AVPixelFormat *)dst = llrint(num / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        *(تعداد AVSampleFormat *)dst = llrint(num / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
        *(صحيح *)dst = llrint(num / den) * intnum;
        اكسر;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:{
        مزدوج d = num / den;
        ܐܢ (intnum == 1 && d == (مزدوج)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ܐܚܪܢܐ
            *(int64_t *)dst = llrint(d) * intnum;
        اكسر;}
    حالة AV_OPT_TYPE_UINT64:{
        مزدوج d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        ܐܢ (intnum == 1 && d == (مزدوج)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ܐܚܪܢܐ ܐܢ (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ܐܚܪܢܐ {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        اكسر;}
    حالة AV_OPT_TYPE_FLOAT:
        *(عائم *)dst = num * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_DOUBLE:
        *(مزدوج    *)dst = num * intnum / den;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
    حالة AV_OPT_TYPE_VIDEO_RATE:
        ܐܢ ((صحيح) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        ܐܚܪܢܐ
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        اكسر;
    افتراضي:
        ܦܢܐ AVERROR(EINVAL);
    }
    ܦܢܐ 0;
}

ساكن صحيح hexchar2int(حرف c) {
    ܐܢ (c >= '0' && c <= '9')
        ܦܢܐ c - '0';
    ܐܢ (c >= 'a' && c <= 'f')
        ܦܢܐ c - 'a' + 10;
    ܐܢ (c >= 'A' && c <= 'F')
        ܦܢܐ c - 'A' + 10;
    ܦܢܐ -1;
}

ساكن صحيح set_string_binary(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحيح *lendst;
    uint8_t *bin, *ptr;
    صحيح len;

    ܐܢ (dst) {
        lendst = (صحيح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    ܐܢ (!val || !(len = strlen(val)))
        ܦܢܐ 0;

    ܐܢ (len & 1)
        ܦܢܐ AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    ܐܢ (!ptr)
        ܦܢܐ AVERROR(ENOMEM);
    ܟܡܐ (*val) {
        صحيح a = hexchar2int(*val++);
        صحيح b = hexchar2int(*val++);
        ܐܢ (a < 0 || b < 0) {
            av_free(bin);
            ܦܢܐ AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    ܐܢ (dst) {
        *dst    = bin;
        *lendst = len;
    } ܐܚܪܢܐ {
        av_free(bin);
    }

    ܦܢܐ 0;
}

ساكن صحيح set_string(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    ܐܢ (!dst)
        ܦܢܐ 0;
    av_freep(dst);
    ܐܢ (!val)
        ܦܢܐ 0;
    *dst = av_strdup(val);
    ܦܢܐ *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ساكن صحيح set_string_number(فراغ *obj, فراغ *target_obj, ثابت AVOption *o, ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);
    صحيح ret = 0;

    ܐܢ (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        صحيح num, den;
        حرف c;
        ܐܢ (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            ܐܢ ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
                ܦܢܐ ret;
            ret = 0;
        }
    }

    لكل (;;) {
        صحيح i = 0;
        حرف buf[256];
        صحيح cmd = 0;
        مزدوج d;
        int64_t intnum = 1;

        ܐܢ (type == AV_OPT_TYPE_FLAGS) {
            ܐܢ (*val == '+' || *val == '-')
                cmd = *(val++);
            لكل (; i < حجم(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            صحيح res;
            صحيح ci = 0;
            مزدوج const_values[64];
            ثابت حرف * const_names[64];
            صحيح search_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_SEARCH_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, search_flags);
            ܐܢ (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                ܐܢ (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ܐܚܪܢܐ {
                ܐܢ (o->unit) {
                    لكل (o_named = عدم; o_named = av_opt_next(target_obj, o_named); ) {
                        ܐܢ (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            ܐܢ (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                ܦܢܐ AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_values[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_values[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_values[ci++] = o->max;
                const_names [ci  ] = "min";
                const_values[ci++] = o->min;
                const_names [ci  ] = "none";
                const_values[ci++] = 0;
                const_names [ci  ] = "all";
                const_values[ci++] = ~0;
                const_names [ci] = عدم;
                const_values[ci] = 0;

                res = av_expr_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_values, عدم, عدم, عدم, عدم, عدم, 0, obj);
                ܐܢ (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    ܦܢܐ res;
                }
            }
        }
        ܐܢ (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned صحيح*)dst;
            ܐܢ (cmd == '+')
                d = intnum | (int64_t)d;
            ܐܚܪܢܐ ܐܢ (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        ܐܢ ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            ܦܢܐ ret;
        val += i;
        ܐܢ (!i || !*val)
            ܦܢܐ 0;
    }
}

ساكن صحيح set_string_image_size(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح tmp[2];
    صحيح ret;

    ܐܢ (!val || !strcmp(val, "none")) {
        ܐܢ (dst) {
        dst[0] =
        dst[1] = 0;
        }
        ܦܢܐ 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    ܐܢ (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        ܦܢܐ ret;
    }
    ܐܢ (dst)
        memcpy(dst, tmp, حجم(tmp));
    ܦܢܐ ret;
}

ساكن صحيح set_string_video_rate(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    AVRational tmp;
    صحيح ret = av_parse_video_rate(&tmp, val);
    ܐܢ (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    ܐܢ (dst)
        *dst = tmp;
    ܦܢܐ ret;
}

ساكن صحيح set_string_color(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح ret;

    ܐܢ (!val) {
        ܦܢܐ 0;
    } ܐܚܪܢܐ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        ܐܢ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            ܦܢܐ ret;
        }
        ܐܢ (dst)
            memcpy(dst, tmp, حجم(tmp));
        ܦܢܐ ret;
    }
    ܦܢܐ 0;
}

ساكن ثابت حرف *get_bool_name(صحيح val)
{
    ܐܢ (val < 0)
        ܦܢܐ "auto";
    ܦܢܐ val ? "true" : "false";
}

ساكن صحيح set_string_bool(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح n;

    ܐܢ (!val)
        ܦܢܐ 0;

    ܐܢ (!strcmp(val, "auto")) {
        n = -1;
    } ܐܚܪܢܐ ܐܢ (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ܐܚܪܢܐ ܐܢ (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ܐܚܪܢܐ {
        حرف *end = عدم;
        n = strtol(val, &end, 10);
        ܐܢ (val + strlen(val) != end)
            اذهب fail;
    }

    ܐܢ (n < o->min || n > o->max)
        اذهب fail;

    ܐܢ (dst)
    *dst = n;
    ܦܢܐ 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    ܦܢܐ AVERROR(EINVAL);
}

ساكن صحيح set_string_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
                          صحيح fmt_nb, صحيح ((*get_fmt)(ثابت حرف *)), ثابت حرف *desc,
                          تعداد AVOptionType type)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح fmt, min, max;

    ܐܢ (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ܐܚܪܢܐ {
        fmt = get_fmt(val);
        ܐܢ (fmt == -1) {
            حرف *tail;
            fmt = strtol(val, &tail, 0);
            ܐܢ (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                ܦܢܐ AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    ܐܢ(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    ܐܢ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        ܦܢܐ AVERROR(ERANGE);
    }

    ܐܢ (dst)
    بدل (type) {
    حالة AV_OPT_TYPE_PIXEL_FMT:  *(تعداد AVPixelFormat *)dst = fmt; اكسر;
    حالة AV_OPT_TYPE_SAMPLE_FMT: *(تعداد AVSampleFormat*)dst = fmt; اكسر;
    افتراضي: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    ܦܢܐ 0;
}

ساكن صحيح get_pix_fmt(ثابت حرف *name)
{
    ܦܢܐ av_get_pix_fmt(name);
}

ساكن صحيح set_string_pixel_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    ܦܢܐ set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساكن صحيح get_sample_fmt(ثابت حرف *name)
{
    ܦܢܐ av_get_sample_fmt(name);
}

ساكن صحيح set_string_sample_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    ܦܢܐ set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساكن صحيح set_string_dict(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    AVDictionary *options = عدم;

    ܐܢ (val) {
        صحيح ret = av_dict_parse_string(&options, val, "=", ":", 0);
        ܐܢ (ret < 0) {
            av_dict_free(&options);
            ܦܢܐ ret;
        }
    }

    ܐܢ (!dst) {
        av_dict_free(&options);
        ܦܢܐ 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    ܦܢܐ 0;
}

ساكن صحيح set_string_channel_layout(فراغ *obj, ثابت AVOption *o,
                                     ثابت حرف *val, فراغ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    صحيح ret;
    ܐܢ (dst)
    av_channel_layout_uninit(channel_layout);
    ܐܚܪܢܐ
        channel_layout = &tmp;
    ܐܢ (!val)
        ܦܢܐ 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    ܐܢ (ret < 0)
        ܦܢܐ ret;
    ܐܢ (!dst)
        av_channel_layout_uninit(channel_layout);
    ܦܢܐ 0;
}

ساكن صحيح opt_set_elem(فراغ *obj, فراغ *target_obj, ثابت AVOption *o,
                        ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);
    صحيح ret;

    ܐܢ (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        ܦܢܐ AVERROR(EINVAL);

    بدل (type) {
    حالة AV_OPT_TYPE_BOOL:
        ܦܢܐ set_string_bool(obj, o, val, dst);
    حالة AV_OPT_TYPE_STRING:
        ܦܢܐ set_string(obj, o, val, dst);
    حالة AV_OPT_TYPE_BINARY:
        ܦܢܐ set_string_binary(obj, o, val, dst);
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_RATIONAL:
        ܦܢܐ set_string_number(obj, target_obj, o, val, dst);
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        ܦܢܐ set_string_image_size(obj, o, val, dst);
    حالة AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        ܐܢ (ret < 0)
            ܦܢܐ ret;
        ܦܢܐ write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    حالة AV_OPT_TYPE_PIXEL_FMT:
        ܦܢܐ set_string_pixel_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        ܦܢܐ set_string_sample_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            ܐܢ (val) {
                ܐܢ ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    ܦܢܐ ret;
                }
            }
            ܐܢ (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                ܦܢܐ AVERROR(ERANGE);
            }
            ܐܢ (dst)
            *(int64_t *)dst = usecs;
            ܦܢܐ 0;
        }
    حالة AV_OPT_TYPE_COLOR:
        ܦܢܐ set_string_color(obj, o, val, dst);
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        ܐܢ (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        ܦܢܐ ret;
    حالة AV_OPT_TYPE_DICT:
        ܦܢܐ set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    ܦܢܐ AVERROR(EINVAL);
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

    ܐܢ (val && *val) {
        str = av_malloc(strlen(val) + 1);
        ܐܢ (!str)
            ܦܢܐ AVERROR(ENOMEM);
    }

    // split and unescape the string
    ܟܡܐ (val && *val) {
        uint8_t *p = str;
        فراغ *tmp;

        ܐܢ (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        لكل (; *val; val++, p++) {
            ܐܢ (*val == '\\' && val[1])
                val++;
            ܐܚܪܢܐ ܐܢ (*val == sep) {
                val++;
                اكسر;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        ܐܢ (!tmp) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        ܐܢ (ret < 0)
            اذهب fail;
        nb_elems++;
    }
    av_freep(&str);

    ܐܢ (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    ܐܢ (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        اذهب fail;
    }

    ܐܢ (dst) {
    *((فراغ **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ܐܚܪܢܐ
        opt_free_array(o, &elems, &nb_elems);

    ܦܢܐ 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    ܦܢܐ ret;
}

صحيح av_opt_set(فراغ *obj, ثابت حرف *name, ثابت حرف *val, صحيح search_flags)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ܦܢܐ ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
صحيح av_opt_eval_ ## name(فراغ *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## _out)        \
{                                                                       \
    ܐܢ (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        ܦܢܐ AVERROR(EINVAL);                                         \
    ܦܢܐ set_string_number(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_NUMBER(flags,  AV_OPT_TYPE_FLAGS,    صحيح)
OPT_EVAL_NUMBER(صحيح,    AV_OPT_TYPE_INT,      صحيح)
OPT_EVAL_NUMBER(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_NUMBER(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_NUMBER(عائم,  AV_OPT_TYPE_FLOAT,    عائم)
OPT_EVAL_NUMBER(مزدوج, AV_OPT_TYPE_DOUBLE,   مزدوج)
OPT_EVAL_NUMBER(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ساكن صحيح set_number(فراغ *obj, ثابت حرف *name, مزدوج num, صحيح den, int64_t intnum,
                      صحيح search_flags, صحيح require_type)
{
    فراغ *dst;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, require_type, عدم, &o, &dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;
    ܐܢ (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    ܦܢܐ ret;
}

صحيح av_opt_set_int(فراغ *obj, ثابت حرف *name, int64_t val, صحيح search_flags)
{
    ܦܢܐ set_number(obj, name, 1, 1, val, search_flags, 0);
}

صحيح av_opt_set_double(فراغ *obj, ثابت حرف *name, مزدوج val, صحيح search_flags)
{
    ܦܢܐ set_number(obj, name, val, 1, 1, search_flags, 0);
}

صحيح av_opt_set_q(فراغ *obj, ثابت حرف *name, AVRational val, صحيح search_flags)
{
    ܦܢܐ set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

صحيح av_opt_set_bin(فراغ *obj, ثابت حرف *name, ثابت uint8_t *val, صحيح len, صحيح search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحيح *lendst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       عدم, عدم, (فراغ**)&dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ܐܢ (dst) {
    ptr = len ? av_malloc(len) : عدم;
    ܐܢ (len && !ptr)
        ܦܢܐ AVERROR(ENOMEM);

    lendst = (صحيح *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    ܐܢ (len)
        memcpy(ptr, val, len);
    }

    ܦܢܐ 0;
}

صحيح av_opt_set_image_size(فراغ *obj, ثابت حرف *name, صحيح w, صحيح h, صحيح search_flags)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       عدم, &o, (فراغ**)&dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    logctx = dst ? obj : عدم;

    ܐܢ (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        ܦܢܐ AVERROR(EINVAL);
    }

    ܐܢ (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    ܦܢܐ 0;
}

صحيح av_opt_set_video_rate(فراغ *obj, ثابت حرف *name, AVRational val, صحيح search_flags)
{
    ܦܢܐ set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

ساكن صحيح set_format(فراغ *obj, ثابت حرف *name, صحيح fmt, صحيح search_flags,
                      تعداد AVOptionType type, ثابت حرف *desc, صحيح nb_fmts)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, عدم, &o, (فراغ**)&dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    logctx = dst ? obj : عدم;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    ܐܢ (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        ܦܢܐ AVERROR(ERANGE);
    }
    ܐܢ (dst)
    *dst = fmt;
    ܦܢܐ 0;
}

صحيح av_opt_set_pixel_fmt(فراغ *obj, ثابت حرف *name, تعداد AVPixelFormat fmt, صحيح search_flags)
{
    ܦܢܐ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحيح av_opt_set_sample_fmt(فراغ *obj, ثابت حرف *name, تعداد AVSampleFormat fmt, صحيح search_flags)
{
    ܦܢܐ set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحيح av_opt_set_dict_val(فراغ *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحيح search_flags)
{
    AVDictionary **dst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, عدم, عدم,
                       (فراغ**)&dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ܐܢ (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    ܦܢܐ ret;
}

صحيح av_opt_set_chlayout(فراغ *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحيح search_flags)
{
    AVChannelLayout *dst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, عدم, عدم,
                       (فراغ**)&dst);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ܐܢ (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    ܦܢܐ ret;
}

ساكن فراغ format_duration(حرف *buf, size_t size, int64_t d)
{
    حرف *e;

    av_assert0(size >= 25);
    ܐܢ (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    ܐܢ (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    ܐܚܪܢܐ ܐܢ (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    ܐܚܪܢܐ ܐܢ (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحيح)((d / 60000000) % 60),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    ܐܚܪܢܐ ܐܢ (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (صحيح)(d / 60000000),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    ܐܚܪܢܐ
        snprintf(buf, size, "%d.%06d",
                 (صحيح)(d / 1000000),
                 (صحيح)(d % 1000000));
    e = buf + strlen(buf);
    ܟܡܐ (e > buf && e[-1] == '0')
        *(--e) = 0;
    ܐܢ (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ساكن صحيح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت فراغ *dst, صحيح search_flags)
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
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->num, ((AVRational *)dst)->den);
        اكسر;
    حالة AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        اكسر;
    حالة AV_OPT_TYPE_STRING:
        ܐܢ (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ܐܚܪܢܐ ܐܢ (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = عدم;
            ܦܢܐ 0;
        } ܐܚܪܢܐ {
            *pbuf = av_strdup("");
        }
        ܦܢܐ *pbuf ? 0 : AVERROR(ENOMEM);
    حالة AV_OPT_TYPE_BINARY: {
        ثابت uint8_t *bin;
        صحيح len;

        ܐܢ (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            ܦܢܐ 0;
        }
        len = *(صحيح *)(((uint8_t *)dst) + حجم(uint8_t *));
        ܐܢ ((uint64_t)len * 2 + 1 > INT_MAX)
            ܦܢܐ AVERROR(EINVAL);
        ܐܢ (!(*pbuf = av_malloc(len * 2 + 1)))
            ܦܢܐ AVERROR(ENOMEM);
        ܐܢ (!len) {
            *pbuf[0] = '\0';
            ܦܢܐ 0;
        }
        bin = *(uint8_t **)dst;
        لكل (صحيح i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        ܦܢܐ 0;
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
        ܐܢ (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            ܦܢܐ 0;
        }
        ܦܢܐ av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    افتراضي:
        ܦܢܐ AVERROR(EINVAL);
    }

    ܦܢܐ ret;
}

ساكن صحيح opt_get_array(ثابت AVOption *o, فراغ *dst, uint8_t **out_val)
{
    ثابت unsigned count = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = عدم;
    size_t   str_len = 0;
    صحيح ret;

    *out_val = عدم;

    لكل (unsigned i = 0; i < count; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, حجم(buf),
                           opt_array_pelem(o, *(فراغ **)dst, i), 0);
        ܐܢ (ret < 0)
            اذهب fail;

        out_len = strlen(out);
        ܐܢ (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            اذهب fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        ܐܢ (ret < 0)
            اذهب fail;

        // add separator if needed
        ܐܢ (i)
            str[str_len++] = sep;

        // escape the element
        لكل (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            ܐܢ (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        ܐܢ (out != buf)
            av_freep(&out);
        ܐܢ (ret < 0) {
            av_freep(&str);
            ܦܢܐ ret;
        }
    }

    *out_val = str;

    ܦܢܐ 0;
}

صحيح av_opt_get(فراغ *obj, ثابت حرف *name, صحيح search_flags, uint8_t **out_val)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    صحيح ret;

    ܐܢ (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;

    ܐܢ (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    ܐܢ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        ܐܢ (ret < 0)
            ܦܢܐ ret;
        ܐܢ (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            ܐܢ (!*out_val)
               ܦܢܐ AVERROR(ENOMEM);
        }
        ܦܢܐ 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, حجم(buf), dst, search_flags);
    ܐܢ (ret < 0)
        ܦܢܐ ret;
    ܐܢ (out != buf) {
        *out_val = out;
        ܦܢܐ 0;
    }

    ܐܢ (ret >= حجم(buf))
        ܦܢܐ AVERROR(EINVAL);
    *out_val = av_strdup(out);
    ܦܢܐ *out_val ? 0 : AVERROR(ENOMEM);
}

ساكن صحيح get_number(فراغ *obj, ثابت حرف *name, مزدوج *num, صحيح *den, int64_t *intnum,
                      صحيح search_flags)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        ܦܢܐ AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    ܦܢܐ read_number(o, dst, num, den, intnum);
}

صحيح av_opt_get_int(فراغ *obj, ثابت حرف *name, صحيح search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    مزدوج num = 1;
    صحيح ret, den = 1;

    ܐܢ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ܦܢܐ ret;
    ܐܢ (num == den)
        *out_val = intnum;
    ܐܚܪܢܐ
        *out_val = num * intnum / den;
    ܦܢܐ 0;
}

صحيح av_opt_get_double(فراغ *obj, ثابت حرف *name, صحيح search_flags, مزدوج *out_val)
{
    int64_t intnum = 1;
    مزدوج num = 1;
    صحيح ret, den = 1;

    ܐܢ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ܦܢܐ ret;
    *out_val = num * intnum / den;
    ܦܢܐ 0;
}

صحيح av_opt_get_q(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    مزدوج num = 1;
    صحيح ret, den = 1;

    ܐܢ ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        ܦܢܐ ret;

    ܐܢ (num == 1.0 && (صحيح)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    ܐܚܪܢܐ
        *out_val = double_to_rational(num*intnum/den);
    ܦܢܐ 0;
}

صحيح av_opt_get_image_size(فراغ *obj, ثابت حرف *name, صحيح search_flags, صحيح *w_out, صحيح *h_out)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        ܦܢܐ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ܐܢ (w_out) *w_out = *(صحيح *)dst;
    ܐܢ (h_out) *h_out = *((صحيح *)dst+1);
    ܦܢܐ 0;
}

صحيح av_opt_get_video_rate(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVRational *out_val)
{
    ܦܢܐ av_opt_get_q(obj, name, search_flags, out_val);
}

ساكن صحيح get_format(فراغ *obj, ثابت حرف *name, صحيح search_flags, فراغ *out_fmt,
                      تعداد AVOptionType type, ثابت حرف *desc)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        ܦܢܐ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ܐܢ (type == AV_OPT_TYPE_PIXEL_FMT)
        *(تعداد AVPixelFormat *)out_fmt = *(تعداد AVPixelFormat *)dst;
    ܐܚܪܢܐ
        *(تعداد AVSampleFormat*)out_fmt = *(تعداد AVSampleFormat*)dst;

    ܦܢܐ 0;
}

صحيح av_opt_get_pixel_fmt(فراغ *obj, ثابت حرف *name, صحيح search_flags, تعداد AVPixelFormat *out_fmt)
{
    ܦܢܐ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحيح av_opt_get_sample_fmt(فراغ *obj, ثابت حرف *name, صحيح search_flags, تعداد AVSampleFormat *out_fmt)
{
    ܦܢܐ get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحيح av_opt_get_chlayout(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVChannelLayout *cl)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        ܦܢܐ AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    ܦܢܐ av_channel_layout_copy(cl, dst);
}

صحيح av_opt_get_dict_val(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVDictionary **out_val)
{
    فراغ *target_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);

    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (o->type != AV_OPT_TYPE_DICT)
        ܦܢܐ AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    ܦܢܐ av_dict_copy(out_val, src, 0);
}

صحيح av_opt_flag_is_set(فراغ *obj, ثابت حرف *field_name, ثابت حرف *flag_name)
{
    ثابت AVOption *field = av_opt_find(obj, field_name, عدم, 0, 0);
    ثابت AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : عدم, 0, 0);
    int64_t res;

    ܐܢ (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        ܦܢܐ 0;
    ܦܢܐ res & flag->default_val.i64;
}

ساكن فراغ log_int_value(فراغ *av_log_obj, صحيح level, int64_t i)
{
    ܐܢ (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ܐܚܪܢܐ ܐܢ (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ܐܚܪܢܐ ܐܢ (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ܐܚܪܢܐ ܐܢ (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ܐܚܪܢܐ ܐܢ (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ܐܚܪܢܐ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ساكن فراغ log_value(فراغ *av_log_obj, صحيح level, مزدوج d)
{
    ܐܢ      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } ܐܚܪܢܐ ܐܢ (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ܐܚܪܢܐ ܐܢ (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ܐܚܪܢܐ ܐܢ (d == (مزدوج)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ܐܚܪܢܐ ܐܢ (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ܐܚܪܢܐ ܐܢ (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ܐܚܪܢܐ ܐܢ (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ܐܚܪܢܐ ܐܢ (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ܐܚܪܢܐ ܐܢ (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ܐܚܪܢܐ ܐܢ (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ܐܚܪܢܐ ܐܢ (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ܐܚܪܢܐ ܐܢ (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ܐܚܪܢܐ ܐܢ (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ܐܚܪܢܐ {
        av_log(av_log_obj, level, "%g", d);
    }
}

ساكن ثابت حرف *get_opt_const_name(فراغ *obj, ثابت حرف *unit, int64_t value)
{
    ثابت AVOption *opt = عدم;

    ܐܢ (!unit)
        ܦܢܐ عدم;
    ܟܡܐ ((opt = av_opt_next(obj, opt)))
        ܐܢ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            ܦܢܐ opt->name;
    ܦܢܐ عدم;
}

ساكن حرف *get_opt_flags_string(فراغ *obj, ثابت حرف *unit, int64_t value)
{
    ثابت AVOption *opt = عدم;
    حرف flags[512];

    flags[0] = 0;
    ܐܢ (!unit)
        ܦܢܐ عدم;
    ܟܡܐ ((opt = av_opt_next(obj, opt))) {
        ܐܢ (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            ܐܢ (flags[0])
                av_strlcatf(flags, حجم(flags), "+");
            av_strlcatf(flags, حجم(flags), "%s", opt->name);
        }
    }
    ܐܢ (flags[0])
        ܦܢܐ av_strdup(flags);
    ܦܢܐ عدم;
}

ساكن فراغ log_type(فراغ *av_log_obj, ثابت AVOption *o,
                     تعداد AVOptionType parent_type)
{
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);

    ܐܢ (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ܐܚܪܢܐ ܐܢ (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        ܐܢ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ܐܚܪܢܐ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ܐܚܪܢܐ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ساكن فراغ log_default(فراغ *obj, فراغ *av_log_obj, ثابت AVOption *opt)
{
    ܐܢ (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        ܦܢܐ;
    ܐܢ ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        ܦܢܐ;

    ܐܢ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت AVOptionArrayDef *arr = opt->default_val.arr;
        ܐܢ (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        ܦܢܐ;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    بدل (opt->type) {
    حالة AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        اكسر;
    حالة AV_OPT_TYPE_FLAGS: {
        حرف *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        ܐܢ (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ܐܚܪܢܐ {
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
        ܐܢ (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ܐܚܪܢܐ
            log_int_value(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        اكسر;
    }
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_FLOAT:
        log_value(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.num, q.den); }
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

    ܟܡܐ ((opt = av_opt_next(obj, opt))) {
        ܐܢ (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            استمر;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        ܐܢ (!unit && opt->type == AV_OPT_TYPE_CONST)
            استمر;
        ܐܚܪܢܐ ܐܢ (unit && opt->type != AV_OPT_TYPE_CONST)
            استمر;
        ܐܚܪܢܐ ܐܢ (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            استمر;
        ܐܚܪܢܐ ܐܢ (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ܐܚܪܢܐ
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

        ܐܢ (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        ܐܢ (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
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
                    log_value(av_log_obj, AV_LOG_INFO, r->range[i]->value_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_value(av_log_obj, AV_LOG_INFO, r->range[i]->value_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                اكسر;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        ܐܢ (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

صحيح av_opt_show2(فراغ *obj, فراغ *av_log_obj, صحيح req_flags, صحيح rej_flags)
{
    ܐܢ (!obj)
        ܦܢܐ -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, عدم, req_flags, rej_flags, -1);

    ܦܢܐ 0;
}

فراغ av_opt_set_defaults(فراغ *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

فراغ av_opt_set_defaults2(فراغ *s, صحيح mask, صحيح flags)
{
    ثابت AVOption *opt = عدم;
    ܟܡܐ ((opt = av_opt_next(s, opt))) {
        فراغ *dst = ((uint8_t*)s) + opt->offset;

        ܐܢ ((opt->flags & mask) != flags)
            استمر;

        ܐܢ (opt->flags & AV_OPT_FLAG_READONLY)
            استمر;

        ܐܢ (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ثابت AVOptionArrayDef *arr = opt->default_val.arr;
            ثابت حرف              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            ܐܢ (arr && arr->def)
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
                write_number(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
            حالة AV_OPT_TYPE_FLOAT: {
                مزدوج val;
                val = opt->default_val.dbl;
                write_number(s, opt, dst, val, 1, 1, 1);
            }
            اكسر;
            حالة AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_number(s, opt, dst, 1, val.den, val.num, 1);
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
            حالة AV_OPT_TYPE_BINARY:
                set_string_binary(s, opt, opt->default_val.str, dst);
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
ساكن صحيح parse_key_value_pair(فراغ *ctx, ثابت حرف **buf,
                                ثابت حرف *key_val_sep, ثابت حرف *pairs_sep)
{
    حرف *key = av_get_token(buf, key_val_sep);
    حرف *val;
    صحيح ret;

    ܐܢ (!key)
        ܦܢܐ AVERROR(ENOMEM);

    ܐܢ (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        ܐܢ (!val) {
            av_freep(&key);
            ܦܢܐ AVERROR(ENOMEM);
        }
    } ܐܚܪܢܐ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        ܦܢܐ AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    ܐܢ (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    ܦܢܐ ret;
}

صحيح av_set_options_string(فراغ *ctx, ثابت حرف *opts,
                          ثابت حرف *key_val_sep, ثابت حرف *pairs_sep)
{
    صحيح ret, count = 0;

    ܐܢ (!opts)
        ܦܢܐ 0;

    ܟܡܐ (*opts) {
        ܐܢ ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            ܦܢܐ ret;
        count++;

        ܐܢ (*opts)
            opts++;
    }

    ܦܢܐ count;
}

#define WHITESPACES " \n\t\r"

ساكن صحيح is_key_char(حرف c)
{
    ܦܢܐ (unsigned)((c | 32) - 'a') < 26 ||
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
ساكن صحيح get_key(ثابت حرف **ropts, ثابت حرف *delim, حرف **rkey)
{
    ثابت حرف *opts = *ropts;
    ثابت حرف *key_start, *key_end;

    key_start = opts += strspn(opts, WHITESPACES);
    ܟܡܐ (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    ܐܢ (!*opts || !strchr(delim, *opts))
        ܦܢܐ AVERROR(EINVAL);
    opts++;
    ܐܢ (!(*rkey = av_malloc(key_end - key_start + 1)))
        ܦܢܐ AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    ܦܢܐ 0;
}

صحيح av_opt_get_key_value(ثابت حرف **ropts,
                         ثابت حرف *key_val_sep, ثابت حرف *pairs_sep,
                         unsigned flags,
                         حرف **rkey, حرف **rval)
{
    صحيح ret;
    حرف *key = عدم, *val;
    ثابت حرف *opts = *ropts;

    ܐܢ ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        ܦܢܐ AVERROR(EINVAL);
    ܐܢ (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        ܦܢܐ AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    ܦܢܐ 0;
}

صحيح av_opt_set_from_string(فراغ *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *key_val_sep, ثابت حرف *pairs_sep)
{
    صحيح ret, count = 0;
    ثابت حرف *dummy_shorthand = عدم;
    ثابت حرف *key;

    ܐܢ (!opts)
        ܦܢܐ 0;
    ܐܢ (!shorthand)
        shorthand = &dummy_shorthand;

    ܟܡܐ (*opts) {
        حرف *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        ܐܢ (ret < 0) {
            ܐܢ (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ܐܚܪܢܐ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            ܦܢܐ ret;
        }
        ܐܢ (*opts)
            opts++;
        ܐܢ (parsed_key) {
            key = parsed_key;
            ܟܡܐ (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ܐܚܪܢܐ {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        ܐܢ ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            ܐܢ (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            ܦܢܐ ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    ܦܢܐ count;
}

فراغ av_opt_free(فراغ *obj)
{
    ثابت AVOption *o = عدم;
    ܟܡܐ ((o = av_opt_next(obj, o))) {
        فراغ *pitem = (uint8_t *)obj + o->offset;

        ܐܢ (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ܐܚܪܢܐ
            opt_free_elem(o->type, pitem);
    }
}

صحيح av_opt_set_dict2(فراغ *obj, AVDictionary **options, صحيح search_flags)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVDictionary    *tmp = عدم;
    صحيح ret;

    ܐܢ (!options)
        ܦܢܐ 0;

    ܟܡܐ ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        ܐܢ (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        ܐܢ (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            ܦܢܐ ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    ܦܢܐ 0;
}

صحيح av_opt_set_dict(فراغ *obj, AVDictionary **options)
{
    ܦܢܐ av_opt_set_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_find(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحيح opt_flags, صحيح search_flags)
{
    ܦܢܐ av_opt_find2(obj, name, unit, opt_flags, search_flags, عدم);
}

ثابت AVOption *av_opt_find2(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحيح opt_flags, صحيح search_flags, فراغ **target_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = عدم;

    ܐܢ(!obj)
        ܦܢܐ عدم;

    c= *(AVClass**)obj;

    ܐܢ (!c)
        ܦܢܐ عدم;

    ܐܢ (search_flags & AV_OPT_SEARCH_CHILDREN) {
        ܐܢ (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            فراغ *iter = عدم;
            ثابت AVClass *child;
            ܟܡܐ (child = av_opt_child_class_iterate(c, &iter))
                ܐܢ (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, عدم))
                    ܦܢܐ o;
        } ܐܚܪܢܐ {
            فراغ *child = عدم;
            ܟܡܐ (child = av_opt_child_next(obj, child))
                ܐܢ (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    ܦܢܐ o;
        }
    }

    ܟܡܐ (o = av_opt_next(obj, o)) {
        ܐܢ (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            ܐܢ (target_obj) {
                ܐܢ (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                ܐܚܪܢܐ
                    *target_obj = عدم;
            }
            ܦܢܐ o;
        }
    }
    ܦܢܐ عدم;
}

فراغ *av_opt_child_next(فراغ *obj, فراغ *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    ܐܢ (c->child_next)
        ܦܢܐ c->child_next(obj, prev);
    ܦܢܐ عدم;
}

ثابت AVClass *av_opt_child_class_iterate(ثابت AVClass *parent, فراغ **iter)
{
    ܐܢ (parent->child_class_iterate)
        ܦܢܐ parent->child_class_iterate(iter);
    ܦܢܐ عدم;
}

ساكن صحيح opt_copy_elem(فراغ *logctx, تعداد AVOptionType type,
                         فراغ *dst, ثابت فراغ *src)
{
    ܐܢ (type == AV_OPT_TYPE_STRING) {
        ثابت حرف *src_str = *(ثابت حرف *ثابت *)src;
        حرف         **dstp =  (حرف **)dst;
        ܐܢ (*dstp != src_str)
            av_freep(dstp);
        ܐܢ (src_str) {
            *dstp = av_strdup(src_str);
            ܐܢ (!*dstp)
                ܦܢܐ AVERROR(ENOMEM);
        }
    } ܐܚܪܢܐ ܐܢ (type == AV_OPT_TYPE_BINARY) {
        ثابت uint8_t *ثابت *src8 = (ثابت uint8_t *ثابت *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        صحيح len = *(ثابت صحيح *)(src8 + 1);
        ܐܢ (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        ܐܢ (len && !*dst8) {
            *(صحيح *)(dst8 + 1) = 0;
            ܦܢܐ AVERROR(ENOMEM);
        }
        *(صحيح *)(dst8 + 1) = len;
    } ܐܚܪܢܐ ܐܢ (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ܐܚܪܢܐ ܐܢ (type == AV_OPT_TYPE_DICT) {
        ثابت AVDictionary *sdict = *(ثابت AVDictionary * ثابت *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        ܐܢ (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = عدم;
        ܦܢܐ av_dict_copy(ddictp, sdict, 0);
    } ܐܚܪܢܐ ܐܢ (type == AV_OPT_TYPE_CHLAYOUT) {
        ثابت AVChannelLayout *slayout = (ثابت AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        ܐܢ (dlayout != slayout) {
            ܐܢ (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = عدم;
            ܦܢܐ av_channel_layout_copy(dst, src);
        }
    } ܐܚܪܢܐ ܐܢ (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } ܐܚܪܢܐ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        ܦܢܐ AVERROR(EINVAL);
    }

    ܦܢܐ 0;
}

ساكن صحيح opt_copy_array(فراغ *logctx, ثابت AVOption *o,
                          فراغ **pdst, ثابت فراغ * ثابت *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    فراغ         *dst = عدم;
    صحيح ret;

    ܐܢ (*pdst == *psrc) {
        *pdst                   = عدم;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    ܐܢ (!dst)
        ܦܢܐ AVERROR(ENOMEM);

    لكل (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(فراغ**)psrc, i));
        ܐܢ (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            ܦܢܐ ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    ܦܢܐ 0;
}

صحيح av_opt_copy(فراغ *dst, ثابت فراغ *src)
{
    ثابت AVOption *o = عدم;
    ثابت AVClass *c;
    صحيح ret = 0;

    ܐܢ (!src)
        ܦܢܐ AVERROR(EINVAL);

    c = *(AVClass **)src;
    ܐܢ (!c || c != *(AVClass **)dst)
        ܦܢܐ AVERROR(EINVAL);

    ܟܡܐ ((o = av_opt_next(src, o))) {
        فراغ *field_dst = (uint8_t *)dst + o->offset;
        فراغ *field_src = (uint8_t *)src + o->offset;

        صحيح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        ܐܢ (err < 0)
            ret = err;
    }
    ܦܢܐ ret;
}

صحيح av_opt_get_array_size(فراغ *obj, ثابت حرف *name, صحيح search_flags,
                          unsigned صحيح *out_val)
{
    فراغ *target_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        ܦܢܐ AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    ܦܢܐ 0;
}

صحيح av_opt_get_array(فراغ *obj, ثابت حرف *name, صحيح search_flags,
                     unsigned صحيح start_elem, unsigned صحيح nb_elems,
                     تعداد AVOptionType out_type, فراغ *out_val)
{
    ثابت size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    ثابت AVOption *o;
    فراغ *target_obj;

    ثابت فراغ *parray;
    unsigned array_size;

    صحيح ret;

    o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    ܐܢ (!o || !target_obj)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܐܢ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        ܦܢܐ AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    ܐܢ (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        ܦܢܐ AVERROR(EINVAL);

    لكل (unsigned i = 0; i < nb_elems; i++) {
        ثابت فراغ *src = opt_array_pelem(o, *(فراغ**)parray, start_elem + i);
        فراغ       *dst = (uint8_t*)out_val + i * elem_size_out;

        ܐܢ (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            ܐܢ (ret < 0)
                اذهب fail;
        } ܐܚܪܢܐ ܐܢ (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, حجم(buf), src, search_flags);
            ܐܢ (ret < 0)
                اذهب fail;

            ܐܢ (out == buf) {
                out = av_strdup(buf);
                ܐܢ (!out) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
            }

            *(uint8_t**)dst = out;
        } ܐܚܪܢܐ ܐܢ (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            مزدوج     num = 1.0;
            صحيح        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            ܐܢ (ret < 0)
                اذهب fail;

            بدل (out_type) {
            حالة AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (num == den) ?  intnum : num * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_DOUBLE:
                *(مزدوج*)dst = num * intnum / den;
                اكسر;
            حالة AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (num == 1.0 && (صحيح)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(num * intnum / den);
                اكسر;
            افتراضي: av_assert0(0);
            }
        } ܐܚܪܢܐ
            ܦܢܐ AVERROR(ENOSYS);
    }

    ܦܢܐ 0;
fail:
    لكل (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    ܦܢܐ ret;
}

صحيح av_opt_set_array(فراغ *obj, ثابت حرف *name, صحيح search_flags,
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

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &parray);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ܐܢ (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        ܦܢܐ AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    ܐܢ (start_elem > *array_size)
        ܦܢܐ AVERROR(EINVAL);

    // compute new array size
    ܐܢ (!val) {
        ܐܢ (*array_size - start_elem < nb_elems)
            ܦܢܐ AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } ܐܚܪܢܐ ܐܢ (search_flags & AV_OPT_ARRAY_REPLACE) {
        ܐܢ (start_elem >= UINT_MAX - nb_elems)
            ܦܢܐ AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } ܐܚܪܢܐ {
        ܐܢ (nb_elems >= UINT_MAX - *array_size)
            ܦܢܐ AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    ܐܢ (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        ܦܢܐ AVERROR(EINVAL);

    // desired operation is shrinking the array
    ܐܢ (!val) {
        فراغ *array = *(فراغ**)parray;

        لكل (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        ܐܢ (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            ܐܢ (!array)
                ܦܢܐ AVERROR(ENOMEM);

            *(فراغ**)parray = array;
        } ܐܚܪܢܐ
            av_freep(parray);

        *array_size = new_size;

        ܦܢܐ 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    ܐܢ (!new_elems)
        ܦܢܐ AVERROR(ENOMEM);

    // convert/validate each new element
    لكل (unsigned i = 0; i < nb_elems; i++) {
        فراغ       *dst = opt_array_pelem(o, new_elems, i);
        ثابت فراغ *src = (uint8_t*)val + i * elem_size_val;

        مزدوج     num = 1.0;
        صحيح        den = 1;
        int64_t intnum = 1;

        ܐܢ (val_type == TYPE_BASE(o->type)) {
            صحيح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            ܐܢ (ret < 0)
                اذهب fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            ܐܢ (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                اذهب fail;
            }
        } ܐܚܪܢܐ ܐܢ (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ثابت حرف **)src, dst);
            ܐܢ (ret < 0)
                اذهب fail;
        } ܐܚܪܢܐ ܐܢ (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            بدل (val_type) {
            حالة AV_OPT_TYPE_INT:       intnum = *(صحيح*)src;                اكسر;
            حالة AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            اكسر;
            حالة AV_OPT_TYPE_FLOAT:     num    = *(عائم*)src;              اكسر;
            حالة AV_OPT_TYPE_DOUBLE:    num    = *(مزدوج*)src;             اكسر;
            حالة AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->num;
                                        den    = ((AVRational*)src)->den;   اكسر;
            افتراضي: av_assert0(0);
            }

            ret = write_number(obj, o, dst, num, den, intnum, 0);
            ܐܢ (ret < 0)
                اذهب fail;
        } ܐܚܪܢܐ {
            ret = AVERROR(ENOSYS);
            اذهب fail;
        }
    }

    // commit new elements to the array
    ܐܢ (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(فراغ**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = عدم;
        nb_elems  = 0;
    } ܐܚܪܢܐ {
        فراغ *array = av_realloc_array(*(فراغ**)parray, new_size, elem_size);
        ܐܢ (!array) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }

        ܐܢ (search_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            لكل (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ܐܚܪܢܐ {
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

    ܦܢܐ ret;
}

صحيح av_opt_query_ranges(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *key, صحيح flags)
{
    صحيح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحيح (*callback)(AVOptionRanges **, فراغ *obj, ثابت حرف *key, صحيح flags) = c->query_ranges;

    ܐܢ (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    ܐܢ (ret >= 0) {
        ܐܢ (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    ܦܢܐ ret;
}

صحيح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *key, صحيح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(فراغ*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *field = av_opt_find(obj, key, عدم, 0, flags);
    صحيح ret;

    *ranges_arg = عدم;

    ܐܢ (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->value_min = field->min;
    range->value_max = field->max;

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
        range->value_min = -1;
        range->value_max = INT_MAX;
        اكسر;
    حالة AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        اكسر;
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->value_min = 0;
        range->value_max = INT_MAX/8;
        اكسر;
    حالة AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->value_min = 1;
        range->value_max = INT_MAX;
        اكسر;
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    *ranges_arg = ranges;
    ܦܢܐ 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    ܦܢܐ ret;
}

فراغ av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    صحيح i;
    AVOptionRanges *ranges = *rangesp;

    ܐܢ (!ranges)
        ܦܢܐ;

    لكل (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        ܐܢ (range) {
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

    ܐܢ (!o || !obj)
        ܦܢܐ AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    ܐܢ (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت حرف *def = o->default_val.arr ? o->default_val.arr->def : عدم;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        ܐܢ (ret < 0)
            ܦܢܐ ret;

        ܐܢ (!!val != !!def)
            ret = 0;
        ܐܚܪܢܐ ܐܢ (val)
            ret = !strcmp(val, def);
        ܐܚܪܢܐ
            ret = 1;

        av_freep(&val);

        ܦܢܐ ret;
    }

    بدل (o->type) {
    حالة AV_OPT_TYPE_CONST:
        ܦܢܐ 1;
    حالة AV_OPT_TYPE_BOOL:
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_PIXEL_FMT:
    حالة AV_OPT_TYPE_SAMPLE_FMT:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        read_number(o, dst, عدم, عدم, &i64);
        ܦܢܐ o->default_val.i64 == i64;
    حالة AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        ܐܢ (o->default_val.str) {
            ܐܢ ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                ܦܢܐ ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        ܦܢܐ ret;
    }
    حالة AV_OPT_TYPE_STRING:
        str = *(حرف **)dst;
        ܐܢ (str == o->default_val.str) //2 NULLs
            ܦܢܐ 1;
        ܐܢ (!str || !o->default_val.str) //1 NULL
            ܦܢܐ 0;
        ܦܢܐ !strcmp(str, o->default_val.str);
    حالة AV_OPT_TYPE_DOUBLE:
        d = *(مزدوج *)dst;
        ܦܢܐ o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالة AV_OPT_TYPE_FLOAT:
        d = *(عائم *)dst;
        ܦܢܐ (عائم)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالة AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        ܦܢܐ !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالة AV_OPT_TYPE_BINARY: {
        بنية {
            uint8_t *data;
            صحيح size;
        } tmp = {0};
        صحيح opt_size = *(صحيح *)((فراغ **)dst + 1);
        فراغ *opt_ptr = *(فراغ **)dst;
        ܐܢ (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            ܦܢܐ 1;
        ܐܢ (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            ܦܢܐ 0;
        ܐܢ (opt_size != strlen(o->default_val.str) / 2)
            ܦܢܐ 0;
        ret = set_string_binary(عدم, عدم, o->default_val.str, &tmp.data);
        ܐܢ (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        ܦܢܐ ret;
    }
    حالة AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = عدم;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionaryEntry *en1 = عدم;
        ثابت AVDictionaryEntry *en2 = عدم;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        ܐܢ (ret < 0) {
            av_dict_free(&dict1);
            ܦܢܐ ret;
        }
        ܥܒܕ {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } ܟܡܐ (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        ܦܢܐ (!en1 && !en2);
    }
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        ܐܢ (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ܐܚܪܢܐ ܐܢ ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            ܦܢܐ ret;
        ܦܢܐ (w == *(صحيح *)dst) && (h == *((صحيح *)dst+1));
    حالة AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        ܐܢ (o->default_val.str) {
            ܐܢ ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                ܦܢܐ ret;
        }
        ܦܢܐ !av_cmp_q(*(AVRational*)dst, q);
    حالة AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        ܐܢ (o->default_val.str) {
            ܐܢ ((ret = av_parse_color(color, o->default_val.str, -1, عدم)) < 0)
                ܦܢܐ ret;
        }
        ܦܢܐ !memcmp(color, dst, حجم(color));
    }
    افتراضي:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        اكسر;
    }
    ܦܢܐ AVERROR_PATCHWELCOME;
}

صحيح av_opt_is_set_to_default_by_name(فراغ *obj, ثابت حرف *name, صحيح search_flags)
{
    ثابت AVOption *o;
    فراغ *target;
    ܐܢ (!obj)
        ܦܢܐ AVERROR(EINVAL);
    o = av_opt_find2(obj, name, عدم, 0, search_flags, &target);
    ܐܢ (!o)
        ܦܢܐ AVERROR_OPTION_NOT_FOUND;
    ܦܢܐ av_opt_is_set_to_default(target, o);
}

ساكن صحيح opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, صحيح *cnt,
                         AVBPrint *bprint, ثابت حرف key_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVOption *o = عدم;
    فراغ *child = عدم;
    uint8_t *buf;
    صحيح ret;
    ثابت حرف special_chars[] = {pairs_sep, key_val_sep, '\0'};

    ܐܢ (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        ܟܡܐ (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            ܐܢ (ret < 0)
                ܦܢܐ ret;
        }

    ܟܡܐ (o = av_opt_next(obj, o)) {
        ܐܢ (o->type == AV_OPT_TYPE_CONST)
            استمر;
        ܐܢ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            ܐܢ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                ܐܢ (o->flags == opt_flags)
                    استمر;
            } ܐܚܪܢܐ ܐܢ ((o->flags & opt_flags) == opt_flags)
                استمر;
        } ܐܚܪܢܐ {
            ܐܢ ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                استمر;
            ܐܚܪܢܐ ܐܢ (((o->flags & opt_flags) != opt_flags))
                استمر;
        }
        ܐܢ (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            استمر;
        ܐܢ ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, عدم);
            ܦܢܐ ret;
        }
        ܐܢ (buf) {
            ܐܢ ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    ܦܢܐ 0;
}

صحيح av_opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, حرف **buffer,
                     ثابت حرف key_val_sep, ثابت حرف pairs_sep)
{
    AVBPrint bprint;
    صحيح ret, cnt = 0;

    ܐܢ (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        ܦܢܐ AVERROR(EINVAL);
    }

    ܐܢ (!obj || !buffer)
        ܦܢܐ AVERROR(EINVAL);

    *buffer = عدم;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    ret = av_bprint_finalize(&bprint, buffer);
    ܐܢ (ret < 0)
        ܦܢܐ ret;
    ܦܢܐ 0;
}
