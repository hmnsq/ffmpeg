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

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_ಆಳ 100

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Parser {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ಪೂರ್ಣಾಂಕ ರಾಶಿ_ಸೂಚ್ಯಂಕ;
    ಅಕ್ಷರ *s;
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *const_ಮೌಲ್ಯಗಳು;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *const_ಹೆಸರುಗಳು;          // NULL terminated
    ದ್ವಿಗುಣ (* ಸ್ಥಿರಾಂಕ *funcs1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ a);           // NULL terminated
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *func1_ಹೆಸರುಗಳು;          // NULL terminated
    ದ್ವಿಗುಣ (* ಸ್ಥಿರಾಂಕ *funcs2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ a, ದ್ವಿಗುಣ b); // NULL terminated
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *func2_ಹೆಸರುಗಳು;          // NULL terminated
    ಶೂನ್ಯ *opaque;
    ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ;
    ಶೂನ್ಯ *log_ctx;
#ವ್ಯಾಖ್ಯಾನಿಸು VARS 10
    ದ್ವಿಗುಣ *var;
    FFSFC64 *prng_state;
} Parser;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass eval_class = {
    .class_name                = "Eval",
    .ಅಂಶ_name                 = av_default_ಅಂಶ_name,
    .option                    = ಖಾಲಿ,
    .ಆವೃತ್ತಿ                   = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ   = offsetof(Parser, log_ಸ್ಥಾನಾಂತರ),
    .ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ = offsetof(Parser, log_ctx),
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ದ್ವಿಗುಣ bin_val;
    ದ್ವಿಗುಣ dec_val;
    int8_t ಘಾತಾಂಕ;
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
    ದ್ವಿಗುಣ ಮೌಲ್ಯ;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

ದ್ವಿಗುಣ av_strtod(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *numstr, ಅಕ್ಷರ **ಬಾಲ)
{
    ದ್ವಿಗುಣ d;
    ಅಕ್ಷರ *ಮುಂದಿನ;
    ಆದರೆ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &ಮುಂದಿನ, 16);
    } ಇಲ್ಲದಿದ್ದರೆ
        d = strtod(numstr, &ಮುಂದಿನ);
    /* if parsing succeeded, check for and interpret postfixes */
    ಆದರೆ (ಮುಂದಿನ!=numstr) {
        ಆದರೆ (ಮುಂದಿನ[0] == 'd' && ಮುಂದಿನ[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            ಮುಂದಿನ += 2;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*ಮುಂದಿನ >= 'E' && *ಮುಂದಿನ <= 'z') {
            ಪೂರ್ಣಾಂಕ e= si_prefixes[*ಮುಂದಿನ - 'E'].ಘಾತಾಂಕ;
            ಆದರೆ (e) {
                ಆದರೆ (ಮುಂದಿನ[1] == 'i') {
                    d*= si_prefixes[*ಮುಂದಿನ - 'E'].bin_val;
                    ಮುಂದಿನ+=2;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    d*= si_prefixes[*ಮುಂದಿನ - 'E'].dec_val;
                    ಮುಂದಿನ++;
                }
            }
        }

        ಆದರೆ (*ಮುಂದಿನ=='B') {
            d*=8;
            ಮುಂದಿನ++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ಆದರೆ (ಬಾಲ)
        *ಬಾಲ = ಮುಂದಿನ;
    ಹಿಂತಿರುಗಿ d;
}

#ವ್ಯಾಖ್ಯಾನಿಸು IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ strmatch(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪೂರ್ವಪ್ರತ್ಯಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i=0; ಪೂರ್ವಪ್ರತ್ಯಯ[i]; i++) {
        ಆದರೆ (ಪೂರ್ವಪ್ರತ್ಯಯ[i] != s[i]) ಹಿಂತಿರುಗಿ 0;
    }
    /* return 1 only if the s identifier is terminated */
    ಹಿಂತಿರುಗಿ !IS_IDENTIFIER_CHAR(s[i]);
}

ಎಣಿಕೆ {
    e_ಮೌಲ್ಯ, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_ಕೂಡಿಸು,
    e_ಕೊನೆಯ, e_st, e_while, e_taylor, e_ಬೇರು, e_floor, e_ceil, e_trunc, e_ಸುತ್ತು,
    e_sqrt, e_not, e_random, e_hypot, e_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ರಚನೆ AVExpr {
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ type;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ಬೇರು;
    ಗಿಡ್ಡ ಆಳ;
    ಪೂರ್ಣಾಂಕ const_ಸೂಚ್ಯಂಕ;
    ದ್ವಿಗುಣ ಮೌಲ್ಯ; // is sign in other types
    ಒಕ್ಕೂಟ {
        ದ್ವಿಗುಣ (*func0)(ದ್ವಿಗುಣ);
        ದ್ವಿಗುಣ (*func1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ);
        ದ್ವಿಗುಣ (*func2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ, ದ್ವಿಗುಣ);
    } ;
    ರಚನೆ AVExpr *param[3];
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ {
    AVExpr avexpr;
    ದ್ವಿಗುಣ *var;
    FFSFC64 *prng_state;
} AVExpr_ಬೇರು;

ಸ್ಥಿರ ದ್ವಿಗುಣ etime(ದ್ವಿಗುಣ v)
{
    ಹಿಂತಿರುಗಿ av_gettime() * 0.000001;
}

ಸ್ಥಿರ ದ್ವಿಗುಣ eval_ಅಭಿವ್ಯಕ್ತಿ(Parser *p, AVExpr *e)
{
    ಆಯ್ಕೆ (e->type) {
        ಸ್ಥಿತಿ e_ಮೌಲ್ಯ:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ;
        ಸ್ಥಿತಿ e_const:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * p->const_ಮೌಲ್ಯಗಳು[e->const_ಸೂಚ್ಯಂಕ];
        ಸ್ಥಿತಿ e_func0:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * e->func0(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_func1:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * e->func1(p->opaque, eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_func2:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * e->func2(p->opaque, eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]));
        ಸ್ಥಿತಿ e_squish: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ/(1+ಘಾತಾಂಕ(4*eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0])));
        ಸ್ಥಿತಿ e_gauss: { ದ್ವಿಗುಣ d = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]); ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * ಘಾತಾಂಕ(-d*d/2)/ವರ್ಗಮೂಲ(2*M_PI); }
        ಸ್ಥಿತಿ e_ld:     ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * p->var[av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), 0, VARS-1)];
        ಸ್ಥಿತಿ e_isnan:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * !!isnan(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_isinf:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * !!isinf(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_floor:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * floor(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_ceil :  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * ceil (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_trunc:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * trunc(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_ಸುತ್ತು:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * round(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_sgn:    ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * FFDIFFSIGN(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), 0);
        ಸ್ಥಿತಿ e_sqrt:   ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * ವರ್ಗಮೂಲ (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]));
        ಸ್ಥಿತಿ e_not:    ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]) == 0);
        ಸ್ಥಿತಿ e_if:     ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]) ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]) :
                                          e->param[2] ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]) : 0);
        ಸ್ಥಿತಿ e_ifnot:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (!eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]) ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]) :
                                          e->param[2] ? eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]) : 0);
        ಸ್ಥಿತಿ e_clip: {
            ದ್ವಿಗುಣ x = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ದ್ವಿಗುಣ min = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]), max = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]);
            ಆದರೆ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ಹಿಂತಿರುಗಿ NAN;
            ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * av_clipd(x, min, max);
        }
        ಸ್ಥಿತಿ e_between: {
            ದ್ವಿಗುಣ d = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d >= eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]) &&
                               d <= eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]));
        }
        ಸ್ಥಿತಿ e_lerp: {
            ದ್ವಿಗುಣ v0 = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ದ್ವಿಗುಣ v1 = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ದ್ವಿಗುಣ f  = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]);
            ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (v0 + (v1 - v0) * f);
        }
        ಸ್ಥಿತಿ e_print: {
            ದ್ವಿಗುಣ x = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ಪೂರ್ಣಾಂಕ level = e->param[1] ? av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]), INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * x;
        }

#ವ್ಯಾಖ್ಯಾನಿಸು COMPUTE_ಮುಂದಿನ_RANDOM()                                        \
            ಪೂರ್ಣಾಂಕ idx = av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ಆದರೆ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        ಸ್ಥಿತಿ e_random: {
            COMPUTE_ಮುಂದಿನ_RANDOM();
            ಹಿಂತಿರುಗಿ r * (1.0/UINT64_MAX);
        }
        ಸ್ಥಿತಿ e_randomi: {
            ದ್ವಿಗುಣ min = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ದ್ವಿಗುಣ max = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]);
            COMPUTE_ಮುಂದಿನ_RANDOM();
            ಹಿಂತಿರುಗಿ min + (max - min) * r / UINT64_MAX;
        }
        ಸ್ಥಿತಿ e_while: {
            ದ್ವಿಗುಣ d = NAN;
            ಆಗ (eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]))
                d=eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಹಿಂತಿರುಗಿ d;
        }
        ಸ್ಥಿತಿ e_taylor: {
            ದ್ವಿಗುಣ t = 1, d = 0, v;
            ದ್ವಿಗುಣ x = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಪೂರ್ಣಾಂಕ id = e->param[2] ? av_clip(eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[2]), 0, VARS-1) : 0;
            ಪೂರ್ಣಾಂಕ i;
            ದ್ವಿಗುಣ var0 = p->var[id];
            ಗಾಗಿ(i=0; i<1000; i++) {
                ದ್ವಿಗುಣ ld = d;
                p->var[id] = i;
                v = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
                d += t*v;
                ಆದರೆ(ld==d && v)
                    ನಿಲ್ಲಿಸು;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ಹಿಂತಿರುಗಿ d;
        }
        ಸ್ಥಿತಿ e_ಬೇರು: {
            ಪೂರ್ಣಾಂಕ i, j;
            ದ್ವಿಗುಣ ಕೆಳಗಿನ = -1, ಮೇಲಿನ = -1, v, ಕೆಳಗಿನ_v = -DBL_MAX, ಮೇಲಿನ_v = DBL_MAX;
            ದ್ವಿಗುಣ var0 = p->var[0];
            ದ್ವಿಗುಣ x_max = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಗಾಗಿ(i=-1; i<1024; i++) {
                ಆದರೆ(i<255) {
                    p->var[0] = ff_ಹಿಮ್ಮುಖ[i&255]*x_max/255;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    p->var[0] = x_max*ಘಾತ(0.9, i-255);
                    ಆದರೆ (i&1) p->var[0] *= -1;
                    ಆದರೆ (i&2) p->var[0] += ಕೆಳಗಿನ;
                    ಇಲ್ಲದಿದ್ದರೆ     p->var[0] += ಮೇಲಿನ;
                }
                v = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
                ಆದರೆ (v<=0 && v>ಕೆಳಗಿನ_v) {
                    ಕೆಳಗಿನ    = p->var[0];
                    ಕೆಳಗಿನ_v  = v;
                }
                ಆದರೆ (v>=0 && v<ಮೇಲಿನ_v) {
                    ಮೇಲಿನ   = p->var[0];
                    ಮೇಲಿನ_v = v;
                }
                ಆದರೆ (ಕೆಳಗಿನ>=0 && ಮೇಲಿನ>=0){
                    ಗಾಗಿ (j=0; j<1000; j++) {
                        p->var[0] = (ಕೆಳಗಿನ+ಮೇಲಿನ)*0.5;
                        ಆದರೆ (ಕೆಳಗಿನ == p->var[0] || ಮೇಲಿನ == p->var[0])
                            ನಿಲ್ಲಿಸು;
                        v = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
                        ಆದರೆ (v<=0) ಕೆಳಗಿನ = p->var[0];
                        ಆದರೆ (v>=0) ಮೇಲಿನ= p->var[0];
                        ಆದರೆ (isnan(v)) {
                            ಕೆಳಗಿನ = ಮೇಲಿನ = v;
                            ನಿಲ್ಲಿಸು;
                        }
                    }
                    ನಿಲ್ಲಿಸು;
                }
            }
            p->var[0] = var0;
            ಹಿಂತಿರುಗಿ -ಕೆಳಗಿನ_v<ಮೇಲಿನ_v ? ಕೆಳಗಿನ : ಮೇಲಿನ;
        }
        ಪೂರ್ವನಿಯೋಜಿತ: {
            ದ್ವಿಗುಣ d = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[0]);
            ದ್ವಿಗುಣ d2 = eval_ಅಭಿವ್ಯಕ್ತಿ(p, e->param[1]);
            ಆಯ್ಕೆ (e->type) {
                ಸ್ಥಿತಿ e_mod: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                ಸ್ಥಿತಿ e_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(d,d2);
                ಸ್ಥಿತಿ e_max: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d >  d2 ?   d : d2);
                ಸ್ಥಿತಿ e_min: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d <  d2 ?   d : d2);
                ಸ್ಥಿತಿ e_eq:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d == d2 ? 1.0 : 0.0);
                ಸ್ಥಿತಿ e_gt:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d >  d2 ? 1.0 : 0.0);
                ಸ್ಥಿತಿ e_gte: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d >= d2 ? 1.0 : 0.0);
                ಸ್ಥಿತಿ e_lt:  ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d <  d2 ? 1.0 : 0.0);
                ಸ್ಥಿತಿ e_lte: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d <= d2 ? 1.0 : 0.0);
                ಸ್ಥಿತಿ e_pow: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * ಘಾತ(d, d2);
                ಸ್ಥಿತಿ e_mul: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d * d2);
                ಸ್ಥಿತಿ e_div: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d2 ? (d / d2) : d * INFINITY);
                ಸ್ಥಿತಿ e_ಕೂಡಿಸು: ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (d + d2);
                ಸ್ಥಿತಿ e_ಕೊನೆಯ:ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * d2;
                ಸ್ಥಿತಿ e_st :  {
                    ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = av_clip(d, 0, VARS-1);
                    p->prng_state[ಸೂಚ್ಯಂಕ].counter = 0;
                    ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * (p->var[ಸೂಚ್ಯಂಕ]= d2);
                }
                ಸ್ಥಿತಿ e_hypot:ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * hypot(d, d2);
                ಸ್ಥಿತಿ e_atan2:ಹಿಂತಿರುಗಿ e->ಮೌಲ್ಯ * atan2(d, d2);
                ಸ್ಥಿತಿ e_bitand: ಹಿಂತಿರುಗಿ isnan(d) || isnan(d2) ? NAN : e->ಮೌಲ್ಯ * ((ದೀರ್ಘ ಪೂರ್ಣಾಂಕ)d & (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ)d2);
                ಸ್ಥಿತಿ e_bitor:  ಹಿಂತಿರುಗಿ isnan(d) || isnan(d2) ? NAN : e->ಮೌಲ್ಯ * ((ದೀರ್ಘ ಪೂರ್ಣಾಂಕ)d | (ದೀರ್ಘ ಪೂರ್ಣಾಂಕ)d2);
            }
        }
    }
    ಹಿಂತಿರುಗಿ NAN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_ಅಭಿವ್ಯಕ್ತಿ(AVExpr **e, Parser *p);

ಶೂನ್ಯ av_ಅಭಿವ್ಯಕ್ತಿ_free(AVExpr *e)
{
    ಆದರೆ (!e) ಹಿಂತಿರುಗಿ;
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e->param[0]);
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e->param[1]);
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e->param[2]);
    ಆದರೆ (e->ಬೇರು) {
        AVExpr_ಬೇರು *r = (AVExpr_ಬೇರು*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(ಗಾತ್ರ(AVExpr));
    ಅಕ್ಷರ *ಮುಂದಿನ = p->s, *s0 = p->s;
    ಪೂರ್ಣಾಂಕ ret, i;

    ಆದರೆ (!d)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /*ಸಂಖ್ಯೆ*/
    d->ಮೌಲ್ಯ = av_strtod(p->s, &ಮುಂದಿನ);
    ಆದರೆ (ಮುಂದಿನ != p->s) {
        d->type = e_ಮೌಲ್ಯ;
        p->s= ಮುಂದಿನ;
        *e = d;
        ಹಿಂತಿರುಗಿ 0;
    }
    d->ಮೌಲ್ಯ = 1;

    /* named constants */
    ಗಾಗಿ (i=0; p->const_ಹೆಸರುಗಳು && p->const_ಹೆಸರುಗಳು[i]; i++) {
        ಆದರೆ (strmatch(p->s, p->const_ಹೆಸರುಗಳು[i])) {
            p->s+= ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(p->const_ಹೆಸರುಗಳು[i]);
            d->type = e_const;
            d->const_ಸೂಚ್ಯಂಕ = i;
            *e = d;
            ಹಿಂತಿರುಗಿ 0;
        }
    }
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ಆದರೆ (strmatch(p->s, constants[i].name)) {
            p->s += ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(constants[i].name);
            d->type = e_ಮೌಲ್ಯ;
            d->ಮೌಲ್ಯ = constants[i].ಮೌಲ್ಯ;
            *e = d;
            ಹಿಂತಿರುಗಿ 0;
        }
    }

    p->s= strchr(p->s, '(');
    ಆದರೆ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= ಮುಂದಿನ;
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    p->s++; // "("
    ಆದರೆ (*ಮುಂದಿನ == '(') { // special case do-nothing
        av_freep(&d);
        ಆದರೆ ((ret = parse_ಅಭಿವ್ಯಕ್ತಿ(&d, p)) < 0)
            ಹಿಂತಿರುಗಿ ret;
        ಆದರೆ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ಹಿಂತಿರುಗಿ 0;
    }
    ಆದರೆ ((ret = parse_ಅಭಿವ್ಯಕ್ತಿ(&(d->param[0]), p)) < 0) {
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಹಿಂತಿರುಗಿ ret;
    }
    ಆದರೆ (p->s[0]== ',') {
        p->s++; // ","
        parse_ಅಭಿವ್ಯಕ್ತಿ(&d->param[1], p);
    }
    ಆದರೆ (p->s[0]== ',') {
        p->s++; // ","
        parse_ಅಭಿವ್ಯಕ್ತಿ(&d->param[2], p);
    }
    ಆದರೆ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    p->s++; // ")"

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i<3; i++)
        ಆದರೆ (d->param[i])
            d->ಆಳ = FFMAX(d->ಆಳ, d->param[i]->ಆಳ+1);
    ಆದರೆ (d->ಆಳ > MAX_ಆಳ) {
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    d->type = e_func0;
         ಆದರೆ (strmatch(ಮುಂದಿನ, "sinh"  )) d->func0 = sinh;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "cosh"  )) d->func0 = cosh;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "tanh"  )) d->func0 = tanh;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "sin"   )) d->func0 = ಜ್ಯಾ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "cos"   )) d->func0 = ಕೋಜ್ಯಾ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "tan"   )) d->func0 = tan;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "atan"  )) d->func0 = atan;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "asin"  )) d->func0 = asin;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "acos"  )) d->func0 = acos;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "exp"   )) d->func0 = ಘಾತಾಂಕ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "log"   )) d->func0 = ಲಘುಗಣಕ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "abs"   )) d->func0 = fabs;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "time"  )) d->func0 = etime;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "squish")) d->type = e_squish;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "gauss" )) d->type = e_gauss;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "mod"   )) d->type = e_mod;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "max"   )) d->type = e_max;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "min"   )) d->type = e_min;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "eq"    )) d->type = e_eq;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "gte"   )) d->type = e_gte;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "gt"    )) d->type = e_gt;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "lte"   )) d->type = e_lte;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "lt"    )) d->type = e_lt;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "ld"    )) d->type = e_ld;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "isnan" )) d->type = e_isnan;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "isinf" )) d->type = e_isinf;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "st"    )) d->type = e_st;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "while" )) d->type = e_while;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "taylor")) d->type = e_taylor;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "root"  )) d->type = e_ಬೇರು;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "floor" )) d->type = e_floor;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "ceil"  )) d->type = e_ceil;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "trunc" )) d->type = e_trunc;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "round" )) d->type = e_ಸುತ್ತು;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "sqrt"  )) d->type = e_sqrt;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "not"   )) d->type = e_not;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "pow"   )) d->type = e_pow;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "print" )) d->type = e_print;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "random")) d->type = e_random;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "randomi")) d->type = e_randomi;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "hypot" )) d->type = e_hypot;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "gcd"   )) d->type = e_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "if"    )) d->type = e_if;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "ifnot" )) d->type = e_ifnot;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "bitand")) d->type = e_bitand;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "bitor" )) d->type = e_bitor;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "between"))d->type = e_between;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "clip"  )) d->type = e_clip;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "atan2" )) d->type = e_atan2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "lerp"  )) d->type = e_lerp;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strmatch(ಮುಂದಿನ, "sgn"   )) d->type = e_sgn;
    ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (i=0; p->func1_ಹೆಸರುಗಳು && p->func1_ಹೆಸರುಗಳು[i]; i++) {
            ಆದರೆ (strmatch(ಮುಂದಿನ, p->func1_ಹೆಸರುಗಳು[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_ಸೂಚ್ಯಂಕ = i;
                *e = d;
                ಹಿಂತಿರುಗಿ 0;
            }
        }

        ಗಾಗಿ (i=0; p->func2_ಹೆಸರುಗಳು && p->func2_ಹೆಸರುಗಳು[i]; i++) {
            ಆದರೆ (strmatch(ಮುಂದಿನ, p->func2_ಹೆಸರುಗಳು[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_ಸೂಚ್ಯಂಕ = i;
                *e = d;
                ಹಿಂತಿರುಗಿ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_ಅಭಿವ್ಯಕ್ತಿ_free(d);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    *e = d;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ AVExpr *make_eval_ಅಭಿವ್ಯಕ್ತಿ(ಪೂರ್ಣಾಂಕ type, ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ, AVExpr *p0, AVExpr *p1)
{
    ಪೂರ್ಣಾಂಕ ಆಳ = FFMAX(p0->ಆಳ, p1->ಆಳ) + 1;
    ಆದರೆ (ಆಳ > MAX_ಆಳ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    AVExpr *e = av_mallocz(ಗಾತ್ರ(AVExpr));
    ಆದರೆ (!e)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    e->type     =type   ;
    e->ಮೌಲ್ಯ    =ಮೌಲ್ಯ  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->ಆಳ    = ಆಳ;
    ಹಿಂತಿರುಗಿ e;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_pow(AVExpr **e, Parser *p, ಪೂರ್ಣಾಂಕ *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ಹಿಂತಿರುಗಿ parse_primary(e, p);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_dB(AVExpr **e, Parser *p, ಪೂರ್ಣಾಂಕ *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ಆದರೆ (*p->s == '-') {
        ಅಕ್ಷರ *ಮುಂದಿನ;
        av_ಬಳಸದ ದ್ವಿಗುಣ ignored = strtod(p->s, &ಮುಂದಿನ);
        ಆದರೆ (ಮುಂದಿನ != p->s && ಮುಂದಿನ[0] == 'd' && ಮುಂದಿನ[1] == 'B') {
            *sign = 0;
            ಹಿಂತಿರುಗಿ parse_primary(e, p);
        }
    }
    ಹಿಂತಿರುಗಿ parse_pow(e, p, sign);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_ಗುಣಕ(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಂಕ sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ಆದರೆ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆಗ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ಆದರೆ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಹಿಂತಿರುಗಿ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(e_pow, 1, e1, e2);
        ಆದರೆ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
        ಆದರೆ (e0->param[1]) e0->param[1]->ಮೌಲ್ಯ *= (sign2|1);
    }
    ಆದರೆ (e0) e0->ಮೌಲ್ಯ *= (sign|1);

    *e = e0;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_ಪದ(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಂಕ ret;
    AVExpr *e0, *e1, *e2;
    ಆದರೆ ((ret = parse_ಗುಣಕ(&e0, p)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆಗ (p->s[0]=='*' || p->s[0]=='/') {
        ಪೂರ್ಣಾಂಕ c= *p->s++;
        e1 = e0;
        ಆದರೆ ((ret = parse_ಗುಣಕ(&e2, p)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಹಿಂತಿರುಗಿ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(c == '*' ? e_mul : e_div, 1, e1, e2);
        ಆದರೆ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_subexpr(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಂಕ ret;
    AVExpr *e0, *e1, *e2;
    ಆದರೆ ((ret = parse_ಪದ(&e0, p)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆಗ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ಆದರೆ ((ret = parse_ಪದ(&e2, p)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಹಿಂತಿರುಗಿ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(e_ಕೂಡಿಸು, 1, e1, e2);
        ಆದರೆ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ parse_ಅಭಿವ್ಯಕ್ತಿ(AVExpr **e, Parser *p)
{
    ಪೂರ್ಣಾಂಕ ret;
    AVExpr *e0, *e1, *e2;
    ಆದರೆ (p->ರಾಶಿ_ಸೂಚ್ಯಂಕ <= 0) //protect against stack overflows
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    p->ರಾಶಿ_ಸೂಚ್ಯಂಕ--;

    ಆದರೆ ((ret = parse_subexpr(&e0, p)) < 0)
        ಹಿಂತಿರುಗಿ ret;
    ಆಗ (*p->s == ';') {
        p->s++;
        e1 = e0;
        ಆದರೆ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            ಹಿಂತಿರುಗಿ ret;
        }
        e0 = make_eval_ಅಭಿವ್ಯಕ್ತಿ(e_ಕೊನೆಯ, 1, e1, e2);
        ಆದರೆ (!e0) {
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e1);
            av_ಅಭಿವ್ಯಕ್ತಿ_free(e2);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }
    };

    p->ರಾಶಿ_ಸೂಚ್ಯಂಕ++;
    *e = e0;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ verify_ಅಭಿವ್ಯಕ್ತಿ(AVExpr *e)
{
    ಆದರೆ (!e) ಹಿಂತಿರುಗಿ 0;
    ಆಯ್ಕೆ (e->type) {
        ಸ್ಥಿತಿ e_ಮೌಲ್ಯ:
        ಸ್ಥಿತಿ e_const: ಹಿಂತಿರುಗಿ 1;
        ಸ್ಥಿತಿ e_func0:
        ಸ್ಥಿತಿ e_func1:
        ಸ್ಥಿತಿ e_squish:
        ಸ್ಥಿತಿ e_ld:
        ಸ್ಥಿತಿ e_gauss:
        ಸ್ಥಿತಿ e_isnan:
        ಸ್ಥಿತಿ e_isinf:
        ಸ್ಥಿತಿ e_floor:
        ಸ್ಥಿತಿ e_ceil:
        ಸ್ಥಿತಿ e_trunc:
        ಸ್ಥಿತಿ e_ಸುತ್ತು:
        ಸ್ಥಿತಿ e_sqrt:
        ಸ್ಥಿತಿ e_not:
        ಸ್ಥಿತಿ e_random:
        ಸ್ಥಿತಿ e_sgn:
            ಹಿಂತಿರುಗಿ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) && !e->param[1];
        ಸ್ಥಿತಿ e_print:
            ಹಿಂತಿರುಗಿ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0])
                   && (!e->param[1] || verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1]));
        ಸ್ಥಿತಿ e_if:
        ಸ್ಥಿತಿ e_ifnot:
        ಸ್ಥಿತಿ e_taylor:
            ಹಿಂತಿರುಗಿ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) && verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1])
                   && (!e->param[2] || verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[2]));
        ಸ್ಥಿತಿ e_between:
        ಸ್ಥಿತಿ e_clip:
        ಸ್ಥಿತಿ e_lerp:
        ಸ್ಥಿತಿ e_randomi:
            ಹಿಂತಿರುಗಿ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) &&
                   verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1]) &&
                   verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[2]);
        ಪೂರ್ವನಿಯೋಜಿತ: ಹಿಂತಿರುಗಿ verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[0]) && verify_ಅಭಿವ್ಯಕ್ತಿ(e->param[1]) && !e->param[2];
    }
}

ಪೂರ್ಣಾಂಕ av_ಅಭಿವ್ಯಕ್ತಿ_parse(AVExpr **ಅಭಿವ್ಯಕ್ತಿ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s,
                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *const_ಹೆಸರುಗಳು,
                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *func1_ಹೆಸರುಗಳು, ದ್ವಿಗುಣ (* ಸ್ಥಿರಾಂಕ *funcs1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ),
                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *func2_ಹೆಸರುಗಳು, ದ್ವಿಗುಣ (* ಸ್ಥಿರಾಂಕ *funcs2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ, ದ್ವಿಗುಣ),
                  ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ಖಾಲಿ;
    ಅಕ್ಷರ *w = av_malloc(ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(s) + 1);
    ಅಕ್ಷರ *wp = w;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s0 = s;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (!w)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಆಗ (*s)
        ಆದರೆ (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ರಾಶಿ_ಸೂಚ್ಯಂಕ=100;
    p.s= w;
    p.const_ಹೆಸರುಗಳು = const_ಹೆಸರುಗಳು;
    p.funcs1      = funcs1;
    p.func1_ಹೆಸರುಗಳು = func1_ಹೆಸರುಗಳು;
    p.funcs2      = funcs2;
    p.func2_ಹೆಸರುಗಳು = func2_ಹೆಸರುಗಳು;
    p.log_ಸ್ಥಾನಾಂತರ = log_ಸ್ಥಾನಾಂತರ;
    p.log_ctx    = log_ctx;

    ಆದರೆ ((ret = parse_ಅಭಿವ್ಯಕ್ತಿ(&e, &p)) < 0)
        ಹೋಗು ಕೊನೆ;
    ಆದರೆ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        ಹೋಗು ಕೊನೆ;
    }
    ಆದರೆ (!verify_ಅಭಿವ್ಯಕ್ತಿ(e)) {
        ret = AVERROR(EINVAL);
        ಹೋಗು ಕೊನೆ;
    }
    AVExpr_ಬೇರು *r = av_realloc(e, ಗಾತ್ರ(*r));
    ಆದರೆ (!r) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು ಕೊನೆ;
    }
    e = (AVExpr*)r;
    e->ಬೇರು = 1;
    r->var= av_mallocz(ಗಾತ್ರ(ದ್ವಿಗುಣ) *VARS);
    r->prng_state = av_mallocz(ಗಾತ್ರ(*r->prng_state) *VARS);
    ಆದರೆ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು ಕೊನೆ;
    }
    *ಅಭಿವ್ಯಕ್ತಿ = e;
    e = ಖಾಲಿ;
ಕೊನೆ:
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e);
    av_free(w);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(AVExpr *e, ಚಿಹ್ನೆರಹಿತ *counter, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, ಪೂರ್ಣಾಂಕ type)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (!e || !counter || !ಗಾತ್ರ_2)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಗಾಗಿ (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(e->param[i], counter, ಗಾತ್ರ_2, type);

    ಆದರೆ (e->type == type && e->const_ಸೂಚ್ಯಂಕ < ಗಾತ್ರ_2)
        counter[e->const_ಸೂಚ್ಯಂಕ]++;

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ_vars(AVExpr *e, ಚಿಹ್ನೆರಹಿತ *counter, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(e, counter, ಗಾತ್ರ_2, e_const);
}

ಪೂರ್ಣಾಂಕ av_ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ_func(AVExpr *e, ಚಿಹ್ನೆರಹಿತ *counter, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2, ಪೂರ್ಣಾಂಕ arg)
{
    ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ_ಎಣಿಕೆ(e, counter, ಗಾತ್ರ_2, ((ಪೂರ್ಣಾಂಕ[]){e_const, e_func1, e_func2})[arg]);
}

ದ್ವಿಗುಣ av_ಅಭಿವ್ಯಕ್ತಿ_eval(AVExpr *e, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *const_ಮೌಲ್ಯಗಳು, ಶೂನ್ಯ *opaque)
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

    ಹಿಂತಿರುಗಿ eval_ಅಭಿವ್ಯಕ್ತಿ(&p, e);
}

ಪೂರ್ಣಾಂಕ av_ಅಭಿವ್ಯಕ್ತಿ_parse_and_eval(ದ್ವಿಗುಣ *d, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *const_ಹೆಸರುಗಳು, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *const_ಮೌಲ್ಯಗಳು,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *func1_ಹೆಸರುಗಳು, ದ್ವಿಗುಣ (* ಸ್ಥಿರಾಂಕ *funcs1)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ),
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ *func2_ಹೆಸರುಗಳು, ದ್ವಿಗುಣ (* ಸ್ಥಿರಾಂಕ *funcs2)(ಶೂನ್ಯ *, ದ್ವಿಗುಣ, ದ್ವಿಗುಣ),
                           ಶೂನ್ಯ *opaque, ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    AVExpr *e = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret = av_ಅಭಿವ್ಯಕ್ತಿ_parse(&e, s, const_ಹೆಸರುಗಳು, func1_ಹೆಸರುಗಳು, funcs1, func2_ಹೆಸರುಗಳು, funcs2, log_ಸ್ಥಾನಾಂತರ, log_ctx);

    ಆದರೆ (ret < 0) {
        *d = NAN;
        ಹಿಂತಿರುಗಿ ret;
    }
    *d = av_ಅಭಿವ್ಯಕ್ತಿ_eval(e, const_ಮೌಲ್ಯಗಳು, opaque);
    av_ಅಭಿವ್ಯಕ್ತಿ_free(e);
    ಹಿಂತಿರುಗಿ isnan(*d) ? AVERROR(EINVAL) : 0;
}
