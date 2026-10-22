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

#अगर_अघोषित AVUTIL_MD5_H
#घोषणा AVUTIL_MD5_H

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "attributes.h"

/**
 * @defgroup lavu_md5 MD5
 * @ingroup lavu_hash
 * MD5 hash function implementation.
 *
 * @{
 */

बाह्य स्थिर पूर्णांक av_md5_आकार;

काष्ठा AVMD5;

/**
 * Allocate an AVMD5 context.
 */
काष्ठा AVMD5 *av_md5_alloc(व्योम);

/**
 * Initialize MD5 hashing.
 *
 * @param ctx pointer to the function context (of size av_md5_size)
 */
व्योम av_md5_init(काष्ठा AVMD5 *ctx);

/**
 * Update hash value.
 *
 * @param ctx hash function context
 * @param src input data to update hash with
 * @param len input data length
 */
व्योम av_md5_update(काष्ठा AVMD5 *ctx, स्थिर uint8_t *src, माप_प्रकार len);

/**
 * Finish hashing and output digest value.
 *
 * @param ctx hash function context
 * @param dst buffer where output digest value is stored
 */
व्योम av_md5_final(काष्ठा AVMD5 *ctx, uint8_t *dst);

/**
 * Hash an array of data.
 *
 * @param dst The output buffer to write the digest into
 * @param src The data to hash
 * @param len The length of the data, in bytes
 */
व्योम av_md5_योग(uint8_t *dst, स्थिर uint8_t *src, माप_प्रकार len);

/**
 * @}
 */

#पूर्ण_अगर /* AVUTIL_MD5_H */
