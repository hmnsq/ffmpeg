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

#यदि_अपरिभाषितम् AVUTIL_AES_H
#परिभाषय AVUTIL_AES_H

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "attributes.h"

/**
 * @defgroup lavu_aes AES
 * @ingroup lavu_crypto
 * @{
 */

बाह्य ध्रुव पूर्णाङ्क av_aes_आकार;

संरचना AVAES;

/**
 * Allocate an AVAES context.
 */
संरचना AVAES *av_aes_alloc(शून्य);

/**
 * Initialize an AVAES context.
 *
 * @param a The AVAES context
 * @param key Pointer to the key
 * @param key_bits 128, 192 or 256
 * @param decrypt 0 for encryption, 1 for decryption
 */
पूर्णाङ्क av_aes_init(संरचना AVAES *a, ध्रुव uint8_t *कुञ्चिका, पूर्णाङ्क कुञ्चिका_द्वयङ्काः, पूर्णाङ्क decrypt);

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
शून्य av_aes_crypt(संरचना AVAES *a, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क गणनम्, uint8_t *iv, पूर्णाङ्क decrypt);

/**
 * @}
 */

#यदि_अन्तः /* AVUTIL_AES_H */
