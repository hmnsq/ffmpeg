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

#अन्तर्भाव <float.h>
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "avutil.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "eval.h"
#अन्तर्भाव "ffmath.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mathematics.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "sfc64.h"
#अन्तर्भाव "time.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "reverse.h"

#define MAX_DEPTH 100

प्रकारनिर्देश संरचना Parser {
    ध्रुव AVClass *class;
    पूर्णाङ्क राशिः_index;
    वर्ण *s;
    ध्रुव द्विगुण *const_मानानि;
    ध्रुव वर्ण * ध्रुव *const_names;          // NULL terminated
    द्विगुण (* ध्रुव *funcs1)(शून्य *, द्विगुण a);           // NULL terminated
    ध्रुव वर्ण * ध्रुव *func1_names;          // NULL terminated
    द्विगुण (* ध्रुव *funcs2)(शून्य *, द्विगुण a, द्विगुण b); // NULL terminated
    ध्रुव वर्ण * ध्रुव *func2_names;          // NULL terminated
    शून्य *opaque;
    पूर्णाङ्क log_offset;
    शून्य *log_ctx;
#define VARS 10
    द्विगुण *var;
    FFSFC64 *prng_state;
} Parser;

स्थिर ध्रुव AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

स्थिर ध्रुव संरचना {
    द्विगुण bin_val;
    द्विगुण dec_val;
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

स्थिर ध्रुव संरचना {
    ध्रुव वर्ण *name;
    द्विगुण मानम्;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

द्विगुण av_strtod(ध्रुव वर्ण *numstr, वर्ण **tail)
{
    द्विगुण d;
    वर्ण *next;
    सचे(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } अञ्ञथा
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    सचे (next!=numstr) {
        सचे (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } अञ्ञथा सचे (*next >= 'E' && *next <= 'z') {
            पूर्णाङ्क e= si_prefixes[*next - 'E'].exp;
            सचे (e) {
                सचे (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } अञ्ञथा {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        सचे (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    सचे (tail)
        *tail = next;
    पटिनिवत्त d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

स्थिर पूर्णाङ्क strmatch(ध्रुव वर्ण *s, ध्रुव वर्ण *prefix)
{
    पूर्णाङ्क i;
    अत्थाय (i=0; prefix[i]; i++) {
        सचे (prefix[i] != s[i]) पटिनिवत्त 0;
    }
    /* return 1 only if the s identifier is terminated */
    पटिनिवत्त !IS_IDENTIFIER_CHAR(s[i]);
}

गणना {
    e_मानम्, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_मूलम्, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
संरचना AVExpr {
    unsigned वर्ण type;
    unsigned वर्ण मूलम्;
    short depth;
    पूर्णाङ्क const_index;
    द्विगुण मानम्; // is sign in other types
    सङ्घ {
        द्विगुण (*func0)(द्विगुण);
        द्विगुण (*func1)(शून्य *, द्विगुण);
        द्विगुण (*func2)(शून्य *, द्विगुण, द्विगुण);
    } ;
    संरचना AVExpr *param[3];
};

प्रकारनिर्देश संरचना {
    AVExpr avexpr;
    द्विगुण *var;
    FFSFC64 *prng_state;
} AVExpr_मूलम्;

स्थिर द्विगुण etime(द्विगुण v)
{
    पटिनिवत्त av_gettime() * 0.000001;
}

स्थिर द्विगुण eval_व्यञ्जकम्(Parser *p, AVExpr *e)
{
    विकल्प (e->type) {
        पक्ष e_मानम्:  पटिनिवत्त e->मानम्;
        पक्ष e_const:  पटिनिवत्त e->मानम् * p->const_मानानि[e->const_index];
        पक्ष e_func0:  पटिनिवत्त e->मानम् * e->func0(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_func1:  पटिनिवत्त e->मानम् * e->func1(p->opaque, eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_func2:  पटिनिवत्त e->मानम् * e->func2(p->opaque, eval_व्यञ्जकम्(p, e->param[0]), eval_व्यञ्जकम्(p, e->param[1]));
        पक्ष e_squish: पटिनिवत्त e->मानम्/(1+exp(4*eval_व्यञ्जकम्(p, e->param[0])));
        पक्ष e_gauss: { द्विगुण d = eval_व्यञ्जकम्(p, e->param[0]); पटिनिवत्त e->मानम् * exp(-d*d/2)/sqrt(2*M_PI); }
        पक्ष e_ld:     पटिनिवत्त e->मानम् * p->var[av_clip(eval_व्यञ्जकम्(p, e->param[0]), 0, VARS-1)];
        पक्ष e_isnan:  पटिनिवत्त e->मानम् * !!isnan(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_isinf:  पटिनिवत्त e->मानम् * !!isinf(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_floor:  पटिनिवत्त e->मानम् * floor(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_ceil :  पटिनिवत्त e->मानम् * ceil (eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_trunc:  पटिनिवत्त e->मानम् * trunc(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_round:  पटिनिवत्त e->मानम् * round(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_sgn:    पटिनिवत्त e->मानम् * FFDIFFSIGN(eval_व्यञ्जकम्(p, e->param[0]), 0);
        पक्ष e_sqrt:   पटिनिवत्त e->मानम् * sqrt (eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_not:    पटिनिवत्त e->मानम् * (eval_व्यञ्जकम्(p, e->param[0]) == 0);
        पक्ष e_if:     पटिनिवत्त e->मानम् * (eval_व्यञ्जकम्(p, e->param[0]) ? eval_व्यञ्जकम्(p, e->param[1]) :
                                          e->param[2] ? eval_व्यञ्जकम्(p, e->param[2]) : 0);
        पक्ष e_ifnot:  पटिनिवत्त e->मानम् * (!eval_व्यञ्जकम्(p, e->param[0]) ? eval_व्यञ्जकम्(p, e->param[1]) :
                                          e->param[2] ? eval_व्यञ्जकम्(p, e->param[2]) : 0);
        पक्ष e_clip: {
            द्विगुण x = eval_व्यञ्जकम्(p, e->param[0]);
            द्विगुण min = eval_व्यञ्जकम्(p, e->param[1]), max = eval_व्यञ्जकम्(p, e->param[2]);
            सचे (isnan(min) || isnan(max) || isnan(x) || min > max)
                पटिनिवत्त NAN;
            पटिनिवत्त e->मानम् * av_clipd(x, min, max);
        }
        पक्ष e_between: {
            द्विगुण d = eval_व्यञ्जकम्(p, e->param[0]);
            पटिनिवत्त e->मानम् * (d >= eval_व्यञ्जकम्(p, e->param[1]) &&
                               d <= eval_व्यञ्जकम्(p, e->param[2]));
        }
        पक्ष e_lerp: {
            द्विगुण v0 = eval_व्यञ्जकम्(p, e->param[0]);
            द्विगुण v1 = eval_व्यञ्जकम्(p, e->param[1]);
            द्विगुण f  = eval_व्यञ्जकम्(p, e->param[2]);
            पटिनिवत्त e->मानम् * (v0 + (v1 - v0) * f);
        }
        पक्ष e_print: {
            द्विगुण x = eval_व्यञ्जकम्(p, e->param[0]);
            पूर्णाङ्क level = e->param[1] ? av_clip(eval_व्यञ्जकम्(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            पटिनिवत्त e->मानम् * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            पूर्णाङ्क idx = av_clip(eval_व्यञ्जकम्(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            सचे (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        पक्ष e_random: {
            COMPUTE_NEXT_RANDOM();
            पटिनिवत्त r * (1.0/UINT64_MAX);
        }
        पक्ष e_randomi: {
            द्विगुण min = eval_व्यञ्जकम्(p, e->param[1]);
            द्विगुण max = eval_व्यञ्जकम्(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            पटिनिवत्त min + (max - min) * r / UINT64_MAX;
        }
        पक्ष e_while: {
            द्विगुण d = NAN;
            याव (eval_व्यञ्जकम्(p, e->param[0]))
                d=eval_व्यञ्जकम्(p, e->param[1]);
            पटिनिवत्त d;
        }
        पक्ष e_taylor: {
            द्विगुण t = 1, d = 0, v;
            द्विगुण x = eval_व्यञ्जकम्(p, e->param[1]);
            पूर्णाङ्क id = e->param[2] ? av_clip(eval_व्यञ्जकम्(p, e->param[2]), 0, VARS-1) : 0;
            पूर्णाङ्क i;
            द्विगुण var0 = p->var[id];
            अत्थाय(i=0; i<1000; i++) {
                द्विगुण ld = d;
                p->var[id] = i;
                v = eval_व्यञ्जकम्(p, e->param[0]);
                d += t*v;
                सचे(ld==d && v)
                    भङ्ग;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            पटिनिवत्त d;
        }
        पक्ष e_मूलम्: {
            पूर्णाङ्क i, j;
            द्विगुण नीचः = -1, उच्चः = -1, v, नीचः_v = -DBL_MAX, उच्चः_v = DBL_MAX;
            द्विगुण var0 = p->var[0];
            द्विगुण x_max = eval_व्यञ्जकम्(p, e->param[1]);
            अत्थाय(i=-1; i<1024; i++) {
                सचे(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } अञ्ञथा {
                    p->var[0] = x_max*pow(0.9, i-255);
                    सचे (i&1) p->var[0] *= -1;
                    सचे (i&2) p->var[0] += नीचः;
                    अञ्ञथा     p->var[0] += उच्चः;
                }
                v = eval_व्यञ्जकम्(p, e->param[0]);
                सचे (v<=0 && v>नीचः_v) {
                    नीचः    = p->var[0];
                    नीचः_v  = v;
                }
                सचे (v>=0 && v<उच्चः_v) {
                    उच्चः   = p->var[0];
                    उच्चः_v = v;
                }
                सचे (नीचः>=0 && उच्चः>=0){
                    अत्थाय (j=0; j<1000; j++) {
                        p->var[0] = (नीचः+उच्चः)*0.5;
                        सचे (नीचः == p->var[0] || उच्चः == p->var[0])
                            भङ्ग;
                        v = eval_व्यञ्जकम्(p, e->param[0]);
                        सचे (v<=0) नीचः = p->var[0];
                        सचे (v>=0) उच्चः= p->var[0];
                        सचे (isnan(v)) {
                            नीचः = उच्चः = v;
                            भङ्ग;
                        }
                    }
                    भङ्ग;
                }
            }
            p->var[0] = var0;
            पटिनिवत्त -नीचः_v<उच्चः_v ? नीचः : उच्चः;
        }
        स्वभाव: {
            द्विगुण d = eval_व्यञ्जकम्(p, e->param[0]);
            द्विगुण d2 = eval_व्यञ्जकम्(p, e->param[1]);
            विकल्प (e->type) {
                पक्ष e_mod: पटिनिवत्त e->मानम् * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                पक्ष e_gcd: पटिनिवत्त e->मानम् * av_gcd(d,d2);
                पक्ष e_max: पटिनिवत्त e->मानम् * (d >  d2 ?   d : d2);
                पक्ष e_min: पटिनिवत्त e->मानम् * (d <  d2 ?   d : d2);
                पक्ष e_eq:  पटिनिवत्त e->मानम् * (d == d2 ? 1.0 : 0.0);
                पक्ष e_gt:  पटिनिवत्त e->मानम् * (d >  d2 ? 1.0 : 0.0);
                पक्ष e_gte: पटिनिवत्त e->मानम् * (d >= d2 ? 1.0 : 0.0);
                पक्ष e_lt:  पटिनिवत्त e->मानम् * (d <  d2 ? 1.0 : 0.0);
                पक्ष e_lte: पटिनिवत्त e->मानम् * (d <= d2 ? 1.0 : 0.0);
                पक्ष e_pow: पटिनिवत्त e->मानम् * pow(d, d2);
                पक्ष e_mul: पटिनिवत्त e->मानम् * (d * d2);
                पक्ष e_div: पटिनिवत्त e->मानम् * (d2 ? (d / d2) : d * INFINITY);
                पक्ष e_add: पटिनिवत्त e->मानम् * (d + d2);
                पक्ष e_last:पटिनिवत्त e->मानम् * d2;
                पक्ष e_st :  {
                    पूर्णाङ्क index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    पटिनिवत्त e->मानम् * (p->var[index]= d2);
                }
                पक्ष e_hypot:पटिनिवत्त e->मानम् * hypot(d, d2);
                पक्ष e_atan2:पटिनिवत्त e->मानम् * atan2(d, d2);
                पक्ष e_bitand: पटिनिवत्त isnan(d) || isnan(d2) ? NAN : e->मानम् * ((long पूर्णाङ्क)d & (long पूर्णाङ्क)d2);
                पक्ष e_bitor:  पटिनिवत्त isnan(d) || isnan(d2) ? NAN : e->मानम् * ((long पूर्णाङ्क)d | (long पूर्णाङ्क)d2);
            }
        }
    }
    पटिनिवत्त NAN;
}

स्थिर पूर्णाङ्क parse_व्यञ्जकम्(AVExpr **e, Parser *p);

शून्य av_व्यञ्जकम्_free(AVExpr *e)
{
    सचे (!e) पटिनिवत्त;
    av_व्यञ्जकम्_free(e->param[0]);
    av_व्यञ्जकम्_free(e->param[1]);
    av_व्यञ्जकम्_free(e->param[2]);
    सचे (e->मूलम्) {
        AVExpr_मूलम् *r = (AVExpr_मूलम्*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

स्थिर पूर्णाङ्क parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(परिमाण(AVExpr));
    वर्ण *next = p->s, *s0 = p->s;
    पूर्णाङ्क ret, i;

    सचे (!d)
        पटिनिवत्त AVERROR(ENOMEM);

    /*सङ्ख्या*/
    d->मानम् = av_strtod(p->s, &next);
    सचे (next != p->s) {
        d->type = e_मानम्;
        p->s= next;
        *e = d;
        पटिनिवत्त 0;
    }
    d->मानम् = 1;

    /* named constants */
    अत्थाय (i=0; p->const_names && p->const_names[i]; i++) {
        सचे (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            पटिनिवत्त 0;
        }
    }
    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        सचे (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_मानम्;
            d->मानम् = constants[i].मानम्;
            *e = d;
            पटिनिवत्त 0;
        }
    }

    p->s= strchr(p->s, '(');
    सचे (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_व्यञ्जकम्_free(d);
        पटिनिवत्त AVERROR(EINVAL);
    }
    p->s++; // "("
    सचे (*next == '(') { // special case do-nothing
        av_freep(&d);
        सचे ((ret = parse_व्यञ्जकम्(&d, p)) < 0)
            पटिनिवत्त ret;
        सचे (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_व्यञ्जकम्_free(d);
            पटिनिवत्त AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        पटिनिवत्त 0;
    }
    सचे ((ret = parse_व्यञ्जकम्(&(d->param[0]), p)) < 0) {
        av_व्यञ्जकम्_free(d);
        पटिनिवत्त ret;
    }
    सचे (p->s[0]== ',') {
        p->s++; // ","
        parse_व्यञ्जकम्(&d->param[1], p);
    }
    सचे (p->s[0]== ',') {
        p->s++; // ","
        parse_व्यञ्जकम्(&d->param[2], p);
    }
    सचे (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_व्यञ्जकम्_free(d);
        पटिनिवत्त AVERROR(EINVAL);
    }
    p->s++; // ")"

    अत्थाय (पूर्णाङ्क i = 0; i<3; i++)
        सचे (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    सचे (d->depth > MAX_DEPTH) {
        av_व्यञ्जकम्_free(d);
        पटिनिवत्त AVERROR(EINVAL);
    }

    d->type = e_func0;
         सचे (strmatch(next, "sinh"  )) d->func0 = sinh;
    अञ्ञथा सचे (strmatch(next, "cosh"  )) d->func0 = cosh;
    अञ्ञथा सचे (strmatch(next, "tanh"  )) d->func0 = tanh;
    अञ्ञथा सचे (strmatch(next, "sin"   )) d->func0 = sin;
    अञ्ञथा सचे (strmatch(next, "cos"   )) d->func0 = cos;
    अञ्ञथा सचे (strmatch(next, "tan"   )) d->func0 = tan;
    अञ्ञथा सचे (strmatch(next, "atan"  )) d->func0 = atan;
    अञ्ञथा सचे (strmatch(next, "asin"  )) d->func0 = asin;
    अञ्ञथा सचे (strmatch(next, "acos"  )) d->func0 = acos;
    अञ्ञथा सचे (strmatch(next, "exp"   )) d->func0 = exp;
    अञ्ञथा सचे (strmatch(next, "log"   )) d->func0 = log;
    अञ्ञथा सचे (strmatch(next, "abs"   )) d->func0 = fabs;
    अञ्ञथा सचे (strmatch(next, "time"  )) d->func0 = etime;
    अञ्ञथा सचे (strmatch(next, "squish")) d->type = e_squish;
    अञ्ञथा सचे (strmatch(next, "gauss" )) d->type = e_gauss;
    अञ्ञथा सचे (strmatch(next, "mod"   )) d->type = e_mod;
    अञ्ञथा सचे (strmatch(next, "max"   )) d->type = e_max;
    अञ्ञथा सचे (strmatch(next, "min"   )) d->type = e_min;
    अञ्ञथा सचे (strmatch(next, "eq"    )) d->type = e_eq;
    अञ्ञथा सचे (strmatch(next, "gte"   )) d->type = e_gte;
    अञ्ञथा सचे (strmatch(next, "gt"    )) d->type = e_gt;
    अञ्ञथा सचे (strmatch(next, "lte"   )) d->type = e_lte;
    अञ्ञथा सचे (strmatch(next, "lt"    )) d->type = e_lt;
    अञ्ञथा सचे (strmatch(next, "ld"    )) d->type = e_ld;
    अञ्ञथा सचे (strmatch(next, "isnan" )) d->type = e_isnan;
    अञ्ञथा सचे (strmatch(next, "isinf" )) d->type = e_isinf;
    अञ्ञथा सचे (strmatch(next, "st"    )) d->type = e_st;
    अञ्ञथा सचे (strmatch(next, "while" )) d->type = e_while;
    अञ्ञथा सचे (strmatch(next, "taylor")) d->type = e_taylor;
    अञ्ञथा सचे (strmatch(next, "root"  )) d->type = e_मूलम्;
    अञ्ञथा सचे (strmatch(next, "floor" )) d->type = e_floor;
    अञ्ञथा सचे (strmatch(next, "ceil"  )) d->type = e_ceil;
    अञ्ञथा सचे (strmatch(next, "trunc" )) d->type = e_trunc;
    अञ्ञथा सचे (strmatch(next, "round" )) d->type = e_round;
    अञ्ञथा सचे (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    अञ्ञथा सचे (strmatch(next, "not"   )) d->type = e_not;
    अञ्ञथा सचे (strmatch(next, "pow"   )) d->type = e_pow;
    अञ्ञथा सचे (strmatch(next, "print" )) d->type = e_print;
    अञ्ञथा सचे (strmatch(next, "random")) d->type = e_random;
    अञ्ञथा सचे (strmatch(next, "randomi")) d->type = e_randomi;
    अञ्ञथा सचे (strmatch(next, "hypot" )) d->type = e_hypot;
    अञ्ञथा सचे (strmatch(next, "gcd"   )) d->type = e_gcd;
    अञ्ञथा सचे (strmatch(next, "if"    )) d->type = e_if;
    अञ्ञथा सचे (strmatch(next, "ifnot" )) d->type = e_ifnot;
    अञ्ञथा सचे (strmatch(next, "bitand")) d->type = e_bitand;
    अञ्ञथा सचे (strmatch(next, "bitor" )) d->type = e_bitor;
    अञ्ञथा सचे (strmatch(next, "between"))d->type = e_between;
    अञ्ञथा सचे (strmatch(next, "clip"  )) d->type = e_clip;
    अञ्ञथा सचे (strmatch(next, "atan2" )) d->type = e_atan2;
    अञ्ञथा सचे (strmatch(next, "lerp"  )) d->type = e_lerp;
    अञ्ञथा सचे (strmatch(next, "sgn"   )) d->type = e_sgn;
    अञ्ञथा {
        अत्थाय (i=0; p->func1_names && p->func1_names[i]; i++) {
            सचे (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                पटिनिवत्त 0;
            }
        }

        अत्थाय (i=0; p->func2_names && p->func2_names[i]; i++) {
            सचे (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                पटिनिवत्त 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_व्यञ्जकम्_free(d);
        पटिनिवत्त AVERROR(EINVAL);
    }

    *e = d;
    पटिनिवत्त 0;
}

स्थिर AVExpr *make_eval_व्यञ्जकम्(पूर्णाङ्क type, पूर्णाङ्क मानम्, AVExpr *p0, AVExpr *p1)
{
    पूर्णाङ्क depth = FFMAX(p0->depth, p1->depth) + 1;
    सचे (depth > MAX_DEPTH)
        पटिनिवत्त रिक्त;
    AVExpr *e = av_mallocz(परिमाण(AVExpr));
    सचे (!e)
        पटिनिवत्त रिक्त;
    e->type     =type   ;
    e->मानम्    =मानम्  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    पटिनिवत्त e;
}

स्थिर पूर्णाङ्क parse_pow(AVExpr **e, Parser *p, पूर्णाङ्क *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    पटिनिवत्त parse_primary(e, p);
}

स्थिर पूर्णाङ्क parse_dB(AVExpr **e, Parser *p, पूर्णाङ्क *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    सचे (*p->s == '-') {
        वर्ण *next;
        av_unused द्विगुण ignored = strtod(p->s, &next);
        सचे (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            पटिनिवत्त parse_primary(e, p);
        }
    }
    पटिनिवत्त parse_pow(e, p, sign);
}

स्थिर पूर्णाङ्क parse_factor(AVExpr **e, Parser *p)
{
    पूर्णाङ्क sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    सचे ((ret = parse_dB(&e0, p, &sign)) < 0)
        पटिनिवत्त ret;
    याव(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        सचे ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_व्यञ्जकम्_free(e1);
            पटिनिवत्त ret;
        }
        e0 = make_eval_व्यञ्जकम्(e_pow, 1, e1, e2);
        सचे (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            पटिनिवत्त AVERROR(ENOMEM);
        }
        सचे (e0->param[1]) e0->param[1]->मानम् *= (sign2|1);
    }
    सचे (e0) e0->मानम् *= (sign|1);

    *e = e0;
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क parse_term(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    सचे ((ret = parse_factor(&e0, p)) < 0)
        पटिनिवत्त ret;
    याव (p->s[0]=='*' || p->s[0]=='/') {
        पूर्णाङ्क c= *p->s++;
        e1 = e0;
        सचे ((ret = parse_factor(&e2, p)) < 0) {
            av_व्यञ्जकम्_free(e1);
            पटिनिवत्त ret;
        }
        e0 = make_eval_व्यञ्जकम्(c == '*' ? e_mul : e_div, 1, e1, e2);
        सचे (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            पटिनिवत्त AVERROR(ENOMEM);
        }
    }
    *e = e0;
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क parse_subexpr(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    सचे ((ret = parse_term(&e0, p)) < 0)
        पटिनिवत्त ret;
    याव (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        सचे ((ret = parse_term(&e2, p)) < 0) {
            av_व्यञ्जकम्_free(e1);
            पटिनिवत्त ret;
        }
        e0 = make_eval_व्यञ्जकम्(e_add, 1, e1, e2);
        सचे (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            पटिनिवत्त AVERROR(ENOMEM);
        }
    };

    *e = e0;
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क parse_व्यञ्जकम्(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    सचे (p->राशिः_index <= 0) //protect against stack overflows
        पटिनिवत्त AVERROR(EINVAL);
    p->राशिः_index--;

    सचे ((ret = parse_subexpr(&e0, p)) < 0)
        पटिनिवत्त ret;
    याव (*p->s == ';') {
        p->s++;
        e1 = e0;
        सचे ((ret = parse_subexpr(&e2, p)) < 0) {
            av_व्यञ्जकम्_free(e1);
            पटिनिवत्त ret;
        }
        e0 = make_eval_व्यञ्जकम्(e_last, 1, e1, e2);
        सचे (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            पटिनिवत्त AVERROR(ENOMEM);
        }
    };

    p->राशिः_index++;
    *e = e0;
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क verify_व्यञ्जकम्(AVExpr *e)
{
    सचे (!e) पटिनिवत्त 0;
    विकल्प (e->type) {
        पक्ष e_मानम्:
        पक्ष e_const: पटिनिवत्त 1;
        पक्ष e_func0:
        पक्ष e_func1:
        पक्ष e_squish:
        पक्ष e_ld:
        पक्ष e_gauss:
        पक्ष e_isnan:
        पक्ष e_isinf:
        पक्ष e_floor:
        पक्ष e_ceil:
        पक्ष e_trunc:
        पक्ष e_round:
        पक्ष e_sqrt:
        पक्ष e_not:
        पक्ष e_random:
        पक्ष e_sgn:
            पटिनिवत्त verify_व्यञ्जकम्(e->param[0]) && !e->param[1];
        पक्ष e_print:
            पटिनिवत्त verify_व्यञ्जकम्(e->param[0])
                   && (!e->param[1] || verify_व्यञ्जकम्(e->param[1]));
        पक्ष e_if:
        पक्ष e_ifnot:
        पक्ष e_taylor:
            पटिनिवत्त verify_व्यञ्जकम्(e->param[0]) && verify_व्यञ्जकम्(e->param[1])
                   && (!e->param[2] || verify_व्यञ्जकम्(e->param[2]));
        पक्ष e_between:
        पक्ष e_clip:
        पक्ष e_lerp:
        पक्ष e_randomi:
            पटिनिवत्त verify_व्यञ्जकम्(e->param[0]) &&
                   verify_व्यञ्जकम्(e->param[1]) &&
                   verify_व्यञ्जकम्(e->param[2]);
        स्वभाव: पटिनिवत्त verify_व्यञ्जकम्(e->param[0]) && verify_व्यञ्जकम्(e->param[1]) && !e->param[2];
    }
}

पूर्णाङ्क av_व्यञ्जकम्_parse(AVExpr **व्यञ्जकम्, ध्रुव वर्ण *s,
                  ध्रुव वर्ण * ध्रुव *const_names,
                  ध्रुव वर्ण * ध्रुव *func1_names, द्विगुण (* ध्रुव *funcs1)(शून्य *, द्विगुण),
                  ध्रुव वर्ण * ध्रुव *func2_names, द्विगुण (* ध्रुव *funcs2)(शून्य *, द्विगुण, द्विगुण),
                  पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = रिक्त;
    वर्ण *w = av_malloc(strlen(s) + 1);
    वर्ण *wp = w;
    ध्रुव वर्ण *s0 = s;
    पूर्णाङ्क ret = 0;

    सचे (!w)
        पटिनिवत्त AVERROR(ENOMEM);

    याव (*s)
        सचे (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.राशिः_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    सचे ((ret = parse_व्यञ्जकम्(&e, &p)) < 0)
        गच्छ end;
    सचे (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        गच्छ end;
    }
    सचे (!verify_व्यञ्जकम्(e)) {
        ret = AVERROR(EINVAL);
        गच्छ end;
    }
    AVExpr_मूलम् *r = av_realloc(e, परिमाण(*r));
    सचे (!r) {
        ret = AVERROR(ENOMEM);
        गच्छ end;
    }
    e = (AVExpr*)r;
    e->मूलम् = 1;
    r->var= av_mallocz(परिमाण(द्विगुण) *VARS);
    r->prng_state = av_mallocz(परिमाण(*r->prng_state) *VARS);
    सचे (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        गच्छ end;
    }
    *व्यञ्जकम् = e;
    e = रिक्त;
end:
    av_व्यञ्जकम्_free(e);
    av_free(w);
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क व्यञ्जकम्_गणनम्(AVExpr *e, unsigned *counter, पूर्णाङ्क size, पूर्णाङ्क type)
{
    पूर्णाङ्क i;

    सचे (!e || !counter || !size)
        पटिनिवत्त AVERROR(EINVAL);

    अत्थाय (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        व्यञ्जकम्_गणनम्(e->param[i], counter, size, type);

    सचे (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    पटिनिवत्त 0;
}

पूर्णाङ्क av_व्यञ्जकम्_गणनम्_vars(AVExpr *e, unsigned *counter, पूर्णाङ्क size)
{
    पटिनिवत्त व्यञ्जकम्_गणनम्(e, counter, size, e_const);
}

पूर्णाङ्क av_व्यञ्जकम्_गणनम्_func(AVExpr *e, unsigned *counter, पूर्णाङ्क size, पूर्णाङ्क arg)
{
    पटिनिवत्त व्यञ्जकम्_गणनम्(e, counter, size, ((पूर्णाङ्क[]){e_const, e_func1, e_func2})[arg]);
}

द्विगुण av_व्यञ्जकम्_eval(AVExpr *e, ध्रुव द्विगुण *const_मानानि, शून्य *opaque)
{
    av_assert1(e->मूलम्);
    AVExpr_मूलम् *r = (AVExpr_मूलम् *)e;
    Parser p = {
        .class        = &eval_class,
        .const_मानानि = const_मानानि,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    पटिनिवत्त eval_व्यञ्जकम्(&p, e);
}

पूर्णाङ्क av_व्यञ्जकम्_parse_and_eval(द्विगुण *d, ध्रुव वर्ण *s,
                           ध्रुव वर्ण * ध्रुव *const_names, ध्रुव द्विगुण *const_मानानि,
                           ध्रुव वर्ण * ध्रुव *func1_names, द्विगुण (* ध्रुव *funcs1)(शून्य *, द्विगुण),
                           ध्रुव वर्ण * ध्रुव *func2_names, द्विगुण (* ध्रुव *funcs2)(शून्य *, द्विगुण, द्विगुण),
                           शून्य *opaque, पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    AVExpr *e = रिक्त;
    पूर्णाङ्क ret = av_व्यञ्जकम्_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    सचे (ret < 0) {
        *d = NAN;
        पटिनिवत्त ret;
    }
    *d = av_व्यञ्जकम्_eval(e, const_मानानि, opaque);
    av_व्यञ्जकम्_free(e);
    पटिनिवत्त isnan(*d) ? AVERROR(EINVAL) : 0;
}
