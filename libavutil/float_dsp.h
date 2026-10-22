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

#ಅನ್ತರ್ಭಾವ <stddef.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVFloatDSPContext {
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
    ಶೂನ್ಯ (*vector_fmul)(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                        ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_fmac_scalar)(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_dmac_scalar)(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_fmul_scalar)(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_dmul_scalar)(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_fmul_window)(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                               ಧ್ರುವ ಭಿನ್ನ *src1, ಧ್ರುವ ಭಿನ್ನ *win, ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_fmul_add)(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                            ಧ್ರುವ ಭಿನ್ನ *src2, ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_fmul_reverse)(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len);

    /**
     * Calculate the sum and difference of two vectors of floats.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    ಶೂನ್ಯ (*butterflies_float)(ಭಿನ್ನ *restrict v1, ಭಿನ್ನ *restrict v2, ಪೂರ್ಣಾಙ್ಕ len);

    /**
     * Calculate the scalar product of two vectors of floats.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    ಭಿನ್ನ (*scalarproduct_float)(ಧ್ರುವ ಭಿನ್ನ *v1, ಧ್ರುವ ಭಿನ್ನ *v2, ಪೂರ್ಣಾಙ್ಕ len);

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
    ಶೂನ್ಯ (*vector_dmul)(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src0, ಧ್ರುವ ದ್ವಿಗುಣ *src1,
                        ಪೂರ್ಣಾಙ್ಕ len);

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
    ದ್ವಿಗುಣ (*scalarproduct_double)(ಧ್ರುವ ದ್ವಿಗುಣ *v1, ಧ್ರುವ ದ್ವಿಗುಣ *v2,
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
ಭಿನ್ನ ff_scalarproduct_float_c(ಧ್ರುವ ಭಿನ್ನ *v1, ಧ್ರುವ ಭಿನ್ನ *v2, ಪೂರ್ಣಾಙ್ಕ len);

/**
 * Return the scalar product of two vectors of doubles.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return inner product of the vectors
 */
ದ್ವಿಗುಣ ff_scalarproduct_double_c(ಧ್ರುವ ದ್ವಿಗುಣ *v1, ಧ್ರುವ ದ್ವಿಗುಣ *v2,
                                 size_t len);

ಶೂನ್ಯ ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_arm(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, ಪೂರ್ಣಾಙ್ಕ strict);
ಶೂನ್ಯ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_mips(AVFloatDSPContext *fdsp);

/**
 * Allocate a float DSP context.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFloatDSPContext *avpriv_float_dsp_alloc(ಪೂರ್ಣಾಙ್ಕ strict);

#endif /* AVUTIL_FLOAT_DSP_H */
