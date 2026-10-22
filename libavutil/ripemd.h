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
 * @ingroup lavu_ripemd
 * Public header for RIPEMD hash function implementation.
 */

#ifndef AVUTIL_RIPEMD_H
#define AVUTIL_RIPEMD_H

#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ <stdint.h>

#অন্তর্ভাৱ "attributes.h"

/**
 * @defgroup lavu_ripemd RIPEMD
 * @ingroup lavu_hash
 * RIPEMD hash function implementation.
 *
 * @{
 */

বাহ্য ধ্রুৱ পূর্ণাঙ্ক av_ripemd_size;

সংরচনা AVRIPEMD;

/**
 * Allocate an AVRIPEMD context.
 */
সংরচনা AVRIPEMD *av_ripemd_alloc(শূন্য);

/**
 * Initialize RIPEMD hashing.
 *
 * @param context pointer to the function context (of size av_ripemd_size)
 * @param bits    number of bits in digest (128, 160, 256 or 320 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
পূর্ণাঙ্ক av_ripemd_init(সংরচনা AVRIPEMD* context, পূর্ণাঙ্ক bits);

/**
 * Update hash value.
 *
 * @param context hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
শূন্য av_ripemd_update(সংরচনা AVRIPEMD* context, ধ্রুৱ uint8_t* data, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
শূন্য av_ripemd_final(সংরচনা AVRIPEMD* context, uint8_t *digest);

/**
 * @}
 */

#endif /* AVUTIL_RIPEMD_H */
