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
    𐤀𐤌 (!obj)
        أرجع عدم;
    class = *(ثابت AVClass**)obj;
    𐤀𐤌 (!last && class && class->option && class->option[0].name)
        أرجع class->option;
    𐤀𐤌 (last && last[1].name)
        أرجع ++last;
    أرجع عدم;
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

ساكن فراغ *opt_array_pelem(ثابت AVOption *o, فراغ *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    أرجع (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

ساكن unsigned *opt_array_pcount(ثابت فراغ *parray)
{
    أرجع (unsigned *)((ثابت فراغ * ثابت *)parray + 1);
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
    𐤀𐤌 (!o || (!tgt && !(search_flags & AV_OPT_SEARCH_FAKE_OBJ)))
        أرجع AVERROR_OPTION_NOT_FOUND;

    𐤀𐤌 (o->flags & AV_OPT_FLAG_READONLY)
        أرجع AVERROR(EINVAL);

    logctx = tgt ? obj : عدم;

    𐤀𐤌 (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        أرجع AVERROR(EINVAL);
    }

    𐤀𐤌 (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = عدم;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        𐤀𐤌 (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        𐤀𐤌 (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            𐤀𐤌 (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        𐤀𐤌 (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            أرجع AVERROR(EINVAL);
        }
    }

    𐤀𐤌 (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    𐤀𐤌 (po)
        *po   = o;
    𐤀𐤌 (ptgt)
        *ptgt = tgt;
    𐤀𐤌 (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : عدم;

    أرجع 0;
}

ساكن AVRational double_to_rational(مزدوج d)
{
     AVRational r = av_d2q(d, 1 << 24);
     𐤀𐤌 ((!r.num || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     أرجع r;
}

ساكن صحيح read_number(ثابت AVOption *o, ثابت فراغ *dst, مزدوج *num, صحيح *den, int64_t *intnum)
{
    بدل (TYPE_BASE(o->type)) {
    حالة AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned صحيح*)dst;
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
        *intnum = *(unsigned صحيح *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_DURATION:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_FLOAT:
        *num = *(عائم *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_DOUBLE:
        *num = *(مزدوج *)dst;
        أرجع 0;
    حالة AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->num;
        *den    = ((AVRational *)dst)->den;
        أرجع 0;
    حالة AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        أرجع 0;
    }
    أرجع AVERROR(EINVAL);
}

ساكن صحيح write_number(فراغ *obj, ثابت AVOption *o, فراغ *dst,
                        مزدوج num, صحيح den, int64_t intnum,
                        صحيح ignore_range)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);

    𐤀𐤌 (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
        num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               num, o->name, o->min, o->max);
        أرجع AVERROR(ERANGE);
    }
    𐤀𐤌 (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        مزدوج d = num*intnum/den;
        𐤀𐤌 (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   num*intnum/den, o->name);
            أرجع AVERROR(ERANGE);
        }
    }

    𐤀𐤌 (!dst)
        أرجع 0;

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
        𐤀𐤌 (intnum == 1 && d == (مزدوج)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } وإلا
            *(int64_t *)dst = llrint(d) * intnum;
        اكسر;}
    حالة AV_OPT_TYPE_UINT64:{
        مزدوج d = num / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        𐤀𐤌 (intnum == 1 && d == (مزدوج)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } وإلا 𐤀𐤌 (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } وإلا {
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
        𐤀𐤌 ((صحيح) num == num)
            *(AVRational *)dst = (AVRational) { num *intnum, den };
        وإلا
            *(AVRational *)dst = double_to_rational(num * intnum / den);
        اكسر;
    افتراضي:
        أرجع AVERROR(EINVAL);
    }
    أرجع 0;
}

ساكن صحيح hexchar2int(حرف c) {
    𐤀𐤌 (c >= '0' && c <= '9')
        أرجع c - '0';
    𐤀𐤌 (c >= 'a' && c <= 'f')
        أرجع c - 'a' + 10;
    𐤀𐤌 (c >= 'A' && c <= 'F')
        أرجع c - 'A' + 10;
    أرجع -1;
}

ساكن صحيح set_string_binary(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحيح *lendst;
    uint8_t *bin, *ptr;
    صحيح len;

    𐤀𐤌 (dst) {
        lendst = (صحيح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    𐤀𐤌 (!val || !(len = strlen(val)))
        أرجع 0;

    𐤀𐤌 (len & 1)
        أرجع AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    𐤀𐤌 (!ptr)
        أرجع AVERROR(ENOMEM);
    طالما (*val) {
        صحيح a = hexchar2int(*val++);
        صحيح b = hexchar2int(*val++);
        𐤀𐤌 (a < 0 || b < 0) {
            av_free(bin);
            أرجع AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    𐤀𐤌 (dst) {
        *dst    = bin;
        *lendst = len;
    } وإلا {
        av_free(bin);
    }

    أرجع 0;
}

ساكن صحيح set_string(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    𐤀𐤌 (!dst)
        أرجع 0;
    av_freep(dst);
    𐤀𐤌 (!val)
        أرجع 0;
    *dst = av_strdup(val);
    أرجع *dst ? 0 : AVERROR(ENOMEM);
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

    𐤀𐤌 (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        صحيح num, den;
        حرف c;
        𐤀𐤌 (sscanf(val, "%d%*1[:/]%d%c", &num, &den, &c) == 2) {
            𐤀𐤌 ((ret = write_number(obj, o, dst, 1, den, num, 0)) >= 0)
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

        𐤀𐤌 (type == AV_OPT_TYPE_FLAGS) {
            𐤀𐤌 (*val == '+' || *val == '-')
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
            𐤀𐤌 (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                𐤀𐤌 (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } وإلا {
                𐤀𐤌 (o->unit) {
                    لكل (o_named = عدم; o_named = av_opt_next(target_obj, o_named); ) {
                        𐤀𐤌 (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            𐤀𐤌 (ci + 6 >= FF_ARRAY_ELEMS(const_values)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                أرجع AVERROR_PATCHWELCOME;
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
                𐤀𐤌 (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    أرجع res;
                }
            }
        }
        𐤀𐤌 (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned صحيح*)dst;
            𐤀𐤌 (cmd == '+')
                d = intnum | (int64_t)d;
            وإلا 𐤀𐤌 (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        𐤀𐤌 ((ret = write_number(obj, o, dst, d, 1, 1, 0)) < 0)
            أرجع ret;
        val += i;
        𐤀𐤌 (!i || !*val)
            أرجع 0;
    }
}

ساكن صحيح set_string_image_size(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح tmp[2];
    صحيح ret;

    𐤀𐤌 (!val || !strcmp(val, "none")) {
        𐤀𐤌 (dst) {
        dst[0] =
        dst[1] = 0;
        }
        أرجع 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    𐤀𐤌 (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        أرجع ret;
    }
    𐤀𐤌 (dst)
        memcpy(dst, tmp, حجم(tmp));
    أرجع ret;
}

ساكن صحيح set_string_video_rate(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    AVRational tmp;
    صحيح ret = av_parse_video_rate(&tmp, val);
    𐤀𐤌 (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    𐤀𐤌 (dst)
        *dst = tmp;
    أرجع ret;
}

ساكن صحيح set_string_color(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح ret;

    𐤀𐤌 (!val) {
        أرجع 0;
    } وإلا {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        𐤀𐤌 (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            أرجع ret;
        }
        𐤀𐤌 (dst)
            memcpy(dst, tmp, حجم(tmp));
        أرجع ret;
    }
    أرجع 0;
}

ساكن ثابت حرف *get_bool_name(صحيح val)
{
    𐤀𐤌 (val < 0)
        أرجع "auto";
    أرجع val ? "true" : "false";
}

ساكن صحيح set_string_bool(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, صحيح *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح n;

    𐤀𐤌 (!val)
        أرجع 0;

    𐤀𐤌 (!strcmp(val, "auto")) {
        n = -1;
    } وإلا 𐤀𐤌 (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } وإلا 𐤀𐤌 (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } وإلا {
        حرف *end = عدم;
        n = strtol(val, &end, 10);
        𐤀𐤌 (val + strlen(val) != end)
            اذهب fail;
    }

    𐤀𐤌 (n < o->min || n > o->max)
        اذهب fail;

    𐤀𐤌 (dst)
    *dst = n;
    أرجع 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    أرجع AVERROR(EINVAL);
}

ساكن صحيح set_string_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
                          صحيح fmt_nb, صحيح ((*get_fmt)(ثابت حرف *)), ثابت حرف *desc,
                          تعداد AVOptionType type)
{
    فراغ *logctx = dst ? obj : عدم;
    صحيح fmt, min, max;

    𐤀𐤌 (!val || !strcmp(val, "none")) {
        fmt = -1;
    } وإلا {
        fmt = get_fmt(val);
        𐤀𐤌 (fmt == -1) {
            حرف *tail;
            fmt = strtol(val, &tail, 0);
            𐤀𐤌 (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                أرجع AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    𐤀𐤌(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    𐤀𐤌 (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        أرجع AVERROR(ERANGE);
    }

    𐤀𐤌 (dst)
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

ساكن صحيح set_string_pixel_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساكن صحيح get_sample_fmt(ثابت حرف *name)
{
    أرجع av_get_sample_fmt(name);
}

ساكن صحيح set_string_sample_fmt(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    أرجع set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساكن صحيح set_string_dict(فراغ *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    AVDictionary *options = عدم;

    𐤀𐤌 (val) {
        صحيح ret = av_dict_parse_string(&options, val, "=", ":", 0);
        𐤀𐤌 (ret < 0) {
            av_dict_free(&options);
            أرجع ret;
        }
    }

    𐤀𐤌 (!dst) {
        av_dict_free(&options);
        أرجع 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    أرجع 0;
}

ساكن صحيح set_string_channel_layout(فراغ *obj, ثابت AVOption *o,
                                     ثابت حرف *val, فراغ *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    صحيح ret;
    𐤀𐤌 (dst)
    av_channel_layout_uninit(channel_layout);
    وإلا
        channel_layout = &tmp;
    𐤀𐤌 (!val)
        أرجع 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    𐤀𐤌 (ret < 0)
        أرجع ret;
    𐤀𐤌 (!dst)
        av_channel_layout_uninit(channel_layout);
    أرجع 0;
}

ساكن صحيح opt_set_elem(فراغ *obj, فراغ *target_obj, ثابت AVOption *o,
                        ثابت حرف *val, فراغ *dst)
{
    فراغ *logctx = dst ? obj : عدم;
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);
    صحيح ret;

    𐤀𐤌 (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        أرجع AVERROR(EINVAL);

    بدل (type) {
    حالة AV_OPT_TYPE_BOOL:
        أرجع set_string_bool(obj, o, val, dst);
    حالة AV_OPT_TYPE_STRING:
        أرجع set_string(obj, o, val, dst);
    حالة AV_OPT_TYPE_BINARY:
        أرجع set_string_binary(obj, o, val, dst);
    حالة AV_OPT_TYPE_FLAGS:
    حالة AV_OPT_TYPE_INT:
    حالة AV_OPT_TYPE_UINT:
    حالة AV_OPT_TYPE_INT64:
    حالة AV_OPT_TYPE_UINT64:
    حالة AV_OPT_TYPE_FLOAT:
    حالة AV_OPT_TYPE_DOUBLE:
    حالة AV_OPT_TYPE_RATIONAL:
        أرجع set_string_number(obj, target_obj, o, val, dst);
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        أرجع set_string_image_size(obj, o, val, dst);
    حالة AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        𐤀𐤌 (ret < 0)
            أرجع ret;
        أرجع write_number(obj, o, dst, 1, tmp.den, tmp.num, 0);
    }
    حالة AV_OPT_TYPE_PIXEL_FMT:
        أرجع set_string_pixel_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_SAMPLE_FMT:
        أرجع set_string_sample_fmt(obj, o, val, dst);
    حالة AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            𐤀𐤌 (val) {
                𐤀𐤌 ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    أرجع ret;
                }
            }
            𐤀𐤌 (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                أرجع AVERROR(ERANGE);
            }
            𐤀𐤌 (dst)
            *(int64_t *)dst = usecs;
            أرجع 0;
        }
    حالة AV_OPT_TYPE_COLOR:
        أرجع set_string_color(obj, o, val, dst);
    حالة AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        𐤀𐤌 (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        أرجع ret;
    حالة AV_OPT_TYPE_DICT:
        أرجع set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    أرجع AVERROR(EINVAL);
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

    𐤀𐤌 (val && *val) {
        str = av_malloc(strlen(val) + 1);
        𐤀𐤌 (!str)
            أرجع AVERROR(ENOMEM);
    }

    // split and unescape the string
    طالما (val && *val) {
        uint8_t *p = str;
        فراغ *tmp;

        𐤀𐤌 (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            اذهب fail;
        }

        لكل (; *val; val++, p++) {
            𐤀𐤌 (*val == '\\' && val[1])
                val++;
            وإلا 𐤀𐤌 (*val == sep) {
                val++;
                اكسر;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        𐤀𐤌 (!tmp) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        𐤀𐤌 (ret < 0)
            اذهب fail;
        nb_elems++;
    }
    av_freep(&str);

    𐤀𐤌 (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    𐤀𐤌 (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        اذهب fail;
    }

    𐤀𐤌 (dst) {
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

صحيح av_opt_set(فراغ *obj, ثابت حرف *name, ثابت حرف *val, صحيح search_flags)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, 0, &target_obj, &o, &dst);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    أرجع ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_NUMBER(name, opttype, vartype)                         \
صحيح av_opt_eval_ ## name(فراغ *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## _out)        \
{                                                                       \
    𐤀𐤌 (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        أرجع AVERROR(EINVAL);                                         \
    أرجع set_string_number(obj, obj, o, val, name ## _out);           \
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
    𐤀𐤌 (ret < 0)
        أرجع ret;
    𐤀𐤌 (dst)
        ret = write_number(obj, o, dst, num, den, intnum, 0);

    أرجع ret;
}

صحيح av_opt_set_int(فراغ *obj, ثابت حرف *name, int64_t val, صحيح search_flags)
{
    أرجع set_number(obj, name, 1, 1, val, search_flags, 0);
}

صحيح av_opt_set_double(فراغ *obj, ثابت حرف *name, مزدوج val, صحيح search_flags)
{
    أرجع set_number(obj, name, val, 1, 1, search_flags, 0);
}

صحيح av_opt_set_q(فراغ *obj, ثابت حرف *name, AVRational val, صحيح search_flags)
{
    أرجع set_number(obj, name, val.num, val.den, 1, search_flags, 0);
}

صحيح av_opt_set_bin(فراغ *obj, ثابت حرف *name, ثابت uint8_t *val, صحيح len, صحيح search_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحيح *lendst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_BINARY,
                       عدم, عدم, (فراغ**)&dst);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    𐤀𐤌 (dst) {
    ptr = len ? av_malloc(len) : عدم;
    𐤀𐤌 (len && !ptr)
        أرجع AVERROR(ENOMEM);

    lendst = (صحيح *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    𐤀𐤌 (len)
        memcpy(ptr, val, len);
    }

    أرجع 0;
}

صحيح av_opt_set_image_size(فراغ *obj, ثابت حرف *name, صحيح w, صحيح h, صحيح search_flags)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       عدم, &o, (فراغ**)&dst);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    logctx = dst ? obj : عدم;

    𐤀𐤌 (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        أرجع AVERROR(EINVAL);
    }

    𐤀𐤌 (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    أرجع 0;
}

صحيح av_opt_set_video_rate(فراغ *obj, ثابت حرف *name, AVRational val, صحيح search_flags)
{
    أرجع set_number(obj, name, val.num, val.den, 1, search_flags, AV_OPT_TYPE_VIDEO_RATE);
}

ساكن صحيح set_format(فراغ *obj, ثابت حرف *name, صحيح fmt, صحيح search_flags,
                      تعداد AVOptionType type, ثابت حرف *desc, صحيح nb_fmts)
{
    ثابت AVOption *o;
    فراغ *logctx;
    صحيح *dst;
    صحيح min, max, ret;

    ret = opt_set_init(obj, name, search_flags, type, عدم, &o, (فراغ**)&dst);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    logctx = dst ? obj : عدم;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    𐤀𐤌 (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        أرجع AVERROR(ERANGE);
    }
    𐤀𐤌 (dst)
    *dst = fmt;
    أرجع 0;
}

صحيح av_opt_set_pixel_fmt(فراغ *obj, ثابت حرف *name, تعداد AVPixelFormat fmt, صحيح search_flags)
{
    أرجع set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحيح av_opt_set_sample_fmt(فراغ *obj, ثابت حرف *name, تعداد AVSampleFormat fmt, صحيح search_flags)
{
    أرجع set_format(obj, name, fmt, search_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحيح av_opt_set_dict_val(فراغ *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحيح search_flags)
{
    AVDictionary **dst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_DICT, عدم, عدم,
                       (فراغ**)&dst);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    𐤀𐤌 (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    أرجع ret;
}

صحيح av_opt_set_chlayout(فراغ *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحيح search_flags)
{
    AVChannelLayout *dst;
    صحيح ret;

    ret = opt_set_init(obj, name, search_flags, AV_OPT_TYPE_CHLAYOUT, عدم, عدم,
                       (فراغ**)&dst);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    𐤀𐤌 (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    أرجع ret;
}

ساكن فراغ format_duration(حرف *buf, size_t size, int64_t d)
{
    حرف *e;

    av_assert0(size >= 25);
    𐤀𐤌 (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    𐤀𐤌 (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    وإلا 𐤀𐤌 (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    وإلا 𐤀𐤌 (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحيح)((d / 60000000) % 60),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا 𐤀𐤌 (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (صحيح)(d / 60000000),
                 (صحيح)((d / 1000000) % 60),
                 (صحيح)(d % 1000000));
    وإلا
        snprintf(buf, size, "%d.%06d",
                 (صحيح)(d / 1000000),
                 (صحيح)(d % 1000000));
    e = buf + strlen(buf);
    طالما (e > buf && e[-1] == '0')
        *(--e) = 0;
    𐤀𐤌 (e > buf && e[-1] == '.')
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
        𐤀𐤌 (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } وإلا 𐤀𐤌 (search_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = عدم;
            أرجع 0;
        } وإلا {
            *pbuf = av_strdup("");
        }
        أرجع *pbuf ? 0 : AVERROR(ENOMEM);
    حالة AV_OPT_TYPE_BINARY: {
        ثابت uint8_t *bin;
        صحيح len;

        𐤀𐤌 (!*(uint8_t **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        len = *(صحيح *)(((uint8_t *)dst) + حجم(uint8_t *));
        𐤀𐤌 ((uint64_t)len * 2 + 1 > INT_MAX)
            أرجع AVERROR(EINVAL);
        𐤀𐤌 (!(*pbuf = av_malloc(len * 2 + 1)))
            أرجع AVERROR(ENOMEM);
        𐤀𐤌 (!len) {
            *pbuf[0] = '\0';
            أرجع 0;
        }
        bin = *(uint8_t **)dst;
        لكل (صحيح i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        أرجع 0;
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
        𐤀𐤌 (!*(AVDictionary **)dst && (search_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = عدم;
            أرجع 0;
        }
        أرجع av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    افتراضي:
        أرجع AVERROR(EINVAL);
    }

    أرجع ret;
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
        𐤀𐤌 (ret < 0)
            اذهب fail;

        out_len = strlen(out);
        𐤀𐤌 (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            اذهب fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        𐤀𐤌 (ret < 0)
            اذهب fail;

        // add separator if needed
        𐤀𐤌 (i)
            str[str_len++] = sep;

        // escape the element
        لكل (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            𐤀𐤌 (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        𐤀𐤌 (out != buf)
            av_freep(&out);
        𐤀𐤌 (ret < 0) {
            av_freep(&str);
            أرجع ret;
        }
    }

    *out_val = str;

    أرجع 0;
}

صحيح av_opt_get(فراغ *obj, ثابت حرف *name, صحيح search_flags, uint8_t **out_val)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    uint8_t *out, buf[128];
    صحيح ret;

    𐤀𐤌 (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        أرجع AVERROR_OPTION_NOT_FOUND;

    𐤀𐤌 (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    𐤀𐤌 (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        𐤀𐤌 (ret < 0)
            أرجع ret;
        𐤀𐤌 (!*out_val && !(search_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            𐤀𐤌 (!*out_val)
               أرجع AVERROR(ENOMEM);
        }
        أرجع 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, حجم(buf), dst, search_flags);
    𐤀𐤌 (ret < 0)
        أرجع ret;
    𐤀𐤌 (out != buf) {
        *out_val = out;
        أرجع 0;
    }

    𐤀𐤌 (ret >= حجم(buf))
        أرجع AVERROR(EINVAL);
    *out_val = av_strdup(out);
    أرجع *out_val ? 0 : AVERROR(ENOMEM);
}

ساكن صحيح get_number(فراغ *obj, ثابت حرف *name, مزدوج *num, صحيح *den, int64_t *intnum,
                      صحيح search_flags)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    أرجع read_number(o, dst, num, den, intnum);
}

صحيح av_opt_get_int(فراغ *obj, ثابت حرف *name, صحيح search_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    مزدوج num = 1;
    صحيح ret, den = 1;

    𐤀𐤌 ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        أرجع ret;
    𐤀𐤌 (num == den)
        *out_val = intnum;
    وإلا
        *out_val = num * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_double(فراغ *obj, ثابت حرف *name, صحيح search_flags, مزدوج *out_val)
{
    int64_t intnum = 1;
    مزدوج num = 1;
    صحيح ret, den = 1;

    𐤀𐤌 ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        أرجع ret;
    *out_val = num * intnum / den;
    أرجع 0;
}

صحيح av_opt_get_q(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    مزدوج num = 1;
    صحيح ret, den = 1;

    𐤀𐤌 ((ret = get_number(obj, name, &num, &den, &intnum, search_flags)) < 0)
        أرجع ret;

    𐤀𐤌 (num == 1.0 && (صحيح)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    وإلا
        *out_val = double_to_rational(num*intnum/den);
    أرجع 0;
}

صحيح av_opt_get_image_size(فراغ *obj, ثابت حرف *name, صحيح search_flags, صحيح *w_out, صحيح *h_out)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    𐤀𐤌 (w_out) *w_out = *(صحيح *)dst;
    𐤀𐤌 (h_out) *h_out = *((صحيح *)dst+1);
    أرجع 0;
}

صحيح av_opt_get_video_rate(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVRational *out_val)
{
    أرجع av_opt_get_q(obj, name, search_flags, out_val);
}

ساكن صحيح get_format(فراغ *obj, ثابت حرف *name, صحيح search_flags, فراغ *out_fmt,
                      تعداد AVOptionType type, ثابت حرف *desc)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    𐤀𐤌 (type == AV_OPT_TYPE_PIXEL_FMT)
        *(تعداد AVPixelFormat *)out_fmt = *(تعداد AVPixelFormat *)dst;
    وإلا
        *(تعداد AVSampleFormat*)out_fmt = *(تعداد AVSampleFormat*)dst;

    أرجع 0;
}

صحيح av_opt_get_pixel_fmt(فراغ *obj, ثابت حرف *name, صحيح search_flags, تعداد AVPixelFormat *out_fmt)
{
    أرجع get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحيح av_opt_get_sample_fmt(فراغ *obj, ثابت حرف *name, صحيح search_flags, تعداد AVSampleFormat *out_fmt)
{
    أرجع get_format(obj, name, search_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحيح av_opt_get_chlayout(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVChannelLayout *cl)
{
    فراغ *dst, *target_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        أرجع AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    أرجع av_channel_layout_copy(cl, dst);
}

صحيح av_opt_get_dict_val(فراغ *obj, ثابت حرف *name, صحيح search_flags, AVDictionary **out_val)
{
    فراغ *target_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);

    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (o->type != AV_OPT_TYPE_DICT)
        أرجع AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    أرجع av_dict_copy(out_val, src, 0);
}

صحيح av_opt_flag_is_set(فراغ *obj, ثابت حرف *field_name, ثابت حرف *flag_name)
{
    ثابت AVOption *field = av_opt_find(obj, field_name, عدم, 0, 0);
    ثابت AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : عدم, 0, 0);
    int64_t res;

    𐤀𐤌 (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        أرجع 0;
    أرجع res & flag->default_val.i64;
}

ساكن فراغ log_int_value(فراغ *av_log_obj, صحيح level, int64_t i)
{
    𐤀𐤌 (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } وإلا 𐤀𐤌 (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } وإلا 𐤀𐤌 (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } وإلا 𐤀𐤌 (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } وإلا 𐤀𐤌 (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } وإلا {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ساكن فراغ log_value(فراغ *av_log_obj, صحيح level, مزدوج d)
{
    𐤀𐤌      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } وإلا 𐤀𐤌 (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } وإلا 𐤀𐤌 (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } وإلا 𐤀𐤌 (d == (مزدوج)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } وإلا 𐤀𐤌 (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } وإلا 𐤀𐤌 (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } وإلا 𐤀𐤌 (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } وإلا 𐤀𐤌 (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } وإلا 𐤀𐤌 (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } وإلا 𐤀𐤌 (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } وإلا 𐤀𐤌 (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } وإلا 𐤀𐤌 (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } وإلا 𐤀𐤌 (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } وإلا {
        av_log(av_log_obj, level, "%g", d);
    }
}

ساكن ثابت حرف *get_opt_const_name(فراغ *obj, ثابت حرف *unit, int64_t value)
{
    ثابت AVOption *opt = عدم;

    𐤀𐤌 (!unit)
        أرجع عدم;
    طالما ((opt = av_opt_next(obj, opt)))
        𐤀𐤌 (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == value)
            أرجع opt->name;
    أرجع عدم;
}

ساكن حرف *get_opt_flags_string(فراغ *obj, ثابت حرف *unit, int64_t value)
{
    ثابت AVOption *opt = عدم;
    حرف flags[512];

    flags[0] = 0;
    𐤀𐤌 (!unit)
        أرجع عدم;
    طالما ((opt = av_opt_next(obj, opt))) {
        𐤀𐤌 (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & value) {
            𐤀𐤌 (flags[0])
                av_strlcatf(flags, حجم(flags), "+");
            av_strlcatf(flags, حجم(flags), "%s", opt->name);
        }
    }
    𐤀𐤌 (flags[0])
        أرجع av_strdup(flags);
    أرجع عدم;
}

ساكن فراغ log_type(فراغ *av_log_obj, ثابت AVOption *o,
                     تعداد AVOptionType parent_type)
{
    ثابت تعداد AVOptionType type = TYPE_BASE(o->type);

    𐤀𐤌 (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    وإلا 𐤀𐤌 (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        𐤀𐤌 (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        وإلا
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    وإلا
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ساكن فراغ log_default(فراغ *obj, فراغ *av_log_obj, ثابت AVOption *opt)
{
    𐤀𐤌 (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_BINARY)
        أرجع;
    𐤀𐤌 ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        أرجع;

    𐤀𐤌 (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت AVOptionArrayDef *arr = opt->default_val.arr;
        𐤀𐤌 (arr && arr->def)
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
        𐤀𐤌 (def_flags) {
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
        𐤀𐤌 (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        وإلا
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

    طالما ((opt = av_opt_next(obj, opt))) {
        𐤀𐤌 (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            استمر;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        𐤀𐤌 (!unit && opt->type == AV_OPT_TYPE_CONST)
            استمر;
        وإلا 𐤀𐤌 (unit && opt->type != AV_OPT_TYPE_CONST)
            استمر;
        وإلا 𐤀𐤌 (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            استمر;
        وإلا 𐤀𐤌 (unit && opt->type == AV_OPT_TYPE_CONST)
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

        𐤀𐤌 (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        𐤀𐤌 (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_SEARCH_FAKE_OBJ) >= 0) {
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
        𐤀𐤌 (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

صحيح av_opt_show2(فراغ *obj, فراغ *av_log_obj, صحيح req_flags, صحيح rej_flags)
{
    𐤀𐤌 (!obj)
        أرجع -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, عدم, req_flags, rej_flags, -1);

    أرجع 0;
}

فراغ av_opt_set_defaults(فراغ *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

فراغ av_opt_set_defaults2(فراغ *s, صحيح mask, صحيح flags)
{
    ثابت AVOption *opt = عدم;
    طالما ((opt = av_opt_next(s, opt))) {
        فراغ *dst = ((uint8_t*)s) + opt->offset;

        𐤀𐤌 ((opt->flags & mask) != flags)
            استمر;

        𐤀𐤌 (opt->flags & AV_OPT_FLAG_READONLY)
            استمر;

        𐤀𐤌 (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ثابت AVOptionArrayDef *arr = opt->default_val.arr;
            ثابت حرف              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            𐤀𐤌 (arr && arr->def)
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

    𐤀𐤌 (!key)
        أرجع AVERROR(ENOMEM);

    𐤀𐤌 (*key && strspn(*buf, key_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        𐤀𐤌 (!val) {
            av_freep(&key);
            أرجع AVERROR(ENOMEM);
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", key);
        av_free(key);
        أرجع AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", key, val);

    ret = av_opt_set(ctx, key, val, AV_OPT_SEARCH_CHILDREN);
    𐤀𐤌 (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", key);

    av_free(key);
    av_free(val);
    أرجع ret;
}

صحيح av_set_options_string(فراغ *ctx, ثابت حرف *opts,
                          ثابت حرف *key_val_sep, ثابت حرف *pairs_sep)
{
    صحيح ret, count = 0;

    𐤀𐤌 (!opts)
        أرجع 0;

    طالما (*opts) {
        𐤀𐤌 ((ret = parse_key_value_pair(ctx, &opts, key_val_sep, pairs_sep)) < 0)
            أرجع ret;
        count++;

        𐤀𐤌 (*opts)
            opts++;
    }

    أرجع count;
}

#define WHITESPACES " \n\t\r"

ساكن صحيح is_key_char(حرف c)
{
    أرجع (unsigned)((c | 32) - 'a') < 26 ||
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
    طالما (is_key_char(*opts))
        opts++;
    key_end = opts;
    opts += strspn(opts, WHITESPACES);
    𐤀𐤌 (!*opts || !strchr(delim, *opts))
        أرجع AVERROR(EINVAL);
    opts++;
    𐤀𐤌 (!(*rkey = av_malloc(key_end - key_start + 1)))
        أرجع AVERROR(ENOMEM);
    memcpy(*rkey, key_start, key_end - key_start);
    (*rkey)[key_end - key_start] = 0;
    *ropts = opts;
    أرجع 0;
}

صحيح av_opt_get_key_value(ثابت حرف **ropts,
                         ثابت حرف *key_val_sep, ثابت حرف *pairs_sep,
                         unsigned flags,
                         حرف **rkey, حرف **rval)
{
    صحيح ret;
    حرف *key = عدم, *val;
    ثابت حرف *opts = *ropts;

    𐤀𐤌 ((ret = get_key(&opts, key_val_sep, &key)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_KEY))
        أرجع AVERROR(EINVAL);
    𐤀𐤌 (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(key);
        أرجع AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = key;
    *rval  = val;
    أرجع 0;
}

صحيح av_opt_set_from_string(فراغ *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *key_val_sep, ثابت حرف *pairs_sep)
{
    صحيح ret, count = 0;
    ثابت حرف *dummy_shorthand = عدم;
    ثابت حرف *key;

    𐤀𐤌 (!opts)
        أرجع 0;
    𐤀𐤌 (!shorthand)
        shorthand = &dummy_shorthand;

    طالما (*opts) {
        حرف *parsed_key, *value;
        ret = av_opt_get_key_value(&opts, key_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_KEY : 0,
                                   &parsed_key, &value);
        𐤀𐤌 (ret < 0) {
            𐤀𐤌 (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            وإلا
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            أرجع ret;
        }
        𐤀𐤌 (*opts)
            opts++;
        𐤀𐤌 (parsed_key) {
            key = parsed_key;
            طالما (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } وإلا {
            key = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", key, value);
        𐤀𐤌 ((ret = av_opt_set(ctx, key, value, 0)) < 0) {
            𐤀𐤌 (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", key);
            av_free(value);
            av_free(parsed_key);
            أرجع ret;
        }

        av_free(value);
        av_free(parsed_key);
        count++;
    }
    أرجع count;
}

فراغ av_opt_free(فراغ *obj)
{
    ثابت AVOption *o = عدم;
    طالما ((o = av_opt_next(obj, o))) {
        فراغ *pitem = (uint8_t *)obj + o->offset;

        𐤀𐤌 (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        وإلا
            opt_free_elem(o->type, pitem);
    }
}

صحيح av_opt_set_dict2(فراغ *obj, AVDictionary **options, صحيح search_flags)
{
    ثابت AVDictionaryEntry *t = عدم;
    AVDictionary    *tmp = عدم;
    صحيح ret;

    𐤀𐤌 (!options)
        أرجع 0;

    طالما ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->key, t->value, search_flags);
        𐤀𐤌 (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->key, t->value, AV_DICT_MULTIKEY);
        𐤀𐤌 (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->key, t->value);
            av_dict_free(&tmp);
            أرجع ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    أرجع 0;
}

صحيح av_opt_set_dict(فراغ *obj, AVDictionary **options)
{
    أرجع av_opt_set_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_find(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحيح opt_flags, صحيح search_flags)
{
    أرجع av_opt_find2(obj, name, unit, opt_flags, search_flags, عدم);
}

ثابت AVOption *av_opt_find2(فراغ *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحيح opt_flags, صحيح search_flags, فراغ **target_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = عدم;

    𐤀𐤌(!obj)
        أرجع عدم;

    c= *(AVClass**)obj;

    𐤀𐤌 (!c)
        أرجع عدم;

    𐤀𐤌 (search_flags & AV_OPT_SEARCH_CHILDREN) {
        𐤀𐤌 (search_flags & AV_OPT_SEARCH_FAKE_OBJ) {
            فراغ *iter = عدم;
            ثابت AVClass *child;
            طالما (child = av_opt_child_class_iterate(c, &iter))
                𐤀𐤌 (o = av_opt_find2(&child, name, unit, opt_flags, search_flags, عدم))
                    أرجع o;
        } وإلا {
            فراغ *child = عدم;
            طالما (child = av_opt_child_next(obj, child))
                𐤀𐤌 (o = av_opt_find2(child, name, unit, opt_flags, search_flags, target_obj))
                    أرجع o;
        }
    }

    طالما (o = av_opt_next(obj, o)) {
        𐤀𐤌 (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            𐤀𐤌 (target_obj) {
                𐤀𐤌 (!(search_flags & AV_OPT_SEARCH_FAKE_OBJ))
                    *target_obj = obj;
                وإلا
                    *target_obj = عدم;
            }
            أرجع o;
        }
    }
    أرجع عدم;
}

فراغ *av_opt_child_next(فراغ *obj, فراغ *prev)
{
    ثابت AVClass *c = *(AVClass **)obj;
    𐤀𐤌 (c->child_next)
        أرجع c->child_next(obj, prev);
    أرجع عدم;
}

ثابت AVClass *av_opt_child_class_iterate(ثابت AVClass *parent, فراغ **iter)
{
    𐤀𐤌 (parent->child_class_iterate)
        أرجع parent->child_class_iterate(iter);
    أرجع عدم;
}

ساكن صحيح opt_copy_elem(فراغ *logctx, تعداد AVOptionType type,
                         فراغ *dst, ثابت فراغ *src)
{
    𐤀𐤌 (type == AV_OPT_TYPE_STRING) {
        ثابت حرف *src_str = *(ثابت حرف *ثابت *)src;
        حرف         **dstp =  (حرف **)dst;
        𐤀𐤌 (*dstp != src_str)
            av_freep(dstp);
        𐤀𐤌 (src_str) {
            *dstp = av_strdup(src_str);
            𐤀𐤌 (!*dstp)
                أرجع AVERROR(ENOMEM);
        }
    } وإلا 𐤀𐤌 (type == AV_OPT_TYPE_BINARY) {
        ثابت uint8_t *ثابت *src8 = (ثابت uint8_t *ثابت *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        صحيح len = *(ثابت صحيح *)(src8 + 1);
        𐤀𐤌 (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        𐤀𐤌 (len && !*dst8) {
            *(صحيح *)(dst8 + 1) = 0;
            أرجع AVERROR(ENOMEM);
        }
        *(صحيح *)(dst8 + 1) = len;
    } وإلا 𐤀𐤌 (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } وإلا 𐤀𐤌 (type == AV_OPT_TYPE_DICT) {
        ثابت AVDictionary *sdict = *(ثابت AVDictionary * ثابت *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        𐤀𐤌 (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = عدم;
        أرجع av_dict_copy(ddictp, sdict, 0);
    } وإلا 𐤀𐤌 (type == AV_OPT_TYPE_CHLAYOUT) {
        ثابت AVChannelLayout *slayout = (ثابت AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        𐤀𐤌 (dlayout != slayout) {
            𐤀𐤌 (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = عدم;
            أرجع av_channel_layout_copy(dst, src);
        }
    } وإلا 𐤀𐤌 (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } وإلا {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        أرجع AVERROR(EINVAL);
    }

    أرجع 0;
}

ساكن صحيح opt_copy_array(فراغ *logctx, ثابت AVOption *o,
                          فراغ **pdst, ثابت فراغ * ثابت *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    فراغ         *dst = عدم;
    صحيح ret;

    𐤀𐤌 (*pdst == *psrc) {
        *pdst                   = عدم;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    𐤀𐤌 (!dst)
        أرجع AVERROR(ENOMEM);

    لكل (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(فراغ**)psrc, i));
        𐤀𐤌 (ret < 0) {
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

    𐤀𐤌 (!src)
        أرجع AVERROR(EINVAL);

    c = *(AVClass **)src;
    𐤀𐤌 (!c || c != *(AVClass **)dst)
        أرجع AVERROR(EINVAL);

    طالما ((o = av_opt_next(src, o))) {
        فراغ *field_dst = (uint8_t *)dst + o->offset;
        فراغ *field_src = (uint8_t *)src + o->offset;

        صحيح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        𐤀𐤌 (err < 0)
            ret = err;
    }
    أرجع ret;
}

صحيح av_opt_get_array_size(فراغ *obj, ثابت حرف *name, صحيح search_flags,
                          unsigned صحيح *out_val)
{
    فراغ *target_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, عدم, 0, search_flags, &target_obj);
    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    أرجع 0;
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
    𐤀𐤌 (!o || !target_obj)
        أرجع AVERROR_OPTION_NOT_FOUND;
    𐤀𐤌 (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    𐤀𐤌 (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        أرجع AVERROR(EINVAL);

    لكل (unsigned i = 0; i < nb_elems; i++) {
        ثابت فراغ *src = opt_array_pelem(o, *(فراغ**)parray, start_elem + i);
        فراغ       *dst = (uint8_t*)out_val + i * elem_size_out;

        𐤀𐤌 (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            𐤀𐤌 (ret < 0)
                اذهب fail;
        } وإلا 𐤀𐤌 (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, حجم(buf), src, search_flags);
            𐤀𐤌 (ret < 0)
                اذهب fail;

            𐤀𐤌 (out == buf) {
                out = av_strdup(buf);
                𐤀𐤌 (!out) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
            }

            *(uint8_t**)dst = out;
        } وإلا 𐤀𐤌 (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            مزدوج     num = 1.0;
            صحيح        den = 1;
            int64_t intnum = 1;

            ret = read_number(o, src, &num, &den, &intnum);
            𐤀𐤌 (ret < 0)
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
        } وإلا
            أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
fail:
    لكل (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    أرجع ret;
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
    𐤀𐤌 (ret < 0)
        أرجع ret;

    𐤀𐤌 (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        أرجع AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    𐤀𐤌 (start_elem > *array_size)
        أرجع AVERROR(EINVAL);

    // compute new array size
    𐤀𐤌 (!val) {
        𐤀𐤌 (*array_size - start_elem < nb_elems)
            أرجع AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } وإلا 𐤀𐤌 (search_flags & AV_OPT_ARRAY_REPLACE) {
        𐤀𐤌 (start_elem >= UINT_MAX - nb_elems)
            أرجع AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } وإلا {
        𐤀𐤌 (nb_elems >= UINT_MAX - *array_size)
            أرجع AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    𐤀𐤌 (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        أرجع AVERROR(EINVAL);

    // desired operation is shrinking the array
    𐤀𐤌 (!val) {
        فراغ *array = *(فراغ**)parray;

        لكل (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        𐤀𐤌 (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            𐤀𐤌 (!array)
                أرجع AVERROR(ENOMEM);

            *(فراغ**)parray = array;
        } وإلا
            av_freep(parray);

        *array_size = new_size;

        أرجع 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    𐤀𐤌 (!new_elems)
        أرجع AVERROR(ENOMEM);

    // convert/validate each new element
    لكل (unsigned i = 0; i < nb_elems; i++) {
        فراغ       *dst = opt_array_pelem(o, new_elems, i);
        ثابت فراغ *src = (uint8_t*)val + i * elem_size_val;

        مزدوج     num = 1.0;
        صحيح        den = 1;
        int64_t intnum = 1;

        𐤀𐤌 (val_type == TYPE_BASE(o->type)) {
            صحيح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            𐤀𐤌 (ret < 0)
                اذهب fail;

            // validate the range for numeric options
            err = read_number(o, dst, &num, &den, &intnum);
            𐤀𐤌 (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < num * intnum || o->min * den > num * intnum)) {
                num = den ? num * intnum / den : (num && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, num, o->min, o->max);
                ret = AVERROR(ERANGE);
                اذهب fail;
            }
        } وإلا 𐤀𐤌 (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(ثابت حرف **)src, dst);
            𐤀𐤌 (ret < 0)
                اذهب fail;
        } وإلا 𐤀𐤌 (val_type == AV_OPT_TYPE_INT ||
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
            𐤀𐤌 (ret < 0)
                اذهب fail;
        } وإلا {
            ret = AVERROR(ENOSYS);
            اذهب fail;
        }
    }

    // commit new elements to the array
    𐤀𐤌 (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(فراغ**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = عدم;
        nb_elems  = 0;
    } وإلا {
        فراغ *array = av_realloc_array(*(فراغ**)parray, new_size, elem_size);
        𐤀𐤌 (!array) {
            ret = AVERROR(ENOMEM);
            اذهب fail;
        }

        𐤀𐤌 (search_flags & AV_OPT_ARRAY_REPLACE) {
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

    أرجع ret;
}

صحيح av_opt_query_ranges(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *key, صحيح flags)
{
    صحيح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحيح (*callback)(AVOptionRanges **, فراغ *obj, ثابت حرف *key, صحيح flags) = c->query_ranges;

    𐤀𐤌 (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, key, flags);
    𐤀𐤌 (ret >= 0) {
        𐤀𐤌 (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    أرجع ret;
}

صحيح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, فراغ *obj, ثابت حرف *key, صحيح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(فراغ*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *field = av_opt_find(obj, key, عدم, 0, flags);
    صحيح ret;

    *ranges_arg = عدم;

    𐤀𐤌 (!ranges || !range || !range_array || !field) {
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

    𐤀𐤌 (!ranges)
        أرجع;

    لكل (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        𐤀𐤌 (range) {
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

    𐤀𐤌 (!o || !obj)
        أرجع AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    𐤀𐤌 (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت حرف *def = o->default_val.arr ? o->default_val.arr->def : عدم;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        𐤀𐤌 (ret < 0)
            أرجع ret;

        𐤀𐤌 (!!val != !!def)
            ret = 0;
        وإلا 𐤀𐤌 (val)
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
        read_number(o, dst, عدم, عدم, &i64);
        أرجع o->default_val.i64 == i64;
    حالة AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        𐤀𐤌 (o->default_val.str) {
            𐤀𐤌 ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                أرجع ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        أرجع ret;
    }
    حالة AV_OPT_TYPE_STRING:
        str = *(حرف **)dst;
        𐤀𐤌 (str == o->default_val.str) //2 NULLs
            أرجع 1;
        𐤀𐤌 (!str || !o->default_val.str) //1 NULL
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
        q = av_d2q(o->default_val.dbl, INT_MAX);
        أرجع !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالة AV_OPT_TYPE_BINARY: {
        بنية {
            uint8_t *data;
            صحيح size;
        } tmp = {0};
        صحيح opt_size = *(صحيح *)((فراغ **)dst + 1);
        فراغ *opt_ptr = *(فراغ **)dst;
        𐤀𐤌 (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            أرجع 1;
        𐤀𐤌 (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            أرجع 0;
        𐤀𐤌 (opt_size != strlen(o->default_val.str) / 2)
            أرجع 0;
        ret = set_string_binary(عدم, عدم, o->default_val.str, &tmp.data);
        𐤀𐤌 (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        أرجع ret;
    }
    حالة AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = عدم;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionaryEntry *en1 = عدم;
        ثابت AVDictionaryEntry *en2 = عدم;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        𐤀𐤌 (ret < 0) {
            av_dict_free(&dict1);
            أرجع ret;
        }
        𐤐𐤏𐤋 {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } طالما (en1 && en2 && !strcmp(en1->key, en2->key) && !strcmp(en1->value, en2->value));
        av_dict_free(&dict1);
        أرجع (!en1 && !en2);
    }
    حالة AV_OPT_TYPE_IMAGE_SIZE:
        𐤀𐤌 (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        وإلا 𐤀𐤌 ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            أرجع ret;
        أرجع (w == *(صحيح *)dst) && (h == *((صحيح *)dst+1));
    حالة AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        𐤀𐤌 (o->default_val.str) {
            𐤀𐤌 ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                أرجع ret;
        }
        أرجع !av_cmp_q(*(AVRational*)dst, q);
    حالة AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        𐤀𐤌 (o->default_val.str) {
            𐤀𐤌 ((ret = av_parse_color(color, o->default_val.str, -1, عدم)) < 0)
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

صحيح av_opt_is_set_to_default_by_name(فراغ *obj, ثابت حرف *name, صحيح search_flags)
{
    ثابت AVOption *o;
    فراغ *target;
    𐤀𐤌 (!obj)
        أرجع AVERROR(EINVAL);
    o = av_opt_find2(obj, name, عدم, 0, search_flags, &target);
    𐤀𐤌 (!o)
        أرجع AVERROR_OPTION_NOT_FOUND;
    أرجع av_opt_is_set_to_default(target, o);
}

ساكن صحيح opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, صحيح *cnt,
                         AVBPrint *bprint, ثابت حرف key_val_sep, ثابت حرف pairs_sep)
{
    ثابت AVOption *o = عدم;
    فراغ *child = عدم;
    uint8_t *buf;
    صحيح ret;
    ثابت حرف special_chars[] = {pairs_sep, key_val_sep, '\0'};

    𐤀𐤌 (flags & AV_OPT_SERIALIZE_SEARCH_CHILDREN)
        طالما (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                key_val_sep, pairs_sep);
            𐤀𐤌 (ret < 0)
                أرجع ret;
        }

    طالما (o = av_opt_next(obj, o)) {
        𐤀𐤌 (o->type == AV_OPT_TYPE_CONST)
            استمر;
        𐤀𐤌 ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            𐤀𐤌 ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                𐤀𐤌 (o->flags == opt_flags)
                    استمر;
            } وإلا 𐤀𐤌 ((o->flags & opt_flags) == opt_flags)
                استمر;
        } وإلا {
            𐤀𐤌 ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                استمر;
            وإلا 𐤀𐤌 (((o->flags & opt_flags) != opt_flags))
                استمر;
        }
        𐤀𐤌 (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            استمر;
        𐤀𐤌 ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, عدم);
            أرجع ret;
        }
        𐤀𐤌 (buf) {
            𐤀𐤌 ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &key_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    أرجع 0;
}

صحيح av_opt_serialize(فراغ *obj, صحيح opt_flags, صحيح flags, حرف **buffer,
                     ثابت حرف key_val_sep, ثابت حرف pairs_sep)
{
    AVBPrint bprint;
    صحيح ret, cnt = 0;

    𐤀𐤌 (pairs_sep == '\0' || key_val_sep == '\0' || pairs_sep == key_val_sep ||
        pairs_sep == '\\' || key_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        أرجع AVERROR(EINVAL);
    }

    𐤀𐤌 (!obj || !buffer)
        أرجع AVERROR(EINVAL);

    *buffer = عدم;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        key_val_sep, pairs_sep);
    𐤀𐤌 (ret < 0)
        أرجع ret;

    ret = av_bprint_finalize(&bprint, buffer);
    𐤀𐤌 (ret < 0)
        أرجع ret;
    أرجع 0;
}
