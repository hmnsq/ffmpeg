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

#ضمن <float.h>
#ضمن "attributes.h"
#ضمن "avassert.h"
#ضمن "avutil.h"
#ضمن "common.h"
#ضمن "eval.h"
#ضمن "ffmath.h"
#ضمن "log.h"
#ضمن "mathematics.h"
#ضمن "mem.h"
#ضمن "sfc64.h"
#ضمن "time.h"
#ضمن "avstring.h"
#ضمن "reverse.h"

#تعریف_کرو MAX_ڈونگھائی 100

تعريفنوع بنية Parser {
    ثابت AVClass *class;
    صحيح ڈھیر_اشاریہ;
    حرف *s;
    ثابت مزدوج *const_اقدار;
    ثابت حرف * ثابت *const_ناں;          // NULL terminated
    مزدوج (* ثابت *funcs1)(فراغ *, مزدوج a);           // NULL terminated
    ثابت حرف * ثابت *func1_ناں;          // NULL terminated
    مزدوج (* ثابت *funcs2)(فراغ *, مزدوج a, مزدوج b); // NULL terminated
    ثابت حرف * ثابت *func2_ناں;          // NULL terminated
    فراغ *opaque;
    صحيح log_وتھ;
    فراغ *log_ctx;
#تعریف_کرو VARS 10
    مزدوج *var;
    FFSFC64 *prng_state;
} Parser;

ساكن ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .شے_name                 = av_default_شے_name,
    .option                    = عدم,
    .نسخہ                   = LIBAVUTIL_نسخہ_INT,
    .log_level_وتھ_وتھ   = offsetof(Parser, log_وتھ),
    .ماپا_log_context_وتھ = offsetof(Parser, log_ctx),
};

ساكن ثابت بنية {
    مزدوج bin_val;
    مزدوج dec_val;
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

ساكن ثابت بنية {
    ثابت حرف *name;
    مزدوج قدر;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

مزدوج av_strtod(ثابت حرف *numstr, حرف **پوچھ)
{
    مزدوج d;
    حرف *اگلا;
    إذا(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &اگلا, 16);
    } وإلا
        d = strtod(numstr, &اگلا);
    /* if parsing succeeded, check for and interpret postfixes */
    إذا (اگلا!=numstr) {
        إذا (اگلا[0] == 'd' && اگلا[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            اگلا += 2;
        } وإلا إذا (*اگلا >= 'E' && *اگلا <= 'z') {
            صحيح e= si_prefixes[*اگلا - 'E'].قوت_نما;
            إذا (e) {
                إذا (اگلا[1] == 'i') {
                    d*= si_prefixes[*اگلا - 'E'].bin_val;
                    اگلا+=2;
                } وإلا {
                    d*= si_prefixes[*اگلا - 'E'].dec_val;
                    اگلا++;
                }
            }
        }

        إذا (*اگلا=='B') {
            d*=8;
            اگلا++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    إذا (پوچھ)
        *پوچھ = اگلا;
    أرجع d;
}

#تعریف_کرو IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ساكن صحيح strmatch(ثابت حرف *s, ثابت حرف *اگیتر)
{
    صحيح i;
    لكل (i=0; اگیتر[i]; i++) {
        إذا (اگیتر[i] != s[i]) أرجع 0;
    }
    /* return 1 only if the s identifier is terminated */
    أرجع !IS_IDENTIFIER_CHAR(s[i]);
}

تعداد {
    e_قدر, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_جوڑو,
    e_آخری, e_st, e_while, e_taylor, e_جڑ, e_floor, e_ceil, e_trunc, e_گیڑا,
    e_sqrt, e_not, e_random, e_hypot, e_عاد_اعظم,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
بنية AVExpr {
    بنانشانی حرف type;
    بنانشانی حرف جڑ;
    چھوٹا ڈونگھائی;
    صحيح const_اشاریہ;
    مزدوج قدر; // is sign in other types
    اتحاد {
        مزدوج (*func0)(مزدوج);
        مزدوج (*func1)(فراغ *, مزدوج);
        مزدوج (*func2)(فراغ *, مزدوج, مزدوج);
    } ;
    بنية AVExpr *param[3];
};

تعريفنوع بنية {
    AVExpr avexpr;
    مزدوج *var;
    FFSFC64 *prng_state;
} AVExpr_جڑ;

ساكن مزدوج etime(مزدوج v)
{
    أرجع av_gettime() * 0.000001;
}

ساكن مزدوج eval_اظہاریہ(Parser *p, AVExpr *e)
{
    بدل (e->type) {
        حالة e_قدر:  أرجع e->قدر;
        حالة e_const:  أرجع e->قدر * p->const_اقدار[e->const_اشاریہ];
        حالة e_func0:  أرجع e->قدر * e->func0(eval_اظہاریہ(p, e->param[0]));
        حالة e_func1:  أرجع e->قدر * e->func1(p->opaque, eval_اظہاریہ(p, e->param[0]));
        حالة e_func2:  أرجع e->قدر * e->func2(p->opaque, eval_اظہاریہ(p, e->param[0]), eval_اظہاریہ(p, e->param[1]));
        حالة e_squish: أرجع e->قدر/(1+قوت_نما(4*eval_اظہاریہ(p, e->param[0])));
        حالة e_gauss: { مزدوج d = eval_اظہاریہ(p, e->param[0]); أرجع e->قدر * قوت_نما(-d*d/2)/جذر(2*M_PI); }
        حالة e_ld:     أرجع e->قدر * p->var[av_clip(eval_اظہاریہ(p, e->param[0]), 0, VARS-1)];
        حالة e_isnan:  أرجع e->قدر * !!isnan(eval_اظہاریہ(p, e->param[0]));
        حالة e_isinf:  أرجع e->قدر * !!isinf(eval_اظہاریہ(p, e->param[0]));
        حالة e_floor:  أرجع e->قدر * floor(eval_اظہاریہ(p, e->param[0]));
        حالة e_ceil :  أرجع e->قدر * ceil (eval_اظہاریہ(p, e->param[0]));
        حالة e_trunc:  أرجع e->قدر * trunc(eval_اظہاریہ(p, e->param[0]));
        حالة e_گیڑا:  أرجع e->قدر * round(eval_اظہاریہ(p, e->param[0]));
        حالة e_sgn:    أرجع e->قدر * FFDIFFSIGN(eval_اظہاریہ(p, e->param[0]), 0);
        حالة e_sqrt:   أرجع e->قدر * جذر (eval_اظہاریہ(p, e->param[0]));
        حالة e_not:    أرجع e->قدر * (eval_اظہاریہ(p, e->param[0]) == 0);
        حالة e_if:     أرجع e->قدر * (eval_اظہاریہ(p, e->param[0]) ? eval_اظہاریہ(p, e->param[1]) :
                                          e->param[2] ? eval_اظہاریہ(p, e->param[2]) : 0);
        حالة e_ifnot:  أرجع e->قدر * (!eval_اظہاریہ(p, e->param[0]) ? eval_اظہاریہ(p, e->param[1]) :
                                          e->param[2] ? eval_اظہاریہ(p, e->param[2]) : 0);
        حالة e_clip: {
            مزدوج x = eval_اظہاریہ(p, e->param[0]);
            مزدوج min = eval_اظہاریہ(p, e->param[1]), max = eval_اظہاریہ(p, e->param[2]);
            إذا (isnan(min) || isnan(max) || isnan(x) || min > max)
                أرجع NAN;
            أرجع e->قدر * av_clipd(x, min, max);
        }
        حالة e_between: {
            مزدوج d = eval_اظہاریہ(p, e->param[0]);
            أرجع e->قدر * (d >= eval_اظہاریہ(p, e->param[1]) &&
                               d <= eval_اظہاریہ(p, e->param[2]));
        }
        حالة e_lerp: {
            مزدوج v0 = eval_اظہاریہ(p, e->param[0]);
            مزدوج v1 = eval_اظہاریہ(p, e->param[1]);
            مزدوج f  = eval_اظہاریہ(p, e->param[2]);
            أرجع e->قدر * (v0 + (v1 - v0) * f);
        }
        حالة e_print: {
            مزدوج x = eval_اظہاریہ(p, e->param[0]);
            صحيح level = e->param[1] ? av_clip(eval_اظہاریہ(p, e->param[1]), INT_MIN, ودھ_توں_ودھ_عدد) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            أرجع e->قدر * x;
        }

#تعریف_کرو COMPUTE_اگلا_RANDOM()                                        \
            صحيح idx = av_clip(eval_اظہاریہ(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            إذا (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        حالة e_random: {
            COMPUTE_اگلا_RANDOM();
            أرجع r * (1.0/UINT64_MAX);
        }
        حالة e_randomi: {
            مزدوج min = eval_اظہاریہ(p, e->param[1]);
            مزدوج max = eval_اظہاریہ(p, e->param[2]);
            COMPUTE_اگلا_RANDOM();
            أرجع min + (max - min) * r / UINT64_MAX;
        }
        حالة e_while: {
            مزدوج d = NAN;
            طالما (eval_اظہاریہ(p, e->param[0]))
                d=eval_اظہاریہ(p, e->param[1]);
            أرجع d;
        }
        حالة e_taylor: {
            مزدوج t = 1, d = 0, v;
            مزدوج x = eval_اظہاریہ(p, e->param[1]);
            صحيح id = e->param[2] ? av_clip(eval_اظہاریہ(p, e->param[2]), 0, VARS-1) : 0;
            صحيح i;
            مزدوج var0 = p->var[id];
            لكل(i=0; i<1000; i++) {
                مزدوج ld = d;
                p->var[id] = i;
                v = eval_اظہاریہ(p, e->param[0]);
                d += t*v;
                إذا(ld==d && v)
                    اكسر;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            أرجع d;
        }
        حالة e_جڑ: {
            صحيح i, j;
            مزدوج کم = -1, بلند = -1, v, کم_v = -DBL_MAX, بلند_v = DBL_MAX;
            مزدوج var0 = p->var[0];
            مزدوج x_max = eval_اظہاریہ(p, e->param[1]);
            لكل(i=-1; i<1024; i++) {
                إذا(i<255) {
                    p->var[0] = ff_الٹ[i&255]*x_max/255;
                } وإلا {
                    p->var[0] = x_max*قوت(0.9, i-255);
                    إذا (i&1) p->var[0] *= -1;
                    إذا (i&2) p->var[0] += کم;
                    وإلا     p->var[0] += بلند;
                }
                v = eval_اظہاریہ(p, e->param[0]);
                إذا (v<=0 && v>کم_v) {
                    کم    = p->var[0];
                    کم_v  = v;
                }
                إذا (v>=0 && v<بلند_v) {
                    بلند   = p->var[0];
                    بلند_v = v;
                }
                إذا (کم>=0 && بلند>=0){
                    لكل (j=0; j<1000; j++) {
                        p->var[0] = (کم+بلند)*0.5;
                        إذا (کم == p->var[0] || بلند == p->var[0])
                            اكسر;
                        v = eval_اظہاریہ(p, e->param[0]);
                        إذا (v<=0) کم = p->var[0];
                        إذا (v>=0) بلند= p->var[0];
                        إذا (isnan(v)) {
                            کم = بلند = v;
                            اكسر;
                        }
                    }
                    اكسر;
                }
            }
            p->var[0] = var0;
            أرجع -کم_v<بلند_v ? کم : بلند;
        }
        افتراضي: {
            مزدوج d = eval_اظہاریہ(p, e->param[0]);
            مزدوج d2 = eval_اظہاریہ(p, e->param[1]);
            بدل (e->type) {
                حالة e_mod: أرجع e->قدر * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالة e_عاد_اعظم: أرجع e->قدر * av_عاد_اعظم(d,d2);
                حالة e_max: أرجع e->قدر * (d >  d2 ?   d : d2);
                حالة e_min: أرجع e->قدر * (d <  d2 ?   d : d2);
                حالة e_eq:  أرجع e->قدر * (d == d2 ? 1.0 : 0.0);
                حالة e_gt:  أرجع e->قدر * (d >  d2 ? 1.0 : 0.0);
                حالة e_gte: أرجع e->قدر * (d >= d2 ? 1.0 : 0.0);
                حالة e_lt:  أرجع e->قدر * (d <  d2 ? 1.0 : 0.0);
                حالة e_lte: أرجع e->قدر * (d <= d2 ? 1.0 : 0.0);
                حالة e_pow: أرجع e->قدر * قوت(d, d2);
                حالة e_mul: أرجع e->قدر * (d * d2);
                حالة e_div: أرجع e->قدر * (d2 ? (d / d2) : d * INFINITY);
                حالة e_جوڑو: أرجع e->قدر * (d + d2);
                حالة e_آخری:أرجع e->قدر * d2;
                حالة e_st :  {
                    صحيح اشاریہ = av_clip(d, 0, VARS-1);
                    p->prng_state[اشاریہ].counter = 0;
                    أرجع e->قدر * (p->var[اشاریہ]= d2);
                }
                حالة e_hypot:أرجع e->قدر * hypot(d, d2);
                حالة e_atan2:أرجع e->قدر * atan2(d, d2);
                حالة e_bitand: أرجع isnan(d) || isnan(d2) ? NAN : e->قدر * ((لما صحيح)d & (لما صحيح)d2);
                حالة e_bitor:  أرجع isnan(d) || isnan(d2) ? NAN : e->قدر * ((لما صحيح)d | (لما صحيح)d2);
            }
        }
    }
    أرجع NAN;
}

ساكن صحيح parse_اظہاریہ(AVExpr **e, Parser *p);

فراغ av_اظہاریہ_free(AVExpr *e)
{
    إذا (!e) أرجع;
    av_اظہاریہ_free(e->param[0]);
    av_اظہاریہ_free(e->param[1]);
    av_اظہاریہ_free(e->param[2]);
    إذا (e->جڑ) {
        AVExpr_جڑ *r = (AVExpr_جڑ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ساكن صحيح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(حجم(AVExpr));
    حرف *اگلا = p->s, *s0 = p->s;
    صحيح ret, i;

    إذا (!d)
        أرجع AVERROR(ENOMEM);

    /*نمبر*/
    d->قدر = av_strtod(p->s, &اگلا);
    إذا (اگلا != p->s) {
        d->type = e_قدر;
        p->s= اگلا;
        *e = d;
        أرجع 0;
    }
    d->قدر = 1;

    /* named constants */
    لكل (i=0; p->const_ناں && p->const_ناں[i]; i++) {
        إذا (strmatch(p->s, p->const_ناں[i])) {
            p->s+= لڑی_لمبائی(p->const_ناں[i]);
            d->type = e_const;
            d->const_اشاریہ = i;
            *e = d;
            أرجع 0;
        }
    }
    لكل (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        إذا (strmatch(p->s, constants[i].name)) {
            p->s += لڑی_لمبائی(constants[i].name);
            d->type = e_قدر;
            d->قدر = constants[i].قدر;
            *e = d;
            أرجع 0;
        }
    }

    p->s= strchr(p->s, '(');
    إذا (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= اگلا;
        av_اظہاریہ_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // "("
    إذا (*اگلا == '(') { // special case do-nothing
        av_freep(&d);
        إذا ((ret = parse_اظہاریہ(&d, p)) < 0)
            أرجع ret;
        إذا (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_اظہاریہ_free(d);
            أرجع AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        أرجع 0;
    }
    إذا ((ret = parse_اظہاریہ(&(d->param[0]), p)) < 0) {
        av_اظہاریہ_free(d);
        أرجع ret;
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_اظہاریہ(&d->param[1], p);
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_اظہاریہ(&d->param[2], p);
    }
    إذا (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_اظہاریہ_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // ")"

    لكل (صحيح i = 0; i<3; i++)
        إذا (d->param[i])
            d->ڈونگھائی = FFMAX(d->ڈونگھائی, d->param[i]->ڈونگھائی+1);
    إذا (d->ڈونگھائی > MAX_ڈونگھائی) {
        av_اظہاریہ_free(d);
        أرجع AVERROR(EINVAL);
    }

    d->type = e_func0;
         إذا (strmatch(اگلا, "sinh"  )) d->func0 = sinh;
    وإلا إذا (strmatch(اگلا, "cosh"  )) d->func0 = cosh;
    وإلا إذا (strmatch(اگلا, "tanh"  )) d->func0 = tanh;
    وإلا إذا (strmatch(اگلا, "sin"   )) d->func0 = جیب;
    وإلا إذا (strmatch(اگلا, "cos"   )) d->func0 = جیب_تمام;
    وإلا إذا (strmatch(اگلا, "tan"   )) d->func0 = tan;
    وإلا إذا (strmatch(اگلا, "atan"  )) d->func0 = atan;
    وإلا إذا (strmatch(اگلا, "asin"  )) d->func0 = asin;
    وإلا إذا (strmatch(اگلا, "acos"  )) d->func0 = acos;
    وإلا إذا (strmatch(اگلا, "exp"   )) d->func0 = قوت_نما;
    وإلا إذا (strmatch(اگلا, "log"   )) d->func0 = لوگارتھم;
    وإلا إذا (strmatch(اگلا, "abs"   )) d->func0 = fabs;
    وإلا إذا (strmatch(اگلا, "time"  )) d->func0 = etime;
    وإلا إذا (strmatch(اگلا, "squish")) d->type = e_squish;
    وإلا إذا (strmatch(اگلا, "gauss" )) d->type = e_gauss;
    وإلا إذا (strmatch(اگلا, "mod"   )) d->type = e_mod;
    وإلا إذا (strmatch(اگلا, "max"   )) d->type = e_max;
    وإلا إذا (strmatch(اگلا, "min"   )) d->type = e_min;
    وإلا إذا (strmatch(اگلا, "eq"    )) d->type = e_eq;
    وإلا إذا (strmatch(اگلا, "gte"   )) d->type = e_gte;
    وإلا إذا (strmatch(اگلا, "gt"    )) d->type = e_gt;
    وإلا إذا (strmatch(اگلا, "lte"   )) d->type = e_lte;
    وإلا إذا (strmatch(اگلا, "lt"    )) d->type = e_lt;
    وإلا إذا (strmatch(اگلا, "ld"    )) d->type = e_ld;
    وإلا إذا (strmatch(اگلا, "isnan" )) d->type = e_isnan;
    وإلا إذا (strmatch(اگلا, "isinf" )) d->type = e_isinf;
    وإلا إذا (strmatch(اگلا, "st"    )) d->type = e_st;
    وإلا إذا (strmatch(اگلا, "while" )) d->type = e_while;
    وإلا إذا (strmatch(اگلا, "taylor")) d->type = e_taylor;
    وإلا إذا (strmatch(اگلا, "root"  )) d->type = e_جڑ;
    وإلا إذا (strmatch(اگلا, "floor" )) d->type = e_floor;
    وإلا إذا (strmatch(اگلا, "ceil"  )) d->type = e_ceil;
    وإلا إذا (strmatch(اگلا, "trunc" )) d->type = e_trunc;
    وإلا إذا (strmatch(اگلا, "round" )) d->type = e_گیڑا;
    وإلا إذا (strmatch(اگلا, "sqrt"  )) d->type = e_sqrt;
    وإلا إذا (strmatch(اگلا, "not"   )) d->type = e_not;
    وإلا إذا (strmatch(اگلا, "pow"   )) d->type = e_pow;
    وإلا إذا (strmatch(اگلا, "print" )) d->type = e_print;
    وإلا إذا (strmatch(اگلا, "random")) d->type = e_random;
    وإلا إذا (strmatch(اگلا, "randomi")) d->type = e_randomi;
    وإلا إذا (strmatch(اگلا, "hypot" )) d->type = e_hypot;
    وإلا إذا (strmatch(اگلا, "gcd"   )) d->type = e_عاد_اعظم;
    وإلا إذا (strmatch(اگلا, "if"    )) d->type = e_if;
    وإلا إذا (strmatch(اگلا, "ifnot" )) d->type = e_ifnot;
    وإلا إذا (strmatch(اگلا, "bitand")) d->type = e_bitand;
    وإلا إذا (strmatch(اگلا, "bitor" )) d->type = e_bitor;
    وإلا إذا (strmatch(اگلا, "between"))d->type = e_between;
    وإلا إذا (strmatch(اگلا, "clip"  )) d->type = e_clip;
    وإلا إذا (strmatch(اگلا, "atan2" )) d->type = e_atan2;
    وإلا إذا (strmatch(اگلا, "lerp"  )) d->type = e_lerp;
    وإلا إذا (strmatch(اگلا, "sgn"   )) d->type = e_sgn;
    وإلا {
        لكل (i=0; p->func1_ناں && p->func1_ناں[i]; i++) {
            إذا (strmatch(اگلا, p->func1_ناں[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_اشاریہ = i;
                *e = d;
                أرجع 0;
            }
        }

        لكل (i=0; p->func2_ناں && p->func2_ناں[i]; i++) {
            إذا (strmatch(اگلا, p->func2_ناں[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_اشاریہ = i;
                *e = d;
                أرجع 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_اظہاریہ_free(d);
        أرجع AVERROR(EINVAL);
    }

    *e = d;
    أرجع 0;
}

ساكن AVExpr *make_eval_اظہاریہ(صحيح type, صحيح قدر, AVExpr *p0, AVExpr *p1)
{
    صحيح ڈونگھائی = FFMAX(p0->ڈونگھائی, p1->ڈونگھائی) + 1;
    إذا (ڈونگھائی > MAX_ڈونگھائی)
        أرجع عدم;
    AVExpr *e = av_mallocz(حجم(AVExpr));
    إذا (!e)
        أرجع عدم;
    e->type     =type   ;
    e->قدر    =قدر  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->ڈونگھائی    = ڈونگھائی;
    أرجع e;
}

ساكن صحيح parse_pow(AVExpr **e, Parser *p, صحيح *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    أرجع parse_primary(e, p);
}

ساكن صحيح parse_dB(AVExpr **e, Parser *p, صحيح *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    إذا (*p->s == '-') {
        حرف *اگلا;
        av_بن_ورتیا مزدوج ignored = strtod(p->s, &اگلا);
        إذا (اگلا != p->s && اگلا[0] == 'd' && اگلا[1] == 'B') {
            *sign = 0;
            أرجع parse_primary(e, p);
        }
    }
    أرجع parse_pow(e, p, sign);
}

ساكن صحيح parse_ضارب(AVExpr **e, Parser *p)
{
    صحيح sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_dB(&e0, p, &sign)) < 0)
        أرجع ret;
    طالما(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        إذا ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_اظہاریہ_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظہاریہ(e_pow, 1, e1, e2);
        إذا (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            أرجع AVERROR(ENOMEM);
        }
        إذا (e0->param[1]) e0->param[1]->قدر *= (sign2|1);
    }
    إذا (e0) e0->قدر *= (sign|1);

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_رکن(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_ضارب(&e0, p)) < 0)
        أرجع ret;
    طالما (p->s[0]=='*' || p->s[0]=='/') {
        صحيح c= *p->s++;
        e1 = e0;
        إذا ((ret = parse_ضارب(&e2, p)) < 0) {
            av_اظہاریہ_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظہاریہ(c == '*' ? e_mul : e_div, 1, e1, e2);
        إذا (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    }
    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_subexpr(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_رکن(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        إذا ((ret = parse_رکن(&e2, p)) < 0) {
            av_اظہاریہ_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظہاریہ(e_جوڑو, 1, e1, e2);
        إذا (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_اظہاریہ(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا (p->ڈھیر_اشاریہ <= 0) //protect against stack overflows
        أرجع AVERROR(EINVAL);
    p->ڈھیر_اشاریہ--;

    إذا ((ret = parse_subexpr(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == ';') {
        p->s++;
        e1 = e0;
        إذا ((ret = parse_subexpr(&e2, p)) < 0) {
            av_اظہاریہ_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظہاریہ(e_آخری, 1, e1, e2);
        إذا (!e0) {
            av_اظہاریہ_free(e1);
            av_اظہاریہ_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    p->ڈھیر_اشاریہ++;
    *e = e0;
    أرجع 0;
}

ساكن صحيح verify_اظہاریہ(AVExpr *e)
{
    إذا (!e) أرجع 0;
    بدل (e->type) {
        حالة e_قدر:
        حالة e_const: أرجع 1;
        حالة e_func0:
        حالة e_func1:
        حالة e_squish:
        حالة e_ld:
        حالة e_gauss:
        حالة e_isnan:
        حالة e_isinf:
        حالة e_floor:
        حالة e_ceil:
        حالة e_trunc:
        حالة e_گیڑا:
        حالة e_sqrt:
        حالة e_not:
        حالة e_random:
        حالة e_sgn:
            أرجع verify_اظہاریہ(e->param[0]) && !e->param[1];
        حالة e_print:
            أرجع verify_اظہاریہ(e->param[0])
                   && (!e->param[1] || verify_اظہاریہ(e->param[1]));
        حالة e_if:
        حالة e_ifnot:
        حالة e_taylor:
            أرجع verify_اظہاریہ(e->param[0]) && verify_اظہاریہ(e->param[1])
                   && (!e->param[2] || verify_اظہاریہ(e->param[2]));
        حالة e_between:
        حالة e_clip:
        حالة e_lerp:
        حالة e_randomi:
            أرجع verify_اظہاریہ(e->param[0]) &&
                   verify_اظہاریہ(e->param[1]) &&
                   verify_اظہاریہ(e->param[2]);
        افتراضي: أرجع verify_اظہاریہ(e->param[0]) && verify_اظہاریہ(e->param[1]) && !e->param[2];
    }
}

صحيح av_اظہاریہ_parse(AVExpr **اظہاریہ, ثابت حرف *s,
                  ثابت حرف * ثابت *const_ناں,
                  ثابت حرف * ثابت *func1_ناں, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                  ثابت حرف * ثابت *func2_ناں, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                  صحيح log_وتھ, فراغ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = عدم;
    حرف *w = av_malloc(لڑی_لمبائی(s) + 1);
    حرف *wp = w;
    ثابت حرف *s0 = s;
    صحيح ret = 0;

    إذا (!w)
        أرجع AVERROR(ENOMEM);

    طالما (*s)
        إذا (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ڈھیر_اشاریہ=100;
    p.s= w;
    p.const_ناں = const_ناں;
    p.funcs1      = funcs1;
    p.func1_ناں = func1_ناں;
    p.funcs2      = funcs2;
    p.func2_ناں = func2_ناں;
    p.log_وتھ = log_وتھ;
    p.log_ctx    = log_ctx;

    إذا ((ret = parse_اظہاریہ(&e, &p)) < 0)
        اذهب سرا;
    إذا (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        اذهب سرا;
    }
    إذا (!verify_اظہاریہ(e)) {
        ret = AVERROR(EINVAL);
        اذهب سرا;
    }
    AVExpr_جڑ *r = av_realloc(e, حجم(*r));
    إذا (!r) {
        ret = AVERROR(ENOMEM);
        اذهب سرا;
    }
    e = (AVExpr*)r;
    e->جڑ = 1;
    r->var= av_mallocz(حجم(مزدوج) *VARS);
    r->prng_state = av_mallocz(حجم(*r->prng_state) *VARS);
    إذا (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        اذهب سرا;
    }
    *اظہاریہ = e;
    e = عدم;
سرا:
    av_اظہاریہ_free(e);
    av_free(w);
    أرجع ret;
}

ساكن صحيح اظہاریہ_گنتی(AVExpr *e, بنانشانی *counter, صحيح ناپ, صحيح type)
{
    صحيح i;

    إذا (!e || !counter || !ناپ)
        أرجع AVERROR(EINVAL);

    لكل (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        اظہاریہ_گنتی(e->param[i], counter, ناپ, type);

    إذا (e->type == type && e->const_اشاریہ < ناپ)
        counter[e->const_اشاریہ]++;

    أرجع 0;
}

صحيح av_اظہاریہ_گنتی_vars(AVExpr *e, بنانشانی *counter, صحيح ناپ)
{
    أرجع اظہاریہ_گنتی(e, counter, ناپ, e_const);
}

صحيح av_اظہاریہ_گنتی_func(AVExpr *e, بنانشانی *counter, صحيح ناپ, صحيح arg)
{
    أرجع اظہاریہ_گنتی(e, counter, ناپ, ((صحيح[]){e_const, e_func1, e_func2})[arg]);
}

مزدوج av_اظہاریہ_eval(AVExpr *e, ثابت مزدوج *const_اقدار, فراغ *opaque)
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

    أرجع eval_اظہاریہ(&p, e);
}

صحيح av_اظہاریہ_parse_and_eval(مزدوج *d, ثابت حرف *s,
                           ثابت حرف * ثابت *const_ناں, ثابت مزدوج *const_اقدار,
                           ثابت حرف * ثابت *func1_ناں, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                           ثابت حرف * ثابت *func2_ناں, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                           فراغ *opaque, صحيح log_وتھ, فراغ *log_ctx)
{
    AVExpr *e = عدم;
    صحيح ret = av_اظہاریہ_parse(&e, s, const_ناں, func1_ناں, funcs1, func2_ناں, funcs2, log_وتھ, log_ctx);

    إذا (ret < 0) {
        *d = NAN;
        أرجع ret;
    }
    *d = av_اظہاریہ_eval(e, const_اقدار, opaque);
    av_اظہاریہ_free(e);
    أرجع isnan(*d) ? AVERROR(EINVAL) : 0;
}
