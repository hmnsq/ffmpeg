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

#अगर_अघोषित AVUTIL_FLOAT_DSP_H
#घोषणा AVUTIL_FLOAT_DSP_H

#समावेश <stddef.h>

प्रकार काष्ठा AVFloatDSPContext {
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
    व्योम (*vector_fmul)(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                        पूर्णांक len);

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
    व्योम (*vector_fmac_scalar)(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                               पूर्णांक len);

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
    व्योम (*vector_dmac_scalar)(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                               पूर्णांक len);

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
    व्योम (*vector_fmul_scalar)(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                               पूर्णांक len);

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
    व्योम (*vector_dmul_scalar)(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                               पूर्णांक len);

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
    व्योम (*vector_fmul_window)(भग्न *dst, स्थिर भग्न *src0,
                               स्थिर भग्न *src1, स्थिर भग्न *win, पूर्णांक len);

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
    व्योम (*vector_fmul_add)(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                            स्थिर भग्न *src2, पूर्णांक len);

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
    व्योम (*vector_fmul_reverse)(भग्न *dst, स्थिर भग्न *src0,
                                स्थिर भग्न *src1, पूर्णांक len);

    /**
     * Calculate the sum and difference of two vectors of floats.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    व्योम (*butterflies_float)(भग्न *restrict v1, भग्न *restrict v2, पूर्णांक len);

    /**
     * Calculate the scalar product of two vectors of floats.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    भग्न (*scalarproduct_float)(स्थिर भग्न *v1, स्थिर भग्न *v2, पूर्णांक len);

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
    व्योम (*vector_dmul)(द्विगुन *dst, स्थिर द्विगुन *src0, स्थिर द्विगुन *src1,
                        पूर्णांक len);

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
    द्विगुन (*scalarproduct_double)(स्थिर द्विगुन *v1, स्थिर द्विगुन *v2,
                                   माप_प्रकार len);
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
भग्न ff_scalarproduct_float_c(स्थिर भग्न *v1, स्थिर भग्न *v2, पूर्णांक len);

/**
 * Return the scalar product of two vectors of doubles.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return inner product of the vectors
 */
द्विगुन ff_scalarproduct_double_c(स्थिर द्विगुन *v1, स्थिर द्विगुन *v2,
                                 माप_प्रकार len);

व्योम ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp);
व्योम ff_float_dsp_init_arm(AVFloatDSPContext *fdsp);
व्योम ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, पूर्णांक strict);
व्योम ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp);
व्योम ff_float_dsp_init_x86(AVFloatDSPContext *fdsp);
व्योम ff_float_dsp_init_mips(AVFloatDSPContext *fdsp);

/**
 * Allocate a float DSP context.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFloatDSPContext *avpriv_float_dsp_alloc(पूर्णांक strict);

#पूर्ण_अगर /* AVUTIL_FLOAT_DSP_H */
