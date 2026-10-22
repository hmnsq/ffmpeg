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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <math.h>

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
স্থির av_always_inline av_const int8_t av_clip_int8_rvi(পূর্ণসংখ্যা a)
{
    সংঘ { uint8_t u; int8_t s; } u = { .u = a };

    যদি (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    ফেরত a;
}

#define av_clip_int16 av_clip_int16_rvi
স্থির av_always_inline av_const int16_t av_clip_int16_rvi(পূর্ণসংখ্যা a)
{
    সংঘ { uint16_t u; int16_t s; } u = { .u = a };

    যদি (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    ফেরত a;
}

#define av_clipl_int32 av_clipl_int32_rvi
স্থির av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    সংঘ { uint32_t u; int32_t s; } u = { .u = a };

    যদি (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    ফেরত a;
}

#define av_clip_intp2 av_clip_intp2_rvi
স্থির av_always_inline av_const পূর্ণসংখ্যা av_clip_intp2_rvi(পূর্ণসংখ্যা a, পূর্ণসংখ্যা p)
{
    ধ্রুবক পূর্ণসংখ্যা shift = 31 - p;
    পূর্ণসংখ্যা b = ((পূর্ণসংখ্যা)(((unsigned)a) << shift)) >> shift;

    যদি (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    ফেরত b;
}

#যদি defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
স্থির av_always_inline av_const দশমিক av_clipf_rvf(দশমিক a, দশমিক min,
                                                    দশমিক max)
{
    ফেরত fminf(fmaxf(a, min), max);
}
#endif

#যদি defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
স্থির av_always_inline av_const দ্বিগুণ av_clipd_rvd(দ্বিগুণ a, দ্বিগুণ min,
                                                     দ্বিগুণ max)
{
    ফেরত fmin(fmax(a, min), max);
}
#endif

#যদি defined (__GNUC__) || defined (__clang__)
স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা ff_ctz_rv(পূর্ণসংখ্যা x)
{
#যদি HAVE_RV && !defined(__riscv_zbb)
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#যদি __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#অন্যথা
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        যদি (y > 32)
            __builtin_unreachable();
        ফেরত y;
    }
#endif
    ফেরত __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা ff_ctzll_rv(long long x)
{
#যদি HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        যদি (y > 64)
            __builtin_unreachable();
        ফেরত y;
    }
#endif
    ফেরত __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা ff_clz_rv(পূর্ণসংখ্যা x)
{
#যদি HAVE_RV && !defined(__riscv_zbb)
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#যদি __riscv_xlen >= 64
            "clzw    %0, %1\n"
#অন্যথা
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        যদি (y > 32)
            __builtin_unreachable();
        ফেরত y;
    }
#endif
    ফেরত __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#যদি __riscv_xlen == 64
স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা ff_clzll_rv(long long x)
{
#যদি HAVE_RV && !defined(__riscv_zbb)
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        যদি (y > 64)
            __builtin_unreachable();
        ফেরত y;
    }
#endif
    ফেরত __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা ff_log2_rv(unsigned পূর্ণসংখ্যা x)
{
    ফেরত 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা av_popcount_rv(unsigned পূর্ণসংখ্যা x)
{
#যদি HAVE_RV && !defined(__riscv_zbb)
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#যদি __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#অন্যথা
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        যদি (y > 32)
            __builtin_unreachable();
        ফেরত y;
    }
#endif
    ফেরত __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা av_popcount64_rv(uint64_t x)
{
#যদি HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        যদি (y > 64)
            __builtin_unreachable();
        ফেরত y;
    }
#endif
    ফেরত __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

স্থির অন্তঃরেখ av_const পূর্ণসংখ্যা av_parity_rv(unsigned পূর্ণসংখ্যা x)
{
#যদি HAVE_RV && !defined(__riscv_zbb)
    যদি (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        পূর্ণসংখ্যা y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#যদি __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#অন্যথা
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ফেরত y & 1;
    }
#endif
    ফেরত __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
