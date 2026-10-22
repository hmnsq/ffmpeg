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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଯଦି defined(_MSC_VER)
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <intrin.h>
#endif
#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"

#ଯଦି defined(_MSC_VER)

#define av_bswap16 av_bswap16
ସ୍ଥିର av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    ଫେରନ୍ତୁ _rotr16(x, 8);
}

#define av_bswap32 av_bswap32
ସ୍ଥିର av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ଫେରନ୍ତୁ _byteswap_ulong(x);
}

#ଯଦି ARCH_X86_64
#define av_bswap64 av_bswap64
ସ୍ଥିର ଧାଡ଼ିଭିତରେ uint64_t av_const av_bswap64(uint64_t x)
{
    ଫେରନ୍ତୁ _byteswap_uint64(x);
}
#endif


#ନଚେତଯଦି HAVE_INLINE_ASM

#ifdef __INTEL_COMPILER
#define av_bswap32 av_bswap32
ସ୍ଥିର av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    ଫେରନ୍ତୁ x;
}

#ଯଦି ARCH_X86_64
#define av_bswap64 av_bswap64
ସ୍ଥିର ଧାଡ଼ିଭିତରେ uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    ଫେରନ୍ତୁ x;
}
#endif
#endif /* __INTEL_COMPILER */

#endif /* HAVE_INLINE_ASM */
#endif /* AVUTIL_X86_BSWAP_H */
