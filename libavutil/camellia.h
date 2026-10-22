/*
 * An implementation of the CAMELLIA algorithm as mentioned in RFC3713
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_CAMELLIA_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_CAMELLIA_H

#ಅನ್ತರ್ಭಾವ <stdint.h>


/**
  * @file
  * @brief Public header for libavutil CAMELLIA algorithm
  * @defgroup lavu_camellia CAMELLIA
  * @ingroup lavu_crypto
  * @{
  */

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ av_camellia_ಗಾತ್ರ;

ರಚನೆ AVCAMELLIA;

/**
  * Allocate an AVCAMELLIA context
  * To free the struct: av_free(ptr)
  */
ರಚನೆ AVCAMELLIA *av_camellia_alloc(ಶೂನ್ಯ);

/**
  * Initialize an AVCAMELLIA context.
  *
  * @param ctx an AVCAMELLIA context
  * @param key a key of 16, 24, 32 bytes used for encryption/decryption
  * @param key_bits number of keybits: possible are 128, 192, 256
 */
ಪೂರ್ಣಾಂಕ av_camellia_init(ರಚನೆ AVCAMELLIA *ctx, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ ಕೀಲಿ_ಬಿಟ್ಟುಗಳು);

/**
  * Encrypt or decrypt a buffer using a previously initialized context
  *
  * @param ctx an AVCAMELLIA context
  * @param dst destination array, can be equal to src
  * @param src source array, can be equal to dst
  * @param count number of 16 byte blocks
  * @param iv initialization vector for CBC mode, NULL for ECB mode
  * @param decrypt 0 for encryption, 1 for decryption
 */
ಶೂನ್ಯ av_camellia_crypt(ರಚನೆ AVCAMELLIA *ctx, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t* iv, ಪೂರ್ಣಾಂಕ decrypt);

/**
 * @}
 */
#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_CAMELLIA_H */
