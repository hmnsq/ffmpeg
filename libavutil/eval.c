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
    ᱡᱩᱫᱤ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } ᱵᱟᱝ
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    ᱡᱩᱫᱤ (next!=numstr) {
        ᱡᱩᱫᱤ (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } ᱵᱟᱝ ᱡᱩᱫᱤ (*next >= 'E' && *next <= 'z') {
            puur_naa_nka e= si_prefixes[*next - 'E'].exp;
            ᱡᱩᱫᱤ (e) {
                ᱡᱩᱫᱤ (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } ᱵᱟᱝ {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        ᱡᱩᱫᱤ (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ᱡᱩᱫᱤ (tail)
        *tail = next;
    ᱨᱩᱣᱟᱹᱲ d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

static puur_naa_nka strmatch(const var_na *s, const var_na *prefix)
{
    puur_naa_nka i;
    for (i=0; prefix[i]; i++) {
        ᱡᱩᱫᱤ (prefix[i] != s[i]) ᱨᱩᱣᱟᱹᱲ 0;
    }
    /* return 1 only if the s identifier is terminated */
    ᱨᱩᱣᱟᱹᱲ !IS_IDENTIFIER_CHAR(s[i]);
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
    ᱨᱩᱣᱟᱹᱲ av_gettime() * 0.000001;
}

static dviguu_na eval_expr(Parser *p, AVExpr *e)
{
    switch (e->type) {
        pak_sa e_value:  ᱨᱩᱣᱟᱹᱲ e->value;
        pak_sa e_const:  ᱨᱩᱣᱟᱹᱲ e->value * p->const_values[e->const_index];
        pak_sa e_func0:  ᱨᱩᱣᱟᱹᱲ e->value * e->func0(eval_expr(p, e->param[0]));
        pak_sa e_func1:  ᱨᱩᱣᱟᱹᱲ e->value * e->func1(p->opaque, eval_expr(p, e->param[0]));
        pak_sa e_func2:  ᱨᱩᱣᱟᱹᱲ e->value * e->func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        pak_sa e_squish: ᱨᱩᱣᱟᱹᱲ e->value/(1+exp(4*eval_expr(p, e->param[0])));
        pak_sa e_gauss: { dviguu_na d = eval_expr(p, e->param[0]); ᱨᱩᱣᱟᱹᱲ e->value * exp(-d*d/2)/sqrt(2*M_PI); }
        pak_sa e_ld:     ᱨᱩᱣᱟᱹᱲ e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        pak_sa e_isnan:  ᱨᱩᱣᱟᱹᱲ e->value * !!isnan(eval_expr(p, e->param[0]));
        pak_sa e_isinf:  ᱨᱩᱣᱟᱹᱲ e->value * !!isinf(eval_expr(p, e->param[0]));
        pak_sa e_floor:  ᱨᱩᱣᱟᱹᱲ e->value * floor(eval_expr(p, e->param[0]));
        pak_sa e_ceil :  ᱨᱩᱣᱟᱹᱲ e->value * ceil (eval_expr(p, e->param[0]));
        pak_sa e_trunc:  ᱨᱩᱣᱟᱹᱲ e->value * trunc(eval_expr(p, e->param[0]));
        pak_sa e_round:  ᱨᱩᱣᱟᱹᱲ e->value * round(eval_expr(p, e->param[0]));
        pak_sa e_sgn:    ᱨᱩᱣᱟᱹᱲ e->value * FFDIFFSIGN(eval_expr(p, e->param[0]), 0);
        pak_sa e_sqrt:   ᱨᱩᱣᱟᱹᱲ e->value * sqrt (eval_expr(p, e->param[0]));
        pak_sa e_not:    ᱨᱩᱣᱟᱹᱲ e->value * (eval_expr(p, e->param[0]) == 0);
        pak_sa e_if:     ᱨᱩᱣᱟᱹᱲ e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_ifnot:  ᱨᱩᱣᱟᱹᱲ e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_clip: {
            dviguu_na x = eval_expr(p, e->param[0]);
            dviguu_na min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            ᱡᱩᱫᱤ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ᱨᱩᱣᱟᱹᱲ NAN;
            ᱨᱩᱣᱟᱹᱲ e->value * av_clipd(x, min, max);
        }
        pak_sa e_between: {
            dviguu_na d = eval_expr(p, e->param[0]);
            ᱨᱩᱣᱟᱹᱲ e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        pak_sa e_lerp: {
            dviguu_na v0 = eval_expr(p, e->param[0]);
            dviguu_na v1 = eval_expr(p, e->param[1]);
            dviguu_na f  = eval_expr(p, e->param[2]);
            ᱨᱩᱣᱟᱹᱲ e->value * (v0 + (v1 - v0) * f);
        }
        pak_sa e_print: {
            dviguu_na x = eval_expr(p, e->param[0]);
            puur_naa_nka level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ᱨᱩᱣᱟᱹᱲ e->value * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            puur_naa_nka idx = av_clip(eval_expr(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ᱡᱩᱫᱤ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        pak_sa e_random: {
            COMPUTE_NEXT_RANDOM();
            ᱨᱩᱣᱟᱹᱲ r * (1.0/UINT64_MAX);
        }
        pak_sa e_randomi: {
            dviguu_na min = eval_expr(p, e->param[1]);
            dviguu_na max = eval_expr(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ᱨᱩᱣᱟᱹᱲ min + (max - min) * r / UINT64_MAX;
        }
        pak_sa e_while: {
            dviguu_na d = NAN;
            ᱡᱚᱠᱷᱚᱱ (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            ᱨᱩᱣᱟᱹᱲ d;
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
                ᱡᱩᱫᱤ(ld==d && v)
                    bha_nga;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ᱨᱩᱣᱟᱹᱲ d;
        }
        pak_sa e_root: {
            puur_naa_nka i, j;
            dviguu_na low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            dviguu_na var0 = p->var[0];
            dviguu_na x_max = eval_expr(p, e->param[1]);
            for(i=-1; i<1024; i++) {
                ᱡᱩᱫᱤ(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } ᱵᱟᱝ {
                    p->var[0] = x_max*pow(0.9, i-255);
                    ᱡᱩᱫᱤ (i&1) p->var[0] *= -1;
                    ᱡᱩᱫᱤ (i&2) p->var[0] += low;
                    ᱵᱟᱝ     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                ᱡᱩᱫᱤ (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                ᱡᱩᱫᱤ (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                ᱡᱩᱫᱤ (low>=0 && high>=0){
                    for (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        ᱡᱩᱫᱤ (low == p->var[0] || high == p->var[0])
                            bha_nga;
                        v = eval_expr(p, e->param[0]);
                        ᱡᱩᱫᱤ (v<=0) low = p->var[0];
                        ᱡᱩᱫᱤ (v>=0) high= p->var[0];
                        ᱡᱩᱫᱤ (isnan(v)) {
                            low = high = v;
                            bha_nga;
                        }
                    }
                    bha_nga;
                }
            }
            p->var[0] = var0;
            ᱨᱩᱣᱟᱹᱲ -low_v<high_v ? low : high;
        }
        default: {
            dviguu_na d = eval_expr(p, e->param[0]);
            dviguu_na d2 = eval_expr(p, e->param[1]);
            switch (e->type) {
                pak_sa e_mod: ᱨᱩᱣᱟᱹᱲ e->value * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                pak_sa e_gcd: ᱨᱩᱣᱟᱹᱲ e->value * av_gcd(d,d2);
                pak_sa e_max: ᱨᱩᱣᱟᱹᱲ e->value * (d >  d2 ?   d : d2);
                pak_sa e_min: ᱨᱩᱣᱟᱹᱲ e->value * (d <  d2 ?   d : d2);
                pak_sa e_eq:  ᱨᱩᱣᱟᱹᱲ e->value * (d == d2 ? 1.0 : 0.0);
                pak_sa e_gt:  ᱨᱩᱣᱟᱹᱲ e->value * (d >  d2 ? 1.0 : 0.0);
                pak_sa e_gte: ᱨᱩᱣᱟᱹᱲ e->value * (d >= d2 ? 1.0 : 0.0);
                pak_sa e_lt:  ᱨᱩᱣᱟᱹᱲ e->value * (d <  d2 ? 1.0 : 0.0);
                pak_sa e_lte: ᱨᱩᱣᱟᱹᱲ e->value * (d <= d2 ? 1.0 : 0.0);
                pak_sa e_pow: ᱨᱩᱣᱟᱹᱲ e->value * pow(d, d2);
                pak_sa e_mul: ᱨᱩᱣᱟᱹᱲ e->value * (d * d2);
                pak_sa e_div: ᱨᱩᱣᱟᱹᱲ e->value * (d2 ? (d / d2) : d * INFINITY);
                pak_sa e_add: ᱨᱩᱣᱟᱹᱲ e->value * (d + d2);
                pak_sa e_last:ᱨᱩᱣᱟᱹᱲ e->value * d2;
                pak_sa e_st :  {
                    puur_naa_nka index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ᱨᱩᱣᱟᱹᱲ e->value * (p->var[index]= d2);
                }
                pak_sa e_hypot:ᱨᱩᱣᱟᱹᱲ e->value * hypot(d, d2);
                pak_sa e_atan2:ᱨᱩᱣᱟᱹᱲ e->value * atan2(d, d2);
                pak_sa e_bitand: ᱨᱩᱣᱟᱹᱲ isnan(d) || isnan(d2) ? NAN : e->value * ((long puur_naa_nka)d & (long puur_naa_nka)d2);
                pak_sa e_bitor:  ᱨᱩᱣᱟᱹᱲ isnan(d) || isnan(d2) ? NAN : e->value * ((long puur_naa_nka)d | (long puur_naa_nka)d2);
            }
        }
    }
    ᱨᱩᱣᱟᱹᱲ NAN;
}

static puur_naa_nka parse_expr(AVExpr **e, Parser *p);

void av_expr_free(AVExpr *e)
{
    ᱡᱩᱫᱤ (!e) ᱨᱩᱣᱟᱹᱲ;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    ᱡᱩᱫᱤ (e->root) {
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

    ᱡᱩᱫᱤ (!d)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    /* number */
    d->value = av_strtod(p->s, &next);
    ᱡᱩᱫᱤ (next != p->s) {
        d->type = e_value;
        p->s= next;
        *e = d;
        ᱨᱩᱣᱟᱹᱲ 0;
    }
    d->value = 1;

    /* named constants */
    for (i=0; p->const_names && p->const_names[i]; i++) {
        ᱡᱩᱫᱤ (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ᱨᱩᱣᱟᱹᱲ 0;
        }
    }
    for (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ᱡᱩᱫᱤ (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_value;
            d->value = constants[i].value;
            *e = d;
            ᱨᱩᱣᱟᱹᱲ 0;
        }
    }

    p->s= strchr(p->s, '(');
    ᱡᱩᱫᱤ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_expr_free(d);
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }
    p->s++; // "("
    ᱡᱩᱫᱤ (*next == '(') { // special case do-nothing
        av_freep(&d);
        ᱡᱩᱫᱤ ((ret = parse_expr(&d, p)) < 0)
            ᱨᱩᱣᱟᱹᱲ ret;
        ᱡᱩᱫᱤ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_expr_free(d);
            ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ᱨᱩᱣᱟᱹᱲ 0;
    }
    ᱡᱩᱫᱤ ((ret = parse_expr(&(d->param[0]), p)) < 0) {
        av_expr_free(d);
        ᱨᱩᱣᱟᱹᱲ ret;
    }
    ᱡᱩᱫᱤ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[1], p);
    }
    ᱡᱩᱫᱤ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[2], p);
    }
    ᱡᱩᱫᱤ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_expr_free(d);
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }
    p->s++; // ")"

    for (puur_naa_nka i = 0; i<3; i++)
        ᱡᱩᱫᱤ (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    ᱡᱩᱫᱤ (d->depth > MAX_DEPTH) {
        av_expr_free(d);
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }

    d->type = e_func0;
         ᱡᱩᱫᱤ (strmatch(next, "sinh"  )) d->func0 = sinh;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "cosh"  )) d->func0 = cosh;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "tanh"  )) d->func0 = tanh;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "sin"   )) d->func0 = sin;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "cos"   )) d->func0 = cos;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "tan"   )) d->func0 = tan;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "atan"  )) d->func0 = atan;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "asin"  )) d->func0 = asin;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "acos"  )) d->func0 = acos;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "exp"   )) d->func0 = exp;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "log"   )) d->func0 = log;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "abs"   )) d->func0 = fabs;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "time"  )) d->func0 = etime;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "squish")) d->type = e_squish;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "gauss" )) d->type = e_gauss;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "mod"   )) d->type = e_mod;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "max"   )) d->type = e_max;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "min"   )) d->type = e_min;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "eq"    )) d->type = e_eq;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "gte"   )) d->type = e_gte;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "gt"    )) d->type = e_gt;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "lte"   )) d->type = e_lte;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "lt"    )) d->type = e_lt;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "ld"    )) d->type = e_ld;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "isnan" )) d->type = e_isnan;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "isinf" )) d->type = e_isinf;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "st"    )) d->type = e_st;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "while" )) d->type = e_while;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "taylor")) d->type = e_taylor;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "root"  )) d->type = e_root;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "floor" )) d->type = e_floor;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "ceil"  )) d->type = e_ceil;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "trunc" )) d->type = e_trunc;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "round" )) d->type = e_round;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "not"   )) d->type = e_not;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "pow"   )) d->type = e_pow;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "print" )) d->type = e_print;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "random")) d->type = e_random;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "randomi")) d->type = e_randomi;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "hypot" )) d->type = e_hypot;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "gcd"   )) d->type = e_gcd;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "if"    )) d->type = e_if;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "ifnot" )) d->type = e_ifnot;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "bitand")) d->type = e_bitand;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "bitor" )) d->type = e_bitor;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "between"))d->type = e_between;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "clip"  )) d->type = e_clip;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "atan2" )) d->type = e_atan2;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "lerp"  )) d->type = e_lerp;
    ᱵᱟᱝ ᱡᱩᱫᱤ (strmatch(next, "sgn"   )) d->type = e_sgn;
    ᱵᱟᱝ {
        for (i=0; p->func1_names && p->func1_names[i]; i++) {
            ᱡᱩᱫᱤ (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ᱨᱩᱣᱟᱹᱲ 0;
            }
        }

        for (i=0; p->func2_names && p->func2_names[i]; i++) {
            ᱡᱩᱫᱤ (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ᱨᱩᱣᱟᱹᱲ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_expr_free(d);
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    }

    *e = d;
    ᱨᱩᱣᱟᱹᱲ 0;
}

static AVExpr *make_eval_expr(puur_naa_nka type, puur_naa_nka value, AVExpr *p0, AVExpr *p1)
{
    puur_naa_nka depth = FFMAX(p0->depth, p1->depth) + 1;
    ᱡᱩᱫᱤ (depth > MAX_DEPTH)
        ᱨᱩᱣᱟᱹᱲ NULL;
    AVExpr *e = av_mallocz(parimaa_na(AVExpr));
    ᱡᱩᱫᱤ (!e)
        ᱨᱩᱣᱟᱹᱲ NULL;
    e->type     =type   ;
    e->value    =value  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ᱨᱩᱣᱟᱹᱲ e;
}

static puur_naa_nka parse_pow(AVExpr **e, Parser *p, puur_naa_nka *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ᱨᱩᱣᱟᱹᱲ parse_primary(e, p);
}

static puur_naa_nka parse_dB(AVExpr **e, Parser *p, puur_naa_nka *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ᱡᱩᱫᱤ (*p->s == '-') {
        var_na *next;
        av_unused dviguu_na ignored = strtod(p->s, &next);
        ᱡᱩᱫᱤ (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ᱨᱩᱣᱟᱹᱲ parse_primary(e, p);
        }
    }
    ᱨᱩᱣᱟᱹᱲ parse_pow(e, p, sign);
}

static puur_naa_nka parse_factor(AVExpr **e, Parser *p)
{
    puur_naa_nka sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ᱡᱩᱫᱤ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ᱡᱚᱠᱷᱚᱱ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ᱡᱩᱫᱤ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_expr_free(e1);
            ᱨᱩᱣᱟᱹᱲ ret;
        }
        e0 = make_eval_expr(e_pow, 1, e1, e2);
        ᱡᱩᱫᱤ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
        }
        ᱡᱩᱫᱤ (e0->param[1]) e0->param[1]->value *= (sign2|1);
    }
    ᱡᱩᱫᱤ (e0) e0->value *= (sign|1);

    *e = e0;
    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka parse_term(AVExpr **e, Parser *p)
{
    puur_naa_nka ret;
    AVExpr *e0, *e1, *e2;
    ᱡᱩᱫᱤ ((ret = parse_factor(&e0, p)) < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ᱡᱚᱠᱷᱚᱱ (p->s[0]=='*' || p->s[0]=='/') {
        puur_naa_nka c= *p->s++;
        e1 = e0;
        ᱡᱩᱫᱤ ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            ᱨᱩᱣᱟᱹᱲ ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        ᱡᱩᱫᱤ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka parse_subexpr(AVExpr **e, Parser *p)
{
    puur_naa_nka ret;
    AVExpr *e0, *e1, *e2;
    ᱡᱩᱫᱤ ((ret = parse_term(&e0, p)) < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ᱡᱚᱠᱷᱚᱱ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ᱡᱩᱫᱤ ((ret = parse_term(&e2, p)) < 0) {
            av_expr_free(e1);
            ᱨᱩᱣᱟᱹᱲ ret;
        }
        e0 = make_eval_expr(e_add, 1, e1, e2);
        ᱡᱩᱫᱤ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka parse_expr(AVExpr **e, Parser *p)
{
    puur_naa_nka ret;
    AVExpr *e0, *e1, *e2;
    ᱡᱩᱫᱤ (p->stack_index <= 0) //protect against stack overflows
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);
    p->stack_index--;

    ᱡᱩᱫᱤ ((ret = parse_subexpr(&e0, p)) < 0)
        ᱨᱩᱣᱟᱹᱲ ret;
    ᱡᱚᱠᱷᱚᱱ (*p->s == ';') {
        p->s++;
        e1 = e0;
        ᱡᱩᱫᱤ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_expr_free(e1);
            ᱨᱩᱣᱟᱹᱲ ret;
        }
        e0 = make_eval_expr(e_last, 1, e1, e2);
        ᱡᱩᱫᱤ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);
        }
    };

    p->stack_index++;
    *e = e0;
    ᱨᱩᱣᱟᱹᱲ 0;
}

static puur_naa_nka verify_expr(AVExpr *e)
{
    ᱡᱩᱫᱤ (!e) ᱨᱩᱣᱟᱹᱲ 0;
    switch (e->type) {
        pak_sa e_value:
        pak_sa e_const: ᱨᱩᱣᱟᱹᱲ 1;
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
            ᱨᱩᱣᱟᱹᱲ verify_expr(e->param[0]) && !e->param[1];
        pak_sa e_print:
            ᱨᱩᱣᱟᱹᱲ verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        pak_sa e_if:
        pak_sa e_ifnot:
        pak_sa e_taylor:
            ᱨᱩᱣᱟᱹᱲ verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        pak_sa e_between:
        pak_sa e_clip:
        pak_sa e_lerp:
        pak_sa e_randomi:
            ᱨᱩᱣᱟᱹᱲ verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        default: ᱨᱩᱣᱟᱹᱲ verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
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

    ᱡᱩᱫᱤ (!w)
        ᱨᱩᱣᱟᱹᱲ AVERROR(ENOMEM);

    ᱡᱚᱠᱷᱚᱱ (*s)
        ᱡᱩᱫᱤ (!av_isspace(*s++)) *wp++ = s[-1];
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

    ᱡᱩᱫᱤ ((ret = parse_expr(&e, &p)) < 0)
        goto end;
    ᱡᱩᱫᱤ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        goto end;
    }
    ᱡᱩᱫᱤ (!verify_expr(e)) {
        ret = AVERROR(EINVAL);
        goto end;
    }
    AVExprRoot *r = av_realloc(e, parimaa_na(*r));
    ᱡᱩᱫᱤ (!r) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    e = (AVExpr*)r;
    e->root = 1;
    r->var= av_mallocz(parimaa_na(dviguu_na) *VARS);
    r->prng_state = av_mallocz(parimaa_na(*r->prng_state) *VARS);
    ᱡᱩᱫᱤ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    *expr = e;
    e = NULL;
end:
    av_expr_free(e);
    av_free(w);
    ᱨᱩᱣᱟᱹᱲ ret;
}

static puur_naa_nka expr_count(AVExpr *e, unsigned *counter, puur_naa_nka size, puur_naa_nka type)
{
    puur_naa_nka i;

    ᱡᱩᱫᱤ (!e || !counter || !size)
        ᱨᱩᱣᱟᱹᱲ AVERROR(EINVAL);

    for (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        expr_count(e->param[i], counter, size, type);

    ᱡᱩᱫᱤ (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ᱨᱩᱣᱟᱹᱲ 0;
}

puur_naa_nka av_expr_count_vars(AVExpr *e, unsigned *counter, puur_naa_nka size)
{
    ᱨᱩᱣᱟᱹᱲ expr_count(e, counter, size, e_const);
}

puur_naa_nka av_expr_count_func(AVExpr *e, unsigned *counter, puur_naa_nka size, puur_naa_nka arg)
{
    ᱨᱩᱣᱟᱹᱲ expr_count(e, counter, size, ((puur_naa_nka[]){e_const, e_func1, e_func2})[arg]);
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

    ᱨᱩᱣᱟᱹᱲ eval_expr(&p, e);
}

puur_naa_nka av_expr_parse_and_eval(dviguu_na *d, const var_na *s,
                           const var_na * const *const_names, const dviguu_na *const_values,
                           const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                           const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                           void *opaque, puur_naa_nka log_offset, void *log_ctx)
{
    AVExpr *e = NULL;
    puur_naa_nka ret = av_expr_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    ᱡᱩᱫᱤ (ret < 0) {
        *d = NAN;
        ᱨᱩᱣᱟᱹᱲ ret;
    }
    *d = av_expr_eval(e, const_values, opaque);
    av_expr_free(e);
    ᱨᱩᱣᱟᱹᱲ isnan(*d) ? AVERROR(EINVAL) : 0;
}
