/*
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

#ifndef AVUTIL_FLOAT_DSP_H
#define AVUTIL_FLOAT_DSP_H

#অন্তর্ভাব <stddef.h>

প্রকারনির্দেশ সংরচনা AVFloatDSPContext {
    /**
     * Calculate the entry wise product of two vectors of floats and store the result in
     * a vector of floats.
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
    শূন্য (*vector_fmul)(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                        পূর্ণাঙ্ক len);

    /**
     * Multiply a vector of floats by a scalar float and add to
     * destination vector.  Source and destination vectors must
     * overlap exactly or not at all.
     *
     * @param dst result vector
     *            constraints: 32-byte aligned
     * @param src input vector
     *            constraints: 32-byte aligned
     * @param mul scalar value
     * @param len length of vector
     *            constraints: multiple of 16
     */
    শূন্য (*vector_fmac_scalar)(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                               পূর্ণাঙ্ক len);

    /**
     * Multiply a vector of doubles by a scalar double and add to
     * destination vector.  Source and destination vectors must
     * overlap exactly or not at all.
     *
     * @param dst result vector
     *            constraints: 32-byte aligned
     * @param src input vector
     *            constraints: 32-byte aligned
     * @param mul scalar value
     * @param len length of vector
     *            constraints: multiple of 16
     */
    শূন্য (*vector_dmac_scalar)(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                               পূর্ণাঙ্ক len);

    /**
     * Multiply a vector of floats by a scalar float.  Source and
     * destination vectors must overlap exactly or not at all.
     *
     * @param dst result vector
     *            constraints: 16-byte aligned
     * @param src input vector
     *            constraints: 16-byte aligned
     * @param mul scalar value
     * @param len length of vector
     *            constraints: multiple of 4
     */
    শূন্য (*vector_fmul_scalar)(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                               পূর্ণাঙ্ক len);

    /**
     * Multiply a vector of double by a scalar double.  Source and
     * destination vectors must overlap exactly or not at all.
     *
     * @param dst result vector
     *            constraints: 32-byte aligned
     * @param src input vector
     *            constraints: 32-byte aligned
     * @param mul scalar value
     * @param len length of vector
     *            constraints: multiple of 8
     */
    শূন্য (*vector_dmul_scalar)(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                               পূর্ণাঙ্ক len);

    /**
     * Overlap/add with window function.
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
     */
    শূন্য (*vector_fmul_window)(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                               ধ্রুব ভিন্ন *src1, ধ্রুব ভিন্ন *win, পূর্ণাঙ্ক len);

    /**
     * Calculate the entry wise product of two vectors of floats, add a third vector of
     * floats and store the result in a vector of floats.
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
    শূন্য (*vector_fmul_add)(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                            ধ্রুব ভিন্ন *src2, পূর্ণাঙ্ক len);

    /**
     * Calculate the entry wise product of two vectors of floats, and store the result
     * in a vector of floats. The second vector of floats is iterated over
     * in reverse order.
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
    শূন্য (*vector_fmul_reverse)(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                                ধ্রুব ভিন্ন *src1, পূর্ণাঙ্ক len);

    /**
     * Calculate the sum and difference of two vectors of floats.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    শূন্য (*butterflies_float)(ভিন্ন *restrict v1, ভিন্ন *restrict v2, পূর্ণাঙ্ক len);

    /**
     * Calculate the scalar product of two vectors of floats.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    ভিন্ন (*scalarproduct_float)(ধ্রুব ভিন্ন *v1, ধ্রুব ভিন্ন *v2, পূর্ণাঙ্ক len);

    /**
     * Calculate the entry wise product of two vectors of doubles and store the result in
     * a vector of doubles.
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
    শূন্য (*vector_dmul)(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src0, ধ্রুব দ্বিগুণ *src1,
                        পূর্ণাঙ্ক len);

    /**
     * Calculate the scalar product of two vectors of doubles.
     *
     * @param v1  first vector
     *            constraints: 32-byte aligned
     * @param v2  second vector
     *            constraints: 32-byte aligned
     * @param len length of vectors
     *            constraints: multiple of 16
     *
     * @return inner product of the vectors
     */
    দ্বিগুণ (*scalarproduct_double)(ধ্রুব দ্বিগুণ *v1, ধ্রুব দ্বিগুণ *v2,
                                   size_t len);
} AVFloatDSPContext;

/**
 * Return the scalar product of two vectors of floats.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return sum of elementwise products
 */
ভিন্ন ff_scalarproduct_float_c(ধ্রুব ভিন্ন *v1, ধ্রুব ভিন্ন *v2, পূর্ণাঙ্ক len);

/**
 * Return the scalar product of two vectors of doubles.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return inner product of the vectors
 */
দ্বিগুণ ff_scalarproduct_double_c(ধ্রুব দ্বিগুণ *v1, ধ্রুব দ্বিগুণ *v2,
                                 size_t len);

শূন্য ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp);
শূন্য ff_float_dsp_init_arm(AVFloatDSPContext *fdsp);
শূন্য ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, পূর্ণাঙ্ক strict);
শূন্য ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp);
শূন্য ff_float_dsp_init_x86(AVFloatDSPContext *fdsp);
শূন্য ff_float_dsp_init_mips(AVFloatDSPContext *fdsp);

/**
 * Allocate a float DSP context.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFloatDSPContext *avpriv_float_dsp_alloc(পূর্ণাঙ্ক strict);

#endif /* AVUTIL_FLOAT_DSP_H */
