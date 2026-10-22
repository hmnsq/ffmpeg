/*
 * copyright (c) 2007 Michael Niedermayer <michaelni@gmx.at>
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

#నిర్వచితం_కాకపోతే AVUTIL_AES_H
#నిర్వచించు AVUTIL_AES_H

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

బాహ్య స్థిరరాశి పూర్ణాంకం av_aes_కొలత;

నిర్మాణం AVAES;

/**
 * Allocate an AVAES context.
 */
నిర్మాణం AVAES *av_aes_alloc(శూన్య);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
పూర్ణాంకం av_aes_init(నిర్మాణం AVAES *a, స్థిరరాశి uint8_t *కీలకం, పూర్ణాంకం కీలకం_బిట్లు, పూర్ణాంకం decrypt);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param a The AVAES context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 16 byte blocks
 * @param iv initialization vector for CBC mode, if NULL then ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
శూన్య av_aes_crypt(నిర్మాణం AVAES *a, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క, uint8_t *iv, పూర్ణాంకం decrypt);

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_AES_H */
