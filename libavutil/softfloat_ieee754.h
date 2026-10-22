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

#నిర్వచితం_కాకపోతే AVUTIL_SOFTFLOAT_IEEE754_H
#నిర్వచించు AVUTIL_SOFTFLOAT_IEEE754_H

#అన్తర్భావ <stdint.h>

#నిర్వచించు EXP_BIAS 127
#నిర్వచించు MANT_బిట్లు 23

రకనిర్వచనం నిర్మాణం SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  ఘాతాంకం;
} SoftFloat_IEEE754;

స్థిర స్థిరరాశి SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
స్థిర స్థిరరాశి SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

/** Normalize the softfloat as defined by IEEE 754 single-recision floating
 *  point specification
 */
స్థిర అంతఃవరుస SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    అయితే( sf.mant >= 0x1000000UL ) {
        sf.ఘాతాంకం++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    తిరిగి sf;
}

/** Convert integer to softfloat.
 *  @return softfloat with value n * 2^e
 */
స్థిర అంతఃవరుస SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, పూర్ణాంకం e) {
    పూర్ణాంకం sign = 0;

    ఒకవేళ (n < 0) {
        sign = 1;
        n    *= -1;
    }
    తిరిగి av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_బిట్లు, 0 + e});
}

/** Make a softfloat out of the bitstream. Assumes the bits are in the form as defined
 *  by the IEEE 754 spec.
 */
స్థిర అంతఃవరుస SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    తిరిగి ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

/** Convert the softfloat to integer
 */
స్థిర అంతఃవరుస పూర్ణాంకం av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    ఒకవేళ(a.ఘాతాంకం >= 0) తిరిగి a.mant <<  a.ఘాతాంకం ;
    లేకపోతే           తిరిగి a.mant >>(-a.ఘాతాంకం);
}

/** Divide a by b. b should not be zero.
 *  @return normalized result
 */
స్థిర అంతఃవరుస SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, ఘాతాంకం, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_బిట్లు) / (b.mant| 0x00800000UL));
    ఘాతాంకం  = a.ఘాతాంకం - b.ఘాతాంకం;
    తిరిగి av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, ఘాతాంకం});
}

/** Multiply a with b
 *  #return normalized result
 */
స్థిర అంతఃవరుస SoftFloat_IEEE754 av_mul_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t sign, mant, ఘాతాంకం;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_బిట్లు);
    ఘాతాంకం  = a.ఘాతాంకం + b.ఘాతాంకం;
    తిరిగి av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, ఘాతాంకం});
}

/** Compare a with b strictly
 *  @returns 1 if the a and b are equal, 0 otherwise.
 */
స్థిర అంతఃవరుస పూర్ణాంకం av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    ఒకవేళ (a.sign != b.sign) తిరిగి 0;
    ఒకవేళ (a.mant != b.mant) తిరిగి 0;
    ఒకవేళ (a.ఘాతాంకం  != b.ఘాతాంకం ) తిరిగి 0;
    తిరిగి 1;
}

#అయితే_ముగింపు /*AVUTIL_SOFTFLOAT_IEEE754_H*/
