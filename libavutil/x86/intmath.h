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

#اگر_غیر_تعریف_شدہ AVUTIL_X86_INTMATH_H
#تعریف_کرو AVUTIL_X86_INTMATH_H

#شامل <stdint.h>
#شامل <stdlib.h>
#اگر HAVE_FAST_CLZ
#اگر defined(_MSC_VER)
#شامل <intrin.h>
#وگرنہ_اگر defined(__INTEL_COMPILER)
#شامل <immintrin.h>
#اگر_ختم
#اگر_ختم
#شامل "config.h"

#اگر HAVE_FAST_CLZ
#اگر (defined(__INTEL_COMPILER) && (__INTEL_COMPILER>=1216)) || defined(_MSC_VER)
#   اگر defined(__INTEL_COMPILER)
#       define ff_log2(x) (ثنائی_ہندسہ_جائزہ_الٹ((x)|1))
#   ورنہ
#       define ff_log2 ff_log2_x86
ساکن av_always_inline av_const صحیح ff_log2_x86(غیرعلامتی صحیح v)
{
    غیرعلامتی طویل n;
    ثنائی_ہندسہ_جائزہ_الٹ_2(&n, v|1);
    واپس n;
}
#   endif
#   define ff_log2_16bit av_log2

#اگر defined(__INTEL_COMPILER) || (defined(_MSC_VER) && \
                                  (defined(__BMI__) || !defined(__clang__)))
#   define ff_ctz(v) _tzcnt_u32(v)

#   اگر ARCH_X86_64
#       define ff_ctzll(v) _tzcnt_u64(v)
#   ورنہ
#       define ff_ctzll ff_ctzll_x86
ساکن av_always_inline av_const صحیح ff_ctzll_x86(طویل طویل v)
{
    واپس ((uint32_t)v == 0) ? _tzcnt_u32((uint32_t)(v >> 32)) + 32 : _tzcnt_u32((uint32_t)v);
}
#   endif
#اگر_ختم /* _MSC_VER */

#اگر_ختم /* __INTEL_COMPILER */

#اگر_ختم /* HAVE_FAST_CLZ */

#اگر defined(__GNUC__) || defined(__clang__)

/* Our generic version of av_popcount is faster than GCC's built-in on
 * CPUs that don't support the popcnt instruction.
 */
#اگر defined(__POPCNT__)
    #تعریف_کرو av_popcount   __builtin_popcount
#اگر ARCH_X86_64
    #تعریف_کرو av_popcount64 __builtin_popcountll
#اگر_ختم

#اگر_ختم /* __POPCNT__ */

#اگر defined(__BMI2__)

#اگر AV_GCC_نسخہ_AT_کم_سے_کم(5,1) || AV_HAS_BUILTIN(__builtin_ia32_bzhi_si)
#اگر defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
#تعریف_کرو av_zero_extend av_zero_extend_bmi2
ساکن av_always_inline av_const غیرعلامتی av_zero_extend_bmi2(غیرعلامتی a, غیرعلامتی p)
{
    اگر (p > 31) abort();
    واپس __builtin_ia32_bzhi_si(a, p);
}
#ورنہ
#تعریف_کرو av_zero_extend __builtin_ia32_bzhi_si
#اگر_ختم
#وگرنہ_اگر HAVE_INLINE_ASM
/* GCC releases before 5.1.0 have a broken bzhi builtin, so for those we
 * implement it using inline assembly
 */
#تعریف_کرو av_zero_extend av_zero_extend_bmi2
ساکن av_always_inline av_const غیرعلامتی av_zero_extend_bmi2(غیرعلامتی a, غیرعلامتی p)
{
#اگر defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    اگر (p > 31) abort();
#اگر_ختم
    اگر (av_builtin_constant_p(p))
        واپس a & ((1U << p) - 1);
    ورنہ {
        غیرعلامتی x;
        __asm__ ("bzhi %2, %1, %0 \n\t" : "=r"(x) : "rm"(a), "r"(p));
        واپس x;
    }
}
#اگر_ختم /* AV_GCC_VERSION_AT_LEAST */

#اگر_ختم /* __BMI2__ */

#اگر_ختم /* __GNUC__ */

#اگر_ختم /* AVUTIL_X86_INTMATH_H */
