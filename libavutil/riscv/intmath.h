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

#جے_بنا_تعریف AVUTIL_RISCV_INTMATH_H
#تعریف_کرو AVUTIL_RISCV_INTMATH_H

#ضمن <stdint.h>
#ضمن <math.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#تعریف_کرو av_clip_int8 av_clip_int8_rvi
ساكن av_always_inline av_const int8_t av_clip_int8_rvi(صحيح a)
{
    اتحاد { uint8_t u; int8_t s; } u = { .u = a };

    إذا (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    أرجع a;
}

#تعریف_کرو av_clip_int16 av_clip_int16_rvi
ساكن av_always_inline av_const int16_t av_clip_int16_rvi(صحيح a)
{
    اتحاد { uint16_t u; int16_t s; } u = { .u = a };

    إذا (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    أرجع a;
}

#تعریف_کرو av_clipl_int32 av_clipl_int32_rvi
ساكن av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    اتحاد { uint32_t u; int32_t s; } u = { .u = a };

    إذا (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    أرجع a;
}

#تعریف_کرو av_clip_intp2 av_clip_intp2_rvi
ساكن av_always_inline av_const صحيح av_clip_intp2_rvi(صحيح a, صحيح p)
{
    ثابت صحيح کھسکاؤ = 31 - p;
    صحيح b = ((صحيح)(((بنانشانی)a) << کھسکاؤ)) >> کھسکاؤ;

    إذا (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    أرجع b;
}

#إذا defined (__riscv_f) || defined (__riscv_zfinx)
#تعریف_کرو av_clipf av_clipf_rvf
ساكن av_always_inline av_const عائم av_clipf_rvf(عائم a, عائم min,
                                                    عائم max)
{
    أرجع fminf(fmaxf(a, min), max);
}
#جے_انت

#إذا defined (__riscv_d) || defined (__riscv_zdinx)
#تعریف_کرو av_clipd av_clipd_rvd
ساكن av_always_inline av_const مزدوج av_clipd_rvd(مزدوج a, مزدوج min,
                                                     مزدوج max)
{
    أرجع fmin(fmax(a, min), max);
}
#جے_انت

#إذا defined (__GNUC__) || defined (__clang__)
ساكن مضمن av_const صحيح ff_ctz_rv(صحيح x)
{
#إذا HAVE_RV && !defined(__riscv_zbb)
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#إذا __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#وإلا
            "ctz     %0, %1\n"
#جے_انت
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#جے_انت
    أرجع __builtin_ctz(x);
}
#تعریف_کرو ff_ctz ff_ctz_rv

ساكن مضمن av_const صحيح ff_ctzll_rv(لما لما x)
{
#إذا HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 64)
            __builtin_unreachable();
        أرجع y;
    }
#جے_انت
    أرجع __builtin_ctzll(x);
}
#تعریف_کرو ff_ctzll ff_ctzll_rv

ساكن مضمن av_const صحيح ff_clz_rv(صحيح x)
{
#إذا HAVE_RV && !defined(__riscv_zbb)
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#إذا __riscv_xlen >= 64
            "clzw    %0, %1\n"
#وإلا
            "clz     %0, %1\n"
#جے_انت
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#جے_انت
    أرجع __builtin_clz(x);
}
#تعریف_کرو ff_clz ff_clz_rv

#إذا __riscv_xlen == 64
ساكن مضمن av_const صحيح ff_clzll_rv(لما لما x)
{
#إذا HAVE_RV && !defined(__riscv_zbb)
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 64)
            __builtin_unreachable();
        أرجع y;
    }
#جے_انت
    أرجع __builtin_clzll(x);
}
#تعریف_کرو ff_clz ff_clz_rv
#جے_انت

ساكن مضمن av_const صحيح ff_log2_rv(بنانشانی صحيح x)
{
    أرجع 31 - ff_clz_rv(x | 1);
}
#تعریف_کرو ff_log2 ff_log2_rv
#تعریف_کرو ff_log2_16bit ff_log2_rv

ساكن مضمن av_const صحيح av_popcount_rv(بنانشانی صحيح x)
{
#إذا HAVE_RV && !defined(__riscv_zbb)
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#إذا __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#وإلا
            "cpop    %0, %1\n"
#جے_انت
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#جے_انت
    أرجع __builtin_popcount(x);
}
#تعریف_کرو av_popcount av_popcount_rv

ساكن مضمن av_const صحيح av_popcount64_rv(uint64_t x)
{
#إذا HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 64)
            __builtin_unreachable();
        أرجع y;
    }
#جے_انت
    أرجع __builtin_popcountl(x);
}
#تعریف_کرو av_popcount64 av_popcount64_rv

ساكن مضمن av_const صحيح av_parity_rv(بنانشانی صحيح x)
{
#إذا HAVE_RV && !defined(__riscv_zbb)
    إذا (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحيح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#إذا __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#وإلا
            "cpop    %0, %1\n"
#جے_انت
            ".option pop" : "=r" (y) : "r" (x));
        أرجع y & 1;
    }
#جے_انت
    أرجع __builtin_parity(x);
}
#تعریف_کرو av_parity av_parity_rv
#جے_انت

#جے_انت /* AVUTIL_RISCV_INTMATH_H */
