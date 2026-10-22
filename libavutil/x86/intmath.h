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

#నిర్వచితం_కాకపోతే AVUTIL_X86_INTMATH_H
#నిర్వచించు AVUTIL_X86_INTMATH_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#ఒకవేళ HAVE_FAST_CLZ
#ఒకవేళ defined(_MSC_VER)
#అన్తర్భావ <intrin.h>
#లేదావేళ defined(__INTEL_COMPILER)
#అన్తర్భావ <immintrin.h>
#అయితే_ముగింపు
#అయితే_ముగింపు
#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_FAST_CLZ
#ఒకవేళ (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   ఒకవేళ defined(__INTEL_COMPILER)
#       define ff_log2(x) (బిట్టు_పరిశీలన_తిరగేయి((x)|1))
#   లేకపోతే
#       define ff_log2 ff_log2_x86
స్థిర av_always_inline av_const పూర్ణాంకం ff_log2_x86(గుర్తులేని పూర్ణాంకం v)
{
    గుర్తులేని దీర్ఘ n;
    బిట్టు_పరిశీలన_తిరగేయి_2(&n, v|1);
    తిరిగి n;
}
#   endif
#   define ff_log2_16bit av_log2

#ఒకవేళ defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   ఒకవేళ ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   లేకపోతే
#       define ff_ctzll ff_ctzll_x86
స్థిర av_always_inline av_const పూర్ణాంకం ff_ctzll_x86(దీర్ఘ దీర్ఘ v)
{
    తిరిగి ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#అయితే_ముగింపు /* _MSC_VER */

#అయితే_ముగింపు /* __INTEL_COMPILER */

#అయితే_ముగింపు /* HAVE_FAST_CLZ */

#ఒకవేళ defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#ఒకవేళ defined(__POPCNT__)
    #నిర్వచించు av_popcount   __builtin_popcount
#ఒకవేళ ARCH_X86_64
    #నిర్వచించు av_popcount64 __builtin_popcountll
#అయితే_ముగింపు

#అయితే_ముగింపు /* __POPCNT__ */

#ఒకవేళ defined(__BMI2__)

#ఒకవేళ AV_GCC_సంస్కరణ_AT_కనిష్ఠ(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#నిర్వచించు av_zero_extend av_zero_extend_bmi2
స్థిర av_always_inline av_const గుర్తులేని av_zero_extend_bmi2(గుర్తులేని a, గుర్తులేని p)
{
    ఒకవేళ (p > 31) abort();
    తిరిగి __builtin_ia32_bzhi_si(a, p);
}
#లేకపోతే
#నిర్వచించు av_zero_extend __builtin_ia32_bzhi_si
#అయితే_ముగింపు
#లేదావేళ HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#నిర్వచించు av_zero_extend av_zero_extend_bmi2
స్థిర av_always_inline av_const గుర్తులేని av_zero_extend_bmi2(గుర్తులేని a, గుర్తులేని p)
{
#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ఒకవేళ (p > 31) abort();
#అయితే_ముగింపు
    ఒకవేళ (av_builtin_constant_p(p))
        తిరిగి a & ((1U << p) - 1);
    లేకపోతే {
        గుర్తులేని x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        తిరిగి x;
    }
}
#అయితే_ముగింపు /* AV_GCC_VERSION_AT_LEAST */

#అయితే_ముగింపు /* __BMI2__ */

#అయితే_ముగింపు /* __GNUC__ */

#అయితే_ముగింపు /* AVUTIL_X86_INTMATH_H */
