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

/**
 * @file
 * byte swapping routines
 */

#अगर_अघोषित AVUTIL_X86_BSWAP_H
#घोषणा AVUTIL_X86_BSWAP_H

#समावेश <stdint.h>
#अगर defined(_MSC_VER)
#समावेश <stdlib.h>
#समावेश <intrin.h>
#पूर्ण_अगर
#समावेश "config.h"
#समावेश "libavutil/attributes.h"

#अगर defined(_MSC_VER)

#घोषणा av_bswap16 av_bswap16
अटल av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    वापस _rotr16(x, 8);
}

#घोषणा av_bswap32 av_bswap32
अटल av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    वापस _byteswap_ulong(x);
}

#अगर ARCH_X86_64
#घोषणा av_bswap64 av_bswap64
अटल अंतरभूत uint64_t av_const av_bswap64(uint64_t x)
{
    वापस _byteswap_uint64(x);
}
#पूर्ण_अगर


#या_अगर HAVE_INLINE_ASM

#अगर_घोषित __INTEL_COMPILER
#घोषणा av_bswap32 av_bswap32
अटल av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    वापस x;
}

#अगर ARCH_X86_64
#घोषणा av_bswap64 av_bswap64
अटल अंतरभूत uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    वापस x;
}
#पूर्ण_अगर
#पूर्ण_अगर /* __INTEL_COMPILER */

#पूर्ण_अगर /* HAVE_INLINE_ASM */
#पूर्ण_अगर /* AVUTIL_X86_BSWAP_H */
