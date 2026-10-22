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

#ifndef AVUTIL_AES_CTR_H
#define AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "attributes.h"

#define AES_CTR_চাবি_আকার (16)
#define AES_CTR_IV_আকার (8)

কাঠামো AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
কাঠামো AVAESCTR *av_aes_ctr_alloc(শূন্য);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
পূর্ণসংখ্যা av_aes_ctr_init(কাঠামো AVAESCTR *a, ধ্রুবক uint8_t *চাবি);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
শূন্য av_aes_ctr_free(কাঠামো AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
শূন্য av_aes_ctr_crypt(কাঠামো AVAESCTR *a, uint8_t *dst, ধ্রুবক uint8_t *src, পূর্ণসংখ্যা আকার_2);

/**
 * Get the current iv
 */
ধ্রুবক uint8_t* av_aes_ctr_get_iv(কাঠামো AVAESCTR *a);

/**
 * Generate a random iv
 */
শূন্য av_aes_ctr_set_random_iv(কাঠামো AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
শূন্য av_aes_ctr_set_iv(কাঠামো AVAESCTR *a, ধ্রুবক uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
শূন্য av_aes_ctr_set_full_iv(কাঠামো AVAESCTR *a, ধ্রুবক uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
শূন্য av_aes_ctr_increment_iv(কাঠামো AVAESCTR *a);

/**
 * @}
 */

#endif /* AVUTIL_AES_CTR_H */
