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
static av_always_inline av_const int8_t av_clip_int8_rvi(số_nguyên a)
{
    union { uint8_t u; int8_t s; } u = { .u = a };

    nếu (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    trả_về a;
}

#define av_clip_int16 av_clip_int16_rvi
static av_always_inline av_const int16_t av_clip_int16_rvi(số_nguyên a)
{
    union { uint16_t u; int16_t s; } u = { .u = a };

    nếu (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    trả_về a;
}

#define av_clipl_int32 av_clipl_int32_rvi
static av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    union { uint32_t u; int32_t s; } u = { .u = a };

    nếu (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    trả_về a;
}

#define av_clip_intp2 av_clip_intp2_rvi
static av_always_inline av_const số_nguyên av_clip_intp2_rvi(số_nguyên a, số_nguyên p)
{
    const số_nguyên shift = 31 - p;
    số_nguyên b = ((số_nguyên)(((unsigned)a) << shift)) >> shift;

    nếu (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    trả_về b;
}

#nếu defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
static av_always_inline av_const float av_clipf_rvf(float a, float min,
                                                    float max)
{
    trả_về fminf(fmaxf(a, min), max);
}
#endif

#nếu defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
static av_always_inline av_const double av_clipd_rvd(double a, double min,
                                                     double max)
{
    trả_về fmin(fmax(a, min), max);
}
#endif

#nếu defined (__GNUC__) || defined (__clang__)
static inline av_const số_nguyên ff_ctz_rv(số_nguyên x)
{
#nếu HAVE_RV && !defined(__riscv_zbb)
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#nếu __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#không_thì
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        nếu (y > 32)
            __builtin_unreachable();
        trả_về y;
    }
#endif
    trả_về __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

static inline av_const số_nguyên ff_ctzll_rv(long long x)
{
#nếu HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        nếu (y > 64)
            __builtin_unreachable();
        trả_về y;
    }
#endif
    trả_về __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

static inline av_const số_nguyên ff_clz_rv(số_nguyên x)
{
#nếu HAVE_RV && !defined(__riscv_zbb)
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#nếu __riscv_xlen >= 64
            "clzw    %0, %1\n"
#không_thì
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        nếu (y > 32)
            __builtin_unreachable();
        trả_về y;
    }
#endif
    trả_về __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#nếu __riscv_xlen == 64
static inline av_const số_nguyên ff_clzll_rv(long long x)
{
#nếu HAVE_RV && !defined(__riscv_zbb)
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        nếu (y > 64)
            __builtin_unreachable();
        trả_về y;
    }
#endif
    trả_về __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

static inline av_const số_nguyên ff_log2_rv(unsigned số_nguyên x)
{
    trả_về 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

static inline av_const số_nguyên av_popcount_rv(unsigned số_nguyên x)
{
#nếu HAVE_RV && !defined(__riscv_zbb)
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#nếu __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#không_thì
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        nếu (y > 32)
            __builtin_unreachable();
        trả_về y;
    }
#endif
    trả_về __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

static inline av_const số_nguyên av_popcount64_rv(uint64_t x)
{
#nếu HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        nếu (y > 64)
            __builtin_unreachable();
        trả_về y;
    }
#endif
    trả_về __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

static inline av_const số_nguyên av_parity_rv(unsigned số_nguyên x)
{
#nếu HAVE_RV && !defined(__riscv_zbb)
    nếu (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        số_nguyên y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#nếu __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#không_thì
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        trả_về y & 1;
    }
#endif
    trả_về __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
