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

#অন্তর্ভাৱ <float.h>
#অন্তর্ভাৱ "attributes.h"
#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "avutil.h"
#অন্তর্ভাৱ "common.h"
#অন্তর্ভাৱ "eval.h"
#অন্তর্ভাৱ "ffmath.h"
#অন্তর্ভাৱ "log.h"
#অন্তর্ভাৱ "mathematics.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "sfc64.h"
#অন্তর্ভাৱ "time.h"
#অন্তর্ভাৱ "avstring.h"
#অন্তর্ভাৱ "reverse.h"

#define MAX_DEPTH 100

প্রকারনির্দেশ সংরচনা Parser {
    ধ্রুৱ AVClass *class;
    পূর্ণাঙ্ক স্তূপ_index;
    ৱর্ণ *s;
    ধ্রুৱ দ্ৱিগুণ *const_মানসমূহ;
    ধ্রুৱ ৱর্ণ * ধ্রুৱ *const_names;          // NULL terminated
    দ্ৱিগুণ (* ধ্রুৱ *funcs1)(শূন্য *, দ্ৱিগুণ a);           // NULL terminated
    ধ্রুৱ ৱর্ণ * ধ্রুৱ *func1_names;          // NULL terminated
    দ্ৱিগুণ (* ধ্রুৱ *funcs2)(শূন্য *, দ্ৱিগুণ a, দ্ৱিগুণ b); // NULL terminated
    ধ্রুৱ ৱর্ণ * ধ্রুৱ *func2_names;          // NULL terminated
    শূন্য *opaque;
    পূর্ণাঙ্ক log_offset;
    শূন্য *log_ctx;
#define VARS 10
    দ্ৱিগুণ *var;
    FFSFC64 *prng_state;
} Parser;

স্থির ধ্রুৱ AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = রিক্ত,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

স্থির ধ্রুৱ সংরচনা {
    দ্ৱিগুণ bin_val;
    দ্ৱিগুণ dec_val;
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

স্থির ধ্রুৱ সংরচনা {
    ধ্রুৱ ৱর্ণ *name;
    দ্ৱিগুণ মান;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

দ্ৱিগুণ av_strtod(ধ্রুৱ ৱর্ণ *numstr, ৱর্ণ **tail)
{
    দ্ৱিগুণ d;
    ৱর্ণ *next;
    যদি(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } অন্যথা
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    যদি (next!=numstr) {
        যদি (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } অন্যথা যদি (*next >= 'E' && *next <= 'z') {
            পূর্ণাঙ্ক e= si_prefixes[*next - 'E'].exp;
            যদি (e) {
                যদি (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } অন্যথা {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        যদি (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    যদি (tail)
        *tail = next;
    ঘূৰাই d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

স্থির পূর্ণাঙ্ক strmatch(ধ্রুৱ ৱর্ণ *s, ধ্রুৱ ৱর্ণ *prefix)
{
    পূর্ণাঙ্ক i;
    বাবে (i=0; prefix[i]; i++) {
        যদি (prefix[i] != s[i]) ঘূৰাই 0;
    }
    /* return 1 only if the s identifier is terminated */
    ঘূৰাই !IS_IDENTIFIER_CHAR(s[i]);
}

গণনা {
    e_মান, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_মূল, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
সংরচনা AVExpr {
    unsigned ৱর্ণ type;
    unsigned ৱর্ণ মূল;
    short depth;
    পূর্ণাঙ্ক const_index;
    দ্ৱিগুণ মান; // is sign in other types
    সঙ্ঘ {
        দ্ৱিগুণ (*func0)(দ্ৱিগুণ);
        দ্ৱিগুণ (*func1)(শূন্য *, দ্ৱিগুণ);
        দ্ৱিগুণ (*func2)(শূন্য *, দ্ৱিগুণ, দ্ৱিগুণ);
    } ;
    সংরচনা AVExpr *param[3];
};

প্রকারনির্দেশ সংরচনা {
    AVExpr avexpr;
    দ্ৱিগুণ *var;
    FFSFC64 *prng_state;
} AVExpr_মূল;

স্থির দ্ৱিগুণ etime(দ্ৱিগুণ v)
{
    ঘূৰাই av_gettime() * 0.000001;
}

স্থির দ্ৱিগুণ eval_ৰাশিমালা(Parser *p, AVExpr *e)
{
    ৱিকল্প (e->type) {
        পক্ষ e_মান:  ঘূৰাই e->মান;
        পক্ষ e_const:  ঘূৰাই e->মান * p->const_মানসমূহ[e->const_index];
        পক্ষ e_func0:  ঘূৰাই e->মান * e->func0(eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_func1:  ঘূৰাই e->মান * e->func1(p->opaque, eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_func2:  ঘূৰাই e->মান * e->func2(p->opaque, eval_ৰাশিমালা(p, e->param[0]), eval_ৰাশিমালা(p, e->param[1]));
        পক্ষ e_squish: ঘূৰাই e->মান/(1+exp(4*eval_ৰাশিমালা(p, e->param[0])));
        পক্ষ e_gauss: { দ্ৱিগুণ d = eval_ৰাশিমালা(p, e->param[0]); ঘূৰাই e->মান * exp(-d*d/2)/sqrt(2*M_PI); }
        পক্ষ e_ld:     ঘূৰাই e->মান * p->var[av_clip(eval_ৰাশিমালা(p, e->param[0]), 0, VARS-1)];
        পক্ষ e_isnan:  ঘূৰাই e->মান * !!isnan(eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_isinf:  ঘূৰাই e->মান * !!isinf(eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_floor:  ঘূৰাই e->মান * floor(eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_ceil :  ঘূৰাই e->মান * ceil (eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_trunc:  ঘূৰাই e->মান * trunc(eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_round:  ঘূৰাই e->মান * round(eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_sgn:    ঘূৰাই e->মান * FFDIFFSIGN(eval_ৰাশিমালা(p, e->param[0]), 0);
        পক্ষ e_sqrt:   ঘূৰাই e->মান * sqrt (eval_ৰাশিমালা(p, e->param[0]));
        পক্ষ e_not:    ঘূৰাই e->মান * (eval_ৰাশিমালা(p, e->param[0]) == 0);
        পক্ষ e_if:     ঘূৰাই e->মান * (eval_ৰাশিমালা(p, e->param[0]) ? eval_ৰাশিমালা(p, e->param[1]) :
                                          e->param[2] ? eval_ৰাশিমালা(p, e->param[2]) : 0);
        পক্ষ e_ifnot:  ঘূৰাই e->মান * (!eval_ৰাশিমালা(p, e->param[0]) ? eval_ৰাশিমালা(p, e->param[1]) :
                                          e->param[2] ? eval_ৰাশিমালা(p, e->param[2]) : 0);
        পক্ষ e_clip: {
            দ্ৱিগুণ x = eval_ৰাশিমালা(p, e->param[0]);
            দ্ৱিগুণ min = eval_ৰাশিমালা(p, e->param[1]), max = eval_ৰাশিমালা(p, e->param[2]);
            যদি (isnan(min) || isnan(max) || isnan(x) || min > max)
                ঘূৰাই NAN;
            ঘূৰাই e->মান * av_clipd(x, min, max);
        }
        পক্ষ e_between: {
            দ্ৱিগুণ d = eval_ৰাশিমালা(p, e->param[0]);
            ঘূৰাই e->মান * (d >= eval_ৰাশিমালা(p, e->param[1]) &&
                               d <= eval_ৰাশিমালা(p, e->param[2]));
        }
        পক্ষ e_lerp: {
            দ্ৱিগুণ v0 = eval_ৰাশিমালা(p, e->param[0]);
            দ্ৱিগুণ v1 = eval_ৰাশিমালা(p, e->param[1]);
            দ্ৱিগুণ f  = eval_ৰাশিমালা(p, e->param[2]);
            ঘূৰাই e->মান * (v0 + (v1 - v0) * f);
        }
        পক্ষ e_print: {
            দ্ৱিগুণ x = eval_ৰাশিমালা(p, e->param[0]);
            পূর্ণাঙ্ক level = e->param[1] ? av_clip(eval_ৰাশিমালা(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ঘূৰাই e->মান * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            পূর্ণাঙ্ক idx = av_clip(eval_ৰাশিমালা(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            যদি (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        পক্ষ e_random: {
            COMPUTE_NEXT_RANDOM();
            ঘূৰাই r * (1.0/UINT64_MAX);
        }
        পক্ষ e_randomi: {
            দ্ৱিগুণ min = eval_ৰাশিমালা(p, e->param[1]);
            দ্ৱিগুণ max = eval_ৰাশিমালা(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ঘূৰাই min + (max - min) * r / UINT64_MAX;
        }
        পক্ষ e_while: {
            দ্ৱিগুণ d = NAN;
            যেতিয়ালৈ (eval_ৰাশিমালা(p, e->param[0]))
                d=eval_ৰাশিমালা(p, e->param[1]);
            ঘূৰাই d;
        }
        পক্ষ e_taylor: {
            দ্ৱিগুণ t = 1, d = 0, v;
            দ্ৱিগুণ x = eval_ৰাশিমালা(p, e->param[1]);
            পূর্ণাঙ্ক id = e->param[2] ? av_clip(eval_ৰাশিমালা(p, e->param[2]), 0, VARS-1) : 0;
            পূর্ণাঙ্ক i;
            দ্ৱিগুণ var0 = p->var[id];
            বাবে(i=0; i<1000; i++) {
                দ্ৱিগুণ ld = d;
                p->var[id] = i;
                v = eval_ৰাশিমালা(p, e->param[0]);
                d += t*v;
                যদি(ld==d && v)
                    ভঙ্গ;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ঘূৰাই d;
        }
        পক্ষ e_মূল: {
            পূর্ণাঙ্ক i, j;
            দ্ৱিগুণ নিচেৰ = -1, উপৰেৰ = -1, v, নিচেৰ_v = -DBL_MAX, উপৰেৰ_v = DBL_MAX;
            দ্ৱিগুণ var0 = p->var[0];
            দ্ৱিগুণ x_max = eval_ৰাশিমালা(p, e->param[1]);
            বাবে(i=-1; i<1024; i++) {
                যদি(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } অন্যথা {
                    p->var[0] = x_max*pow(0.9, i-255);
                    যদি (i&1) p->var[0] *= -1;
                    যদি (i&2) p->var[0] += নিচেৰ;
                    অন্যথা     p->var[0] += উপৰেৰ;
                }
                v = eval_ৰাশিমালা(p, e->param[0]);
                যদি (v<=0 && v>নিচেৰ_v) {
                    নিচেৰ    = p->var[0];
                    নিচেৰ_v  = v;
                }
                যদি (v>=0 && v<উপৰেৰ_v) {
                    উপৰেৰ   = p->var[0];
                    উপৰেৰ_v = v;
                }
                যদি (নিচেৰ>=0 && উপৰেৰ>=0){
                    বাবে (j=0; j<1000; j++) {
                        p->var[0] = (নিচেৰ+উপৰেৰ)*0.5;
                        যদি (নিচেৰ == p->var[0] || উপৰেৰ == p->var[0])
                            ভঙ্গ;
                        v = eval_ৰাশিমালা(p, e->param[0]);
                        যদি (v<=0) নিচেৰ = p->var[0];
                        যদি (v>=0) উপৰেৰ= p->var[0];
                        যদি (isnan(v)) {
                            নিচেৰ = উপৰেৰ = v;
                            ভঙ্গ;
                        }
                    }
                    ভঙ্গ;
                }
            }
            p->var[0] = var0;
            ঘূৰাই -নিচেৰ_v<উপৰেৰ_v ? নিচেৰ : উপৰেৰ;
        }
        স্ৱভাৱ: {
            দ্ৱিগুণ d = eval_ৰাশিমালা(p, e->param[0]);
            দ্ৱিগুণ d2 = eval_ৰাশিমালা(p, e->param[1]);
            ৱিকল্প (e->type) {
                পক্ষ e_mod: ঘূৰাই e->মান * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                পক্ষ e_gcd: ঘূৰাই e->মান * av_gcd(d,d2);
                পক্ষ e_max: ঘূৰাই e->মান * (d >  d2 ?   d : d2);
                পক্ষ e_min: ঘূৰাই e->মান * (d <  d2 ?   d : d2);
                পক্ষ e_eq:  ঘূৰাই e->মান * (d == d2 ? 1.0 : 0.0);
                পক্ষ e_gt:  ঘূৰাই e->মান * (d >  d2 ? 1.0 : 0.0);
                পক্ষ e_gte: ঘূৰাই e->মান * (d >= d2 ? 1.0 : 0.0);
                পক্ষ e_lt:  ঘূৰাই e->মান * (d <  d2 ? 1.0 : 0.0);
                পক্ষ e_lte: ঘূৰাই e->মান * (d <= d2 ? 1.0 : 0.0);
                পক্ষ e_pow: ঘূৰাই e->মান * pow(d, d2);
                পক্ষ e_mul: ঘূৰাই e->মান * (d * d2);
                পক্ষ e_div: ঘূৰাই e->মান * (d2 ? (d / d2) : d * INFINITY);
                পক্ষ e_add: ঘূৰাই e->মান * (d + d2);
                পক্ষ e_last:ঘূৰাই e->মান * d2;
                পক্ষ e_st :  {
                    পূর্ণাঙ্ক index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ঘূৰাই e->মান * (p->var[index]= d2);
                }
                পক্ষ e_hypot:ঘূৰাই e->মান * hypot(d, d2);
                পক্ষ e_atan2:ঘূৰাই e->মান * atan2(d, d2);
                পক্ষ e_bitand: ঘূৰাই isnan(d) || isnan(d2) ? NAN : e->মান * ((long পূর্ণাঙ্ক)d & (long পূর্ণাঙ্ক)d2);
                পক্ষ e_bitor:  ঘূৰাই isnan(d) || isnan(d2) ? NAN : e->মান * ((long পূর্ণাঙ্ক)d | (long পূর্ণাঙ্ক)d2);
            }
        }
    }
    ঘূৰাই NAN;
}

স্থির পূর্ণাঙ্ক parse_ৰাশিমালা(AVExpr **e, Parser *p);

শূন্য av_ৰাশিমালা_free(AVExpr *e)
{
    যদি (!e) ঘূৰাই;
    av_ৰাশিমালা_free(e->param[0]);
    av_ৰাশিমালা_free(e->param[1]);
    av_ৰাশিমালা_free(e->param[2]);
    যদি (e->মূল) {
        AVExpr_মূল *r = (AVExpr_মূল*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

স্থির পূর্ণাঙ্ক parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(পরিমাণ(AVExpr));
    ৱর্ণ *next = p->s, *s0 = p->s;
    পূর্ণাঙ্ক ret, i;

    যদি (!d)
        ঘূৰাই AVERROR(ENOMEM);

    /*সংখ্যা*/
    d->মান = av_strtod(p->s, &next);
    যদি (next != p->s) {
        d->type = e_মান;
        p->s= next;
        *e = d;
        ঘূৰাই 0;
    }
    d->মান = 1;

    /* named constants */
    বাবে (i=0; p->const_names && p->const_names[i]; i++) {
        যদি (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ঘূৰাই 0;
        }
    }
    বাবে (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        যদি (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_মান;
            d->মান = constants[i].মান;
            *e = d;
            ঘূৰাই 0;
        }
    }

    p->s= strchr(p->s, '(');
    যদি (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_ৰাশিমালা_free(d);
        ঘূৰাই AVERROR(EINVAL);
    }
    p->s++; // "("
    যদি (*next == '(') { // special case do-nothing
        av_freep(&d);
        যদি ((ret = parse_ৰাশিমালা(&d, p)) < 0)
            ঘূৰাই ret;
        যদি (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_ৰাশিমালা_free(d);
            ঘূৰাই AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ঘূৰাই 0;
    }
    যদি ((ret = parse_ৰাশিমালা(&(d->param[0]), p)) < 0) {
        av_ৰাশিমালা_free(d);
        ঘূৰাই ret;
    }
    যদি (p->s[0]== ',') {
        p->s++; // ","
        parse_ৰাশিমালা(&d->param[1], p);
    }
    যদি (p->s[0]== ',') {
        p->s++; // ","
        parse_ৰাশিমালা(&d->param[2], p);
    }
    যদি (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_ৰাশিমালা_free(d);
        ঘূৰাই AVERROR(EINVAL);
    }
    p->s++; // ")"

    বাবে (পূর্ণাঙ্ক i = 0; i<3; i++)
        যদি (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    যদি (d->depth > MAX_DEPTH) {
        av_ৰাশিমালা_free(d);
        ঘূৰাই AVERROR(EINVAL);
    }

    d->type = e_func0;
         যদি (strmatch(next, "sinh"  )) d->func0 = sinh;
    অন্যথা যদি (strmatch(next, "cosh"  )) d->func0 = cosh;
    অন্যথা যদি (strmatch(next, "tanh"  )) d->func0 = tanh;
    অন্যথা যদি (strmatch(next, "sin"   )) d->func0 = sin;
    অন্যথা যদি (strmatch(next, "cos"   )) d->func0 = cos;
    অন্যথা যদি (strmatch(next, "tan"   )) d->func0 = tan;
    অন্যথা যদি (strmatch(next, "atan"  )) d->func0 = atan;
    অন্যথা যদি (strmatch(next, "asin"  )) d->func0 = asin;
    অন্যথা যদি (strmatch(next, "acos"  )) d->func0 = acos;
    অন্যথা যদি (strmatch(next, "exp"   )) d->func0 = exp;
    অন্যথা যদি (strmatch(next, "log"   )) d->func0 = log;
    অন্যথা যদি (strmatch(next, "abs"   )) d->func0 = fabs;
    অন্যথা যদি (strmatch(next, "time"  )) d->func0 = etime;
    অন্যথা যদি (strmatch(next, "squish")) d->type = e_squish;
    অন্যথা যদি (strmatch(next, "gauss" )) d->type = e_gauss;
    অন্যথা যদি (strmatch(next, "mod"   )) d->type = e_mod;
    অন্যথা যদি (strmatch(next, "max"   )) d->type = e_max;
    অন্যথা যদি (strmatch(next, "min"   )) d->type = e_min;
    অন্যথা যদি (strmatch(next, "eq"    )) d->type = e_eq;
    অন্যথা যদি (strmatch(next, "gte"   )) d->type = e_gte;
    অন্যথা যদি (strmatch(next, "gt"    )) d->type = e_gt;
    অন্যথা যদি (strmatch(next, "lte"   )) d->type = e_lte;
    অন্যথা যদি (strmatch(next, "lt"    )) d->type = e_lt;
    অন্যথা যদি (strmatch(next, "ld"    )) d->type = e_ld;
    অন্যথা যদি (strmatch(next, "isnan" )) d->type = e_isnan;
    অন্যথা যদি (strmatch(next, "isinf" )) d->type = e_isinf;
    অন্যথা যদি (strmatch(next, "st"    )) d->type = e_st;
    অন্যথা যদি (strmatch(next, "while" )) d->type = e_while;
    অন্যথা যদি (strmatch(next, "taylor")) d->type = e_taylor;
    অন্যথা যদি (strmatch(next, "root"  )) d->type = e_মূল;
    অন্যথা যদি (strmatch(next, "floor" )) d->type = e_floor;
    অন্যথা যদি (strmatch(next, "ceil"  )) d->type = e_ceil;
    অন্যথা যদি (strmatch(next, "trunc" )) d->type = e_trunc;
    অন্যথা যদি (strmatch(next, "round" )) d->type = e_round;
    অন্যথা যদি (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    অন্যথা যদি (strmatch(next, "not"   )) d->type = e_not;
    অন্যথা যদি (strmatch(next, "pow"   )) d->type = e_pow;
    অন্যথা যদি (strmatch(next, "print" )) d->type = e_print;
    অন্যথা যদি (strmatch(next, "random")) d->type = e_random;
    অন্যথা যদি (strmatch(next, "randomi")) d->type = e_randomi;
    অন্যথা যদি (strmatch(next, "hypot" )) d->type = e_hypot;
    অন্যথা যদি (strmatch(next, "gcd"   )) d->type = e_gcd;
    অন্যথা যদি (strmatch(next, "if"    )) d->type = e_if;
    অন্যথা যদি (strmatch(next, "ifnot" )) d->type = e_ifnot;
    অন্যথা যদি (strmatch(next, "bitand")) d->type = e_bitand;
    অন্যথা যদি (strmatch(next, "bitor" )) d->type = e_bitor;
    অন্যথা যদি (strmatch(next, "between"))d->type = e_between;
    অন্যথা যদি (strmatch(next, "clip"  )) d->type = e_clip;
    অন্যথা যদি (strmatch(next, "atan2" )) d->type = e_atan2;
    অন্যথা যদি (strmatch(next, "lerp"  )) d->type = e_lerp;
    অন্যথা যদি (strmatch(next, "sgn"   )) d->type = e_sgn;
    অন্যথা {
        বাবে (i=0; p->func1_names && p->func1_names[i]; i++) {
            যদি (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ঘূৰাই 0;
            }
        }

        বাবে (i=0; p->func2_names && p->func2_names[i]; i++) {
            যদি (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ঘূৰাই 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_ৰাশিমালা_free(d);
        ঘূৰাই AVERROR(EINVAL);
    }

    *e = d;
    ঘূৰাই 0;
}

স্থির AVExpr *make_eval_ৰাশিমালা(পূর্ণাঙ্ক type, পূর্ণাঙ্ক মান, AVExpr *p0, AVExpr *p1)
{
    পূর্ণাঙ্ক depth = FFMAX(p0->depth, p1->depth) + 1;
    যদি (depth > MAX_DEPTH)
        ঘূৰাই রিক্ত;
    AVExpr *e = av_mallocz(পরিমাণ(AVExpr));
    যদি (!e)
        ঘূৰাই রিক্ত;
    e->type     =type   ;
    e->মান    =মান  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ঘূৰাই e;
}

স্থির পূর্ণাঙ্ক parse_pow(AVExpr **e, Parser *p, পূর্ণাঙ্ক *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ঘূৰাই parse_primary(e, p);
}

স্থির পূর্ণাঙ্ক parse_dB(AVExpr **e, Parser *p, পূর্ণাঙ্ক *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    যদি (*p->s == '-') {
        ৱর্ণ *next;
        av_unused দ্ৱিগুণ ignored = strtod(p->s, &next);
        যদি (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ঘূৰাই parse_primary(e, p);
        }
    }
    ঘূৰাই parse_pow(e, p, sign);
}

স্থির পূর্ণাঙ্ক parse_factor(AVExpr **e, Parser *p)
{
    পূর্ণাঙ্ক sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    যদি ((ret = parse_dB(&e0, p, &sign)) < 0)
        ঘূৰাই ret;
    যেতিয়ালৈ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        যদি ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_ৰাশিমালা_free(e1);
            ঘূৰাই ret;
        }
        e0 = make_eval_ৰাশিমালা(e_pow, 1, e1, e2);
        যদি (!e0) {
            av_ৰাশিমালা_free(e1);
            av_ৰাশিমালা_free(e2);
            ঘূৰাই AVERROR(ENOMEM);
        }
        যদি (e0->param[1]) e0->param[1]->মান *= (sign2|1);
    }
    যদি (e0) e0->মান *= (sign|1);

    *e = e0;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক parse_term(AVExpr **e, Parser *p)
{
    পূর্ণাঙ্ক ret;
    AVExpr *e0, *e1, *e2;
    যদি ((ret = parse_factor(&e0, p)) < 0)
        ঘূৰাই ret;
    যেতিয়ালৈ (p->s[0]=='*' || p->s[0]=='/') {
        পূর্ণাঙ্ক c= *p->s++;
        e1 = e0;
        যদি ((ret = parse_factor(&e2, p)) < 0) {
            av_ৰাশিমালা_free(e1);
            ঘূৰাই ret;
        }
        e0 = make_eval_ৰাশিমালা(c == '*' ? e_mul : e_div, 1, e1, e2);
        যদি (!e0) {
            av_ৰাশিমালা_free(e1);
            av_ৰাশিমালা_free(e2);
            ঘূৰাই AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক parse_subexpr(AVExpr **e, Parser *p)
{
    পূর্ণাঙ্ক ret;
    AVExpr *e0, *e1, *e2;
    যদি ((ret = parse_term(&e0, p)) < 0)
        ঘূৰাই ret;
    যেতিয়ালৈ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        যদি ((ret = parse_term(&e2, p)) < 0) {
            av_ৰাশিমালা_free(e1);
            ঘূৰাই ret;
        }
        e0 = make_eval_ৰাশিমালা(e_add, 1, e1, e2);
        যদি (!e0) {
            av_ৰাশিমালা_free(e1);
            av_ৰাশিমালা_free(e2);
            ঘূৰাই AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক parse_ৰাশিমালা(AVExpr **e, Parser *p)
{
    পূর্ণাঙ্ক ret;
    AVExpr *e0, *e1, *e2;
    যদি (p->স্তূপ_index <= 0) //protect against stack overflows
        ঘূৰাই AVERROR(EINVAL);
    p->স্তূপ_index--;

    যদি ((ret = parse_subexpr(&e0, p)) < 0)
        ঘূৰাই ret;
    যেতিয়ালৈ (*p->s == ';') {
        p->s++;
        e1 = e0;
        যদি ((ret = parse_subexpr(&e2, p)) < 0) {
            av_ৰাশিমালা_free(e1);
            ঘূৰাই ret;
        }
        e0 = make_eval_ৰাশিমালা(e_last, 1, e1, e2);
        যদি (!e0) {
            av_ৰাশিমালা_free(e1);
            av_ৰাশিমালা_free(e2);
            ঘূৰাই AVERROR(ENOMEM);
        }
    };

    p->স্তূপ_index++;
    *e = e0;
    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক verify_ৰাশিমালা(AVExpr *e)
{
    যদি (!e) ঘূৰাই 0;
    ৱিকল্প (e->type) {
        পক্ষ e_মান:
        পক্ষ e_const: ঘূৰাই 1;
        পক্ষ e_func0:
        পক্ষ e_func1:
        পক্ষ e_squish:
        পক্ষ e_ld:
        পক্ষ e_gauss:
        পক্ষ e_isnan:
        পক্ষ e_isinf:
        পক্ষ e_floor:
        পক্ষ e_ceil:
        পক্ষ e_trunc:
        পক্ষ e_round:
        পক্ষ e_sqrt:
        পক্ষ e_not:
        পক্ষ e_random:
        পক্ষ e_sgn:
            ঘূৰাই verify_ৰাশিমালা(e->param[0]) && !e->param[1];
        পক্ষ e_print:
            ঘূৰাই verify_ৰাশিমালা(e->param[0])
                   && (!e->param[1] || verify_ৰাশিমালা(e->param[1]));
        পক্ষ e_if:
        পক্ষ e_ifnot:
        পক্ষ e_taylor:
            ঘূৰাই verify_ৰাশিমালা(e->param[0]) && verify_ৰাশিমালা(e->param[1])
                   && (!e->param[2] || verify_ৰাশিমালা(e->param[2]));
        পক্ষ e_between:
        পক্ষ e_clip:
        পক্ষ e_lerp:
        পক্ষ e_randomi:
            ঘূৰাই verify_ৰাশিমালা(e->param[0]) &&
                   verify_ৰাশিমালা(e->param[1]) &&
                   verify_ৰাশিমালা(e->param[2]);
        স্ৱভাৱ: ঘূৰাই verify_ৰাশিমালা(e->param[0]) && verify_ৰাশিমালা(e->param[1]) && !e->param[2];
    }
}

পূর্ণাঙ্ক av_ৰাশিমালা_parse(AVExpr **ৰাশিমালা, ধ্রুৱ ৱর্ণ *s,
                  ধ্রুৱ ৱর্ণ * ধ্রুৱ *const_names,
                  ধ্রুৱ ৱর্ণ * ধ্রুৱ *func1_names, দ্ৱিগুণ (* ধ্রুৱ *funcs1)(শূন্য *, দ্ৱিগুণ),
                  ধ্রুৱ ৱর্ণ * ধ্রুৱ *func2_names, দ্ৱিগুণ (* ধ্রুৱ *funcs2)(শূন্য *, দ্ৱিগুণ, দ্ৱিগুণ),
                  পূর্ণাঙ্ক log_offset, শূন্য *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = রিক্ত;
    ৱর্ণ *w = av_malloc(strlen(s) + 1);
    ৱর্ণ *wp = w;
    ধ্রুৱ ৱর্ণ *s0 = s;
    পূর্ণাঙ্ক ret = 0;

    যদি (!w)
        ঘূৰাই AVERROR(ENOMEM);

    যেতিয়ালৈ (*s)
        যদি (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.স্তূপ_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    যদি ((ret = parse_ৰাশিমালা(&e, &p)) < 0)
        গচ্ছ end;
    যদি (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        গচ্ছ end;
    }
    যদি (!verify_ৰাশিমালা(e)) {
        ret = AVERROR(EINVAL);
        গচ্ছ end;
    }
    AVExpr_মূল *r = av_realloc(e, পরিমাণ(*r));
    যদি (!r) {
        ret = AVERROR(ENOMEM);
        গচ্ছ end;
    }
    e = (AVExpr*)r;
    e->মূল = 1;
    r->var= av_mallocz(পরিমাণ(দ্ৱিগুণ) *VARS);
    r->prng_state = av_mallocz(পরিমাণ(*r->prng_state) *VARS);
    যদি (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        গচ্ছ end;
    }
    *ৰাশিমালা = e;
    e = রিক্ত;
end:
    av_ৰাশিমালা_free(e);
    av_free(w);
    ঘূৰাই ret;
}

স্থির পূর্ণাঙ্ক ৰাশিমালা_গুনতি(AVExpr *e, unsigned *counter, পূর্ণাঙ্ক size, পূর্ণাঙ্ক type)
{
    পূর্ণাঙ্ক i;

    যদি (!e || !counter || !size)
        ঘূৰাই AVERROR(EINVAL);

    বাবে (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        ৰাশিমালা_গুনতি(e->param[i], counter, size, type);

    যদি (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_ৰাশিমালা_গুনতি_vars(AVExpr *e, unsigned *counter, পূর্ণাঙ্ক size)
{
    ঘূৰাই ৰাশিমালা_গুনতি(e, counter, size, e_const);
}

পূর্ণাঙ্ক av_ৰাশিমালা_গুনতি_func(AVExpr *e, unsigned *counter, পূর্ণাঙ্ক size, পূর্ণাঙ্ক arg)
{
    ঘূৰাই ৰাশিমালা_গুনতি(e, counter, size, ((পূর্ণাঙ্ক[]){e_const, e_func1, e_func2})[arg]);
}

দ্ৱিগুণ av_ৰাশিমালা_eval(AVExpr *e, ধ্রুৱ দ্ৱিগুণ *const_মানসমূহ, শূন্য *opaque)
{
    av_assert1(e->মূল);
    AVExpr_মূল *r = (AVExpr_মূল *)e;
    Parser p = {
        .class        = &eval_class,
        .const_মানসমূহ = const_মানসমূহ,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    ঘূৰাই eval_ৰাশিমালা(&p, e);
}

পূর্ণাঙ্ক av_ৰাশিমালা_parse_and_eval(দ্ৱিগুণ *d, ধ্রুৱ ৱর্ণ *s,
                           ধ্রুৱ ৱর্ণ * ধ্রুৱ *const_names, ধ্রুৱ দ্ৱিগুণ *const_মানসমূহ,
                           ধ্রুৱ ৱর্ণ * ধ্রুৱ *func1_names, দ্ৱিগুণ (* ধ্রুৱ *funcs1)(শূন্য *, দ্ৱিগুণ),
                           ধ্রুৱ ৱর্ণ * ধ্রুৱ *func2_names, দ্ৱিগুণ (* ধ্রুৱ *funcs2)(শূন্য *, দ্ৱিগুণ, দ্ৱিগুণ),
                           শূন্য *opaque, পূর্ণাঙ্ক log_offset, শূন্য *log_ctx)
{
    AVExpr *e = রিক্ত;
    পূর্ণাঙ্ক ret = av_ৰাশিমালা_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    যদি (ret < 0) {
        *d = NAN;
        ঘূৰাই ret;
    }
    *d = av_ৰাশিমালা_eval(e, const_মানসমূহ, opaque);
    av_ৰাশিমালা_free(e);
    ঘূৰাই isnan(*d) ? AVERROR(EINVAL) : 0;
}
