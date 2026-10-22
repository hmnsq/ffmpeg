/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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
 * @ingroup lavu_md5
 * Public header for MD5 hash function implementation.
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_MD5_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_MD5_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

/**
 * @defgroup lavu_md5 MD5
 * @ingroup lavu_hash
 * MD5 hash function implementation.
 *
 * @{
 */

ਬਾਹਰੀ ਅਚਲ ਪੂਰਨ av_md5_ਮਾਪ;

ਬਣਤਰ AVMD5;

/**
 * Allocate an AVMD5 context.
 */
ਬਣਤਰ AVMD5 *av_md5_alloc(ਖਾਲੀ);

/**
 * Initialize MD5 hashing.
 *
 * @param ctx pointer to the function context (of size av_md5_size)
 */
ਖਾਲੀ av_md5_init(ਬਣਤਰ AVMD5 *ctx);

/**
 * Update hash value.
 *
 * @param ctx hash function context
 * @param src input data to update hash with
 * @param len input data length
 */
ਖਾਲੀ av_md5_update(ਬਣਤਰ AVMD5 *ctx, ਅਚਲ uint8_t *src, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param ctx hash function context
 * @param dst buffer where output digest value is stored
 */
ਖਾਲੀ av_md5_final(ਬਣਤਰ AVMD5 *ctx, uint8_t *dst);

/**
 * Hash an array of data.
 *
 * @param dst The output buffer to write the digest into
 * @param src The data to hash
 * @param len The length of the data, in bytes
 */
ਖਾਲੀ av_md5_ਜੋੜ(uint8_t *dst, ਅਚਲ uint8_t *src, size_t len);

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_MD5_H */
