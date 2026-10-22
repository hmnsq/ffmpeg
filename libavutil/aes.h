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

#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

ବାହ୍ୟ ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_aes_size;

ସଂରଚନା AVAES;

/**
 * Allocate an AVAES context.
 */
ସଂରଚନା AVAES *av_aes_alloc(ଶୂନ୍ୟ);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_aes_init(ସଂରଚନା AVAES *a, ଅଚଳ uint8_t *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି_bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt);

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
ଶୂନ୍ୟ av_aes_crypt(ସଂରଚନା AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt);

/**
 * @}
 */

#endif /* AVUTIL_AES_H */
