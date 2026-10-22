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

#اگر_تعریف_نشده AVUTIL_ARM_BSWAP_H
#تعریف_کن AVUTIL_ARM_BSWAP_H

#ضمن <stdint.h>
#ضمن "config.h"
#ضمن "libavutil/attributes.h"

#اگر_تعریف_شده __ARMCC_VERSION

#إذا HAVE_ARMV6
#تعریف_کن av_bswap32 av_bswap32
ساكن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    أرجع __rev(x);
}
#پایان_اگر /* HAVE_ARMV6 */

#وإلاإذا HAVE_INLINE_ASM

#إذا HAVE_ARMV6_INLINE
#تعریف_کن av_bswap16 av_bswap16
ساكن av_always_inline av_const بیعلامت av_bswap16(بیعلامت x)
{
    بیعلامت y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    أرجع y;
}
#پایان_اگر
#پایان_اگر /* __ARMCC_VERSION */

#پایان_اگر /* AVUTIL_ARM_BSWAP_H */
