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

#ضمن <stdint.h>
#ضمن "common.h"

#ضمن "avassert.h"
#ضمن "softfloat_tables.h"

#define MIN_EXP -149
#define MAX_EXP  126
#define ONE_BITS 29

تعريفنوع بنية SoftFloat{
    int32_t mant;
    int32_t  exp;
}SoftFloat;

ساكن ثابت SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
ساكن ثابت SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
ساكن ثابت SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
ساكن ثابت SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
ساكن ثابت SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
ساكن ثابت SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
ساكن ثابت SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
ساكن ثابت SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
ساكن مضمن av_const مزدوج av_sf2double(SoftFloat v) {
    v.exp -= ONE_BITS +1;
    أرجع ldexp(v.mant, v.exp);
}

ساكن av_const SoftFloat av_normalize_sf(SoftFloat a){
    𐤀𐤌(a.mant){
#𐤀𐤌 1
        طالما((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.exp  -= 1;
        }
#وإلا
        صحيح s=ONE_BITS - av_log2(FFABS(a.mant));
        a.exp   -= s;
        a.mant <<= s;
#endif
        𐤀𐤌(a.exp < MIN_EXP){
            a.exp = MIN_EXP;
            a.mant= 0;
        }
    }وإلا{
        a.exp= MIN_EXP;
    }
    أرجع a;
}

ساكن مضمن av_const SoftFloat av_normalize1_sf(SoftFloat a){
#𐤀𐤌 1
    𐤀𐤌((int32_t)(a.mant + 0x40000000U) <= 0){
        a.exp++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.exp <= MAX_EXP);
    أرجع a;
#وإلاإذا 1
    صحيح t= a.mant + 0x40000000 < 0;
    أرجع (SoftFloat){ a.mant>>t, a.exp+t};
#وإلا
    صحيح t= (a.mant + 0x3FFFFFFFU)>>31;
    أرجع (SoftFloat){a.mant>>t, a.exp+t};
#endif
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
ساكن مضمن av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.exp += b.exp;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_BITS) == (a.mant * (int64_t)b.mant) >> ONE_BITS);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_BITS;
    a = av_normalize1_sf((SoftFloat){a.mant, a.exp - 1});
    𐤀𐤌 (!a.mant || a.exp < MIN_EXP)
        أرجع FLOAT_0;
    أرجع a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
ساكن مضمن av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t temp = (int64_t)a.mant * (1<<(ONE_BITS+1));
    temp /= b.mant;
    a.exp -= b.exp;
    a.mant = temp;
    طالما (a.mant != temp) {
        temp /= 2;
        a.exp--;
        a.mant = temp;
    }
    a = av_normalize1_sf(a);
    𐤀𐤌 (!a.mant || a.exp < MIN_EXP)
        أرجع FLOAT_0;
    أرجع a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
ساكن مضمن av_const صحيح av_cmp_sf(SoftFloat a, SoftFloat b){
    صحيح t= a.exp - b.exp;
    𐤀𐤌      (t <-31) أرجع                  -  b.mant      ;
    وإلا 𐤀𐤌 (t <  0) أرجع (a.mant >> (-t)) -  b.mant      ;
    وإلا 𐤀𐤌 (t < 32) أرجع  a.mant          - (b.mant >> t);
    وإلا             أرجع  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
ساكن مضمن av_const صحيح av_gt_sf(SoftFloat a, SoftFloat b)
{
    صحيح t= a.exp - b.exp;
    𐤀𐤌      (t <-31) أرجع 0                >  b.mant      ;
    وإلا 𐤀𐤌 (t <  0) أرجع (a.mant >> (-t)) >  b.mant      ;
    وإلا 𐤀𐤌 (t < 32) أرجع  a.mant          > (b.mant >> t);
    وإلا             أرجع  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
ساكن مضمن av_const SoftFloat av_add_sf(SoftFloat a, SoftFloat b){
    صحيح t= a.exp - b.exp;
    𐤀𐤌      (t <-31) أرجع b;
    وإلا 𐤀𐤌 (t <  0) أرجع av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.exp}));
    وإلا 𐤀𐤌 (t < 32) أرجع av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.exp}));
    وإلا             أرجع a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
ساكن مضمن av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    أرجع av_add_sf(a, (SoftFloat){ -b.mant, b.exp});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
ساكن مضمن av_const SoftFloat av_int2sf(صحيح v, صحيح frac_bits){
    صحيح exp_offset = 0;
    𐤀𐤌(v <= INT_MIN + 1){
        exp_offset = 1;
        v>>=1;
    }
    أرجع av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_BITS + 1 - frac_bits + exp_offset}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
ساكن مضمن av_const صحيح av_sf2int(SoftFloat v, صحيح frac_bits){
    v.exp += frac_bits - (ONE_BITS + 1);
    𐤀𐤌(v.exp >= 0) أرجع v.mant <<  v.exp ;
    وإلا           أرجع v.mant >>(-v.exp);
}

/**
 * Rounding-to-nearest used.
 */
ساكن av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    صحيح tabIndex, rem;

    𐤀𐤌 (val.mant == 0)
        val.exp = MIN_EXP;
    وإلا 𐤀𐤌 (val.mant < 0)
        abort();
    وإلا
    {
        tabIndex = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (صحيح)(((int64_t)av_sqrttbl_sf[tabIndex] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tabIndex + 1] * rem +
                           0x80000) >> 20);
        val.mant = (صحيح)(((int64_t)av_sqr_exp_multbl_sf[val.exp & 1] * val.mant +
                          0x10000000) >> 29);

        𐤀𐤌 (val.mant < 0x40000000)
            val.exp -= 2;
        وإلا
            val.mant >>= 1;

        val.exp = (val.exp >> 1) + 1;
    }

    أرجع val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_unused ساكن فراغ av_sincos_sf(صحيح a, صحيح *s, صحيح *c)
{
    صحيح idx, sign;
    صحيح sv, cv;
    صحيح st, ct;

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

    idx = (صحيح)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (صحيح)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (صحيح)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (صحيح)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (صحيح)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (صحيح)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (صحيح)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (صحيح)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#endif /* AVUTIL_SOFTFLOAT_H */
