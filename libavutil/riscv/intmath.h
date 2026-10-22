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

#اگر_غیر_تعریف_شدہ AVUTIL_RISCV_INTMATH_H
#تعریف_کرو AVUTIL_RISCV_INTMATH_H

#شامل <stdint.h>
#شامل <math.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#تعریف_کرو av_clip_int8 av_clip_int8_rvi
ساکن av_always_inline av_const int8_t av_clip_int8_rvi(صحیح a)
{
    اتحاد { uint8_t u; int8_t s; } u = { .u = a };

    اگر (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    واپس a;
}

#تعریف_کرو av_clip_int16 av_clip_int16_rvi
ساکن av_always_inline av_const int16_t av_clip_int16_rvi(صحیح a)
{
    اتحاد { uint16_t u; int16_t s; } u = { .u = a };

    اگر (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    واپس a;
}

#تعریف_کرو av_clipl_int32 av_clipl_int32_rvi
ساکن av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    اتحاد { uint32_t u; int32_t s; } u = { .u = a };

    اگر (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    واپس a;
}

#تعریف_کرو av_clip_intp2 av_clip_intp2_rvi
ساکن av_always_inline av_const صحیح av_clip_intp2_rvi(صحیح a, صحیح p)
{
    ثابت صحیح سرکاؤ = 31 - p;
    صحیح b = ((صحیح)(((غیرعلامتی)a) << سرکاؤ)) >> سرکاؤ;

    اگر (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    واپس b;
}

#اگر defined (__riscv_f) || defined (__riscv_zfinx)
#تعریف_کرو av_clipf av_clipf_rvf
ساکن av_always_inline av_const اعشاری av_clipf_rvf(اعشاری a, اعشاری min,
                                                    اعشاری max)
{
    واپس fminf(fmaxf(a, min), max);
}
#اگر_ختم

#اگر defined (__riscv_d) || defined (__riscv_zdinx)
#تعریف_کرو av_clipd av_clipd_rvd
ساکن av_always_inline av_const دوہرا av_clipd_rvd(دوہرا a, دوہرا min,
                                                     دوہرا max)
{
    واپس fmin(fmax(a, min), max);
}
#اگر_ختم

#اگر defined (__GNUC__) || defined (__clang__)
ساکن اندرونی av_const صحیح ff_ctz_rv(صحیح x)
{
#اگر HAVE_RV && !defined(__riscv_zbb)
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#اگر __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#ورنہ
            "ctz     %0, %1\n"
#اگر_ختم
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 32)
            __builtin_unreachable();
        واپس y;
    }
#اگر_ختم
    واپس __builtin_ctz(x);
}
#تعریف_کرو ff_ctz ff_ctz_rv

ساکن اندرونی av_const صحیح ff_ctzll_rv(طویل طویل x)
{
#اگر HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 64)
            __builtin_unreachable();
        واپس y;
    }
#اگر_ختم
    واپس __builtin_ctzll(x);
}
#تعریف_کرو ff_ctzll ff_ctzll_rv

ساکن اندرونی av_const صحیح ff_clz_rv(صحیح x)
{
#اگر HAVE_RV && !defined(__riscv_zbb)
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#اگر __riscv_xlen >= 64
            "clzw    %0, %1\n"
#ورنہ
            "clz     %0, %1\n"
#اگر_ختم
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 32)
            __builtin_unreachable();
        واپس y;
    }
#اگر_ختم
    واپس __builtin_clz(x);
}
#تعریف_کرو ff_clz ff_clz_rv

#اگر __riscv_xlen == 64
ساکن اندرونی av_const صحیح ff_clzll_rv(طویل طویل x)
{
#اگر HAVE_RV && !defined(__riscv_zbb)
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 64)
            __builtin_unreachable();
        واپس y;
    }
#اگر_ختم
    واپس __builtin_clzll(x);
}
#تعریف_کرو ff_clz ff_clz_rv
#اگر_ختم

ساکن اندرونی av_const صحیح ff_log2_rv(غیرعلامتی صحیح x)
{
    واپس 31 - ff_clz_rv(x | 1);
}
#تعریف_کرو ff_log2 ff_log2_rv
#تعریف_کرو ff_log2_16bit ff_log2_rv

ساکن اندرونی av_const صحیح av_popcount_rv(غیرعلامتی صحیح x)
{
#اگر HAVE_RV && !defined(__riscv_zbb)
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#اگر __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ورنہ
            "cpop    %0, %1\n"
#اگر_ختم
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 32)
            __builtin_unreachable();
        واپس y;
    }
#اگر_ختم
    واپس __builtin_popcount(x);
}
#تعریف_کرو av_popcount av_popcount_rv

ساکن اندرونی av_const صحیح av_popcount64_rv(uint64_t x)
{
#اگر HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 64)
            __builtin_unreachable();
        واپس y;
    }
#اگر_ختم
    واپس __builtin_popcountl(x);
}
#تعریف_کرو av_popcount64 av_popcount64_rv

ساکن اندرونی av_const صحیح av_parity_rv(غیرعلامتی صحیح x)
{
#اگر HAVE_RV && !defined(__riscv_zbb)
    اگر (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        صحیح y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#اگر __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ورنہ
            "cpop    %0, %1\n"
#اگر_ختم
            ".option pop" : "=r" (y) : "r" (x));
        واپس y & 1;
    }
#اگر_ختم
    واپس __builtin_parity(x);
}
#تعریف_کرو av_parity av_parity_rv
#اگر_ختم

#اگر_ختم /* AVUTIL_RISCV_INTMATH_H */
