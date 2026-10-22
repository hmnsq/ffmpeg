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

#ضمن <stdint.h>
#ضمن <math.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
ساكن av_always_inline av_const int8_t av_clip_int8_rvi(صحيح a)
{
    اتحاد { uint8_t u; int8_t s; } u = { .u = a };

    𐤀𐤌 (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    أرجع a;
}

#define av_clip_int16 av_clip_int16_rvi
ساكن av_always_inline av_const int16_t av_clip_int16_rvi(صحيح a)
{
    اتحاد { uint16_t u; int16_t s; } u = { .u = a };

    𐤀𐤌 (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    أرجع a;
}

#define av_clipl_int32 av_clipl_int32_rvi
ساكن av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    اتحاد { uint32_t u; int32_t s; } u = { .u = a };

    𐤀𐤌 (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    أرجع a;
}

#define av_clip_intp2 av_clip_intp2_rvi
ساكن av_always_inline av_const صحيح av_clip_intp2_rvi(صحيح a, صحيح p)
{
    ثابت صحيح shift = 31 - p;
    صحيح b = ((صحيح)(((unsigned)a) << shift)) >> shift;

    𐤀𐤌 (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    أرجع b;
}

#𐤀𐤌 defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
ساكن av_always_inline av_const عائم av_clipf_rvf(عائم a, عائم min,
                                                    عائم max)
{
    أرجع fminf(fmaxf(a, min), max);
}
#endif

#𐤀𐤌 defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
ساكن av_always_inline av_const مزدوج av_clipd_rvd(مزدوج a, مزدوج min,
                                                     مزدوج max)
{
    أرجع fmin(fmax(a, min), max);
}
#endif

#𐤀𐤌 defined (__GNUC__) || defined (__clang__)
ساكن مضمن av_const صحيح ff_ctz_rv(صحيح x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb)
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#𐤀𐤌 __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#وإلا
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        𐤀𐤌 (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#endif
    أرجع __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

ساكن مضمن av_const صحيح ff_ctzll_rv(long long x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        𐤀𐤌 (y > 64)
            __builtin_unreachable();
        أرجع y;
    }
#endif
    أرجع __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

ساكن مضمن av_const صحيح ff_clz_rv(صحيح x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb)
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#𐤀𐤌 __riscv_xlen >= 64
            "clzw    %0, %1\n"
#وإلا
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        𐤀𐤌 (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#endif
    أرجع __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#𐤀𐤌 __riscv_xlen == 64
ساكن مضمن av_const صحيح ff_clzll_rv(long long x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb)
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        𐤀𐤌 (y > 64)
            __builtin_unreachable();
        أرجع y;
    }
#endif
    أرجع __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

ساكن مضمن av_const صحيح ff_log2_rv(unsigned صحيح x)
{
    أرجع 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

ساكن مضمن av_const صحيح av_popcount_rv(unsigned صحيح x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb)
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#𐤀𐤌 __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#وإلا
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        𐤀𐤌 (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#endif
    أرجع __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

ساكن مضمن av_const صحيح av_popcount64_rv(uint64_t x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        𐤀𐤌 (y > 64)
            __builtin_unreachable();
        أرجع y;
    }
#endif
    أرجع __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

ساكن مضمن av_const صحيح av_parity_rv(unsigned صحيح x)
{
#𐤀𐤌 HAVE_RV && !defined(__riscv_zbb)
    𐤀𐤌 (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#𐤀𐤌 __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#وإلا
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        أرجع y & 1;
    }
#endif
    أرجع __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
