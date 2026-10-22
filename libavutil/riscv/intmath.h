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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <math.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
સ્થિર av_always_inline av_const int8_t av_clip_int8_rvi(પૂર્ણાંક a)
{
    સંઘ { uint8_t u; int8_t s; } u = { .u = a };

    જો (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    પાછા a;
}

#define av_clip_int16 av_clip_int16_rvi
સ્થિર av_always_inline av_const int16_t av_clip_int16_rvi(પૂર્ણાંક a)
{
    સંઘ { uint16_t u; int16_t s; } u = { .u = a };

    જો (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    પાછા a;
}

#define av_clipl_int32 av_clipl_int32_rvi
સ્થિર av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    સંઘ { uint32_t u; int32_t s; } u = { .u = a };

    જો (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    પાછા a;
}

#define av_clip_intp2 av_clip_intp2_rvi
સ્થિર av_always_inline av_const પૂર્ણાંક av_clip_intp2_rvi(પૂર્ણાંક a, પૂર્ણાંક p)
{
    અચલ પૂર્ણાંક shift = 31 - p;
    પૂર્ણાંક b = ((પૂર્ણાંક)(((unsigned)a) << shift)) >> shift;

    જો (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    પાછા b;
}

#જો defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
સ્થિર av_always_inline av_const દશાંશ av_clipf_rvf(દશાંશ a, દશાંશ min,
                                                    દશાંશ max)
{
    પાછા fminf(fmaxf(a, min), max);
}
#endif

#જો defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
સ્થિર av_always_inline av_const દ્વિગુણ av_clipd_rvd(દ્વિગુણ a, દ્વિગુણ min,
                                                     દ્વિગુણ max)
{
    પાછા fmin(fmax(a, min), max);
}
#endif

#જો defined (__GNUC__) || defined (__clang__)
સ્થિર અંતઃરેખ av_const પૂર્ણાંક ff_ctz_rv(પૂર્ણાંક x)
{
#જો HAVE_RV && !defined(__riscv_zbb)
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#જો __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#નહીંતર
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        જો (y > 32)
            __builtin_unreachable();
        પાછા y;
    }
#endif
    પાછા __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

સ્થિર અંતઃરેખ av_const પૂર્ણાંક ff_ctzll_rv(long long x)
{
#જો HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        જો (y > 64)
            __builtin_unreachable();
        પાછા y;
    }
#endif
    પાછા __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

સ્થિર અંતઃરેખ av_const પૂર્ણાંક ff_clz_rv(પૂર્ણાંક x)
{
#જો HAVE_RV && !defined(__riscv_zbb)
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#જો __riscv_xlen >= 64
            "clzw    %0, %1\n"
#નહીંતર
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        જો (y > 32)
            __builtin_unreachable();
        પાછા y;
    }
#endif
    પાછા __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#જો __riscv_xlen == 64
સ્થિર અંતઃરેખ av_const પૂર્ણાંક ff_clzll_rv(long long x)
{
#જો HAVE_RV && !defined(__riscv_zbb)
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        જો (y > 64)
            __builtin_unreachable();
        પાછા y;
    }
#endif
    પાછા __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

સ્થિર અંતઃરેખ av_const પૂર્ણાંક ff_log2_rv(unsigned પૂર્ણાંક x)
{
    પાછા 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

સ્થિર અંતઃરેખ av_const પૂર્ણાંક av_popcount_rv(unsigned પૂર્ણાંક x)
{
#જો HAVE_RV && !defined(__riscv_zbb)
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#જો __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#નહીંતર
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        જો (y > 32)
            __builtin_unreachable();
        પાછા y;
    }
#endif
    પાછા __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

સ્થિર અંતઃરેખ av_const પૂર્ણાંક av_popcount64_rv(uint64_t x)
{
#જો HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        જો (y > 64)
            __builtin_unreachable();
        પાછા y;
    }
#endif
    પાછા __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

સ્થિર અંતઃરેખ av_const પૂર્ણાંક av_parity_rv(unsigned પૂર્ણાંક x)
{
#જો HAVE_RV && !defined(__riscv_zbb)
    જો (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        પૂર્ણાંક y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#જો __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#નહીંતર
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        પાછા y & 1;
    }
#endif
    પાછા __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
