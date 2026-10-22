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
    अचर AVClass *class;
    पूर्णाङ्क थाक_index;
    वर्ण *s;
    अचर द्विगुण *const_मानहरू;
    अचर वर्ण * अचर *const_names;          // NULL terminated
    द्विगुण (* अचर *funcs1)(शून्य *, द्विगुण a);           // NULL terminated
    अचर वर्ण * अचर *func1_names;          // NULL terminated
    द्विगुण (* अचर *funcs2)(शून्य *, द्विगुण a, द्विगुण b); // NULL terminated
    अचर वर्ण * अचर *func2_names;          // NULL terminated
    शून्य *opaque;
    पूर्णाङ्क log_offset;
    शून्य *log_ctx;
#define VARS 10
    द्विगुण *var;
    FFSFC64 *prng_state;
} Parser;

स्थिर अचर AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(Parser, log_offset),
    .parent_log_context_offset = दुरत्व(Parser, log_ctx),
};

स्थिर अचर संरचना {
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

स्थिर अचर संरचना {
    अचर वर्ण *name;
    द्विगुण मान;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

द्विगुण av_strtod(अचर वर्ण *numstr, वर्ण **tail)
{
    द्विगुण d;
    वर्ण *next;
    यदि(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = म_से_अदीर्घ(numstr, &next, 16);
    } अन्यथा
        d = म_से_भग्न(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    यदि (next!=numstr) {
        यदि (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } अन्यथा यदि (*next >= 'E' && *next <= 'z') {
            पूर्णाङ्क e= si_prefixes[*next - 'E'].exp;
            यदि (e) {
                यदि (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } अन्यथा {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        यदि (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    यदि (tail)
        *tail = next;
    फर्काऊ d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

स्थिर पूर्णाङ्क strmatch(अचर वर्ण *s, अचर वर्ण *prefix)
{
    पूर्णाङ्क i;
    लागि (i=0; prefix[i]; i++) {
        यदि (prefix[i] != s[i]) फर्काऊ 0;
    }
    /* return 1 only if the s identifier is terminated */
    फर्काऊ !IS_IDENTIFIER_CHAR(s[i]);
}

गणना {
    e_मान, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_जरा, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
संरचना AVExpr {
    अचिन्हित वर्ण type;
    अचिन्हित वर्ण जरा;
    लघु depth;
    पूर्णाङ्क const_index;
    द्विगुण मान; // is sign in other types
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
} AVExpr_जरा;

स्थिर द्विगुण etime(द्विगुण v)
{
    फर्काऊ av_gettime() * 0.000001;
}

स्थिर द्विगुण eval_अभिव्यक्ति(Parser *p, AVExpr *e)
{
    विकल्प (e->type) {
        पक्ष e_मान:  फर्काऊ e->मान;
        पक्ष e_const:  फर्काऊ e->मान * p->const_मानहरू[e->const_index];
        पक्ष e_func0:  फर्काऊ e->मान * e->func0(eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_func1:  फर्काऊ e->मान * e->func1(p->opaque, eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_func2:  फर्काऊ e->मान * e->func2(p->opaque, eval_अभिव्यक्ति(p, e->param[0]), eval_अभिव्यक्ति(p, e->param[1]));
        पक्ष e_squish: फर्काऊ e->मान/(1+exp(4*eval_अभिव्यक्ति(p, e->param[0])));
        पक्ष e_gauss: { द्विगुण d = eval_अभिव्यक्ति(p, e->param[0]); फर्काऊ e->मान * exp(-d*d/2)/वर्ग_मूल(2*M_PI); }
        पक्ष e_ld:     फर्काऊ e->मान * p->var[av_clip(eval_अभिव्यक्ति(p, e->param[0]), 0, VARS-1)];
        पक्ष e_isnan:  फर्काऊ e->मान * !!isnan(eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_isinf:  फर्काऊ e->मान * !!isinf(eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_floor:  फर्काऊ e->मान * न्यूनमान(eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_ceil :  फर्काऊ e->मान * उच्चमान (eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_trunc:  फर्काऊ e->मान * trunc(eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_round:  फर्काऊ e->मान * round(eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_sgn:    फर्काऊ e->मान * FFDIFFSIGN(eval_अभिव्यक्ति(p, e->param[0]), 0);
        पक्ष e_sqrt:   फर्काऊ e->मान * वर्ग_मूल (eval_अभिव्यक्ति(p, e->param[0]));
        पक्ष e_not:    फर्काऊ e->मान * (eval_अभिव्यक्ति(p, e->param[0]) == 0);
        पक्ष e_if:     फर्काऊ e->मान * (eval_अभिव्यक्ति(p, e->param[0]) ? eval_अभिव्यक्ति(p, e->param[1]) :
                                          e->param[2] ? eval_अभिव्यक्ति(p, e->param[2]) : 0);
        पक्ष e_ifnot:  फर्काऊ e->मान * (!eval_अभिव्यक्ति(p, e->param[0]) ? eval_अभिव्यक्ति(p, e->param[1]) :
                                          e->param[2] ? eval_अभिव्यक्ति(p, e->param[2]) : 0);
        पक्ष e_clip: {
            द्विगुण x = eval_अभिव्यक्ति(p, e->param[0]);
            द्विगुण min = eval_अभिव्यक्ति(p, e->param[1]), max = eval_अभिव्यक्ति(p, e->param[2]);
            यदि (isnan(min) || isnan(max) || isnan(x) || min > max)
                फर्काऊ न_अंक;
            फर्काऊ e->मान * av_clipd(x, min, max);
        }
        पक्ष e_between: {
            द्विगुण d = eval_अभिव्यक्ति(p, e->param[0]);
            फर्काऊ e->मान * (d >= eval_अभिव्यक्ति(p, e->param[1]) &&
                               d <= eval_अभिव्यक्ति(p, e->param[2]));
        }
        पक्ष e_lerp: {
            द्विगुण v0 = eval_अभिव्यक्ति(p, e->param[0]);
            द्विगुण v1 = eval_अभिव्यक्ति(p, e->param[1]);
            द्विगुण f  = eval_अभिव्यक्ति(p, e->param[2]);
            फर्काऊ e->मान * (v0 + (v1 - v0) * f);
        }
        पक्ष e_print: {
            द्विगुण x = eval_अभिव्यक्ति(p, e->param[0]);
            पूर्णाङ्क level = e->param[1] ? av_clip(eval_अभिव्यक्ति(p, e->param[1]), पूर्णांक_न्यून, पूर्णांक_उच्च) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            फर्काऊ e->मान * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            पूर्णाङ्क idx = av_clip(eval_अभिव्यक्ति(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            यदि (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        पक्ष e_random: {
            COMPUTE_NEXT_RANDOM();
            फर्काऊ r * (1.0/UINT64_MAX);
        }
        पक्ष e_randomi: {
            द्विगुण min = eval_अभिव्यक्ति(p, e->param[1]);
            द्विगुण max = eval_अभिव्यक्ति(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            फर्काऊ min + (max - min) * r / UINT64_MAX;
        }
        पक्ष e_while: {
            द्विगुण d = न_अंक;
            जबसम्म (eval_अभिव्यक्ति(p, e->param[0]))
                d=eval_अभिव्यक्ति(p, e->param[1]);
            फर्काऊ d;
        }
        पक्ष e_taylor: {
            द्विगुण t = 1, d = 0, v;
            द्विगुण x = eval_अभिव्यक्ति(p, e->param[1]);
            पूर्णाङ्क id = e->param[2] ? av_clip(eval_अभिव्यक्ति(p, e->param[2]), 0, VARS-1) : 0;
            पूर्णाङ्क i;
            द्विगुण var0 = p->var[id];
            लागि(i=0; i<1000; i++) {
                द्विगुण ld = d;
                p->var[id] = i;
                v = eval_अभिव्यक्ति(p, e->param[0]);
                d += t*v;
                यदि(ld==d && v)
                    रोक;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            फर्काऊ d;
        }
        पक्ष e_जरा: {
            पूर्णाङ्क i, j;
            द्विगुण तल्लो = -1, माथिल्लो = -1, v, तल्लो_v = -द्विग_उच्च, माथिल्लो_v = द्विग_उच्च;
            द्विगुण var0 = p->var[0];
            द्विगुण x_max = eval_अभिव्यक्ति(p, e->param[1]);
            लागि(i=-1; i<1024; i++) {
                यदि(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } अन्यथा {
                    p->var[0] = x_max*घात(0.9, i-255);
                    यदि (i&1) p->var[0] *= -1;
                    यदि (i&2) p->var[0] += तल्लो;
                    अन्यथा     p->var[0] += माथिल्लो;
                }
                v = eval_अभिव्यक्ति(p, e->param[0]);
                यदि (v<=0 && v>तल्लो_v) {
                    तल्लो    = p->var[0];
                    तल्लो_v  = v;
                }
                यदि (v>=0 && v<माथिल्लो_v) {
                    माथिल्लो   = p->var[0];
                    माथिल्लो_v = v;
                }
                यदि (तल्लो>=0 && माथिल्लो>=0){
                    लागि (j=0; j<1000; j++) {
                        p->var[0] = (तल्लो+माथिल्लो)*0.5;
                        यदि (तल्लो == p->var[0] || माथिल्लो == p->var[0])
                            रोक;
                        v = eval_अभिव्यक्ति(p, e->param[0]);
                        यदि (v<=0) तल्लो = p->var[0];
                        यदि (v>=0) माथिल्लो= p->var[0];
                        यदि (isnan(v)) {
                            तल्लो = माथिल्लो = v;
                            रोक;
                        }
                    }
                    रोक;
                }
            }
            p->var[0] = var0;
            फर्काऊ -तल्लो_v<माथिल्लो_v ? तल्लो : माथिल्लो;
        }
        स्वभाव: {
            द्विगुण d = eval_अभिव्यक्ति(p, e->param[0]);
            द्विगुण d2 = eval_अभिव्यक्ति(p, e->param[1]);
            विकल्प (e->type) {
                पक्ष e_mod: फर्काऊ e->मान * (d - न्यूनमान(d2 ? d / d2 : d * अनन्त) * d2);
                पक्ष e_gcd: फर्काऊ e->मान * av_gcd(d,d2);
                पक्ष e_max: फर्काऊ e->मान * (d >  d2 ?   d : d2);
                पक्ष e_min: फर्काऊ e->मान * (d <  d2 ?   d : d2);
                पक्ष e_eq:  फर्काऊ e->मान * (d == d2 ? 1.0 : 0.0);
                पक्ष e_gt:  फर्काऊ e->मान * (d >  d2 ? 1.0 : 0.0);
                पक्ष e_gte: फर्काऊ e->मान * (d >= d2 ? 1.0 : 0.0);
                पक्ष e_lt:  फर्काऊ e->मान * (d <  d2 ? 1.0 : 0.0);
                पक्ष e_lte: फर्काऊ e->मान * (d <= d2 ? 1.0 : 0.0);
                पक्ष e_pow: फर्काऊ e->मान * घात(d, d2);
                पक्ष e_mul: फर्काऊ e->मान * (d * d2);
                पक्ष e_div: फर्काऊ e->मान * (d2 ? (d / d2) : d * अनन्त);
                पक्ष e_add: फर्काऊ e->मान * (d + d2);
                पक्ष e_last:फर्काऊ e->मान * d2;
                पक्ष e_st :  {
                    पूर्णाङ्क index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    फर्काऊ e->मान * (p->var[index]= d2);
                }
                पक्ष e_hypot:फर्काऊ e->मान * hypot(d, d2);
                पक्ष e_atan2:फर्काऊ e->मान * atan2(d, d2);
                पक्ष e_bitand: फर्काऊ isnan(d) || isnan(d2) ? न_अंक : e->मान * ((दीर्घ पूर्णाङ्क)d & (दीर्घ पूर्णाङ्क)d2);
                पक्ष e_bitor:  फर्काऊ isnan(d) || isnan(d2) ? न_अंक : e->मान * ((दीर्घ पूर्णाङ्क)d | (दीर्घ पूर्णाङ्क)d2);
            }
        }
    }
    फर्काऊ न_अंक;
}

स्थिर पूर्णाङ्क parse_अभिव्यक्ति(AVExpr **e, Parser *p);

शून्य av_अभिव्यक्ति_free(AVExpr *e)
{
    यदि (!e) फर्काऊ;
    av_अभिव्यक्ति_free(e->param[0]);
    av_अभिव्यक्ति_free(e->param[1]);
    av_अभिव्यक्ति_free(e->param[2]);
    यदि (e->जरा) {
        AVExpr_जरा *r = (AVExpr_जरा*)e;
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

    यदि (!d)
        फर्काऊ AVERROR(ENOMEM);

    /*सङ्ख्या*/
    d->मान = av_strtod(p->s, &next);
    यदि (next != p->s) {
        d->type = e_मान;
        p->s= next;
        *e = d;
        फर्काऊ 0;
    }
    d->मान = 1;

    /* named constants */
    लागि (i=0; p->const_names && p->const_names[i]; i++) {
        यदि (strmatch(p->s, p->const_names[i])) {
            p->s+= म_माप(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            फर्काऊ 0;
        }
    }
    लागि (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        यदि (strmatch(p->s, constants[i].name)) {
            p->s += म_माप(constants[i].name);
            d->type = e_मान;
            d->मान = constants[i].मान;
            *e = d;
            फर्काऊ 0;
        }
    }

    p->s= म_अक्षर(p->s, '(');
    यदि (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_अभिव्यक्ति_free(d);
        फर्काऊ AVERROR(EINVAL);
    }
    p->s++; // "("
    यदि (*next == '(') { // special case do-nothing
        av_freep(&d);
        यदि ((ret = parse_अभिव्यक्ति(&d, p)) < 0)
            फर्काऊ ret;
        यदि (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_अभिव्यक्ति_free(d);
            फर्काऊ AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        फर्काऊ 0;
    }
    यदि ((ret = parse_अभिव्यक्ति(&(d->param[0]), p)) < 0) {
        av_अभिव्यक्ति_free(d);
        फर्काऊ ret;
    }
    यदि (p->s[0]== ',') {
        p->s++; // ","
        parse_अभिव्यक्ति(&d->param[1], p);
    }
    यदि (p->s[0]== ',') {
        p->s++; // ","
        parse_अभिव्यक्ति(&d->param[2], p);
    }
    यदि (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_अभिव्यक्ति_free(d);
        फर्काऊ AVERROR(EINVAL);
    }
    p->s++; // ")"

    लागि (पूर्णाङ्क i = 0; i<3; i++)
        यदि (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    यदि (d->depth > MAX_DEPTH) {
        av_अभिव्यक्ति_free(d);
        फर्काऊ AVERROR(EINVAL);
    }

    d->type = e_func0;
         यदि (strmatch(next, "sinh"  )) d->func0 = sinh;
    अन्यथा यदि (strmatch(next, "cosh"  )) d->func0 = cosh;
    अन्यथा यदि (strmatch(next, "tanh"  )) d->func0 = tanh;
    अन्यथा यदि (strmatch(next, "sin"   )) d->func0 = sin;
    अन्यथा यदि (strmatch(next, "cos"   )) d->func0 = cos;
    अन्यथा यदि (strmatch(next, "tan"   )) d->func0 = tan;
    अन्यथा यदि (strmatch(next, "atan"  )) d->func0 = atan;
    अन्यथा यदि (strmatch(next, "asin"  )) d->func0 = asin;
    अन्यथा यदि (strmatch(next, "acos"  )) d->func0 = acos;
    अन्यथा यदि (strmatch(next, "exp"   )) d->func0 = exp;
    अन्यथा यदि (strmatch(next, "log"   )) d->func0 = log;
    अन्यथा यदि (strmatch(next, "abs"   )) d->func0 = भ_असल;
    अन्यथा यदि (strmatch(next, "time"  )) d->func0 = etime;
    अन्यथा यदि (strmatch(next, "squish")) d->type = e_squish;
    अन्यथा यदि (strmatch(next, "gauss" )) d->type = e_gauss;
    अन्यथा यदि (strmatch(next, "mod"   )) d->type = e_mod;
    अन्यथा यदि (strmatch(next, "max"   )) d->type = e_max;
    अन्यथा यदि (strmatch(next, "min"   )) d->type = e_min;
    अन्यथा यदि (strmatch(next, "eq"    )) d->type = e_eq;
    अन्यथा यदि (strmatch(next, "gte"   )) d->type = e_gte;
    अन्यथा यदि (strmatch(next, "gt"    )) d->type = e_gt;
    अन्यथा यदि (strmatch(next, "lte"   )) d->type = e_lte;
    अन्यथा यदि (strmatch(next, "lt"    )) d->type = e_lt;
    अन्यथा यदि (strmatch(next, "ld"    )) d->type = e_ld;
    अन्यथा यदि (strmatch(next, "isnan" )) d->type = e_isnan;
    अन्यथा यदि (strmatch(next, "isinf" )) d->type = e_isinf;
    अन्यथा यदि (strmatch(next, "st"    )) d->type = e_st;
    अन्यथा यदि (strmatch(next, "while" )) d->type = e_while;
    अन्यथा यदि (strmatch(next, "taylor")) d->type = e_taylor;
    अन्यथा यदि (strmatch(next, "root"  )) d->type = e_जरा;
    अन्यथा यदि (strmatch(next, "floor" )) d->type = e_floor;
    अन्यथा यदि (strmatch(next, "ceil"  )) d->type = e_ceil;
    अन्यथा यदि (strmatch(next, "trunc" )) d->type = e_trunc;
    अन्यथा यदि (strmatch(next, "round" )) d->type = e_round;
    अन्यथा यदि (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    अन्यथा यदि (strmatch(next, "not"   )) d->type = e_not;
    अन्यथा यदि (strmatch(next, "pow"   )) d->type = e_pow;
    अन्यथा यदि (strmatch(next, "print" )) d->type = e_print;
    अन्यथा यदि (strmatch(next, "random")) d->type = e_random;
    अन्यथा यदि (strmatch(next, "randomi")) d->type = e_randomi;
    अन्यथा यदि (strmatch(next, "hypot" )) d->type = e_hypot;
    अन्यथा यदि (strmatch(next, "gcd"   )) d->type = e_gcd;
    अन्यथा यदि (strmatch(next, "if"    )) d->type = e_if;
    अन्यथा यदि (strmatch(next, "ifnot" )) d->type = e_ifnot;
    अन्यथा यदि (strmatch(next, "bitand")) d->type = e_bitand;
    अन्यथा यदि (strmatch(next, "bitor" )) d->type = e_bitor;
    अन्यथा यदि (strmatch(next, "between"))d->type = e_between;
    अन्यथा यदि (strmatch(next, "clip"  )) d->type = e_clip;
    अन्यथा यदि (strmatch(next, "atan2" )) d->type = e_atan2;
    अन्यथा यदि (strmatch(next, "lerp"  )) d->type = e_lerp;
    अन्यथा यदि (strmatch(next, "sgn"   )) d->type = e_sgn;
    अन्यथा {
        लागि (i=0; p->func1_names && p->func1_names[i]; i++) {
            यदि (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                फर्काऊ 0;
            }
        }

        लागि (i=0; p->func2_names && p->func2_names[i]; i++) {
            यदि (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                फर्काऊ 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_अभिव्यक्ति_free(d);
        फर्काऊ AVERROR(EINVAL);
    }

    *e = d;
    फर्काऊ 0;
}

स्थिर AVExpr *make_eval_अभिव्यक्ति(पूर्णाङ्क type, पूर्णाङ्क मान, AVExpr *p0, AVExpr *p1)
{
    पूर्णाङ्क depth = FFMAX(p0->depth, p1->depth) + 1;
    यदि (depth > MAX_DEPTH)
        फर्काऊ रिक्त;
    AVExpr *e = av_mallocz(परिमाण(AVExpr));
    यदि (!e)
        फर्काऊ रिक्त;
    e->type     =type   ;
    e->मान    =मान  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    फर्काऊ e;
}

स्थिर पूर्णाङ्क parse_pow(AVExpr **e, Parser *p, पूर्णाङ्क *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    फर्काऊ parse_primary(e, p);
}

स्थिर पूर्णाङ्क parse_dB(AVExpr **e, Parser *p, पूर्णाङ्क *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    यदि (*p->s == '-') {
        वर्ण *next;
        av_unused द्विगुण ignored = म_से_भग्न(p->s, &next);
        यदि (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            फर्काऊ parse_primary(e, p);
        }
    }
    फर्काऊ parse_pow(e, p, sign);
}

स्थिर पूर्णाङ्क parse_factor(AVExpr **e, Parser *p)
{
    पूर्णाङ्क sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    यदि ((ret = parse_dB(&e0, p, &sign)) < 0)
        फर्काऊ ret;
    जबसम्म(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        यदि ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_अभिव्यक्ति_free(e1);
            फर्काऊ ret;
        }
        e0 = make_eval_अभिव्यक्ति(e_pow, 1, e1, e2);
        यदि (!e0) {
            av_अभिव्यक्ति_free(e1);
            av_अभिव्यक्ति_free(e2);
            फर्काऊ AVERROR(ENOMEM);
        }
        यदि (e0->param[1]) e0->param[1]->मान *= (sign2|1);
    }
    यदि (e0) e0->मान *= (sign|1);

    *e = e0;
    फर्काऊ 0;
}

स्थिर पूर्णाङ्क parse_term(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    यदि ((ret = parse_factor(&e0, p)) < 0)
        फर्काऊ ret;
    जबसम्म (p->s[0]=='*' || p->s[0]=='/') {
        पूर्णाङ्क c= *p->s++;
        e1 = e0;
        यदि ((ret = parse_factor(&e2, p)) < 0) {
            av_अभिव्यक्ति_free(e1);
            फर्काऊ ret;
        }
        e0 = make_eval_अभिव्यक्ति(c == '*' ? e_mul : e_div, 1, e1, e2);
        यदि (!e0) {
            av_अभिव्यक्ति_free(e1);
            av_अभिव्यक्ति_free(e2);
            फर्काऊ AVERROR(ENOMEM);
        }
    }
    *e = e0;
    फर्काऊ 0;
}

स्थिर पूर्णाङ्क parse_subexpr(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    यदि ((ret = parse_term(&e0, p)) < 0)
        फर्काऊ ret;
    जबसम्म (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        यदि ((ret = parse_term(&e2, p)) < 0) {
            av_अभिव्यक्ति_free(e1);
            फर्काऊ ret;
        }
        e0 = make_eval_अभिव्यक्ति(e_add, 1, e1, e2);
        यदि (!e0) {
            av_अभिव्यक्ति_free(e1);
            av_अभिव्यक्ति_free(e2);
            फर्काऊ AVERROR(ENOMEM);
        }
    };

    *e = e0;
    फर्काऊ 0;
}

स्थिर पूर्णाङ्क parse_अभिव्यक्ति(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    यदि (p->थाक_index <= 0) //protect against stack overflows
        फर्काऊ AVERROR(EINVAL);
    p->थाक_index--;

    यदि ((ret = parse_subexpr(&e0, p)) < 0)
        फर्काऊ ret;
    जबसम्म (*p->s == ';') {
        p->s++;
        e1 = e0;
        यदि ((ret = parse_subexpr(&e2, p)) < 0) {
            av_अभिव्यक्ति_free(e1);
            फर्काऊ ret;
        }
        e0 = make_eval_अभिव्यक्ति(e_last, 1, e1, e2);
        यदि (!e0) {
            av_अभिव्यक्ति_free(e1);
            av_अभिव्यक्ति_free(e2);
            फर्काऊ AVERROR(ENOMEM);
        }
    };

    p->थाक_index++;
    *e = e0;
    फर्काऊ 0;
}

स्थिर पूर्णाङ्क verify_अभिव्यक्ति(AVExpr *e)
{
    यदि (!e) फर्काऊ 0;
    विकल्प (e->type) {
        पक्ष e_मान:
        पक्ष e_const: फर्काऊ 1;
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
            फर्काऊ verify_अभिव्यक्ति(e->param[0]) && !e->param[1];
        पक्ष e_print:
            फर्काऊ verify_अभिव्यक्ति(e->param[0])
                   && (!e->param[1] || verify_अभिव्यक्ति(e->param[1]));
        पक्ष e_if:
        पक्ष e_ifnot:
        पक्ष e_taylor:
            फर्काऊ verify_अभिव्यक्ति(e->param[0]) && verify_अभिव्यक्ति(e->param[1])
                   && (!e->param[2] || verify_अभिव्यक्ति(e->param[2]));
        पक्ष e_between:
        पक्ष e_clip:
        पक्ष e_lerp:
        पक्ष e_randomi:
            फर्काऊ verify_अभिव्यक्ति(e->param[0]) &&
                   verify_अभिव्यक्ति(e->param[1]) &&
                   verify_अभिव्यक्ति(e->param[2]);
        स्वभाव: फर्काऊ verify_अभिव्यक्ति(e->param[0]) && verify_अभिव्यक्ति(e->param[1]) && !e->param[2];
    }
}

पूर्णाङ्क av_अभिव्यक्ति_parse(AVExpr **अभिव्यक्ति, अचर वर्ण *s,
                  अचर वर्ण * अचर *const_names,
                  अचर वर्ण * अचर *func1_names, द्विगुण (* अचर *funcs1)(शून्य *, द्विगुण),
                  अचर वर्ण * अचर *func2_names, द्विगुण (* अचर *funcs2)(शून्य *, द्विगुण, द्विगुण),
                  पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = रिक्त;
    वर्ण *w = av_malloc(म_माप(s) + 1);
    वर्ण *wp = w;
    अचर वर्ण *s0 = s;
    पूर्णाङ्क ret = 0;

    यदि (!w)
        फर्काऊ AVERROR(ENOMEM);

    जबसम्म (*s)
        यदि (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.थाक_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    यदि ((ret = parse_अभिव्यक्ति(&e, &p)) < 0)
        गच्छ end;
    यदि (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        गच्छ end;
    }
    यदि (!verify_अभिव्यक्ति(e)) {
        ret = AVERROR(EINVAL);
        गच्छ end;
    }
    AVExpr_जरा *r = av_realloc(e, परिमाण(*r));
    यदि (!r) {
        ret = AVERROR(ENOMEM);
        गच्छ end;
    }
    e = (AVExpr*)r;
    e->जरा = 1;
    r->var= av_mallocz(परिमाण(द्विगुण) *VARS);
    r->prng_state = av_mallocz(परिमाण(*r->prng_state) *VARS);
    यदि (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        गच्छ end;
    }
    *अभिव्यक्ति = e;
    e = रिक्त;
end:
    av_अभिव्यक्ति_free(e);
    av_free(w);
    फर्काऊ ret;
}

स्थिर पूर्णाङ्क अभिव्यक्ति_गन्ती(AVExpr *e, अचिन्हित *counter, पूर्णाङ्क size, पूर्णाङ्क type)
{
    पूर्णाङ्क i;

    यदि (!e || !counter || !size)
        फर्काऊ AVERROR(EINVAL);

    लागि (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        अभिव्यक्ति_गन्ती(e->param[i], counter, size, type);

    यदि (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    फर्काऊ 0;
}

पूर्णाङ्क av_अभिव्यक्ति_गन्ती_vars(AVExpr *e, अचिन्हित *counter, पूर्णाङ्क size)
{
    फर्काऊ अभिव्यक्ति_गन्ती(e, counter, size, e_const);
}

पूर्णाङ्क av_अभिव्यक्ति_गन्ती_func(AVExpr *e, अचिन्हित *counter, पूर्णाङ्क size, पूर्णाङ्क arg)
{
    फर्काऊ अभिव्यक्ति_गन्ती(e, counter, size, ((पूर्णाङ्क[]){e_const, e_func1, e_func2})[arg]);
}

द्विगुण av_अभिव्यक्ति_eval(AVExpr *e, अचर द्विगुण *const_मानहरू, शून्य *opaque)
{
    av_assert1(e->जरा);
    AVExpr_जरा *r = (AVExpr_जरा *)e;
    Parser p = {
        .class        = &eval_class,
        .const_मानहरू = const_मानहरू,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    फर्काऊ eval_अभिव्यक्ति(&p, e);
}

पूर्णाङ्क av_अभिव्यक्ति_parse_and_eval(द्विगुण *d, अचर वर्ण *s,
                           अचर वर्ण * अचर *const_names, अचर द्विगुण *const_मानहरू,
                           अचर वर्ण * अचर *func1_names, द्विगुण (* अचर *funcs1)(शून्य *, द्विगुण),
                           अचर वर्ण * अचर *func2_names, द्विगुण (* अचर *funcs2)(शून्य *, द्विगुण, द्विगुण),
                           शून्य *opaque, पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    AVExpr *e = रिक्त;
    पूर्णाङ्क ret = av_अभिव्यक्ति_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    यदि (ret < 0) {
        *d = न_अंक;
        फर्काऊ ret;
    }
    *d = av_अभिव्यक्ति_eval(e, const_मानहरू, opaque);
    av_अभिव्यक्ति_free(e);
    फर्काऊ isnan(*d) ? AVERROR(EINVAL) : 0;
}
