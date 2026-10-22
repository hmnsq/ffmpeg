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

#నిర్వచితం_కాకపోతే AVUTIL_RIPEMD_H
#నిర్వచించు AVUTIL_RIPEMD_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "attributes.h"

/**
 * @defgroup lavu_ripemd RIPEMD
 * @ingroup lavu_hash
 * RIPEMD hash function implementation.
 *
 * @{
 */

బాహ్య స్థిరరాశి పూర్ణాంకం av_ripemd_కొలత;

నిర్మాణం AVRIPEMD;

/**
 * Allocate an AVRIPEMD context.
 */
నిర్మాణం AVRIPEMD *av_ripemd_alloc(శూన్య);

/**
 * Initialize RIPEMD hashing.
 *
 * @param context pointer to the function context (of size av_ripemd_size)
 * @param bits    number of bits in digest (128, 160, 256 or 320 bits)
 * @return        zero if initialization succeeded, -1 otherwise
 */
పూర్ణాంకం av_ripemd_init(నిర్మాణం AVRIPEMD* context, పూర్ణాంకం బిట్లు);

/**
 * Update hash value.
 *
 * @param context hash function context
 * @param data    input data to update hash with
 * @param len     input data length
 */
శూన్య av_ripemd_update(నిర్మాణం AVRIPEMD* context, స్థిరరాశి uint8_t* దత్తాంశం, size_t len);

/**
 * Finish hashing and output digest value.
 *
 * @param context hash function context
 * @param digest  buffer where output digest value is stored
 */
శూన్య av_ripemd_final(నిర్మాణం AVRIPEMD* context, uint8_t *digest);

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_RIPEMD_H */
