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

#ifndef AVUTIL_AES_H
#define AVUTIL_AES_H

#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

বাহ্যিক ধ্রুবক পূর্ণসংখ্যা av_aes_আকার;

কাঠামো AVAES;

/**
 * Allocate an AVAES context.
 */
কাঠামো AVAES *av_aes_alloc(শূন্য);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
পূর্ণসংখ্যা av_aes_init(কাঠামো AVAES *a, ধ্রুবক uint8_t *চাবি, পূর্ণসংখ্যা চাবি_bits, পূর্ণসংখ্যা decrypt);

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
শূন্য av_aes_crypt(কাঠামো AVAES *a, uint8_t *dst, ধ্রুবক uint8_t *src, পূর্ণসংখ্যা গুনতি, uint8_t *iv, পূর্ণসংখ্যা decrypt);

/**
 * @}
 */

#endif /* AVUTIL_AES_H */
