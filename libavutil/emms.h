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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/log.h"

#यदि ARCH_X86

#यदि HAVE_MMX_INLINE
#ifndef __MMX__
#अन्तर्भाव "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
स्थिर av_always_inline शून्य emms_c(शून्य)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#यदि !defined(__MMX__)
    यदि(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ चञ्चल ("emms" ::: "memory");
}

स्थिर अन्तःस्थ शून्य ff_assert0_fpu(अचर वर्ण *file, पूर्णाङ्क पङ्क्ति_सङ्ख्या)
{
    uint16_t state[14];
     __asm__ चञ्चल (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    यदि ((state[4] & 3) != 3) {
        emms_c();
        av_log(रिक्त, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               पङ्क्ति_सङ्ख्या, file);
        पात();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#अथवायदि HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#अथवायदि HAVE_MMX_EXTERNAL
शून्य ff_emms_asm(शून्य);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() गर {} जबसम्म(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((शून्य)0)
#endif

#यदि defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#अन्यथा
#define ff_assert1_fpu() ((शून्य)0)
#endif

#endif /* AVUTIL_EMMS_H */
