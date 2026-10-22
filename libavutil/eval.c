/*
 * Copyright (c) 2002-2006 Michael Niedermayer <michaelni@gmx.at>
 * Copyright (c) 2006 Oded Shimon <ods15@ods15.dyndns.org>
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
 * simple arithmetic expression evaluator.
 *
 * see http://joe.hotchkiss.com/programming/eval/eval.html
 */

#شامل <float.h>
#شامل "attributes.h"
#شامل "avassert.h"
#شامل "avutil.h"
#شامل "common.h"
#شامل "eval.h"
#شامل "ffmath.h"
#شامل "log.h"
#شامل "mathematics.h"
#شامل "mem.h"
#شامل "sfc64.h"
#شامل "time.h"
#شامل "avstring.h"
#شامل "reverse.h"

#تعریف_کرو MAX_گہرائی 100

قسمتعریف ساخت Parser {
    ثابت AVClass *class;
    صحیح ڈھیر_اشاریہ;
    حرف *s;
    ثابت دوہرا *const_اقدار;
    ثابت حرف * ثابت *const_نام;          // NULL terminated
    دوہرا (* ثابت *funcs1)(خالی *, دوہرا a);           // NULL terminated
    ثابت حرف * ثابت *func1_نام;          // NULL terminated
    دوہرا (* ثابت *funcs2)(خالی *, دوہرا a, دوہرا b); // NULL terminated
    ثابت حرف * ثابت *func2_نام;          // NULL terminated
    خالی *opaque;
    صحیح log_انحراف;
    خالی *log_ctx;
#تعریف_کرو VARS 10
    دوہرا *var;
    FFSFC64 *prng_state;
} Parser;

ساکن ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .شے_name                 = av_default_شے_name,
    .option                    = تہی,
    .نسخہ                   = LIBAVUTIL_نسخہ_INT,
    .log_level_انحراف_انحراف   = offsetof(Parser, log_انحراف),
    .والد_log_context_انحراف = offsetof(Parser, log_ctx),
};

ساکن ثابت ساخت {
    دوہرا bin_val;
    دوہرا dec_val;
    int8_t قوت_نما;
} si_prefixes['z' - 'E' + 1] = {
    ['y'-'E']= { 8.271806125530276749e-25, 1e-24, -24 },
    ['z'-'E']= { 8.4703294725430034e-22, 1e-21, -21 },
    ['a'-'E']= { 8.6736173798840355e-19, 1e-18, -18 },
    ['f'-'E']= { 8.8817841970012523e-16, 1e-15, -15 },
    ['p'-'E']= { 9.0949470177292824e-13, 1e-12, -12 },
    ['n'-'E']= { 9.3132257461547852e-10, 1e-9,  -9 },
    ['u'-'E']= { 9.5367431640625e-7, 1e-6, -6 },
    ['m'-'E']= { 9.765625e-4, 1e-3, -3 },
    ['c'-'E']= { 9.8431332023036951e-3, 1e-2, -2 },
    ['d'-'E']= { 9.921256574801246e-2, 1e-1, -1 },
    ['h'-'E']= { 1.0159366732596479e2, 1e2, 2 },
    ['k'-'E']= { 1.024e3, 1e3, 3 },
    ['K'-'E']= { 1.024e3, 1e3, 3 },
    ['M'-'E']= { 1.048576e6, 1e6, 6 },
    ['G'-'E']= { 1.073741824e9, 1e9, 9 },
    ['T'-'E']= { 1.099511627776e12, 1e12, 12 },
    ['P'-'E']= { 1.125899906842624e15, 1e15, 15 },
    ['E'-'E']= { 1.152921504606847e18, 1e18, 18 },
    ['Z'-'E']= { 1.1805916207174113e21, 1e21, 21 },
    ['Y'-'E']= { 1.2089258196146292e24, 1e24, 24 },
};

ساکن ثابت ساخت {
    ثابت حرف *name;
    دوہرا قدر;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

دوہرا av_strtod(ثابت حرف *numstr, حرف **دم)
{
    دوہرا d;
    حرف *اگلا;
    اگر(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &اگلا, 16);
    } ورنہ
        d = strtod(numstr, &اگلا);
    /* if parsing succeeded, check for and interpret postfixes */
    اگر (اگلا!=numstr) {
        اگر (اگلا[0] == 'd' && اگلا[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            اگلا += 2;
        } ورنہ اگر (*اگلا >= 'E' && *اگلا <= 'z') {
            صحیح e= si_prefixes[*اگلا - 'E'].قوت_نما;
            اگر (e) {
                اگر (اگلا[1] == 'i') {
                    d*= si_prefixes[*اگلا - 'E'].bin_val;
                    اگلا+=2;
                } ورنہ {
                    d*= si_prefixes[*اگلا - 'E'].dec_val;
                    اگلا++;
                }
            }
        }

        اگر (*اگلا=='B') {
            d*=8;
            اگلا++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    اگر (دم)
        *دم = اگلا;
    واپس d;
}

#تعریف_کرو IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ساکن صحیح strmatch(ثابت حرف *s, ثابت حرف *سابقہ)
{
    صحیح i;
    برائے (i=0; سابقہ[i]; i++) {
        اگر (سابقہ[i] != s[i]) واپس 0;
    }
    /* return 1 only if the s identifier is terminated */
    واپس !IS_IDENTIFIER_CHAR(s[i]);
}

شمار {
    e_قدر, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_جوڑو,
    e_آخری, e_st, e_while, e_taylor, e_جڑ, e_floor, e_ceil, e_trunc, e_باری,
    e_sqrt, e_not, e_random, e_hypot, e_عاد_اعظم,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ساخت AVExpr {
    غیرعلامتی حرف type;
    غیرعلامتی حرف جڑ;
    مختصر گہرائی;
    صحیح const_اشاریہ;
    دوہرا قدر; // is sign in other types
    اتحاد {
        دوہرا (*func0)(دوہرا);
        دوہرا (*func1)(خالی *, دوہرا);
        دوہرا (*func2)(خالی *, دوہرا, دوہرا);
    } ;
    ساخت AVExpr *param[3];
};

قسمتعریف ساخت {
    AVExpr avexpr;
    دوہرا *var;
    FFSFC64 *prng_state;
} AVExpr_جڑ;

ساکن دوہرا etime(دوہرا v)
{
    واپس av_gettime() * 0.000001;
}

ساکن دوہرا eval_اظہاریہ(Parser *p, AVExpr *e)
{
    انتخاب (e->type) {
        حالت e_قدر:  واپس e->قدر;
        حالت e_const:  واپس e->قدر * p->const_اقدار[e->const_اشاریہ];
        حالت e_func0:  واپس e->قدر * e->func0(eval_اظہاریہ(p, e->param[0]));
        حالت e_func1:  واپس e->قدر * e->func1(p->opaque, eval_اظہاریہ(p, e->param[0]));
        حالت e_func2:  واپس e->قدر * e->func2(p->opaque, eval_اظہاریہ(p, e->param[0]), eval_اظہاریہ(p, e->param[1]));
        حالت e_squish: واپس e->قدر/(1+قوت_نما(4*eval_اظہاریہ(p, e->param[0])));
        حالت e_gauss: { دوہرا d = eval_اظہاریہ(p, e->param[0]); واپس e->قدر * قوت_نما(-d*d/2)/جذر(2*M_PI); }
        حالت e_ld:     واپس e->قدر * p->var[av_clip(eval_اظہاریہ(p, e->param[0]), 0, VARS-1)];
        حالت e_isnan:  واپس e->قدر * !!isnan(eval_اظہاریہ(p, e->param[0]));
        حالت e_isinf:  واپس e->قدر * !!isinf(eval_اظہاریہ(p, e->param[0]));
        حالت e_floor:  واپس e->قدر * floor(eval_اظہاریہ(p, e->param[0]));
        حالت e_ceil :  واپس e->قدر * ceil (eval_اظہاریہ(p, e->param[0]));
        حالت e_trunc:  واپس e->قدر * trunc(eval_اظہاریہ(p, e->param[0]));
        حالت e_باری:  واپس e->قدر * round(eval_اظہاریہ(p, e->param[0]));
        حالت e_sgn:    واپس e->قدر * FFDIFFSIGN(eval_اظہاریہ(p, e->param[0]), 0);
        حالت e_sqrt:   واپس e->قدر * جذر (eval_اظہاریہ(p, e->param[0]));
        حالت e_not:    واپس e->قدر * (eval_اظہاریہ(p, e->param[0]) == 0);
        حالت e_if:     واپس e->قدر * (eval_اظہاریہ(p, e->param[0]) ? eval_اظہاریہ(p, e->param[1]) :
                                          e->param[2] ? eval_اظہاریہ(p, e->param[2]) : 0);
        حالت e_ifnot:  واپس e->قدر * (!eval_اظہاریہ(p, e->param[0]) ? eval_اظہاریہ(p, e->param[1]) :
                                          e->param[2] ? eval_اظہاریہ(p, e->param[2]) : 0);
        حالت e_clip: {
            دوہرا x = eval_اظہاریہ(p, e->param[0]);
            دوہرا min = eval_اظہاریہ(p, e->param[1]), max = eval_اظہاریہ(p, e->param[2]);
            اگر (isnan(min) || isnan(max) || isnan(x) || min > max)
                واپس NAN;
            واپس e->قدر * av_clipd(x, min, max);
        }
        حالت e_between: {
            دوہرا d = eval_اظہاریہ(p, e->param[0]);
            واپس e->قدر * (d >= eval_اظہاریہ(p, e->param[1]) &&
                               d <= eval_اظہاریہ(p, e->param[2]));
        }
        حالت e_lerp: {
            دوہرا v0 = eval_اظہاریہ(p, e->param[0]);
            دوہرا v1 = eval_اظہاریہ(p, e->param[1]);
            دوہرا f  = eval_اظہاریہ(p, e->param[2]);
            واپس e->قدر * (v0 + (v1 - v0) * f);
        }
        حالت e_print: {
            دوہرا x = eval_اظہاریہ(p, e->param[0]);
            صحیح level = e->param[1] ? av_clip(eval_اظہاریہ(p, e->param[1]), INT_MIN, زیادہ_سے_زیادہ_عدد) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            واپس e->قدر * x;
        }

#تعریف_کرو COMPUTE_اگلا_RANDOM()                                        \
            صحیح idx = av_clip(eval_اظہاریہ(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            اگر (!s->شمار_2) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        حالت e_random: {
            COMPUTE_اگلا_RANDOM();
            واپس r * (1.0/UINT64_MAX);
        }
        حالت e_randomi: {
            دوہرا min = eval_اظہاریہ(p, e->param[1]);
            دوہرا max = eval_اظہاریہ(p, e->param[2]);
            COMPUTE_اگلا_RANDOM();
            واپس min + (max - min) * r / UINT64_MAX;
        }
        حالت e_while: {
            دوہرا d = NAN;
            جب (eval_اظہاریہ(p, e->param[0]))
                d=eval_اظہاریہ(p, e->param[1]);
            واپس d;
        }
        حالت e_taylor: {
            دوہرا t = 1, d = 0, v;
            دوہرا x = eval_اظہاریہ(p, e->param[1]);
            صحیح id = e->param[2] ? av_clip(eval_اظہاریہ(p, e->param[2]), 0, VARS-1) : 0;
            صحیح i;
            دوہرا var0 = p->var[id];
            برائے(i=0; i<1000; i++) {
                دوہرا ld = d;
                p->var[id] = i;
                v = eval_اظہاریہ(p, e->param[0]);
                d += t*v;
                اگر(ld==d && v)
                    توڑو;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            واپس d;
        }
        حالت e_جڑ: {
            صحیح i, j;
            دوہرا کم = -1, بلند = -1, v, کم_v = -DBL_MAX, بلند_v = DBL_MAX;
            دوہرا var0 = p->var[0];
            دوہرا x_max = eval_اظہاریہ(p, e->param[1]);
            برائے(i=-1; i<1024; i++) {
                اگر(i<255) {
                    p->var[0] = ff_الٹ[i&255]*x_max/255;
                } ورنہ {
                    p->var[0] = x_max*قوت(0.9, i-255);
                    اگر (i&1) p->var[0] *= -1;
                    اگر (i&2) p->var[0] += کم;
                    ورنہ     p->var[0] += بلند;
                }
                v = eval_اظہاریہ(p, e->param[0]);
                اگر (v<=0 && v>کم_v) {
                    کم    = p->var[0];
                    کم_v  = v;
                }
                اگر (v>=0 && v<بلند_v) {
                    بلند   = p->var[0];
                    بلند_v = v;
                }
                اگر (کم>=0 && بلند>=0){
                    برائے (j=0; j<1000; j++) {
                        p->var[0] = (کم+بلند)*0.5;
                        اگر (کم == p->var[0] || بلند == p->var[0])
                            توڑو;
                        v = eval_اظہاریہ(p, e->param[0]);
                        اگر (v<=0) کم = p->var[0];
                        اگر (v>=0) بلند= p->var[0];
                        اگر (isnan(v)) {
                            کم = بلند = v;
                            توڑو;
                        }
                    }
                    توڑو;
                }
            }
            p->var[0] = var0;
            واپس -کم_v<بلند_v ? کم : بلند;
        }
        طےشدہ: {
            دوہرا d = eval_اظہاریہ(p, e->param[0]);
            دوہرا d2 = eval_اظہاریہ(p, e->param[1]);
            انتخاب (e->type) {
                حالت e_mod: واپس e->قدر * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالت e_عاد_اعظم: واپس e->قدر * av_عاد_اعظم(d,d2);
                حالت e_max: واپس e->قدر * (d >  d2 ?   d : d2);
                حالت e_min: واپس e->قدر * (d <  d2 ?   d : d2);
                حالت e_eq:  واپس e->قدر * (d == d2 ? 1.0 : 0.0);
                حالت e_gt:  واپس e->قدر * (d >  d2 ? 1.0 : 0.0);
                حالت e_gte: واپس e->قدر * (d >= d2 ? 1.0 : 0.0);
                حالت e_lt:  واپس e->قدر * (d <  d2 ? 1.0 : 0.0);
                حالت e_lte: واپس e->قدر * (d <= d2 ? 1.0 : 0.0);
                حالت e_pow: واپس e->قدر * قوت(d, d2);
                حالت e_mul: واپس e->قدر * (d * d2);
                حالت e_div: واپس e->قدر * (d2 ? (d / d2) : d * INFINITY);
                حالت e_جوڑو: واپس e->قدر * (d + d2);
                حالت e_آخری:واپس e->قدر * d2;
                حالت e_st :  {
                    صحیح اشاریہ = av_clip(d, 0, VARS-1);
                    p->prng_state[اشاریہ].شمار_2 = 0;
                    واپس e->قدر * (p->var[اشاریہ]= d2);
                }
                حالت e_hypot:واپس e->قدر * hypot(d, d2);
                حالت e_atan2:واپس e->قدر * atan2(d, d2);
                حالت e_bitand: واپس isnan(d) || isnan(d2) ? NAN : e->قدر * ((طویل صحیح)d & (طویل صحیح)d2);
                حالت e_bitor:  واپس isnan(d) || isnan(d2) ? NAN : e->قدر * ((طویل صحیح)d | (طویل صحیح)d2);
            }
        }
    }
    واپس NAN;
}

ساکن صحیح parse_اظہاریہ(AVExpr **e, Parser *p);

خالی av_اظہاریہ_free(AVExpr *e)
{
    اگر (!e) واپس;
    av_اظہاریہ_free(e->param[0]);
    av_اظہاریہ_free(e->param[1]);
    av_اظہاریہ_free(e->param[2]);
    اگر (e->جڑ) {
        AVExpr_جڑ *r = (AVExpr_جڑ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ساکن صحیح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(حجم(AVExpr));
    حرف *اگلا = p->s, *s0 = p->s;
    صحیح ret, i;

    اگر (!d)
        واپس AVERROR(ENOMEM);

    /*نمبر*/
    d->قدر = av_strtod(p->s, &اگلا);
    اگر (اگلا != p->s) {
        d->type = e_قدر;
        p->s= اگلا;
        *e = d;
        واپس 0;
    }
    d->قدر = 1;

    /* named constants */
    برائے (i=0; p->const_نام && p->const_نام[i]; i++) {
        اگر (strmatch(p->s, p->const_نام[i])) {
            p->s+= لڑی_لمبائی(p->const_نام[i]);
            d->type = e_const;
            d->const_اشاریہ = i;
            *e = d;
            واپس 0;
        }
    }
    برائے (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        اگر (strmatch(p->s, constants[i].name)) {
            p->s += لڑی_لمبائی(constants[i].name);
            d->type = e_قدر;
            d->قدر = constants[i].قدر;
            *e = d;
            واپس 0;
        }
    }

    p->s= strchr(p->s, '(');
    اگر (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= اگلا;
        av_اظہاریہ_free(d);
        واپس AVERROR(EINVAL);
    }
    p->s++; // "("
    اگر (*اگلا == '(') { // special case do-nothing
        av_freep(&d);
        اگر ((ret = parse_اظہاریہ(&d, p)) < 0)
            واپس ret;
        اگر (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_اظہاریہ_free(d);
            واپس AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        واپس 0;
    }
    اگر ((ret = parse_اظہاریہ(&(d->param[0]), p)) < 0) {
        av_اظہاریہ_free(d);
        واپس ret;
    }
    اگر (p->s[0]== ',') {
        p->s++; // ","
        parse_اظہاریہ(&d->param[1], p);
    }
    اگر (p->s[0]== ',') {
        p->s++; // ","
        parse_اظہاریہ(&d->param[2], p);
    }
    اگر (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_اظہاریہ_free(d);
        واپس AVERROR(EINVAL);
    }
    p->s++; // ")"

    برائے (صحیح i = 0; i<3; i++)
        اگر (d->param[i])
            d->گہرائی = FFMAX(d->گہرائی, d->param[i]->گہرائی+1);
    اگر (d->گہرائی > MAX_گہرائی) {
        av_اظہاریہ_free(d);
        واپس AVERROR(EINVAL);
    }

    d->type = e_func0;
         اگر (strmatch(اگلا, "sinh"  )) d->func0 = sinh;
    ورنہ اگر (strmatch(اگلا, "cosh"  )) d->func0 = cosh;
    ورنہ اگر (strmatch(اگلا, "tanh"  )) d->func0 = tanh;
    ورنہ اگر (strmatch(اگلا, "sin"   )) d->func0 = جیب;
    ورنہ اگر (strmatch(اگلا, "cos"   )) d->func0 = جیب_تمام;
    ورنہ اگر (strmatch(اگلا, "tan"   )) d->func0 = tan;
    ورنہ اگر (strmatch(اگلا, "atan"  )) d->func0 = atan;
    ورنہ اگر (strmatch(اگلا, "asin"  )) d->func0 = asin;
    ورنہ اگر (strmatch(اگلا, "acos"  )) d->func0 = acos;
    ورنہ اگر (strmatch(اگلا, "exp"   )) d->func0 = قوت_نما;
    ورنہ اگر (strmatch(اگلا, "log"   )) d->func0 = لوگارتھم;
    ورنہ اگر (strmatch(اگلا, "abs"   )) d->func0 = fabs;
    ورنہ اگر (strmatch(اگلا, "time"  )) d->func0 = etime;
    ورنہ اگر (strmatch(اگلا, "squish")) d->type = e_squish;
    ورنہ اگر (strmatch(اگلا, "gauss" )) d->type = e_gauss;
    ورنہ اگر (strmatch(اگلا, "mod"   )) d->type = e_mod;
    ورنہ اگر (strmatch(اگلا, "max"   )) d->type = e_max;
    ورنہ اگر (strmatch(اگلا, "min"   )) d->type = e_min;
    ورنہ اگر (strmatch(اگلا, "eq"    )) d->type = e_eq;
    ورنہ اگر (strmatch(اگلا, "gte"   )) d->type = e_gte;
    ورنہ اگر (strmatch(اگلا, "gt"    )) d->type = e_gt;
    ورنہ اگر (strmatch(اگلا, "lte"   )) d->type = e_lte;
    ورنہ اگر (strmatch(اگلا, "lt"    )) d->type = e_lt;
    ورنہ اگر (strmatch(اگلا, "ld"    )) d->type = e_ld;
    ورنہ اگر (strmatch(اگلا, "isnan" )) d->type = e_isnan;
    ورنہ اگر (strmatch(اگلا, "isinf" )) d->type = e_isinf;
    ورنہ اگر (strmatch(اگلا, "st"    )) d->type = e_st;
    ورنہ اگر (strmatch(اگلا, "while" )) d->type = e_while;
    ورنہ اگر (strmatch(اگلا, "taylor")) d->type = e_taylor;
    ورنہ اگر (strmatch(اگلا, "root"  )) d->type = e_جڑ;
    ورنہ اگر (strmatch(اگلا, "floor" )) d->type = e_floor;
    ورنہ اگر (strmatch(اگلا, "ceil"  )) d->type = e_ceil;
    ورنہ اگر (strmatch(اگلا, "trunc" )) d->type = e_trunc;
    ورنہ اگر (strmatch(اگلا, "round" )) d->type = e_باری;
    ورنہ اگر (strmatch(اگلا, "sqrt"  )) d->type = e_sqrt;
    ورنہ اگر (strmatch(اگلا, "not"   )) d->type = e_not;
    ورنہ اگر (strmatch(اگلا, "pow"   )) d->type = e_pow;
    ورنہ اگر (strmatch(اگلا, "print" )) d->type = e_print;
    ورنہ اگر (strmatch(اگلا, "random")) d->type = e_random;
    ورنہ اگر (strmatch(اگلا, "randomi")) d->type = e_randomi;
    ورنہ اگر (strmatch(اگلا, "hypot" )) d->type = e_hypot;
    ورنہ اگر (strmatch(اگلا, "gcd"   )) d->type = e_عاد_اعظم;
    ورنہ اگر (strmatch(اگلا, "if"    )) d->type = e_if;
    ورنہ اگر (strmatch(اگلا, "ifnot" )) d->type = e_ifnot;
    ورنہ اگر (strmatch(اگلا, "bitand")) d->type = e_bitand;
    ورنہ اگر (strmatch(اگلا, "bitor" )) d->type = e_bitor;
    ورنہ اگر (strmatch(اگلا, "between"))d->type = e_between;
    ورنہ اگر (strmatch(اگلا, "clip"  )) d->type = e_clip;
    ورنہ اگر (strmatch(اگلا, "atan2" )) d->type = e_atan2;
    ورنہ اگر (strmatch(اگلا, "lerp"  )) d->type = e_lerp;
    ورنہ اگر (strmatch(اگلا, "sgn"   )) d->type = e_sgn;
    ورنہ {
        برائے (i=0; p->func1_نام && p->func1_نام[i]; i++) {
            اگر (strmatch(اگلا, p->func1_نام[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_اشاریہ = i;
                *e = d;
                واپس 0;
            }
        }

        برائے (i=0; p->func2_نام && p->func2_نام[i]; i++) {
            اگر (strmatch(اگلا, p->func2_نام[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_اشاریہ = i;
                *e = d;
                واپس 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_اظہاریہ_free(d);
        واپس AVERROR(EINVAL);
    }

    *e = d;
    واپس 0;
}

ساکن AVExpr *make_eval_اظہاریہ(صحیح type, صحیح قدر, AVExpr *p0, AVExpr *p1)
{
    صحیح گہرائی = FFMAX(p0->گہرائی, p1->گہرائی) + 1;
    اگر (گہرائی > MAX_گہرائی)
        واپس تہی;
    AVExpr *e = av_mallocz(حجم(AVExpr));
    اگر (!e)
        واپس تہی;
    e->type     =type   ;
    e->قدر    =قدر  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->گہرائی    = گہرائی;
    واپس e;
}

ساکن صحیح parse_pow(AVExpr **e, Parser *p, صحیح *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    واپس parse_primary(e, p);
}

ساکن صحیح parse_dB(AVExpr **e, Parser *p, صحیح *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    اگر (*p->s == '-') {
        حرف *اگلا;
        av_غیر_مستعمل دوہرا ignored = strtod(p->s, &اگلا);
        اگر (اگلا != p->s && اگلا[0] == 'd' && اگلا[1] == 'B') {
            *sign = 0;
            واپس parse_primary(e, p);
        }
    }
    واپس parse_pow(e, p, sign);
}

ساکن صحیح parse_ضربی_عدد(AVExpr **e, Parser *p)
{
    صحیح sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    اگر ((ret = parse_dB(&e0, p, &sign)) < 0)
        واپس ret;
    جب(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        اگر ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_اظہاریہ_free(e1);
            واپس ret;
        }
        e0 = make_eval_اظہاریہ(e_pow, 1, e1, e2);
        اگر (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            واپس AVERROR(ENOMEM);
        }
        اگر (e0->param[1]) e0->param[1]->قدر *= (sign2|1);
    }
    اگر (e0) e0->قدر *= (sign|1);

    *e = e0;
    واپس 0;
}

ساکن صحیح parse_رکن(AVExpr **e, Parser *p)
{
    صحیح ret;
    AVExpr *e0, *e1, *e2;
    اگر ((ret = parse_ضربی_عدد(&e0, p)) < 0)
        واپس ret;
    جب (p->s[0]=='*' || p->s[0]=='/') {
        صحیح c= *p->s++;
        e1 = e0;
        اگر ((ret = parse_ضربی_عدد(&e2, p)) < 0) {
            av_اظہاریہ_free(e1);
            واپس ret;
        }
        e0 = make_eval_اظہاریہ(c == '*' ? e_mul : e_div, 1, e1, e2);
        اگر (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            واپس AVERROR(ENOMEM);
        }
    }
    *e = e0;
    واپس 0;
}

ساکن صحیح parse_subexpr(AVExpr **e, Parser *p)
{
    صحیح ret;
    AVExpr *e0, *e1, *e2;
    اگر ((ret = parse_رکن(&e0, p)) < 0)
        واپس ret;
    جب (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        اگر ((ret = parse_رکن(&e2, p)) < 0) {
            av_اظہاریہ_free(e1);
            واپس ret;
        }
        e0 = make_eval_اظہاریہ(e_جوڑو, 1, e1, e2);
        اگر (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            واپس AVERROR(ENOMEM);
        }
    };

    *e = e0;
    واپس 0;
}

ساکن صحیح parse_اظہاریہ(AVExpr **e, Parser *p)
{
    صحیح ret;
    AVExpr *e0, *e1, *e2;
    اگر (p->ڈھیر_اشاریہ <= 0) //protect against stack overflows
        واپس AVERROR(EINVAL);
    p->ڈھیر_اشاریہ--;

    اگر ((ret = parse_subexpr(&e0, p)) < 0)
        واپس ret;
    جب (*p->s == ';') {
        p->s++;
        e1 = e0;
        اگر ((ret = parse_subexpr(&e2, p)) < 0) {
            av_اظہاریہ_free(e1);
            واپس ret;
        }
        e0 = make_eval_اظہاریہ(e_آخری, 1, e1, e2);
        اگر (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            واپس AVERROR(ENOMEM);
        }
    };

    p->ڈھیر_اشاریہ++;
    *e = e0;
    واپس 0;
}

ساکن صحیح verify_اظہاریہ(AVExpr *e)
{
    اگر (!e) واپس 0;
    انتخاب (e->type) {
        حالت e_قدر:
        حالت e_const: واپس 1;
        حالت e_func0:
        حالت e_func1:
        حالت e_squish:
        حالت e_ld:
        حالت e_gauss:
        حالت e_isnan:
        حالت e_isinf:
        حالت e_floor:
        حالت e_ceil:
        حالت e_trunc:
        حالت e_باری:
        حالت e_sqrt:
        حالت e_not:
        حالت e_random:
        حالت e_sgn:
            واپس verify_اظہاریہ(e->param[0]) && !e->param[1];
        حالت e_print:
            واپس verify_اظہاریہ(e->param[0])
                   && (!e->param[1] || verify_اظہاریہ(e->param[1]));
        حالت e_if:
        حالت e_ifnot:
        حالت e_taylor:
            واپس verify_اظہاریہ(e->param[0]) && verify_اظہاریہ(e->param[1])
                   && (!e->param[2] || verify_اظہاریہ(e->param[2]));
        حالت e_between:
        حالت e_clip:
        حالت e_lerp:
        حالت e_randomi:
            واپس verify_اظہاریہ(e->param[0]) &&
                   verify_اظہاریہ(e->param[1]) &&
                   verify_اظہاریہ(e->param[2]);
        طےشدہ: واپس verify_اظہاریہ(e->param[0]) && verify_اظہاریہ(e->param[1]) && !e->param[2];
    }
}

صحیح av_اظہاریہ_parse(AVExpr **اظہاریہ, ثابت حرف *s,
                  ثابت حرف * ثابت *const_نام,
                  ثابت حرف * ثابت *func1_نام, دوہرا (* ثابت *funcs1)(خالی *, دوہرا),
                  ثابت حرف * ثابت *func2_نام, دوہرا (* ثابت *funcs2)(خالی *, دوہرا, دوہرا),
                  صحیح log_انحراف, خالی *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = تہی;
    حرف *w = av_malloc(لڑی_لمبائی(s) + 1);
    حرف *wp = w;
    ثابت حرف *s0 = s;
    صحیح ret = 0;

    اگر (!w)
        واپس AVERROR(ENOMEM);

    جب (*s)
        اگر (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ڈھیر_اشاریہ=100;
    p.s= w;
    p.const_نام = const_نام;
    p.funcs1      = funcs1;
    p.func1_نام = func1_نام;
    p.funcs2      = funcs2;
    p.func2_نام = func2_نام;
    p.log_انحراف = log_انحراف;
    p.log_ctx    = log_ctx;

    اگر ((ret = parse_اظہاریہ(&e, &p)) < 0)
        جاؤ انتہا;
    اگر (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        جاؤ انتہا;
    }
    اگر (!verify_اظہاریہ(e)) {
        ret = AVERROR(EINVAL);
        جاؤ انتہا;
    }
    AVExpr_جڑ *r = av_realloc(e, حجم(*r));
    اگر (!r) {
        ret = AVERROR(ENOMEM);
        جاؤ انتہا;
    }
    e = (AVExpr*)r;
    e->جڑ = 1;
    r->var= av_mallocz(حجم(دوہرا) *VARS);
    r->prng_state = av_mallocz(حجم(*r->prng_state) *VARS);
    اگر (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        جاؤ انتہا;
    }
    *اظہاریہ = e;
    e = تہی;
انتہا:
    av_اظہاریہ_free(e);
    av_free(w);
    واپس ret;
}

ساکن صحیح اظہاریہ_گنتی(AVExpr *e, غیرعلامتی *شمار_2, صحیح سائز, صحیح type)
{
    صحیح i;

    اگر (!e || !شمار_2 || !سائز)
        واپس AVERROR(EINVAL);

    برائے (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        اظہاریہ_گنتی(e->param[i], شمار_2, سائز, type);

    اگر (e->type == type && e->const_اشاریہ < سائز)
        شمار_2[e->const_اشاریہ]++;

    واپس 0;
}

صحیح av_اظہاریہ_گنتی_vars(AVExpr *e, غیرعلامتی *شمار_2, صحیح سائز)
{
    واپس اظہاریہ_گنتی(e, شمار_2, سائز, e_const);
}

صحیح av_اظہاریہ_گنتی_func(AVExpr *e, غیرعلامتی *شمار_2, صحیح سائز, صحیح arg)
{
    واپس اظہاریہ_گنتی(e, شمار_2, سائز, ((صحیح[]){e_const, e_func1, e_func2})[arg]);
}

دوہرا av_اظہاریہ_eval(AVExpr *e, ثابت دوہرا *const_اقدار, خالی *opaque)
{
    av_assert1(e->جڑ);
    AVExpr_جڑ *r = (AVExpr_جڑ *)e;
    Parser p = {
        .class        = &eval_class,
        .const_اقدار = const_اقدار,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    واپس eval_اظہاریہ(&p, e);
}

صحیح av_اظہاریہ_parse_and_eval(دوہرا *d, ثابت حرف *s,
                           ثابت حرف * ثابت *const_نام, ثابت دوہرا *const_اقدار,
                           ثابت حرف * ثابت *func1_نام, دوہرا (* ثابت *funcs1)(خالی *, دوہرا),
                           ثابت حرف * ثابت *func2_نام, دوہرا (* ثابت *funcs2)(خالی *, دوہرا, دوہرا),
                           خالی *opaque, صحیح log_انحراف, خالی *log_ctx)
{
    AVExpr *e = تہی;
    صحیح ret = av_اظہاریہ_parse(&e, s, const_نام, func1_نام, funcs1, func2_نام, funcs2, log_انحراف, log_ctx);

    اگر (ret < 0) {
        *d = NAN;
        واپس ret;
    }
    *d = av_اظہاریہ_eval(e, const_اقدار, opaque);
    av_اظہاریہ_free(e);
    واپس isnan(*d) ? AVERROR(EINVAL) : 0;
}
