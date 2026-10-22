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

#അന്തര്ഭാവ <stddef.h>

തരനിർവചനം ഘടന AVFloatDSPContext {
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
    ശൂന്യം (*vector_fmul)(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                        പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_fmac_scalar)(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                               പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_dmac_scalar)(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                               പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_fmul_scalar)(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                               പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_dmul_scalar)(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                               പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_fmul_window)(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                               സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win, പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_fmul_add)(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                            സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_fmul_reverse)(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);

    /**
     * Calculate the sum and difference of two vectors of floats.
     *
     * @param v1  first input vector, sum output, 16-byte aligned
     * @param v2  second input vector, difference output, 16-byte aligned
     * @param len length of vectors, multiple of 4
     */
    ശൂന്യം (*butterflies_float)(ദശാംശം *restrict v1, ദശാംശം *restrict v2, പൂർണ്ണസംഖ്യ len);

    /**
     * Calculate the scalar product of two vectors of floats.
     *
     * @param v1  first vector, 16-byte aligned
     * @param v2  second vector, 16-byte aligned
     * @param len length of vectors, multiple of 4
     *
     * @return sum of elementwise products
     */
    ദശാംശം (*scalarproduct_float)(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ len);

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
    ശൂന്യം (*vector_dmul)(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src0, സ്ഥിരം ഇരട്ട *src1,
                        പൂർണ്ണസംഖ്യ len);

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
    ഇരട്ട (*scalarproduct_double)(സ്ഥിരം ഇരട്ട *v1, സ്ഥിരം ഇരട്ട *v2,
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
ദശാംശം ff_scalarproduct_float_c(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ len);

/**
 * Return the scalar product of two vectors of doubles.
 *
 * @param v1  first input vector
 * @param v2  first input vector
 * @param len number of elements
 *
 * @return inner product of the vectors
 */
ഇരട്ട ff_scalarproduct_double_c(സ്ഥിരം ഇരട്ട *v1, സ്ഥിരം ഇരട്ട *v2,
                                 size_t len);

ശൂന്യം ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp);
ശൂന്യം ff_float_dsp_init_arm(AVFloatDSPContext *fdsp);
ശൂന്യം ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, പൂർണ്ണസംഖ്യ strict);
ശൂന്യം ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp);
ശൂന്യം ff_float_dsp_init_x86(AVFloatDSPContext *fdsp);
ശൂന്യം ff_float_dsp_init_mips(AVFloatDSPContext *fdsp);

/**
 * Allocate a float DSP context.
 *
 * @param strict  setting to non-zero avoids using functions which may not be IEEE-754 compliant
 */
AVFloatDSPContext *avpriv_float_dsp_alloc(പൂർണ്ണസംഖ്യ strict);

#endif /* AVUTIL_FLOAT_DSP_H */
