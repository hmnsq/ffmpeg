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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "common.h"

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "softfloat_tables.h"

#define MIN_EXP -149
#define MAX_EXP  126
#define ONE_BITS 29

প্রকারলেখ কাঠামো SoftFloat{
    int32_t mant;
    int32_t  exp;
}SoftFloat;

স্থির ধ্রুবক SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
স্থির ধ্রুবক SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
স্থির ধ্রুবক SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
স্থির ধ্রুবক SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
স্থির ধ্রুবক SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
স্থির ধ্রুবক SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
স্থির ধ্রুবক SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
স্থির ধ্রুবক SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
স্থির অন্তঃরেখ av_const দ্বিগুণ av_sf2double(SoftFloat v) {
    v.exp -= ONE_BITS +1;
    ফেরত ldexp(v.mant, v.exp);
}

স্থির av_const SoftFloat av_normalize_sf(SoftFloat a){
    যদি(a.mant){
#যদি 1
        যখন((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.exp  -= 1;
        }
#অন্যথা
        পূর্ণসংখ্যা s=ONE_BITS - av_log2(FFABS(a.mant));
        a.exp   -= s;
        a.mant <<= s;
#endif
        যদি(a.exp < MIN_EXP){
            a.exp = MIN_EXP;
            a.mant= 0;
        }
    }অন্যথা{
        a.exp= MIN_EXP;
    }
    ফেরত a;
}

স্থির অন্তঃরেখ av_const SoftFloat av_normalize1_sf(SoftFloat a){
#যদি 1
    যদি((int32_t)(a.mant + 0x40000000U) <= 0){
        a.exp++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.exp <= MAX_EXP);
    ফেরত a;
#নতুবা_যদি 1
    পূর্ণসংখ্যা t= a.mant + 0x40000000 < 0;
    ফেরত (SoftFloat){ a.mant>>t, a.exp+t};
#অন্যথা
    পূর্ণসংখ্যা t= (a.mant + 0x3FFFFFFFU)>>31;
    ফেরত (SoftFloat){a.mant>>t, a.exp+t};
#endif
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
স্থির অন্তঃরেখ av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.exp += b.exp;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_BITS) == (a.mant * (int64_t)b.mant) >> ONE_BITS);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_BITS;
    a = av_normalize1_sf((SoftFloat){a.mant, a.exp - 1});
    যদি (!a.mant || a.exp < MIN_EXP)
        ফেরত FLOAT_0;
    ফেরত a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
স্থির অন্তঃরেখ av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t অস্থায়ী = (int64_t)a.mant * (1<<(ONE_BITS+1));
    অস্থায়ী /= b.mant;
    a.exp -= b.exp;
    a.mant = অস্থায়ী;
    যখন (a.mant != অস্থায়ী) {
        অস্থায়ী /= 2;
        a.exp--;
        a.mant = অস্থায়ী;
    }
    a = av_normalize1_sf(a);
    যদি (!a.mant || a.exp < MIN_EXP)
        ফেরত FLOAT_0;
    ফেরত a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা av_cmp_sf(SoftFloat a, SoftFloat b){
    পূর্ণসংখ্যা t= a.exp - b.exp;
    যদি      (t <-31) ফেরত                  -  b.mant      ;
    অন্যথা যদি (t <  0) ফেরত (a.mant >> (-t)) -  b.mant      ;
    অন্যথা যদি (t < 32) ফেরত  a.mant          - (b.mant >> t);
    অন্যথা             ফেরত  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা av_gt_sf(SoftFloat a, SoftFloat b)
{
    পূর্ণসংখ্যা t= a.exp - b.exp;
    যদি      (t <-31) ফেরত 0                >  b.mant      ;
    অন্যথা যদি (t <  0) ফেরত (a.mant >> (-t)) >  b.mant      ;
    অন্যথা যদি (t < 32) ফেরত  a.mant          > (b.mant >> t);
    অন্যথা             ফেরত  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
স্থির অন্তঃরেখ av_const SoftFloat av_add_sf(SoftFloat a, SoftFloat b){
    পূর্ণসংখ্যা t= a.exp - b.exp;
    যদি      (t <-31) ফেরত b;
    অন্যথা যদি (t <  0) ফেরত av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.exp}));
    অন্যথা যদি (t < 32) ফেরত av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.exp}));
    অন্যথা             ফেরত a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
স্থির অন্তঃরেখ av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    ফেরত av_add_sf(a, (SoftFloat){ -b.mant, b.exp});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
স্থির অন্তঃরেখ av_const SoftFloat av_int2sf(পূর্ণসংখ্যা v, পূর্ণসংখ্যা frac_bits){
    পূর্ণসংখ্যা exp_offset = 0;
    যদি(v <= INT_MIN + 1){
        exp_offset = 1;
        v>>=1;
    }
    ফেরত av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_BITS + 1 - frac_bits + exp_offset}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা av_sf2int(SoftFloat v, পূর্ণসংখ্যা frac_bits){
    v.exp += frac_bits - (ONE_BITS + 1);
    যদি(v.exp >= 0) ফেরত v.mant <<  v.exp ;
    অন্যথা           ফেরত v.mant >>(-v.exp);
}

/**
 * Rounding-to-nearest used.
 */
স্থির av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    পূর্ণসংখ্যা tab_সূচক, rem;

    যদি (val.mant == 0)
        val.exp = MIN_EXP;
    অন্যথা যদি (val.mant < 0)
        abort();
    অন্যথা
    {
        tab_সূচক = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (পূর্ণসংখ্যা)(((int64_t)av_sqrttbl_sf[tab_সূচক] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_সূচক + 1] * rem +
                           0x80000) >> 20);
        val.mant = (পূর্ণসংখ্যা)(((int64_t)av_sqr_exp_multbl_sf[val.exp & 1] * val.mant +
                          0x10000000) >> 29);

        যদি (val.mant < 0x40000000)
            val.exp -= 2;
        অন্যথা
            val.mant >>= 1;

        val.exp = (val.exp >> 1) + 1;
    }

    ফেরত val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_unused স্থির শূন্য av_sincos_sf(পূর্ণসংখ্যা a, পূর্ণসংখ্যা *s, পূর্ণসংখ্যা *c)
{
    পূর্ণসংখ্যা idx, sign;
    পূর্ণসংখ্যা sv, cv;
    পূর্ণসংখ্যা st, ct;

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

    idx = (পূর্ণসংখ্যা)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (পূর্ণসংখ্যা)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (পূর্ণসংখ্যা)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (পূর্ণসংখ্যা)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (পূর্ণসংখ্যা)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (পূর্ণসংখ্যা)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (পূর্ণসংখ্যা)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (পূর্ণসংখ্যা)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#endif /* AVUTIL_SOFTFLOAT_H */
