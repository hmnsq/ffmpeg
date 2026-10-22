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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_INTMATH_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_INTMATH_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಆದರೆ HAVE_FAST_CLZ
#ಆದರೆ defined(_MSC_VER)
#ಅನ್ತರ್ಭಾವ <intrin.h>
#ಅಥವಾಆದರೆ defined(__INTEL_COMPILER)
#ಅನ್ತರ್ಭಾವ <immintrin.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_FAST_CLZ
#ಆದರೆ (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   ಆದರೆ defined(__INTEL_COMPILER)
#       define ff_log2(x) (ಬಿಟ್_ಪರಿಶೀಲನೆ_ಹಿಮ್ಮುಖ((x)|1))
#   ಇಲ್ಲದಿದ್ದರೆ
#       define ff_log2 ff_log2_x86
ಸ್ಥಿರ av_always_inline av_const ಪೂರ್ಣಾಂಕ ff_log2_x86(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ v)
{
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ n;
    ಬಿಟ್_ಪರಿಶೀಲನೆ_ಹಿಮ್ಮುಖ_2(&n, v|1);
    ಹಿಂತಿರುಗಿ n;
}
#   endif
#   define ff_log2_16bit av_log2

#ಆದರೆ defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   ಆದರೆ ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   ಇಲ್ಲದಿದ್ದರೆ
#       define ff_ctzll ff_ctzll_x86
ಸ್ಥಿರ av_always_inline av_const ಪೂರ್ಣಾಂಕ ff_ctzll_x86(ದೀರ್ಘ ದೀರ್ಘ v)
{
    ಹಿಂತಿರುಗಿ ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#ಆದರೆ_ಅಂತ್ಯ /* _MSC_VER */

#ಆದರೆ_ಅಂತ್ಯ /* __INTEL_COMPILER */

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_FAST_CLZ */

#ಆದರೆ defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#ಆದರೆ defined(__POPCNT__)
    #ವ್ಯಾಖ್ಯಾನಿಸು av_popcount   __builtin_popcount
#ಆದರೆ ARCH_X86_64
    #ವ್ಯಾಖ್ಯಾನಿಸು av_popcount64 __builtin_popcountll
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* __POPCNT__ */

#ಆದರೆ defined(__BMI2__)

#ಆದರೆ AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#ವ್ಯಾಖ್ಯಾನಿಸು av_zero_extend av_zero_extend_bmi2
ಸ್ಥಿರ av_always_inline av_const ಚಿಹ್ನೆರಹಿತ av_zero_extend_bmi2(ಚಿಹ್ನೆರಹಿತ a, ಚಿಹ್ನೆರಹಿತ p)
{
    ಆದರೆ (p > 31) abort();
    ಹಿಂತಿರುಗಿ __builtin_ia32_bzhi_si(a, p);
}
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು av_zero_extend __builtin_ia32_bzhi_si
#ಆದರೆ_ಅಂತ್ಯ
#ಅಥವಾಆದರೆ HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#ವ್ಯಾಖ್ಯಾನಿಸು av_zero_extend av_zero_extend_bmi2
ಸ್ಥಿರ av_always_inline av_const ಚಿಹ್ನೆರಹಿತ av_zero_extend_bmi2(ಚಿಹ್ನೆರಹಿತ a, ಚಿಹ್ನೆರಹಿತ p)
{
#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ಆದರೆ (p > 31) abort();
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (av_builtin_constant_p(p))
        ಹಿಂತಿರುಗಿ a & ((1U << p) - 1);
    ಇಲ್ಲದಿದ್ದರೆ {
        ಚಿಹ್ನೆರಹಿತ x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        ಹಿಂತಿರುಗಿ x;
    }
}
#ಆದರೆ_ಅಂತ್ಯ /* AV_GCC_VERSION_AT_LEAST */

#ಆದರೆ_ಅಂತ್ಯ /* __BMI2__ */

#ಆದರೆ_ಅಂತ್ಯ /* __GNUC__ */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_INTMATH_H */
