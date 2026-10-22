/*
 * copyright (c) 2006 Mans Rullgard
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
 * @ingroup lavu_adler32
 * Public header for Adler-32 hash function implementation.
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ADLER32_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ADLER32_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "attributes.h"

/**
 * @defgroup lavu_adler32 Adler-32
 * @ingroup lavu_hash
 * Adler-32 hash function implementation.
 *
 * @{
 */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uint32_t AVAdler;

/**
 * Calculate the Adler32 checksum of a buffer.
 *
 * Passing the return value to a subsequent av_adler32_update() call
 * allows the checksum of multiple buffers to be calculated as though
 * they were concatenated.
 *
 * @param adler initial checksum value
 * @param buf   pointer to input buffer
 * @param len   size of input buffer
 * @return      updated checksum
 */
AVAdler av_adler32_update(AVAdler adler, ಸ್ಥಿರಾಂಕ uint8_t *buf,
                          size_t len) av_ಶುದ್ಧ;

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_ADLER32_H */
