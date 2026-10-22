/*
 * Copyright © 2022-2024 Rémi Denis-Courmont.
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

#अगर_अघोषित AVUTIL_RISCV_INTMATH_H
#घोषणा AVUTIL_RISCV_INTMATH_H

#समावेश <stdint.h>
#समावेश <math.h>

#समावेश "config.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#घोषणा av_clip_int8 av_clip_int8_rvi
अटल av_always_inline av_const int8_t av_clip_int8_rvi(पूर्णांक a)
{
    जोड़ { uint8_t u; int8_t s; } u = { .u = a };

    अगर (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    वापस a;
}

#घोषणा av_clip_int16 av_clip_int16_rvi
अटल av_always_inline av_const int16_t av_clip_int16_rvi(पूर्णांक a)
{
    जोड़ { uint16_t u; int16_t s; } u = { .u = a };

    अगर (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    वापस a;
}

#घोषणा av_clipl_int32 av_clipl_int32_rvi
अटल av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    जोड़ { uint32_t u; int32_t s; } u = { .u = a };

    अगर (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    वापस a;
}

#घोषणा av_clip_intp2 av_clip_intp2_rvi
अटल av_always_inline av_const पूर्णांक av_clip_intp2_rvi(पूर्णांक a, पूर्णांक p)
{
    स्थिर पूर्णांक shift = 31 - p;
    पूर्णांक b = ((पूर्णांक)(((अचिन्हित)a) << shift)) >> shift;

    अगर (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    वापस b;
}

#अगर defined (__riscv_f) || defined (__riscv_zfinx)
#घोषणा av_clipf av_clipf_rvf
अटल av_always_inline av_const भग्न av_clipf_rvf(भग्न a, भग्न min,
                                                    भग्न max)
{
    वापस fminf(fmaxf(a, min), max);
}
#पूर्ण_अगर

#अगर defined (__riscv_d) || defined (__riscv_zdinx)
#घोषणा av_clipd av_clipd_rvd
अटल av_always_inline av_const द्विगुन av_clipd_rvd(द्विगुन a, द्विगुन min,
                                                     द्विगुन max)
{
    वापस fmin(fmax(a, min), max);
}
#पूर्ण_अगर

#अगर defined (__GNUC__) || defined (__clang__)
अटल अंतरभूत av_const पूर्णांक ff_ctz_rv(पूर्णांक x)
{
#अगर HAVE_RV && !defined(__riscv_zbb)
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#अगर __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#अन्यथा
            "ctz     %0, %1\n"
#पूर्ण_अगर
            ".option pop" : "=r" (y) : "r" (x));
        अगर (y > 32)
            __builtin_unreachable();
        वापस y;
    }
#पूर्ण_अगर
    वापस __builtin_ctz(x);
}
#घोषणा ff_ctz ff_ctz_rv

अटल अंतरभूत av_const पूर्णांक ff_ctzll_rv(दीर्घ दीर्घ x)
{
#अगर HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        अगर (y > 64)
            __builtin_unreachable();
        वापस y;
    }
#पूर्ण_अगर
    वापस __builtin_ctzll(x);
}
#घोषणा ff_ctzll ff_ctzll_rv

अटल अंतरभूत av_const पूर्णांक ff_clz_rv(पूर्णांक x)
{
#अगर HAVE_RV && !defined(__riscv_zbb)
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#अगर __riscv_xlen >= 64
            "clzw    %0, %1\n"
#अन्यथा
            "clz     %0, %1\n"
#पूर्ण_अगर
            ".option pop" : "=r" (y) : "r" (x));
        अगर (y > 32)
            __builtin_unreachable();
        वापस y;
    }
#पूर्ण_अगर
    वापस __builtin_clz(x);
}
#घोषणा ff_clz ff_clz_rv

#अगर __riscv_xlen == 64
अटल अंतरभूत av_const पूर्णांक ff_clzll_rv(दीर्घ दीर्घ x)
{
#अगर HAVE_RV && !defined(__riscv_zbb)
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        अगर (y > 64)
            __builtin_unreachable();
        वापस y;
    }
#पूर्ण_अगर
    वापस __builtin_clzll(x);
}
#घोषणा ff_clz ff_clz_rv
#पूर्ण_अगर

अटल अंतरभूत av_const पूर्णांक ff_log2_rv(अचिन्हित पूर्णांक x)
{
    वापस 31 - ff_clz_rv(x | 1);
}
#घोषणा ff_log2 ff_log2_rv
#घोषणा ff_log2_16bit ff_log2_rv

अटल अंतरभूत av_const पूर्णांक av_popcount_rv(अचिन्हित पूर्णांक x)
{
#अगर HAVE_RV && !defined(__riscv_zbb)
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#अगर __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#अन्यथा
            "cpop    %0, %1\n"
#पूर्ण_अगर
            ".option pop" : "=r" (y) : "r" (x));
        अगर (y > 32)
            __builtin_unreachable();
        वापस y;
    }
#पूर्ण_अगर
    वापस __builtin_popcount(x);
}
#घोषणा av_popcount av_popcount_rv

अटल अंतरभूत av_const पूर्णांक av_popcount64_rv(uint64_t x)
{
#अगर HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        अगर (y > 64)
            __builtin_unreachable();
        वापस y;
    }
#पूर्ण_अगर
    वापस __builtin_popcountl(x);
}
#घोषणा av_popcount64 av_popcount64_rv

अटल अंतरभूत av_const पूर्णांक av_parity_rv(अचिन्हित पूर्णांक x)
{
#अगर HAVE_RV && !defined(__riscv_zbb)
    अगर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#अगर __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#अन्यथा
            "cpop    %0, %1\n"
#पूर्ण_अगर
            ".option pop" : "=r" (y) : "r" (x));
        वापस y & 1;
    }
#पूर्ण_अगर
    वापस __builtin_parity(x);
}
#घोषणा av_parity av_parity_rv
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_RISCV_INTMATH_H */
