/*
 * Copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

#ifndef AVUTIL_SOFTFLOAT_H
#define AVUTIL_SOFTFLOAT_H

#include <stdint.h>
#include "common.h"

#include "avassert.h"
#include "softfloat_tables.h"

#define MIN_EXP -149
#define MAX_EXP  126
#define ONE_BITS 29

typedef struct SoftFloat{
    int32_t mant;
    int32_t  exp;
}SoftFloat;

static const SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
static const SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
static const SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
static const SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
static const SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
static const SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
static const SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
static const SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
static inline av_const double av_sf2double(SoftFloat v) {
    v.exp -= ONE_BITS +1;
    върни ldexp(v.mant, v.exp);
}

static av_const SoftFloat av_normalize_sf(SoftFloat a){
    ако(a.mant){
#ако 1
        докато((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.exp  -= 1;
        }
#иначе
        цяло s=ONE_BITS - av_log2(FFABS(a.mant));
        a.exp   -= s;
        a.mant <<= s;
#endif
        ако(a.exp < MIN_EXP){
            a.exp = MIN_EXP;
            a.mant= 0;
        }
    }иначе{
        a.exp= MIN_EXP;
    }
    върни a;
}

static inline av_const SoftFloat av_normalize1_sf(SoftFloat a){
#ако 1
    ако((int32_t)(a.mant + 0x40000000U) <= 0){
        a.exp++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.exp <= MAX_EXP);
    върни a;
#elif 1
    цяло t= a.mant + 0x40000000 < 0;
    върни (SoftFloat){ a.mant>>t, a.exp+t};
#иначе
    цяло t= (a.mant + 0x3FFFFFFFU)>>31;
    върни (SoftFloat){a.mant>>t, a.exp+t};
#endif
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
static inline av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.exp += b.exp;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_BITS) == (a.mant * (int64_t)b.mant) >> ONE_BITS);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_BITS;
    a = av_normalize1_sf((SoftFloat){a.mant, a.exp - 1});
    ако (!a.mant || a.exp < MIN_EXP)
        върни FLOAT_0;
    върни a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
static inline av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t temp = (int64_t)a.mant * (1<<(ONE_BITS+1));
    temp /= b.mant;
    a.exp -= b.exp;
    a.mant = temp;
    докато (a.mant != temp) {
        temp /= 2;
        a.exp--;
        a.mant = temp;
    }
    a = av_normalize1_sf(a);
    ако (!a.mant || a.exp < MIN_EXP)
        върни FLOAT_0;
    върни a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
static inline av_const цяло av_cmp_sf(SoftFloat a, SoftFloat b){
    цяло t= a.exp - b.exp;
    ако      (t <-31) върни                  -  b.mant      ;
    иначе ако (t <  0) върни (a.mant >> (-t)) -  b.mant      ;
    иначе ако (t < 32) върни  a.mant          - (b.mant >> t);
    иначе             върни  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
static inline av_const цяло av_gt_sf(SoftFloat a, SoftFloat b)
{
    цяло t= a.exp - b.exp;
    ако      (t <-31) върни 0                >  b.mant      ;
    иначе ако (t <  0) върни (a.mant >> (-t)) >  b.mant      ;
    иначе ако (t < 32) върни  a.mant          > (b.mant >> t);
    иначе             върни  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
static inline av_const SoftFloat av_add_sf(SoftFloat a, SoftFloat b){
    цяло t= a.exp - b.exp;
    ако      (t <-31) върни b;
    иначе ако (t <  0) върни av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.exp}));
    иначе ако (t < 32) върни av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.exp}));
    иначе             върни a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
static inline av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    върни av_add_sf(a, (SoftFloat){ -b.mant, b.exp});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
static inline av_const SoftFloat av_int2sf(цяло v, цяло frac_bits){
    цяло exp_offset = 0;
    ако(v <= INT_MIN + 1){
        exp_offset = 1;
        v>>=1;
    }
    върни av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_BITS + 1 - frac_bits + exp_offset}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
static inline av_const цяло av_sf2int(SoftFloat v, цяло frac_bits){
    v.exp += frac_bits - (ONE_BITS + 1);
    ако(v.exp >= 0) върни v.mant <<  v.exp ;
    иначе           върни v.mant >>(-v.exp);
}

/**
 * Rounding-to-nearest used.
 */
static av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    цяло tabIndex, rem;

    ако (val.mant == 0)
        val.exp = MIN_EXP;
    иначе ако (val.mant < 0)
        abort();
    иначе
    {
        tabIndex = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (цяло)(((int64_t)av_sqrttbl_sf[tabIndex] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tabIndex + 1] * rem +
                           0x80000) >> 20);
        val.mant = (цяло)(((int64_t)av_sqr_exp_multbl_sf[val.exp & 1] * val.mant +
                          0x10000000) >> 29);

        ако (val.mant < 0x40000000)
            val.exp -= 2;
        иначе
            val.mant >>= 1;

        val.exp = (val.exp >> 1) + 1;
    }

    върни val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_unused static void av_sincos_sf(цяло a, цяло *s, цяло *c)
{
    цяло idx, sign;
    цяло sv, cv;
    цяло st, ct;

    idx = a >> 26;
    sign = (int32_t)((unsigned)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((unsigned)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (цяло)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (цяло)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (цяло)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (цяло)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (цяло)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (цяло)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (цяло)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (цяло)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#endif /* AVUTIL_SOFTFLOAT_H */
