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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_EMMS_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_EMMS_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"

#ಆದರೆ ARCH_X86

#ಆದರೆ HAVE_MMX_INLINE
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __MMX__
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಆದರೆ_ಅಂತ್ಯ

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
#ಆದರೆ !defined(__MMX__)
    ಆದರೆ(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#ಆದರೆ_ಅಂತ್ಯ
        __asm__ ಅಸ್ಥಿರ ("emms" ::: "memory");
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ff_assert0_fpu(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *file, ಪೂರ್ಣಾಂಕ ಸಾಲು_ಸಂಖ್ಯೆ)
{
    uint16_t state[14];
     __asm__ ಅಸ್ಥಿರ (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    ಆದರೆ ((state[4] & 3) != 3) {
        emms_c();
        av_log(ಖಾಲಿ, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               ಸಾಲು_ಸಂಖ್ಯೆ, file);
        abort();
    }
}

#ವ್ಯಾಖ್ಯಾನಿಸು ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#ಅಥವಾಆದರೆ HAVE_MMX && HAVE_MM_ಖಾಲಿಗಳು
#   include <mmintrin.h>
#   define emms_c mm_ಖಾಲಿಗಳು
#ಅಥವಾಆದರೆ HAVE_MMX_EXTERNAL
ಶೂನ್ಯ ff_emms_asm(ಶೂನ್ಯ);
#   define emms_c ff_emms_asm
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_MMX_INLINE */

#ಆದರೆ_ಅಂತ್ಯ /* ARCH_X86 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ emms_c
#   define emms_c() ಮಾಡು {} ಆಗ(0)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ff_assert0_fpu
#ವ್ಯಾಖ್ಯಾನಿಸು ff_assert0_fpu() ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#ವ್ಯಾಖ್ಯಾನಿಸು ff_assert1_fpu() ff_assert0_fpu()
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ff_assert1_fpu() ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_EMMS_H */
