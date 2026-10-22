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

#ਅਨ੍ਤਰ੍ਭਾਵ <float.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "eval.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "ffmath.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sfc64.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "time.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "reverse.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_ਡੂੰਘਾਈ 100

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Parser {
    ਅਚਲ AVClass *class;
    ਪੂਰਨ ਢੇਰ_ਸੂਚਕਾਂਕ;
    ਅੱਖਰ *s;
    ਅਚਲ ਦੁੱਗਣਾ *const_ਮੁੱਲਾਂ;
    ਅਚਲ ਅੱਖਰ * ਅਚਲ *const_ਨਾਂ;          // NULL terminated
    ਦੁੱਗਣਾ (* ਅਚਲ *funcs1)(ਖਾਲੀ *, ਦੁੱਗਣਾ a);           // NULL terminated
    ਅਚਲ ਅੱਖਰ * ਅਚਲ *func1_ਨਾਂ;          // NULL terminated
    ਦੁੱਗਣਾ (* ਅਚਲ *funcs2)(ਖਾਲੀ *, ਦੁੱਗਣਾ a, ਦੁੱਗਣਾ b); // NULL terminated
    ਅਚਲ ਅੱਖਰ * ਅਚਲ *func2_ਨਾਂ;          // NULL terminated
    ਖਾਲੀ *opaque;
    ਪੂਰਨ log_ਵਿੱਥ;
    ਖਾਲੀ *log_ctx;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VARS 10
    ਦੁੱਗਣਾ *var;
    FFSFC64 *prng_state;
} Parser;

ਸਥਿਰ ਅਚਲ AVClass eval_class = {
    .class_name                = "Eval",
    .ਵਸਤੂ_name                 = av_default_ਵਸਤੂ_name,
    .option                    = ਨਿਰਾ,
    .ਸੰਸਕਰਣ                   = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .log_level_ਵਿੱਥ_ਵਿੱਥ   = offsetof(Parser, log_ਵਿੱਥ),
    .ਮਾਪਾ_log_context_ਵਿੱਥ = offsetof(Parser, log_ctx),
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਦੁੱਗਣਾ bin_val;
    ਦੁੱਗਣਾ dec_val;
    int8_t ਘਾਤਾਂਕ;
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

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਅਚਲ ਅੱਖਰ *name;
    ਦੁੱਗਣਾ ਮੁੱਲ;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

ਦੁੱਗਣਾ av_strtod(ਅਚਲ ਅੱਖਰ *numstr, ਅੱਖਰ **ਪੂਛ)
{
    ਦੁੱਗਣਾ d;
    ਅੱਖਰ *ਅਗਲਾ;
    ਜੇ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &ਅਗਲਾ, 16);
    } ਨਹੀਂਤਾਂ
        d = strtod(numstr, &ਅਗਲਾ);
    /* if parsing succeeded, check for and interpret postfixes */
    ਜੇ (ਅਗਲਾ!=numstr) {
        ਜੇ (ਅਗਲਾ[0] == 'd' && ਅਗਲਾ[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            ਅਗਲਾ += 2;
        } ਨਹੀਂਤਾਂ ਜੇ (*ਅਗਲਾ >= 'E' && *ਅਗਲਾ <= 'z') {
            ਪੂਰਨ e= si_prefixes[*ਅਗਲਾ - 'E'].ਘਾਤਾਂਕ;
            ਜੇ (e) {
                ਜੇ (ਅਗਲਾ[1] == 'i') {
                    d*= si_prefixes[*ਅਗਲਾ - 'E'].bin_val;
                    ਅਗਲਾ+=2;
                } ਨਹੀਂਤਾਂ {
                    d*= si_prefixes[*ਅਗਲਾ - 'E'].dec_val;
                    ਅਗਲਾ++;
                }
            }
        }

        ਜੇ (*ਅਗਲਾ=='B') {
            d*=8;
            ਅਗਲਾ++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ਜੇ (ਪੂਛ)
        *ਪੂਛ = ਅਗਲਾ;
    ਵਾਪਸ d;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ਸਥਿਰ ਪੂਰਨ strmatch(ਅਚਲ ਅੱਖਰ *s, ਅਚਲ ਅੱਖਰ *ਅਗੇਤਰ)
{
    ਪੂਰਨ i;
    ਲਈ (i=0; ਅਗੇਤਰ[i]; i++) {
        ਜੇ (ਅਗੇਤਰ[i] != s[i]) ਵਾਪਸ 0;
    }
    /* return 1 only if the s identifier is terminated */
    ਵਾਪਸ !IS_IDENTIFIER_CHAR(s[i]);
}

ਗਿਣਤੀ {
    e_ਮੁੱਲ, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_ਜੋੜੋ,
    e_ਆਖਰੀ, e_st, e_while, e_taylor, e_ਜੜ੍ਹ, e_floor, e_ceil, e_trunc, e_ਗੇੜਾ,
    e_sqrt, e_not, e_random, e_hypot, e_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ਬਣਤਰ AVExpr {
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ type;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ ਜੜ੍ਹ;
    ਛੋਟਾ ਡੂੰਘਾਈ;
    ਪੂਰਨ const_ਸੂਚਕਾਂਕ;
    ਦੁੱਗਣਾ ਮੁੱਲ; // is sign in other types
    ਸੰਘ {
        ਦੁੱਗਣਾ (*func0)(ਦੁੱਗਣਾ);
        ਦੁੱਗਣਾ (*func1)(ਖਾਲੀ *, ਦੁੱਗਣਾ);
        ਦੁੱਗਣਾ (*func2)(ਖਾਲੀ *, ਦੁੱਗਣਾ, ਦੁੱਗਣਾ);
    } ;
    ਬਣਤਰ AVExpr *param[3];
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ {
    AVExpr avexpr;
    ਦੁੱਗਣਾ *var;
    FFSFC64 *prng_state;
} AVExpr_ਜੜ੍ਹ;

ਸਥਿਰ ਦੁੱਗਣਾ etime(ਦੁੱਗਣਾ v)
{
    ਵਾਪਸ av_gettime() * 0.000001;
}

ਸਥਿਰ ਦੁੱਗਣਾ eval_ਵਿਅੰਜਕ(Parser *p, AVExpr *e)
{
    ਚੋਣ (e->type) {
        ਹਾਲਤ e_ਮੁੱਲ:  ਵਾਪਸ e->ਮੁੱਲ;
        ਹਾਲਤ e_const:  ਵਾਪਸ e->ਮੁੱਲ * p->const_ਮੁੱਲਾਂ[e->const_ਸੂਚਕਾਂਕ];
        ਹਾਲਤ e_func0:  ਵਾਪਸ e->ਮੁੱਲ * e->func0(eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_func1:  ਵਾਪਸ e->ਮੁੱਲ * e->func1(p->opaque, eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_func2:  ਵਾਪਸ e->ਮੁੱਲ * e->func2(p->opaque, eval_ਵਿਅੰਜਕ(p, e->param[0]), eval_ਵਿਅੰਜਕ(p, e->param[1]));
        ਹਾਲਤ e_squish: ਵਾਪਸ e->ਮੁੱਲ/(1+ਘਾਤਾਂਕ(4*eval_ਵਿਅੰਜਕ(p, e->param[0])));
        ਹਾਲਤ e_gauss: { ਦੁੱਗਣਾ d = eval_ਵਿਅੰਜਕ(p, e->param[0]); ਵਾਪਸ e->ਮੁੱਲ * ਘਾਤਾਂਕ(-d*d/2)/ਵਰਗਮੂਲ(2*M_PI); }
        ਹਾਲਤ e_ld:     ਵਾਪਸ e->ਮੁੱਲ * p->var[av_clip(eval_ਵਿਅੰਜਕ(p, e->param[0]), 0, VARS-1)];
        ਹਾਲਤ e_isnan:  ਵਾਪਸ e->ਮੁੱਲ * !!isnan(eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_isinf:  ਵਾਪਸ e->ਮੁੱਲ * !!isinf(eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_floor:  ਵਾਪਸ e->ਮੁੱਲ * floor(eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_ceil :  ਵਾਪਸ e->ਮੁੱਲ * ceil (eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_trunc:  ਵਾਪਸ e->ਮੁੱਲ * trunc(eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_ਗੇੜਾ:  ਵਾਪਸ e->ਮੁੱਲ * round(eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_sgn:    ਵਾਪਸ e->ਮੁੱਲ * FFDIFFSIGN(eval_ਵਿਅੰਜਕ(p, e->param[0]), 0);
        ਹਾਲਤ e_sqrt:   ਵਾਪਸ e->ਮੁੱਲ * ਵਰਗਮੂਲ (eval_ਵਿਅੰਜਕ(p, e->param[0]));
        ਹਾਲਤ e_not:    ਵਾਪਸ e->ਮੁੱਲ * (eval_ਵਿਅੰਜਕ(p, e->param[0]) == 0);
        ਹਾਲਤ e_if:     ਵਾਪਸ e->ਮੁੱਲ * (eval_ਵਿਅੰਜਕ(p, e->param[0]) ? eval_ਵਿਅੰਜਕ(p, e->param[1]) :
                                          e->param[2] ? eval_ਵਿਅੰਜਕ(p, e->param[2]) : 0);
        ਹਾਲਤ e_ifnot:  ਵਾਪਸ e->ਮੁੱਲ * (!eval_ਵਿਅੰਜਕ(p, e->param[0]) ? eval_ਵਿਅੰਜਕ(p, e->param[1]) :
                                          e->param[2] ? eval_ਵਿਅੰਜਕ(p, e->param[2]) : 0);
        ਹਾਲਤ e_clip: {
            ਦੁੱਗਣਾ x = eval_ਵਿਅੰਜਕ(p, e->param[0]);
            ਦੁੱਗਣਾ min = eval_ਵਿਅੰਜਕ(p, e->param[1]), max = eval_ਵਿਅੰਜਕ(p, e->param[2]);
            ਜੇ (isnan(min) || isnan(max) || isnan(x) || min > max)
                ਵਾਪਸ NAN;
            ਵਾਪਸ e->ਮੁੱਲ * av_clipd(x, min, max);
        }
        ਹਾਲਤ e_between: {
            ਦੁੱਗਣਾ d = eval_ਵਿਅੰਜਕ(p, e->param[0]);
            ਵਾਪਸ e->ਮੁੱਲ * (d >= eval_ਵਿਅੰਜਕ(p, e->param[1]) &&
                               d <= eval_ਵਿਅੰਜਕ(p, e->param[2]));
        }
        ਹਾਲਤ e_lerp: {
            ਦੁੱਗਣਾ v0 = eval_ਵਿਅੰਜਕ(p, e->param[0]);
            ਦੁੱਗਣਾ v1 = eval_ਵਿਅੰਜਕ(p, e->param[1]);
            ਦੁੱਗਣਾ f  = eval_ਵਿਅੰਜਕ(p, e->param[2]);
            ਵਾਪਸ e->ਮੁੱਲ * (v0 + (v1 - v0) * f);
        }
        ਹਾਲਤ e_print: {
            ਦੁੱਗਣਾ x = eval_ਵਿਅੰਜਕ(p, e->param[0]);
            ਪੂਰਨ level = e->param[1] ? av_clip(eval_ਵਿਅੰਜਕ(p, e->param[1]), INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ਵਾਪਸ e->ਮੁੱਲ * x;
        }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COMPUTE_ਅਗਲਾ_RANDOM()                                        \
            ਪੂਰਨ idx = av_clip(eval_ਵਿਅੰਜਕ(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ਜੇ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        ਹਾਲਤ e_random: {
            COMPUTE_ਅਗਲਾ_RANDOM();
            ਵਾਪਸ r * (1.0/UINT64_MAX);
        }
        ਹਾਲਤ e_randomi: {
            ਦੁੱਗਣਾ min = eval_ਵਿਅੰਜਕ(p, e->param[1]);
            ਦੁੱਗਣਾ max = eval_ਵਿਅੰਜਕ(p, e->param[2]);
            COMPUTE_ਅਗਲਾ_RANDOM();
            ਵਾਪਸ min + (max - min) * r / UINT64_MAX;
        }
        ਹਾਲਤ e_while: {
            ਦੁੱਗਣਾ d = NAN;
            ਜਦੋਂ (eval_ਵਿਅੰਜਕ(p, e->param[0]))
                d=eval_ਵਿਅੰਜਕ(p, e->param[1]);
            ਵਾਪਸ d;
        }
        ਹਾਲਤ e_taylor: {
            ਦੁੱਗਣਾ t = 1, d = 0, v;
            ਦੁੱਗਣਾ x = eval_ਵਿਅੰਜਕ(p, e->param[1]);
            ਪੂਰਨ id = e->param[2] ? av_clip(eval_ਵਿਅੰਜਕ(p, e->param[2]), 0, VARS-1) : 0;
            ਪੂਰਨ i;
            ਦੁੱਗਣਾ var0 = p->var[id];
            ਲਈ(i=0; i<1000; i++) {
                ਦੁੱਗਣਾ ld = d;
                p->var[id] = i;
                v = eval_ਵਿਅੰਜਕ(p, e->param[0]);
                d += t*v;
                ਜੇ(ld==d && v)
                    ਰੋਕੋ;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ਵਾਪਸ d;
        }
        ਹਾਲਤ e_ਜੜ੍ਹ: {
            ਪੂਰਨ i, j;
            ਦੁੱਗਣਾ ਨੀਵਾਂ = -1, ਉੱਚਾ = -1, v, ਨੀਵਾਂ_v = -DBL_MAX, ਉੱਚਾ_v = DBL_MAX;
            ਦੁੱਗਣਾ var0 = p->var[0];
            ਦੁੱਗਣਾ x_max = eval_ਵਿਅੰਜਕ(p, e->param[1]);
            ਲਈ(i=-1; i<1024; i++) {
                ਜੇ(i<255) {
                    p->var[0] = ff_ਉਲਟ[i&255]*x_max/255;
                } ਨਹੀਂਤਾਂ {
                    p->var[0] = x_max*ਘਾਤ(0.9, i-255);
                    ਜੇ (i&1) p->var[0] *= -1;
                    ਜੇ (i&2) p->var[0] += ਨੀਵਾਂ;
                    ਨਹੀਂਤਾਂ     p->var[0] += ਉੱਚਾ;
                }
                v = eval_ਵਿਅੰਜਕ(p, e->param[0]);
                ਜੇ (v<=0 && v>ਨੀਵਾਂ_v) {
                    ਨੀਵਾਂ    = p->var[0];
                    ਨੀਵਾਂ_v  = v;
                }
                ਜੇ (v>=0 && v<ਉੱਚਾ_v) {
                    ਉੱਚਾ   = p->var[0];
                    ਉੱਚਾ_v = v;
                }
                ਜੇ (ਨੀਵਾਂ>=0 && ਉੱਚਾ>=0){
                    ਲਈ (j=0; j<1000; j++) {
                        p->var[0] = (ਨੀਵਾਂ+ਉੱਚਾ)*0.5;
                        ਜੇ (ਨੀਵਾਂ == p->var[0] || ਉੱਚਾ == p->var[0])
                            ਰੋਕੋ;
                        v = eval_ਵਿਅੰਜਕ(p, e->param[0]);
                        ਜੇ (v<=0) ਨੀਵਾਂ = p->var[0];
                        ਜੇ (v>=0) ਉੱਚਾ= p->var[0];
                        ਜੇ (isnan(v)) {
                            ਨੀਵਾਂ = ਉੱਚਾ = v;
                            ਰੋਕੋ;
                        }
                    }
                    ਰੋਕੋ;
                }
            }
            p->var[0] = var0;
            ਵਾਪਸ -ਨੀਵਾਂ_v<ਉੱਚਾ_v ? ਨੀਵਾਂ : ਉੱਚਾ;
        }
        ਮੂਲ: {
            ਦੁੱਗਣਾ d = eval_ਵਿਅੰਜਕ(p, e->param[0]);
            ਦੁੱਗਣਾ d2 = eval_ਵਿਅੰਜਕ(p, e->param[1]);
            ਚੋਣ (e->type) {
                ਹਾਲਤ e_mod: ਵਾਪਸ e->ਮੁੱਲ * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                ਹਾਲਤ e_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ: ਵਾਪਸ e->ਮੁੱਲ * av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(d,d2);
                ਹਾਲਤ e_max: ਵਾਪਸ e->ਮੁੱਲ * (d >  d2 ?   d : d2);
                ਹਾਲਤ e_min: ਵਾਪਸ e->ਮੁੱਲ * (d <  d2 ?   d : d2);
                ਹਾਲਤ e_eq:  ਵਾਪਸ e->ਮੁੱਲ * (d == d2 ? 1.0 : 0.0);
                ਹਾਲਤ e_gt:  ਵਾਪਸ e->ਮੁੱਲ * (d >  d2 ? 1.0 : 0.0);
                ਹਾਲਤ e_gte: ਵਾਪਸ e->ਮੁੱਲ * (d >= d2 ? 1.0 : 0.0);
                ਹਾਲਤ e_lt:  ਵਾਪਸ e->ਮੁੱਲ * (d <  d2 ? 1.0 : 0.0);
                ਹਾਲਤ e_lte: ਵਾਪਸ e->ਮੁੱਲ * (d <= d2 ? 1.0 : 0.0);
                ਹਾਲਤ e_pow: ਵਾਪਸ e->ਮੁੱਲ * ਘਾਤ(d, d2);
                ਹਾਲਤ e_mul: ਵਾਪਸ e->ਮੁੱਲ * (d * d2);
                ਹਾਲਤ e_div: ਵਾਪਸ e->ਮੁੱਲ * (d2 ? (d / d2) : d * INFINITY);
                ਹਾਲਤ e_ਜੋੜੋ: ਵਾਪਸ e->ਮੁੱਲ * (d + d2);
                ਹਾਲਤ e_ਆਖਰੀ:ਵਾਪਸ e->ਮੁੱਲ * d2;
                ਹਾਲਤ e_st :  {
                    ਪੂਰਨ ਸੂਚਕਾਂਕ = av_clip(d, 0, VARS-1);
                    p->prng_state[ਸੂਚਕਾਂਕ].counter = 0;
                    ਵਾਪਸ e->ਮੁੱਲ * (p->var[ਸੂਚਕਾਂਕ]= d2);
                }
                ਹਾਲਤ e_hypot:ਵਾਪਸ e->ਮੁੱਲ * hypot(d, d2);
                ਹਾਲਤ e_atan2:ਵਾਪਸ e->ਮੁੱਲ * atan2(d, d2);
                ਹਾਲਤ e_bitand: ਵਾਪਸ isnan(d) || isnan(d2) ? NAN : e->ਮੁੱਲ * ((ਲੰਮਾ ਪੂਰਨ)d & (ਲੰਮਾ ਪੂਰਨ)d2);
                ਹਾਲਤ e_bitor:  ਵਾਪਸ isnan(d) || isnan(d2) ? NAN : e->ਮੁੱਲ * ((ਲੰਮਾ ਪੂਰਨ)d | (ਲੰਮਾ ਪੂਰਨ)d2);
            }
        }
    }
    ਵਾਪਸ NAN;
}

ਸਥਿਰ ਪੂਰਨ parse_ਵਿਅੰਜਕ(AVExpr **e, Parser *p);

ਖਾਲੀ av_ਵਿਅੰਜਕ_free(AVExpr *e)
{
    ਜੇ (!e) ਵਾਪਸ;
    av_ਵਿਅੰਜਕ_free(e->param[0]);
    av_ਵਿਅੰਜਕ_free(e->param[1]);
    av_ਵਿਅੰਜਕ_free(e->param[2]);
    ਜੇ (e->ਜੜ੍ਹ) {
        AVExpr_ਜੜ੍ਹ *r = (AVExpr_ਜੜ੍ਹ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ਸਥਿਰ ਪੂਰਨ parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(ਆਕਾਰ(AVExpr));
    ਅੱਖਰ *ਅਗਲਾ = p->s, *s0 = p->s;
    ਪੂਰਨ ret, i;

    ਜੇ (!d)
        ਵਾਪਸ AVERROR(ENOMEM);

    /*ਸੰਖਿਆ*/
    d->ਮੁੱਲ = av_strtod(p->s, &ਅਗਲਾ);
    ਜੇ (ਅਗਲਾ != p->s) {
        d->type = e_ਮੁੱਲ;
        p->s= ਅਗਲਾ;
        *e = d;
        ਵਾਪਸ 0;
    }
    d->ਮੁੱਲ = 1;

    /* named constants */
    ਲਈ (i=0; p->const_ਨਾਂ && p->const_ਨਾਂ[i]; i++) {
        ਜੇ (strmatch(p->s, p->const_ਨਾਂ[i])) {
            p->s+= ਲੜੀ_ਲੰਬਾਈ(p->const_ਨਾਂ[i]);
            d->type = e_const;
            d->const_ਸੂਚਕਾਂਕ = i;
            *e = d;
            ਵਾਪਸ 0;
        }
    }
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ਜੇ (strmatch(p->s, constants[i].name)) {
            p->s += ਲੜੀ_ਲੰਬਾਈ(constants[i].name);
            d->type = e_ਮੁੱਲ;
            d->ਮੁੱਲ = constants[i].ਮੁੱਲ;
            *e = d;
            ਵਾਪਸ 0;
        }
    }

    p->s= strchr(p->s, '(');
    ਜੇ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= ਅਗਲਾ;
        av_ਵਿਅੰਜਕ_free(d);
        ਵਾਪਸ AVERROR(EINVAL);
    }
    p->s++; // "("
    ਜੇ (*ਅਗਲਾ == '(') { // special case do-nothing
        av_freep(&d);
        ਜੇ ((ret = parse_ਵਿਅੰਜਕ(&d, p)) < 0)
            ਵਾਪਸ ret;
        ਜੇ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_ਵਿਅੰਜਕ_free(d);
            ਵਾਪਸ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ਵਾਪਸ 0;
    }
    ਜੇ ((ret = parse_ਵਿਅੰਜਕ(&(d->param[0]), p)) < 0) {
        av_ਵਿਅੰਜਕ_free(d);
        ਵਾਪਸ ret;
    }
    ਜੇ (p->s[0]== ',') {
        p->s++; // ","
        parse_ਵਿਅੰਜਕ(&d->param[1], p);
    }
    ਜੇ (p->s[0]== ',') {
        p->s++; // ","
        parse_ਵਿਅੰਜਕ(&d->param[2], p);
    }
    ਜੇ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_ਵਿਅੰਜਕ_free(d);
        ਵਾਪਸ AVERROR(EINVAL);
    }
    p->s++; // ")"

    ਲਈ (ਪੂਰਨ i = 0; i<3; i++)
        ਜੇ (d->param[i])
            d->ਡੂੰਘਾਈ = FFMAX(d->ਡੂੰਘਾਈ, d->param[i]->ਡੂੰਘਾਈ+1);
    ਜੇ (d->ਡੂੰਘਾਈ > MAX_ਡੂੰਘਾਈ) {
        av_ਵਿਅੰਜਕ_free(d);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    d->type = e_func0;
         ਜੇ (strmatch(ਅਗਲਾ, "sinh"  )) d->func0 = sinh;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "cosh"  )) d->func0 = cosh;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "tanh"  )) d->func0 = tanh;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "sin"   )) d->func0 = ਜੀਵਾ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "cos"   )) d->func0 = ਕੋਜੀਵਾ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "tan"   )) d->func0 = tan;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "atan"  )) d->func0 = atan;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "asin"  )) d->func0 = asin;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "acos"  )) d->func0 = acos;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "exp"   )) d->func0 = ਘਾਤਾਂਕ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "log"   )) d->func0 = ਲਘੂਗਣਕ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "abs"   )) d->func0 = fabs;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "time"  )) d->func0 = etime;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "squish")) d->type = e_squish;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "gauss" )) d->type = e_gauss;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "mod"   )) d->type = e_mod;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "max"   )) d->type = e_max;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "min"   )) d->type = e_min;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "eq"    )) d->type = e_eq;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "gte"   )) d->type = e_gte;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "gt"    )) d->type = e_gt;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "lte"   )) d->type = e_lte;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "lt"    )) d->type = e_lt;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "ld"    )) d->type = e_ld;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "isnan" )) d->type = e_isnan;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "isinf" )) d->type = e_isinf;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "st"    )) d->type = e_st;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "while" )) d->type = e_while;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "taylor")) d->type = e_taylor;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "root"  )) d->type = e_ਜੜ੍ਹ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "floor" )) d->type = e_floor;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "ceil"  )) d->type = e_ceil;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "trunc" )) d->type = e_trunc;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "round" )) d->type = e_ਗੇੜਾ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "sqrt"  )) d->type = e_sqrt;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "not"   )) d->type = e_not;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "pow"   )) d->type = e_pow;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "print" )) d->type = e_print;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "random")) d->type = e_random;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "randomi")) d->type = e_randomi;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "hypot" )) d->type = e_hypot;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "gcd"   )) d->type = e_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "if"    )) d->type = e_if;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "ifnot" )) d->type = e_ifnot;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "bitand")) d->type = e_bitand;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "bitor" )) d->type = e_bitor;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "between"))d->type = e_between;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "clip"  )) d->type = e_clip;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "atan2" )) d->type = e_atan2;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "lerp"  )) d->type = e_lerp;
    ਨਹੀਂਤਾਂ ਜੇ (strmatch(ਅਗਲਾ, "sgn"   )) d->type = e_sgn;
    ਨਹੀਂਤਾਂ {
        ਲਈ (i=0; p->func1_ਨਾਂ && p->func1_ਨਾਂ[i]; i++) {
            ਜੇ (strmatch(ਅਗਲਾ, p->func1_ਨਾਂ[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_ਸੂਚਕਾਂਕ = i;
                *e = d;
                ਵਾਪਸ 0;
            }
        }

        ਲਈ (i=0; p->func2_ਨਾਂ && p->func2_ਨਾਂ[i]; i++) {
            ਜੇ (strmatch(ਅਗਲਾ, p->func2_ਨਾਂ[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_ਸੂਚਕਾਂਕ = i;
                *e = d;
                ਵਾਪਸ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_ਵਿਅੰਜਕ_free(d);
        ਵਾਪਸ AVERROR(EINVAL);
    }

    *e = d;
    ਵਾਪਸ 0;
}

ਸਥਿਰ AVExpr *make_eval_ਵਿਅੰਜਕ(ਪੂਰਨ type, ਪੂਰਨ ਮੁੱਲ, AVExpr *p0, AVExpr *p1)
{
    ਪੂਰਨ ਡੂੰਘਾਈ = FFMAX(p0->ਡੂੰਘਾਈ, p1->ਡੂੰਘਾਈ) + 1;
    ਜੇ (ਡੂੰਘਾਈ > MAX_ਡੂੰਘਾਈ)
        ਵਾਪਸ ਨਿਰਾ;
    AVExpr *e = av_mallocz(ਆਕਾਰ(AVExpr));
    ਜੇ (!e)
        ਵਾਪਸ ਨਿਰਾ;
    e->type     =type   ;
    e->ਮੁੱਲ    =ਮੁੱਲ  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->ਡੂੰਘਾਈ    = ਡੂੰਘਾਈ;
    ਵਾਪਸ e;
}

ਸਥਿਰ ਪੂਰਨ parse_pow(AVExpr **e, Parser *p, ਪੂਰਨ *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ਵਾਪਸ parse_primary(e, p);
}

ਸਥਿਰ ਪੂਰਨ parse_dB(AVExpr **e, Parser *p, ਪੂਰਨ *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ਜੇ (*p->s == '-') {
        ਅੱਖਰ *ਅਗਲਾ;
        av_ਅਣਵਰਤਿਆ ਦੁੱਗਣਾ ignored = strtod(p->s, &ਅਗਲਾ);
        ਜੇ (ਅਗਲਾ != p->s && ਅਗਲਾ[0] == 'd' && ਅਗਲਾ[1] == 'B') {
            *sign = 0;
            ਵਾਪਸ parse_primary(e, p);
        }
    }
    ਵਾਪਸ parse_pow(e, p, sign);
}

ਸਥਿਰ ਪੂਰਨ parse_ਗੁਣਕ(AVExpr **e, Parser *p)
{
    ਪੂਰਨ sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ਜੇ ((ret = parse_dB(&e0, p, &sign)) < 0)
        ਵਾਪਸ ret;
    ਜਦੋਂ(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ਜੇ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_ਵਿਅੰਜਕ_free(e1);
            ਵਾਪਸ ret;
        }
        e0 = make_eval_ਵਿਅੰਜਕ(e_pow, 1, e1, e2);
        ਜੇ (!e0) {
            av_ਵਿਅੰਜਕ_free(e1);
            av_ਵਿਅੰਜਕ_free(e2);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
        ਜੇ (e0->param[1]) e0->param[1]->ਮੁੱਲ *= (sign2|1);
    }
    ਜੇ (e0) e0->ਮੁੱਲ *= (sign|1);

    *e = e0;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ parse_ਪਦ(AVExpr **e, Parser *p)
{
    ਪੂਰਨ ret;
    AVExpr *e0, *e1, *e2;
    ਜੇ ((ret = parse_ਗੁਣਕ(&e0, p)) < 0)
        ਵਾਪਸ ret;
    ਜਦੋਂ (p->s[0]=='*' || p->s[0]=='/') {
        ਪੂਰਨ c= *p->s++;
        e1 = e0;
        ਜੇ ((ret = parse_ਗੁਣਕ(&e2, p)) < 0) {
            av_ਵਿਅੰਜਕ_free(e1);
            ਵਾਪਸ ret;
        }
        e0 = make_eval_ਵਿਅੰਜਕ(c == '*' ? e_mul : e_div, 1, e1, e2);
        ਜੇ (!e0) {
            av_ਵਿਅੰਜਕ_free(e1);
            av_ਵਿਅੰਜਕ_free(e2);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ parse_subexpr(AVExpr **e, Parser *p)
{
    ਪੂਰਨ ret;
    AVExpr *e0, *e1, *e2;
    ਜੇ ((ret = parse_ਪਦ(&e0, p)) < 0)
        ਵਾਪਸ ret;
    ਜਦੋਂ (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ਜੇ ((ret = parse_ਪਦ(&e2, p)) < 0) {
            av_ਵਿਅੰਜਕ_free(e1);
            ਵਾਪਸ ret;
        }
        e0 = make_eval_ਵਿਅੰਜਕ(e_ਜੋੜੋ, 1, e1, e2);
        ਜੇ (!e0) {
            av_ਵਿਅੰਜਕ_free(e1);
            av_ਵਿਅੰਜਕ_free(e2);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ parse_ਵਿਅੰਜਕ(AVExpr **e, Parser *p)
{
    ਪੂਰਨ ret;
    AVExpr *e0, *e1, *e2;
    ਜੇ (p->ਢੇਰ_ਸੂਚਕਾਂਕ <= 0) //protect against stack overflows
        ਵਾਪਸ AVERROR(EINVAL);
    p->ਢੇਰ_ਸੂਚਕਾਂਕ--;

    ਜੇ ((ret = parse_subexpr(&e0, p)) < 0)
        ਵਾਪਸ ret;
    ਜਦੋਂ (*p->s == ';') {
        p->s++;
        e1 = e0;
        ਜੇ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_ਵਿਅੰਜਕ_free(e1);
            ਵਾਪਸ ret;
        }
        e0 = make_eval_ਵਿਅੰਜਕ(e_ਆਖਰੀ, 1, e1, e2);
        ਜੇ (!e0) {
            av_ਵਿਅੰਜਕ_free(e1);
            av_ਵਿਅੰਜਕ_free(e2);
            ਵਾਪਸ AVERROR(ENOMEM);
        }
    };

    p->ਢੇਰ_ਸੂਚਕਾਂਕ++;
    *e = e0;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ verify_ਵਿਅੰਜਕ(AVExpr *e)
{
    ਜੇ (!e) ਵਾਪਸ 0;
    ਚੋਣ (e->type) {
        ਹਾਲਤ e_ਮੁੱਲ:
        ਹਾਲਤ e_const: ਵਾਪਸ 1;
        ਹਾਲਤ e_func0:
        ਹਾਲਤ e_func1:
        ਹਾਲਤ e_squish:
        ਹਾਲਤ e_ld:
        ਹਾਲਤ e_gauss:
        ਹਾਲਤ e_isnan:
        ਹਾਲਤ e_isinf:
        ਹਾਲਤ e_floor:
        ਹਾਲਤ e_ceil:
        ਹਾਲਤ e_trunc:
        ਹਾਲਤ e_ਗੇੜਾ:
        ਹਾਲਤ e_sqrt:
        ਹਾਲਤ e_not:
        ਹਾਲਤ e_random:
        ਹਾਲਤ e_sgn:
            ਵਾਪਸ verify_ਵਿਅੰਜਕ(e->param[0]) && !e->param[1];
        ਹਾਲਤ e_print:
            ਵਾਪਸ verify_ਵਿਅੰਜਕ(e->param[0])
                   && (!e->param[1] || verify_ਵਿਅੰਜਕ(e->param[1]));
        ਹਾਲਤ e_if:
        ਹਾਲਤ e_ifnot:
        ਹਾਲਤ e_taylor:
            ਵਾਪਸ verify_ਵਿਅੰਜਕ(e->param[0]) && verify_ਵਿਅੰਜਕ(e->param[1])
                   && (!e->param[2] || verify_ਵਿਅੰਜਕ(e->param[2]));
        ਹਾਲਤ e_between:
        ਹਾਲਤ e_clip:
        ਹਾਲਤ e_lerp:
        ਹਾਲਤ e_randomi:
            ਵਾਪਸ verify_ਵਿਅੰਜਕ(e->param[0]) &&
                   verify_ਵਿਅੰਜਕ(e->param[1]) &&
                   verify_ਵਿਅੰਜਕ(e->param[2]);
        ਮੂਲ: ਵਾਪਸ verify_ਵਿਅੰਜਕ(e->param[0]) && verify_ਵਿਅੰਜਕ(e->param[1]) && !e->param[2];
    }
}

ਪੂਰਨ av_ਵਿਅੰਜਕ_parse(AVExpr **ਵਿਅੰਜਕ, ਅਚਲ ਅੱਖਰ *s,
                  ਅਚਲ ਅੱਖਰ * ਅਚਲ *const_ਨਾਂ,
                  ਅਚਲ ਅੱਖਰ * ਅਚਲ *func1_ਨਾਂ, ਦੁੱਗਣਾ (* ਅਚਲ *funcs1)(ਖਾਲੀ *, ਦੁੱਗਣਾ),
                  ਅਚਲ ਅੱਖਰ * ਅਚਲ *func2_ਨਾਂ, ਦੁੱਗਣਾ (* ਅਚਲ *funcs2)(ਖਾਲੀ *, ਦੁੱਗਣਾ, ਦੁੱਗਣਾ),
                  ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ਨਿਰਾ;
    ਅੱਖਰ *w = av_malloc(ਲੜੀ_ਲੰਬਾਈ(s) + 1);
    ਅੱਖਰ *wp = w;
    ਅਚਲ ਅੱਖਰ *s0 = s;
    ਪੂਰਨ ret = 0;

    ਜੇ (!w)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਜਦੋਂ (*s)
        ਜੇ (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ਢੇਰ_ਸੂਚਕਾਂਕ=100;
    p.s= w;
    p.const_ਨਾਂ = const_ਨਾਂ;
    p.funcs1      = funcs1;
    p.func1_ਨਾਂ = func1_ਨਾਂ;
    p.funcs2      = funcs2;
    p.func2_ਨਾਂ = func2_ਨਾਂ;
    p.log_ਵਿੱਥ = log_ਵਿੱਥ;
    p.log_ctx    = log_ctx;

    ਜੇ ((ret = parse_ਵਿਅੰਜਕ(&e, &p)) < 0)
        ਜਾਓ ਸਿਰਾ;
    ਜੇ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        ਜਾਓ ਸਿਰਾ;
    }
    ਜੇ (!verify_ਵਿਅੰਜਕ(e)) {
        ret = AVERROR(EINVAL);
        ਜਾਓ ਸਿਰਾ;
    }
    AVExpr_ਜੜ੍ਹ *r = av_realloc(e, ਆਕਾਰ(*r));
    ਜੇ (!r) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ ਸਿਰਾ;
    }
    e = (AVExpr*)r;
    e->ਜੜ੍ਹ = 1;
    r->var= av_mallocz(ਆਕਾਰ(ਦੁੱਗਣਾ) *VARS);
    r->prng_state = av_mallocz(ਆਕਾਰ(*r->prng_state) *VARS);
    ਜੇ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ ਸਿਰਾ;
    }
    *ਵਿਅੰਜਕ = e;
    e = ਨਿਰਾ;
ਸਿਰਾ:
    av_ਵਿਅੰਜਕ_free(e);
    av_free(w);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ ਵਿਅੰਜਕ_ਗਿਣਤੀ(AVExpr *e, ਬਿਨਾਨਿਸ਼ਾਨੀ *counter, ਪੂਰਨ ਮਾਪ, ਪੂਰਨ type)
{
    ਪੂਰਨ i;

    ਜੇ (!e || !counter || !ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    ਲਈ (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        ਵਿਅੰਜਕ_ਗਿਣਤੀ(e->param[i], counter, ਮਾਪ, type);

    ਜੇ (e->type == type && e->const_ਸੂਚਕਾਂਕ < ਮਾਪ)
        counter[e->const_ਸੂਚਕਾਂਕ]++;

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਵਿਅੰਜਕ_ਗਿਣਤੀ_vars(AVExpr *e, ਬਿਨਾਨਿਸ਼ਾਨੀ *counter, ਪੂਰਨ ਮਾਪ)
{
    ਵਾਪਸ ਵਿਅੰਜਕ_ਗਿਣਤੀ(e, counter, ਮਾਪ, e_const);
}

ਪੂਰਨ av_ਵਿਅੰਜਕ_ਗਿਣਤੀ_func(AVExpr *e, ਬਿਨਾਨਿਸ਼ਾਨੀ *counter, ਪੂਰਨ ਮਾਪ, ਪੂਰਨ arg)
{
    ਵਾਪਸ ਵਿਅੰਜਕ_ਗਿਣਤੀ(e, counter, ਮਾਪ, ((ਪੂਰਨ[]){e_const, e_func1, e_func2})[arg]);
}

ਦੁੱਗਣਾ av_ਵਿਅੰਜਕ_eval(AVExpr *e, ਅਚਲ ਦੁੱਗਣਾ *const_ਮੁੱਲਾਂ, ਖਾਲੀ *opaque)
{
    av_assert1(e->ਜੜ੍ਹ);
    AVExpr_ਜੜ੍ਹ *r = (AVExpr_ਜੜ੍ਹ *)e;
    Parser p = {
        .class        = &eval_class,
        .const_ਮੁੱਲਾਂ = const_ਮੁੱਲਾਂ,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    ਵਾਪਸ eval_ਵਿਅੰਜਕ(&p, e);
}

ਪੂਰਨ av_ਵਿਅੰਜਕ_parse_and_eval(ਦੁੱਗਣਾ *d, ਅਚਲ ਅੱਖਰ *s,
                           ਅਚਲ ਅੱਖਰ * ਅਚਲ *const_ਨਾਂ, ਅਚਲ ਦੁੱਗਣਾ *const_ਮੁੱਲਾਂ,
                           ਅਚਲ ਅੱਖਰ * ਅਚਲ *func1_ਨਾਂ, ਦੁੱਗਣਾ (* ਅਚਲ *funcs1)(ਖਾਲੀ *, ਦੁੱਗਣਾ),
                           ਅਚਲ ਅੱਖਰ * ਅਚਲ *func2_ਨਾਂ, ਦੁੱਗਣਾ (* ਅਚਲ *funcs2)(ਖਾਲੀ *, ਦੁੱਗਣਾ, ਦੁੱਗਣਾ),
                           ਖਾਲੀ *opaque, ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    AVExpr *e = ਨਿਰਾ;
    ਪੂਰਨ ret = av_ਵਿਅੰਜਕ_parse(&e, s, const_ਨਾਂ, func1_ਨਾਂ, funcs1, func2_ਨਾਂ, funcs2, log_ਵਿੱਥ, log_ctx);

    ਜੇ (ret < 0) {
        *d = NAN;
        ਵਾਪਸ ret;
    }
    *d = av_ਵਿਅੰਜਕ_eval(e, const_ਮੁੱਲਾਂ, opaque);
    av_ਵਿਅੰਜਕ_free(e);
    ਵਾਪਸ isnan(*d) ? AVERROR(EINVAL) : 0;
}
