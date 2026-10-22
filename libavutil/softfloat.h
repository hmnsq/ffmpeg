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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "common.h"

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "softfloat_tables.h"

#define MIN_EXP -149
#define MAX_EXP  126
#define ONE_BITS 29

प्रकारव्याख्या संरचना SoftFloat{
    int32_t mant;
    int32_t  exp;
}SoftFloat;

स्थिर स्थिरांक SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
स्थिर स्थिरांक SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
स्थिर स्थिरांक SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
स्थिर स्थिरांक SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
स्थिर स्थिरांक SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
स्थिर स्थिरांक SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
स्थिर स्थिरांक SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
स्थिर स्थिरांक SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
स्थिर ओळीत av_const द्विगुण av_sf2double(SoftFloat v) {
    v.exp -= ONE_BITS +1;
    परत ldexp(v.mant, v.exp);
}

स्थिर av_const SoftFloat av_normalize_sf(SoftFloat a){
    जर(a.mant){
#जर 1
        पर्यंत((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.exp  -= 1;
        }
#अन्यथा
        पूर्णांक s=ONE_BITS - av_log2(FFABS(a.mant));
        a.exp   -= s;
        a.mant <<= s;
#endif
        जर(a.exp < MIN_EXP){
            a.exp = MIN_EXP;
            a.mant= 0;
        }
    }अन्यथा{
        a.exp= MIN_EXP;
    }
    परत a;
}

स्थिर ओळीत av_const SoftFloat av_normalize1_sf(SoftFloat a){
#जर 1
    जर((int32_t)(a.mant + 0x40000000U) <= 0){
        a.exp++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.exp <= MAX_EXP);
    परत a;
#किंवाजर 1
    पूर्णांक t= a.mant + 0x40000000 < 0;
    परत (SoftFloat){ a.mant>>t, a.exp+t};
#अन्यथा
    पूर्णांक t= (a.mant + 0x3FFFFFFFU)>>31;
    परत (SoftFloat){a.mant>>t, a.exp+t};
#endif
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
स्थिर ओळीत av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.exp += b.exp;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_BITS) == (a.mant * (int64_t)b.mant) >> ONE_BITS);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_BITS;
    a = av_normalize1_sf((SoftFloat){a.mant, a.exp - 1});
    जर (!a.mant || a.exp < MIN_EXP)
        परत FLOAT_0;
    परत a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
स्थिर ओळीत av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t temp = (int64_t)a.mant * (1<<(ONE_BITS+1));
    temp /= b.mant;
    a.exp -= b.exp;
    a.mant = temp;
    पर्यंत (a.mant != temp) {
        temp /= 2;
        a.exp--;
        a.mant = temp;
    }
    a = av_normalize1_sf(a);
    जर (!a.mant || a.exp < MIN_EXP)
        परत FLOAT_0;
    परत a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
स्थिर ओळीत av_const पूर्णांक av_cmp_sf(SoftFloat a, SoftFloat b){
    पूर्णांक t= a.exp - b.exp;
    जर      (t <-31) परत                  -  b.mant      ;
    अन्यथा जर (t <  0) परत (a.mant >> (-t)) -  b.mant      ;
    अन्यथा जर (t < 32) परत  a.mant          - (b.mant >> t);
    अन्यथा             परत  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
स्थिर ओळीत av_const पूर्णांक av_gt_sf(SoftFloat a, SoftFloat b)
{
    पूर्णांक t= a.exp - b.exp;
    जर      (t <-31) परत 0                >  b.mant      ;
    अन्यथा जर (t <  0) परत (a.mant >> (-t)) >  b.mant      ;
    अन्यथा जर (t < 32) परत  a.mant          > (b.mant >> t);
    अन्यथा             परत  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
स्थिर ओळीत av_const SoftFloat av_add_sf(SoftFloat a, SoftFloat b){
    पूर्णांक t= a.exp - b.exp;
    जर      (t <-31) परत b;
    अन्यथा जर (t <  0) परत av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.exp}));
    अन्यथा जर (t < 32) परत av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.exp}));
    अन्यथा             परत a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
स्थिर ओळीत av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    परत av_add_sf(a, (SoftFloat){ -b.mant, b.exp});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
स्थिर ओळीत av_const SoftFloat av_int2sf(पूर्णांक v, पूर्णांक frac_bits){
    पूर्णांक exp_offset = 0;
    जर(v <= पूर्णांक_न्यून + 1){
        exp_offset = 1;
        v>>=1;
    }
    परत av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_BITS + 1 - frac_bits + exp_offset}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
स्थिर ओळीत av_const पूर्णांक av_sf2int(SoftFloat v, पूर्णांक frac_bits){
    v.exp += frac_bits - (ONE_BITS + 1);
    जर(v.exp >= 0) परत v.mant <<  v.exp ;
    अन्यथा           परत v.mant >>(-v.exp);
}

/**
 * Rounding-to-nearest used.
 */
स्थिर av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    पूर्णांक tabIndex, rem;

    जर (val.mant == 0)
        val.exp = MIN_EXP;
    अन्यथा जर (val.mant < 0)
        पात();
    अन्यथा
    {
        tabIndex = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (पूर्णांक)(((int64_t)av_sqrttbl_sf[tabIndex] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tabIndex + 1] * rem +
                           0x80000) >> 20);
        val.mant = (पूर्णांक)(((int64_t)av_sqr_exp_multbl_sf[val.exp & 1] * val.mant +
                          0x10000000) >> 29);

        जर (val.mant < 0x40000000)
            val.exp -= 2;
        अन्यथा
            val.mant >>= 1;

        val.exp = (val.exp >> 1) + 1;
    }

    परत val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_unused स्थिर शून्य av_sincos_sf(पूर्णांक a, पूर्णांक *s, पूर्णांक *c)
{
    पूर्णांक idx, sign;
    पूर्णांक sv, cv;
    पूर्णांक st, ct;

    idx = a >> 26;
    sign = (int32_t)((अचिन्हित)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((अचिन्हित)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (पूर्णांक)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (पूर्णांक)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (पूर्णांक)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (पूर्णांक)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (पूर्णांक)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (पूर्णांक)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (पूर्णांक)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (पूर्णांक)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#endif /* AVUTIL_SOFTFLOAT_H */
