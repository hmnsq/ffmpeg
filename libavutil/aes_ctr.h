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

#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "attributes.h"

#define AES_CTR_ચાવી_SIZE (16)
#define AES_CTR_IV_SIZE (8)

સંરચના AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
સંરચના AVAESCTR *av_aes_ctr_alloc(શૂન્ય);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
પૂર્ણાંક av_aes_ctr_init(સંરચના AVAESCTR *a, અચલ uint8_t *ચાવી);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
શૂન્ય av_aes_ctr_free(સંરચના AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
શૂન્ય av_aes_ctr_crypt(સંરચના AVAESCTR *a, uint8_t *dst, અચલ uint8_t *src, પૂર્ણાંક size);

/**
 * Get the current iv
 */
અચલ uint8_t* av_aes_ctr_get_iv(સંરચના AVAESCTR *a);

/**
 * Generate a random iv
 */
શૂન્ય av_aes_ctr_set_random_iv(સંરચના AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
શૂન્ય av_aes_ctr_set_iv(સંરચના AVAESCTR *a, અચલ uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
શૂન્ય av_aes_ctr_set_full_iv(સંરચના AVAESCTR *a, અચલ uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
શૂન્ય av_aes_ctr_increment_iv(સંરચના AVAESCTR *a);

/**
 * @}
 */

#endif /* AVUTIL_AES_CTR_H */
