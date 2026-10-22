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

#include <stdint.h>
#include <stdlib.h>

#include "config.h"
#include "libavutil/attributes.h"
#include "libavutil/log.h"

#නම් ARCH_X86

#නම් HAVE_MMX_INLINE
#ifndef __MMX__
#include "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
static av_always_inline void emms_c(void)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#නම් !defined(__MMX__)
    නම්(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ ca_ncala ("emms" ::: "memory");
}

static anta_hstha void ff_assert0_fpu(const var_na *file, පූර්ණ_සංඛ්‍යා line_number)
{
    uint16_t state[14];
     __asm__ ca_ncala (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    නම් ((state[4] & 3) != 3) {
        emms_c();
        av_log(NULL, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               line_number, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#elif HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#elif HAVE_MMX_EXTERNAL
void ff_emms_asm(void);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() do {} අතරතුර(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((void)0)
#endif

#නම් defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#නැතහොත්
#define ff_assert1_fpu() ((void)0)
#endif

#endif /* AVUTIL_EMMS_H */
