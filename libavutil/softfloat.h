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

#अगर_अघोषित AVUTIL_SOFTFLOAT_H
#घोषणा AVUTIL_SOFTFLOAT_H

#समावेश <stdint.h>
#समावेश "common.h"

#समावेश "avassert.h"
#समावेश "softfloat_tables.h"

#घोषणा MIN_EXP -149
#घोषणा MAX_EXP  126
#घोषणा ONE_BITS 29

प्रकार काष्ठा SoftFloat{
    int32_t mant;
    int32_t  exp;
}SoftFloat;

अटल स्थिर SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
अटल स्थिर SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
अटल स्थिर SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
अटल स्थिर SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
अटल स्थिर SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
अटल स्थिर SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
अटल स्थिर SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
अटल स्थिर SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
अटल अंतरभूत av_const द्विगुन av_sf2double(SoftFloat v) {
    v.exp -= ONE_BITS +1;
    वापस ldexp(v.mant, v.exp);
}

अटल av_const SoftFloat av_normalize_sf(SoftFloat a){
    अगर(a.mant){
#अगर 1
        जबतक((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.exp  -= 1;
        }
#अन्यथा
        पूर्णांक s=ONE_BITS - av_log2(FFABS(a.mant));
        a.exp   -= s;
        a.mant <<= s;
#पूर्ण_अगर
        अगर(a.exp < MIN_EXP){
            a.exp = MIN_EXP;
            a.mant= 0;
        }
    }अन्यथा{
        a.exp= MIN_EXP;
    }
    वापस a;
}

अटल अंतरभूत av_const SoftFloat av_normalize1_sf(SoftFloat a){
#अगर 1
    अगर((int32_t)(a.mant + 0x40000000U) <= 0){
        a.exp++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.exp <= MAX_EXP);
    वापस a;
#या_अगर 1
    पूर्णांक t= a.mant + 0x40000000 < 0;
    वापस (SoftFloat){ a.mant>>t, a.exp+t};
#अन्यथा
    पूर्णांक t= (a.mant + 0x3FFFFFFFU)>>31;
    वापस (SoftFloat){a.mant>>t, a.exp+t};
#पूर्ण_अगर
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
अटल अंतरभूत av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.exp += b.exp;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_BITS) == (a.mant * (int64_t)b.mant) >> ONE_BITS);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_BITS;
    a = av_normalize1_sf((SoftFloat){a.mant, a.exp - 1});
    अगर (!a.mant || a.exp < MIN_EXP)
        वापस FLOAT_0;
    वापस a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
अटल अंतरभूत av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t अस्थायी = (int64_t)a.mant * (1<<(ONE_BITS+1));
    अस्थायी /= b.mant;
    a.exp -= b.exp;
    a.mant = अस्थायी;
    जबतक (a.mant != अस्थायी) {
        अस्थायी /= 2;
        a.exp--;
        a.mant = अस्थायी;
    }
    a = av_normalize1_sf(a);
    अगर (!a.mant || a.exp < MIN_EXP)
        वापस FLOAT_0;
    वापस a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
अटल अंतरभूत av_const पूर्णांक av_cmp_sf(SoftFloat a, SoftFloat b){
    पूर्णांक t= a.exp - b.exp;
    अगर      (t <-31) वापस                  -  b.mant      ;
    अन्यथा अगर (t <  0) वापस (a.mant >> (-t)) -  b.mant      ;
    अन्यथा अगर (t < 32) वापस  a.mant          - (b.mant >> t);
    अन्यथा             वापस  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
अटल अंतरभूत av_const पूर्णांक av_gt_sf(SoftFloat a, SoftFloat b)
{
    पूर्णांक t= a.exp - b.exp;
    अगर      (t <-31) वापस 0                >  b.mant      ;
    अन्यथा अगर (t <  0) वापस (a.mant >> (-t)) >  b.mant      ;
    अन्यथा अगर (t < 32) वापस  a.mant          > (b.mant >> t);
    अन्यथा             वापस  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
अटल अंतरभूत av_const SoftFloat av_add_sf(SoftFloat a, SoftFloat b){
    पूर्णांक t= a.exp - b.exp;
    अगर      (t <-31) वापस b;
    अन्यथा अगर (t <  0) वापस av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.exp}));
    अन्यथा अगर (t < 32) वापस av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.exp}));
    अन्यथा             वापस a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
अटल अंतरभूत av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    वापस av_add_sf(a, (SoftFloat){ -b.mant, b.exp});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
अटल अंतरभूत av_const SoftFloat av_int2sf(पूर्णांक v, पूर्णांक frac_bits){
    पूर्णांक exp_offset = 0;
    अगर(v <= पूर्णांक_न्यून + 1){
        exp_offset = 1;
        v>>=1;
    }
    वापस av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_BITS + 1 - frac_bits + exp_offset}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
अटल अंतरभूत av_const पूर्णांक av_sf2int(SoftFloat v, पूर्णांक frac_bits){
    v.exp += frac_bits - (ONE_BITS + 1);
    अगर(v.exp >= 0) वापस v.mant <<  v.exp ;
    अन्यथा           वापस v.mant >>(-v.exp);
}

/**
 * Rounding-to-nearest used.
 */
अटल av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    पूर्णांक tab_सूचकांक, rem;

    अगर (val.mant == 0)
        val.exp = MIN_EXP;
    अन्यथा अगर (val.mant < 0)
        पात();
    अन्यथा
    {
        tab_सूचकांक = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (पूर्णांक)(((int64_t)av_sqrttbl_sf[tab_सूचकांक] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_सूचकांक + 1] * rem +
                           0x80000) >> 20);
        val.mant = (पूर्णांक)(((int64_t)av_sqr_exp_multbl_sf[val.exp & 1] * val.mant +
                          0x10000000) >> 29);

        अगर (val.mant < 0x40000000)
            val.exp -= 2;
        अन्यथा
            val.mant >>= 1;

        val.exp = (val.exp >> 1) + 1;
    }

    वापस val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_unused अटल व्योम av_sincos_sf(पूर्णांक a, पूर्णांक *s, पूर्णांक *c)
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

#पूर्ण_अगर /* AVUTIL_SOFTFLOAT_H */
