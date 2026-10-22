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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_AES_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_AES_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ "mem_internal.h"
#ಅನ್ತರ್ಭಾವ <stdint.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಒಕ್ಕೂಟ {
    uint64_t u64[2];
    uint32_t u32[4];
    uint8_t u8x4[4][4];
    uint8_t u8[16];
} av_aes_ಖಂಡ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVAES {
    // Note: round_key[16] is accessed in the init code, but this only
    // overwrites state, which does not matter (see also commit ba554c0).
    DECLARE_ALIGNED(16, av_aes_ಖಂಡ, ಸುತ್ತು_ಕೀಲಿ)[15];
    DECLARE_ALIGNED(16, av_aes_ಖಂಡ, state)[2];
    ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು;
    ಶೂನ್ಯ (*crypt)(ರಚನೆ AVAES *a, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t *iv, ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು);
} AVAES;

ಶೂನ್ಯ ff_init_aes_x86(AVAES *a, ಪೂರ್ಣಾಂಕ decrypt);
ಶೂನ್ಯ ff_init_aes_aarch64(AVAES *a, ಪೂರ್ಣಾಂಕ decrypt);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_AES_INTERNAL_H */
