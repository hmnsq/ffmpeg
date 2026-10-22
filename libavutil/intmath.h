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

#నిర్వచితం_కాకపోతే AVUTIL_INTMATH_H
#నిర్వచించు AVUTIL_INTMATH_H

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "attributes.h"

#ఒకవేళ ARCH_ARM
#   include "arm/intmath.h"
#లేదావేళ ARCH_RISCV
#   include "riscv/intmath.h"
#లేదావేళ ARCH_X86
#   include "x86/intmath.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_FAST_CLZ
#ఒకవేళ defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz)
#నిర్వచితం_కాకపోతే ff_log2
#   define ff_log2(x) (31 - __builtin_clz((x)|1))
#   ifndef ff_log2_16bit
#      define ff_log2_16bit av_log2
#   endif
#అయితే_ముగింపు /* ff_log2 */
#అయితే_ముగింపు /* defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz) */
#అయితే_ముగింపు

బాహ్య స్థిరరాశి uint8_t ff_log2_tab[256];

#నిర్వచితం_కాకపోతే ff_log2
#నిర్వచించు ff_log2 ff_log2_c
స్థిర av_always_inline av_const పూర్ణాంకం ff_log2_c(గుర్తులేని పూర్ణాంకం v)
{
    పూర్ణాంకం n = 0;
    ఒకవేళ (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    ఒకవేళ (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    తిరిగి n;
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే ff_log2_16bit
#నిర్వచించు ff_log2_16bit ff_log2_16bit_c
స్థిర av_always_inline av_const పూర్ణాంకం ff_log2_16bit_c(గుర్తులేని పూర్ణాంకం v)
{
    పూర్ణాంకం n = 0;
    ఒకవేళ (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    తిరిగి n;
}
#అయితే_ముగింపు

#నిర్వచించు av_log2       ff_log2
#నిర్వచించు av_log2_16bit ff_log2_16bit

/**
 * @addtogroup lavu_math
 * @{
 */

#ఒకవేళ HAVE_FAST_CLZ
#ఒకవేళ !defined(ff_ctz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctz))
#నిర్వచించు ff_ctz(v) __builtin_ctz(v)
#అయితే_ముగింపు
#ఒకవేళ !defined(ff_ctzll) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctzll))
#నిర్వచించు ff_ctzll(v) __builtin_ctzll(v)
#అయితే_ముగింపు
#ఒకవేళ !defined(ff_clz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz))
#నిర్వచించు ff_clz(v) __builtin_clz(v)
#అయితే_ముగింపు
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే ff_ctz
#నిర్వచించు ff_ctz ff_ctz_c
/**
 * Trailing zero bit count.
 *
 * @param v  input value. If v is 0, the result is undefined.
 * @return   the number of trailing 0-bits
 */
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
స్థిర av_always_inline av_const పూర్ణాంకం ff_ctz_c(పూర్ణాంకం v)
{
    స్థిర స్థిరరాశి uint8_t debruijn_ctz32[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    తిరిగి debruijn_ctz32[(uint32_t)((v & -(uint32_t)v) * 0x077CB531U) >> 27];
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే ff_ctzll
#నిర్వచించు ff_ctzll ff_ctzll_c
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
స్థిర av_always_inline av_const పూర్ణాంకం ff_ctzll_c(దీర్ఘ దీర్ఘ v)
{
    స్థిర స్థిరరాశి uint8_t debruijn_ctz64[64] = {
        0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
        62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
    };
    తిరిగి debruijn_ctz64[(uint64_t)((v & -(uint64_t)v) * 0x022FDD63CC95386DU) >> 58];
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే ff_clz
#నిర్వచించు ff_clz ff_clz_c
స్థిర av_always_inline av_const గుర్తులేని ff_clz_c(గుర్తులేని x)
{
    గుర్తులేని i = పరిమాణం(x) * 8;

    అయితే (x) {
        x >>= 1;
        i--;
    }

    తిరిగి i;
}
#అయితే_ముగింపు

#ఒకవేళ defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_parity)
#నిర్వచితం_కాకపోతే av_parity
#నిర్వచించు av_parity __builtin_parity
#అయితే_ముగింపు
#అయితే_ముగింపు

/**
 * @}
 */
#అయితే_ముగింపు /* AVUTIL_INTMATH_H */
