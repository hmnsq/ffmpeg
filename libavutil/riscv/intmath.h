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

#شامل <stdint.h>
#شامل <math.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
ایستا av_always_inline av_const int8_t av_clip_int8_rvi(صحیح a)
{
    اجتماع { uint8_t u; int8_t s; } u = { .u = a };

    اگر (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    بازگشت a;
}

#define av_clip_int16 av_clip_int16_rvi
ایستا av_always_inline av_const int16_t av_clip_int16_rvi(صحیح a)
{
    اجتماع { uint16_t u; int16_t s; } u = { .u = a };

    اگر (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    بازگشت a;
}

#define av_clipl_int32 av_clipl_int32_rvi
ایستا av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    اجتماع { uint32_t u; int32_t s; } u = { .u = a };

    اگر (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    بازگشت a;
}

#define av_clip_intp2 av_clip_intp2_rvi
ایستا av_always_inline av_const صحیح av_clip_intp2_rvi(صحیح a, صحیح p)
{
    ثابت صحیح shift = 31 - p;
    صحیح b = ((صحیح)(((unsigned)a) << shift)) >> shift;

    اگر (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    بازگشت b;
}

#اگر defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
ایستا av_always_inline av_const اعشاری av_clipf_rvf(اعشاری a, اعشاری min,
                                                    اعشاری max)
{
    بازگشت fminf(fmaxf(a, min), max);
}
#endif

#اگر defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
ایستا av_always_inline av_const دوگانه av_clipd_rvd(دوگانه a, دوگانه min,
                                                     دوگانه max)
{
    بازگشت fmin(fmax(a, min), max);
}
#endif

#اگر defined (__GNUC__) || defined (__clang__)
ایستا درونخطی av_const صحیح ff_ctz_rv(صحیح x)
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
#وگرنه
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 32)
            __builtin_unreachable();
        بازگشت y;
    }
#endif
    بازگشت __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

ایستا درونخطی av_const صحیح ff_ctzll_rv(long long x)
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
        بازگشت y;
    }
#endif
    بازگشت __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

ایستا درونخطی av_const صحیح ff_clz_rv(صحیح x)
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
#وگرنه
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 32)
            __builtin_unreachable();
        بازگشت y;
    }
#endif
    بازگشت __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#اگر __riscv_xlen == 64
ایستا درونخطی av_const صحیح ff_clzll_rv(long long x)
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
        بازگشت y;
    }
#endif
    بازگشت __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

ایستا درونخطی av_const صحیح ff_log2_rv(unsigned صحیح x)
{
    بازگشت 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

ایستا درونخطی av_const صحیح av_popcount_rv(unsigned صحیح x)
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
#وگرنه
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        اگر (y > 32)
            __builtin_unreachable();
        بازگشت y;
    }
#endif
    بازگشت __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

ایستا درونخطی av_const صحیح av_popcount64_rv(uint64_t x)
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
        بازگشت y;
    }
#endif
    بازگشت __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

ایستا درونخطی av_const صحیح av_parity_rv(unsigned صحیح x)
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
#وگرنه
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        بازگشت y & 1;
    }
#endif
    بازگشت __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
