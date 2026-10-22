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

#నిర్వచితం_కాకపోతే AVUTIL_FLOAT_DSP_H
#నిర్వచించు AVUTIL_FLOAT_DSP_H

#అన్తర్భావ <stddef.h>

రకనిర్వచనం నిర్మాణం AVFloatDSPContext {
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
    శూన్య (*సదిశ_fmul)(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                        పూర్ణాంకం len);

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
    శూన్య (*సదిశ_fmac_scalar)(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                               పూర్ణాంకం len);

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
    శూన్య (*సదిశ_dmac_scalar)(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                               పూర్ణాంకం len);

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
    శూన్య (*సదిశ_fmul_scalar)(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                               పూర్ణాంకం len);

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
    శూన్య (*సదిశ_dmul_scalar)(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                               పూర్ణాంకం len);

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
    శూన్య (*సదిశ_fmul_కిటికీ)(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                               స్థిరరాశి దశాంశం *src1, స్థిరరాశి దశాంశం *win, పూర్ణాంకం len);

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
    శూన్య (*సదిశ_fmul_కూడు)(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                            స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len);

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
    శూన్య (*సదిశ_fmul_తిరగేయి)(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);

    /**
     * Calculate the sum and difference of two vectors of floats.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    శూన్య (*butterflies_float)(దశాంశం *పరిమిత v1, దశాంశం *పరిమిత v2, పూర్ణాంకం len);

    /**
     * Calculate the scalar product of two vectors of floats.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    దశాంశం (*scalarproduct_float)(స్థిరరాశి దశాంశం *v1, స్థిరరాశి దశాంశం *v2, పూర్ణాంకం len);

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
    శూన్య (*సదిశ_dmul)(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src0, స్థిరరాశి ద్విగుణ *src1,
                        పూర్ణాంకం len);

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
    ద్విగుణ (*scalarproduct_double)(స్థిరరాశి ద్విగుణ *v1, స్థిరరాశి ద్విగుణ *v2,
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
దశాంశం ff_scalarproduct_float_c(స్థిరరాశి దశాంశం *v1, స్థిరరాశి దశాంశం *v2, పూర్ణాంకం len);

/**
 * Return the scalar product of two vectors of doubles.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return inner product of the vectors
 */
ద్విగుణ ff_scalarproduct_double_c(స్థిరరాశి ద్విగుణ *v1, స్థిరరాశి ద్విగుణ *v2,
                                 size_t len);

శూన్య ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp);
శూన్య ff_float_dsp_init_arm(AVFloatDSPContext *fdsp);
శూన్య ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, పూర్ణాంకం strict);
శూన్య ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp);
శూన్య ff_float_dsp_init_x86(AVFloatDSPContext *fdsp);
శూన్య ff_float_dsp_init_mips(AVFloatDSPContext *fdsp);

/**
 * Allocate a float DSP context.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFloatDSPContext *avpriv_float_dsp_alloc(పూర్ణాంకం strict);

#అయితే_ముగింపు /* AVUTIL_FLOAT_DSP_H */
