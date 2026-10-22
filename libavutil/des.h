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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_DES_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_DES_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/**
 * @defgroup lavu_des DES
 * @ingroup lavu_crypto
 * @{
 */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVDES {
    uint64_t ਗੇੜਾ_ਕੁੰਜੀਆਂ[3][16];
    ਪੂਰਨ triple_des;
} AVDES;

/**
 * Allocate an AVDES context.
 */
AVDES *av_des_alloc(ਖਾਲੀ);

/**
 * @brief Initializes an AVDES context.
 *
 * @param d pointer to a AVDES structure to initialize
 * @param key pointer to the key to use
 * @param key_bits must be 64 or 192
 * @param decrypt 0 for encryption/CBC-MAC, 1 for decryption
 * @return zero on success, negative value otherwise
 */
ਪੂਰਨ av_des_init(ਬਣਤਰ AVDES *d, ਅਚਲ uint8_t *ਕੁੰਜੀ, ਪੂਰਨ ਕੁੰਜੀ_ਬਿੱਟ, ਪੂਰਨ decrypt);

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
ਖਾਲੀ av_des_crypt(ਬਣਤਰ AVDES *d, uint8_t *dst, ਅਚਲ uint8_t *src, ਪੂਰਨ ਗਿਣਤੀ_2, uint8_t *iv, ਪੂਰਨ decrypt);

/**
 * @brief Calculates CBC-MAC using the DES algorithm.
 *
 * @param d pointer to the AVDES structure
 * @param dst destination array, can be equal to src, must be 8-byte aligned
 * @param src source array, can be equal to dst, must be 8-byte aligned, may be NULL
 * @param count number of 8 byte blocks
 */
ਖਾਲੀ av_des_mac(ਬਣਤਰ AVDES *d, uint8_t *dst, ਅਚਲ uint8_t *src, ਪੂਰਨ ਗਿਣਤੀ_2);

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_DES_H */
