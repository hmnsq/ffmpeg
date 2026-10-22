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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ARM_BSWAP_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ARM_BSWAP_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARMCC_VERSION

#ਜੇ HAVE_ARMV6
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap32 av_bswap32
ਸਥਿਰ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ਵਾਪਸ __rev(x);
}
#ਜੇ_ਅੰਤ /* HAVE_ARMV6 */

#ਜਾਂਜੇ HAVE_INLINE_ASM

#ਜੇ HAVE_ARMV6_INLINE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap16 av_bswap16
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ av_bswap16(ਬਿਨਾਨਿਸ਼ਾਨੀ x)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    ਵਾਪਸ y;
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* __ARMCC_VERSION */

#ਜੇ_ਅੰਤ /* AVUTIL_ARM_BSWAP_H */
