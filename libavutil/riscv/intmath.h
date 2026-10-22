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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <math.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
ସ୍ଥିର av_always_inline av_const int8_t av_clip_int8_rvi(ପୂର୍ଣ୍ଣସଂଖ୍ୟା a)
{
    ସଂଘ { uint8_t u; int8_t s; } u = { .u = a };

    ଯଦି (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    ଫେରନ୍ତୁ a;
}

#define av_clip_int16 av_clip_int16_rvi
ସ୍ଥିର av_always_inline av_const int16_t av_clip_int16_rvi(ପୂର୍ଣ୍ଣସଂଖ୍ୟା a)
{
    ସଂଘ { uint16_t u; int16_t s; } u = { .u = a };

    ଯଦି (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    ଫେରନ୍ତୁ a;
}

#define av_clipl_int32 av_clipl_int32_rvi
ସ୍ଥିର av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    ସଂଘ { uint32_t u; int32_t s; } u = { .u = a };

    ଯଦି (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    ଫେରନ୍ତୁ a;
}

#define av_clip_intp2 av_clip_intp2_rvi
ସ୍ଥିର av_always_inline av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_clip_intp2_rvi(ପୂର୍ଣ୍ଣସଂଖ୍ୟା a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା p)
{
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift = 31 - p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା b = ((ପୂର୍ଣ୍ଣସଂଖ୍ୟା)(((unsigned)a) << shift)) >> shift;

    ଯଦି (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    ଫେରନ୍ତୁ b;
}

#ଯଦି defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
ସ୍ଥିର av_always_inline av_const ଦଶମିକ av_clipf_rvf(ଦଶମିକ a, ଦଶମିକ min,
                                                    ଦଶମିକ max)
{
    ଫେରନ୍ତୁ fminf(fmaxf(a, min), max);
}
#endif

#ଯଦି defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
ସ୍ଥିର av_always_inline av_const ଦ୍ୱିଗୁଣ av_clipd_rvd(ଦ୍ୱିଗୁଣ a, ଦ୍ୱିଗୁଣ min,
                                                     ଦ୍ୱିଗୁଣ max)
{
    ଫେରନ୍ତୁ fmin(fmax(a, min), max);
}
#endif

#ଯଦି defined (__GNUC__) || defined (__clang__)
ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_ctz_rv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb)
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ଯଦି __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#ଅନ୍ୟଥା
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ଯଦି (y > 32)
            __builtin_unreachable();
        ଫେରନ୍ତୁ y;
    }
#endif
    ଫେରନ୍ତୁ __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_ctzll_rv(long long x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ଯଦି (y > 64)
            __builtin_unreachable();
        ଫେରନ୍ତୁ y;
    }
#endif
    ଫେରନ୍ତୁ __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_clz_rv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb)
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ଯଦି __riscv_xlen >= 64
            "clzw    %0, %1\n"
#ଅନ୍ୟଥା
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ଯଦି (y > 32)
            __builtin_unreachable();
        ଫେରନ୍ତୁ y;
    }
#endif
    ଫେରନ୍ତୁ __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#ଯଦି __riscv_xlen == 64
ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_clzll_rv(long long x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb)
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ଯଦି (y > 64)
            __builtin_unreachable();
        ଫେରନ୍ତୁ y;
    }
#endif
    ଫେରନ୍ତୁ __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_log2_rv(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା x)
{
    ଫେରନ୍ତୁ 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_popcount_rv(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb)
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ଯଦି __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ଅନ୍ୟଥା
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ଯଦି (y > 32)
            __builtin_unreachable();
        ଫେରନ୍ତୁ y;
    }
#endif
    ଫେରନ୍ତୁ __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_popcount64_rv(uint64_t x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ଯଦି (y > 64)
            __builtin_unreachable();
        ଫେରନ୍ତୁ y;
    }
#endif
    ଫେରନ୍ତୁ __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_parity_rv(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା x)
{
#ଯଦି HAVE_RV && !defined(__riscv_zbb)
    ଯଦି (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#ଯଦି __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#ଅନ୍ୟଥା
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        ଫେରନ୍ତୁ y & 1;
    }
#endif
    ଫେରନ୍ତୁ __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
