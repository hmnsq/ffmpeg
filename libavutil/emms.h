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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"

#ಯದಿ ARCH_X86

#ಯದಿ HAVE_MMX_INLINE
#ifndef __MMX__
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ emms_c(ಶೂನ್ಯ)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#ಯದಿ !defined(__MMX__)
    ಯದಿ(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ ಚಞ್ಚಲ ("emms" ::: "memory");
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ ff_assert0_fpu(ಧ್ರುವ ವರ್ಣ *file, ಪೂರ್ಣಾಙ್ಕ ಸಾಲು_ಸಂಖ್ಯೆ)
{
    uint16_t state[14];
     __asm__ ಚಞ್ಚಲ (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    ಯದಿ ((state[4] & 3) != 3) {
        emms_c();
        av_log(ರಿಕ್ತ, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               ಸಾಲು_ಸಂಖ್ಯೆ, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#ನೋಚೇದ್ಯದಿ HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#ನೋಚೇದ್ಯದಿ HAVE_MMX_EXTERNAL
ಶೂನ್ಯ ff_emms_asm(ಶೂನ್ಯ);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() ಕುರು {} ಯಾವತ್(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((ಶೂನ್ಯ)0)
#endif

#ಯದಿ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#ಅನ್ಯಥಾ
#define ff_assert1_fpu() ((ಶೂನ್ಯ)0)
#endif

#endif /* AVUTIL_EMMS_H */
