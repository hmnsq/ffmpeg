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

#અન્તર્ભાવ <float.h>
#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "avutil.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "eval.h"
#અન્તર્ભાવ "ffmath.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "mathematics.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "sfc64.h"
#અન્તર્ભાવ "time.h"
#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "reverse.h"

#define MAX_DEPTH 100

પ્રકારવ્યાખ્યા સંરચના Parser {
    અચલ AVClass *class;
    પૂર્ણાંક ઢગલો_index;
    અક્ષર *s;
    અચલ દ્વિગુણ *const_કિંમતો;
    અચલ અક્ષર * અચલ *const_names;          // NULL terminated
    દ્વિગુણ (* અચલ *funcs1)(શૂન્ય *, દ્વિગુણ a);           // NULL terminated
    અચલ અક્ષર * અચલ *func1_names;          // NULL terminated
    દ્વિગુણ (* અચલ *funcs2)(શૂન્ય *, દ્વિગુણ a, દ્વિગુણ b); // NULL terminated
    અચલ અક્ષર * અચલ *func2_names;          // NULL terminated
    શૂન્ય *opaque;
    પૂર્ણાંક log_offset;
    શૂન્ય *log_ctx;
#define VARS 10
    દ્વિગુણ *var;
    FFSFC64 *prng_state;
} Parser;

સ્થિર અચલ AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = ખાલી,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

સ્થિર અચલ સંરચના {
    દ્વિગુણ bin_val;
    દ્વિગુણ dec_val;
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

સ્થિર અચલ સંરચના {
    અચલ અક્ષર *name;
    દ્વિગુણ કિંમત;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

દ્વિગુણ av_strtod(અચલ અક્ષર *numstr, અક્ષર **tail)
{
    દ્વિગુણ d;
    અક્ષર *next;
    જો(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } નહીંતર
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    જો (next!=numstr) {
        જો (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } નહીંતર જો (*next >= 'E' && *next <= 'z') {
            પૂર્ણાંક e= si_prefixes[*next - 'E'].exp;
            જો (e) {
                જો (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } નહીંતર {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        જો (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    જો (tail)
        *tail = next;
    પાછા d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

સ્થિર પૂર્ણાંક strmatch(અચલ અક્ષર *s, અચલ અક્ષર *prefix)
{
    પૂર્ણાંક i;
    માટે (i=0; prefix[i]; i++) {
        જો (prefix[i] != s[i]) પાછા 0;
    }
    /* return 1 only if the s identifier is terminated */
    પાછા !IS_IDENTIFIER_CHAR(s[i]);
}

ગણના {
    e_કિંમત, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_મૂળ, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
સંરચના AVExpr {
    unsigned અક્ષર type;
    unsigned અક્ષર મૂળ;
    short depth;
    પૂર્ણાંક const_index;
    દ્વિગુણ કિંમત; // is sign in other types
    સંઘ {
        દ્વિગુણ (*func0)(દ્વિગુણ);
        દ્વિગુણ (*func1)(શૂન્ય *, દ્વિગુણ);
        દ્વિગુણ (*func2)(શૂન્ય *, દ્વિગુણ, દ્વિગુણ);
    } ;
    સંરચના AVExpr *param[3];
};

પ્રકારવ્યાખ્યા સંરચના {
    AVExpr avexpr;
    દ્વિગુણ *var;
    FFSFC64 *prng_state;
} AVExpr_મૂળ;

સ્થિર દ્વિગુણ etime(દ્વિગુણ v)
{
    પાછા av_gettime() * 0.000001;
}

સ્થિર દ્વિગુણ eval_પદાવલિ(Parser *p, AVExpr *e)
{
    પસંદગી (e->type) {
        સ્થિતિ e_કિંમત:  પાછા e->કિંમત;
        સ્થિતિ e_const:  પાછા e->કિંમત * p->const_કિંમતો[e->const_index];
        સ્થિતિ e_func0:  પાછા e->કિંમત * e->func0(eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_func1:  પાછા e->કિંમત * e->func1(p->opaque, eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_func2:  પાછા e->કિંમત * e->func2(p->opaque, eval_પદાવલિ(p, e->param[0]), eval_પદાવલિ(p, e->param[1]));
        સ્થિતિ e_squish: પાછા e->કિંમત/(1+exp(4*eval_પદાવલિ(p, e->param[0])));
        સ્થિતિ e_gauss: { દ્વિગુણ d = eval_પદાવલિ(p, e->param[0]); પાછા e->કિંમત * exp(-d*d/2)/sqrt(2*M_PI); }
        સ્થિતિ e_ld:     પાછા e->કિંમત * p->var[av_clip(eval_પદાવલિ(p, e->param[0]), 0, VARS-1)];
        સ્થિતિ e_isnan:  પાછા e->કિંમત * !!isnan(eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_isinf:  પાછા e->કિંમત * !!isinf(eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_floor:  પાછા e->કિંમત * floor(eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_ceil :  પાછા e->કિંમત * ceil (eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_trunc:  પાછા e->કિંમત * trunc(eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_round:  પાછા e->કિંમત * round(eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_sgn:    પાછા e->કિંમત * FFDIFFSIGN(eval_પદાવલિ(p, e->param[0]), 0);
        સ્થિતિ e_sqrt:   પાછા e->કિંમત * sqrt (eval_પદાવલિ(p, e->param[0]));
        સ્થિતિ e_not:    પાછા e->કિંમત * (eval_પદાવલિ(p, e->param[0]) == 0);
        સ્થિતિ e_if:     પાછા e->કિંમત * (eval_પદાવલિ(p, e->param[0]) ? eval_પદાવલિ(p, e->param[1]) :
                                          e->param[2] ? eval_પદાવલિ(p, e->param[2]) : 0);
        સ્થિતિ e_ifnot:  પાછા e->કિંમત * (!eval_પદાવલિ(p, e->param[0]) ? eval_પદાવલિ(p, e->param[1]) :
                                          e->param[2] ? eval_પદાવલિ(p, e->param[2]) : 0);
        સ્થિતિ e_clip: {
            દ્વિગુણ x = eval_પદાવલિ(p, e->param[0]);
            દ્વિગુણ min = eval_પદાવલિ(p, e->param[1]), max = eval_પદાવલિ(p, e->param[2]);
            જો (isnan(min) || isnan(max) || isnan(x) || min > max)
                પાછા NAN;
            પાછા e->કિંમત * av_clipd(x, min, max);
        }
        સ્થિતિ e_between: {
            દ્વિગુણ d = eval_પદાવલિ(p, e->param[0]);
            પાછા e->કિંમત * (d >= eval_પદાવલિ(p, e->param[1]) &&
                               d <= eval_પદાવલિ(p, e->param[2]));
        }
        સ્થિતિ e_lerp: {
            દ્વિગુણ v0 = eval_પદાવલિ(p, e->param[0]);
            દ્વિગુણ v1 = eval_પદાવલિ(p, e->param[1]);
            દ્વિગુણ f  = eval_પદાવલિ(p, e->param[2]);
            પાછા e->કિંમત * (v0 + (v1 - v0) * f);
        }
        સ્થિતિ e_print: {
            દ્વિગુણ x = eval_પદાવલિ(p, e->param[0]);
            પૂર્ણાંક level = e->param[1] ? av_clip(eval_પદાવલિ(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            પાછા e->કિંમત * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            પૂર્ણાંક idx = av_clip(eval_પદાવલિ(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            જો (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        સ્થિતિ e_random: {
            COMPUTE_NEXT_RANDOM();
            પાછા r * (1.0/UINT64_MAX);
        }
        સ્થિતિ e_randomi: {
            દ્વિગુણ min = eval_પદાવલિ(p, e->param[1]);
            દ્વિગુણ max = eval_પદાવલિ(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            પાછા min + (max - min) * r / UINT64_MAX;
        }
        સ્થિતિ e_while: {
            દ્વિગુણ d = NAN;
            જ્યારે (eval_પદાવલિ(p, e->param[0]))
                d=eval_પદાવલિ(p, e->param[1]);
            પાછા d;
        }
        સ્થિતિ e_taylor: {
            દ્વિગુણ t = 1, d = 0, v;
            દ્વિગુણ x = eval_પદાવલિ(p, e->param[1]);
            પૂર્ણાંક id = e->param[2] ? av_clip(eval_પદાવલિ(p, e->param[2]), 0, VARS-1) : 0;
            પૂર્ણાંક i;
            દ્વિગુણ var0 = p->var[id];
            માટે(i=0; i<1000; i++) {
                દ્વિગુણ ld = d;
                p->var[id] = i;
                v = eval_પદાવલિ(p, e->param[0]);
                d += t*v;
                જો(ld==d && v)
                    તોડો;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            પાછા d;
        }
        સ્થિતિ e_મૂળ: {
            પૂર્ણાંક i, j;
            દ્વિગુણ નીચલું = -1, ઉપલું = -1, v, નીચલું_v = -DBL_MAX, ઉપલું_v = DBL_MAX;
            દ્વિગુણ var0 = p->var[0];
            દ્વિગુણ x_max = eval_પદાવલિ(p, e->param[1]);
            માટે(i=-1; i<1024; i++) {
                જો(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } નહીંતર {
                    p->var[0] = x_max*pow(0.9, i-255);
                    જો (i&1) p->var[0] *= -1;
                    જો (i&2) p->var[0] += નીચલું;
                    નહીંતર     p->var[0] += ઉપલું;
                }
                v = eval_પદાવલિ(p, e->param[0]);
                જો (v<=0 && v>નીચલું_v) {
                    નીચલું    = p->var[0];
                    નીચલું_v  = v;
                }
                જો (v>=0 && v<ઉપલું_v) {
                    ઉપલું   = p->var[0];
                    ઉપલું_v = v;
                }
                જો (નીચલું>=0 && ઉપલું>=0){
                    માટે (j=0; j<1000; j++) {
                        p->var[0] = (નીચલું+ઉપલું)*0.5;
                        જો (નીચલું == p->var[0] || ઉપલું == p->var[0])
                            તોડો;
                        v = eval_પદાવલિ(p, e->param[0]);
                        જો (v<=0) નીચલું = p->var[0];
                        જો (v>=0) ઉપલું= p->var[0];
                        જો (isnan(v)) {
                            નીચલું = ઉપલું = v;
                            તોડો;
                        }
                    }
                    તોડો;
                }
            }
            p->var[0] = var0;
            પાછા -નીચલું_v<ઉપલું_v ? નીચલું : ઉપલું;
        }
        મૂળભૂત: {
            દ્વિગુણ d = eval_પદાવલિ(p, e->param[0]);
            દ્વિગુણ d2 = eval_પદાવલિ(p, e->param[1]);
            પસંદગી (e->type) {
                સ્થિતિ e_mod: પાછા e->કિંમત * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                સ્થિતિ e_gcd: પાછા e->કિંમત * av_gcd(d,d2);
                સ્થિતિ e_max: પાછા e->કિંમત * (d >  d2 ?   d : d2);
                સ્થિતિ e_min: પાછા e->કિંમત * (d <  d2 ?   d : d2);
                સ્થિતિ e_eq:  પાછા e->કિંમત * (d == d2 ? 1.0 : 0.0);
                સ્થિતિ e_gt:  પાછા e->કિંમત * (d >  d2 ? 1.0 : 0.0);
                સ્થિતિ e_gte: પાછા e->કિંમત * (d >= d2 ? 1.0 : 0.0);
                સ્થિતિ e_lt:  પાછા e->કિંમત * (d <  d2 ? 1.0 : 0.0);
                સ્થિતિ e_lte: પાછા e->કિંમત * (d <= d2 ? 1.0 : 0.0);
                સ્થિતિ e_pow: પાછા e->કિંમત * pow(d, d2);
                સ્થિતિ e_mul: પાછા e->કિંમત * (d * d2);
                સ્થિતિ e_div: પાછા e->કિંમત * (d2 ? (d / d2) : d * INFINITY);
                સ્થિતિ e_add: પાછા e->કિંમત * (d + d2);
                સ્થિતિ e_last:પાછા e->કિંમત * d2;
                સ્થિતિ e_st :  {
                    પૂર્ણાંક index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    પાછા e->કિંમત * (p->var[index]= d2);
                }
                સ્થિતિ e_hypot:પાછા e->કિંમત * hypot(d, d2);
                સ્થિતિ e_atan2:પાછા e->કિંમત * atan2(d, d2);
                સ્થિતિ e_bitand: પાછા isnan(d) || isnan(d2) ? NAN : e->કિંમત * ((long પૂર્ણાંક)d & (long પૂર્ણાંક)d2);
                સ્થિતિ e_bitor:  પાછા isnan(d) || isnan(d2) ? NAN : e->કિંમત * ((long પૂર્ણાંક)d | (long પૂર્ણાંક)d2);
            }
        }
    }
    પાછા NAN;
}

સ્થિર પૂર્ણાંક parse_પદાવલિ(AVExpr **e, Parser *p);

શૂન્ય av_પદાવલિ_free(AVExpr *e)
{
    જો (!e) પાછા;
    av_પદાવલિ_free(e->param[0]);
    av_પદાવલિ_free(e->param[1]);
    av_પદાવલિ_free(e->param[2]);
    જો (e->મૂળ) {
        AVExpr_મૂળ *r = (AVExpr_મૂળ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

સ્થિર પૂર્ણાંક parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(કદ(AVExpr));
    અક્ષર *next = p->s, *s0 = p->s;
    પૂર્ણાંક ret, i;

    જો (!d)
        પાછા AVERROR(ENOMEM);

    /*સંખ્યા*/
    d->કિંમત = av_strtod(p->s, &next);
    જો (next != p->s) {
        d->type = e_કિંમત;
        p->s= next;
        *e = d;
        પાછા 0;
    }
    d->કિંમત = 1;

    /* named constants */
    માટે (i=0; p->const_names && p->const_names[i]; i++) {
        જો (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            પાછા 0;
        }
    }
    માટે (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        જો (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_કિંમત;
            d->કિંમત = constants[i].કિંમત;
            *e = d;
            પાછા 0;
        }
    }

    p->s= strchr(p->s, '(');
    જો (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_પદાવલિ_free(d);
        પાછા AVERROR(EINVAL);
    }
    p->s++; // "("
    જો (*next == '(') { // special case do-nothing
        av_freep(&d);
        જો ((ret = parse_પદાવલિ(&d, p)) < 0)
            પાછા ret;
        જો (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_પદાવલિ_free(d);
            પાછા AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        પાછા 0;
    }
    જો ((ret = parse_પદાવલિ(&(d->param[0]), p)) < 0) {
        av_પદાવલિ_free(d);
        પાછા ret;
    }
    જો (p->s[0]== ',') {
        p->s++; // ","
        parse_પદાવલિ(&d->param[1], p);
    }
    જો (p->s[0]== ',') {
        p->s++; // ","
        parse_પદાવલિ(&d->param[2], p);
    }
    જો (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_પદાવલિ_free(d);
        પાછા AVERROR(EINVAL);
    }
    p->s++; // ")"

    માટે (પૂર્ણાંક i = 0; i<3; i++)
        જો (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    જો (d->depth > MAX_DEPTH) {
        av_પદાવલિ_free(d);
        પાછા AVERROR(EINVAL);
    }

    d->type = e_func0;
         જો (strmatch(next, "sinh"  )) d->func0 = sinh;
    નહીંતર જો (strmatch(next, "cosh"  )) d->func0 = cosh;
    નહીંતર જો (strmatch(next, "tanh"  )) d->func0 = tanh;
    નહીંતર જો (strmatch(next, "sin"   )) d->func0 = sin;
    નહીંતર જો (strmatch(next, "cos"   )) d->func0 = cos;
    નહીંતર જો (strmatch(next, "tan"   )) d->func0 = tan;
    નહીંતર જો (strmatch(next, "atan"  )) d->func0 = atan;
    નહીંતર જો (strmatch(next, "asin"  )) d->func0 = asin;
    નહીંતર જો (strmatch(next, "acos"  )) d->func0 = acos;
    નહીંતર જો (strmatch(next, "exp"   )) d->func0 = exp;
    નહીંતર જો (strmatch(next, "log"   )) d->func0 = log;
    નહીંતર જો (strmatch(next, "abs"   )) d->func0 = fabs;
    નહીંતર જો (strmatch(next, "time"  )) d->func0 = etime;
    નહીંતર જો (strmatch(next, "squish")) d->type = e_squish;
    નહીંતર જો (strmatch(next, "gauss" )) d->type = e_gauss;
    નહીંતર જો (strmatch(next, "mod"   )) d->type = e_mod;
    નહીંતર જો (strmatch(next, "max"   )) d->type = e_max;
    નહીંતર જો (strmatch(next, "min"   )) d->type = e_min;
    નહીંતર જો (strmatch(next, "eq"    )) d->type = e_eq;
    નહીંતર જો (strmatch(next, "gte"   )) d->type = e_gte;
    નહીંતર જો (strmatch(next, "gt"    )) d->type = e_gt;
    નહીંતર જો (strmatch(next, "lte"   )) d->type = e_lte;
    નહીંતર જો (strmatch(next, "lt"    )) d->type = e_lt;
    નહીંતર જો (strmatch(next, "ld"    )) d->type = e_ld;
    નહીંતર જો (strmatch(next, "isnan" )) d->type = e_isnan;
    નહીંતર જો (strmatch(next, "isinf" )) d->type = e_isinf;
    નહીંતર જો (strmatch(next, "st"    )) d->type = e_st;
    નહીંતર જો (strmatch(next, "while" )) d->type = e_while;
    નહીંતર જો (strmatch(next, "taylor")) d->type = e_taylor;
    નહીંતર જો (strmatch(next, "root"  )) d->type = e_મૂળ;
    નહીંતર જો (strmatch(next, "floor" )) d->type = e_floor;
    નહીંતર જો (strmatch(next, "ceil"  )) d->type = e_ceil;
    નહીંતર જો (strmatch(next, "trunc" )) d->type = e_trunc;
    નહીંતર જો (strmatch(next, "round" )) d->type = e_round;
    નહીંતર જો (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    નહીંતર જો (strmatch(next, "not"   )) d->type = e_not;
    નહીંતર જો (strmatch(next, "pow"   )) d->type = e_pow;
    નહીંતર જો (strmatch(next, "print" )) d->type = e_print;
    નહીંતર જો (strmatch(next, "random")) d->type = e_random;
    નહીંતર જો (strmatch(next, "randomi")) d->type = e_randomi;
    નહીંતર જો (strmatch(next, "hypot" )) d->type = e_hypot;
    નહીંતર જો (strmatch(next, "gcd"   )) d->type = e_gcd;
    નહીંતર જો (strmatch(next, "if"    )) d->type = e_if;
    નહીંતર જો (strmatch(next, "ifnot" )) d->type = e_ifnot;
    નહીંતર જો (strmatch(next, "bitand")) d->type = e_bitand;
    નહીંતર જો (strmatch(next, "bitor" )) d->type = e_bitor;
    નહીંતર જો (strmatch(next, "between"))d->type = e_between;
    નહીંતર જો (strmatch(next, "clip"  )) d->type = e_clip;
    નહીંતર જો (strmatch(next, "atan2" )) d->type = e_atan2;
    નહીંતર જો (strmatch(next, "lerp"  )) d->type = e_lerp;
    નહીંતર જો (strmatch(next, "sgn"   )) d->type = e_sgn;
    નહીંતર {
        માટે (i=0; p->func1_names && p->func1_names[i]; i++) {
            જો (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                પાછા 0;
            }
        }

        માટે (i=0; p->func2_names && p->func2_names[i]; i++) {
            જો (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                પાછા 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_પદાવલિ_free(d);
        પાછા AVERROR(EINVAL);
    }

    *e = d;
    પાછા 0;
}

સ્થિર AVExpr *make_eval_પદાવલિ(પૂર્ણાંક type, પૂર્ણાંક કિંમત, AVExpr *p0, AVExpr *p1)
{
    પૂર્ણાંક depth = FFMAX(p0->depth, p1->depth) + 1;
    જો (depth > MAX_DEPTH)
        પાછા ખાલી;
    AVExpr *e = av_mallocz(કદ(AVExpr));
    જો (!e)
        પાછા ખાલી;
    e->type     =type   ;
    e->કિંમત    =કિંમત  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    પાછા e;
}

સ્થિર પૂર્ણાંક parse_pow(AVExpr **e, Parser *p, પૂર્ણાંક *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    પાછા parse_primary(e, p);
}

સ્થિર પૂર્ણાંક parse_dB(AVExpr **e, Parser *p, પૂર્ણાંક *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    જો (*p->s == '-') {
        અક્ષર *next;
        av_unused દ્વિગુણ ignored = strtod(p->s, &next);
        જો (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            પાછા parse_primary(e, p);
        }
    }
    પાછા parse_pow(e, p, sign);
}

સ્થિર પૂર્ણાંક parse_factor(AVExpr **e, Parser *p)
{
    પૂર્ણાંક sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    જો ((ret = parse_dB(&e0, p, &sign)) < 0)
        પાછા ret;
    જ્યારે(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        જો ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_પદાવલિ_free(e1);
            પાછા ret;
        }
        e0 = make_eval_પદાવલિ(e_pow, 1, e1, e2);
        જો (!e0) {
            av_પદાવલિ_free(e1);
            av_પદાવલિ_free(e2);
            પાછા AVERROR(ENOMEM);
        }
        જો (e0->param[1]) e0->param[1]->કિંમત *= (sign2|1);
    }
    જો (e0) e0->કિંમત *= (sign|1);

    *e = e0;
    પાછા 0;
}

સ્થિર પૂર્ણાંક parse_term(AVExpr **e, Parser *p)
{
    પૂર્ણાંક ret;
    AVExpr *e0, *e1, *e2;
    જો ((ret = parse_factor(&e0, p)) < 0)
        પાછા ret;
    જ્યારે (p->s[0]=='*' || p->s[0]=='/') {
        પૂર્ણાંક c= *p->s++;
        e1 = e0;
        જો ((ret = parse_factor(&e2, p)) < 0) {
            av_પદાવલિ_free(e1);
            પાછા ret;
        }
        e0 = make_eval_પદાવલિ(c == '*' ? e_mul : e_div, 1, e1, e2);
        જો (!e0) {
            av_પદાવલિ_free(e1);
            av_પદાવલિ_free(e2);
            પાછા AVERROR(ENOMEM);
        }
    }
    *e = e0;
    પાછા 0;
}

સ્થિર પૂર્ણાંક parse_subexpr(AVExpr **e, Parser *p)
{
    પૂર્ણાંક ret;
    AVExpr *e0, *e1, *e2;
    જો ((ret = parse_term(&e0, p)) < 0)
        પાછા ret;
    જ્યારે (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        જો ((ret = parse_term(&e2, p)) < 0) {
            av_પદાવલિ_free(e1);
            પાછા ret;
        }
        e0 = make_eval_પદાવલિ(e_add, 1, e1, e2);
        જો (!e0) {
            av_પદાવલિ_free(e1);
            av_પદાવલિ_free(e2);
            પાછા AVERROR(ENOMEM);
        }
    };

    *e = e0;
    પાછા 0;
}

સ્થિર પૂર્ણાંક parse_પદાવલિ(AVExpr **e, Parser *p)
{
    પૂર્ણાંક ret;
    AVExpr *e0, *e1, *e2;
    જો (p->ઢગલો_index <= 0) //protect against stack overflows
        પાછા AVERROR(EINVAL);
    p->ઢગલો_index--;

    જો ((ret = parse_subexpr(&e0, p)) < 0)
        પાછા ret;
    જ્યારે (*p->s == ';') {
        p->s++;
        e1 = e0;
        જો ((ret = parse_subexpr(&e2, p)) < 0) {
            av_પદાવલિ_free(e1);
            પાછા ret;
        }
        e0 = make_eval_પદાવલિ(e_last, 1, e1, e2);
        જો (!e0) {
            av_પદાવલિ_free(e1);
            av_પદાવલિ_free(e2);
            પાછા AVERROR(ENOMEM);
        }
    };

    p->ઢગલો_index++;
    *e = e0;
    પાછા 0;
}

સ્થિર પૂર્ણાંક verify_પદાવલિ(AVExpr *e)
{
    જો (!e) પાછા 0;
    પસંદગી (e->type) {
        સ્થિતિ e_કિંમત:
        સ્થિતિ e_const: પાછા 1;
        સ્થિતિ e_func0:
        સ્થિતિ e_func1:
        સ્થિતિ e_squish:
        સ્થિતિ e_ld:
        સ્થિતિ e_gauss:
        સ્થિતિ e_isnan:
        સ્થિતિ e_isinf:
        સ્થિતિ e_floor:
        સ્થિતિ e_ceil:
        સ્થિતિ e_trunc:
        સ્થિતિ e_round:
        સ્થિતિ e_sqrt:
        સ્થિતિ e_not:
        સ્થિતિ e_random:
        સ્થિતિ e_sgn:
            પાછા verify_પદાવલિ(e->param[0]) && !e->param[1];
        સ્થિતિ e_print:
            પાછા verify_પદાવલિ(e->param[0])
                   && (!e->param[1] || verify_પદાવલિ(e->param[1]));
        સ્થિતિ e_if:
        સ્થિતિ e_ifnot:
        સ્થિતિ e_taylor:
            પાછા verify_પદાવલિ(e->param[0]) && verify_પદાવલિ(e->param[1])
                   && (!e->param[2] || verify_પદાવલિ(e->param[2]));
        સ્થિતિ e_between:
        સ્થિતિ e_clip:
        સ્થિતિ e_lerp:
        સ્થિતિ e_randomi:
            પાછા verify_પદાવલિ(e->param[0]) &&
                   verify_પદાવલિ(e->param[1]) &&
                   verify_પદાવલિ(e->param[2]);
        મૂળભૂત: પાછા verify_પદાવલિ(e->param[0]) && verify_પદાવલિ(e->param[1]) && !e->param[2];
    }
}

પૂર્ણાંક av_પદાવલિ_parse(AVExpr **પદાવલિ, અચલ અક્ષર *s,
                  અચલ અક્ષર * અચલ *const_names,
                  અચલ અક્ષર * અચલ *func1_names, દ્વિગુણ (* અચલ *funcs1)(શૂન્ય *, દ્વિગુણ),
                  અચલ અક્ષર * અચલ *func2_names, દ્વિગુણ (* અચલ *funcs2)(શૂન્ય *, દ્વિગુણ, દ્વિગુણ),
                  પૂર્ણાંક log_offset, શૂન્ય *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = ખાલી;
    અક્ષર *w = av_malloc(strlen(s) + 1);
    અક્ષર *wp = w;
    અચલ અક્ષર *s0 = s;
    પૂર્ણાંક ret = 0;

    જો (!w)
        પાછા AVERROR(ENOMEM);

    જ્યારે (*s)
        જો (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ઢગલો_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    જો ((ret = parse_પદાવલિ(&e, &p)) < 0)
        જાઓ end;
    જો (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        જાઓ end;
    }
    જો (!verify_પદાવલિ(e)) {
        ret = AVERROR(EINVAL);
        જાઓ end;
    }
    AVExpr_મૂળ *r = av_realloc(e, કદ(*r));
    જો (!r) {
        ret = AVERROR(ENOMEM);
        જાઓ end;
    }
    e = (AVExpr*)r;
    e->મૂળ = 1;
    r->var= av_mallocz(કદ(દ્વિગુણ) *VARS);
    r->prng_state = av_mallocz(કદ(*r->prng_state) *VARS);
    જો (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        જાઓ end;
    }
    *પદાવલિ = e;
    e = ખાલી;
end:
    av_પદાવલિ_free(e);
    av_free(w);
    પાછા ret;
}

સ્થિર પૂર્ણાંક પદાવલિ_ગણતરી(AVExpr *e, unsigned *counter, પૂર્ણાંક size, પૂર્ણાંક type)
{
    પૂર્ણાંક i;

    જો (!e || !counter || !size)
        પાછા AVERROR(EINVAL);

    માટે (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        પદાવલિ_ગણતરી(e->param[i], counter, size, type);

    જો (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    પાછા 0;
}

પૂર્ણાંક av_પદાવલિ_ગણતરી_vars(AVExpr *e, unsigned *counter, પૂર્ણાંક size)
{
    પાછા પદાવલિ_ગણતરી(e, counter, size, e_const);
}

પૂર્ણાંક av_પદાવલિ_ગણતરી_func(AVExpr *e, unsigned *counter, પૂર્ણાંક size, પૂર્ણાંક arg)
{
    પાછા પદાવલિ_ગણતરી(e, counter, size, ((પૂર્ણાંક[]){e_const, e_func1, e_func2})[arg]);
}

દ્વિગુણ av_પદાવલિ_eval(AVExpr *e, અચલ દ્વિગુણ *const_કિંમતો, શૂન્ય *opaque)
{
    av_assert1(e->મૂળ);
    AVExpr_મૂળ *r = (AVExpr_મૂળ *)e;
    Parser p = {
        .class        = &eval_class,
        .const_કિંમતો = const_કિંમતો,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    પાછા eval_પદાવલિ(&p, e);
}

પૂર્ણાંક av_પદાવલિ_parse_and_eval(દ્વિગુણ *d, અચલ અક્ષર *s,
                           અચલ અક્ષર * અચલ *const_names, અચલ દ્વિગુણ *const_કિંમતો,
                           અચલ અક્ષર * અચલ *func1_names, દ્વિગુણ (* અચલ *funcs1)(શૂન્ય *, દ્વિગુણ),
                           અચલ અક્ષર * અચલ *func2_names, દ્વિગુણ (* અચલ *funcs2)(શૂન્ય *, દ્વિગુણ, દ્વિગુણ),
                           શૂન્ય *opaque, પૂર્ણાંક log_offset, શૂન્ય *log_ctx)
{
    AVExpr *e = ખાલી;
    પૂર્ણાંક ret = av_પદાવલિ_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    જો (ret < 0) {
        *d = NAN;
        પાછા ret;
    }
    *d = av_પદાવલિ_eval(e, const_કિંમતો, opaque);
    av_પદાવલિ_free(e);
    પાછા isnan(*d) ? AVERROR(EINVAL) : 0;
}
