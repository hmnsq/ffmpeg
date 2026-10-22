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

#यदि_अपरिभाषितम् AVUTIL_X86_INTMATH_H
#परिभाषय AVUTIL_X86_INTMATH_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#यदि HAVE_FAST_CLZ
#यदि defined(_MSC_VER)
#अन्तर्भाव <intrin.h>
#नोचेद्यदि defined(__INTEL_COMPILER)
#अन्तर्भाव <immintrin.h>
#यदि_अन्तः
#यदि_अन्तः
#अन्तर्भाव "config.h"

#यदि HAVE_FAST_CLZ
#यदि (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   यदि defined(__INTEL_COMPILER)
#       define ff_log2(x) (bit_अवलोकनम्_reverse((x)|1))
#   अन्यथा
#       define ff_log2 ff_log2_x86
स्थिर av_always_inline av_const पूर्णाङ्क ff_log2_x86(अचिह्नित पूर्णाङ्क v)
{
    अचिह्नित दीर्घ n;
    Bit_अवलोकनम्_Reverse(&n, v|1);
    प्रत्यागम n;
}
#   endif
#   define ff_log2_16bit av_log2

#यदि defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   यदि ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   अन्यथा
#       define ff_ctzll ff_ctzll_x86
स्थिर av_always_inline av_const पूर्णाङ्क ff_ctzll_x86(दीर्घ दीर्घ v)
{
    प्रत्यागम ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#यदि_अन्तः /* _MSC_VER */

#यदि_अन्तः /* __INTEL_COMPILER */

#यदि_अन्तः /* HAVE_FAST_CLZ */

#यदि defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#यदि defined(__POPCNT__)
    #परिभाषय av_popcount   __builtin_popcount
#यदि ARCH_X86_64
    #परिभाषय av_popcount64 __builtin_popcountll
#यदि_अन्तः

#यदि_अन्तः /* __POPCNT__ */

#यदि defined(__BMI2__)

#यदि AV_GCC_संस्करणम्_AT_न्यूनतमम्(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#यदि defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#परिभाषय av_zero_extend av_zero_extend_bmi2
स्थिर av_always_inline av_const अचिह्नित av_zero_extend_bmi2(अचिह्नित a, अचिह्नित p)
{
    यदि (p > 31) abort();
    प्रत्यागम __builtin_ia32_bzhi_si(a, p);
}
#अन्यथा
#परिभाषय av_zero_extend __builtin_ia32_bzhi_si
#यदि_अन्तः
#नोचेद्यदि HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#परिभाषय av_zero_extend av_zero_extend_bmi2
स्थिर av_always_inline av_const अचिह्नित av_zero_extend_bmi2(अचिह्नित a, अचिह्नित p)
{
#यदि defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    यदि (p > 31) abort();
#यदि_अन्तः
    यदि (av_builtin_constant_p(p))
        प्रत्यागम a & ((1U << p) - 1);
    अन्यथा {
        अचिह्नित x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        प्रत्यागम x;
    }
}
#यदि_अन्तः /* AV_GCC_VERSION_AT_LEAST */

#यदि_अन्तः /* __BMI2__ */

#यदि_अन्तः /* __GNUC__ */

#यदि_अन्तः /* AVUTIL_X86_INTMATH_H */
