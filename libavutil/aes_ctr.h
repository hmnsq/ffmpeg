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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_AES_CTR_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"

#ವ್ಯಾಖ್ಯಾನಿಸು AES_CTR_ಕೀಲಿ_ಗಾತ್ರ (16)
#ವ್ಯಾಖ್ಯಾನಿಸು AES_CTR_IV_ಗಾತ್ರ (8)

ರಚನೆ AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
ರಚನೆ AVAESCTR *av_aes_ctr_alloc(ಶೂನ್ಯ);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
ಪೂರ್ಣಾಂಕ av_aes_ctr_init(ರಚನೆ AVAESCTR *a, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
ಶೂನ್ಯ av_aes_ctr_free(ರಚನೆ AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
ಶೂನ್ಯ av_aes_ctr_crypt(ರಚನೆ AVAESCTR *a, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2);

/**
 * Get the current iv
 */
ಸ್ಥಿರಾಂಕ uint8_t* av_aes_ctr_get_iv(ರಚನೆ AVAESCTR *a);

/**
 * Generate a random iv
 */
ಶೂನ್ಯ av_aes_ctr_ಗಣ_random_iv(ರಚನೆ AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
ಶೂನ್ಯ av_aes_ctr_ಗಣ_iv(ರಚನೆ AVAESCTR *a, ಸ್ಥಿರಾಂಕ uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
ಶೂನ್ಯ av_aes_ctr_ಗಣ_ತುಂಬಿದ_iv(ರಚನೆ AVAESCTR *a, ಸ್ಥಿರಾಂಕ uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
ಶೂನ್ಯ av_aes_ctr_increment_iv(ರಚನೆ AVAESCTR *a);

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_AES_CTR_H */
