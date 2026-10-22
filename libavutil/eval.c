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

#define MAX_DEPTH 100

تعريفنوع بنية Parser {
    ثابت AVClass *class;
    صحيح stack_index;
    حرف *s;
    ثابت مزدوج *const_values;
    ثابت حرف * ثابت *const_names;          // NULL terminated
    مزدوج (* ثابت *funcs1)(فراغ *, مزدوج a);           // NULL terminated
    ثابت حرف * ثابت *func1_names;          // NULL terminated
    مزدوج (* ثابت *funcs2)(فراغ *, مزدوج a, مزدوج b); // NULL terminated
    ثابت حرف * ثابت *func2_names;          // NULL terminated
    فراغ *opaque;
    صحيح log_offset;
    فراغ *log_ctx;
#define VARS 10
    مزدوج *var;
    FFSFC64 *prng_state;
} Parser;

ساكن ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = عدم,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

ساكن ثابت بنية {
    مزدوج bin_val;
    مزدوج dec_val;
    int8_t exp;
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
    مزدوج value;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

مزدوج av_strtod(ثابت حرف *numstr, حرف **tail)
{
    مزدوج d;
    حرف *next;
    𐤀𐤌(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } وإلا
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    𐤀𐤌 (next!=numstr) {
        𐤀𐤌 (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } وإلا 𐤀𐤌 (*next >= 'E' && *next <= 'z') {
            صحيح e= si_prefixes[*next - 'E'].exp;
            𐤀𐤌 (e) {
                𐤀𐤌 (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } وإلا {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        𐤀𐤌 (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    𐤀𐤌 (tail)
        *tail = next;
    أرجع d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ساكن صحيح strmatch(ثابت حرف *s, ثابت حرف *prefix)
{
    صحيح i;
    لكل (i=0; prefix[i]; i++) {
        𐤀𐤌 (prefix[i] != s[i]) أرجع 0;
    }
    /* return 1 only if the s identifier is terminated */
    أرجع !IS_IDENTIFIER_CHAR(s[i]);
}

تعداد {
    e_value, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_root, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
بنية AVExpr {
    unsigned حرف type;
    unsigned حرف root;
    short depth;
    صحيح const_index;
    مزدوج value; // is sign in other types
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
} AVExprRoot;

ساكن مزدوج etime(مزدوج v)
{
    أرجع av_gettime() * 0.000001;
}

ساكن مزدوج eval_expr(Parser *p, AVExpr *e)
{
    بدل (e->type) {
        حالة e_value:  أرجع e->value;
        حالة e_const:  أرجع e->value * p->const_values[e->const_index];
        حالة e_func0:  أرجع e->value * e->func0(eval_expr(p, e->param[0]));
        حالة e_func1:  أرجع e->value * e->func1(p->opaque, eval_expr(p, e->param[0]));
        حالة e_func2:  أرجع e->value * e->func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        حالة e_squish: أرجع e->value/(1+exp(4*eval_expr(p, e->param[0])));
        حالة e_gauss: { مزدوج d = eval_expr(p, e->param[0]); أرجع e->value * exp(-d*d/2)/sqrt(2*M_PI); }
        حالة e_ld:     أرجع e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        حالة e_isnan:  أرجع e->value * !!isnan(eval_expr(p, e->param[0]));
        حالة e_isinf:  أرجع e->value * !!isinf(eval_expr(p, e->param[0]));
        حالة e_floor:  أرجع e->value * floor(eval_expr(p, e->param[0]));
        حالة e_ceil :  أرجع e->value * ceil (eval_expr(p, e->param[0]));
        حالة e_trunc:  أرجع e->value * trunc(eval_expr(p, e->param[0]));
        حالة e_round:  أرجع e->value * round(eval_expr(p, e->param[0]));
        حالة e_sgn:    أرجع e->value * FFDIFFSIGN(eval_expr(p, e->param[0]), 0);
        حالة e_sqrt:   أرجع e->value * sqrt (eval_expr(p, e->param[0]));
        حالة e_not:    أرجع e->value * (eval_expr(p, e->param[0]) == 0);
        حالة e_if:     أرجع e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        حالة e_ifnot:  أرجع e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        حالة e_clip: {
            مزدوج x = eval_expr(p, e->param[0]);
            مزدوج min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            𐤀𐤌 (isnan(min) || isnan(max) || isnan(x) || min > max)
                أرجع NAN;
            أرجع e->value * av_clipd(x, min, max);
        }
        حالة e_between: {
            مزدوج d = eval_expr(p, e->param[0]);
            أرجع e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        حالة e_lerp: {
            مزدوج v0 = eval_expr(p, e->param[0]);
            مزدوج v1 = eval_expr(p, e->param[1]);
            مزدوج f  = eval_expr(p, e->param[2]);
            أرجع e->value * (v0 + (v1 - v0) * f);
        }
        حالة e_print: {
            مزدوج x = eval_expr(p, e->param[0]);
            صحيح level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            أرجع e->value * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            صحيح idx = av_clip(eval_expr(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            𐤀𐤌 (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        حالة e_random: {
            COMPUTE_NEXT_RANDOM();
            أرجع r * (1.0/UINT64_MAX);
        }
        حالة e_randomi: {
            مزدوج min = eval_expr(p, e->param[1]);
            مزدوج max = eval_expr(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            أرجع min + (max - min) * r / UINT64_MAX;
        }
        حالة e_while: {
            مزدوج d = NAN;
            طالما (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            أرجع d;
        }
        حالة e_taylor: {
            مزدوج t = 1, d = 0, v;
            مزدوج x = eval_expr(p, e->param[1]);
            صحيح id = e->param[2] ? av_clip(eval_expr(p, e->param[2]), 0, VARS-1) : 0;
            صحيح i;
            مزدوج var0 = p->var[id];
            لكل(i=0; i<1000; i++) {
                مزدوج ld = d;
                p->var[id] = i;
                v = eval_expr(p, e->param[0]);
                d += t*v;
                𐤀𐤌(ld==d && v)
                    اكسر;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            أرجع d;
        }
        حالة e_root: {
            صحيح i, j;
            مزدوج low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            مزدوج var0 = p->var[0];
            مزدوج x_max = eval_expr(p, e->param[1]);
            لكل(i=-1; i<1024; i++) {
                𐤀𐤌(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } وإلا {
                    p->var[0] = x_max*pow(0.9, i-255);
                    𐤀𐤌 (i&1) p->var[0] *= -1;
                    𐤀𐤌 (i&2) p->var[0] += low;
                    وإلا     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                𐤀𐤌 (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                𐤀𐤌 (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                𐤀𐤌 (low>=0 && high>=0){
                    لكل (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        𐤀𐤌 (low == p->var[0] || high == p->var[0])
                            اكسر;
                        v = eval_expr(p, e->param[0]);
                        𐤀𐤌 (v<=0) low = p->var[0];
                        𐤀𐤌 (v>=0) high= p->var[0];
                        𐤀𐤌 (isnan(v)) {
                            low = high = v;
                            اكسر;
                        }
                    }
                    اكسر;
                }
            }
            p->var[0] = var0;
            أرجع -low_v<high_v ? low : high;
        }
        افتراضي: {
            مزدوج d = eval_expr(p, e->param[0]);
            مزدوج d2 = eval_expr(p, e->param[1]);
            بدل (e->type) {
                حالة e_mod: أرجع e->value * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالة e_gcd: أرجع e->value * av_gcd(d,d2);
                حالة e_max: أرجع e->value * (d >  d2 ?   d : d2);
                حالة e_min: أرجع e->value * (d <  d2 ?   d : d2);
                حالة e_eq:  أرجع e->value * (d == d2 ? 1.0 : 0.0);
                حالة e_gt:  أرجع e->value * (d >  d2 ? 1.0 : 0.0);
                حالة e_gte: أرجع e->value * (d >= d2 ? 1.0 : 0.0);
                حالة e_lt:  أرجع e->value * (d <  d2 ? 1.0 : 0.0);
                حالة e_lte: أرجع e->value * (d <= d2 ? 1.0 : 0.0);
                حالة e_pow: أرجع e->value * pow(d, d2);
                حالة e_mul: أرجع e->value * (d * d2);
                حالة e_div: أرجع e->value * (d2 ? (d / d2) : d * INFINITY);
                حالة e_add: أرجع e->value * (d + d2);
                حالة e_last:أرجع e->value * d2;
                حالة e_st :  {
                    صحيح index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    أرجع e->value * (p->var[index]= d2);
                }
                حالة e_hypot:أرجع e->value * hypot(d, d2);
                حالة e_atan2:أرجع e->value * atan2(d, d2);
                حالة e_bitand: أرجع isnan(d) || isnan(d2) ? NAN : e->value * ((long صحيح)d & (long صحيح)d2);
                حالة e_bitor:  أرجع isnan(d) || isnan(d2) ? NAN : e->value * ((long صحيح)d | (long صحيح)d2);
            }
        }
    }
    أرجع NAN;
}

ساكن صحيح parse_expr(AVExpr **e, Parser *p);

فراغ av_expr_free(AVExpr *e)
{
    𐤀𐤌 (!e) أرجع;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    𐤀𐤌 (e->root) {
        AVExprRoot *r = (AVExprRoot*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ساكن صحيح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(حجم(AVExpr));
    حرف *next = p->s, *s0 = p->s;
    صحيح ret, i;

    𐤀𐤌 (!d)
        أرجع AVERROR(ENOMEM);

    /* number */
    d->value = av_strtod(p->s, &next);
    𐤀𐤌 (next != p->s) {
        d->type = e_value;
        p->s= next;
        *e = d;
        أرجع 0;
    }
    d->value = 1;

    /* named constants */
    لكل (i=0; p->const_names && p->const_names[i]; i++) {
        𐤀𐤌 (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            أرجع 0;
        }
    }
    لكل (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        𐤀𐤌 (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_value;
            d->value = constants[i].value;
            *e = d;
            أرجع 0;
        }
    }

    p->s= strchr(p->s, '(');
    𐤀𐤌 (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_expr_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // "("
    𐤀𐤌 (*next == '(') { // special case do-nothing
        av_freep(&d);
        𐤀𐤌 ((ret = parse_expr(&d, p)) < 0)
            أرجع ret;
        𐤀𐤌 (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_expr_free(d);
            أرجع AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        أرجع 0;
    }
    𐤀𐤌 ((ret = parse_expr(&(d->param[0]), p)) < 0) {
        av_expr_free(d);
        أرجع ret;
    }
    𐤀𐤌 (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[1], p);
    }
    𐤀𐤌 (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[2], p);
    }
    𐤀𐤌 (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_expr_free(d);
        أرجع AVERROR(EINVAL);
    }
    p->s++; // ")"

    لكل (صحيح i = 0; i<3; i++)
        𐤀𐤌 (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    𐤀𐤌 (d->depth > MAX_DEPTH) {
        av_expr_free(d);
        أرجع AVERROR(EINVAL);
    }

    d->type = e_func0;
         𐤀𐤌 (strmatch(next, "sinh"  )) d->func0 = sinh;
    وإلا 𐤀𐤌 (strmatch(next, "cosh"  )) d->func0 = cosh;
    وإلا 𐤀𐤌 (strmatch(next, "tanh"  )) d->func0 = tanh;
    وإلا 𐤀𐤌 (strmatch(next, "sin"   )) d->func0 = sin;
    وإلا 𐤀𐤌 (strmatch(next, "cos"   )) d->func0 = cos;
    وإلا 𐤀𐤌 (strmatch(next, "tan"   )) d->func0 = tan;
    وإلا 𐤀𐤌 (strmatch(next, "atan"  )) d->func0 = atan;
    وإلا 𐤀𐤌 (strmatch(next, "asin"  )) d->func0 = asin;
    وإلا 𐤀𐤌 (strmatch(next, "acos"  )) d->func0 = acos;
    وإلا 𐤀𐤌 (strmatch(next, "exp"   )) d->func0 = exp;
    وإلا 𐤀𐤌 (strmatch(next, "log"   )) d->func0 = log;
    وإلا 𐤀𐤌 (strmatch(next, "abs"   )) d->func0 = fabs;
    وإلا 𐤀𐤌 (strmatch(next, "time"  )) d->func0 = etime;
    وإلا 𐤀𐤌 (strmatch(next, "squish")) d->type = e_squish;
    وإلا 𐤀𐤌 (strmatch(next, "gauss" )) d->type = e_gauss;
    وإلا 𐤀𐤌 (strmatch(next, "mod"   )) d->type = e_mod;
    وإلا 𐤀𐤌 (strmatch(next, "max"   )) d->type = e_max;
    وإلا 𐤀𐤌 (strmatch(next, "min"   )) d->type = e_min;
    وإلا 𐤀𐤌 (strmatch(next, "eq"    )) d->type = e_eq;
    وإلا 𐤀𐤌 (strmatch(next, "gte"   )) d->type = e_gte;
    وإلا 𐤀𐤌 (strmatch(next, "gt"    )) d->type = e_gt;
    وإلا 𐤀𐤌 (strmatch(next, "lte"   )) d->type = e_lte;
    وإلا 𐤀𐤌 (strmatch(next, "lt"    )) d->type = e_lt;
    وإلا 𐤀𐤌 (strmatch(next, "ld"    )) d->type = e_ld;
    وإلا 𐤀𐤌 (strmatch(next, "isnan" )) d->type = e_isnan;
    وإلا 𐤀𐤌 (strmatch(next, "isinf" )) d->type = e_isinf;
    وإلا 𐤀𐤌 (strmatch(next, "st"    )) d->type = e_st;
    وإلا 𐤀𐤌 (strmatch(next, "while" )) d->type = e_while;
    وإلا 𐤀𐤌 (strmatch(next, "taylor")) d->type = e_taylor;
    وإلا 𐤀𐤌 (strmatch(next, "root"  )) d->type = e_root;
    وإلا 𐤀𐤌 (strmatch(next, "floor" )) d->type = e_floor;
    وإلا 𐤀𐤌 (strmatch(next, "ceil"  )) d->type = e_ceil;
    وإلا 𐤀𐤌 (strmatch(next, "trunc" )) d->type = e_trunc;
    وإلا 𐤀𐤌 (strmatch(next, "round" )) d->type = e_round;
    وإلا 𐤀𐤌 (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    وإلا 𐤀𐤌 (strmatch(next, "not"   )) d->type = e_not;
    وإلا 𐤀𐤌 (strmatch(next, "pow"   )) d->type = e_pow;
    وإلا 𐤀𐤌 (strmatch(next, "print" )) d->type = e_print;
    وإلا 𐤀𐤌 (strmatch(next, "random")) d->type = e_random;
    وإلا 𐤀𐤌 (strmatch(next, "randomi")) d->type = e_randomi;
    وإلا 𐤀𐤌 (strmatch(next, "hypot" )) d->type = e_hypot;
    وإلا 𐤀𐤌 (strmatch(next, "gcd"   )) d->type = e_gcd;
    وإلا 𐤀𐤌 (strmatch(next, "if"    )) d->type = e_if;
    وإلا 𐤀𐤌 (strmatch(next, "ifnot" )) d->type = e_ifnot;
    وإلا 𐤀𐤌 (strmatch(next, "bitand")) d->type = e_bitand;
    وإلا 𐤀𐤌 (strmatch(next, "bitor" )) d->type = e_bitor;
    وإلا 𐤀𐤌 (strmatch(next, "between"))d->type = e_between;
    وإلا 𐤀𐤌 (strmatch(next, "clip"  )) d->type = e_clip;
    وإلا 𐤀𐤌 (strmatch(next, "atan2" )) d->type = e_atan2;
    وإلا 𐤀𐤌 (strmatch(next, "lerp"  )) d->type = e_lerp;
    وإلا 𐤀𐤌 (strmatch(next, "sgn"   )) d->type = e_sgn;
    وإلا {
        لكل (i=0; p->func1_names && p->func1_names[i]; i++) {
            𐤀𐤌 (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                أرجع 0;
            }
        }

        لكل (i=0; p->func2_names && p->func2_names[i]; i++) {
            𐤀𐤌 (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                أرجع 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_expr_free(d);
        أرجع AVERROR(EINVAL);
    }

    *e = d;
    أرجع 0;
}

ساكن AVExpr *make_eval_expr(صحيح type, صحيح value, AVExpr *p0, AVExpr *p1)
{
    صحيح depth = FFMAX(p0->depth, p1->depth) + 1;
    𐤀𐤌 (depth > MAX_DEPTH)
        أرجع عدم;
    AVExpr *e = av_mallocz(حجم(AVExpr));
    𐤀𐤌 (!e)
        أرجع عدم;
    e->type     =type   ;
    e->value    =value  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
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
    𐤀𐤌 (*p->s == '-') {
        حرف *next;
        av_unused مزدوج ignored = strtod(p->s, &next);
        𐤀𐤌 (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            أرجع parse_primary(e, p);
        }
    }
    أرجع parse_pow(e, p, sign);
}

ساكن صحيح parse_factor(AVExpr **e, Parser *p)
{
    صحيح sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    𐤀𐤌 ((ret = parse_dB(&e0, p, &sign)) < 0)
        أرجع ret;
    طالما(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        𐤀𐤌 ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_expr_free(e1);
            أرجع ret;
        }
        e0 = make_eval_expr(e_pow, 1, e1, e2);
        𐤀𐤌 (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            أرجع AVERROR(ENOMEM);
        }
        𐤀𐤌 (e0->param[1]) e0->param[1]->value *= (sign2|1);
    }
    𐤀𐤌 (e0) e0->value *= (sign|1);

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_term(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    𐤀𐤌 ((ret = parse_factor(&e0, p)) < 0)
        أرجع ret;
    طالما (p->s[0]=='*' || p->s[0]=='/') {
        صحيح c= *p->s++;
        e1 = e0;
        𐤀𐤌 ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            أرجع ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        𐤀𐤌 (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
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
    𐤀𐤌 ((ret = parse_term(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        𐤀𐤌 ((ret = parse_term(&e2, p)) < 0) {
            av_expr_free(e1);
            أرجع ret;
        }
        e0 = make_eval_expr(e_add, 1, e1, e2);
        𐤀𐤌 (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    *e = e0;
    أرجع 0;
}

ساكن صحيح parse_expr(AVExpr **e, Parser *p)
{
    صحيح ret;
    AVExpr *e0, *e1, *e2;
    𐤀𐤌 (p->stack_index <= 0) //protect against stack overflows
        أرجع AVERROR(EINVAL);
    p->stack_index--;

    𐤀𐤌 ((ret = parse_subexpr(&e0, p)) < 0)
        أرجع ret;
    طالما (*p->s == ';') {
        p->s++;
        e1 = e0;
        𐤀𐤌 ((ret = parse_subexpr(&e2, p)) < 0) {
            av_expr_free(e1);
            أرجع ret;
        }
        e0 = make_eval_expr(e_last, 1, e1, e2);
        𐤀𐤌 (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            أرجع AVERROR(ENOMEM);
        }
    };

    p->stack_index++;
    *e = e0;
    أرجع 0;
}

ساكن صحيح verify_expr(AVExpr *e)
{
    𐤀𐤌 (!e) أرجع 0;
    بدل (e->type) {
        حالة e_value:
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
        حالة e_round:
        حالة e_sqrt:
        حالة e_not:
        حالة e_random:
        حالة e_sgn:
            أرجع verify_expr(e->param[0]) && !e->param[1];
        حالة e_print:
            أرجع verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        حالة e_if:
        حالة e_ifnot:
        حالة e_taylor:
            أرجع verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        حالة e_between:
        حالة e_clip:
        حالة e_lerp:
        حالة e_randomi:
            أرجع verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        افتراضي: أرجع verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
    }
}

صحيح av_expr_parse(AVExpr **expr, ثابت حرف *s,
                  ثابت حرف * ثابت *const_names,
                  ثابت حرف * ثابت *func1_names, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                  ثابت حرف * ثابت *func2_names, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                  صحيح log_offset, فراغ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = عدم;
    حرف *w = av_malloc(strlen(s) + 1);
    حرف *wp = w;
    ثابت حرف *s0 = s;
    صحيح ret = 0;

    𐤀𐤌 (!w)
        أرجع AVERROR(ENOMEM);

    طالما (*s)
        𐤀𐤌 (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.stack_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    𐤀𐤌 ((ret = parse_expr(&e, &p)) < 0)
        اذهب end;
    𐤀𐤌 (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        اذهب end;
    }
    𐤀𐤌 (!verify_expr(e)) {
        ret = AVERROR(EINVAL);
        اذهب end;
    }
    AVExprRoot *r = av_realloc(e, حجم(*r));
    𐤀𐤌 (!r) {
        ret = AVERROR(ENOMEM);
        اذهب end;
    }
    e = (AVExpr*)r;
    e->root = 1;
    r->var= av_mallocz(حجم(مزدوج) *VARS);
    r->prng_state = av_mallocz(حجم(*r->prng_state) *VARS);
    𐤀𐤌 (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        اذهب end;
    }
    *expr = e;
    e = عدم;
end:
    av_expr_free(e);
    av_free(w);
    أرجع ret;
}

ساكن صحيح expr_count(AVExpr *e, unsigned *counter, صحيح size, صحيح type)
{
    صحيح i;

    𐤀𐤌 (!e || !counter || !size)
        أرجع AVERROR(EINVAL);

    لكل (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        expr_count(e->param[i], counter, size, type);

    𐤀𐤌 (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    أرجع 0;
}

صحيح av_expr_count_vars(AVExpr *e, unsigned *counter, صحيح size)
{
    أرجع expr_count(e, counter, size, e_const);
}

صحيح av_expr_count_func(AVExpr *e, unsigned *counter, صحيح size, صحيح arg)
{
    أرجع expr_count(e, counter, size, ((صحيح[]){e_const, e_func1, e_func2})[arg]);
}

مزدوج av_expr_eval(AVExpr *e, ثابت مزدوج *const_values, فراغ *opaque)
{
    av_assert1(e->root);
    AVExprRoot *r = (AVExprRoot *)e;
    Parser p = {
        .class        = &eval_class,
        .const_values = const_values,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    أرجع eval_expr(&p, e);
}

صحيح av_expr_parse_and_eval(مزدوج *d, ثابت حرف *s,
                           ثابت حرف * ثابت *const_names, ثابت مزدوج *const_values,
                           ثابت حرف * ثابت *func1_names, مزدوج (* ثابت *funcs1)(فراغ *, مزدوج),
                           ثابت حرف * ثابت *func2_names, مزدوج (* ثابت *funcs2)(فراغ *, مزدوج, مزدوج),
                           فراغ *opaque, صحيح log_offset, فراغ *log_ctx)
{
    AVExpr *e = عدم;
    صحيح ret = av_expr_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    𐤀𐤌 (ret < 0) {
        *d = NAN;
        أرجع ret;
    }
    *d = av_expr_eval(e, const_values, opaque);
    av_expr_free(e);
    أرجع isnan(*d) ? AVERROR(EINVAL) : 0;
}
