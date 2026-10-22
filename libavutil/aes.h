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

#अगर_अघोषित AVUTIL_AES_H
#घोषणा AVUTIL_AES_H

#समावेश <stdint.h>

#समावेश "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

बाह्य स्थिर पूर्णांक av_aes_आकार;

काष्ठा AVAES;

/**
 * Allocate an AVAES context.
 */
काष्ठा AVAES *av_aes_alloc(व्योम);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
पूर्णांक av_aes_init(काष्ठा AVAES *a, स्थिर uint8_t *कुंजी, पूर्णांक कुंजी_bits, पूर्णांक decrypt);

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
व्योम av_aes_crypt(काष्ठा AVAES *a, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती, uint8_t *iv, पूर्णांक decrypt);

/**
 * @}
 */

#पूर्ण_अगर /* AVUTIL_AES_H */
