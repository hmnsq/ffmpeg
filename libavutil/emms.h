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

#ifndef AVUTIL_EMMS_H
#define AVUTIL_EMMS_H

#شامل <stdint.h>
#شامل <stdlib.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/log.h"

#اگر ARCH_X86

#اگر HAVE_MMX_INLINE
#ifndef __MMX__
#شامل "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
ایستا av_always_inline تهی emms_c(تهی)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#اگر !defined(__MMX__)
    اگر(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ فرار ("emms" ::: "memory");
}

ایستا درونخطی تهی ff_assert0_fpu(ثابت نویسه *file, صحیح سطر_عدد)
{
    uint16_t state[14];
     __asm__ فرار (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    اگر ((state[4] & 3) != 3) {
        emms_c();
        av_log(پوچ, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               سطر_عدد, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#وگرنهاگر HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#وگرنهاگر HAVE_MMX_EXTERNAL
تهی ff_emms_asm(تهی);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() انجامبده {} وقتی(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((تهی)0)
#endif

#اگر defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#وگرنه
#define ff_assert1_fpu() ((تهی)0)
#endif

#endif /* AVUTIL_EMMS_H */
