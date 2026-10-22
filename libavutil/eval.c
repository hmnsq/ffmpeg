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

#ଅନ୍ତର୍ଭାଵ <float.h>
#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "avutil.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "eval.h"
#ଅନ୍ତର୍ଭାଵ "ffmath.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "mathematics.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "sfc64.h"
#ଅନ୍ତର୍ଭାଵ "time.h"
#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "reverse.h"

#define MAX_DEPTH 100

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Parser {
    ଅଚଳ AVClass *class;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଦା_index;
    ଅକ୍ଷର *s;
    ଅଚଳ ଦ୍ୱିଗୁଣ *const_ମୂଲ୍ୟଗୁଡ଼ିକ;
    ଅଚଳ ଅକ୍ଷର * ଅଚଳ *const_names;          // NULL terminated
    ଦ୍ୱିଗୁଣ (* ଅଚଳ *funcs1)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ a);           // NULL terminated
    ଅଚଳ ଅକ୍ଷର * ଅଚଳ *func1_names;          // NULL terminated
    ଦ୍ୱିଗୁଣ (* ଅଚଳ *funcs2)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ a, ଦ୍ୱିଗୁଣ b); // NULL terminated
    ଅଚଳ ଅକ୍ଷର * ଅଚଳ *func2_names;          // NULL terminated
    ଶୂନ୍ୟ *opaque;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset;
    ଶୂନ୍ୟ *log_ctx;
#define VARS 10
    ଦ୍ୱିଗୁଣ *var;
    FFSFC64 *prng_state;
} Parser;

ସ୍ଥିର ଅଚଳ AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = ଖାଲି,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ଦ୍ୱିଗୁଣ bin_val;
    ଦ୍ୱିଗୁଣ dec_val;
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

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର *name;
    ଦ୍ୱିଗୁଣ ମୂଲ୍ୟ;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

ଦ୍ୱିଗୁଣ av_strtod(ଅଚଳ ଅକ୍ଷର *numstr, ଅକ୍ଷର **tail)
{
    ଦ୍ୱିଗୁଣ d;
    ଅକ୍ଷର *next;
    ଯଦି(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } ଅନ୍ୟଥା
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    ଯଦି (next!=numstr) {
        ଯଦି (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } ଅନ୍ୟଥା ଯଦି (*next >= 'E' && *next <= 'z') {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା e= si_prefixes[*next - 'E'].exp;
            ଯଦି (e) {
                ଯଦି (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } ଅନ୍ୟଥା {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        ଯଦି (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ଯଦି (tail)
        *tail = next;
    ଫେରନ୍ତୁ d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା strmatch(ଅଚଳ ଅକ୍ଷର *s, ଅଚଳ ଅକ୍ଷର *prefix)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i=0; prefix[i]; i++) {
        ଯଦି (prefix[i] != s[i]) ଫେରନ୍ତୁ 0;
    }
    /* return 1 only if the s identifier is terminated */
    ଫେରନ୍ତୁ !IS_IDENTIFIER_CHAR(s[i]);
}

ଗଣନା {
    e_ମୂଲ୍ୟ, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_ମୂଳ, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ସଂରଚନା AVExpr {
    unsigned ଅକ୍ଷର type;
    unsigned ଅକ୍ଷର ମୂଳ;
    short depth;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା const_index;
    ଦ୍ୱିଗୁଣ ମୂଲ୍ୟ; // is sign in other types
    ସଂଘ {
        ଦ୍ୱିଗୁଣ (*func0)(ଦ୍ୱିଗୁଣ);
        ଦ୍ୱିଗୁଣ (*func1)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ);
        ଦ୍ୱିଗୁଣ (*func2)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ, ଦ୍ୱିଗୁଣ);
    } ;
    ସଂରଚନା AVExpr *param[3];
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା {
    AVExpr avexpr;
    ଦ୍ୱିଗୁଣ *var;
    FFSFC64 *prng_state;
} AVExpr_ମୂଳ;

ସ୍ଥିର ଦ୍ୱିଗୁଣ etime(ଦ୍ୱିଗୁଣ v)
{
    ଫେରନ୍ତୁ av_gettime() * 0.000001;
}

ସ୍ଥିର ଦ୍ୱିଗୁଣ eval_ପଦସମଷ୍ଟି(Parser *p, AVExpr *e)
{
    ବାଛ (e->type) {
        ସ୍ଥିତି e_ମୂଲ୍ୟ:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ;
        ସ୍ଥିତି e_const:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * p->const_ମୂଲ୍ୟଗୁଡ଼ିକ[e->const_index];
        ସ୍ଥିତି e_func0:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * e->func0(eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_func1:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * e->func1(p->opaque, eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_func2:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * e->func2(p->opaque, eval_ପଦସମଷ୍ଟି(p, e->param[0]), eval_ପଦସମଷ୍ଟି(p, e->param[1]));
        ସ୍ଥିତି e_squish: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ/(1+exp(4*eval_ପଦସମଷ୍ଟି(p, e->param[0])));
        ସ୍ଥିତି e_gauss: { ଦ୍ୱିଗୁଣ d = eval_ପଦସମଷ୍ଟି(p, e->param[0]); ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * exp(-d*d/2)/sqrt(2*M_PI); }
        ସ୍ଥିତି e_ld:     ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * p->var[av_clip(eval_ପଦସମଷ୍ଟି(p, e->param[0]), 0, VARS-1)];
        ସ୍ଥିତି e_isnan:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * !!isnan(eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_isinf:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * !!isinf(eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_floor:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * floor(eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_ceil :  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * ceil (eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_trunc:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * trunc(eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_round:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * round(eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_sgn:    ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * FFDIFFSIGN(eval_ପଦସମଷ୍ଟି(p, e->param[0]), 0);
        ସ୍ଥିତି e_sqrt:   ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * sqrt (eval_ପଦସମଷ୍ଟି(p, e->param[0]));
        ସ୍ଥିତି e_not:    ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (eval_ପଦସମଷ୍ଟି(p, e->param[0]) == 0);
        ସ୍ଥିତି e_if:     ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (eval_ପଦସମଷ୍ଟି(p, e->param[0]) ? eval_ପଦସମଷ୍ଟି(p, e->param[1]) :
                                          e->param[2] ? eval_ପଦସମଷ୍ଟି(p, e->param[2]) : 0);
        ସ୍ଥିତି e_ifnot:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (!eval_ପଦସମଷ୍ଟି(p, e->param[0]) ? eval_ପଦସମଷ୍ଟି(p, e->param[1]) :
                                          e->param[2] ? eval_ପଦସମଷ୍ଟି(p, e->param[2]) : 0);
        ସ୍ଥିତି e_clip: {
            ଦ୍ୱିଗୁଣ x = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
            ଦ୍ୱିଗୁଣ min = eval_ପଦସମଷ୍ଟି(p, e->param[1]), max = eval_ପଦସମଷ୍ଟି(p, e->param[2]);
            ଯଦି (isnan(min) || isnan(max) || isnan(x) || min > max)
                ଫେରନ୍ତୁ NAN;
            ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * av_clipd(x, min, max);
        }
        ସ୍ଥିତି e_between: {
            ଦ୍ୱିଗୁଣ d = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
            ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d >= eval_ପଦସମଷ୍ଟି(p, e->param[1]) &&
                               d <= eval_ପଦସମଷ୍ଟି(p, e->param[2]));
        }
        ସ୍ଥିତି e_lerp: {
            ଦ୍ୱିଗୁଣ v0 = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
            ଦ୍ୱିଗୁଣ v1 = eval_ପଦସମଷ୍ଟି(p, e->param[1]);
            ଦ୍ୱିଗୁଣ f  = eval_ପଦସମଷ୍ଟି(p, e->param[2]);
            ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (v0 + (v1 - v0) * f);
        }
        ସ୍ଥିତି e_print: {
            ଦ୍ୱିଗୁଣ x = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା level = e->param[1] ? av_clip(eval_ପଦସମଷ୍ଟି(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା idx = av_clip(eval_ପଦସମଷ୍ଟି(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ଯଦି (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        ସ୍ଥିତି e_random: {
            COMPUTE_NEXT_RANDOM();
            ଫେରନ୍ତୁ r * (1.0/UINT64_MAX);
        }
        ସ୍ଥିତି e_randomi: {
            ଦ୍ୱିଗୁଣ min = eval_ପଦସମଷ୍ଟି(p, e->param[1]);
            ଦ୍ୱିଗୁଣ max = eval_ପଦସମଷ୍ଟି(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ଫେରନ୍ତୁ min + (max - min) * r / UINT64_MAX;
        }
        ସ୍ଥିତି e_while: {
            ଦ୍ୱିଗୁଣ d = NAN;
            ଯେତେବେଳେ (eval_ପଦସମଷ୍ଟି(p, e->param[0]))
                d=eval_ପଦସମଷ୍ଟି(p, e->param[1]);
            ଫେରନ୍ତୁ d;
        }
        ସ୍ଥିତି e_taylor: {
            ଦ୍ୱିଗୁଣ t = 1, d = 0, v;
            ଦ୍ୱିଗୁଣ x = eval_ପଦସମଷ୍ଟି(p, e->param[1]);
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା id = e->param[2] ? av_clip(eval_ପଦସମଷ୍ଟି(p, e->param[2]), 0, VARS-1) : 0;
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
            ଦ୍ୱିଗୁଣ var0 = p->var[id];
            ପାଇଁ(i=0; i<1000; i++) {
                ଦ୍ୱିଗୁଣ ld = d;
                p->var[id] = i;
                v = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
                d += t*v;
                ଯଦି(ld==d && v)
                    ଭାଙ୍ଗ;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ଫେରନ୍ତୁ d;
        }
        ସ୍ଥିତି e_ମୂଳ: {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;
            ଦ୍ୱିଗୁଣ ତଳ = -1, ଉପର = -1, v, ତଳ_v = -DBL_MAX, ଉପର_v = DBL_MAX;
            ଦ୍ୱିଗୁଣ var0 = p->var[0];
            ଦ୍ୱିଗୁଣ x_max = eval_ପଦସମଷ୍ଟି(p, e->param[1]);
            ପାଇଁ(i=-1; i<1024; i++) {
                ଯଦି(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } ଅନ୍ୟଥା {
                    p->var[0] = x_max*pow(0.9, i-255);
                    ଯଦି (i&1) p->var[0] *= -1;
                    ଯଦି (i&2) p->var[0] += ତଳ;
                    ଅନ୍ୟଥା     p->var[0] += ଉପର;
                }
                v = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
                ଯଦି (v<=0 && v>ତଳ_v) {
                    ତଳ    = p->var[0];
                    ତଳ_v  = v;
                }
                ଯଦି (v>=0 && v<ଉପର_v) {
                    ଉପର   = p->var[0];
                    ଉପର_v = v;
                }
                ଯଦି (ତଳ>=0 && ଉପର>=0){
                    ପାଇଁ (j=0; j<1000; j++) {
                        p->var[0] = (ତଳ+ଉପର)*0.5;
                        ଯଦି (ତଳ == p->var[0] || ଉପର == p->var[0])
                            ଭାଙ୍ଗ;
                        v = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
                        ଯଦି (v<=0) ତଳ = p->var[0];
                        ଯଦି (v>=0) ଉପର= p->var[0];
                        ଯଦି (isnan(v)) {
                            ତଳ = ଉପର = v;
                            ଭାଙ୍ଗ;
                        }
                    }
                    ଭାଙ୍ଗ;
                }
            }
            p->var[0] = var0;
            ଫେରନ୍ତୁ -ତଳ_v<ଉପର_v ? ତଳ : ଉପର;
        }
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ: {
            ଦ୍ୱିଗୁଣ d = eval_ପଦସମଷ୍ଟି(p, e->param[0]);
            ଦ୍ୱିଗୁଣ d2 = eval_ପଦସମଷ୍ଟି(p, e->param[1]);
            ବାଛ (e->type) {
                ସ୍ଥିତି e_mod: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                ସ୍ଥିତି e_gcd: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * av_gcd(d,d2);
                ସ୍ଥିତି e_max: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d >  d2 ?   d : d2);
                ସ୍ଥିତି e_min: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d <  d2 ?   d : d2);
                ସ୍ଥିତି e_eq:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d == d2 ? 1.0 : 0.0);
                ସ୍ଥିତି e_gt:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d >  d2 ? 1.0 : 0.0);
                ସ୍ଥିତି e_gte: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d >= d2 ? 1.0 : 0.0);
                ସ୍ଥିତି e_lt:  ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d <  d2 ? 1.0 : 0.0);
                ସ୍ଥିତି e_lte: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d <= d2 ? 1.0 : 0.0);
                ସ୍ଥିତି e_pow: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * pow(d, d2);
                ସ୍ଥିତି e_mul: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d * d2);
                ସ୍ଥିତି e_div: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d2 ? (d / d2) : d * INFINITY);
                ସ୍ଥିତି e_add: ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (d + d2);
                ସ୍ଥିତି e_last:ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * d2;
                ସ୍ଥିତି e_st :  {
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * (p->var[index]= d2);
                }
                ସ୍ଥିତି e_hypot:ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * hypot(d, d2);
                ସ୍ଥିତି e_atan2:ଫେରନ୍ତୁ e->ମୂଲ୍ୟ * atan2(d, d2);
                ସ୍ଥିତି e_bitand: ଫେରନ୍ତୁ isnan(d) || isnan(d2) ? NAN : e->ମୂଲ୍ୟ * ((long ପୂର୍ଣ୍ଣସଂଖ୍ୟା)d & (long ପୂର୍ଣ୍ଣସଂଖ୍ୟା)d2);
                ସ୍ଥିତି e_bitor:  ଫେରନ୍ତୁ isnan(d) || isnan(d2) ? NAN : e->ମୂଲ୍ୟ * ((long ପୂର୍ଣ୍ଣସଂଖ୍ୟା)d | (long ପୂର୍ଣ୍ଣସଂଖ୍ୟା)d2);
            }
        }
    }
    ଫେରନ୍ତୁ NAN;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_ପଦସମଷ୍ଟି(AVExpr **e, Parser *p);

ଶୂନ୍ୟ av_ପଦସମଷ୍ଟି_free(AVExpr *e)
{
    ଯଦି (!e) ଫେରନ୍ତୁ;
    av_ପଦସମଷ୍ଟି_free(e->param[0]);
    av_ପଦସମଷ୍ଟି_free(e->param[1]);
    av_ପଦସମଷ୍ଟି_free(e->param[2]);
    ଯଦି (e->ମୂଳ) {
        AVExpr_ମୂଳ *r = (AVExpr_ମୂଳ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(ଆକାର(AVExpr));
    ଅକ୍ଷର *next = p->s, *s0 = p->s;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, i;

    ଯଦି (!d)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    /*ସଂଖ୍ୟା*/
    d->ମୂଲ୍ୟ = av_strtod(p->s, &next);
    ଯଦି (next != p->s) {
        d->type = e_ମୂଲ୍ୟ;
        p->s= next;
        *e = d;
        ଫେରନ୍ତୁ 0;
    }
    d->ମୂଲ୍ୟ = 1;

    /* named constants */
    ପାଇଁ (i=0; p->const_names && p->const_names[i]; i++) {
        ଯଦି (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ଫେରନ୍ତୁ 0;
        }
    }
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ଯଦି (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_ମୂଲ୍ୟ;
            d->ମୂଲ୍ୟ = constants[i].ମୂଲ୍ୟ;
            *e = d;
            ଫେରନ୍ତୁ 0;
        }
    }

    p->s= strchr(p->s, '(');
    ଯଦି (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_ପଦସମଷ୍ଟି_free(d);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    p->s++; // "("
    ଯଦି (*next == '(') { // special case do-nothing
        av_freep(&d);
        ଯଦି ((ret = parse_ପଦସମଷ୍ଟି(&d, p)) < 0)
            ଫେରନ୍ତୁ ret;
        ଯଦି (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_ପଦସମଷ୍ଟି_free(d);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ଫେରନ୍ତୁ 0;
    }
    ଯଦି ((ret = parse_ପଦସମଷ୍ଟି(&(d->param[0]), p)) < 0) {
        av_ପଦସମଷ୍ଟି_free(d);
        ଫେରନ୍ତୁ ret;
    }
    ଯଦି (p->s[0]== ',') {
        p->s++; // ","
        parse_ପଦସମଷ୍ଟି(&d->param[1], p);
    }
    ଯଦି (p->s[0]== ',') {
        p->s++; // ","
        parse_ପଦସମଷ୍ଟି(&d->param[2], p);
    }
    ଯଦି (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_ପଦସମଷ୍ଟି_free(d);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    p->s++; // ")"

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i<3; i++)
        ଯଦି (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    ଯଦି (d->depth > MAX_DEPTH) {
        av_ପଦସମଷ୍ଟି_free(d);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    d->type = e_func0;
         ଯଦି (strmatch(next, "sinh"  )) d->func0 = sinh;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "cosh"  )) d->func0 = cosh;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "tanh"  )) d->func0 = tanh;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "sin"   )) d->func0 = sin;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "cos"   )) d->func0 = cos;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "tan"   )) d->func0 = tan;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "atan"  )) d->func0 = atan;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "asin"  )) d->func0 = asin;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "acos"  )) d->func0 = acos;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "exp"   )) d->func0 = exp;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "log"   )) d->func0 = log;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "abs"   )) d->func0 = fabs;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "time"  )) d->func0 = etime;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "squish")) d->type = e_squish;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "gauss" )) d->type = e_gauss;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "mod"   )) d->type = e_mod;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "max"   )) d->type = e_max;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "min"   )) d->type = e_min;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "eq"    )) d->type = e_eq;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "gte"   )) d->type = e_gte;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "gt"    )) d->type = e_gt;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "lte"   )) d->type = e_lte;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "lt"    )) d->type = e_lt;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "ld"    )) d->type = e_ld;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "isnan" )) d->type = e_isnan;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "isinf" )) d->type = e_isinf;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "st"    )) d->type = e_st;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "while" )) d->type = e_while;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "taylor")) d->type = e_taylor;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "root"  )) d->type = e_ମୂଳ;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "floor" )) d->type = e_floor;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "ceil"  )) d->type = e_ceil;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "trunc" )) d->type = e_trunc;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "round" )) d->type = e_round;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "not"   )) d->type = e_not;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "pow"   )) d->type = e_pow;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "print" )) d->type = e_print;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "random")) d->type = e_random;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "randomi")) d->type = e_randomi;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "hypot" )) d->type = e_hypot;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "gcd"   )) d->type = e_gcd;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "if"    )) d->type = e_if;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "ifnot" )) d->type = e_ifnot;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "bitand")) d->type = e_bitand;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "bitor" )) d->type = e_bitor;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "between"))d->type = e_between;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "clip"  )) d->type = e_clip;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "atan2" )) d->type = e_atan2;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "lerp"  )) d->type = e_lerp;
    ଅନ୍ୟଥା ଯଦି (strmatch(next, "sgn"   )) d->type = e_sgn;
    ଅନ୍ୟଥା {
        ପାଇଁ (i=0; p->func1_names && p->func1_names[i]; i++) {
            ଯଦି (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ଫେରନ୍ତୁ 0;
            }
        }

        ପାଇଁ (i=0; p->func2_names && p->func2_names[i]; i++) {
            ଯଦି (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ଫେରନ୍ତୁ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_ପଦସମଷ୍ଟି_free(d);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    *e = d;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର AVExpr *make_eval_ପଦସମଷ୍ଟି(ପୂର୍ଣ୍ଣସଂଖ୍ୟା type, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ, AVExpr *p0, AVExpr *p1)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth = FFMAX(p0->depth, p1->depth) + 1;
    ଯଦି (depth > MAX_DEPTH)
        ଫେରନ୍ତୁ ଖାଲି;
    AVExpr *e = av_mallocz(ଆକାର(AVExpr));
    ଯଦି (!e)
        ଫେରନ୍ତୁ ଖାଲି;
    e->type     =type   ;
    e->ମୂଲ୍ୟ    =ମୂଲ୍ୟ  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ଫେରନ୍ତୁ e;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_pow(AVExpr **e, Parser *p, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ଫେରନ୍ତୁ parse_primary(e, p);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_dB(AVExpr **e, Parser *p, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ଯଦି (*p->s == '-') {
        ଅକ୍ଷର *next;
        av_unused ଦ୍ୱିଗୁଣ ignored = strtod(p->s, &next);
        ଯଦି (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ଫେରନ୍ତୁ parse_primary(e, p);
        }
    }
    ଫେରନ୍ତୁ parse_pow(e, p, sign);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_factor(AVExpr **e, Parser *p)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ଯଦି ((ret = parse_dB(&e0, p, &sign)) < 0)
        ଫେରନ୍ତୁ ret;
    ଯେତେବେଳେ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ଯଦି ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            ଫେରନ୍ତୁ ret;
        }
        e0 = make_eval_ପଦସମଷ୍ଟି(e_pow, 1, e1, e2);
        ଯଦି (!e0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            av_ପଦସମଷ୍ଟି_free(e2);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
        ଯଦି (e0->param[1]) e0->param[1]->ମୂଲ୍ୟ *= (sign2|1);
    }
    ଯଦି (e0) e0->ମୂଲ୍ୟ *= (sign|1);

    *e = e0;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_term(AVExpr **e, Parser *p)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    AVExpr *e0, *e1, *e2;
    ଯଦି ((ret = parse_factor(&e0, p)) < 0)
        ଫେରନ୍ତୁ ret;
    ଯେତେବେଳେ (p->s[0]=='*' || p->s[0]=='/') {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା c= *p->s++;
        e1 = e0;
        ଯଦି ((ret = parse_factor(&e2, p)) < 0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            ଫେରନ୍ତୁ ret;
        }
        e0 = make_eval_ପଦସମଷ୍ଟି(c == '*' ? e_mul : e_div, 1, e1, e2);
        ଯଦି (!e0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            av_ପଦସମଷ୍ଟି_free(e2);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_subexpr(AVExpr **e, Parser *p)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    AVExpr *e0, *e1, *e2;
    ଯଦି ((ret = parse_term(&e0, p)) < 0)
        ଫେରନ୍ତୁ ret;
    ଯେତେବେଳେ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ଯଦି ((ret = parse_term(&e2, p)) < 0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            ଫେରନ୍ତୁ ret;
        }
        e0 = make_eval_ପଦସମଷ୍ଟି(e_add, 1, e1, e2);
        ଯଦି (!e0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            av_ପଦସମଷ୍ଟି_free(e2);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା parse_ପଦସମଷ୍ଟି(AVExpr **e, Parser *p)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    AVExpr *e0, *e1, *e2;
    ଯଦି (p->ଗଦା_index <= 0) //protect against stack overflows
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    p->ଗଦା_index--;

    ଯଦି ((ret = parse_subexpr(&e0, p)) < 0)
        ଫେରନ୍ତୁ ret;
    ଯେତେବେଳେ (*p->s == ';') {
        p->s++;
        e1 = e0;
        ଯଦି ((ret = parse_subexpr(&e2, p)) < 0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            ଫେରନ୍ତୁ ret;
        }
        e0 = make_eval_ପଦସମଷ୍ଟି(e_last, 1, e1, e2);
        ଯଦି (!e0) {
            av_ପଦସମଷ୍ଟି_free(e1);
            av_ପଦସମଷ୍ଟି_free(e2);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }
    };

    p->ଗଦା_index++;
    *e = e0;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା verify_ପଦସମଷ୍ଟି(AVExpr *e)
{
    ଯଦି (!e) ଫେରନ୍ତୁ 0;
    ବାଛ (e->type) {
        ସ୍ଥିତି e_ମୂଲ୍ୟ:
        ସ୍ଥିତି e_const: ଫେରନ୍ତୁ 1;
        ସ୍ଥିତି e_func0:
        ସ୍ଥିତି e_func1:
        ସ୍ଥିତି e_squish:
        ସ୍ଥିତି e_ld:
        ସ୍ଥିତି e_gauss:
        ସ୍ଥିତି e_isnan:
        ସ୍ଥିତି e_isinf:
        ସ୍ଥିତି e_floor:
        ସ୍ଥିତି e_ceil:
        ସ୍ଥିତି e_trunc:
        ସ୍ଥିତି e_round:
        ସ୍ଥିତି e_sqrt:
        ସ୍ଥିତି e_not:
        ସ୍ଥିତି e_random:
        ସ୍ଥିତି e_sgn:
            ଫେରନ୍ତୁ verify_ପଦସମଷ୍ଟି(e->param[0]) && !e->param[1];
        ସ୍ଥିତି e_print:
            ଫେରନ୍ତୁ verify_ପଦସମଷ୍ଟି(e->param[0])
                   && (!e->param[1] || verify_ପଦସମଷ୍ଟି(e->param[1]));
        ସ୍ଥିତି e_if:
        ସ୍ଥିତି e_ifnot:
        ସ୍ଥିତି e_taylor:
            ଫେରନ୍ତୁ verify_ପଦସମଷ୍ଟି(e->param[0]) && verify_ପଦସମଷ୍ଟି(e->param[1])
                   && (!e->param[2] || verify_ପଦସମଷ୍ଟି(e->param[2]));
        ସ୍ଥିତି e_between:
        ସ୍ଥିତି e_clip:
        ସ୍ଥିତି e_lerp:
        ସ୍ଥିତି e_randomi:
            ଫେରନ୍ତୁ verify_ପଦସମଷ୍ଟି(e->param[0]) &&
                   verify_ପଦସମଷ୍ଟି(e->param[1]) &&
                   verify_ପଦସମଷ୍ଟି(e->param[2]);
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ: ଫେରନ୍ତୁ verify_ପଦସମଷ୍ଟି(e->param[0]) && verify_ପଦସମଷ୍ଟି(e->param[1]) && !e->param[2];
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_ପଦସମଷ୍ଟି_parse(AVExpr **ପଦସମଷ୍ଟି, ଅଚଳ ଅକ୍ଷର *s,
                  ଅଚଳ ଅକ୍ଷର * ଅଚଳ *const_names,
                  ଅଚଳ ଅକ୍ଷର * ଅଚଳ *func1_names, ଦ୍ୱିଗୁଣ (* ଅଚଳ *funcs1)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ),
                  ଅଚଳ ଅକ୍ଷର * ଅଚଳ *func2_names, ଦ୍ୱିଗୁଣ (* ଅଚଳ *funcs2)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ, ଦ୍ୱିଗୁଣ),
                  ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset, ଶୂନ୍ୟ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ଖାଲି;
    ଅକ୍ଷର *w = av_malloc(strlen(s) + 1);
    ଅକ୍ଷର *wp = w;
    ଅଚଳ ଅକ୍ଷର *s0 = s;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (!w)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଯେତେବେଳେ (*s)
        ଯଦି (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ଗଦା_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    ଯଦି ((ret = parse_ପଦସମଷ୍ଟି(&e, &p)) < 0)
        ଯାଅ end;
    ଯଦି (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        ଯାଅ end;
    }
    ଯଦି (!verify_ପଦସମଷ୍ଟି(e)) {
        ret = AVERROR(EINVAL);
        ଯାଅ end;
    }
    AVExpr_ମୂଳ *r = av_realloc(e, ଆକାର(*r));
    ଯଦି (!r) {
        ret = AVERROR(ENOMEM);
        ଯାଅ end;
    }
    e = (AVExpr*)r;
    e->ମୂଳ = 1;
    r->var= av_mallocz(ଆକାର(ଦ୍ୱିଗୁଣ) *VARS);
    r->prng_state = av_mallocz(ଆକାର(*r->prng_state) *VARS);
    ଯଦି (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        ଯାଅ end;
    }
    *ପଦସମଷ୍ଟି = e;
    e = ଖାଲି;
end:
    av_ପଦସମଷ୍ଟି_free(e);
    av_free(w);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ପଦସମଷ୍ଟି_ଗଣନା(AVExpr *e, unsigned *counter, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା type)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (!e || !counter || !size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ପାଇଁ (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        ପଦସମଷ୍ଟି_ଗଣନା(e->param[i], counter, size, type);

    ଯଦି (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_ପଦସମଷ୍ଟି_ଗଣନା_vars(AVExpr *e, unsigned *counter, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି_ଗଣନା(e, counter, size, e_const);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_ପଦସମଷ୍ଟି_ଗଣନା_func(AVExpr *e, unsigned *counter, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା arg)
{
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି_ଗଣନା(e, counter, size, ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା[]){e_const, e_func1, e_func2})[arg]);
}

ଦ୍ୱିଗୁଣ av_ପଦସମଷ୍ଟି_eval(AVExpr *e, ଅଚଳ ଦ୍ୱିଗୁଣ *const_ମୂଲ୍ୟଗୁଡ଼ିକ, ଶୂନ୍ୟ *opaque)
{
    av_assert1(e->ମୂଳ);
    AVExpr_ମୂଳ *r = (AVExpr_ମୂଳ *)e;
    Parser p = {
        .class        = &eval_class,
        .const_ମୂଲ୍ୟଗୁଡ଼ିକ = const_ମୂଲ୍ୟଗୁଡ଼ିକ,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    ଫେରନ୍ତୁ eval_ପଦସମଷ୍ଟି(&p, e);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_ପଦସମଷ୍ଟି_parse_and_eval(ଦ୍ୱିଗୁଣ *d, ଅଚଳ ଅକ୍ଷର *s,
                           ଅଚଳ ଅକ୍ଷର * ଅଚଳ *const_names, ଅଚଳ ଦ୍ୱିଗୁଣ *const_ମୂଲ୍ୟଗୁଡ଼ିକ,
                           ଅଚଳ ଅକ୍ଷର * ଅଚଳ *func1_names, ଦ୍ୱିଗୁଣ (* ଅଚଳ *funcs1)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ),
                           ଅଚଳ ଅକ୍ଷର * ଅଚଳ *func2_names, ଦ୍ୱିଗୁଣ (* ଅଚଳ *funcs2)(ଶୂନ୍ୟ *, ଦ୍ୱିଗୁଣ, ଦ୍ୱିଗୁଣ),
                           ଶୂନ୍ୟ *opaque, ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset, ଶୂନ୍ୟ *log_ctx)
{
    AVExpr *e = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = av_ପଦସମଷ୍ଟି_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    ଯଦି (ret < 0) {
        *d = NAN;
        ଫେରନ୍ତୁ ret;
    }
    *d = av_ପଦସମଷ୍ଟି_eval(e, const_ମୂଲ୍ୟଗୁଡ଼ିକ, opaque);
    av_ପଦସମଷ୍ଟି_free(e);
    ଫେରନ୍ତୁ isnan(*d) ? AVERROR(EINVAL) : 0;
}
