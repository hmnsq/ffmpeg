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

#ifndef AVUTIL_X86_BSWAP_H
#define AVUTIL_X86_BSWAP_H

#અન્તર્ભાવ <stdint.h>
#જો defined(_MSC_VER)
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <intrin.h>
#endif
#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "libavutil/attributes.h"

#જો defined(_MSC_VER)

#define av_bswap16 av_bswap16
સ્થિર av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    પાછા _rotr16(x, 8);
}

#define av_bswap32 av_bswap32
સ્થિર av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    પાછા _byteswap_ulong(x);
}

#જો ARCH_X86_64
#define av_bswap64 av_bswap64
સ્થિર અંતઃરેખ uint64_t av_const av_bswap64(uint64_t x)
{
    પાછા _byteswap_uint64(x);
}
#endif


#અથવાજો HAVE_INLINE_ASM

#ifdef __INTEL_COMPILER
#define av_bswap32 av_bswap32
સ્થિર av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    પાછા x;
}

#જો ARCH_X86_64
#define av_bswap64 av_bswap64
સ્થિર અંતઃરેખ uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    પાછા x;
}
#endif
#endif /* __INTEL_COMPILER */

#endif /* HAVE_INLINE_ASM */
#endif /* AVUTIL_X86_BSWAP_H */
