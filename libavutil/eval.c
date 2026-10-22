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

#وصف_ڪريو MAX_اونهائي 100

تعريفنوع بنية Parser {
    ثابت AVClass *class;
    صحيح ڍير_اشاريو;
    حرف *s;
    ثابت مزدوج *const_قدرون;
    ثابت حرف * ثابت *const_نالا;          // NULL terminated
    مزدوج (* ثابت *funcs1)(فراغ *, مزدوج a);           // NULL terminated
    ثابت حرف * ثابت *func1_نالا;          // NULL terminated
    مزدوج (* ثابت *funcs2)(فراغ *, مزدوج a, مزدوج b); // NULL terminated
    ثابت حرف * ثابت *func2_نالا;          // NULL terminated
    فراغ *opaque;
    صحيح log_وٿي;
    فراغ *log_ctx;
#وصف_ڪريو VARS 10
    مزدوج *var;
    FFSFC64 *prng_state;
} Parser;

ساكن ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .شي_name                 = av_default_شي_name,
    .option                    = عدم,
    .نسخو                   = LIBAVUTIL_نسخو_INT,
    .log_level_وٿي_وٿي   = offsetof(Parser, log_وٿي),
    .والد_log_context_وٿي = offsetof(Parser, log_ctx),
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

مزدوج av_strtod(ثابت حرف *numstr, حرف **پڇ)
{
    مزدوج d;
    حرف *ايندڙ;
    إذا(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &ايندڙ, 16);
    } وإلا
        d = strtod(numstr, &ايندڙ);
    /* if parsing succeeded, check for and interpret postfixes */
    إذا (ايندڙ!=numstr) {
        إذا (ايندڙ[0] == 'd' && ايندڙ[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            ايندڙ += 2;
        } وإلا إذا (*ايندڙ >= 'E' && *ايندڙ <= 'z') {
            صحيح e= si_prefixes[*ايندڙ - 'E'].قوت_نما;
            إذا (e) {
                إذا (ايندڙ[1] == 'i') {
                    d*= si_prefixes[*ايندڙ - 'E'].bin_val;
                    ايندڙ+=2;
                } وإلا {
                    d*= si_prefixes[*ايندڙ - 'E'].dec_val;
                    ايندڙ++;
                }
            }
        }

        إذا (*ايندڙ=='B') {
            d*=8;
            ايندڙ++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    إذا (پڇ)
        *پڇ = ايندڙ;
    أرجع d;
}

#وصف_ڪريو IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ساكن صحيح strmatch(ثابت حرف *s, ثابت حرف *اڳياڙي)
{
    صحيح i;
    لكل (i=0; اڳياڙي[i]; i++) {
        إذا (اڳياڙي[i] != s[i]) أرجع 0;
    }
    /* return 1 only if the s identifier is terminated */
    أرجع !IS_IDENTIFIER_CHAR(s[i]);
}

تعداد {
    e_قدر, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_جوڙيو,
    e_آخري, e_st, e_while, e_taylor, e_پاڙ, e_floor, e_ceil, e_trunc, e_ڦيرو,
    e_sqrt, e_not, e_random, e_hypot, e_وڏو_گڏيل_ونڊيندڙ,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
بنية AVExpr {
    بنانشان حرف type;
    بنانشان حرف پاڙ;
    ننڍو اونهائي;
    صحيح const_اشاريو;
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
} AVExpr_پاڙ;

ساكن مزدوج etime(مزدوج v)
{
    أرجع av_gettime() * 0.000001;
}

ساكن مزدوج eval_اظهار(Parser *p, AVExpr *e)
{
    بدل (e->type) {
        حالة e_قدر:  أرجع e->قدر;
        حالة e_const:  أرجع e->قدر * p->const_قدرون[e->const_اشاريو];
        حالة e_func0:  أرجع e->قدر * e->func0(eval_اظهار(p, e->param[0]));
        حالة e_func1:  أرجع e->قدر * e->func1(p->opaque, eval_اظهار(p, e->param[0]));
        حالة e_func2:  أرجع e->قدر * e->func2(p->opaque, eval_اظهار(p, e->param[0]), eval_اظهار(p, e->param[1]));
        حالة e_squish: أرجع e->قدر/(1+قوت_نما(4*eval_اظهار(p, e->param[0])));
        حالة e_gauss: { مزدوج d = eval_اظهار(p, e->param[0]); أرجع e->قدر * قوت_نما(-d*d/2)/جذر(2*M_PI); }
        حالة e_ld:     أرجع e->قدر * p->var[av_clip(eval_اظهار(p, e->param[0]), 0, VARS-1)];
        حالة e_isnan:  أرجع e->قدر * !!isnan(eval_اظهار(p, e->param[0]));
        حالة e_isinf:  أرجع e->قدر * !!isinf(eval_اظهار(p, e->param[0]));
        حالة e_floor:  أرجع e->قدر * floor(eval_اظهار(p, e->param[0]));
        حالة e_ceil :  أرجع e->قدر * ceil (eval_اظهار(p, e->param[0]));
        حالة e_trunc:  أرجع e->قدر * trunc(eval_اظهار(p, e->param[0]));
        حالة e_ڦيرو:  أرجع e->قدر * round(eval_اظهار(p, e->param[0]));
        حالة e_sgn:    أرجع e->قدر * FFDIFFSIGN(eval_اظهار(p, e->param[0]), 0);
        حالة e_sqrt:   أرجع e->قدر * جذر (eval_اظهار(p, e->param[0]));
        حالة e_not:    أرجع e->قدر * (eval_اظهار(p, e->param[0]) == 0);
        حالة e_if:     أرجع e->قدر * (eval_اظهار(p, e->param[0]) ? eval_اظهار(p, e->param[1]) :
                                          e->param[2] ? eval_اظهار(p, e->param[2]) : 0);
        حالة e_ifnot:  أرجع e->قدر * (!eval_اظهار(p, e->param[0]) ? eval_اظهار(p, e->param[1]) :
                                          e->param[2] ? eval_اظهار(p, e->param[2]) : 0);
        حالة e_clip: {
            مزدوج x = eval_اظهار(p, e->param[0]);
            مزدوج min = eval_اظهار(p, e->param[1]), max = eval_اظهار(p, e->param[2]);
            إذا (isnan(min) || isnan(max) || isnan(x) || min > max)
                أرجع NAN;
            أرجع e->قدر * av_clipd(x, min, max);
        }
        حالة e_between: {
            مزدوج d = eval_اظهار(p, e->param[0]);
            أرجع e->قدر * (d >= eval_اظهار(p, e->param[1]) &&
                               d <= eval_اظهار(p, e->param[2]));
        }
        حالة e_lerp: {
            مزدوج v0 = eval_اظهار(p, e->param[0]);
            مزدوج v1 = eval_اظهار(p, e->param[1]);
            مزدوج f  = eval_اظهار(p, e->param[2]);
            أرجع e->قدر * (v0 + (v1 - v0) * f);
        }
        حالة e_print: {
            مزدوج x = eval_اظهار(p, e->param[0]);
            صحيح level = e->param[1] ? av_clip(eval_اظهار(p, e->param[1]), INT_MIN, وڌ_کان_وڌ_عدد) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            أرجع e->قدر * x;
        }

#وصف_ڪريو COMPUTE_ايندڙ_RANDOM()                                        \
            صحيح idx = av_clip(eval_اظهار(p, e->param[0]), 0, VARS-1); \
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
            COMPUTE_ايندڙ_RANDOM();
            أرجع r * (1.0/UINT64_MAX);
        }
        حالة e_randomi: {
            مزدوج min = eval_اظهار(p, e->param[1]);
            مزدوج max = eval_اظهار(p, e->param[2]);
            COMPUTE_ايندڙ_RANDOM();
            أرجع min + (max - min) * r / UINT64_MAX;
        }
        حالة e_while: {
            مزدوج d = NAN;
            طالما (eval_اظهار(p, e->param[0]))
                d=eval_اظهار(p, e->param[1]);
            أرجع d;
        }
        حالة e_taylor: {
            مزدوج t = 1, d = 0, v;
            مزدوج x = eval_اظهار(p, e->param[1]);
            صحيح id = e->param[2] ? av_clip(eval_اظهار(p, e->param[2]), 0, VARS-1) : 0;
            صحيح i;
            مزدوج var0 = p->var[id];
            لكل(i=0; i<1000; i++) {
                مزدوج ld = d;
                p->var[id] = i;
                v = eval_اظهار(p, e->param[0]);
                d += t*v;
                إذا(ld==d && v)
                    اكسر;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            أرجع d;
        }
        حالة e_پاڙ: {
            صحيح i, j;
            مزدوج هيٺيون = -1, مٿاهون = -1, v, هيٺيون_v = -DBL_MAX, مٿاهون_v = DBL_MAX;
            مزدوج var0 = p->var[0];
            مزدوج x_max = eval_اظهار(p, e->param[1]);
            لكل(i=-1; i<1024; i++) {
                إذا(i<255) {
                    p->var[0] = ff_ابتو[i&255]*x_max/255;
                } وإلا {
                    p->var[0] = x_max*قوت(0.9, i-255);
                    إذا (i&1) p->var[0] *= -1;
                    إذا (i&2) p->var[0] += هيٺيون;
                    وإلا     p->var[0] += مٿاهون;
                }
                v = eval_اظهار(p, e->param[0]);
                إذا (v<=0 && v>هيٺيون_v) {
                    هيٺيون    = p->var[0];
                    هيٺيون_v  = v;
                }
                إذا (v>=0 && v<مٿاهون_v) {
                    مٿاهون   = p->var[0];
                    مٿاهون_v = v;
                }
                إذا (هيٺيون>=0 && مٿاهون>=0){
                    لكل (j=0; j<1000; j++) {
                        p->var[0] = (هيٺيون+مٿاهون)*0.5;
                        إذا (هيٺيون == p->var[0] || مٿاهون == p->var[0])
                            اكسر;
                        v = eval_اظهار(p, e->param[0]);
                        إذا (v<=0) هيٺيون = p->var[0];
                        إذا (v>=0) مٿاهون= p->var[0];
                        إذا (isnan(v)) {
                            هيٺيون = مٿاهون = v;
                            اكسر;
                        }
                    }
                    اكسر;
                }
            }
            p->var[0] = var0;
            أرجع -هيٺيون_v<مٿاهون_v ? هيٺيون : مٿاهون;
        }
        افتراضي: {
            مزدوج d = eval_اظهار(p, e->param[0]);
            مزدوج d2 = eval_اظهار(p, e->param[1]);
            بدل (e->type) {
                حالة e_mod: أرجع e->قدر * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالة e_وڏو_گڏيل_ونڊيندڙ: أرجع e->قدر * av_وڏو_گڏيل_ونڊيندڙ(d,d2);
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
                حالة e_جوڙيو: أرجع e->قدر * (d + d2);
                حالة e_آخري:أرجع e->قدر * d2;
                حالة e_st :  {
                    صحيح اشاريو = av_clip(d, 0, VARS-1);
                    p->prng_state[اشاريو].counter = 0;
                    أرجع e->قدر * (p->var[اشاريو]= d2);
                }
                حالة e_hypot:أرجع e->قدر * hypot(d, d2);
                حالة e_atan2:أرجع e->قدر * atan2(d, d2);
                حالة e_bitand: أرجع isnan(d) || isnan(d2) ? NAN : e->قدر * ((ڊگهو صحيح)d & (ڊگهو صحيح)d2);
                حالة e_bitor:  أرجع isnan(d) || isnan(d2) ? NAN : e->قدر * ((ڊگهو صحيح)d | (ڊگهو صحيح)d2);
            }
        }
    }
    أرجع NAN;
}

ساكن صحيح parse_اظهار(AVExpr **e, Parser *p);

فراغ av_اظهار_free(AVExpr *e)
{
    إذا (!e) أرجع;
    av_اظهار_free(e->param[0]);
    av_اظهار_free(e->param[1]);
    av_اظهار_free(e->param[2]);
    إذا (e->پاڙ) {
        AVExpr_پاڙ *r = (AVExpr_پاڙ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ساكن صحيح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(حجم(AVExpr));
    حرف *ايندڙ = p->s, *s0 = p->s;
    صحيح ret, i;

    إذا (!d)
        أرجع AVERROR(ENOMEM);

    /*عدد*/
    d->قدر = av_strtod(p->s, &ايندڙ);
    إذا (ايندڙ != p->s) {
        d->type = e_قدر;
        p->s= ايندڙ;
        *e = d;
        أرجع 0;
    }
    d->قدر = 1;

    /* named constants */
    لكل (i=0; p->const_نالا && p->const_نالا[i]; i++) {
        إذا (strmatch(p->s, p->const_نالا[i])) {
            p->s+= لڙي_ڊيگهه(p->const_نالا[i]);
            d->type = e_const;
            d->const_اشاريو = i;
            *e = d;
            أرجع 0;
        }
    }
    لكل (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        إذا (strmatch(p->s, constants[i].name)) {
            p->s += لڙي_ڊيگهه(constants[i].name);
            d->type = e_قدر;
            d->قدر = constants[i].قدر;
            *e = d;
            أرجع 0;
        }
    }

    p->s= strchr(p->s, '(');
    إذا (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= ايندڙ;
        av_اظهار_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // "("
    إذا (*ايندڙ == '(') { // special case do-nothing
        av_freep(&d);
        إذا ((ret = parse_اظهار(&d, p)) < 0)
            أرجع ret;
        إذا (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_اظهار_free(d);
            أرجع AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        أرجع 0;
    }
    إذا ((ret = parse_اظهار(&(d->param[0]), p)) < 0) {
        av_اظهار_free(d);
        أرجع ret;
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_اظهار(&d->param[1], p);
    }
    إذا (p->s[0]== ',') {
        p->s++; // ","
        parse_اظهار(&d->param[2], p);
    }
    إذا (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_اظهار_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // ")"

    لكل (صحيح i = 0; i<3; i++)
        إذا (d->param[i])
            d->اونهائي = FFMAX(d->اونهائي, d->param[i]->اونهائي+1);
    إذا (d->اونهائي > MAX_اونهائي) {
        av_اظهار_free(d);
        أرجع AVERROR(EINVAL);
    }

    d->type = e_func0;
         إذا (strmatch(ايندڙ, "sinh"  )) d->func0 = sinh;
    وإلا إذا (strmatch(ايندڙ, "cosh"  )) d->func0 = cosh;
    وإلا إذا (strmatch(ايندڙ, "tanh"  )) d->func0 = tanh;
    وإلا إذا (strmatch(ايندڙ, "sin"   )) d->func0 = جيب;
    وإلا إذا (strmatch(ايندڙ, "cos"   )) d->func0 = جيب_تمام;
    وإلا إذا (strmatch(ايندڙ, "tan"   )) d->func0 = tan;
    وإلا إذا (strmatch(ايندڙ, "atan"  )) d->func0 = atan;
    وإلا إذا (strmatch(ايندڙ, "asin"  )) d->func0 = asin;
    وإلا إذا (strmatch(ايندڙ, "acos"  )) d->func0 = acos;
    وإلا إذا (strmatch(ايندڙ, "exp"   )) d->func0 = قوت_نما;
    وإلا إذا (strmatch(ايندڙ, "log"   )) d->func0 = لاگرٿم;
    وإلا إذا (strmatch(ايندڙ, "abs"   )) d->func0 = fabs;
    وإلا إذا (strmatch(ايندڙ, "time"  )) d->func0 = etime;
    وإلا إذا (strmatch(ايندڙ, "squish")) d->type = e_squish;
    وإلا إذا (strmatch(ايندڙ, "gauss" )) d->type = e_gauss;
    وإلا إذا (strmatch(ايندڙ, "mod"   )) d->type = e_mod;
    وإلا إذا (strmatch(ايندڙ, "max"   )) d->type = e_max;
    وإلا إذا (strmatch(ايندڙ, "min"   )) d->type = e_min;
    وإلا إذا (strmatch(ايندڙ, "eq"    )) d->type = e_eq;
    وإلا إذا (strmatch(ايندڙ, "gte"   )) d->type = e_gte;
    وإلا إذا (strmatch(ايندڙ, "gt"    )) d->type = e_gt;
    وإلا إذا (strmatch(ايندڙ, "lte"   )) d->type = e_lte;
    وإلا إذا (strmatch(ايندڙ, "lt"    )) d->type = e_lt;
    وإلا إذا (strmatch(ايندڙ, "ld"    )) d->type = e_ld;
    وإلا إذا (strmatch(ايندڙ, "isnan" )) d->type = e_isnan;
    وإلا إذا (strmatch(ايندڙ, "isinf" )) d->type = e_isinf;
    وإلا إذا (strmatch(ايندڙ, "st"    )) d->type = e_st;
    وإلا إذا (strmatch(ايندڙ, "while" )) d->type = e_while;
    وإلا إذا (strmatch(ايندڙ, "taylor")) d->type = e_taylor;
    وإلا إذا (strmatch(ايندڙ, "root"  )) d->type = e_پاڙ;
    وإلا إذا (strmatch(ايندڙ, "floor" )) d->type = e_floor;
    وإلا إذا (strmatch(ايندڙ, "ceil"  )) d->type = e_ceil;
    وإلا إذا (strmatch(ايندڙ, "trunc" )) d->type = e_trunc;
    وإلا إذا (strmatch(ايندڙ, "round" )) d->type = e_ڦيرو;
    وإلا إذا (strmatch(ايندڙ, "sqrt"  )) d->type = e_sqrt;
    وإلا إذا (strmatch(ايندڙ, "not"   )) d->type = e_not;
    وإلا إذا (strmatch(ايندڙ, "pow"   )) d->type = e_pow;
    وإلا إذا (strmatch(ايندڙ, "print" )) d->type = e_print;
    وإلا إذا (strmatch(ايندڙ, "random")) d->type = e_random;
    وإلا إذا (strmatch(ايندڙ, "randomi")) d->type = e_randomi;
    وإلا إذا (strmatch(ايندڙ, "hypot" )) d->type = e_hypot;
    وإلا إذا (strmatch(ايندڙ, "gcd"   )) d->type = e_وڏو_گڏيل_ونڊيندڙ;
    وإلا إذا (strmatch(ايندڙ, "if"    )) d->type = e_if;
    وإلا إذا (strmatch(ايندڙ, "ifnot" )) d->type = e_ifnot;
    وإلا إذا (strmatch(ايندڙ, "bitand")) d->type = e_bitand;
    وإلا إذا (strmatch(ايندڙ, "bitor" )) d->type = e_bitor;
    وإلا إذا (strmatch(ايندڙ, "between"))d->type = e_between;
    وإلا إذا (strmatch(ايندڙ, "clip"  )) d->type = e_clip;
    وإلا إذا (strmatch(ايندڙ, "atan2" )) d->type = e_atan2;
    وإلا إذا (strmatch(ايندڙ, "lerp"  )) d->type = e_lerp;
    وإلا إذا (strmatch(ايندڙ, "sgn"   )) d->type = e_sgn;
    وإلا {
        لكل (i=0; p->func1_نالا && p->func1_نالا[i]; i++) {
            إذا (strmatch(ايندڙ, p->func1_نالا[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_اشاريو = i;
                *e = d;
                أرجع 0;
            }
        }

        لكل (i=0; p->func2_نالا && p->func2_نالا[i]; i++) {
            إذا (strmatch(ايندڙ, p->func2_نالا[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_اشاريو = i;
                *e = d;
                أرجع 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_اظهار_free(d);
        أرجع AVERROR(EINVAL);
    }

    *e = d;
    أرجع 0;
}

ساكن AVExpr *make_eval_اظهار(صحيح type, صحيح قدر, AVExpr *p0, AVExpr *p1)
{
    صحيح اونهائي = FFMAX(p0->اونهائي, p1->اونهائي) + 1;
    إذا (اونهائي > MAX_اونهائي)
        أرجع عدم;
    AVExpr *e = av_mallocz(حجم(AVExpr));
    إذا (!e)
        أرجع عدم;
    e->type     =type   ;
    e->قدر    =قدر  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->اونهائي    = اونهائي;
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
        حرف *ايندڙ;
        av_اڻ_استعمال_ٿيل مزدوج ignored = strtod(p->s, &ايندڙ);
        إذا (ايندڙ != p->s && ايندڙ[0] == 'd' && ايندڙ[1] == 'B') {
            *sign = 0;
            أرجع parse_primary(e, p);
        }
    }
    أرجع parse_pow(e, p, sign);
}

ساكن صحيح parse_ضرب_ڪندڙ(AVExpr **e, Parser *p)
{
    صحيح sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_dB(&e0, p, &sign)) < 0)
        أرجع ret;
    طالما(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        إذا ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_اظهار_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظهار(e_pow, 1, e1, e2);
        إذا (!e0) {
            av_اظهار_free(e1);
            av_اظهار_free(e2);
            أرجع AVERROR(ENOMEM);
        }
        إذا (e0->param[1]) e0->param[1]->قدر *= (sign2|1);
    }
    إذا (e0) e0->قدر *= (sign|1);

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_رڪن(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا ((ret = parse_ضرب_ڪندڙ(&e0, p)) < 0)
        أرجع ret;
    طالما (p->s[0]=='*' || p->s[0]=='/') {
        صحيح c= *p->s++;
        e1 = e0;
        إذا ((ret = parse_ضرب_ڪندڙ(&e2, p)) < 0) {
            av_اظهار_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظهار(c == '*' ? e_mul : e_div, 1, e1, e2);
        إذا (!e0) {
            av_اظهار_free(e1);
            av_اظهار_free(e2);
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
    إذا ((ret = parse_رڪن(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        إذا ((ret = parse_رڪن(&e2, p)) < 0) {
            av_اظهار_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظهار(e_جوڙيو, 1, e1, e2);
        إذا (!e0) {
            av_اظهار_free(e1);
            av_اظهار_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_اظهار(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    إذا (p->ڍير_اشاريو <= 0) //protect against stack overflows
        أرجع AVERROR(EINVAL);
    p->ڍير_اشاريو--;

    إذا ((ret = parse_subexpr(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == ';') {
        p->s++;
        e1 = e0;
        إذا ((ret = parse_subexpr(&e2, p)) < 0) {
            av_اظهار_free(e1);
            أرجع ret;
        }
        e0 = make_eval_اظهار(e_آخري, 1, e1, e2);
        إذا (!e0) {
            av_اظهار_free(e1);
            av_اظهار_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    p->ڍير_اشاريو++;
    *e = e0;
    أرجع 0;
}

ساكن صحيح verify_اظهار(AVExpr *e)
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
        حالة e_ڦيرو:
        حالة e_sqrt:
        حالة e_not:
        حالة e_random:
        حالة e_sgn:
            أرجع verify_اظهار(e->param[0]) && !e->param[1];
        حالة e_print:
            أرجع verify_اظهار(e->param[0])
                   && (!e->param[1] || verify_اظهار(e->param[1]));
        حالة e_if:
        حالة e_ifnot:
        حالة e_taylor:
            أرجع verify_اظهار(e->param[0]) && verify_اظهار(e->param[1])
                   && (!e->param[2] || verify_اظهار(e->param[2]));
        حالة e_between:
        حالة e_clip:
        حالة e_lerp:
        حالة e_randomi:
            أرجع verify_اظهار(e->param[0]) &&
                   verify_اظهار(e->param[1]) &&
                   verify_اظهار(e->param[2]);
        افتراضي: أرجع verify_اظهار(e->param[0]) && verify_اظهار(e->param[1]) && !e->param[2];
    }
}

صحيح av_اظهار_parse(AVExpr **اظهار, ثابت حرف *s,
                  ثابت حرف * ثابت *const_نالا,
                  ثابت حرف * ثابت *func1_نالا, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                  ثابت حرف * ثابت *func2_نالا, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                  صحيح log_وٿي, فراغ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = عدم;
    حرف *w = av_malloc(لڙي_ڊيگهه(s) + 1);
    حرف *wp = w;
    ثابت حرف *s0 = s;
    صحيح ret = 0;

    إذا (!w)
        أرجع AVERROR(ENOMEM);

    طالما (*s)
        إذا (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ڍير_اشاريو=100;
    p.s= w;
    p.const_نالا = const_نالا;
    p.funcs1      = funcs1;
    p.func1_نالا = func1_نالا;
    p.funcs2      = funcs2;
    p.func2_نالا = func2_نالا;
    p.log_وٿي = log_وٿي;
    p.log_ctx    = log_ctx;

    إذا ((ret = parse_اظهار(&e, &p)) < 0)
        اذهب پڇاڙي;
    إذا (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        اذهب پڇاڙي;
    }
    إذا (!verify_اظهار(e)) {
        ret = AVERROR(EINVAL);
        اذهب پڇاڙي;
    }
    AVExpr_پاڙ *r = av_realloc(e, حجم(*r));
    إذا (!r) {
        ret = AVERROR(ENOMEM);
        اذهب پڇاڙي;
    }
    e = (AVExpr*)r;
    e->پاڙ = 1;
    r->var= av_mallocz(حجم(مزدوج) *VARS);
    r->prng_state = av_mallocz(حجم(*r->prng_state) *VARS);
    إذا (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        اذهب پڇاڙي;
    }
    *اظهار = e;
    e = عدم;
پڇاڙي:
    av_اظهار_free(e);
    av_free(w);
    أرجع ret;
}

ساكن صحيح اظهار_ڳڻپ(AVExpr *e, بنانشان *counter, صحيح سائيز, صحيح type)
{
    صحيح i;

    إذا (!e || !counter || !سائيز)
        أرجع AVERROR(EINVAL);

    لكل (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        اظهار_ڳڻپ(e->param[i], counter, سائيز, type);

    إذا (e->type == type && e->const_اشاريو < سائيز)
        counter[e->const_اشاريو]++;

    أرجع 0;
}

صحيح av_اظهار_ڳڻپ_vars(AVExpr *e, بنانشان *counter, صحيح سائيز)
{
    أرجع اظهار_ڳڻپ(e, counter, سائيز, e_const);
}

صحيح av_اظهار_ڳڻپ_func(AVExpr *e, بنانشان *counter, صحيح سائيز, صحيح arg)
{
    أرجع اظهار_ڳڻپ(e, counter, سائيز, ((صحيح[]){e_const, e_func1, e_func2})[arg]);
}

مزدوج av_اظهار_eval(AVExpr *e, ثابت مزدوج *const_قدرون, فراغ *opaque)
{
    av_assert1(e->پاڙ);
    AVExpr_پاڙ *r = (AVExpr_پاڙ *)e;
    Parser p = {
        .class        = &eval_class,
        .const_قدرون = const_قدرون,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    أرجع eval_اظهار(&p, e);
}

صحيح av_اظهار_parse_and_eval(مزدوج *d, ثابت حرف *s,
                           ثابت حرف * ثابت *const_نالا, ثابت مزدوج *const_قدرون,
                           ثابت حرف * ثابت *func1_نالا, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                           ثابت حرف * ثابت *func2_نالا, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                           فراغ *opaque, صحيح log_وٿي, فراغ *log_ctx)
{
    AVExpr *e = عدم;
    صحيح ret = av_اظهار_parse(&e, s, const_نالا, func1_نالا, funcs1, func2_نالا, funcs2, log_وٿي, log_ctx);

    إذا (ret < 0) {
        *d = NAN;
        أرجع ret;
    }
    *d = av_اظهار_eval(e, const_قدرون, opaque);
    av_اظهار_free(e);
    أرجع isnan(*d) ? AVERROR(EINVAL) : 0;
}
