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

#నిర్వచితం_కాకపోతే AVUTIL_SOFTFLOAT_H
#నిర్వచించు AVUTIL_SOFTFLOAT_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "common.h"

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "softfloat_tables.h"

#నిర్వచించు MIN_EXP -149
#నిర్వచించు MAX_EXP  126
#నిర్వచించు ONE_బిట్లు 29

రకనిర్వచనం నిర్మాణం SoftFloat{
    int32_t mant;
    int32_t  ఘాతాంకం;
}SoftFloat;

స్థిర స్థిరరాశి SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
స్థిర స్థిరరాశి SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
స్థిర స్థిరరాశి SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
స్థిర స్థిరరాశి SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
స్థిర స్థిరరాశి SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
స్థిర స్థిరరాశి SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
స్థిర స్థిరరాశి SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
స్థిర స్థిరరాశి SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
స్థిర అంతఃవరుస av_const ద్విగుణ av_sf2double(SoftFloat v) {
    v.ఘాతాంకం -= ONE_బిట్లు +1;
    తిరిగి ldexp(v.mant, v.ఘాతాంకం);
}

స్థిర av_const SoftFloat av_normalize_sf(SoftFloat a){
    ఒకవేళ(a.mant){
#ఒకవేళ 1
        అయితే((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.ఘాతాంకం  -= 1;
        }
#లేకపోతే
        పూర్ణాంకం s=ONE_బిట్లు - av_log2(FFABS(a.mant));
        a.ఘాతాంకం   -= s;
        a.mant <<= s;
#అయితే_ముగింపు
        ఒకవేళ(a.ఘాతాంకం < MIN_EXP){
            a.ఘాతాంకం = MIN_EXP;
            a.mant= 0;
        }
    }లేకపోతే{
        a.ఘాతాంకం= MIN_EXP;
    }
    తిరిగి a;
}

స్థిర అంతఃవరుస av_const SoftFloat av_normalize1_sf(SoftFloat a){
#ఒకవేళ 1
    ఒకవేళ((int32_t)(a.mant + 0x40000000U) <= 0){
        a.ఘాతాంకం++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.ఘాతాంకం <= MAX_EXP);
    తిరిగి a;
#లేదావేళ 1
    పూర్ణాంకం t= a.mant + 0x40000000 < 0;
    తిరిగి (SoftFloat){ a.mant>>t, a.ఘాతాంకం+t};
#లేకపోతే
    పూర్ణాంకం t= (a.mant + 0x3FFFFFFFU)>>31;
    తిరిగి (SoftFloat){a.mant>>t, a.ఘాతాంకం+t};
#అయితే_ముగింపు
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
స్థిర అంతఃవరుస av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.ఘాతాంకం += b.ఘాతాంకం;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_బిట్లు) == (a.mant * (int64_t)b.mant) >> ONE_బిట్లు);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_బిట్లు;
    a = av_normalize1_sf((SoftFloat){a.mant, a.ఘాతాంకం - 1});
    ఒకవేళ (!a.mant || a.ఘాతాంకం < MIN_EXP)
        తిరిగి FLOAT_0;
    తిరిగి a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
స్థిర అంతఃవరుస av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t తాత్కాలిక = (int64_t)a.mant * (1<<(ONE_బిట్లు+1));
    తాత్కాలిక /= b.mant;
    a.ఘాతాంకం -= b.ఘాతాంకం;
    a.mant = తాత్కాలిక;
    అయితే (a.mant != తాత్కాలిక) {
        తాత్కాలిక /= 2;
        a.ఘాతాంకం--;
        a.mant = తాత్కాలిక;
    }
    a = av_normalize1_sf(a);
    ఒకవేళ (!a.mant || a.ఘాతాంకం < MIN_EXP)
        తిరిగి FLOAT_0;
    తిరిగి a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
స్థిర అంతఃవరుస av_const పూర్ణాంకం av_cmp_sf(SoftFloat a, SoftFloat b){
    పూర్ణాంకం t= a.ఘాతాంకం - b.ఘాతాంకం;
    ఒకవేళ      (t <-31) తిరిగి                  -  b.mant      ;
    లేకపోతే ఒకవేళ (t <  0) తిరిగి (a.mant >> (-t)) -  b.mant      ;
    లేకపోతే ఒకవేళ (t < 32) తిరిగి  a.mant          - (b.mant >> t);
    లేకపోతే             తిరిగి  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
స్థిర అంతఃవరుస av_const పూర్ణాంకం av_gt_sf(SoftFloat a, SoftFloat b)
{
    పూర్ణాంకం t= a.ఘాతాంకం - b.ఘాతాంకం;
    ఒకవేళ      (t <-31) తిరిగి 0                >  b.mant      ;
    లేకపోతే ఒకవేళ (t <  0) తిరిగి (a.mant >> (-t)) >  b.mant      ;
    లేకపోతే ఒకవేళ (t < 32) తిరిగి  a.mant          > (b.mant >> t);
    లేకపోతే             తిరిగి  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
స్థిర అంతఃవరుస av_const SoftFloat av_కూడు_sf(SoftFloat a, SoftFloat b){
    పూర్ణాంకం t= a.ఘాతాంకం - b.ఘాతాంకం;
    ఒకవేళ      (t <-31) తిరిగి b;
    లేకపోతే ఒకవేళ (t <  0) తిరిగి av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.ఘాతాంకం}));
    లేకపోతే ఒకవేళ (t < 32) తిరిగి av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.ఘాతాంకం}));
    లేకపోతే             తిరిగి a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
స్థిర అంతఃవరుస av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    తిరిగి av_కూడు_sf(a, (SoftFloat){ -b.mant, b.ఘాతాంకం});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
స్థిర అంతఃవరుస av_const SoftFloat av_int2sf(పూర్ణాంకం v, పూర్ణాంకం frac_బిట్లు){
    పూర్ణాంకం exp_స్థానభ్రంశం = 0;
    ఒకవేళ(v <= INT_MIN + 1){
        exp_స్థానభ్రంశం = 1;
        v>>=1;
    }
    తిరిగి av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_బిట్లు + 1 - frac_బిట్లు + exp_స్థానభ్రంశం}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
స్థిర అంతఃవరుస av_const పూర్ణాంకం av_sf2int(SoftFloat v, పూర్ణాంకం frac_బిట్లు){
    v.ఘాతాంకం += frac_బిట్లు - (ONE_బిట్లు + 1);
    ఒకవేళ(v.ఘాతాంకం >= 0) తిరిగి v.mant <<  v.ఘాతాంకం ;
    లేకపోతే           తిరిగి v.mant >>(-v.ఘాతాంకం);
}

/**
 * Rounding-to-nearest used.
 */
స్థిర av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    పూర్ణాంకం tab_సూచీ, rem;

    ఒకవేళ (val.mant == 0)
        val.ఘాతాంకం = MIN_EXP;
    లేకపోతే ఒకవేళ (val.mant < 0)
        abort();
    లేకపోతే
    {
        tab_సూచీ = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (పూర్ణాంకం)(((int64_t)av_sqrttbl_sf[tab_సూచీ] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_సూచీ + 1] * rem +
                           0x80000) >> 20);
        val.mant = (పూర్ణాంకం)(((int64_t)av_sqr_exp_multbl_sf[val.ఘాతాంకం & 1] * val.mant +
                          0x10000000) >> 29);

        ఒకవేళ (val.mant < 0x40000000)
            val.ఘాతాంకం -= 2;
        లేకపోతే
            val.mant >>= 1;

        val.ఘాతాంకం = (val.ఘాతాంకం >> 1) + 1;
    }

    తిరిగి val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_వాడని స్థిర శూన్య av_sincos_sf(పూర్ణాంకం a, పూర్ణాంకం *s, పూర్ణాంకం *c)
{
    పూర్ణాంకం idx, sign;
    పూర్ణాంకం sv, cv;
    పూర్ణాంకం st, ct;

    idx = a >> 26;
    sign = (int32_t)((గుర్తులేని)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((గుర్తులేని)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (పూర్ణాంకం)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (పూర్ణాంకం)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (పూర్ణాంకం)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (పూర్ణాంకం)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (పూర్ణాంకం)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (పూర్ణాంకం)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (పూర్ణాంకం)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (పూర్ణాంకం)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#అయితే_ముగింపు /* AVUTIL_SOFTFLOAT_H */
