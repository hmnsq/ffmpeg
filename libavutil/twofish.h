/*
 * An implementation of the TwoFish algorithm
 * Copyright (c) 2015 Supraja Meedinti
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

#अगर_अघोषित AVUTIL_TWOFISH_H
#घोषणा AVUTIL_TWOFISH_H

#समावेश <stdint.h>


/**
  * @file
  * @brief Public header for libavutil TWOFISH algorithm
  * @defgroup lavu_twofish TWOFISH
  * @ingroup lavu_crypto
  * @{
  */

बाह्य स्थिर पूर्णांक av_twofish_आकार;

काष्ठा AVTWOFISH;

/**
  * Allocate an AVTWOFISH context
  * To free the struct: av_free(ptr)
  */
काष्ठा AVTWOFISH *av_twofish_alloc(व्योम);

/**
  * Initialize an AVTWOFISH context.
  *
  * @param ctx an AVTWOFISH context
  * @param key a key of size ranging from 1 to 32 bytes used for encryption/decryption
  * @param key_bits number of keybits: 128, 192, 256 If less than the required, padded with zeroes to nearest valid value; return value is 0 if key_bits is 128/192/256, -1 if less than 0, 1 otherwise
 */
पूर्णांक av_twofish_init(काष्ठा AVTWOFISH *ctx, स्थिर uint8_t *कुंजी, पूर्णांक कुंजी_bits);

/**
  * Encrypt or decrypt a buffer using a previously initialized context
  *
  * @param ctx an AVTWOFISH context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 16 byte blocks
  * @param iv initialization vector for CBC mode, NULL for ECB mode
  * @param decrypt 0 for encryption, 1 for decryption
 */
व्योम av_twofish_crypt(काष्ठा AVTWOFISH *ctx, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती, uint8_t* iv, पूर्णांक decrypt);

/**
 * @}
 */
#पूर्ण_अगर /* AVUTIL_TWOFISH_H */
