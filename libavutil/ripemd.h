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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_RIPEMD_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_RIPEMD_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

/**
 * @defgroup lavu_ripemd RIPEMD
 * @ingroup lavu_hash
 * RIPEMD hash function implementation.
 *
 * @{
 */

ਬਾਹਰੀ ਅਚਲ ਪੂਰਨ av_ripemd_ਮਾਪ;

ਬਣਤਰ AVRIPEMD;

/**
 * Allocate an AVRIPEMD context.
 */
ਬਣਤਰ AVRIPEMD *av_ripemd_alloc(ਖਾਲੀ);

/**
 * Initialize RIPEMD hashing.
 *
 * @param context pointer to the function context (of size av_ripemd_size)
 * @param bits    number of bits in digest (128, 160, 256 or 320 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
ਪੂਰਨ av_ripemd_init(ਬਣਤਰ AVRIPEMD* context, ਪੂਰਨ ਬਿੱਟ);

/**
 * Update hash value.
 *
 * @param context hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
ਖਾਲੀ av_ripemd_update(ਬਣਤਰ AVRIPEMD* context, ਅਚਲ uint8_t* ਅੰਕੜੇ, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
ਖਾਲੀ av_ripemd_final(ਬਣਤਰ AVRIPEMD* context, uint8_t *digest);

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_RIPEMD_H */
