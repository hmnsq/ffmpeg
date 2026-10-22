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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_SOFTFLOAT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_SOFTFLOAT_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "softfloat_tables.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_EXP -149
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_EXP  126
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ONE_ਬਿੱਟ 29

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SoftFloat{
    int32_t mant;
    int32_t  ਘਾਤਾਂਕ;
}SoftFloat;

ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
ਸਥਿਰ ਅਚਲ SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਦੁੱਗਣਾ av_sf2double(SoftFloat v) {
    v.ਘਾਤਾਂਕ -= ONE_ਬਿੱਟ +1;
    ਵਾਪਸ ldexp(v.mant, v.ਘਾਤਾਂਕ);
}

ਸਥਿਰ av_const SoftFloat av_normalize_sf(SoftFloat a){
    ਜੇ(a.mant){
#ਜੇ 1
        ਜਦੋਂ((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.ਘਾਤਾਂਕ  -= 1;
        }
#ਨਹੀਂਤਾਂ
        ਪੂਰਨ s=ONE_ਬਿੱਟ - av_log2(FFABS(a.mant));
        a.ਘਾਤਾਂਕ   -= s;
        a.mant <<= s;
#ਜੇ_ਅੰਤ
        ਜੇ(a.ਘਾਤਾਂਕ < MIN_EXP){
            a.ਘਾਤਾਂਕ = MIN_EXP;
            a.mant= 0;
        }
    }ਨਹੀਂਤਾਂ{
        a.ਘਾਤਾਂਕ= MIN_EXP;
    }
    ਵਾਪਸ a;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const SoftFloat av_normalize1_sf(SoftFloat a){
#ਜੇ 1
    ਜੇ((int32_t)(a.mant + 0x40000000U) <= 0){
        a.ਘਾਤਾਂਕ++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.ਘਾਤਾਂਕ <= MAX_EXP);
    ਵਾਪਸ a;
#ਜਾਂਜੇ 1
    ਪੂਰਨ t= a.mant + 0x40000000 < 0;
    ਵਾਪਸ (SoftFloat){ a.mant>>t, a.ਘਾਤਾਂਕ+t};
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ t= (a.mant + 0x3FFFFFFFU)>>31;
    ਵਾਪਸ (SoftFloat){a.mant>>t, a.ਘਾਤਾਂਕ+t};
#ਜੇ_ਅੰਤ
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.ਘਾਤਾਂਕ += b.ਘਾਤਾਂਕ;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_ਬਿੱਟ) == (a.mant * (int64_t)b.mant) >> ONE_ਬਿੱਟ);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_ਬਿੱਟ;
    a = av_normalize1_sf((SoftFloat){a.mant, a.ਘਾਤਾਂਕ - 1});
    ਜੇ (!a.mant || a.ਘਾਤਾਂਕ < MIN_EXP)
        ਵਾਪਸ FLOAT_0;
    ਵਾਪਸ a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t ਆਰਜ਼ੀ = (int64_t)a.mant * (1<<(ONE_ਬਿੱਟ+1));
    ਆਰਜ਼ੀ /= b.mant;
    a.ਘਾਤਾਂਕ -= b.ਘਾਤਾਂਕ;
    a.mant = ਆਰਜ਼ੀ;
    ਜਦੋਂ (a.mant != ਆਰਜ਼ੀ) {
        ਆਰਜ਼ੀ /= 2;
        a.ਘਾਤਾਂਕ--;
        a.mant = ਆਰਜ਼ੀ;
    }
    a = av_normalize1_sf(a);
    ਜੇ (!a.mant || a.ਘਾਤਾਂਕ < MIN_EXP)
        ਵਾਪਸ FLOAT_0;
    ਵਾਪਸ a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ av_cmp_sf(SoftFloat a, SoftFloat b){
    ਪੂਰਨ t= a.ਘਾਤਾਂਕ - b.ਘਾਤਾਂਕ;
    ਜੇ      (t <-31) ਵਾਪਸ                  -  b.mant      ;
    ਨਹੀਂਤਾਂ ਜੇ (t <  0) ਵਾਪਸ (a.mant >> (-t)) -  b.mant      ;
    ਨਹੀਂਤਾਂ ਜੇ (t < 32) ਵਾਪਸ  a.mant          - (b.mant >> t);
    ਨਹੀਂਤਾਂ             ਵਾਪਸ  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ av_gt_sf(SoftFloat a, SoftFloat b)
{
    ਪੂਰਨ t= a.ਘਾਤਾਂਕ - b.ਘਾਤਾਂਕ;
    ਜੇ      (t <-31) ਵਾਪਸ 0                >  b.mant      ;
    ਨਹੀਂਤਾਂ ਜੇ (t <  0) ਵਾਪਸ (a.mant >> (-t)) >  b.mant      ;
    ਨਹੀਂਤਾਂ ਜੇ (t < 32) ਵਾਪਸ  a.mant          > (b.mant >> t);
    ਨਹੀਂਤਾਂ             ਵਾਪਸ  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const SoftFloat av_ਜੋੜੋ_sf(SoftFloat a, SoftFloat b){
    ਪੂਰਨ t= a.ਘਾਤਾਂਕ - b.ਘਾਤਾਂਕ;
    ਜੇ      (t <-31) ਵਾਪਸ b;
    ਨਹੀਂਤਾਂ ਜੇ (t <  0) ਵਾਪਸ av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.ਘਾਤਾਂਕ}));
    ਨਹੀਂਤਾਂ ਜੇ (t < 32) ਵਾਪਸ av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.ਘਾਤਾਂਕ}));
    ਨਹੀਂਤਾਂ             ਵਾਪਸ a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    ਵਾਪਸ av_ਜੋੜੋ_sf(a, (SoftFloat){ -b.mant, b.ਘਾਤਾਂਕ});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const SoftFloat av_int2sf(ਪੂਰਨ v, ਪੂਰਨ frac_ਬਿੱਟ){
    ਪੂਰਨ exp_ਵਿੱਥ = 0;
    ਜੇ(v <= INT_MIN + 1){
        exp_ਵਿੱਥ = 1;
        v>>=1;
    }
    ਵਾਪਸ av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_ਬਿੱਟ + 1 - frac_ਬਿੱਟ + exp_ਵਿੱਥ}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ av_sf2int(SoftFloat v, ਪੂਰਨ frac_ਬਿੱਟ){
    v.ਘਾਤਾਂਕ += frac_ਬਿੱਟ - (ONE_ਬਿੱਟ + 1);
    ਜੇ(v.ਘਾਤਾਂਕ >= 0) ਵਾਪਸ v.mant <<  v.ਘਾਤਾਂਕ ;
    ਨਹੀਂਤਾਂ           ਵਾਪਸ v.mant >>(-v.ਘਾਤਾਂਕ);
}

/**
 * Rounding-to-nearest used.
 */
ਸਥਿਰ av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    ਪੂਰਨ tab_ਸੂਚਕਾਂਕ, rem;

    ਜੇ (val.mant == 0)
        val.ਘਾਤਾਂਕ = MIN_EXP;
    ਨਹੀਂਤਾਂ ਜੇ (val.mant < 0)
        abort();
    ਨਹੀਂਤਾਂ
    {
        tab_ਸੂਚਕਾਂਕ = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (ਪੂਰਨ)(((int64_t)av_sqrttbl_sf[tab_ਸੂਚਕਾਂਕ] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_ਸੂਚਕਾਂਕ + 1] * rem +
                           0x80000) >> 20);
        val.mant = (ਪੂਰਨ)(((int64_t)av_sqr_exp_multbl_sf[val.ਘਾਤਾਂਕ & 1] * val.mant +
                          0x10000000) >> 29);

        ਜੇ (val.mant < 0x40000000)
            val.ਘਾਤਾਂਕ -= 2;
        ਨਹੀਂਤਾਂ
            val.mant >>= 1;

        val.ਘਾਤਾਂਕ = (val.ਘਾਤਾਂਕ >> 1) + 1;
    }

    ਵਾਪਸ val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_ਅਣਵਰਤਿਆ ਸਥਿਰ ਖਾਲੀ av_sincos_sf(ਪੂਰਨ a, ਪੂਰਨ *s, ਪੂਰਨ *c)
{
    ਪੂਰਨ idx, sign;
    ਪੂਰਨ sv, cv;
    ਪੂਰਨ st, ct;

    idx = a >> 26;
    sign = (int32_t)((ਬਿਨਾਨਿਸ਼ਾਨੀ)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((ਬਿਨਾਨਿਸ਼ਾਨੀ)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (ਪੂਰਨ)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (ਪੂਰਨ)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (ਪੂਰਨ)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (ਪੂਰਨ)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (ਪੂਰਨ)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (ਪੂਰਨ)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (ਪੂਰਨ)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (ਪੂਰਨ)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#ਜੇ_ਅੰਤ /* AVUTIL_SOFTFLOAT_H */
