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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdlib.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/log.h"

#எனில் ARCH_X86

#எனில் HAVE_MMX_INLINE
#ifndef __MMX__
#அந்தர்பாவ "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
நிலையான av_always_inline வெறுமை emms_c(வெறுமை)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#எனில் !defined(__MMX__)
    எனில்(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ நிலையற்ற ("emms" ::: "memory");
}

நிலையான உள்வரி வெறுமை ff_assert0_fpu(மாறிலி எழுத்து *file, முழு வரி_எண்)
{
    uint16_t state[14];
     __asm__ நிலையற்ற (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    எனில் ((state[4] & 3) != 3) {
        emms_c();
        av_log(வெற்று, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               வரி_எண், file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#அல்லதெனில் HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#அல்லதெனில் HAVE_MMX_EXTERNAL
வெறுமை ff_emms_asm(வெறுமை);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() செய் {} போது(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((வெறுமை)0)
#endif

#எனில் defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#இல்லையெனில்
#define ff_assert1_fpu() ((வெறுமை)0)
#endif

#endif /* AVUTIL_EMMS_H */
