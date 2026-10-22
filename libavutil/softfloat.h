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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_SOFTFLOAT_H
#وصف_ڪريو AVUTIL_SOFTFLOAT_H

#ضمن <stdint.h>
#ضمن "common.h"

#ضمن "avassert.h"
#ضمن "softfloat_tables.h"

#وصف_ڪريو MIN_EXP -149
#وصف_ڪريو MAX_EXP  126
#وصف_ڪريو ONE_بٽ 29

تعريفنوع بنية SoftFloat{
    int32_t mant;
    int32_t  قوت_نما;
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
    v.قوت_نما -= ONE_بٽ +1;
    أرجع ldexp(v.mant, v.قوت_نما);
}

ساكن av_const SoftFloat av_normalize_sf(SoftFloat a){
    إذا(a.mant){
#إذا 1
        طالما((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.قوت_نما  -= 1;
        }
#وإلا
        صحيح s=ONE_بٽ - av_log2(FFABS(a.mant));
        a.قوت_نما   -= s;
        a.mant <<= s;
#جيڪڏهن_پورو
        إذا(a.قوت_نما < MIN_EXP){
            a.قوت_نما = MIN_EXP;
            a.mant= 0;
        }
    }وإلا{
        a.قوت_نما= MIN_EXP;
    }
    أرجع a;
}

ساكن مضمن av_const SoftFloat av_normalize1_sf(SoftFloat a){
#إذا 1
    إذا((int32_t)(a.mant + 0x40000000U) <= 0){
        a.قوت_نما++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.قوت_نما <= MAX_EXP);
    أرجع a;
#وإلاإذا 1
    صحيح t= a.mant + 0x40000000 < 0;
    أرجع (SoftFloat){ a.mant>>t, a.قوت_نما+t};
#وإلا
    صحيح t= (a.mant + 0x3FFFFFFFU)>>31;
    أرجع (SoftFloat){a.mant>>t, a.قوت_نما+t};
#جيڪڏهن_پورو
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
ساكن مضمن av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.قوت_نما += b.قوت_نما;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_بٽ) == (a.mant * (int64_t)b.mant) >> ONE_بٽ);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_بٽ;
    a = av_normalize1_sf((SoftFloat){a.mant, a.قوت_نما - 1});
    إذا (!a.mant || a.قوت_نما < MIN_EXP)
        أرجع FLOAT_0;
    أرجع a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
ساكن مضمن av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t عارضي = (int64_t)a.mant * (1<<(ONE_بٽ+1));
    عارضي /= b.mant;
    a.قوت_نما -= b.قوت_نما;
    a.mant = عارضي;
    طالما (a.mant != عارضي) {
        عارضي /= 2;
        a.قوت_نما--;
        a.mant = عارضي;
    }
    a = av_normalize1_sf(a);
    إذا (!a.mant || a.قوت_نما < MIN_EXP)
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
    صحيح t= a.قوت_نما - b.قوت_نما;
    إذا      (t <-31) أرجع                  -  b.mant      ;
    وإلا إذا (t <  0) أرجع (a.mant >> (-t)) -  b.mant      ;
    وإلا إذا (t < 32) أرجع  a.mant          - (b.mant >> t);
    وإلا             أرجع  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
ساكن مضمن av_const صحيح av_gt_sf(SoftFloat a, SoftFloat b)
{
    صحيح t= a.قوت_نما - b.قوت_نما;
    إذا      (t <-31) أرجع 0                >  b.mant      ;
    وإلا إذا (t <  0) أرجع (a.mant >> (-t)) >  b.mant      ;
    وإلا إذا (t < 32) أرجع  a.mant          > (b.mant >> t);
    وإلا             أرجع  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
ساكن مضمن av_const SoftFloat av_جوڙيو_sf(SoftFloat a, SoftFloat b){
    صحيح t= a.قوت_نما - b.قوت_نما;
    إذا      (t <-31) أرجع b;
    وإلا إذا (t <  0) أرجع av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.قوت_نما}));
    وإلا إذا (t < 32) أرجع av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.قوت_نما}));
    وإلا             أرجع a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
ساكن مضمن av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    أرجع av_جوڙيو_sf(a, (SoftFloat){ -b.mant, b.قوت_نما});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
ساكن مضمن av_const SoftFloat av_int2sf(صحيح v, صحيح frac_بٽ){
    صحيح exp_وٿي = 0;
    إذا(v <= INT_MIN + 1){
        exp_وٿي = 1;
        v>>=1;
    }
    أرجع av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_بٽ + 1 - frac_بٽ + exp_وٿي}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
ساكن مضمن av_const صحيح av_sf2int(SoftFloat v, صحيح frac_بٽ){
    v.قوت_نما += frac_بٽ - (ONE_بٽ + 1);
    إذا(v.قوت_نما >= 0) أرجع v.mant <<  v.قوت_نما ;
    وإلا           أرجع v.mant >>(-v.قوت_نما);
}

/**
 * Rounding-to-nearest used.
 */
ساكن av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    صحيح tab_اشاريو, rem;

    إذا (val.mant == 0)
        val.قوت_نما = MIN_EXP;
    وإلا إذا (val.mant < 0)
        abort();
    وإلا
    {
        tab_اشاريو = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (صحيح)(((int64_t)av_sqrttbl_sf[tab_اشاريو] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_اشاريو + 1] * rem +
                           0x80000) >> 20);
        val.mant = (صحيح)(((int64_t)av_sqr_exp_multbl_sf[val.قوت_نما & 1] * val.mant +
                          0x10000000) >> 29);

        إذا (val.mant < 0x40000000)
            val.قوت_نما -= 2;
        وإلا
            val.mant >>= 1;

        val.قوت_نما = (val.قوت_نما >> 1) + 1;
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
av_اڻ_استعمال_ٿيل ساكن فراغ av_sincos_sf(صحيح a, صحيح *s, صحيح *c)
{
    صحيح idx, sign;
    صحيح sv, cv;
    صحيح st, ct;

    idx = a >> 26;
    sign = (int32_t)((بنانشان)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((بنانشان)idx << 27) >> 31;
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

#جيڪڏهن_پورو /* AVUTIL_SOFTFLOAT_H */
