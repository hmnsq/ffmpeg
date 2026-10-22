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

#परिभाषय MAX_गभीरता 100

प्रकारनिर्देश संरचना Parser {
    ध्रुव AVClass *class;
    पूर्णाङ्क राशिः_सूचकांक;
    वर्ण *s;
    ध्रुव द्विगुण *const_मानानि;
    ध्रुव वर्ण * ध्रुव *const_नामानि;          // NULL terminated
    द्विगुण (* ध्रुव *funcs1)(शून्य *, द्विगुण a);           // NULL terminated
    ध्रुव वर्ण * ध्रुव *func1_नामानि;          // NULL terminated
    द्विगुण (* ध्रुव *funcs2)(शून्य *, द्विगुण a, द्विगुण b); // NULL terminated
    ध्रुव वर्ण * ध्रुव *func2_नामानि;          // NULL terminated
    शून्य *opaque;
    पूर्णाङ्क log_विस्थापनम्;
    शून्य *log_ctx;
#परिभाषय VARS 10
    द्विगुण *var;
    FFSFC64 *prng_state;
} Parser;

स्थिर ध्रुव AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .संस्करणम्                   = LIBAVUTIL_संस्करणम्_INT,
    .log_level_विस्थापनम्_विस्थापनम्   = offsetof(Parser, log_विस्थापनम्),
    .parent_log_context_विस्थापनम् = offsetof(Parser, log_ctx),
};

स्थिर ध्रुव संरचना {
    द्विगुण bin_val;
    द्विगुण dec_val;
    int8_t घातांकः;
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

द्विगुण av_strtod(ध्रुव वर्ण *numstr, वर्ण **पुच्छ)
{
    द्विगुण d;
    वर्ण *अग्र;
    यदि(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &अग्र, 16);
    } अन्यथा
        d = strtod(numstr, &अग्र);
    /* if parsing succeeded, check for and interpret postfixes */
    यदि (अग्र!=numstr) {
        यदि (अग्र[0] == 'd' && अग्र[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            अग्र += 2;
        } अन्यथा यदि (*अग्र >= 'E' && *अग्र <= 'z') {
            पूर्णाङ्क e= si_prefixes[*अग्र - 'E'].घातांकः;
            यदि (e) {
                यदि (अग्र[1] == 'i') {
                    d*= si_prefixes[*अग्र - 'E'].bin_val;
                    अग्र+=2;
                } अन्यथा {
                    d*= si_prefixes[*अग्र - 'E'].dec_val;
                    अग्र++;
                }
            }
        }

        यदि (*अग्र=='B') {
            d*=8;
            अग्र++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    यदि (पुच्छ)
        *पुच्छ = अग्र;
    प्रत्यागम d;
}

#परिभाषय IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

स्थिर पूर्णाङ्क strmatch(ध्रुव वर्ण *s, ध्रुव वर्ण *उपसर्गः)
{
    पूर्णाङ्क i;
    प्रति (i=0; उपसर्गः[i]; i++) {
        यदि (उपसर्गः[i] != s[i]) प्रत्यागम 0;
    }
    /* return 1 only if the s identifier is terminated */
    प्रत्यागम !IS_IDENTIFIER_CHAR(s[i]);
}

गणना {
    e_मानम्, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_सङ्कलय,
    e_चरमः, e_st, e_while, e_taylor, e_मूलम्, e_floor, e_ceil, e_trunc, e_आवर्तनम्,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
संरचना AVExpr {
    अचिह्नित वर्ण type;
    अचिह्नित वर्ण मूलम्;
    ह्रस्व गभीरता;
    पूर्णाङ्क const_सूचकांक;
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
    प्रत्यागम av_gettime() * 0.000001;
}

स्थिर द्विगुण eval_व्यञ्जकम्(Parser *p, AVExpr *e)
{
    विकल्प (e->type) {
        पक्ष e_मानम्:  प्रत्यागम e->मानम्;
        पक्ष e_const:  प्रत्यागम e->मानम् * p->const_मानानि[e->const_सूचकांक];
        पक्ष e_func0:  प्रत्यागम e->मानम् * e->func0(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_func1:  प्रत्यागम e->मानम् * e->func1(p->opaque, eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_func2:  प्रत्यागम e->मानम् * e->func2(p->opaque, eval_व्यञ्जकम्(p, e->param[0]), eval_व्यञ्जकम्(p, e->param[1]));
        पक्ष e_squish: प्रत्यागम e->मानम्/(1+घातांकः(4*eval_व्यञ्जकम्(p, e->param[0])));
        पक्ष e_gauss: { द्विगुण d = eval_व्यञ्जकम्(p, e->param[0]); प्रत्यागम e->मानम् * घातांकः(-d*d/2)/वर्गमूलम्(2*M_PI); }
        पक्ष e_ld:     प्रत्यागम e->मानम् * p->var[av_clip(eval_व्यञ्जकम्(p, e->param[0]), 0, VARS-1)];
        पक्ष e_isnan:  प्रत्यागम e->मानम् * !!isnan(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_isinf:  प्रत्यागम e->मानम् * !!isinf(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_floor:  प्रत्यागम e->मानम् * floor(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_ceil :  प्रत्यागम e->मानम् * ceil (eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_trunc:  प्रत्यागम e->मानम् * trunc(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_आवर्तनम्:  प्रत्यागम e->मानम् * round(eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_sgn:    प्रत्यागम e->मानम् * FFDIFFSIGN(eval_व्यञ्जकम्(p, e->param[0]), 0);
        पक्ष e_sqrt:   प्रत्यागम e->मानम् * वर्गमूलम् (eval_व्यञ्जकम्(p, e->param[0]));
        पक्ष e_not:    प्रत्यागम e->मानम् * (eval_व्यञ्जकम्(p, e->param[0]) == 0);
        पक्ष e_if:     प्रत्यागम e->मानम् * (eval_व्यञ्जकम्(p, e->param[0]) ? eval_व्यञ्जकम्(p, e->param[1]) :
                                          e->param[2] ? eval_व्यञ्जकम्(p, e->param[2]) : 0);
        पक्ष e_ifnot:  प्रत्यागम e->मानम् * (!eval_व्यञ्जकम्(p, e->param[0]) ? eval_व्यञ्जकम्(p, e->param[1]) :
                                          e->param[2] ? eval_व्यञ्जकम्(p, e->param[2]) : 0);
        पक्ष e_clip: {
            द्विगुण x = eval_व्यञ्जकम्(p, e->param[0]);
            द्विगुण min = eval_व्यञ्जकम्(p, e->param[1]), max = eval_व्यञ्जकम्(p, e->param[2]);
            यदि (isnan(min) || isnan(max) || isnan(x) || min > max)
                प्रत्यागम NAN;
            प्रत्यागम e->मानम् * av_clipd(x, min, max);
        }
        पक्ष e_between: {
            द्विगुण d = eval_व्यञ्जकम्(p, e->param[0]);
            प्रत्यागम e->मानम् * (d >= eval_व्यञ्जकम्(p, e->param[1]) &&
                               d <= eval_व्यञ्जकम्(p, e->param[2]));
        }
        पक्ष e_lerp: {
            द्विगुण v0 = eval_व्यञ्जकम्(p, e->param[0]);
            द्विगुण v1 = eval_व्यञ्जकम्(p, e->param[1]);
            द्विगुण f  = eval_व्यञ्जकम्(p, e->param[2]);
            प्रत्यागम e->मानम् * (v0 + (v1 - v0) * f);
        }
        पक्ष e_print: {
            द्विगुण x = eval_व्यञ्जकम्(p, e->param[0]);
            पूर्णाङ्क level = e->param[1] ? av_clip(eval_व्यञ्जकम्(p, e->param[1]), INT_MIN, अधिकतम_पूर्णाङ्कः) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            प्रत्यागम e->मानम् * x;
        }

#परिभाषय COMPUTE_अग्र_RANDOM()                                        \
            पूर्णाङ्क idx = av_clip(eval_व्यञ्जकम्(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            यदि (!s->गणक) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        पक्ष e_random: {
            COMPUTE_अग्र_RANDOM();
            प्रत्यागम r * (1.0/UINT64_MAX);
        }
        पक्ष e_randomi: {
            द्विगुण min = eval_व्यञ्जकम्(p, e->param[1]);
            द्विगुण max = eval_व्यञ्जकम्(p, e->param[2]);
            COMPUTE_अग्र_RANDOM();
            प्रत्यागम min + (max - min) * r / UINT64_MAX;
        }
        पक्ष e_while: {
            द्विगुण d = NAN;
            यावत् (eval_व्यञ्जकम्(p, e->param[0]))
                d=eval_व्यञ्जकम्(p, e->param[1]);
            प्रत्यागम d;
        }
        पक्ष e_taylor: {
            द्विगुण t = 1, d = 0, v;
            द्विगुण x = eval_व्यञ्जकम्(p, e->param[1]);
            पूर्णाङ्क id = e->param[2] ? av_clip(eval_व्यञ्जकम्(p, e->param[2]), 0, VARS-1) : 0;
            पूर्णाङ्क i;
            द्विगुण var0 = p->var[id];
            प्रति(i=0; i<1000; i++) {
                द्विगुण ld = d;
                p->var[id] = i;
                v = eval_व्यञ्जकम्(p, e->param[0]);
                d += t*v;
                यदि(ld==d && v)
                    भङ्ग;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            प्रत्यागम d;
        }
        पक्ष e_मूलम्: {
            पूर्णाङ्क i, j;
            द्विगुण नीचः = -1, उच्चः = -1, v, नीचः_v = -DBL_MAX, उच्चः_v = DBL_MAX;
            द्विगुण var0 = p->var[0];
            द्विगुण x_max = eval_व्यञ्जकम्(p, e->param[1]);
            प्रति(i=-1; i<1024; i++) {
                यदि(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } अन्यथा {
                    p->var[0] = x_max*घातः(0.9, i-255);
                    यदि (i&1) p->var[0] *= -1;
                    यदि (i&2) p->var[0] += नीचः;
                    अन्यथा     p->var[0] += उच्चः;
                }
                v = eval_व्यञ्जकम्(p, e->param[0]);
                यदि (v<=0 && v>नीचः_v) {
                    नीचः    = p->var[0];
                    नीचः_v  = v;
                }
                यदि (v>=0 && v<उच्चः_v) {
                    उच्चः   = p->var[0];
                    उच्चः_v = v;
                }
                यदि (नीचः>=0 && उच्चः>=0){
                    प्रति (j=0; j<1000; j++) {
                        p->var[0] = (नीचः+उच्चः)*0.5;
                        यदि (नीचः == p->var[0] || उच्चः == p->var[0])
                            भङ्ग;
                        v = eval_व्यञ्जकम्(p, e->param[0]);
                        यदि (v<=0) नीचः = p->var[0];
                        यदि (v>=0) उच्चः= p->var[0];
                        यदि (isnan(v)) {
                            नीचः = उच्चः = v;
                            भङ्ग;
                        }
                    }
                    भङ्ग;
                }
            }
            p->var[0] = var0;
            प्रत्यागम -नीचः_v<उच्चः_v ? नीचः : उच्चः;
        }
        स्वभाव: {
            द्विगुण d = eval_व्यञ्जकम्(p, e->param[0]);
            द्विगुण d2 = eval_व्यञ्जकम्(p, e->param[1]);
            विकल्प (e->type) {
                पक्ष e_mod: प्रत्यागम e->मानम् * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                पक्ष e_gcd: प्रत्यागम e->मानम् * av_gcd(d,d2);
                पक्ष e_max: प्रत्यागम e->मानम् * (d >  d2 ?   d : d2);
                पक्ष e_min: प्रत्यागम e->मानम् * (d <  d2 ?   d : d2);
                पक्ष e_eq:  प्रत्यागम e->मानम् * (d == d2 ? 1.0 : 0.0);
                पक्ष e_gt:  प्रत्यागम e->मानम् * (d >  d2 ? 1.0 : 0.0);
                पक्ष e_gte: प्रत्यागम e->मानम् * (d >= d2 ? 1.0 : 0.0);
                पक्ष e_lt:  प्रत्यागम e->मानम् * (d <  d2 ? 1.0 : 0.0);
                पक्ष e_lte: प्रत्यागम e->मानम् * (d <= d2 ? 1.0 : 0.0);
                पक्ष e_pow: प्रत्यागम e->मानम् * घातः(d, d2);
                पक्ष e_mul: प्रत्यागम e->मानम् * (d * d2);
                पक्ष e_div: प्रत्यागम e->मानम् * (d2 ? (d / d2) : d * INFINITY);
                पक्ष e_सङ्कलय: प्रत्यागम e->मानम् * (d + d2);
                पक्ष e_चरमः:प्रत्यागम e->मानम् * d2;
                पक्ष e_st :  {
                    पूर्णाङ्क सूचकांक = av_clip(d, 0, VARS-1);
                    p->prng_state[सूचकांक].गणक = 0;
                    प्रत्यागम e->मानम् * (p->var[सूचकांक]= d2);
                }
                पक्ष e_hypot:प्रत्यागम e->मानम् * hypot(d, d2);
                पक्ष e_atan2:प्रत्यागम e->मानम् * atan2(d, d2);
                पक्ष e_bitand: प्रत्यागम isnan(d) || isnan(d2) ? NAN : e->मानम् * ((दीर्घ पूर्णाङ्क)d & (दीर्घ पूर्णाङ्क)d2);
                पक्ष e_bitor:  प्रत्यागम isnan(d) || isnan(d2) ? NAN : e->मानम् * ((दीर्घ पूर्णाङ्क)d | (दीर्घ पूर्णाङ्क)d2);
            }
        }
    }
    प्रत्यागम NAN;
}

स्थिर पूर्णाङ्क parse_व्यञ्जकम्(AVExpr **e, Parser *p);

शून्य av_व्यञ्जकम्_free(AVExpr *e)
{
    यदि (!e) प्रत्यागम;
    av_व्यञ्जकम्_free(e->param[0]);
    av_व्यञ्जकम्_free(e->param[1]);
    av_व्यञ्जकम्_free(e->param[2]);
    यदि (e->मूलम्) {
        AVExpr_मूलम् *r = (AVExpr_मूलम्*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

स्थिर पूर्णाङ्क parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(परिमाण(AVExpr));
    वर्ण *अग्र = p->s, *s0 = p->s;
    पूर्णाङ्क ret, i;

    यदि (!d)
        प्रत्यागम AVERROR(ENOMEM);

    /*सङ्ख्या*/
    d->मानम् = av_strtod(p->s, &अग्र);
    यदि (अग्र != p->s) {
        d->type = e_मानम्;
        p->s= अग्र;
        *e = d;
        प्रत्यागम 0;
    }
    d->मानम् = 1;

    /* named constants */
    प्रति (i=0; p->const_नामानि && p->const_नामानि[i]; i++) {
        यदि (strmatch(p->s, p->const_नामानि[i])) {
            p->s+= वाक्यदैर्घ्यम्(p->const_नामानि[i]);
            d->type = e_const;
            d->const_सूचकांक = i;
            *e = d;
            प्रत्यागम 0;
        }
    }
    प्रति (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        यदि (strmatch(p->s, constants[i].name)) {
            p->s += वाक्यदैर्घ्यम्(constants[i].name);
            d->type = e_मानम्;
            d->मानम् = constants[i].मानम्;
            *e = d;
            प्रत्यागम 0;
        }
    }

    p->s= strchr(p->s, '(');
    यदि (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= अग्र;
        av_व्यञ्जकम्_free(d);
        प्रत्यागम AVERROR(EINVAL);
    }
    p->s++; // "("
    यदि (*अग्र == '(') { // special case do-nothing
        av_freep(&d);
        यदि ((ret = parse_व्यञ्जकम्(&d, p)) < 0)
            प्रत्यागम ret;
        यदि (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_व्यञ्जकम्_free(d);
            प्रत्यागम AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        प्रत्यागम 0;
    }
    यदि ((ret = parse_व्यञ्जकम्(&(d->param[0]), p)) < 0) {
        av_व्यञ्जकम्_free(d);
        प्रत्यागम ret;
    }
    यदि (p->s[0]== ',') {
        p->s++; // ","
        parse_व्यञ्जकम्(&d->param[1], p);
    }
    यदि (p->s[0]== ',') {
        p->s++; // ","
        parse_व्यञ्जकम्(&d->param[2], p);
    }
    यदि (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_व्यञ्जकम्_free(d);
        प्रत्यागम AVERROR(EINVAL);
    }
    p->s++; // ")"

    प्रति (पूर्णाङ्क i = 0; i<3; i++)
        यदि (d->param[i])
            d->गभीरता = FFMAX(d->गभीरता, d->param[i]->गभीरता+1);
    यदि (d->गभीरता > MAX_गभीरता) {
        av_व्यञ्जकम्_free(d);
        प्रत्यागम AVERROR(EINVAL);
    }

    d->type = e_func0;
         यदि (strmatch(अग्र, "sinh"  )) d->func0 = sinh;
    अन्यथा यदि (strmatch(अग्र, "cosh"  )) d->func0 = cosh;
    अन्यथा यदि (strmatch(अग्र, "tanh"  )) d->func0 = tanh;
    अन्यथा यदि (strmatch(अग्र, "sin"   )) d->func0 = ज्या;
    अन्यथा यदि (strmatch(अग्र, "cos"   )) d->func0 = कोटिज्या;
    अन्यथा यदि (strmatch(अग्र, "tan"   )) d->func0 = tan;
    अन्यथा यदि (strmatch(अग्र, "atan"  )) d->func0 = atan;
    अन्यथा यदि (strmatch(अग्र, "asin"  )) d->func0 = asin;
    अन्यथा यदि (strmatch(अग्र, "acos"  )) d->func0 = acos;
    अन्यथा यदि (strmatch(अग्र, "exp"   )) d->func0 = घातांकः;
    अन्यथा यदि (strmatch(अग्र, "log"   )) d->func0 = लघुगणकः;
    अन्यथा यदि (strmatch(अग्र, "abs"   )) d->func0 = fabs;
    अन्यथा यदि (strmatch(अग्र, "time"  )) d->func0 = etime;
    अन्यथा यदि (strmatch(अग्र, "squish")) d->type = e_squish;
    अन्यथा यदि (strmatch(अग्र, "gauss" )) d->type = e_gauss;
    अन्यथा यदि (strmatch(अग्र, "mod"   )) d->type = e_mod;
    अन्यथा यदि (strmatch(अग्र, "max"   )) d->type = e_max;
    अन्यथा यदि (strmatch(अग्र, "min"   )) d->type = e_min;
    अन्यथा यदि (strmatch(अग्र, "eq"    )) d->type = e_eq;
    अन्यथा यदि (strmatch(अग्र, "gte"   )) d->type = e_gte;
    अन्यथा यदि (strmatch(अग्र, "gt"    )) d->type = e_gt;
    अन्यथा यदि (strmatch(अग्र, "lte"   )) d->type = e_lte;
    अन्यथा यदि (strmatch(अग्र, "lt"    )) d->type = e_lt;
    अन्यथा यदि (strmatch(अग्र, "ld"    )) d->type = e_ld;
    अन्यथा यदि (strmatch(अग्र, "isnan" )) d->type = e_isnan;
    अन्यथा यदि (strmatch(अग्र, "isinf" )) d->type = e_isinf;
    अन्यथा यदि (strmatch(अग्र, "st"    )) d->type = e_st;
    अन्यथा यदि (strmatch(अग्र, "while" )) d->type = e_while;
    अन्यथा यदि (strmatch(अग्र, "taylor")) d->type = e_taylor;
    अन्यथा यदि (strmatch(अग्र, "root"  )) d->type = e_मूलम्;
    अन्यथा यदि (strmatch(अग्र, "floor" )) d->type = e_floor;
    अन्यथा यदि (strmatch(अग्र, "ceil"  )) d->type = e_ceil;
    अन्यथा यदि (strmatch(अग्र, "trunc" )) d->type = e_trunc;
    अन्यथा यदि (strmatch(अग्र, "round" )) d->type = e_आवर्तनम्;
    अन्यथा यदि (strmatch(अग्र, "sqrt"  )) d->type = e_sqrt;
    अन्यथा यदि (strmatch(अग्र, "not"   )) d->type = e_not;
    अन्यथा यदि (strmatch(अग्र, "pow"   )) d->type = e_pow;
    अन्यथा यदि (strmatch(अग्र, "print" )) d->type = e_print;
    अन्यथा यदि (strmatch(अग्र, "random")) d->type = e_random;
    अन्यथा यदि (strmatch(अग्र, "randomi")) d->type = e_randomi;
    अन्यथा यदि (strmatch(अग्र, "hypot" )) d->type = e_hypot;
    अन्यथा यदि (strmatch(अग्र, "gcd"   )) d->type = e_gcd;
    अन्यथा यदि (strmatch(अग्र, "if"    )) d->type = e_if;
    अन्यथा यदि (strmatch(अग्र, "ifnot" )) d->type = e_ifnot;
    अन्यथा यदि (strmatch(अग्र, "bitand")) d->type = e_bitand;
    अन्यथा यदि (strmatch(अग्र, "bitor" )) d->type = e_bitor;
    अन्यथा यदि (strmatch(अग्र, "between"))d->type = e_between;
    अन्यथा यदि (strmatch(अग्र, "clip"  )) d->type = e_clip;
    अन्यथा यदि (strmatch(अग्र, "atan2" )) d->type = e_atan2;
    अन्यथा यदि (strmatch(अग्र, "lerp"  )) d->type = e_lerp;
    अन्यथा यदि (strmatch(अग्र, "sgn"   )) d->type = e_sgn;
    अन्यथा {
        प्रति (i=0; p->func1_नामानि && p->func1_नामानि[i]; i++) {
            यदि (strmatch(अग्र, p->func1_नामानि[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_सूचकांक = i;
                *e = d;
                प्रत्यागम 0;
            }
        }

        प्रति (i=0; p->func2_नामानि && p->func2_नामानि[i]; i++) {
            यदि (strmatch(अग्र, p->func2_नामानि[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_सूचकांक = i;
                *e = d;
                प्रत्यागम 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_व्यञ्जकम्_free(d);
        प्रत्यागम AVERROR(EINVAL);
    }

    *e = d;
    प्रत्यागम 0;
}

स्थिर AVExpr *make_eval_व्यञ्जकम्(पूर्णाङ्क type, पूर्णाङ्क मानम्, AVExpr *p0, AVExpr *p1)
{
    पूर्णाङ्क गभीरता = FFMAX(p0->गभीरता, p1->गभीरता) + 1;
    यदि (गभीरता > MAX_गभीरता)
        प्रत्यागम रिक्त;
    AVExpr *e = av_mallocz(परिमाण(AVExpr));
    यदि (!e)
        प्रत्यागम रिक्त;
    e->type     =type   ;
    e->मानम्    =मानम्  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->गभीरता    = गभीरता;
    प्रत्यागम e;
}

स्थिर पूर्णाङ्क parse_pow(AVExpr **e, Parser *p, पूर्णाङ्क *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    प्रत्यागम parse_primary(e, p);
}

स्थिर पूर्णाङ्क parse_dB(AVExpr **e, Parser *p, पूर्णाङ्क *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    यदि (*p->s == '-') {
        वर्ण *अग्र;
        av_अप्रयुक्तम् द्विगुण ignored = strtod(p->s, &अग्र);
        यदि (अग्र != p->s && अग्र[0] == 'd' && अग्र[1] == 'B') {
            *sign = 0;
            प्रत्यागम parse_primary(e, p);
        }
    }
    प्रत्यागम parse_pow(e, p, sign);
}

स्थिर पूर्णाङ्क parse_गुणकः(AVExpr **e, Parser *p)
{
    पूर्णाङ्क sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    यदि ((ret = parse_dB(&e0, p, &sign)) < 0)
        प्रत्यागम ret;
    यावत्(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        यदि ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_व्यञ्जकम्_free(e1);
            प्रत्यागम ret;
        }
        e0 = make_eval_व्यञ्जकम्(e_pow, 1, e1, e2);
        यदि (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            प्रत्यागम AVERROR(ENOMEM);
        }
        यदि (e0->param[1]) e0->param[1]->मानम् *= (sign2|1);
    }
    यदि (e0) e0->मानम् *= (sign|1);

    *e = e0;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क parse_पदांशः(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    यदि ((ret = parse_गुणकः(&e0, p)) < 0)
        प्रत्यागम ret;
    यावत् (p->s[0]=='*' || p->s[0]=='/') {
        पूर्णाङ्क c= *p->s++;
        e1 = e0;
        यदि ((ret = parse_गुणकः(&e2, p)) < 0) {
            av_व्यञ्जकम्_free(e1);
            प्रत्यागम ret;
        }
        e0 = make_eval_व्यञ्जकम्(c == '*' ? e_mul : e_div, 1, e1, e2);
        यदि (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            प्रत्यागम AVERROR(ENOMEM);
        }
    }
    *e = e0;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क parse_subexpr(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    यदि ((ret = parse_पदांशः(&e0, p)) < 0)
        प्रत्यागम ret;
    यावत् (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        यदि ((ret = parse_पदांशः(&e2, p)) < 0) {
            av_व्यञ्जकम्_free(e1);
            प्रत्यागम ret;
        }
        e0 = make_eval_व्यञ्जकम्(e_सङ्कलय, 1, e1, e2);
        यदि (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            प्रत्यागम AVERROR(ENOMEM);
        }
    };

    *e = e0;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क parse_व्यञ्जकम्(AVExpr **e, Parser *p)
{
    पूर्णाङ्क ret;
    AVExpr *e0, *e1, *e2;
    यदि (p->राशिः_सूचकांक <= 0) //protect against stack overflows
        प्रत्यागम AVERROR(EINVAL);
    p->राशिः_सूचकांक--;

    यदि ((ret = parse_subexpr(&e0, p)) < 0)
        प्रत्यागम ret;
    यावत् (*p->s == ';') {
        p->s++;
        e1 = e0;
        यदि ((ret = parse_subexpr(&e2, p)) < 0) {
            av_व्यञ्जकम्_free(e1);
            प्रत्यागम ret;
        }
        e0 = make_eval_व्यञ्जकम्(e_चरमः, 1, e1, e2);
        यदि (!e0) {
            av_व्यञ्जकम्_free(e1);
            av_व्यञ्जकम्_free(e2);
            प्रत्यागम AVERROR(ENOMEM);
        }
    };

    p->राशिः_सूचकांक++;
    *e = e0;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क verify_व्यञ्जकम्(AVExpr *e)
{
    यदि (!e) प्रत्यागम 0;
    विकल्प (e->type) {
        पक्ष e_मानम्:
        पक्ष e_const: प्रत्यागम 1;
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
        पक्ष e_आवर्तनम्:
        पक्ष e_sqrt:
        पक्ष e_not:
        पक्ष e_random:
        पक्ष e_sgn:
            प्रत्यागम verify_व्यञ्जकम्(e->param[0]) && !e->param[1];
        पक्ष e_print:
            प्रत्यागम verify_व्यञ्जकम्(e->param[0])
                   && (!e->param[1] || verify_व्यञ्जकम्(e->param[1]));
        पक्ष e_if:
        पक्ष e_ifnot:
        पक्ष e_taylor:
            प्रत्यागम verify_व्यञ्जकम्(e->param[0]) && verify_व्यञ्जकम्(e->param[1])
                   && (!e->param[2] || verify_व्यञ्जकम्(e->param[2]));
        पक्ष e_between:
        पक्ष e_clip:
        पक्ष e_lerp:
        पक्ष e_randomi:
            प्रत्यागम verify_व्यञ्जकम्(e->param[0]) &&
                   verify_व्यञ्जकम्(e->param[1]) &&
                   verify_व्यञ्जकम्(e->param[2]);
        स्वभाव: प्रत्यागम verify_व्यञ्जकम्(e->param[0]) && verify_व्यञ्जकम्(e->param[1]) && !e->param[2];
    }
}

पूर्णाङ्क av_व्यञ्जकम्_parse(AVExpr **व्यञ्जकम्, ध्रुव वर्ण *s,
                  ध्रुव वर्ण * ध्रुव *const_नामानि,
                  ध्रुव वर्ण * ध्रुव *func1_नामानि, द्विगुण (* ध्रुव *funcs1)(शून्य *, द्विगुण),
                  ध्रुव वर्ण * ध्रुव *func2_नामानि, द्विगुण (* ध्रुव *funcs2)(शून्य *, द्विगुण, द्विगुण),
                  पूर्णाङ्क log_विस्थापनम्, शून्य *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = रिक्त;
    वर्ण *w = av_malloc(वाक्यदैर्घ्यम्(s) + 1);
    वर्ण *wp = w;
    ध्रुव वर्ण *s0 = s;
    पूर्णाङ्क ret = 0;

    यदि (!w)
        प्रत्यागम AVERROR(ENOMEM);

    यावत् (*s)
        यदि (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.राशिः_सूचकांक=100;
    p.s= w;
    p.const_नामानि = const_नामानि;
    p.funcs1      = funcs1;
    p.func1_नामानि = func1_नामानि;
    p.funcs2      = funcs2;
    p.func2_नामानि = func2_नामानि;
    p.log_विस्थापनम् = log_विस्थापनम्;
    p.log_ctx    = log_ctx;

    यदि ((ret = parse_व्यञ्जकम्(&e, &p)) < 0)
        गच्छ अन्तः_2;
    यदि (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        गच्छ अन्तः_2;
    }
    यदि (!verify_व्यञ्जकम्(e)) {
        ret = AVERROR(EINVAL);
        गच्छ अन्तः_2;
    }
    AVExpr_मूलम् *r = av_realloc(e, परिमाण(*r));
    यदि (!r) {
        ret = AVERROR(ENOMEM);
        गच्छ अन्तः_2;
    }
    e = (AVExpr*)r;
    e->मूलम् = 1;
    r->var= av_mallocz(परिमाण(द्विगुण) *VARS);
    r->prng_state = av_mallocz(परिमाण(*r->prng_state) *VARS);
    यदि (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        गच्छ अन्तः_2;
    }
    *व्यञ्जकम् = e;
    e = रिक्त;
अन्तः_2:
    av_व्यञ्जकम्_free(e);
    av_free(w);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क व्यञ्जकम्_गणनम्(AVExpr *e, अचिह्नित *गणक, पूर्णाङ्क आकार, पूर्णाङ्क type)
{
    पूर्णाङ्क i;

    यदि (!e || !गणक || !आकार)
        प्रत्यागम AVERROR(EINVAL);

    प्रति (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        व्यञ्जकम्_गणनम्(e->param[i], गणक, आकार, type);

    यदि (e->type == type && e->const_सूचकांक < आकार)
        गणक[e->const_सूचकांक]++;

    प्रत्यागम 0;
}

पूर्णाङ्क av_व्यञ्जकम्_गणनम्_vars(AVExpr *e, अचिह्नित *गणक, पूर्णाङ्क आकार)
{
    प्रत्यागम व्यञ्जकम्_गणनम्(e, गणक, आकार, e_const);
}

पूर्णाङ्क av_व्यञ्जकम्_गणनम्_func(AVExpr *e, अचिह्नित *गणक, पूर्णाङ्क आकार, पूर्णाङ्क arg)
{
    प्रत्यागम व्यञ्जकम्_गणनम्(e, गणक, आकार, ((पूर्णाङ्क[]){e_const, e_func1, e_func2})[arg]);
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

    प्रत्यागम eval_व्यञ्जकम्(&p, e);
}

पूर्णाङ्क av_व्यञ्जकम्_parse_and_eval(द्विगुण *d, ध्रुव वर्ण *s,
                           ध्रुव वर्ण * ध्रुव *const_नामानि, ध्रुव द्विगुण *const_मानानि,
                           ध्रुव वर्ण * ध्रुव *func1_नामानि, द्विगुण (* ध्रुव *funcs1)(शून्य *, द्विगुण),
                           ध्रुव वर्ण * ध्रुव *func2_नामानि, द्विगुण (* ध्रुव *funcs2)(शून्य *, द्विगुण, द्विगुण),
                           शून्य *opaque, पूर्णाङ्क log_विस्थापनम्, शून्य *log_ctx)
{
    AVExpr *e = रिक्त;
    पूर्णाङ्क ret = av_व्यञ्जकम्_parse(&e, s, const_नामानि, func1_नामानि, funcs1, func2_नामानि, funcs2, log_विस्थापनम्, log_ctx);

    यदि (ret < 0) {
        *d = NAN;
        प्रत्यागम ret;
    }
    *d = av_व्यञ्जकम्_eval(e, const_मानानि, opaque);
    av_व्यञ्जकम्_free(e);
    प्रत्यागम isnan(*d) ? AVERROR(EINVAL) : 0;
}
