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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_RIPEMD_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_RIPEMD_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"

/**
 * @defgroup lavu_ripemd RIPEMD
 * @ingroup lavu_hash
 * RIPEMD hash function implementation.
 *
 * @{
 */

ಬಾಹ್ಯ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ av_ripemd_ಗಾತ್ರ;

ರಚನೆ AVRIPEMD;

/**
 * Allocate an AVRIPEMD context.
 */
ರಚನೆ AVRIPEMD *av_ripemd_alloc(ಶೂನ್ಯ);

/**
 * Initialize RIPEMD hashing.
 *
 * @param context pointer to the function context (of size av_ripemd_size)
 * @param bits    number of bits in digest (128, 160, 256 or 320 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
ಪೂರ್ಣಾಂಕ av_ripemd_init(ರಚನೆ AVRIPEMD* context, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು);

/**
 * Update hash value.
 *
 * @param context hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
ಶೂನ್ಯ av_ripemd_update(ರಚನೆ AVRIPEMD* context, ಸ್ಥಿರಾಂಕ uint8_t* ದತ್ತಾಂಶ, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
ಶೂನ್ಯ av_ripemd_final(ರಚನೆ AVRIPEMD* context, uint8_t *digest);

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_RIPEMD_H */
