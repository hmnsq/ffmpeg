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

#అన్తర్భావ <float.h>
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "avutil.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "eval.h"
#అన్తర్భావ "ffmath.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mathematics.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "sfc64.h"
#అన్తర్భావ "time.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "reverse.h"

#నిర్వచించు MAX_లోతు 100

రకనిర్వచనం నిర్మాణం Parser {
    స్థిరరాశి AVClass *class;
    పూర్ణాంకం దొంతర_సూచీ;
    అక్షరం *s;
    స్థిరరాశి ద్విగుణ *const_విలువలు;
    స్థిరరాశి అక్షరం * స్థిరరాశి *const_పేర్లు;          // NULL terminated
    ద్విగుణ (* స్థిరరాశి *funcs1)(శూన్య *, ద్విగుణ a);           // NULL terminated
    స్థిరరాశి అక్షరం * స్థిరరాశి *func1_పేర్లు;          // NULL terminated
    ద్విగుణ (* స్థిరరాశి *funcs2)(శూన్య *, ద్విగుణ a, ద్విగుణ b); // NULL terminated
    స్థిరరాశి అక్షరం * స్థిరరాశి *func2_పేర్లు;          // NULL terminated
    శూన్య *opaque;
    పూర్ణాంకం log_స్థానభ్రంశం;
    శూన్య *log_ctx;
#నిర్వచించు VARS 10
    ద్విగుణ *var;
    FFSFC64 *prng_state;
} Parser;

స్థిర స్థిరరాశి AVClass eval_class = {
    .class_name                = "Eval",
    .అంశం_name                 = av_default_అంశం_name,
    .option                    = ఖాళీ,
    .సంస్కరణ                   = LIBAVUTIL_సంస్కరణ_INT,
    .log_level_స్థానభ్రంశం_స్థానభ్రంశం   = offsetof(Parser, log_స్థానభ్రంశం),
    .మాతృ_log_context_స్థానభ్రంశం = offsetof(Parser, log_ctx),
};

స్థిర స్థిరరాశి నిర్మాణం {
    ద్విగుణ bin_val;
    ద్విగుణ dec_val;
    int8_t ఘాతాంకం;
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

స్థిర స్థిరరాశి నిర్మాణం {
    స్థిరరాశి అక్షరం *name;
    ద్విగుణ విలువ;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

ద్విగుణ av_strtod(స్థిరరాశి అక్షరం *numstr, అక్షరం **తోక)
{
    ద్విగుణ d;
    అక్షరం *తదుపరి;
    ఒకవేళ(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &తదుపరి, 16);
    } లేకపోతే
        d = strtod(numstr, &తదుపరి);
    /* if parsing succeeded, check for and interpret postfixes */
    ఒకవేళ (తదుపరి!=numstr) {
        ఒకవేళ (తదుపరి[0] == 'd' && తదుపరి[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            తదుపరి += 2;
        } లేకపోతే ఒకవేళ (*తదుపరి >= 'E' && *తదుపరి <= 'z') {
            పూర్ణాంకం e= si_prefixes[*తదుపరి - 'E'].ఘాతాంకం;
            ఒకవేళ (e) {
                ఒకవేళ (తదుపరి[1] == 'i') {
                    d*= si_prefixes[*తదుపరి - 'E'].bin_val;
                    తదుపరి+=2;
                } లేకపోతే {
                    d*= si_prefixes[*తదుపరి - 'E'].dec_val;
                    తదుపరి++;
                }
            }
        }

        ఒకవేళ (*తదుపరి=='B') {
            d*=8;
            తదుపరి++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    ఒకవేళ (తోక)
        *తోక = తదుపరి;
    తిరిగి d;
}

#నిర్వచించు IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

స్థిర పూర్ణాంకం strmatch(స్థిరరాశి అక్షరం *s, స్థిరరాశి అక్షరం *ఉపసర్గ)
{
    పూర్ణాంకం i;
    కొరకు (i=0; ఉపసర్గ[i]; i++) {
        ఒకవేళ (ఉపసర్గ[i] != s[i]) తిరిగి 0;
    }
    /* return 1 only if the s identifier is terminated */
    తిరిగి !IS_IDENTIFIER_CHAR(s[i]);
}

గణన {
    e_విలువ, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_కూడు,
    e_చివరి, e_st, e_while, e_taylor, e_మూలం, e_floor, e_ceil, e_trunc, e_విడత,
    e_sqrt, e_not, e_random, e_hypot, e_గరిష్ఠ_సామాన్య_భాజకం,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
నిర్మాణం AVExpr {
    గుర్తులేని అక్షరం type;
    గుర్తులేని అక్షరం మూలం;
    పొట్టి లోతు;
    పూర్ణాంకం const_సూచీ;
    ద్విగుణ విలువ; // is sign in other types
    సంఘం {
        ద్విగుణ (*func0)(ద్విగుణ);
        ద్విగుణ (*func1)(శూన్య *, ద్విగుణ);
        ద్విగుణ (*func2)(శూన్య *, ద్విగుణ, ద్విగుణ);
    } ;
    నిర్మాణం AVExpr *param[3];
};

రకనిర్వచనం నిర్మాణం {
    AVExpr avexpr;
    ద్విగుణ *var;
    FFSFC64 *prng_state;
} AVExpr_మూలం;

స్థిర ద్విగుణ etime(ద్విగుణ v)
{
    తిరిగి av_gettime() * 0.000001;
}

స్థిర ద్విగుణ eval_సమాసం(Parser *p, AVExpr *e)
{
    ఎంపిక (e->type) {
        స్థితి e_విలువ:  తిరిగి e->విలువ;
        స్థితి e_const:  తిరిగి e->విలువ * p->const_విలువలు[e->const_సూచీ];
        స్థితి e_func0:  తిరిగి e->విలువ * e->func0(eval_సమాసం(p, e->param[0]));
        స్థితి e_func1:  తిరిగి e->విలువ * e->func1(p->opaque, eval_సమాసం(p, e->param[0]));
        స్థితి e_func2:  తిరిగి e->విలువ * e->func2(p->opaque, eval_సమాసం(p, e->param[0]), eval_సమాసం(p, e->param[1]));
        స్థితి e_squish: తిరిగి e->విలువ/(1+ఘాతాంకం(4*eval_సమాసం(p, e->param[0])));
        స్థితి e_gauss: { ద్విగుణ d = eval_సమాసం(p, e->param[0]); తిరిగి e->విలువ * ఘాతాంకం(-d*d/2)/వర్గమూలం(2*M_PI); }
        స్థితి e_ld:     తిరిగి e->విలువ * p->var[av_clip(eval_సమాసం(p, e->param[0]), 0, VARS-1)];
        స్థితి e_isnan:  తిరిగి e->విలువ * !!isnan(eval_సమాసం(p, e->param[0]));
        స్థితి e_isinf:  తిరిగి e->విలువ * !!isinf(eval_సమాసం(p, e->param[0]));
        స్థితి e_floor:  తిరిగి e->విలువ * floor(eval_సమాసం(p, e->param[0]));
        స్థితి e_ceil :  తిరిగి e->విలువ * ceil (eval_సమాసం(p, e->param[0]));
        స్థితి e_trunc:  తిరిగి e->విలువ * trunc(eval_సమాసం(p, e->param[0]));
        స్థితి e_విడత:  తిరిగి e->విలువ * round(eval_సమాసం(p, e->param[0]));
        స్థితి e_sgn:    తిరిగి e->విలువ * FFDIFFSIGN(eval_సమాసం(p, e->param[0]), 0);
        స్థితి e_sqrt:   తిరిగి e->విలువ * వర్గమూలం (eval_సమాసం(p, e->param[0]));
        స్థితి e_not:    తిరిగి e->విలువ * (eval_సమాసం(p, e->param[0]) == 0);
        స్థితి e_if:     తిరిగి e->విలువ * (eval_సమాసం(p, e->param[0]) ? eval_సమాసం(p, e->param[1]) :
                                          e->param[2] ? eval_సమాసం(p, e->param[2]) : 0);
        స్థితి e_ifnot:  తిరిగి e->విలువ * (!eval_సమాసం(p, e->param[0]) ? eval_సమాసం(p, e->param[1]) :
                                          e->param[2] ? eval_సమాసం(p, e->param[2]) : 0);
        స్థితి e_clip: {
            ద్విగుణ x = eval_సమాసం(p, e->param[0]);
            ద్విగుణ min = eval_సమాసం(p, e->param[1]), max = eval_సమాసం(p, e->param[2]);
            ఒకవేళ (isnan(min) || isnan(max) || isnan(x) || min > max)
                తిరిగి NAN;
            తిరిగి e->విలువ * av_clipd(x, min, max);
        }
        స్థితి e_between: {
            ద్విగుణ d = eval_సమాసం(p, e->param[0]);
            తిరిగి e->విలువ * (d >= eval_సమాసం(p, e->param[1]) &&
                               d <= eval_సమాసం(p, e->param[2]));
        }
        స్థితి e_lerp: {
            ద్విగుణ v0 = eval_సమాసం(p, e->param[0]);
            ద్విగుణ v1 = eval_సమాసం(p, e->param[1]);
            ద్విగుణ f  = eval_సమాసం(p, e->param[2]);
            తిరిగి e->విలువ * (v0 + (v1 - v0) * f);
        }
        స్థితి e_print: {
            ద్విగుణ x = eval_సమాసం(p, e->param[0]);
            పూర్ణాంకం level = e->param[1] ? av_clip(eval_సమాసం(p, e->param[1]), INT_MIN, గరిష్ఠ_పూర్ణాంకం) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            తిరిగి e->విలువ * x;
        }

#నిర్వచించు COMPUTE_తదుపరి_RANDOM()                                        \
            పూర్ణాంకం idx = av_clip(eval_సమాసం(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            ఒకవేళ (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        స్థితి e_random: {
            COMPUTE_తదుపరి_RANDOM();
            తిరిగి r * (1.0/UINT64_MAX);
        }
        స్థితి e_randomi: {
            ద్విగుణ min = eval_సమాసం(p, e->param[1]);
            ద్విగుణ max = eval_సమాసం(p, e->param[2]);
            COMPUTE_తదుపరి_RANDOM();
            తిరిగి min + (max - min) * r / UINT64_MAX;
        }
        స్థితి e_while: {
            ద్విగుణ d = NAN;
            అయితే (eval_సమాసం(p, e->param[0]))
                d=eval_సమాసం(p, e->param[1]);
            తిరిగి d;
        }
        స్థితి e_taylor: {
            ద్విగుణ t = 1, d = 0, v;
            ద్విగుణ x = eval_సమాసం(p, e->param[1]);
            పూర్ణాంకం id = e->param[2] ? av_clip(eval_సమాసం(p, e->param[2]), 0, VARS-1) : 0;
            పూర్ణాంకం i;
            ద్విగుణ var0 = p->var[id];
            కొరకు(i=0; i<1000; i++) {
                ద్విగుణ ld = d;
                p->var[id] = i;
                v = eval_సమాసం(p, e->param[0]);
                d += t*v;
                ఒకవేళ(ld==d && v)
                    ఆపు;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            తిరిగి d;
        }
        స్థితి e_మూలం: {
            పూర్ణాంకం i, j;
            ద్విగుణ దిగువ = -1, ఎగువ = -1, v, దిగువ_v = -DBL_MAX, ఎగువ_v = DBL_MAX;
            ద్విగుణ var0 = p->var[0];
            ద్విగుణ x_max = eval_సమాసం(p, e->param[1]);
            కొరకు(i=-1; i<1024; i++) {
                ఒకవేళ(i<255) {
                    p->var[0] = ff_తిరగేయి[i&255]*x_max/255;
                } లేకపోతే {
                    p->var[0] = x_max*ఘాతం(0.9, i-255);
                    ఒకవేళ (i&1) p->var[0] *= -1;
                    ఒకవేళ (i&2) p->var[0] += దిగువ;
                    లేకపోతే     p->var[0] += ఎగువ;
                }
                v = eval_సమాసం(p, e->param[0]);
                ఒకవేళ (v<=0 && v>దిగువ_v) {
                    దిగువ    = p->var[0];
                    దిగువ_v  = v;
                }
                ఒకవేళ (v>=0 && v<ఎగువ_v) {
                    ఎగువ   = p->var[0];
                    ఎగువ_v = v;
                }
                ఒకవేళ (దిగువ>=0 && ఎగువ>=0){
                    కొరకు (j=0; j<1000; j++) {
                        p->var[0] = (దిగువ+ఎగువ)*0.5;
                        ఒకవేళ (దిగువ == p->var[0] || ఎగువ == p->var[0])
                            ఆపు;
                        v = eval_సమాసం(p, e->param[0]);
                        ఒకవేళ (v<=0) దిగువ = p->var[0];
                        ఒకవేళ (v>=0) ఎగువ= p->var[0];
                        ఒకవేళ (isnan(v)) {
                            దిగువ = ఎగువ = v;
                            ఆపు;
                        }
                    }
                    ఆపు;
                }
            }
            p->var[0] = var0;
            తిరిగి -దిగువ_v<ఎగువ_v ? దిగువ : ఎగువ;
        }
        అప్రమేయ: {
            ద్విగుణ d = eval_సమాసం(p, e->param[0]);
            ద్విగుణ d2 = eval_సమాసం(p, e->param[1]);
            ఎంపిక (e->type) {
                స్థితి e_mod: తిరిగి e->విలువ * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                స్థితి e_గరిష్ఠ_సామాన్య_భాజకం: తిరిగి e->విలువ * av_గరిష్ఠ_సామాన్య_భాజకం(d,d2);
                స్థితి e_max: తిరిగి e->విలువ * (d >  d2 ?   d : d2);
                స్థితి e_min: తిరిగి e->విలువ * (d <  d2 ?   d : d2);
                స్థితి e_eq:  తిరిగి e->విలువ * (d == d2 ? 1.0 : 0.0);
                స్థితి e_gt:  తిరిగి e->విలువ * (d >  d2 ? 1.0 : 0.0);
                స్థితి e_gte: తిరిగి e->విలువ * (d >= d2 ? 1.0 : 0.0);
                స్థితి e_lt:  తిరిగి e->విలువ * (d <  d2 ? 1.0 : 0.0);
                స్థితి e_lte: తిరిగి e->విలువ * (d <= d2 ? 1.0 : 0.0);
                స్థితి e_pow: తిరిగి e->విలువ * ఘాతం(d, d2);
                స్థితి e_mul: తిరిగి e->విలువ * (d * d2);
                స్థితి e_div: తిరిగి e->విలువ * (d2 ? (d / d2) : d * INFINITY);
                స్థితి e_కూడు: తిరిగి e->విలువ * (d + d2);
                స్థితి e_చివరి:తిరిగి e->విలువ * d2;
                స్థితి e_st :  {
                    పూర్ణాంకం సూచీ = av_clip(d, 0, VARS-1);
                    p->prng_state[సూచీ].counter = 0;
                    తిరిగి e->విలువ * (p->var[సూచీ]= d2);
                }
                స్థితి e_hypot:తిరిగి e->విలువ * hypot(d, d2);
                స్థితి e_atan2:తిరిగి e->విలువ * atan2(d, d2);
                స్థితి e_bitand: తిరిగి isnan(d) || isnan(d2) ? NAN : e->విలువ * ((దీర్ఘ పూర్ణాంకం)d & (దీర్ఘ పూర్ణాంకం)d2);
                స్థితి e_bitor:  తిరిగి isnan(d) || isnan(d2) ? NAN : e->విలువ * ((దీర్ఘ పూర్ణాంకం)d | (దీర్ఘ పూర్ణాంకం)d2);
            }
        }
    }
    తిరిగి NAN;
}

స్థిర పూర్ణాంకం parse_సమాసం(AVExpr **e, Parser *p);

శూన్య av_సమాసం_free(AVExpr *e)
{
    ఒకవేళ (!e) తిరిగి;
    av_సమాసం_free(e->param[0]);
    av_సమాసం_free(e->param[1]);
    av_సమాసం_free(e->param[2]);
    ఒకవేళ (e->మూలం) {
        AVExpr_మూలం *r = (AVExpr_మూలం*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

స్థిర పూర్ణాంకం parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(పరిమాణం(AVExpr));
    అక్షరం *తదుపరి = p->s, *s0 = p->s;
    పూర్ణాంకం ret, i;

    ఒకవేళ (!d)
        తిరిగి AVERROR(ENOMEM);

    /*సంఖ్య*/
    d->విలువ = av_strtod(p->s, &తదుపరి);
    ఒకవేళ (తదుపరి != p->s) {
        d->type = e_విలువ;
        p->s= తదుపరి;
        *e = d;
        తిరిగి 0;
    }
    d->విలువ = 1;

    /* named constants */
    కొరకు (i=0; p->const_పేర్లు && p->const_పేర్లు[i]; i++) {
        ఒకవేళ (strmatch(p->s, p->const_పేర్లు[i])) {
            p->s+= అక్షరశ్రేణి_పొడవు(p->const_పేర్లు[i]);
            d->type = e_const;
            d->const_సూచీ = i;
            *e = d;
            తిరిగి 0;
        }
    }
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        ఒకవేళ (strmatch(p->s, constants[i].name)) {
            p->s += అక్షరశ్రేణి_పొడవు(constants[i].name);
            d->type = e_విలువ;
            d->విలువ = constants[i].విలువ;
            *e = d;
            తిరిగి 0;
        }
    }

    p->s= strchr(p->s, '(');
    ఒకవేళ (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= తదుపరి;
        av_సమాసం_free(d);
        తిరిగి AVERROR(EINVAL);
    }
    p->s++; // "("
    ఒకవేళ (*తదుపరి == '(') { // special case do-nothing
        av_freep(&d);
        ఒకవేళ ((ret = parse_సమాసం(&d, p)) < 0)
            తిరిగి ret;
        ఒకవేళ (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_సమాసం_free(d);
            తిరిగి AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        తిరిగి 0;
    }
    ఒకవేళ ((ret = parse_సమాసం(&(d->param[0]), p)) < 0) {
        av_సమాసం_free(d);
        తిరిగి ret;
    }
    ఒకవేళ (p->s[0]== ',') {
        p->s++; // ","
        parse_సమాసం(&d->param[1], p);
    }
    ఒకవేళ (p->s[0]== ',') {
        p->s++; // ","
        parse_సమాసం(&d->param[2], p);
    }
    ఒకవేళ (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_సమాసం_free(d);
        తిరిగి AVERROR(EINVAL);
    }
    p->s++; // ")"

    కొరకు (పూర్ణాంకం i = 0; i<3; i++)
        ఒకవేళ (d->param[i])
            d->లోతు = FFMAX(d->లోతు, d->param[i]->లోతు+1);
    ఒకవేళ (d->లోతు > MAX_లోతు) {
        av_సమాసం_free(d);
        తిరిగి AVERROR(EINVAL);
    }

    d->type = e_func0;
         ఒకవేళ (strmatch(తదుపరి, "sinh"  )) d->func0 = sinh;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "cosh"  )) d->func0 = cosh;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "tanh"  )) d->func0 = tanh;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "sin"   )) d->func0 = జ్యా;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "cos"   )) d->func0 = కోజ్యా;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "tan"   )) d->func0 = tan;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "atan"  )) d->func0 = atan;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "asin"  )) d->func0 = asin;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "acos"  )) d->func0 = acos;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "exp"   )) d->func0 = ఘాతాంకం;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "log"   )) d->func0 = సంవర్గమానం;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "abs"   )) d->func0 = fabs;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "time"  )) d->func0 = etime;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "squish")) d->type = e_squish;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "gauss" )) d->type = e_gauss;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "mod"   )) d->type = e_mod;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "max"   )) d->type = e_max;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "min"   )) d->type = e_min;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "eq"    )) d->type = e_eq;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "gte"   )) d->type = e_gte;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "gt"    )) d->type = e_gt;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "lte"   )) d->type = e_lte;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "lt"    )) d->type = e_lt;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "ld"    )) d->type = e_ld;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "isnan" )) d->type = e_isnan;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "isinf" )) d->type = e_isinf;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "st"    )) d->type = e_st;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "while" )) d->type = e_while;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "taylor")) d->type = e_taylor;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "root"  )) d->type = e_మూలం;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "floor" )) d->type = e_floor;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "ceil"  )) d->type = e_ceil;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "trunc" )) d->type = e_trunc;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "round" )) d->type = e_విడత;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "sqrt"  )) d->type = e_sqrt;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "not"   )) d->type = e_not;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "pow"   )) d->type = e_pow;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "print" )) d->type = e_print;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "random")) d->type = e_random;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "randomi")) d->type = e_randomi;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "hypot" )) d->type = e_hypot;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "gcd"   )) d->type = e_గరిష్ఠ_సామాన్య_భాజకం;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "if"    )) d->type = e_if;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "ifnot" )) d->type = e_ifnot;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "bitand")) d->type = e_bitand;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "bitor" )) d->type = e_bitor;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "between"))d->type = e_between;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "clip"  )) d->type = e_clip;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "atan2" )) d->type = e_atan2;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "lerp"  )) d->type = e_lerp;
    లేకపోతే ఒకవేళ (strmatch(తదుపరి, "sgn"   )) d->type = e_sgn;
    లేకపోతే {
        కొరకు (i=0; p->func1_పేర్లు && p->func1_పేర్లు[i]; i++) {
            ఒకవేళ (strmatch(తదుపరి, p->func1_పేర్లు[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_సూచీ = i;
                *e = d;
                తిరిగి 0;
            }
        }

        కొరకు (i=0; p->func2_పేర్లు && p->func2_పేర్లు[i]; i++) {
            ఒకవేళ (strmatch(తదుపరి, p->func2_పేర్లు[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_సూచీ = i;
                *e = d;
                తిరిగి 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_సమాసం_free(d);
        తిరిగి AVERROR(EINVAL);
    }

    *e = d;
    తిరిగి 0;
}

స్థిర AVExpr *make_eval_సమాసం(పూర్ణాంకం type, పూర్ణాంకం విలువ, AVExpr *p0, AVExpr *p1)
{
    పూర్ణాంకం లోతు = FFMAX(p0->లోతు, p1->లోతు) + 1;
    ఒకవేళ (లోతు > MAX_లోతు)
        తిరిగి ఖాళీ;
    AVExpr *e = av_mallocz(పరిమాణం(AVExpr));
    ఒకవేళ (!e)
        తిరిగి ఖాళీ;
    e->type     =type   ;
    e->విలువ    =విలువ  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->లోతు    = లోతు;
    తిరిగి e;
}

స్థిర పూర్ణాంకం parse_pow(AVExpr **e, Parser *p, పూర్ణాంకం *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    తిరిగి parse_primary(e, p);
}

స్థిర పూర్ణాంకం parse_dB(AVExpr **e, Parser *p, పూర్ణాంకం *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    ఒకవేళ (*p->s == '-') {
        అక్షరం *తదుపరి;
        av_వాడని ద్విగుణ ignored = strtod(p->s, &తదుపరి);
        ఒకవేళ (తదుపరి != p->s && తదుపరి[0] == 'd' && తదుపరి[1] == 'B') {
            *sign = 0;
            తిరిగి parse_primary(e, p);
        }
    }
    తిరిగి parse_pow(e, p, sign);
}

స్థిర పూర్ణాంకం parse_గుణకం(AVExpr **e, Parser *p)
{
    పూర్ణాంకం sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    ఒకవేళ ((ret = parse_dB(&e0, p, &sign)) < 0)
        తిరిగి ret;
    అయితే(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        ఒకవేళ ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_సమాసం_free(e1);
            తిరిగి ret;
        }
        e0 = make_eval_సమాసం(e_pow, 1, e1, e2);
        ఒకవేళ (!e0) {
            av_సమాసం_free(e1);
            av_సమాసం_free(e2);
            తిరిగి AVERROR(ENOMEM);
        }
        ఒకవేళ (e0->param[1]) e0->param[1]->విలువ *= (sign2|1);
    }
    ఒకవేళ (e0) e0->విలువ *= (sign|1);

    *e = e0;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం parse_పదం(AVExpr **e, Parser *p)
{
    పూర్ణాంకం ret;
    AVExpr *e0, *e1, *e2;
    ఒకవేళ ((ret = parse_గుణకం(&e0, p)) < 0)
        తిరిగి ret;
    అయితే (p->s[0]=='*' || p->s[0]=='/') {
        పూర్ణాంకం c= *p->s++;
        e1 = e0;
        ఒకవేళ ((ret = parse_గుణకం(&e2, p)) < 0) {
            av_సమాసం_free(e1);
            తిరిగి ret;
        }
        e0 = make_eval_సమాసం(c == '*' ? e_mul : e_div, 1, e1, e2);
        ఒకవేళ (!e0) {
            av_సమాసం_free(e1);
            av_సమాసం_free(e2);
            తిరిగి AVERROR(ENOMEM);
        }
    }
    *e = e0;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం parse_subexpr(AVExpr **e, Parser *p)
{
    పూర్ణాంకం ret;
    AVExpr *e0, *e1, *e2;
    ఒకవేళ ((ret = parse_పదం(&e0, p)) < 0)
        తిరిగి ret;
    అయితే (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        ఒకవేళ ((ret = parse_పదం(&e2, p)) < 0) {
            av_సమాసం_free(e1);
            తిరిగి ret;
        }
        e0 = make_eval_సమాసం(e_కూడు, 1, e1, e2);
        ఒకవేళ (!e0) {
            av_సమాసం_free(e1);
            av_సమాసం_free(e2);
            తిరిగి AVERROR(ENOMEM);
        }
    };

    *e = e0;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం parse_సమాసం(AVExpr **e, Parser *p)
{
    పూర్ణాంకం ret;
    AVExpr *e0, *e1, *e2;
    ఒకవేళ (p->దొంతర_సూచీ <= 0) //protect against stack overflows
        తిరిగి AVERROR(EINVAL);
    p->దొంతర_సూచీ--;

    ఒకవేళ ((ret = parse_subexpr(&e0, p)) < 0)
        తిరిగి ret;
    అయితే (*p->s == ';') {
        p->s++;
        e1 = e0;
        ఒకవేళ ((ret = parse_subexpr(&e2, p)) < 0) {
            av_సమాసం_free(e1);
            తిరిగి ret;
        }
        e0 = make_eval_సమాసం(e_చివరి, 1, e1, e2);
        ఒకవేళ (!e0) {
            av_సమాసం_free(e1);
            av_సమాసం_free(e2);
            తిరిగి AVERROR(ENOMEM);
        }
    };

    p->దొంతర_సూచీ++;
    *e = e0;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం verify_సమాసం(AVExpr *e)
{
    ఒకవేళ (!e) తిరిగి 0;
    ఎంపిక (e->type) {
        స్థితి e_విలువ:
        స్థితి e_const: తిరిగి 1;
        స్థితి e_func0:
        స్థితి e_func1:
        స్థితి e_squish:
        స్థితి e_ld:
        స్థితి e_gauss:
        స్థితి e_isnan:
        స్థితి e_isinf:
        స్థితి e_floor:
        స్థితి e_ceil:
        స్థితి e_trunc:
        స్థితి e_విడత:
        స్థితి e_sqrt:
        స్థితి e_not:
        స్థితి e_random:
        స్థితి e_sgn:
            తిరిగి verify_సమాసం(e->param[0]) && !e->param[1];
        స్థితి e_print:
            తిరిగి verify_సమాసం(e->param[0])
                   && (!e->param[1] || verify_సమాసం(e->param[1]));
        స్థితి e_if:
        స్థితి e_ifnot:
        స్థితి e_taylor:
            తిరిగి verify_సమాసం(e->param[0]) && verify_సమాసం(e->param[1])
                   && (!e->param[2] || verify_సమాసం(e->param[2]));
        స్థితి e_between:
        స్థితి e_clip:
        స్థితి e_lerp:
        స్థితి e_randomi:
            తిరిగి verify_సమాసం(e->param[0]) &&
                   verify_సమాసం(e->param[1]) &&
                   verify_సమాసం(e->param[2]);
        అప్రమేయ: తిరిగి verify_సమాసం(e->param[0]) && verify_సమాసం(e->param[1]) && !e->param[2];
    }
}

పూర్ణాంకం av_సమాసం_parse(AVExpr **సమాసం, స్థిరరాశి అక్షరం *s,
                  స్థిరరాశి అక్షరం * స్థిరరాశి *const_పేర్లు,
                  స్థిరరాశి అక్షరం * స్థిరరాశి *func1_పేర్లు, ద్విగుణ (* స్థిరరాశి *funcs1)(శూన్య *, ద్విగుణ),
                  స్థిరరాశి అక్షరం * స్థిరరాశి *func2_పేర్లు, ద్విగుణ (* స్థిరరాశి *funcs2)(శూన్య *, ద్విగుణ, ద్విగుణ),
                  పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ఖాళీ;
    అక్షరం *w = av_malloc(అక్షరశ్రేణి_పొడవు(s) + 1);
    అక్షరం *wp = w;
    స్థిరరాశి అక్షరం *s0 = s;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (!w)
        తిరిగి AVERROR(ENOMEM);

    అయితే (*s)
        ఒకవేళ (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.దొంతర_సూచీ=100;
    p.s= w;
    p.const_పేర్లు = const_పేర్లు;
    p.funcs1      = funcs1;
    p.func1_పేర్లు = func1_పేర్లు;
    p.funcs2      = funcs2;
    p.func2_పేర్లు = func2_పేర్లు;
    p.log_స్థానభ్రంశం = log_స్థానభ్రంశం;
    p.log_ctx    = log_ctx;

    ఒకవేళ ((ret = parse_సమాసం(&e, &p)) < 0)
        వెళ్ళు చివర;
    ఒకవేళ (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        వెళ్ళు చివర;
    }
    ఒకవేళ (!verify_సమాసం(e)) {
        ret = AVERROR(EINVAL);
        వెళ్ళు చివర;
    }
    AVExpr_మూలం *r = av_realloc(e, పరిమాణం(*r));
    ఒకవేళ (!r) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు చివర;
    }
    e = (AVExpr*)r;
    e->మూలం = 1;
    r->var= av_mallocz(పరిమాణం(ద్విగుణ) *VARS);
    r->prng_state = av_mallocz(పరిమాణం(*r->prng_state) *VARS);
    ఒకవేళ (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు చివర;
    }
    *సమాసం = e;
    e = ఖాళీ;
చివర:
    av_సమాసం_free(e);
    av_free(w);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం సమాసం_లెక్క(AVExpr *e, గుర్తులేని *counter, పూర్ణాంకం కొలత, పూర్ణాంకం type)
{
    పూర్ణాంకం i;

    ఒకవేళ (!e || !counter || !కొలత)
        తిరిగి AVERROR(EINVAL);

    కొరకు (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        సమాసం_లెక్క(e->param[i], counter, కొలత, type);

    ఒకవేళ (e->type == type && e->const_సూచీ < కొలత)
        counter[e->const_సూచీ]++;

    తిరిగి 0;
}

పూర్ణాంకం av_సమాసం_లెక్క_vars(AVExpr *e, గుర్తులేని *counter, పూర్ణాంకం కొలత)
{
    తిరిగి సమాసం_లెక్క(e, counter, కొలత, e_const);
}

పూర్ణాంకం av_సమాసం_లెక్క_func(AVExpr *e, గుర్తులేని *counter, పూర్ణాంకం కొలత, పూర్ణాంకం arg)
{
    తిరిగి సమాసం_లెక్క(e, counter, కొలత, ((పూర్ణాంకం[]){e_const, e_func1, e_func2})[arg]);
}

ద్విగుణ av_సమాసం_eval(AVExpr *e, స్థిరరాశి ద్విగుణ *const_విలువలు, శూన్య *opaque)
{
    av_assert1(e->మూలం);
    AVExpr_మూలం *r = (AVExpr_మూలం *)e;
    Parser p = {
        .class        = &eval_class,
        .const_విలువలు = const_విలువలు,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    తిరిగి eval_సమాసం(&p, e);
}

పూర్ణాంకం av_సమాసం_parse_and_eval(ద్విగుణ *d, స్థిరరాశి అక్షరం *s,
                           స్థిరరాశి అక్షరం * స్థిరరాశి *const_పేర్లు, స్థిరరాశి ద్విగుణ *const_విలువలు,
                           స్థిరరాశి అక్షరం * స్థిరరాశి *func1_పేర్లు, ద్విగుణ (* స్థిరరాశి *funcs1)(శూన్య *, ద్విగుణ),
                           స్థిరరాశి అక్షరం * స్థిరరాశి *func2_పేర్లు, ద్విగుణ (* స్థిరరాశి *funcs2)(శూన్య *, ద్విగుణ, ద్విగుణ),
                           శూన్య *opaque, పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    AVExpr *e = ఖాళీ;
    పూర్ణాంకం ret = av_సమాసం_parse(&e, s, const_పేర్లు, func1_పేర్లు, funcs1, func2_పేర్లు, funcs2, log_స్థానభ్రంశం, log_ctx);

    ఒకవేళ (ret < 0) {
        *d = NAN;
        తిరిగి ret;
    }
    *d = av_సమాసం_eval(e, const_విలువలు, opaque);
    av_సమాసం_free(e);
    తిరిగి isnan(*d) ? AVERROR(EINVAL) : 0;
}
