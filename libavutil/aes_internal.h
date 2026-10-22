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

#অন্তর্ভাব "mem_internal.h"
#অন্তর্ভাব <stdint.h>

প্রকারলেখ সংঘ {
    uint64_t u64[2];
    uint32_t u32[4];
    uint8_t u8x4[4][4];
    uint8_t u8[16];
} av_aes_block;

প্রকারলেখ কাঠামো AVAES {
    // Note: round_key[16] is accessed in the init code, but this only
    // overwrites state, which does not matter (see also commit ba554c0).
    DECLARE_ALIGNED(16, av_aes_block, round_চাবি)[15];
    DECLARE_ALIGNED(16, av_aes_block, state)[2];
    পূর্ণসংখ্যা rounds;
    শূন্য (*crypt)(কাঠামো AVAES *a, uint8_t *dst, ধ্রুবক uint8_t *src, পূর্ণসংখ্যা গুনতি, uint8_t *iv, পূর্ণসংখ্যা rounds);
} AVAES;

শূন্য ff_init_aes_x86(AVAES *a, পূর্ণসংখ্যা decrypt);
শূন্য ff_init_aes_aarch64(AVAES *a, পূর্ণসংখ্যা decrypt);

#endif /* AVUTIL_AES_INTERNAL_H */
