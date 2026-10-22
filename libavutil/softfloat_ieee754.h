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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_SOFTFLOAT_IEEE754_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_SOFTFLOAT_IEEE754_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXP_BIAS 127
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MANT_ਬਿੱਟ 23

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  ਘਾਤਾਂਕ;
} SoftFloat_IEEE754;

ਸਥਿਰ ਅਚਲ SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
ਸਥਿਰ ਅਚਲ SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

/** Normalize the softfloat as defined by IEEE 754 single-recision floating
 *  point specification
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    ਜਦੋਂ( sf.mant >= 0x1000000UL ) {
        sf.ਘਾਤਾਂਕ++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    ਵਾਪਸ sf;
}

/** Convert integer to softfloat.
 *  @return softfloat with value n * 2^e
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, ਪੂਰਨ e) {
    ਪੂਰਨ sign = 0;

    ਜੇ (n < 0) {
        sign = 1;
        n    *= -1;
    }
    ਵਾਪਸ av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_ਬਿੱਟ, 0 + e});
}

/** Make a softfloat out of the bitstream. Assumes the bits are in the form as defined
 *  by the IEEE 754 spec.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    ਵਾਪਸ ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

/** Convert the softfloat to integer
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    ਜੇ(a.ਘਾਤਾਂਕ >= 0) ਵਾਪਸ a.mant <<  a.ਘਾਤਾਂਕ ;
    ਨਹੀਂਤਾਂ           ਵਾਪਸ a.mant >>(-a.ਘਾਤਾਂਕ);
}

/** Divide a by b. b should not be zero.
 *  @return normalized result
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, ਘਾਤਾਂਕ, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_ਬਿੱਟ) / (b.mant| 0x00800000UL));
    ਘਾਤਾਂਕ  = a.ਘਾਤਾਂਕ - b.ਘਾਤਾਂਕ;
    ਵਾਪਸ av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, ਘਾਤਾਂਕ});
}

/** Multiply a with b
 *  #return normalized result
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ SoftFloat_IEEE754 av_mul_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t sign, mant, ਘਾਤਾਂਕ;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_ਬਿੱਟ);
    ਘਾਤਾਂਕ  = a.ਘਾਤਾਂਕ + b.ਘਾਤਾਂਕ;
    ਵਾਪਸ av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, ਘਾਤਾਂਕ});
}

/** Compare a with b strictly
 *  @returns 1 if the a and b are equal, 0 otherwise.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    ਜੇ (a.sign != b.sign) ਵਾਪਸ 0;
    ਜੇ (a.mant != b.mant) ਵਾਪਸ 0;
    ਜੇ (a.ਘਾਤਾਂਕ  != b.ਘਾਤਾਂਕ ) ਵਾਪਸ 0;
    ਵਾਪਸ 1;
}

#ਜੇ_ਅੰਤ /*AVUTIL_SOFTFLOAT_IEEE754_H*/
