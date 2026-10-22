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

#اگر_تعریف_نشده AVUTIL_X86_BSWAP_H
#تعریف_کن AVUTIL_X86_BSWAP_H

#ضمن <stdint.h>
#إذا defined(_MSC_VER)
#ضمن <stdlib.h>
#ضمن <intrin.h>
#پایان_اگر
#ضمن "config.h"
#ضمن "libavutil/attributes.h"

#إذا defined(_MSC_VER)

#تعریف_کن av_bswap16 av_bswap16
ساكن av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    أرجع _rotr16(x, 8);
}

#تعریف_کن av_bswap32 av_bswap32
ساكن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    أرجع _byteswap_ulong(x);
}

#إذا ARCH_X86_64
#تعریف_کن av_bswap64 av_bswap64
ساكن مضمن uint64_t av_const av_bswap64(uint64_t x)
{
    أرجع _byteswap_uint64(x);
}
#پایان_اگر


#وإلاإذا HAVE_INLINE_ASM

#اگر_تعریف_شده __INTEL_COMPILER
#تعریف_کن av_bswap32 av_bswap32
ساكن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    أرجع x;
}

#إذا ARCH_X86_64
#تعریف_کن av_bswap64 av_bswap64
ساكن مضمن uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    أرجع x;
}
#پایان_اگر
#پایان_اگر /* __INTEL_COMPILER */

#پایان_اگر /* HAVE_INLINE_ASM */
#پایان_اگر /* AVUTIL_X86_BSWAP_H */
