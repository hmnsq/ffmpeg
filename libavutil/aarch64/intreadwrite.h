/*
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

#నిర్వచితం_కాకపోతే AVUTIL_AARCH64_INTREADWRITE_H
#నిర్వచించు AVUTIL_AARCH64_INTREADWRITE_H

#ఒకవేళ HAVE_INTRINSICS_NEON

#అన్తర్భావ <arm_neon.h>

#నిర్వచించు AV_COPY128 AV_COPY128
స్థిర av_always_inline శూన్య AV_COPY128(శూన్య *d, స్థిరరాశి శూన్య *s)
{
    uint8x16_t tmp = vld1q_u8((స్థిరరాశి uint8_t *)s);
    vst1q_u8((uint8_t *)d, tmp);
}

#నిర్వచించు AV_ZERO128 AV_ZERO128
స్థిర av_always_inline శూన్య AV_ZERO128(శూన్య *d)
{
    uint8x16_t zero = vdupq_n_u8(0);
    vst1q_u8((uint8_t *)d, zero);
}

#అయితే_ముగింపు /* HAVE_INTRINSICS_NEON */

#అయితే_ముగింపు /* AVUTIL_AARCH64_INTREADWRITE_H */
