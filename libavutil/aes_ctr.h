/*
 * AES-CTR cipher
 * Copyright (c) 2015 Eran Kornblau <erankor at gmail dot com>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_AES_CTR_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AES_CTR_ਕੁੰਜੀ_ਮਾਪ (16)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AES_CTR_IV_ਮਾਪ (8)

ਬਣਤਰ AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
ਬਣਤਰ AVAESCTR *av_aes_ctr_alloc(ਖਾਲੀ);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
ਪੂਰਨ av_aes_ctr_init(ਬਣਤਰ AVAESCTR *a, ਅਚਲ uint8_t *ਕੁੰਜੀ);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
ਖਾਲੀ av_aes_ctr_free(ਬਣਤਰ AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
ਖਾਲੀ av_aes_ctr_crypt(ਬਣਤਰ AVAESCTR *a, uint8_t *dst, ਅਚਲ uint8_t *src, ਪੂਰਨ ਮਾਪ);

/**
 * Get the current iv
 */
ਅਚਲ uint8_t* av_aes_ctr_get_iv(ਬਣਤਰ AVAESCTR *a);

/**
 * Generate a random iv
 */
ਖਾਲੀ av_aes_ctr_ਸੈੱਟ_random_iv(ਬਣਤਰ AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
ਖਾਲੀ av_aes_ctr_ਸੈੱਟ_iv(ਬਣਤਰ AVAESCTR *a, ਅਚਲ uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
ਖਾਲੀ av_aes_ctr_ਸੈੱਟ_ਭਰਿਆ_iv(ਬਣਤਰ AVAESCTR *a, ਅਚਲ uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
ਖਾਲੀ av_aes_ctr_increment_iv(ਬਣਤਰ AVAESCTR *a);

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_AES_CTR_H */
