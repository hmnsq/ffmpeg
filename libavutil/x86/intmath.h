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

#अगर_अघोषित AVUTIL_X86_INTMATH_H
#घोषणा AVUTIL_X86_INTMATH_H

#समावेश <stdint.h>
#समावेश <stdlib.h>
#अगर HAVE_FAST_CLZ
#अगर defined(_MSC_VER)
#समावेश <intrin.h>
#या_अगर defined(__INTEL_COMPILER)
#समावेश <immintrin.h>
#पूर्ण_अगर
#पूर्ण_अगर
#समावेश "config.h"

#अगर HAVE_FAST_CLZ
#अगर (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   अगर defined(__INTEL_COMPILER)
#       define ff_log2(x) (_bit_scan_reverse((x)|1))
#   अन्यथा
#       define ff_log2 ff_log2_x86
अटल av_always_inline av_const पूर्णांक ff_log2_x86(अचिन्हित पूर्णांक v)
{
    अचिन्हित दीर्घ n;
    _BitScanReverse(&n, v|1);
    वापस n;
}
#   endif
#   define ff_log2_16bit av_log2

#अगर defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   अगर ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   अन्यथा
#       define ff_ctzll ff_ctzll_x86
अटल av_always_inline av_const पूर्णांक ff_ctzll_x86(दीर्घ दीर्घ v)
{
    वापस ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#पूर्ण_अगर /* _MSC_VER */

#पूर्ण_अगर /* __INTEL_COMPILER */

#पूर्ण_अगर /* HAVE_FAST_CLZ */

#अगर defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#अगर defined(__POPCNT__)
    #घोषणा av_popcount   __builtin_popcount
#अगर ARCH_X86_64
    #घोषणा av_popcount64 __builtin_popcountll
#पूर्ण_अगर

#पूर्ण_अगर /* __POPCNT__ */

#अगर defined(__BMI2__)

#अगर AV_GCC_VERSION_AT_LEAST(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#घोषणा av_zero_extend av_zero_extend_bmi2
अटल av_always_inline av_const अचिन्हित av_zero_extend_bmi2(अचिन्हित a, अचिन्हित p)
{
    अगर (p > 31) पात();
    वापस __builtin_ia32_bzhi_si(a, p);
}
#अन्यथा
#घोषणा av_zero_extend __builtin_ia32_bzhi_si
#पूर्ण_अगर
#या_अगर HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#घोषणा av_zero_extend av_zero_extend_bmi2
अटल av_always_inline av_const अचिन्हित av_zero_extend_bmi2(अचिन्हित a, अचिन्हित p)
{
#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    अगर (p > 31) पात();
#पूर्ण_अगर
    अगर (av_builtin_constant_p(p))
        वापस a & ((1U << p) - 1);
    अन्यथा {
        अचिन्हित x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        वापस x;
    }
}
#पूर्ण_अगर /* AV_GCC_VERSION_AT_LEAST */

#पूर्ण_अगर /* __BMI2__ */

#पूर्ण_अगर /* __GNUC__ */

#पूर्ण_अगर /* AVUTIL_X86_INTMATH_H */
