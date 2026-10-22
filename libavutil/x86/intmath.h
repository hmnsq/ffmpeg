/*
 * Copyright (c) 2015 James Almer
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

#ifndef AVUTIL_X86_INTMATH_H
#define AVUTIL_X86_INTMATH_H

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdlib.h>
#যদি HAVE_FAST_CLZ
#যদি defined(_MSC_VER)
#অন্তর্ভাৱ <intrin.h>
#নোচেদ্যদি defined(__INTEL_COMPILER)
#অন্তর্ভাৱ <immintrin.h>
#endif
#endif
#অন্তর্ভাৱ "config.h"

#যদি HAVE_FAST_CLZ
#যদি (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   যদি defined(__INTEL_COMPILER)
#       define ff_log2(x) (_bit_scan_reverse((x)|1))
#   অন্যথা
#       define ff_log2 ff_log2_x86
স্থির av_always_inline av_const পূর্ণাঙ্ক ff_log2_x86(unsigned পূর্ণাঙ্ক v)
{
    unsigned long n;
    _BitScanReverse(&n, v|1);
    ঘূৰাই n;
}
#   endif
#   define ff_log2_16bit av_log2

#যদি defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   যদি ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   অন্যথা
#       define ff_ctzll ff_ctzll_x86
স্থির av_always_inline av_const পূর্ণাঙ্ক ff_ctzll_x86(long long v)
{
    ঘূৰাই ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#endif /* _MSC_VER */

#endif /* __INTEL_COMPILER */

#endif /* HAVE_FAST_CLZ */

#যদি defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#যদি defined(__POPCNT__)
    #define av_popcount   __builtin_popcount
#যদি ARCH_X86_64
    #define av_popcount64 __builtin_popcountll
#endif

#endif /* __POPCNT__ */

#যদি defined(__BMI2__)

#যদি AV_GCC_VERSION_AT_LEAST(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#যদি defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#define av_zero_extend av_zero_extend_bmi2
স্থির av_always_inline av_const unsigned av_zero_extend_bmi2(unsigned a, unsigned p)
{
    যদি (p > 31) abort();
    ঘূৰাই __builtin_ia32_bzhi_si(a, p);
}
#অন্যথা
#define av_zero_extend __builtin_ia32_bzhi_si
#endif
#নোচেদ্যদি HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#define av_zero_extend av_zero_extend_bmi2
স্থির av_always_inline av_const unsigned av_zero_extend_bmi2(unsigned a, unsigned p)
{
#যদি defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    যদি (p > 31) abort();
#endif
    যদি (av_builtin_constant_p(p))
        ঘূৰাই a & ((1U << p) - 1);
    অন্যথা {
        unsigned x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        ঘূৰাই x;
    }
}
#endif /* AV_GCC_VERSION_AT_LEAST */

#endif /* __BMI2__ */

#endif /* __GNUC__ */

#endif /* AVUTIL_X86_INTMATH_H */
