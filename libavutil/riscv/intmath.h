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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <math.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/riscv/cpu.h"

/*
 * The compiler is forced to sign-extend the result anyhow, so it is faster to
 * compute it explicitly and use it.
 */
#define av_clip_int8 av_clip_int8_rvi
സ്ഥിതം av_always_inline av_const int8_t av_clip_int8_rvi(പൂർണ്ണസംഖ്യ a)
{
    സംഘം { uint8_t u; int8_t s; } u = { .u = a };

    എങ്കിൽ (a != u.s)
        a = ((a >> 31) ^ 0x7F);
    തിരികെ a;
}

#define av_clip_int16 av_clip_int16_rvi
സ്ഥിതം av_always_inline av_const int16_t av_clip_int16_rvi(പൂർണ്ണസംഖ്യ a)
{
    സംഘം { uint16_t u; int16_t s; } u = { .u = a };

    എങ്കിൽ (a != u.s)
        a = ((a >> 31) ^ 0x7FFF);
    തിരികെ a;
}

#define av_clipl_int32 av_clipl_int32_rvi
സ്ഥിതം av_always_inline av_const int32_t av_clipl_int32_rvi(int64_t a)
{
    സംഘം { uint32_t u; int32_t s; } u = { .u = a };

    എങ്കിൽ (a != u.s)
        a = ((a >> 63) ^ 0x7FFFFFFF);
    തിരികെ a;
}

#define av_clip_intp2 av_clip_intp2_rvi
സ്ഥിതം av_always_inline av_const പൂർണ്ണസംഖ്യ av_clip_intp2_rvi(പൂർണ്ണസംഖ്യ a, പൂർണ്ണസംഖ്യ p)
{
    സ്ഥിരം പൂർണ്ണസംഖ്യ shift = 31 - p;
    പൂർണ്ണസംഖ്യ b = ((പൂർണ്ണസംഖ്യ)(((unsigned)a) << shift)) >> shift;

    എങ്കിൽ (a != b)
        b = (a >> 31) ^ ((1 << p) - 1);
    തിരികെ b;
}

#എങ്കിൽ defined (__riscv_f) || defined (__riscv_zfinx)
#define av_clipf av_clipf_rvf
സ്ഥിതം av_always_inline av_const ദശാംശം av_clipf_rvf(ദശാംശം a, ദശാംശം min,
                                                    ദശാംശം max)
{
    തിരികെ fminf(fmaxf(a, min), max);
}
#endif

#എങ്കിൽ defined (__riscv_d) || defined (__riscv_zdinx)
#define av_clipd av_clipd_rvd
സ്ഥിതം av_always_inline av_const ഇരട്ട av_clipd_rvd(ഇരട്ട a, ഇരട്ട min,
                                                     ഇരട്ട max)
{
    തിരികെ fmin(fmax(a, min), max);
}
#endif

#എങ്കിൽ defined (__GNUC__) || defined (__clang__)
സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ ff_ctz_rv(പൂർണ്ണസംഖ്യ x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb)
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#എങ്കിൽ __riscv_xlen >= 64
            "ctzw    %0, %1\n"
#അല്ലെങ്കിൽ
            "ctz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        എങ്കിൽ (y > 32)
            __builtin_unreachable();
        തിരികെ y;
    }
#endif
    തിരികെ __builtin_ctz(x);
}
#define ff_ctz ff_ctz_rv

സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ ff_ctzll_rv(long long x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen == 64
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "ctz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        എങ്കിൽ (y > 64)
            __builtin_unreachable();
        തിരികെ y;
    }
#endif
    തിരികെ __builtin_ctzll(x);
}
#define ff_ctzll ff_ctzll_rv

സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ ff_clz_rv(പൂർണ്ണസംഖ്യ x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb)
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#എങ്കിൽ __riscv_xlen >= 64
            "clzw    %0, %1\n"
#അല്ലെങ്കിൽ
            "clz     %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        എങ്കിൽ (y > 32)
            __builtin_unreachable();
        തിരികെ y;
    }
#endif
    തിരികെ __builtin_clz(x);
}
#define ff_clz ff_clz_rv

#എങ്കിൽ __riscv_xlen == 64
സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ ff_clzll_rv(long long x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb)
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "clz     %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        എങ്കിൽ (y > 64)
            __builtin_unreachable();
        തിരികെ y;
    }
#endif
    തിരികെ __builtin_clzll(x);
}
#define ff_clz ff_clz_rv
#endif

സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ ff_log2_rv(unsigned പൂർണ്ണസംഖ്യ x)
{
    തിരികെ 31 - ff_clz_rv(x | 1);
}
#define ff_log2 ff_log2_rv
#define ff_log2_16bit ff_log2_rv

സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ av_popcount_rv(unsigned പൂർണ്ണസംഖ്യ x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb)
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#എങ്കിൽ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#അല്ലെങ്കിൽ
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        എങ്കിൽ (y > 32)
            __builtin_unreachable();
        തിരികെ y;
    }
#endif
    തിരികെ __builtin_popcount(x);
}
#define av_popcount av_popcount_rv

സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ av_popcount64_rv(uint64_t x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb) && __riscv_xlen >= 64
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "cpop    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        എങ്കിൽ (y > 64)
            __builtin_unreachable();
        തിരികെ y;
    }
#endif
    തിരികെ __builtin_popcountl(x);
}
#define av_popcount64 av_popcount64_rv

സ്ഥിതം വരിയിൽ av_const പൂർണ്ണസംഖ്യ av_parity_rv(unsigned പൂർണ്ണസംഖ്യ x)
{
#എങ്കിൽ HAVE_RV && !defined(__riscv_zbb)
    എങ്കിൽ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), true)) {
        പൂർണ്ണസംഖ്യ y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
#എങ്കിൽ __riscv_xlen >= 64
            "cpopw   %0, %1\n"
#അല്ലെങ്കിൽ
            "cpop    %0, %1\n"
#endif
            ".option pop" : "=r" (y) : "r" (x));
        തിരികെ y & 1;
    }
#endif
    തിരികെ __builtin_parity(x);
}
#define av_parity av_parity_rv
#endif

#endif /* AVUTIL_RISCV_INTMATH_H */
