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

#جے_بنا_تعریف AVUTIL_AES_CTR_H
#تعریف_کرو AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#ضمن <stdint.h>

#ضمن "attributes.h"

#تعریف_کرو AES_CTR_کلید_ناپ (16)
#تعریف_کرو AES_CTR_IV_ناپ (8)

بنية AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
بنية AVAESCTR *av_aes_ctr_alloc(فراغ);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
صحيح av_aes_ctr_init(بنية AVAESCTR *a, ثابت uint8_t *کلید);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
فراغ av_aes_ctr_free(بنية AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
فراغ av_aes_ctr_crypt(بنية AVAESCTR *a, uint8_t *dst, ثابت uint8_t *src, صحيح ناپ);

/**
 * Get the current iv
 */
ثابت uint8_t* av_aes_ctr_get_iv(بنية AVAESCTR *a);

/**
 * Generate a random iv
 */
فراغ av_aes_ctr_سیٹ_random_iv(بنية AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
فراغ av_aes_ctr_سیٹ_iv(بنية AVAESCTR *a, ثابت uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
فراغ av_aes_ctr_سیٹ_بھریا_iv(بنية AVAESCTR *a, ثابت uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
فراغ av_aes_ctr_increment_iv(بنية AVAESCTR *a);

/**
 * @}
 */

#جے_انت /* AVUTIL_AES_CTR_H */
