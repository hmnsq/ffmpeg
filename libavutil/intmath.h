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

#अगर_अघोषित AVUTIL_INTMATH_H
#घोषणा AVUTIL_INTMATH_H

#समावेश <stdint.h>

#समावेश "config.h"
#समावेश "attributes.h"

#अगर ARCH_ARM
#   include "arm/intmath.h"
#या_अगर ARCH_RISCV
#   include "riscv/intmath.h"
#या_अगर ARCH_X86
#   include "x86/intmath.h"
#पूर्ण_अगर

#अगर HAVE_FAST_CLZ
#अगर defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz)
#अगर_अघोषित ff_log2
#   define ff_log2(x) (31 - __builtin_clz((x)|1))
#   ifndef ff_log2_16bit
#      define ff_log2_16bit av_log2
#   endif
#पूर्ण_अगर /* ff_log2 */
#पूर्ण_अगर /* defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz) */
#पूर्ण_अगर

बाह्य स्थिर uint8_t ff_log2_tab[256];

#अगर_अघोषित ff_log2
#घोषणा ff_log2 ff_log2_c
अटल av_always_inline av_const पूर्णांक ff_log2_c(अचिन्हित पूर्णांक v)
{
    पूर्णांक n = 0;
    अगर (v & 0xffff0000) {
        v >>= 16;
        n += 16;
    }
    अगर (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    वापस n;
}
#पूर्ण_अगर

#अगर_अघोषित ff_log2_16bit
#घोषणा ff_log2_16bit ff_log2_16bit_c
अटल av_always_inline av_const पूर्णांक ff_log2_16bit_c(अचिन्हित पूर्णांक v)
{
    पूर्णांक n = 0;
    अगर (v & 0xff00) {
        v >>= 8;
        n += 8;
    }
    n += ff_log2_tab[v];

    वापस n;
}
#पूर्ण_अगर

#घोषणा av_log2       ff_log2
#घोषणा av_log2_16bit ff_log2_16bit

/**
 * @addtogroup lavu_math
 * @{
 */

#अगर HAVE_FAST_CLZ
#अगर !defined(ff_ctz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctz))
#घोषणा ff_ctz(v) __builtin_ctz(v)
#पूर्ण_अगर
#अगर !defined(ff_ctzll) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_ctzll))
#घोषणा ff_ctzll(v) __builtin_ctzll(v)
#पूर्ण_अगर
#अगर !defined(ff_clz) && (defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_clz))
#घोषणा ff_clz(v) __builtin_clz(v)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित ff_ctz
#घोषणा ff_ctz ff_ctz_c
/**
 * Trailing zero bit count.
 *
 * @param v  input value. If v is 0, the result is undefined.
 * @return   the number of trailing 0-bits
 */
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
अटल av_always_inline av_const पूर्णांक ff_ctz_c(पूर्णांक v)
{
    अटल स्थिर uint8_t debruijn_ctz32[32] = {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    वापस debruijn_ctz32[(uint32_t)((v & -(uint32_t)v) * 0x077CB531U) >> 27];
}
#पूर्ण_अगर

#अगर_अघोषित ff_ctzll
#घोषणा ff_ctzll ff_ctzll_c
/* We use the De-Bruijn method outlined in:
 * http://supertech.csail.mit.edu/papers/debruijn.pdf. */
अटल av_always_inline av_const पूर्णांक ff_ctzll_c(दीर्घ दीर्घ v)
{
    अटल स्थिर uint8_t debruijn_ctz64[64] = {
        0, 1, 2, 53, 3, 7, 54, 27, 4, 38, 41, 8, 34, 55, 48, 28,
        62, 5, 39, 46, 44, 42, 22, 9, 24, 35, 59, 56, 49, 18, 29, 11,
        63, 52, 6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
        51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
    };
    वापस debruijn_ctz64[(uint64_t)((v & -(uint64_t)v) * 0x022FDD63CC95386DU) >> 58];
}
#पूर्ण_अगर

#अगर_अघोषित ff_clz
#घोषणा ff_clz ff_clz_c
अटल av_always_inline av_const अचिन्हित ff_clz_c(अचिन्हित x)
{
    अचिन्हित i = माप(x) * 8;

    जबतक (x) {
        x >>= 1;
        i--;
    }

    वापस i;
}
#पूर्ण_अगर

#अगर defined(__GNUC__) || AV_HAS_BUILTIN(__builtin_parity)
#अगर_अघोषित av_parity
#घोषणा av_parity __builtin_parity
#पूर्ण_अगर
#पूर्ण_अगर

/**
 * @}
 */
#पूर्ण_अगर /* AVUTIL_INTMATH_H */
