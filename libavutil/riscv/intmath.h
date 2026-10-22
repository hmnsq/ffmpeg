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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_RISCV_INTMATH_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_RISCV_INTMATH_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <math.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು av_clip_int8 av_clip_int8_rvi
ಸ್ಥಿರ av_always_inline av_const int8_t av_clip_int8_rvi(ಪೂರ್ಣಾಂಕ a)
{
    ಒಕ್ಕೂಟ { uint8_t u; int8_t s; } u = { .u = a };

    ಆದರೆ (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    ಹಿಂತಿರುಗಿ a;
}

#ವ್ಯಾಖ್ಯಾನಿಸು av_clip_int16 av_clip_int16_rvi
ಸ್ಥಿರ av_always_inline av_const int16_t av_clip_int16_rvi(ಪೂರ್ಣಾಂಕ a)
{
    ಒಕ್ಕೂಟ { uint16_t u; int16_t s; } u = { .u = a };

    ಆದರೆ (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    ಹಿಂತಿರುಗಿ a;
}

#ವ್ಯಾಖ್ಯಾನಿಸು av_clipl_int32 av_clipl_int32_rvi
ಸ್ಥಿರ av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    ಒಕ್ಕೂಟ { uint32_t u; int32_t s; } u = { .u = a };

    ಆದರೆ (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    ಹಿಂತಿರುಗಿ a;
}

#ವ್ಯಾಖ್ಯಾನಿಸು av_clip_intp2 av_clip_intp2_rvi
ಸ್ಥಿರ av_always_inline av_const ಪೂರ್ಣಾಂಕ av_clip_intp2_rvi(ಪೂರ್ಣಾಂಕ a, ಪೂರ್ಣಾಂಕ p)
{
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಸರಿಸು = 31 - p;
    ಪೂರ್ಣಾಂಕ b = ((ಪೂರ್ಣಾಂಕ)(((ಚಿಹ್ನೆರಹಿತ)a) << ಸರಿಸು)) >> ಸರಿಸು;

    ಆದರೆ (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    ಹಿಂತಿರುಗಿ b;
}

#ಆದರೆ defined (__riscv_f) || defined (__riscv_zfinx)
#ವ್ಯಾಖ್ಯಾನಿಸು av_clipf av_clipf_rvf
ಸ್ಥಿರ av_always_inline av_const ದಶಮಾಂಶ av_clipf_rvf(ದಶಮಾಂಶ a, ದಶಮಾಂಶ min,
                                                    ದಶಮಾಂಶ max)
{
    ಹಿಂತಿರುಗಿ fminf(fmaxf(a, min), max);
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined (__riscv_d) || defined (__riscv_zdinx)
#ವ್ಯಾಖ್ಯಾನಿಸು av_clipd av_clipd_rvd
ಸ್ಥಿರ av_always_inline av_const ದ್ವಿಗುಣ av_clipd_rvd(ದ್ವಿಗುಣ a, ದ್ವಿಗುಣ min,
                                                     ದ್ವಿಗುಣ max)
{
    ಹಿಂತಿರುಗಿ fmin(fmax(a, min), max);
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined (__GNUC__) || defined (__clang__)
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ ff_ctz_rv(ಪೂರ್ಣಾಂಕ x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಆದರೆ __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#ಇಲ್ಲದಿದ್ದರೆ
            "ctz     %0, %1\n"
#ಆದರೆ_ಅಂತ್ಯ
            ".option pop" : "=r" (y) : "r" (x));
        ಆದರೆ (y > 32)
            __builtin_unreachable();
        ಹಿಂತಿರುಗಿ y;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_ctz(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು ff_ctz ff_ctz_rv

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ ff_ctzll_rv(ದೀರ್ಘ ದೀರ್ಘ x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಆದರೆ (y > 64)
            __builtin_unreachable();
        ಹಿಂತಿರುಗಿ y;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_ctzll(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು ff_ctzll ff_ctzll_rv

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ ff_clz_rv(ಪೂರ್ಣಾಂಕ x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಆದರೆ __riscv_xlen >= 64
            "clzw    %0, %1\n"
#ಇಲ್ಲದಿದ್ದರೆ
            "clz     %0, %1\n"
#ಆದರೆ_ಅಂತ್ಯ
            ".option pop" : "=r" (y) : "r" (x));
        ಆದರೆ (y > 32)
            __builtin_unreachable();
        ಹಿಂತಿರುಗಿ y;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_clz(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು ff_clz ff_clz_rv

#ಆದರೆ __riscv_xlen == 64
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ ff_clzll_rv(ದೀರ್ಘ ದೀರ್ಘ x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಆದರೆ (y > 64)
            __builtin_unreachable();
        ಹಿಂತಿರುಗಿ y;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_clzll(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು ff_clz ff_clz_rv
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ ff_log2_rv(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x)
{
    ಹಿಂತಿರುಗಿ 31 - ff_clz_rv(x | 1);
}
#ವ್ಯಾಖ್ಯಾನಿಸು ff_log2 ff_log2_rv
#ವ್ಯಾಖ್ಯಾನಿಸು ff_log2_16bit ff_log2_rv

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ av_popcount_rv(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಆದರೆ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ಇಲ್ಲದಿದ್ದರೆ
            "cpop    %0, %1\n"
#ಆದರೆ_ಅಂತ್ಯ
            ".option pop" : "=r" (y) : "r" (x));
        ಆದರೆ (y > 32)
            __builtin_unreachable();
        ಹಿಂತಿರುಗಿ y;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_popcount(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು av_popcount av_popcount_rv

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ av_popcount64_rv(uint64_t x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಆದರೆ (y > 64)
            __builtin_unreachable();
        ಹಿಂತಿರುಗಿ y;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_popcountl(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು av_popcount64 av_popcount64_rv

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const ಪೂರ್ಣಾಂಕ av_parity_rv(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ಪೂರ್ಣಾಂಕ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ಆದರೆ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ಇಲ್ಲದಿದ್ದರೆ
            "cpop    %0, %1\n"
#ಆದರೆ_ಅಂತ್ಯ
            ".option pop" : "=r" (y) : "r" (x));
        ಹಿಂತಿರುಗಿ y & 1;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_parity(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು av_parity av_parity_rv
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_RISCV_INTMATH_H */
