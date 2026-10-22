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

#جے_بنا_تعریف AVUTIL_X86_INTMATH_H
#تعریف_کرو AVUTIL_X86_INTMATH_H

#ضمن <stdint.h>
#ضمن <stdlib.h>
#إذا HAVE_FAST_CLZ
#إذا defined(_MSC_VER)
#ضمن <intrin.h>
#وإلاإذا defined(__INTEL_COMPILER)
#ضمن <immintrin.h>
#جے_انت
#جے_انت
#ضمن "config.h"

#إذا HAVE_FAST_CLZ
#إذا (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   إذا defined(__INTEL_COMPILER)
#       define ff_log2(x) (ثنائی_ہندسہ_جانچ_الٹ((x)|1))
#   وإلا
#       define ff_log2 ff_log2_x86
ساكن av_always_inline av_const صحيح ff_log2_x86(بنانشانی صحيح v)
{
    بنانشانی لما n;
    ثنائی_ہندسہ_جانچ_الٹ_2(&n, v|1);
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
ساكن av_always_inline av_const صحيح ff_ctzll_x86(لما لما v)
{
    أرجع ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#جے_انت /* _MSC_VER */

#جے_انت /* __INTEL_COMPILER */

#جے_انت /* HAVE_FAST_CLZ */

#إذا defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#إذا defined(__POPCNT__)
    #تعریف_کرو av_popcount   __builtin_popcount
#إذا ARCH_X86_64
    #تعریف_کرو av_popcount64 __builtin_popcountll
#جے_انت

#جے_انت /* __POPCNT__ */

#إذا defined(__BMI2__)

#إذا AV_GCC_نسخہ_AT_گھٹ_توں_گھٹ(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#تعریف_کرو av_zero_extend av_zero_extend_bmi2
ساكن av_always_inline av_const بنانشانی av_zero_extend_bmi2(بنانشانی a, بنانشانی p)
{
    إذا (p > 31) abort();
    أرجع __builtin_ia32_bzhi_si(a, p);
}
#وإلا
#تعریف_کرو av_zero_extend __builtin_ia32_bzhi_si
#جے_انت
#وإلاإذا HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#تعریف_کرو av_zero_extend av_zero_extend_bmi2
ساكن av_always_inline av_const بنانشانی av_zero_extend_bmi2(بنانشانی a, بنانشانی p)
{
#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    إذا (p > 31) abort();
#جے_انت
    إذا (av_builtin_constant_p(p))
        أرجع a & ((1U << p) - 1);
    وإلا {
        بنانشانی x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        أرجع x;
    }
}
#جے_انت /* AV_GCC_VERSION_AT_LEAST */

#جے_انت /* __BMI2__ */

#جے_انت /* __GNUC__ */

#جے_انت /* AVUTIL_X86_INTMATH_H */
