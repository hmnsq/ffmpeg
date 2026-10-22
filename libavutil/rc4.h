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

#અન્તર્ભાવ <stdint.h>

/**
 * @defgroup lavu_rc4 RC4
 * @ingroup lavu_crypto
 * @{
 */

પ્રકારવ્યાખ્યા સંરચના AVRC4 {
    uint8_t state[256];
    પૂર્ણાંક x, y;
} AVRC4;

/**
 * Allocate an AVRC4 context.
 */
AVRC4 *av_rc4_alloc(શૂન્ય);

/**
 * @brief Initializes an AVRC4 context.
 *
 * @param d pointer to the AVRC4 context
 * @param key buffer containing the key
 * @param key_bits must be a multiple of 8
 * @param decrypt 0 for encryption, 1 for decryption, currently has no effect
 * @return zero on success, negative value otherwise
 */
પૂર્ણાંક av_rc4_init(સંરચના AVRC4 *d, અચલ uint8_t *ચાવી, પૂર્ણાંક ચાવી_bits, પૂર્ણાંક decrypt);

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
શૂન્ય av_rc4_crypt(સંરચના AVRC4 *d, uint8_t *dst, અચલ uint8_t *src, પૂર્ણાંક ગણતરી, uint8_t *iv, પૂર્ણાંક decrypt);

/**
 * @}
 */

#endif /* AVUTIL_RC4_H */
