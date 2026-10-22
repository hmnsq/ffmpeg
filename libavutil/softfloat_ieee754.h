/*
 * Copyright (c) 2016 Umair Khan <omerjerk@gmail.com>
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

#ifndef AVUTIL_SOFTFLOAT_IEEE754_H
#define AVUTIL_SOFTFLOAT_IEEE754_H

#شامل <stdint.h>

#define EXP_BIAS 127
#define MANT_BITS 23

تعریفنوع ساختار SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  exp;
} SoftFloat_IEEE754;

ایستا ثابت SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
ایستا ثابت SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

/** Normalize the softfloat as defined by IEEE 754 single-recision floating
 *  point specification
 */
ایستا درونخطی SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    وقتی( sf.mant >= 0x1000000UL ) {
        sf.exp++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    بازگشت sf;
}

/** Convert integer to softfloat.
 *  @return softfloat with value n * 2^e
 */
ایستا درونخطی SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, صحیح e) {
    صحیح sign = 0;

    اگر (n < 0) {
        sign = 1;
        n    *= -1;
    }
    بازگشت av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_BITS, 0 + e});
}

/** Make a softfloat out of the bitstream. Assumes the bits are in the form as defined
 *  by the IEEE 754 spec.
 */
ایستا درونخطی SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    بازگشت ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

/** Convert the softfloat to integer
 */
ایستا درونخطی صحیح av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    اگر(a.exp >= 0) بازگشت a.mant <<  a.exp ;
    وگرنه           بازگشت a.mant >>(-a.exp);
}

/** Divide a by b. b should not be zero.
 *  @return normalized result
 */
ایستا درونخطی SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, exp, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_BITS) / (b.mant| 0x00800000UL));
    exp  = a.exp - b.exp;
    بازگشت av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, exp});
}

/** Multiply a with b
 *  #return normalized result
 */
ایستا درونخطی SoftFloat_IEEE754 av_mul_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t sign, mant, exp;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_BITS);
    exp  = a.exp + b.exp;
    بازگشت av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, exp});
}

/** Compare a with b strictly
 *  @returns 1 if the a and b are equal, 0 otherwise.
 */
ایستا درونخطی صحیح av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    اگر (a.sign != b.sign) بازگشت 0;
    اگر (a.mant != b.mant) بازگشت 0;
    اگر (a.exp  != b.exp ) بازگشت 0;
    بازگشت 1;
}

#endif /*AVUTIL_SOFTFLOAT_IEEE754_H*/
