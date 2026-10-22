/*
 * Copyright (c) 2010 Mans Rullgard <mans@mansr.com>
 *
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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_INTMATH_H
#وصف_ڪريو AVUTIL_INTMATH_H

#ضمن <stdint.h>

#ضمن "config.h"
#ضمن "attributes.h"

#إذا ARCH_ARM
#   include "arm/intmath.h"
#وإلاإذا ARCH_RISCV
#   include "riscv/intmath.h"
#وإلاإذا ARCH_X86
#   include "x86/intmath.h"
#جيڪڏهن_پورو

#إذا HAVE_FAST_CLZ
#إذا defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz)
#جيڪڏهن_وصف_نه_ٿيل ff_log2
#   define ff_log2(x) (31 - __builtin_clz((x)|1))
#   ifndef ff_log2_16bit
#      define ff_log2_16bit av_log2
#   endif
#جيڪڏهن_پورو /* ff_log2 */
#جيڪڏهن_پورو /* defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz) */
#جيڪڏهن_پورو

خارجي ثابت uint8_t ff_log2_tab[256];

#جيڪڏهن_وصف_نه_ٿيل ff_log2
#وصف_ڪريو ff_log2 ff_log2_c
ساكن av_always_inline av_const صحيح ff_log2_c(بنانشان صحيح v)
{
    صحيح n = 0;
    إذا (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    إذا (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    أرجع n;
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل ff_log2_16bit
#وصف_ڪريو ff_log2_16bit ff_log2_16bit_c
ساكن av_always_inline av_const صحيح ff_log2_16bit_c(بنانشان صحيح v)
{
    صحيح n = 0;
    إذا (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    أرجع n;
}
#جيڪڏهن_پورو

#وصف_ڪريو av_log2       ff_log2
#وصف_ڪريو av_log2_16bit ff_log2_16bit

/**
 * @addtogroup lavu_math
 * @{
 */

#إذا HAVE_FAST_CLZ
#إذا !defined(ff_ctz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctz))
#وصف_ڪريو ff_ctz(v) __builtin_ctz(v)
#جيڪڏهن_پورو
#إذا !defined(ff_ctzll) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctzll))
#وصف_ڪريو ff_ctzll(v) __builtin_ctzll(v)
#جيڪڏهن_پورو
#إذا !defined(ff_clz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz))
#وصف_ڪريو ff_clz(v) __builtin_clz(v)
#جيڪڏهن_پورو
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل ff_ctz
#وصف_ڪريو ff_ctz ff_ctz_c
/**
 * Trailing zero bit count.
 *
 * @param v  input value. If v is 0, the result is undefined.
 * @return   the number of trailing 0-bits
 */
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
ساكن av_always_inline av_const صحيح ff_ctz_c(صحيح v)
{
    ساكن ثابت uint8_t debruijn_ctz32[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    أرجع debruijn_ctz32[(uint32_t)((v & -(uint32_t)v) * 0x077CB531U) >> 27];
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل ff_ctzll
#وصف_ڪريو ff_ctzll ff_ctzll_c
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
ساكن av_always_inline av_const صحيح ff_ctzll_c(ڊگهو ڊگهو v)
{
    ساكن ثابت uint8_t debruijn_ctz64[64] = {
        0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
        62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
    };
    أرجع debruijn_ctz64[(uint64_t)((v & -(uint64_t)v) * 0x022FDD63CC95386DU) >> 58];
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل ff_clz
#وصف_ڪريو ff_clz ff_clz_c
ساكن av_always_inline av_const بنانشان ff_clz_c(بنانشان x)
{
    بنانشان i = حجم(x) * 8;

    طالما (x) {
        x >>= 1;
        i--;
    }

    أرجع i;
}
#جيڪڏهن_پورو

#إذا defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_parity)
#جيڪڏهن_وصف_نه_ٿيل av_parity
#وصف_ڪريو av_parity __builtin_parity
#جيڪڏهن_پورو
#جيڪڏهن_پورو

/**
 * @}
 */
#جيڪڏهن_پورو /* AVUTIL_INTMATH_H */
