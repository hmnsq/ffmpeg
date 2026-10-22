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

#నిర్వచితం_కాకపోతే AVUTIL_X86_BSWAP_H
#నిర్వచించు AVUTIL_X86_BSWAP_H

#అన్తర్భావ <stdint.h>
#ఒకవేళ defined(_MSC_VER)
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <intrin.h>
#అయితే_ముగింపు
#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"

#ఒకవేళ defined(_MSC_VER)

#నిర్వచించు av_bswap16 av_bswap16
స్థిర av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    తిరిగి _rotr16(x, 8);
}

#నిర్వచించు av_bswap32 av_bswap32
స్థిర av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    తిరిగి _byteswap_ulong(x);
}

#ఒకవేళ ARCH_X86_64
#నిర్వచించు av_bswap64 av_bswap64
స్థిర అంతఃవరుస uint64_t av_const av_bswap64(uint64_t x)
{
    తిరిగి _byteswap_uint64(x);
}
#అయితే_ముగింపు


#లేదావేళ HAVE_INLINE_ASM

#నిర్వచితమైతే __INTEL_COMPILER
#నిర్వచించు av_bswap32 av_bswap32
స్థిర av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    తిరిగి x;
}

#ఒకవేళ ARCH_X86_64
#నిర్వచించు av_bswap64 av_bswap64
స్థిర అంతఃవరుస uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    తిరిగి x;
}
#అయితే_ముగింపు
#అయితే_ముగింపు /* __INTEL_COMPILER */

#అయితే_ముగింపు /* HAVE_INLINE_ASM */
#అయితే_ముగింపు /* AVUTIL_X86_BSWAP_H */
