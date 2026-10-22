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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_INTMATH_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_INTMATH_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

#ਜੇ ARCH_ARM
#   include "arm/intmath.h"
#ਜਾਂਜੇ ARCH_RISCV
#   include "riscv/intmath.h"
#ਜਾਂਜੇ ARCH_X86
#   include "x86/intmath.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_FAST_CLZ
#ਜੇ defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_log2
#   define ff_log2(x) (31 - __builtin_clz((x)|1))
#   ifndef ff_log2_16bit
#      define ff_log2_16bit av_log2
#   endif
#ਜੇ_ਅੰਤ /* ff_log2 */
#ਜੇ_ਅੰਤ /* defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz) */
#ਜੇ_ਅੰਤ

ਬਾਹਰੀ ਅਚਲ uint8_t ff_log2_tab[256];

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_log2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_log2 ff_log2_c
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ ff_log2_c(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v)
{
    ਪੂਰਨ n = 0;
    ਜੇ (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    ਜੇ (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    ਵਾਪਸ n;
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_log2_16bit
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_log2_16bit ff_log2_16bit_c
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ ff_log2_16bit_c(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v)
{
    ਪੂਰਨ n = 0;
    ਜੇ (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    ਵਾਪਸ n;
}
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_log2       ff_log2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_log2_16bit ff_log2_16bit

/**
 * @addtogroup lavu_math
 * @{
 */

#ਜੇ HAVE_FAST_CLZ
#ਜੇ !defined(ff_ctz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctz))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_ctz(v) __builtin_ctz(v)
#ਜੇ_ਅੰਤ
#ਜੇ !defined(ff_ctzll) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctzll))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_ctzll(v) __builtin_ctzll(v)
#ਜੇ_ਅੰਤ
#ਜੇ !defined(ff_clz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_clz(v) __builtin_clz(v)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_ctz
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_ctz ff_ctz_c
/**
 * Trailing zero bit count.
 *
 * @param v  input value. If v is 0, the result is undefined.
 * @return   the number of trailing 0-bits
 */
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ ff_ctz_c(ਪੂਰਨ v)
{
    ਸਥਿਰ ਅਚਲ uint8_t debruijn_ctz32[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    ਵਾਪਸ debruijn_ctz32[(uint32_t)((v & -(uint32_t)v) * 0x077CB531U) >> 27];
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_ctzll
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_ctzll ff_ctzll_c
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ ff_ctzll_c(ਲੰਮਾ ਲੰਮਾ v)
{
    ਸਥਿਰ ਅਚਲ uint8_t debruijn_ctz64[64] = {
        0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
        62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
    };
    ਵਾਪਸ debruijn_ctz64[(uint64_t)((v & -(uint64_t)v) * 0x022FDD63CC95386DU) >> 58];
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_clz
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_clz ff_clz_c
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ ff_clz_c(ਬਿਨਾਨਿਸ਼ਾਨੀ x)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ i = ਆਕਾਰ(x) * 8;

    ਜਦੋਂ (x) {
        x >>= 1;
        i--;
    }

    ਵਾਪਸ i;
}
#ਜੇ_ਅੰਤ

#ਜੇ defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_parity)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_parity
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_parity __builtin_parity
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

/**
 * @}
 */
#ਜੇ_ਅੰਤ /* AVUTIL_INTMATH_H */
