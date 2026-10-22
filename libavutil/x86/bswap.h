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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_BSWAP_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_BSWAP_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਜੇ defined(_MSC_VER)
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <intrin.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"

#ਜੇ defined(_MSC_VER)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap16 av_bswap16
ਸਥਿਰ av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    ਵਾਪਸ _rotr16(x, 8);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap32 av_bswap32
ਸਥਿਰ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ਵਾਪਸ _byteswap_ulong(x);
}

#ਜੇ ARCH_X86_64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap64 av_bswap64
ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t av_const av_bswap64(uint64_t x)
{
    ਵਾਪਸ _byteswap_uint64(x);
}
#ਜੇ_ਅੰਤ


#ਜਾਂਜੇ HAVE_INLINE_ASM

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __INTEL_COMPILER
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap32 av_bswap32
ਸਥਿਰ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    ਵਾਪਸ x;
}

#ਜੇ ARCH_X86_64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_bswap64 av_bswap64
ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    ਵਾਪਸ x;
}
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* __INTEL_COMPILER */

#ਜੇ_ਅੰਤ /* HAVE_INLINE_ASM */
#ਜੇ_ਅੰਤ /* AVUTIL_X86_BSWAP_H */
