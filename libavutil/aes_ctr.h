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

#నిర్వచితం_కాకపోతే AVUTIL_AES_CTR_H
#నిర్వచించు AVUTIL_AES_CTR_H

/**
 * @defgroup lavu_aes_ctr AES-CTR
 * @ingroup lavu_crypto
 * @{
 */

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "attributes.h"

#నిర్వచించు AES_CTR_కీలకం_కొలత (16)
#నిర్వచించు AES_CTR_IV_కొలత (8)

నిర్మాణం AVAESCTR;

/**
 * Allocate an AVAESCTR context.
 */
నిర్మాణం AVAESCTR *av_aes_ctr_alloc(శూన్య);

/**
 * Initialize an AVAESCTR context.
 *
 * @param a The AVAESCTR context to initialize
 * @param key encryption key, must have a length of AES_CTR_KEY_SIZE
 */
పూర్ణాంకం av_aes_ctr_init(నిర్మాణం AVAESCTR *a, స్థిరరాశి uint8_t *కీలకం);

/**
 * Release an AVAESCTR context.
 *
 * @param a The AVAESCTR context
 */
శూన్య av_aes_ctr_free(నిర్మాణం AVAESCTR *a);

/**
 * Process a buffer using a previously initialized context.
 *
 * @param a The AVAESCTR context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param size the size of src and dst
 */
శూన్య av_aes_ctr_crypt(నిర్మాణం AVAESCTR *a, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం కొలత);

/**
 * Get the current iv
 */
స్థిరరాశి uint8_t* av_aes_ctr_get_iv(నిర్మాణం AVAESCTR *a);

/**
 * Generate a random iv
 */
శూన్య av_aes_ctr_సమితి_random_iv(నిర్మాణం AVAESCTR *a);

/**
 * Forcefully change the 8-byte iv
 */
శూన్య av_aes_ctr_సమితి_iv(నిర్మాణం AVAESCTR *a, స్థిరరాశి uint8_t* iv);

/**
 * Forcefully change the "full" 16-byte iv, including the counter
 */
శూన్య av_aes_ctr_సమితి_నిండిన_iv(నిర్మాణం AVAESCTR *a, స్థిరరాశి uint8_t* iv);

/**
 * Increment the top 64 bit of the iv (performed after each frame)
 */
శూన్య av_aes_ctr_increment_iv(నిర్మాణం AVAESCTR *a);

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_AES_CTR_H */
