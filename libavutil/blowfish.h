/*
 * Blowfish algorithm
 * Copyright (c) 2012 Samuel Pitoiset
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_BLOWFISH_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_BLOWFISH_H

#ಅನ್ತರ್ಭಾವ <stdint.h>

/**
 * @defgroup lavu_blowfish Blowfish
 * @ingroup lavu_crypto
 * @{
 */

#ವ್ಯಾಖ್ಯಾನಿಸು AV_BF_ಸುತ್ತುಗಳು 16

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVBlowfish {
    uint32_t p[AV_BF_ಸುತ್ತುಗಳು + 2];
    uint32_t s[4][256];
} AVBlowfish;

/**
 * Allocate an AVBlowfish context.
 */
AVBlowfish *av_blowfish_alloc(ಶೂನ್ಯ);

/**
 * Initialize an AVBlowfish context.
 *
 * @param ctx an AVBlowfish context
 * @param key a key
 * @param key_len length of the key
 */
ಶೂನ್ಯ av_blowfish_init(ರಚನೆ AVBlowfish *ctx, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ ಕೀಲಿ_len);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param ctx an AVBlowfish context
 * @param xl left four bytes halves of input to be encrypted
 * @param xr right four bytes halves of input to be encrypted
 * @param decrypt 0 for encryption, 1 for decryption
 */
ಶೂನ್ಯ av_blowfish_crypt_ecb(ರಚನೆ AVBlowfish *ctx, uint32_t *xl, uint32_t *xr,
                           ಪೂರ್ಣಾಂಕ decrypt);

/**
 * Encrypt or decrypt a buffer using a previously initialized context.
 *
 * @param ctx an AVBlowfish context
 * @param dst destination array, can be equal to src
 * @param src source array, can be equal to dst
 * @param count number of 8 byte blocks
 * @param iv initialization vector for CBC mode, if NULL ECB will be used
 * @param decrypt 0 for encryption, 1 for decryption
 */
ಶೂನ್ಯ av_blowfish_crypt(ರಚನೆ AVBlowfish *ctx, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src,
                       ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t *iv, ಪೂರ್ಣಾಂಕ decrypt);

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_BLOWFISH_H */
