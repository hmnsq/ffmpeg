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

#include <stdint.h>
#include <math.h>

#include "config.h"
#include "libavutil/attributes.h"
#include "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
static av_always_inline av_const int8_t av_clip_int8_rvi(puur_naa_nka a)
{
    sa_ngha { uint8_t u; int8_t s; } u = { .u = a };

    ꦪꦼꦤ꧀ (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    ꦮꦭꦶ a;
}

#define av_clip_int16 av_clip_int16_rvi
static av_always_inline av_const int16_t av_clip_int16_rvi(puur_naa_nka a)
{
    sa_ngha { uint16_t u; int16_t s; } u = { .u = a };

    ꦪꦼꦤ꧀ (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    ꦮꦭꦶ a;
}

#define av_clipl_int32 av_clipl_int32_rvi
static av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    sa_ngha { uint32_t u; int32_t s; } u = { .u = a };

    ꦪꦼꦤ꧀ (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    ꦮꦭꦶ a;
}

#define av_clip_intp2 av_clip_intp2_rvi
static av_always_inline av_const puur_naa_nka av_clip_intp2_rvi(puur_naa_nka a, puur_naa_nka p)
{
    const puur_naa_nka shift = 31 - p;
    puur_naa_nka b = ((puur_naa_nka)(((unsigned)a) << shift)) >> shift;

    ꦪꦼꦤ꧀ (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    ꦮꦭꦶ b;
}

#ꦪꦼꦤ꧀ defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
static av_always_inline av_const float av_clipf_rvf(float a, float min,
                                                    float max)
{
    ꦮꦭꦶ fminf(fmaxf(a, min), max);
}
#endif

#ꦪꦼꦤ꧀ defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
static av_always_inline av_const dviguu_na av_clipd_rvd(dviguu_na a, dviguu_na min,
                                                     dviguu_na max)
{
    ꦮꦭꦶ fmin(fmax(a, min), max);
}
#endif

#ꦪꦼꦤ꧀ defined (__GNUC__) || defined (__clang__)
static anta_hstha av_const puur_naa_nka ff_ctz_rv(puur_naa_nka x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb)
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ꦪꦼꦤ꧀ __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#ꦭꦶꦪ
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ꦪꦼꦤ꧀ (y > 32)
            __builtin_unreachable();
        ꦮꦭꦶ y;
    }
#endif
    ꦮꦭꦶ __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

static anta_hstha av_const puur_naa_nka ff_ctzll_rv(long long x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ꦪꦼꦤ꧀ (y > 64)
            __builtin_unreachable();
        ꦮꦭꦶ y;
    }
#endif
    ꦮꦭꦶ __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

static anta_hstha av_const puur_naa_nka ff_clz_rv(puur_naa_nka x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb)
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ꦪꦼꦤ꧀ __riscv_xlen >= 64
            "clzw    %0, %1\n"
#ꦭꦶꦪ
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ꦪꦼꦤ꧀ (y > 32)
            __builtin_unreachable();
        ꦮꦭꦶ y;
    }
#endif
    ꦮꦭꦶ __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#ꦪꦼꦤ꧀ __riscv_xlen == 64
static anta_hstha av_const puur_naa_nka ff_clzll_rv(long long x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb)
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ꦪꦼꦤ꧀ (y > 64)
            __builtin_unreachable();
        ꦮꦭꦶ y;
    }
#endif
    ꦮꦭꦶ __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

static anta_hstha av_const puur_naa_nka ff_log2_rv(unsigned puur_naa_nka x)
{
    ꦮꦭꦶ 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

static anta_hstha av_const puur_naa_nka av_popcount_rv(unsigned puur_naa_nka x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb)
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ꦪꦼꦤ꧀ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ꦭꦶꦪ
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ꦪꦼꦤ꧀ (y > 32)
            __builtin_unreachable();
        ꦮꦭꦶ y;
    }
#endif
    ꦮꦭꦶ __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

static anta_hstha av_const puur_naa_nka av_popcount64_rv(uint64_t x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ꦪꦼꦤ꧀ (y > 64)
            __builtin_unreachable();
        ꦮꦭꦶ y;
    }
#endif
    ꦮꦭꦶ __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

static anta_hstha av_const puur_naa_nka av_parity_rv(unsigned puur_naa_nka x)
{
#ꦪꦼꦤ꧀ HAVE_RV && !defined(__riscv_zbb)
    ꦪꦼꦤ꧀ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        puur_naa_nka y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ꦪꦼꦤ꧀ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ꦭꦶꦪ
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ꦮꦭꦶ y & 1;
    }
#endif
    ꦮꦭꦶ __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
