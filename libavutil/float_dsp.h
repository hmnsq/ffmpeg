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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_FLOAT_DSP_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_FLOAT_DSP_H

#ಅನ್ತರ್ಭಾವ <stddef.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVFloatDSPContext {
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
    ಶೂನ್ಯ (*ಸದಿಶ_fmul)(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                        ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_fmac_scalar)(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                               ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_dmac_scalar)(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                               ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_fmul_scalar)(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                               ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_dmul_scalar)(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                               ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_fmul_ಕಿಟಕಿ)(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                               ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *win, ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_fmul_ಕೂಡಿಸು)(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ)(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);

    /**
     * Calculate the sum and difference of two vectors of floats.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    ಶೂನ್ಯ (*butterflies_float)(ದಶಮಾಂಶ *ಸೀಮಿತ v1, ದಶಮಾಂಶ *ಸೀಮಿತ v2, ಪೂರ್ಣಾಂಕ len);

    /**
     * Calculate the scalar product of two vectors of floats.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    ದಶಮಾಂಶ (*scalarproduct_float)(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len);

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
    ಶೂನ್ಯ (*ಸದಿಶ_dmul)(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src0, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src1,
                        ಪೂರ್ಣಾಂಕ len);

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
    ದ್ವಿಗುಣ (*scalarproduct_double)(ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v1, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v2,
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
ದಶಮಾಂಶ ff_scalarproduct_float_c(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len);

/**
 * Return the scalar product of two vectors of doubles.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return inner product of the vectors
 */
ದ್ವಿಗುಣ ff_scalarproduct_double_c(ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v1, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v2,
                                 size_t len);

ಶೂನ್ಯ ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_arm(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, ಪೂರ್ಣಾಂಕ strict);
ಶೂನ್ಯ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp);
ಶೂನ್ಯ ff_float_dsp_init_mips(AVFloatDSPContext *fdsp);

/**
 * Allocate a float DSP context.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFloatDSPContext *avpriv_float_dsp_alloc(ಪೂರ್ಣಾಂಕ strict);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_FLOAT_DSP_H */
