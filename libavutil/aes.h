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

#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

ബാഹ്യ സ്ഥിരം പൂർണ്ണസംഖ്യ av_aes_size;

ഘടന AVAES;

/**
 * Allocate an AVAES context.
 */
ഘടന AVAES *av_aes_alloc(ശൂന്യം);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
പൂർണ്ണസംഖ്യ av_aes_init(ഘടന AVAES *a, സ്ഥിരം uint8_t *താക്കോൽ, പൂർണ്ണസംഖ്യ താക്കോൽ_bits, പൂർണ്ണസംഖ്യ decrypt);

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
ശൂന്യം av_aes_crypt(ഘടന AVAES *a, uint8_t *dst, സ്ഥിരം uint8_t *src, പൂർണ്ണസംഖ്യ എണ്ണം, uint8_t *iv, പൂർണ്ണസംഖ്യ decrypt);

/**
 * @}
 */

#endif /* AVUTIL_AES_H */
