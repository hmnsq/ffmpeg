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

#اگر_غیر_تعریف_شدہ AVUTIL_INTMATH_H
#تعریف_کرو AVUTIL_INTMATH_H

#شامل <stdint.h>

#شامل "config.h"
#شامل "attributes.h"

#اگر ARCH_ARM
#   include "arm/intmath.h"
#وگرنہ_اگر ARCH_RISCV
#   include "riscv/intmath.h"
#وگرنہ_اگر ARCH_X86
#   include "x86/intmath.h"
#اگر_ختم

#اگر HAVE_FAST_CLZ
#اگر defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz)
#اگر_غیر_تعریف_شدہ ff_log2
#   define ff_log2(x) (31 - __builtin_clz((x)|1))
#   ifndef ff_log2_16bit
#      define ff_log2_16bit av_log2
#   endif
#اگر_ختم /* ff_log2 */
#اگر_ختم /* defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz) */
#اگر_ختم

خارجی ثابت uint8_t ff_log2_tab[256];

#اگر_غیر_تعریف_شدہ ff_log2
#تعریف_کرو ff_log2 ff_log2_c
ساکن av_always_inline av_const صحیح ff_log2_c(غیرعلامتی صحیح v)
{
    صحیح n = 0;
    اگر (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    اگر (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    واپس n;
}
#اگر_ختم

#اگر_غیر_تعریف_شدہ ff_log2_16bit
#تعریف_کرو ff_log2_16bit ff_log2_16bit_c
ساکن av_always_inline av_const صحیح ff_log2_16bit_c(غیرعلامتی صحیح v)
{
    صحیح n = 0;
    اگر (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    واپس n;
}
#اگر_ختم

#تعریف_کرو av_log2       ff_log2
#تعریف_کرو av_log2_16bit ff_log2_16bit

/**
 * @addtogroup lavu_math
 * @{
 */

#اگر HAVE_FAST_CLZ
#اگر !defined(ff_ctz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctz))
#تعریف_کرو ff_ctz(v) __builtin_ctz(v)
#اگر_ختم
#اگر !defined(ff_ctzll) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctzll))
#تعریف_کرو ff_ctzll(v) __builtin_ctzll(v)
#اگر_ختم
#اگر !defined(ff_clz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz))
#تعریف_کرو ff_clz(v) __builtin_clz(v)
#اگر_ختم
#اگر_ختم

#اگر_غیر_تعریف_شدہ ff_ctz
#تعریف_کرو ff_ctz ff_ctz_c
/**
 * Trailing zero bit count.
 *
 * @param v  input value. If v is 0, the result is undefined.
 * @return   the number of trailing 0-bits
 */
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
ساکن av_always_inline av_const صحیح ff_ctz_c(صحیح v)
{
    ساکن ثابت uint8_t debruijn_ctz32[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    واپس debruijn_ctz32[(uint32_t)((v & -(uint32_t)v) * 0x077CB531U) >> 27];
}
#اگر_ختم

#اگر_غیر_تعریف_شدہ ff_ctzll
#تعریف_کرو ff_ctzll ff_ctzll_c
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
ساکن av_always_inline av_const صحیح ff_ctzll_c(طویل طویل v)
{
    ساکن ثابت uint8_t debruijn_ctz64[64] = {
        0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
        62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
    };
    واپس debruijn_ctz64[(uint64_t)((v & -(uint64_t)v) * 0x022FDD63CC95386DU) >> 58];
}
#اگر_ختم

#اگر_غیر_تعریف_شدہ ff_clz
#تعریف_کرو ff_clz ff_clz_c
ساکن av_always_inline av_const غیرعلامتی ff_clz_c(غیرعلامتی x)
{
    غیرعلامتی i = حجم(x) * 8;

    جب (x) {
        x >>= 1;
        i--;
    }

    واپس i;
}
#اگر_ختم

#اگر defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_parity)
#اگر_غیر_تعریف_شدہ av_parity
#تعریف_کرو av_parity __builtin_parity
#اگر_ختم
#اگر_ختم

/**
 * @}
 */
#اگر_ختم /* AVUTIL_INTMATH_H */
