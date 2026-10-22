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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdlib.h>

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/log.h"

#যদি ARCH_X86

#যদি HAVE_MMX_INLINE
#ifndef __MMX__
#অন্তর্ভাব "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
স্থির av_always_inline শূন্য emms_c(শূন্য)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#যদি !defined(__MMX__)
    যদি(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ চঞ্চল ("emms" ::: "memory");
}

স্থির অন্তঃস্থ শূন্য ff_assert0_fpu(ধ্রুব বর্ণ *file, পূর্ণাঙ্ক সারি_সংখ্যা)
{
    uint16_t state[14];
     __asm__ চঞ্চল (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    যদি ((state[4] & 3) != 3) {
        emms_c();
        av_log(রিক্ত, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               সারি_সংখ্যা, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#নোচেদ্যদি HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#নোচেদ্যদি HAVE_MMX_EXTERNAL
শূন্য ff_emms_asm(শূন্য);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() কুরু {} যাবত্(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((শূন্য)0)
#endif

#যদি defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#অন্যথা
#define ff_assert1_fpu() ((শূন্য)0)
#endif

#endif /* AVUTIL_EMMS_H */
