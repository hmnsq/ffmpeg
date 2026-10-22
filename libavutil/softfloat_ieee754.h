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

#اگر_غیر_تعریف_شدہ AVUTIL_SOFTFLOAT_IEEE754_H
#تعریف_کرو AVUTIL_SOFTFLOAT_IEEE754_H

#شامل <stdint.h>

#تعریف_کرو EXP_BIAS 127
#تعریف_کرو MANT_بٹ 23

قسمتعریف ساخت SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  قوت_نما;
} SoftFloat_IEEE754;

ساکن ثابت SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
ساکن ثابت SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

/** Normalize the softfloat as defined by IEEE 754 single-recision floating
 *  point specification
 */
ساکن اندرونی SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    جب( sf.mant >= 0x1000000UL ) {
        sf.قوت_نما++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    واپس sf;
}

/** Convert integer to softfloat.
 *  @return softfloat with value n * 2^e
 */
ساکن اندرونی SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, صحیح e) {
    صحیح sign = 0;

    اگر (n < 0) {
        sign = 1;
        n    *= -1;
    }
    واپس av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_بٹ, 0 + e});
}

/** Make a softfloat out of the bitstream. Assumes the bits are in the form as defined
 *  by the IEEE 754 spec.
 */
ساکن اندرونی SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    واپس ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

/** Convert the softfloat to integer
 */
ساکن اندرونی صحیح av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    اگر(a.قوت_نما >= 0) واپس a.mant <<  a.قوت_نما ;
    ورنہ           واپس a.mant >>(-a.قوت_نما);
}

/** Divide a by b. b should not be zero.
 *  @return normalized result
 */
ساکن اندرونی SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, قوت_نما, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_بٹ) / (b.mant| 0x00800000UL));
    قوت_نما  = a.قوت_نما - b.قوت_نما;
    واپس av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, قوت_نما});
}

/** Multiply a with b
 *  #return normalized result
 */
ساکن اندرونی SoftFloat_IEEE754 av_mul_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t sign, mant, قوت_نما;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_بٹ);
    قوت_نما  = a.قوت_نما + b.قوت_نما;
    واپس av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, قوت_نما});
}

/** Compare a with b strictly
 *  @returns 1 if the a and b are equal, 0 otherwise.
 */
ساکن اندرونی صحیح av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    اگر (a.sign != b.sign) واپس 0;
    اگر (a.mant != b.mant) واپس 0;
    اگر (a.قوت_نما  != b.قوت_نما ) واپس 0;
    واپس 1;
}

#اگر_ختم /*AVUTIL_SOFTFLOAT_IEEE754_H*/
