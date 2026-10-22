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

#अगर_अघोषित AVUTIL_SHA_H
#घोषणा AVUTIL_SHA_H

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "attributes.h"

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

बाह्य स्थिर पूर्णांक av_sha_आकार;

काष्ठा AVSHA;

/**
 * Allocate an AVSHA context.
 */
काष्ठा AVSHA *av_sha_alloc(व्योम);

/**
 * Initialize SHA-1 or SHA-2 hashing.
 *
 * @param context pointer to the function context (of size av_sha_size)
 * @param bits    number of bits in digest (SHA-1 - 160 bits, SHA-2 224 or 256 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
पूर्णांक av_sha_init(काष्ठा AVSHA* context, पूर्णांक bits);

/**
 * Update hash value.
 *
 * @param ctx     hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
व्योम av_sha_update(काष्ठा AVSHA *ctx, स्थिर uint8_t *तथ्य, माप_प्रकार len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
व्योम av_sha_final(काष्ठा AVSHA* context, uint8_t *digest);

/**
 * @}
 */

#पूर्ण_अगर /* AVUTIL_SHA_H */
