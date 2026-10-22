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

#यदि_अपरिभाषितम् AVUTIL_INTMATH_H
#परिभाषय AVUTIL_INTMATH_H

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "attributes.h"

#यदि ARCH_ARM
#   include "arm/intmath.h"
#नोचेद्यदि ARCH_RISCV
#   include "riscv/intmath.h"
#नोचेद्यदि ARCH_X86
#   include "x86/intmath.h"
#यदि_अन्तः

#यदि HAVE_FAST_CLZ
#यदि defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz)
#यदि_अपरिभाषितम् ff_log2
#   define ff_log2(x) (31 - __builtin_clz((x)|1))
#   ifndef ff_log2_16bit
#      define ff_log2_16bit av_log2
#   endif
#यदि_अन्तः /* ff_log2 */
#यदि_अन्तः /* defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz) */
#यदि_अन्तः

बाह्य ध्रुव uint8_t ff_log2_tab[256];

#यदि_अपरिभाषितम् ff_log2
#परिभाषय ff_log2 ff_log2_c
स्थिर av_always_inline av_const पूर्णाङ्क ff_log2_c(अचिह्नित पूर्णाङ्क v)
{
    पूर्णाङ्क n = 0;
    यदि (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    यदि (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    प्रत्यागम n;
}
#यदि_अन्तः

#यदि_अपरिभाषितम् ff_log2_16bit
#परिभाषय ff_log2_16bit ff_log2_16bit_c
स्थिर av_always_inline av_const पूर्णाङ्क ff_log2_16bit_c(अचिह्नित पूर्णाङ्क v)
{
    पूर्णाङ्क n = 0;
    यदि (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    प्रत्यागम n;
}
#यदि_अन्तः

#परिभाषय av_log2       ff_log2
#परिभाषय av_log2_16bit ff_log2_16bit

/**
 * @addtogroup lavu_math
 * @{
 */

#यदि HAVE_FAST_CLZ
#यदि !defined(ff_ctz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctz))
#परिभाषय ff_ctz(v) __builtin_ctz(v)
#यदि_अन्तः
#यदि !defined(ff_ctzll) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctzll))
#परिभाषय ff_ctzll(v) __builtin_ctzll(v)
#यदि_अन्तः
#यदि !defined(ff_clz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz))
#परिभाषय ff_clz(v) __builtin_clz(v)
#यदि_अन्तः
#यदि_अन्तः

#यदि_अपरिभाषितम् ff_ctz
#परिभाषय ff_ctz ff_ctz_c
/**
 * Trailing zero bit count.
 *
 * @param v  input value. If v is 0, the result is undefined.
 * @return   the number of trailing 0-bits
 */
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
स्थिर av_always_inline av_const पूर्णाङ्क ff_ctz_c(पूर्णाङ्क v)
{
    स्थिर ध्रुव uint8_t debruijn_ctz32[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    प्रत्यागम debruijn_ctz32[(uint32_t)((v & -(uint32_t)v) * 0x077CB531U) >> 27];
}
#यदि_अन्तः

#यदि_अपरिभाषितम् ff_ctzll
#परिभाषय ff_ctzll ff_ctzll_c
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
स्थिर av_always_inline av_const पूर्णाङ्क ff_ctzll_c(दीर्घ दीर्घ v)
{
    स्थिर ध्रुव uint8_t debruijn_ctz64[64] = {
        0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
        62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
    };
    प्रत्यागम debruijn_ctz64[(uint64_t)((v & -(uint64_t)v) * 0x022FDD63CC95386DU) >> 58];
}
#यदि_अन्तः

#यदि_अपरिभाषितम् ff_clz
#परिभाषय ff_clz ff_clz_c
स्थिर av_always_inline av_const अचिह्नित ff_clz_c(अचिह्नित x)
{
    अचिह्नित i = परिमाण(x) * 8;

    यावत् (x) {
        x >>= 1;
        i--;
    }

    प्रत्यागम i;
}
#यदि_अन्तः

#यदि defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_parity)
#यदि_अपरिभाषितम् av_parity
#परिभाषय av_parity __builtin_parity
#यदि_अन्तः
#यदि_अन्तः

/**
 * @}
 */
#यदि_अन्तः /* AVUTIL_INTMATH_H */
