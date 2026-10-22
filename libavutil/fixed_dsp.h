/*
 * Copyright (c) 2012
 *      MIPS Technologies, Inc., California.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the MIPS Technologies, Inc., nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE MIPS TECHNOLOGIES, INC. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE MIPS TECHNOLOGIES, INC. BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Author:  Nedeljko Babic (nbabic@mips.com)
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

#اگر_غیر_تعریف_شدہ AVUTIL_FIXED_DSP_H
#تعریف_کرو AVUTIL_FIXED_DSP_H

#شامل <stdint.h>
#شامل "attributes.h"
#شامل "libavcodec/mathops.h"

قسمتعریف ساخت AVFixedDSPContext {
    /* Assume len is a multiple of 16, and arrays are 32-byte aligned */
    /* Results of multiplications are scaled down by 31 bit (and rounded) if not
     * stated otherwise */

    /**
     * Overlap/add with window function.
     * Result is scaled down by "bits" bits.
     * Used primarily by MDCT-based audio codecs.
     * Source and destination vectors must overlap exactly or not at all.
     *
     * @param dst  result vector
     *             constraints: 16-byte aligned
     * @param src0 first source vector
     *             constraints: 16-byte aligned
     * @param src1 second source vector
     *             constraints: 16-byte aligned
     * @param win  half-window vector
     *             constraints: 16-byte aligned
     * @param len  length of vector
     *             constraints: multiple of 4
     * @param bits scaling parameter
     *
     */
    خالی (*سمتیہ_fmul_کھڑکی_scaled)(int16_t *dst, ثابت int32_t *src0, ثابت int32_t *src1, ثابت int32_t *win, صحیح len, uint8_t بٹ);

    /**
     * Overlap/add with window function.
     * Used primarily by MDCT-based audio codecs.
     * Source and destination vectors must overlap exactly or not at all.
     *
     * @param dst  result vector
     *             constraints: 32-byte aligned
     * @param src0 first source vector
     *             constraints: 16-byte aligned
     * @param src1 second source vector
     *             constraints: 16-byte aligned
     * @param win  half-window vector
     *             constraints: 16-byte aligned
     * @param len  length of vector
     *             constraints: multiple of 4
     */
    خالی (*سمتیہ_fmul_کھڑکی)(int32_t *dst, ثابت int32_t *src0, ثابت int32_t *src1, ثابت int32_t *win, صحیح len);

    /**
     * Fixed-point multiplication that calculates the entry wise product of two
     * vectors of integers and stores the result in a vector of integers.
     *
     * @param dst  output vector
     *             constraints: 32-byte aligned
     * @param src0 first input vector
     *             constraints: 32-byte aligned
     * @param src1 second input vector
     *             constraints: 32-byte aligned
     * @param len  number of elements in the input
     *             constraints: multiple of 16
     */
    خالی (*سمتیہ_fmul)(صحیح *dst, ثابت صحیح *src0, ثابت صحیح *src1,
                        صحیح len);

    خالی (*سمتیہ_fmul_الٹ)(صحیح *dst, ثابت صحیح *src0, ثابت صحیح *src1, صحیح len);
    /**
     * Calculate the entry wise product of two vectors of integers, add a third vector of
     * integers and store the result in a vector of integers.
     *
     * @param dst  output vector
     *             constraints: 32-byte aligned
     * @param src0 first input vector
     *             constraints: 32-byte aligned
     * @param src1 second input vector
     *             constraints: 32-byte aligned
     * @param src2 third input vector
     *             constraints: 32-byte aligned
     * @param len  number of elements in the input
     *             constraints: multiple of 16
     */
    خالی (*سمتیہ_fmul_جوڑو)(صحیح *dst, ثابت صحیح *src0, ثابت صحیح *src1,
                            ثابت صحیح *src2, صحیح len);

    /**
     * Calculate the scalar product of two vectors of integers.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    صحیح (*scalarproduct_fixed)(ثابت صحیح *v1, ثابت صحیح *v2, صحیح len);

    /**
     * Calculate the sum and difference of two vectors of integers.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    خالی (*butterflies_fixed)(صحیح *محدود v1, صحیح *محدود v2, صحیح len);
} AVFixedDSPContext;

/**
 * Allocate and initialize a fixed DSP context.
 * note: should be freed with a av_free call when no longer needed.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFixedDSPContext * avpriv_alloc_fixed_dsp(صحیح strict);

خالی ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp);
خالی ff_fixed_dsp_init_x86(AVFixedDSPContext *fdsp);

/**
 * Calculate the square root
 *
 * @param x    input fixed point number
 *
 * @param bits format of fixed point number (32 - bits).bits
 *
 * note: input is normalized to (0, 1) fixed point value
 */

ساکن av_always_inline صحیح fixed_sqrt(صحیح x, صحیح بٹ)
{
    صحیح retval, ثنائی_ہندسہ_نقاب, guess, مربع, i;
    int64_t accu;
    صحیح shift1 = 30 - بٹ;
    صحیح shift2 = بٹ - 15;

    اگر (shift1 > 0) retval = ff_sqrt(x << shift1);
    ورنہ retval = ff_sqrt(x >> -shift1);

    اگر (shift2 > 0) {
        retval = retval << shift2;
        ثنائی_ہندسہ_نقاب = (1 << (shift2 - 1));

        برائے (i=0; i<shift2; i++){
            guess = retval + ثنائی_ہندسہ_نقاب;
            accu = (int64_t)guess * guess;
            مربع = (صحیح)((accu + ثنائی_ہندسہ_نقاب) >> بٹ);
            اگر (x >= مربع)
                retval += ثنائی_ہندسہ_نقاب;
            ثنائی_ہندسہ_نقاب >>= 1;
        }

    }
    ورنہ retval >>= (-shift2);

    واپس retval;
}

#اگر_ختم /* AVUTIL_FIXED_DSP_H */
