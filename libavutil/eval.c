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

#അന്തര്ഭാവ <float.h>
#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "avutil.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "eval.h"
#അന്തര്ഭാവ "ffmath.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "mathematics.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "sfc64.h"
#അന്തര്ഭാവ "time.h"
#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "reverse.h"

#define MAX_DEPTH 100

തരനിർവചനം ഘടന Parser {
    സ്ഥിരം AVClass *class;
    പൂർണ്ണസംഖ്യ അട്ടി_index;
    അക്ഷരം *s;
    സ്ഥിരം ഇരട്ട *const_മൂല്യങ്ങൾ;
    സ്ഥിരം അക്ഷരം * സ്ഥിരം *const_names;          // NULL terminated
    ഇരട്ട (* സ്ഥിരം *funcs1)(ശൂന്യം *, ഇരട്ട a);           // NULL terminated
    സ്ഥിരം അക്ഷരം * സ്ഥിരം *func1_names;          // NULL terminated
    ഇരട്ട (* സ്ഥിരം *funcs2)(ശൂന്യം *, ഇരട്ട a, ഇരട്ട b); // NULL terminated
    സ്ഥിരം അക്ഷരം * സ്ഥിരം *func2_names;          // NULL terminated
    ശൂന്യം *opaque;
    പൂർണ്ണസംഖ്യ log_offset;
    ശൂന്യം *log_ctx;
#define VARS 10
    ഇരട്ട *var;
    FFSFC64 *prng_state;
} Parser;

സ്ഥിതം സ്ഥിരം AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = ശൂന്യ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

സ്ഥിതം സ്ഥിരം ഘടന {
    ഇരട്ട bin_val;
    ഇരട്ട dec_val;
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

സ്ഥിതം സ്ഥിരം ഘടന {
    സ്ഥിരം അക്ഷരം *name;
    ഇരട്ട മൂല്യം;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

ഇരട്ട av_strtod(സ്ഥിരം അക്ഷരം *numstr, അക്ഷരം **tail)
{
    ഇരട്ട d;
    അക്ഷരം *next;
    എങ്കിൽ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } അല്ലെങ്കിൽ
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    എങ്കിൽ (next!=numstr) {
        എങ്കിൽ (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } അല്ലെങ്കിൽ എങ്കിൽ (*next >= 'E' && *next <= 'z') {
            പൂർണ്ണസംഖ്യ e= si_prefixes[*next - 'E'].exp;
            എങ്കിൽ (e) {
                എങ്കിൽ (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } അല്ലെങ്കിൽ {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        എങ്കിൽ (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    എങ്കിൽ (tail)
        *tail = next;
    തിരികെ d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

സ്ഥിതം പൂർണ്ണസംഖ്യ strmatch(സ്ഥിരം അക്ഷരം *s, സ്ഥിരം അക്ഷരം *prefix)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i=0; prefix[i]; i++) {
        എങ്കിൽ (prefix[i] != s[i]) തിരികെ 0;
    }
    /* return 1 only if the s identifier is terminated */
    തിരികെ !IS_IDENTIFIER_CHAR(s[i]);
}

എണ്ണൽ {
    e_മൂല്യം, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_വേര്, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ഘടന AVExpr {
    unsigned അക്ഷരം type;
    unsigned അക്ഷരം വേര്;
    short depth;
    പൂർണ്ണസംഖ്യ const_index;
    ഇരട്ട മൂല്യം; // is sign in other types
    സംഘം {
        ഇരട്ട (*func0)(ഇരട്ട);
        ഇരട്ട (*func1)(ശൂന്യം *, ഇരട്ട);
        ഇരട്ട (*func2)(ശൂന്യം *, ഇരട്ട, ഇരട്ട);
    } ;
    ഘടന AVExpr *param[3];
};

തരനിർവചനം ഘടന {
    AVExpr avexpr;
    ഇരട്ട *var;
    FFSFC64 *prng_state;
} AVExpr_വേര്;

സ്ഥിതം ഇരട്ട etime(ഇരട്ട v)
{
    തിരികെ av_gettime() * 0.000001;
}

സ്ഥിതം ഇരട്ട eval_വ്യഞ്ജകം(Parser *p, AVExpr *e)
{
    തിരഞ്ഞെടുപ്പ് (e->type) {
        അവസ്ഥ e_മൂല്യം:  തിരികെ e->മൂല്യം;
        അവസ്ഥ e_const:  തിരികെ e->മൂല്യം * p->const_മൂല്യങ്ങൾ[e->const_index];
        അവസ്ഥ e_func0:  തിരികെ e->മൂല്യം * e->func0(eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_func1:  തിരികെ e->മൂല്യം * e->func1(p->opaque, eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_func2:  തിരികെ e->മൂല്യം * e->func2(p->opaque, eval_വ്യഞ്ജകം(p, e->param[0]), eval_വ്യഞ്ജകം(p, e->param[1]));
        അവസ്ഥ e_squish: തിരികെ e->മൂല്യം/(1+exp(4*eval_വ്യഞ്ജകം(p, e->param[0])));
        അവസ്ഥ e_gauss: { ഇരട്ട d = eval_വ്യഞ്ജകം(p, e->param[0]); തിരികെ e->മൂല്യം * exp(-d*d/2)/sqrt(2*M_PI); }
        അവസ്ഥ e_ld:     തിരികെ e->മൂല്യം * p->var[av_clip(eval_വ്യഞ്ജകം(p, e->param[0]), 0, VARS-1)];
        അവസ്ഥ e_isnan:  തിരികെ e->മൂല്യം * !!isnan(eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_isinf:  തിരികെ e->മൂല്യം * !!isinf(eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_floor:  തിരികെ e->മൂല്യം * floor(eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_ceil :  തിരികെ e->മൂല്യം * ceil (eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_trunc:  തിരികെ e->മൂല്യം * trunc(eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_round:  തിരികെ e->മൂല്യം * round(eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_sgn:    തിരികെ e->മൂല്യം * FFDIFFSIGN(eval_വ്യഞ്ജകം(p, e->param[0]), 0);
        അവസ്ഥ e_sqrt:   തിരികെ e->മൂല്യം * sqrt (eval_വ്യഞ്ജകം(p, e->param[0]));
        അവസ്ഥ e_not:    തിരികെ e->മൂല്യം * (eval_വ്യഞ്ജകം(p, e->param[0]) == 0);
        അവസ്ഥ e_if:     തിരികെ e->മൂല്യം * (eval_വ്യഞ്ജകം(p, e->param[0]) ? eval_വ്യഞ്ജകം(p, e->param[1]) :
                                          e->param[2] ? eval_വ്യഞ്ജകം(p, e->param[2]) : 0);
        അവസ്ഥ e_ifnot:  തിരികെ e->മൂല്യം * (!eval_വ്യഞ്ജകം(p, e->param[0]) ? eval_വ്യഞ്ജകം(p, e->param[1]) :
                                          e->param[2] ? eval_വ്യഞ്ജകം(p, e->param[2]) : 0);
        അവസ്ഥ e_clip: {
            ഇരട്ട x = eval_വ്യഞ്ജകം(p, e->param[0]);
            ഇരട്ട min = eval_വ്യഞ്ജകം(p, e->param[1]), max = eval_വ്യഞ്ജകം(p, e->param[2]);
            എങ്കിൽ (isnan(min) || isnan(max) || isnan(x) || min > max)
                തിരികെ NAN;
            തിരികെ e->മൂല്യം * av_clipd(x, min, max);
        }
        അവസ്ഥ e_between: {
            ഇരട്ട d = eval_വ്യഞ്ജകം(p, e->param[0]);
            തിരികെ e->മൂല്യം * (d >= eval_വ്യഞ്ജകം(p, e->param[1]) &&
                               d <= eval_വ്യഞ്ജകം(p, e->param[2]));
        }
        അവസ്ഥ e_lerp: {
            ഇരട്ട v0 = eval_വ്യഞ്ജകം(p, e->param[0]);
            ഇരട്ട v1 = eval_വ്യഞ്ജകം(p, e->param[1]);
            ഇരട്ട f  = eval_വ്യഞ്ജകം(p, e->param[2]);
            തിരികെ e->മൂല്യം * (v0 + (v1 - v0) * f);
        }
        അവസ്ഥ e_print: {
            ഇരട്ട x = eval_വ്യഞ്ജകം(p, e->param[0]);
            പൂർണ്ണസംഖ്യ level = e->param[1] ? av_clip(eval_വ്യഞ്ജകം(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            തിരികെ e->മൂല്യം * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            പൂർണ്ണസംഖ്യ idx = av_clip(eval_വ്യഞ്ജകം(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            എങ്കിൽ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        അവസ്ഥ e_random: {
            COMPUTE_NEXT_RANDOM();
            തിരികെ r * (1.0/UINT64_MAX);
        }
        അവസ്ഥ e_randomi: {
            ഇരട്ട min = eval_വ്യഞ്ജകം(p, e->param[1]);
            ഇരട്ട max = eval_വ്യഞ്ജകം(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            തിരികെ min + (max - min) * r / UINT64_MAX;
        }
        അവസ്ഥ e_while: {
            ഇരട്ട d = NAN;
            ആകുമ്പോൾ (eval_വ്യഞ്ജകം(p, e->param[0]))
                d=eval_വ്യഞ്ജകം(p, e->param[1]);
            തിരികെ d;
        }
        അവസ്ഥ e_taylor: {
            ഇരട്ട t = 1, d = 0, v;
            ഇരട്ട x = eval_വ്യഞ്ജകം(p, e->param[1]);
            പൂർണ്ണസംഖ്യ id = e->param[2] ? av_clip(eval_വ്യഞ്ജകം(p, e->param[2]), 0, VARS-1) : 0;
            പൂർണ്ണസംഖ്യ i;
            ഇരട്ട var0 = p->var[id];
            വേണ്ടി(i=0; i<1000; i++) {
                ഇരട്ട ld = d;
                p->var[id] = i;
                v = eval_വ്യഞ്ജകം(p, e->param[0]);
                d += t*v;
                എങ്കിൽ(ld==d && v)
                    നിർത്തുക;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            തിരികെ d;
        }
        അവസ്ഥ e_വേര്: {
            പൂർണ്ണസംഖ്യ i, j;
            ഇരട്ട താഴെയുള്ള = -1, മുകളിലെ = -1, v, താഴെയുള്ള_v = -DBL_MAX, മുകളിലെ_v = DBL_MAX;
            ഇരട്ട var0 = p->var[0];
            ഇരട്ട x_max = eval_വ്യഞ്ജകം(p, e->param[1]);
            വേണ്ടി(i=-1; i<1024; i++) {
                എങ്കിൽ(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } അല്ലെങ്കിൽ {
                    p->var[0] = x_max*pow(0.9, i-255);
                    എങ്കിൽ (i&1) p->var[0] *= -1;
                    എങ്കിൽ (i&2) p->var[0] += താഴെയുള്ള;
                    അല്ലെങ്കിൽ     p->var[0] += മുകളിലെ;
                }
                v = eval_വ്യഞ്ജകം(p, e->param[0]);
                എങ്കിൽ (v<=0 && v>താഴെയുള്ള_v) {
                    താഴെയുള്ള    = p->var[0];
                    താഴെയുള്ള_v  = v;
                }
                എങ്കിൽ (v>=0 && v<മുകളിലെ_v) {
                    മുകളിലെ   = p->var[0];
                    മുകളിലെ_v = v;
                }
                എങ്കിൽ (താഴെയുള്ള>=0 && മുകളിലെ>=0){
                    വേണ്ടി (j=0; j<1000; j++) {
                        p->var[0] = (താഴെയുള്ള+മുകളിലെ)*0.5;
                        എങ്കിൽ (താഴെയുള്ള == p->var[0] || മുകളിലെ == p->var[0])
                            നിർത്തുക;
                        v = eval_വ്യഞ്ജകം(p, e->param[0]);
                        എങ്കിൽ (v<=0) താഴെയുള്ള = p->var[0];
                        എങ്കിൽ (v>=0) മുകളിലെ= p->var[0];
                        എങ്കിൽ (isnan(v)) {
                            താഴെയുള്ള = മുകളിലെ = v;
                            നിർത്തുക;
                        }
                    }
                    നിർത്തുക;
                }
            }
            p->var[0] = var0;
            തിരികെ -താഴെയുള്ള_v<മുകളിലെ_v ? താഴെയുള്ള : മുകളിലെ;
        }
        സ്ഥിരസ്ഥിതി: {
            ഇരട്ട d = eval_വ്യഞ്ജകം(p, e->param[0]);
            ഇരട്ട d2 = eval_വ്യഞ്ജകം(p, e->param[1]);
            തിരഞ്ഞെടുപ്പ് (e->type) {
                അവസ്ഥ e_mod: തിരികെ e->മൂല്യം * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                അവസ്ഥ e_gcd: തിരികെ e->മൂല്യം * av_gcd(d,d2);
                അവസ്ഥ e_max: തിരികെ e->മൂല്യം * (d >  d2 ?   d : d2);
                അവസ്ഥ e_min: തിരികെ e->മൂല്യം * (d <  d2 ?   d : d2);
                അവസ്ഥ e_eq:  തിരികെ e->മൂല്യം * (d == d2 ? 1.0 : 0.0);
                അവസ്ഥ e_gt:  തിരികെ e->മൂല്യം * (d >  d2 ? 1.0 : 0.0);
                അവസ്ഥ e_gte: തിരികെ e->മൂല്യം * (d >= d2 ? 1.0 : 0.0);
                അവസ്ഥ e_lt:  തിരികെ e->മൂല്യം * (d <  d2 ? 1.0 : 0.0);
                അവസ്ഥ e_lte: തിരികെ e->മൂല്യം * (d <= d2 ? 1.0 : 0.0);
                അവസ്ഥ e_pow: തിരികെ e->മൂല്യം * pow(d, d2);
                അവസ്ഥ e_mul: തിരികെ e->മൂല്യം * (d * d2);
                അവസ്ഥ e_div: തിരികെ e->മൂല്യം * (d2 ? (d / d2) : d * INFINITY);
                അവസ്ഥ e_add: തിരികെ e->മൂല്യം * (d + d2);
                അവസ്ഥ e_last:തിരികെ e->മൂല്യം * d2;
                അവസ്ഥ e_st :  {
                    പൂർണ്ണസംഖ്യ index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    തിരികെ e->മൂല്യം * (p->var[index]= d2);
                }
                അവസ്ഥ e_hypot:തിരികെ e->മൂല്യം * hypot(d, d2);
                അവസ്ഥ e_atan2:തിരികെ e->മൂല്യം * atan2(d, d2);
                അവസ്ഥ e_bitand: തിരികെ isnan(d) || isnan(d2) ? NAN : e->മൂല്യം * ((long പൂർണ്ണസംഖ്യ)d & (long പൂർണ്ണസംഖ്യ)d2);
                അവസ്ഥ e_bitor:  തിരികെ isnan(d) || isnan(d2) ? NAN : e->മൂല്യം * ((long പൂർണ്ണസംഖ്യ)d | (long പൂർണ്ണസംഖ്യ)d2);
            }
        }
    }
    തിരികെ NAN;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_വ്യഞ്ജകം(AVExpr **e, Parser *p);

ശൂന്യം av_വ്യഞ്ജകം_free(AVExpr *e)
{
    എങ്കിൽ (!e) തിരികെ;
    av_വ്യഞ്ജകം_free(e->param[0]);
    av_വ്യഞ്ജകം_free(e->param[1]);
    av_വ്യഞ്ജകം_free(e->param[2]);
    എങ്കിൽ (e->വേര്) {
        AVExpr_വേര് *r = (AVExpr_വേര്*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(വലുപ്പം(AVExpr));
    അക്ഷരം *next = p->s, *s0 = p->s;
    പൂർണ്ണസംഖ്യ ret, i;

    എങ്കിൽ (!d)
        തിരികെ AVERROR(ENOMEM);

    /*സംഖ്യ*/
    d->മൂല്യം = av_strtod(p->s, &next);
    എങ്കിൽ (next != p->s) {
        d->type = e_മൂല്യം;
        p->s= next;
        *e = d;
        തിരികെ 0;
    }
    d->മൂല്യം = 1;

    /* named constants */
    വേണ്ടി (i=0; p->const_names && p->const_names[i]; i++) {
        എങ്കിൽ (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            തിരികെ 0;
        }
    }
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        എങ്കിൽ (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_മൂല്യം;
            d->മൂല്യം = constants[i].മൂല്യം;
            *e = d;
            തിരികെ 0;
        }
    }

    p->s= strchr(p->s, '(');
    എങ്കിൽ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_വ്യഞ്ജകം_free(d);
        തിരികെ AVERROR(EINVAL);
    }
    p->s++; // "("
    എങ്കിൽ (*next == '(') { // special case do-nothing
        av_freep(&d);
        എങ്കിൽ ((ret = parse_വ്യഞ്ജകം(&d, p)) < 0)
            തിരികെ ret;
        എങ്കിൽ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_വ്യഞ്ജകം_free(d);
            തിരികെ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        തിരികെ 0;
    }
    എങ്കിൽ ((ret = parse_വ്യഞ്ജകം(&(d->param[0]), p)) < 0) {
        av_വ്യഞ്ജകം_free(d);
        തിരികെ ret;
    }
    എങ്കിൽ (p->s[0]== ',') {
        p->s++; // ","
        parse_വ്യഞ്ജകം(&d->param[1], p);
    }
    എങ്കിൽ (p->s[0]== ',') {
        p->s++; // ","
        parse_വ്യഞ്ജകം(&d->param[2], p);
    }
    എങ്കിൽ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_വ്യഞ്ജകം_free(d);
        തിരികെ AVERROR(EINVAL);
    }
    p->s++; // ")"

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i<3; i++)
        എങ്കിൽ (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    എങ്കിൽ (d->depth > MAX_DEPTH) {
        av_വ്യഞ്ജകം_free(d);
        തിരികെ AVERROR(EINVAL);
    }

    d->type = e_func0;
         എങ്കിൽ (strmatch(next, "sinh"  )) d->func0 = sinh;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "cosh"  )) d->func0 = cosh;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "tanh"  )) d->func0 = tanh;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "sin"   )) d->func0 = sin;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "cos"   )) d->func0 = cos;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "tan"   )) d->func0 = tan;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "atan"  )) d->func0 = atan;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "asin"  )) d->func0 = asin;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "acos"  )) d->func0 = acos;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "exp"   )) d->func0 = exp;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "log"   )) d->func0 = log;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "abs"   )) d->func0 = fabs;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "time"  )) d->func0 = etime;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "squish")) d->type = e_squish;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "gauss" )) d->type = e_gauss;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "mod"   )) d->type = e_mod;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "max"   )) d->type = e_max;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "min"   )) d->type = e_min;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "eq"    )) d->type = e_eq;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "gte"   )) d->type = e_gte;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "gt"    )) d->type = e_gt;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "lte"   )) d->type = e_lte;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "lt"    )) d->type = e_lt;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "ld"    )) d->type = e_ld;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "isnan" )) d->type = e_isnan;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "isinf" )) d->type = e_isinf;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "st"    )) d->type = e_st;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "while" )) d->type = e_while;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "taylor")) d->type = e_taylor;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "root"  )) d->type = e_വേര്;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "floor" )) d->type = e_floor;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "ceil"  )) d->type = e_ceil;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "trunc" )) d->type = e_trunc;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "round" )) d->type = e_round;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "not"   )) d->type = e_not;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "pow"   )) d->type = e_pow;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "print" )) d->type = e_print;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "random")) d->type = e_random;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "randomi")) d->type = e_randomi;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "hypot" )) d->type = e_hypot;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "gcd"   )) d->type = e_gcd;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "if"    )) d->type = e_if;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "ifnot" )) d->type = e_ifnot;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "bitand")) d->type = e_bitand;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "bitor" )) d->type = e_bitor;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "between"))d->type = e_between;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "clip"  )) d->type = e_clip;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "atan2" )) d->type = e_atan2;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "lerp"  )) d->type = e_lerp;
    അല്ലെങ്കിൽ എങ്കിൽ (strmatch(next, "sgn"   )) d->type = e_sgn;
    അല്ലെങ്കിൽ {
        വേണ്ടി (i=0; p->func1_names && p->func1_names[i]; i++) {
            എങ്കിൽ (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                തിരികെ 0;
            }
        }

        വേണ്ടി (i=0; p->func2_names && p->func2_names[i]; i++) {
            എങ്കിൽ (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                തിരികെ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_വ്യഞ്ജകം_free(d);
        തിരികെ AVERROR(EINVAL);
    }

    *e = d;
    തിരികെ 0;
}

സ്ഥിതം AVExpr *make_eval_വ്യഞ്ജകം(പൂർണ്ണസംഖ്യ type, പൂർണ്ണസംഖ്യ മൂല്യം, AVExpr *p0, AVExpr *p1)
{
    പൂർണ്ണസംഖ്യ depth = FFMAX(p0->depth, p1->depth) + 1;
    എങ്കിൽ (depth > MAX_DEPTH)
        തിരികെ ശൂന്യ;
    AVExpr *e = av_mallocz(വലുപ്പം(AVExpr));
    എങ്കിൽ (!e)
        തിരികെ ശൂന്യ;
    e->type     =type   ;
    e->മൂല്യം    =മൂല്യം  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    തിരികെ e;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_pow(AVExpr **e, Parser *p, പൂർണ്ണസംഖ്യ *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    തിരികെ parse_primary(e, p);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_dB(AVExpr **e, Parser *p, പൂർണ്ണസംഖ്യ *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    എങ്കിൽ (*p->s == '-') {
        അക്ഷരം *next;
        av_unused ഇരട്ട ignored = strtod(p->s, &next);
        എങ്കിൽ (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            തിരികെ parse_primary(e, p);
        }
    }
    തിരികെ parse_pow(e, p, sign);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_factor(AVExpr **e, Parser *p)
{
    പൂർണ്ണസംഖ്യ sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    എങ്കിൽ ((ret = parse_dB(&e0, p, &sign)) < 0)
        തിരികെ ret;
    ആകുമ്പോൾ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        എങ്കിൽ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_വ്യഞ്ജകം_free(e1);
            തിരികെ ret;
        }
        e0 = make_eval_വ്യഞ്ജകം(e_pow, 1, e1, e2);
        എങ്കിൽ (!e0) {
            av_വ്യഞ്ജകം_free(e1);
            av_വ്യഞ്ജകം_free(e2);
            തിരികെ AVERROR(ENOMEM);
        }
        എങ്കിൽ (e0->param[1]) e0->param[1]->മൂല്യം *= (sign2|1);
    }
    എങ്കിൽ (e0) e0->മൂല്യം *= (sign|1);

    *e = e0;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_term(AVExpr **e, Parser *p)
{
    പൂർണ്ണസംഖ്യ ret;
    AVExpr *e0, *e1, *e2;
    എങ്കിൽ ((ret = parse_factor(&e0, p)) < 0)
        തിരികെ ret;
    ആകുമ്പോൾ (p->s[0]=='*' || p->s[0]=='/') {
        പൂർണ്ണസംഖ്യ c= *p->s++;
        e1 = e0;
        എങ്കിൽ ((ret = parse_factor(&e2, p)) < 0) {
            av_വ്യഞ്ജകം_free(e1);
            തിരികെ ret;
        }
        e0 = make_eval_വ്യഞ്ജകം(c == '*' ? e_mul : e_div, 1, e1, e2);
        എങ്കിൽ (!e0) {
            av_വ്യഞ്ജകം_free(e1);
            av_വ്യഞ്ജകം_free(e2);
            തിരികെ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_subexpr(AVExpr **e, Parser *p)
{
    പൂർണ്ണസംഖ്യ ret;
    AVExpr *e0, *e1, *e2;
    എങ്കിൽ ((ret = parse_term(&e0, p)) < 0)
        തിരികെ ret;
    ആകുമ്പോൾ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        എങ്കിൽ ((ret = parse_term(&e2, p)) < 0) {
            av_വ്യഞ്ജകം_free(e1);
            തിരികെ ret;
        }
        e0 = make_eval_വ്യഞ്ജകം(e_add, 1, e1, e2);
        എങ്കിൽ (!e0) {
            av_വ്യഞ്ജകം_free(e1);
            av_വ്യഞ്ജകം_free(e2);
            തിരികെ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ parse_വ്യഞ്ജകം(AVExpr **e, Parser *p)
{
    പൂർണ്ണസംഖ്യ ret;
    AVExpr *e0, *e1, *e2;
    എങ്കിൽ (p->അട്ടി_index <= 0) //protect against stack overflows
        തിരികെ AVERROR(EINVAL);
    p->അട്ടി_index--;

    എങ്കിൽ ((ret = parse_subexpr(&e0, p)) < 0)
        തിരികെ ret;
    ആകുമ്പോൾ (*p->s == ';') {
        p->s++;
        e1 = e0;
        എങ്കിൽ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_വ്യഞ്ജകം_free(e1);
            തിരികെ ret;
        }
        e0 = make_eval_വ്യഞ്ജകം(e_last, 1, e1, e2);
        എങ്കിൽ (!e0) {
            av_വ്യഞ്ജകം_free(e1);
            av_വ്യഞ്ജകം_free(e2);
            തിരികെ AVERROR(ENOMEM);
        }
    };

    p->അട്ടി_index++;
    *e = e0;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ verify_വ്യഞ്ജകം(AVExpr *e)
{
    എങ്കിൽ (!e) തിരികെ 0;
    തിരഞ്ഞെടുപ്പ് (e->type) {
        അവസ്ഥ e_മൂല്യം:
        അവസ്ഥ e_const: തിരികെ 1;
        അവസ്ഥ e_func0:
        അവസ്ഥ e_func1:
        അവസ്ഥ e_squish:
        അവസ്ഥ e_ld:
        അവസ്ഥ e_gauss:
        അവസ്ഥ e_isnan:
        അവസ്ഥ e_isinf:
        അവസ്ഥ e_floor:
        അവസ്ഥ e_ceil:
        അവസ്ഥ e_trunc:
        അവസ്ഥ e_round:
        അവസ്ഥ e_sqrt:
        അവസ്ഥ e_not:
        അവസ്ഥ e_random:
        അവസ്ഥ e_sgn:
            തിരികെ verify_വ്യഞ്ജകം(e->param[0]) && !e->param[1];
        അവസ്ഥ e_print:
            തിരികെ verify_വ്യഞ്ജകം(e->param[0])
                   && (!e->param[1] || verify_വ്യഞ്ജകം(e->param[1]));
        അവസ്ഥ e_if:
        അവസ്ഥ e_ifnot:
        അവസ്ഥ e_taylor:
            തിരികെ verify_വ്യഞ്ജകം(e->param[0]) && verify_വ്യഞ്ജകം(e->param[1])
                   && (!e->param[2] || verify_വ്യഞ്ജകം(e->param[2]));
        അവസ്ഥ e_between:
        അവസ്ഥ e_clip:
        അവസ്ഥ e_lerp:
        അവസ്ഥ e_randomi:
            തിരികെ verify_വ്യഞ്ജകം(e->param[0]) &&
                   verify_വ്യഞ്ജകം(e->param[1]) &&
                   verify_വ്യഞ്ജകം(e->param[2]);
        സ്ഥിരസ്ഥിതി: തിരികെ verify_വ്യഞ്ജകം(e->param[0]) && verify_വ്യഞ്ജകം(e->param[1]) && !e->param[2];
    }
}

പൂർണ്ണസംഖ്യ av_വ്യഞ്ജകം_parse(AVExpr **വ്യഞ്ജകം, സ്ഥിരം അക്ഷരം *s,
                  സ്ഥിരം അക്ഷരം * സ്ഥിരം *const_names,
                  സ്ഥിരം അക്ഷരം * സ്ഥിരം *func1_names, ഇരട്ട (* സ്ഥിരം *funcs1)(ശൂന്യം *, ഇരട്ട),
                  സ്ഥിരം അക്ഷരം * സ്ഥിരം *func2_names, ഇരട്ട (* സ്ഥിരം *funcs2)(ശൂന്യം *, ഇരട്ട, ഇരട്ട),
                  പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ശൂന്യ;
    അക്ഷരം *w = av_malloc(strlen(s) + 1);
    അക്ഷരം *wp = w;
    സ്ഥിരം അക്ഷരം *s0 = s;
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (!w)
        തിരികെ AVERROR(ENOMEM);

    ആകുമ്പോൾ (*s)
        എങ്കിൽ (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.അട്ടി_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    എങ്കിൽ ((ret = parse_വ്യഞ്ജകം(&e, &p)) < 0)
        പോകുക end;
    എങ്കിൽ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        പോകുക end;
    }
    എങ്കിൽ (!verify_വ്യഞ്ജകം(e)) {
        ret = AVERROR(EINVAL);
        പോകുക end;
    }
    AVExpr_വേര് *r = av_realloc(e, വലുപ്പം(*r));
    എങ്കിൽ (!r) {
        ret = AVERROR(ENOMEM);
        പോകുക end;
    }
    e = (AVExpr*)r;
    e->വേര് = 1;
    r->var= av_mallocz(വലുപ്പം(ഇരട്ട) *VARS);
    r->prng_state = av_mallocz(വലുപ്പം(*r->prng_state) *VARS);
    എങ്കിൽ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        പോകുക end;
    }
    *വ്യഞ്ജകം = e;
    e = ശൂന്യ;
end:
    av_വ്യഞ്ജകം_free(e);
    av_free(w);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ വ്യഞ്ജകം_എണ്ണം(AVExpr *e, unsigned *counter, പൂർണ്ണസംഖ്യ size, പൂർണ്ണസംഖ്യ type)
{
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (!e || !counter || !size)
        തിരികെ AVERROR(EINVAL);

    വേണ്ടി (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        വ്യഞ്ജകം_എണ്ണം(e->param[i], counter, size, type);

    എങ്കിൽ (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_വ്യഞ്ജകം_എണ്ണം_vars(AVExpr *e, unsigned *counter, പൂർണ്ണസംഖ്യ size)
{
    തിരികെ വ്യഞ്ജകം_എണ്ണം(e, counter, size, e_const);
}

പൂർണ്ണസംഖ്യ av_വ്യഞ്ജകം_എണ്ണം_func(AVExpr *e, unsigned *counter, പൂർണ്ണസംഖ്യ size, പൂർണ്ണസംഖ്യ arg)
{
    തിരികെ വ്യഞ്ജകം_എണ്ണം(e, counter, size, ((പൂർണ്ണസംഖ്യ[]){e_const, e_func1, e_func2})[arg]);
}

ഇരട്ട av_വ്യഞ്ജകം_eval(AVExpr *e, സ്ഥിരം ഇരട്ട *const_മൂല്യങ്ങൾ, ശൂന്യം *opaque)
{
    av_assert1(e->വേര്);
    AVExpr_വേര് *r = (AVExpr_വേര് *)e;
    Parser p = {
        .class        = &eval_class,
        .const_മൂല്യങ്ങൾ = const_മൂല്യങ്ങൾ,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    തിരികെ eval_വ്യഞ്ജകം(&p, e);
}

പൂർണ്ണസംഖ്യ av_വ്യഞ്ജകം_parse_and_eval(ഇരട്ട *d, സ്ഥിരം അക്ഷരം *s,
                           സ്ഥിരം അക്ഷരം * സ്ഥിരം *const_names, സ്ഥിരം ഇരട്ട *const_മൂല്യങ്ങൾ,
                           സ്ഥിരം അക്ഷരം * സ്ഥിരം *func1_names, ഇരട്ട (* സ്ഥിരം *funcs1)(ശൂന്യം *, ഇരട്ട),
                           സ്ഥിരം അക്ഷരം * സ്ഥിരം *func2_names, ഇരട്ട (* സ്ഥിരം *funcs2)(ശൂന്യം *, ഇരട്ട, ഇരട്ട),
                           ശൂന്യം *opaque, പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    AVExpr *e = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret = av_വ്യഞ്ജകം_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    എങ്കിൽ (ret < 0) {
        *d = NAN;
        തിരികെ ret;
    }
    *d = av_വ്യഞ്ജകം_eval(e, const_മൂല്യങ്ങൾ, opaque);
    av_വ്യഞ്ജകം_free(e);
    തിരികെ isnan(*d) ? AVERROR(EINVAL) : 0;
}
