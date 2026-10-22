/*
 * DES encryption/decryption
 * Copyright (c) 2007 Reimar Doeffinger
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

#ifndef AVUTIL_DES_H
#define AVUTIL_DES_H

#شامل <stdint.h>

/**
 * @defgroup lavu_des DES
 * @ingroup lavu_crypto
 * @{
 */

تعریفنوع ساختار AVDES {
    uint64_t round_کلیدها[3][16];
    صحیح triple_des;
} AVDES;

/**
 * Allocate an AVDES context.
 */
AVDES *av_des_alloc(تهی);

/**
 * @brief Initializes an AVDES context.
 *
 * @param d pointer to a AVDES structure to initialize
 * @param key pointer to the key to use
 * @param key_bits must be 64 or 192
 * @param decrypt 0 for encryption/CBC-MAC, 1 for decryption
 * @return zero on success, negative value otherwise
 */
صحیح av_des_init(ساختار AVDES *d, ثابت uint8_t *کلید, صحیح کلید_bits, صحیح decrypt);

/**
 * @brief Encrypts / decrypts using the DES algorithm.
 *
 * @param d pointer to the AVDES structure
 * @param dst destination array, can be equal to src, must be 8-byte aligned
 * @param src source array, can be equal to dst, must be 8-byte aligned, may be NULL
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL then ECB will be used,
 *           must be 8-byte aligned
 * @param decrypt 0 for encryption, 1 for decryption
 */
تهی av_des_crypt(ساختار AVDES *d, uint8_t *dst, ثابت uint8_t *src, صحیح شمار, uint8_t *iv, صحیح decrypt);

/**
 * @brief Calculates CBC-MAC using the DES algorithm.
 *
 * @param d pointer to the AVDES structure
 * @param dst destination array, can be equal to src, must be 8-byte aligned
 * @param src source array, can be equal to dst, must be 8-byte aligned, may be NULL
 * @param count number of 8 byte blocks
 */
تهی av_des_mac(ساختار AVDES *d, uint8_t *dst, ثابت uint8_t *src, صحیح شمار);

/**
 * @}
 */

#endif /* AVUTIL_DES_H */
