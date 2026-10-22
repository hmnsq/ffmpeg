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
 * @ingroup lavu_crc32
 * Public header for CRC hash function implementation.
 */

#که_نه_تعریف_شوی AVUTIL_دوراني_ازموینه_H
#تعریف_کړه AVUTIL_دوراني_ازموینه_H

#ضمن <stdint.h>
#ضمن <stddef.h>
#ضمن "attributes.h"

/**
 * @defgroup lavu_crc32 CRC
 * @ingroup lavu_hash
 * CRC (Cyclic Redundancy Check) hash function implementation.
 *
 * This module supports numerous CRC polynomials, in addition to the most
 * widely used CRC-32-IEEE. See @ref AVCRCId for a list of available
 * polynomials.
 *
 * @{
 */

تعريفنوع uint32_t AVCRC;

تعريفنوع تعداد {
    AV_دوراني_ازموینه_8_ATM,
    AV_دوراني_ازموینه_16_ANSI,
    AV_دوراني_ازموینه_16_CCITT,
    AV_دوراني_ازموینه_32_IEEE,
    AV_دوراني_ازموینه_32_IEEE_LE,  /*< reversed bitorder version of AV_CRC_32_IEEE */
    AV_دوراني_ازموینه_16_ANSI_LE,  /*< reversed bitorder version of AV_CRC_16_ANSI */
    AV_دوراني_ازموینه_24_IEEE,
    AV_دوراني_ازموینه_8_EBU,
    AV_دوراني_ازموینه_MAX,         /*< Not part of public API! Do not use outside libavutil. */
}AVCRCId;

/**
 * Initialize a CRC table.
 * @param ctx must be an array of size sizeof(AVCRC)*257 or sizeof(AVCRC)*1024
 * @param le If 1, the lowest bit represents the coefficient for the highest
 *           exponent of the corresponding polynomial (both for poly and
 *           actual CRC).
 *           If 0, you must swap the CRC parameter and the result of av_crc
 *           if you need the standard representation (can be simplified in
 *           most cases to e.g. bswap16):
 *           av_bswap32(crc << (32-bits))
 * @param bits number of bits for the CRC
 * @param poly generator polynomial without the x**bits coefficient, in the
 *             representation as specified by le
 * @param ctx_size size of ctx in bytes
 * @return <0 on failure
 */
صحيح av_دوراني_ازموینه_init(AVCRC *ctx, صحيح le, صحيح بټونه, uint32_t poly, صحيح ctx_اندازه);

/**
 * Get an initialized standard CRC table.
 * @param crc_id ID of a standard CRC
 * @return a pointer to the CRC table or NULL on failure
 */
ثابت AVCRC *av_دوراني_ازموینه_get_جدول(AVCRCId دوراني_ازموینه_id);

/**
 * Calculate the CRC of a block.
 * @param ctx initialized AVCRC array (see av_crc_init())
 * @param crc CRC of previous blocks if any or initial value for CRC
 * @param buffer buffer whose CRC to calculate
 * @param length length of the buffer
 * @return CRC updated with the data from the given block
 *
 * @see av_crc_init() "le" parameter
 */
uint32_t av_دوراني_ازموینه(ثابت AVCRC *ctx, uint32_t دوراني_ازموینه,
                ثابت uint8_t *بفر, size_t اوږدتیا) av_خالص;

/**
 * @}
 */

#د_که_پای /* AVUTIL_CRC_H */
