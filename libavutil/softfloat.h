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

#اگر_غیر_تعریف_شدہ AVUTIL_SOFTFLOAT_H
#تعریف_کرو AVUTIL_SOFTFLOAT_H

#شامل <stdint.h>
#شامل "common.h"

#شامل "avassert.h"
#شامل "softfloat_tables.h"

#تعریف_کرو MIN_EXP -149
#تعریف_کرو MAX_EXP  126
#تعریف_کرو ONE_بٹ 29

قسمتعریف ساخت SoftFloat{
    int32_t mant;
    int32_t  قوت_نما;
}SoftFloat;

ساکن ثابت SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
ساکن ثابت SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
ساکن ثابت SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
ساکن ثابت SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
ساکن ثابت SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
ساکن ثابت SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
ساکن ثابت SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
ساکن ثابت SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
ساکن اندرونی av_const دوہرا av_sf2double(SoftFloat v) {
    v.قوت_نما -= ONE_بٹ +1;
    واپس ldexp(v.mant, v.قوت_نما);
}

ساکن av_const SoftFloat av_normalize_sf(SoftFloat a){
    اگر(a.mant){
#اگر 1
        جب((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.قوت_نما  -= 1;
        }
#ورنہ
        صحیح s=ONE_بٹ - av_log2(FFABS(a.mant));
        a.قوت_نما   -= s;
        a.mant <<= s;
#اگر_ختم
        اگر(a.قوت_نما < MIN_EXP){
            a.قوت_نما = MIN_EXP;
            a.mant= 0;
        }
    }ورنہ{
        a.قوت_نما= MIN_EXP;
    }
    واپس a;
}

ساکن اندرونی av_const SoftFloat av_normalize1_sf(SoftFloat a){
#اگر 1
    اگر((int32_t)(a.mant + 0x40000000U) <= 0){
        a.قوت_نما++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.قوت_نما <= MAX_EXP);
    واپس a;
#وگرنہ_اگر 1
    صحیح t= a.mant + 0x40000000 < 0;
    واپس (SoftFloat){ a.mant>>t, a.قوت_نما+t};
#ورنہ
    صحیح t= (a.mant + 0x3FFFFFFFU)>>31;
    واپس (SoftFloat){a.mant>>t, a.قوت_نما+t};
#اگر_ختم
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
ساکن اندرونی av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.قوت_نما += b.قوت_نما;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_بٹ) == (a.mant * (int64_t)b.mant) >> ONE_بٹ);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_بٹ;
    a = av_normalize1_sf((SoftFloat){a.mant, a.قوت_نما - 1});
    اگر (!a.mant || a.قوت_نما < MIN_EXP)
        واپس FLOAT_0;
    واپس a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
ساکن اندرونی av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t عارضی = (int64_t)a.mant * (1<<(ONE_بٹ+1));
    عارضی /= b.mant;
    a.قوت_نما -= b.قوت_نما;
    a.mant = عارضی;
    جب (a.mant != عارضی) {
        عارضی /= 2;
        a.قوت_نما--;
        a.mant = عارضی;
    }
    a = av_normalize1_sf(a);
    اگر (!a.mant || a.قوت_نما < MIN_EXP)
        واپس FLOAT_0;
    واپس a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
ساکن اندرونی av_const صحیح av_cmp_sf(SoftFloat a, SoftFloat b){
    صحیح t= a.قوت_نما - b.قوت_نما;
    اگر      (t <-31) واپس                  -  b.mant      ;
    ورنہ اگر (t <  0) واپس (a.mant >> (-t)) -  b.mant      ;
    ورنہ اگر (t < 32) واپس  a.mant          - (b.mant >> t);
    ورنہ             واپس  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
ساکن اندرونی av_const صحیح av_gt_sf(SoftFloat a, SoftFloat b)
{
    صحیح t= a.قوت_نما - b.قوت_نما;
    اگر      (t <-31) واپس 0                >  b.mant      ;
    ورنہ اگر (t <  0) واپس (a.mant >> (-t)) >  b.mant      ;
    ورنہ اگر (t < 32) واپس  a.mant          > (b.mant >> t);
    ورنہ             واپس  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
ساکن اندرونی av_const SoftFloat av_جوڑو_sf(SoftFloat a, SoftFloat b){
    صحیح t= a.قوت_نما - b.قوت_نما;
    اگر      (t <-31) واپس b;
    ورنہ اگر (t <  0) واپس av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.قوت_نما}));
    ورنہ اگر (t < 32) واپس av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.قوت_نما}));
    ورنہ             واپس a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
ساکن اندرونی av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    واپس av_جوڑو_sf(a, (SoftFloat){ -b.mant, b.قوت_نما});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
ساکن اندرونی av_const SoftFloat av_int2sf(صحیح v, صحیح frac_بٹ){
    صحیح exp_انحراف = 0;
    اگر(v <= INT_MIN + 1){
        exp_انحراف = 1;
        v>>=1;
    }
    واپس av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_بٹ + 1 - frac_بٹ + exp_انحراف}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
ساکن اندرونی av_const صحیح av_sf2int(SoftFloat v, صحیح frac_بٹ){
    v.قوت_نما += frac_بٹ - (ONE_بٹ + 1);
    اگر(v.قوت_نما >= 0) واپس v.mant <<  v.قوت_نما ;
    ورنہ           واپس v.mant >>(-v.قوت_نما);
}

/**
 * Rounding-to-nearest used.
 */
ساکن av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    صحیح tab_اشاریہ, rem;

    اگر (val.mant == 0)
        val.قوت_نما = MIN_EXP;
    ورنہ اگر (val.mant < 0)
        abort();
    ورنہ
    {
        tab_اشاریہ = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (صحیح)(((int64_t)av_sqrttbl_sf[tab_اشاریہ] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_اشاریہ + 1] * rem +
                           0x80000) >> 20);
        val.mant = (صحیح)(((int64_t)av_sqr_exp_multbl_sf[val.قوت_نما & 1] * val.mant +
                          0x10000000) >> 29);

        اگر (val.mant < 0x40000000)
            val.قوت_نما -= 2;
        ورنہ
            val.mant >>= 1;

        val.قوت_نما = (val.قوت_نما >> 1) + 1;
    }

    واپس val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_غیر_مستعمل ساکن خالی av_sincos_sf(صحیح a, صحیح *s, صحیح *c)
{
    صحیح idx, sign;
    صحیح sv, cv;
    صحیح st, ct;

    idx = a >> 26;
    sign = (int32_t)((غیرعلامتی)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((غیرعلامتی)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (صحیح)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (صحیح)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (صحیح)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (صحیح)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (صحیح)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (صحیح)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (صحیح)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (صحیح)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#اگر_ختم /* AVUTIL_SOFTFLOAT_H */
