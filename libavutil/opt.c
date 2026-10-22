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

#تعریف_کرو TYPE_بنیاد(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

ثابت AVOption *av_opt_اگلا(ثابت خالی *obj, ثابت AVOption *آخری)
{
    ثابت AVClass *class;
    اگر (!obj)
        واپس تہی;
    class = *(ثابت AVClass**)obj;
    اگر (!آخری && class && class->option && class->option[0].name)
        واپس class->option;
    اگر (آخری && آخری[1].name)
        واپس ++آخری;
    واپس تہی;
}

ساکن ثابت ساخت {
    size_t      سائز;
    ثابت حرف *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { حجم(غیرعلامتی),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { حجم(صحیح),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { حجم(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { حجم(غیرعلامتی),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { حجم(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { حجم(دوہرا),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { حجم(اعشاری),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { حجم(حرف *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { حجم(AVRational),     "<rational>" },
    [AV_OPT_TYPE_ثنائی]        = { حجم(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { حجم(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_سائز]    = { حجم(صحیح[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_شرح]    = { حجم(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { حجم(شمار AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { حجم(شمار AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { حجم(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { حجم(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { حجم(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { حجم(صحیح),            "<boolean>" },
};

// option is plain old data
ساکن صحیح opt_is_pod(شمار AVOptionType type)
{
    انتخاب (type) {
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_FLOAT:
    حالت AV_OPT_TYPE_RATIONAL:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_IMAGE_سائز:
    حالت AV_OPT_TYPE_PIXEL_FMT:
    حالت AV_OPT_TYPE_SAMPLE_FMT:
    حالت AV_OPT_TYPE_VIDEO_شرح:
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_COLOR:
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_UINT:
        واپس 1;
    }
    واپس 0;
}

ساکن uint8_t opt_array_sep(ثابت AVOption *o)
{
    ثابت AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    واپس (d && d->sep) ? d->sep : ',';
}

ساکن خالی *opt_array_pelem(ثابت AVOption *o, خالی *array, غیرعلامتی idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    واپس (uint8_t *)array + idx * opt_type_desc[TYPE_بنیاد(o->type)].سائز;
}

ساکن غیرعلامتی *opt_array_pcount(ثابت خالی *parray)
{
    واپس (غیرعلامتی *)((ثابت خالی * ثابت *)parray + 1);
}

ساکن خالی opt_free_elem(شمار AVOptionType type, خالی *ptr)
{
    انتخاب (TYPE_بنیاد(type)) {
    حالت AV_OPT_TYPE_STRING:
    حالت AV_OPT_TYPE_ثنائی:
        av_freep(ptr);
        توڑو;

    حالت AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        توڑو;

    حالت AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        توڑو;

    طےشدہ:
        توڑو;
    }
}

ساکن خالی opt_free_array(ثابت AVOption *o, خالی *parray, غیرعلامتی *گنتی)
{
    برائے (غیرعلامتی i = 0; i < *گنتی; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(خالی **)parray, i));

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
ساکن صحیح opt_سیٹ_init(خالی *obj, ثابت حرف *name, صحیح تلاش_flags,
                        صحیح require_type,
                        خالی **ptgt, ثابت AVOption **po, خالی **pdst)
{
    خالی *logctx;
    ثابت AVOption *o;
    خالی *tgt;

    o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &tgt);
    اگر (!o || (!tgt && !(تلاش_flags & AV_OPT_تلاش_FAKE_OBJ)))
        واپس AVERROR_OPTION_NOT_ملا;

    اگر (o->flags & AV_OPT_FLAG_READONLY)
        واپس AVERROR(EINVAL);

    logctx = tgt ? obj : تہی;

    اگر (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        واپس AVERROR(EINVAL);
    }

    اگر (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        غیرعلامتی *state_flags = تہی;
        ثابت AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(ثابت AVClass**)tgt;
        اگر (class->state_flags_انحراف)
            state_flags = (غیرعلامتی*)((uint8_t*)tgt + class->state_flags_انحراف);

        اگر (!state_flags && obj != tgt) {
            class = *(ثابت AVClass**)obj;
            اگر (class->state_flags_انحراف)
                state_flags = (غیرعلامتی*)((uint8_t*)obj + class->state_flags_انحراف);
        }

        اگر (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            واپس AVERROR(EINVAL);
        }
    }

    اگر (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    اگر (po)
        *po   = o;
    اگر (ptgt)
        *ptgt = tgt;
    اگر (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->انحراف : تہی;

    واپس 0;
}

ساکن AVRational double_مقصد_rational(دوہرا d)
{
     AVRational r = av_d2q(d, 1 << 24);
     اگر ((!r.عدد || !r.den) && d)
         r = av_d2q(d, زیادہ_سے_زیادہ_عدد);
     واپس r;
}

ساکن صحیح read_نمبر(ثابت AVOption *o, ثابت خالی *dst, دوہرا *عدد, صحیح *den, int64_t *intnum)
{
    انتخاب (TYPE_بنیاد(o->type)) {
    حالت AV_OPT_TYPE_FLAGS:
        *intnum = *(غیرعلامتی صحیح*)dst;
        واپس 0;
    حالت AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(شمار AVPixelFormat *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(شمار AVSampleFormat *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_INT:
        *intnum = *(صحیح *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_UINT:
        *intnum = *(غیرعلامتی صحیح *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_FLOAT:
        *عدد = *(اعشاری *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_DOUBLE:
        *عدد = *(دوہرا *)dst;
        واپس 0;
    حالت AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->عدد;
        *den    = ((AVRational *)dst)->den;
        واپس 0;
    حالت AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        واپس 0;
    }
    واپس AVERROR(EINVAL);
}

ساکن صحیح write_نمبر(خالی *obj, ثابت AVOption *o, خالی *dst,
                        دوہرا عدد, صحیح den, int64_t intnum,
                        صحیح ignore_range)
{
    خالی *logctx = dst ? obj : تہی;
    ثابت شمار AVOptionType type = TYPE_بنیاد(o->type);

    اگر (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < عدد * intnum || o->min * den > عدد * intnum)) {
        عدد = den ? عدد * intnum / den : (عدد && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               عدد, o->name, o->min, o->max);
        واپس AVERROR(ERANGE);
    }
    اگر (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        دوہرا d = عدد*intnum/den;
        اگر (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   عدد*intnum/den, o->name);
            واپس AVERROR(ERANGE);
        }
    }

    اگر (!dst)
        واپس 0;

    انتخاب (type) {
    حالت AV_OPT_TYPE_PIXEL_FMT:
        *(شمار AVPixelFormat *)dst = llrint(عدد / den) * intnum;
        توڑو;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        *(شمار AVSampleFormat *)dst = llrint(عدد / den) * intnum;
        توڑو;
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
        *(صحیح *)dst = llrint(عدد / den) * intnum;
        توڑو;
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_INT64:{
        دوہرا d = عدد / den;
        اگر (intnum == 1 && d == (دوہرا)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } ورنہ
            *(int64_t *)dst = llrint(d) * intnum;
        توڑو;}
    حالت AV_OPT_TYPE_UINT64:{
        دوہرا d = عدد / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        اگر (intnum == 1 && d == (دوہرا)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } ورنہ اگر (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } ورنہ {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        توڑو;}
    حالت AV_OPT_TYPE_FLOAT:
        *(اعشاری *)dst = عدد * intnum / den;
        توڑو;
    حالت AV_OPT_TYPE_DOUBLE:
        *(دوہرا    *)dst = عدد * intnum / den;
        توڑو;
    حالت AV_OPT_TYPE_RATIONAL:
    حالت AV_OPT_TYPE_VIDEO_شرح:
        اگر ((صحیح) عدد == عدد)
            *(AVRational *)dst = (AVRational) { عدد *intnum, den };
        ورنہ
            *(AVRational *)dst = double_مقصد_rational(عدد * intnum / den);
        توڑو;
    طےشدہ:
        واپس AVERROR(EINVAL);
    }
    واپس 0;
}

ساکن صحیح hexchar2int(حرف c) {
    اگر (c >= '0' && c <= '9')
        واپس c - '0';
    اگر (c >= 'a' && c <= 'f')
        واپس c - 'a' + 10;
    اگر (c >= 'A' && c <= 'F')
        واپس c - 'A' + 10;
    واپس -1;
}

ساکن صحیح سیٹ_string_ثنائی(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    صحیح *lendst;
    uint8_t *bin, *ptr;
    صحیح len;

    اگر (dst) {
        lendst = (صحیح *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    اگر (!val || !(len = لڑی_لمبائی(val)))
        واپس 0;

    اگر (len & 1)
        واپس AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    اگر (!ptr)
        واپس AVERROR(ENOMEM);
    جب (*val) {
        صحیح a = hexchar2int(*val++);
        صحیح b = hexchar2int(*val++);
        اگر (a < 0 || b < 0) {
            av_free(bin);
            واپس AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    اگر (dst) {
        *dst    = bin;
        *lendst = len;
    } ورنہ {
        av_free(bin);
    }

    واپس 0;
}

ساکن صحیح سیٹ_string(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    اگر (!dst)
        واپس 0;
    av_freep(dst);
    اگر (!val)
        واپس 0;
    *dst = av_strdup(val);
    واپس *dst ? 0 : AVERROR(ENOMEM);
}

#تعریف_کرو DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

ساکن صحیح سیٹ_string_نمبر(خالی *obj, خالی *ہدف_obj, ثابت AVOption *o, ثابت حرف *val, خالی *dst)
{
    خالی *logctx = dst ? obj : تہی;
    ثابت شمار AVOptionType type = TYPE_بنیاد(o->type);
    صحیح ret = 0;

    اگر (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_شرح) {
        صحیح عدد, den;
        حرف c;
        اگر (لڑی_سے_پڑھو(val, "%d%*1[:/]%d%c", &عدد, &den, &c) == 2) {
            اگر ((ret = write_نمبر(obj, o, dst, 1, den, عدد, 0)) >= 0)
                واپس ret;
            ret = 0;
        }
    }

    برائے (;;) {
        صحیح i = 0;
        حرف buf[256];
        صحیح cmd = 0;
        دوہرا d;
        int64_t intnum = 1;

        اگر (type == AV_OPT_TYPE_FLAGS) {
            اگر (*val == '+' || *val == '-')
                cmd = *(val++);
            برائے (; i < حجم(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            صحیح res;
            صحیح ci = 0;
            دوہرا const_اقدار[64];
            ثابت حرف * const_نام[64];
            صحیح تلاش_flags = (o->flags & AV_OPT_FLAG_بچہ_CONSTS) ? AV_OPT_تلاش_CHILDREN : 0;
            ثابت AVOption *o_named = av_opt_ڈھونڈو(ہدف_obj, i ? buf : val, o->unit, 0, تلاش_flags);
            اگر (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                اگر (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } ورنہ {
                اگر (o->unit) {
                    برائے (o_named = تہی; o_named = av_opt_اگلا(ہدف_obj, o_named); ) {
                        اگر (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            اگر (ci + 6 >= FF_ARRAY_ELEMS(const_اقدار)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                واپس AVERROR_PATCHWELCOME;
                            }
                            const_نام [ci  ] = o_named->name;
                            const_اقدار[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_نام [ci  ] = "default";
                const_اقدار[ci++] = DEFAULT_NUMVAL(o);
                const_نام [ci  ] = "max";
                const_اقدار[ci++] = o->max;
                const_نام [ci  ] = "min";
                const_اقدار[ci++] = o->min;
                const_نام [ci  ] = "none";
                const_اقدار[ci++] = 0;
                const_نام [ci  ] = "all";
                const_اقدار[ci++] = ~0;
                const_نام [ci] = تہی;
                const_اقدار[ci] = 0;

                res = av_اظہاریہ_parse_and_eval(&d, i ? buf : val, const_نام,
                                            const_اقدار, تہی, تہی, تہی, تہی, تہی, 0, obj);
                اگر (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    واپس res;
                }
            }
        }
        اگر (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(غیرعلامتی صحیح*)dst;
            اگر (cmd == '+')
                d = intnum | (int64_t)d;
            ورنہ اگر (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        اگر ((ret = write_نمبر(obj, o, dst, d, 1, 1, 0)) < 0)
            واپس ret;
        val += i;
        اگر (!i || !*val)
            واپس 0;
    }
}

ساکن صحیح سیٹ_string_image_سائز(خالی *obj, ثابت AVOption *o, ثابت حرف *val, صحیح *dst)
{
    خالی *logctx = dst ? obj : تہی;
    صحیح tmp[2];
    صحیح ret;

    اگر (!val || !strcmp(val, "none")) {
        اگر (dst) {
        dst[0] =
        dst[1] = 0;
        }
        واپس 0;
    }
    ret = av_parse_video_سائز(&tmp[0], &tmp[1], val);
    اگر (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        واپس ret;
    }
    اگر (dst)
        حافظہ_نقل(dst, tmp, حجم(tmp));
    واپس ret;
}

ساکن صحیح سیٹ_string_video_شرح(خالی *obj, ثابت AVOption *o, ثابت حرف *val, AVRational *dst)
{
    خالی *logctx = dst ? obj : تہی;
    AVRational tmp;
    صحیح ret = av_parse_video_شرح(&tmp, val);
    اگر (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    اگر (dst)
        *dst = tmp;
    واپس ret;
}

ساکن صحیح سیٹ_string_color(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    خالی *logctx = dst ? obj : تہی;
    صحیح ret;

    اگر (!val) {
        واپس 0;
    } ورنہ {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        اگر (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            واپس ret;
        }
        اگر (dst)
            حافظہ_نقل(dst, tmp, حجم(tmp));
        واپس ret;
    }
    واپس 0;
}

ساکن ثابت حرف *get_bool_name(صحیح val)
{
    اگر (val < 0)
        واپس "auto";
    واپس val ? "true" : "false";
}

ساکن صحیح سیٹ_string_bool(خالی *obj, ثابت AVOption *o, ثابت حرف *val, صحیح *dst)
{
    خالی *logctx = dst ? obj : تہی;
    صحیح n;

    اگر (!val)
        واپس 0;

    اگر (!strcmp(val, "auto")) {
        n = -1;
    } ورنہ اگر (av_مطابقت_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } ورنہ اگر (av_مطابقت_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } ورنہ {
        حرف *انتہا = تہی;
        n = strtol(val, &انتہا, 10);
        اگر (val + لڑی_لمبائی(val) != انتہا)
            جاؤ fail;
    }

    اگر (n < o->min || n > o->max)
        جاؤ fail;

    اگر (dst)
    *dst = n;
    واپس 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    واپس AVERROR(EINVAL);
}

ساکن صحیح سیٹ_string_fmt(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst,
                          صحیح fmt_nb, صحیح ((*get_fmt)(ثابت حرف *)), ثابت حرف *desc,
                          شمار AVOptionType type)
{
    خالی *logctx = dst ? obj : تہی;
    صحیح fmt, min, max;

    اگر (!val || !strcmp(val, "none")) {
        fmt = -1;
    } ورنہ {
        fmt = get_fmt(val);
        اگر (fmt == -1) {
            حرف *دم;
            fmt = strtol(val, &دم, 0);
            اگر (*دم || (غیرعلامتی)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                واپس AVERROR(EINVAL);
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
        واپس AVERROR(ERANGE);
    }

    اگر (dst)
    انتخاب (type) {
    حالت AV_OPT_TYPE_PIXEL_FMT:  *(شمار AVPixelFormat *)dst = fmt; توڑو;
    حالت AV_OPT_TYPE_SAMPLE_FMT: *(شمار AVSampleFormat*)dst = fmt; توڑو;
    طےشدہ: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    واپس 0;
}

ساکن صحیح get_pix_fmt(ثابت حرف *name)
{
    واپس av_get_pix_fmt(name);
}

ساکن صحیح سیٹ_string_pixel_fmt(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    واپس سیٹ_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

ساکن صحیح get_sample_fmt(ثابت حرف *name)
{
    واپس av_get_sample_fmt(name);
}

ساکن صحیح سیٹ_string_sample_fmt(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t *dst)
{
    واپس سیٹ_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

ساکن صحیح سیٹ_string_dict(خالی *obj, ثابت AVOption *o, ثابت حرف *val, uint8_t **dst)
{
    AVDictionary *options = تہی;

    اگر (val) {
        صحیح ret = av_dict_parse_string(&options, val, "=", ":", 0);
        اگر (ret < 0) {
            av_dict_free(&options);
            واپس ret;
        }
    }

    اگر (!dst) {
        av_dict_free(&options);
        واپس 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    واپس 0;
}

ساکن صحیح سیٹ_string_channel_layout(خالی *obj, ثابت AVOption *o,
                                     ثابت حرف *val, خالی *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    صحیح ret;
    اگر (dst)
    av_channel_layout_uninit(channel_layout);
    ورنہ
        channel_layout = &tmp;
    اگر (!val)
        واپس 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    اگر (ret < 0)
        واپس ret;
    اگر (!dst)
        av_channel_layout_uninit(channel_layout);
    واپس 0;
}

ساکن صحیح opt_سیٹ_elem(خالی *obj, خالی *ہدف_obj, ثابت AVOption *o,
                        ثابت حرف *val, خالی *dst)
{
    خالی *logctx = dst ? obj : تہی;
    ثابت شمار AVOptionType type = TYPE_بنیاد(o->type);
    صحیح ret;

    اگر (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_سائز &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        واپس AVERROR(EINVAL);

    انتخاب (type) {
    حالت AV_OPT_TYPE_BOOL:
        واپس سیٹ_string_bool(obj, o, val, dst);
    حالت AV_OPT_TYPE_STRING:
        واپس سیٹ_string(obj, o, val, dst);
    حالت AV_OPT_TYPE_ثنائی:
        واپس سیٹ_string_ثنائی(obj, o, val, dst);
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_FLOAT:
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_RATIONAL:
        واپس سیٹ_string_نمبر(obj, ہدف_obj, o, val, dst);
    حالت AV_OPT_TYPE_IMAGE_سائز:
        واپس سیٹ_string_image_سائز(obj, o, val, dst);
    حالت AV_OPT_TYPE_VIDEO_شرح: {
        AVRational tmp;
        ret = سیٹ_string_video_شرح(obj, o, val, &tmp);
        اگر (ret < 0)
            واپس ret;
        واپس write_نمبر(obj, o, dst, 1, tmp.den, tmp.عدد, 0);
    }
    حالت AV_OPT_TYPE_PIXEL_FMT:
        واپس سیٹ_string_pixel_fmt(obj, o, val, dst);
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        واپس سیٹ_string_sample_fmt(obj, o, val, dst);
    حالت AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            اگر (val) {
                اگر ((ret = av_parse_وقت(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    واپس ret;
                }
            }
            اگر (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                واپس AVERROR(ERANGE);
            }
            اگر (dst)
            *(int64_t *)dst = usecs;
            واپس 0;
        }
    حالت AV_OPT_TYPE_COLOR:
        واپس سیٹ_string_color(obj, o, val, dst);
    حالت AV_OPT_TYPE_CHLAYOUT:
        ret = سیٹ_string_channel_layout(obj, o, val, dst);
        اگر (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        واپس ret;
    حالت AV_OPT_TYPE_DICT:
        واپس سیٹ_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    واپس AVERROR(EINVAL);
}

ساکن صحیح opt_سیٹ_array(خالی *obj, خالی *ہدف_obj, ثابت AVOption *o,
                         ثابت حرف *val, خالی *dst)
{
    ثابت AVOptionArrayDef *arr = o->default_val.arr;
    ثابت size_t      elem_سائز = opt_type_desc[TYPE_بنیاد(o->type)].سائز;
    ثابت uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = تہی;

    خالی      *logctx = dst ? obj : تہی;
    خالی       *elems = تہی;
    غیرعلامتی nb_elems = 0;
    صحیح ret;

    اگر (val && *val) {
        str = av_malloc(لڑی_لمبائی(val) + 1);
        اگر (!str)
            واپس AVERROR(ENOMEM);
    }

    // split and unescape the string
    جب (val && *val) {
        uint8_t *p = str;
        خالی *tmp;

        اگر (arr && arr->سائز_max && nb_elems >= arr->سائز_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->سائز_max, o->name);
            ret = AVERROR(EINVAL);
            جاؤ fail;
        }

        برائے (; *val; val++, p++) {
            اگر (*val == '\\' && val[1])
                val++;
            ورنہ اگر (*val == sep) {
                val++;
                توڑو;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_سائز);
        اگر (!tmp) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_سائز);

        ret = opt_سیٹ_elem(obj, ہدف_obj, o, str, tmp);
        اگر (ret < 0)
            جاؤ fail;
        nb_elems++;
    }
    av_freep(&str);

    اگر (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    اگر (arr && nb_elems < arr->سائز_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->سائز_min, o->name);
        ret = AVERROR(EINVAL);
        جاؤ fail;
    }

    اگر (dst) {
    *((خالی **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } ورنہ
        opt_free_array(o, &elems, &nb_elems);

    واپس 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    واپس ret;
}

صحیح av_opt_سیٹ(خالی *obj, ثابت حرف *name, ثابت حرف *val, صحیح تلاش_flags)
{
    خالی *dst, *ہدف_obj;
    ثابت AVOption *o;
    صحیح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, 0, &ہدف_obj, &o, &dst);
    اگر (ret < 0)
        واپس ret;

    واپس ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_سیٹ_array : opt_سیٹ_elem)(obj, ہدف_obj, o, val, dst);
}

#تعریف_کرو OPT_EVAL_نمبر(name, opttype, vartype)                         \
صحیح av_opt_eval_ ## name(خالی *obj, ثابت AVOption *o,                  \
                         ثابت حرف *val, vartype *name ## برآمد_3)        \
{                                                                       \
    اگر (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        واپس AVERROR(EINVAL);                                         \
    واپس سیٹ_string_نمبر(obj, obj, o, val, name ## برآمد_3);           \
}

OPT_EVAL_نمبر(flags,  AV_OPT_TYPE_FLAGS,    صحیح)
OPT_EVAL_نمبر(صحیح,    AV_OPT_TYPE_INT,      صحیح)
OPT_EVAL_نمبر(uint,   AV_OPT_TYPE_UINT,     غیرعلامتی)
OPT_EVAL_نمبر(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_نمبر(اعشاری,  AV_OPT_TYPE_FLOAT,    اعشاری)
OPT_EVAL_نمبر(دوہرا, AV_OPT_TYPE_DOUBLE,   دوہرا)
OPT_EVAL_نمبر(q,      AV_OPT_TYPE_RATIONAL, AVRational)

ساکن صحیح سیٹ_نمبر(خالی *obj, ثابت حرف *name, دوہرا عدد, صحیح den, int64_t intnum,
                      صحیح تلاش_flags, صحیح require_type)
{
    خالی *dst;
    ثابت AVOption *o;
    صحیح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, require_type, تہی, &o, &dst);
    اگر (ret < 0)
        واپس ret;
    اگر (dst)
        ret = write_نمبر(obj, o, dst, عدد, den, intnum, 0);

    واپس ret;
}

صحیح av_opt_سیٹ_int(خالی *obj, ثابت حرف *name, int64_t val, صحیح تلاش_flags)
{
    واپس سیٹ_نمبر(obj, name, 1, 1, val, تلاش_flags, 0);
}

صحیح av_opt_سیٹ_double(خالی *obj, ثابت حرف *name, دوہرا val, صحیح تلاش_flags)
{
    واپس سیٹ_نمبر(obj, name, val, 1, 1, تلاش_flags, 0);
}

صحیح av_opt_سیٹ_q(خالی *obj, ثابت حرف *name, AVRational val, صحیح تلاش_flags)
{
    واپس سیٹ_نمبر(obj, name, val.عدد, val.den, 1, تلاش_flags, 0);
}

صحیح av_opt_سیٹ_bin(خالی *obj, ثابت حرف *name, ثابت uint8_t *val, صحیح len, صحیح تلاش_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    صحیح *lendst;
    صحیح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_ثنائی,
                       تہی, تہی, (خالی**)&dst);
    اگر (ret < 0)
        واپس ret;

    اگر (dst) {
    ptr = len ? av_malloc(len) : تہی;
    اگر (len && !ptr)
        واپس AVERROR(ENOMEM);

    lendst = (صحیح *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    اگر (len)
        حافظہ_نقل(ptr, val, len);
    }

    واپس 0;
}

صحیح av_opt_سیٹ_image_سائز(خالی *obj, ثابت حرف *name, صحیح w, صحیح h, صحیح تلاش_flags)
{
    ثابت AVOption *o;
    خالی *logctx;
    صحیح *dst;
    صحیح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_IMAGE_سائز,
                       تہی, &o, (خالی**)&dst);
    اگر (ret < 0)
        واپس ret;

    logctx = dst ? obj : تہی;

    اگر (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        واپس AVERROR(EINVAL);
    }

    اگر (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    واپس 0;
}

صحیح av_opt_سیٹ_video_شرح(خالی *obj, ثابت حرف *name, AVRational val, صحیح تلاش_flags)
{
    واپس سیٹ_نمبر(obj, name, val.عدد, val.den, 1, تلاش_flags, AV_OPT_TYPE_VIDEO_شرح);
}

ساکن صحیح سیٹ_format(خالی *obj, ثابت حرف *name, صحیح fmt, صحیح تلاش_flags,
                      شمار AVOptionType type, ثابت حرف *desc, صحیح nb_fmts)
{
    ثابت AVOption *o;
    خالی *logctx;
    صحیح *dst;
    صحیح min, max, ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, type, تہی, &o, (خالی**)&dst);
    اگر (ret < 0)
        واپس ret;

    logctx = dst ? obj : تہی;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    اگر (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        واپس AVERROR(ERANGE);
    }
    اگر (dst)
    *dst = fmt;
    واپس 0;
}

صحیح av_opt_سیٹ_pixel_fmt(خالی *obj, ثابت حرف *name, شمار AVPixelFormat fmt, صحیح تلاش_flags)
{
    واپس سیٹ_format(obj, name, fmt, تلاش_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

صحیح av_opt_سیٹ_sample_fmt(خالی *obj, ثابت حرف *name, شمار AVSampleFormat fmt, صحیح تلاش_flags)
{
    واپس سیٹ_format(obj, name, fmt, تلاش_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

صحیح av_opt_سیٹ_dict_val(خالی *obj, ثابت حرف *name, ثابت AVDictionary *val,
                        صحیح تلاش_flags)
{
    AVDictionary **dst;
    صحیح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_DICT, تہی, تہی,
                       (خالی**)&dst);
    اگر (ret < 0)
        واپس ret;

    اگر (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    واپس ret;
}

صحیح av_opt_سیٹ_chlayout(خالی *obj, ثابت حرف *name,
                        ثابت AVChannelLayout *channel_layout,
                        صحیح تلاش_flags)
{
    AVChannelLayout *dst;
    صحیح ret;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, AV_OPT_TYPE_CHLAYOUT, تہی, تہی,
                       (خالی**)&dst);
    اگر (ret < 0)
        واپس ret;

    اگر (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    واپس ret;
}

ساکن خالی format_duration(حرف *buf, size_t سائز, int64_t d)
{
    حرف *e;

    av_assert0(سائز >= 25);
    اگر (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        سائز--;
        d = -d;
    }
    اگر (d == INT64_MAX)
        snprintf(buf, سائز, "INT64_MAX");
    ورنہ اگر (d == INT64_MIN)
        snprintf(buf, سائز, "INT64_MIN");
    ورنہ اگر (d > (int64_t)3600*1000000)
        snprintf(buf, سائز, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (صحیح)((d / 60000000) % 60),
                 (صحیح)((d / 1000000) % 60),
                 (صحیح)(d % 1000000));
    ورنہ اگر (d > 60*1000000)
        snprintf(buf, سائز, "%d:%02d.%06d",
                 (صحیح)(d / 60000000),
                 (صحیح)((d / 1000000) % 60),
                 (صحیح)(d % 1000000));
    ورنہ
        snprintf(buf, سائز, "%d.%06d",
                 (صحیح)(d / 1000000),
                 (صحیح)(d % 1000000));
    e = buf + لڑی_لمبائی(buf);
    جب (e > buf && e[-1] == '0')
        *(--e) = 0;
    اگر (e > buf && e[-1] == '.')
        *(--e) = 0;
}

ساکن صحیح opt_get_elem(ثابت AVOption *o, uint8_t **pbuf, size_t buf_len,
                        ثابت خالی *dst, صحیح تلاش_flags)
{
    صحیح ret;

    انتخاب (TYPE_بنیاد(o->type)) {
    حالت AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(صحیح *)dst));
        توڑو;
    حالت AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(صحیح *)dst);
        توڑو;
    حالت AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(صحیح *)dst);
        توڑو;
    حالت AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(غیرعلامتی *)dst);
        توڑو;
    حالت AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        توڑو;
    حالت AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        توڑو;
    حالت AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(اعشاری *)dst);
        توڑو;
    حالت AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(دوہرا *)dst);
        توڑو;
    حالت AV_OPT_TYPE_VIDEO_شرح:
    حالت AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->عدد, ((AVRational *)dst)->den);
        توڑو;
    حالت AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        توڑو;
    حالت AV_OPT_TYPE_STRING:
        اگر (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } ورنہ اگر (تلاش_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = تہی;
            واپس 0;
        } ورنہ {
            *pbuf = av_strdup("");
        }
        واپس *pbuf ? 0 : AVERROR(ENOMEM);
    حالت AV_OPT_TYPE_ثنائی: {
        ثابت uint8_t *bin;
        صحیح len;

        اگر (!*(uint8_t **)dst && (تلاش_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = تہی;
            واپس 0;
        }
        len = *(صحیح *)(((uint8_t *)dst) + حجم(uint8_t *));
        اگر ((uint64_t)len * 2 + 1 > زیادہ_سے_زیادہ_عدد)
            واپس AVERROR(EINVAL);
        اگر (!(*pbuf = av_malloc(len * 2 + 1)))
            واپس AVERROR(ENOMEM);
        اگر (!len) {
            *pbuf[0] = '\0';
            واپس 0;
        }
        bin = *(uint8_t **)dst;
        برائے (صحیح i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        واپس 0;
    }
    حالت AV_OPT_TYPE_IMAGE_سائز:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((صحیح *)dst)[0], ((صحیح *)dst)[1]);
        توڑو;
    حالت AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(*(شمار AVPixelFormat *)dst), "none"));
        توڑو;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(*(شمار AVSampleFormat *)dst), "none"));
        توڑو;
    حالت AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = لڑی_لمبائی(*pbuf); // no overflow possible, checked by an assert
        توڑو;
    }
    حالت AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (صحیح)((uint8_t *)dst)[0], (صحیح)((uint8_t *)dst)[1],
                       (صحیح)((uint8_t *)dst)[2], (صحیح)((uint8_t *)dst)[3]);
        توڑو;
    حالت AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        توڑو;
    حالت AV_OPT_TYPE_DICT:
        اگر (!*(AVDictionary **)dst && (تلاش_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = تہی;
            واپس 0;
        }
        واپس av_dict_get_string(*(AVDictionary **)dst, (حرف **)pbuf, '=', ':');
    طےشدہ:
        واپس AVERROR(EINVAL);
    }

    واپس ret;
}

ساکن صحیح opt_get_array(ثابت AVOption *o, خالی *dst, uint8_t **برآمد_val)
{
    ثابت غیرعلامتی گنتی = *opt_array_pcount(dst);
    ثابت uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = تہی;
    size_t   str_len = 0;
    صحیح ret;

    *برآمد_val = تہی;

    برائے (غیرعلامتی i = 0; i < گنتی; i++) {
        uint8_t buf[128], *برآمد = buf;
        size_t برآمد_len;

        ret = opt_get_elem(o, &برآمد, حجم(buf),
                           opt_array_pelem(o, *(خالی **)dst, i), 0);
        اگر (ret < 0)
            جاؤ fail;

        برآمد_len = لڑی_لمبائی(برآمد);
        اگر (برآمد_len > SIZE_MAX / 2 - !!i ||
            !!i + برآمد_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            جاؤ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + برآمد_len * 2 + !!i);
        اگر (ret < 0)
            جاؤ fail;

        // add separator if needed
        اگر (i)
            str[str_len++] = sep;

        // escape the element
        برائے (غیرعلامتی j = 0; j < برآمد_len; j++) {
            uint8_t val = برآمد[j];
            اگر (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        اگر (برآمد != buf)
            av_freep(&برآمد);
        اگر (ret < 0) {
            av_freep(&str);
            واپس ret;
        }
    }

    *برآمد_val = str;

    واپس 0;
}

صحیح av_opt_get(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, uint8_t **برآمد_val)
{
    خالی *dst, *ہدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    uint8_t *برآمد, buf[128];
    صحیح ret;

    اگر (!o || !ہدف_obj || (o->انحراف<=0 && o->type != AV_OPT_TYPE_CONST))
        واپس AVERROR_OPTION_NOT_ملا;

    اگر (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)ہدف_obj + o->انحراف;

    اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, برآمد_val);
        اگر (ret < 0)
            واپس ret;
        اگر (!*برآمد_val && !(تلاش_flags & AV_OPT_ALLOW_NULL)) {
            *برآمد_val = av_strdup("");
            اگر (!*برآمد_val)
               واپس AVERROR(ENOMEM);
        }
        واپس 0;
    }

    buf[0] = 0;
    برآمد = buf;
    ret = opt_get_elem(o, &برآمد, حجم(buf), dst, تلاش_flags);
    اگر (ret < 0)
        واپس ret;
    اگر (برآمد != buf) {
        *برآمد_val = برآمد;
        واپس 0;
    }

    اگر (ret >= حجم(buf))
        واپس AVERROR(EINVAL);
    *برآمد_val = av_strdup(برآمد);
    واپس *برآمد_val ? 0 : AVERROR(ENOMEM);
}

ساکن صحیح get_نمبر(خالی *obj, ثابت حرف *name, دوہرا *عدد, صحیح *den, int64_t *intnum,
                      صحیح تلاش_flags)
{
    خالی *dst, *ہدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        واپس AVERROR(EINVAL);

    dst = ((uint8_t *)ہدف_obj) + o->انحراف;

    واپس read_نمبر(o, dst, عدد, den, intnum);
}

صحیح av_opt_get_int(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, int64_t *برآمد_val)
{
    int64_t intnum = 1;
    دوہرا عدد = 1;
    صحیح ret, den = 1;

    اگر ((ret = get_نمبر(obj, name, &عدد, &den, &intnum, تلاش_flags)) < 0)
        واپس ret;
    اگر (عدد == den)
        *برآمد_val = intnum;
    ورنہ
        *برآمد_val = عدد * intnum / den;
    واپس 0;
}

صحیح av_opt_get_double(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, دوہرا *برآمد_val)
{
    int64_t intnum = 1;
    دوہرا عدد = 1;
    صحیح ret, den = 1;

    اگر ((ret = get_نمبر(obj, name, &عدد, &den, &intnum, تلاش_flags)) < 0)
        واپس ret;
    *برآمد_val = عدد * intnum / den;
    واپس 0;
}

صحیح av_opt_get_q(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, AVRational *برآمد_val)
{
    int64_t intnum = 1;
    دوہرا عدد = 1;
    صحیح ret, den = 1;

    اگر ((ret = get_نمبر(obj, name, &عدد, &den, &intnum, تلاش_flags)) < 0)
        واپس ret;

    اگر (عدد == 1.0 && (صحیح)intnum == intnum)
        *برآمد_val = (AVRational){intnum, den};
    ورنہ
        *برآمد_val = double_مقصد_rational(عدد*intnum/den);
    واپس 0;
}

صحیح av_opt_get_image_سائز(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, صحیح *w_برآمد, صحیح *h_برآمد)
{
    خالی *dst, *ہدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (o->type != AV_OPT_TYPE_IMAGE_سائز) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        واپس AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ہدف_obj) + o->انحراف;
    اگر (w_برآمد) *w_برآمد = *(صحیح *)dst;
    اگر (h_برآمد) *h_برآمد = *((صحیح *)dst+1);
    واپس 0;
}

صحیح av_opt_get_video_شرح(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, AVRational *برآمد_val)
{
    واپس av_opt_get_q(obj, name, تلاش_flags, برآمد_val);
}

ساکن صحیح get_format(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, خالی *برآمد_fmt,
                      شمار AVOptionType type, ثابت حرف *desc)
{
    خالی *dst, *ہدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        واپس AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ہدف_obj) + o->انحراف;
    اگر (type == AV_OPT_TYPE_PIXEL_FMT)
        *(شمار AVPixelFormat *)برآمد_fmt = *(شمار AVPixelFormat *)dst;
    ورنہ
        *(شمار AVSampleFormat*)برآمد_fmt = *(شمار AVSampleFormat*)dst;

    واپس 0;
}

صحیح av_opt_get_pixel_fmt(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, شمار AVPixelFormat *برآمد_fmt)
{
    واپس get_format(obj, name, تلاش_flags, برآمد_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

صحیح av_opt_get_sample_fmt(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, شمار AVSampleFormat *برآمد_fmt)
{
    واپس get_format(obj, name, تلاش_flags, برآمد_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

صحیح av_opt_get_chlayout(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, AVChannelLayout *cl)
{
    خالی *dst, *ہدف_obj;
    ثابت AVOption *o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        واپس AVERROR(EINVAL);
    }

    dst = ((uint8_t*)ہدف_obj) + o->انحراف;
    واپس av_channel_layout_copy(cl, dst);
}

صحیح av_opt_get_dict_val(خالی *obj, ثابت حرف *name, صحیح تلاش_flags, AVDictionary **برآمد_val)
{
    خالی *ہدف_obj;
    AVDictionary *src;
    ثابت AVOption *o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);

    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (o->type != AV_OPT_TYPE_DICT)
        واپس AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)ہدف_obj) + o->انحراف);

    واپس av_dict_copy(برآمد_val, src, 0);
}

صحیح av_opt_flag_is_سیٹ(خالی *obj, ثابت حرف *میدان_name, ثابت حرف *flag_name)
{
    ثابت AVOption *میدان = av_opt_ڈھونڈو(obj, میدان_name, تہی, 0, 0);
    ثابت AVOption *flag  = av_opt_ڈھونڈو(obj, flag_name,
                                        میدان ? میدان->unit : تہی, 0, 0);
    int64_t res;

    اگر (!میدان || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, میدان_name, 0, &res) < 0)
        واپس 0;
    واپس res & flag->default_val.i64;
}

ساکن خالی log_int_قدر(خالی *av_log_obj, صحیح level, int64_t i)
{
    اگر (i == زیادہ_سے_زیادہ_عدد) {
        av_log(av_log_obj, level, "INT_MAX");
    } ورنہ اگر (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ورنہ اگر (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ورنہ اگر (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ورنہ اگر (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ورنہ {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

ساکن خالی log_قدر(خالی *av_log_obj, صحیح level, دوہرا d)
{
    اگر      (d == زیادہ_سے_زیادہ_عدد) {
        av_log(av_log_obj, level, "INT_MAX");
    } ورنہ اگر (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } ورنہ اگر (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } ورنہ اگر (d == (دوہرا)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } ورنہ اگر (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } ورنہ اگر (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } ورنہ اگر (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } ورنہ اگر (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } ورنہ اگر (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } ورنہ اگر (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } ورنہ اگر (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } ورنہ اگر (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } ورنہ اگر (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } ورنہ {
        av_log(av_log_obj, level, "%g", d);
    }
}

ساکن ثابت حرف *get_opt_const_name(خالی *obj, ثابت حرف *unit, int64_t قدر)
{
    ثابت AVOption *opt = تہی;

    اگر (!unit)
        واپس تہی;
    جب ((opt = av_opt_اگلا(obj, opt)))
        اگر (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == قدر)
            واپس opt->name;
    واپس تہی;
}

ساکن حرف *get_opt_flags_string(خالی *obj, ثابت حرف *unit, int64_t قدر)
{
    ثابت AVOption *opt = تہی;
    حرف flags[512];

    flags[0] = 0;
    اگر (!unit)
        واپس تہی;
    جب ((opt = av_opt_اگلا(obj, opt))) {
        اگر (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & قدر) {
            اگر (flags[0])
                av_strlcatf(flags, حجم(flags), "+");
            av_strlcatf(flags, حجم(flags), "%s", opt->name);
        }
    }
    اگر (flags[0])
        واپس av_strdup(flags);
    واپس تہی;
}

ساکن خالی log_type(خالی *av_log_obj, ثابت AVOption *o,
                     شمار AVOptionType والد_type)
{
    ثابت شمار AVOptionType type = TYPE_بنیاد(o->type);

    اگر (o->type == AV_OPT_TYPE_CONST && (TYPE_بنیاد(والد_type) == AV_OPT_TYPE_INT || TYPE_بنیاد(والد_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    ورنہ اگر (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        ورنہ
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    ورنہ
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

ساکن خالی log_default(خالی *obj, خالی *av_log_obj, ثابت AVOption *opt)
{
    اگر (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_ثنائی)
        واپس;
    اگر ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_سائز ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_شرح) &&
        !opt->default_val.str)
        واپس;

    اگر (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت AVOptionArrayDef *arr = opt->default_val.arr;
        اگر (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        واپس;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    انتخاب (opt->type) {
    حالت AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        توڑو;
    حالت AV_OPT_TYPE_FLAGS: {
        حرف *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        اگر (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } ورنہ {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        توڑو;
    }
    حالت AV_OPT_TYPE_DURATION: {
        حرف buf[25];
        format_duration(buf, حجم(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        توڑو;
    }
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT64:
    حالت AV_OPT_TYPE_INT64: {
        ثابت حرف *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        اگر (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        ورنہ
            log_int_قدر(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        توڑو;
    }
    حالت AV_OPT_TYPE_DOUBLE:
    حالت AV_OPT_TYPE_FLOAT:
        log_قدر(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        توڑو;
    حالت AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, زیادہ_سے_زیادہ_عدد);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.عدد, q.den); }
        توڑو;
    حالت AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        توڑو;
    حالت AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (حرف *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        توڑو;
    حالت AV_OPT_TYPE_COLOR:
    حالت AV_OPT_TYPE_IMAGE_سائز:
    حالت AV_OPT_TYPE_STRING:
    حالت AV_OPT_TYPE_DICT:
    حالت AV_OPT_TYPE_VIDEO_شرح:
    حالت AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        توڑو;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

ساکن خالی opt_list(خالی *obj, خالی *av_log_obj, ثابت حرف *unit,
                     صحیح req_flags, صحیح rej_flags, شمار AVOptionType والد_type)
{
    ثابت AVOption *opt = تہی;
    AVOptionRanges *r;
    صحیح i;

    جب ((opt = av_opt_اگلا(obj, opt))) {
        اگر (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            جاری;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        اگر (!unit && opt->type == AV_OPT_TYPE_CONST)
            جاری;
        ورنہ اگر (unit && opt->type != AV_OPT_TYPE_CONST)
            جاری;
        ورنہ اگر (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            جاری;
        ورنہ اگر (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        ورنہ
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

        اگر (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        اگر (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_تلاش_FAKE_OBJ) >= 0) {
            انتخاب (opt->type) {
            حالت AV_OPT_TYPE_INT:
            حالت AV_OPT_TYPE_UINT:
            حالت AV_OPT_TYPE_INT64:
            حالت AV_OPT_TYPE_UINT64:
            حالت AV_OPT_TYPE_DOUBLE:
            حالت AV_OPT_TYPE_FLOAT:
            حالت AV_OPT_TYPE_RATIONAL:
                برائے (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_قدر(av_log_obj, AV_LOG_INFO, r->range[i]->قدر_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_قدر(av_log_obj, AV_LOG_INFO, r->range[i]->قدر_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                توڑو;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        اگر (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

صحیح av_opt_show2(خالی *obj, خالی *av_log_obj, صحیح req_flags, صحیح rej_flags)
{
    اگر (!obj)
        واپس -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, تہی, req_flags, rej_flags, -1);

    واپس 0;
}

خالی av_opt_سیٹ_defaults(خالی *s)
{
    av_opt_سیٹ_defaults2(s, 0, 0);
}

خالی av_opt_سیٹ_defaults2(خالی *s, صحیح نقاب_2, صحیح flags)
{
    ثابت AVOption *opt = تہی;
    جب ((opt = av_opt_اگلا(s, opt))) {
        خالی *dst = ((uint8_t*)s) + opt->انحراف;

        اگر ((opt->flags & نقاب_2) != flags)
            جاری;

        اگر (opt->flags & AV_OPT_FLAG_READONLY)
            جاری;

        اگر (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            ثابت AVOptionArrayDef *arr = opt->default_val.arr;
            ثابت حرف              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            اگر (arr && arr->def)
                opt_سیٹ_array(s, s, opt, arr->def, dst);

            جاری;
        }

        انتخاب (opt->type) {
            حالت AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                توڑو;
            حالت AV_OPT_TYPE_BOOL:
            حالت AV_OPT_TYPE_FLAGS:
            حالت AV_OPT_TYPE_INT:
            حالت AV_OPT_TYPE_UINT:
            حالت AV_OPT_TYPE_INT64:
            حالت AV_OPT_TYPE_UINT64:
            حالت AV_OPT_TYPE_DURATION:
            حالت AV_OPT_TYPE_PIXEL_FMT:
            حالت AV_OPT_TYPE_SAMPLE_FMT:
                write_نمبر(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                توڑو;
            حالت AV_OPT_TYPE_DOUBLE:
            حالت AV_OPT_TYPE_FLOAT: {
                دوہرا val;
                val = opt->default_val.dbl;
                write_نمبر(s, opt, dst, val, 1, 1, 1);
            }
            توڑو;
            حالت AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, زیادہ_سے_زیادہ_عدد);
                write_نمبر(s, opt, dst, 1, val.den, val.عدد, 1);
            }
            توڑو;
            حالت AV_OPT_TYPE_COLOR:
                سیٹ_string_color(s, opt, opt->default_val.str, dst);
                توڑو;
            حالت AV_OPT_TYPE_STRING:
                سیٹ_string(s, opt, opt->default_val.str, dst);
                توڑو;
            حالت AV_OPT_TYPE_IMAGE_سائز:
                سیٹ_string_image_سائز(s, opt, opt->default_val.str, dst);
                توڑو;
            حالت AV_OPT_TYPE_VIDEO_شرح:
                سیٹ_string_video_شرح(s, opt, opt->default_val.str, dst);
                توڑو;
            حالت AV_OPT_TYPE_ثنائی:
                سیٹ_string_ثنائی(s, opt, opt->default_val.str, dst);
                توڑو;
            حالت AV_OPT_TYPE_CHLAYOUT:
                سیٹ_string_channel_layout(s, opt, opt->default_val.str, dst);
                توڑو;
            حالت AV_OPT_TYPE_DICT:
                سیٹ_string_dict(s, opt, opt->default_val.str, dst);
                توڑو;
        طےشدہ:
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
ساکن صحیح parse_کلید_قدر_pair(خالی *ctx, ثابت حرف **buf,
                                ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep)
{
    حرف *کلید = av_get_token(buf, کلید_val_sep);
    حرف *val;
    صحیح ret;

    اگر (!کلید)
        واپس AVERROR(ENOMEM);

    اگر (*کلید && strspn(*buf, کلید_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, جوڑے_sep);
        اگر (!val) {
            av_freep(&کلید);
            واپس AVERROR(ENOMEM);
        }
    } ورنہ {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", کلید);
        av_free(کلید);
        واپس AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", کلید, val);

    ret = av_opt_سیٹ(ctx, کلید, val, AV_OPT_تلاش_CHILDREN);
    اگر (ret == AVERROR_OPTION_NOT_ملا)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", کلید);

    av_free(کلید);
    av_free(val);
    واپس ret;
}

صحیح av_سیٹ_options_string(خالی *ctx, ثابت حرف *opts,
                          ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep)
{
    صحیح ret, گنتی = 0;

    اگر (!opts)
        واپس 0;

    جب (*opts) {
        اگر ((ret = parse_کلید_قدر_pair(ctx, &opts, کلید_val_sep, جوڑے_sep)) < 0)
            واپس ret;
        گنتی++;

        اگر (*opts)
            opts++;
    }

    واپس گنتی;
}

#تعریف_کرو WHITESPACES " \n\t\r"

ساکن صحیح is_کلید_char(حرف c)
{
    واپس (غیرعلامتی)((c | 32) - 'a') < 26 ||
           (غیرعلامتی)(c - '0') < 10 ||
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
ساکن صحیح get_کلید(ثابت حرف **ropts, ثابت حرف *delim, حرف **rkey)
{
    ثابت حرف *opts = *ropts;
    ثابت حرف *کلید_آغاز, *کلید_انتہا;

    کلید_آغاز = opts += strspn(opts, WHITESPACES);
    جب (is_کلید_char(*opts))
        opts++;
    کلید_انتہا = opts;
    opts += strspn(opts, WHITESPACES);
    اگر (!*opts || !strchr(delim, *opts))
        واپس AVERROR(EINVAL);
    opts++;
    اگر (!(*rkey = av_malloc(کلید_انتہا - کلید_آغاز + 1)))
        واپس AVERROR(ENOMEM);
    حافظہ_نقل(*rkey, کلید_آغاز, کلید_انتہا - کلید_آغاز);
    (*rkey)[کلید_انتہا - کلید_آغاز] = 0;
    *ropts = opts;
    واپس 0;
}

صحیح av_opt_get_کلید_قدر(ثابت حرف **ropts,
                         ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep,
                         غیرعلامتی flags,
                         حرف **rkey, حرف **rval)
{
    صحیح ret;
    حرف *کلید = تہی, *val;
    ثابت حرف *opts = *ropts;

    اگر ((ret = get_کلید(&opts, کلید_val_sep, &کلید)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_کلید))
        واپس AVERROR(EINVAL);
    اگر (!(val = av_get_token(&opts, جوڑے_sep))) {
        av_free(کلید);
        واپس AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = کلید;
    *rval  = val;
    واپس 0;
}

صحیح av_opt_سیٹ_from_string(خالی *ctx, ثابت حرف *opts,
                           ثابت حرف *ثابت *shorthand,
                           ثابت حرف *کلید_val_sep, ثابت حرف *جوڑے_sep)
{
    صحیح ret, گنتی = 0;
    ثابت حرف *dummy_shorthand = تہی;
    ثابت حرف *کلید;

    اگر (!opts)
        واپس 0;
    اگر (!shorthand)
        shorthand = &dummy_shorthand;

    جب (*opts) {
        حرف *parsed_کلید, *قدر;
        ret = av_opt_get_کلید_قدر(&opts, کلید_val_sep, جوڑے_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_کلید : 0,
                                   &parsed_کلید, &قدر);
        اگر (ret < 0) {
            اگر (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            ورنہ
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            واپس ret;
        }
        اگر (*opts)
            opts++;
        اگر (parsed_کلید) {
            کلید = parsed_کلید;
            جب (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } ورنہ {
            کلید = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", کلید, قدر);
        اگر ((ret = av_opt_سیٹ(ctx, کلید, قدر, 0)) < 0) {
            اگر (ret == AVERROR_OPTION_NOT_ملا)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", کلید);
            av_free(قدر);
            av_free(parsed_کلید);
            واپس ret;
        }

        av_free(قدر);
        av_free(parsed_کلید);
        گنتی++;
    }
    واپس گنتی;
}

خالی av_opt_free(خالی *obj)
{
    ثابت AVOption *o = تہی;
    جب ((o = av_opt_اگلا(obj, o))) {
        خالی *pitem = (uint8_t *)obj + o->انحراف;

        اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        ورنہ
            opt_free_elem(o->type, pitem);
    }
}

صحیح av_opt_سیٹ_dict2(خالی *obj, AVDictionary **options, صحیح تلاش_flags)
{
    ثابت AVDictionary_اندراج *t = تہی;
    AVDictionary    *tmp = تہی;
    صحیح ret;

    اگر (!options)
        واپس 0;

    جب ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_سیٹ(obj, t->کلید, t->قدر, تلاش_flags);
        اگر (ret == AVERROR_OPTION_NOT_ملا)
            ret = av_dict_سیٹ(&tmp, t->کلید, t->قدر, AV_DICT_MULTIKEY);
        اگر (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->کلید, t->قدر);
            av_dict_free(&tmp);
            واپس ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    واپس 0;
}

صحیح av_opt_سیٹ_dict(خالی *obj, AVDictionary **options)
{
    واپس av_opt_سیٹ_dict2(obj, options, 0);
}

ثابت AVOption *av_opt_ڈھونڈو(خالی *obj, ثابت حرف *name, ثابت حرف *unit,
                            صحیح opt_flags, صحیح تلاش_flags)
{
    واپس av_opt_find2(obj, name, unit, opt_flags, تلاش_flags, تہی);
}

ثابت AVOption *av_opt_find2(خالی *obj, ثابت حرف *name, ثابت حرف *unit,
                             صحیح opt_flags, صحیح تلاش_flags, خالی **ہدف_obj)
{
    ثابت AVClass  *c;
    ثابت AVOption *o = تہی;

    اگر(!obj)
        واپس تہی;

    c= *(AVClass**)obj;

    اگر (!c)
        واپس تہی;

    اگر (تلاش_flags & AV_OPT_تلاش_CHILDREN) {
        اگر (تلاش_flags & AV_OPT_تلاش_FAKE_OBJ) {
            خالی *iter = تہی;
            ثابت AVClass *بچہ;
            جب (بچہ = av_opt_بچہ_class_iterate(c, &iter))
                اگر (o = av_opt_find2(&بچہ, name, unit, opt_flags, تلاش_flags, تہی))
                    واپس o;
        } ورنہ {
            خالی *بچہ = تہی;
            جب (بچہ = av_opt_بچہ_اگلا(obj, بچہ))
                اگر (o = av_opt_find2(بچہ, name, unit, opt_flags, تلاش_flags, ہدف_obj))
                    واپس o;
        }
    }

    جب (o = av_opt_اگلا(obj, o)) {
        اگر (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            اگر (ہدف_obj) {
                اگر (!(تلاش_flags & AV_OPT_تلاش_FAKE_OBJ))
                    *ہدف_obj = obj;
                ورنہ
                    *ہدف_obj = تہی;
            }
            واپس o;
        }
    }
    واپس تہی;
}

خالی *av_opt_بچہ_اگلا(خالی *obj, خالی *پچھلا)
{
    ثابت AVClass *c = *(AVClass **)obj;
    اگر (c->بچہ_اگلا)
        واپس c->بچہ_اگلا(obj, پچھلا);
    واپس تہی;
}

ثابت AVClass *av_opt_بچہ_class_iterate(ثابت AVClass *والد, خالی **iter)
{
    اگر (والد->بچہ_class_iterate)
        واپس والد->بچہ_class_iterate(iter);
    واپس تہی;
}

ساکن صحیح opt_copy_elem(خالی *logctx, شمار AVOptionType type,
                         خالی *dst, ثابت خالی *src)
{
    اگر (type == AV_OPT_TYPE_STRING) {
        ثابت حرف *src_str = *(ثابت حرف *ثابت *)src;
        حرف         **dstp =  (حرف **)dst;
        اگر (*dstp != src_str)
            av_freep(dstp);
        اگر (src_str) {
            *dstp = av_strdup(src_str);
            اگر (!*dstp)
                واپس AVERROR(ENOMEM);
        }
    } ورنہ اگر (type == AV_OPT_TYPE_ثنائی) {
        ثابت uint8_t *ثابت *src8 = (ثابت uint8_t *ثابت *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        صحیح len = *(ثابت صحیح *)(src8 + 1);
        اگر (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        اگر (len && !*dst8) {
            *(صحیح *)(dst8 + 1) = 0;
            واپس AVERROR(ENOMEM);
        }
        *(صحیح *)(dst8 + 1) = len;
    } ورنہ اگر (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } ورنہ اگر (type == AV_OPT_TYPE_DICT) {
        ثابت AVDictionary *sdict = *(ثابت AVDictionary * ثابت *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        اگر (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = تہی;
        واپس av_dict_copy(ddictp, sdict, 0);
    } ورنہ اگر (type == AV_OPT_TYPE_CHLAYOUT) {
        ثابت AVChannelLayout *slayout = (ثابت AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        اگر (dlayout != slayout) {
            اگر (dlayout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                slayout->ترتیب == AV_CHANNEL_ترتیب_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = تہی;
            واپس av_channel_layout_copy(dst, src);
        }
    } ورنہ اگر (opt_is_pod(type)) {
        size_t سائز = opt_type_desc[type].سائز;
        حافظہ_نقل(dst, src, سائز);
    } ورنہ {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        واپس AVERROR(EINVAL);
    }

    واپس 0;
}

ساکن صحیح opt_copy_array(خالی *logctx, ثابت AVOption *o,
                          خالی **pdst, ثابت خالی * ثابت *psrc)
{
    غیرعلامتی nb_elems = *opt_array_pcount(psrc);
    خالی         *dst = تہی;
    صحیح ret;

    اگر (*pdst == *psrc) {
        *pdst                   = تہی;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_بنیاد(o->type)].سائز);
    اگر (!dst)
        واپس AVERROR(ENOMEM);

    برائے (غیرعلامتی i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_بنیاد(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(خالی**)psrc, i));
        اگر (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            واپس ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    واپس 0;
}

صحیح av_opt_copy(خالی *dst, ثابت خالی *src)
{
    ثابت AVOption *o = تہی;
    ثابت AVClass *c;
    صحیح ret = 0;

    اگر (!src)
        واپس AVERROR(EINVAL);

    c = *(AVClass **)src;
    اگر (!c || c != *(AVClass **)dst)
        واپس AVERROR(EINVAL);

    جب ((o = av_opt_اگلا(src, o))) {
        خالی *میدان_dst = (uint8_t *)dst + o->انحراف;
        خالی *میدان_src = (uint8_t *)src + o->انحراف;

        صحیح err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       میدان_dst, میدان_src) :
                  opt_copy_elem (dst, o->type, میدان_dst, میدان_src);
        اگر (err < 0)
            ret = err;
    }
    واپس ret;
}

صحیح av_opt_get_array_سائز(خالی *obj, ثابت حرف *name, صحیح تلاش_flags,
                          غیرعلامتی صحیح *برآمد_val)
{
    خالی *ہدف_obj, *parray;
    ثابت AVOption *o;

    o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        واپس AVERROR(EINVAL);

    parray = (uint8_t *)ہدف_obj + o->انحراف;
    *برآمد_val = *opt_array_pcount(parray);

    واپس 0;
}

صحیح av_opt_get_array(خالی *obj, ثابت حرف *name, صحیح تلاش_flags,
                     غیرعلامتی صحیح آغاز_elem, غیرعلامتی صحیح nb_elems,
                     شمار AVOptionType برآمد_type, خالی *برآمد_val)
{
    ثابت size_t elem_سائز_برآمد = opt_type_desc[TYPE_بنیاد(برآمد_type)].سائز;

    ثابت AVOption *o;
    خالی *ہدف_obj;

    ثابت خالی *parray;
    غیرعلامتی array_سائز;

    صحیح ret;

    o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف_obj);
    اگر (!o || !ہدف_obj)
        واپس AVERROR_OPTION_NOT_ملا;
    اگر (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (برآمد_type & AV_OPT_TYPE_FLAG_ARRAY))
        واپس AVERROR(EINVAL);

    parray     = (uint8_t *)ہدف_obj + o->انحراف;
    array_سائز = *opt_array_pcount(parray);

    اگر (آغاز_elem >= array_سائز ||
        array_سائز - آغاز_elem < nb_elems)
        واپس AVERROR(EINVAL);

    برائے (غیرعلامتی i = 0; i < nb_elems; i++) {
        ثابت خالی *src = opt_array_pelem(o, *(خالی**)parray, آغاز_elem + i);
        خالی       *dst = (uint8_t*)برآمد_val + i * elem_سائز_برآمد;

        اگر (برآمد_type == TYPE_بنیاد(o->type)) {
            ret = opt_copy_elem(obj, برآمد_type, dst, src);
            اگر (ret < 0)
                جاؤ fail;
        } ورنہ اگر (برآمد_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *برآمد = buf;

            ret = opt_get_elem(o, &برآمد, حجم(buf), src, تلاش_flags);
            اگر (ret < 0)
                جاؤ fail;

            اگر (برآمد == buf) {
                برآمد = av_strdup(buf);
                اگر (!برآمد) {
                    ret = AVERROR(ENOMEM);
                    جاؤ fail;
                }
            }

            *(uint8_t**)dst = برآمد;
        } ورنہ اگر (برآمد_type == AV_OPT_TYPE_INT64    ||
                   برآمد_type == AV_OPT_TYPE_DOUBLE   ||
                   برآمد_type == AV_OPT_TYPE_RATIONAL) {
            دوہرا     عدد = 1.0;
            صحیح        den = 1;
            int64_t intnum = 1;

            ret = read_نمبر(o, src, &عدد, &den, &intnum);
            اگر (ret < 0)
                جاؤ fail;

            انتخاب (برآمد_type) {
            حالت AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (عدد == den) ?  intnum : عدد * intnum / den;
                توڑو;
            حالت AV_OPT_TYPE_DOUBLE:
                *(دوہرا*)dst = عدد * intnum / den;
                توڑو;
            حالت AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (عدد == 1.0 && (صحیح)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_مقصد_rational(عدد * intnum / den);
                توڑو;
            طےشدہ: av_assert0(0);
            }
        } ورنہ
            واپس AVERROR(ENOSYS);
    }

    واپس 0;
fail:
    برائے (غیرعلامتی i = 0; i < nb_elems; i++)
        opt_free_elem(برآمد_type, (uint8_t*)برآمد_val + i * elem_سائز_برآمد);
    واپس ret;
}

صحیح av_opt_سیٹ_array(خالی *obj, ثابت حرف *name, صحیح تلاش_flags,
                     غیرعلامتی صحیح آغاز_elem, غیرعلامتی صحیح nb_elems,
                     شمار AVOptionType val_type, ثابت خالی *val)
{
    ثابت size_t elem_سائز_val = opt_type_desc[TYPE_بنیاد(val_type)].سائز;

    ثابت AVOption *o;
    ثابت AVOptionArrayDef *arr;
    خالی *ہدف_obj;

    خالی *parray;
    خالی *new_elems;
    غیرعلامتی *array_سائز, new_سائز;
    size_t elem_سائز;

    صحیح ret = 0;

    ret = opt_سیٹ_init(obj, name, تلاش_flags, 0, &ہدف_obj, &o, &parray);
    اگر (ret < 0)
        واپس ret;

    اگر (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        واپس AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_سائز = opt_array_pcount(parray);
    elem_سائز  = opt_type_desc[TYPE_بنیاد(o->type)].سائز;

    اگر (آغاز_elem > *array_سائز)
        واپس AVERROR(EINVAL);

    // compute new array size
    اگر (!val) {
        اگر (*array_سائز - آغاز_elem < nb_elems)
            واپس AVERROR(EINVAL);

        new_سائز = *array_سائز - nb_elems;
    } ورنہ اگر (تلاش_flags & AV_OPT_ARRAY_REPLACE) {
        اگر (آغاز_elem >= UINT_MAX - nb_elems)
            واپس AVERROR(EINVAL);

        new_سائز = FFMAX(*array_سائز, آغاز_elem + nb_elems);
    } ورنہ {
        اگر (nb_elems >= UINT_MAX - *array_سائز)
            واپس AVERROR(EINVAL);

        new_سائز = *array_سائز + nb_elems;
    }

    اگر (arr &&
        ((arr->سائز_max && new_سائز > arr->سائز_max) ||
         (arr->سائز_min && new_سائز < arr->سائز_min)))
        واپس AVERROR(EINVAL);

    // desired operation is shrinking the array
    اگر (!val) {
        خالی *array = *(خالی**)parray;

        برائے (غیرعلامتی i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, آغاز_elem + i));
        }

        اگر (new_سائز > 0) {
            memmove(opt_array_pelem(o, array, آغاز_elem),
                    opt_array_pelem(o, array, آغاز_elem + nb_elems),
                    elem_سائز * (*array_سائز - آغاز_elem - nb_elems));

            array = av_realloc_array(array, new_سائز, elem_سائز);
            اگر (!array)
                واپس AVERROR(ENOMEM);

            *(خالی**)parray = array;
        } ورنہ
            av_freep(parray);

        *array_سائز = new_سائز;

        واپس 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_سائز);
    اگر (!new_elems)
        واپس AVERROR(ENOMEM);

    // convert/validate each new element
    برائے (غیرعلامتی i = 0; i < nb_elems; i++) {
        خالی       *dst = opt_array_pelem(o, new_elems, i);
        ثابت خالی *src = (uint8_t*)val + i * elem_سائز_val;

        دوہرا     عدد = 1.0;
        صحیح        den = 1;
        int64_t intnum = 1;

        اگر (val_type == TYPE_بنیاد(o->type)) {
            صحیح err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            اگر (ret < 0)
                جاؤ fail;

            // validate the range for numeric options
            err = read_نمبر(o, dst, &عدد, &den, &intnum);
            اگر (err >= 0 && TYPE_بنیاد(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < عدد * intnum || o->min * den > عدد * intnum)) {
                عدد = den ? عدد * intnum / den : (عدد && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       آغاز_elem + i, o->name, عدد, o->min, o->max);
                ret = AVERROR(ERANGE);
                جاؤ fail;
            }
        } ورنہ اگر (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_سیٹ_elem(obj, ہدف_obj, o, *(ثابت حرف **)src, dst);
            اگر (ret < 0)
                جاؤ fail;
        } ورنہ اگر (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            انتخاب (val_type) {
            حالت AV_OPT_TYPE_INT:       intnum = *(صحیح*)src;                توڑو;
            حالت AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            توڑو;
            حالت AV_OPT_TYPE_FLOAT:     عدد    = *(اعشاری*)src;              توڑو;
            حالت AV_OPT_TYPE_DOUBLE:    عدد    = *(دوہرا*)src;             توڑو;
            حالت AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->عدد;
                                        den    = ((AVRational*)src)->den;   توڑو;
            طےشدہ: av_assert0(0);
            }

            ret = write_نمبر(obj, o, dst, عدد, den, intnum, 0);
            اگر (ret < 0)
                جاؤ fail;
        } ورنہ {
            ret = AVERROR(ENOSYS);
            جاؤ fail;
        }
    }

    // commit new elements to the array
    اگر (آغاز_elem == 0 && nb_elems == new_سائز) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_سائز);
        *(خالی**)parray = new_elems;
        *array_سائز     = nb_elems;

        new_elems = تہی;
        nb_elems  = 0;
    } ورنہ {
        خالی *array = av_realloc_array(*(خالی**)parray, new_سائز, elem_سائز);
        اگر (!array) {
            ret = AVERROR(ENOMEM);
            جاؤ fail;
        }

        اگر (تلاش_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            برائے (غیرعلامتی i = آغاز_elem; i < FFMIN(آغاز_elem + nb_elems, *array_سائز); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } ورنہ {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, آغاز_elem + nb_elems),
                    opt_array_pelem(o, array, آغاز_elem),
                    elem_سائز * (*array_سائز - آغاز_elem));
        }

        حافظہ_نقل((uint8_t*)array + elem_سائز * آغاز_elem, new_elems, elem_سائز * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(خالی**)parray = array;
        *array_سائز     = new_سائز;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    واپس ret;
}

صحیح av_opt_query_ranges(AVOptionRanges **ranges_arg, خالی *obj, ثابت حرف *کلید, صحیح flags)
{
    صحیح ret;
    ثابت AVClass *c = *(AVClass**)obj;
    صحیح (*callback)(AVOptionRanges **, خالی *obj, ثابت حرف *کلید, صحیح flags) = c->query_ranges;

    اگر (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, کلید, flags);
    اگر (ret >= 0) {
        اگر (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    واپس ret;
}

صحیح av_opt_query_ranges_default(AVOptionRanges **ranges_arg, خالی *obj, ثابت حرف *کلید, صحیح flags)
{
    AVOptionRanges *ranges = av_mallocz(حجم(*ranges));
    AVOptionRange **range_array = av_mallocz(حجم(خالی*));
    AVOptionRange *range = av_mallocz(حجم(*range));
    ثابت AVOption *میدان = av_opt_ڈھونڈو(obj, کلید, تہی, 0, flags);
    صحیح ret;

    *ranges_arg = تہی;

    اگر (!ranges || !range || !range_array || !میدان) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->قدر_min = میدان->min;
    range->قدر_max = میدان->max;

    انتخاب (میدان->type) {
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
        توڑو;
    حالت AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->قدر_min = -1;
        range->قدر_max = زیادہ_سے_زیادہ_عدد;
        توڑو;
    حالت AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = زیادہ_سے_زیادہ_عدد;
        توڑو;
    حالت AV_OPT_TYPE_IMAGE_سائز:
        range->component_min = 0;
        range->component_max = زیادہ_سے_زیادہ_عدد/128/8;
        range->قدر_min = 0;
        range->قدر_max = زیادہ_سے_زیادہ_عدد/8;
        توڑو;
    حالت AV_OPT_TYPE_VIDEO_شرح:
        range->component_min = 1;
        range->component_max = زیادہ_سے_زیادہ_عدد;
        range->قدر_min = 1;
        range->قدر_max = زیادہ_سے_زیادہ_عدد;
        توڑو;
    طےشدہ:
        ret = AVERROR(ENOSYS);
        جاؤ fail;
    }

    *ranges_arg = ranges;
    واپس 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    واپس ret;
}

خالی av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    صحیح i;
    AVOptionRanges *ranges = *rangesp;

    اگر (!ranges)
        واپس;

    برائے (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        اگر (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

صحیح av_opt_is_سیٹ_مقصد_default(خالی *obj, ثابت AVOption *o)
{
    int64_t i64;
    دوہرا d;
    AVRational q;
    صحیح ret, w, h;
    حرف *str;
    خالی *dst;

    اگر (!o || !obj)
        واپس AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->انحراف;

    اگر (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ثابت حرف *def = o->default_val.arr ? o->default_val.arr->def : تہی;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        اگر (ret < 0)
            واپس ret;

        اگر (!!val != !!def)
            ret = 0;
        ورنہ اگر (val)
            ret = !strcmp(val, def);
        ورنہ
            ret = 1;

        av_freep(&val);

        واپس ret;
    }

    انتخاب (o->type) {
    حالت AV_OPT_TYPE_CONST:
        واپس 1;
    حالت AV_OPT_TYPE_BOOL:
    حالت AV_OPT_TYPE_FLAGS:
    حالت AV_OPT_TYPE_PIXEL_FMT:
    حالت AV_OPT_TYPE_SAMPLE_FMT:
    حالت AV_OPT_TYPE_INT:
    حالت AV_OPT_TYPE_UINT:
    حالت AV_OPT_TYPE_DURATION:
    حالت AV_OPT_TYPE_INT64:
    حالت AV_OPT_TYPE_UINT64:
        read_نمبر(o, dst, تہی, تہی, &i64);
        واپس o->default_val.i64 == i64;
    حالت AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        اگر (o->default_val.str) {
            اگر ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                واپس ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        واپس ret;
    }
    حالت AV_OPT_TYPE_STRING:
        str = *(حرف **)dst;
        اگر (str == o->default_val.str) //2 NULLs
            واپس 1;
        اگر (!str || !o->default_val.str) //1 NULL
            واپس 0;
        واپس !strcmp(str, o->default_val.str);
    حالت AV_OPT_TYPE_DOUBLE:
        d = *(دوہرا *)dst;
        واپس o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالت AV_OPT_TYPE_FLOAT:
        d = *(اعشاری *)dst;
        واپس (اعشاری)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    حالت AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, زیادہ_سے_زیادہ_عدد);
        واپس !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    حالت AV_OPT_TYPE_ثنائی: {
        ساخت {
            uint8_t *ڈیٹا;
            صحیح سائز;
        } tmp = {0};
        صحیح opt_سائز = *(صحیح *)((خالی **)dst + 1);
        خالی *opt_ptr = *(خالی **)dst;
        اگر (!opt_سائز && (!o->default_val.str || !لڑی_لمبائی(o->default_val.str)))
            واپس 1;
        اگر (!opt_سائز ||  !o->default_val.str || !لڑی_لمبائی(o->default_val.str ))
            واپس 0;
        اگر (opt_سائز != لڑی_لمبائی(o->default_val.str) / 2)
            واپس 0;
        ret = سیٹ_string_ثنائی(تہی, تہی, o->default_val.str, &tmp.ڈیٹا);
        اگر (!ret)
            ret = !memcmp(opt_ptr, tmp.ڈیٹا, tmp.سائز);
        av_free(tmp.ڈیٹا);
        واپس ret;
    }
    حالت AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = تہی;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        ثابت AVDictionary_اندراج *en1 = تہی;
        ثابت AVDictionary_اندراج *en2 = تہی;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        اگر (ret < 0) {
            av_dict_free(&dict1);
            واپس ret;
        }
        کرو {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } جب (en1 && en2 && !strcmp(en1->کلید, en2->کلید) && !strcmp(en1->قدر, en2->قدر));
        av_dict_free(&dict1);
        واپس (!en1 && !en2);
    }
    حالت AV_OPT_TYPE_IMAGE_سائز:
        اگر (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        ورنہ اگر ((ret = av_parse_video_سائز(&w, &h, o->default_val.str)) < 0)
            واپس ret;
        واپس (w == *(صحیح *)dst) && (h == *((صحیح *)dst+1));
    حالت AV_OPT_TYPE_VIDEO_شرح:
        q = (AVRational){0, 0};
        اگر (o->default_val.str) {
            اگر ((ret = av_parse_video_شرح(&q, o->default_val.str)) < 0)
                واپس ret;
        }
        واپس !av_cmp_q(*(AVRational*)dst, q);
    حالت AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        اگر (o->default_val.str) {
            اگر ((ret = av_parse_color(color, o->default_val.str, -1, تہی)) < 0)
                واپس ret;
        }
        واپس !memcmp(color, dst, حجم(color));
    }
    طےشدہ:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        توڑو;
    }
    واپس AVERROR_PATCHWELCOME;
}

صحیح av_opt_is_سیٹ_مقصد_default_by_name(خالی *obj, ثابت حرف *name, صحیح تلاش_flags)
{
    ثابت AVOption *o;
    خالی *ہدف;
    اگر (!obj)
        واپس AVERROR(EINVAL);
    o = av_opt_find2(obj, name, تہی, 0, تلاش_flags, &ہدف);
    اگر (!o)
        واپس AVERROR_OPTION_NOT_ملا;
    واپس av_opt_is_سیٹ_مقصد_default(ہدف, o);
}

ساکن صحیح opt_serialize(خالی *obj, صحیح opt_flags, صحیح flags, صحیح *cnt,
                         AVBPrint *bprint, ثابت حرف کلید_val_sep, ثابت حرف جوڑے_sep)
{
    ثابت AVOption *o = تہی;
    خالی *بچہ = تہی;
    uint8_t *buf;
    صحیح ret;
    ثابت حرف special_chars[] = {جوڑے_sep, کلید_val_sep, '\0'};

    اگر (flags & AV_OPT_SERIALIZE_تلاش_CHILDREN)
        جب (بچہ = av_opt_بچہ_اگلا(obj, بچہ)) {
            ret = opt_serialize(بچہ, opt_flags, flags, cnt, bprint,
                                کلید_val_sep, جوڑے_sep);
            اگر (ret < 0)
                واپس ret;
        }

    جب (o = av_opt_اگلا(obj, o)) {
        اگر (o->type == AV_OPT_TYPE_CONST)
            جاری;
        اگر ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            اگر ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                اگر (o->flags == opt_flags)
                    جاری;
            } ورنہ اگر ((o->flags & opt_flags) == opt_flags)
                جاری;
        } ورنہ {
            اگر ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                جاری;
            ورنہ اگر (((o->flags & opt_flags) != opt_flags))
                جاری;
        }
        اگر (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_سیٹ_مقصد_default(obj, o) > 0)
            جاری;
        اگر ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, تہی);
            واپس ret;
        }
        اگر (buf) {
            اگر ((*cnt)++)
                av_bprint_append_ڈیٹا(bprint, &جوڑے_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
            av_bprint_append_ڈیٹا(bprint, &کلید_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_منوال_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    واپس 0;
}

صحیح av_opt_serialize(خالی *obj, صحیح opt_flags, صحیح flags, حرف **بفر,
                     ثابت حرف کلید_val_sep, ثابت حرف جوڑے_sep)
{
    AVBPrint bprint;
    صحیح ret, cnt = 0;

    اگر (جوڑے_sep == '\0' || کلید_val_sep == '\0' || جوڑے_sep == کلید_val_sep ||
        جوڑے_sep == '\\' || کلید_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        واپس AVERROR(EINVAL);
    }

    اگر (!obj || !بفر)
        واپس AVERROR(EINVAL);

    *بفر = تہی;
    av_bprint_init(&bprint, 64, AV_BPRINT_سائز_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        کلید_val_sep, جوڑے_sep);
    اگر (ret < 0)
        واپس ret;

    ret = av_bprint_finalize(&bprint, بفر);
    اگر (ret < 0)
        واپس ret;
    واپس 0;
}
