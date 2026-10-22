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

#அந்தர்பாவ <float.h>
#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "avutil.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "eval.h"
#அந்தர்பாவ "ffmath.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "mathematics.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "sfc64.h"
#அந்தர்பாவ "time.h"
#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "reverse.h"

#define MAX_DEPTH 100

வகைவரை கட்டமைப்பு Parser {
    மாறிலி AVClass *class;
    முழு அடுக்கு_index;
    எழுத்து *s;
    மாறிலி இரட்டை *const_மதிப்புகள்;
    மாறிலி எழுத்து * மாறிலி *const_names;          // NULL terminated
    இரட்டை (* மாறிலி *funcs1)(வெறுமை *, இரட்டை a);           // NULL terminated
    மாறிலி எழுத்து * மாறிலி *func1_names;          // NULL terminated
    இரட்டை (* மாறிலி *funcs2)(வெறுமை *, இரட்டை a, இரட்டை b); // NULL terminated
    மாறிலி எழுத்து * மாறிலி *func2_names;          // NULL terminated
    வெறுமை *opaque;
    முழு log_offset;
    வெறுமை *log_ctx;
#define VARS 10
    இரட்டை *var;
    FFSFC64 *prng_state;
} Parser;

நிலையான மாறிலி AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = வெற்று,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

நிலையான மாறிலி கட்டமைப்பு {
    இரட்டை bin_val;
    இரட்டை dec_val;
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

நிலையான மாறிலி கட்டமைப்பு {
    மாறிலி எழுத்து *name;
    இரட்டை மதிப்பு;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

இரட்டை av_strtod(மாறிலி எழுத்து *numstr, எழுத்து **tail)
{
    இரட்டை d;
    எழுத்து *next;
    எனில்(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } இல்லையெனில்
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    எனில் (next!=numstr) {
        எனில் (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } இல்லையெனில் எனில் (*next >= 'E' && *next <= 'z') {
            முழு e= si_prefixes[*next - 'E'].exp;
            எனில் (e) {
                எனில் (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } இல்லையெனில் {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        எனில் (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    எனில் (tail)
        *tail = next;
    திரும்பு d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

நிலையான முழு strmatch(மாறிலி எழுத்து *s, மாறிலி எழுத்து *prefix)
{
    முழு i;
    க்கு (i=0; prefix[i]; i++) {
        எனில் (prefix[i] != s[i]) திரும்பு 0;
    }
    /* return 1 only if the s identifier is terminated */
    திரும்பு !IS_IDENTIFIER_CHAR(s[i]);
}

எண்ணிக்கை {
    e_மதிப்பு, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_வேர், e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
கட்டமைப்பு AVExpr {
    unsigned எழுத்து type;
    unsigned எழுத்து வேர்;
    short depth;
    முழு const_index;
    இரட்டை மதிப்பு; // is sign in other types
    ஒன்றிப்பு {
        இரட்டை (*func0)(இரட்டை);
        இரட்டை (*func1)(வெறுமை *, இரட்டை);
        இரட்டை (*func2)(வெறுமை *, இரட்டை, இரட்டை);
    } ;
    கட்டமைப்பு AVExpr *param[3];
};

வகைவரை கட்டமைப்பு {
    AVExpr avexpr;
    இரட்டை *var;
    FFSFC64 *prng_state;
} AVExpr_வேர்;

நிலையான இரட்டை etime(இரட்டை v)
{
    திரும்பு av_gettime() * 0.000001;
}

நிலையான இரட்டை eval_கோவை(Parser *p, AVExpr *e)
{
    தேர்வு (e->type) {
        நிலை e_மதிப்பு:  திரும்பு e->மதிப்பு;
        நிலை e_const:  திரும்பு e->மதிப்பு * p->const_மதிப்புகள்[e->const_index];
        நிலை e_func0:  திரும்பு e->மதிப்பு * e->func0(eval_கோவை(p, e->param[0]));
        நிலை e_func1:  திரும்பு e->மதிப்பு * e->func1(p->opaque, eval_கோவை(p, e->param[0]));
        நிலை e_func2:  திரும்பு e->மதிப்பு * e->func2(p->opaque, eval_கோவை(p, e->param[0]), eval_கோவை(p, e->param[1]));
        நிலை e_squish: திரும்பு e->மதிப்பு/(1+exp(4*eval_கோவை(p, e->param[0])));
        நிலை e_gauss: { இரட்டை d = eval_கோவை(p, e->param[0]); திரும்பு e->மதிப்பு * exp(-d*d/2)/sqrt(2*M_PI); }
        நிலை e_ld:     திரும்பு e->மதிப்பு * p->var[av_clip(eval_கோவை(p, e->param[0]), 0, VARS-1)];
        நிலை e_isnan:  திரும்பு e->மதிப்பு * !!isnan(eval_கோவை(p, e->param[0]));
        நிலை e_isinf:  திரும்பு e->மதிப்பு * !!isinf(eval_கோவை(p, e->param[0]));
        நிலை e_floor:  திரும்பு e->மதிப்பு * floor(eval_கோவை(p, e->param[0]));
        நிலை e_ceil :  திரும்பு e->மதிப்பு * ceil (eval_கோவை(p, e->param[0]));
        நிலை e_trunc:  திரும்பு e->மதிப்பு * trunc(eval_கோவை(p, e->param[0]));
        நிலை e_round:  திரும்பு e->மதிப்பு * round(eval_கோவை(p, e->param[0]));
        நிலை e_sgn:    திரும்பு e->மதிப்பு * FFDIFFSIGN(eval_கோவை(p, e->param[0]), 0);
        நிலை e_sqrt:   திரும்பு e->மதிப்பு * sqrt (eval_கோவை(p, e->param[0]));
        நிலை e_not:    திரும்பு e->மதிப்பு * (eval_கோவை(p, e->param[0]) == 0);
        நிலை e_if:     திரும்பு e->மதிப்பு * (eval_கோவை(p, e->param[0]) ? eval_கோவை(p, e->param[1]) :
                                          e->param[2] ? eval_கோவை(p, e->param[2]) : 0);
        நிலை e_ifnot:  திரும்பு e->மதிப்பு * (!eval_கோவை(p, e->param[0]) ? eval_கோவை(p, e->param[1]) :
                                          e->param[2] ? eval_கோவை(p, e->param[2]) : 0);
        நிலை e_clip: {
            இரட்டை x = eval_கோவை(p, e->param[0]);
            இரட்டை min = eval_கோவை(p, e->param[1]), max = eval_கோவை(p, e->param[2]);
            எனில் (isnan(min) || isnan(max) || isnan(x) || min > max)
                திரும்பு NAN;
            திரும்பு e->மதிப்பு * av_clipd(x, min, max);
        }
        நிலை e_between: {
            இரட்டை d = eval_கோவை(p, e->param[0]);
            திரும்பு e->மதிப்பு * (d >= eval_கோவை(p, e->param[1]) &&
                               d <= eval_கோவை(p, e->param[2]));
        }
        நிலை e_lerp: {
            இரட்டை v0 = eval_கோவை(p, e->param[0]);
            இரட்டை v1 = eval_கோவை(p, e->param[1]);
            இரட்டை f  = eval_கோவை(p, e->param[2]);
            திரும்பு e->மதிப்பு * (v0 + (v1 - v0) * f);
        }
        நிலை e_print: {
            இரட்டை x = eval_கோவை(p, e->param[0]);
            முழு level = e->param[1] ? av_clip(eval_கோவை(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            திரும்பு e->மதிப்பு * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            முழு idx = av_clip(eval_கோவை(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            எனில் (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        நிலை e_random: {
            COMPUTE_NEXT_RANDOM();
            திரும்பு r * (1.0/UINT64_MAX);
        }
        நிலை e_randomi: {
            இரட்டை min = eval_கோவை(p, e->param[1]);
            இரட்டை max = eval_கோவை(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            திரும்பு min + (max - min) * r / UINT64_MAX;
        }
        நிலை e_while: {
            இரட்டை d = NAN;
            போது (eval_கோவை(p, e->param[0]))
                d=eval_கோவை(p, e->param[1]);
            திரும்பு d;
        }
        நிலை e_taylor: {
            இரட்டை t = 1, d = 0, v;
            இரட்டை x = eval_கோவை(p, e->param[1]);
            முழு id = e->param[2] ? av_clip(eval_கோவை(p, e->param[2]), 0, VARS-1) : 0;
            முழு i;
            இரட்டை var0 = p->var[id];
            க்கு(i=0; i<1000; i++) {
                இரட்டை ld = d;
                p->var[id] = i;
                v = eval_கோவை(p, e->param[0]);
                d += t*v;
                எனில்(ld==d && v)
                    நிறுத்து;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            திரும்பு d;
        }
        நிலை e_வேர்: {
            முழு i, j;
            இரட்டை கீழ் = -1, உயர்வு = -1, v, கீழ்_v = -DBL_MAX, உயர்வு_v = DBL_MAX;
            இரட்டை var0 = p->var[0];
            இரட்டை x_max = eval_கோவை(p, e->param[1]);
            க்கு(i=-1; i<1024; i++) {
                எனில்(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } இல்லையெனில் {
                    p->var[0] = x_max*pow(0.9, i-255);
                    எனில் (i&1) p->var[0] *= -1;
                    எனில் (i&2) p->var[0] += கீழ்;
                    இல்லையெனில்     p->var[0] += உயர்வு;
                }
                v = eval_கோவை(p, e->param[0]);
                எனில் (v<=0 && v>கீழ்_v) {
                    கீழ்    = p->var[0];
                    கீழ்_v  = v;
                }
                எனில் (v>=0 && v<உயர்வு_v) {
                    உயர்வு   = p->var[0];
                    உயர்வு_v = v;
                }
                எனில் (கீழ்>=0 && உயர்வு>=0){
                    க்கு (j=0; j<1000; j++) {
                        p->var[0] = (கீழ்+உயர்வு)*0.5;
                        எனில் (கீழ் == p->var[0] || உயர்வு == p->var[0])
                            நிறுத்து;
                        v = eval_கோவை(p, e->param[0]);
                        எனில் (v<=0) கீழ் = p->var[0];
                        எனில் (v>=0) உயர்வு= p->var[0];
                        எனில் (isnan(v)) {
                            கீழ் = உயர்வு = v;
                            நிறுத்து;
                        }
                    }
                    நிறுத்து;
                }
            }
            p->var[0] = var0;
            திரும்பு -கீழ்_v<உயர்வு_v ? கீழ் : உயர்வு;
        }
        இயல்பு: {
            இரட்டை d = eval_கோவை(p, e->param[0]);
            இரட்டை d2 = eval_கோவை(p, e->param[1]);
            தேர்வு (e->type) {
                நிலை e_mod: திரும்பு e->மதிப்பு * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                நிலை e_gcd: திரும்பு e->மதிப்பு * av_gcd(d,d2);
                நிலை e_max: திரும்பு e->மதிப்பு * (d >  d2 ?   d : d2);
                நிலை e_min: திரும்பு e->மதிப்பு * (d <  d2 ?   d : d2);
                நிலை e_eq:  திரும்பு e->மதிப்பு * (d == d2 ? 1.0 : 0.0);
                நிலை e_gt:  திரும்பு e->மதிப்பு * (d >  d2 ? 1.0 : 0.0);
                நிலை e_gte: திரும்பு e->மதிப்பு * (d >= d2 ? 1.0 : 0.0);
                நிலை e_lt:  திரும்பு e->மதிப்பு * (d <  d2 ? 1.0 : 0.0);
                நிலை e_lte: திரும்பு e->மதிப்பு * (d <= d2 ? 1.0 : 0.0);
                நிலை e_pow: திரும்பு e->மதிப்பு * pow(d, d2);
                நிலை e_mul: திரும்பு e->மதிப்பு * (d * d2);
                நிலை e_div: திரும்பு e->மதிப்பு * (d2 ? (d / d2) : d * INFINITY);
                நிலை e_add: திரும்பு e->மதிப்பு * (d + d2);
                நிலை e_last:திரும்பு e->மதிப்பு * d2;
                நிலை e_st :  {
                    முழு index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    திரும்பு e->மதிப்பு * (p->var[index]= d2);
                }
                நிலை e_hypot:திரும்பு e->மதிப்பு * hypot(d, d2);
                நிலை e_atan2:திரும்பு e->மதிப்பு * atan2(d, d2);
                நிலை e_bitand: திரும்பு isnan(d) || isnan(d2) ? NAN : e->மதிப்பு * ((long முழு)d & (long முழு)d2);
                நிலை e_bitor:  திரும்பு isnan(d) || isnan(d2) ? NAN : e->மதிப்பு * ((long முழு)d | (long முழு)d2);
            }
        }
    }
    திரும்பு NAN;
}

நிலையான முழு parse_கோவை(AVExpr **e, Parser *p);

வெறுமை av_கோவை_free(AVExpr *e)
{
    எனில் (!e) திரும்பு;
    av_கோவை_free(e->param[0]);
    av_கோவை_free(e->param[1]);
    av_கோவை_free(e->param[2]);
    எனில் (e->வேர்) {
        AVExpr_வேர் *r = (AVExpr_வேர்*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

நிலையான முழு parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(அளவு(AVExpr));
    எழுத்து *next = p->s, *s0 = p->s;
    முழு ret, i;

    எனில் (!d)
        திரும்பு AVERROR(ENOMEM);

    /*எண்*/
    d->மதிப்பு = av_strtod(p->s, &next);
    எனில் (next != p->s) {
        d->type = e_மதிப்பு;
        p->s= next;
        *e = d;
        திரும்பு 0;
    }
    d->மதிப்பு = 1;

    /* named constants */
    க்கு (i=0; p->const_names && p->const_names[i]; i++) {
        எனில் (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            திரும்பு 0;
        }
    }
    க்கு (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        எனில் (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_மதிப்பு;
            d->மதிப்பு = constants[i].மதிப்பு;
            *e = d;
            திரும்பு 0;
        }
    }

    p->s= strchr(p->s, '(');
    எனில் (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_கோவை_free(d);
        திரும்பு AVERROR(EINVAL);
    }
    p->s++; // "("
    எனில் (*next == '(') { // special case do-nothing
        av_freep(&d);
        எனில் ((ret = parse_கோவை(&d, p)) < 0)
            திரும்பு ret;
        எனில் (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_கோவை_free(d);
            திரும்பு AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        திரும்பு 0;
    }
    எனில் ((ret = parse_கோவை(&(d->param[0]), p)) < 0) {
        av_கோவை_free(d);
        திரும்பு ret;
    }
    எனில் (p->s[0]== ',') {
        p->s++; // ","
        parse_கோவை(&d->param[1], p);
    }
    எனில் (p->s[0]== ',') {
        p->s++; // ","
        parse_கோவை(&d->param[2], p);
    }
    எனில் (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_கோவை_free(d);
        திரும்பு AVERROR(EINVAL);
    }
    p->s++; // ")"

    க்கு (முழு i = 0; i<3; i++)
        எனில் (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    எனில் (d->depth > MAX_DEPTH) {
        av_கோவை_free(d);
        திரும்பு AVERROR(EINVAL);
    }

    d->type = e_func0;
         எனில் (strmatch(next, "sinh"  )) d->func0 = sinh;
    இல்லையெனில் எனில் (strmatch(next, "cosh"  )) d->func0 = cosh;
    இல்லையெனில் எனில் (strmatch(next, "tanh"  )) d->func0 = tanh;
    இல்லையெனில் எனில் (strmatch(next, "sin"   )) d->func0 = sin;
    இல்லையெனில் எனில் (strmatch(next, "cos"   )) d->func0 = cos;
    இல்லையெனில் எனில் (strmatch(next, "tan"   )) d->func0 = tan;
    இல்லையெனில் எனில் (strmatch(next, "atan"  )) d->func0 = atan;
    இல்லையெனில் எனில் (strmatch(next, "asin"  )) d->func0 = asin;
    இல்லையெனில் எனில் (strmatch(next, "acos"  )) d->func0 = acos;
    இல்லையெனில் எனில் (strmatch(next, "exp"   )) d->func0 = exp;
    இல்லையெனில் எனில் (strmatch(next, "log"   )) d->func0 = log;
    இல்லையெனில் எனில் (strmatch(next, "abs"   )) d->func0 = fabs;
    இல்லையெனில் எனில் (strmatch(next, "time"  )) d->func0 = etime;
    இல்லையெனில் எனில் (strmatch(next, "squish")) d->type = e_squish;
    இல்லையெனில் எனில் (strmatch(next, "gauss" )) d->type = e_gauss;
    இல்லையெனில் எனில் (strmatch(next, "mod"   )) d->type = e_mod;
    இல்லையெனில் எனில் (strmatch(next, "max"   )) d->type = e_max;
    இல்லையெனில் எனில் (strmatch(next, "min"   )) d->type = e_min;
    இல்லையெனில் எனில் (strmatch(next, "eq"    )) d->type = e_eq;
    இல்லையெனில் எனில் (strmatch(next, "gte"   )) d->type = e_gte;
    இல்லையெனில் எனில் (strmatch(next, "gt"    )) d->type = e_gt;
    இல்லையெனில் எனில் (strmatch(next, "lte"   )) d->type = e_lte;
    இல்லையெனில் எனில் (strmatch(next, "lt"    )) d->type = e_lt;
    இல்லையெனில் எனில் (strmatch(next, "ld"    )) d->type = e_ld;
    இல்லையெனில் எனில் (strmatch(next, "isnan" )) d->type = e_isnan;
    இல்லையெனில் எனில் (strmatch(next, "isinf" )) d->type = e_isinf;
    இல்லையெனில் எனில் (strmatch(next, "st"    )) d->type = e_st;
    இல்லையெனில் எனில் (strmatch(next, "while" )) d->type = e_while;
    இல்லையெனில் எனில் (strmatch(next, "taylor")) d->type = e_taylor;
    இல்லையெனில் எனில் (strmatch(next, "root"  )) d->type = e_வேர்;
    இல்லையெனில் எனில் (strmatch(next, "floor" )) d->type = e_floor;
    இல்லையெனில் எனில் (strmatch(next, "ceil"  )) d->type = e_ceil;
    இல்லையெனில் எனில் (strmatch(next, "trunc" )) d->type = e_trunc;
    இல்லையெனில் எனில் (strmatch(next, "round" )) d->type = e_round;
    இல்லையெனில் எனில் (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    இல்லையெனில் எனில் (strmatch(next, "not"   )) d->type = e_not;
    இல்லையெனில் எனில் (strmatch(next, "pow"   )) d->type = e_pow;
    இல்லையெனில் எனில் (strmatch(next, "print" )) d->type = e_print;
    இல்லையெனில் எனில் (strmatch(next, "random")) d->type = e_random;
    இல்லையெனில் எனில் (strmatch(next, "randomi")) d->type = e_randomi;
    இல்லையெனில் எனில் (strmatch(next, "hypot" )) d->type = e_hypot;
    இல்லையெனில் எனில் (strmatch(next, "gcd"   )) d->type = e_gcd;
    இல்லையெனில் எனில் (strmatch(next, "if"    )) d->type = e_if;
    இல்லையெனில் எனில் (strmatch(next, "ifnot" )) d->type = e_ifnot;
    இல்லையெனில் எனில் (strmatch(next, "bitand")) d->type = e_bitand;
    இல்லையெனில் எனில் (strmatch(next, "bitor" )) d->type = e_bitor;
    இல்லையெனில் எனில் (strmatch(next, "between"))d->type = e_between;
    இல்லையெனில் எனில் (strmatch(next, "clip"  )) d->type = e_clip;
    இல்லையெனில் எனில் (strmatch(next, "atan2" )) d->type = e_atan2;
    இல்லையெனில் எனில் (strmatch(next, "lerp"  )) d->type = e_lerp;
    இல்லையெனில் எனில் (strmatch(next, "sgn"   )) d->type = e_sgn;
    இல்லையெனில் {
        க்கு (i=0; p->func1_names && p->func1_names[i]; i++) {
            எனில் (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                திரும்பு 0;
            }
        }

        க்கு (i=0; p->func2_names && p->func2_names[i]; i++) {
            எனில் (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                திரும்பு 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_கோவை_free(d);
        திரும்பு AVERROR(EINVAL);
    }

    *e = d;
    திரும்பு 0;
}

நிலையான AVExpr *make_eval_கோவை(முழு type, முழு மதிப்பு, AVExpr *p0, AVExpr *p1)
{
    முழு depth = FFMAX(p0->depth, p1->depth) + 1;
    எனில் (depth > MAX_DEPTH)
        திரும்பு வெற்று;
    AVExpr *e = av_mallocz(அளவு(AVExpr));
    எனில் (!e)
        திரும்பு வெற்று;
    e->type     =type   ;
    e->மதிப்பு    =மதிப்பு  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    திரும்பு e;
}

நிலையான முழு parse_pow(AVExpr **e, Parser *p, முழு *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    திரும்பு parse_primary(e, p);
}

நிலையான முழு parse_dB(AVExpr **e, Parser *p, முழு *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    எனில் (*p->s == '-') {
        எழுத்து *next;
        av_unused இரட்டை ignored = strtod(p->s, &next);
        எனில் (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            திரும்பு parse_primary(e, p);
        }
    }
    திரும்பு parse_pow(e, p, sign);
}

நிலையான முழு parse_factor(AVExpr **e, Parser *p)
{
    முழு sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    எனில் ((ret = parse_dB(&e0, p, &sign)) < 0)
        திரும்பு ret;
    போது(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        எனில் ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_கோவை_free(e1);
            திரும்பு ret;
        }
        e0 = make_eval_கோவை(e_pow, 1, e1, e2);
        எனில் (!e0) {
            av_கோவை_free(e1);
            av_கோவை_free(e2);
            திரும்பு AVERROR(ENOMEM);
        }
        எனில் (e0->param[1]) e0->param[1]->மதிப்பு *= (sign2|1);
    }
    எனில் (e0) e0->மதிப்பு *= (sign|1);

    *e = e0;
    திரும்பு 0;
}

நிலையான முழு parse_term(AVExpr **e, Parser *p)
{
    முழு ret;
    AVExpr *e0, *e1, *e2;
    எனில் ((ret = parse_factor(&e0, p)) < 0)
        திரும்பு ret;
    போது (p->s[0]=='*' || p->s[0]=='/') {
        முழு c= *p->s++;
        e1 = e0;
        எனில் ((ret = parse_factor(&e2, p)) < 0) {
            av_கோவை_free(e1);
            திரும்பு ret;
        }
        e0 = make_eval_கோவை(c == '*' ? e_mul : e_div, 1, e1, e2);
        எனில் (!e0) {
            av_கோவை_free(e1);
            av_கோவை_free(e2);
            திரும்பு AVERROR(ENOMEM);
        }
    }
    *e = e0;
    திரும்பு 0;
}

நிலையான முழு parse_subexpr(AVExpr **e, Parser *p)
{
    முழு ret;
    AVExpr *e0, *e1, *e2;
    எனில் ((ret = parse_term(&e0, p)) < 0)
        திரும்பு ret;
    போது (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        எனில் ((ret = parse_term(&e2, p)) < 0) {
            av_கோவை_free(e1);
            திரும்பு ret;
        }
        e0 = make_eval_கோவை(e_add, 1, e1, e2);
        எனில் (!e0) {
            av_கோவை_free(e1);
            av_கோவை_free(e2);
            திரும்பு AVERROR(ENOMEM);
        }
    };

    *e = e0;
    திரும்பு 0;
}

நிலையான முழு parse_கோவை(AVExpr **e, Parser *p)
{
    முழு ret;
    AVExpr *e0, *e1, *e2;
    எனில் (p->அடுக்கு_index <= 0) //protect against stack overflows
        திரும்பு AVERROR(EINVAL);
    p->அடுக்கு_index--;

    எனில் ((ret = parse_subexpr(&e0, p)) < 0)
        திரும்பு ret;
    போது (*p->s == ';') {
        p->s++;
        e1 = e0;
        எனில் ((ret = parse_subexpr(&e2, p)) < 0) {
            av_கோவை_free(e1);
            திரும்பு ret;
        }
        e0 = make_eval_கோவை(e_last, 1, e1, e2);
        எனில் (!e0) {
            av_கோவை_free(e1);
            av_கோவை_free(e2);
            திரும்பு AVERROR(ENOMEM);
        }
    };

    p->அடுக்கு_index++;
    *e = e0;
    திரும்பு 0;
}

நிலையான முழு verify_கோவை(AVExpr *e)
{
    எனில் (!e) திரும்பு 0;
    தேர்வு (e->type) {
        நிலை e_மதிப்பு:
        நிலை e_const: திரும்பு 1;
        நிலை e_func0:
        நிலை e_func1:
        நிலை e_squish:
        நிலை e_ld:
        நிலை e_gauss:
        நிலை e_isnan:
        நிலை e_isinf:
        நிலை e_floor:
        நிலை e_ceil:
        நிலை e_trunc:
        நிலை e_round:
        நிலை e_sqrt:
        நிலை e_not:
        நிலை e_random:
        நிலை e_sgn:
            திரும்பு verify_கோவை(e->param[0]) && !e->param[1];
        நிலை e_print:
            திரும்பு verify_கோவை(e->param[0])
                   && (!e->param[1] || verify_கோவை(e->param[1]));
        நிலை e_if:
        நிலை e_ifnot:
        நிலை e_taylor:
            திரும்பு verify_கோவை(e->param[0]) && verify_கோவை(e->param[1])
                   && (!e->param[2] || verify_கோவை(e->param[2]));
        நிலை e_between:
        நிலை e_clip:
        நிலை e_lerp:
        நிலை e_randomi:
            திரும்பு verify_கோவை(e->param[0]) &&
                   verify_கோவை(e->param[1]) &&
                   verify_கோவை(e->param[2]);
        இயல்பு: திரும்பு verify_கோவை(e->param[0]) && verify_கோவை(e->param[1]) && !e->param[2];
    }
}

முழு av_கோவை_parse(AVExpr **கோவை, மாறிலி எழுத்து *s,
                  மாறிலி எழுத்து * மாறிலி *const_names,
                  மாறிலி எழுத்து * மாறிலி *func1_names, இரட்டை (* மாறிலி *funcs1)(வெறுமை *, இரட்டை),
                  மாறிலி எழுத்து * மாறிலி *func2_names, இரட்டை (* மாறிலி *funcs2)(வெறுமை *, இரட்டை, இரட்டை),
                  முழு log_offset, வெறுமை *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = வெற்று;
    எழுத்து *w = av_malloc(strlen(s) + 1);
    எழுத்து *wp = w;
    மாறிலி எழுத்து *s0 = s;
    முழு ret = 0;

    எனில் (!w)
        திரும்பு AVERROR(ENOMEM);

    போது (*s)
        எனில் (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.அடுக்கு_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    எனில் ((ret = parse_கோவை(&e, &p)) < 0)
        செல் end;
    எனில் (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        செல் end;
    }
    எனில் (!verify_கோவை(e)) {
        ret = AVERROR(EINVAL);
        செல் end;
    }
    AVExpr_வேர் *r = av_realloc(e, அளவு(*r));
    எனில் (!r) {
        ret = AVERROR(ENOMEM);
        செல் end;
    }
    e = (AVExpr*)r;
    e->வேர் = 1;
    r->var= av_mallocz(அளவு(இரட்டை) *VARS);
    r->prng_state = av_mallocz(அளவு(*r->prng_state) *VARS);
    எனில் (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        செல் end;
    }
    *கோவை = e;
    e = வெற்று;
end:
    av_கோவை_free(e);
    av_free(w);
    திரும்பு ret;
}

நிலையான முழு கோவை_மொத்தம்(AVExpr *e, unsigned *counter, முழு size, முழு type)
{
    முழு i;

    எனில் (!e || !counter || !size)
        திரும்பு AVERROR(EINVAL);

    க்கு (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        கோவை_மொத்தம்(e->param[i], counter, size, type);

    எனில் (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    திரும்பு 0;
}

முழு av_கோவை_மொத்தம்_vars(AVExpr *e, unsigned *counter, முழு size)
{
    திரும்பு கோவை_மொத்தம்(e, counter, size, e_const);
}

முழு av_கோவை_மொத்தம்_func(AVExpr *e, unsigned *counter, முழு size, முழு arg)
{
    திரும்பு கோவை_மொத்தம்(e, counter, size, ((முழு[]){e_const, e_func1, e_func2})[arg]);
}

இரட்டை av_கோவை_eval(AVExpr *e, மாறிலி இரட்டை *const_மதிப்புகள், வெறுமை *opaque)
{
    av_assert1(e->வேர்);
    AVExpr_வேர் *r = (AVExpr_வேர் *)e;
    Parser p = {
        .class        = &eval_class,
        .const_மதிப்புகள் = const_மதிப்புகள்,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    திரும்பு eval_கோவை(&p, e);
}

முழு av_கோவை_parse_and_eval(இரட்டை *d, மாறிலி எழுத்து *s,
                           மாறிலி எழுத்து * மாறிலி *const_names, மாறிலி இரட்டை *const_மதிப்புகள்,
                           மாறிலி எழுத்து * மாறிலி *func1_names, இரட்டை (* மாறிலி *funcs1)(வெறுமை *, இரட்டை),
                           மாறிலி எழுத்து * மாறிலி *func2_names, இரட்டை (* மாறிலி *funcs2)(வெறுமை *, இரட்டை, இரட்டை),
                           வெறுமை *opaque, முழு log_offset, வெறுமை *log_ctx)
{
    AVExpr *e = வெற்று;
    முழு ret = av_கோவை_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    எனில் (ret < 0) {
        *d = NAN;
        திரும்பு ret;
    }
    *d = av_கோவை_eval(e, const_மதிப்புகள், opaque);
    av_கோவை_free(e);
    திரும்பு isnan(*d) ? AVERROR(EINVAL) : 0;
}
