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

#నిర్వచితం_కాకపోతే AVUTIL_ARM_BSWAP_H
#నిర్వచించు AVUTIL_ARM_BSWAP_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"

#నిర్వచితమైతే __ARMCC_VERSION

#ఒకవేళ HAVE_ARMV6
#నిర్వచించు av_bswap32 av_bswap32
స్థిర av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    తిరిగి __rev(x);
}
#అయితే_ముగింపు /* HAVE_ARMV6 */

#లేదావేళ HAVE_INLINE_ASM

#ఒకవేళ HAVE_ARMV6_INLINE
#నిర్వచించు av_bswap16 av_bswap16
స్థిర av_always_inline av_const గుర్తులేని av_bswap16(గుర్తులేని x)
{
    గుర్తులేని y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    తిరిగి y;
}
#అయితే_ముగింపు
#అయితే_ముగింపు /* __ARMCC_VERSION */

#అయితే_ముగింపు /* AVUTIL_ARM_BSWAP_H */
