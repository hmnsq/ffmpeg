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

#నిర్వచితం_కాకపోతే AVUTIL_RISCV_INTMATH_H
#నిర్వచించు AVUTIL_RISCV_INTMATH_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <math.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#నిర్వచించు av_clip_int8 av_clip_int8_rvi
స్థిర av_always_inline av_const int8_t av_clip_int8_rvi(పూర్ణాంకం a)
{
    సంఘం { uint8_t u; int8_t s; } u = { .u = a };

    ఒకవేళ (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    తిరిగి a;
}

#నిర్వచించు av_clip_int16 av_clip_int16_rvi
స్థిర av_always_inline av_const int16_t av_clip_int16_rvi(పూర్ణాంకం a)
{
    సంఘం { uint16_t u; int16_t s; } u = { .u = a };

    ఒకవేళ (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    తిరిగి a;
}

#నిర్వచించు av_clipl_int32 av_clipl_int32_rvi
స్థిర av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    సంఘం { uint32_t u; int32_t s; } u = { .u = a };

    ఒకవేళ (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    తిరిగి a;
}

#నిర్వచించు av_clip_intp2 av_clip_intp2_rvi
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_intp2_rvi(పూర్ణాంకం a, పూర్ణాంకం p)
{
    స్థిరరాశి పూర్ణాంకం జరుపు = 31 - p;
    పూర్ణాంకం b = ((పూర్ణాంకం)(((గుర్తులేని)a) << జరుపు)) >> జరుపు;

    ఒకవేళ (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    తిరిగి b;
}

#ఒకవేళ defined (__riscv_f) || defined (__riscv_zfinx)
#నిర్వచించు av_clipf av_clipf_rvf
స్థిర av_always_inline av_const దశాంశం av_clipf_rvf(దశాంశం a, దశాంశం min,
                                                    దశాంశం max)
{
    తిరిగి fminf(fmaxf(a, min), max);
}
#అయితే_ముగింపు

#ఒకవేళ defined (__riscv_d) || defined (__riscv_zdinx)
#నిర్వచించు av_clipd av_clipd_rvd
స్థిర av_always_inline av_const ద్విగుణ av_clipd_rvd(ద్విగుణ a, ద్విగుణ min,
                                                     ద్విగుణ max)
{
    తిరిగి fmin(fmax(a, min), max);
}
#అయితే_ముగింపు

#ఒకవేళ defined (__GNUC__) || defined (__clang__)
స్థిర అంతఃవరుస av_const పూర్ణాంకం ff_ctz_rv(పూర్ణాంకం x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb)
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ఒకవేళ __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#లేకపోతే
            "ctz     %0, %1\n"
#అయితే_ముగింపు
            ".option pop" : "=r" (y) : "r" (x));
        ఒకవేళ (y > 32)
            __builtin_unreachable();
        తిరిగి y;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_ctz(x);
}
#నిర్వచించు ff_ctz ff_ctz_rv

స్థిర అంతఃవరుస av_const పూర్ణాంకం ff_ctzll_rv(దీర్ఘ దీర్ఘ x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ఒకవేళ (y > 64)
            __builtin_unreachable();
        తిరిగి y;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_ctzll(x);
}
#నిర్వచించు ff_ctzll ff_ctzll_rv

స్థిర అంతఃవరుస av_const పూర్ణాంకం ff_clz_rv(పూర్ణాంకం x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb)
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ఒకవేళ __riscv_xlen >= 64
            "clzw    %0, %1\n"
#లేకపోతే
            "clz     %0, %1\n"
#అయితే_ముగింపు
            ".option pop" : "=r" (y) : "r" (x));
        ఒకవేళ (y > 32)
            __builtin_unreachable();
        తిరిగి y;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_clz(x);
}
#నిర్వచించు ff_clz ff_clz_rv

#ఒకవేళ __riscv_xlen == 64
స్థిర అంతఃవరుస av_const పూర్ణాంకం ff_clzll_rv(దీర్ఘ దీర్ఘ x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb)
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ఒకవేళ (y > 64)
            __builtin_unreachable();
        తిరిగి y;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_clzll(x);
}
#నిర్వచించు ff_clz ff_clz_rv
#అయితే_ముగింపు

స్థిర అంతఃవరుస av_const పూర్ణాంకం ff_log2_rv(గుర్తులేని పూర్ణాంకం x)
{
    తిరిగి 31 - ff_clz_rv(x | 1);
}
#నిర్వచించు ff_log2 ff_log2_rv
#నిర్వచించు ff_log2_16bit ff_log2_rv

స్థిర అంతఃవరుస av_const పూర్ణాంకం av_popcount_rv(గుర్తులేని పూర్ణాంకం x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb)
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ఒకవేళ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#లేకపోతే
            "cpop    %0, %1\n"
#అయితే_ముగింపు
            ".option pop" : "=r" (y) : "r" (x));
        ఒకవేళ (y > 32)
            __builtin_unreachable();
        తిరిగి y;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_popcount(x);
}
#నిర్వచించు av_popcount av_popcount_rv

స్థిర అంతఃవరుస av_const పూర్ణాంకం av_popcount64_rv(uint64_t x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ఒకవేళ (y > 64)
            __builtin_unreachable();
        తిరిగి y;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_popcountl(x);
}
#నిర్వచించు av_popcount64 av_popcount64_rv

స్థిర అంతఃవరుస av_const పూర్ణాంకం av_parity_rv(గుర్తులేని పూర్ణాంకం x)
{
#ఒకవేళ HAVE_RV && !defined(__riscv_zbb)
    ఒకవేళ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        పూర్ణాంకం y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ఒకవేళ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#లేకపోతే
            "cpop    %0, %1\n"
#అయితే_ముగింపు
            ".option pop" : "=r" (y) : "r" (x));
        తిరిగి y & 1;
    }
#అయితే_ముగింపు
    తిరిగి __builtin_parity(x);
}
#నిర్వచించు av_parity av_parity_rv
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_RISCV_INTMATH_H */
