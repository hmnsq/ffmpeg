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

#ಅನ್ತರ್ಭಾವ <float.h>
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "eval.h"
#ಅನ್ತರ್ಭಾವ "ffmath.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "sfc64.h"
#ಅನ್ತರ್ಭಾವ "time.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "reverse.h"

#define MAX_DEPTH 100

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Parser {
    ಧ್ರುವ AVClass *class;
    ಪೂರ್ಣಾಙ್ಕ ರಾಶಿ_index;
    ವರ್ಣ *s;
    ಧ್ರುವ ದ್ವಿಗುಣ *const_ಮೌಲ್ಯಗಳು;
    ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *const_names;          // NULL terminated
    ದ್ವಿಗುಣ (* ಧ್ರುವ *funcs1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ a);           // NULL terminated
    ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *func1_names;          // NULL terminated
    ದ್ವಿಗುಣ (* ಧ್ರುವ *funcs2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ a, ದ್ವಿಗುಣ b); // NULL terminated
    ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *func2_names;          // NULL terminated
    ಶೂನ್ಯ *opaque;
    ಪೂರ್ಣಾಙ್ಕ log_offset;
    ಶೂನ್ಯ *log_ctx;
#define VARS 10
    ದ್ವಿಗುಣ *var;
    FFSFC64 *prng_state;
} Parser;

ಸ್ಥಿರ ಧ್ರುವ AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = ರಿಕ್ತ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ದ್ವಿಗುಣ bin_val;
    ದ್ವಿಗುಣ dec_val;
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

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ *name;
    ದ್ವಿಗುಣ ಮೌಲ್ಯ;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

ದ್ವಿಗುಣ av_strtod(ಧ್ರುವ ವರ್ಣ *numstr, ವರ್ಣ **tail)
{
    ದ್ವಿಗುಣ d;
    ವರ್ಣ *next;
    ಯದಿ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } ಅನ್ಯಥಾ
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    ಯದಿ (next!=numstr) {
        ಯದಿ (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } ಅನ್ಯಥಾ ಯದಿ (*next >= 'E' && *next <= 'z') {
            ಪೂರ್ಣಾಙ್ಕ e= si_prefixes[*next - 'E'].exp;
            ಯದಿ (e) {
                ಯದಿ (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } ಅನ್ಯಥಾ {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        ಯದಿ (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ಯದಿ (tail)
        *tail = next;
    ಪ್ರತ್ಯಾಗಮ d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ strmatch(ಧ್ರುವ ವರ್ಣ *s, ಧ್ರುವ ವರ್ಣ *prefix)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i=0; prefix[i]; i++) {
        ಯದಿ (prefix[i] != s[i]) ಪ್ರತ್ಯಾಗಮ 0;
    }
    /* return 1 only if the s identifier is terminated */
    ಪ್ರತ್ಯಾಗಮ !IS_IDENTIFIER_CHAR(s[i]);
}

ಗಣನಾ {
    e_ಮೌಲ್ಯ, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_ಬೇರು, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ಸಂರಚನಾ AVExpr {
    unsigned ವರ್ಣ type;
    unsigned ವರ್ಣ ಬೇರು;
    short depth;
    ಪೂರ್ಣಾಙ್ಕ const_index;
    ದ್ವಿಗುಣ ಮೌಲ್ಯ; // is sign in other types
    ಸಙ್ಘ {
        ದ್ವಿಗುಣ (*func0)(ದ್ವಿಗುಣ);
        ದ್ವಿಗುಣ (*func1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ);
        ದ್ವಿಗುಣ (*func2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ, ದ್ವಿಗುಣ);
    } ;
    ಸಂರಚನಾ AVExpr *param[3];
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ {
    AVExpr avexpr;
    ದ್ವಿಗುಣ *var;
    FFSFC64 *prng_state;
} AVExpr_ಬೇರು;

ಸ್ಥಿರ ದ್ವಿಗುಣ etime(ದ್ವಿಗುಣ v)
{
    ಪ್ರತ್ಯಾಗಮ av_gettime() * 0.000001;
}

ಸ್ಥಿರ ದ್ವಿಗುಣ eval_ಅಭಿವ್ಯಕ್ತಿ(Parser *p, AVExpr *e)
{
    ವಿಕಲ್ಪ (e->type) {
        ಪಕ್ಷ e_ಮೌಲ್ಯ:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ;
        ಪಕ್ಷ e_const:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * p->const_ಮೌಲ್ಯಗಳು[e->const_index];
        ಪಕ್ಷ e_func0:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * e->func0(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_func1:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * e->func1(p->opaque, eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_func2:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * e->func2(p->opaque, eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]));
        ಪಕ್ಷ e_squish: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ/(1+exp(4*eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0])));
        ಪಕ್ಷ e_gauss: { ದ್ವಿಗುಣ d = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]); ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * exp(-d*d/2)/sqrt(2*M_PI); }
        ಪಕ್ಷ e_ld:     ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * p->var[av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), 0, VARS-1)];
        ಪಕ್ಷ e_isnan:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * !!isnan(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_isinf:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * !!isinf(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_floor:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * floor(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_ceil :  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * ceil (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_trunc:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * trunc(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_round:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * round(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_sgn:    ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * FFDIFFSIGN(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), 0);
        ಪಕ್ಷ e_sqrt:   ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * sqrt (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಪಕ್ಷ e_not:    ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]) == 0);
        ಪಕ್ಷ e_if:     ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]) ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]) :
                                          e->param[2] ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]) : 0);
        ಪಕ್ಷ e_ifnot:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (!eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]) ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]) :
                                          e->param[2] ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]) : 0);
        ಪಕ್ಷ e_clip: {
            ದ್ವಿಗುಣ x = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ದ್ವಿಗುಣ min = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]), max = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]);
            ಯದಿ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ಪ್ರತ್ಯಾಗಮ NAN;
            ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * av_clipd(x, min, max);
        }
        ಪಕ್ಷ e_between: {
            ದ್ವಿಗುಣ d = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d >= eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]) &&
                               d <= eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]));
        }
        ಪಕ್ಷ e_lerp: {
            ದ್ವಿಗುಣ v0 = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ದ್ವಿಗುಣ v1 = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ದ್ವಿಗುಣ f  = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]);
            ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (v0 + (v1 - v0) * f);
        }
        ಪಕ್ಷ e_print: {
            ದ್ವಿಗುಣ x = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ಪೂರ್ಣಾಙ್ಕ level = e->param[1] ? av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            ಪೂರ್ಣಾಙ್ಕ idx = av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ಯದಿ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        ಪಕ್ಷ e_random: {
            COMPUTE_NEXT_RANDOM();
            ಪ್ರತ್ಯಾಗಮ r * (1.0/UINT64_MAX);
        }
        ಪಕ್ಷ e_randomi: {
            ದ್ವಿಗುಣ min = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ದ್ವಿಗುಣ max = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            ಪ್ರತ್ಯಾಗಮ min + (max - min) * r / UINT64_MAX;
        }
        ಪಕ್ಷ e_while: {
            ದ್ವಿಗುಣ d = NAN;
            ಯಾವತ್ (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]))
                d=eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಪ್ರತ್ಯಾಗಮ d;
        }
        ಪಕ್ಷ e_taylor: {
            ದ್ವಿಗುಣ t = 1, d = 0, v;
            ದ್ವಿಗುಣ x = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಪೂರ್ಣಾಙ್ಕ id = e->param[2] ? av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]), 0, VARS-1) : 0;
            ಪೂರ್ಣಾಙ್ಕ i;
            ದ್ವಿಗುಣ var0 = p->var[id];
            ಪ್ರತಿ(i=0; i<1000; i++) {
                ದ್ವಿಗುಣ ld = d;
                p->var[id] = i;
                v = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
                d += t*v;
                ಯದಿ(ld==d && v)
                    ಭಙ್ಗ;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ಪ್ರತ್ಯಾಗಮ d;
        }
        ಪಕ್ಷ e_ಬೇರು: {
            ಪೂರ್ಣಾಙ್ಕ i, j;
            ದ್ವಿಗುಣ ಕೆಳಗಿನ = -1, ಮೇಲಿನ = -1, v, ಕೆಳಗಿನ_v = -DBL_MAX, ಮೇಲಿನ_v = DBL_MAX;
            ದ್ವಿಗುಣ var0 = p->var[0];
            ದ್ವಿಗುಣ x_max = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಪ್ರತಿ(i=-1; i<1024; i++) {
                ಯದಿ(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } ಅನ್ಯಥಾ {
                    p->var[0] = x_max*pow(0.9, i-255);
                    ಯದಿ (i&1) p->var[0] *= -1;
                    ಯದಿ (i&2) p->var[0] += ಕೆಳಗಿನ;
                    ಅನ್ಯಥಾ     p->var[0] += ಮೇಲಿನ;
                }
                v = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
                ಯದಿ (v<=0 && v>ಕೆಳಗಿನ_v) {
                    ಕೆಳಗಿನ    = p->var[0];
                    ಕೆಳಗಿನ_v  = v;
                }
                ಯದಿ (v>=0 && v<ಮೇಲಿನ_v) {
                    ಮೇಲಿನ   = p->var[0];
                    ಮೇಲಿನ_v = v;
                }
                ಯದಿ (ಕೆಳಗಿನ>=0 && ಮೇಲಿನ>=0){
                    ಪ್ರತಿ (j=0; j<1000; j++) {
                        p->var[0] = (ಕೆಳಗಿನ+ಮೇಲಿನ)*0.5;
                        ಯದಿ (ಕೆಳಗಿನ == p->var[0] || ಮೇಲಿನ == p->var[0])
                            ಭಙ್ಗ;
                        v = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
                        ಯದಿ (v<=0) ಕೆಳಗಿನ = p->var[0];
                        ಯದಿ (v>=0) ಮೇಲಿನ= p->var[0];
                        ಯದಿ (isnan(v)) {
                            ಕೆಳಗಿನ = ಮೇಲಿನ = v;
                            ಭಙ್ಗ;
                        }
                    }
                    ಭಙ್ಗ;
                }
            }
            p->var[0] = var0;
            ಪ್ರತ್ಯಾಗಮ -ಕೆಳಗಿನ_v<ಮೇಲಿನ_v ? ಕೆಳಗಿನ : ಮೇಲಿನ;
        }
        ಸ್ವಭಾವ: {
            ದ್ವಿಗುಣ d = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ದ್ವಿಗುಣ d2 = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ವಿಕಲ್ಪ (e->type) {
                ಪಕ್ಷ e_mod: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                ಪಕ್ಷ e_gcd: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * av_gcd(d,d2);
                ಪಕ್ಷ e_max: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d >  d2 ?   d : d2);
                ಪಕ್ಷ e_min: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d <  d2 ?   d : d2);
                ಪಕ್ಷ e_eq:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d == d2 ? 1.0 : 0.0);
                ಪಕ್ಷ e_gt:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d >  d2 ? 1.0 : 0.0);
                ಪಕ್ಷ e_gte: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d >= d2 ? 1.0 : 0.0);
                ಪಕ್ಷ e_lt:  ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d <  d2 ? 1.0 : 0.0);
                ಪಕ್ಷ e_lte: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d <= d2 ? 1.0 : 0.0);
                ಪಕ್ಷ e_pow: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * pow(d, d2);
                ಪಕ್ಷ e_mul: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d * d2);
                ಪಕ್ಷ e_div: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d2 ? (d / d2) : d * INFINITY);
                ಪಕ್ಷ e_add: ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (d + d2);
                ಪಕ್ಷ e_last:ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * d2;
                ಪಕ್ಷ e_st :  {
                    ಪೂರ್ಣಾಙ್ಕ index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * (p->var[index]= d2);
                }
                ಪಕ್ಷ e_hypot:ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * hypot(d, d2);
                ಪಕ್ಷ e_atan2:ಪ್ರತ್ಯಾಗಮ e->ಮೌಲ್ಯ * atan2(d, d2);
                ಪಕ್ಷ e_bitand: ಪ್ರತ್ಯಾಗಮ isnan(d) || isnan(d2) ? NAN : e->ಮೌಲ್ಯ * ((long ಪೂರ್ಣಾಙ್ಕ)d & (long ಪೂರ್ಣಾಙ್ಕ)d2);
                ಪಕ್ಷ e_bitor:  ಪ್ರತ್ಯಾಗಮ isnan(d) || isnan(d2) ? NAN : e->ಮೌಲ್ಯ * ((long ಪೂರ್ಣಾಙ್ಕ)d | (long ಪೂರ್ಣಾಙ್ಕ)d2);
            }
        }
    }
    ಪ್ರತ್ಯಾಗಮ NAN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_ಅಭಿವ್ಯಕ್ತಿ(AVExpr **e, Parser *p);

ಶೂನ್ಯ av_ಅಭಿವ್ಯಕ್ತಿ_free(AVExpr *e)
{
    ಯದಿ (!e) ಪ್ರತ್ಯಾಗಮ;
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e->param[0]);
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e->param[1]);
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e->param[2]);
    ಯದಿ (e->ಬೇರು) {
        AVExpr_ಬೇರು *r = (AVExpr_ಬೇರು*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(ಪರಿಮಾಣ(AVExpr));
    ವರ್ಣ *next = p->s, *s0 = p->s;
    ಪೂರ್ಣಾಙ್ಕ ret, i;

    ಯದಿ (!d)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    /*ಸಂಖ್ಯೆ*/
    d->ಮೌಲ್ಯ = av_strtod(p->s, &next);
    ಯದಿ (next != p->s) {
        d->type = e_ಮೌಲ್ಯ;
        p->s= next;
        *e = d;
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    d->ಮೌಲ್ಯ = 1;

    /* named constants */
    ಪ್ರತಿ (i=0; p->const_names && p->const_names[i]; i++) {
        ಯದಿ (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ಯದಿ (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_ಮೌಲ್ಯ;
            d->ಮೌಲ್ಯ = constants[i].ಮೌಲ್ಯ;
            *e = d;
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }

    p->s= strchr(p->s, '(');
    ಯದಿ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    p->s++; // "("
    ಯದಿ (*next == '(') { // special case do-nothing
        av_freep(&d);
        ಯದಿ ((ret = parse_ಅಭಿವ್ಯಕ್ತಿ(&d, p)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
        ಯದಿ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ಪ್ರತ್ಯಾಗಮ 0;
    }
    ಯದಿ ((ret = parse_ಅಭಿವ್ಯಕ್ತಿ(&(d->param[0]), p)) < 0) {
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    ಯದಿ (p->s[0]== ',') {
        p->s++; // ","
        parse_ಅಭಿವ್ಯಕ್ತಿ(&d->param[1], p);
    }
    ಯದಿ (p->s[0]== ',') {
        p->s++; // ","
        parse_ಅಭಿವ್ಯಕ್ತಿ(&d->param[2], p);
    }
    ಯದಿ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    p->s++; // ")"

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i<3; i++)
        ಯದಿ (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    ಯದಿ (d->depth > MAX_DEPTH) {
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    d->type = e_func0;
         ಯದಿ (strmatch(next, "sinh"  )) d->func0 = sinh;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "cosh"  )) d->func0 = cosh;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "tanh"  )) d->func0 = tanh;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "sin"   )) d->func0 = sin;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "cos"   )) d->func0 = cos;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "tan"   )) d->func0 = tan;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "atan"  )) d->func0 = atan;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "asin"  )) d->func0 = asin;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "acos"  )) d->func0 = acos;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "exp"   )) d->func0 = exp;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "log"   )) d->func0 = log;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "abs"   )) d->func0 = fabs;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "time"  )) d->func0 = etime;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "squish")) d->type = e_squish;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "gauss" )) d->type = e_gauss;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "mod"   )) d->type = e_mod;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "max"   )) d->type = e_max;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "min"   )) d->type = e_min;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "eq"    )) d->type = e_eq;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "gte"   )) d->type = e_gte;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "gt"    )) d->type = e_gt;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "lte"   )) d->type = e_lte;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "lt"    )) d->type = e_lt;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "ld"    )) d->type = e_ld;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "isnan" )) d->type = e_isnan;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "isinf" )) d->type = e_isinf;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "st"    )) d->type = e_st;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "while" )) d->type = e_while;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "taylor")) d->type = e_taylor;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "root"  )) d->type = e_ಬೇರು;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "floor" )) d->type = e_floor;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "ceil"  )) d->type = e_ceil;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "trunc" )) d->type = e_trunc;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "round" )) d->type = e_round;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "not"   )) d->type = e_not;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "pow"   )) d->type = e_pow;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "print" )) d->type = e_print;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "random")) d->type = e_random;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "randomi")) d->type = e_randomi;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "hypot" )) d->type = e_hypot;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "gcd"   )) d->type = e_gcd;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "if"    )) d->type = e_if;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "ifnot" )) d->type = e_ifnot;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "bitand")) d->type = e_bitand;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "bitor" )) d->type = e_bitor;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "between"))d->type = e_between;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "clip"  )) d->type = e_clip;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "atan2" )) d->type = e_atan2;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "lerp"  )) d->type = e_lerp;
    ಅನ್ಯಥಾ ಯದಿ (strmatch(next, "sgn"   )) d->type = e_sgn;
    ಅನ್ಯಥಾ {
        ಪ್ರತಿ (i=0; p->func1_names && p->func1_names[i]; i++) {
            ಯದಿ (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                ಪ್ರತ್ಯಾಗಮ 0;
            }
        }

        ಪ್ರತಿ (i=0; p->func2_names && p->func2_names[i]; i++) {
            ಯದಿ (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                ಪ್ರತ್ಯಾಗಮ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    *e = d;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ AVExpr *make_eval_ಅಭಿವ್ಯಕ್ತಿ(ಪೂರ್ಣಾಙ್ಕ type, ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ, AVExpr *p0, AVExpr *p1)
{
    ಪೂರ್ಣಾಙ್ಕ depth = FFMAX(p0->depth, p1->depth) + 1;
    ಯದಿ (depth > MAX_DEPTH)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    AVExpr *e = av_mallocz(ಪರಿಮಾಣ(AVExpr));
    ಯದಿ (!e)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    e->type     =type   ;
    e->ಮೌಲ್ಯ    =ಮೌಲ್ಯ  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ಪ್ರತ್ಯಾಗಮ e;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_pow(AVExpr **e, Parser *p, ಪೂರ್ಣಾಙ್ಕ *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ಪ್ರತ್ಯಾಗಮ parse_primary(e, p);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_dB(AVExpr **e, Parser *p, ಪೂರ್ಣಾಙ್ಕ *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ಯದಿ (*p->s == '-') {
        ವರ್ಣ *next;
        av_unused ದ್ವಿಗುಣ ignored = strtod(p->s, &next);
        ಯದಿ (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            ಪ್ರತ್ಯಾಗಮ parse_primary(e, p);
        }
    }
    ಪ್ರತ್ಯಾಗಮ parse_pow(e, p, sign);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_factor(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಙ್ಕ sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ಯದಿ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯಾವತ್(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ಯದಿ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(e_pow, 1, e1, e2);
        ಯದಿ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
        ಯದಿ (e0->param[1]) e0->param[1]->ಮೌಲ್ಯ *= (sign2|1);
    }
    ಯದಿ (e0) e0->ಮೌಲ್ಯ *= (sign|1);

    *e = e0;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_term(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    AVExpr *e0, *e1, *e2;
    ಯದಿ ((ret = parse_factor(&e0, p)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯಾವತ್ (p->s[0]=='*' || p->s[0]=='/') {
        ಪೂರ್ಣಾಙ್ಕ c= *p->s++;
        e1 = e0;
        ಯದಿ ((ret = parse_factor(&e2, p)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(c == '*' ? e_mul : e_div, 1, e1, e2);
        ಯದಿ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_subexpr(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    AVExpr *e0, *e1, *e2;
    ಯದಿ ((ret = parse_term(&e0, p)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯಾವತ್ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ಯದಿ ((ret = parse_term(&e2, p)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(e_add, 1, e1, e2);
        ಯದಿ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ parse_ಅಭಿವ್ಯಕ್ತಿ(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    AVExpr *e0, *e1, *e2;
    ಯದಿ (p->ರಾಶಿ_index <= 0) //protect against stack overflows
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    p->ರಾಶಿ_index--;

    ಯದಿ ((ret = parse_subexpr(&e0, p)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
    ಯಾವತ್ (*p->s == ';') {
        p->s++;
        e1 = e0;
        ಯದಿ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(e_last, 1, e1, e2);
        ಯದಿ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }
    };

    p->ರಾಶಿ_index++;
    *e = e0;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ verify_ಅಭಿವ್ಯಕ್ತಿ(AVExpr *e)
{
    ಯದಿ (!e) ಪ್ರತ್ಯಾಗಮ 0;
    ವಿಕಲ್ಪ (e->type) {
        ಪಕ್ಷ e_ಮೌಲ್ಯ:
        ಪಕ್ಷ e_const: ಪ್ರತ್ಯಾಗಮ 1;
        ಪಕ್ಷ e_func0:
        ಪಕ್ಷ e_func1:
        ಪಕ್ಷ e_squish:
        ಪಕ್ಷ e_ld:
        ಪಕ್ಷ e_gauss:
        ಪಕ್ಷ e_isnan:
        ಪಕ್ಷ e_isinf:
        ಪಕ್ಷ e_floor:
        ಪಕ್ಷ e_ceil:
        ಪಕ್ಷ e_trunc:
        ಪಕ್ಷ e_round:
        ಪಕ್ಷ e_sqrt:
        ಪಕ್ಷ e_not:
        ಪಕ್ಷ e_random:
        ಪಕ್ಷ e_sgn:
            ಪ್ರತ್ಯಾಗಮ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) && !e->param[1];
        ಪಕ್ಷ e_print:
            ಪ್ರತ್ಯಾಗಮ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0])
                   && (!e->param[1] || verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1]));
        ಪಕ್ಷ e_if:
        ಪಕ್ಷ e_ifnot:
        ಪಕ್ಷ e_taylor:
            ಪ್ರತ್ಯಾಗಮ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) && verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1])
                   && (!e->param[2] || verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[2]));
        ಪಕ್ಷ e_between:
        ಪಕ್ಷ e_clip:
        ಪಕ್ಷ e_lerp:
        ಪಕ್ಷ e_randomi:
            ಪ್ರತ್ಯಾಗಮ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) &&
                   verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1]) &&
                   verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[2]);
        ಸ್ವಭಾವ: ಪ್ರತ್ಯಾಗಮ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) && verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1]) && !e->param[2];
    }
}

ಪೂರ್ಣಾಙ್ಕ av_ಅಭಿವ್ಯಕ್ತಿ_parse(AVExpr **ಅಭಿವ್ಯಕ್ತಿ, ಧ್ರುವ ವರ್ಣ *s,
                  ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *const_names,
                  ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *func1_names, ದ್ವಿಗುಣ (* ಧ್ರುವ *funcs1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ),
                  ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *func2_names, ದ್ವಿಗುಣ (* ಧ್ರುವ *funcs2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ, ದ್ವಿಗುಣ),
                  ಪೂರ್ಣಾಙ್ಕ log_offset, ಶೂನ್ಯ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ರಿಕ್ತ;
    ವರ್ಣ *w = av_malloc(strlen(s) + 1);
    ವರ್ಣ *wp = w;
    ಧ್ರುವ ವರ್ಣ *s0 = s;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (!w)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಯಾವತ್ (*s)
        ಯದಿ (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ರಾಶಿ_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    ಯದಿ ((ret = parse_ಅಭಿವ್ಯಕ್ತಿ(&e, &p)) < 0)
        ಗಚ್ಛ end;
    ಯದಿ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        ಗಚ್ಛ end;
    }
    ಯದಿ (!verify_ಅಭಿವ್ಯಕ್ತಿ(e)) {
        ret = AVERROR(EINVAL);
        ಗಚ್ಛ end;
    }
    AVExpr_ಬೇರು *r = av_realloc(e, ಪರಿಮಾಣ(*r));
    ಯದಿ (!r) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ end;
    }
    e = (AVExpr*)r;
    e->ಬೇರು = 1;
    r->var= av_mallocz(ಪರಿಮಾಣ(ದ್ವಿಗುಣ) *VARS);
    r->prng_state = av_mallocz(ಪರಿಮಾಣ(*r->prng_state) *VARS);
    ಯದಿ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ end;
    }
    *ಅಭಿವ್ಯಕ್ತಿ = e;
    e = ರಿಕ್ತ;
end:
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e);
    av_free(w);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(AVExpr *e, unsigned *counter, ಪೂರ್ಣಾಙ್ಕ size, ಪೂರ್ಣಾಙ್ಕ type)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (!e || !counter || !size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಪ್ರತಿ (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(e->param[i], counter, size, type);

    ಯದಿ (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ_vars(AVExpr *e, unsigned *counter, ಪೂರ್ಣಾಙ್ಕ size)
{
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(e, counter, size, e_const);
}

ಪೂರ್ಣಾಙ್ಕ av_ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ_func(AVExpr *e, unsigned *counter, ಪೂರ್ಣಾಙ್ಕ size, ಪೂರ್ಣಾಙ್ಕ arg)
{
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(e, counter, size, ((ಪೂರ್ಣಾಙ್ಕ[]){e_const, e_func1, e_func2})[arg]);
}

ದ್ವಿಗುಣ av_ಅಭಿವ್ಯಕ್ತಿ_eval(AVExpr *e, ಧ್ರುವ ದ್ವಿಗುಣ *const_ಮೌಲ್ಯಗಳು, ಶೂನ್ಯ *opaque)
{
    av_assert1(e->ಬೇರು);
    AVExpr_ಬೇರು *r = (AVExpr_ಬೇರು *)e;
    Parser p = {
        .class        = &eval_class,
        .const_ಮೌಲ್ಯಗಳು = const_ಮೌಲ್ಯಗಳು,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    ಪ್ರತ್ಯಾಗಮ eval_ಅಭಿವ್ಯಕ್ತಿ(&p, e);
}

ಪೂರ್ಣಾಙ್ಕ av_ಅಭಿವ್ಯಕ್ತಿ_parse_and_eval(ದ್ವಿಗುಣ *d, ಧ್ರುವ ವರ್ಣ *s,
                           ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *const_names, ಧ್ರುವ ದ್ವಿಗುಣ *const_ಮೌಲ್ಯಗಳು,
                           ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *func1_names, ದ್ವಿಗುಣ (* ಧ್ರುವ *funcs1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ),
                           ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ *func2_names, ದ್ವಿಗುಣ (* ಧ್ರುವ *funcs2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ, ದ್ವಿಗುಣ),
                           ಶೂನ್ಯ *opaque, ಪೂರ್ಣಾಙ್ಕ log_offset, ಶೂನ್ಯ *log_ctx)
{
    AVExpr *e = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret = av_ಅಭಿವ್ಯಕ್ತಿ_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    ಯದಿ (ret < 0) {
        *d = NAN;
        ಪ್ರತ್ಯಾಗಮ ret;
    }
    *d = av_ಅಭಿವ್ಯಕ್ತಿ_eval(e, const_ಮೌಲ್ಯಗಳು, opaque);
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e);
    ಪ್ರತ್ಯಾಗಮ isnan(*d) ? AVERROR(EINVAL) : 0;
}
