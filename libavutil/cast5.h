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

#اگر_غیر_تعریف_شدہ AVUTIL_CAST5_H
#تعریف_کرو AVUTIL_CAST5_H

#شامل <stdint.h>


/**
  * @file
  * @brief Public header for libavutil CAST5 algorithm
  * @defgroup lavu_cast5 CAST5
  * @ingroup lavu_crypto
  * @{
  */

خارجی ثابت صحیح av_cast5_سائز;

ساخت AVCAST5;

/**
  * Allocate an AVCAST5 context
  * To free the struct: av_free(ptr)
  */
ساخت AVCAST5 *av_cast5_alloc(خالی);
/**
  * Initialize an AVCAST5 context.
  *
  * @param ctx an AVCAST5 context
  * @param key a key of 5,6,...16 bytes used for encryption/decryption
  * @param key_bits number of keybits: possible are 40,48,...,128
  * @return 0 on success, less than 0 on failure
 */
صحیح av_cast5_init(ساخت AVCAST5 *ctx, ثابت uint8_t *کلید, صحیح کلید_بٹ);

/**
  * Encrypt or decrypt a buffer using a previously initialized context, ECB mode only
  *
  * @param ctx an AVCAST5 context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 8 byte blocks
  * @param decrypt 0 for encryption, 1 for decryption
 */
خالی av_cast5_crypt(ساخت AVCAST5 *ctx, uint8_t *dst, ثابت uint8_t *src, صحیح گنتی, صحیح decrypt);

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
خالی av_cast5_crypt2(ساخت AVCAST5 *ctx, uint8_t *dst, ثابت uint8_t *src, صحیح گنتی, uint8_t *iv, صحیح decrypt);
/**
 * @}
 */
#اگر_ختم /* AVUTIL_CAST5_H */
