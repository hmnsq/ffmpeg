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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_SOFTFLOAT_IEEE754_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_SOFTFLOAT_IEEE754_H

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ವ್ಯಾಖ್ಯಾನಿಸು EXP_BIAS 127
#ವ್ಯಾಖ್ಯಾನಿಸು MANT_ಬಿಟ್ಟುಗಳು 23

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  ಘಾತಾಂಕ;
} SoftFloat_IEEE754;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

/** Normalize the softfloat as defined by IEEE 754 single-recision floating
 *  point specification
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    ಆಗ( sf.mant >= 0x1000000UL ) {
        sf.ಘಾತಾಂಕ++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    ಹಿಂತಿರುಗಿ sf;
}

/** Convert integer to softfloat.
 *  @return softfloat with value n * 2^e
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, ಪೂರ್ಣಾಂಕ e) {
    ಪೂರ್ಣಾಂಕ sign = 0;

    ಆದರೆ (n < 0) {
        sign = 1;
        n    *= -1;
    }
    ಹಿಂತಿರುಗಿ av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_ಬಿಟ್ಟುಗಳು, 0 + e});
}

/** Make a softfloat out of the bitstream. Assumes the bits are in the form as defined
 *  by the IEEE 754 spec.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    ಹಿಂತಿರುಗಿ ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

/** Convert the softfloat to integer
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    ಆದರೆ(a.ಘಾತಾಂಕ >= 0) ಹಿಂತಿರುಗಿ a.mant <<  a.ಘಾತಾಂಕ ;
    ಇಲ್ಲದಿದ್ದರೆ           ಹಿಂತಿರುಗಿ a.mant >>(-a.ಘಾತಾಂಕ);
}

/** Divide a by b. b should not be zero.
 *  @return normalized result
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, ಘಾತಾಂಕ, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_ಬಿಟ್ಟುಗಳು) / (b.mant| 0x00800000UL));
    ಘಾತಾಂಕ  = a.ಘಾತಾಂಕ - b.ಘಾತಾಂಕ;
    ಹಿಂತಿರುಗಿ av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, ಘಾತಾಂಕ});
}

/** Multiply a with b
 *  #return normalized result
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ SoftFloat_IEEE754 av_mul_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t sign, mant, ಘಾತಾಂಕ;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_ಬಿಟ್ಟುಗಳು);
    ಘಾತಾಂಕ  = a.ಘಾತಾಂಕ + b.ಘಾತಾಂಕ;
    ಹಿಂತಿರುಗಿ av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, ಘಾತಾಂಕ});
}

/** Compare a with b strictly
 *  @returns 1 if the a and b are equal, 0 otherwise.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    ಆದರೆ (a.sign != b.sign) ಹಿಂತಿರುಗಿ 0;
    ಆದರೆ (a.mant != b.mant) ಹಿಂತಿರುಗಿ 0;
    ಆದರೆ (a.ಘಾತಾಂಕ  != b.ಘಾತಾಂಕ ) ಹಿಂತಿರುಗಿ 0;
    ಹಿಂತಿರುಗಿ 1;
}

#ಆದರೆ_ಅಂತ್ಯ /*AVUTIL_SOFTFLOAT_IEEE754_H*/
