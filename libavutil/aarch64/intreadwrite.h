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

#که_نه_تعریف_شوی AVUTIL_AARCH64_INTREADWRITE_H
#تعریف_کړه AVUTIL_AARCH64_INTREADWRITE_H

#إذا HAVE_INTRINSICS_NEON

#ضمن <arm_neon.h>

#تعریف_کړه AV_COPY128 AV_COPY128
ساكن av_always_inline فراغ AV_COPY128(فراغ *d, ثابت فراغ *s)
{
    uint8x16_t tmp = vld1q_u8((ثابت uint8_t *)s);
    vst1q_u8((uint8_t *)d, tmp);
}

#تعریف_کړه AV_ZERO128 AV_ZERO128
ساكن av_always_inline فراغ AV_ZERO128(فراغ *d)
{
    uint8x16_t zero = vdupq_n_u8(0);
    vst1q_u8((uint8_t *)d, zero);
}

#د_که_پای /* HAVE_INTRINSICS_NEON */

#د_که_پای /* AVUTIL_AARCH64_INTREADWRITE_H */
