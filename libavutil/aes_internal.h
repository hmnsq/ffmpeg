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

#ଅନ୍ତର୍ଭାଵ "mem_internal.h"
#ଅନ୍ତର୍ଭାଵ <stdint.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂଘ {
    uint64_t u64[2];
    uint32_t u32[4];
    uint8_t u8x4[4][4];
    uint8_t u8[16];
} av_aes_block;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVAES {
    // Note: round_key[16] is accessed in the init code, but this only
    // overwrites state, which does not matter (see also commit ba554c0).
    DECLARE_ALIGNED(16, av_aes_block, round_ଚାବି)[15];
    DECLARE_ALIGNED(16, av_aes_block, state)[2];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds;
    ଶୂନ୍ୟ (*crypt)(ସଂରଚନା AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds);
} AVAES;

ଶୂନ୍ୟ ff_init_aes_x86(AVAES *a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt);
ଶୂନ୍ୟ ff_init_aes_aarch64(AVAES *a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt);

#endif /* AVUTIL_AES_INTERNAL_H */
