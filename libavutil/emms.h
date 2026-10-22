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

#నిర్వచితం_కాకపోతే AVUTIL_EMMS_H
#నిర్వచించు AVUTIL_EMMS_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/log.h"

#ఒకవేళ ARCH_X86

#ఒకవేళ HAVE_MMX_INLINE
#నిర్వచితం_కాకపోతే __MMX__
#అన్తర్భావ "libavutil/cpu.h"
#అయితే_ముగింపు

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
స్థిర av_always_inline శూన్య emms_c(శూన్య)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#ఒకవేళ !defined(__MMX__)
    ఒకవేళ(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#అయితే_ముగింపు
        __asm__ అస్థిర ("emms" ::: "memory");
}

స్థిర అంతఃవరుస శూన్య ff_assert0_fpu(స్థిరరాశి అక్షరం *file, పూర్ణాంకం పంక్తి_సంఖ్య)
{
    uint16_t state[14];
     __asm__ అస్థిర (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    ఒకవేళ ((state[4] & 3) != 3) {
        emms_c();
        av_log(ఖాళీ, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               పంక్తి_సంఖ్య, file);
        abort();
    }
}

#నిర్వచించు ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#లేదావేళ HAVE_MMX && HAVE_MM_ఖాళీలు
#   include <mmintrin.h>
#   define emms_c mm_ఖాళీలు
#లేదావేళ HAVE_MMX_EXTERNAL
శూన్య ff_emms_asm(శూన్య);
#   define emms_c ff_emms_asm
#అయితే_ముగింపు /* HAVE_MMX_INLINE */

#అయితే_ముగింపు /* ARCH_X86 */

#నిర్వచితం_కాకపోతే emms_c
#   define emms_c() చేయి {} అయితే(0)
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే ff_assert0_fpu
#నిర్వచించు ff_assert0_fpu() ((శూన్య)0)
#అయితే_ముగింపు

#ఒకవేళ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#నిర్వచించు ff_assert1_fpu() ff_assert0_fpu()
#లేకపోతే
#నిర్వచించు ff_assert1_fpu() ((శూన్య)0)
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_EMMS_H */
