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

#अगर_अघोषित AVUTIL_AES_CTR_H
#घोषणा AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#समावेश <stdint.h>

#समावेश "attributes.h"

#घोषणा AES_CTR_कुंजी_आकार (16)
#घोषणा AES_CTR_IV_आकार (8)

काष्ठा AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
काष्ठा AVAESCTR *av_aes_ctr_alloc(व्योम);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
पूर्णांक av_aes_ctr_init(काष्ठा AVAESCTR *a, स्थिर uint8_t *कुंजी);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
व्योम av_aes_ctr_free(काष्ठा AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
व्योम av_aes_ctr_crypt(काष्ठा AVAESCTR *a, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक आकार);

/**
 * Get the current iv
 */
स्थिर uint8_t* av_aes_ctr_get_iv(काष्ठा AVAESCTR *a);

/**
 * Generate a random iv
 */
व्योम av_aes_ctr_set_random_iv(काष्ठा AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
व्योम av_aes_ctr_set_iv(काष्ठा AVAESCTR *a, स्थिर uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
व्योम av_aes_ctr_set_full_iv(काष्ठा AVAESCTR *a, स्थिर uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
व्योम av_aes_ctr_increment_iv(काष्ठा AVAESCTR *a);

/**
 * @}
 */

#पूर्ण_अगर /* AVUTIL_AES_CTR_H */
