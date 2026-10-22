/*
 * An implementation of the CAST128 algorithm as mentioned in RFC2144
 * Copyright (c) 2014 Supraja Meedinti
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

#ifndef AVUTIL_CAST5_H
#define AVUTIL_CAST5_H

#अन्तर्भाव <stdint.h>


/**
  * @file
  * @brief Public header for libavutil CAST5 algorithm
  * @defgroup lavu_cast5 CAST5
  * @ingroup lavu_crypto
  * @{
  */

बाह्य ध्रुव पूर्णाङ्क av_cast5_size;

संरचना AVCAST5;

/**
  * Allocate an AVCAST5 context
  * To free the struct: av_free(ptr)
  */
संरचना AVCAST5 *av_cast5_alloc(शून्य);
/**
  * Initialize an AVCAST5 context.
  *
  * @param ctx an AVCAST5 context
  * @param key a key of 5,6,...16 bytes used for encryption/decryption
  * @param key_bits number of keybits: possible are 40,48,...,128
  * @return 0 on success, less than 0 on failure
 */
पूर्णाङ्क av_cast5_init(संरचना AVCAST5 *ctx, ध्रुव uint8_t *कुंजी, पूर्णाङ्क कुंजी_bits);

/**
  * Encrypt or decrypt a buffer using a previously initialized context, ECB mode only
  *
  * @param ctx an AVCAST5 context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 8 byte blocks
  * @param decrypt 0 for encryption, 1 for decryption
 */
शून्य av_cast5_crypt(संरचना AVCAST5 *ctx, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क गिनती, पूर्णाङ्क decrypt);

/**
  * Encrypt or decrypt a buffer using a previously initialized context
  *
  * @param ctx an AVCAST5 context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 8 byte blocks
  * @param iv initialization vector for CBC mode, NULL for ECB mode
  * @param decrypt 0 for encryption, 1 for decryption
 */
शून्य av_cast5_crypt2(संरचना AVCAST5 *ctx, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क गिनती, uint8_t *iv, पूर्णाङ्क decrypt);
/**
 * @}
 */
#endif /* AVUTIL_CAST5_H */
