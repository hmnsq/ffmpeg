/*
 * Copyright (C) 2007 Michael Niedermayer <michaelni@gmx.at>
 * Copyright (C) 2013 James Almer <jamrial@gmail.com>
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

/**
 * @file
 * @ingroup lavu_sha512
 * Public header for SHA-512 implementation.
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_SHA512_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_SHA512_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"

/**
 * @defgroup lavu_sha512 SHA-512
 * @ingroup lavu_hash
 * SHA-512 (Secure Hash Algorithm) hash function implementations.
 *
 * This module supports the following SHA-2 hash functions:
 *
 * - SHA-512/224: 224 bits
 * - SHA-512/256: 256 bits
 * - SHA-384: 384 bits
 * - SHA-512: 512 bits
 *
 * @see For SHA-1, SHA-256, and variants thereof, see @ref lavu_sha.
 *
 * @{
 */

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ av_sha512_ಗಾತ್ರ;

ರಚನೆ AVSHA512;

/**
 * Allocate an AVSHA512 context.
 */
ರಚನೆ AVSHA512 *av_sha512_alloc(ಶೂನ್ಯ);

/**
 * Initialize SHA-2 512 hashing.
 *
 * @param context pointer to the function context (of size av_sha512_size)
 * @param bits    number of bits in digest (224, 256, 384 or 512 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
ಪೂರ್ಣಾಂಕ av_sha512_init(ರಚನೆ AVSHA512* context, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು);

/**
 * Update hash value.
 *
 * @param context hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
ಶೂನ್ಯ av_sha512_update(ರಚನೆ AVSHA512* context, ಸ್ಥಿರಾಂಕ uint8_t* ದತ್ತಾಂಶ, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
ಶೂನ್ಯ av_sha512_final(ರಚನೆ AVSHA512* context, uint8_t *digest);

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_SHA512_H */
