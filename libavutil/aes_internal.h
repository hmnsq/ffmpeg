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

#அந்தர்பாவ "mem_internal.h"
#அந்தர்பாவ <stdint.h>

வகைவரை ஒன்றிப்பு {
    uint64_t u64[2];
    uint32_t u32[4];
    uint8_t u8x4[4][4];
    uint8_t u8[16];
} av_aes_block;

வகைவரை கட்டமைப்பு AVAES {
    // Note: round_key[16] is accessed in the init code, but this only
    // overwrites state, which does not matter (see also commit ba554c0).
    DECLARE_ALIGNED(16, av_aes_block, round_சாவி)[15];
    DECLARE_ALIGNED(16, av_aes_block, state)[2];
    முழு rounds;
    வெறுமை (*crypt)(கட்டமைப்பு AVAES *a, uint8_t *dst, மாறிலி uint8_t *src, முழு மொத்தம், uint8_t *iv, முழு rounds);
} AVAES;

வெறுமை ff_init_aes_x86(AVAES *a, முழு decrypt);
வெறுமை ff_init_aes_aarch64(AVAES *a, முழு decrypt);

#endif /* AVUTIL_AES_INTERNAL_H */
