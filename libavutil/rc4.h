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

#ifndef AVUTIL_RC4_H
#define AVUTIL_RC4_H

#அந்தர்பாவ <stdint.h>

/**
 * @defgroup lavu_rc4 RC4
 * @ingroup lavu_crypto
 * @{
 */

வகைவரை கட்டமைப்பு AVRC4 {
    uint8_t state[256];
    முழு x, y;
} AVRC4;

/**
 * Allocate an AVRC4 context.
 */
AVRC4 *av_rc4_alloc(வெறுமை);

/**
 * @brief Initializes an AVRC4 context.
 *
 * @param d pointer to the AVRC4 context
 * @param key buffer containing the key
 * @param key_bits must be a multiple of 8
 * @param decrypt 0 for encryption, 1 for decryption, currently has no effect
 * @return zero on success, negative value otherwise
 */
முழு av_rc4_init(கட்டமைப்பு AVRC4 *d, மாறிலி uint8_t *சாவி, முழு சாவி_bits, முழு decrypt);

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
வெறுமை av_rc4_crypt(கட்டமைப்பு AVRC4 *d, uint8_t *dst, மாறிலி uint8_t *src, முழு மொத்தம், uint8_t *iv, முழு decrypt);

/**
 * @}
 */

#endif /* AVUTIL_RC4_H */
