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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_RISCV_INTMATH_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_RISCV_INTMATH_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_int8 av_clip_int8_rvi
ਸਥਿਰ av_always_inline av_const int8_t av_clip_int8_rvi(ਪੂਰਨ a)
{
    ਸੰਘ { uint8_t u; int8_t s; } u = { .u = a };

    ਜੇ (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    ਵਾਪਸ a;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_int16 av_clip_int16_rvi
ਸਥਿਰ av_always_inline av_const int16_t av_clip_int16_rvi(ਪੂਰਨ a)
{
    ਸੰਘ { uint16_t u; int16_t s; } u = { .u = a };

    ਜੇ (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    ਵਾਪਸ a;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clipl_int32 av_clipl_int32_rvi
ਸਥਿਰ av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    ਸੰਘ { uint32_t u; int32_t s; } u = { .u = a };

    ਜੇ (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    ਵਾਪਸ a;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_intp2 av_clip_intp2_rvi
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_intp2_rvi(ਪੂਰਨ a, ਪੂਰਨ p)
{
    ਅਚਲ ਪੂਰਨ ਖਿਸਕਾਓ = 31 - p;
    ਪੂਰਨ b = ((ਪੂਰਨ)(((ਬਿਨਾਨਿਸ਼ਾਨੀ)a) << ਖਿਸਕਾਓ)) >> ਖਿਸਕਾਓ;

    ਜੇ (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    ਵਾਪਸ b;
}

#ਜੇ defined (__riscv_f) || defined (__riscv_zfinx)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clipf av_clipf_rvf
ਸਥਿਰ av_always_inline av_const ਦਸ਼ਮਲਵ av_clipf_rvf(ਦਸ਼ਮਲਵ a, ਦਸ਼ਮਲਵ min,
                                                    ਦਸ਼ਮਲਵ max)
{
    ਵਾਪਸ fminf(fmaxf(a, min), max);
}
#ਜੇ_ਅੰਤ

#ਜੇ defined (__riscv_d) || defined (__riscv_zdinx)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clipd av_clipd_rvd
ਸਥਿਰ av_always_inline av_const ਦੁੱਗਣਾ av_clipd_rvd(ਦੁੱਗਣਾ a, ਦੁੱਗਣਾ min,
                                                     ਦੁੱਗਣਾ max)
{
    ਵਾਪਸ fmin(fmax(a, min), max);
}
#ਜੇ_ਅੰਤ

#ਜੇ defined (__GNUC__) || defined (__clang__)
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ ff_ctz_rv(ਪੂਰਨ x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb)
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ਜੇ __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#ਨਹੀਂਤਾਂ
            "ctz     %0, %1\n"
#ਜੇ_ਅੰਤ
            ".option pop" : "=r" (y) : "r" (x));
        ਜੇ (y > 32)
            __builtin_unreachable();
        ਵਾਪਸ y;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_ctz(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_ctz ff_ctz_rv

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ ff_ctzll_rv(ਲੰਮਾ ਲੰਮਾ x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ਜੇ (y > 64)
            __builtin_unreachable();
        ਵਾਪਸ y;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_ctzll(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_ctzll ff_ctzll_rv

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ ff_clz_rv(ਪੂਰਨ x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb)
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ਜੇ __riscv_xlen >= 64
            "clzw    %0, %1\n"
#ਨਹੀਂਤਾਂ
            "clz     %0, %1\n"
#ਜੇ_ਅੰਤ
            ".option pop" : "=r" (y) : "r" (x));
        ਜੇ (y > 32)
            __builtin_unreachable();
        ਵਾਪਸ y;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_clz(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_clz ff_clz_rv

#ਜੇ __riscv_xlen == 64
ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ ff_clzll_rv(ਲੰਮਾ ਲੰਮਾ x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb)
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ਜੇ (y > 64)
            __builtin_unreachable();
        ਵਾਪਸ y;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_clzll(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_clz ff_clz_rv
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ ff_log2_rv(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x)
{
    ਵਾਪਸ 31 - ff_clz_rv(x | 1);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_log2 ff_log2_rv
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_log2_16bit ff_log2_rv

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ av_popcount_rv(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb)
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ਜੇ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ਨਹੀਂਤਾਂ
            "cpop    %0, %1\n"
#ਜੇ_ਅੰਤ
            ".option pop" : "=r" (y) : "r" (x));
        ਜੇ (y > 32)
            __builtin_unreachable();
        ਵਾਪਸ y;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_popcount(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_popcount av_popcount_rv

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ av_popcount64_rv(uint64_t x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ਜੇ (y > 64)
            __builtin_unreachable();
        ਵਾਪਸ y;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_popcountl(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_popcount64 av_popcount64_rv

ਸਥਿਰ ਸਤਰਅੰਦਰ av_const ਪੂਰਨ av_parity_rv(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ x)
{
#ਜੇ HAVE_RV && !defined(__riscv_zbb)
    ਜੇ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ਪੂਰਨ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ਜੇ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ਨਹੀਂਤਾਂ
            "cpop    %0, %1\n"
#ਜੇ_ਅੰਤ
            ".option pop" : "=r" (y) : "r" (x));
        ਵਾਪਸ y & 1;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ __builtin_parity(x);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_parity av_parity_rv
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_RISCV_INTMATH_H */
