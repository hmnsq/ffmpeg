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

typedef struct Parser {
    const AVClass *class;
    цео stack_index;
    char *s;
    const double *const_values;
    const char * const *const_names;          // NULL terminated
    double (* const *funcs1)(void *, double a);           // NULL terminated
    const char * const *func1_names;          // NULL terminated
    double (* const *funcs2)(void *, double a, double b); // NULL terminated
    const char * const *func2_names;          // NULL terminated
    void *opaque;
    цео log_offset;
    void *log_ctx;
#define VARS 10
    double *var;
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

static const struct {
    double bin_val;
    double dec_val;
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

static const struct {
    const char *name;
    double value;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

double av_strtod(const char *numstr, char **tail)
{
    double d;
    char *next;
    ако(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } инако
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    ако (next!=numstr) {
        ако (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } инако ако (*next >= 'E' && *next <= 'z') {
            цео e= si_prefixes[*next - 'E'].exp;
            ако (e) {
                ако (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } инако {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        ако (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ако (tail)
        *tail = next;
    врати d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

static цео strmatch(const char *s, const char *prefix)
{
    цео i;
    за (i=0; prefix[i]; i++) {
        ако (prefix[i] != s[i]) врати 0;
    }
    /* return 1 only if the s identifier is terminated */
    врати !IS_IDENTIFIER_CHAR(s[i]);
}

enum {
    e_value, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_root, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
struct AVExpr {
    unsigned char type;
    unsigned char root;
    short depth;
    цео const_index;
    double value; // is sign in other types
    union {
        double (*func0)(double);
        double (*func1)(void *, double);
        double (*func2)(void *, double, double);
    } ;
    struct AVExpr *param[3];
};

typedef struct {
    AVExpr avexpr;
    double *var;
    FFSFC64 *prng_state;
} AVExprRoot;

static double etime(double v)
{
    врати av_gettime() * 0.000001;
}

static double eval_expr(Parser *p, AVExpr *e)
{
    switch (e->type) {
        case e_value:  врати e->value;
        case e_const:  врати e->value * p->const_values[e->const_index];
        case e_func0:  врати e->value * e->func0(eval_expr(p, e->param[0]));
        case e_func1:  врати e->value * e->func1(p->opaque, eval_expr(p, e->param[0]));
        case e_func2:  врати e->value * e->func2(p->opaque, eval_expr(p, e->param[0]), eval_expr(p, e->param[1]));
        case e_squish: врати e->value/(1+exp(4*eval_expr(p, e->param[0])));
        case e_gauss: { double d = eval_expr(p, e->param[0]); врати e->value * exp(-d*d/2)/sqrt(2*M_PI); }
        case e_ld:     врати e->value * p->var[av_clip(eval_expr(p, e->param[0]), 0, VARS-1)];
        case e_isnan:  врати e->value * !!isnan(eval_expr(p, e->param[0]));
        case e_isinf:  врати e->value * !!isinf(eval_expr(p, e->param[0]));
        case e_floor:  врати e->value * floor(eval_expr(p, e->param[0]));
        case e_ceil :  врати e->value * ceil (eval_expr(p, e->param[0]));
        case e_trunc:  врати e->value * trunc(eval_expr(p, e->param[0]));
        case e_round:  врати e->value * round(eval_expr(p, e->param[0]));
        case e_sgn:    врати e->value * FFDIFFSIGN(eval_expr(p, e->param[0]), 0);
        case e_sqrt:   врати e->value * sqrt (eval_expr(p, e->param[0]));
        case e_not:    врати e->value * (eval_expr(p, e->param[0]) == 0);
        case e_if:     врати e->value * (eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        case e_ifnot:  врати e->value * (!eval_expr(p, e->param[0]) ? eval_expr(p, e->param[1]) :
                                          e->param[2] ? eval_expr(p, e->param[2]) : 0);
        case e_clip: {
            double x = eval_expr(p, e->param[0]);
            double min = eval_expr(p, e->param[1]), max = eval_expr(p, e->param[2]);
            ако (isnan(min) || isnan(max) || isnan(x) || min > max)
                врати NAN;
            врати e->value * av_clipd(x, min, max);
        }
        case e_between: {
            double d = eval_expr(p, e->param[0]);
            врати e->value * (d >= eval_expr(p, e->param[1]) &&
                               d <= eval_expr(p, e->param[2]));
        }
        case e_lerp: {
            double v0 = eval_expr(p, e->param[0]);
            double v1 = eval_expr(p, e->param[1]);
            double f  = eval_expr(p, e->param[2]);
            врати e->value * (v0 + (v1 - v0) * f);
        }
        case e_print: {
            double x = eval_expr(p, e->param[0]);
            цео level = e->param[1] ? av_clip(eval_expr(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            врати e->value * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            цео idx = av_clip(eval_expr(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ако (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        case e_random: {
            COMPUTE_NEXT_RANDOM();
            врати r * (1.0/UINT64_MAX);
        }
        case e_randomi: {
            double min = eval_expr(p, e->param[1]);
            double max = eval_expr(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            врати min + (max - min) * r / UINT64_MAX;
        }
        case e_while: {
            double d = NAN;
            док (eval_expr(p, e->param[0]))
                d=eval_expr(p, e->param[1]);
            врати d;
        }
        case e_taylor: {
            double t = 1, d = 0, v;
            double x = eval_expr(p, e->param[1]);
            цео id = e->param[2] ? av_clip(eval_expr(p, e->param[2]), 0, VARS-1) : 0;
            цео i;
            double var0 = p->var[id];
            за(i=0; i<1000; i++) {
                double ld = d;
                p->var[id] = i;
                v = eval_expr(p, e->param[0]);
                d += t*v;
                ако(ld==d && v)
                    break;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            врати d;
        }
        case e_root: {
            цео i, j;
            double low = -1, high = -1, v, low_v = -DBL_MAX, high_v = DBL_MAX;
            double var0 = p->var[0];
            double x_max = eval_expr(p, e->param[1]);
            за(i=-1; i<1024; i++) {
                ако(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } инако {
                    p->var[0] = x_max*pow(0.9, i-255);
                    ако (i&1) p->var[0] *= -1;
                    ако (i&2) p->var[0] += low;
                    инако     p->var[0] += high;
                }
                v = eval_expr(p, e->param[0]);
                ако (v<=0 && v>low_v) {
                    low    = p->var[0];
                    low_v  = v;
                }
                ако (v>=0 && v<high_v) {
                    high   = p->var[0];
                    high_v = v;
                }
                ако (low>=0 && high>=0){
                    за (j=0; j<1000; j++) {
                        p->var[0] = (low+high)*0.5;
                        ако (low == p->var[0] || high == p->var[0])
                            break;
                        v = eval_expr(p, e->param[0]);
                        ако (v<=0) low = p->var[0];
                        ако (v>=0) high= p->var[0];
                        ако (isnan(v)) {
                            low = high = v;
                            break;
                        }
                    }
                    break;
                }
            }
            p->var[0] = var0;
            врати -low_v<high_v ? low : high;
        }
        default: {
            double d = eval_expr(p, e->param[0]);
            double d2 = eval_expr(p, e->param[1]);
            switch (e->type) {
                case e_mod: врати e->value * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                case e_gcd: врати e->value * av_gcd(d,d2);
                case e_max: врати e->value * (d >  d2 ?   d : d2);
                case e_min: врати e->value * (d <  d2 ?   d : d2);
                case e_eq:  врати e->value * (d == d2 ? 1.0 : 0.0);
                case e_gt:  врати e->value * (d >  d2 ? 1.0 : 0.0);
                case e_gte: врати e->value * (d >= d2 ? 1.0 : 0.0);
                case e_lt:  врати e->value * (d <  d2 ? 1.0 : 0.0);
                case e_lte: врати e->value * (d <= d2 ? 1.0 : 0.0);
                case e_pow: врати e->value * pow(d, d2);
                case e_mul: врати e->value * (d * d2);
                case e_div: врати e->value * (d2 ? (d / d2) : d * INFINITY);
                case e_add: врати e->value * (d + d2);
                case e_last:врати e->value * d2;
                case e_st :  {
                    цео index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    врати e->value * (p->var[index]= d2);
                }
                case e_hypot:врати e->value * hypot(d, d2);
                case e_atan2:врати e->value * atan2(d, d2);
                case e_bitand: врати isnan(d) || isnan(d2) ? NAN : e->value * ((long цео)d & (long цео)d2);
                case e_bitor:  врати isnan(d) || isnan(d2) ? NAN : e->value * ((long цео)d | (long цео)d2);
            }
        }
    }
    врати NAN;
}

static цео parse_expr(AVExpr **e, Parser *p);

void av_expr_free(AVExpr *e)
{
    ако (!e) врати;
    av_expr_free(e->param[0]);
    av_expr_free(e->param[1]);
    av_expr_free(e->param[2]);
    ако (e->root) {
        AVExprRoot *r = (AVExprRoot*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

static цео parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(sizeof(AVExpr));
    char *next = p->s, *s0 = p->s;
    цео ret, i;

    ако (!d)
        врати AVERROR(ENOMEM);

    /* number */
    d->value = av_strtod(p->s, &next);
    ако (next != p->s) {
        d->type = e_value;
        p->s= next;
        *e = d;
        врати 0;
    }
    d->value = 1;

    /* named constants */
    за (i=0; p->const_names && p->const_names[i]; i++) {
        ако (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            врати 0;
        }
    }
    за (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ако (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_value;
            d->value = constants[i].value;
            *e = d;
            врати 0;
        }
    }

    p->s= strchr(p->s, '(');
    ако (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_expr_free(d);
        врати AVERROR(EINVAL);
    }
    p->s++; // "("
    ако (*next == '(') { // special case do-nothing
        av_freep(&d);
        ако ((ret = parse_expr(&d, p)) < 0)
            врати ret;
        ако (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_expr_free(d);
            врати AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        врати 0;
    }
    ако ((ret = parse_expr(&(d->param[0]), p)) < 0) {
        av_expr_free(d);
        врати ret;
    }
    ако (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[1], p);
    }
    ако (p->s[0]== ',') {
        p->s++; // ","
        parse_expr(&d->param[2], p);
    }
    ако (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_expr_free(d);
        врати AVERROR(EINVAL);
    }
    p->s++; // ")"

    за (цео i = 0; i<3; i++)
        ако (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    ако (d->depth > MAX_DEPTH) {
        av_expr_free(d);
        врати AVERROR(EINVAL);
    }

    d->type = e_func0;
         ако (strmatch(next, "sinh"  )) d->func0 = sinh;
    инако ако (strmatch(next, "cosh"  )) d->func0 = cosh;
    инако ако (strmatch(next, "tanh"  )) d->func0 = tanh;
    инако ако (strmatch(next, "sin"   )) d->func0 = sin;
    инако ако (strmatch(next, "cos"   )) d->func0 = cos;
    инако ако (strmatch(next, "tan"   )) d->func0 = tan;
    инако ако (strmatch(next, "atan"  )) d->func0 = atan;
    инако ако (strmatch(next, "asin"  )) d->func0 = asin;
    инако ако (strmatch(next, "acos"  )) d->func0 = acos;
    инако ако (strmatch(next, "exp"   )) d->func0 = exp;
    инако ако (strmatch(next, "log"   )) d->func0 = log;
    инако ако (strmatch(next, "abs"   )) d->func0 = fabs;
    инако ако (strmatch(next, "time"  )) d->func0 = etime;
    инако ако (strmatch(next, "squish")) d->type = e_squish;
    инако ако (strmatch(next, "gauss" )) d->type = e_gauss;
    инако ако (strmatch(next, "mod"   )) d->type = e_mod;
    инако ако (strmatch(next, "max"   )) d->type = e_max;
    инако ако (strmatch(next, "min"   )) d->type = e_min;
    инако ако (strmatch(next, "eq"    )) d->type = e_eq;
    инако ако (strmatch(next, "gte"   )) d->type = e_gte;
    инако ако (strmatch(next, "gt"    )) d->type = e_gt;
    инако ако (strmatch(next, "lte"   )) d->type = e_lte;
    инако ако (strmatch(next, "lt"    )) d->type = e_lt;
    инако ако (strmatch(next, "ld"    )) d->type = e_ld;
    инако ако (strmatch(next, "isnan" )) d->type = e_isnan;
    инако ако (strmatch(next, "isinf" )) d->type = e_isinf;
    инако ако (strmatch(next, "st"    )) d->type = e_st;
    инако ако (strmatch(next, "while" )) d->type = e_while;
    инако ако (strmatch(next, "taylor")) d->type = e_taylor;
    инако ако (strmatch(next, "root"  )) d->type = e_root;
    инако ако (strmatch(next, "floor" )) d->type = e_floor;
    инако ако (strmatch(next, "ceil"  )) d->type = e_ceil;
    инако ако (strmatch(next, "trunc" )) d->type = e_trunc;
    инако ако (strmatch(next, "round" )) d->type = e_round;
    инако ако (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    инако ако (strmatch(next, "not"   )) d->type = e_not;
    инако ако (strmatch(next, "pow"   )) d->type = e_pow;
    инако ако (strmatch(next, "print" )) d->type = e_print;
    инако ако (strmatch(next, "random")) d->type = e_random;
    инако ако (strmatch(next, "randomi")) d->type = e_randomi;
    инако ако (strmatch(next, "hypot" )) d->type = e_hypot;
    инако ако (strmatch(next, "gcd"   )) d->type = e_gcd;
    инако ако (strmatch(next, "if"    )) d->type = e_if;
    инако ако (strmatch(next, "ifnot" )) d->type = e_ifnot;
    инако ако (strmatch(next, "bitand")) d->type = e_bitand;
    инако ако (strmatch(next, "bitor" )) d->type = e_bitor;
    инако ако (strmatch(next, "between"))d->type = e_between;
    инако ако (strmatch(next, "clip"  )) d->type = e_clip;
    инако ако (strmatch(next, "atan2" )) d->type = e_atan2;
    инако ако (strmatch(next, "lerp"  )) d->type = e_lerp;
    инако ако (strmatch(next, "sgn"   )) d->type = e_sgn;
    инако {
        за (i=0; p->func1_names && p->func1_names[i]; i++) {
            ако (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                врати 0;
            }
        }

        за (i=0; p->func2_names && p->func2_names[i]; i++) {
            ако (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                врати 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_expr_free(d);
        врати AVERROR(EINVAL);
    }

    *e = d;
    врати 0;
}

static AVExpr *make_eval_expr(цео type, цео value, AVExpr *p0, AVExpr *p1)
{
    цео depth = FFMAX(p0->depth, p1->depth) + 1;
    ако (depth > MAX_DEPTH)
        врати NULL;
    AVExpr *e = av_mallocz(sizeof(AVExpr));
    ако (!e)
        врати NULL;
    e->type     =type   ;
    e->value    =value  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    врати e;
}

static цео parse_pow(AVExpr **e, Parser *p, цео *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    врати parse_primary(e, p);
}

static цео parse_dB(AVExpr **e, Parser *p, цео *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ако (*p->s == '-') {
        char *next;
        av_unused double ignored = strtod(p->s, &next);
        ако (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            врати parse_primary(e, p);
        }
    }
    врати parse_pow(e, p, sign);
}

static цео parse_factor(AVExpr **e, Parser *p)
{
    цео sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ако ((ret = parse_dB(&e0, p, &sign)) < 0)
        врати ret;
    док(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ако ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_expr_free(e1);
            врати ret;
        }
        e0 = make_eval_expr(e_pow, 1, e1, e2);
        ако (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            врати AVERROR(ENOMEM);
        }
        ако (e0->param[1]) e0->param[1]->value *= (sign2|1);
    }
    ако (e0) e0->value *= (sign|1);

    *e = e0;
    врати 0;
}

static цео parse_term(AVExpr **e, Parser *p)
{
    цео ret;
    AVExpr *e0, *e1, *e2;
    ако ((ret = parse_factor(&e0, p)) < 0)
        врати ret;
    док (p->s[0]=='*' || p->s[0]=='/') {
        цео c= *p->s++;
        e1 = e0;
        ако ((ret = parse_factor(&e2, p)) < 0) {
            av_expr_free(e1);
            врати ret;
        }
        e0 = make_eval_expr(c == '*' ? e_mul : e_div, 1, e1, e2);
        ако (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            врати AVERROR(ENOMEM);
        }
    }
    *e = e0;
    врати 0;
}

static цео parse_subexpr(AVExpr **e, Parser *p)
{
    цео ret;
    AVExpr *e0, *e1, *e2;
    ако ((ret = parse_term(&e0, p)) < 0)
        врати ret;
    док (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ако ((ret = parse_term(&e2, p)) < 0) {
            av_expr_free(e1);
            врати ret;
        }
        e0 = make_eval_expr(e_add, 1, e1, e2);
        ако (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            врати AVERROR(ENOMEM);
        }
    };

    *e = e0;
    врати 0;
}

static цео parse_expr(AVExpr **e, Parser *p)
{
    цео ret;
    AVExpr *e0, *e1, *e2;
    ако (p->stack_index <= 0) //protect against stack overflows
        врати AVERROR(EINVAL);
    p->stack_index--;

    ако ((ret = parse_subexpr(&e0, p)) < 0)
        врати ret;
    док (*p->s == ';') {
        p->s++;
        e1 = e0;
        ако ((ret = parse_subexpr(&e2, p)) < 0) {
            av_expr_free(e1);
            врати ret;
        }
        e0 = make_eval_expr(e_last, 1, e1, e2);
        ако (!e0) {
            av_expr_free(e1);
            av_expr_free(e2);
            врати AVERROR(ENOMEM);
        }
    };

    p->stack_index++;
    *e = e0;
    врати 0;
}

static цео verify_expr(AVExpr *e)
{
    ако (!e) врати 0;
    switch (e->type) {
        case e_value:
        case e_const: врати 1;
        case e_func0:
        case e_func1:
        case e_squish:
        case e_ld:
        case e_gauss:
        case e_isnan:
        case e_isinf:
        case e_floor:
        case e_ceil:
        case e_trunc:
        case e_round:
        case e_sqrt:
        case e_not:
        case e_random:
        case e_sgn:
            врати verify_expr(e->param[0]) && !e->param[1];
        case e_print:
            врати verify_expr(e->param[0])
                   && (!e->param[1] || verify_expr(e->param[1]));
        case e_if:
        case e_ifnot:
        case e_taylor:
            врати verify_expr(e->param[0]) && verify_expr(e->param[1])
                   && (!e->param[2] || verify_expr(e->param[2]));
        case e_between:
        case e_clip:
        case e_lerp:
        case e_randomi:
            врати verify_expr(e->param[0]) &&
                   verify_expr(e->param[1]) &&
                   verify_expr(e->param[2]);
        default: врати verify_expr(e->param[0]) && verify_expr(e->param[1]) && !e->param[2];
    }
}

цео av_expr_parse(AVExpr **expr, const char *s,
                  const char * const *const_names,
                  const char * const *func1_names, double (* const *funcs1)(void *, double),
                  const char * const *func2_names, double (* const *funcs2)(void *, double, double),
                  цео log_offset, void *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = NULL;
    char *w = av_malloc(strlen(s) + 1);
    char *wp = w;
    const char *s0 = s;
    цео ret = 0;

    ако (!w)
        врати AVERROR(ENOMEM);

    док (*s)
        ако (!av_isspace(*s++)) *wp++ = s[-1];
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

    ако ((ret = parse_expr(&e, &p)) < 0)
        goto end;
    ако (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        goto end;
    }
    ако (!verify_expr(e)) {
        ret = AVERROR(EINVAL);
        goto end;
    }
    AVExprRoot *r = av_realloc(e, sizeof(*r));
    ако (!r) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    e = (AVExpr*)r;
    e->root = 1;
    r->var= av_mallocz(sizeof(double) *VARS);
    r->prng_state = av_mallocz(sizeof(*r->prng_state) *VARS);
    ако (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    *expr = e;
    e = NULL;
end:
    av_expr_free(e);
    av_free(w);
    врати ret;
}

static цео expr_count(AVExpr *e, unsigned *counter, цео size, цео type)
{
    цео i;

    ако (!e || !counter || !size)
        врати AVERROR(EINVAL);

    за (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        expr_count(e->param[i], counter, size, type);

    ако (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    врати 0;
}

цео av_expr_count_vars(AVExpr *e, unsigned *counter, цео size)
{
    врати expr_count(e, counter, size, e_const);
}

цео av_expr_count_func(AVExpr *e, unsigned *counter, цео size, цео arg)
{
    врати expr_count(e, counter, size, ((цео[]){e_const, e_func1, e_func2})[arg]);
}

double av_expr_eval(AVExpr *e, const double *const_values, void *opaque)
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

    врати eval_expr(&p, e);
}

цео av_expr_parse_and_eval(double *d, const char *s,
                           const char * const *const_names, const double *const_values,
                           const char * const *func1_names, double (* const *funcs1)(void *, double),
                           const char * const *func2_names, double (* const *funcs2)(void *, double, double),
                           void *opaque, цео log_offset, void *log_ctx)
{
    AVExpr *e = NULL;
    цео ret = av_expr_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    ако (ret < 0) {
        *d = NAN;
        врати ret;
    }
    *d = av_expr_eval(e, const_values, opaque);
    av_expr_free(e);
    врати isnan(*d) ? AVERROR(EINVAL) : 0;
}
