/*
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

#اگر_تعریف_نشده AVUTIL_EMMS_H
#تعریف_کن AVUTIL_EMMS_H

#ضمن <stdint.h>
#ضمن <stdlib.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/log.h"

#إذا ARCH_X86

#إذا HAVE_MMX_INLINE
#اگر_تعریف_نشده __MMX__
#ضمن "libavutil/cpu.h"
#پایان_اگر

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
ساكن av_always_inline فراغ emms_c(فراغ)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#إذا !defined(__MMX__)
    إذا(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#پایان_اگر
        __asm__ متطاير ("emms" ::: "memory");
}

ساكن مضمن فراغ ff_assert0_fpu(ثابت حرف *file, صحيح سطر_عدد)
{
    uint16_t state[14];
     __asm__ متطاير (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    إذا ((state[4] & 3) != 3) {
        emms_c();
        av_log(عدم, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               سطر_عدد, file);
        abort();
    }
}

#تعریف_کن ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#وإلاإذا HAVE_MMX && HAVE_MM_خالی
#   include <mmintrin.h>
#   define emms_c mm_خالی
#وإلاإذا HAVE_MMX_EXTERNAL
فراغ ff_emms_asm(فراغ);
#   define emms_c ff_emms_asm
#پایان_اگر /* HAVE_MMX_INLINE */

#پایان_اگر /* ARCH_X86 */

#اگر_تعریف_نشده emms_c
#   define emms_c() افعل {} طالما(0)
#پایان_اگر

#اگر_تعریف_نشده ff_assert0_fpu
#تعریف_کن ff_assert0_fpu() ((فراغ)0)
#پایان_اگر

#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#تعریف_کن ff_assert1_fpu() ff_assert0_fpu()
#وإلا
#تعریف_کن ff_assert1_fpu() ((فراغ)0)
#پایان_اگر

#پایان_اگر /* AVUTIL_EMMS_H */
