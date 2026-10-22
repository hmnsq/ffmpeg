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

#यदि_अपरिभाषितम् AVUTIL_SOFTFLOAT_H
#परिभाषय AVUTIL_SOFTFLOAT_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "common.h"

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "softfloat_tables.h"

#परिभाषय MIN_EXP -149
#परिभाषय MAX_EXP  126
#परिभाषय ONE_द्वयङ्काः 29

प्रकारनिर्देश संरचना SoftFloat{
    int32_t mant;
    int32_t  घातांकः;
}SoftFloat;

स्थिर ध्रुव SoftFloat FLOAT_0          = {          0,   MIN_EXP};             ///< 0.0
स्थिर ध्रुव SoftFloat FLOAT_05         = { 0x20000000,   0};                   ///< 0.5
स्थिर ध्रुव SoftFloat FLOAT_1          = { 0x20000000,   1};                   ///< 1.0
स्थिर ध्रुव SoftFloat FLOAT_EPSILON    = { 0x29F16B12, -16};                   ///< A small value
स्थिर ध्रुव SoftFloat FLOAT_1584893192 = { 0x32B771ED,   1};                   ///< 1.584893192 (10^.2)
स्थिर ध्रुव SoftFloat FLOAT_100000     = { 0x30D40000,  17};                   ///< 100000
स्थिर ध्रुव SoftFloat FLOAT_0999999    = { 0x3FFFFBCE,   0};                   ///< 0.999999
स्थिर ध्रुव SoftFloat FLOAT_MIN        = { 0x20000000,   MIN_EXP};


/**
 * Convert a SoftFloat to a double precision float.
 */
स्थिर अन्तःस्थ av_const द्विगुण av_sf2double(SoftFloat v) {
    v.घातांकः -= ONE_द्वयङ्काः +1;
    प्रत्यागम ldexp(v.mant, v.घातांकः);
}

स्थिर av_const SoftFloat av_normalize_sf(SoftFloat a){
    यदि(a.mant){
#यदि 1
        यावत्((a.mant + 0x1FFFFFFFU)<0x3FFFFFFFU){
            a.mant += a.mant;
            a.घातांकः  -= 1;
        }
#अन्यथा
        पूर्णाङ्क s=ONE_द्वयङ्काः - av_log2(FFABS(a.mant));
        a.घातांकः   -= s;
        a.mant <<= s;
#यदि_अन्तः
        यदि(a.घातांकः < MIN_EXP){
            a.घातांकः = MIN_EXP;
            a.mant= 0;
        }
    }अन्यथा{
        a.घातांकः= MIN_EXP;
    }
    प्रत्यागम a;
}

स्थिर अन्तःस्थ av_const SoftFloat av_normalize1_sf(SoftFloat a){
#यदि 1
    यदि((int32_t)(a.mant + 0x40000000U) <= 0){
        a.घातांकः++;
        a.mant>>=1;
    }
    av_assert2(a.mant < 0x40000000 && a.mant > -0x40000000);
    av_assert2(a.घातांकः <= MAX_EXP);
    प्रत्यागम a;
#नोचेद्यदि 1
    पूर्णाङ्क t= a.mant + 0x40000000 < 0;
    प्रत्यागम (SoftFloat){ a.mant>>t, a.घातांकः+t};
#अन्यथा
    पूर्णाङ्क t= (a.mant + 0x3FFFFFFFU)>>31;
    प्रत्यागम (SoftFloat){a.mant>>t, a.घातांकः+t};
#यदि_अन्तः
}

/**
 * @return Will not be more denormalized than a*b. So if either input is
 *         normalized, then the output will not be worse then the other input.
 *         If both are normalized, then the output will be normalized.
 */
स्थिर अन्तःस्थ av_const SoftFloat av_mul_sf(SoftFloat a, SoftFloat b){
    a.घातांकः += b.घातांकः;
    av_assert2((int32_t)((a.mant * (int64_t)b.mant) >> ONE_द्वयङ्काः) == (a.mant * (int64_t)b.mant) >> ONE_द्वयङ्काः);
    a.mant = (a.mant * (int64_t)b.mant) >> ONE_द्वयङ्काः;
    a = av_normalize1_sf((SoftFloat){a.mant, a.घातांकः - 1});
    यदि (!a.mant || a.घातांकः < MIN_EXP)
        प्रत्यागम FLOAT_0;
    प्रत्यागम a;
}

/**
 * b has to be normalized and not zero.
 * @return Will not be more denormalized than a.
 */
स्थिर अन्तःस्थ av_const SoftFloat av_div_sf(SoftFloat a, SoftFloat b){
    int64_t अस्थायी = (int64_t)a.mant * (1<<(ONE_द्वयङ्काः+1));
    अस्थायी /= b.mant;
    a.घातांकः -= b.घातांकः;
    a.mant = अस्थायी;
    यावत् (a.mant != अस्थायी) {
        अस्थायी /= 2;
        a.घातांकः--;
        a.mant = अस्थायी;
    }
    a = av_normalize1_sf(a);
    यदि (!a.mant || a.घातांकः < MIN_EXP)
        प्रत्यागम FLOAT_0;
    प्रत्यागम a;
}

/**
 * Compares two SoftFloats.
 * @returns < 0 if the first is less
 *          > 0 if the first is greater
 *            0 if they are equal
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_cmp_sf(SoftFloat a, SoftFloat b){
    पूर्णाङ्क t= a.घातांकः - b.घातांकः;
    यदि      (t <-31) प्रत्यागम                  -  b.mant      ;
    अन्यथा यदि (t <  0) प्रत्यागम (a.mant >> (-t)) -  b.mant      ;
    अन्यथा यदि (t < 32) प्रत्यागम  a.mant          - (b.mant >> t);
    अन्यथा             प्रत्यागम  a.mant                         ;
}

/**
 * Compares two SoftFloats.
 * @returns 1 if a is greater than b, 0 otherwise
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_gt_sf(SoftFloat a, SoftFloat b)
{
    पूर्णाङ्क t= a.घातांकः - b.घातांकः;
    यदि      (t <-31) प्रत्यागम 0                >  b.mant      ;
    अन्यथा यदि (t <  0) प्रत्यागम (a.mant >> (-t)) >  b.mant      ;
    अन्यथा यदि (t < 32) प्रत्यागम  a.mant          > (b.mant >> t);
    अन्यथा             प्रत्यागम  a.mant          >  0           ;
}

/**
 * @returns the sum of 2 SoftFloats.
 */
स्थिर अन्तःस्थ av_const SoftFloat av_सङ्कलय_sf(SoftFloat a, SoftFloat b){
    पूर्णाङ्क t= a.घातांकः - b.घातांकः;
    यदि      (t <-31) प्रत्यागम b;
    अन्यथा यदि (t <  0) प्रत्यागम av_normalize_sf(av_normalize1_sf((SoftFloat){ b.mant + (a.mant >> (-t)), b.घातांकः}));
    अन्यथा यदि (t < 32) प्रत्यागम av_normalize_sf(av_normalize1_sf((SoftFloat){ a.mant + (b.mant >>   t ), a.घातांकः}));
    अन्यथा             प्रत्यागम a;
}

/**
 * @returns the difference of 2 SoftFloats.
 */
स्थिर अन्तःस्थ av_const SoftFloat av_sub_sf(SoftFloat a, SoftFloat b){
    प्रत्यागम av_सङ्कलय_sf(a, (SoftFloat){ -b.mant, b.घातांकः});
}

//FIXME log, exp, pow

/**
 * Converts a mantisse and exponent to a SoftFloat.
 * This converts a fixed point value v with frac_bits fractional bits to a
 * SoftFloat.
 * @returns a SoftFloat with value v * 2^-frac_bits
 */
स्थिर अन्तःस्थ av_const SoftFloat av_int2sf(पूर्णाङ्क v, पूर्णाङ्क frac_द्वयङ्काः){
    पूर्णाङ्क exp_विस्थापनम् = 0;
    यदि(v <= INT_MIN + 1){
        exp_विस्थापनम् = 1;
        v>>=1;
    }
    प्रत्यागम av_normalize_sf(av_normalize1_sf((SoftFloat){v, ONE_द्वयङ्काः + 1 - frac_द्वयङ्काः + exp_विस्थापनम्}));
}

/**
 * Converts a SoftFloat to an integer.
 * Rounding is to -inf.
 */
स्थिर अन्तःस्थ av_const पूर्णाङ्क av_sf2int(SoftFloat v, पूर्णाङ्क frac_द्वयङ्काः){
    v.घातांकः += frac_द्वयङ्काः - (ONE_द्वयङ्काः + 1);
    यदि(v.घातांकः >= 0) प्रत्यागम v.mant <<  v.घातांकः ;
    अन्यथा           प्रत्यागम v.mant >>(-v.घातांकः);
}

/**
 * Rounding-to-nearest used.
 */
स्थिर av_always_inline SoftFloat av_sqrt_sf(SoftFloat val)
{
    पूर्णाङ्क tab_सूचकांक, rem;

    यदि (val.mant == 0)
        val.घातांकः = MIN_EXP;
    अन्यथा यदि (val.mant < 0)
        abort();
    अन्यथा
    {
        tab_सूचकांक = (val.mant - 0x20000000) >> 20;

        rem = val.mant & 0xFFFFF;
        val.mant  = (पूर्णाङ्क)(((int64_t)av_sqrttbl_sf[tab_सूचकांक] * (0x100000 - rem) +
                           (int64_t)av_sqrttbl_sf[tab_सूचकांक + 1] * rem +
                           0x80000) >> 20);
        val.mant = (पूर्णाङ्क)(((int64_t)av_sqr_exp_multbl_sf[val.घातांकः & 1] * val.mant +
                          0x10000000) >> 29);

        यदि (val.mant < 0x40000000)
            val.घातांकः -= 2;
        अन्यथा
            val.mant >>= 1;

        val.घातांकः = (val.घातांकः >> 1) + 1;
    }

    प्रत्यागम val;
}

/**
 * Rounding-to-nearest used.
 *
 * @param a angle in units of (1ULL<<30)/M_PI radians
 * @param s pointer to where   sine in units of (1<<30) is returned
 * @param c pointer to where cosine in units of (1<<30) is returned
 */
av_अप्रयुक्तम् स्थिर शून्य av_sincos_sf(पूर्णाङ्क a, पूर्णाङ्क *s, पूर्णाङ्क *c)
{
    पूर्णाङ्क idx, sign;
    पूर्णाङ्क sv, cv;
    पूर्णाङ्क st, ct;

    idx = a >> 26;
    sign = (int32_t)((अचिह्नित)idx << 27) >> 31;
    cv = av_costbl_1_sf[idx & 0xf];
    cv = (cv ^ sign) - sign;

    idx -= 8;
    sign = (int32_t)((अचिह्नित)idx << 27) >> 31;
    sv = av_costbl_1_sf[idx & 0xf];
    sv = (sv ^ sign) - sign;

    idx = a >> 21;
    ct = av_costbl_2_sf[idx & 0x1f];
    st = av_sintbl_2_sf[idx & 0x1f];

    idx = (पूर्णाङ्क)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (पूर्णाङ्क)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);

    cv = idx;

    idx = a >> 16;
    ct = av_costbl_3_sf[idx & 0x1f];
    st = av_sintbl_3_sf[idx & 0x1f];

    idx = (पूर्णाङ्क)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    sv = (पूर्णाङ्क)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
    cv = idx;

    idx = a >> 11;

    ct = (पूर्णाङ्क)(((int64_t)av_costbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_costbl_4_sf[(idx & 0x1f)+1]*(a & 0x7ff) +
                0x400) >> 11);
    st = (पूर्णाङ्क)(((int64_t)av_sintbl_4_sf[idx & 0x1f] * (0x800 - (a & 0x7ff)) +
                (int64_t)av_sintbl_4_sf[(idx & 0x1f) + 1] * (a & 0x7ff) +
                0x400) >> 11);

    *c = (पूर्णाङ्क)(((int64_t)cv * ct - (int64_t)sv * st + 0x20000000) >> 30);

    *s = (पूर्णाङ्क)(((int64_t)cv * st + (int64_t)sv * ct + 0x20000000) >> 30);
}

#यदि_अन्तः /* AVUTIL_SOFTFLOAT_H */
