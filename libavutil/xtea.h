/*
 * A 32-bit implementation of the XTEA algorithm
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

#اگر_غیر_تعریف_شدہ AVUTIL_XTEA_H
#تعریف_کرو AVUTIL_XTEA_H

#شامل <stdint.h>

/**
 * @file
 * @brief Public header for libavutil XTEA algorithm
 * @defgroup lavu_xtea XTEA
 * @ingroup lavu_crypto
 * @{
 */

قسمتعریف ساخت AVXTEA {
    uint32_t کلید[16];
} AVXTEA;

/**
 * Allocate an AVXTEA context.
 */
AVXTEA *av_xtea_alloc(خالی);

/**
 * Initialize an AVXTEA context.
 *
 * @param ctx an AVXTEA context
 * @param key a key of 16 bytes used for encryption/decryption,
 *            interpreted as big endian 32 bit numbers
 */
خالی av_xtea_init(ساخت AVXTEA *ctx, ثابت uint8_t کلید[16]);

/**
 * Initialize an AVXTEA context.
 *
 * @param ctx an AVXTEA context
 * @param key a key of 16 bytes used for encryption/decryption,
 *            interpreted as little endian 32 bit numbers
 */
خالی av_xtea_le_init(ساخت AVXTEA *ctx, ثابت uint8_t کلید[16]);

/**
 * Encrypt or decrypt a buffer using a previously initialized context,
 * in big endian format.
 *
 * @param ctx an AVXTEA context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL then ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
خالی av_xtea_crypt(ساخت AVXTEA *ctx, uint8_t *dst, ثابت uint8_t *src,
                   صحیح گنتی, uint8_t *iv, صحیح decrypt);

/**
 * Encrypt or decrypt a buffer using a previously initialized context,
 * in little endian format.
 *
 * @param ctx an AVXTEA context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL then ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
خالی av_xtea_le_crypt(ساخت AVXTEA *ctx, uint8_t *dst, ثابت uint8_t *src,
                      صحیح گنتی, uint8_t *iv, صحیح decrypt);

/**
 * @}
 */

#اگر_ختم /* AVUTIL_XTEA_H */
