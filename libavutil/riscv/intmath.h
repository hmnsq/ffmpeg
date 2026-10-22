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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <math.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
ಸ್ಥಿರ av_always_inline av_const int8_t av_clip_int8_rvi(ಪೂರ್ಣಾಙ್ಕ a)
{
    ಸಙ್ಘ { uint8_t u; int8_t s; } u = { .u = a };

    ಯದಿ (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    ಪ್ರತ್ಯಾಗಮ a;
}

#define av_clip_int16 av_clip_int16_rvi
ಸ್ಥಿರ av_always_inline av_const int16_t av_clip_int16_rvi(ಪೂರ್ಣಾಙ್ಕ a)
{
    ಸಙ್ಘ { uint16_t u; int16_t s; } u = { .u = a };

    ಯದಿ (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    ಪ್ರತ್ಯಾಗಮ a;
}

#define av_clipl_int32 av_clipl_int32_rvi
ಸ್ಥಿರ av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    ಸಙ್ಘ { uint32_t u; int32_t s; } u = { .u = a };

    ಯದಿ (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    ಪ್ರತ್ಯಾಗಮ a;
}

#define av_clip_intp2 av_clip_intp2_rvi
ಸ್ಥಿರ av_always_inline av_const ಪೂರ್ಣಾಙ್ಕ av_clip_intp2_rvi(ಪೂರ್ಣಾಙ್ಕ a, ಪೂರ್ಣಾಙ್ಕ p)
{
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ shift = 31 - p;
    ಪೂರ್ಣಾಙ್ಕ b = ((ಪೂರ್ಣಾಙ್ಕ)(((unsigned)a) << shift)) >> shift;

    ಯದಿ (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    ಪ್ರತ್ಯಾಗಮ b;
}

#ಯದಿ defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
ಸ್ಥಿರ av_always_inline av_const ಭಿನ್ನ av_clipf_rvf(ಭಿನ್ನ a, ಭಿನ್ನ min,
                                                    ಭಿನ್ನ max)
{
    ಪ್ರತ್ಯಾಗಮ fminf(fmaxf(a, min), max);
}
#endif

#ಯದಿ defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
ಸ್ಥಿರ av_always_inline av_const ದ್ವಿಗುಣ av_clipd_rvd(ದ್ವಿಗುಣ a, ದ್ವಿಗುಣ min,
                                                     ದ್ವಿಗುಣ max)
{
    ಪ್ರತ್ಯಾಗಮ fmin(fmax(a, min), max);
}
#endif

#ಯದಿ defined (__GNUC__) || defined (__clang__)
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ ff_ctz_rv(ಪೂರ್ಣಾಙ್ಕ x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb)
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಯದಿ __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#ಅನ್ಯಥಾ
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ಯದಿ (y > 32)
            __builtin_unreachable();
        ಪ್ರತ್ಯಾಗಮ y;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ ff_ctzll_rv(long long x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಯದಿ (y > 64)
            __builtin_unreachable();
        ಪ್ರತ್ಯಾಗಮ y;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ ff_clz_rv(ಪೂರ್ಣಾಙ್ಕ x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb)
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಯದಿ __riscv_xlen >= 64
            "clzw    %0, %1\n"
#ಅನ್ಯಥಾ
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ಯದಿ (y > 32)
            __builtin_unreachable();
        ಪ್ರತ್ಯಾಗಮ y;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#ಯದಿ __riscv_xlen == 64
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ ff_clzll_rv(long long x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb)
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಯದಿ (y > 64)
            __builtin_unreachable();
        ಪ್ರತ್ಯಾಗಮ y;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ ff_log2_rv(unsigned ಪೂರ್ಣಾಙ್ಕ x)
{
    ಪ್ರತ್ಯಾಗಮ 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ av_popcount_rv(unsigned ಪೂರ್ಣಾಙ್ಕ x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb)
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಯದಿ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ಅನ್ಯಥಾ
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ಯದಿ (y > 32)
            __builtin_unreachable();
        ಪ್ರತ್ಯಾಗಮ y;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ av_popcount64_rv(uint64_t x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಯದಿ (y > 64)
            __builtin_unreachable();
        ಪ್ರತ್ಯಾಗಮ y;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_const ಪೂರ್ಣಾಙ್ಕ av_parity_rv(unsigned ಪೂರ್ಣಾಙ್ಕ x)
{
#ಯದಿ HAVE_RV && !defined(__riscv_zbb)
    ಯದಿ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಙ್ಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಯದಿ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ಅನ್ಯಥಾ
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ಪ್ರತ್ಯಾಗಮ y & 1;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
