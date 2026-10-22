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

#அந்தர்பாவ <stdint.h>
#எனில் defined(_MSC_VER)
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <intrin.h>
#endif
#அந்தர்பாவ "config.h"
#அந்தர்பாவ "libavutil/attributes.h"

#எனில் defined(_MSC_VER)

#define av_bswap16 av_bswap16
நிலையான av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    திரும்பு _rotr16(x, 8);
}

#define av_bswap32 av_bswap32
நிலையான av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    திரும்பு _byteswap_ulong(x);
}

#எனில் ARCH_X86_64
#define av_bswap64 av_bswap64
நிலையான உள்வரி uint64_t av_const av_bswap64(uint64_t x)
{
    திரும்பு _byteswap_uint64(x);
}
#endif


#அல்லதெனில் HAVE_INLINE_ASM

#ifdef __INTEL_COMPILER
#define av_bswap32 av_bswap32
நிலையான av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    திரும்பு x;
}

#எனில் ARCH_X86_64
#define av_bswap64 av_bswap64
நிலையான உள்வரி uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    திரும்பு x;
}
#endif
#endif /* __INTEL_COMPILER */

#endif /* HAVE_INLINE_ASM */
#endif /* AVUTIL_X86_BSWAP_H */
