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

#અન્તર્ભાવ "avutil.h"
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "channel_layout.h"
#અન્તર્ભાવ "dict.h"
#અન્તર્ભાવ "eval.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "parseutils.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "mathematics.h"
#અન્તર્ભાવ "opt.h"
#અન્તર્ભાવ "samplefmt.h"
#અન્તર્ભાવ "bprint.h"

#અન્તર્ભાવ <float.h>

#define TYPE_BASE(type) ((type) & ~AV_OPT_TYPE_FLAG_ARRAY)

અચલ AVOption *av_opt_next(અચલ શૂન્ય *obj, અચલ AVOption *last)
{
    અચલ AVClass *class;
    જો (!obj)
        પાછા ખાલી;
    class = *(અચલ AVClass**)obj;
    જો (!last && class && class->option && class->option[0].name)
        પાછા class->option;
    જો (last && last[1].name)
        પાછા ++last;
    પાછા ખાલી;
}

સ્થિર અચલ સંરચના {
    size_t      size;
    અચલ અક્ષર *name;
} opt_type_desc[] = {
    [AV_OPT_TYPE_FLAGS]         = { કદ(unsigned),       "<flags>" },
    [AV_OPT_TYPE_INT]           = { કદ(પૂર્ણાંક),            "<int>" },
    [AV_OPT_TYPE_INT64]         = { કદ(int64_t),        "<int64>" },
    [AV_OPT_TYPE_UINT]          = { કદ(unsigned),       "<unsigned>" },
    [AV_OPT_TYPE_UINT64]        = { કદ(uint64_t),       "<uint64>" },
    [AV_OPT_TYPE_DOUBLE]        = { કદ(દ્વિગુણ),         "<double>" },
    [AV_OPT_TYPE_FLOAT]         = { કદ(દશાંશ),          "<float>" },
    [AV_OPT_TYPE_STRING]        = { કદ(અક્ષર *),         "<string>" },
    [AV_OPT_TYPE_RATIONAL]      = { કદ(AVRational),     "<rational>" },
    [AV_OPT_TYPE_દ્વિઅંકી]        = { કદ(uint8_t *),      "<binary>" },
    [AV_OPT_TYPE_DICT]          = { કદ(AVDictionary *), "<dictionary>" },
    [AV_OPT_TYPE_IMAGE_SIZE]    = { કદ(પૂર્ણાંક[2]),         "<image_size>" },
    [AV_OPT_TYPE_VIDEO_RATE]    = { કદ(AVRational),     "<video_rate>" },
    [AV_OPT_TYPE_PIXEL_FMT]     = { કદ(ગણના AVPixelFormat),  "<pix_fmt>" },
    [AV_OPT_TYPE_SAMPLE_FMT]    = { કદ(ગણના AVSampleFormat), "<sample_fmt>" },
    [AV_OPT_TYPE_DURATION]      = { કદ(int64_t),        "<duration>" },
    [AV_OPT_TYPE_COLOR]         = { કદ(uint8_t[4]),     "<color>" },
    [AV_OPT_TYPE_CHLAYOUT]      = { કદ(AVChannelLayout),"<channel_layout>" },
    [AV_OPT_TYPE_BOOL]          = { કદ(પૂર્ણાંક),            "<boolean>" },
};

// option is plain old data
સ્થિર પૂર્ણાંક opt_is_pod(ગણના AVOptionType type)
{
    પસંદગી (type) {
    સ્થિતિ AV_OPT_TYPE_FLAGS:
    સ્થિતિ AV_OPT_TYPE_INT:
    સ્થિતિ AV_OPT_TYPE_INT64:
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
    સ્થિતિ AV_OPT_TYPE_FLOAT:
    સ્થિતિ AV_OPT_TYPE_RATIONAL:
    સ્થિતિ AV_OPT_TYPE_UINT64:
    સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
    સ્થિતિ AV_OPT_TYPE_DURATION:
    સ્થિતિ AV_OPT_TYPE_COLOR:
    સ્થિતિ AV_OPT_TYPE_BOOL:
    સ્થિતિ AV_OPT_TYPE_UINT:
        પાછા 1;
    }
    પાછા 0;
}

સ્થિર uint8_t opt_array_sep(અચલ AVOption *o)
{
    અચલ AVOptionArrayDef *d = o->default_val.arr;
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    પાછા (d && d->sep) ? d->sep : ',';
}

સ્થિર શૂન્ય *opt_array_pelem(અચલ AVOption *o, શૂન્ય *array, unsigned idx)
{
    av_assert1(o->type & AV_OPT_TYPE_FLAG_ARRAY);
    પાછા (uint8_t *)array + idx * opt_type_desc[TYPE_BASE(o->type)].size;
}

સ્થિર unsigned *opt_array_pcount(અચલ શૂન્ય *parray)
{
    પાછા (unsigned *)((અચલ શૂન્ય * અચલ *)parray + 1);
}

સ્થિર શૂન્ય opt_free_elem(ગણના AVOptionType type, શૂન્ય *ptr)
{
    પસંદગી (TYPE_BASE(type)) {
    સ્થિતિ AV_OPT_TYPE_STRING:
    સ્થિતિ AV_OPT_TYPE_દ્વિઅંકી:
        av_freep(ptr);
        તોડો;

    સ્થિતિ AV_OPT_TYPE_DICT:
        av_dict_free((AVDictionary **)ptr);
        તોડો;

    સ્થિતિ AV_OPT_TYPE_CHLAYOUT:
        av_channel_layout_uninit((AVChannelLayout *)ptr);
        તોડો;

    મૂળભૂત:
        તોડો;
    }
}

સ્થિર શૂન્ય opt_free_array(અચલ AVOption *o, શૂન્ય *parray, unsigned *ગણતરી)
{
    માટે (unsigned i = 0; i < *ગણતરી; i++)
        opt_free_elem(o->type, opt_array_pelem(o, *(શૂન્ય **)parray, i));

    av_freep(parray);
    *ગણતરી = 0;
}

/**
 * Perform common setup for option-setting functions.
 *
 * @param require_type when non-0, require the option to be of this type
 * @param ptgt         target object is written here
 * @param po           the option is written here
 * @param pdst         pointer to option value is written here
 */
સ્થિર પૂર્ણાંક opt_set_init(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags,
                        પૂર્ણાંક require_type,
                        શૂન્ય **ptgt, અચલ AVOption **po, શૂન્ય **pdst)
{
    શૂન્ય *logctx;
    અચલ AVOption *o;
    શૂન્ય *tgt;

    o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &tgt);
    જો (!o || (!tgt && !(શોધ_flags & AV_OPT_શોધ_FAKE_OBJ)))
        પાછા AVERROR_OPTION_NOT_FOUND;

    જો (o->flags & AV_OPT_FLAG_READONLY)
        પાછા AVERROR(EINVAL);

    logctx = tgt ? obj : ખાલી;

    જો (require_type && (o->type != require_type)) {
        av_log(logctx, AV_LOG_ERROR,
               "Tried to set option '%s' of type %s from value of type %s, "
               "this is not supported\n", o->name, opt_type_desc[o->type].name,
               opt_type_desc[require_type].name);
        પાછા AVERROR(EINVAL);
    }

    જો (!(o->flags & AV_OPT_FLAG_RUNTIME_PARAM)) {
        unsigned *state_flags = ખાલી;
        અચલ AVClass *class;

        // try state flags first from the target (child), then from its parent
        class = *(અચલ AVClass**)tgt;
        જો (class->state_flags_offset)
            state_flags = (unsigned*)((uint8_t*)tgt + class->state_flags_offset);

        જો (!state_flags && obj != tgt) {
            class = *(અચલ AVClass**)obj;
            જો (class->state_flags_offset)
                state_flags = (unsigned*)((uint8_t*)obj + class->state_flags_offset);
        }

        જો (state_flags && (*state_flags & AV_CLASS_STATE_INITIALIZED)) {
            av_log(logctx, AV_LOG_ERROR, "Option '%s' is not a runtime option and "
                   "so cannot be set after the object has been initialized\n",
                   o->name);
            પાછા AVERROR(EINVAL);
        }
    }

    જો (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    જો (po)
        *po   = o;
    જો (ptgt)
        *ptgt = tgt;
    જો (pdst)
        *pdst = tgt ? ((uint8_t *)tgt) + o->offset : ખાલી;

    પાછા 0;
}

સ્થિર AVRational double_to_rational(દ્વિગુણ d)
{
     AVRational r = av_d2q(d, 1 << 24);
     જો ((!r.અંક || !r.den) && d)
         r = av_d2q(d, INT_MAX);
     પાછા r;
}

સ્થિર પૂર્ણાંક read_સંખ્યા(અચલ AVOption *o, અચલ શૂન્ય *dst, દ્વિગુણ *અંક, પૂર્ણાંક *den, int64_t *intnum)
{
    પસંદગી (TYPE_BASE(o->type)) {
    સ્થિતિ AV_OPT_TYPE_FLAGS:
        *intnum = *(unsigned પૂર્ણાંક*)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
        *intnum = *(ગણના AVPixelFormat *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
        *intnum = *(ગણના AVSampleFormat *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_BOOL:
    સ્થિતિ AV_OPT_TYPE_INT:
        *intnum = *(પૂર્ણાંક *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_UINT:
        *intnum = *(unsigned પૂર્ણાંક *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_DURATION:
    સ્થિતિ AV_OPT_TYPE_INT64:
    સ્થિતિ AV_OPT_TYPE_UINT64:
        *intnum = *(int64_t *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_FLOAT:
        *અંક = *(દશાંશ *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
        *અંક = *(દ્વિગુણ *)dst;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_RATIONAL:
        *intnum = ((AVRational *)dst)->અંક;
        *den    = ((AVRational *)dst)->den;
        પાછા 0;
    સ્થિતિ AV_OPT_TYPE_CONST:
        *intnum = o->default_val.i64;
        પાછા 0;
    }
    પાછા AVERROR(EINVAL);
}

સ્થિર પૂર્ણાંક write_સંખ્યા(શૂન્ય *obj, અચલ AVOption *o, શૂન્ય *dst,
                        દ્વિગુણ અંક, પૂર્ણાંક den, int64_t intnum,
                        પૂર્ણાંક ignore_range)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    અચલ ગણના AVOptionType type = TYPE_BASE(o->type);

    જો (!ignore_range && type != AV_OPT_TYPE_FLAGS &&
        (!den || o->max * den < અંક * intnum || o->min * den > અંક * intnum)) {
        અંક = den ? અંક * intnum / den : (અંક && intnum ? INFINITY : NAN);
        av_log(obj, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
               અંક, o->name, o->min, o->max);
        પાછા AVERROR(ERANGE);
    }
    જો (!ignore_range && type == AV_OPT_TYPE_FLAGS) {
        દ્વિગુણ d = અંક*intnum/den;
        જો (d < -1.5 || d > 0xFFFFFFFF+0.5 || (llrint(d*256) & 255)) {
            av_log(logctx, AV_LOG_ERROR,
                   "Value %f for parameter '%s' is not a valid set of 32bit integer flags\n",
                   અંક*intnum/den, o->name);
            પાછા AVERROR(ERANGE);
        }
    }

    જો (!dst)
        પાછા 0;

    પસંદગી (type) {
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
        *(ગણના AVPixelFormat *)dst = llrint(અંક / den) * intnum;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
        *(ગણના AVSampleFormat *)dst = llrint(અંક / den) * intnum;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_BOOL:
    સ્થિતિ AV_OPT_TYPE_FLAGS:
    સ્થિતિ AV_OPT_TYPE_INT:
    સ્થિતિ AV_OPT_TYPE_UINT:
        *(પૂર્ણાંક *)dst = llrint(અંક / den) * intnum;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_DURATION:
    સ્થિતિ AV_OPT_TYPE_INT64:{
        દ્વિગુણ d = અંક / den;
        જો (intnum == 1 && d == (દ્વિગુણ)INT64_MAX) {
            *(int64_t *)dst = INT64_MAX;
        } નહીંતર
            *(int64_t *)dst = llrint(d) * intnum;
        તોડો;}
    સ્થિતિ AV_OPT_TYPE_UINT64:{
        દ્વિગુણ d = અંક / den;
        // We must special case uint64_t here as llrint() does not support values
        // outside the int64_t range and there is no portable function which does
        // "INT64_MAX + 1ULL" is used as it is representable exactly as IEEE double
        // while INT64_MAX is not
        જો (intnum == 1 && d == (દ્વિગુણ)UINT64_MAX) {
            *(uint64_t *)dst = UINT64_MAX;
        } નહીંતર જો (d > INT64_MAX + 1ULL) {
            *(uint64_t *)dst = (llrint(d - (INT64_MAX + 1ULL)) + (INT64_MAX + 1ULL))*intnum;
        } નહીંતર {
            *(uint64_t *)dst = llrint(d) * intnum;
        }
        તોડો;}
    સ્થિતિ AV_OPT_TYPE_FLOAT:
        *(દશાંશ *)dst = અંક * intnum / den;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
        *(દ્વિગુણ    *)dst = અંક * intnum / den;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_RATIONAL:
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
        જો ((પૂર્ણાંક) અંક == અંક)
            *(AVRational *)dst = (AVRational) { અંક *intnum, den };
        નહીંતર
            *(AVRational *)dst = double_to_rational(અંક * intnum / den);
        તોડો;
    મૂળભૂત:
        પાછા AVERROR(EINVAL);
    }
    પાછા 0;
}

સ્થિર પૂર્ણાંક hexchar2int(અક્ષર c) {
    જો (c >= '0' && c <= '9')
        પાછા c - '0';
    જો (c >= 'a' && c <= 'f')
        પાછા c - 'a' + 10;
    જો (c >= 'A' && c <= 'F')
        પાછા c - 'A' + 10;
    પાછા -1;
}

સ્થિર પૂર્ણાંક set_string_દ્વિઅંકી(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t **dst)
{
    પૂર્ણાંક *lendst;
    uint8_t *bin, *ptr;
    પૂર્ણાંક len;

    જો (dst) {
        lendst = (પૂર્ણાંક *)(dst + 1);
        av_freep(dst);
        *lendst = 0;
    }

    જો (!val || !(len = strlen(val)))
        પાછા 0;

    જો (len & 1)
        પાછા AVERROR(EINVAL);
    len /= 2;

    ptr = bin = av_malloc(len);
    જો (!ptr)
        પાછા AVERROR(ENOMEM);
    જ્યારે (*val) {
        પૂર્ણાંક a = hexchar2int(*val++);
        પૂર્ણાંક b = hexchar2int(*val++);
        જો (a < 0 || b < 0) {
            av_free(bin);
            પાછા AVERROR(EINVAL);
        }
        *ptr++ = (a << 4) | b;
    }

    જો (dst) {
        *dst    = bin;
        *lendst = len;
    } નહીંતર {
        av_free(bin);
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક set_string(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t **dst)
{
    જો (!dst)
        પાછા 0;
    av_freep(dst);
    જો (!val)
        પાછા 0;
    *dst = av_strdup(val);
    પાછા *dst ? 0 : AVERROR(ENOMEM);
}

#define DEFAULT_NUMVAL(opt) ((opt->type == AV_OPT_TYPE_INT64 || \
                              opt->type == AV_OPT_TYPE_UINT64 || \
                              opt->type == AV_OPT_TYPE_CONST || \
                              opt->type == AV_OPT_TYPE_FLAGS || \
                              opt->type == AV_OPT_TYPE_UINT  || \
                              opt->type == AV_OPT_TYPE_INT)     \
                             ? opt->default_val.i64             \
                             : opt->default_val.dbl)

સ્થિર પૂર્ણાંક set_string_સંખ્યા(શૂન્ય *obj, શૂન્ય *target_obj, અચલ AVOption *o, અચલ અક્ષર *val, શૂન્ય *dst)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    અચલ ગણના AVOptionType type = TYPE_BASE(o->type);
    પૂર્ણાંક ret = 0;

    જો (type == AV_OPT_TYPE_RATIONAL || type == AV_OPT_TYPE_VIDEO_RATE) {
        પૂર્ણાંક અંક, den;
        અક્ષર c;
        જો (sscanf(val, "%d%*1[:/]%d%c", &અંક, &den, &c) == 2) {
            જો ((ret = write_સંખ્યા(obj, o, dst, 1, den, અંક, 0)) >= 0)
                પાછા ret;
            ret = 0;
        }
    }

    માટે (;;) {
        પૂર્ણાંક i = 0;
        અક્ષર buf[256];
        પૂર્ણાંક cmd = 0;
        દ્વિગુણ d;
        int64_t intnum = 1;

        જો (type == AV_OPT_TYPE_FLAGS) {
            જો (*val == '+' || *val == '-')
                cmd = *(val++);
            માટે (; i < કદ(buf) - 1 && val[i] && val[i] != '+' && val[i] != '-'; i++)
                buf[i] = val[i];
            buf[i] = 0;
        }

        {
            પૂર્ણાંક res;
            પૂર્ણાંક ci = 0;
            દ્વિગુણ const_કિંમતો[64];
            અચલ અક્ષર * const_names[64];
            પૂર્ણાંક શોધ_flags = (o->flags & AV_OPT_FLAG_CHILD_CONSTS) ? AV_OPT_શોધ_CHILDREN : 0;
            અચલ AVOption *o_named = av_opt_find(target_obj, i ? buf : val, o->unit, 0, શોધ_flags);
            જો (o_named && o_named->type == AV_OPT_TYPE_CONST) {
                d = DEFAULT_NUMVAL(o_named);
                જો (o_named->flags & AV_OPT_FLAG_DEPRECATED)
                    av_log(logctx, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n",
                           o_named->name, o_named->help);
            } નહીંતર {
                જો (o->unit) {
                    માટે (o_named = ખાલી; o_named = av_opt_next(target_obj, o_named); ) {
                        જો (o_named->type == AV_OPT_TYPE_CONST &&
                            o_named->unit &&
                            !strcmp(o_named->unit, o->unit)) {
                            જો (ci + 6 >= FF_ARRAY_ELEMS(const_કિંમતો)) {
                                av_log(logctx, AV_LOG_ERROR, "const_values array too small for %s\n", o->unit);
                                પાછા AVERROR_PATCHWELCOME;
                            }
                            const_names [ci  ] = o_named->name;
                            const_કિંમતો[ci++] = DEFAULT_NUMVAL(o_named);
                        }
                    }
                }
                const_names [ci  ] = "default";
                const_કિંમતો[ci++] = DEFAULT_NUMVAL(o);
                const_names [ci  ] = "max";
                const_કિંમતો[ci++] = o->max;
                const_names [ci  ] = "min";
                const_કિંમતો[ci++] = o->min;
                const_names [ci  ] = "none";
                const_કિંમતો[ci++] = 0;
                const_names [ci  ] = "all";
                const_કિંમતો[ci++] = ~0;
                const_names [ci] = ખાલી;
                const_કિંમતો[ci] = 0;

                res = av_પદાવલિ_parse_and_eval(&d, i ? buf : val, const_names,
                                            const_કિંમતો, ખાલી, ખાલી, ખાલી, ખાલી, ખાલી, 0, obj);
                જો (res < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\"\n", o->name, val);
                    પાછા res;
                }
            }
        }
        જો (type == AV_OPT_TYPE_FLAGS && dst) {
            intnum = *(unsigned પૂર્ણાંક*)dst;
            જો (cmd == '+')
                d = intnum | (int64_t)d;
            નહીંતર જો (cmd == '-')
                d = intnum &~(int64_t)d;
        }

        જો ((ret = write_સંખ્યા(obj, o, dst, d, 1, 1, 0)) < 0)
            પાછા ret;
        val += i;
        જો (!i || !*val)
            પાછા 0;
    }
}

સ્થિર પૂર્ણાંક set_string_image_size(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, પૂર્ણાંક *dst)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    પૂર્ણાંક tmp[2];
    પૂર્ણાંક ret;

    જો (!val || !strcmp(val, "none")) {
        જો (dst) {
        dst[0] =
        dst[1] = 0;
        }
        પાછા 0;
    }
    ret = av_parse_video_size(&tmp[0], &tmp[1], val);
    જો (ret < 0) {
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as image size\n", o->name, val);
        પાછા ret;
    }
    જો (dst)
        memcpy(dst, tmp, કદ(tmp));
    પાછા ret;
}

સ્થિર પૂર્ણાંક set_string_video_rate(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, AVRational *dst)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    AVRational tmp;
    પૂર્ણાંક ret = av_parse_video_rate(&tmp, val);
    જો (ret < 0)
        av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as video rate\n", o->name, val);
    જો (dst)
        *dst = tmp;
    પાછા ret;
}

સ્થિર પૂર્ણાંક set_string_color(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t *dst)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    પૂર્ણાંક ret;

    જો (!val) {
        પાછા 0;
    } નહીંતર {
        uint8_t tmp[4];
        ret = av_parse_color(tmp, val, -1, obj);
        જો (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as color\n", o->name, val);
            પાછા ret;
        }
        જો (dst)
            memcpy(dst, tmp, કદ(tmp));
        પાછા ret;
    }
    પાછા 0;
}

સ્થિર અચલ અક્ષર *get_bool_name(પૂર્ણાંક val)
{
    જો (val < 0)
        પાછા "auto";
    પાછા val ? "true" : "false";
}

સ્થિર પૂર્ણાંક set_string_bool(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, પૂર્ણાંક *dst)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    પૂર્ણાંક n;

    જો (!val)
        પાછા 0;

    જો (!strcmp(val, "auto")) {
        n = -1;
    } નહીંતર જો (av_match_name(val, "true,y,yes,enable,enabled,on")) {
        n = 1;
    } નહીંતર જો (av_match_name(val, "false,n,no,disable,disabled,off")) {
        n = 0;
    } નહીંતર {
        અક્ષર *end = ખાલી;
        n = strtol(val, &end, 10);
        જો (val + strlen(val) != end)
            જાઓ fail;
    }

    જો (n < o->min || n > o->max)
        જાઓ fail;

    જો (dst)
    *dst = n;
    પાછા 0;

fail:
    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as boolean\n", o->name, val);
    પાછા AVERROR(EINVAL);
}

સ્થિર પૂર્ણાંક set_string_fmt(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t *dst,
                          પૂર્ણાંક fmt_nb, પૂર્ણાંક ((*get_fmt)(અચલ અક્ષર *)), અચલ અક્ષર *desc,
                          ગણના AVOptionType type)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    પૂર્ણાંક fmt, min, max;

    જો (!val || !strcmp(val, "none")) {
        fmt = -1;
    } નહીંતર {
        fmt = get_fmt(val);
        જો (fmt == -1) {
            અક્ષર *tail;
            fmt = strtol(val, &tail, 0);
            જો (*tail || (unsigned)fmt >= fmt_nb) {
                av_log(logctx, AV_LOG_ERROR,
                       "Unable to parse \"%s\" option value \"%s\" as %s\n", o->name, val, desc);
                પાછા AVERROR(EINVAL);
            }
        }
    }

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, fmt_nb-1);

    // hack for compatibility with old ffmpeg
    જો(min == 0 && max == 0) {
        min = -1;
        max = fmt_nb-1;
    }

    જો (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, o->name, desc, min, max);
        પાછા AVERROR(ERANGE);
    }

    જો (dst)
    પસંદગી (type) {
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:  *(ગણના AVPixelFormat *)dst = fmt; તોડો;
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT: *(ગણના AVSampleFormat*)dst = fmt; તોડો;
    મૂળભૂત: av_unreachable("set_string_fmt() is only called for pixel and sample formats");
    }
    પાછા 0;
}

સ્થિર પૂર્ણાંક get_pix_fmt(અચલ અક્ષર *name)
{
    પાછા av_get_pix_fmt(name);
}

સ્થિર પૂર્ણાંક set_string_pixel_fmt(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t *dst)
{
    પાછા set_string_fmt(obj, o, val, dst,
                          AV_PIX_FMT_NB, get_pix_fmt,
                          "pixel format", AV_OPT_TYPE_PIXEL_FMT);
}

સ્થિર પૂર્ણાંક get_sample_fmt(અચલ અક્ષર *name)
{
    પાછા av_get_sample_fmt(name);
}

સ્થિર પૂર્ણાંક set_string_sample_fmt(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t *dst)
{
    પાછા set_string_fmt(obj, o, val, dst,
                          AV_SAMPLE_FMT_NB, get_sample_fmt,
                          "sample format", AV_OPT_TYPE_SAMPLE_FMT);
}

સ્થિર પૂર્ણાંક set_string_dict(શૂન્ય *obj, અચલ AVOption *o, અચલ અક્ષર *val, uint8_t **dst)
{
    AVDictionary *options = ખાલી;

    જો (val) {
        પૂર્ણાંક ret = av_dict_parse_string(&options, val, "=", ":", 0);
        જો (ret < 0) {
            av_dict_free(&options);
            પાછા ret;
        }
    }

    જો (!dst) {
        av_dict_free(&options);
        પાછા 0;
    }

    av_dict_free((AVDictionary **)dst);
    *dst = (uint8_t *)options;

    પાછા 0;
}

સ્થિર પૂર્ણાંક set_string_channel_layout(શૂન્ય *obj, અચલ AVOption *o,
                                     અચલ અક્ષર *val, શૂન્ય *dst)
{
    AVChannelLayout tmp;
    AVChannelLayout *channel_layout = dst;
    પૂર્ણાંક ret;
    જો (dst)
    av_channel_layout_uninit(channel_layout);
    નહીંતર
        channel_layout = &tmp;
    જો (!val)
        પાછા 0;
    ret = av_channel_layout_from_string(channel_layout, val);
    જો (ret < 0)
        પાછા ret;
    જો (!dst)
        av_channel_layout_uninit(channel_layout);
    પાછા 0;
}

સ્થિર પૂર્ણાંક opt_set_elem(શૂન્ય *obj, શૂન્ય *target_obj, અચલ AVOption *o,
                        અચલ અક્ષર *val, શૂન્ય *dst)
{
    શૂન્ય *logctx = dst ? obj : ખાલી;
    અચલ ગણના AVOptionType type = TYPE_BASE(o->type);
    પૂર્ણાંક ret;

    જો (!val && (type != AV_OPT_TYPE_STRING &&
                 type != AV_OPT_TYPE_PIXEL_FMT && type != AV_OPT_TYPE_SAMPLE_FMT &&
                 type != AV_OPT_TYPE_IMAGE_SIZE &&
                 type != AV_OPT_TYPE_DURATION && type != AV_OPT_TYPE_COLOR &&
                 type != AV_OPT_TYPE_BOOL))
        પાછા AVERROR(EINVAL);

    પસંદગી (type) {
    સ્થિતિ AV_OPT_TYPE_BOOL:
        પાછા set_string_bool(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_STRING:
        પાછા set_string(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_દ્વિઅંકી:
        પાછા set_string_દ્વિઅંકી(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_FLAGS:
    સ્થિતિ AV_OPT_TYPE_INT:
    સ્થિતિ AV_OPT_TYPE_UINT:
    સ્થિતિ AV_OPT_TYPE_INT64:
    સ્થિતિ AV_OPT_TYPE_UINT64:
    સ્થિતિ AV_OPT_TYPE_FLOAT:
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
    સ્થિતિ AV_OPT_TYPE_RATIONAL:
        પાછા set_string_સંખ્યા(obj, target_obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
        પાછા set_string_image_size(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE: {
        AVRational tmp;
        ret = set_string_video_rate(obj, o, val, &tmp);
        જો (ret < 0)
            પાછા ret;
        પાછા write_સંખ્યા(obj, o, dst, 1, tmp.den, tmp.અંક, 0);
    }
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
        પાછા set_string_pixel_fmt(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
        પાછા set_string_sample_fmt(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_DURATION:
        {
            int64_t usecs = 0;
            જો (val) {
                જો ((ret = av_parse_time(&usecs, val, 1)) < 0) {
                    av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as duration\n", o->name, val);
                    પાછા ret;
                }
            }
            જો (usecs < o->min || usecs > o->max) {
                av_log(logctx, AV_LOG_ERROR, "Value %f for parameter '%s' out of range [%g - %g]\n",
                       usecs / 1000000.0, o->name, o->min / 1000000.0, o->max / 1000000.0);
                પાછા AVERROR(ERANGE);
            }
            જો (dst)
            *(int64_t *)dst = usecs;
            પાછા 0;
        }
    સ્થિતિ AV_OPT_TYPE_COLOR:
        પાછા set_string_color(obj, o, val, dst);
    સ્થિતિ AV_OPT_TYPE_CHLAYOUT:
        ret = set_string_channel_layout(obj, o, val, dst);
        જો (ret < 0) {
            av_log(logctx, AV_LOG_ERROR, "Unable to parse \"%s\" option value \"%s\" as channel layout\n", o->name, val);
            ret = AVERROR(EINVAL);
        }
        પાછા ret;
    સ્થિતિ AV_OPT_TYPE_DICT:
        પાછા set_string_dict(obj, o, val, dst);
    }

    av_log(logctx, AV_LOG_ERROR, "Invalid option type.\n");
    પાછા AVERROR(EINVAL);
}

સ્થિર પૂર્ણાંક opt_set_array(શૂન્ય *obj, શૂન્ય *target_obj, અચલ AVOption *o,
                         અચલ અક્ષર *val, શૂન્ય *dst)
{
    અચલ AVOptionArrayDef *arr = o->default_val.arr;
    અચલ size_t      elem_size = opt_type_desc[TYPE_BASE(o->type)].size;
    અચલ uint8_t           sep = opt_array_sep(o);
    uint8_t                *str = ખાલી;

    શૂન્ય      *logctx = dst ? obj : ખાલી;
    શૂન્ય       *elems = ખાલી;
    unsigned nb_elems = 0;
    પૂર્ણાંક ret;

    જો (val && *val) {
        str = av_malloc(strlen(val) + 1);
        જો (!str)
            પાછા AVERROR(ENOMEM);
    }

    // split and unescape the string
    જ્યારે (val && *val) {
        uint8_t *p = str;
        શૂન્ય *tmp;

        જો (arr && arr->size_max && nb_elems >= arr->size_max) {
            av_log(logctx, AV_LOG_ERROR,
                   "Cannot assign more than %u elements to array option %s\n",
                   arr->size_max, o->name);
            ret = AVERROR(EINVAL);
            જાઓ fail;
        }

        માટે (; *val; val++, p++) {
            જો (*val == '\\' && val[1])
                val++;
            નહીંતર જો (*val == sep) {
                val++;
                તોડો;
            }
            *p = *val;
        }
        *p = 0;

        tmp = av_realloc_array(elems, nb_elems + 1, elem_size);
        જો (!tmp) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }
        elems = tmp;

        tmp = opt_array_pelem(o, elems, nb_elems);
        memset(tmp, 0, elem_size);

        ret = opt_set_elem(obj, target_obj, o, str, tmp);
        જો (ret < 0)
            જાઓ fail;
        nb_elems++;
    }
    av_freep(&str);

    જો (dst)
    opt_free_array(o, dst, opt_array_pcount(dst));

    જો (arr && nb_elems < arr->size_min) {
        av_log(logctx, AV_LOG_ERROR,
               "Cannot assign fewer than %u elements to array option %s\n",
               arr->size_min, o->name);
        ret = AVERROR(EINVAL);
        જાઓ fail;
    }

    જો (dst) {
    *((શૂન્ય **)dst)        = elems;
    *opt_array_pcount(dst) = nb_elems;
    } નહીંતર
        opt_free_array(o, &elems, &nb_elems);

    પાછા 0;
fail:
    av_freep(&str);
    opt_free_array(o, &elems, &nb_elems);
    પાછા ret;
}

પૂર્ણાંક av_opt_set(શૂન્ય *obj, અચલ અક્ષર *name, અચલ અક્ષર *val, પૂર્ણાંક શોધ_flags)
{
    શૂન્ય *dst, *target_obj;
    અચલ AVOption *o;
    પૂર્ણાંક ret;

    ret = opt_set_init(obj, name, શોધ_flags, 0, &target_obj, &o, &dst);
    જો (ret < 0)
        પાછા ret;

    પાછા ((o->type & AV_OPT_TYPE_FLAG_ARRAY) ?
            opt_set_array : opt_set_elem)(obj, target_obj, o, val, dst);
}

#define OPT_EVAL_સંખ્યા(name, opttype, vartype)                         \
પૂર્ણાંક av_opt_eval_ ## name(શૂન્ય *obj, અચલ AVOption *o,                  \
                         અચલ અક્ષર *val, vartype *name ## _out)        \
{                                                                       \
    જો (!o || o->type != opttype || o->flags & AV_OPT_FLAG_READONLY)    \
        પાછા AVERROR(EINVAL);                                         \
    પાછા set_string_સંખ્યા(obj, obj, o, val, name ## _out);           \
}

OPT_EVAL_સંખ્યા(flags,  AV_OPT_TYPE_FLAGS,    પૂર્ણાંક)
OPT_EVAL_સંખ્યા(પૂર્ણાંક,    AV_OPT_TYPE_INT,      પૂર્ણાંક)
OPT_EVAL_સંખ્યા(uint,   AV_OPT_TYPE_UINT,     unsigned)
OPT_EVAL_સંખ્યા(int64,  AV_OPT_TYPE_INT64,    int64_t)
OPT_EVAL_સંખ્યા(દશાંશ,  AV_OPT_TYPE_FLOAT,    દશાંશ)
OPT_EVAL_સંખ્યા(દ્વિગુણ, AV_OPT_TYPE_DOUBLE,   દ્વિગુણ)
OPT_EVAL_સંખ્યા(q,      AV_OPT_TYPE_RATIONAL, AVRational)

સ્થિર પૂર્ણાંક set_સંખ્યા(શૂન્ય *obj, અચલ અક્ષર *name, દ્વિગુણ અંક, પૂર્ણાંક den, int64_t intnum,
                      પૂર્ણાંક શોધ_flags, પૂર્ણાંક require_type)
{
    શૂન્ય *dst;
    અચલ AVOption *o;
    પૂર્ણાંક ret;

    ret = opt_set_init(obj, name, શોધ_flags, require_type, ખાલી, &o, &dst);
    જો (ret < 0)
        પાછા ret;
    જો (dst)
        ret = write_સંખ્યા(obj, o, dst, અંક, den, intnum, 0);

    પાછા ret;
}

પૂર્ણાંક av_opt_set_int(શૂન્ય *obj, અચલ અક્ષર *name, int64_t val, પૂર્ણાંક શોધ_flags)
{
    પાછા set_સંખ્યા(obj, name, 1, 1, val, શોધ_flags, 0);
}

પૂર્ણાંક av_opt_set_double(શૂન્ય *obj, અચલ અક્ષર *name, દ્વિગુણ val, પૂર્ણાંક શોધ_flags)
{
    પાછા set_સંખ્યા(obj, name, val, 1, 1, શોધ_flags, 0);
}

પૂર્ણાંક av_opt_set_q(શૂન્ય *obj, અચલ અક્ષર *name, AVRational val, પૂર્ણાંક શોધ_flags)
{
    પાછા set_સંખ્યા(obj, name, val.અંક, val.den, 1, શોધ_flags, 0);
}

પૂર્ણાંક av_opt_set_bin(શૂન્ય *obj, અચલ અક્ષર *name, અચલ uint8_t *val, પૂર્ણાંક len, પૂર્ણાંક શોધ_flags)
{
    uint8_t *ptr;
    uint8_t **dst;
    પૂર્ણાંક *lendst;
    પૂર્ણાંક ret;

    ret = opt_set_init(obj, name, શોધ_flags, AV_OPT_TYPE_દ્વિઅંકી,
                       ખાલી, ખાલી, (શૂન્ય**)&dst);
    જો (ret < 0)
        પાછા ret;

    જો (dst) {
    ptr = len ? av_malloc(len) : ખાલી;
    જો (len && !ptr)
        પાછા AVERROR(ENOMEM);

    lendst = (પૂર્ણાંક *)(dst + 1);

    av_free(*dst);
    *dst    = ptr;
    *lendst = len;
    જો (len)
        memcpy(ptr, val, len);
    }

    પાછા 0;
}

પૂર્ણાંક av_opt_set_image_size(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક શોધ_flags)
{
    અચલ AVOption *o;
    શૂન્ય *logctx;
    પૂર્ણાંક *dst;
    પૂર્ણાંક ret;

    ret = opt_set_init(obj, name, શોધ_flags, AV_OPT_TYPE_IMAGE_SIZE,
                       ખાલી, &o, (શૂન્ય**)&dst);
    જો (ret < 0)
        પાછા ret;

    logctx = dst ? obj : ખાલી;

    જો (w<0 || h<0) {
        av_log(logctx, AV_LOG_ERROR,
               "Invalid negative size value %dx%d for size '%s'\n", w, h, o->name);
        પાછા AVERROR(EINVAL);
    }

    જો (dst) {
    dst[0] = w;
    dst[1] = h;
    }

    પાછા 0;
}

પૂર્ણાંક av_opt_set_video_rate(શૂન્ય *obj, અચલ અક્ષર *name, AVRational val, પૂર્ણાંક શોધ_flags)
{
    પાછા set_સંખ્યા(obj, name, val.અંક, val.den, 1, શોધ_flags, AV_OPT_TYPE_VIDEO_RATE);
}

સ્થિર પૂર્ણાંક set_format(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક fmt, પૂર્ણાંક શોધ_flags,
                      ગણના AVOptionType type, અચલ અક્ષર *desc, પૂર્ણાંક nb_fmts)
{
    અચલ AVOption *o;
    શૂન્ય *logctx;
    પૂર્ણાંક *dst;
    પૂર્ણાંક min, max, ret;

    ret = opt_set_init(obj, name, શોધ_flags, type, ખાલી, &o, (શૂન્ય**)&dst);
    જો (ret < 0)
        પાછા ret;

    logctx = dst ? obj : ખાલી;

    min = FFMAX(o->min, -1);
    max = FFMIN(o->max, nb_fmts-1);

    જો (fmt < min || fmt > max) {
        av_log(logctx, AV_LOG_ERROR,
               "Value %d for parameter '%s' out of %s format range [%d - %d]\n",
               fmt, name, desc, min, max);
        પાછા AVERROR(ERANGE);
    }
    જો (dst)
    *dst = fmt;
    પાછા 0;
}

પૂર્ણાંક av_opt_set_pixel_fmt(શૂન્ય *obj, અચલ અક્ષર *name, ગણના AVPixelFormat fmt, પૂર્ણાંક શોધ_flags)
{
    પાછા set_format(obj, name, fmt, શોધ_flags, AV_OPT_TYPE_PIXEL_FMT, "pixel", AV_PIX_FMT_NB);
}

પૂર્ણાંક av_opt_set_sample_fmt(શૂન્ય *obj, અચલ અક્ષર *name, ગણના AVSampleFormat fmt, પૂર્ણાંક શોધ_flags)
{
    પાછા set_format(obj, name, fmt, શોધ_flags, AV_OPT_TYPE_SAMPLE_FMT, "sample", AV_SAMPLE_FMT_NB);
}

પૂર્ણાંક av_opt_set_dict_val(શૂન્ય *obj, અચલ અક્ષર *name, અચલ AVDictionary *val,
                        પૂર્ણાંક શોધ_flags)
{
    AVDictionary **dst;
    પૂર્ણાંક ret;

    ret = opt_set_init(obj, name, શોધ_flags, AV_OPT_TYPE_DICT, ખાલી, ખાલી,
                       (શૂન્ય**)&dst);
    જો (ret < 0)
        પાછા ret;

    જો (dst) {
    av_dict_free(dst);

        ret = av_dict_copy(dst, val, 0);
    }

    પાછા ret;
}

પૂર્ણાંક av_opt_set_chlayout(શૂન્ય *obj, અચલ અક્ષર *name,
                        અચલ AVChannelLayout *channel_layout,
                        પૂર્ણાંક શોધ_flags)
{
    AVChannelLayout *dst;
    પૂર્ણાંક ret;

    ret = opt_set_init(obj, name, શોધ_flags, AV_OPT_TYPE_CHLAYOUT, ખાલી, ખાલી,
                       (શૂન્ય**)&dst);
    જો (ret < 0)
        પાછા ret;

    જો (dst)
        ret = av_channel_layout_copy(dst, channel_layout);

    પાછા ret;
}

સ્થિર શૂન્ય format_duration(અક્ષર *buf, size_t size, int64_t d)
{
    અક્ષર *e;

    av_assert0(size >= 25);
    જો (d < 0 && d != INT64_MIN) {
        *(buf++) = '-';
        size--;
        d = -d;
    }
    જો (d == INT64_MAX)
        snprintf(buf, size, "INT64_MAX");
    નહીંતર જો (d == INT64_MIN)
        snprintf(buf, size, "INT64_MIN");
    નહીંતર જો (d > (int64_t)3600*1000000)
        snprintf(buf, size, "%"PRId64":%02d:%02d.%06d", d / 3600000000,
                 (પૂર્ણાંક)((d / 60000000) % 60),
                 (પૂર્ણાંક)((d / 1000000) % 60),
                 (પૂર્ણાંક)(d % 1000000));
    નહીંતર જો (d > 60*1000000)
        snprintf(buf, size, "%d:%02d.%06d",
                 (પૂર્ણાંક)(d / 60000000),
                 (પૂર્ણાંક)((d / 1000000) % 60),
                 (પૂર્ણાંક)(d % 1000000));
    નહીંતર
        snprintf(buf, size, "%d.%06d",
                 (પૂર્ણાંક)(d / 1000000),
                 (પૂર્ણાંક)(d % 1000000));
    e = buf + strlen(buf);
    જ્યારે (e > buf && e[-1] == '0')
        *(--e) = 0;
    જો (e > buf && e[-1] == '.')
        *(--e) = 0;
}

સ્થિર પૂર્ણાંક opt_get_elem(અચલ AVOption *o, uint8_t **pbuf, size_t buf_len,
                        અચલ શૂન્ય *dst, પૂર્ણાંક શોધ_flags)
{
    પૂર્ણાંક ret;

    પસંદગી (TYPE_BASE(o->type)) {
    સ્થિતિ AV_OPT_TYPE_BOOL:
        ret = snprintf(*pbuf, buf_len, "%s", get_bool_name(*(પૂર્ણાંક *)dst));
        તોડો;
    સ્થિતિ AV_OPT_TYPE_FLAGS:
        ret = snprintf(*pbuf, buf_len, "0x%08X", *(પૂર્ણાંક *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_INT:
        ret = snprintf(*pbuf, buf_len, "%d", *(પૂર્ણાંક *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_UINT:
        ret = snprintf(*pbuf, buf_len, "%u", *(unsigned *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_INT64:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, *(int64_t *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_UINT64:
        ret = snprintf(*pbuf, buf_len, "%"PRIu64, *(uint64_t *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_FLOAT:
        ret = snprintf(*pbuf, buf_len, "%f", *(દશાંશ *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
        ret = snprintf(*pbuf, buf_len, "%f", *(દ્વિગુણ *)dst);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
    સ્થિતિ AV_OPT_TYPE_RATIONAL:
        ret = snprintf(*pbuf, buf_len, "%d/%d", ((AVRational *)dst)->અંક, ((AVRational *)dst)->den);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_CONST:
        ret = snprintf(*pbuf, buf_len, "%"PRId64, o->default_val.i64);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_STRING:
        જો (*(uint8_t **)dst) {
            *pbuf = av_strdup(*(uint8_t **)dst);
        } નહીંતર જો (શોધ_flags & AV_OPT_ALLOW_NULL) {
            *pbuf = ખાલી;
            પાછા 0;
        } નહીંતર {
            *pbuf = av_strdup("");
        }
        પાછા *pbuf ? 0 : AVERROR(ENOMEM);
    સ્થિતિ AV_OPT_TYPE_દ્વિઅંકી: {
        અચલ uint8_t *bin;
        પૂર્ણાંક len;

        જો (!*(uint8_t **)dst && (શોધ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ખાલી;
            પાછા 0;
        }
        len = *(પૂર્ણાંક *)(((uint8_t *)dst) + કદ(uint8_t *));
        જો ((uint64_t)len * 2 + 1 > INT_MAX)
            પાછા AVERROR(EINVAL);
        જો (!(*pbuf = av_malloc(len * 2 + 1)))
            પાછા AVERROR(ENOMEM);
        જો (!len) {
            *pbuf[0] = '\0';
            પાછા 0;
        }
        bin = *(uint8_t **)dst;
        માટે (પૂર્ણાંક i = 0; i < len; i++)
            snprintf(*pbuf + i * 2, 3, "%02X", bin[i]);
        પાછા 0;
    }
    સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
        ret = snprintf(*pbuf, buf_len, "%dx%d", ((પૂર્ણાંક *)dst)[0], ((પૂર્ણાંક *)dst)[1]);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (અક્ષર *)av_x_if_null(av_get_pix_fmt_name(*(ગણના AVPixelFormat *)dst), "none"));
        તોડો;
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
        ret = snprintf(*pbuf, buf_len, "%s", (અક્ષર *)av_x_if_null(av_get_sample_fmt_name(*(ગણના AVSampleFormat *)dst), "none"));
        તોડો;
    સ્થિતિ AV_OPT_TYPE_DURATION: {
        int64_t i64 = *(int64_t *)dst;
        format_duration(*pbuf, buf_len, i64);
        ret = strlen(*pbuf); // no overflow possible, checked by an assert
        તોડો;
    }
    સ્થિતિ AV_OPT_TYPE_COLOR:
        ret = snprintf(*pbuf, buf_len, "0x%02x%02x%02x%02x",
                       (પૂર્ણાંક)((uint8_t *)dst)[0], (પૂર્ણાંક)((uint8_t *)dst)[1],
                       (પૂર્ણાંક)((uint8_t *)dst)[2], (પૂર્ણાંક)((uint8_t *)dst)[3]);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_CHLAYOUT:
        ret = av_channel_layout_describe(dst, *pbuf, buf_len);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_DICT:
        જો (!*(AVDictionary **)dst && (શોધ_flags & AV_OPT_ALLOW_NULL)) {
            *pbuf = ખાલી;
            પાછા 0;
        }
        પાછા av_dict_get_string(*(AVDictionary **)dst, (અક્ષર **)pbuf, '=', ':');
    મૂળભૂત:
        પાછા AVERROR(EINVAL);
    }

    પાછા ret;
}

સ્થિર પૂર્ણાંક opt_get_array(અચલ AVOption *o, શૂન્ય *dst, uint8_t **out_val)
{
    અચલ unsigned ગણતરી = *opt_array_pcount(dst);
    અચલ uint8_t    sep = opt_array_sep(o);

    uint8_t *str     = ખાલી;
    size_t   str_len = 0;
    પૂર્ણાંક ret;

    *out_val = ખાલી;

    માટે (unsigned i = 0; i < ગણતરી; i++) {
        uint8_t buf[128], *out = buf;
        size_t out_len;

        ret = opt_get_elem(o, &out, કદ(buf),
                           opt_array_pelem(o, *(શૂન્ય **)dst, i), 0);
        જો (ret < 0)
            જાઓ fail;

        out_len = strlen(out);
        જો (out_len > SIZE_MAX / 2 - !!i ||
            !!i + out_len * 2 > SIZE_MAX - str_len - 1) {
            ret = AVERROR(ERANGE);
            જાઓ fail;
        }

        //                         terminator     escaping  separator
        //                                ↓             ↓     ↓
        ret = av_reallocp(&str, str_len + 1 + out_len * 2 + !!i);
        જો (ret < 0)
            જાઓ fail;

        // add separator if needed
        જો (i)
            str[str_len++] = sep;

        // escape the element
        માટે (unsigned j = 0; j < out_len; j++) {
            uint8_t val = out[j];
            જો (val == sep || val == '\\')
                str[str_len++] = '\\';
            str[str_len++] = val;
        }
        str[str_len] = 0;

fail:
        જો (out != buf)
            av_freep(&out);
        જો (ret < 0) {
            av_freep(&str);
            પાછા ret;
        }
    }

    *out_val = str;

    પાછા 0;
}

પૂર્ણાંક av_opt_get(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, uint8_t **out_val)
{
    શૂન્ય *dst, *target_obj;
    અચલ AVOption *o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    uint8_t *out, buf[128];
    પૂર્ણાંક ret;

    જો (!o || !target_obj || (o->offset<=0 && o->type != AV_OPT_TYPE_CONST))
        પાછા AVERROR_OPTION_NOT_FOUND;

    જો (o->flags & AV_OPT_FLAG_DEPRECATED)
        av_log(obj, AV_LOG_WARNING, "The \"%s\" option is deprecated: %s\n", name, o->help);

    dst = (uint8_t *)target_obj + o->offset;

    જો (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        ret = opt_get_array(o, dst, out_val);
        જો (ret < 0)
            પાછા ret;
        જો (!*out_val && !(શોધ_flags & AV_OPT_ALLOW_NULL)) {
            *out_val = av_strdup("");
            જો (!*out_val)
               પાછા AVERROR(ENOMEM);
        }
        પાછા 0;
    }

    buf[0] = 0;
    out = buf;
    ret = opt_get_elem(o, &out, કદ(buf), dst, શોધ_flags);
    જો (ret < 0)
        પાછા ret;
    જો (out != buf) {
        *out_val = out;
        પાછા 0;
    }

    જો (ret >= કદ(buf))
        પાછા AVERROR(EINVAL);
    *out_val = av_strdup(out);
    પાછા *out_val ? 0 : AVERROR(ENOMEM);
}

સ્થિર પૂર્ણાંક get_સંખ્યા(શૂન્ય *obj, અચલ અક્ષર *name, દ્વિગુણ *અંક, પૂર્ણાંક *den, int64_t *intnum,
                      પૂર્ણાંક શોધ_flags)
{
    શૂન્ય *dst, *target_obj;
    અચલ AVOption *o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (o->type & AV_OPT_TYPE_FLAG_ARRAY)
        પાછા AVERROR(EINVAL);

    dst = ((uint8_t *)target_obj) + o->offset;

    પાછા read_સંખ્યા(o, dst, અંક, den, intnum);
}

પૂર્ણાંક av_opt_get_int(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, int64_t *out_val)
{
    int64_t intnum = 1;
    દ્વિગુણ અંક = 1;
    પૂર્ણાંક ret, den = 1;

    જો ((ret = get_સંખ્યા(obj, name, &અંક, &den, &intnum, શોધ_flags)) < 0)
        પાછા ret;
    જો (અંક == den)
        *out_val = intnum;
    નહીંતર
        *out_val = અંક * intnum / den;
    પાછા 0;
}

પૂર્ણાંક av_opt_get_double(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, દ્વિગુણ *out_val)
{
    int64_t intnum = 1;
    દ્વિગુણ અંક = 1;
    પૂર્ણાંક ret, den = 1;

    જો ((ret = get_સંખ્યા(obj, name, &અંક, &den, &intnum, શોધ_flags)) < 0)
        પાછા ret;
    *out_val = અંક * intnum / den;
    પાછા 0;
}

પૂર્ણાંક av_opt_get_q(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, AVRational *out_val)
{
    int64_t intnum = 1;
    દ્વિગુણ અંક = 1;
    પૂર્ણાંક ret, den = 1;

    જો ((ret = get_સંખ્યા(obj, name, &અંક, &den, &intnum, શોધ_flags)) < 0)
        પાછા ret;

    જો (અંક == 1.0 && (પૂર્ણાંક)intnum == intnum)
        *out_val = (AVRational){intnum, den};
    નહીંતર
        *out_val = double_to_rational(અંક*intnum/den);
    પાછા 0;
}

પૂર્ણાંક av_opt_get_image_size(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, પૂર્ણાંક *w_out, પૂર્ણાંક *h_out)
{
    શૂન્ય *dst, *target_obj;
    અચલ AVOption *o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (o->type != AV_OPT_TYPE_IMAGE_SIZE) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a image size.\n", name);
        પાછા AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    જો (w_out) *w_out = *(પૂર્ણાંક *)dst;
    જો (h_out) *h_out = *((પૂર્ણાંક *)dst+1);
    પાછા 0;
}

પૂર્ણાંક av_opt_get_video_rate(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, AVRational *out_val)
{
    પાછા av_opt_get_q(obj, name, શોધ_flags, out_val);
}

સ્થિર પૂર્ણાંક get_format(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, શૂન્ય *out_fmt,
                      ગણના AVOptionType type, અચલ અક્ષર *desc)
{
    શૂન્ય *dst, *target_obj;
    અચલ AVOption *o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (o->type != type) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a %s format.\n", desc, name);
        પાછા AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    જો (type == AV_OPT_TYPE_PIXEL_FMT)
        *(ગણના AVPixelFormat *)out_fmt = *(ગણના AVPixelFormat *)dst;
    નહીંતર
        *(ગણના AVSampleFormat*)out_fmt = *(ગણના AVSampleFormat*)dst;

    પાછા 0;
}

પૂર્ણાંક av_opt_get_pixel_fmt(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, ગણના AVPixelFormat *out_fmt)
{
    પાછા get_format(obj, name, શોધ_flags, out_fmt, AV_OPT_TYPE_PIXEL_FMT, "pixel");
}

પૂર્ણાંક av_opt_get_sample_fmt(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, ગણના AVSampleFormat *out_fmt)
{
    પાછા get_format(obj, name, શોધ_flags, out_fmt, AV_OPT_TYPE_SAMPLE_FMT, "sample");
}

પૂર્ણાંક av_opt_get_chlayout(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, AVChannelLayout *cl)
{
    શૂન્ય *dst, *target_obj;
    અચલ AVOption *o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (o->type != AV_OPT_TYPE_CHLAYOUT) {
        av_log(obj, AV_LOG_ERROR,
               "The value for option '%s' is not a channel layout.\n", name);
        પાછા AVERROR(EINVAL);
    }

    dst = ((uint8_t*)target_obj) + o->offset;
    પાછા av_channel_layout_copy(cl, dst);
}

પૂર્ણાંક av_opt_get_dict_val(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags, AVDictionary **out_val)
{
    શૂન્ય *target_obj;
    AVDictionary *src;
    અચલ AVOption *o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);

    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (o->type != AV_OPT_TYPE_DICT)
        પાછા AVERROR(EINVAL);

    src = *(AVDictionary **)(((uint8_t *)target_obj) + o->offset);

    પાછા av_dict_copy(out_val, src, 0);
}

પૂર્ણાંક av_opt_flag_is_set(શૂન્ય *obj, અચલ અક્ષર *field_name, અચલ અક્ષર *flag_name)
{
    અચલ AVOption *field = av_opt_find(obj, field_name, ખાલી, 0, 0);
    અચલ AVOption *flag  = av_opt_find(obj, flag_name,
                                        field ? field->unit : ખાલી, 0, 0);
    int64_t res;

    જો (!field || !flag || flag->type != AV_OPT_TYPE_CONST ||
        av_opt_get_int(obj, field_name, 0, &res) < 0)
        પાછા 0;
    પાછા res & flag->default_val.i64;
}

સ્થિર શૂન્ય log_int_કિંમત(શૂન્ય *av_log_obj, પૂર્ણાંક level, int64_t i)
{
    જો (i == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } નહીંતર જો (i == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } નહીંતર જો (i == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } નહીંતર જો (i == INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } નહીંતર જો (i == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } નહીંતર {
        av_log(av_log_obj, level, "%"PRId64, i);
    }
}

સ્થિર શૂન્ય log_કિંમત(શૂન્ય *av_log_obj, પૂર્ણાંક level, દ્વિગુણ d)
{
    જો      (d == INT_MAX) {
        av_log(av_log_obj, level, "INT_MAX");
    } નહીંતર જો (d == INT_MIN) {
        av_log(av_log_obj, level, "INT_MIN");
    } નહીંતર જો (d == UINT32_MAX) {
        av_log(av_log_obj, level, "UINT32_MAX");
    } નહીંતર જો (d == (દ્વિગુણ)INT64_MAX) {
        av_log(av_log_obj, level, "I64_MAX");
    } નહીંતર જો (d == INT64_MIN) {
        av_log(av_log_obj, level, "I64_MIN");
    } નહીંતર જો (d == FLT_MAX) {
        av_log(av_log_obj, level, "FLT_MAX");
    } નહીંતર જો (d == FLT_MIN) {
        av_log(av_log_obj, level, "FLT_MIN");
    } નહીંતર જો (d == -FLT_MAX) {
        av_log(av_log_obj, level, "-FLT_MAX");
    } નહીંતર જો (d == -FLT_MIN) {
        av_log(av_log_obj, level, "-FLT_MIN");
    } નહીંતર જો (d == DBL_MAX) {
        av_log(av_log_obj, level, "DBL_MAX");
    } નહીંતર જો (d == DBL_MIN) {
        av_log(av_log_obj, level, "DBL_MIN");
    } નહીંતર જો (d == -DBL_MAX) {
        av_log(av_log_obj, level, "-DBL_MAX");
    } નહીંતર જો (d == -DBL_MIN) {
        av_log(av_log_obj, level, "-DBL_MIN");
    } નહીંતર {
        av_log(av_log_obj, level, "%g", d);
    }
}

સ્થિર અચલ અક્ષર *get_opt_const_name(શૂન્ય *obj, અચલ અક્ષર *unit, int64_t કિંમત)
{
    અચલ AVOption *opt = ખાલી;

    જો (!unit)
        પાછા ખાલી;
    જ્યારે ((opt = av_opt_next(obj, opt)))
        જો (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 == કિંમત)
            પાછા opt->name;
    પાછા ખાલી;
}

સ્થિર અક્ષર *get_opt_flags_string(શૂન્ય *obj, અચલ અક્ષર *unit, int64_t કિંમત)
{
    અચલ AVOption *opt = ખાલી;
    અક્ષર flags[512];

    flags[0] = 0;
    જો (!unit)
        પાછા ખાલી;
    જ્યારે ((opt = av_opt_next(obj, opt))) {
        જો (opt->type == AV_OPT_TYPE_CONST && !strcmp(opt->unit, unit) &&
            opt->default_val.i64 & કિંમત) {
            જો (flags[0])
                av_strlcatf(flags, કદ(flags), "+");
            av_strlcatf(flags, કદ(flags), "%s", opt->name);
        }
    }
    જો (flags[0])
        પાછા av_strdup(flags);
    પાછા ખાલી;
}

સ્થિર શૂન્ય log_type(શૂન્ય *av_log_obj, અચલ AVOption *o,
                     ગણના AVOptionType parent_type)
{
    અચલ ગણના AVOptionType type = TYPE_BASE(o->type);

    જો (o->type == AV_OPT_TYPE_CONST && (TYPE_BASE(parent_type) == AV_OPT_TYPE_INT || TYPE_BASE(parent_type) == AV_OPT_TYPE_INT64))
        av_log(av_log_obj, AV_LOG_INFO, "%-12"PRId64" ", o->default_val.i64);
    નહીંતર જો (type < FF_ARRAY_ELEMS(opt_type_desc) && opt_type_desc[type].name) {
        જો (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            av_log(av_log_obj, AV_LOG_INFO, "[%-10s]", opt_type_desc[type].name);
        નહીંતર
            av_log(av_log_obj, AV_LOG_INFO, "%-12s ", opt_type_desc[type].name);
    }
    નહીંતર
        av_log(av_log_obj, AV_LOG_INFO, "%-12s ", "");
}

સ્થિર શૂન્ય log_default(શૂન્ય *obj, શૂન્ય *av_log_obj, અચલ AVOption *opt)
{
    જો (opt->type == AV_OPT_TYPE_CONST || opt->type == AV_OPT_TYPE_દ્વિઅંકી)
        પાછા;
    જો ((opt->type == AV_OPT_TYPE_COLOR      ||
         opt->type == AV_OPT_TYPE_IMAGE_SIZE ||
         opt->type == AV_OPT_TYPE_STRING     ||
         opt->type == AV_OPT_TYPE_DICT       ||
         opt->type == AV_OPT_TYPE_CHLAYOUT   ||
         opt->type == AV_OPT_TYPE_VIDEO_RATE) &&
        !opt->default_val.str)
        પાછા;

    જો (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
        અચલ AVOptionArrayDef *arr = opt->default_val.arr;
        જો (arr && arr->def)
            av_log(av_log_obj, AV_LOG_INFO, " (default %s)", arr->def);
        પાછા;
    }

    av_log(av_log_obj, AV_LOG_INFO, " (default ");
    પસંદગી (opt->type) {
    સ્થિતિ AV_OPT_TYPE_BOOL:
        av_log(av_log_obj, AV_LOG_INFO, "%s", get_bool_name(opt->default_val.i64));
        તોડો;
    સ્થિતિ AV_OPT_TYPE_FLAGS: {
        અક્ષર *def_flags = get_opt_flags_string(obj, opt->unit, opt->default_val.i64);
        જો (def_flags) {
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_flags);
            av_freep(&def_flags);
        } નહીંતર {
            av_log(av_log_obj, AV_LOG_INFO, "%"PRIX64, opt->default_val.i64);
        }
        તોડો;
    }
    સ્થિતિ AV_OPT_TYPE_DURATION: {
        અક્ષર buf[25];
        format_duration(buf, કદ(buf), opt->default_val.i64);
        av_log(av_log_obj, AV_LOG_INFO, "%s", buf);
        તોડો;
    }
    સ્થિતિ AV_OPT_TYPE_UINT:
    સ્થિતિ AV_OPT_TYPE_INT:
    સ્થિતિ AV_OPT_TYPE_UINT64:
    સ્થિતિ AV_OPT_TYPE_INT64: {
        અચલ અક્ષર *def_const = get_opt_const_name(obj, opt->unit, opt->default_val.i64);
        જો (def_const)
            av_log(av_log_obj, AV_LOG_INFO, "%s", def_const);
        નહીંતર
            log_int_કિંમત(av_log_obj, AV_LOG_INFO, opt->default_val.i64);
        તોડો;
    }
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
    સ્થિતિ AV_OPT_TYPE_FLOAT:
        log_કિંમત(av_log_obj, AV_LOG_INFO, opt->default_val.dbl);
        તોડો;
    સ્થિતિ AV_OPT_TYPE_RATIONAL: {
        AVRational q = av_d2q(opt->default_val.dbl, INT_MAX);
        av_log(av_log_obj, AV_LOG_INFO, "%d/%d", q.અંક, q.den); }
        તોડો;
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (અક્ષર *)av_x_if_null(av_get_pix_fmt_name(opt->default_val.i64), "none"));
        તોડો;
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
        av_log(av_log_obj, AV_LOG_INFO, "%s", (અક્ષર *)av_x_if_null(av_get_sample_fmt_name(opt->default_val.i64), "none"));
        તોડો;
    સ્થિતિ AV_OPT_TYPE_COLOR:
    સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
    સ્થિતિ AV_OPT_TYPE_STRING:
    સ્થિતિ AV_OPT_TYPE_DICT:
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
    સ્થિતિ AV_OPT_TYPE_CHLAYOUT:
        av_log(av_log_obj, AV_LOG_INFO, "\"%s\"", opt->default_val.str);
        તોડો;
    }
    av_log(av_log_obj, AV_LOG_INFO, ")");
}

સ્થિર શૂન્ય opt_list(શૂન્ય *obj, શૂન્ય *av_log_obj, અચલ અક્ષર *unit,
                     પૂર્ણાંક req_flags, પૂર્ણાંક rej_flags, ગણના AVOptionType parent_type)
{
    અચલ AVOption *opt = ખાલી;
    AVOptionRanges *r;
    પૂર્ણાંક i;

    જ્યારે ((opt = av_opt_next(obj, opt))) {
        જો (!(opt->flags & req_flags) || (opt->flags & rej_flags))
            ચાલુ;

        /* Don't print CONST's on level one.
         * Don't print anything but CONST's on level two.
         * Only print items from the requested unit.
         */
        જો (!unit && opt->type == AV_OPT_TYPE_CONST)
            ચાલુ;
        નહીંતર જો (unit && opt->type != AV_OPT_TYPE_CONST)
            ચાલુ;
        નહીંતર જો (unit && opt->type == AV_OPT_TYPE_CONST && strcmp(unit, opt->unit))
            ચાલુ;
        નહીંતર જો (unit && opt->type == AV_OPT_TYPE_CONST)
            av_log(av_log_obj, AV_LOG_INFO, "     %-15s ", opt->name);
        નહીંતર
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

        જો (opt->help)
            av_log(av_log_obj, AV_LOG_INFO, " %s", opt->help);

        જો (av_opt_query_ranges(&r, obj, opt->name, AV_OPT_શોધ_FAKE_OBJ) >= 0) {
            પસંદગી (opt->type) {
            સ્થિતિ AV_OPT_TYPE_INT:
            સ્થિતિ AV_OPT_TYPE_UINT:
            સ્થિતિ AV_OPT_TYPE_INT64:
            સ્થિતિ AV_OPT_TYPE_UINT64:
            સ્થિતિ AV_OPT_TYPE_DOUBLE:
            સ્થિતિ AV_OPT_TYPE_FLOAT:
            સ્થિતિ AV_OPT_TYPE_RATIONAL:
                માટે (i = 0; i < r->nb_ranges; i++) {
                    av_log(av_log_obj, AV_LOG_INFO, " (from ");
                    log_કિંમત(av_log_obj, AV_LOG_INFO, r->range[i]->કિંમત_min);
                    av_log(av_log_obj, AV_LOG_INFO, " to ");
                    log_કિંમત(av_log_obj, AV_LOG_INFO, r->range[i]->કિંમત_max);
                    av_log(av_log_obj, AV_LOG_INFO, ")");
                }
                તોડો;
            }
            av_opt_freep_ranges(&r);
        }

        log_default(obj, av_log_obj, opt);

        av_log(av_log_obj, AV_LOG_INFO, "\n");
        જો (opt->unit && opt->type != AV_OPT_TYPE_CONST)
            opt_list(obj, av_log_obj, opt->unit, req_flags, rej_flags, opt->type);
    }
}

પૂર્ણાંક av_opt_show2(શૂન્ય *obj, શૂન્ય *av_log_obj, પૂર્ણાંક req_flags, પૂર્ણાંક rej_flags)
{
    જો (!obj)
        પાછા -1;

    av_log(av_log_obj, AV_LOG_INFO, "%s AVOptions:\n", (*(AVClass **)obj)->class_name);

    opt_list(obj, av_log_obj, ખાલી, req_flags, rej_flags, -1);

    પાછા 0;
}

શૂન્ય av_opt_set_defaults(શૂન્ય *s)
{
    av_opt_set_defaults2(s, 0, 0);
}

શૂન્ય av_opt_set_defaults2(શૂન્ય *s, પૂર્ણાંક mask, પૂર્ણાંક flags)
{
    અચલ AVOption *opt = ખાલી;
    જ્યારે ((opt = av_opt_next(s, opt))) {
        શૂન્ય *dst = ((uint8_t*)s) + opt->offset;

        જો ((opt->flags & mask) != flags)
            ચાલુ;

        જો (opt->flags & AV_OPT_FLAG_READONLY)
            ચાલુ;

        જો (opt->type & AV_OPT_TYPE_FLAG_ARRAY) {
            અચલ AVOptionArrayDef *arr = opt->default_val.arr;
            અચલ અક્ષર              sep = opt_array_sep(opt);

            av_assert0(sep && sep != '\\' &&
                       (sep < 'a' || sep > 'z') &&
                       (sep < 'A' || sep > 'Z') &&
                       (sep < '0' || sep > '9'));

            જો (arr && arr->def)
                opt_set_array(s, s, opt, arr->def, dst);

            ચાલુ;
        }

        પસંદગી (opt->type) {
            સ્થિતિ AV_OPT_TYPE_CONST:
                /* Nothing to be done here */
                તોડો;
            સ્થિતિ AV_OPT_TYPE_BOOL:
            સ્થિતિ AV_OPT_TYPE_FLAGS:
            સ્થિતિ AV_OPT_TYPE_INT:
            સ્થિતિ AV_OPT_TYPE_UINT:
            સ્થિતિ AV_OPT_TYPE_INT64:
            સ્થિતિ AV_OPT_TYPE_UINT64:
            સ્થિતિ AV_OPT_TYPE_DURATION:
            સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
            સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
                write_સંખ્યા(s, opt, dst, 1, 1, opt->default_val.i64, 1);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_DOUBLE:
            સ્થિતિ AV_OPT_TYPE_FLOAT: {
                દ્વિગુણ val;
                val = opt->default_val.dbl;
                write_સંખ્યા(s, opt, dst, val, 1, 1, 1);
            }
            તોડો;
            સ્થિતિ AV_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val.dbl, INT_MAX);
                write_સંખ્યા(s, opt, dst, 1, val.den, val.અંક, 1);
            }
            તોડો;
            સ્થિતિ AV_OPT_TYPE_COLOR:
                set_string_color(s, opt, opt->default_val.str, dst);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_STRING:
                set_string(s, opt, opt->default_val.str, dst);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
                set_string_image_size(s, opt, opt->default_val.str, dst);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
                set_string_video_rate(s, opt, opt->default_val.str, dst);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_દ્વિઅંકી:
                set_string_દ્વિઅંકી(s, opt, opt->default_val.str, dst);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_CHLAYOUT:
                set_string_channel_layout(s, opt, opt->default_val.str, dst);
                તોડો;
            સ્થિતિ AV_OPT_TYPE_DICT:
                set_string_dict(s, opt, opt->default_val.str, dst);
                તોડો;
        મૂળભૂત:
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
સ્થિર પૂર્ણાંક parse_ચાવી_કિંમત_pair(શૂન્ય *ctx, અચલ અક્ષર **buf,
                                અચલ અક્ષર *ચાવી_val_sep, અચલ અક્ષર *pairs_sep)
{
    અક્ષર *ચાવી = av_get_token(buf, ચાવી_val_sep);
    અક્ષર *val;
    પૂર્ણાંક ret;

    જો (!ચાવી)
        પાછા AVERROR(ENOMEM);

    જો (*ચાવી && strspn(*buf, ચાવી_val_sep)) {
        (*buf)++;
        val = av_get_token(buf, pairs_sep);
        જો (!val) {
            av_freep(&ચાવી);
            પાછા AVERROR(ENOMEM);
        }
    } નહીંતર {
        av_log(ctx, AV_LOG_ERROR, "Missing key or no key/value separator found after key '%s'\n", ચાવી);
        av_free(ચાવી);
        પાછા AVERROR(EINVAL);
    }

    av_log(ctx, AV_LOG_DEBUG, "Setting entry with key '%s' to value '%s'\n", ચાવી, val);

    ret = av_opt_set(ctx, ચાવી, val, AV_OPT_શોધ_CHILDREN);
    જો (ret == AVERROR_OPTION_NOT_FOUND)
        av_log(ctx, AV_LOG_ERROR, "Key '%s' not found.\n", ચાવી);

    av_free(ચાવી);
    av_free(val);
    પાછા ret;
}

પૂર્ણાંક av_set_options_string(શૂન્ય *ctx, અચલ અક્ષર *opts,
                          અચલ અક્ષર *ચાવી_val_sep, અચલ અક્ષર *pairs_sep)
{
    પૂર્ણાંક ret, ગણતરી = 0;

    જો (!opts)
        પાછા 0;

    જ્યારે (*opts) {
        જો ((ret = parse_ચાવી_કિંમત_pair(ctx, &opts, ચાવી_val_sep, pairs_sep)) < 0)
            પાછા ret;
        ગણતરી++;

        જો (*opts)
            opts++;
    }

    પાછા ગણતરી;
}

#define WHITESPACES " \n\t\r"

સ્થિર પૂર્ણાંક is_ચાવી_char(અક્ષર c)
{
    પાછા (unsigned)((c | 32) - 'a') < 26 ||
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
સ્થિર પૂર્ણાંક get_ચાવી(અચલ અક્ષર **ropts, અચલ અક્ષર *delim, અક્ષર **rkey)
{
    અચલ અક્ષર *opts = *ropts;
    અચલ અક્ષર *ચાવી_start, *ચાવી_end;

    ચાવી_start = opts += strspn(opts, WHITESPACES);
    જ્યારે (is_ચાવી_char(*opts))
        opts++;
    ચાવી_end = opts;
    opts += strspn(opts, WHITESPACES);
    જો (!*opts || !strchr(delim, *opts))
        પાછા AVERROR(EINVAL);
    opts++;
    જો (!(*rkey = av_malloc(ચાવી_end - ચાવી_start + 1)))
        પાછા AVERROR(ENOMEM);
    memcpy(*rkey, ચાવી_start, ચાવી_end - ચાવી_start);
    (*rkey)[ચાવી_end - ચાવી_start] = 0;
    *ropts = opts;
    પાછા 0;
}

પૂર્ણાંક av_opt_get_ચાવી_કિંમત(અચલ અક્ષર **ropts,
                         અચલ અક્ષર *ચાવી_val_sep, અચલ અક્ષર *pairs_sep,
                         unsigned flags,
                         અક્ષર **rkey, અક્ષર **rval)
{
    પૂર્ણાંક ret;
    અક્ષર *ચાવી = ખાલી, *val;
    અચલ અક્ષર *opts = *ropts;

    જો ((ret = get_ચાવી(&opts, ચાવી_val_sep, &ચાવી)) < 0 &&
        !(flags & AV_OPT_FLAG_IMPLICIT_ચાવી))
        પાછા AVERROR(EINVAL);
    જો (!(val = av_get_token(&opts, pairs_sep))) {
        av_free(ચાવી);
        પાછા AVERROR(ENOMEM);
    }
    *ropts = opts;
    *rkey  = ચાવી;
    *rval  = val;
    પાછા 0;
}

પૂર્ણાંક av_opt_set_from_string(શૂન્ય *ctx, અચલ અક્ષર *opts,
                           અચલ અક્ષર *અચલ *shorthand,
                           અચલ અક્ષર *ચાવી_val_sep, અચલ અક્ષર *pairs_sep)
{
    પૂર્ણાંક ret, ગણતરી = 0;
    અચલ અક્ષર *dummy_shorthand = ખાલી;
    અચલ અક્ષર *ચાવી;

    જો (!opts)
        પાછા 0;
    જો (!shorthand)
        shorthand = &dummy_shorthand;

    જ્યારે (*opts) {
        અક્ષર *parsed_ચાવી, *કિંમત;
        ret = av_opt_get_ચાવી_કિંમત(&opts, ચાવી_val_sep, pairs_sep,
                                   *shorthand ? AV_OPT_FLAG_IMPLICIT_ચાવી : 0,
                                   &parsed_ચાવી, &કિંમત);
        જો (ret < 0) {
            જો (ret == AVERROR(EINVAL))
                av_log(ctx, AV_LOG_ERROR, "No option name near '%s'\n", opts);
            નહીંતર
                av_log(ctx, AV_LOG_ERROR, "Unable to parse '%s': %s\n", opts,
                       av_err2str(ret));
            પાછા ret;
        }
        જો (*opts)
            opts++;
        જો (parsed_ચાવી) {
            ચાવી = parsed_ચાવી;
            જ્યારે (*shorthand) /* discard all remaining shorthand */
                shorthand++;
        } નહીંતર {
            ચાવી = *(shorthand++);
        }

        av_log(ctx, AV_LOG_DEBUG, "Setting '%s' to value '%s'\n", ચાવી, કિંમત);
        જો ((ret = av_opt_set(ctx, ચાવી, કિંમત, 0)) < 0) {
            જો (ret == AVERROR_OPTION_NOT_FOUND)
                av_log(ctx, AV_LOG_ERROR, "Option '%s' not found\n", ચાવી);
            av_free(કિંમત);
            av_free(parsed_ચાવી);
            પાછા ret;
        }

        av_free(કિંમત);
        av_free(parsed_ચાવી);
        ગણતરી++;
    }
    પાછા ગણતરી;
}

શૂન્ય av_opt_free(શૂન્ય *obj)
{
    અચલ AVOption *o = ખાલી;
    જ્યારે ((o = av_opt_next(obj, o))) {
        શૂન્ય *pitem = (uint8_t *)obj + o->offset;

        જો (o->type & AV_OPT_TYPE_FLAG_ARRAY)
            opt_free_array(o, pitem, opt_array_pcount(pitem));
        નહીંતર
            opt_free_elem(o->type, pitem);
    }
}

પૂર્ણાંક av_opt_set_dict2(શૂન્ય *obj, AVDictionary **options, પૂર્ણાંક શોધ_flags)
{
    અચલ AVDictionaryEntry *t = ખાલી;
    AVDictionary    *tmp = ખાલી;
    પૂર્ણાંક ret;

    જો (!options)
        પાછા 0;

    જ્યારે ((t = av_dict_iterate(*options, t))) {
        ret = av_opt_set(obj, t->ચાવી, t->કિંમત, શોધ_flags);
        જો (ret == AVERROR_OPTION_NOT_FOUND)
            ret = av_dict_set(&tmp, t->ચાવી, t->કિંમત, AV_DICT_MULTIKEY);
        જો (ret < 0) {
            av_log(obj, AV_LOG_ERROR, "Error setting option %s to value %s.\n", t->ચાવી, t->કિંમત);
            av_dict_free(&tmp);
            પાછા ret;
        }
    }
    av_dict_free(options);
    *options = tmp;
    પાછા 0;
}

પૂર્ણાંક av_opt_set_dict(શૂન્ય *obj, AVDictionary **options)
{
    પાછા av_opt_set_dict2(obj, options, 0);
}

અચલ AVOption *av_opt_find(શૂન્ય *obj, અચલ અક્ષર *name, અચલ અક્ષર *unit,
                            પૂર્ણાંક opt_flags, પૂર્ણાંક શોધ_flags)
{
    પાછા av_opt_find2(obj, name, unit, opt_flags, શોધ_flags, ખાલી);
}

અચલ AVOption *av_opt_find2(શૂન્ય *obj, અચલ અક્ષર *name, અચલ અક્ષર *unit,
                             પૂર્ણાંક opt_flags, પૂર્ણાંક શોધ_flags, શૂન્ય **target_obj)
{
    અચલ AVClass  *c;
    અચલ AVOption *o = ખાલી;

    જો(!obj)
        પાછા ખાલી;

    c= *(AVClass**)obj;

    જો (!c)
        પાછા ખાલી;

    જો (શોધ_flags & AV_OPT_શોધ_CHILDREN) {
        જો (શોધ_flags & AV_OPT_શોધ_FAKE_OBJ) {
            શૂન્ય *iter = ખાલી;
            અચલ AVClass *child;
            જ્યારે (child = av_opt_child_class_iterate(c, &iter))
                જો (o = av_opt_find2(&child, name, unit, opt_flags, શોધ_flags, ખાલી))
                    પાછા o;
        } નહીંતર {
            શૂન્ય *child = ખાલી;
            જ્યારે (child = av_opt_child_next(obj, child))
                જો (o = av_opt_find2(child, name, unit, opt_flags, શોધ_flags, target_obj))
                    પાછા o;
        }
    }

    જ્યારે (o = av_opt_next(obj, o)) {
        જો (!strcmp(o->name, name) && (o->flags & opt_flags) == opt_flags &&
            ((!unit && o->type != AV_OPT_TYPE_CONST) ||
             (unit  && o->type == AV_OPT_TYPE_CONST && o->unit && !strcmp(o->unit, unit)))) {
            જો (target_obj) {
                જો (!(શોધ_flags & AV_OPT_શોધ_FAKE_OBJ))
                    *target_obj = obj;
                નહીંતર
                    *target_obj = ખાલી;
            }
            પાછા o;
        }
    }
    પાછા ખાલી;
}

શૂન્ય *av_opt_child_next(શૂન્ય *obj, શૂન્ય *prev)
{
    અચલ AVClass *c = *(AVClass **)obj;
    જો (c->child_next)
        પાછા c->child_next(obj, prev);
    પાછા ખાલી;
}

અચલ AVClass *av_opt_child_class_iterate(અચલ AVClass *parent, શૂન્ય **iter)
{
    જો (parent->child_class_iterate)
        પાછા parent->child_class_iterate(iter);
    પાછા ખાલી;
}

સ્થિર પૂર્ણાંક opt_copy_elem(શૂન્ય *logctx, ગણના AVOptionType type,
                         શૂન્ય *dst, અચલ શૂન્ય *src)
{
    જો (type == AV_OPT_TYPE_STRING) {
        અચલ અક્ષર *src_str = *(અચલ અક્ષર *અચલ *)src;
        અક્ષર         **dstp =  (અક્ષર **)dst;
        જો (*dstp != src_str)
            av_freep(dstp);
        જો (src_str) {
            *dstp = av_strdup(src_str);
            જો (!*dstp)
                પાછા AVERROR(ENOMEM);
        }
    } નહીંતર જો (type == AV_OPT_TYPE_દ્વિઅંકી) {
        અચલ uint8_t *અચલ *src8 = (અચલ uint8_t *અચલ *)src;
        uint8_t             **dst8 = (uint8_t **)dst;
        પૂર્ણાંક len = *(અચલ પૂર્ણાંક *)(src8 + 1);
        જો (*dst8 != *src8)
            av_freep(dst8);
        *dst8 = av_memdup(*src8, len);
        જો (len && !*dst8) {
            *(પૂર્ણાંક *)(dst8 + 1) = 0;
            પાછા AVERROR(ENOMEM);
        }
        *(પૂર્ણાંક *)(dst8 + 1) = len;
    } નહીંતર જો (type == AV_OPT_TYPE_CONST) {
        // do nothing
    } નહીંતર જો (type == AV_OPT_TYPE_DICT) {
        અચલ AVDictionary *sdict = *(અચલ AVDictionary * અચલ *)src;
        AVDictionary     **ddictp = (AVDictionary **)dst;
        જો (sdict != *ddictp)
            av_dict_free(ddictp);
        *ddictp = ખાલી;
        પાછા av_dict_copy(ddictp, sdict, 0);
    } નહીંતર જો (type == AV_OPT_TYPE_CHLAYOUT) {
        અચલ AVChannelLayout *slayout = (અચલ AVChannelLayout *)src;
        AVChannelLayout *dlayout = (AVChannelLayout *)dst;
        જો (dlayout != slayout) {
            જો (dlayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                slayout->order == AV_CHANNEL_ORDER_CUSTOM &&
                dlayout->u.map == slayout->u.map)
                dlayout->u.map = ખાલી;
            પાછા av_channel_layout_copy(dst, src);
        }
    } નહીંતર જો (opt_is_pod(type)) {
        size_t size = opt_type_desc[type].size;
        memcpy(dst, src, size);
    } નહીંતર {
        av_log(logctx, AV_LOG_ERROR, "Unhandled option type: %d\n", type);
        પાછા AVERROR(EINVAL);
    }

    પાછા 0;
}

સ્થિર પૂર્ણાંક opt_copy_array(શૂન્ય *logctx, અચલ AVOption *o,
                          શૂન્ય **pdst, અચલ શૂન્ય * અચલ *psrc)
{
    unsigned nb_elems = *opt_array_pcount(psrc);
    શૂન્ય         *dst = ખાલી;
    પૂર્ણાંક ret;

    જો (*pdst == *psrc) {
        *pdst                   = ખાલી;
        *opt_array_pcount(pdst) = 0;
    }

    opt_free_array(o, pdst, opt_array_pcount(pdst));

    dst = av_calloc(nb_elems, opt_type_desc[TYPE_BASE(o->type)].size);
    જો (!dst)
        પાછા AVERROR(ENOMEM);

    માટે (unsigned i = 0; i < nb_elems; i++) {
        ret = opt_copy_elem(logctx, TYPE_BASE(o->type),
                            opt_array_pelem(o, dst, i),
                            opt_array_pelem(o, *(શૂન્ય**)psrc, i));
        જો (ret < 0) {
            opt_free_array(o, &dst, &nb_elems);
            પાછા ret;
        }
    }

    *pdst                   = dst;
    *opt_array_pcount(pdst) = nb_elems;

    પાછા 0;
}

પૂર્ણાંક av_opt_copy(શૂન્ય *dst, અચલ શૂન્ય *src)
{
    અચલ AVOption *o = ખાલી;
    અચલ AVClass *c;
    પૂર્ણાંક ret = 0;

    જો (!src)
        પાછા AVERROR(EINVAL);

    c = *(AVClass **)src;
    જો (!c || c != *(AVClass **)dst)
        પાછા AVERROR(EINVAL);

    જ્યારે ((o = av_opt_next(src, o))) {
        શૂન્ય *field_dst = (uint8_t *)dst + o->offset;
        શૂન્ય *field_src = (uint8_t *)src + o->offset;

        પૂર્ણાંક err = (o->type & AV_OPT_TYPE_FLAG_ARRAY)                 ?
                  opt_copy_array(dst, o,       field_dst, field_src) :
                  opt_copy_elem (dst, o->type, field_dst, field_src);
        જો (err < 0)
            ret = err;
    }
    પાછા ret;
}

પૂર્ણાંક av_opt_get_array_size(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags,
                          unsigned પૂર્ણાંક *out_val)
{
    શૂન્ય *target_obj, *parray;
    અચલ AVOption *o;

    o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (!(o->type & AV_OPT_TYPE_FLAG_ARRAY))
        પાછા AVERROR(EINVAL);

    parray = (uint8_t *)target_obj + o->offset;
    *out_val = *opt_array_pcount(parray);

    પાછા 0;
}

પૂર્ણાંક av_opt_get_array(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags,
                     unsigned પૂર્ણાંક start_elem, unsigned પૂર્ણાંક nb_elems,
                     ગણના AVOptionType out_type, શૂન્ય *out_val)
{
    અચલ size_t elem_size_out = opt_type_desc[TYPE_BASE(out_type)].size;

    અચલ AVOption *o;
    શૂન્ય *target_obj;

    અચલ શૂન્ય *parray;
    unsigned array_size;

    પૂર્ણાંક ret;

    o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target_obj);
    જો (!o || !target_obj)
        પાછા AVERROR_OPTION_NOT_FOUND;
    જો (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (out_type & AV_OPT_TYPE_FLAG_ARRAY))
        પાછા AVERROR(EINVAL);

    parray     = (uint8_t *)target_obj + o->offset;
    array_size = *opt_array_pcount(parray);

    જો (start_elem >= array_size ||
        array_size - start_elem < nb_elems)
        પાછા AVERROR(EINVAL);

    માટે (unsigned i = 0; i < nb_elems; i++) {
        અચલ શૂન્ય *src = opt_array_pelem(o, *(શૂન્ય**)parray, start_elem + i);
        શૂન્ય       *dst = (uint8_t*)out_val + i * elem_size_out;

        જો (out_type == TYPE_BASE(o->type)) {
            ret = opt_copy_elem(obj, out_type, dst, src);
            જો (ret < 0)
                જાઓ fail;
        } નહીંતર જો (out_type == AV_OPT_TYPE_STRING) {
            uint8_t buf[128], *out = buf;

            ret = opt_get_elem(o, &out, કદ(buf), src, શોધ_flags);
            જો (ret < 0)
                જાઓ fail;

            જો (out == buf) {
                out = av_strdup(buf);
                જો (!out) {
                    ret = AVERROR(ENOMEM);
                    જાઓ fail;
                }
            }

            *(uint8_t**)dst = out;
        } નહીંતર જો (out_type == AV_OPT_TYPE_INT64    ||
                   out_type == AV_OPT_TYPE_DOUBLE   ||
                   out_type == AV_OPT_TYPE_RATIONAL) {
            દ્વિગુણ     અંક = 1.0;
            પૂર્ણાંક        den = 1;
            int64_t intnum = 1;

            ret = read_સંખ્યા(o, src, &અંક, &den, &intnum);
            જો (ret < 0)
                જાઓ fail;

            પસંદગી (out_type) {
            સ્થિતિ AV_OPT_TYPE_INT64:
                *(int64_t*)dst = (અંક == den) ?  intnum : અંક * intnum / den;
                તોડો;
            સ્થિતિ AV_OPT_TYPE_DOUBLE:
                *(દ્વિગુણ*)dst = અંક * intnum / den;
                તોડો;
            સ્થિતિ AV_OPT_TYPE_RATIONAL:
                *(AVRational*)dst = (અંક == 1.0 && (પૂર્ણાંક)intnum == intnum) ?
                                    (AVRational){ intnum, den }           :
                                    double_to_rational(અંક * intnum / den);
                તોડો;
            મૂળભૂત: av_assert0(0);
            }
        } નહીંતર
            પાછા AVERROR(ENOSYS);
    }

    પાછા 0;
fail:
    માટે (unsigned i = 0; i < nb_elems; i++)
        opt_free_elem(out_type, (uint8_t*)out_val + i * elem_size_out);
    પાછા ret;
}

પૂર્ણાંક av_opt_set_array(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags,
                     unsigned પૂર્ણાંક start_elem, unsigned પૂર્ણાંક nb_elems,
                     ગણના AVOptionType val_type, અચલ શૂન્ય *val)
{
    અચલ size_t elem_size_val = opt_type_desc[TYPE_BASE(val_type)].size;

    અચલ AVOption *o;
    અચલ AVOptionArrayDef *arr;
    શૂન્ય *target_obj;

    શૂન્ય *parray;
    શૂન્ય *new_elems;
    unsigned *array_size, new_size;
    size_t elem_size;

    પૂર્ણાંક ret = 0;

    ret = opt_set_init(obj, name, શોધ_flags, 0, &target_obj, &o, &parray);
    જો (ret < 0)
        પાછા ret;

    જો (!(o->type & AV_OPT_TYPE_FLAG_ARRAY) ||
        (val_type & AV_OPT_TYPE_FLAG_ARRAY))
        પાછા AVERROR(EINVAL);

    arr        = o->default_val.arr;
    array_size = opt_array_pcount(parray);
    elem_size  = opt_type_desc[TYPE_BASE(o->type)].size;

    જો (start_elem > *array_size)
        પાછા AVERROR(EINVAL);

    // compute new array size
    જો (!val) {
        જો (*array_size - start_elem < nb_elems)
            પાછા AVERROR(EINVAL);

        new_size = *array_size - nb_elems;
    } નહીંતર જો (શોધ_flags & AV_OPT_ARRAY_REPLACE) {
        જો (start_elem >= UINT_MAX - nb_elems)
            પાછા AVERROR(EINVAL);

        new_size = FFMAX(*array_size, start_elem + nb_elems);
    } નહીંતર {
        જો (nb_elems >= UINT_MAX - *array_size)
            પાછા AVERROR(EINVAL);

        new_size = *array_size + nb_elems;
    }

    જો (arr &&
        ((arr->size_max && new_size > arr->size_max) ||
         (arr->size_min && new_size < arr->size_min)))
        પાછા AVERROR(EINVAL);

    // desired operation is shrinking the array
    જો (!val) {
        શૂન્ય *array = *(શૂન્ય**)parray;

        માટે (unsigned i = 0; i < nb_elems; i++) {
            opt_free_elem(o->type,
                          opt_array_pelem(o, array, start_elem + i));
        }

        જો (new_size > 0) {
            memmove(opt_array_pelem(o, array, start_elem),
                    opt_array_pelem(o, array, start_elem + nb_elems),
                    elem_size * (*array_size - start_elem - nb_elems));

            array = av_realloc_array(array, new_size, elem_size);
            જો (!array)
                પાછા AVERROR(ENOMEM);

            *(શૂન્ય**)parray = array;
        } નહીંતર
            av_freep(parray);

        *array_size = new_size;

        પાછા 0;
    }

    // otherwise, desired operation is insert/replace;
    // first, store new elements in a separate array to simplify
    // rollback on failure
    new_elems = av_calloc(nb_elems, elem_size);
    જો (!new_elems)
        પાછા AVERROR(ENOMEM);

    // convert/validate each new element
    માટે (unsigned i = 0; i < nb_elems; i++) {
        શૂન્ય       *dst = opt_array_pelem(o, new_elems, i);
        અચલ શૂન્ય *src = (uint8_t*)val + i * elem_size_val;

        દ્વિગુણ     અંક = 1.0;
        પૂર્ણાંક        den = 1;
        int64_t intnum = 1;

        જો (val_type == TYPE_BASE(o->type)) {
            પૂર્ણાંક err;

            ret = opt_copy_elem(obj, val_type, dst, src);
            જો (ret < 0)
                જાઓ fail;

            // validate the range for numeric options
            err = read_સંખ્યા(o, dst, &અંક, &den, &intnum);
            જો (err >= 0 && TYPE_BASE(o->type) != AV_OPT_TYPE_FLAGS &&
                (!den || o->max * den < અંક * intnum || o->min * den > અંક * intnum)) {
                અંક = den ? અંક * intnum / den : (અંક && intnum ? INFINITY : NAN);
                av_log(obj, AV_LOG_ERROR, "Cannot set array element %u for "
                       "parameter '%s': value %f out of range [%g - %g]\n",
                       start_elem + i, o->name, અંક, o->min, o->max);
                ret = AVERROR(ERANGE);
                જાઓ fail;
            }
        } નહીંતર જો (val_type == AV_OPT_TYPE_STRING) {
            ret = opt_set_elem(obj, target_obj, o, *(અચલ અક્ષર **)src, dst);
            જો (ret < 0)
                જાઓ fail;
        } નહીંતર જો (val_type == AV_OPT_TYPE_INT ||
              val_type == AV_OPT_TYPE_INT64    ||
              val_type == AV_OPT_TYPE_FLOAT    ||
              val_type == AV_OPT_TYPE_DOUBLE   ||
              val_type == AV_OPT_TYPE_RATIONAL) {

            પસંદગી (val_type) {
            સ્થિતિ AV_OPT_TYPE_INT:       intnum = *(પૂર્ણાંક*)src;                તોડો;
            સ્થિતિ AV_OPT_TYPE_INT64:     intnum = *(int64_t*)src;            તોડો;
            સ્થિતિ AV_OPT_TYPE_FLOAT:     અંક    = *(દશાંશ*)src;              તોડો;
            સ્થિતિ AV_OPT_TYPE_DOUBLE:    અંક    = *(દ્વિગુણ*)src;             તોડો;
            સ્થિતિ AV_OPT_TYPE_RATIONAL:  intnum = ((AVRational*)src)->અંક;
                                        den    = ((AVRational*)src)->den;   તોડો;
            મૂળભૂત: av_assert0(0);
            }

            ret = write_સંખ્યા(obj, o, dst, અંક, den, intnum, 0);
            જો (ret < 0)
                જાઓ fail;
        } નહીંતર {
            ret = AVERROR(ENOSYS);
            જાઓ fail;
        }
    }

    // commit new elements to the array
    જો (start_elem == 0 && nb_elems == new_size) {
        // replacing the existing array entirely
        opt_free_array(o, parray, array_size);
        *(શૂન્ય**)parray = new_elems;
        *array_size     = nb_elems;

        new_elems = ખાલી;
        nb_elems  = 0;
    } નહીંતર {
        શૂન્ય *array = av_realloc_array(*(શૂન્ય**)parray, new_size, elem_size);
        જો (!array) {
            ret = AVERROR(ENOMEM);
            જાઓ fail;
        }

        જો (શોધ_flags & AV_OPT_ARRAY_REPLACE) {
            // free the elements being overwritten
            માટે (unsigned i = start_elem; i < FFMIN(start_elem + nb_elems, *array_size); i++)
                opt_free_elem(o->type, opt_array_pelem(o, array, i));
        } નહીંતર {
            // shift existing elements to the end
            memmove(opt_array_pelem(o, array, start_elem + nb_elems),
                    opt_array_pelem(o, array, start_elem),
                    elem_size * (*array_size - start_elem));
        }

        memcpy((uint8_t*)array + elem_size * start_elem, new_elems, elem_size * nb_elems);

        av_freep(&new_elems);
        nb_elems = 0;

        *(શૂન્ય**)parray = array;
        *array_size     = new_size;
    }

fail:
    opt_free_array(o, &new_elems, &nb_elems);

    પાછા ret;
}

પૂર્ણાંક av_opt_query_ranges(AVOptionRanges **ranges_arg, શૂન્ય *obj, અચલ અક્ષર *ચાવી, પૂર્ણાંક flags)
{
    પૂર્ણાંક ret;
    અચલ AVClass *c = *(AVClass**)obj;
    પૂર્ણાંક (*callback)(AVOptionRanges **, શૂન્ય *obj, અચલ અક્ષર *ચાવી, પૂર્ણાંક flags) = c->query_ranges;

    જો (!callback)
        callback = av_opt_query_ranges_default;

    ret = callback(ranges_arg, obj, ચાવી, flags);
    જો (ret >= 0) {
        જો (!(flags & AV_OPT_MULTI_COMPONENT_RANGE))
            ret = 1;
        (*ranges_arg)->nb_components = ret;
    }
    પાછા ret;
}

પૂર્ણાંક av_opt_query_ranges_default(AVOptionRanges **ranges_arg, શૂન્ય *obj, અચલ અક્ષર *ચાવી, પૂર્ણાંક flags)
{
    AVOptionRanges *ranges = av_mallocz(કદ(*ranges));
    AVOptionRange **range_array = av_mallocz(કદ(શૂન્ય*));
    AVOptionRange *range = av_mallocz(કદ(*range));
    અચલ AVOption *field = av_opt_find(obj, ચાવી, ખાલી, 0, flags);
    પૂર્ણાંક ret;

    *ranges_arg = ખાલી;

    જો (!ranges || !range || !range_array || !field) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    ranges->range = range_array;
    ranges->range[0] = range;
    ranges->nb_ranges = 1;
    ranges->nb_components = 1;
    range->is_range = 1;
    range->કિંમત_min = field->min;
    range->કિંમત_max = field->max;

    પસંદગી (field->type) {
    સ્થિતિ AV_OPT_TYPE_BOOL:
    સ્થિતિ AV_OPT_TYPE_INT:
    સ્થિતિ AV_OPT_TYPE_UINT:
    સ્થિતિ AV_OPT_TYPE_INT64:
    સ્થિતિ AV_OPT_TYPE_UINT64:
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
    સ્થિતિ AV_OPT_TYPE_FLOAT:
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
    સ્થિતિ AV_OPT_TYPE_DURATION:
    સ્થિતિ AV_OPT_TYPE_COLOR:
        તોડો;
    સ્થિતિ AV_OPT_TYPE_STRING:
        range->component_min = 0;
        range->component_max = 0x10FFFF; // max unicode value
        range->કિંમત_min = -1;
        range->કિંમત_max = INT_MAX;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_RATIONAL:
        range->component_min = INT_MIN;
        range->component_max = INT_MAX;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
        range->component_min = 0;
        range->component_max = INT_MAX/128/8;
        range->કિંમત_min = 0;
        range->કિંમત_max = INT_MAX/8;
        તોડો;
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
        range->component_min = 1;
        range->component_max = INT_MAX;
        range->કિંમત_min = 1;
        range->કિંમત_max = INT_MAX;
        તોડો;
    મૂળભૂત:
        ret = AVERROR(ENOSYS);
        જાઓ fail;
    }

    *ranges_arg = ranges;
    પાછા 1;
fail:
    av_free(ranges);
    av_free(range);
    av_free(range_array);
    પાછા ret;
}

શૂન્ય av_opt_freep_ranges(AVOptionRanges **rangesp)
{
    પૂર્ણાંક i;
    AVOptionRanges *ranges = *rangesp;

    જો (!ranges)
        પાછા;

    માટે (i = 0; i < ranges->nb_ranges * ranges->nb_components; i++) {
        AVOptionRange *range = ranges->range[i];
        જો (range) {
            av_freep(&range->str);
            av_freep(&ranges->range[i]);
        }
    }
    av_freep(&ranges->range);
    av_freep(rangesp);
}

પૂર્ણાંક av_opt_is_set_to_default(શૂન્ય *obj, અચલ AVOption *o)
{
    int64_t i64;
    દ્વિગુણ d;
    AVRational q;
    પૂર્ણાંક ret, w, h;
    અક્ષર *str;
    શૂન્ય *dst;

    જો (!o || !obj)
        પાછા AVERROR(EINVAL);

    dst = ((uint8_t*)obj) + o->offset;

    જો (o->type & AV_OPT_TYPE_FLAG_ARRAY) {
        અચલ અક્ષર *def = o->default_val.arr ? o->default_val.arr->def : ખાલી;
        uint8_t *val;

        ret = opt_get_array(o, dst, &val);
        જો (ret < 0)
            પાછા ret;

        જો (!!val != !!def)
            ret = 0;
        નહીંતર જો (val)
            ret = !strcmp(val, def);
        નહીંતર
            ret = 1;

        av_freep(&val);

        પાછા ret;
    }

    પસંદગી (o->type) {
    સ્થિતિ AV_OPT_TYPE_CONST:
        પાછા 1;
    સ્થિતિ AV_OPT_TYPE_BOOL:
    સ્થિતિ AV_OPT_TYPE_FLAGS:
    સ્થિતિ AV_OPT_TYPE_PIXEL_FMT:
    સ્થિતિ AV_OPT_TYPE_SAMPLE_FMT:
    સ્થિતિ AV_OPT_TYPE_INT:
    સ્થિતિ AV_OPT_TYPE_UINT:
    સ્થિતિ AV_OPT_TYPE_DURATION:
    સ્થિતિ AV_OPT_TYPE_INT64:
    સ્થિતિ AV_OPT_TYPE_UINT64:
        read_સંખ્યા(o, dst, ખાલી, ખાલી, &i64);
        પાછા o->default_val.i64 == i64;
    સ્થિતિ AV_OPT_TYPE_CHLAYOUT: {
        AVChannelLayout ch_layout = { 0 };
        જો (o->default_val.str) {
            જો ((ret = av_channel_layout_from_string(&ch_layout, o->default_val.str)) < 0)
                પાછા ret;
        }
        ret = !av_channel_layout_compare((AVChannelLayout *)dst, &ch_layout);
        av_channel_layout_uninit(&ch_layout);
        પાછા ret;
    }
    સ્થિતિ AV_OPT_TYPE_STRING:
        str = *(અક્ષર **)dst;
        જો (str == o->default_val.str) //2 NULLs
            પાછા 1;
        જો (!str || !o->default_val.str) //1 NULL
            પાછા 0;
        પાછા !strcmp(str, o->default_val.str);
    સ્થિતિ AV_OPT_TYPE_DOUBLE:
        d = *(દ્વિગુણ *)dst;
        પાછા o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    સ્થિતિ AV_OPT_TYPE_FLOAT:
        d = *(દશાંશ *)dst;
        પાછા (દશાંશ)o->default_val.dbl == d || isnan(d) && isnan(o->default_val.dbl);
    સ્થિતિ AV_OPT_TYPE_RATIONAL: {
        AVRational v = *(AVRational *) dst;
        q = av_d2q(o->default_val.dbl, INT_MAX);
        પાછા !av_cmp_q(v, q) || (!q.den && !v.den);
    }
    સ્થિતિ AV_OPT_TYPE_દ્વિઅંકી: {
        સંરચના {
            uint8_t *data;
            પૂર્ણાંક size;
        } tmp = {0};
        પૂર્ણાંક opt_size = *(પૂર્ણાંક *)((શૂન્ય **)dst + 1);
        શૂન્ય *opt_ptr = *(શૂન્ય **)dst;
        જો (!opt_size && (!o->default_val.str || !strlen(o->default_val.str)))
            પાછા 1;
        જો (!opt_size ||  !o->default_val.str || !strlen(o->default_val.str ))
            પાછા 0;
        જો (opt_size != strlen(o->default_val.str) / 2)
            પાછા 0;
        ret = set_string_દ્વિઅંકી(ખાલી, ખાલી, o->default_val.str, &tmp.data);
        જો (!ret)
            ret = !memcmp(opt_ptr, tmp.data, tmp.size);
        av_free(tmp.data);
        પાછા ret;
    }
    સ્થિતિ AV_OPT_TYPE_DICT: {
        AVDictionary *dict1 = ખાલી;
        AVDictionary *dict2 = *(AVDictionary **)dst;
        અચલ AVDictionaryEntry *en1 = ખાલી;
        અચલ AVDictionaryEntry *en2 = ખાલી;
        ret = av_dict_parse_string(&dict1, o->default_val.str, "=", ":", 0);
        જો (ret < 0) {
            av_dict_free(&dict1);
            પાછા ret;
        }
        કરો {
            en1 = av_dict_iterate(dict1, en1);
            en2 = av_dict_iterate(dict2, en2);
        } જ્યારે (en1 && en2 && !strcmp(en1->ચાવી, en2->ચાવી) && !strcmp(en1->કિંમત, en2->કિંમત));
        av_dict_free(&dict1);
        પાછા (!en1 && !en2);
    }
    સ્થિતિ AV_OPT_TYPE_IMAGE_SIZE:
        જો (!o->default_val.str || !strcmp(o->default_val.str, "none"))
            w = h = 0;
        નહીંતર જો ((ret = av_parse_video_size(&w, &h, o->default_val.str)) < 0)
            પાછા ret;
        પાછા (w == *(પૂર્ણાંક *)dst) && (h == *((પૂર્ણાંક *)dst+1));
    સ્થિતિ AV_OPT_TYPE_VIDEO_RATE:
        q = (AVRational){0, 0};
        જો (o->default_val.str) {
            જો ((ret = av_parse_video_rate(&q, o->default_val.str)) < 0)
                પાછા ret;
        }
        પાછા !av_cmp_q(*(AVRational*)dst, q);
    સ્થિતિ AV_OPT_TYPE_COLOR: {
        uint8_t color[4] = {0, 0, 0, 0};
        જો (o->default_val.str) {
            જો ((ret = av_parse_color(color, o->default_val.str, -1, ખાલી)) < 0)
                પાછા ret;
        }
        પાછા !memcmp(color, dst, કદ(color));
    }
    મૂળભૂત:
        av_log(obj, AV_LOG_WARNING, "Not supported option type: %d, option name: %s\n", o->type, o->name);
        તોડો;
    }
    પાછા AVERROR_PATCHWELCOME;
}

પૂર્ણાંક av_opt_is_set_to_default_by_name(શૂન્ય *obj, અચલ અક્ષર *name, પૂર્ણાંક શોધ_flags)
{
    અચલ AVOption *o;
    શૂન્ય *target;
    જો (!obj)
        પાછા AVERROR(EINVAL);
    o = av_opt_find2(obj, name, ખાલી, 0, શોધ_flags, &target);
    જો (!o)
        પાછા AVERROR_OPTION_NOT_FOUND;
    પાછા av_opt_is_set_to_default(target, o);
}

સ્થિર પૂર્ણાંક opt_serialize(શૂન્ય *obj, પૂર્ણાંક opt_flags, પૂર્ણાંક flags, પૂર્ણાંક *cnt,
                         AVBPrint *bprint, અચલ અક્ષર ચાવી_val_sep, અચલ અક્ષર pairs_sep)
{
    અચલ AVOption *o = ખાલી;
    શૂન્ય *child = ખાલી;
    uint8_t *buf;
    પૂર્ણાંક ret;
    અચલ અક્ષર special_chars[] = {pairs_sep, ચાવી_val_sep, '\0'};

    જો (flags & AV_OPT_SERIALIZE_શોધ_CHILDREN)
        જ્યારે (child = av_opt_child_next(obj, child)) {
            ret = opt_serialize(child, opt_flags, flags, cnt, bprint,
                                ચાવી_val_sep, pairs_sep);
            જો (ret < 0)
                પાછા ret;
        }

    જ્યારે (o = av_opt_next(obj, o)) {
        જો (o->type == AV_OPT_TYPE_CONST)
            ચાલુ;
        જો ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXCLUDE)) {
            જો ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT)) {
                જો (o->flags == opt_flags)
                    ચાલુ;
            } નહીંતર જો ((o->flags & opt_flags) == opt_flags)
                ચાલુ;
        } નહીંતર {
            જો ((flags & AV_OPT_SERIALIZE_OPT_FLAGS_EXACT) && o->flags != opt_flags)
                ચાલુ;
            નહીંતર જો (((o->flags & opt_flags) != opt_flags))
                ચાલુ;
        }
        જો (flags & AV_OPT_SERIALIZE_SKIP_DEFAULTS && av_opt_is_set_to_default(obj, o) > 0)
            ચાલુ;
        જો ((ret = av_opt_get(obj, o->name, 0, &buf)) < 0) {
            av_bprint_finalize(bprint, ખાલી);
            પાછા ret;
        }
        જો (buf) {
            જો ((*cnt)++)
                av_bprint_append_data(bprint, &pairs_sep, 1);
            av_bprint_escape(bprint, o->name, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_bprint_append_data(bprint, &ચાવી_val_sep, 1);
            av_bprint_escape(bprint, buf, special_chars, AV_ESCAPE_MODE_BACKSLASH, 0);
            av_freep(&buf);
        }
    }

    પાછા 0;
}

પૂર્ણાંક av_opt_serialize(શૂન્ય *obj, પૂર્ણાંક opt_flags, પૂર્ણાંક flags, અક્ષર **buffer,
                     અચલ અક્ષર ચાવી_val_sep, અચલ અક્ષર pairs_sep)
{
    AVBPrint bprint;
    પૂર્ણાંક ret, cnt = 0;

    જો (pairs_sep == '\0' || ચાવી_val_sep == '\0' || pairs_sep == ચાવી_val_sep ||
        pairs_sep == '\\' || ચાવી_val_sep == '\\') {
        av_log(obj, AV_LOG_ERROR, "Invalid separator(s) found.");
        પાછા AVERROR(EINVAL);
    }

    જો (!obj || !buffer)
        પાછા AVERROR(EINVAL);

    *buffer = ખાલી;
    av_bprint_init(&bprint, 64, AV_BPRINT_SIZE_UNLIMITED);

    ret = opt_serialize(obj, opt_flags, flags, &cnt, &bprint,
                        ચાવી_val_sep, pairs_sep);
    જો (ret < 0)
        પાછા ret;

    ret = av_bprint_finalize(&bprint, buffer);
    જો (ret < 0)
        પાછા ret;
    પાછા 0;
}
