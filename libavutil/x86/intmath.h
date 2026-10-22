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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଯଦି HAVE_FAST_CLZ
#ଯଦି defined(_MSC_VER)
#ଅନ୍ତର୍ଭାଵ <intrin.h>
#ନଚେତଯଦି defined(__INTEL_COMPILER)
#ଅନ୍ତର୍ଭାଵ <immintrin.h>
#endif
#endif
#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_FAST_CLZ
#ଯଦି (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   ଯଦି defined(__INTEL_COMPILER)
#       define ff_log2(x) (_bit_scan_reverse((x)|1))
#   ଅନ୍ୟଥା
#       define ff_log2 ff_log2_x86
ସ୍ଥିର av_always_inline av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_log2_x86(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା v)
{
    unsigned long n;
    _BitScanReverse(&n, v|1);
    ଫେରନ୍ତୁ n;
}
#   endif
#   define ff_log2_16bit av_log2

#ଯଦି defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   ଯଦି ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   ଅନ୍ୟଥା
#       define ff_ctzll ff_ctzll_x86
ସ୍ଥିର av_always_inline av_const ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_ctzll_x86(long long v)
{
    ଫେରନ୍ତୁ ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#endif /* _MSC_VER */

#endif /* __INTEL_COMPILER */

#endif /* HAVE_FAST_CLZ */

#ଯଦି defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#ଯଦି defined(__POPCNT__)
    #define av_popcount   __builtin_popcount
#ଯଦି ARCH_X86_64
    #define av_popcount64 __builtin_popcountll
#endif

#endif /* __POPCNT__ */

#ଯଦି defined(__BMI2__)

#ଯଦି AV_GCC_VERSION_AT_LEAST(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#define av_zero_extend av_zero_extend_bmi2
ସ୍ଥିର av_always_inline av_const unsigned av_zero_extend_bmi2(unsigned a, unsigned p)
{
    ଯଦି (p > 31) abort();
    ଫେରନ୍ତୁ __builtin_ia32_bzhi_si(a, p);
}
#ଅନ୍ୟଥା
#define av_zero_extend __builtin_ia32_bzhi_si
#endif
#ନଚେତଯଦି HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#define av_zero_extend av_zero_extend_bmi2
ସ୍ଥିର av_always_inline av_const unsigned av_zero_extend_bmi2(unsigned a, unsigned p)
{
#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ଯଦି (p > 31) abort();
#endif
    ଯଦି (av_builtin_constant_p(p))
        ଫେରନ୍ତୁ a & ((1U << p) - 1);
    ଅନ୍ୟଥା {
        unsigned x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        ଫେରନ୍ତୁ x;
    }
}
#endif /* AV_GCC_VERSION_AT_LEAST */

#endif /* __BMI2__ */

#endif /* __GNUC__ */

#endif /* AVUTIL_X86_INTMATH_H */
