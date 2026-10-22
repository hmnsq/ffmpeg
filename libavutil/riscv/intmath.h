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
स्थिर av_always_inline av_const int8_t av_clip_int8_rvi(पूर्णाङ्क a)
{
    सङ्घ { uint8_t u; int8_t s; } u = { .u = a };

    सचे (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    पटिनिवत्त a;
}

#define av_clip_int16 av_clip_int16_rvi
स्थिर av_always_inline av_const int16_t av_clip_int16_rvi(पूर्णाङ्क a)
{
    सङ्घ { uint16_t u; int16_t s; } u = { .u = a };

    सचे (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    पटिनिवत्त a;
}

#define av_clipl_int32 av_clipl_int32_rvi
स्थिर av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    सङ्घ { uint32_t u; int32_t s; } u = { .u = a };

    सचे (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    पटिनिवत्त a;
}

#define av_clip_intp2 av_clip_intp2_rvi
स्थिर av_always_inline av_const पूर्णाङ्क av_clip_intp2_rvi(पूर्णाङ्क a, पूर्णाङ्क p)
{
    ध्रुव पूर्णाङ्क shift = 31 - p;
    पूर्णाङ्क b = ((पूर्णाङ्क)(((unsigned)a) << shift)) >> shift;

    सचे (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    पटिनिवत्त b;
}

#सचे defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
स्थिर av_always_inline av_const भिन्न av_clipf_rvf(भिन्न a, भिन्न min,
                                                    भिन्न max)
{
    पटिनिवत्त fminf(fmaxf(a, min), max);
}
#endif

#सचे defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
स्थिर av_always_inline av_const द्विगुण av_clipd_rvd(द्विगुण a, द्विगुण min,
                                                     द्विगुण max)
{
    पटिनिवत्त fmin(fmax(a, min), max);
}
#endif

#सचे defined (__GNUC__) || defined (__clang__)
स्थिर अन्तःस्थ av_const पूर्णाङ्क ff_ctz_rv(पूर्णाङ्क x)
{
#सचे HAVE_RV && !defined(__riscv_zbb)
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#सचे __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#अञ्ञथा
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        सचे (y > 32)
            __builtin_unreachable();
        पटिनिवत्त y;
    }
#endif
    पटिनिवत्त __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

स्थिर अन्तःस्थ av_const पूर्णाङ्क ff_ctzll_rv(long long x)
{
#सचे HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        सचे (y > 64)
            __builtin_unreachable();
        पटिनिवत्त y;
    }
#endif
    पटिनिवत्त __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

स्थिर अन्तःस्थ av_const पूर्णाङ्क ff_clz_rv(पूर्णाङ्क x)
{
#सचे HAVE_RV && !defined(__riscv_zbb)
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#सचे __riscv_xlen >= 64
            "clzw    %0, %1\n"
#अञ्ञथा
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        सचे (y > 32)
            __builtin_unreachable();
        पटिनिवत्त y;
    }
#endif
    पटिनिवत्त __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#सचे __riscv_xlen == 64
स्थिर अन्तःस्थ av_const पूर्णाङ्क ff_clzll_rv(long long x)
{
#सचे HAVE_RV && !defined(__riscv_zbb)
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        सचे (y > 64)
            __builtin_unreachable();
        पटिनिवत्त y;
    }
#endif
    पटिनिवत्त __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

स्थिर अन्तःस्थ av_const पूर्णाङ्क ff_log2_rv(unsigned पूर्णाङ्क x)
{
    पटिनिवत्त 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

स्थिर अन्तःस्थ av_const पूर्णाङ्क av_popcount_rv(unsigned पूर्णाङ्क x)
{
#सचे HAVE_RV && !defined(__riscv_zbb)
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#सचे __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#अञ्ञथा
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        सचे (y > 32)
            __builtin_unreachable();
        पटिनिवत्त y;
    }
#endif
    पटिनिवत्त __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

स्थिर अन्तःस्थ av_const पूर्णाङ्क av_popcount64_rv(uint64_t x)
{
#सचे HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        सचे (y > 64)
            __builtin_unreachable();
        पटिनिवत्त y;
    }
#endif
    पटिनिवत्त __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

स्थिर अन्तःस्थ av_const पूर्णाङ्क av_parity_rv(unsigned पूर्णाङ्क x)
{
#सचे HAVE_RV && !defined(__riscv_zbb)
    सचे (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        पूर्णाङ्क y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#सचे __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#अञ्ञथा
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        पटिनिवत्त y & 1;
    }
#endif
    पटिनिवत्त __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
