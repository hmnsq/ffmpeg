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

#اگر_غیر_تعریف_شدہ AVUTIL_AES_H
#تعریف_کرو AVUTIL_AES_H

#شامل <stdint.h>

#شامل "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

خارجی ثابت صحیح av_aes_سائز;

ساخت AVAES;

/**
 * Allocate an AVAES context.
 */
ساخت AVAES *av_aes_alloc(خالی);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
صحیح av_aes_init(ساخت AVAES *a, ثابت uint8_t *کلید, صحیح کلید_بٹ, صحیح decrypt);

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
خالی av_aes_crypt(ساخت AVAES *a, uint8_t *dst, ثابت uint8_t *src, صحیح گنتی, uint8_t *iv, صحیح decrypt);

/**
 * @}
 */

#اگر_ختم /* AVUTIL_AES_H */
