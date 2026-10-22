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

#اگر_غیر_تعریف_شدہ AVUTIL_X86_BSWAP_H
#تعریف_کرو AVUTIL_X86_BSWAP_H

#شامل <stdint.h>
#اگر defined(_MSC_VER)
#شامل <stdlib.h>
#شامل <intrin.h>
#اگر_ختم
#شامل "config.h"
#شامل "libavutil/attributes.h"

#اگر defined(_MSC_VER)

#تعریف_کرو av_bswap16 av_bswap16
ساکن av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    واپس _rotr16(x, 8);
}

#تعریف_کرو av_bswap32 av_bswap32
ساکن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    واپس _byteswap_ulong(x);
}

#اگر ARCH_X86_64
#تعریف_کرو av_bswap64 av_bswap64
ساکن اندرونی uint64_t av_const av_bswap64(uint64_t x)
{
    واپس _byteswap_uint64(x);
}
#اگر_ختم


#وگرنہ_اگر HAVE_INLINE_ASM

#اگر_تعریف_شدہ __INTEL_COMPILER
#تعریف_کرو av_bswap32 av_bswap32
ساکن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    واپس x;
}

#اگر ARCH_X86_64
#تعریف_کرو av_bswap64 av_bswap64
ساکن اندرونی uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    واپس x;
}
#اگر_ختم
#اگر_ختم /* __INTEL_COMPILER */

#اگر_ختم /* HAVE_INLINE_ASM */
#اگر_ختم /* AVUTIL_X86_BSWAP_H */
