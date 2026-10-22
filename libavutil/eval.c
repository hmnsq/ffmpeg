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

प्रकारव्याख्या संरचना Parser {
    स्थिरांक AVClass *class;
    पूर्णांक चळत_index;
    अक्षर *s;
    स्थिरांक द्विगुण *const_मूल्ये;
    स्थिरांक अक्षर * स्थिरांक *const_names;          // NULL terminated
    द्विगुण (* स्थिरांक *funcs1)(शून्य *, द्विगुण a);           // NULL terminated
    स्थिरांक अक्षर * स्थिरांक *func1_names;          // NULL terminated
    द्विगुण (* स्थिरांक *funcs2)(शून्य *, द्विगुण a, द्विगुण b); // NULL terminated
    स्थिरांक अक्षर * स्थिरांक *func2_names;          // NULL terminated
    शून्य *opaque;
    पूर्णांक log_offset;
    शून्य *log_ctx;
#define VARS 10
    द्विगुण *var;
    FFSFC64 *prng_state;
} Parser;

स्थिर स्थिरांक AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(Parser, log_offset),
    .parent_log_context_offset = दुरत्व(Parser, log_ctx),
};

स्थिर स्थिरांक संरचना {
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

स्थिर स्थिरांक संरचना {
    स्थिरांक अक्षर *name;
    द्विगुण मूल्य;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

द्विगुण av_strtod(स्थिरांक अक्षर *numstr, अक्षर **tail)
{
    द्विगुण d;
    अक्षर *next;
    जर(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = म_से_अदीर्घ(numstr, &next, 16);
    } अन्यथा
        d = म_से_भग्न(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    जर (next!=numstr) {
        जर (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } अन्यथा जर (*next >= 'E' && *next <= 'z') {
            पूर्णांक e= si_prefixes[*next - 'E'].exp;
            जर (e) {
                जर (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } अन्यथा {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        जर (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    जर (tail)
        *tail = next;
    परत d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

स्थिर पूर्णांक strmatch(स्थिरांक अक्षर *s, स्थिरांक अक्षर *prefix)
{
    पूर्णांक i;
    साठी (i=0; prefix[i]; i++) {
        जर (prefix[i] != s[i]) परत 0;
    }
    /* return 1 only if the s identifier is terminated */
    परत !IS_IDENTIFIER_CHAR(s[i]);
}

गणना {
    e_मूल्य, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_मूळ, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
संरचना AVExpr {
    अचिन्हित अक्षर type;
    अचिन्हित अक्षर मूळ;
    लघु depth;
    पूर्णांक const_index;
    द्विगुण मूल्य; // is sign in other types
    संघ {
        द्विगुण (*func0)(द्विगुण);
        द्विगुण (*func1)(शून्य *, द्विगुण);
        द्विगुण (*func2)(शून्य *, द्विगुण, द्विगुण);
    } ;
    संरचना AVExpr *param[3];
};

प्रकारव्याख्या संरचना {
    AVExpr avexpr;
    द्विगुण *var;
    FFSFC64 *prng_state;
} AVExpr_मूळ;

स्थिर द्विगुण etime(द्विगुण v)
{
    परत av_gettime() * 0.000001;
}

स्थिर द्विगुण eval_अभिव्यक्ती(Parser *p, AVExpr *e)
{
    निवड (e->type) {
        स्थिती e_मूल्य:  परत e->मूल्य;
        स्थिती e_const:  परत e->मूल्य * p->const_मूल्ये[e->const_index];
        स्थिती e_func0:  परत e->मूल्य * e->func0(eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_func1:  परत e->मूल्य * e->func1(p->opaque, eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_func2:  परत e->मूल्य * e->func2(p->opaque, eval_अभिव्यक्ती(p, e->param[0]), eval_अभिव्यक्ती(p, e->param[1]));
        स्थिती e_squish: परत e->मूल्य/(1+exp(4*eval_अभिव्यक्ती(p, e->param[0])));
        स्थिती e_gauss: { द्विगुण d = eval_अभिव्यक्ती(p, e->param[0]); परत e->मूल्य * exp(-d*d/2)/वर्ग_मूल(2*M_PI); }
        स्थिती e_ld:     परत e->मूल्य * p->var[av_clip(eval_अभिव्यक्ती(p, e->param[0]), 0, VARS-1)];
        स्थिती e_isnan:  परत e->मूल्य * !!isnan(eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_isinf:  परत e->मूल्य * !!isinf(eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_floor:  परत e->मूल्य * न्यूनमान(eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_ceil :  परत e->मूल्य * उच्चमान (eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_trunc:  परत e->मूल्य * trunc(eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_round:  परत e->मूल्य * round(eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_sgn:    परत e->मूल्य * FFDIFFSIGN(eval_अभिव्यक्ती(p, e->param[0]), 0);
        स्थिती e_sqrt:   परत e->मूल्य * वर्ग_मूल (eval_अभिव्यक्ती(p, e->param[0]));
        स्थिती e_not:    परत e->मूल्य * (eval_अभिव्यक्ती(p, e->param[0]) == 0);
        स्थिती e_if:     परत e->मूल्य * (eval_अभिव्यक्ती(p, e->param[0]) ? eval_अभिव्यक्ती(p, e->param[1]) :
                                          e->param[2] ? eval_अभिव्यक्ती(p, e->param[2]) : 0);
        स्थिती e_ifnot:  परत e->मूल्य * (!eval_अभिव्यक्ती(p, e->param[0]) ? eval_अभिव्यक्ती(p, e->param[1]) :
                                          e->param[2] ? eval_अभिव्यक्ती(p, e->param[2]) : 0);
        स्थिती e_clip: {
            द्विगुण x = eval_अभिव्यक्ती(p, e->param[0]);
            द्विगुण min = eval_अभिव्यक्ती(p, e->param[1]), max = eval_अभिव्यक्ती(p, e->param[2]);
            जर (isnan(min) || isnan(max) || isnan(x) || min > max)
                परत न_अंक;
            परत e->मूल्य * av_clipd(x, min, max);
        }
        स्थिती e_between: {
            द्विगुण d = eval_अभिव्यक्ती(p, e->param[0]);
            परत e->मूल्य * (d >= eval_अभिव्यक्ती(p, e->param[1]) &&
                               d <= eval_अभिव्यक्ती(p, e->param[2]));
        }
        स्थिती e_lerp: {
            द्विगुण v0 = eval_अभिव्यक्ती(p, e->param[0]);
            द्विगुण v1 = eval_अभिव्यक्ती(p, e->param[1]);
            द्विगुण f  = eval_अभिव्यक्ती(p, e->param[2]);
            परत e->मूल्य * (v0 + (v1 - v0) * f);
        }
        स्थिती e_print: {
            द्विगुण x = eval_अभिव्यक्ती(p, e->param[0]);
            पूर्णांक level = e->param[1] ? av_clip(eval_अभिव्यक्ती(p, e->param[1]), पूर्णांक_न्यून, पूर्णांक_उच्च) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            परत e->मूल्य * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            पूर्णांक idx = av_clip(eval_अभिव्यक्ती(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            जर (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        स्थिती e_random: {
            COMPUTE_NEXT_RANDOM();
            परत r * (1.0/UINT64_MAX);
        }
        स्थिती e_randomi: {
            द्विगुण min = eval_अभिव्यक्ती(p, e->param[1]);
            द्विगुण max = eval_अभिव्यक्ती(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            परत min + (max - min) * r / UINT64_MAX;
        }
        स्थिती e_while: {
            द्विगुण d = न_अंक;
            पर्यंत (eval_अभिव्यक्ती(p, e->param[0]))
                d=eval_अभिव्यक्ती(p, e->param[1]);
            परत d;
        }
        स्थिती e_taylor: {
            द्विगुण t = 1, d = 0, v;
            द्विगुण x = eval_अभिव्यक्ती(p, e->param[1]);
            पूर्णांक id = e->param[2] ? av_clip(eval_अभिव्यक्ती(p, e->param[2]), 0, VARS-1) : 0;
            पूर्णांक i;
            द्विगुण var0 = p->var[id];
            साठी(i=0; i<1000; i++) {
                द्विगुण ld = d;
                p->var[id] = i;
                v = eval_अभिव्यक्ती(p, e->param[0]);
                d += t*v;
                जर(ld==d && v)
                    थांबा;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            परत d;
        }
        स्थिती e_मूळ: {
            पूर्णांक i, j;
            द्विगुण खालचा = -1, वरचा = -1, v, खालचा_v = -द्विग_उच्च, वरचा_v = द्विग_उच्च;
            द्विगुण var0 = p->var[0];
            द्विगुण x_max = eval_अभिव्यक्ती(p, e->param[1]);
            साठी(i=-1; i<1024; i++) {
                जर(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } अन्यथा {
                    p->var[0] = x_max*घात(0.9, i-255);
                    जर (i&1) p->var[0] *= -1;
                    जर (i&2) p->var[0] += खालचा;
                    अन्यथा     p->var[0] += वरचा;
                }
                v = eval_अभिव्यक्ती(p, e->param[0]);
                जर (v<=0 && v>खालचा_v) {
                    खालचा    = p->var[0];
                    खालचा_v  = v;
                }
                जर (v>=0 && v<वरचा_v) {
                    वरचा   = p->var[0];
                    वरचा_v = v;
                }
                जर (खालचा>=0 && वरचा>=0){
                    साठी (j=0; j<1000; j++) {
                        p->var[0] = (खालचा+वरचा)*0.5;
                        जर (खालचा == p->var[0] || वरचा == p->var[0])
                            थांबा;
                        v = eval_अभिव्यक्ती(p, e->param[0]);
                        जर (v<=0) खालचा = p->var[0];
                        जर (v>=0) वरचा= p->var[0];
                        जर (isnan(v)) {
                            खालचा = वरचा = v;
                            थांबा;
                        }
                    }
                    थांबा;
                }
            }
            p->var[0] = var0;
            परत -खालचा_v<वरचा_v ? खालचा : वरचा;
        }
        पूर्वनिर्धारित: {
            द्विगुण d = eval_अभिव्यक्ती(p, e->param[0]);
            द्विगुण d2 = eval_अभिव्यक्ती(p, e->param[1]);
            निवड (e->type) {
                स्थिती e_mod: परत e->मूल्य * (d - न्यूनमान(d2 ? d / d2 : d * अनन्त) * d2);
                स्थिती e_gcd: परत e->मूल्य * av_gcd(d,d2);
                स्थिती e_max: परत e->मूल्य * (d >  d2 ?   d : d2);
                स्थिती e_min: परत e->मूल्य * (d <  d2 ?   d : d2);
                स्थिती e_eq:  परत e->मूल्य * (d == d2 ? 1.0 : 0.0);
                स्थिती e_gt:  परत e->मूल्य * (d >  d2 ? 1.0 : 0.0);
                स्थिती e_gte: परत e->मूल्य * (d >= d2 ? 1.0 : 0.0);
                स्थिती e_lt:  परत e->मूल्य * (d <  d2 ? 1.0 : 0.0);
                स्थिती e_lte: परत e->मूल्य * (d <= d2 ? 1.0 : 0.0);
                स्थिती e_pow: परत e->मूल्य * घात(d, d2);
                स्थिती e_mul: परत e->मूल्य * (d * d2);
                स्थिती e_div: परत e->मूल्य * (d2 ? (d / d2) : d * अनन्त);
                स्थिती e_add: परत e->मूल्य * (d + d2);
                स्थिती e_last:परत e->मूल्य * d2;
                स्थिती e_st :  {
                    पूर्णांक index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    परत e->मूल्य * (p->var[index]= d2);
                }
                स्थिती e_hypot:परत e->मूल्य * hypot(d, d2);
                स्थिती e_atan2:परत e->मूल्य * atan2(d, d2);
                स्थिती e_bitand: परत isnan(d) || isnan(d2) ? न_अंक : e->मूल्य * ((दीर्घ पूर्णांक)d & (दीर्घ पूर्णांक)d2);
                स्थिती e_bitor:  परत isnan(d) || isnan(d2) ? न_अंक : e->मूल्य * ((दीर्घ पूर्णांक)d | (दीर्घ पूर्णांक)d2);
            }
        }
    }
    परत न_अंक;
}

स्थिर पूर्णांक parse_अभिव्यक्ती(AVExpr **e, Parser *p);

शून्य av_अभिव्यक्ती_free(AVExpr *e)
{
    जर (!e) परत;
    av_अभिव्यक्ती_free(e->param[0]);
    av_अभिव्यक्ती_free(e->param[1]);
    av_अभिव्यक्ती_free(e->param[2]);
    जर (e->मूळ) {
        AVExpr_मूळ *r = (AVExpr_मूळ*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

स्थिर पूर्णांक parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(आकार(AVExpr));
    अक्षर *next = p->s, *s0 = p->s;
    पूर्णांक ret, i;

    जर (!d)
        परत AVERROR(ENOMEM);

    /*संख्या*/
    d->मूल्य = av_strtod(p->s, &next);
    जर (next != p->s) {
        d->type = e_मूल्य;
        p->s= next;
        *e = d;
        परत 0;
    }
    d->मूल्य = 1;

    /* named constants */
    साठी (i=0; p->const_names && p->const_names[i]; i++) {
        जर (strmatch(p->s, p->const_names[i])) {
            p->s+= म_माप(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            परत 0;
        }
    }
    साठी (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        जर (strmatch(p->s, constants[i].name)) {
            p->s += म_माप(constants[i].name);
            d->type = e_मूल्य;
            d->मूल्य = constants[i].मूल्य;
            *e = d;
            परत 0;
        }
    }

    p->s= म_अक्षर(p->s, '(');
    जर (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_अभिव्यक्ती_free(d);
        परत AVERROR(EINVAL);
    }
    p->s++; // "("
    जर (*next == '(') { // special case do-nothing
        av_freep(&d);
        जर ((ret = parse_अभिव्यक्ती(&d, p)) < 0)
            परत ret;
        जर (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_अभिव्यक्ती_free(d);
            परत AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        परत 0;
    }
    जर ((ret = parse_अभिव्यक्ती(&(d->param[0]), p)) < 0) {
        av_अभिव्यक्ती_free(d);
        परत ret;
    }
    जर (p->s[0]== ',') {
        p->s++; // ","
        parse_अभिव्यक्ती(&d->param[1], p);
    }
    जर (p->s[0]== ',') {
        p->s++; // ","
        parse_अभिव्यक्ती(&d->param[2], p);
    }
    जर (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_अभिव्यक्ती_free(d);
        परत AVERROR(EINVAL);
    }
    p->s++; // ")"

    साठी (पूर्णांक i = 0; i<3; i++)
        जर (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    जर (d->depth > MAX_DEPTH) {
        av_अभिव्यक्ती_free(d);
        परत AVERROR(EINVAL);
    }

    d->type = e_func0;
         जर (strmatch(next, "sinh"  )) d->func0 = sinh;
    अन्यथा जर (strmatch(next, "cosh"  )) d->func0 = cosh;
    अन्यथा जर (strmatch(next, "tanh"  )) d->func0 = tanh;
    अन्यथा जर (strmatch(next, "sin"   )) d->func0 = sin;
    अन्यथा जर (strmatch(next, "cos"   )) d->func0 = cos;
    अन्यथा जर (strmatch(next, "tan"   )) d->func0 = tan;
    अन्यथा जर (strmatch(next, "atan"  )) d->func0 = atan;
    अन्यथा जर (strmatch(next, "asin"  )) d->func0 = asin;
    अन्यथा जर (strmatch(next, "acos"  )) d->func0 = acos;
    अन्यथा जर (strmatch(next, "exp"   )) d->func0 = exp;
    अन्यथा जर (strmatch(next, "log"   )) d->func0 = log;
    अन्यथा जर (strmatch(next, "abs"   )) d->func0 = भ_असल;
    अन्यथा जर (strmatch(next, "time"  )) d->func0 = etime;
    अन्यथा जर (strmatch(next, "squish")) d->type = e_squish;
    अन्यथा जर (strmatch(next, "gauss" )) d->type = e_gauss;
    अन्यथा जर (strmatch(next, "mod"   )) d->type = e_mod;
    अन्यथा जर (strmatch(next, "max"   )) d->type = e_max;
    अन्यथा जर (strmatch(next, "min"   )) d->type = e_min;
    अन्यथा जर (strmatch(next, "eq"    )) d->type = e_eq;
    अन्यथा जर (strmatch(next, "gte"   )) d->type = e_gte;
    अन्यथा जर (strmatch(next, "gt"    )) d->type = e_gt;
    अन्यथा जर (strmatch(next, "lte"   )) d->type = e_lte;
    अन्यथा जर (strmatch(next, "lt"    )) d->type = e_lt;
    अन्यथा जर (strmatch(next, "ld"    )) d->type = e_ld;
    अन्यथा जर (strmatch(next, "isnan" )) d->type = e_isnan;
    अन्यथा जर (strmatch(next, "isinf" )) d->type = e_isinf;
    अन्यथा जर (strmatch(next, "st"    )) d->type = e_st;
    अन्यथा जर (strmatch(next, "while" )) d->type = e_while;
    अन्यथा जर (strmatch(next, "taylor")) d->type = e_taylor;
    अन्यथा जर (strmatch(next, "root"  )) d->type = e_मूळ;
    अन्यथा जर (strmatch(next, "floor" )) d->type = e_floor;
    अन्यथा जर (strmatch(next, "ceil"  )) d->type = e_ceil;
    अन्यथा जर (strmatch(next, "trunc" )) d->type = e_trunc;
    अन्यथा जर (strmatch(next, "round" )) d->type = e_round;
    अन्यथा जर (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    अन्यथा जर (strmatch(next, "not"   )) d->type = e_not;
    अन्यथा जर (strmatch(next, "pow"   )) d->type = e_pow;
    अन्यथा जर (strmatch(next, "print" )) d->type = e_print;
    अन्यथा जर (strmatch(next, "random")) d->type = e_random;
    अन्यथा जर (strmatch(next, "randomi")) d->type = e_randomi;
    अन्यथा जर (strmatch(next, "hypot" )) d->type = e_hypot;
    अन्यथा जर (strmatch(next, "gcd"   )) d->type = e_gcd;
    अन्यथा जर (strmatch(next, "if"    )) d->type = e_if;
    अन्यथा जर (strmatch(next, "ifnot" )) d->type = e_ifnot;
    अन्यथा जर (strmatch(next, "bitand")) d->type = e_bitand;
    अन्यथा जर (strmatch(next, "bitor" )) d->type = e_bitor;
    अन्यथा जर (strmatch(next, "between"))d->type = e_between;
    अन्यथा जर (strmatch(next, "clip"  )) d->type = e_clip;
    अन्यथा जर (strmatch(next, "atan2" )) d->type = e_atan2;
    अन्यथा जर (strmatch(next, "lerp"  )) d->type = e_lerp;
    अन्यथा जर (strmatch(next, "sgn"   )) d->type = e_sgn;
    अन्यथा {
        साठी (i=0; p->func1_names && p->func1_names[i]; i++) {
            जर (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                परत 0;
            }
        }

        साठी (i=0; p->func2_names && p->func2_names[i]; i++) {
            जर (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                परत 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_अभिव्यक्ती_free(d);
        परत AVERROR(EINVAL);
    }

    *e = d;
    परत 0;
}

स्थिर AVExpr *make_eval_अभिव्यक्ती(पूर्णांक type, पूर्णांक मूल्य, AVExpr *p0, AVExpr *p1)
{
    पूर्णांक depth = FFMAX(p0->depth, p1->depth) + 1;
    जर (depth > MAX_DEPTH)
        परत रिक्त;
    AVExpr *e = av_mallocz(आकार(AVExpr));
    जर (!e)
        परत रिक्त;
    e->type     =type   ;
    e->मूल्य    =मूल्य  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    परत e;
}

स्थिर पूर्णांक parse_pow(AVExpr **e, Parser *p, पूर्णांक *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    परत parse_primary(e, p);
}

स्थिर पूर्णांक parse_dB(AVExpr **e, Parser *p, पूर्णांक *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    जर (*p->s == '-') {
        अक्षर *next;
        av_unused द्विगुण ignored = म_से_भग्न(p->s, &next);
        जर (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            परत parse_primary(e, p);
        }
    }
    परत parse_pow(e, p, sign);
}

स्थिर पूर्णांक parse_factor(AVExpr **e, Parser *p)
{
    पूर्णांक sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    जर ((ret = parse_dB(&e0, p, &sign)) < 0)
        परत ret;
    पर्यंत(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        जर ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_अभिव्यक्ती_free(e1);
            परत ret;
        }
        e0 = make_eval_अभिव्यक्ती(e_pow, 1, e1, e2);
        जर (!e0) {
            av_अभिव्यक्ती_free(e1);
            av_अभिव्यक्ती_free(e2);
            परत AVERROR(ENOMEM);
        }
        जर (e0->param[1]) e0->param[1]->मूल्य *= (sign2|1);
    }
    जर (e0) e0->मूल्य *= (sign|1);

    *e = e0;
    परत 0;
}

स्थिर पूर्णांक parse_term(AVExpr **e, Parser *p)
{
    पूर्णांक ret;
    AVExpr *e0, *e1, *e2;
    जर ((ret = parse_factor(&e0, p)) < 0)
        परत ret;
    पर्यंत (p->s[0]=='*' || p->s[0]=='/') {
        पूर्णांक c= *p->s++;
        e1 = e0;
        जर ((ret = parse_factor(&e2, p)) < 0) {
            av_अभिव्यक्ती_free(e1);
            परत ret;
        }
        e0 = make_eval_अभिव्यक्ती(c == '*' ? e_mul : e_div, 1, e1, e2);
        जर (!e0) {
            av_अभिव्यक्ती_free(e1);
            av_अभिव्यक्ती_free(e2);
            परत AVERROR(ENOMEM);
        }
    }
    *e = e0;
    परत 0;
}

स्थिर पूर्णांक parse_subexpr(AVExpr **e, Parser *p)
{
    पूर्णांक ret;
    AVExpr *e0, *e1, *e2;
    जर ((ret = parse_term(&e0, p)) < 0)
        परत ret;
    पर्यंत (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        जर ((ret = parse_term(&e2, p)) < 0) {
            av_अभिव्यक्ती_free(e1);
            परत ret;
        }
        e0 = make_eval_अभिव्यक्ती(e_add, 1, e1, e2);
        जर (!e0) {
            av_अभिव्यक्ती_free(e1);
            av_अभिव्यक्ती_free(e2);
            परत AVERROR(ENOMEM);
        }
    };

    *e = e0;
    परत 0;
}

स्थिर पूर्णांक parse_अभिव्यक्ती(AVExpr **e, Parser *p)
{
    पूर्णांक ret;
    AVExpr *e0, *e1, *e2;
    जर (p->चळत_index <= 0) //protect against stack overflows
        परत AVERROR(EINVAL);
    p->चळत_index--;

    जर ((ret = parse_subexpr(&e0, p)) < 0)
        परत ret;
    पर्यंत (*p->s == ';') {
        p->s++;
        e1 = e0;
        जर ((ret = parse_subexpr(&e2, p)) < 0) {
            av_अभिव्यक्ती_free(e1);
            परत ret;
        }
        e0 = make_eval_अभिव्यक्ती(e_last, 1, e1, e2);
        जर (!e0) {
            av_अभिव्यक्ती_free(e1);
            av_अभिव्यक्ती_free(e2);
            परत AVERROR(ENOMEM);
        }
    };

    p->चळत_index++;
    *e = e0;
    परत 0;
}

स्थिर पूर्णांक verify_अभिव्यक्ती(AVExpr *e)
{
    जर (!e) परत 0;
    निवड (e->type) {
        स्थिती e_मूल्य:
        स्थिती e_const: परत 1;
        स्थिती e_func0:
        स्थिती e_func1:
        स्थिती e_squish:
        स्थिती e_ld:
        स्थिती e_gauss:
        स्थिती e_isnan:
        स्थिती e_isinf:
        स्थिती e_floor:
        स्थिती e_ceil:
        स्थिती e_trunc:
        स्थिती e_round:
        स्थिती e_sqrt:
        स्थिती e_not:
        स्थिती e_random:
        स्थिती e_sgn:
            परत verify_अभिव्यक्ती(e->param[0]) && !e->param[1];
        स्थिती e_print:
            परत verify_अभिव्यक्ती(e->param[0])
                   && (!e->param[1] || verify_अभिव्यक्ती(e->param[1]));
        स्थिती e_if:
        स्थिती e_ifnot:
        स्थिती e_taylor:
            परत verify_अभिव्यक्ती(e->param[0]) && verify_अभिव्यक्ती(e->param[1])
                   && (!e->param[2] || verify_अभिव्यक्ती(e->param[2]));
        स्थिती e_between:
        स्थिती e_clip:
        स्थिती e_lerp:
        स्थिती e_randomi:
            परत verify_अभिव्यक्ती(e->param[0]) &&
                   verify_अभिव्यक्ती(e->param[1]) &&
                   verify_अभिव्यक्ती(e->param[2]);
        पूर्वनिर्धारित: परत verify_अभिव्यक्ती(e->param[0]) && verify_अभिव्यक्ती(e->param[1]) && !e->param[2];
    }
}

पूर्णांक av_अभिव्यक्ती_parse(AVExpr **अभिव्यक्ती, स्थिरांक अक्षर *s,
                  स्थिरांक अक्षर * स्थिरांक *const_names,
                  स्थिरांक अक्षर * स्थिरांक *func1_names, द्विगुण (* स्थिरांक *funcs1)(शून्य *, द्विगुण),
                  स्थिरांक अक्षर * स्थिरांक *func2_names, द्विगुण (* स्थिरांक *funcs2)(शून्य *, द्विगुण, द्विगुण),
                  पूर्णांक log_offset, शून्य *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = रिक्त;
    अक्षर *w = av_malloc(म_माप(s) + 1);
    अक्षर *wp = w;
    स्थिरांक अक्षर *s0 = s;
    पूर्णांक ret = 0;

    जर (!w)
        परत AVERROR(ENOMEM);

    पर्यंत (*s)
        जर (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.चळत_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    जर ((ret = parse_अभिव्यक्ती(&e, &p)) < 0)
        जा end;
    जर (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        जा end;
    }
    जर (!verify_अभिव्यक्ती(e)) {
        ret = AVERROR(EINVAL);
        जा end;
    }
    AVExpr_मूळ *r = av_realloc(e, आकार(*r));
    जर (!r) {
        ret = AVERROR(ENOMEM);
        जा end;
    }
    e = (AVExpr*)r;
    e->मूळ = 1;
    r->var= av_mallocz(आकार(द्विगुण) *VARS);
    r->prng_state = av_mallocz(आकार(*r->prng_state) *VARS);
    जर (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        जा end;
    }
    *अभिव्यक्ती = e;
    e = रिक्त;
end:
    av_अभिव्यक्ती_free(e);
    av_free(w);
    परत ret;
}

स्थिर पूर्णांक अभिव्यक्ती_मोजणी(AVExpr *e, अचिन्हित *counter, पूर्णांक size, पूर्णांक type)
{
    पूर्णांक i;

    जर (!e || !counter || !size)
        परत AVERROR(EINVAL);

    साठी (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        अभिव्यक्ती_मोजणी(e->param[i], counter, size, type);

    जर (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    परत 0;
}

पूर्णांक av_अभिव्यक्ती_मोजणी_vars(AVExpr *e, अचिन्हित *counter, पूर्णांक size)
{
    परत अभिव्यक्ती_मोजणी(e, counter, size, e_const);
}

पूर्णांक av_अभिव्यक्ती_मोजणी_func(AVExpr *e, अचिन्हित *counter, पूर्णांक size, पूर्णांक arg)
{
    परत अभिव्यक्ती_मोजणी(e, counter, size, ((पूर्णांक[]){e_const, e_func1, e_func2})[arg]);
}

द्विगुण av_अभिव्यक्ती_eval(AVExpr *e, स्थिरांक द्विगुण *const_मूल्ये, शून्य *opaque)
{
    av_assert1(e->मूळ);
    AVExpr_मूळ *r = (AVExpr_मूळ *)e;
    Parser p = {
        .class        = &eval_class,
        .const_मूल्ये = const_मूल्ये,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    परत eval_अभिव्यक्ती(&p, e);
}

पूर्णांक av_अभिव्यक्ती_parse_and_eval(द्विगुण *d, स्थिरांक अक्षर *s,
                           स्थिरांक अक्षर * स्थिरांक *const_names, स्थिरांक द्विगुण *const_मूल्ये,
                           स्थिरांक अक्षर * स्थिरांक *func1_names, द्विगुण (* स्थिरांक *funcs1)(शून्य *, द्विगुण),
                           स्थिरांक अक्षर * स्थिरांक *func2_names, द्विगुण (* स्थिरांक *funcs2)(शून्य *, द्विगुण, द्विगुण),
                           शून्य *opaque, पूर्णांक log_offset, शून्य *log_ctx)
{
    AVExpr *e = रिक्त;
    पूर्णांक ret = av_अभिव्यक्ती_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    जर (ret < 0) {
        *d = न_अंक;
        परत ret;
    }
    *d = av_अभिव्यक्ती_eval(e, const_मूल्ये, opaque);
    av_अभिव्यक्ती_free(e);
    परत isnan(*d) ? AVERROR(EINVAL) : 0;
}
