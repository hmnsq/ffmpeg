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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_SHA512_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_SHA512_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

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

ਬਾਹਰੀ ਅਚਲ ਪੂਰਨ av_sha512_ਮਾਪ;

ਬਣਤਰ AVSHA512;

/**
 * Allocate an AVSHA512 context.
 */
ਬਣਤਰ AVSHA512 *av_sha512_alloc(ਖਾਲੀ);

/**
 * Initialize SHA-2 512 hashing.
 *
 * @param context pointer to the function context (of size av_sha512_size)
 * @param bits    number of bits in digest (224, 256, 384 or 512 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
ਪੂਰਨ av_sha512_init(ਬਣਤਰ AVSHA512* context, ਪੂਰਨ ਬਿੱਟ);

/**
 * Update hash value.
 *
 * @param context hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
ਖਾਲੀ av_sha512_update(ਬਣਤਰ AVSHA512* context, ਅਚਲ uint8_t* ਅੰਕੜੇ, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
ਖਾਲੀ av_sha512_final(ਬਣਤਰ AVSHA512* context, uint8_t *digest);

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_SHA512_H */
