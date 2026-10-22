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

#यदि_अपरिभाषितम् AVUTIL_AES_CTR_H
#परिभाषय AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "attributes.h"

#परिभाषय AES_CTR_कुञ्चिका_आकार (16)
#परिभाषय AES_CTR_IV_आकार (8)

संरचना AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
संरचना AVAESCTR *av_aes_ctr_alloc(शून्य);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
पूर्णाङ्क av_aes_ctr_init(संरचना AVAESCTR *a, ध्रुव uint8_t *कुञ्चिका);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
शून्य av_aes_ctr_free(संरचना AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
शून्य av_aes_ctr_crypt(संरचना AVAESCTR *a, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क आकार);

/**
 * Get the current iv
 */
ध्रुव uint8_t* av_aes_ctr_get_iv(संरचना AVAESCTR *a);

/**
 * Generate a random iv
 */
शून्य av_aes_ctr_समुच्चयः_random_iv(संरचना AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
शून्य av_aes_ctr_समुच्चयः_iv(संरचना AVAESCTR *a, ध्रुव uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
शून्य av_aes_ctr_समुच्चयः_पूर्णम्_iv(संरचना AVAESCTR *a, ध्रुव uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
शून्य av_aes_ctr_increment_iv(संरचना AVAESCTR *a);

/**
 * @}
 */

#यदि_अन्तः /* AVUTIL_AES_CTR_H */
