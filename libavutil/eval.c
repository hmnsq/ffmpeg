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
    puur_naa_nka stack_index;
    var_na *s;
    const dviguu_na *const_values;
    const var_na * const *const_names;          // NULL terminated
    dviguu_na (* const *funcs1)(void *, dviguu_na a);           // NULL terminated
    const var_na * const *func1_names;          // NULL terminated
    dviguu_na (* const *funcs2)(void *, dviguu_na a, dviguu_na b); // NULL terminated
    const var_na * const *func2_names;          // NULL terminated
    void *opaque;
    puur_naa_nka log_offset;
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
    ᮚᮦᮔ᮪(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } ᮜᮤᮚ
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    ᮚᮦᮔ᮪ (next!=numstr) {
        ᮚᮦᮔ᮪ (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } ᮜᮤᮚ ᮚᮦᮔ᮪ (*next >= 'E' && *next <= 'z') {
            puur_naa_nka e= si_prefixes[*next - 'E'].exp;
            ᮚᮦᮔ᮪ (e) {
                ᮚᮦᮔ᮪ (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } ᮜᮤᮚ {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        ᮚᮦᮔ᮪ (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ᮚᮦᮔ᮪ (tail)
        *tail = next;
    ᮝᮜᮤ d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

static puur_naa_nka strmatch(const var_na *s, const var_na *prefix)
{
    puur_naa_nka i;
    for (i=0; prefix[i]; i++) {
        ᮚᮦᮔ᮪ (prefix[i] != s[i]) ᮝᮜᮤ 0;
    }
    /* return 1 only if the s identifier is terminated */
    ᮝᮜᮤ !IS_IDENTIFIER_CHAR(s[i]);
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
    puur_naa_nka const_index;
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
    ᮝᮜᮤ av_gettime() * 0.000001;
}

static dviguu_na eval_expr(Parser *p, AVExpr *e)
{
    switch (e->type) {
        pak_sa e_value:  ᮝᮜᮤ e->value;
        pak_sa e_const:  ᮝᮜᮤ e->value * p->const_values[e->const_index];
        pak_sa e_func0:  ᮝᮜᮤ e->value * e->func0(eval_expr(p, e->param[0]));
        pak_sa e_func1:  ᮝᮜᮤ e->value * e->func1(p->opaque, eval_expr(p, e->param[0]));
        pak_sa e_func2:  ᮝᮜᮤ e->value * e->func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        pak_sa e_squish: ᮝᮜᮤ e->value/(1+exp(4*eval_expr(p, e->param[0])));
        pak_sa e_gauss: { dviguu_na d = eval_expr(p, e->param[0]); ᮝᮜᮤ e->value * exp(-d*d/2)/sqrt(2*M_PI); }
        pak_sa e_ld:     ᮝᮜᮤ e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        pak_sa e_isnan:  ᮝᮜᮤ e->value * !!isnan(eval_expr(p, e->param[0]));
        pak_sa e_isinf:  ᮝᮜᮤ e->value * !!isinf(eval_expr(p, e->param[0]));
        pak_sa e_floor:  ᮝᮜᮤ e->value * floor(eval_expr(p, e->param[0]));
        pak_sa e_ceil :  ᮝᮜᮤ e->value * ceil (eval_expr(p, e->param[0]));
        pak_sa e_trunc:  ᮝᮜᮤ e->value * trunc(eval_expr(p, e->param[0]));
        pak_sa e_round:  ᮝᮜᮤ e->value * round(eval_expr(p, e->param[0]));
        pak_sa e_sgn:    ᮝᮜᮤ e->value * FFDIFFSIGN(eval_expr(p, e->param[0]), 0);
        pak_sa e_sqrt:   ᮝᮜᮤ e->value * sqrt (eval_expr(p, e->param[0]));
        pak_sa e_not:    ᮝᮜᮤ e->value * (eval_expr(p, e->param[0]) == 0);
        pak_sa e_if:     ᮝᮜᮤ e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_ifnot:  ᮝᮜᮤ e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_clip: {
            dviguu_na x = eval_expr(p, e->param[0]);
            dviguu_na min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            ᮚᮦᮔ᮪ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ᮝᮜᮤ NAN;
            ᮝᮜᮤ e->value * av_clipd(x, min, max);
        }
        pak_sa e_between: {
            dviguu_na d = eval_expr(p, e->param[0]);
            ᮝᮜᮤ e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        pak_sa e_lerp: {
            dviguu_na v0 = eval_expr(p, e->param[0]);
            dviguu_na v1 = eval_expr(p, e->param[1]);
            dviguu_na f  = eval_expr(p, e->param[2]);
            ᮝᮜᮤ e->value * (v0 + (v1 - v0) * f);
        }
        pak_sa e_print: {
            dviguu_na x = eval_expr(p, e->param[0]);
            puur_naa_nka level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ᮝᮜᮤ e->value * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            puur_naa_nka idx = av_clip(eval_expr(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ᮚᮦᮔ᮪ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        pak_sa e_random: {
            COMPUTE_NEXT_RANDOM();
            ᮝᮜᮤ r * (1.0/UINT64_MAX);
        }
        pak_sa e_randomi: {
            dviguu_na min = eval_expr(p, e->param[1]);
            dviguu_na max = eval_expr(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ᮝᮜᮤ min + (max - min) * r / UINT64_MAX;
        }
        pak_sa e_while: {
            dviguu_na d = NAN;
            ᮞᮨᮓᮨᮜ (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            ᮝᮜᮤ d;
        }
        pak_sa e_taylor: {
            dviguu_na t = 1, d = 0, v;
            dviguu_na x = eval_expr(p, e->param[1]);
            puur_naa_nka id = e->param[2] ? av_clip(eval_expr(p, e->param[2]), 0, VARS-1) : 0;
            puur_naa_nka i;
            dviguu_na var0 = p->var[id];
            for(i=0; i<1000; i++) {
                dviguu_na ld = d;
                p->var[id] = i;
                v = eval_expr(p, e->param[0]);
                d += t*v;
                ᮚᮦᮔ᮪(ld==d && v)
                    bha_nga;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ᮝᮜᮤ d;
        }
        pak_sa e_root: {
            puur_naa_nka i, j;
            dviguu_na low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            dviguu_na var0 = p->var[0];
            dviguu_na x_max = eval_expr(p, e->param[1]);
            for(i=-1; i<1024; i++) {
                ᮚᮦᮔ᮪(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } ᮜᮤᮚ {
                    p->var[0] = x_max*pow(0.9, i-255);
                    ᮚᮦᮔ᮪ (i&1) p->var[0] *= -1;
                    ᮚᮦᮔ᮪ (i&2) p->var[0] += low;
                    ᮜᮤᮚ     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                ᮚᮦᮔ᮪ (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                ᮚᮦᮔ᮪ (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                ᮚᮦᮔ᮪ (low>=0 && high>=0){
                    for (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        ᮚᮦᮔ᮪ (low == p->var[0] || high == p->var[0])
                            bha_nga;
                        v = eval_expr(p, e->param[0]);
                        ᮚᮦᮔ᮪ (v<=0) low = p->var[0];
                        ᮚᮦᮔ᮪ (v>=0) high= p->var[0];
                        ᮚᮦᮔ᮪ (isnan(v)) {
                            low = high = v;
                            bha_nga;
                        }
                    }
                    bha_nga;
                }
            }
            p->var[0] = var0;
            ᮝᮜᮤ -low_v<high_v ? low : high;
        }
        default: {
            dviguu_na d = eval_expr(p, e->param[0]);
            dviguu_na d2 = eval_expr(p, e->param[1]);
            switch (e->type) {
                pak_sa e_mod: ᮝᮜᮤ e->value * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                pak_sa e_gcd: ᮝᮜᮤ e->value * av_gcd(d,d2);
                pak_sa e_max: ᮝᮜᮤ e->value * (d >  d2 ?   d : d2);
                pak_sa e_min: ᮝᮜᮤ e->value * (d <  d2 ?   d : d2);
                pak_sa e_eq:  ᮝᮜᮤ e->value * (d == d2 ? 1.0 : 0.0);
                pak_sa e_gt:  ᮝᮜᮤ e->value * (d >  d2 ? 1.0 : 0.0);
                pak_sa e_gte: ᮝᮜᮤ e->value * (d >= d2 ? 1.0 : 0.0);
                pak_sa e_lt:  ᮝᮜᮤ e->value * (d <  d2 ? 1.0 : 0.0);
                pak_sa e_lte: ᮝᮜᮤ e->value * (d <= d2 ? 1.0 : 0.0);
                pak_sa e_pow: ᮝᮜᮤ e->value * pow(d, d2);
                pak_sa e_mul: ᮝᮜᮤ e->value * (d * d2);
                pak_sa e_div: ᮝᮜᮤ e->value * (d2 ? (d / d2) : d * INFINITY);
                pak_sa e_add: ᮝᮜᮤ e->value * (d + d2);
                pak_sa e_last:ᮝᮜᮤ e->value * d2;
                pak_sa e_st :  {
                    puur_naa_nka index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ᮝᮜᮤ e->value * (p->var[index]= d2);
                }
                pak_sa e_hypot:ᮝᮜᮤ e->value * hypot(d, d2);
                pak_sa e_atan2:ᮝᮜᮤ e->value * atan2(d, d2);
                pak_sa e_bitand: ᮝᮜᮤ isnan(d) || isnan(d2) ? NAN : e->value * ((long puur_naa_nka)d & (long puur_naa_nka)d2);
                pak_sa e_bitor:  ᮝᮜᮤ isnan(d) || isnan(d2) ? NAN : e->value * ((long puur_naa_nka)d | (long puur_naa_nka)d2);
            }
        }
    }
    ᮝᮜᮤ NAN;
}

static puur_naa_nka parse_expr(AVExpr **e, Parser *p);

void av_expr_free(AVExpr *e)
{
    ᮚᮦᮔ᮪ (!e) ᮝᮜᮤ;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    ᮚᮦᮔ᮪ (e->root) {
        AVExprRoot *r = (AVExprRoot*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

static puur_naa_nka parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(parimaa_na(AVExpr));
    var_na *next = p->s, *s0 = p->s;
    puur_naa_nka ret, i;

    ᮚᮦᮔ᮪ (!d)
        ᮝᮜᮤ AVERROR(ENOMEM);

    /* number */
    d->value = av_strtod(p->s, &next);
    ᮚᮦᮔ᮪ (next != p->s) {
        d->type = e_value;
        p->s= next;
        *e = d;
        ᮝᮜᮤ 0;
    }
    d->value = 1;

    /* named constants */
    for (i=0; p->const_names && p->const_names[i]; i++) {
        ᮚᮦᮔ᮪ (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ᮝᮜᮤ 0;
        }
    }
    for (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ᮚᮦᮔ᮪ (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_value;
            d->value = constants[i].value;
            *e = d;
            ᮝᮜᮤ 0;
        }
    }

    p->s= strchr(p->s, '(');
    ᮚᮦᮔ᮪ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_expr_free(d);
        ᮝᮜᮤ AVERROR(EINVAL);
    }
    p->s++; // "("
    ᮚᮦᮔ᮪ (*next == '(') { // special case do-nothing
        av_freep(&d);
        ᮚᮦᮔ᮪ ((ret = parse_expr(&d, p)) < 0)
            ᮝᮜᮤ ret;
        ᮚᮦᮔ᮪ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_expr_free(d);
            ᮝᮜᮤ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ᮝᮜᮤ 0;
    }
    ᮚᮦᮔ᮪ ((ret = parse_expr(&(d->param[0]), p)) < 0) {
        av_expr_free(d);
        ᮝᮜᮤ ret;
    }
    ᮚᮦᮔ᮪ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[1], p);
    }
    ᮚᮦᮔ᮪ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[2], p);
    }
    ᮚᮦᮔ᮪ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_expr_free(d);
        ᮝᮜᮤ AVERROR(EINVAL);
    }
    p->s++; // ")"

    for (puur_naa_nka i = 0; i<3; i++)
        ᮚᮦᮔ᮪ (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    ᮚᮦᮔ᮪ (d->depth > MAX_DEPTH) {
        av_expr_free(d);
        ᮝᮜᮤ AVERROR(EINVAL);
    }

    d->type = e_func0;
         ᮚᮦᮔ᮪ (strmatch(next, "sinh"  )) d->func0 = sinh;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "cosh"  )) d->func0 = cosh;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "tanh"  )) d->func0 = tanh;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "sin"   )) d->func0 = sin;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "cos"   )) d->func0 = cos;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "tan"   )) d->func0 = tan;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "atan"  )) d->func0 = atan;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "asin"  )) d->func0 = asin;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "acos"  )) d->func0 = acos;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "exp"   )) d->func0 = exp;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "log"   )) d->func0 = log;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "abs"   )) d->func0 = fabs;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "time"  )) d->func0 = etime;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "squish")) d->type = e_squish;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "gauss" )) d->type = e_gauss;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "mod"   )) d->type = e_mod;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "max"   )) d->type = e_max;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "min"   )) d->type = e_min;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "eq"    )) d->type = e_eq;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "gte"   )) d->type = e_gte;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "gt"    )) d->type = e_gt;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "lte"   )) d->type = e_lte;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "lt"    )) d->type = e_lt;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "ld"    )) d->type = e_ld;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "isnan" )) d->type = e_isnan;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "isinf" )) d->type = e_isinf;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "st"    )) d->type = e_st;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "while" )) d->type = e_while;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "taylor")) d->type = e_taylor;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "root"  )) d->type = e_root;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "floor" )) d->type = e_floor;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "ceil"  )) d->type = e_ceil;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "trunc" )) d->type = e_trunc;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "round" )) d->type = e_round;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "not"   )) d->type = e_not;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "pow"   )) d->type = e_pow;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "print" )) d->type = e_print;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "random")) d->type = e_random;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "randomi")) d->type = e_randomi;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "hypot" )) d->type = e_hypot;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "gcd"   )) d->type = e_gcd;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "if"    )) d->type = e_if;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "ifnot" )) d->type = e_ifnot;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "bitand")) d->type = e_bitand;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "bitor" )) d->type = e_bitor;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "between"))d->type = e_between;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "clip"  )) d->type = e_clip;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "atan2" )) d->type = e_atan2;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "lerp"  )) d->type = e_lerp;
    ᮜᮤᮚ ᮚᮦᮔ᮪ (strmatch(next, "sgn"   )) d->type = e_sgn;
    ᮜᮤᮚ {
        for (i=0; p->func1_names && p->func1_names[i]; i++) {
            ᮚᮦᮔ᮪ (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ᮝᮜᮤ 0;
            }
        }

        for (i=0; p->func2_names && p->func2_names[i]; i++) {
            ᮚᮦᮔ᮪ (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ᮝᮜᮤ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_expr_free(d);
        ᮝᮜᮤ AVERROR(EINVAL);
    }

    *e = d;
    ᮝᮜᮤ 0;
}

static AVExpr *make_eval_expr(puur_naa_nka type, puur_naa_nka value, AVExpr *p0, AVExpr *p1)
{
    puur_naa_nka depth = FFMAX(p0->depth, p1->depth) + 1;
    ᮚᮦᮔ᮪ (depth > MAX_DEPTH)
        ᮝᮜᮤ NULL;
    AVExpr *e = av_mallocz(parimaa_na(AVExpr));
    ᮚᮦᮔ᮪ (!e)
        ᮝᮜᮤ NULL;
    e->type     =type   ;
    e->value    =value  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ᮝᮜᮤ e;
}

static puur_naa_nka parse_pow(AVExpr **e, Parser *p, puur_naa_nka *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ᮝᮜᮤ parse_primary(e, p);
}

static puur_naa_nka parse_dB(AVExpr **e, Parser *p, puur_naa_nka *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ᮚᮦᮔ᮪ (*p->s == '-') {
        var_na *next;
        av_unused dviguu_na ignored = strtod(p->s, &next);
        ᮚᮦᮔ᮪ (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ᮝᮜᮤ parse_primary(e, p);
        }
    }
    ᮝᮜᮤ parse_pow(e, p, sign);
}

static puur_naa_nka parse_factor(AVExpr **e, Parser *p)
{
    puur_naa_nka sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ᮚᮦᮔ᮪ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ᮝᮜᮤ ret;
    ᮞᮨᮓᮨᮜ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ᮚᮦᮔ᮪ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_expr_free(e1);
            ᮝᮜᮤ ret;
        }
        e0 = make_eval_expr(e_pow, 1, e1, e2);
        ᮚᮦᮔ᮪ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᮝᮜᮤ AVERROR(ENOMEM);
        }
        ᮚᮦᮔ᮪ (e0->param[1]) e0->param[1]->value *= (sign2|1);
    }
    ᮚᮦᮔ᮪ (e0) e0->value *= (sign|1);

    *e = e0;
    ᮝᮜᮤ 0;
}

static puur_naa_nka parse_term(AVExpr **e, Parser *p)
{
    puur_naa_nka ret;
    AVExpr *e0, *e1, *e2;
    ᮚᮦᮔ᮪ ((ret = parse_factor(&e0, p)) < 0)
        ᮝᮜᮤ ret;
    ᮞᮨᮓᮨᮜ (p->s[0]=='*' || p->s[0]=='/') {
        puur_naa_nka c= *p->s++;
        e1 = e0;
        ᮚᮦᮔ᮪ ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            ᮝᮜᮤ ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        ᮚᮦᮔ᮪ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᮝᮜᮤ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ᮝᮜᮤ 0;
}

static puur_naa_nka parse_subexpr(AVExpr **e, Parser *p)
{
    puur_naa_nka ret;
    AVExpr *e0, *e1, *e2;
    ᮚᮦᮔ᮪ ((ret = parse_term(&e0, p)) < 0)
        ᮝᮜᮤ ret;
    ᮞᮨᮓᮨᮜ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ᮚᮦᮔ᮪ ((ret = parse_term(&e2, p)) < 0) {
            av_expr_free(e1);
            ᮝᮜᮤ ret;
        }
        e0 = make_eval_expr(e_add, 1, e1, e2);
        ᮚᮦᮔ᮪ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᮝᮜᮤ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ᮝᮜᮤ 0;
}

static puur_naa_nka parse_expr(AVExpr **e, Parser *p)
{
    puur_naa_nka ret;
    AVExpr *e0, *e1, *e2;
    ᮚᮦᮔ᮪ (p->stack_index <= 0) //protect against stack overflows
        ᮝᮜᮤ AVERROR(EINVAL);
    p->stack_index--;

    ᮚᮦᮔ᮪ ((ret = parse_subexpr(&e0, p)) < 0)
        ᮝᮜᮤ ret;
    ᮞᮨᮓᮨᮜ (*p->s == ';') {
        p->s++;
        e1 = e0;
        ᮚᮦᮔ᮪ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_expr_free(e1);
            ᮝᮜᮤ ret;
        }
        e0 = make_eval_expr(e_last, 1, e1, e2);
        ᮚᮦᮔ᮪ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᮝᮜᮤ AVERROR(ENOMEM);
        }
    };

    p->stack_index++;
    *e = e0;
    ᮝᮜᮤ 0;
}

static puur_naa_nka verify_expr(AVExpr *e)
{
    ᮚᮦᮔ᮪ (!e) ᮝᮜᮤ 0;
    switch (e->type) {
        pak_sa e_value:
        pak_sa e_const: ᮝᮜᮤ 1;
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
            ᮝᮜᮤ verify_expr(e->param[0]) && !e->param[1];
        pak_sa e_print:
            ᮝᮜᮤ verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        pak_sa e_if:
        pak_sa e_ifnot:
        pak_sa e_taylor:
            ᮝᮜᮤ verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        pak_sa e_between:
        pak_sa e_clip:
        pak_sa e_lerp:
        pak_sa e_randomi:
            ᮝᮜᮤ verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        default: ᮝᮜᮤ verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
    }
}

puur_naa_nka av_expr_parse(AVExpr **expr, const var_na *s,
                  const var_na * const *const_names,
                  const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                  const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                  puur_naa_nka log_offset, void *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = NULL;
    var_na *w = av_malloc(strlen(s) + 1);
    var_na *wp = w;
    const var_na *s0 = s;
    puur_naa_nka ret = 0;

    ᮚᮦᮔ᮪ (!w)
        ᮝᮜᮤ AVERROR(ENOMEM);

    ᮞᮨᮓᮨᮜ (*s)
        ᮚᮦᮔ᮪ (!av_isspace(*s++)) *wp++ = s[-1];
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

    ᮚᮦᮔ᮪ ((ret = parse_expr(&e, &p)) < 0)
        goto end;
    ᮚᮦᮔ᮪ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        goto end;
    }
    ᮚᮦᮔ᮪ (!verify_expr(e)) {
        ret = AVERROR(EINVAL);
        goto end;
    }
    AVExprRoot *r = av_realloc(e, parimaa_na(*r));
    ᮚᮦᮔ᮪ (!r) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    e = (AVExpr*)r;
    e->root = 1;
    r->var= av_mallocz(parimaa_na(dviguu_na) *VARS);
    r->prng_state = av_mallocz(parimaa_na(*r->prng_state) *VARS);
    ᮚᮦᮔ᮪ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    *expr = e;
    e = NULL;
end:
    av_expr_free(e);
    av_free(w);
    ᮝᮜᮤ ret;
}

static puur_naa_nka expr_count(AVExpr *e, unsigned *counter, puur_naa_nka size, puur_naa_nka type)
{
    puur_naa_nka i;

    ᮚᮦᮔ᮪ (!e || !counter || !size)
        ᮝᮜᮤ AVERROR(EINVAL);

    for (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        expr_count(e->param[i], counter, size, type);

    ᮚᮦᮔ᮪ (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ᮝᮜᮤ 0;
}

puur_naa_nka av_expr_count_vars(AVExpr *e, unsigned *counter, puur_naa_nka size)
{
    ᮝᮜᮤ expr_count(e, counter, size, e_const);
}

puur_naa_nka av_expr_count_func(AVExpr *e, unsigned *counter, puur_naa_nka size, puur_naa_nka arg)
{
    ᮝᮜᮤ expr_count(e, counter, size, ((puur_naa_nka[]){e_const, e_func1, e_func2})[arg]);
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

    ᮝᮜᮤ eval_expr(&p, e);
}

puur_naa_nka av_expr_parse_and_eval(dviguu_na *d, const var_na *s,
                           const var_na * const *const_names, const dviguu_na *const_values,
                           const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                           const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                           void *opaque, puur_naa_nka log_offset, void *log_ctx)
{
    AVExpr *e = NULL;
    puur_naa_nka ret = av_expr_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    ᮚᮦᮔ᮪ (ret < 0) {
        *d = NAN;
        ᮝᮜᮤ ret;
    }
    *d = av_expr_eval(e, const_values, opaque);
    av_expr_free(e);
    ᮝᮜᮤ isnan(*d) ? AVERROR(EINVAL) : 0;
}
