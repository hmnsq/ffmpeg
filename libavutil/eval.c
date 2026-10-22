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

#تعریف_کړه MAX_ژوروالی 100

تعريفنوع بنية Parser {
    ثابت AVClass *class;
    صحيح ډېری_شاخص;
    حرف *s;
    ثابت مزدوج *const_ارزښتونه;
    ثابت حرف * ثابت *const_نومونه;          // NULL terminated
    مزدوج (* ثابت *funcs1)(فراغ *, مزدوج a);           // NULL terminated
    ثابت حرف * ثابت *func1_نومونه;          // NULL terminated
    مزدوج (* ثابت *funcs2)(فراغ *, مزدوج a, مزدوج b); // NULL terminated
    ثابت حرف * ثابت *func2_نومونه;          // NULL terminated
    فراغ *opaque;
    صحيح log_دننه_واټن;
    فراغ *log_ctx;
#تعریف_کړه VARS 10
    مزدوج *var;
    FFSFC64 *prng_state;
} Parser;

ساكن ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .توکی_name                 = av_default_توکی_name,
    .option                    = عدم,
    .نسخه                   = LIBAVUTIL_نسخه_INT,
    .log_level_دننه_واټن_دننه_واټن   = offsetof(Parser, log_دننه_واټن),
    .پلار_log_context_دننه_واټن = offsetof(Parser, log_ctx),
};

ساكن ثابت بنية {
    مزدوج bin_val;
    مزدوج dec_val;
    int8_t توانیز_تابع;
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
    مزدوج ارزښت;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

مزدوج av_strtod(ثابت حرف *numstr, حرف **لکۍ)
{
    مزدوج d;
    حرف *بل;
    إذا(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &بل, 16);
    } وإلا
        d = strtod(numstr, &بل);
    /* if parsing succeeded, check for and interpret postfixes */
    إذا (بل!=numstr) {
        إذا (بل[0] == 'd' && بل[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            بل += 2;
        } وإلا إذا (*بل >= 'E' && *بل <= 'z') {
            صحيح e= si_prefixes[*بل - 'E'].توانیز_تابع;
            إذا (e) {
                إذا (بل[1] == 'i') {
                    d*= si_prefixes[*بل - 'E'].bin_val;
                    بل+=2;
                } وإلا {
                    d*= si_prefixes[*بل - 'E'].dec_val;
                    بل++;
                }
            }
        }

        إذا (*بل=='B') {
            d*=8;
            بل++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    إذا (لکۍ)
        *لکۍ = بل;
    أرجع d;
}

#تعریف_کړه IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ساكن صحيح strmatch(ثابت حرف *s, ثابت حرف *مختاړی)
{
    صحيح i;
    لكل (i=0; مختاړی[i]; i++) {
        إذا (مختاړی[i] != s[i]) أرجع 0;
    }
    /* return 1 only if the s identifier is terminated */
    أرجع !IS_IDENTIFIER_CHAR(s[i]);
}

تعداد {
    e_ارزښت, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_جمع_کړه,
    e_وروستی, e_st, e_while, e_taylor, e_ریښه, e_floor, e_ceil, e_trunc, e_پړاو,
    e_sqrt, e_not, e_random, e_hypot, e_لوی_ګډ_وېشونکی,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
بنية AVExpr {
    بینښه حرف type;
    بینښه حرف ریښه;
    لنډ ژوروالی;
    صحيح const_شاخص;
    مزدوج ارزښت; // is sign in other types
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
} AVExpr_ریښه;

ساكن مزدوج etime(مزدوج v)
{
    أرجع av_gettime() * 0.000001;
}

ساكن مزدوج eval_بیان(Parser *p, AVExpr *e)
{
    بدل (e->type) {
        حالة e_ارزښت:  أرجع e->ارزښت;
        حالة e_const:  أرجع e->ارزښت * p->const_ارزښتونه[e->const_شاخص];
        حالة e_func0:  أرجع e->ارزښت * e->func0(eval_بیان(p, e->param[0]));
        حالة e_func1:  أرجع e->ارزښت * e->func1(p->opaque, eval_بیان(p, e->param[0]));
        حالة e_func2:  أرجع e->ارزښت * e->func2(p->opaque, eval_بیان(p, e->param[0]), eval_بیان(p, e->param[1]));
        حالة e_squish: أرجع e->ارزښت/(1+توانیز_تابع(4*eval_بیان(p, e->param[0])));
        حالة e_gauss: { مزدوج d = eval_بیان(p, e->param[0]); أرجع e->ارزښت * توانیز_تابع(-d*d/2)/جذر(2*M_PI); }
        حالة e_ld:     أرجع e->ارزښت * p->var[av_clip(eval_بیان(p, e->param[0]), 0, VARS-1)];
        حالة e_isnan:  أرجع e->ارزښت * !!isnan(eval_بیان(p, e->param[0]));
        حالة e_isinf:  أرجع e->ارزښت * !!isinf(eval_بیان(p, e->param[0]));
        حالة e_floor:  أرجع e->ارزښت * floor(eval_بیان(p, e->param[0]));
        حالة e_ceil :  أرجع e->ارزښت * ceil (eval_بیان(p, e->param[0]));
        حالة e_trunc:  أرجع e->ارزښت * trunc(eval_بیان(p, e->param[0]));
        حالة e_پړاو:  أرجع e->ارزښت * round(eval_بیان(p, e->param[0]));
        حالة e_sgn:    أرجع e->ارزښت * FFDIFFSIGN(eval_بیان(p, e->param[0]), 0);
        حالة e_sqrt:   أرجع e->ارزښت * جذر (eval_بیان(p, e->param[0]));
        حالة e_not:    أرجع e->ارزښت * (eval_بیان(p, e->param[0]) == 0);
        حالة e_if:     أرجع e->ارزښت * (eval_بیان(p, e->param[0]) ? eval_بیان(p, e->param[1]) :
                                          e->param[2] ? eval_بیان(p, e->param[2]) : 0);
        حالة e_ifnot:  أرجع e->ارزښت * (!eval_بیان(p, e->param[0]) ? eval_بیان(p, e->param[1]) :
                                          e->param[2] ? eval_بیان(p, e->param[2]) : 0);
        حالة e_clip: {
            مزدوج x = eval_بیان(p, e->param[0]);
            مزدوج min = eval_بیان(p, e->param[1]), max = eval_بیان(p, e->param[2]);
            إذا (isnan(min) || isnan(max) || isnan(x) || min > max)
                أرجع NAN;
            أرجع e->ارزښت * av_clipd(x, min, max);
        }
        حالة e_between: {
            مزدوج d = eval_بیان(p, e->param[0]);
            أرجع e->ارزښت * (d >= eval_بیان(p, e->param[1]) &&
                               d <= eval_بیان(p, e->param[2]));
        }
        حالة e_lerp: {
            مزدوج v0 = eval_بیان(p, e->param[0]);
            مزدوج v1 = eval_بیان(p, e->param[1]);
            مزدوج f  = eval_بیان(p, e->param[2]);
            أرجع e->ارزښت * (v0 + (v1 - v0) * f);
        }
        حالة e_print: {
            مزدوج x = eval_بیان(p, e->param[0]);
            صحيح level = e->param[1] ? av_clip(eval_بیان(p, e->param[1]), INT_MIN, لوی_عدد) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            أرجع e->ارزښت * x;
        }

#تعریف_کړه COMPUTE_بل_RANDOM()                                        \
            صحيح idx = av_clip(eval_بیان(p, e->param[0]), 0, VARS-1); \
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
            COMPUTE_بل_RANDOM();
            أرجع r * (1.0/UINT64_MAX);
        }
        حالة e_randomi: {
            مزدوج min = eval_بیان(p, e->param[1]);
            مزدوج max = eval_بیان(p, e->param[2]);
            COMPUTE_بل_RANDOM();
            أرجع min + (max - min) * r / UINT64_MAX;
        }
        حالة e_while: {
            مزدوج d = NAN;
            طالما (eval_بیان(p, e->param[0]))
                d=eval_بیان(p, e->param[1]);
            أرجع d;
        }
        حالة e_taylor: {
            مزدوج t = 1, d = 0, v;
            مزدوج x = eval_بیان(p, e->param[1]);
            صحيح id = e->param[2] ? av_clip(eval_بیان(p, e->param[2]), 0, VARS-1) : 0;
            صحيح i;
            مزدوج var0 = p->var[id];
            لكل(i=0; i<1000; i++) {
                مزدوج ld = d;
                p->var[id] = i;
                v = eval_بیان(p, e->param[0]);
                d += t*v;
                إذا(ld==d && v)
                    اكسر;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            أرجع d;
        }
        حالة e_ریښه: {
            صحيح i, j;
            مزدوج ټیټ = -1, لوړ = -1, v, ټیټ_v = -DBL_MAX, لوړ_v = DBL_MAX;
            مزدوج var0 = p->var[0];
            مزدوج x_max = eval_بیان(p, e->param[1]);
            لكل(i=-1; i<1024; i++) {
                إذا(i<255) {
                    p->var[0] = ff_سرچپه[i&255]*x_max/255;
                } وإلا {
                    p->var[0] = x_max*توان(0.9, i-255);
                    إذا (i&1) p->var[0] *= -1;
                    إذا (i&2) p->var[0] += ټیټ;
                    وإلا     p->var[0] += لوړ;
                }
                v = eval_بیان(p, e->param[0]);
                إذا (v<=0 && v>ټیټ_v) {
                    ټیټ    = p->var[0];
                    ټیټ_v  = v;
                }
                إذا (v>=0 && v<لوړ_v) {
                    لوړ   = p->var[0];
                    لوړ_v = v;
                }
                إذا (ټیټ>=0 && لوړ>=0){
                    لكل (j=0; j<1000; j++) {
                        p->var[0] = (ټیټ+لوړ)*0.5;
                        إذا (ټیټ == p->var[0] || لوړ == p->var[0])
                            اكسر;
                        v = eval_بیان(p, e->param[0]);
                        إذا (v<=0) ټیټ = p->var[0];
                        إذا (v>=0) لوړ= p->var[0];
                        إذا (isnan(v)) {
                            ټیټ = لوړ = v;
                            اكسر;
                        }
                    }
                    اكسر;
                }
            }
            p->var[0] = var0;
            أرجع -ټیټ_v<لوړ_v ? ټیټ : لوړ;
        }
        افتراضي: {
            مزدوج d = eval_بیان(p, e->param[0]);
            مزدوج d2 = eval_بیان(p, e->param[1]);
            بدل (e->type) {
                حالة e_mod: أرجع e->ارزښت * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالة e_لوی_ګډ_وېشونکی: أرجع e->ارزښت * av_لوی_ګډ_وېشونکی(d,d2);
                حالة e_max: أرجع e->ارزښت * (d >  d2 ?   d : d2);
                حالة e_min: أرجع e->ارزښت * (d <  d2 ?   d : d2);
                حالة e_eq:  أرجع e->ارزښت * (d == d2 ? 1.0 : 0.0);
                حالة e_gt:  أرجع e->ارزښت * (d >  d2 ? 1.0 : 0.0);
                حالة e_gte: أرجع e->ارزښت * (d >= d2 ? 1.0 : 0.0);
                حالة e_lt:  أرجع e->ارزښت * (d <  d2 ? 1.0 : 0.0);
                حالة e_lte: أرجع e->ارزښت * (d <= d2 ? 1.0 : 0.0);
                حالة e_pow: أرجع e->ارزښت * توان(d, d2);
                حالة e_mul: أرجع e->ارزښت * (d * d2);
                حالة e_div: أرجع e->ارزښت * (d2 ? (d / d2) : d * INFINITY);
                حالة e_جمع_کړه: أرجع e->ارزښت * (d + d2);
                حالة e_وروستی:أرجع e->ارزښت * d2;
                حالة e_st :  {
                    صحيح شاخص = av_clip(d, 0, VARS-1);
                    p->prng_state[شاخص].counter = 0;
                    أرجع e->ارزښت * (p->var[شاخص]= d2);
                }
                حالة e_hypot:أرجع e->ارزښت * hypot(d, d2);
                حالة e_atan2:أرجع e->ارزښت * atan2(d, d2);
                حالة e_bitand: أرجع isnan(d) || isnan(d2) ? NAN : e->ارزښت * ((اوږد صحيح)d & (اوږد صحيح)d2);
                حالة e_bitor:  أرجع isnan(d) || isnan(d2) ? NAN : e->ارزښت * ((اوږد صحيح)d | (اوږد صحيح)d2);
            }
        }
    }
    أرجع NAN;
}

ساكن صحيح parse_بیان(AVExpr **e, Parser *p);

فراغ av_بیان_free(AVExpr *e)
{
    إذا (!e) أرجع;
    av_بیان_free(e->param[0]);
    av_بیان_free(e->param[1]);
    av_بیان_free(e->param[2]);
    إذا (e->ریښه) {
        AVExpr_ریښه *r = (AVExpr_ریښه*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ساكن صحيح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(حجم(AVExpr));
    حرف *بل = p->s, *s0 = p->s;
    صحيح ret, i;

    إذا (!d)
        أرجع AVERROR(ENOMEM);

    /*شمېره*/
    d->ارزښت = av_strtod(p->s, &بل);
    إذا (بل != p->s) {
        d->type = e_ارزښت;
        p->s= بل;
        *e = d;
        أرجع 0;
    }
    d->ارزښت = 1;

    /* named constants */
    لكل (i=0; p->const_نومونه && p->const_نومونه[i]; i++) {
        إذا (strmatch(p->s, p->const_نومونه[i])) {
            p->s+= مزي_اوږدوالی(p->const_نومونه[i]);
            d->type = e_const;
            d->const_شاخص = i;
            *e = d;
            أرجع 0;
        }
    }
    لكل (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        إذا (strmatch(p->s, constants[i].name)) {
            p->s += مزي_اوږدوالی(constants[i].name);
            d->type = e_ارزښت;
            d->ارزښت = constants[i].ارزښت;
            *e = d;
            أرجع 0;
        }
    }

    p->s= strchr(p->s, '(');
    إذا (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= بل;
        av_بیان_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // "("
    إذا (*بل == '(') { // special case do-nothing
        av_freep(&d);
        إذا ((ret = parse_بیان(&d, p)) < 0)
            أرجع ret;
        إذا (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_بیان_free(d);
            أرجع AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        أرجع 0;
    }
    إذا ((ret = parse_بیان(&(d->param[0]), p)) < 0) {
        av_بیان_free(d);
        أرجع ret;
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_بیان(&d->param[1], p);
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_بیان(&d->param[2], p);
    }
    إذا (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_بیان_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // ")"

    لكل (صحيح i = 0; i<3; i++)
        إذا (d->param[i])
            d->ژوروالی = FFMAX(d->ژوروالی, d->param[i]->ژوروالی+1);
    إذا (d->ژوروالی > MAX_ژوروالی) {
        av_بیان_free(d);
        أرجع AVERROR(EINVAL);
    }

    d->type = e_func0;
         إذا (strmatch(بل, "sinh"  )) d->func0 = sinh;
    وإلا إذا (strmatch(بل, "cosh"  )) d->func0 = cosh;
    وإلا إذا (strmatch(بل, "tanh"  )) d->func0 = tanh;
    وإلا إذا (strmatch(بل, "sin"   )) d->func0 = ساین;
    وإلا إذا (strmatch(بل, "cos"   )) d->func0 = کوساین;
    وإلا إذا (strmatch(بل, "tan"   )) d->func0 = tan;
    وإلا إذا (strmatch(بل, "atan"  )) d->func0 = atan;
    وإلا إذا (strmatch(بل, "asin"  )) d->func0 = asin;
    وإلا إذا (strmatch(بل, "acos"  )) d->func0 = acos;
    وإلا إذا (strmatch(بل, "exp"   )) d->func0 = توانیز_تابع;
    وإلا إذا (strmatch(بل, "log"   )) d->func0 = لوګاریتم;
    وإلا إذا (strmatch(بل, "abs"   )) d->func0 = fabs;
    وإلا إذا (strmatch(بل, "time"  )) d->func0 = etime;
    وإلا إذا (strmatch(بل, "squish")) d->type = e_squish;
    وإلا إذا (strmatch(بل, "gauss" )) d->type = e_gauss;
    وإلا إذا (strmatch(بل, "mod"   )) d->type = e_mod;
    وإلا إذا (strmatch(بل, "max"   )) d->type = e_max;
    وإلا إذا (strmatch(بل, "min"   )) d->type = e_min;
    وإلا إذا (strmatch(بل, "eq"    )) d->type = e_eq;
    وإلا إذا (strmatch(بل, "gte"   )) d->type = e_gte;
    وإلا إذا (strmatch(بل, "gt"    )) d->type = e_gt;
    وإلا إذا (strmatch(بل, "lte"   )) d->type = e_lte;
    وإلا إذا (strmatch(بل, "lt"    )) d->type = e_lt;
    وإلا إذا (strmatch(بل, "ld"    )) d->type = e_ld;
    وإلا إذا (strmatch(بل, "isnan" )) d->type = e_isnan;
    وإلا إذا (strmatch(بل, "isinf" )) d->type = e_isinf;
    وإلا إذا (strmatch(بل, "st"    )) d->type = e_st;
    وإلا إذا (strmatch(بل, "while" )) d->type = e_while;
    وإلا إذا (strmatch(بل, "taylor")) d->type = e_taylor;
    وإلا إذا (strmatch(بل, "root"  )) d->type = e_ریښه;
    وإلا إذا (strmatch(بل, "floor" )) d->type = e_floor;
    وإلا إذا (strmatch(بل, "ceil"  )) d->type = e_ceil;
    وإلا إذا (strmatch(بل, "trunc" )) d->type = e_trunc;
    وإلا إذا (strmatch(بل, "round" )) d->type = e_پړاو;
    وإلا إذا (strmatch(بل, "sqrt"  )) d->type = e_sqrt;
    وإلا إذا (strmatch(بل, "not"   )) d->type = e_not;
    وإلا إذا (strmatch(بل, "pow"   )) d->type = e_pow;
    وإلا إذا (strmatch(بل, "print" )) d->type = e_print;
    وإلا إذا (strmatch(بل, "random")) d->type = e_random;
    وإلا إذا (strmatch(بل, "randomi")) d->type = e_randomi;
    وإلا إذا (strmatch(بل, "hypot" )) d->type = e_hypot;
    وإلا إذا (strmatch(بل, "gcd"   )) d->type = e_لوی_ګډ_وېشونکی;
    وإلا إذا (strmatch(بل, "if"    )) d->type = e_if;
    وإلا إذا (strmatch(بل, "ifnot" )) d->type = e_ifnot;
    وإلا إذا (strmatch(بل, "bitand")) d->type = e_bitand;
    وإلا إذا (strmatch(بل, "bitor" )) d->type = e_bitor;
    وإلا إذا (strmatch(بل, "between"))d->type = e_between;
    وإلا إذا (strmatch(بل, "clip"  )) d->type = e_clip;
    وإلا إذا (strmatch(بل, "atan2" )) d->type = e_atan2;
    وإلا إذا (strmatch(بل, "lerp"  )) d->type = e_lerp;
    وإلا إذا (strmatch(بل, "sgn"   )) d->type = e_sgn;
    وإلا {
        لكل (i=0; p->func1_نومونه && p->func1_نومونه[i]; i++) {
            إذا (strmatch(بل, p->func1_نومونه[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_شاخص = i;
                *e = d;
                أرجع 0;
            }
        }

        لكل (i=0; p->func2_نومونه && p->func2_نومونه[i]; i++) {
            إذا (strmatch(بل, p->func2_نومونه[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_شاخص = i;
                *e = d;
                أرجع 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_بیان_free(d);
        أرجع AVERROR(EINVAL);
    }

    *e = d;
    أرجع 0;
}

ساكن AVExpr *make_eval_بیان(صحيح type, صحيح ارزښت, AVExpr *p0, AVExpr *p1)
{
    صحيح ژوروالی = FFMAX(p0->ژوروالی, p1->ژوروالی) + 1;
    إذا (ژوروالی > MAX_ژوروالی)
        أرجع عدم;
    AVExpr *e = av_mallocz(حجم(AVExpr));
    إذا (!e)
        أرجع عدم;
    e->type     =type   ;
    e->ارزښت    =ارزښت  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->ژوروالی    = ژوروالی;
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
        حرف *بل;
        av_ناکارول_شوی مزدوج ignored = strtod(p->s, &بل);
        إذا (بل != p->s && بل[0] == 'd' && بل[1] == 'B') {
            *sign = 0;
            أرجع parse_primary(e, p);
        }
    }
    أرجع parse_pow(e, p, sign);
}

ساكن صحيح parse_ضریب(AVExpr **e, Parser *p)
{
    صحيح sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_dB(&e0, p, &sign)) < 0)
        أرجع ret;
    طالما(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        إذا ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_بیان_free(e1);
            أرجع ret;
        }
        e0 = make_eval_بیان(e_pow, 1, e1, e2);
        إذا (!e0) {
            av_بیان_free(e1);
            av_بیان_free(e2);
            أرجع AVERROR(ENOMEM);
        }
        إذا (e0->param[1]) e0->param[1]->ارزښت *= (sign2|1);
    }
    إذا (e0) e0->ارزښت *= (sign|1);

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_غړی(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_ضریب(&e0, p)) < 0)
        أرجع ret;
    طالما (p->s[0]=='*' || p->s[0]=='/') {
        صحيح c= *p->s++;
        e1 = e0;
        إذا ((ret = parse_ضریب(&e2, p)) < 0) {
            av_بیان_free(e1);
            أرجع ret;
        }
        e0 = make_eval_بیان(c == '*' ? e_mul : e_div, 1, e1, e2);
        إذا (!e0) {
            av_بیان_free(e1);
            av_بیان_free(e2);
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
    إذا ((ret = parse_غړی(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        إذا ((ret = parse_غړی(&e2, p)) < 0) {
            av_بیان_free(e1);
            أرجع ret;
        }
        e0 = make_eval_بیان(e_جمع_کړه, 1, e1, e2);
        إذا (!e0) {
            av_بیان_free(e1);
            av_بیان_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_بیان(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا (p->ډېری_شاخص <= 0) //protect against stack overflows
        أرجع AVERROR(EINVAL);
    p->ډېری_شاخص--;

    إذا ((ret = parse_subexpr(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == ';') {
        p->s++;
        e1 = e0;
        إذا ((ret = parse_subexpr(&e2, p)) < 0) {
            av_بیان_free(e1);
            أرجع ret;
        }
        e0 = make_eval_بیان(e_وروستی, 1, e1, e2);
        إذا (!e0) {
            av_بیان_free(e1);
            av_بیان_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    p->ډېری_شاخص++;
    *e = e0;
    أرجع 0;
}

ساكن صحيح verify_بیان(AVExpr *e)
{
    إذا (!e) أرجع 0;
    بدل (e->type) {
        حالة e_ارزښت:
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
        حالة e_پړاو:
        حالة e_sqrt:
        حالة e_not:
        حالة e_random:
        حالة e_sgn:
            أرجع verify_بیان(e->param[0]) && !e->param[1];
        حالة e_print:
            أرجع verify_بیان(e->param[0])
                   && (!e->param[1] || verify_بیان(e->param[1]));
        حالة e_if:
        حالة e_ifnot:
        حالة e_taylor:
            أرجع verify_بیان(e->param[0]) && verify_بیان(e->param[1])
                   && (!e->param[2] || verify_بیان(e->param[2]));
        حالة e_between:
        حالة e_clip:
        حالة e_lerp:
        حالة e_randomi:
            أرجع verify_بیان(e->param[0]) &&
                   verify_بیان(e->param[1]) &&
                   verify_بیان(e->param[2]);
        افتراضي: أرجع verify_بیان(e->param[0]) && verify_بیان(e->param[1]) && !e->param[2];
    }
}

صحيح av_بیان_parse(AVExpr **بیان, ثابت حرف *s,
                  ثابت حرف * ثابت *const_نومونه,
                  ثابت حرف * ثابت *func1_نومونه, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                  ثابت حرف * ثابت *func2_نومونه, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                  صحيح log_دننه_واټن, فراغ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = عدم;
    حرف *w = av_malloc(مزي_اوږدوالی(s) + 1);
    حرف *wp = w;
    ثابت حرف *s0 = s;
    صحيح ret = 0;

    إذا (!w)
        أرجع AVERROR(ENOMEM);

    طالما (*s)
        إذا (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ډېری_شاخص=100;
    p.s= w;
    p.const_نومونه = const_نومونه;
    p.funcs1      = funcs1;
    p.func1_نومونه = func1_نومونه;
    p.funcs2      = funcs2;
    p.func2_نومونه = func2_نومونه;
    p.log_دننه_واټن = log_دننه_واټن;
    p.log_ctx    = log_ctx;

    إذا ((ret = parse_بیان(&e, &p)) < 0)
        اذهب پای_ټکی;
    إذا (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        اذهب پای_ټکی;
    }
    إذا (!verify_بیان(e)) {
        ret = AVERROR(EINVAL);
        اذهب پای_ټکی;
    }
    AVExpr_ریښه *r = av_realloc(e, حجم(*r));
    إذا (!r) {
        ret = AVERROR(ENOMEM);
        اذهب پای_ټکی;
    }
    e = (AVExpr*)r;
    e->ریښه = 1;
    r->var= av_mallocz(حجم(مزدوج) *VARS);
    r->prng_state = av_mallocz(حجم(*r->prng_state) *VARS);
    إذا (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        اذهب پای_ټکی;
    }
    *بیان = e;
    e = عدم;
پای_ټکی:
    av_بیان_free(e);
    av_free(w);
    أرجع ret;
}

ساكن صحيح بیان_شمېر(AVExpr *e, بینښه *counter, صحيح اندازه, صحيح type)
{
    صحيح i;

    إذا (!e || !counter || !اندازه)
        أرجع AVERROR(EINVAL);

    لكل (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        بیان_شمېر(e->param[i], counter, اندازه, type);

    إذا (e->type == type && e->const_شاخص < اندازه)
        counter[e->const_شاخص]++;

    أرجع 0;
}

صحيح av_بیان_شمېر_vars(AVExpr *e, بینښه *counter, صحيح اندازه)
{
    أرجع بیان_شمېر(e, counter, اندازه, e_const);
}

صحيح av_بیان_شمېر_func(AVExpr *e, بینښه *counter, صحيح اندازه, صحيح arg)
{
    أرجع بیان_شمېر(e, counter, اندازه, ((صحيح[]){e_const, e_func1, e_func2})[arg]);
}

مزدوج av_بیان_eval(AVExpr *e, ثابت مزدوج *const_ارزښتونه, فراغ *opaque)
{
    av_assert1(e->ریښه);
    AVExpr_ریښه *r = (AVExpr_ریښه *)e;
    Parser p = {
        .class        = &eval_class,
        .const_ارزښتونه = const_ارزښتونه,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    أرجع eval_بیان(&p, e);
}

صحيح av_بیان_parse_and_eval(مزدوج *d, ثابت حرف *s,
                           ثابت حرف * ثابت *const_نومونه, ثابت مزدوج *const_ارزښتونه,
                           ثابت حرف * ثابت *func1_نومونه, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                           ثابت حرف * ثابت *func2_نومونه, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                           فراغ *opaque, صحيح log_دننه_واټن, فراغ *log_ctx)
{
    AVExpr *e = عدم;
    صحيح ret = av_بیان_parse(&e, s, const_نومونه, func1_نومونه, funcs1, func2_نومونه, funcs2, log_دننه_واټن, log_ctx);

    إذا (ret < 0) {
        *d = NAN;
        أرجع ret;
    }
    *d = av_بیان_eval(e, const_ارزښتونه, opaque);
    av_بیان_free(e);
    أرجع isnan(*d) ? AVERROR(EINVAL) : 0;
}
