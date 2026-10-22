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

#ifndef AVUTIL_MD5_H
#define AVUTIL_MD5_H

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "attributes.h"

/**
 * @defgroup lavu_md5 MD5
 * @ingroup lavu_hash
 * MD5 hash function implementation.
 *
 * @{
 */

বাহ্য ধ্রুব পূর্ণাঙ্ক av_md5_size;

সংরচনা AVMD5;

/**
 * Allocate an AVMD5 context.
 */
সংরচনা AVMD5 *av_md5_alloc(শূন্য);

/**
 * Initialize MD5 hashing.
 *
 * @param ctx pointer to the function context (of size av_md5_size)
 */
শূন্য av_md5_init(সংরচনা AVMD5 *ctx);

/**
 * Update hash value.
 *
 * @param ctx hash function context
 * @param src input data to update hash with
 * @param len input data length
 */
শূন্য av_md5_update(সংরচনা AVMD5 *ctx, ধ্রুব uint8_t *src, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param ctx hash function context
 * @param dst buffer where output digest value is stored
 */
শূন্য av_md5_final(সংরচনা AVMD5 *ctx, uint8_t *dst);

/**
 * Hash an array of data.
 *
 * @param dst The output buffer to write the digest into
 * @param src The data to hash
 * @param len The length of the data, in bytes
 */
শূন্য av_md5_sum(uint8_t *dst, ধ্রুব uint8_t *src, size_t len);

/**
 * @}
 */

#endif /* AVUTIL_MD5_H */
