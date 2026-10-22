/*
 * RC4 encryption/decryption/pseudo-random number generator
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

#جے_بنا_تعریف AVUTIL_RC4_H
#تعریف_کرو AVUTIL_RC4_H

#ضمن <stdint.h>

/**
 * @defgroup lavu_rc4 RC4
 * @ingroup lavu_crypto
 * @{
 */

تعريفنوع بنية AVRC4 {
    uint8_t state[256];
    صحيح x, y;
} AVRC4;

/**
 * Allocate an AVRC4 context.
 */
AVRC4 *av_rc4_alloc(فراغ);

/**
 * @brief Initializes an AVRC4 context.
 *
 * @param d pointer to the AVRC4 context
 * @param key buffer containing the key
 * @param key_bits must be a multiple of 8
 * @param decrypt 0 for encryption, 1 for decryption, currently has no effect
 * @return zero on success, negative value otherwise
 */
صحيح av_rc4_init(بنية AVRC4 *d, ثابت uint8_t *کلید, صحيح کلید_بٹ, صحيح decrypt);

/**
 * @brief Encrypts / decrypts using the RC4 algorithm.
 *
 * @param d pointer to the AVRC4 context
 * @param count number of bytes
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst, may be NULL
 * @param iv not (yet) used for RC4, should be NULL
 * @param decrypt 0 for encryption, 1 for decryption, not (yet) used
 */
فراغ av_rc4_crypt(بنية AVRC4 *d, uint8_t *dst, ثابت uint8_t *src, صحيح گنتی, uint8_t *iv, صحيح decrypt);

/**
 * @}
 */

#جے_انت /* AVUTIL_RC4_H */
