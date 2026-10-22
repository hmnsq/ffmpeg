/*
 * Copyright (C) 2007 Michael Niedermayer <michaelni@gmx.at>
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
 * @ingroup lavu_sha
 * Public header for SHA-1 & SHA-256 hash function implementations.
 */

#ifndef AVUTIL_SHA_H
#define AVUTIL_SHA_H

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "attributes.h"

/**
 * @defgroup lavu_sha SHA
 * @ingroup lavu_hash
 * SHA-1 and SHA-256 (Secure Hash Algorithm) hash function implementations.
 *
 * This module supports the following SHA hash functions:
 *
 * - SHA-1: 160 bits
 * - SHA-224: 224 bits, as a variant of SHA-2
 * - SHA-256: 256 bits, as a variant of SHA-2
 *
 * @see For SHA-384, SHA-512, and variants thereof, see @ref lavu_sha512.
 *
 * @{
 */

બાહ્ય અચલ પૂર્ણાંક av_sha_size;

સંરચના AVSHA;

/**
 * Allocate an AVSHA context.
 */
સંરચના AVSHA *av_sha_alloc(શૂન્ય);

/**
 * Initialize SHA-1 or SHA-2 hashing.
 *
 * @param context pointer to the function context (of size av_sha_size)
 * @param bits    number of bits in digest (SHA-1 - 160 bits, SHA-2 224 or 256 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
પૂર્ણાંક av_sha_init(સંરચના AVSHA* context, પૂર્ણાંક bits);

/**
 * Update hash value.
 *
 * @param ctx     hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
શૂન્ય av_sha_update(સંરચના AVSHA *ctx, અચલ uint8_t *data, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
શૂન્ય av_sha_final(સંરચના AVSHA* context, uint8_t *digest);

/**
 * @}
 */

#endif /* AVUTIL_SHA_H */
