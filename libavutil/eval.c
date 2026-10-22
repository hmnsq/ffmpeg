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

#অন্তর্ভাব <float.h>
#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "avutil.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "eval.h"
#অন্তর্ভাব "ffmath.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "mathematics.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "sfc64.h"
#অন্তর্ভাব "time.h"
#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "reverse.h"

#define MAX_DEPTH 100

প্রকারলেখ কাঠামো Parser {
    ধ্রুবক AVClass *class;
    পূর্ণসংখ্যা স্তূপ_সূচক;
    অক্ষর *s;
    ধ্রুবক দ্বিগুণ *const_মানসমূহ;
    ধ্রুবক অক্ষর * ধ্রুবক *const_names;          // NULL terminated
    দ্বিগুণ (* ধ্রুবক *funcs1)(শূন্য *, দ্বিগুণ a);           // NULL terminated
    ধ্রুবক অক্ষর * ধ্রুবক *func1_names;          // NULL terminated
    দ্বিগুণ (* ধ্রুবক *funcs2)(শূন্য *, দ্বিগুণ a, দ্বিগুণ b); // NULL terminated
    ধ্রুবক অক্ষর * ধ্রুবক *func2_names;          // NULL terminated
    শূন্য *opaque;
    পূর্ণসংখ্যা log_offset;
    শূন্য *log_ctx;
#define VARS 10
    দ্বিগুণ *var;
    FFSFC64 *prng_state;
} Parser;

স্থির ধ্রুবক AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = ফাঁকা,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

স্থির ধ্রুবক কাঠামো {
    দ্বিগুণ bin_val;
    দ্বিগুণ dec_val;
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

স্থির ধ্রুবক কাঠামো {
    ধ্রুবক অক্ষর *name;
    দ্বিগুণ মান;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

দ্বিগুণ av_strtod(ধ্রুবক অক্ষর *numstr, অক্ষর **লেজ)
{
    দ্বিগুণ d;
    অক্ষর *পরবর্তী;
    যদি(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &পরবর্তী, 16);
    } অন্যথা
        d = strtod(numstr, &পরবর্তী);
    /* if parsing succeeded, check for and interpret postfixes */
    যদি (পরবর্তী!=numstr) {
        যদি (পরবর্তী[0] == 'd' && পরবর্তী[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            পরবর্তী += 2;
        } অন্যথা যদি (*পরবর্তী >= 'E' && *পরবর্তী <= 'z') {
            পূর্ণসংখ্যা e= si_prefixes[*পরবর্তী - 'E'].exp;
            যদি (e) {
                যদি (পরবর্তী[1] == 'i') {
                    d*= si_prefixes[*পরবর্তী - 'E'].bin_val;
                    পরবর্তী+=2;
                } অন্যথা {
                    d*= si_prefixes[*পরবর্তী - 'E'].dec_val;
                    পরবর্তী++;
                }
            }
        }

        যদি (*পরবর্তী=='B') {
            d*=8;
            পরবর্তী++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    যদি (লেজ)
        *লেজ = পরবর্তী;
    ফেরত d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

স্থির পূর্ণসংখ্যা strmatch(ধ্রুবক অক্ষর *s, ধ্রুবক অক্ষর *prefix)
{
    পূর্ণসংখ্যা i;
    জন্য (i=0; prefix[i]; i++) {
        যদি (prefix[i] != s[i]) ফেরত 0;
    }
    /* return 1 only if the s identifier is terminated */
    ফেরত !IS_IDENTIFIER_CHAR(s[i]);
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
কাঠামো AVExpr {
    unsigned অক্ষর type;
    unsigned অক্ষর মূল;
    short depth;
    পূর্ণসংখ্যা const_সূচক;
    দ্বিগুণ মান; // is sign in other types
    সংঘ {
        দ্বিগুণ (*func0)(দ্বিগুণ);
        দ্বিগুণ (*func1)(শূন্য *, দ্বিগুণ);
        দ্বিগুণ (*func2)(শূন্য *, দ্বিগুণ, দ্বিগুণ);
    } ;
    কাঠামো AVExpr *param[3];
};

প্রকারলেখ কাঠামো {
    AVExpr avexpr;
    দ্বিগুণ *var;
    FFSFC64 *prng_state;
} AVExpr_মূল;

স্থির দ্বিগুণ etime(দ্বিগুণ v)
{
    ফেরত av_gettime() * 0.000001;
}

স্থির দ্বিগুণ eval_রাশিমালা(Parser *p, AVExpr *e)
{
    নির্বাচন (e->type) {
        ক্ষেত্র e_মান:  ফেরত e->মান;
        ক্ষেত্র e_const:  ফেরত e->মান * p->const_মানসমূহ[e->const_সূচক];
        ক্ষেত্র e_func0:  ফেরত e->মান * e->func0(eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_func1:  ফেরত e->মান * e->func1(p->opaque, eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_func2:  ফেরত e->মান * e->func2(p->opaque, eval_রাশিমালা(p, e->param[0]), eval_রাশিমালা(p, e->param[1]));
        ক্ষেত্র e_squish: ফেরত e->মান/(1+exp(4*eval_রাশিমালা(p, e->param[0])));
        ক্ষেত্র e_gauss: { দ্বিগুণ d = eval_রাশিমালা(p, e->param[0]); ফেরত e->মান * exp(-d*d/2)/sqrt(2*M_PI); }
        ক্ষেত্র e_ld:     ফেরত e->মান * p->var[av_clip(eval_রাশিমালা(p, e->param[0]), 0, VARS-1)];
        ক্ষেত্র e_isnan:  ফেরত e->মান * !!isnan(eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_isinf:  ফেরত e->মান * !!isinf(eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_floor:  ফেরত e->মান * floor(eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_ceil :  ফেরত e->মান * ceil (eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_trunc:  ফেরত e->মান * trunc(eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_round:  ফেরত e->মান * round(eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_sgn:    ফেরত e->মান * FFDIFFSIGN(eval_রাশিমালা(p, e->param[0]), 0);
        ক্ষেত্র e_sqrt:   ফেরত e->মান * sqrt (eval_রাশিমালা(p, e->param[0]));
        ক্ষেত্র e_not:    ফেরত e->মান * (eval_রাশিমালা(p, e->param[0]) == 0);
        ক্ষেত্র e_if:     ফেরত e->মান * (eval_রাশিমালা(p, e->param[0]) ? eval_রাশিমালা(p, e->param[1]) :
                                          e->param[2] ? eval_রাশিমালা(p, e->param[2]) : 0);
        ক্ষেত্র e_ifnot:  ফেরত e->মান * (!eval_রাশিমালা(p, e->param[0]) ? eval_রাশিমালা(p, e->param[1]) :
                                          e->param[2] ? eval_রাশিমালা(p, e->param[2]) : 0);
        ক্ষেত্র e_clip: {
            দ্বিগুণ x = eval_রাশিমালা(p, e->param[0]);
            দ্বিগুণ min = eval_রাশিমালা(p, e->param[1]), max = eval_রাশিমালা(p, e->param[2]);
            যদি (isnan(min) || isnan(max) || isnan(x) || min > max)
                ফেরত NAN;
            ফেরত e->মান * av_clipd(x, min, max);
        }
        ক্ষেত্র e_between: {
            দ্বিগুণ d = eval_রাশিমালা(p, e->param[0]);
            ফেরত e->মান * (d >= eval_রাশিমালা(p, e->param[1]) &&
                               d <= eval_রাশিমালা(p, e->param[2]));
        }
        ক্ষেত্র e_lerp: {
            দ্বিগুণ v0 = eval_রাশিমালা(p, e->param[0]);
            দ্বিগুণ v1 = eval_রাশিমালা(p, e->param[1]);
            দ্বিগুণ f  = eval_রাশিমালা(p, e->param[2]);
            ফেরত e->মান * (v0 + (v1 - v0) * f);
        }
        ক্ষেত্র e_print: {
            দ্বিগুণ x = eval_রাশিমালা(p, e->param[0]);
            পূর্ণসংখ্যা level = e->param[1] ? av_clip(eval_রাশিমালা(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            ফেরত e->মান * x;
        }

#define COMPUTE_পরবর্তী_RANDOM()                                        \
            পূর্ণসংখ্যা idx = av_clip(eval_রাশিমালা(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            যদি (!s->গণক) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        ক্ষেত্র e_random: {
            COMPUTE_পরবর্তী_RANDOM();
            ফেরত r * (1.0/UINT64_MAX);
        }
        ক্ষেত্র e_randomi: {
            দ্বিগুণ min = eval_রাশিমালা(p, e->param[1]);
            দ্বিগুণ max = eval_রাশিমালা(p, e->param[2]);
            COMPUTE_পরবর্তী_RANDOM();
            ফেরত min + (max - min) * r / UINT64_MAX;
        }
        ক্ষেত্র e_while: {
            দ্বিগুণ d = NAN;
            যখন (eval_রাশিমালা(p, e->param[0]))
                d=eval_রাশিমালা(p, e->param[1]);
            ফেরত d;
        }
        ক্ষেত্র e_taylor: {
            দ্বিগুণ t = 1, d = 0, v;
            দ্বিগুণ x = eval_রাশিমালা(p, e->param[1]);
            পূর্ণসংখ্যা id = e->param[2] ? av_clip(eval_রাশিমালা(p, e->param[2]), 0, VARS-1) : 0;
            পূর্ণসংখ্যা i;
            দ্বিগুণ var0 = p->var[id];
            জন্য(i=0; i<1000; i++) {
                দ্বিগুণ ld = d;
                p->var[id] = i;
                v = eval_রাশিমালা(p, e->param[0]);
                d += t*v;
                যদি(ld==d && v)
                    বিরতি;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            ফেরত d;
        }
        ক্ষেত্র e_মূল: {
            পূর্ণসংখ্যা i, j;
            দ্বিগুণ নিচের = -1, উপরের = -1, v, নিচের_v = -DBL_MAX, উপরের_v = DBL_MAX;
            দ্বিগুণ var0 = p->var[0];
            দ্বিগুণ x_max = eval_রাশিমালা(p, e->param[1]);
            জন্য(i=-1; i<1024; i++) {
                যদি(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } অন্যথা {
                    p->var[0] = x_max*pow(0.9, i-255);
                    যদি (i&1) p->var[0] *= -1;
                    যদি (i&2) p->var[0] += নিচের;
                    অন্যথা     p->var[0] += উপরের;
                }
                v = eval_রাশিমালা(p, e->param[0]);
                যদি (v<=0 && v>নিচের_v) {
                    নিচের    = p->var[0];
                    নিচের_v  = v;
                }
                যদি (v>=0 && v<উপরের_v) {
                    উপরের   = p->var[0];
                    উপরের_v = v;
                }
                যদি (নিচের>=0 && উপরের>=0){
                    জন্য (j=0; j<1000; j++) {
                        p->var[0] = (নিচের+উপরের)*0.5;
                        যদি (নিচের == p->var[0] || উপরের == p->var[0])
                            বিরতি;
                        v = eval_রাশিমালা(p, e->param[0]);
                        যদি (v<=0) নিচের = p->var[0];
                        যদি (v>=0) উপরের= p->var[0];
                        যদি (isnan(v)) {
                            নিচের = উপরের = v;
                            বিরতি;
                        }
                    }
                    বিরতি;
                }
            }
            p->var[0] = var0;
            ফেরত -নিচের_v<উপরের_v ? নিচের : উপরের;
        }
        পূর্বনির্ধারিত: {
            দ্বিগুণ d = eval_রাশিমালা(p, e->param[0]);
            দ্বিগুণ d2 = eval_রাশিমালা(p, e->param[1]);
            নির্বাচন (e->type) {
                ক্ষেত্র e_mod: ফেরত e->মান * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                ক্ষেত্র e_gcd: ফেরত e->মান * av_gcd(d,d2);
                ক্ষেত্র e_max: ফেরত e->মান * (d >  d2 ?   d : d2);
                ক্ষেত্র e_min: ফেরত e->মান * (d <  d2 ?   d : d2);
                ক্ষেত্র e_eq:  ফেরত e->মান * (d == d2 ? 1.0 : 0.0);
                ক্ষেত্র e_gt:  ফেরত e->মান * (d >  d2 ? 1.0 : 0.0);
                ক্ষেত্র e_gte: ফেরত e->মান * (d >= d2 ? 1.0 : 0.0);
                ক্ষেত্র e_lt:  ফেরত e->মান * (d <  d2 ? 1.0 : 0.0);
                ক্ষেত্র e_lte: ফেরত e->মান * (d <= d2 ? 1.0 : 0.0);
                ক্ষেত্র e_pow: ফেরত e->মান * pow(d, d2);
                ক্ষেত্র e_mul: ফেরত e->মান * (d * d2);
                ক্ষেত্র e_div: ফেরত e->মান * (d2 ? (d / d2) : d * INFINITY);
                ক্ষেত্র e_add: ফেরত e->মান * (d + d2);
                ক্ষেত্র e_last:ফেরত e->মান * d2;
                ক্ষেত্র e_st :  {
                    পূর্ণসংখ্যা সূচক = av_clip(d, 0, VARS-1);
                    p->prng_state[সূচক].গণক = 0;
                    ফেরত e->মান * (p->var[সূচক]= d2);
                }
                ক্ষেত্র e_hypot:ফেরত e->মান * hypot(d, d2);
                ক্ষেত্র e_atan2:ফেরত e->মান * atan2(d, d2);
                ক্ষেত্র e_bitand: ফেরত isnan(d) || isnan(d2) ? NAN : e->মান * ((long পূর্ণসংখ্যা)d & (long পূর্ণসংখ্যা)d2);
                ক্ষেত্র e_bitor:  ফেরত isnan(d) || isnan(d2) ? NAN : e->মান * ((long পূর্ণসংখ্যা)d | (long পূর্ণসংখ্যা)d2);
            }
        }
    }
    ফেরত NAN;
}

স্থির পূর্ণসংখ্যা parse_রাশিমালা(AVExpr **e, Parser *p);

শূন্য av_রাশিমালা_free(AVExpr *e)
{
    যদি (!e) ফেরত;
    av_রাশিমালা_free(e->param[0]);
    av_রাশিমালা_free(e->param[1]);
    av_রাশিমালা_free(e->param[2]);
    যদি (e->মূল) {
        AVExpr_মূল *r = (AVExpr_মূল*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

স্থির পূর্ণসংখ্যা parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(আকার(AVExpr));
    অক্ষর *পরবর্তী = p->s, *s0 = p->s;
    পূর্ণসংখ্যা ret, i;

    যদি (!d)
        ফেরত AVERROR(ENOMEM);

    /*সংখ্যা*/
    d->মান = av_strtod(p->s, &পরবর্তী);
    যদি (পরবর্তী != p->s) {
        d->type = e_মান;
        p->s= পরবর্তী;
        *e = d;
        ফেরত 0;
    }
    d->মান = 1;

    /* named constants */
    জন্য (i=0; p->const_names && p->const_names[i]; i++) {
        যদি (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_সূচক = i;
            *e = d;
            ফেরত 0;
        }
    }
    জন্য (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        যদি (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_মান;
            d->মান = constants[i].মান;
            *e = d;
            ফেরত 0;
        }
    }

    p->s= strchr(p->s, '(');
    যদি (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= পরবর্তী;
        av_রাশিমালা_free(d);
        ফেরত AVERROR(EINVAL);
    }
    p->s++; // "("
    যদি (*পরবর্তী == '(') { // special case do-nothing
        av_freep(&d);
        যদি ((ret = parse_রাশিমালা(&d, p)) < 0)
            ফেরত ret;
        যদি (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_রাশিমালা_free(d);
            ফেরত AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        ফেরত 0;
    }
    যদি ((ret = parse_রাশিমালা(&(d->param[0]), p)) < 0) {
        av_রাশিমালা_free(d);
        ফেরত ret;
    }
    যদি (p->s[0]== ',') {
        p->s++; // ","
        parse_রাশিমালা(&d->param[1], p);
    }
    যদি (p->s[0]== ',') {
        p->s++; // ","
        parse_রাশিমালা(&d->param[2], p);
    }
    যদি (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_রাশিমালা_free(d);
        ফেরত AVERROR(EINVAL);
    }
    p->s++; // ")"

    জন্য (পূর্ণসংখ্যা i = 0; i<3; i++)
        যদি (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    যদি (d->depth > MAX_DEPTH) {
        av_রাশিমালা_free(d);
        ফেরত AVERROR(EINVAL);
    }

    d->type = e_func0;
         যদি (strmatch(পরবর্তী, "sinh"  )) d->func0 = sinh;
    অন্যথা যদি (strmatch(পরবর্তী, "cosh"  )) d->func0 = cosh;
    অন্যথা যদি (strmatch(পরবর্তী, "tanh"  )) d->func0 = tanh;
    অন্যথা যদি (strmatch(পরবর্তী, "sin"   )) d->func0 = sin;
    অন্যথা যদি (strmatch(পরবর্তী, "cos"   )) d->func0 = cos;
    অন্যথা যদি (strmatch(পরবর্তী, "tan"   )) d->func0 = tan;
    অন্যথা যদি (strmatch(পরবর্তী, "atan"  )) d->func0 = atan;
    অন্যথা যদি (strmatch(পরবর্তী, "asin"  )) d->func0 = asin;
    অন্যথা যদি (strmatch(পরবর্তী, "acos"  )) d->func0 = acos;
    অন্যথা যদি (strmatch(পরবর্তী, "exp"   )) d->func0 = exp;
    অন্যথা যদি (strmatch(পরবর্তী, "log"   )) d->func0 = log;
    অন্যথা যদি (strmatch(পরবর্তী, "abs"   )) d->func0 = fabs;
    অন্যথা যদি (strmatch(পরবর্তী, "time"  )) d->func0 = etime;
    অন্যথা যদি (strmatch(পরবর্তী, "squish")) d->type = e_squish;
    অন্যথা যদি (strmatch(পরবর্তী, "gauss" )) d->type = e_gauss;
    অন্যথা যদি (strmatch(পরবর্তী, "mod"   )) d->type = e_mod;
    অন্যথা যদি (strmatch(পরবর্তী, "max"   )) d->type = e_max;
    অন্যথা যদি (strmatch(পরবর্তী, "min"   )) d->type = e_min;
    অন্যথা যদি (strmatch(পরবর্তী, "eq"    )) d->type = e_eq;
    অন্যথা যদি (strmatch(পরবর্তী, "gte"   )) d->type = e_gte;
    অন্যথা যদি (strmatch(পরবর্তী, "gt"    )) d->type = e_gt;
    অন্যথা যদি (strmatch(পরবর্তী, "lte"   )) d->type = e_lte;
    অন্যথা যদি (strmatch(পরবর্তী, "lt"    )) d->type = e_lt;
    অন্যথা যদি (strmatch(পরবর্তী, "ld"    )) d->type = e_ld;
    অন্যথা যদি (strmatch(পরবর্তী, "isnan" )) d->type = e_isnan;
    অন্যথা যদি (strmatch(পরবর্তী, "isinf" )) d->type = e_isinf;
    অন্যথা যদি (strmatch(পরবর্তী, "st"    )) d->type = e_st;
    অন্যথা যদি (strmatch(পরবর্তী, "while" )) d->type = e_while;
    অন্যথা যদি (strmatch(পরবর্তী, "taylor")) d->type = e_taylor;
    অন্যথা যদি (strmatch(পরবর্তী, "root"  )) d->type = e_মূল;
    অন্যথা যদি (strmatch(পরবর্তী, "floor" )) d->type = e_floor;
    অন্যথা যদি (strmatch(পরবর্তী, "ceil"  )) d->type = e_ceil;
    অন্যথা যদি (strmatch(পরবর্তী, "trunc" )) d->type = e_trunc;
    অন্যথা যদি (strmatch(পরবর্তী, "round" )) d->type = e_round;
    অন্যথা যদি (strmatch(পরবর্তী, "sqrt"  )) d->type = e_sqrt;
    অন্যথা যদি (strmatch(পরবর্তী, "not"   )) d->type = e_not;
    অন্যথা যদি (strmatch(পরবর্তী, "pow"   )) d->type = e_pow;
    অন্যথা যদি (strmatch(পরবর্তী, "print" )) d->type = e_print;
    অন্যথা যদি (strmatch(পরবর্তী, "random")) d->type = e_random;
    অন্যথা যদি (strmatch(পরবর্তী, "randomi")) d->type = e_randomi;
    অন্যথা যদি (strmatch(পরবর্তী, "hypot" )) d->type = e_hypot;
    অন্যথা যদি (strmatch(পরবর্তী, "gcd"   )) d->type = e_gcd;
    অন্যথা যদি (strmatch(পরবর্তী, "if"    )) d->type = e_if;
    অন্যথা যদি (strmatch(পরবর্তী, "ifnot" )) d->type = e_ifnot;
    অন্যথা যদি (strmatch(পরবর্তী, "bitand")) d->type = e_bitand;
    অন্যথা যদি (strmatch(পরবর্তী, "bitor" )) d->type = e_bitor;
    অন্যথা যদি (strmatch(পরবর্তী, "between"))d->type = e_between;
    অন্যথা যদি (strmatch(পরবর্তী, "clip"  )) d->type = e_clip;
    অন্যথা যদি (strmatch(পরবর্তী, "atan2" )) d->type = e_atan2;
    অন্যথা যদি (strmatch(পরবর্তী, "lerp"  )) d->type = e_lerp;
    অন্যথা যদি (strmatch(পরবর্তী, "sgn"   )) d->type = e_sgn;
    অন্যথা {
        জন্য (i=0; p->func1_names && p->func1_names[i]; i++) {
            যদি (strmatch(পরবর্তী, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_সূচক = i;
                *e = d;
                ফেরত 0;
            }
        }

        জন্য (i=0; p->func2_names && p->func2_names[i]; i++) {
            যদি (strmatch(পরবর্তী, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_সূচক = i;
                *e = d;
                ফেরত 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_রাশিমালা_free(d);
        ফেরত AVERROR(EINVAL);
    }

    *e = d;
    ফেরত 0;
}

স্থির AVExpr *make_eval_রাশিমালা(পূর্ণসংখ্যা type, পূর্ণসংখ্যা মান, AVExpr *p0, AVExpr *p1)
{
    পূর্ণসংখ্যা depth = FFMAX(p0->depth, p1->depth) + 1;
    যদি (depth > MAX_DEPTH)
        ফেরত ফাঁকা;
    AVExpr *e = av_mallocz(আকার(AVExpr));
    যদি (!e)
        ফেরত ফাঁকা;
    e->type     =type   ;
    e->মান    =মান  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    ফেরত e;
}

স্থির পূর্ণসংখ্যা parse_pow(AVExpr **e, Parser *p, পূর্ণসংখ্যা *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    ফেরত parse_primary(e, p);
}

স্থির পূর্ণসংখ্যা parse_dB(AVExpr **e, Parser *p, পূর্ণসংখ্যা *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    যদি (*p->s == '-') {
        অক্ষর *পরবর্তী;
        av_unused দ্বিগুণ ignored = strtod(p->s, &পরবর্তী);
        যদি (পরবর্তী != p->s && পরবর্তী[0] == 'd' && পরবর্তী[1] == 'B') {
            *sign = 0;
            ফেরত parse_primary(e, p);
        }
    }
    ফেরত parse_pow(e, p, sign);
}

স্থির পূর্ণসংখ্যা parse_factor(AVExpr **e, Parser *p)
{
    পূর্ণসংখ্যা sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    যদি ((ret = parse_dB(&e0, p, &sign)) < 0)
        ফেরত ret;
    যখন(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        যদি ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_রাশিমালা_free(e1);
            ফেরত ret;
        }
        e0 = make_eval_রাশিমালা(e_pow, 1, e1, e2);
        যদি (!e0) {
            av_রাশিমালা_free(e1);
            av_রাশিমালা_free(e2);
            ফেরত AVERROR(ENOMEM);
        }
        যদি (e0->param[1]) e0->param[1]->মান *= (sign2|1);
    }
    যদি (e0) e0->মান *= (sign|1);

    *e = e0;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা parse_term(AVExpr **e, Parser *p)
{
    পূর্ণসংখ্যা ret;
    AVExpr *e0, *e1, *e2;
    যদি ((ret = parse_factor(&e0, p)) < 0)
        ফেরত ret;
    যখন (p->s[0]=='*' || p->s[0]=='/') {
        পূর্ণসংখ্যা c= *p->s++;
        e1 = e0;
        যদি ((ret = parse_factor(&e2, p)) < 0) {
            av_রাশিমালা_free(e1);
            ফেরত ret;
        }
        e0 = make_eval_রাশিমালা(c == '*' ? e_mul : e_div, 1, e1, e2);
        যদি (!e0) {
            av_রাশিমালা_free(e1);
            av_রাশিমালা_free(e2);
            ফেরত AVERROR(ENOMEM);
        }
    }
    *e = e0;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা parse_subexpr(AVExpr **e, Parser *p)
{
    পূর্ণসংখ্যা ret;
    AVExpr *e0, *e1, *e2;
    যদি ((ret = parse_term(&e0, p)) < 0)
        ফেরত ret;
    যখন (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        যদি ((ret = parse_term(&e2, p)) < 0) {
            av_রাশিমালা_free(e1);
            ফেরত ret;
        }
        e0 = make_eval_রাশিমালা(e_add, 1, e1, e2);
        যদি (!e0) {
            av_রাশিমালা_free(e1);
            av_রাশিমালা_free(e2);
            ফেরত AVERROR(ENOMEM);
        }
    };

    *e = e0;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা parse_রাশিমালা(AVExpr **e, Parser *p)
{
    পূর্ণসংখ্যা ret;
    AVExpr *e0, *e1, *e2;
    যদি (p->স্তূপ_সূচক <= 0) //protect against stack overflows
        ফেরত AVERROR(EINVAL);
    p->স্তূপ_সূচক--;

    যদি ((ret = parse_subexpr(&e0, p)) < 0)
        ফেরত ret;
    যখন (*p->s == ';') {
        p->s++;
        e1 = e0;
        যদি ((ret = parse_subexpr(&e2, p)) < 0) {
            av_রাশিমালা_free(e1);
            ফেরত ret;
        }
        e0 = make_eval_রাশিমালা(e_last, 1, e1, e2);
        যদি (!e0) {
            av_রাশিমালা_free(e1);
            av_রাশিমালা_free(e2);
            ফেরত AVERROR(ENOMEM);
        }
    };

    p->স্তূপ_সূচক++;
    *e = e0;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা verify_রাশিমালা(AVExpr *e)
{
    যদি (!e) ফেরত 0;
    নির্বাচন (e->type) {
        ক্ষেত্র e_মান:
        ক্ষেত্র e_const: ফেরত 1;
        ক্ষেত্র e_func0:
        ক্ষেত্র e_func1:
        ক্ষেত্র e_squish:
        ক্ষেত্র e_ld:
        ক্ষেত্র e_gauss:
        ক্ষেত্র e_isnan:
        ক্ষেত্র e_isinf:
        ক্ষেত্র e_floor:
        ক্ষেত্র e_ceil:
        ক্ষেত্র e_trunc:
        ক্ষেত্র e_round:
        ক্ষেত্র e_sqrt:
        ক্ষেত্র e_not:
        ক্ষেত্র e_random:
        ক্ষেত্র e_sgn:
            ফেরত verify_রাশিমালা(e->param[0]) && !e->param[1];
        ক্ষেত্র e_print:
            ফেরত verify_রাশিমালা(e->param[0])
                   && (!e->param[1] || verify_রাশিমালা(e->param[1]));
        ক্ষেত্র e_if:
        ক্ষেত্র e_ifnot:
        ক্ষেত্র e_taylor:
            ফেরত verify_রাশিমালা(e->param[0]) && verify_রাশিমালা(e->param[1])
                   && (!e->param[2] || verify_রাশিমালা(e->param[2]));
        ক্ষেত্র e_between:
        ক্ষেত্র e_clip:
        ক্ষেত্র e_lerp:
        ক্ষেত্র e_randomi:
            ফেরত verify_রাশিমালা(e->param[0]) &&
                   verify_রাশিমালা(e->param[1]) &&
                   verify_রাশিমালা(e->param[2]);
        পূর্বনির্ধারিত: ফেরত verify_রাশিমালা(e->param[0]) && verify_রাশিমালা(e->param[1]) && !e->param[2];
    }
}

পূর্ণসংখ্যা av_রাশিমালা_parse(AVExpr **রাশিমালা, ধ্রুবক অক্ষর *s,
                  ধ্রুবক অক্ষর * ধ্রুবক *const_names,
                  ধ্রুবক অক্ষর * ধ্রুবক *func1_names, দ্বিগুণ (* ধ্রুবক *funcs1)(শূন্য *, দ্বিগুণ),
                  ধ্রুবক অক্ষর * ধ্রুবক *func2_names, দ্বিগুণ (* ধ্রুবক *funcs2)(শূন্য *, দ্বিগুণ, দ্বিগুণ),
                  পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ফাঁকা;
    অক্ষর *w = av_malloc(strlen(s) + 1);
    অক্ষর *wp = w;
    ধ্রুবক অক্ষর *s0 = s;
    পূর্ণসংখ্যা ret = 0;

    যদি (!w)
        ফেরত AVERROR(ENOMEM);

    যখন (*s)
        যদি (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.স্তূপ_সূচক=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    যদি ((ret = parse_রাশিমালা(&e, &p)) < 0)
        যাও end;
    যদি (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        যাও end;
    }
    যদি (!verify_রাশিমালা(e)) {
        ret = AVERROR(EINVAL);
        যাও end;
    }
    AVExpr_মূল *r = av_realloc(e, আকার(*r));
    যদি (!r) {
        ret = AVERROR(ENOMEM);
        যাও end;
    }
    e = (AVExpr*)r;
    e->মূল = 1;
    r->var= av_mallocz(আকার(দ্বিগুণ) *VARS);
    r->prng_state = av_mallocz(আকার(*r->prng_state) *VARS);
    যদি (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        যাও end;
    }
    *রাশিমালা = e;
    e = ফাঁকা;
end:
    av_রাশিমালা_free(e);
    av_free(w);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা রাশিমালা_গুনতি(AVExpr *e, unsigned *গণক, পূর্ণসংখ্যা আকার_2, পূর্ণসংখ্যা type)
{
    পূর্ণসংখ্যা i;

    যদি (!e || !গণক || !আকার_2)
        ফেরত AVERROR(EINVAL);

    জন্য (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        রাশিমালা_গুনতি(e->param[i], গণক, আকার_2, type);

    যদি (e->type == type && e->const_সূচক < আকার_2)
        গণক[e->const_সূচক]++;

    ফেরত 0;
}

পূর্ণসংখ্যা av_রাশিমালা_গুনতি_vars(AVExpr *e, unsigned *গণক, পূর্ণসংখ্যা আকার_2)
{
    ফেরত রাশিমালা_গুনতি(e, গণক, আকার_2, e_const);
}

পূর্ণসংখ্যা av_রাশিমালা_গুনতি_func(AVExpr *e, unsigned *গণক, পূর্ণসংখ্যা আকার_2, পূর্ণসংখ্যা arg)
{
    ফেরত রাশিমালা_গুনতি(e, গণক, আকার_2, ((পূর্ণসংখ্যা[]){e_const, e_func1, e_func2})[arg]);
}

দ্বিগুণ av_রাশিমালা_eval(AVExpr *e, ধ্রুবক দ্বিগুণ *const_মানসমূহ, শূন্য *opaque)
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

    ফেরত eval_রাশিমালা(&p, e);
}

পূর্ণসংখ্যা av_রাশিমালা_parse_and_eval(দ্বিগুণ *d, ধ্রুবক অক্ষর *s,
                           ধ্রুবক অক্ষর * ধ্রুবক *const_names, ধ্রুবক দ্বিগুণ *const_মানসমূহ,
                           ধ্রুবক অক্ষর * ধ্রুবক *func1_names, দ্বিগুণ (* ধ্রুবক *funcs1)(শূন্য *, দ্বিগুণ),
                           ধ্রুবক অক্ষর * ধ্রুবক *func2_names, দ্বিগুণ (* ধ্রুবক *funcs2)(শূন্য *, দ্বিগুণ, দ্বিগুণ),
                           শূন্য *opaque, পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    AVExpr *e = ফাঁকা;
    পূর্ণসংখ্যা ret = av_রাশিমালা_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    যদি (ret < 0) {
        *d = NAN;
        ফেরত ret;
    }
    *d = av_রাশিমালা_eval(e, const_মানসমূহ, opaque);
    av_রাশিমালা_free(e);
    ফেরত isnan(*d) ? AVERROR(EINVAL) : 0;
}
