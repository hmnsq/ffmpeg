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

#اگر_غیر_تعریف_شدہ AVUTIL_EMMS_H
#تعریف_کرو AVUTIL_EMMS_H

#شامل <stdint.h>
#شامل <stdlib.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/log.h"

#اگر ARCH_X86

#اگر HAVE_MMX_INLINE
#اگر_غیر_تعریف_شدہ __MMX__
#شامل "libavutil/cpu.h"
#اگر_ختم

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
ساکن av_always_inline خالی emms_c(خالی)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#اگر !defined(__MMX__)
    اگر(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#اگر_ختم
        __asm__ متلون ("emms" ::: "memory");
}

ساکن اندرونی خالی ff_assert0_fpu(ثابت حرف *file, صحیح سطر_نمبر)
{
    uint16_t state[14];
     __asm__ متلون (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    اگر ((state[4] & 3) != 3) {
        emms_c();
        av_log(تہی, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               سطر_نمبر, file);
        abort();
    }
}

#تعریف_کرو ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#وگرنہ_اگر HAVE_MMX && HAVE_MM_خالی_خانے
#   include <mmintrin.h>
#   define emms_c mm_خالی_خانے
#وگرنہ_اگر HAVE_MMX_EXTERNAL
خالی ff_emms_asm(خالی);
#   define emms_c ff_emms_asm
#اگر_ختم /* HAVE_MMX_INLINE */

#اگر_ختم /* ARCH_X86 */

#اگر_غیر_تعریف_شدہ emms_c
#   define emms_c() کرو {} جب(0)
#اگر_ختم

#اگر_غیر_تعریف_شدہ ff_assert0_fpu
#تعریف_کرو ff_assert0_fpu() ((خالی)0)
#اگر_ختم

#اگر defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#تعریف_کرو ff_assert1_fpu() ff_assert0_fpu()
#ورنہ
#تعریف_کرو ff_assert1_fpu() ((خالی)0)
#اگر_ختم

#اگر_ختم /* AVUTIL_EMMS_H */
