/*
 * Blowfish algorithm
 * Copyright (c) 2012 Samuel Pitoiset
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

#నిర్వచితం_కాకపోతే AVUTIL_BLOWFISH_H
#నిర్వచించు AVUTIL_BLOWFISH_H

#అన్తర్భావ <stdint.h>

/**
 * @defgroup lavu_blowfish Blowfish
 * @ingroup lavu_crypto
 * @{
 */

#నిర్వచించు AV_BF_విడతలు 16

రకనిర్వచనం నిర్మాణం AVBlowfish {
    uint32_t p[AV_BF_విడతలు + 2];
    uint32_t s[4][256];
} AVBlowfish;

/**
 * Allocate an AVBlowfish context.
 */
AVBlowfish *av_blowfish_alloc(శూన్య);

/**
 * Initialize an AVBlowfish context.
 *
 * @param ctx an AVBlowfish context
 * @param key a key
 * @param key_len length of the key
 */
శూన్య av_blowfish_init(నిర్మాణం AVBlowfish *ctx, స్థిరరాశి uint8_t *కీలకం, పూర్ణాంకం కీలకం_len);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param ctx an AVBlowfish context
 * @param xl left four bytes halves of input to be encrypted
 * @param xr right four bytes halves of input to be encrypted
 * @param decrypt 0 for encryption, 1 for decryption
 */
శూన్య av_blowfish_crypt_ecb(నిర్మాణం AVBlowfish *ctx, uint32_t *xl, uint32_t *xr,
                           పూర్ణాంకం decrypt);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param ctx an AVBlowfish context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
శూన్య av_blowfish_crypt(నిర్మాణం AVBlowfish *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src,
                       పూర్ణాంకం లెక్క, uint8_t *iv, పూర్ణాంకం decrypt);

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_BLOWFISH_H */
