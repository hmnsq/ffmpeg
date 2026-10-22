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

#اگر_غیر_تعریف_شدہ AVUTIL_AARCH64_INTREADWRITE_H
#تعریف_کرو AVUTIL_AARCH64_INTREADWRITE_H

#اگر HAVE_INTRINSICS_NEON

#شامل <arm_neon.h>

#تعریف_کرو AV_COPY128 AV_COPY128
ساکن av_always_inline خالی AV_COPY128(خالی *d, ثابت خالی *s)
{
    uint8x16_t tmp = vld1q_u8((ثابت uint8_t *)s);
    vst1q_u8((uint8_t *)d, tmp);
}

#تعریف_کرو AV_ZERO128 AV_ZERO128
ساکن av_always_inline خالی AV_ZERO128(خالی *d)
{
    uint8x16_t zero = vdupq_n_u8(0);
    vst1q_u8((uint8_t *)d, zero);
}

#اگر_ختم /* HAVE_INTRINSICS_NEON */

#اگر_ختم /* AVUTIL_AARCH64_INTREADWRITE_H */
