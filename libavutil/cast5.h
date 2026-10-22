/*
 * An implementation of the CAST128 algorithm as mentioned in RFC2144
 * Copyright (c) 2014 Supraja Meedinti
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

#నిర్వచితం_కాకపోతే AVUTIL_CAST5_H
#నిర్వచించు AVUTIL_CAST5_H

#అన్తర్భావ <stdint.h>


/**
  * @file
  * @brief Public header for libavutil CAST5 algorithm
  * @defgroup lavu_cast5 CAST5
  * @ingroup lavu_crypto
  * @{
  */

బాహ్య స్థిరరాశి పూర్ణాంకం av_cast5_కొలత;

నిర్మాణం AVCAST5;

/**
  * Allocate an AVCAST5 context
  * To free the struct: av_free(ptr)
  */
నిర్మాణం AVCAST5 *av_cast5_alloc(శూన్య);
/**
  * Initialize an AVCAST5 context.
  *
  * @param ctx an AVCAST5 context
  * @param key a key of 5,6,...16 bytes used for encryption/decryption
  * @param key_bits number of keybits: possible are 40,48,...,128
  * @return 0 on success, less than 0 on failure
 */
పూర్ణాంకం av_cast5_init(నిర్మాణం AVCAST5 *ctx, స్థిరరాశి uint8_t *కీలకం, పూర్ణాంకం కీలకం_బిట్లు);

/**
  * Encrypt or decrypt a buffer using a previously initialized context, ECB mode only
  *
  * @param ctx an AVCAST5 context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 8 byte blocks
  * @param decrypt 0 for encryption, 1 for decryption
 */
శూన్య av_cast5_crypt(నిర్మాణం AVCAST5 *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క, పూర్ణాంకం decrypt);

/**
  * Encrypt or decrypt a buffer using a previously initialized context
  *
  * @param ctx an AVCAST5 context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 8 byte blocks
  * @param iv initialization vector for CBC mode, NULL for ECB mode
  * @param decrypt 0 for encryption, 1 for decryption
 */
శూన్య av_cast5_crypt2(నిర్మాణం AVCAST5 *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క, uint8_t *iv, పూర్ణాంకం decrypt);
/**
 * @}
 */
#అయితే_ముగింపు /* AVUTIL_CAST5_H */
