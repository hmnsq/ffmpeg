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

#నిర్వచితం_కాకపోతే AVUTIL_AES_అంతర్గత_H
#నిర్వచించు AVUTIL_AES_అంతర్గత_H

#అన్తర్భావ "mem_internal.h"
#అన్తర్భావ <stdint.h>

రకనిర్వచనం సంఘం {
    uint64_t u64[2];
    uint32_t u32[4];
    uint8_t u8x4[4][4];
    uint8_t u8[16];
} av_aes_ఖండం;

రకనిర్వచనం నిర్మాణం AVAES {
    // Note: round_key[16] is accessed in the init code, but this only
    // overwrites state, which does not matter (see also commit ba554c0).
    DECLARE_ALIGNED(16, av_aes_ఖండం, విడత_కీలకం)[15];
    DECLARE_ALIGNED(16, av_aes_ఖండం, state)[2];
    పూర్ణాంకం విడతలు;
    శూన్య (*crypt)(నిర్మాణం AVAES *a, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క, uint8_t *iv, పూర్ణాంకం విడతలు);
} AVAES;

శూన్య ff_init_aes_x86(AVAES *a, పూర్ణాంకం decrypt);
శూన్య ff_init_aes_aarch64(AVAES *a, పూర్ణాంకం decrypt);

#అయితే_ముగింపు /* AVUTIL_AES_INTERNAL_H */
