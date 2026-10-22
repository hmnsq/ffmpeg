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

#ifndef AVUTIL_RISCV_INTMATH_H
#define AVUTIL_RISCV_INTMATH_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <math.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
स्थिर av_always_inline av_const int8_t av_clip_int8_rvi(पूर्णांक a)
{
    संघ { uint8_t u; int8_t s; } u = { .u = a };

    जर (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    परत a;
}

#define av_clip_int16 av_clip_int16_rvi
स्थिर av_always_inline av_const int16_t av_clip_int16_rvi(पूर्णांक a)
{
    संघ { uint16_t u; int16_t s; } u = { .u = a };

    जर (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    परत a;
}

#define av_clipl_int32 av_clipl_int32_rvi
स्थिर av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    संघ { uint32_t u; int32_t s; } u = { .u = a };

    जर (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    परत a;
}

#define av_clip_intp2 av_clip_intp2_rvi
स्थिर av_always_inline av_const पूर्णांक av_clip_intp2_rvi(पूर्णांक a, पूर्णांक p)
{
    स्थिरांक पूर्णांक shift = 31 - p;
    पूर्णांक b = ((पूर्णांक)(((अचिन्हित)a) << shift)) >> shift;

    जर (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    परत b;
}

#जर defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
स्थिर av_always_inline av_const दशांश av_clipf_rvf(दशांश a, दशांश min,
                                                    दशांश max)
{
    परत fminf(fmaxf(a, min), max);
}
#endif

#जर defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
स्थिर av_always_inline av_const द्विगुण av_clipd_rvd(द्विगुण a, द्विगुण min,
                                                     द्विगुण max)
{
    परत fmin(fmax(a, min), max);
}
#endif

#जर defined (__GNUC__) || defined (__clang__)
स्थिर ओळीत av_const पूर्णांक ff_ctz_rv(पूर्णांक x)
{
#जर HAVE_RV && !defined(__riscv_zbb)
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#जर __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#अन्यथा
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        जर (y > 32)
            __builtin_unreachable();
        परत y;
    }
#endif
    परत __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

स्थिर ओळीत av_const पूर्णांक ff_ctzll_rv(दीर्घ दीर्घ x)
{
#जर HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        जर (y > 64)
            __builtin_unreachable();
        परत y;
    }
#endif
    परत __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

स्थिर ओळीत av_const पूर्णांक ff_clz_rv(पूर्णांक x)
{
#जर HAVE_RV && !defined(__riscv_zbb)
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#जर __riscv_xlen >= 64
            "clzw    %0, %1\n"
#अन्यथा
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        जर (y > 32)
            __builtin_unreachable();
        परत y;
    }
#endif
    परत __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#जर __riscv_xlen == 64
स्थिर ओळीत av_const पूर्णांक ff_clzll_rv(दीर्घ दीर्घ x)
{
#जर HAVE_RV && !defined(__riscv_zbb)
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        जर (y > 64)
            __builtin_unreachable();
        परत y;
    }
#endif
    परत __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

स्थिर ओळीत av_const पूर्णांक ff_log2_rv(अचिन्हित पूर्णांक x)
{
    परत 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

स्थिर ओळीत av_const पूर्णांक av_popcount_rv(अचिन्हित पूर्णांक x)
{
#जर HAVE_RV && !defined(__riscv_zbb)
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#जर __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#अन्यथा
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        जर (y > 32)
            __builtin_unreachable();
        परत y;
    }
#endif
    परत __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

स्थिर ओळीत av_const पूर्णांक av_popcount64_rv(uint64_t x)
{
#जर HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        जर (y > 64)
            __builtin_unreachable();
        परत y;
    }
#endif
    परत __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

स्थिर ओळीत av_const पूर्णांक av_parity_rv(अचिन्हित पूर्णांक x)
{
#जर HAVE_RV && !defined(__riscv_zbb)
    जर (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णांक y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#जर __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#अन्यथा
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        परत y & 1;
    }
#endif
    परत __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
