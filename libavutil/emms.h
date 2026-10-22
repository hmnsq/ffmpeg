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

#جے_بنا_تعریف AVUTIL_EMMS_H
#تعریف_کرو AVUTIL_EMMS_H

#ضمن <stdint.h>
#ضمن <stdlib.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/log.h"

#إذا ARCH_X86

#إذا HAVE_MMX_INLINE
#جے_بنا_تعریف __MMX__
#ضمن "libavutil/cpu.h"
#جے_انت

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
#جے_انت
        __asm__ متطاير ("emms" ::: "memory");
}

ساكن مضمن فراغ ff_assert0_fpu(ثابت حرف *file, صحيح سطر_نمبر)
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
               سطر_نمبر, file);
        abort();
    }
}

#تعریف_کرو ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#وإلاإذا HAVE_MMX && HAVE_MM_خالی_تھاواں
#   include <mmintrin.h>
#   define emms_c mm_خالی_تھاواں
#وإلاإذا HAVE_MMX_EXTERNAL
فراغ ff_emms_asm(فراغ);
#   define emms_c ff_emms_asm
#جے_انت /* HAVE_MMX_INLINE */

#جے_انت /* ARCH_X86 */

#جے_بنا_تعریف emms_c
#   define emms_c() افعل {} طالما(0)
#جے_انت

#جے_بنا_تعریف ff_assert0_fpu
#تعریف_کرو ff_assert0_fpu() ((فراغ)0)
#جے_انت

#إذا defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#تعریف_کرو ff_assert1_fpu() ff_assert0_fpu()
#وإلا
#تعریف_کرو ff_assert1_fpu() ((فراغ)0)
#جے_انت

#جے_انت /* AVUTIL_EMMS_H */
