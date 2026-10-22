/*
 * A 32-bit implementation of the TEA algorithm
 * Copyright (c) 2015 Vesselin Bontchev
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

#నిర్వచితం_కాకపోతే AVUTIL_TEA_H
#నిర్వచించు AVUTIL_TEA_H

#అన్తర్భావ <stdint.h>

/**
 * @file
 * @brief Public header for libavutil TEA algorithm
 * @defgroup lavu_tea TEA
 * @ingroup lavu_crypto
 * @{
 */

బాహ్య స్థిరరాశి పూర్ణాంకం av_tea_కొలత;

నిర్మాణం AVTEA;

/**
  * Allocate an AVTEA context
  * To free the struct: av_free(ptr)
  */
నిర్మాణం AVTEA *av_tea_alloc(శూన్య);

/**
 * Initialize an AVTEA context.
 *
 * @param ctx an AVTEA context
 * @param key a key of 16 bytes used for encryption/decryption
 * @param rounds the number of rounds in TEA (64 is the "standard")
 */
శూన్య av_tea_init(నిర్మాణం AVTEA *ctx, స్థిరరాశి uint8_t కీలకం[16], పూర్ణాంకం విడతలు);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param ctx an AVTEA context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL then ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
శూన్య av_tea_crypt(నిర్మాణం AVTEA *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src,
                  పూర్ణాంకం లెక్క, uint8_t *iv, పూర్ణాంకం decrypt);

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_TEA_H */
