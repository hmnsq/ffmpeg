/*
 * copyright (c) 2015 rcombs
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

#ifndef AVUTIL_AES_INTERNAL_H
#define AVUTIL_AES_INTERNAL_H

#ಅನ್ತರ್ಭಾವ "mem_internal.h"
#ಅನ್ತರ್ಭಾವ <stdint.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಙ್ಘ {
    uint64_t u64[2];
    uint32_t u32[4];
    uint8_t u8x4[4][4];
    uint8_t u8[16];
} av_aes_block;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVAES {
    // Note: round_key[16] is accessed in the init code, but this only
    // overwrites state, which does not matter (see also commit ba554c0).
    DECLARE_ALIGNED(16, av_aes_block, round_ಕೀಲಿ)[15];
    DECLARE_ALIGNED(16, av_aes_block, state)[2];
    ಪೂರ್ಣಾಙ್ಕ rounds;
    ಶೂನ್ಯ (*crypt)(ಸಂರಚನಾ AVAES *a, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ rounds);
} AVAES;

ಶೂನ್ಯ ff_init_aes_x86(AVAES *a, ಪೂರ್ಣಾಙ್ಕ decrypt);
ಶೂನ್ಯ ff_init_aes_aarch64(AVAES *a, ಪೂರ್ಣಾಙ್ಕ decrypt);

#endif /* AVUTIL_AES_INTERNAL_H */
