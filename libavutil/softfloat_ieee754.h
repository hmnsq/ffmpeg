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

#اگر_تعریف_نشده AVUTIL_SOFTFLOAT_IEEE754_H
#تعریف_کن AVUTIL_SOFTFLOAT_IEEE754_H

#ضمن <stdint.h>

#تعریف_کن EXP_BIAS 127
#تعریف_کن MANT_بیتها 23

تعريفنوع بنية SoftFloat_IEEE754 {
    int32_t sign;
    uint64_t mant;
    int32_t  نمایی_تابع;
} SoftFloat_IEEE754;

ساكن ثابت SoftFloat_IEEE754 FLOAT_0 = {0, 0, -126};
ساكن ثابت SoftFloat_IEEE754 FLOAT_1 = {0, 0,    0};

/** Normalize the softfloat as defined by IEEE 754 single-recision floating
 *  point specification
 */
ساكن مضمن SoftFloat_IEEE754 av_normalize_sf_ieee754(SoftFloat_IEEE754 sf) {
    طالما( sf.mant >= 0x1000000UL ) {
        sf.نمایی_تابع++;
        sf.mant >>= 1;
    }
    sf.mant &= 0x007fffffUL;
    أرجع sf;
}

/** Convert integer to softfloat.
 *  @return softfloat with value n * 2^e
 */
ساكن مضمن SoftFloat_IEEE754 av_int2sf_ieee754(int64_t n, صحيح e) {
    صحيح sign = 0;

    إذا (n < 0) {
        sign = 1;
        n    *= -1;
    }
    أرجع av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, n << MANT_بیتها, 0 + e});
}

/** Make a softfloat out of the bitstream. Assumes the bits are in the form as defined
 *  by the IEEE 754 spec.
 */
ساكن مضمن SoftFloat_IEEE754 av_bits2sf_ieee754(uint32_t n) {
    أرجع ((SoftFloat_IEEE754) { (n & 0x80000000UL) >> 31, (n & 0x7FFFFFUL), (int8_t)((n & 0x7F800000UL) >> 23)});
}

/** Convert the softfloat to integer
 */
ساكن مضمن صحيح av_sf2int_ieee754(SoftFloat_IEEE754 a) {
    إذا(a.نمایی_تابع >= 0) أرجع a.mant <<  a.نمایی_تابع ;
    وإلا           أرجع a.mant >>(-a.نمایی_تابع);
}

/** Divide a by b. b should not be zero.
 *  @return normalized result
 */
ساكن مضمن SoftFloat_IEEE754 av_div_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t mant, نمایی_تابع, sign;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = ((((uint64_t) (a.mant | 0x00800000UL)) << MANT_بیتها) / (b.mant| 0x00800000UL));
    نمایی_تابع  = a.نمایی_تابع - b.نمایی_تابع;
    أرجع av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, نمایی_تابع});
}

/** Multiply a with b
 *  #return normalized result
 */
ساكن مضمن SoftFloat_IEEE754 av_mul_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    int32_t sign, mant, نمایی_تابع;
    a    = av_normalize_sf_ieee754(a);
    b    = av_normalize_sf_ieee754(b);
    sign = a.sign ^ b.sign;
    mant = (((uint64_t)(a.mant|0x00800000UL) * (uint64_t)(b.mant|0x00800000UL))>>MANT_بیتها);
    نمایی_تابع  = a.نمایی_تابع + b.نمایی_تابع;
    أرجع av_normalize_sf_ieee754((SoftFloat_IEEE754) {sign, mant, نمایی_تابع});
}

/** Compare a with b strictly
 *  @returns 1 if the a and b are equal, 0 otherwise.
 */
ساكن مضمن صحيح av_cmp_sf_ieee754(SoftFloat_IEEE754 a, SoftFloat_IEEE754 b) {
    a = av_normalize_sf_ieee754(a);
    b = av_normalize_sf_ieee754(b);
    إذا (a.sign != b.sign) أرجع 0;
    إذا (a.mant != b.mant) أرجع 0;
    إذا (a.نمایی_تابع  != b.نمایی_تابع ) أرجع 0;
    أرجع 1;
}

#پایان_اگر /*AVUTIL_SOFTFLOAT_IEEE754_H*/
