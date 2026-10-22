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

#اگر_غیر_تعریف_شدہ AVUTIL_ARM_BSWAP_H
#تعریف_کرو AVUTIL_ARM_BSWAP_H

#شامل <stdint.h>
#شامل "config.h"
#شامل "libavutil/attributes.h"

#اگر_تعریف_شدہ __ARMCC_VERSION

#اگر HAVE_ARMV6
#تعریف_کرو av_bswap32 av_bswap32
ساکن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    واپس __rev(x);
}
#اگر_ختم /* HAVE_ARMV6 */

#وگرنہ_اگر HAVE_INLINE_ASM

#اگر HAVE_ARMV6_INLINE
#تعریف_کرو av_bswap16 av_bswap16
ساکن av_always_inline av_const غیرعلامتی av_bswap16(غیرعلامتی x)
{
    غیرعلامتی y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    واپس y;
}
#اگر_ختم
#اگر_ختم /* __ARMCC_VERSION */

#اگر_ختم /* AVUTIL_ARM_BSWAP_H */
