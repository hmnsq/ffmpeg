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

#تعریف_کن MAX_عمق 100

تعريفنوع بنية Parser {
    ثابت AVClass *class;
    صحيح پشته_شاخص;
    حرف *s;
    ثابت مزدوج *const_مقادیر;
    ثابت حرف * ثابت *const_نامها;          // NULL terminated
    مزدوج (* ثابت *funcs1)(فراغ *, مزدوج a);           // NULL terminated
    ثابت حرف * ثابت *func1_نامها;          // NULL terminated
    مزدوج (* ثابت *funcs2)(فراغ *, مزدوج a, مزدوج b); // NULL terminated
    ثابت حرف * ثابت *func2_نامها;          // NULL terminated
    فراغ *opaque;
    صحيح log_جابه_جایی;
    فراغ *log_ctx;
#تعریف_کن VARS 10
    مزدوج *var;
    FFSFC64 *prng_state;
} Parser;

ساكن ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .قلم_name                 = av_default_قلم_name,
    .option                    = عدم,
    .نسخه                   = LIBAVUTIL_نسخه_INT,
    .log_level_جابه_جایی_جابه_جایی   = offsetof(Parser, log_جابه_جایی),
    .والد_log_context_جابه_جایی = offsetof(Parser, log_ctx),
};

ساكن ثابت بنية {
    مزدوج bin_val;
    مزدوج dec_val;
    int8_t نمایی_تابع;
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
    مزدوج مقدار;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

مزدوج av_strtod(ثابت حرف *numstr, حرف **دم)
{
    مزدوج d;
    حرف *بعدی;
    إذا(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &بعدی, 16);
    } وإلا
        d = strtod(numstr, &بعدی);
    /* if parsing succeeded, check for and interpret postfixes */
    إذا (بعدی!=numstr) {
        إذا (بعدی[0] == 'd' && بعدی[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            بعدی += 2;
        } وإلا إذا (*بعدی >= 'E' && *بعدی <= 'z') {
            صحيح e= si_prefixes[*بعدی - 'E'].نمایی_تابع;
            إذا (e) {
                إذا (بعدی[1] == 'i') {
                    d*= si_prefixes[*بعدی - 'E'].bin_val;
                    بعدی+=2;
                } وإلا {
                    d*= si_prefixes[*بعدی - 'E'].dec_val;
                    بعدی++;
                }
            }
        }

        إذا (*بعدی=='B') {
            d*=8;
            بعدی++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    إذا (دم)
        *دم = بعدی;
    أرجع d;
}

#تعریف_کن IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ساكن صحيح strmatch(ثابت حرف *s, ثابت حرف *پیشوند)
{
    صحيح i;
    لكل (i=0; پیشوند[i]; i++) {
        إذا (پیشوند[i] != s[i]) أرجع 0;
    }
    /* return 1 only if the s identifier is terminated */
    أرجع !IS_IDENTIFIER_CHAR(s[i]);
}

تعداد {
    e_مقدار, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_جمع_کن,
    e_آخرین, e_st, e_while, e_taylor, e_ریشه, e_floor, e_ceil, e_trunc, e_دور,
    e_sqrt, e_not, e_random, e_hypot, e_بزرگترین_مقسوم_علیه,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
بنية AVExpr {
    بیعلامت حرف type;
    بیعلامت حرف ریشه;
    کوتاه عمق;
    صحيح const_شاخص;
    مزدوج مقدار; // is sign in other types
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
} AVExpr_ریشه;

ساكن مزدوج etime(مزدوج v)
{
    أرجع av_gettime() * 0.000001;
}

ساكن مزدوج eval_عبارت(Parser *p, AVExpr *e)
{
    بدل (e->type) {
        حالة e_مقدار:  أرجع e->مقدار;
        حالة e_const:  أرجع e->مقدار * p->const_مقادیر[e->const_شاخص];
        حالة e_func0:  أرجع e->مقدار * e->func0(eval_عبارت(p, e->param[0]));
        حالة e_func1:  أرجع e->مقدار * e->func1(p->opaque, eval_عبارت(p, e->param[0]));
        حالة e_func2:  أرجع e->مقدار * e->func2(p->opaque, eval_عبارت(p, e->param[0]), eval_عبارت(p, e->param[1]));
        حالة e_squish: أرجع e->مقدار/(1+نمایی_تابع(4*eval_عبارت(p, e->param[0])));
        حالة e_gauss: { مزدوج d = eval_عبارت(p, e->param[0]); أرجع e->مقدار * نمایی_تابع(-d*d/2)/جذر(2*M_PI); }
        حالة e_ld:     أرجع e->مقدار * p->var[av_clip(eval_عبارت(p, e->param[0]), 0, VARS-1)];
        حالة e_isnan:  أرجع e->مقدار * !!isnan(eval_عبارت(p, e->param[0]));
        حالة e_isinf:  أرجع e->مقدار * !!isinf(eval_عبارت(p, e->param[0]));
        حالة e_floor:  أرجع e->مقدار * floor(eval_عبارت(p, e->param[0]));
        حالة e_ceil :  أرجع e->مقدار * ceil (eval_عبارت(p, e->param[0]));
        حالة e_trunc:  أرجع e->مقدار * trunc(eval_عبارت(p, e->param[0]));
        حالة e_دور:  أرجع e->مقدار * round(eval_عبارت(p, e->param[0]));
        حالة e_sgn:    أرجع e->مقدار * FFDIFFSIGN(eval_عبارت(p, e->param[0]), 0);
        حالة e_sqrt:   أرجع e->مقدار * جذر (eval_عبارت(p, e->param[0]));
        حالة e_not:    أرجع e->مقدار * (eval_عبارت(p, e->param[0]) == 0);
        حالة e_if:     أرجع e->مقدار * (eval_عبارت(p, e->param[0]) ? eval_عبارت(p, e->param[1]) :
                                          e->param[2] ? eval_عبارت(p, e->param[2]) : 0);
        حالة e_ifnot:  أرجع e->مقدار * (!eval_عبارت(p, e->param[0]) ? eval_عبارت(p, e->param[1]) :
                                          e->param[2] ? eval_عبارت(p, e->param[2]) : 0);
        حالة e_clip: {
            مزدوج x = eval_عبارت(p, e->param[0]);
            مزدوج min = eval_عبارت(p, e->param[1]), max = eval_عبارت(p, e->param[2]);
            إذا (isnan(min) || isnan(max) || isnan(x) || min > max)
                أرجع NAN;
            أرجع e->مقدار * av_clipd(x, min, max);
        }
        حالة e_between: {
            مزدوج d = eval_عبارت(p, e->param[0]);
            أرجع e->مقدار * (d >= eval_عبارت(p, e->param[1]) &&
                               d <= eval_عبارت(p, e->param[2]));
        }
        حالة e_lerp: {
            مزدوج v0 = eval_عبارت(p, e->param[0]);
            مزدوج v1 = eval_عبارت(p, e->param[1]);
            مزدوج f  = eval_عبارت(p, e->param[2]);
            أرجع e->مقدار * (v0 + (v1 - v0) * f);
        }
        حالة e_print: {
            مزدوج x = eval_عبارت(p, e->param[0]);
            صحيح level = e->param[1] ? av_clip(eval_عبارت(p, e->param[1]), INT_MIN, بیشترین_صحیح) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            أرجع e->مقدار * x;
        }

#تعریف_کن COMPUTE_بعدی_RANDOM()                                        \
            صحيح idx = av_clip(eval_عبارت(p, e->param[0]), 0, VARS-1); \
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
            COMPUTE_بعدی_RANDOM();
            أرجع r * (1.0/UINT64_MAX);
        }
        حالة e_randomi: {
            مزدوج min = eval_عبارت(p, e->param[1]);
            مزدوج max = eval_عبارت(p, e->param[2]);
            COMPUTE_بعدی_RANDOM();
            أرجع min + (max - min) * r / UINT64_MAX;
        }
        حالة e_while: {
            مزدوج d = NAN;
            طالما (eval_عبارت(p, e->param[0]))
                d=eval_عبارت(p, e->param[1]);
            أرجع d;
        }
        حالة e_taylor: {
            مزدوج t = 1, d = 0, v;
            مزدوج x = eval_عبارت(p, e->param[1]);
            صحيح id = e->param[2] ? av_clip(eval_عبارت(p, e->param[2]), 0, VARS-1) : 0;
            صحيح i;
            مزدوج var0 = p->var[id];
            لكل(i=0; i<1000; i++) {
                مزدوج ld = d;
                p->var[id] = i;
                v = eval_عبارت(p, e->param[0]);
                d += t*v;
                إذا(ld==d && v)
                    اكسر;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            أرجع d;
        }
        حالة e_ریشه: {
            صحيح i, j;
            مزدوج کم = -1, بالا = -1, v, کم_v = -DBL_MAX, بالا_v = DBL_MAX;
            مزدوج var0 = p->var[0];
            مزدوج x_max = eval_عبارت(p, e->param[1]);
            لكل(i=-1; i<1024; i++) {
                إذا(i<255) {
                    p->var[0] = ff_معکوس[i&255]*x_max/255;
                } وإلا {
                    p->var[0] = x_max*توان(0.9, i-255);
                    إذا (i&1) p->var[0] *= -1;
                    إذا (i&2) p->var[0] += کم;
                    وإلا     p->var[0] += بالا;
                }
                v = eval_عبارت(p, e->param[0]);
                إذا (v<=0 && v>کم_v) {
                    کم    = p->var[0];
                    کم_v  = v;
                }
                إذا (v>=0 && v<بالا_v) {
                    بالا   = p->var[0];
                    بالا_v = v;
                }
                إذا (کم>=0 && بالا>=0){
                    لكل (j=0; j<1000; j++) {
                        p->var[0] = (کم+بالا)*0.5;
                        إذا (کم == p->var[0] || بالا == p->var[0])
                            اكسر;
                        v = eval_عبارت(p, e->param[0]);
                        إذا (v<=0) کم = p->var[0];
                        إذا (v>=0) بالا= p->var[0];
                        إذا (isnan(v)) {
                            کم = بالا = v;
                            اكسر;
                        }
                    }
                    اكسر;
                }
            }
            p->var[0] = var0;
            أرجع -کم_v<بالا_v ? کم : بالا;
        }
        افتراضي: {
            مزدوج d = eval_عبارت(p, e->param[0]);
            مزدوج d2 = eval_عبارت(p, e->param[1]);
            بدل (e->type) {
                حالة e_mod: أرجع e->مقدار * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالة e_بزرگترین_مقسوم_علیه: أرجع e->مقدار * av_بزرگترین_مقسوم_علیه(d,d2);
                حالة e_max: أرجع e->مقدار * (d >  d2 ?   d : d2);
                حالة e_min: أرجع e->مقدار * (d <  d2 ?   d : d2);
                حالة e_eq:  أرجع e->مقدار * (d == d2 ? 1.0 : 0.0);
                حالة e_gt:  أرجع e->مقدار * (d >  d2 ? 1.0 : 0.0);
                حالة e_gte: أرجع e->مقدار * (d >= d2 ? 1.0 : 0.0);
                حالة e_lt:  أرجع e->مقدار * (d <  d2 ? 1.0 : 0.0);
                حالة e_lte: أرجع e->مقدار * (d <= d2 ? 1.0 : 0.0);
                حالة e_pow: أرجع e->مقدار * توان(d, d2);
                حالة e_mul: أرجع e->مقدار * (d * d2);
                حالة e_div: أرجع e->مقدار * (d2 ? (d / d2) : d * INFINITY);
                حالة e_جمع_کن: أرجع e->مقدار * (d + d2);
                حالة e_آخرین:أرجع e->مقدار * d2;
                حالة e_st :  {
                    صحيح شاخص = av_clip(d, 0, VARS-1);
                    p->prng_state[شاخص].counter = 0;
                    أرجع e->مقدار * (p->var[شاخص]= d2);
                }
                حالة e_hypot:أرجع e->مقدار * hypot(d, d2);
                حالة e_atan2:أرجع e->مقدار * atan2(d, d2);
                حالة e_bitand: أرجع isnan(d) || isnan(d2) ? NAN : e->مقدار * ((دراز صحيح)d & (دراز صحيح)d2);
                حالة e_bitor:  أرجع isnan(d) || isnan(d2) ? NAN : e->مقدار * ((دراز صحيح)d | (دراز صحيح)d2);
            }
        }
    }
    أرجع NAN;
}

ساكن صحيح parse_عبارت(AVExpr **e, Parser *p);

فراغ av_عبارت_free(AVExpr *e)
{
    إذا (!e) أرجع;
    av_عبارت_free(e->param[0]);
    av_عبارت_free(e->param[1]);
    av_عبارت_free(e->param[2]);
    إذا (e->ریشه) {
        AVExpr_ریشه *r = (AVExpr_ریشه*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ساكن صحيح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(حجم(AVExpr));
    حرف *بعدی = p->s, *s0 = p->s;
    صحيح ret, i;

    إذا (!d)
        أرجع AVERROR(ENOMEM);

    /*عدد*/
    d->مقدار = av_strtod(p->s, &بعدی);
    إذا (بعدی != p->s) {
        d->type = e_مقدار;
        p->s= بعدی;
        *e = d;
        أرجع 0;
    }
    d->مقدار = 1;

    /* named constants */
    لكل (i=0; p->const_نامها && p->const_نامها[i]; i++) {
        إذا (strmatch(p->s, p->const_نامها[i])) {
            p->s+= طول_رشته(p->const_نامها[i]);
            d->type = e_const;
            d->const_شاخص = i;
            *e = d;
            أرجع 0;
        }
    }
    لكل (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        إذا (strmatch(p->s, constants[i].name)) {
            p->s += طول_رشته(constants[i].name);
            d->type = e_مقدار;
            d->مقدار = constants[i].مقدار;
            *e = d;
            أرجع 0;
        }
    }

    p->s= strchr(p->s, '(');
    إذا (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= بعدی;
        av_عبارت_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // "("
    إذا (*بعدی == '(') { // special case do-nothing
        av_freep(&d);
        إذا ((ret = parse_عبارت(&d, p)) < 0)
            أرجع ret;
        إذا (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_عبارت_free(d);
            أرجع AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        أرجع 0;
    }
    إذا ((ret = parse_عبارت(&(d->param[0]), p)) < 0) {
        av_عبارت_free(d);
        أرجع ret;
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_عبارت(&d->param[1], p);
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_عبارت(&d->param[2], p);
    }
    إذا (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_عبارت_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // ")"

    لكل (صحيح i = 0; i<3; i++)
        إذا (d->param[i])
            d->عمق = FFMAX(d->عمق, d->param[i]->عمق+1);
    إذا (d->عمق > MAX_عمق) {
        av_عبارت_free(d);
        أرجع AVERROR(EINVAL);
    }

    d->type = e_func0;
         إذا (strmatch(بعدی, "sinh"  )) d->func0 = sinh;
    وإلا إذا (strmatch(بعدی, "cosh"  )) d->func0 = cosh;
    وإلا إذا (strmatch(بعدی, "tanh"  )) d->func0 = tanh;
    وإلا إذا (strmatch(بعدی, "sin"   )) d->func0 = سینوس;
    وإلا إذا (strmatch(بعدی, "cos"   )) d->func0 = کسینوس;
    وإلا إذا (strmatch(بعدی, "tan"   )) d->func0 = tan;
    وإلا إذا (strmatch(بعدی, "atan"  )) d->func0 = atan;
    وإلا إذا (strmatch(بعدی, "asin"  )) d->func0 = asin;
    وإلا إذا (strmatch(بعدی, "acos"  )) d->func0 = acos;
    وإلا إذا (strmatch(بعدی, "exp"   )) d->func0 = نمایی_تابع;
    وإلا إذا (strmatch(بعدی, "log"   )) d->func0 = لگاریتم;
    وإلا إذا (strmatch(بعدی, "abs"   )) d->func0 = fabs;
    وإلا إذا (strmatch(بعدی, "time"  )) d->func0 = etime;
    وإلا إذا (strmatch(بعدی, "squish")) d->type = e_squish;
    وإلا إذا (strmatch(بعدی, "gauss" )) d->type = e_gauss;
    وإلا إذا (strmatch(بعدی, "mod"   )) d->type = e_mod;
    وإلا إذا (strmatch(بعدی, "max"   )) d->type = e_max;
    وإلا إذا (strmatch(بعدی, "min"   )) d->type = e_min;
    وإلا إذا (strmatch(بعدی, "eq"    )) d->type = e_eq;
    وإلا إذا (strmatch(بعدی, "gte"   )) d->type = e_gte;
    وإلا إذا (strmatch(بعدی, "gt"    )) d->type = e_gt;
    وإلا إذا (strmatch(بعدی, "lte"   )) d->type = e_lte;
    وإلا إذا (strmatch(بعدی, "lt"    )) d->type = e_lt;
    وإلا إذا (strmatch(بعدی, "ld"    )) d->type = e_ld;
    وإلا إذا (strmatch(بعدی, "isnan" )) d->type = e_isnan;
    وإلا إذا (strmatch(بعدی, "isinf" )) d->type = e_isinf;
    وإلا إذا (strmatch(بعدی, "st"    )) d->type = e_st;
    وإلا إذا (strmatch(بعدی, "while" )) d->type = e_while;
    وإلا إذا (strmatch(بعدی, "taylor")) d->type = e_taylor;
    وإلا إذا (strmatch(بعدی, "root"  )) d->type = e_ریشه;
    وإلا إذا (strmatch(بعدی, "floor" )) d->type = e_floor;
    وإلا إذا (strmatch(بعدی, "ceil"  )) d->type = e_ceil;
    وإلا إذا (strmatch(بعدی, "trunc" )) d->type = e_trunc;
    وإلا إذا (strmatch(بعدی, "round" )) d->type = e_دور;
    وإلا إذا (strmatch(بعدی, "sqrt"  )) d->type = e_sqrt;
    وإلا إذا (strmatch(بعدی, "not"   )) d->type = e_not;
    وإلا إذا (strmatch(بعدی, "pow"   )) d->type = e_pow;
    وإلا إذا (strmatch(بعدی, "print" )) d->type = e_print;
    وإلا إذا (strmatch(بعدی, "random")) d->type = e_random;
    وإلا إذا (strmatch(بعدی, "randomi")) d->type = e_randomi;
    وإلا إذا (strmatch(بعدی, "hypot" )) d->type = e_hypot;
    وإلا إذا (strmatch(بعدی, "gcd"   )) d->type = e_بزرگترین_مقسوم_علیه;
    وإلا إذا (strmatch(بعدی, "if"    )) d->type = e_if;
    وإلا إذا (strmatch(بعدی, "ifnot" )) d->type = e_ifnot;
    وإلا إذا (strmatch(بعدی, "bitand")) d->type = e_bitand;
    وإلا إذا (strmatch(بعدی, "bitor" )) d->type = e_bitor;
    وإلا إذا (strmatch(بعدی, "between"))d->type = e_between;
    وإلا إذا (strmatch(بعدی, "clip"  )) d->type = e_clip;
    وإلا إذا (strmatch(بعدی, "atan2" )) d->type = e_atan2;
    وإلا إذا (strmatch(بعدی, "lerp"  )) d->type = e_lerp;
    وإلا إذا (strmatch(بعدی, "sgn"   )) d->type = e_sgn;
    وإلا {
        لكل (i=0; p->func1_نامها && p->func1_نامها[i]; i++) {
            إذا (strmatch(بعدی, p->func1_نامها[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_شاخص = i;
                *e = d;
                أرجع 0;
            }
        }

        لكل (i=0; p->func2_نامها && p->func2_نامها[i]; i++) {
            إذا (strmatch(بعدی, p->func2_نامها[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_شاخص = i;
                *e = d;
                أرجع 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_عبارت_free(d);
        أرجع AVERROR(EINVAL);
    }

    *e = d;
    أرجع 0;
}

ساكن AVExpr *make_eval_عبارت(صحيح type, صحيح مقدار, AVExpr *p0, AVExpr *p1)
{
    صحيح عمق = FFMAX(p0->عمق, p1->عمق) + 1;
    إذا (عمق > MAX_عمق)
        أرجع عدم;
    AVExpr *e = av_mallocz(حجم(AVExpr));
    إذا (!e)
        أرجع عدم;
    e->type     =type   ;
    e->مقدار    =مقدار  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->عمق    = عمق;
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
        حرف *بعدی;
        av_استفادهنشده مزدوج ignored = strtod(p->s, &بعدی);
        إذا (بعدی != p->s && بعدی[0] == 'd' && بعدی[1] == 'B') {
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
            av_عبارت_free(e1);
            أرجع ret;
        }
        e0 = make_eval_عبارت(e_pow, 1, e1, e2);
        إذا (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            أرجع AVERROR(ENOMEM);
        }
        إذا (e0->param[1]) e0->param[1]->مقدار *= (sign2|1);
    }
    إذا (e0) e0->مقدار *= (sign|1);

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_جمله(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_ضریب(&e0, p)) < 0)
        أرجع ret;
    طالما (p->s[0]=='*' || p->s[0]=='/') {
        صحيح c= *p->s++;
        e1 = e0;
        إذا ((ret = parse_ضریب(&e2, p)) < 0) {
            av_عبارت_free(e1);
            أرجع ret;
        }
        e0 = make_eval_عبارت(c == '*' ? e_mul : e_div, 1, e1, e2);
        إذا (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
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
    إذا ((ret = parse_جمله(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        إذا ((ret = parse_جمله(&e2, p)) < 0) {
            av_عبارت_free(e1);
            أرجع ret;
        }
        e0 = make_eval_عبارت(e_جمع_کن, 1, e1, e2);
        إذا (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_عبارت(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا (p->پشته_شاخص <= 0) //protect against stack overflows
        أرجع AVERROR(EINVAL);
    p->پشته_شاخص--;

    إذا ((ret = parse_subexpr(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == ';') {
        p->s++;
        e1 = e0;
        إذا ((ret = parse_subexpr(&e2, p)) < 0) {
            av_عبارت_free(e1);
            أرجع ret;
        }
        e0 = make_eval_عبارت(e_آخرین, 1, e1, e2);
        إذا (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    p->پشته_شاخص++;
    *e = e0;
    أرجع 0;
}

ساكن صحيح verify_عبارت(AVExpr *e)
{
    إذا (!e) أرجع 0;
    بدل (e->type) {
        حالة e_مقدار:
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
        حالة e_دور:
        حالة e_sqrt:
        حالة e_not:
        حالة e_random:
        حالة e_sgn:
            أرجع verify_عبارت(e->param[0]) && !e->param[1];
        حالة e_print:
            أرجع verify_عبارت(e->param[0])
                   && (!e->param[1] || verify_عبارت(e->param[1]));
        حالة e_if:
        حالة e_ifnot:
        حالة e_taylor:
            أرجع verify_عبارت(e->param[0]) && verify_عبارت(e->param[1])
                   && (!e->param[2] || verify_عبارت(e->param[2]));
        حالة e_between:
        حالة e_clip:
        حالة e_lerp:
        حالة e_randomi:
            أرجع verify_عبارت(e->param[0]) &&
                   verify_عبارت(e->param[1]) &&
                   verify_عبارت(e->param[2]);
        افتراضي: أرجع verify_عبارت(e->param[0]) && verify_عبارت(e->param[1]) && !e->param[2];
    }
}

صحيح av_عبارت_parse(AVExpr **عبارت, ثابت حرف *s,
                  ثابت حرف * ثابت *const_نامها,
                  ثابت حرف * ثابت *func1_نامها, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                  ثابت حرف * ثابت *func2_نامها, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                  صحيح log_جابه_جایی, فراغ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = عدم;
    حرف *w = av_malloc(طول_رشته(s) + 1);
    حرف *wp = w;
    ثابت حرف *s0 = s;
    صحيح ret = 0;

    إذا (!w)
        أرجع AVERROR(ENOMEM);

    طالما (*s)
        إذا (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.پشته_شاخص=100;
    p.s= w;
    p.const_نامها = const_نامها;
    p.funcs1      = funcs1;
    p.func1_نامها = func1_نامها;
    p.funcs2      = funcs2;
    p.func2_نامها = func2_نامها;
    p.log_جابه_جایی = log_جابه_جایی;
    p.log_ctx    = log_ctx;

    إذا ((ret = parse_عبارت(&e, &p)) < 0)
        اذهب انتها;
    إذا (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        اذهب انتها;
    }
    إذا (!verify_عبارت(e)) {
        ret = AVERROR(EINVAL);
        اذهب انتها;
    }
    AVExpr_ریشه *r = av_realloc(e, حجم(*r));
    إذا (!r) {
        ret = AVERROR(ENOMEM);
        اذهب انتها;
    }
    e = (AVExpr*)r;
    e->ریشه = 1;
    r->var= av_mallocz(حجم(مزدوج) *VARS);
    r->prng_state = av_mallocz(حجم(*r->prng_state) *VARS);
    إذا (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        اذهب انتها;
    }
    *عبارت = e;
    e = عدم;
انتها:
    av_عبارت_free(e);
    av_free(w);
    أرجع ret;
}

ساكن صحيح عبارت_شمار(AVExpr *e, بیعلامت *counter, صحيح اندازه, صحيح type)
{
    صحيح i;

    إذا (!e || !counter || !اندازه)
        أرجع AVERROR(EINVAL);

    لكل (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        عبارت_شمار(e->param[i], counter, اندازه, type);

    إذا (e->type == type && e->const_شاخص < اندازه)
        counter[e->const_شاخص]++;

    أرجع 0;
}

صحيح av_عبارت_شمار_vars(AVExpr *e, بیعلامت *counter, صحيح اندازه)
{
    أرجع عبارت_شمار(e, counter, اندازه, e_const);
}

صحيح av_عبارت_شمار_func(AVExpr *e, بیعلامت *counter, صحيح اندازه, صحيح arg)
{
    أرجع عبارت_شمار(e, counter, اندازه, ((صحيح[]){e_const, e_func1, e_func2})[arg]);
}

مزدوج av_عبارت_eval(AVExpr *e, ثابت مزدوج *const_مقادیر, فراغ *opaque)
{
    av_assert1(e->ریشه);
    AVExpr_ریشه *r = (AVExpr_ریشه *)e;
    Parser p = {
        .class        = &eval_class,
        .const_مقادیر = const_مقادیر,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    أرجع eval_عبارت(&p, e);
}

صحيح av_عبارت_parse_and_eval(مزدوج *d, ثابت حرف *s,
                           ثابت حرف * ثابت *const_نامها, ثابت مزدوج *const_مقادیر,
                           ثابت حرف * ثابت *func1_نامها, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                           ثابت حرف * ثابت *func2_نامها, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                           فراغ *opaque, صحيح log_جابه_جایی, فراغ *log_ctx)
{
    AVExpr *e = عدم;
    صحيح ret = av_عبارت_parse(&e, s, const_نامها, func1_نامها, funcs1, func2_نامها, funcs2, log_جابه_جایی, log_ctx);

    إذا (ret < 0) {
        *d = NAN;
        أرجع ret;
    }
    *d = av_عبارت_eval(e, const_مقادیر, opaque);
    av_عبارت_free(e);
    أرجع isnan(*d) ? AVERROR(EINVAL) : 0;
}
