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

#समावेश <float.h>
#समावेश "attributes.h"
#समावेश "avassert.h"
#समावेश "avutil.h"
#समावेश "common.h"
#समावेश "eval.h"
#समावेश "ffmath.h"
#समावेश "log.h"
#समावेश "mathematics.h"
#समावेश "mem.h"
#समावेश "sfc64.h"
#समावेश "time.h"
#समावेश "avstring.h"
#समावेश "reverse.h"

#घोषणा MAX_DEPTH 100

प्रकार काष्ठा Parser {
    स्थिर AVClass *class;
    पूर्णांक ढेर_सूचकांक;
    अक्षर *s;
    स्थिर द्विगुन *const_मूल्यावली;
    स्थिर अक्षर * स्थिर *const_names;          // NULL terminated
    द्विगुन (* स्थिर *funcs1)(व्योम *, द्विगुन a);           // NULL terminated
    स्थिर अक्षर * स्थिर *func1_names;          // NULL terminated
    द्विगुन (* स्थिर *funcs2)(व्योम *, द्विगुन a, द्विगुन b); // NULL terminated
    स्थिर अक्षर * स्थिर *func2_names;          // NULL terminated
    व्योम *opaque;
    पूर्णांक log_offset;
    व्योम *log_ctx;
#घोषणा VARS 10
    द्विगुन *var;
    FFSFC64 *prng_state;
} Parser;

अटल स्थिर AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = शून्य,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(Parser, log_offset),
    .parent_log_context_offset = दुरत्व(Parser, log_ctx),
};

अटल स्थिर काष्ठा {
    द्विगुन bin_val;
    द्विगुन dec_val;
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

अटल स्थिर काष्ठा {
    स्थिर अक्षर *name;
    द्विगुन मूल्य;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

द्विगुन av_strtod(स्थिर अक्षर *numstr, अक्षर **पुच्छ)
{
    द्विगुन d;
    अक्षर *अग्र;
    अगर(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = म_से_अदीर्घ(numstr, &अग्र, 16);
    } अन्यथा
        d = म_से_भग्न(numstr, &अग्र);
    /* if parsing succeeded, check for and interpret postfixes */
    अगर (अग्र!=numstr) {
        अगर (अग्र[0] == 'd' && अग्र[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            अग्र += 2;
        } अन्यथा अगर (*अग्र >= 'E' && *अग्र <= 'z') {
            पूर्णांक e= si_prefixes[*अग्र - 'E'].exp;
            अगर (e) {
                अगर (अग्र[1] == 'i') {
                    d*= si_prefixes[*अग्र - 'E'].bin_val;
                    अग्र+=2;
                } अन्यथा {
                    d*= si_prefixes[*अग्र - 'E'].dec_val;
                    अग्र++;
                }
            }
        }

        अगर (*अग्र=='B') {
            d*=8;
            अग्र++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    अगर (पुच्छ)
        *पुच्छ = अग्र;
    वापस d;
}

#घोषणा IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

अटल पूर्णांक strmatch(स्थिर अक्षर *s, स्थिर अक्षर *prefix)
{
    पूर्णांक i;
    क्रम (i=0; prefix[i]; i++) {
        अगर (prefix[i] != s[i]) वापस 0;
    }
    /* return 1 only if the s identifier is terminated */
    वापस !IS_IDENTIFIER_CHAR(s[i]);
}

क्रमागत {
    e_मूल्य, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_मूल, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
काष्ठा AVExpr {
    अचिन्हित अक्षर type;
    अचिन्हित अक्षर मूल;
    लघु depth;
    पूर्णांक const_सूचकांक;
    द्विगुन मूल्य; // is sign in other types
    जोड़ {
        द्विगुन (*func0)(द्विगुन);
        द्विगुन (*func1)(व्योम *, द्विगुन);
        द्विगुन (*func2)(व्योम *, द्विगुन, द्विगुन);
    } ;
    काष्ठा AVExpr *param[3];
};

प्रकार काष्ठा {
    AVExpr avexpr;
    द्विगुन *var;
    FFSFC64 *prng_state;
} AVExpr_मूल;

अटल द्विगुन etime(द्विगुन v)
{
    वापस av_gettime() * 0.000001;
}

अटल द्विगुन eval_व्यंजक(Parser *p, AVExpr *e)
{
    चयन (e->type) {
        हाल e_मूल्य:  वापस e->मूल्य;
        हाल e_const:  वापस e->मूल्य * p->const_मूल्यावली[e->const_सूचकांक];
        हाल e_func0:  वापस e->मूल्य * e->func0(eval_व्यंजक(p, e->param[0]));
        हाल e_func1:  वापस e->मूल्य * e->func1(p->opaque, eval_व्यंजक(p, e->param[0]));
        हाल e_func2:  वापस e->मूल्य * e->func2(p->opaque, eval_व्यंजक(p, e->param[0]), eval_व्यंजक(p, e->param[1]));
        हाल e_squish: वापस e->मूल्य/(1+exp(4*eval_व्यंजक(p, e->param[0])));
        हाल e_gauss: { द्विगुन d = eval_व्यंजक(p, e->param[0]); वापस e->मूल्य * exp(-d*d/2)/वर्ग_मूल(2*M_PI); }
        हाल e_ld:     वापस e->मूल्य * p->var[av_clip(eval_व्यंजक(p, e->param[0]), 0, VARS-1)];
        हाल e_isnan:  वापस e->मूल्य * !!isnan(eval_व्यंजक(p, e->param[0]));
        हाल e_isinf:  वापस e->मूल्य * !!isinf(eval_व्यंजक(p, e->param[0]));
        हाल e_floor:  वापस e->मूल्य * न्यूनमान(eval_व्यंजक(p, e->param[0]));
        हाल e_ceil :  वापस e->मूल्य * उच्चमान (eval_व्यंजक(p, e->param[0]));
        हाल e_trunc:  वापस e->मूल्य * trunc(eval_व्यंजक(p, e->param[0]));
        हाल e_round:  वापस e->मूल्य * round(eval_व्यंजक(p, e->param[0]));
        हाल e_sgn:    वापस e->मूल्य * FFDIFFSIGN(eval_व्यंजक(p, e->param[0]), 0);
        हाल e_sqrt:   वापस e->मूल्य * वर्ग_मूल (eval_व्यंजक(p, e->param[0]));
        हाल e_not:    वापस e->मूल्य * (eval_व्यंजक(p, e->param[0]) == 0);
        हाल e_if:     वापस e->मूल्य * (eval_व्यंजक(p, e->param[0]) ? eval_व्यंजक(p, e->param[1]) :
                                          e->param[2] ? eval_व्यंजक(p, e->param[2]) : 0);
        हाल e_ifnot:  वापस e->मूल्य * (!eval_व्यंजक(p, e->param[0]) ? eval_व्यंजक(p, e->param[1]) :
                                          e->param[2] ? eval_व्यंजक(p, e->param[2]) : 0);
        हाल e_clip: {
            द्विगुन x = eval_व्यंजक(p, e->param[0]);
            द्विगुन min = eval_व्यंजक(p, e->param[1]), max = eval_व्यंजक(p, e->param[2]);
            अगर (isnan(min) || isnan(max) || isnan(x) || min > max)
                वापस न_अंक;
            वापस e->मूल्य * av_clipd(x, min, max);
        }
        हाल e_between: {
            द्विगुन d = eval_व्यंजक(p, e->param[0]);
            वापस e->मूल्य * (d >= eval_व्यंजक(p, e->param[1]) &&
                               d <= eval_व्यंजक(p, e->param[2]));
        }
        हाल e_lerp: {
            द्विगुन v0 = eval_व्यंजक(p, e->param[0]);
            द्विगुन v1 = eval_व्यंजक(p, e->param[1]);
            द्विगुन f  = eval_व्यंजक(p, e->param[2]);
            वापस e->मूल्य * (v0 + (v1 - v0) * f);
        }
        हाल e_print: {
            द्विगुन x = eval_व्यंजक(p, e->param[0]);
            पूर्णांक level = e->param[1] ? av_clip(eval_व्यंजक(p, e->param[1]), पूर्णांक_न्यून, पूर्णांक_उच्च) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            वापस e->मूल्य * x;
        }

#घोषणा COMPUTE_अग्र_RANDOM()                                        \
            पूर्णांक idx = av_clip(eval_व्यंजक(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            अगर (!s->गणक) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        हाल e_random: {
            COMPUTE_अग्र_RANDOM();
            वापस r * (1.0/UINT64_MAX);
        }
        हाल e_randomi: {
            द्विगुन min = eval_व्यंजक(p, e->param[1]);
            द्विगुन max = eval_व्यंजक(p, e->param[2]);
            COMPUTE_अग्र_RANDOM();
            वापस min + (max - min) * r / UINT64_MAX;
        }
        हाल e_while: {
            द्विगुन d = न_अंक;
            जबतक (eval_व्यंजक(p, e->param[0]))
                d=eval_व्यंजक(p, e->param[1]);
            वापस d;
        }
        हाल e_taylor: {
            द्विगुन t = 1, d = 0, v;
            द्विगुन x = eval_व्यंजक(p, e->param[1]);
            पूर्णांक id = e->param[2] ? av_clip(eval_व्यंजक(p, e->param[2]), 0, VARS-1) : 0;
            पूर्णांक i;
            द्विगुन var0 = p->var[id];
            क्रम(i=0; i<1000; i++) {
                द्विगुन ld = d;
                p->var[id] = i;
                v = eval_व्यंजक(p, e->param[0]);
                d += t*v;
                अगर(ld==d && v)
                    अवरोध;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            वापस d;
        }
        हाल e_मूल: {
            पूर्णांक i, j;
            द्विगुन निचला = -1, ऊपरी = -1, v, निचला_v = -द्विग_उच्च, ऊपरी_v = द्विग_उच्च;
            द्विगुन var0 = p->var[0];
            द्विगुन x_max = eval_व्यंजक(p, e->param[1]);
            क्रम(i=-1; i<1024; i++) {
                अगर(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } अन्यथा {
                    p->var[0] = x_max*घात(0.9, i-255);
                    अगर (i&1) p->var[0] *= -1;
                    अगर (i&2) p->var[0] += निचला;
                    अन्यथा     p->var[0] += ऊपरी;
                }
                v = eval_व्यंजक(p, e->param[0]);
                अगर (v<=0 && v>निचला_v) {
                    निचला    = p->var[0];
                    निचला_v  = v;
                }
                अगर (v>=0 && v<ऊपरी_v) {
                    ऊपरी   = p->var[0];
                    ऊपरी_v = v;
                }
                अगर (निचला>=0 && ऊपरी>=0){
                    क्रम (j=0; j<1000; j++) {
                        p->var[0] = (निचला+ऊपरी)*0.5;
                        अगर (निचला == p->var[0] || ऊपरी == p->var[0])
                            अवरोध;
                        v = eval_व्यंजक(p, e->param[0]);
                        अगर (v<=0) निचला = p->var[0];
                        अगर (v>=0) ऊपरी= p->var[0];
                        अगर (isnan(v)) {
                            निचला = ऊपरी = v;
                            अवरोध;
                        }
                    }
                    अवरोध;
                }
            }
            p->var[0] = var0;
            वापस -निचला_v<ऊपरी_v ? निचला : ऊपरी;
        }
        शेष: {
            द्विगुन d = eval_व्यंजक(p, e->param[0]);
            द्विगुन d2 = eval_व्यंजक(p, e->param[1]);
            चयन (e->type) {
                हाल e_mod: वापस e->मूल्य * (d - न्यूनमान(d2 ? d / d2 : d * अनन्त) * d2);
                हाल e_gcd: वापस e->मूल्य * av_gcd(d,d2);
                हाल e_max: वापस e->मूल्य * (d >  d2 ?   d : d2);
                हाल e_min: वापस e->मूल्य * (d <  d2 ?   d : d2);
                हाल e_eq:  वापस e->मूल्य * (d == d2 ? 1.0 : 0.0);
                हाल e_gt:  वापस e->मूल्य * (d >  d2 ? 1.0 : 0.0);
                हाल e_gte: वापस e->मूल्य * (d >= d2 ? 1.0 : 0.0);
                हाल e_lt:  वापस e->मूल्य * (d <  d2 ? 1.0 : 0.0);
                हाल e_lte: वापस e->मूल्य * (d <= d2 ? 1.0 : 0.0);
                हाल e_pow: वापस e->मूल्य * घात(d, d2);
                हाल e_mul: वापस e->मूल्य * (d * d2);
                हाल e_div: वापस e->मूल्य * (d2 ? (d / d2) : d * अनन्त);
                हाल e_add: वापस e->मूल्य * (d + d2);
                हाल e_last:वापस e->मूल्य * d2;
                हाल e_st :  {
                    पूर्णांक सूचकांक = av_clip(d, 0, VARS-1);
                    p->prng_state[सूचकांक].गणक = 0;
                    वापस e->मूल्य * (p->var[सूचकांक]= d2);
                }
                हाल e_hypot:वापस e->मूल्य * hypot(d, d2);
                हाल e_atan2:वापस e->मूल्य * atan2(d, d2);
                हाल e_bitand: वापस isnan(d) || isnan(d2) ? न_अंक : e->मूल्य * ((दीर्घ पूर्णांक)d & (दीर्घ पूर्णांक)d2);
                हाल e_bitor:  वापस isnan(d) || isnan(d2) ? न_अंक : e->मूल्य * ((दीर्घ पूर्णांक)d | (दीर्घ पूर्णांक)d2);
            }
        }
    }
    वापस न_अंक;
}

अटल पूर्णांक parse_व्यंजक(AVExpr **e, Parser *p);

व्योम av_व्यंजक_free(AVExpr *e)
{
    अगर (!e) वापस;
    av_व्यंजक_free(e->param[0]);
    av_व्यंजक_free(e->param[1]);
    av_व्यंजक_free(e->param[2]);
    अगर (e->मूल) {
        AVExpr_मूल *r = (AVExpr_मूल*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

अटल पूर्णांक parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(माप(AVExpr));
    अक्षर *अग्र = p->s, *s0 = p->s;
    पूर्णांक ret, i;

    अगर (!d)
        वापस AVERROR(ENOMEM);

    /*संख्या*/
    d->मूल्य = av_strtod(p->s, &अग्र);
    अगर (अग्र != p->s) {
        d->type = e_मूल्य;
        p->s= अग्र;
        *e = d;
        वापस 0;
    }
    d->मूल्य = 1;

    /* named constants */
    क्रम (i=0; p->const_names && p->const_names[i]; i++) {
        अगर (strmatch(p->s, p->const_names[i])) {
            p->s+= म_माप(p->const_names[i]);
            d->type = e_const;
            d->const_सूचकांक = i;
            *e = d;
            वापस 0;
        }
    }
    क्रम (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        अगर (strmatch(p->s, constants[i].name)) {
            p->s += म_माप(constants[i].name);
            d->type = e_मूल्य;
            d->मूल्य = constants[i].मूल्य;
            *e = d;
            वापस 0;
        }
    }

    p->s= म_अक्षर(p->s, '(');
    अगर (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= अग्र;
        av_व्यंजक_free(d);
        वापस AVERROR(EINVAL);
    }
    p->s++; // "("
    अगर (*अग्र == '(') { // special case do-nothing
        av_freep(&d);
        अगर ((ret = parse_व्यंजक(&d, p)) < 0)
            वापस ret;
        अगर (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_व्यंजक_free(d);
            वापस AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        वापस 0;
    }
    अगर ((ret = parse_व्यंजक(&(d->param[0]), p)) < 0) {
        av_व्यंजक_free(d);
        वापस ret;
    }
    अगर (p->s[0]== ',') {
        p->s++; // ","
        parse_व्यंजक(&d->param[1], p);
    }
    अगर (p->s[0]== ',') {
        p->s++; // ","
        parse_व्यंजक(&d->param[2], p);
    }
    अगर (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_व्यंजक_free(d);
        वापस AVERROR(EINVAL);
    }
    p->s++; // ")"

    क्रम (पूर्णांक i = 0; i<3; i++)
        अगर (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    अगर (d->depth > MAX_DEPTH) {
        av_व्यंजक_free(d);
        वापस AVERROR(EINVAL);
    }

    d->type = e_func0;
         अगर (strmatch(अग्र, "sinh"  )) d->func0 = sinh;
    अन्यथा अगर (strmatch(अग्र, "cosh"  )) d->func0 = cosh;
    अन्यथा अगर (strmatch(अग्र, "tanh"  )) d->func0 = tanh;
    अन्यथा अगर (strmatch(अग्र, "sin"   )) d->func0 = sin;
    अन्यथा अगर (strmatch(अग्र, "cos"   )) d->func0 = cos;
    अन्यथा अगर (strmatch(अग्र, "tan"   )) d->func0 = tan;
    अन्यथा अगर (strmatch(अग्र, "atan"  )) d->func0 = atan;
    अन्यथा अगर (strmatch(अग्र, "asin"  )) d->func0 = asin;
    अन्यथा अगर (strmatch(अग्र, "acos"  )) d->func0 = acos;
    अन्यथा अगर (strmatch(अग्र, "exp"   )) d->func0 = exp;
    अन्यथा अगर (strmatch(अग्र, "log"   )) d->func0 = log;
    अन्यथा अगर (strmatch(अग्र, "abs"   )) d->func0 = भ_असल;
    अन्यथा अगर (strmatch(अग्र, "time"  )) d->func0 = etime;
    अन्यथा अगर (strmatch(अग्र, "squish")) d->type = e_squish;
    अन्यथा अगर (strmatch(अग्र, "gauss" )) d->type = e_gauss;
    अन्यथा अगर (strmatch(अग्र, "mod"   )) d->type = e_mod;
    अन्यथा अगर (strmatch(अग्र, "max"   )) d->type = e_max;
    अन्यथा अगर (strmatch(अग्र, "min"   )) d->type = e_min;
    अन्यथा अगर (strmatch(अग्र, "eq"    )) d->type = e_eq;
    अन्यथा अगर (strmatch(अग्र, "gte"   )) d->type = e_gte;
    अन्यथा अगर (strmatch(अग्र, "gt"    )) d->type = e_gt;
    अन्यथा अगर (strmatch(अग्र, "lte"   )) d->type = e_lte;
    अन्यथा अगर (strmatch(अग्र, "lt"    )) d->type = e_lt;
    अन्यथा अगर (strmatch(अग्र, "ld"    )) d->type = e_ld;
    अन्यथा अगर (strmatch(अग्र, "isnan" )) d->type = e_isnan;
    अन्यथा अगर (strmatch(अग्र, "isinf" )) d->type = e_isinf;
    अन्यथा अगर (strmatch(अग्र, "st"    )) d->type = e_st;
    अन्यथा अगर (strmatch(अग्र, "while" )) d->type = e_while;
    अन्यथा अगर (strmatch(अग्र, "taylor")) d->type = e_taylor;
    अन्यथा अगर (strmatch(अग्र, "root"  )) d->type = e_मूल;
    अन्यथा अगर (strmatch(अग्र, "floor" )) d->type = e_floor;
    अन्यथा अगर (strmatch(अग्र, "ceil"  )) d->type = e_ceil;
    अन्यथा अगर (strmatch(अग्र, "trunc" )) d->type = e_trunc;
    अन्यथा अगर (strmatch(अग्र, "round" )) d->type = e_round;
    अन्यथा अगर (strmatch(अग्र, "sqrt"  )) d->type = e_sqrt;
    अन्यथा अगर (strmatch(अग्र, "not"   )) d->type = e_not;
    अन्यथा अगर (strmatch(अग्र, "pow"   )) d->type = e_pow;
    अन्यथा अगर (strmatch(अग्र, "print" )) d->type = e_print;
    अन्यथा अगर (strmatch(अग्र, "random")) d->type = e_random;
    अन्यथा अगर (strmatch(अग्र, "randomi")) d->type = e_randomi;
    अन्यथा अगर (strmatch(अग्र, "hypot" )) d->type = e_hypot;
    अन्यथा अगर (strmatch(अग्र, "gcd"   )) d->type = e_gcd;
    अन्यथा अगर (strmatch(अग्र, "if"    )) d->type = e_if;
    अन्यथा अगर (strmatch(अग्र, "ifnot" )) d->type = e_ifnot;
    अन्यथा अगर (strmatch(अग्र, "bitand")) d->type = e_bitand;
    अन्यथा अगर (strmatch(अग्र, "bitor" )) d->type = e_bitor;
    अन्यथा अगर (strmatch(अग्र, "between"))d->type = e_between;
    अन्यथा अगर (strmatch(अग्र, "clip"  )) d->type = e_clip;
    अन्यथा अगर (strmatch(अग्र, "atan2" )) d->type = e_atan2;
    अन्यथा अगर (strmatch(अग्र, "lerp"  )) d->type = e_lerp;
    अन्यथा अगर (strmatch(अग्र, "sgn"   )) d->type = e_sgn;
    अन्यथा {
        क्रम (i=0; p->func1_names && p->func1_names[i]; i++) {
            अगर (strmatch(अग्र, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_सूचकांक = i;
                *e = d;
                वापस 0;
            }
        }

        क्रम (i=0; p->func2_names && p->func2_names[i]; i++) {
            अगर (strmatch(अग्र, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_सूचकांक = i;
                *e = d;
                वापस 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_व्यंजक_free(d);
        वापस AVERROR(EINVAL);
    }

    *e = d;
    वापस 0;
}

अटल AVExpr *make_eval_व्यंजक(पूर्णांक type, पूर्णांक मूल्य, AVExpr *p0, AVExpr *p1)
{
    पूर्णांक depth = FFMAX(p0->depth, p1->depth) + 1;
    अगर (depth > MAX_DEPTH)
        वापस शून्य;
    AVExpr *e = av_mallocz(माप(AVExpr));
    अगर (!e)
        वापस शून्य;
    e->type     =type   ;
    e->मूल्य    =मूल्य  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    वापस e;
}

अटल पूर्णांक parse_pow(AVExpr **e, Parser *p, पूर्णांक *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    वापस parse_primary(e, p);
}

अटल पूर्णांक parse_dB(AVExpr **e, Parser *p, पूर्णांक *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    अगर (*p->s == '-') {
        अक्षर *अग्र;
        av_unused द्विगुन ignored = म_से_भग्न(p->s, &अग्र);
        अगर (अग्र != p->s && अग्र[0] == 'd' && अग्र[1] == 'B') {
            *sign = 0;
            वापस parse_primary(e, p);
        }
    }
    वापस parse_pow(e, p, sign);
}

अटल पूर्णांक parse_factor(AVExpr **e, Parser *p)
{
    पूर्णांक sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    अगर ((ret = parse_dB(&e0, p, &sign)) < 0)
        वापस ret;
    जबतक(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        अगर ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_व्यंजक_free(e1);
            वापस ret;
        }
        e0 = make_eval_व्यंजक(e_pow, 1, e1, e2);
        अगर (!e0) {
            av_व्यंजक_free(e1);
            av_व्यंजक_free(e2);
            वापस AVERROR(ENOMEM);
        }
        अगर (e0->param[1]) e0->param[1]->मूल्य *= (sign2|1);
    }
    अगर (e0) e0->मूल्य *= (sign|1);

    *e = e0;
    वापस 0;
}

अटल पूर्णांक parse_term(AVExpr **e, Parser *p)
{
    पूर्णांक ret;
    AVExpr *e0, *e1, *e2;
    अगर ((ret = parse_factor(&e0, p)) < 0)
        वापस ret;
    जबतक (p->s[0]=='*' || p->s[0]=='/') {
        पूर्णांक c= *p->s++;
        e1 = e0;
        अगर ((ret = parse_factor(&e2, p)) < 0) {
            av_व्यंजक_free(e1);
            वापस ret;
        }
        e0 = make_eval_व्यंजक(c == '*' ? e_mul : e_div, 1, e1, e2);
        अगर (!e0) {
            av_व्यंजक_free(e1);
            av_व्यंजक_free(e2);
            वापस AVERROR(ENOMEM);
        }
    }
    *e = e0;
    वापस 0;
}

अटल पूर्णांक parse_subexpr(AVExpr **e, Parser *p)
{
    पूर्णांक ret;
    AVExpr *e0, *e1, *e2;
    अगर ((ret = parse_term(&e0, p)) < 0)
        वापस ret;
    जबतक (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        अगर ((ret = parse_term(&e2, p)) < 0) {
            av_व्यंजक_free(e1);
            वापस ret;
        }
        e0 = make_eval_व्यंजक(e_add, 1, e1, e2);
        अगर (!e0) {
            av_व्यंजक_free(e1);
            av_व्यंजक_free(e2);
            वापस AVERROR(ENOMEM);
        }
    };

    *e = e0;
    वापस 0;
}

अटल पूर्णांक parse_व्यंजक(AVExpr **e, Parser *p)
{
    पूर्णांक ret;
    AVExpr *e0, *e1, *e2;
    अगर (p->ढेर_सूचकांक <= 0) //protect against stack overflows
        वापस AVERROR(EINVAL);
    p->ढेर_सूचकांक--;

    अगर ((ret = parse_subexpr(&e0, p)) < 0)
        वापस ret;
    जबतक (*p->s == ';') {
        p->s++;
        e1 = e0;
        अगर ((ret = parse_subexpr(&e2, p)) < 0) {
            av_व्यंजक_free(e1);
            वापस ret;
        }
        e0 = make_eval_व्यंजक(e_last, 1, e1, e2);
        अगर (!e0) {
            av_व्यंजक_free(e1);
            av_व्यंजक_free(e2);
            वापस AVERROR(ENOMEM);
        }
    };

    p->ढेर_सूचकांक++;
    *e = e0;
    वापस 0;
}

अटल पूर्णांक verify_व्यंजक(AVExpr *e)
{
    अगर (!e) वापस 0;
    चयन (e->type) {
        हाल e_मूल्य:
        हाल e_const: वापस 1;
        हाल e_func0:
        हाल e_func1:
        हाल e_squish:
        हाल e_ld:
        हाल e_gauss:
        हाल e_isnan:
        हाल e_isinf:
        हाल e_floor:
        हाल e_ceil:
        हाल e_trunc:
        हाल e_round:
        हाल e_sqrt:
        हाल e_not:
        हाल e_random:
        हाल e_sgn:
            वापस verify_व्यंजक(e->param[0]) && !e->param[1];
        हाल e_print:
            वापस verify_व्यंजक(e->param[0])
                   && (!e->param[1] || verify_व्यंजक(e->param[1]));
        हाल e_if:
        हाल e_ifnot:
        हाल e_taylor:
            वापस verify_व्यंजक(e->param[0]) && verify_व्यंजक(e->param[1])
                   && (!e->param[2] || verify_व्यंजक(e->param[2]));
        हाल e_between:
        हाल e_clip:
        हाल e_lerp:
        हाल e_randomi:
            वापस verify_व्यंजक(e->param[0]) &&
                   verify_व्यंजक(e->param[1]) &&
                   verify_व्यंजक(e->param[2]);
        शेष: वापस verify_व्यंजक(e->param[0]) && verify_व्यंजक(e->param[1]) && !e->param[2];
    }
}

पूर्णांक av_व्यंजक_parse(AVExpr **व्यंजक, स्थिर अक्षर *s,
                  स्थिर अक्षर * स्थिर *const_names,
                  स्थिर अक्षर * स्थिर *func1_names, द्विगुन (* स्थिर *funcs1)(व्योम *, द्विगुन),
                  स्थिर अक्षर * स्थिर *func2_names, द्विगुन (* स्थिर *funcs2)(व्योम *, द्विगुन, द्विगुन),
                  पूर्णांक log_offset, व्योम *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = शून्य;
    अक्षर *w = av_malloc(म_माप(s) + 1);
    अक्षर *wp = w;
    स्थिर अक्षर *s0 = s;
    पूर्णांक ret = 0;

    अगर (!w)
        वापस AVERROR(ENOMEM);

    जबतक (*s)
        अगर (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.ढेर_सूचकांक=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    अगर ((ret = parse_व्यंजक(&e, &p)) < 0)
        जाओ end;
    अगर (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        जाओ end;
    }
    अगर (!verify_व्यंजक(e)) {
        ret = AVERROR(EINVAL);
        जाओ end;
    }
    AVExpr_मूल *r = av_realloc(e, माप(*r));
    अगर (!r) {
        ret = AVERROR(ENOMEM);
        जाओ end;
    }
    e = (AVExpr*)r;
    e->मूल = 1;
    r->var= av_mallocz(माप(द्विगुन) *VARS);
    r->prng_state = av_mallocz(माप(*r->prng_state) *VARS);
    अगर (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        जाओ end;
    }
    *व्यंजक = e;
    e = शून्य;
end:
    av_व्यंजक_free(e);
    av_free(w);
    वापस ret;
}

अटल पूर्णांक व्यंजक_गिनती(AVExpr *e, अचिन्हित *गणक, पूर्णांक आकार, पूर्णांक type)
{
    पूर्णांक i;

    अगर (!e || !गणक || !आकार)
        वापस AVERROR(EINVAL);

    क्रम (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        व्यंजक_गिनती(e->param[i], गणक, आकार, type);

    अगर (e->type == type && e->const_सूचकांक < आकार)
        गणक[e->const_सूचकांक]++;

    वापस 0;
}

पूर्णांक av_व्यंजक_गिनती_vars(AVExpr *e, अचिन्हित *गणक, पूर्णांक आकार)
{
    वापस व्यंजक_गिनती(e, गणक, आकार, e_const);
}

पूर्णांक av_व्यंजक_गिनती_func(AVExpr *e, अचिन्हित *गणक, पूर्णांक आकार, पूर्णांक arg)
{
    वापस व्यंजक_गिनती(e, गणक, आकार, ((पूर्णांक[]){e_const, e_func1, e_func2})[arg]);
}

द्विगुन av_व्यंजक_eval(AVExpr *e, स्थिर द्विगुन *const_मूल्यावली, व्योम *opaque)
{
    av_assert1(e->मूल);
    AVExpr_मूल *r = (AVExpr_मूल *)e;
    Parser p = {
        .class        = &eval_class,
        .const_मूल्यावली = const_मूल्यावली,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    वापस eval_व्यंजक(&p, e);
}

पूर्णांक av_व्यंजक_parse_and_eval(द्विगुन *d, स्थिर अक्षर *s,
                           स्थिर अक्षर * स्थिर *const_names, स्थिर द्विगुन *const_मूल्यावली,
                           स्थिर अक्षर * स्थिर *func1_names, द्विगुन (* स्थिर *funcs1)(व्योम *, द्विगुन),
                           स्थिर अक्षर * स्थिर *func2_names, द्विगुन (* स्थिर *funcs2)(व्योम *, द्विगुन, द्विगुन),
                           व्योम *opaque, पूर्णांक log_offset, व्योम *log_ctx)
{
    AVExpr *e = शून्य;
    पूर्णांक ret = av_व्यंजक_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    अगर (ret < 0) {
        *d = न_अंक;
        वापस ret;
    }
    *d = av_व्यंजक_eval(e, const_मूल्यावली, opaque);
    av_व्यंजक_free(e);
    वापस isnan(*d) ? AVERROR(EINVAL) : 0;
}
