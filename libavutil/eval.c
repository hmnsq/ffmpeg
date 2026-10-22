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

#شامل <float.h>
#شامل "attributes.h"
#شامل "avassert.h"
#شامل "avutil.h"
#شامل "common.h"
#شامل "eval.h"
#شامل "ffmath.h"
#شامل "log.h"
#شامل "mathematics.h"
#شامل "mem.h"
#شامل "sfc64.h"
#شامل "time.h"
#شامل "avstring.h"
#شامل "reverse.h"

#define MAX_DEPTH 100

تعریفنوع ساختار Parser {
    ثابت AVClass *class;
    صحیح پشته_index;
    نویسه *s;
    ثابت دوگانه *const_مقادیر;
    ثابت نویسه * ثابت *const_names;          // NULL terminated
    دوگانه (* ثابت *funcs1)(تهی *, دوگانه a);           // NULL terminated
    ثابت نویسه * ثابت *func1_names;          // NULL terminated
    دوگانه (* ثابت *funcs2)(تهی *, دوگانه a, دوگانه b); // NULL terminated
    ثابت نویسه * ثابت *func2_names;          // NULL terminated
    تهی *opaque;
    صحیح log_offset;
    تهی *log_ctx;
#define VARS 10
    دوگانه *var;
    FFSFC64 *prng_state;
} Parser;

ایستا ثابت AVClass eval_class = {
    .class_name                = "Eval",
    .item_name                 = av_default_item_name,
    .option                    = پوچ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(Parser, log_offset),
    .parent_log_context_offset = offsetof(Parser, log_ctx),
};

ایستا ثابت ساختار {
    دوگانه bin_val;
    دوگانه dec_val;
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

ایستا ثابت ساختار {
    ثابت نویسه *name;
    دوگانه مقدار;
} constants[] = {
    { "E",   M_E   },
    { "PI",  M_PI  },
    { "PHI", M_PHI },
    { "QP2LAMBDA", FF_QP2LAMBDA },
};

دوگانه av_strtod(ثابت نویسه *numstr, نویسه **tail)
{
    دوگانه d;
    نویسه *next;
    اگر(numstr[0]=='0' && (numstr[1]|0x20)=='x') {
        d = strtoul(numstr, &next, 16);
    } وگرنه
        d = strtod(numstr, &next);
    /* if parsing succeeded, check for and interpret postfixes */
    اگر (next!=numstr) {
        اگر (next[0] == 'd' && next[1] == 'B') {
            /* treat dB as decibels instead of decibytes */
            d = ff_exp10(d / 20);
            next += 2;
        } وگرنه اگر (*next >= 'E' && *next <= 'z') {
            صحیح e= si_prefixes[*next - 'E'].exp;
            اگر (e) {
                اگر (next[1] == 'i') {
                    d*= si_prefixes[*next - 'E'].bin_val;
                    next+=2;
                } وگرنه {
                    d*= si_prefixes[*next - 'E'].dec_val;
                    next++;
                }
            }
        }

        اگر (*next=='B') {
            d*=8;
            next++;
        }
    }
    /* if requested, fill in tail with the position after the last parsed
       character */
    اگر (tail)
        *tail = next;
    بازگشت d;
}

#define IS_IDENTIFIER_CHAR(c) ((c) - '0' <= 9U || (c) - 'a' <= 25U || (c) - 'A' <= 25U || (c) == '_')

ایستا صحیح strmatch(ثابت نویسه *s, ثابت نویسه *prefix)
{
    صحیح i;
    برای (i=0; prefix[i]; i++) {
        اگر (prefix[i] != s[i]) بازگشت 0;
    }
    /* return 1 only if the s identifier is terminated */
    بازگشت !IS_IDENTIFIER_CHAR(s[i]);
}

شمارش {
    e_مقدار, e_const, e_func0, e_func1, e_func2,
    e_squish, e_gauss, e_ld, e_isnan, e_isinf,
    e_mod, e_max, e_min, e_eq, e_gt, e_gte, e_lte, e_lt,
    e_pow, e_mul, e_div, e_add,
    e_last, e_st, e_while, e_taylor, e_ریشه, e_floor, e_ceil, e_trunc, e_round,
    e_sqrt, e_not, e_random, e_hypot, e_gcd,
    e_if, e_ifnot, e_print, e_bitand, e_bitor, e_between, e_clip, e_atan2, e_lerp,
    e_sgn, e_randomi
};
ساختار AVExpr {
    unsigned نویسه type;
    unsigned نویسه ریشه;
    short depth;
    صحیح const_index;
    دوگانه مقدار; // is sign in other types
    اجتماع {
        دوگانه (*func0)(دوگانه);
        دوگانه (*func1)(تهی *, دوگانه);
        دوگانه (*func2)(تهی *, دوگانه, دوگانه);
    } ;
    ساختار AVExpr *param[3];
};

تعریفنوع ساختار {
    AVExpr avexpr;
    دوگانه *var;
    FFSFC64 *prng_state;
} AVExpr_ریشه;

ایستا دوگانه etime(دوگانه v)
{
    بازگشت av_gettime() * 0.000001;
}

ایستا دوگانه eval_عبارت(Parser *p, AVExpr *e)
{
    انتخاب (e->type) {
        حالت e_مقدار:  بازگشت e->مقدار;
        حالت e_const:  بازگشت e->مقدار * p->const_مقادیر[e->const_index];
        حالت e_func0:  بازگشت e->مقدار * e->func0(eval_عبارت(p, e->param[0]));
        حالت e_func1:  بازگشت e->مقدار * e->func1(p->opaque, eval_عبارت(p, e->param[0]));
        حالت e_func2:  بازگشت e->مقدار * e->func2(p->opaque, eval_عبارت(p, e->param[0]), eval_عبارت(p, e->param[1]));
        حالت e_squish: بازگشت e->مقدار/(1+exp(4*eval_عبارت(p, e->param[0])));
        حالت e_gauss: { دوگانه d = eval_عبارت(p, e->param[0]); بازگشت e->مقدار * exp(-d*d/2)/sqrt(2*M_PI); }
        حالت e_ld:     بازگشت e->مقدار * p->var[av_clip(eval_عبارت(p, e->param[0]), 0, VARS-1)];
        حالت e_isnan:  بازگشت e->مقدار * !!isnan(eval_عبارت(p, e->param[0]));
        حالت e_isinf:  بازگشت e->مقدار * !!isinf(eval_عبارت(p, e->param[0]));
        حالت e_floor:  بازگشت e->مقدار * floor(eval_عبارت(p, e->param[0]));
        حالت e_ceil :  بازگشت e->مقدار * ceil (eval_عبارت(p, e->param[0]));
        حالت e_trunc:  بازگشت e->مقدار * trunc(eval_عبارت(p, e->param[0]));
        حالت e_round:  بازگشت e->مقدار * round(eval_عبارت(p, e->param[0]));
        حالت e_sgn:    بازگشت e->مقدار * FFDIFFSIGN(eval_عبارت(p, e->param[0]), 0);
        حالت e_sqrt:   بازگشت e->مقدار * sqrt (eval_عبارت(p, e->param[0]));
        حالت e_not:    بازگشت e->مقدار * (eval_عبارت(p, e->param[0]) == 0);
        حالت e_if:     بازگشت e->مقدار * (eval_عبارت(p, e->param[0]) ? eval_عبارت(p, e->param[1]) :
                                          e->param[2] ? eval_عبارت(p, e->param[2]) : 0);
        حالت e_ifnot:  بازگشت e->مقدار * (!eval_عبارت(p, e->param[0]) ? eval_عبارت(p, e->param[1]) :
                                          e->param[2] ? eval_عبارت(p, e->param[2]) : 0);
        حالت e_clip: {
            دوگانه x = eval_عبارت(p, e->param[0]);
            دوگانه min = eval_عبارت(p, e->param[1]), max = eval_عبارت(p, e->param[2]);
            اگر (isnan(min) || isnan(max) || isnan(x) || min > max)
                بازگشت NAN;
            بازگشت e->مقدار * av_clipd(x, min, max);
        }
        حالت e_between: {
            دوگانه d = eval_عبارت(p, e->param[0]);
            بازگشت e->مقدار * (d >= eval_عبارت(p, e->param[1]) &&
                               d <= eval_عبارت(p, e->param[2]));
        }
        حالت e_lerp: {
            دوگانه v0 = eval_عبارت(p, e->param[0]);
            دوگانه v1 = eval_عبارت(p, e->param[1]);
            دوگانه f  = eval_عبارت(p, e->param[2]);
            بازگشت e->مقدار * (v0 + (v1 - v0) * f);
        }
        حالت e_print: {
            دوگانه x = eval_عبارت(p, e->param[0]);
            صحیح level = e->param[1] ? av_clip(eval_عبارت(p, e->param[1]), INT_MIN, INT_MAX) : AV_LOG_INFO;
            av_log(p, level, "%f\n", x);
            بازگشت e->مقدار * x;
        }

#define COMPUTE_NEXT_RANDOM()                                        \
            صحیح idx = av_clip(eval_عبارت(p, e->param[0]), 0, VARS-1); \
            FFSFC64 *s = p->prng_state + idx;                        \
            uint64_t r;                                              \
                                                                     \
            اگر (!s->counter) {                                       \
                r = isnan(p->var[idx]) ? 0 : p->var[idx];            \
                ff_sfc64_init(s, r, r, r, 12);                       \
            }                                                        \
            r = ff_sfc64_get(s);                                     \
            p->var[idx] = r;                                         \

        حالت e_random: {
            COMPUTE_NEXT_RANDOM();
            بازگشت r * (1.0/UINT64_MAX);
        }
        حالت e_randomi: {
            دوگانه min = eval_عبارت(p, e->param[1]);
            دوگانه max = eval_عبارت(p, e->param[2]);
            COMPUTE_NEXT_RANDOM();
            بازگشت min + (max - min) * r / UINT64_MAX;
        }
        حالت e_while: {
            دوگانه d = NAN;
            وقتی (eval_عبارت(p, e->param[0]))
                d=eval_عبارت(p, e->param[1]);
            بازگشت d;
        }
        حالت e_taylor: {
            دوگانه t = 1, d = 0, v;
            دوگانه x = eval_عبارت(p, e->param[1]);
            صحیح id = e->param[2] ? av_clip(eval_عبارت(p, e->param[2]), 0, VARS-1) : 0;
            صحیح i;
            دوگانه var0 = p->var[id];
            برای(i=0; i<1000; i++) {
                دوگانه ld = d;
                p->var[id] = i;
                v = eval_عبارت(p, e->param[0]);
                d += t*v;
                اگر(ld==d && v)
                    بشکن;
                t *= x / (i+1);
            }
            p->var[id] = var0;
            بازگشت d;
        }
        حالت e_ریشه: {
            صحیح i, j;
            دوگانه کم = -1, بالا = -1, v, کم_v = -DBL_MAX, بالا_v = DBL_MAX;
            دوگانه var0 = p->var[0];
            دوگانه x_max = eval_عبارت(p, e->param[1]);
            برای(i=-1; i<1024; i++) {
                اگر(i<255) {
                    p->var[0] = ff_reverse[i&255]*x_max/255;
                } وگرنه {
                    p->var[0] = x_max*pow(0.9, i-255);
                    اگر (i&1) p->var[0] *= -1;
                    اگر (i&2) p->var[0] += کم;
                    وگرنه     p->var[0] += بالا;
                }
                v = eval_عبارت(p, e->param[0]);
                اگر (v<=0 && v>کم_v) {
                    کم    = p->var[0];
                    کم_v  = v;
                }
                اگر (v>=0 && v<بالا_v) {
                    بالا   = p->var[0];
                    بالا_v = v;
                }
                اگر (کم>=0 && بالا>=0){
                    برای (j=0; j<1000; j++) {
                        p->var[0] = (کم+بالا)*0.5;
                        اگر (کم == p->var[0] || بالا == p->var[0])
                            بشکن;
                        v = eval_عبارت(p, e->param[0]);
                        اگر (v<=0) کم = p->var[0];
                        اگر (v>=0) بالا= p->var[0];
                        اگر (isnan(v)) {
                            کم = بالا = v;
                            بشکن;
                        }
                    }
                    بشکن;
                }
            }
            p->var[0] = var0;
            بازگشت -کم_v<بالا_v ? کم : بالا;
        }
        پیشفرض: {
            دوگانه d = eval_عبارت(p, e->param[0]);
            دوگانه d2 = eval_عبارت(p, e->param[1]);
            انتخاب (e->type) {
                حالت e_mod: بازگشت e->مقدار * (d - floor(d2 ? d / d2 : d * INFINITY) * d2);
                حالت e_gcd: بازگشت e->مقدار * av_gcd(d,d2);
                حالت e_max: بازگشت e->مقدار * (d >  d2 ?   d : d2);
                حالت e_min: بازگشت e->مقدار * (d <  d2 ?   d : d2);
                حالت e_eq:  بازگشت e->مقدار * (d == d2 ? 1.0 : 0.0);
                حالت e_gt:  بازگشت e->مقدار * (d >  d2 ? 1.0 : 0.0);
                حالت e_gte: بازگشت e->مقدار * (d >= d2 ? 1.0 : 0.0);
                حالت e_lt:  بازگشت e->مقدار * (d <  d2 ? 1.0 : 0.0);
                حالت e_lte: بازگشت e->مقدار * (d <= d2 ? 1.0 : 0.0);
                حالت e_pow: بازگشت e->مقدار * pow(d, d2);
                حالت e_mul: بازگشت e->مقدار * (d * d2);
                حالت e_div: بازگشت e->مقدار * (d2 ? (d / d2) : d * INFINITY);
                حالت e_add: بازگشت e->مقدار * (d + d2);
                حالت e_last:بازگشت e->مقدار * d2;
                حالت e_st :  {
                    صحیح index = av_clip(d, 0, VARS-1);
                    p->prng_state[index].counter = 0;
                    بازگشت e->مقدار * (p->var[index]= d2);
                }
                حالت e_hypot:بازگشت e->مقدار * hypot(d, d2);
                حالت e_atan2:بازگشت e->مقدار * atan2(d, d2);
                حالت e_bitand: بازگشت isnan(d) || isnan(d2) ? NAN : e->مقدار * ((long صحیح)d & (long صحیح)d2);
                حالت e_bitor:  بازگشت isnan(d) || isnan(d2) ? NAN : e->مقدار * ((long صحیح)d | (long صحیح)d2);
            }
        }
    }
    بازگشت NAN;
}

ایستا صحیح parse_عبارت(AVExpr **e, Parser *p);

تهی av_عبارت_free(AVExpr *e)
{
    اگر (!e) بازگشت;
    av_عبارت_free(e->param[0]);
    av_عبارت_free(e->param[1]);
    av_عبارت_free(e->param[2]);
    اگر (e->ریشه) {
        AVExpr_ریشه *r = (AVExpr_ریشه*)e;
        av_freep(&r->var);
        av_freep(&r->prng_state);
    }
    av_freep(&e);
}

ایستا صحیح parse_primary(AVExpr **e, Parser *p)
{
    AVExpr *d = av_mallocz(اندازه(AVExpr));
    نویسه *next = p->s, *s0 = p->s;
    صحیح ret, i;

    اگر (!d)
        بازگشت AVERROR(ENOMEM);

    /*عدد*/
    d->مقدار = av_strtod(p->s, &next);
    اگر (next != p->s) {
        d->type = e_مقدار;
        p->s= next;
        *e = d;
        بازگشت 0;
    }
    d->مقدار = 1;

    /* named constants */
    برای (i=0; p->const_names && p->const_names[i]; i++) {
        اگر (strmatch(p->s, p->const_names[i])) {
            p->s+= strlen(p->const_names[i]);
            d->type = e_const;
            d->const_index = i;
            *e = d;
            بازگشت 0;
        }
    }
    برای (i = 0; i < FF_ARRAY_ELEMS(constants); i++) {
        اگر (strmatch(p->s, constants[i].name)) {
            p->s += strlen(constants[i].name);
            d->type = e_مقدار;
            d->مقدار = constants[i].مقدار;
            *e = d;
            بازگشت 0;
        }
    }

    p->s= strchr(p->s, '(');
    اگر (!p->s) {
        av_log(p, AV_LOG_ERROR, "Undefined constant or missing '(' in '%s'\n", s0);
        p->s= next;
        av_عبارت_free(d);
        بازگشت AVERROR(EINVAL);
    }
    p->s++; // "("
    اگر (*next == '(') { // special case do-nothing
        av_freep(&d);
        اگر ((ret = parse_عبارت(&d, p)) < 0)
            بازگشت ret;
        اگر (p->s[0] != ')') {
            av_log(p, AV_LOG_ERROR, "Missing ')' in '%s'\n", s0);
            av_عبارت_free(d);
            بازگشت AVERROR(EINVAL);
        }
        p->s++; // ")"
        *e = d;
        بازگشت 0;
    }
    اگر ((ret = parse_عبارت(&(d->param[0]), p)) < 0) {
        av_عبارت_free(d);
        بازگشت ret;
    }
    اگر (p->s[0]== ',') {
        p->s++; // ","
        parse_عبارت(&d->param[1], p);
    }
    اگر (p->s[0]== ',') {
        p->s++; // ","
        parse_عبارت(&d->param[2], p);
    }
    اگر (p->s[0] != ')') {
        av_log(p, AV_LOG_ERROR, "Missing ')' or too many args in '%s'\n", s0);
        av_عبارت_free(d);
        بازگشت AVERROR(EINVAL);
    }
    p->s++; // ")"

    برای (صحیح i = 0; i<3; i++)
        اگر (d->param[i])
            d->depth = FFMAX(d->depth, d->param[i]->depth+1);
    اگر (d->depth > MAX_DEPTH) {
        av_عبارت_free(d);
        بازگشت AVERROR(EINVAL);
    }

    d->type = e_func0;
         اگر (strmatch(next, "sinh"  )) d->func0 = sinh;
    وگرنه اگر (strmatch(next, "cosh"  )) d->func0 = cosh;
    وگرنه اگر (strmatch(next, "tanh"  )) d->func0 = tanh;
    وگرنه اگر (strmatch(next, "sin"   )) d->func0 = sin;
    وگرنه اگر (strmatch(next, "cos"   )) d->func0 = cos;
    وگرنه اگر (strmatch(next, "tan"   )) d->func0 = tan;
    وگرنه اگر (strmatch(next, "atan"  )) d->func0 = atan;
    وگرنه اگر (strmatch(next, "asin"  )) d->func0 = asin;
    وگرنه اگر (strmatch(next, "acos"  )) d->func0 = acos;
    وگرنه اگر (strmatch(next, "exp"   )) d->func0 = exp;
    وگرنه اگر (strmatch(next, "log"   )) d->func0 = log;
    وگرنه اگر (strmatch(next, "abs"   )) d->func0 = fabs;
    وگرنه اگر (strmatch(next, "time"  )) d->func0 = etime;
    وگرنه اگر (strmatch(next, "squish")) d->type = e_squish;
    وگرنه اگر (strmatch(next, "gauss" )) d->type = e_gauss;
    وگرنه اگر (strmatch(next, "mod"   )) d->type = e_mod;
    وگرنه اگر (strmatch(next, "max"   )) d->type = e_max;
    وگرنه اگر (strmatch(next, "min"   )) d->type = e_min;
    وگرنه اگر (strmatch(next, "eq"    )) d->type = e_eq;
    وگرنه اگر (strmatch(next, "gte"   )) d->type = e_gte;
    وگرنه اگر (strmatch(next, "gt"    )) d->type = e_gt;
    وگرنه اگر (strmatch(next, "lte"   )) d->type = e_lte;
    وگرنه اگر (strmatch(next, "lt"    )) d->type = e_lt;
    وگرنه اگر (strmatch(next, "ld"    )) d->type = e_ld;
    وگرنه اگر (strmatch(next, "isnan" )) d->type = e_isnan;
    وگرنه اگر (strmatch(next, "isinf" )) d->type = e_isinf;
    وگرنه اگر (strmatch(next, "st"    )) d->type = e_st;
    وگرنه اگر (strmatch(next, "while" )) d->type = e_while;
    وگرنه اگر (strmatch(next, "taylor")) d->type = e_taylor;
    وگرنه اگر (strmatch(next, "root"  )) d->type = e_ریشه;
    وگرنه اگر (strmatch(next, "floor" )) d->type = e_floor;
    وگرنه اگر (strmatch(next, "ceil"  )) d->type = e_ceil;
    وگرنه اگر (strmatch(next, "trunc" )) d->type = e_trunc;
    وگرنه اگر (strmatch(next, "round" )) d->type = e_round;
    وگرنه اگر (strmatch(next, "sqrt"  )) d->type = e_sqrt;
    وگرنه اگر (strmatch(next, "not"   )) d->type = e_not;
    وگرنه اگر (strmatch(next, "pow"   )) d->type = e_pow;
    وگرنه اگر (strmatch(next, "print" )) d->type = e_print;
    وگرنه اگر (strmatch(next, "random")) d->type = e_random;
    وگرنه اگر (strmatch(next, "randomi")) d->type = e_randomi;
    وگرنه اگر (strmatch(next, "hypot" )) d->type = e_hypot;
    وگرنه اگر (strmatch(next, "gcd"   )) d->type = e_gcd;
    وگرنه اگر (strmatch(next, "if"    )) d->type = e_if;
    وگرنه اگر (strmatch(next, "ifnot" )) d->type = e_ifnot;
    وگرنه اگر (strmatch(next, "bitand")) d->type = e_bitand;
    وگرنه اگر (strmatch(next, "bitor" )) d->type = e_bitor;
    وگرنه اگر (strmatch(next, "between"))d->type = e_between;
    وگرنه اگر (strmatch(next, "clip"  )) d->type = e_clip;
    وگرنه اگر (strmatch(next, "atan2" )) d->type = e_atan2;
    وگرنه اگر (strmatch(next, "lerp"  )) d->type = e_lerp;
    وگرنه اگر (strmatch(next, "sgn"   )) d->type = e_sgn;
    وگرنه {
        برای (i=0; p->func1_names && p->func1_names[i]; i++) {
            اگر (strmatch(next, p->func1_names[i])) {
                d->func1 = p->funcs1[i];
                d->type = e_func1;
                d->const_index = i;
                *e = d;
                بازگشت 0;
            }
        }

        برای (i=0; p->func2_names && p->func2_names[i]; i++) {
            اگر (strmatch(next, p->func2_names[i])) {
                d->func2 = p->funcs2[i];
                d->type = e_func2;
                d->const_index = i;
                *e = d;
                بازگشت 0;
            }
        }

        av_log(p, AV_LOG_ERROR, "Unknown function in '%s'\n", s0);
        av_عبارت_free(d);
        بازگشت AVERROR(EINVAL);
    }

    *e = d;
    بازگشت 0;
}

ایستا AVExpr *make_eval_عبارت(صحیح type, صحیح مقدار, AVExpr *p0, AVExpr *p1)
{
    صحیح depth = FFMAX(p0->depth, p1->depth) + 1;
    اگر (depth > MAX_DEPTH)
        بازگشت پوچ;
    AVExpr *e = av_mallocz(اندازه(AVExpr));
    اگر (!e)
        بازگشت پوچ;
    e->type     =type   ;
    e->مقدار    =مقدار  ;
    e->param[0] =p0     ;
    e->param[1] =p1     ;
    e->depth    = depth;
    بازگشت e;
}

ایستا صحیح parse_pow(AVExpr **e, Parser *p, صحیح *sign)
{
    *sign= (*p->s == '+') - (*p->s == '-');
    p->s += *sign&1;
    بازگشت parse_primary(e, p);
}

ایستا صحیح parse_dB(AVExpr **e, Parser *p, صحیح *sign)
{
    /* do not filter out the negative sign when parsing a dB value.
       for example, -3dB is not the same as -(3dB) */
    اگر (*p->s == '-') {
        نویسه *next;
        av_unused دوگانه ignored = strtod(p->s, &next);
        اگر (next != p->s && next[0] == 'd' && next[1] == 'B') {
            *sign = 0;
            بازگشت parse_primary(e, p);
        }
    }
    بازگشت parse_pow(e, p, sign);
}

ایستا صحیح parse_factor(AVExpr **e, Parser *p)
{
    صحیح sign, sign2, ret;
    AVExpr *e0, *e1, *e2;
    اگر ((ret = parse_dB(&e0, p, &sign)) < 0)
        بازگشت ret;
    وقتی(p->s[0]=='^'){
        e1 = e0;
        p->s++;
        اگر ((ret = parse_dB(&e2, p, &sign2)) < 0) {
            av_عبارت_free(e1);
            بازگشت ret;
        }
        e0 = make_eval_عبارت(e_pow, 1, e1, e2);
        اگر (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            بازگشت AVERROR(ENOMEM);
        }
        اگر (e0->param[1]) e0->param[1]->مقدار *= (sign2|1);
    }
    اگر (e0) e0->مقدار *= (sign|1);

    *e = e0;
    بازگشت 0;
}

ایستا صحیح parse_term(AVExpr **e, Parser *p)
{
    صحیح ret;
    AVExpr *e0, *e1, *e2;
    اگر ((ret = parse_factor(&e0, p)) < 0)
        بازگشت ret;
    وقتی (p->s[0]=='*' || p->s[0]=='/') {
        صحیح c= *p->s++;
        e1 = e0;
        اگر ((ret = parse_factor(&e2, p)) < 0) {
            av_عبارت_free(e1);
            بازگشت ret;
        }
        e0 = make_eval_عبارت(c == '*' ? e_mul : e_div, 1, e1, e2);
        اگر (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            بازگشت AVERROR(ENOMEM);
        }
    }
    *e = e0;
    بازگشت 0;
}

ایستا صحیح parse_subexpr(AVExpr **e, Parser *p)
{
    صحیح ret;
    AVExpr *e0, *e1, *e2;
    اگر ((ret = parse_term(&e0, p)) < 0)
        بازگشت ret;
    وقتی (*p->s == '+' || *p->s == '-') {
        e1 = e0;
        اگر ((ret = parse_term(&e2, p)) < 0) {
            av_عبارت_free(e1);
            بازگشت ret;
        }
        e0 = make_eval_عبارت(e_add, 1, e1, e2);
        اگر (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            بازگشت AVERROR(ENOMEM);
        }
    };

    *e = e0;
    بازگشت 0;
}

ایستا صحیح parse_عبارت(AVExpr **e, Parser *p)
{
    صحیح ret;
    AVExpr *e0, *e1, *e2;
    اگر (p->پشته_index <= 0) //protect against stack overflows
        بازگشت AVERROR(EINVAL);
    p->پشته_index--;

    اگر ((ret = parse_subexpr(&e0, p)) < 0)
        بازگشت ret;
    وقتی (*p->s == ';') {
        p->s++;
        e1 = e0;
        اگر ((ret = parse_subexpr(&e2, p)) < 0) {
            av_عبارت_free(e1);
            بازگشت ret;
        }
        e0 = make_eval_عبارت(e_last, 1, e1, e2);
        اگر (!e0) {
            av_عبارت_free(e1);
            av_عبارت_free(e2);
            بازگشت AVERROR(ENOMEM);
        }
    };

    p->پشته_index++;
    *e = e0;
    بازگشت 0;
}

ایستا صحیح verify_عبارت(AVExpr *e)
{
    اگر (!e) بازگشت 0;
    انتخاب (e->type) {
        حالت e_مقدار:
        حالت e_const: بازگشت 1;
        حالت e_func0:
        حالت e_func1:
        حالت e_squish:
        حالت e_ld:
        حالت e_gauss:
        حالت e_isnan:
        حالت e_isinf:
        حالت e_floor:
        حالت e_ceil:
        حالت e_trunc:
        حالت e_round:
        حالت e_sqrt:
        حالت e_not:
        حالت e_random:
        حالت e_sgn:
            بازگشت verify_عبارت(e->param[0]) && !e->param[1];
        حالت e_print:
            بازگشت verify_عبارت(e->param[0])
                   && (!e->param[1] || verify_عبارت(e->param[1]));
        حالت e_if:
        حالت e_ifnot:
        حالت e_taylor:
            بازگشت verify_عبارت(e->param[0]) && verify_عبارت(e->param[1])
                   && (!e->param[2] || verify_عبارت(e->param[2]));
        حالت e_between:
        حالت e_clip:
        حالت e_lerp:
        حالت e_randomi:
            بازگشت verify_عبارت(e->param[0]) &&
                   verify_عبارت(e->param[1]) &&
                   verify_عبارت(e->param[2]);
        پیشفرض: بازگشت verify_عبارت(e->param[0]) && verify_عبارت(e->param[1]) && !e->param[2];
    }
}

صحیح av_عبارت_parse(AVExpr **عبارت, ثابت نویسه *s,
                  ثابت نویسه * ثابت *const_names,
                  ثابت نویسه * ثابت *func1_names, دوگانه (* ثابت *funcs1)(تهی *, دوگانه),
                  ثابت نویسه * ثابت *func2_names, دوگانه (* ثابت *funcs2)(تهی *, دوگانه, دوگانه),
                  صحیح log_offset, تهی *log_ctx)
{
    Parser p = { 0 };
    AVExpr *e = پوچ;
    نویسه *w = av_malloc(strlen(s) + 1);
    نویسه *wp = w;
    ثابت نویسه *s0 = s;
    صحیح ret = 0;

    اگر (!w)
        بازگشت AVERROR(ENOMEM);

    وقتی (*s)
        اگر (!av_isspace(*s++)) *wp++ = s[-1];
    *wp++ = 0;

    p.class      = &eval_class;
    p.پشته_index=100;
    p.s= w;
    p.const_names = const_names;
    p.funcs1      = funcs1;
    p.func1_names = func1_names;
    p.funcs2      = funcs2;
    p.func2_names = func2_names;
    p.log_offset = log_offset;
    p.log_ctx    = log_ctx;

    اگر ((ret = parse_عبارت(&e, &p)) < 0)
        برو end;
    اگر (*p.s) {
        av_log(&p, AV_LOG_ERROR, "Invalid chars '%s' at the end of expression '%s'\n", p.s, s0);
        ret = AVERROR(EINVAL);
        برو end;
    }
    اگر (!verify_عبارت(e)) {
        ret = AVERROR(EINVAL);
        برو end;
    }
    AVExpr_ریشه *r = av_realloc(e, اندازه(*r));
    اگر (!r) {
        ret = AVERROR(ENOMEM);
        برو end;
    }
    e = (AVExpr*)r;
    e->ریشه = 1;
    r->var= av_mallocz(اندازه(دوگانه) *VARS);
    r->prng_state = av_mallocz(اندازه(*r->prng_state) *VARS);
    اگر (!r->var || !r->prng_state) {
        ret = AVERROR(ENOMEM);
        برو end;
    }
    *عبارت = e;
    e = پوچ;
end:
    av_عبارت_free(e);
    av_free(w);
    بازگشت ret;
}

ایستا صحیح عبارت_شمار(AVExpr *e, unsigned *counter, صحیح size, صحیح type)
{
    صحیح i;

    اگر (!e || !counter || !size)
        بازگشت AVERROR(EINVAL);

    برای (i = 0; e->type != type && i < 3 && e->param[i]; i++)
        عبارت_شمار(e->param[i], counter, size, type);

    اگر (e->type == type && e->const_index < size)
        counter[e->const_index]++;

    بازگشت 0;
}

صحیح av_عبارت_شمار_vars(AVExpr *e, unsigned *counter, صحیح size)
{
    بازگشت عبارت_شمار(e, counter, size, e_const);
}

صحیح av_عبارت_شمار_func(AVExpr *e, unsigned *counter, صحیح size, صحیح arg)
{
    بازگشت عبارت_شمار(e, counter, size, ((صحیح[]){e_const, e_func1, e_func2})[arg]);
}

دوگانه av_عبارت_eval(AVExpr *e, ثابت دوگانه *const_مقادیر, تهی *opaque)
{
    av_assert1(e->ریشه);
    AVExpr_ریشه *r = (AVExpr_ریشه *)e;
    Parser p = {
        .class        = &eval_class,
        .const_مقادیر = const_مقادیر,
        .opaque       = opaque,
        .var          = r->var,
        .prng_state   = r->prng_state,
    };

    بازگشت eval_عبارت(&p, e);
}

صحیح av_عبارت_parse_and_eval(دوگانه *d, ثابت نویسه *s,
                           ثابت نویسه * ثابت *const_names, ثابت دوگانه *const_مقادیر,
                           ثابت نویسه * ثابت *func1_names, دوگانه (* ثابت *funcs1)(تهی *, دوگانه),
                           ثابت نویسه * ثابت *func2_names, دوگانه (* ثابت *funcs2)(تهی *, دوگانه, دوگانه),
                           تهی *opaque, صحیح log_offset, تهی *log_ctx)
{
    AVExpr *e = پوچ;
    صحیح ret = av_عبارت_parse(&e, s, const_names, func1_names, funcs1, func2_names, funcs2, log_offset, log_ctx);

    اگر (ret < 0) {
        *d = NAN;
        بازگشت ret;
    }
    *d = av_عبارت_eval(e, const_مقادیر, opaque);
    av_عبارت_free(e);
    بازگشت isnan(*d) ? AVERROR(EINVAL) : 0;
}
