/*
 * A 32-bit implementation of the TEA algorithm
 * Copyright (c) 2015 Vesselin Bontchev
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

#ifndef AVUTIL_TEA_H
#define AVUTIL_TEA_H

#അന്തര്ഭാവ <stdint.h>

/**
 * @file
 * @brief Public header for libavutil TEA algorithm
 * @defgroup lavu_tea TEA
 * @ingroup lavu_crypto
 * @{
 */

ബാഹ്യ സ്ഥിരം പൂർണ്ണസംഖ്യ av_tea_size;

ഘടന AVTEA;

/**
  * Allocate an AVTEA context
  * To free the struct: av_free(ptr)
  */
ഘടന AVTEA *av_tea_alloc(ശൂന്യം);

/**
 * Initialize an AVTEA context.
 *
 * @param ctx an AVTEA context
 * @param key a key of 16 bytes used for encryption/decryption
 * @param rounds the number of rounds in TEA (64 is the "standard")
 */
ശൂന്യം av_tea_init(ഘടന AVTEA *ctx, സ്ഥിരം uint8_t താക്കോൽ[16], പൂർണ്ണസംഖ്യ rounds);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param ctx an AVTEA context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL then ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
ശൂന്യം av_tea_crypt(ഘടന AVTEA *ctx, uint8_t *dst, സ്ഥിരം uint8_t *src,
                  പൂർണ്ണസംഖ്യ എണ്ണം, uint8_t *iv, പൂർണ്ണസംഖ്യ decrypt);

/**
 * @}
 */

#endif /* AVUTIL_TEA_H */
