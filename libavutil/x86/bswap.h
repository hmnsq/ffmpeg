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

#جے_بنا_تعریف AVUTIL_X86_BSWAP_H
#تعریف_کرو AVUTIL_X86_BSWAP_H

#ضمن <stdint.h>
#إذا defined(_MSC_VER)
#ضمن <stdlib.h>
#ضمن <intrin.h>
#جے_انت
#ضمن "config.h"
#ضمن "libavutil/attributes.h"

#إذا defined(_MSC_VER)

#تعریف_کرو av_bswap16 av_bswap16
ساكن av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    أرجع _rotr16(x, 8);
}

#تعریف_کرو av_bswap32 av_bswap32
ساكن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    أرجع _byteswap_ulong(x);
}

#إذا ARCH_X86_64
#تعریف_کرو av_bswap64 av_bswap64
ساكن مضمن uint64_t av_const av_bswap64(uint64_t x)
{
    أرجع _byteswap_uint64(x);
}
#جے_انت


#وإلاإذا HAVE_INLINE_ASM

#جے_تعریف_شدہ __INTEL_COMPILER
#تعریف_کرو av_bswap32 av_bswap32
ساكن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    أرجع x;
}

#إذا ARCH_X86_64
#تعریف_کرو av_bswap64 av_bswap64
ساكن مضمن uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    أرجع x;
}
#جے_انت
#جے_انت /* __INTEL_COMPILER */

#جے_انت /* HAVE_INLINE_ASM */
#جے_انت /* AVUTIL_X86_BSWAP_H */
