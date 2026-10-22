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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdlib.h>
#எனில் HAVE_FAST_CLZ
#எனில் defined(_MSC_VER)
#அந்தர்பாவ <intrin.h>
#அல்லதெனில் defined(__INTEL_COMPILER)
#அந்தர்பாவ <immintrin.h>
#endif
#endif
#அந்தர்பாவ "config.h"

#எனில் HAVE_FAST_CLZ
#எனில் (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   எனில் defined(__INTEL_COMPILER)
#       define ff_log2(x) (_bit_scan_reverse((x)|1))
#   இல்லையெனில்
#       define ff_log2 ff_log2_x86
நிலையான av_always_inline av_const முழு ff_log2_x86(unsigned முழு v)
{
    unsigned long n;
    _BitScanReverse(&n, v|1);
    திரும்பு n;
}
#   endif
#   define ff_log2_16bit av_log2

#எனில் defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   எனில் ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   இல்லையெனில்
#       define ff_ctzll ff_ctzll_x86
நிலையான av_always_inline av_const முழு ff_ctzll_x86(long long v)
{
    திரும்பு ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#endif /* _MSC_VER */

#endif /* __INTEL_COMPILER */

#endif /* HAVE_FAST_CLZ */

#எனில் defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#எனில் defined(__POPCNT__)
    #define av_popcount   __builtin_popcount
#எனில் ARCH_X86_64
    #define av_popcount64 __builtin_popcountll
#endif

#endif /* __POPCNT__ */

#எனில் defined(__BMI2__)

#எனில் AV_GCC_VERSION_AT_LEAST(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#எனில் defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#define av_zero_extend av_zero_extend_bmi2
நிலையான av_always_inline av_const unsigned av_zero_extend_bmi2(unsigned a, unsigned p)
{
    எனில் (p > 31) abort();
    திரும்பு __builtin_ia32_bzhi_si(a, p);
}
#இல்லையெனில்
#define av_zero_extend __builtin_ia32_bzhi_si
#endif
#அல்லதெனில் HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#define av_zero_extend av_zero_extend_bmi2
நிலையான av_always_inline av_const unsigned av_zero_extend_bmi2(unsigned a, unsigned p)
{
#எனில் defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    எனில் (p > 31) abort();
#endif
    எனில் (av_builtin_constant_p(p))
        திரும்பு a & ((1U << p) - 1);
    இல்லையெனில் {
        unsigned x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        திரும்பு x;
    }
}
#endif /* AV_GCC_VERSION_AT_LEAST */

#endif /* __BMI2__ */

#endif /* __GNUC__ */

#endif /* AVUTIL_X86_INTMATH_H */
