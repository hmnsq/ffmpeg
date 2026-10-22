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

#include <float.h>
#include "attributes.h"
#include "avassert.h"
#include "avutil.h"
#include "common.h"
#include "eval.h"
#include "ffmath.h"
#include "log.h"
#include "mathematics.h"
#include "mem.h"
#include "sfc64.h"
#include "time.h"
#include "avstring.h"
#include "reverse.h"

#define MAX_DEPTH 100

typedef sa_nracanaa Parser {
    const AVClass *class;
    ကိန်းပြည့် stack_index;
    var_na *s;
    const dviguu_na *const_values;
    const var_na * const *const_names;          // NULL terminated
    dviguu_na (* const *funcs1)(void *, dviguu_na a);           // NULL terminated
    const var_na * const *func1_names;          // NULL terminated
    dviguu_na (* const *funcs2)(void *, dviguu_na a, dviguu_na b); // NULL terminated
    const var_na * const *func2_names;          // NULL terminated
    void *opaque;
    ကိန်းပြည့် log_offset;
    void *log_ctx;
#define VARS 10
    dviguu_na *var;
    FFSFC64 *prng_state;
} Parser;

static const AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = NULL,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

static const sa_nracanaa {
    dviguu_na bin_val;
    dviguu_na dec_val;
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

static const sa_nracanaa {
    const var_na *name;
    dviguu_na value;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

dviguu_na av_strtod(const var_na *numstr, var_na **tail)
{
    dviguu_na d;
    var_na *next;
    အကယ်၍(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } မဟုတ်ပါက
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    အကယ်၍ (next!=numstr) {
        အကယ်၍ (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } မဟုတ်ပါက အကယ်၍ (*next >= 'E' && *next <= 'z') {
            ကိန်းပြည့် e= si_prefixes[*next - 'E'].exp;
            အကယ်၍ (e) {
                အကယ်၍ (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } မဟုတ်ပါက {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        အကယ်၍ (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    အကယ်၍ (tail)
        *tail = next;
    ပြန်ပေး d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

static ကိန်းပြည့် strmatch(const var_na *s, const var_na *prefix)
{
    ကိန်းပြည့် i;
    အတွက် (i=0; prefix[i]; i++) {
        အကယ်၍ (prefix[i] != s[i]) ပြန်ပေး 0;
    }
    /* return 1 only if the s identifier is terminated */
    ပြန်ပေး !IS_IDENTIFIER_CHAR(s[i]);
}

ga_nanaa {
    e_value, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_root, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
sa_nracanaa AVExpr {
    unsigned var_na type;
    unsigned var_na root;
    short depth;
    ကိန်းပြည့် const_index;
    dviguu_na value; // is sign in other types
    sa_ngha {
        dviguu_na (*func0)(dviguu_na);
        dviguu_na (*func1)(void *, dviguu_na);
        dviguu_na (*func2)(void *, dviguu_na, dviguu_na);
    } ;
    sa_nracanaa AVExpr *param[3];
};

typedef sa_nracanaa {
    AVExpr avexpr;
    dviguu_na *var;
    FFSFC64 *prng_state;
} AVExprRoot;

static dviguu_na etime(dviguu_na v)
{
    ပြန်ပေး av_gettime() * 0.000001;
}

static dviguu_na eval_expr(Parser *p, AVExpr *e)
{
    switch (e->type) {
        pak_sa e_value:  ပြန်ပေး e->value;
        pak_sa e_const:  ပြန်ပေး e->value * p->const_values[e->const_index];
        pak_sa e_func0:  ပြန်ပေး e->value * e->func0(eval_expr(p, e->param[0]));
        pak_sa e_func1:  ပြန်ပေး e->value * e->func1(p->opaque, eval_expr(p, e->param[0]));
        pak_sa e_func2:  ပြန်ပေး e->value * e->func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        pak_sa e_squish: ပြန်ပေး e->value/(1+exp(4*eval_expr(p, e->param[0])));
        pak_sa e_gauss: { dviguu_na d = eval_expr(p, e->param[0]); ပြန်ပေး e->value * exp(-d*d/2)/sqrt(2*M_PI); }
        pak_sa e_ld:     ပြန်ပေး e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        pak_sa e_isnan:  ပြန်ပေး e->value * !!isnan(eval_expr(p, e->param[0]));
        pak_sa e_isinf:  ပြန်ပေး e->value * !!isinf(eval_expr(p, e->param[0]));
        pak_sa e_floor:  ပြန်ပေး e->value * floor(eval_expr(p, e->param[0]));
        pak_sa e_ceil :  ပြန်ပေး e->value * ceil (eval_expr(p, e->param[0]));
        pak_sa e_trunc:  ပြန်ပေး e->value * trunc(eval_expr(p, e->param[0]));
        pak_sa e_round:  ပြန်ပေး e->value * round(eval_expr(p, e->param[0]));
        pak_sa e_sgn:    ပြန်ပေး e->value * FFDIFFSIGN(eval_expr(p, e->param[0]), 0);
        pak_sa e_sqrt:   ပြန်ပေး e->value * sqrt (eval_expr(p, e->param[0]));
        pak_sa e_not:    ပြန်ပေး e->value * (eval_expr(p, e->param[0]) == 0);
        pak_sa e_if:     ပြန်ပေး e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_ifnot:  ပြန်ပေး e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_clip: {
            dviguu_na x = eval_expr(p, e->param[0]);
            dviguu_na min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            အကယ်၍ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ပြန်ပေး NAN;
            ပြန်ပေး e->value * av_clipd(x, min, max);
        }
        pak_sa e_between: {
            dviguu_na d = eval_expr(p, e->param[0]);
            ပြန်ပေး e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        pak_sa e_lerp: {
            dviguu_na v0 = eval_expr(p, e->param[0]);
            dviguu_na v1 = eval_expr(p, e->param[1]);
            dviguu_na f  = eval_expr(p, e->param[2]);
            ပြန်ပေး e->value * (v0 + (v1 - v0) * f);
        }
        pak_sa e_print: {
            dviguu_na x = eval_expr(p, e->param[0]);
            ကိန်းပြည့် level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ပြန်ပေး e->value * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            ကိန်းပြည့် idx = av_clip(eval_expr(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            အကယ်၍ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        pak_sa e_random: {
            COMPUTE_NEXT_RANDOM();
            ပြန်ပေး r * (1.0/UINT64_MAX);
        }
        pak_sa e_randomi: {
            dviguu_na min = eval_expr(p, e->param[1]);
            dviguu_na max = eval_expr(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ပြန်ပေး min + (max - min) * r / UINT64_MAX;
        }
        pak_sa e_while: {
            dviguu_na d = NAN;
            နေစဉ် (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            ပြန်ပေး d;
        }
        pak_sa e_taylor: {
            dviguu_na t = 1, d = 0, v;
            dviguu_na x = eval_expr(p, e->param[1]);
            ကိန်းပြည့် id = e->param[2] ? av_clip(eval_expr(p, e->param[2]), 0, VARS-1) : 0;
            ကိန်းပြည့် i;
            dviguu_na var0 = p->var[id];
            အတွက်(i=0; i<1000; i++) {
                dviguu_na ld = d;
                p->var[id] = i;
                v = eval_expr(p, e->param[0]);
                d += t*v;
                အကယ်၍(ld==d && v)
                    bha_nga;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ပြန်ပေး d;
        }
        pak_sa e_root: {
            ကိန်းပြည့် i, j;
            dviguu_na low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            dviguu_na var0 = p->var[0];
            dviguu_na x_max = eval_expr(p, e->param[1]);
            အတွက်(i=-1; i<1024; i++) {
                အကယ်၍(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } မဟုတ်ပါက {
                    p->var[0] = x_max*pow(0.9, i-255);
                    အကယ်၍ (i&1) p->var[0] *= -1;
                    အကယ်၍ (i&2) p->var[0] += low;
                    မဟုတ်ပါက     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                အကယ်၍ (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                အကယ်၍ (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                အကယ်၍ (low>=0 && high>=0){
                    အတွက် (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        အကယ်၍ (low == p->var[0] || high == p->var[0])
                            bha_nga;
                        v = eval_expr(p, e->param[0]);
                        အကယ်၍ (v<=0) low = p->var[0];
                        အကယ်၍ (v>=0) high= p->var[0];
                        အကယ်၍ (isnan(v)) {
                            low = high = v;
                            bha_nga;
                        }
                    }
                    bha_nga;
                }
            }
            p->var[0] = var0;
            ပြန်ပေး -low_v<high_v ? low : high;
        }
        default: {
            dviguu_na d = eval_expr(p, e->param[0]);
            dviguu_na d2 = eval_expr(p, e->param[1]);
            switch (e->type) {
                pak_sa e_mod: ပြန်ပေး e->value * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                pak_sa e_gcd: ပြန်ပေး e->value * av_gcd(d,d2);
                pak_sa e_max: ပြန်ပေး e->value * (d >  d2 ?   d : d2);
                pak_sa e_min: ပြန်ပေး e->value * (d <  d2 ?   d : d2);
                pak_sa e_eq:  ပြန်ပေး e->value * (d == d2 ? 1.0 : 0.0);
                pak_sa e_gt:  ပြန်ပေး e->value * (d >  d2 ? 1.0 : 0.0);
                pak_sa e_gte: ပြန်ပေး e->value * (d >= d2 ? 1.0 : 0.0);
                pak_sa e_lt:  ပြန်ပေး e->value * (d <  d2 ? 1.0 : 0.0);
                pak_sa e_lte: ပြန်ပေး e->value * (d <= d2 ? 1.0 : 0.0);
                pak_sa e_pow: ပြန်ပေး e->value * pow(d, d2);
                pak_sa e_mul: ပြန်ပေး e->value * (d * d2);
                pak_sa e_div: ပြန်ပေး e->value * (d2 ? (d / d2) : d * INFINITY);
                pak_sa e_add: ပြန်ပေး e->value * (d + d2);
                pak_sa e_last:ပြန်ပေး e->value * d2;
                pak_sa e_st :  {
                    ကိန်းပြည့် index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ပြန်ပေး e->value * (p->var[index]= d2);
                }
                pak_sa e_hypot:ပြန်ပေး e->value * hypot(d, d2);
                pak_sa e_atan2:ပြန်ပေး e->value * atan2(d, d2);
                pak_sa e_bitand: ပြန်ပေး isnan(d) || isnan(d2) ? NAN : e->value * ((long ကိန်းပြည့်)d & (long ကိန်းပြည့်)d2);
                pak_sa e_bitor:  ပြန်ပေး isnan(d) || isnan(d2) ? NAN : e->value * ((long ကိန်းပြည့်)d | (long ကိန်းပြည့်)d2);
            }
        }
    }
    ပြန်ပေး NAN;
}

static ကိန်းပြည့် parse_expr(AVExpr **e, Parser *p);

void av_expr_free(AVExpr *e)
{
    အကယ်၍ (!e) ပြန်ပေး;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    အကယ်၍ (e->root) {
        AVExprRoot *r = (AVExprRoot*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

static ကိန်းပြည့် parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(parimaa_na(AVExpr));
    var_na *next = p->s, *s0 = p->s;
    ကိန်းပြည့် ret, i;

    အကယ်၍ (!d)
        ပြန်ပေး AVERROR(ENOMEM);

    /* number */
    d->value = av_strtod(p->s, &next);
    အကယ်၍ (next != p->s) {
        d->type = e_value;
        p->s= next;
        *e = d;
        ပြန်ပေး 0;
    }
    d->value = 1;

    /* named constants */
    အတွက် (i=0; p->const_names && p->const_names[i]; i++) {
        အကယ်၍ (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ပြန်ပေး 0;
        }
    }
    အတွက် (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        အကယ်၍ (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_value;
            d->value = constants[i].value;
            *e = d;
            ပြန်ပေး 0;
        }
    }

    p->s= strchr(p->s, '(');
    အကယ်၍ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_expr_free(d);
        ပြန်ပေး AVERROR(EINVAL);
    }
    p->s++; // "("
    အကယ်၍ (*next == '(') { // special case do-nothing
        av_freep(&d);
        အကယ်၍ ((ret = parse_expr(&d, p)) < 0)
            ပြန်ပေး ret;
        အကယ်၍ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_expr_free(d);
            ပြန်ပေး AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ပြန်ပေး 0;
    }
    အကယ်၍ ((ret = parse_expr(&(d->param[0]), p)) < 0) {
        av_expr_free(d);
        ပြန်ပေး ret;
    }
    အကယ်၍ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[1], p);
    }
    အကယ်၍ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[2], p);
    }
    အကယ်၍ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_expr_free(d);
        ပြန်ပေး AVERROR(EINVAL);
    }
    p->s++; // ")"

    အတွက် (ကိန်းပြည့် i = 0; i<3; i++)
        အကယ်၍ (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    အကယ်၍ (d->depth > MAX_DEPTH) {
        av_expr_free(d);
        ပြန်ပေး AVERROR(EINVAL);
    }

    d->type = e_func0;
         အကယ်၍ (strmatch(next, "sinh"  )) d->func0 = sinh;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "cosh"  )) d->func0 = cosh;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "tanh"  )) d->func0 = tanh;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "sin"   )) d->func0 = sin;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "cos"   )) d->func0 = cos;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "tan"   )) d->func0 = tan;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "atan"  )) d->func0 = atan;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "asin"  )) d->func0 = asin;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "acos"  )) d->func0 = acos;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "exp"   )) d->func0 = exp;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "log"   )) d->func0 = log;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "abs"   )) d->func0 = fabs;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "time"  )) d->func0 = etime;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "squish")) d->type = e_squish;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "gauss" )) d->type = e_gauss;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "mod"   )) d->type = e_mod;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "max"   )) d->type = e_max;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "min"   )) d->type = e_min;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "eq"    )) d->type = e_eq;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "gte"   )) d->type = e_gte;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "gt"    )) d->type = e_gt;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "lte"   )) d->type = e_lte;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "lt"    )) d->type = e_lt;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "ld"    )) d->type = e_ld;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "isnan" )) d->type = e_isnan;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "isinf" )) d->type = e_isinf;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "st"    )) d->type = e_st;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "while" )) d->type = e_while;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "taylor")) d->type = e_taylor;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "root"  )) d->type = e_root;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "floor" )) d->type = e_floor;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "ceil"  )) d->type = e_ceil;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "trunc" )) d->type = e_trunc;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "round" )) d->type = e_round;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "not"   )) d->type = e_not;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "pow"   )) d->type = e_pow;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "print" )) d->type = e_print;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "random")) d->type = e_random;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "randomi")) d->type = e_randomi;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "hypot" )) d->type = e_hypot;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "gcd"   )) d->type = e_gcd;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "if"    )) d->type = e_if;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "ifnot" )) d->type = e_ifnot;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "bitand")) d->type = e_bitand;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "bitor" )) d->type = e_bitor;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "between"))d->type = e_between;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "clip"  )) d->type = e_clip;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "atan2" )) d->type = e_atan2;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "lerp"  )) d->type = e_lerp;
    မဟုတ်ပါက အကယ်၍ (strmatch(next, "sgn"   )) d->type = e_sgn;
    မဟုတ်ပါက {
        အတွက် (i=0; p->func1_names && p->func1_names[i]; i++) {
            အကယ်၍ (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ပြန်ပေး 0;
            }
        }

        အတွက် (i=0; p->func2_names && p->func2_names[i]; i++) {
            အကယ်၍ (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ပြန်ပေး 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_expr_free(d);
        ပြန်ပေး AVERROR(EINVAL);
    }

    *e = d;
    ပြန်ပေး 0;
}

static AVExpr *make_eval_expr(ကိန်းပြည့် type, ကိန်းပြည့် value, AVExpr *p0, AVExpr *p1)
{
    ကိန်းပြည့် depth = FFMAX(p0->depth, p1->depth) + 1;
    အကယ်၍ (depth > MAX_DEPTH)
        ပြန်ပေး NULL;
    AVExpr *e = av_mallocz(parimaa_na(AVExpr));
    အကယ်၍ (!e)
        ပြန်ပေး NULL;
    e->type     =type   ;
    e->value    =value  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ပြန်ပေး e;
}

static ကိန်းပြည့် parse_pow(AVExpr **e, Parser *p, ကိန်းပြည့် *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ပြန်ပေး parse_primary(e, p);
}

static ကိန်းပြည့် parse_dB(AVExpr **e, Parser *p, ကိန်းပြည့် *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    အကယ်၍ (*p->s == '-') {
        var_na *next;
        av_unused dviguu_na ignored = strtod(p->s, &next);
        အကယ်၍ (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ပြန်ပေး parse_primary(e, p);
        }
    }
    ပြန်ပေး parse_pow(e, p, sign);
}

static ကိန်းပြည့် parse_factor(AVExpr **e, Parser *p)
{
    ကိန်းပြည့် sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    အကယ်၍ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ပြန်ပေး ret;
    နေစဉ်(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        အကယ်၍ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_expr_free(e1);
            ပြန်ပေး ret;
        }
        e0 = make_eval_expr(e_pow, 1, e1, e2);
        အကယ်၍ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ပြန်ပေး AVERROR(ENOMEM);
        }
        အကယ်၍ (e0->param[1]) e0->param[1]->value *= (sign2|1);
    }
    အကယ်၍ (e0) e0->value *= (sign|1);

    *e = e0;
    ပြန်ပေး 0;
}

static ကိန်းပြည့် parse_term(AVExpr **e, Parser *p)
{
    ကိန်းပြည့် ret;
    AVExpr *e0, *e1, *e2;
    အကယ်၍ ((ret = parse_factor(&e0, p)) < 0)
        ပြန်ပေး ret;
    နေစဉ် (p->s[0]=='*' || p->s[0]=='/') {
        ကိန်းပြည့် c= *p->s++;
        e1 = e0;
        အကယ်၍ ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            ပြန်ပေး ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        အကယ်၍ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ပြန်ပေး AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ပြန်ပေး 0;
}

static ကိန်းပြည့် parse_subexpr(AVExpr **e, Parser *p)
{
    ကိန်းပြည့် ret;
    AVExpr *e0, *e1, *e2;
    အကယ်၍ ((ret = parse_term(&e0, p)) < 0)
        ပြန်ပေး ret;
    နေစဉ် (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        အကယ်၍ ((ret = parse_term(&e2, p)) < 0) {
            av_expr_free(e1);
            ပြန်ပေး ret;
        }
        e0 = make_eval_expr(e_add, 1, e1, e2);
        အကယ်၍ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ပြန်ပေး AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ပြန်ပေး 0;
}

static ကိန်းပြည့် parse_expr(AVExpr **e, Parser *p)
{
    ကိန်းပြည့် ret;
    AVExpr *e0, *e1, *e2;
    အကယ်၍ (p->stack_index <= 0) //protect against stack overflows
        ပြန်ပေး AVERROR(EINVAL);
    p->stack_index--;

    အကယ်၍ ((ret = parse_subexpr(&e0, p)) < 0)
        ပြန်ပေး ret;
    နေစဉ် (*p->s == ';') {
        p->s++;
        e1 = e0;
        အကယ်၍ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_expr_free(e1);
            ပြန်ပေး ret;
        }
        e0 = make_eval_expr(e_last, 1, e1, e2);
        အကယ်၍ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ပြန်ပေး AVERROR(ENOMEM);
        }
    };

    p->stack_index++;
    *e = e0;
    ပြန်ပေး 0;
}

static ကိန်းပြည့် verify_expr(AVExpr *e)
{
    အကယ်၍ (!e) ပြန်ပေး 0;
    switch (e->type) {
        pak_sa e_value:
        pak_sa e_const: ပြန်ပေး 1;
        pak_sa e_func0:
        pak_sa e_func1:
        pak_sa e_squish:
        pak_sa e_ld:
        pak_sa e_gauss:
        pak_sa e_isnan:
        pak_sa e_isinf:
        pak_sa e_floor:
        pak_sa e_ceil:
        pak_sa e_trunc:
        pak_sa e_round:
        pak_sa e_sqrt:
        pak_sa e_not:
        pak_sa e_random:
        pak_sa e_sgn:
            ပြန်ပေး verify_expr(e->param[0]) && !e->param[1];
        pak_sa e_print:
            ပြန်ပေး verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        pak_sa e_if:
        pak_sa e_ifnot:
        pak_sa e_taylor:
            ပြန်ပေး verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        pak_sa e_between:
        pak_sa e_clip:
        pak_sa e_lerp:
        pak_sa e_randomi:
            ပြန်ပေး verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        default: ပြန်ပေး verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
    }
}

ကိန်းပြည့် av_expr_parse(AVExpr **expr, const var_na *s,
                  const var_na * const *const_names,
                  const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                  const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                  ကိန်းပြည့် log_offset, void *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = NULL;
    var_na *w = av_malloc(strlen(s) + 1);
    var_na *wp = w;
    const var_na *s0 = s;
    ကိန်းပြည့် ret = 0;

    အကယ်၍ (!w)
        ပြန်ပေး AVERROR(ENOMEM);

    နေစဉ် (*s)
        အကယ်၍ (!av_isspace(*s++)) *wp++ = s[-1];
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

    အကယ်၍ ((ret = parse_expr(&e, &p)) < 0)
        goto end;
    အကယ်၍ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        goto end;
    }
    အကယ်၍ (!verify_expr(e)) {
        ret = AVERROR(EINVAL);
        goto end;
    }
    AVExprRoot *r = av_realloc(e, parimaa_na(*r));
    အကယ်၍ (!r) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    e = (AVExpr*)r;
    e->root = 1;
    r->var= av_mallocz(parimaa_na(dviguu_na) *VARS);
    r->prng_state = av_mallocz(parimaa_na(*r->prng_state) *VARS);
    အကယ်၍ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    *expr = e;
    e = NULL;
end:
    av_expr_free(e);
    av_free(w);
    ပြန်ပေး ret;
}

static ကိန်းပြည့် expr_count(AVExpr *e, unsigned *counter, ကိန်းပြည့် size, ကိန်းပြည့် type)
{
    ကိန်းပြည့် i;

    အကယ်၍ (!e || !counter || !size)
        ပြန်ပေး AVERROR(EINVAL);

    အတွက် (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        expr_count(e->param[i], counter, size, type);

    အကယ်၍ (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ပြန်ပေး 0;
}

ကိန်းပြည့် av_expr_count_vars(AVExpr *e, unsigned *counter, ကိန်းပြည့် size)
{
    ပြန်ပေး expr_count(e, counter, size, e_const);
}

ကိန်းပြည့် av_expr_count_func(AVExpr *e, unsigned *counter, ကိန်းပြည့် size, ကိန်းပြည့် arg)
{
    ပြန်ပေး expr_count(e, counter, size, ((ကိန်းပြည့်[]){e_const, e_func1, e_func2})[arg]);
}

dviguu_na av_expr_eval(AVExpr *e, const dviguu_na *const_values, void *opaque)
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

    ပြန်ပေး eval_expr(&p, e);
}

ကိန်းပြည့် av_expr_parse_and_eval(dviguu_na *d, const var_na *s,
                           const var_na * const *const_names, const dviguu_na *const_values,
                           const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                           const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                           void *opaque, ကိန်းပြည့် log_offset, void *log_ctx)
{
    AVExpr *e = NULL;
    ကိန်းပြည့် ret = av_expr_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    အကယ်၍ (ret < 0) {
        *d = NAN;
        ပြန်ပေး ret;
    }
    *d = av_expr_eval(e, const_values, opaque);
    av_expr_free(e);
    ပြန်ပေး isnan(*d) ? AVERROR(EINVAL) : 0;
}
