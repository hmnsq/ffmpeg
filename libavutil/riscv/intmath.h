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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <math.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
நிலையான av_always_inline av_const int8_t av_clip_int8_rvi(முழு a)
{
    ஒன்றிப்பு { uint8_t u; int8_t s; } u = { .u = a };

    எனில் (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    திரும்பு a;
}

#define av_clip_int16 av_clip_int16_rvi
நிலையான av_always_inline av_const int16_t av_clip_int16_rvi(முழு a)
{
    ஒன்றிப்பு { uint16_t u; int16_t s; } u = { .u = a };

    எனில் (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    திரும்பு a;
}

#define av_clipl_int32 av_clipl_int32_rvi
நிலையான av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    ஒன்றிப்பு { uint32_t u; int32_t s; } u = { .u = a };

    எனில் (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    திரும்பு a;
}

#define av_clip_intp2 av_clip_intp2_rvi
நிலையான av_always_inline av_const முழு av_clip_intp2_rvi(முழு a, முழு p)
{
    மாறிலி முழு shift = 31 - p;
    முழு b = ((முழு)(((unsigned)a) << shift)) >> shift;

    எனில் (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    திரும்பு b;
}

#எனில் defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
நிலையான av_always_inline av_const தசம av_clipf_rvf(தசம a, தசம min,
                                                    தசம max)
{
    திரும்பு fminf(fmaxf(a, min), max);
}
#endif

#எனில் defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
நிலையான av_always_inline av_const இரட்டை av_clipd_rvd(இரட்டை a, இரட்டை min,
                                                     இரட்டை max)
{
    திரும்பு fmin(fmax(a, min), max);
}
#endif

#எனில் defined (__GNUC__) || defined (__clang__)
நிலையான உள்வரி av_const முழு ff_ctz_rv(முழு x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb)
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#எனில் __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#இல்லையெனில்
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        எனில் (y > 32)
            __builtin_unreachable();
        திரும்பு y;
    }
#endif
    திரும்பு __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

நிலையான உள்வரி av_const முழு ff_ctzll_rv(long long x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        எனில் (y > 64)
            __builtin_unreachable();
        திரும்பு y;
    }
#endif
    திரும்பு __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

நிலையான உள்வரி av_const முழு ff_clz_rv(முழு x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb)
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#எனில் __riscv_xlen >= 64
            "clzw    %0, %1\n"
#இல்லையெனில்
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        எனில் (y > 32)
            __builtin_unreachable();
        திரும்பு y;
    }
#endif
    திரும்பு __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#எனில் __riscv_xlen == 64
நிலையான உள்வரி av_const முழு ff_clzll_rv(long long x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb)
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        எனில் (y > 64)
            __builtin_unreachable();
        திரும்பு y;
    }
#endif
    திரும்பு __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

நிலையான உள்வரி av_const முழு ff_log2_rv(unsigned முழு x)
{
    திரும்பு 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

நிலையான உள்வரி av_const முழு av_popcount_rv(unsigned முழு x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb)
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#எனில் __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#இல்லையெனில்
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        எனில் (y > 32)
            __builtin_unreachable();
        திரும்பு y;
    }
#endif
    திரும்பு __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

நிலையான உள்வரி av_const முழு av_popcount64_rv(uint64_t x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        எனில் (y > 64)
            __builtin_unreachable();
        திரும்பு y;
    }
#endif
    திரும்பு __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

நிலையான உள்வரி av_const முழு av_parity_rv(unsigned முழு x)
{
#எனில் HAVE_RV && !defined(__riscv_zbb)
    எனில் (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        முழு y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#எனில் __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#இல்லையெனில்
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        திரும்பு y & 1;
    }
#endif
    திரும்பு __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
