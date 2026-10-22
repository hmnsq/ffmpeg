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

#यदि_अपरिभाषितम् AVUTIL_ARM_BSWAP_H
#परिभाषय AVUTIL_ARM_BSWAP_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "config.h"
#अन्तर्भाव "libavutil/attributes.h"

#यदि_परिभाषितम् __ARMCC_VERSION

#यदि HAVE_ARMV6
#परिभाषय av_bswap32 av_bswap32
स्थिर av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    प्रत्यागम __rev(x);
}
#यदि_अन्तः /* HAVE_ARMV6 */

#नोचेद्यदि HAVE_INLINE_ASM

#यदि HAVE_ARMV6_INLINE
#परिभाषय av_bswap16 av_bswap16
स्थिर av_always_inline av_const अचिह्नित av_bswap16(अचिह्नित x)
{
    अचिह्नित y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    प्रत्यागम y;
}
#यदि_अन्तः
#यदि_अन्तः /* __ARMCC_VERSION */

#यदि_अन्तः /* AVUTIL_ARM_BSWAP_H */
