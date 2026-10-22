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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_INTMATH_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_INTMATH_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਜੇ HAVE_FAST_CLZ
#ਜੇ defined(_MSC_VER)
#ਅਨ੍ਤਰ੍ਭਾਵ <intrin.h>
#ਜਾਂਜੇ defined(__INTEL_COMPILER)
#ਅਨ੍ਤਰ੍ਭਾਵ <immintrin.h>
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_FAST_CLZ
#ਜੇ (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   ਜੇ defined(__INTEL_COMPILER)
#       define ff_log2(x) (ਦੋਆਧਾਰੀ_ਅੰਕ_ਜਾਂਚ_ਉਲਟ((x)|1))
#   ਨਹੀਂਤਾਂ
#       define ff_log2 ff_log2_x86
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ ff_log2_x86(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ v)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ n;
    ਦੋਆਧਾਰੀ_ਅੰਕ_ਜਾਂਚ_ਉਲਟ_2(&n, v|1);
    ਵਾਪਸ n;
}
#   endif
#   define ff_log2_16bit av_log2

#ਜੇ defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   ਜੇ ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   ਨਹੀਂਤਾਂ
#       define ff_ctzll ff_ctzll_x86
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ ff_ctzll_x86(ਲੰਮਾ ਲੰਮਾ v)
{
    ਵਾਪਸ ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#ਜੇ_ਅੰਤ /* _MSC_VER */

#ਜੇ_ਅੰਤ /* __INTEL_COMPILER */

#ਜੇ_ਅੰਤ /* HAVE_FAST_CLZ */

#ਜੇ defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#ਜੇ defined(__POPCNT__)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_popcount   __builtin_popcount
#ਜੇ ARCH_X86_64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_popcount64 __builtin_popcountll
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* __POPCNT__ */

#ਜੇ defined(__BMI2__)

#ਜੇ AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_zero_extend av_zero_extend_bmi2
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ av_zero_extend_bmi2(ਬਿਨਾਨਿਸ਼ਾਨੀ a, ਬਿਨਾਨਿਸ਼ਾਨੀ p)
{
    ਜੇ (p > 31) abort();
    ਵਾਪਸ __builtin_ia32_bzhi_si(a, p);
}
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_zero_extend __builtin_ia32_bzhi_si
#ਜੇ_ਅੰਤ
#ਜਾਂਜੇ HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_zero_extend av_zero_extend_bmi2
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ av_zero_extend_bmi2(ਬਿਨਾਨਿਸ਼ਾਨੀ a, ਬਿਨਾਨਿਸ਼ਾਨੀ p)
{
#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ਜੇ (p > 31) abort();
#ਜੇ_ਅੰਤ
    ਜੇ (av_builtin_constant_p(p))
        ਵਾਪਸ a & ((1U << p) - 1);
    ਨਹੀਂਤਾਂ {
        ਬਿਨਾਨਿਸ਼ਾਨੀ x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        ਵਾਪਸ x;
    }
}
#ਜੇ_ਅੰਤ /* AV_GCC_VERSION_AT_LEAST */

#ਜੇ_ਅੰਤ /* __BMI2__ */

#ਜੇ_ਅੰਤ /* __GNUC__ */

#ਜੇ_ਅੰਤ /* AVUTIL_X86_INTMATH_H */
