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

#که_نه_تعریف_شوی AVUTIL_X86_INTMATH_H
#تعریف_کړه AVUTIL_X86_INTMATH_H

#ضمن <stdint.h>
#ضمن <stdlib.h>
#إذا HAVE_FAST_CLZ
#إذا defined(_MSC_VER)
#ضمن <intrin.h>
#وإلاإذا defined(__INTEL_COMPILER)
#ضمن <immintrin.h>
#د_که_پای
#د_که_پای
#ضمن "config.h"

#إذا HAVE_FAST_CLZ
#إذا (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   إذا defined(__INTEL_COMPILER)
#       define ff_log2(x) (بټ_لټون_سرچپه((x)|1))
#   وإلا
#       define ff_log2 ff_log2_x86
ساكن av_always_inline av_const صحيح ff_log2_x86(بینښه صحيح v)
{
    بینښه اوږد n;
    بټ_لټون_سرچپه_2(&n, v|1);
    أرجع n;
}
#   endif
#   define ff_log2_16bit av_log2

#إذا defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   إذا ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   وإلا
#       define ff_ctzll ff_ctzll_x86
ساكن av_always_inline av_const صحيح ff_ctzll_x86(اوږد اوږد v)
{
    أرجع ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#د_که_پای /* _MSC_VER */

#د_که_پای /* __INTEL_COMPILER */

#د_که_پای /* HAVE_FAST_CLZ */

#إذا defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#إذا defined(__POPCNT__)
    #تعریف_کړه av_popcount   __builtin_popcount
#إذا ARCH_X86_64
    #تعریف_کړه av_popcount64 __builtin_popcountll
#د_که_پای

#د_که_پای /* __POPCNT__ */

#إذا defined(__BMI2__)

#إذا AV_GCC_نسخه_AT_لږترلږه(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#تعریف_کړه av_zero_extend av_zero_extend_bmi2
ساكن av_always_inline av_const بینښه av_zero_extend_bmi2(بینښه a, بینښه p)
{
    إذا (p > 31) abort();
    أرجع __builtin_ia32_bzhi_si(a, p);
}
#وإلا
#تعریف_کړه av_zero_extend __builtin_ia32_bzhi_si
#د_که_پای
#وإلاإذا HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#تعریف_کړه av_zero_extend av_zero_extend_bmi2
ساكن av_always_inline av_const بینښه av_zero_extend_bmi2(بینښه a, بینښه p)
{
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    إذا (p > 31) abort();
#د_که_پای
    إذا (av_builtin_constant_p(p))
        أرجع a & ((1U << p) - 1);
    وإلا {
        بینښه x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        أرجع x;
    }
}
#د_که_پای /* AV_GCC_VERSION_AT_LEAST */

#د_که_پای /* __BMI2__ */

#د_که_پای /* __GNUC__ */

#د_که_پای /* AVUTIL_X86_INTMATH_H */
