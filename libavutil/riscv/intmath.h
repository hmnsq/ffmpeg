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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_RISCV_INTMATH_H
#وصف_ڪريو AVUTIL_RISCV_INTMATH_H

#ضمن <stdint.h>
#ضمن <math.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#وصف_ڪريو av_clip_int8 av_clip_int8_rvi
ساكن av_always_inline av_const int8_t av_clip_int8_rvi(صحيح a)
{
    اتحاد { uint8_t u; int8_t s; } u = { .u = a };

    إذا (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    أرجع a;
}

#وصف_ڪريو av_clip_int16 av_clip_int16_rvi
ساكن av_always_inline av_const int16_t av_clip_int16_rvi(صحيح a)
{
    اتحاد { uint16_t u; int16_t s; } u = { .u = a };

    إذا (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    أرجع a;
}

#وصف_ڪريو av_clipl_int32 av_clipl_int32_rvi
ساكن av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    اتحاد { uint32_t u; int32_t s; } u = { .u = a };

    إذا (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    أرجع a;
}

#وصف_ڪريو av_clip_intp2 av_clip_intp2_rvi
ساكن av_always_inline av_const صحيح av_clip_intp2_rvi(صحيح a, صحيح p)
{
    ثابت صحيح سرڪايو = 31 - p;
    صحيح b = ((صحيح)(((بنانشان)a) << سرڪايو)) >> سرڪايو;

    إذا (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    أرجع b;
}

#إذا defined (__riscv_f) || defined (__riscv_zfinx)
#وصف_ڪريو av_clipf av_clipf_rvf
ساكن av_always_inline av_const عائم av_clipf_rvf(عائم a, عائم min,
                                                    عائم max)
{
    أرجع fminf(fmaxf(a, min), max);
}
#جيڪڏهن_پورو

#إذا defined (__riscv_d) || defined (__riscv_zdinx)
#وصف_ڪريو av_clipd av_clipd_rvd
ساكن av_always_inline av_const مزدوج av_clipd_rvd(مزدوج a, مزدوج min,
                                                     مزدوج max)
{
    أرجع fmin(fmax(a, min), max);
}
#جيڪڏهن_پورو

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
#جيڪڏهن_پورو
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#جيڪڏهن_پورو
    أرجع __builtin_ctz(x);
}
#وصف_ڪريو ff_ctz ff_ctz_rv

ساكن مضمن av_const صحيح ff_ctzll_rv(ڊگهو ڊگهو x)
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
#جيڪڏهن_پورو
    أرجع __builtin_ctzll(x);
}
#وصف_ڪريو ff_ctzll ff_ctzll_rv

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
#جيڪڏهن_پورو
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#جيڪڏهن_پورو
    أرجع __builtin_clz(x);
}
#وصف_ڪريو ff_clz ff_clz_rv

#إذا __riscv_xlen == 64
ساكن مضمن av_const صحيح ff_clzll_rv(ڊگهو ڊگهو x)
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
#جيڪڏهن_پورو
    أرجع __builtin_clzll(x);
}
#وصف_ڪريو ff_clz ff_clz_rv
#جيڪڏهن_پورو

ساكن مضمن av_const صحيح ff_log2_rv(بنانشان صحيح x)
{
    أرجع 31 - ff_clz_rv(x | 1);
}
#وصف_ڪريو ff_log2 ff_log2_rv
#وصف_ڪريو ff_log2_16bit ff_log2_rv

ساكن مضمن av_const صحيح av_popcount_rv(بنانشان صحيح x)
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
#جيڪڏهن_پورو
            ".option pop" : "=r" (y) : "r" (x));
        إذا (y > 32)
            __builtin_unreachable();
        أرجع y;
    }
#جيڪڏهن_پورو
    أرجع __builtin_popcount(x);
}
#وصف_ڪريو av_popcount av_popcount_rv

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
#جيڪڏهن_پورو
    أرجع __builtin_popcountl(x);
}
#وصف_ڪريو av_popcount64 av_popcount64_rv

ساكن مضمن av_const صحيح av_parity_rv(بنانشان صحيح x)
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
#جيڪڏهن_پورو
            ".option pop" : "=r" (y) : "r" (x));
        أرجع y & 1;
    }
#جيڪڏهن_پورو
    أرجع __builtin_parity(x);
}
#وصف_ڪريو av_parity av_parity_rv
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* AVUTIL_RISCV_INTMATH_H */
