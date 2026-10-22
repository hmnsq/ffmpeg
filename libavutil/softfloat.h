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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_SOFTFLOAT_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_SOFTFLOAT_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "common.h"

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "softfloat_tables.h"

#ವ್ಯಾಖ್ಯಾನಿಸು MIN_EXP -149
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_EXP  126
#ವ್ಯಾಖ್ಯಾನಿಸು ONE_ಬಿಟ್ಟುಗಳು 29

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SoftFloat{
    int32_t mant;
    int32_t  ಘಾತಾಂಕ;
}SoftFloat;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ದ್ವಿಗುಣ av_sf2double(SoftFloat v) {
    v.ಘಾತಾಂಕ -= ONE_ಬಿಟ್ಟುಗಳು +1;
    ಹಿಂತಿರುಗಿ ldexp(v.mant, v.ಘಾತಾಂಕ);
}

ಸ್ಥಿರ av_const SoftFloat av_normalize_sf(SoftFloat a){
    ಆದರೆ(a.mant){
#ಆದರೆ 1
        ಆಗ((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.ಘಾತಾಂಕ  -= 1;
        }
#ಇಲ್ಲದಿದ್ದರೆ
        ಪೂರ್ಣಾಂಕ s=ONE_ಬಿಟ್ಟುಗಳು - av_log2(FFABS(a.mant));
        a.ಘಾತಾಂಕ   -= s;
        a.mant <<= s;
#ಆದರೆ_ಅಂತ್ಯ
        ಆದರೆ(a.ಘಾತಾಂಕ < MIN_EXP){
            a.ಘಾತಾಂಕ = MIN_EXP;
            a.mant= 0;
        }
    }ಇಲ್ಲದಿದ್ದರೆ{
        a.ಘಾತಾಂಕ= MIN_EXP;
    }
    ಹಿಂತಿರುಗಿ a;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const SoftFloat av_normalize1_sf(SoftFloat a){
#ಆದರೆ 1
    ಆದರೆ((int32_t)(a.mant + 0x40000000U) <= 0){
        a.ಘಾತಾಂಕ++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.ಘಾತಾಂಕ <= MAX_EXP);
    ಹಿಂತಿರುಗಿ a;
#ಅಥವಾಆದರೆ 1
    ಪೂರ್ಣಾಂಕ t= a.mant + 0x40000000 < 0;
    ಹಿಂತಿರುಗಿ (SoftFloat){ a.mant>>t, a.ಘಾತಾಂಕ+t};
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ t= (a.mant + 0x3FFFFFFFU)>>31;
    ಹಿಂತಿರುಗಿ (SoftFloat){a.mant>>t, a.ಘಾತಾಂಕ+t};
#ಆದರೆ_ಅಂತ್ಯ
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.ಘಾತಾಂಕ += b.ಘಾತಾಂಕ;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_ಬಿಟ್ಟುಗಳು) == (a.mant * (int64_t)b.mant) >> ONE_ಬಿಟ್ಟುಗಳು);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_ಬಿಟ್ಟುಗಳು;
    a = av_normalize1_sf((SoftFloat){a.mant, a.ಘಾತಾಂಕ - 1});
    ಆದರೆ (!a.mant || a.ಘಾತಾಂಕ < MIN_EXP)
        ಹಿಂತಿರುಗಿ FLOAT_0;
    ಹಿಂತಿರುಗಿ a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t ತಾತ್ಕಾಲಿಕ = (int64_t)a.mant * (1<<(ONE_ಬಿಟ್ಟುಗಳು+1));
    ತಾತ್ಕಾಲಿಕ /= b.mant;
    a.ಘಾತಾಂಕ -= b.ಘಾತಾಂಕ;
    a.mant = ತಾತ್ಕಾಲಿಕ;
    ಆಗ (a.mant != ತಾತ್ಕಾಲಿಕ) {
        ತಾತ್ಕಾಲಿಕ /= 2;
        a.ಘಾತಾಂಕ--;
        a.mant = ತಾತ್ಕಾಲಿಕ;
    }
    a = av_normalize1_sf(a);
    ಆದರೆ (!a.mant || a.ಘಾತಾಂಕ < MIN_EXP)
        ಹಿಂತಿರುಗಿ FLOAT_0;
    ಹಿಂತಿರುಗಿ a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ av_cmp_sf(SoftFloat a, SoftFloat b){
    ಪೂರ್ಣಾಂಕ t= a.ಘಾತಾಂಕ - b.ಘಾತಾಂಕ;
    ಆದರೆ      (t <-31) ಹಿಂತಿರುಗಿ                  -  b.mant      ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t <  0) ಹಿಂತಿರುಗಿ (a.mant >> (-t)) -  b.mant      ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t < 32) ಹಿಂತಿರುಗಿ  a.mant          - (b.mant >> t);
    ಇಲ್ಲದಿದ್ದರೆ             ಹಿಂತಿರುಗಿ  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ av_gt_sf(SoftFloat a, SoftFloat b)
{
    ಪೂರ್ಣಾಂಕ t= a.ಘಾತಾಂಕ - b.ಘಾತಾಂಕ;
    ಆದರೆ      (t <-31) ಹಿಂತಿರುಗಿ 0                >  b.mant      ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t <  0) ಹಿಂತಿರುಗಿ (a.mant >> (-t)) >  b.mant      ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t < 32) ಹಿಂತಿರುಗಿ  a.mant          > (b.mant >> t);
    ಇಲ್ಲದಿದ್ದರೆ             ಹಿಂತಿರುಗಿ  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const SoftFloat av_ಕೂಡಿಸು_sf(SoftFloat a, SoftFloat b){
    ಪೂರ್ಣಾಂಕ t= a.ಘಾತಾಂಕ - b.ಘಾತಾಂಕ;
    ಆದರೆ      (t <-31) ಹಿಂತಿರುಗಿ b;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t <  0) ಹಿಂತಿರುಗಿ av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.ಘಾತಾಂಕ}));
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (t < 32) ಹಿಂತಿರುಗಿ av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.ಘಾತಾಂಕ}));
    ಇಲ್ಲದಿದ್ದರೆ             ಹಿಂತಿರುಗಿ a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    ಹಿಂತಿರುಗಿ av_ಕೂಡಿಸು_sf(a, (SoftFloat){ -b.mant, b.ಘಾತಾಂಕ});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const SoftFloat av_int2sf(ಪೂರ್ಣಾಂಕ v, ಪೂರ್ಣಾಂಕ frac_ಬಿಟ್ಟುಗಳು){
    ಪೂರ್ಣಾಂಕ exp_ಸ್ಥಾನಾಂತರ = 0;
    ಆದರೆ(v <= INT_MIN + 1){
        exp_ಸ್ಥಾನಾಂತರ = 1;
        v>>=1;
    }
    ಹಿಂತಿರುಗಿ av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_ಬಿಟ್ಟುಗಳು + 1 - frac_ಬಿಟ್ಟುಗಳು + exp_ಸ್ಥಾನಾಂತರ}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ av_sf2int(SoftFloat v, ಪೂರ್ಣಾಂಕ frac_ಬಿಟ್ಟುಗಳು){
    v.ಘಾತಾಂಕ += frac_ಬಿಟ್ಟುಗಳು - (ONE_ಬಿಟ್ಟುಗಳು + 1);
    ಆದರೆ(v.ಘಾತಾಂಕ >= 0) ಹಿಂತಿರುಗಿ v.mant <<  v.ಘಾತಾಂಕ ;
    ಇಲ್ಲದಿದ್ದರೆ           ಹಿಂತಿರುಗಿ v.mant >>(-v.ಘಾತಾಂಕ);
}

/**
 * Rounding-to-nearest used.
 */
ಸ್ಥಿರ av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    ಪೂರ್ಣಾಂಕ tab_ಸೂಚ್ಯಂಕ, rem;

    ಆದರೆ (val.mant == 0)
        val.ಘಾತಾಂಕ = MIN_EXP;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (val.mant < 0)
        abort();
    ಇಲ್ಲದಿದ್ದರೆ
    {
        tab_ಸೂಚ್ಯಂಕ = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (ಪೂರ್ಣಾಂಕ)(((int64_t)av_sqrttbl_sf[tab_ಸೂಚ್ಯಂಕ] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_ಸೂಚ್ಯಂಕ + 1] * rem +
                           0x80000) >> 20);
        val.mant = (ಪೂರ್ಣಾಂಕ)(((int64_t)av_sqr_exp_multbl_sf[val.ಘಾತಾಂಕ & 1] * val.mant +
                          0x10000000) >> 29);

        ಆದರೆ (val.mant < 0x40000000)
            val.ಘಾತಾಂಕ -= 2;
        ಇಲ್ಲದಿದ್ದರೆ
            val.mant >>= 1;

        val.ಘಾತಾಂಕ = (val.ಘಾತಾಂಕ >> 1) + 1;
    }

    ಹಿಂತಿರುಗಿ val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_ಬಳಸದ ಸ್ಥಿರ ಶೂನ್ಯ av_sincos_sf(ಪೂರ್ಣಾಂಕ a, ಪೂರ್ಣಾಂಕ *s, ಪೂರ್ಣಾಂಕ *c)
{
    ಪೂರ್ಣಾಂಕ idx, sign;
    ಪೂರ್ಣಾಂಕ sv, cv;
    ಪೂರ್ಣಾಂಕ st, ct;

    idx = a >> 26;
    sign = (int32_t)((ಚಿಹ್ನೆರಹಿತ)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((ಚಿಹ್ನೆರಹಿತ)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (ಪೂರ್ಣಾಂಕ)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (ಪೂರ್ಣಾಂಕ)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (ಪೂರ್ಣಾಂಕ)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (ಪೂರ್ಣಾಂಕ)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (ಪೂರ್ಣಾಂಕ)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (ಪೂರ್ಣಾಂಕ)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (ಪೂರ್ಣಾಂಕ)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (ಪೂರ್ಣಾಂಕ)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_SOFTFLOAT_H */
