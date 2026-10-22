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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ "attributes.h"

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

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t AVCRC;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ {
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_8_ATM,
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_ANSI,
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_CCITT,
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE,
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE,  /*< reversed bitorder version of AV_CRC_32_IEEE */
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_ANSI_LE,  /*< reversed bitorder version of AV_CRC_16_ANSI */
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_24_IEEE,
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_8_EBU,
    AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_MAX,         /*< Not part of public API! Do not use outside libavutil. */
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
ಪೂರ್ಣಾಂಕ av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_init(AVCRC *ctx, ಪೂರ್ಣಾಂಕ le, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು, uint32_t poly, ಪೂರ್ಣಾಂಕ ctx_ಗಾತ್ರ);

/**
 * Get an initialized standard CRC table.
 * @param crc_id ID of a standard CRC
 * @return a pointer to the CRC table or NULL on failure
 */
ಸ್ಥಿರಾಂಕ AVCRC *av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_get_ಕೋಷ್ಟಕ(AVCRCId ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_id);

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
uint32_t av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(ಸ್ಥಿರಾಂಕ AVCRC *ctx, uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ,
                ಸ್ಥಿರಾಂಕ uint8_t *ಬಫರ್, size_t ಉದ್ದಳತೆ) av_ಶುದ್ಧ;

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_CRC_H */
