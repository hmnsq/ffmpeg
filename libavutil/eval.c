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
    ཧྲིལ stack_index;
    var_na *s;
    const dviguu_na *const_values;
    const var_na * const *const_names;          // NULL terminated
    dviguu_na (* const *funcs1)(void *, dviguu_na a);           // NULL terminated
    const var_na * const *func1_names;          // NULL terminated
    dviguu_na (* const *funcs2)(void *, dviguu_na a, dviguu_na b); // NULL terminated
    const var_na * const *func2_names;          // NULL terminated
    void *opaque;
    ཧྲིལ log_offset;
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
    གལ་ཏེ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } དེ་མིན
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    གལ་ཏེ (next!=numstr) {
        གལ་ཏེ (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } དེ་མིན གལ་ཏེ (*next >= 'E' && *next <= 'z') {
            ཧྲིལ e= si_prefixes[*next - 'E'].exp;
            གལ་ཏེ (e) {
                གལ་ཏེ (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } དེ་མིན {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        གལ་ཏེ (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    གལ་ཏེ (tail)
        *tail = next;
    ཕྱིར d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

static ཧྲིལ strmatch(const var_na *s, const var_na *prefix)
{
    ཧྲིལ i;
    ཆེད་དུ (i=0; prefix[i]; i++) {
        གལ་ཏེ (prefix[i] != s[i]) ཕྱིར 0;
    }
    /* return 1 only if the s identifier is terminated */
    ཕྱིར !IS_IDENTIFIER_CHAR(s[i]);
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
    ཧྲིལ const_index;
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
    ཕྱིར av_gettime() * 0.000001;
}

static dviguu_na eval_expr(Parser *p, AVExpr *e)
{
    switch (e->type) {
        pak_sa e_value:  ཕྱིར e->value;
        pak_sa e_const:  ཕྱིར e->value * p->const_values[e->const_index];
        pak_sa e_func0:  ཕྱིར e->value * e->func0(eval_expr(p, e->param[0]));
        pak_sa e_func1:  ཕྱིར e->value * e->func1(p->opaque, eval_expr(p, e->param[0]));
        pak_sa e_func2:  ཕྱིར e->value * e->func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        pak_sa e_squish: ཕྱིར e->value/(1+exp(4*eval_expr(p, e->param[0])));
        pak_sa e_gauss: { dviguu_na d = eval_expr(p, e->param[0]); ཕྱིར e->value * exp(-d*d/2)/sqrt(2*M_PI); }
        pak_sa e_ld:     ཕྱིར e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        pak_sa e_isnan:  ཕྱིར e->value * !!isnan(eval_expr(p, e->param[0]));
        pak_sa e_isinf:  ཕྱིར e->value * !!isinf(eval_expr(p, e->param[0]));
        pak_sa e_floor:  ཕྱིར e->value * floor(eval_expr(p, e->param[0]));
        pak_sa e_ceil :  ཕྱིར e->value * ceil (eval_expr(p, e->param[0]));
        pak_sa e_trunc:  ཕྱིར e->value * trunc(eval_expr(p, e->param[0]));
        pak_sa e_round:  ཕྱིར e->value * round(eval_expr(p, e->param[0]));
        pak_sa e_sgn:    ཕྱིར e->value * FFDIFFSIGN(eval_expr(p, e->param[0]), 0);
        pak_sa e_sqrt:   ཕྱིར e->value * sqrt (eval_expr(p, e->param[0]));
        pak_sa e_not:    ཕྱིར e->value * (eval_expr(p, e->param[0]) == 0);
        pak_sa e_if:     ཕྱིར e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_ifnot:  ཕྱིར e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        pak_sa e_clip: {
            dviguu_na x = eval_expr(p, e->param[0]);
            dviguu_na min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            གལ་ཏེ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ཕྱིར NAN;
            ཕྱིར e->value * av_clipd(x, min, max);
        }
        pak_sa e_between: {
            dviguu_na d = eval_expr(p, e->param[0]);
            ཕྱིར e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        pak_sa e_lerp: {
            dviguu_na v0 = eval_expr(p, e->param[0]);
            dviguu_na v1 = eval_expr(p, e->param[1]);
            dviguu_na f  = eval_expr(p, e->param[2]);
            ཕྱིར e->value * (v0 + (v1 - v0) * f);
        }
        pak_sa e_print: {
            dviguu_na x = eval_expr(p, e->param[0]);
            ཧྲིལ level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ཕྱིར e->value * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            ཧྲིལ idx = av_clip(eval_expr(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            གལ་ཏེ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        pak_sa e_random: {
            COMPUTE_NEXT_RANDOM();
            ཕྱིར r * (1.0/UINT64_MAX);
        }
        pak_sa e_randomi: {
            dviguu_na min = eval_expr(p, e->param[1]);
            dviguu_na max = eval_expr(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ཕྱིར min + (max - min) * r / UINT64_MAX;
        }
        pak_sa e_while: {
            dviguu_na d = NAN;
            སྐབས (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            ཕྱིར d;
        }
        pak_sa e_taylor: {
            dviguu_na t = 1, d = 0, v;
            dviguu_na x = eval_expr(p, e->param[1]);
            ཧྲིལ id = e->param[2] ? av_clip(eval_expr(p, e->param[2]), 0, VARS-1) : 0;
            ཧྲིལ i;
            dviguu_na var0 = p->var[id];
            ཆེད་དུ(i=0; i<1000; i++) {
                dviguu_na ld = d;
                p->var[id] = i;
                v = eval_expr(p, e->param[0]);
                d += t*v;
                གལ་ཏེ(ld==d && v)
                    bha_nga;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ཕྱིར d;
        }
        pak_sa e_root: {
            ཧྲིལ i, j;
            dviguu_na low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            dviguu_na var0 = p->var[0];
            dviguu_na x_max = eval_expr(p, e->param[1]);
            ཆེད་དུ(i=-1; i<1024; i++) {
                གལ་ཏེ(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } དེ་མིན {
                    p->var[0] = x_max*pow(0.9, i-255);
                    གལ་ཏེ (i&1) p->var[0] *= -1;
                    གལ་ཏེ (i&2) p->var[0] += low;
                    དེ་མིན     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                གལ་ཏེ (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                གལ་ཏེ (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                གལ་ཏེ (low>=0 && high>=0){
                    ཆེད་དུ (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        གལ་ཏེ (low == p->var[0] || high == p->var[0])
                            bha_nga;
                        v = eval_expr(p, e->param[0]);
                        གལ་ཏེ (v<=0) low = p->var[0];
                        གལ་ཏེ (v>=0) high= p->var[0];
                        གལ་ཏེ (isnan(v)) {
                            low = high = v;
                            bha_nga;
                        }
                    }
                    bha_nga;
                }
            }
            p->var[0] = var0;
            ཕྱིར -low_v<high_v ? low : high;
        }
        default: {
            dviguu_na d = eval_expr(p, e->param[0]);
            dviguu_na d2 = eval_expr(p, e->param[1]);
            switch (e->type) {
                pak_sa e_mod: ཕྱིར e->value * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                pak_sa e_gcd: ཕྱིར e->value * av_gcd(d,d2);
                pak_sa e_max: ཕྱིར e->value * (d >  d2 ?   d : d2);
                pak_sa e_min: ཕྱིར e->value * (d <  d2 ?   d : d2);
                pak_sa e_eq:  ཕྱིར e->value * (d == d2 ? 1.0 : 0.0);
                pak_sa e_gt:  ཕྱིར e->value * (d >  d2 ? 1.0 : 0.0);
                pak_sa e_gte: ཕྱིར e->value * (d >= d2 ? 1.0 : 0.0);
                pak_sa e_lt:  ཕྱིར e->value * (d <  d2 ? 1.0 : 0.0);
                pak_sa e_lte: ཕྱིར e->value * (d <= d2 ? 1.0 : 0.0);
                pak_sa e_pow: ཕྱིར e->value * pow(d, d2);
                pak_sa e_mul: ཕྱིར e->value * (d * d2);
                pak_sa e_div: ཕྱིར e->value * (d2 ? (d / d2) : d * INFINITY);
                pak_sa e_add: ཕྱིར e->value * (d + d2);
                pak_sa e_last:ཕྱིར e->value * d2;
                pak_sa e_st :  {
                    ཧྲིལ index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ཕྱིར e->value * (p->var[index]= d2);
                }
                pak_sa e_hypot:ཕྱིར e->value * hypot(d, d2);
                pak_sa e_atan2:ཕྱིར e->value * atan2(d, d2);
                pak_sa e_bitand: ཕྱིར isnan(d) || isnan(d2) ? NAN : e->value * ((long ཧྲིལ)d & (long ཧྲིལ)d2);
                pak_sa e_bitor:  ཕྱིར isnan(d) || isnan(d2) ? NAN : e->value * ((long ཧྲིལ)d | (long ཧྲིལ)d2);
            }
        }
    }
    ཕྱིར NAN;
}

static ཧྲིལ parse_expr(AVExpr **e, Parser *p);

void av_expr_free(AVExpr *e)
{
    གལ་ཏེ (!e) ཕྱིར;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    གལ་ཏེ (e->root) {
        AVExprRoot *r = (AVExprRoot*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

static ཧྲིལ parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(parimaa_na(AVExpr));
    var_na *next = p->s, *s0 = p->s;
    ཧྲིལ ret, i;

    གལ་ཏེ (!d)
        ཕྱིར AVERROR(ENOMEM);

    /* number */
    d->value = av_strtod(p->s, &next);
    གལ་ཏེ (next != p->s) {
        d->type = e_value;
        p->s= next;
        *e = d;
        ཕྱིར 0;
    }
    d->value = 1;

    /* named constants */
    ཆེད་དུ (i=0; p->const_names && p->const_names[i]; i++) {
        གལ་ཏེ (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ཕྱིར 0;
        }
    }
    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        གལ་ཏེ (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_value;
            d->value = constants[i].value;
            *e = d;
            ཕྱིར 0;
        }
    }

    p->s= strchr(p->s, '(');
    གལ་ཏེ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_expr_free(d);
        ཕྱིར AVERROR(EINVAL);
    }
    p->s++; // "("
    གལ་ཏེ (*next == '(') { // special case do-nothing
        av_freep(&d);
        གལ་ཏེ ((ret = parse_expr(&d, p)) < 0)
            ཕྱིར ret;
        གལ་ཏེ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_expr_free(d);
            ཕྱིར AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ཕྱིར 0;
    }
    གལ་ཏེ ((ret = parse_expr(&(d->param[0]), p)) < 0) {
        av_expr_free(d);
        ཕྱིར ret;
    }
    གལ་ཏེ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[1], p);
    }
    གལ་ཏེ (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[2], p);
    }
    གལ་ཏེ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_expr_free(d);
        ཕྱིར AVERROR(EINVAL);
    }
    p->s++; // ")"

    ཆེད་དུ (ཧྲིལ i = 0; i<3; i++)
        གལ་ཏེ (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    གལ་ཏེ (d->depth > MAX_DEPTH) {
        av_expr_free(d);
        ཕྱིར AVERROR(EINVAL);
    }

    d->type = e_func0;
         གལ་ཏེ (strmatch(next, "sinh"  )) d->func0 = sinh;
    དེ་མིན གལ་ཏེ (strmatch(next, "cosh"  )) d->func0 = cosh;
    དེ་མིན གལ་ཏེ (strmatch(next, "tanh"  )) d->func0 = tanh;
    དེ་མིན གལ་ཏེ (strmatch(next, "sin"   )) d->func0 = sin;
    དེ་མིན གལ་ཏེ (strmatch(next, "cos"   )) d->func0 = cos;
    དེ་མིན གལ་ཏེ (strmatch(next, "tan"   )) d->func0 = tan;
    དེ་མིན གལ་ཏེ (strmatch(next, "atan"  )) d->func0 = atan;
    དེ་མིན གལ་ཏེ (strmatch(next, "asin"  )) d->func0 = asin;
    དེ་མིན གལ་ཏེ (strmatch(next, "acos"  )) d->func0 = acos;
    དེ་མིན གལ་ཏེ (strmatch(next, "exp"   )) d->func0 = exp;
    དེ་མིན གལ་ཏེ (strmatch(next, "log"   )) d->func0 = log;
    དེ་མིན གལ་ཏེ (strmatch(next, "abs"   )) d->func0 = fabs;
    དེ་མིན གལ་ཏེ (strmatch(next, "time"  )) d->func0 = etime;
    དེ་མིན གལ་ཏེ (strmatch(next, "squish")) d->type = e_squish;
    དེ་མིན གལ་ཏེ (strmatch(next, "gauss" )) d->type = e_gauss;
    དེ་མིན གལ་ཏེ (strmatch(next, "mod"   )) d->type = e_mod;
    དེ་མིན གལ་ཏེ (strmatch(next, "max"   )) d->type = e_max;
    དེ་མིན གལ་ཏེ (strmatch(next, "min"   )) d->type = e_min;
    དེ་མིན གལ་ཏེ (strmatch(next, "eq"    )) d->type = e_eq;
    དེ་མིན གལ་ཏེ (strmatch(next, "gte"   )) d->type = e_gte;
    དེ་མིན གལ་ཏེ (strmatch(next, "gt"    )) d->type = e_gt;
    དེ་མིན གལ་ཏེ (strmatch(next, "lte"   )) d->type = e_lte;
    དེ་མིན གལ་ཏེ (strmatch(next, "lt"    )) d->type = e_lt;
    དེ་མིན གལ་ཏེ (strmatch(next, "ld"    )) d->type = e_ld;
    དེ་མིན གལ་ཏེ (strmatch(next, "isnan" )) d->type = e_isnan;
    དེ་མིན གལ་ཏེ (strmatch(next, "isinf" )) d->type = e_isinf;
    དེ་མིན གལ་ཏེ (strmatch(next, "st"    )) d->type = e_st;
    དེ་མིན གལ་ཏེ (strmatch(next, "while" )) d->type = e_while;
    དེ་མིན གལ་ཏེ (strmatch(next, "taylor")) d->type = e_taylor;
    དེ་མིན གལ་ཏེ (strmatch(next, "root"  )) d->type = e_root;
    དེ་མིན གལ་ཏེ (strmatch(next, "floor" )) d->type = e_floor;
    དེ་མིན གལ་ཏེ (strmatch(next, "ceil"  )) d->type = e_ceil;
    དེ་མིན གལ་ཏེ (strmatch(next, "trunc" )) d->type = e_trunc;
    དེ་མིན གལ་ཏེ (strmatch(next, "round" )) d->type = e_round;
    དེ་མིན གལ་ཏེ (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    དེ་མིན གལ་ཏེ (strmatch(next, "not"   )) d->type = e_not;
    དེ་མིན གལ་ཏེ (strmatch(next, "pow"   )) d->type = e_pow;
    དེ་མིན གལ་ཏེ (strmatch(next, "print" )) d->type = e_print;
    དེ་མིན གལ་ཏེ (strmatch(next, "random")) d->type = e_random;
    དེ་མིན གལ་ཏེ (strmatch(next, "randomi")) d->type = e_randomi;
    དེ་མིན གལ་ཏེ (strmatch(next, "hypot" )) d->type = e_hypot;
    དེ་མིན གལ་ཏེ (strmatch(next, "gcd"   )) d->type = e_gcd;
    དེ་མིན གལ་ཏེ (strmatch(next, "if"    )) d->type = e_if;
    དེ་མིན གལ་ཏེ (strmatch(next, "ifnot" )) d->type = e_ifnot;
    དེ་མིན གལ་ཏེ (strmatch(next, "bitand")) d->type = e_bitand;
    དེ་མིན གལ་ཏེ (strmatch(next, "bitor" )) d->type = e_bitor;
    དེ་མིན གལ་ཏེ (strmatch(next, "between"))d->type = e_between;
    དེ་མིན གལ་ཏེ (strmatch(next, "clip"  )) d->type = e_clip;
    དེ་མིན གལ་ཏེ (strmatch(next, "atan2" )) d->type = e_atan2;
    དེ་མིན གལ་ཏེ (strmatch(next, "lerp"  )) d->type = e_lerp;
    དེ་མིན གལ་ཏེ (strmatch(next, "sgn"   )) d->type = e_sgn;
    དེ་མིན {
        ཆེད་དུ (i=0; p->func1_names && p->func1_names[i]; i++) {
            གལ་ཏེ (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ཕྱིར 0;
            }
        }

        ཆེད་དུ (i=0; p->func2_names && p->func2_names[i]; i++) {
            གལ་ཏེ (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ཕྱིར 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_expr_free(d);
        ཕྱིར AVERROR(EINVAL);
    }

    *e = d;
    ཕྱིར 0;
}

static AVExpr *make_eval_expr(ཧྲིལ type, ཧྲིལ value, AVExpr *p0, AVExpr *p1)
{
    ཧྲིལ depth = FFMAX(p0->depth, p1->depth) + 1;
    གལ་ཏེ (depth > MAX_DEPTH)
        ཕྱིར NULL;
    AVExpr *e = av_mallocz(parimaa_na(AVExpr));
    གལ་ཏེ (!e)
        ཕྱིར NULL;
    e->type     =type   ;
    e->value    =value  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ཕྱིར e;
}

static ཧྲིལ parse_pow(AVExpr **e, Parser *p, ཧྲིལ *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ཕྱིར parse_primary(e, p);
}

static ཧྲིལ parse_dB(AVExpr **e, Parser *p, ཧྲིལ *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    གལ་ཏེ (*p->s == '-') {
        var_na *next;
        av_unused dviguu_na ignored = strtod(p->s, &next);
        གལ་ཏེ (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ཕྱིར parse_primary(e, p);
        }
    }
    ཕྱིར parse_pow(e, p, sign);
}

static ཧྲིལ parse_factor(AVExpr **e, Parser *p)
{
    ཧྲིལ sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    གལ་ཏེ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ཕྱིར ret;
    སྐབས(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        གལ་ཏེ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_expr_free(e1);
            ཕྱིར ret;
        }
        e0 = make_eval_expr(e_pow, 1, e1, e2);
        གལ་ཏེ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ཕྱིར AVERROR(ENOMEM);
        }
        གལ་ཏེ (e0->param[1]) e0->param[1]->value *= (sign2|1);
    }
    གལ་ཏེ (e0) e0->value *= (sign|1);

    *e = e0;
    ཕྱིར 0;
}

static ཧྲིལ parse_term(AVExpr **e, Parser *p)
{
    ཧྲིལ ret;
    AVExpr *e0, *e1, *e2;
    གལ་ཏེ ((ret = parse_factor(&e0, p)) < 0)
        ཕྱིར ret;
    སྐབས (p->s[0]=='*' || p->s[0]=='/') {
        ཧྲིལ c= *p->s++;
        e1 = e0;
        གལ་ཏེ ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            ཕྱིར ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        གལ་ཏེ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ཕྱིར AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ཕྱིར 0;
}

static ཧྲིལ parse_subexpr(AVExpr **e, Parser *p)
{
    ཧྲིལ ret;
    AVExpr *e0, *e1, *e2;
    གལ་ཏེ ((ret = parse_term(&e0, p)) < 0)
        ཕྱིར ret;
    སྐབས (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        གལ་ཏེ ((ret = parse_term(&e2, p)) < 0) {
            av_expr_free(e1);
            ཕྱིར ret;
        }
        e0 = make_eval_expr(e_add, 1, e1, e2);
        གལ་ཏེ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ཕྱིར AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ཕྱིར 0;
}

static ཧྲིལ parse_expr(AVExpr **e, Parser *p)
{
    ཧྲིལ ret;
    AVExpr *e0, *e1, *e2;
    གལ་ཏེ (p->stack_index <= 0) //protect against stack overflows
        ཕྱིར AVERROR(EINVAL);
    p->stack_index--;

    གལ་ཏེ ((ret = parse_subexpr(&e0, p)) < 0)
        ཕྱིར ret;
    སྐབས (*p->s == ';') {
        p->s++;
        e1 = e0;
        གལ་ཏེ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_expr_free(e1);
            ཕྱིར ret;
        }
        e0 = make_eval_expr(e_last, 1, e1, e2);
        གལ་ཏེ (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            ཕྱིར AVERROR(ENOMEM);
        }
    };

    p->stack_index++;
    *e = e0;
    ཕྱིར 0;
}

static ཧྲིལ verify_expr(AVExpr *e)
{
    གལ་ཏེ (!e) ཕྱིར 0;
    switch (e->type) {
        pak_sa e_value:
        pak_sa e_const: ཕྱིར 1;
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
            ཕྱིར verify_expr(e->param[0]) && !e->param[1];
        pak_sa e_print:
            ཕྱིར verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        pak_sa e_if:
        pak_sa e_ifnot:
        pak_sa e_taylor:
            ཕྱིར verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        pak_sa e_between:
        pak_sa e_clip:
        pak_sa e_lerp:
        pak_sa e_randomi:
            ཕྱིར verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        default: ཕྱིར verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
    }
}

ཧྲིལ av_expr_parse(AVExpr **expr, const var_na *s,
                  const var_na * const *const_names,
                  const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                  const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                  ཧྲིལ log_offset, void *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = NULL;
    var_na *w = av_malloc(strlen(s) + 1);
    var_na *wp = w;
    const var_na *s0 = s;
    ཧྲིལ ret = 0;

    གལ་ཏེ (!w)
        ཕྱིར AVERROR(ENOMEM);

    སྐབས (*s)
        གལ་ཏེ (!av_isspace(*s++)) *wp++ = s[-1];
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

    གལ་ཏེ ((ret = parse_expr(&e, &p)) < 0)
        goto end;
    གལ་ཏེ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        goto end;
    }
    གལ་ཏེ (!verify_expr(e)) {
        ret = AVERROR(EINVAL);
        goto end;
    }
    AVExprRoot *r = av_realloc(e, parimaa_na(*r));
    གལ་ཏེ (!r) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    e = (AVExpr*)r;
    e->root = 1;
    r->var= av_mallocz(parimaa_na(dviguu_na) *VARS);
    r->prng_state = av_mallocz(parimaa_na(*r->prng_state) *VARS);
    གལ་ཏེ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    *expr = e;
    e = NULL;
end:
    av_expr_free(e);
    av_free(w);
    ཕྱིར ret;
}

static ཧྲིལ expr_count(AVExpr *e, unsigned *counter, ཧྲིལ size, ཧྲིལ type)
{
    ཧྲིལ i;

    གལ་ཏེ (!e || !counter || !size)
        ཕྱིར AVERROR(EINVAL);

    ཆེད་དུ (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        expr_count(e->param[i], counter, size, type);

    གལ་ཏེ (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ཕྱིར 0;
}

ཧྲིལ av_expr_count_vars(AVExpr *e, unsigned *counter, ཧྲིལ size)
{
    ཕྱིར expr_count(e, counter, size, e_const);
}

ཧྲིལ av_expr_count_func(AVExpr *e, unsigned *counter, ཧྲིལ size, ཧྲིལ arg)
{
    ཕྱིར expr_count(e, counter, size, ((ཧྲིལ[]){e_const, e_func1, e_func2})[arg]);
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

    ཕྱིར eval_expr(&p, e);
}

ཧྲིལ av_expr_parse_and_eval(dviguu_na *d, const var_na *s,
                           const var_na * const *const_names, const dviguu_na *const_values,
                           const var_na * const *func1_names, dviguu_na (* const *funcs1)(void *, dviguu_na),
                           const var_na * const *func2_names, dviguu_na (* const *funcs2)(void *, dviguu_na, dviguu_na),
                           void *opaque, ཧྲིལ log_offset, void *log_ctx)
{
    AVExpr *e = NULL;
    ཧྲིལ ret = av_expr_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    གལ་ཏེ (ret < 0) {
        *d = NAN;
        ཕྱིར ret;
    }
    *d = av_expr_eval(e, const_values, opaque);
    av_expr_free(e);
    ཕྱིར isnan(*d) ? AVERROR(EINVAL) : 0;
}
