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

#अगर_अघोषित AVUTIL_ARM_BSWAP_H
#घोषणा AVUTIL_ARM_BSWAP_H

#समावेश <stdint.h>
#समावेश "config.h"
#समावेश "libavutil/attributes.h"

#अगर_घोषित __ARMCC_VERSION

#अगर HAVE_ARMV6
#घोषणा av_bswap32 av_bswap32
अटल av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    वापस __rev(x);
}
#पूर्ण_अगर /* HAVE_ARMV6 */

#या_अगर HAVE_INLINE_ASM

#अगर HAVE_ARMV6_INLINE
#घोषणा av_bswap16 av_bswap16
अटल av_always_inline av_const अचिन्हित av_bswap16(अचिन्हित x)
{
    अचिन्हित y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    वापस y;
}
#पूर्ण_अगर
#पूर्ण_अगर /* __ARMCC_VERSION */

#पूर्ण_अगर /* AVUTIL_ARM_BSWAP_H */
