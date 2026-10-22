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

#अगर_अघोषित AVUTIL_EMMS_H
#घोषणा AVUTIL_EMMS_H

#समावेश <stdint.h>
#समावेश <stdlib.h>

#समावेश "config.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/log.h"

#अगर ARCH_X86

#अगर HAVE_MMX_INLINE
#अगर_अघोषित __MMX__
#समावेश "libavutil/cpu.h"
#पूर्ण_अगर

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
अटल av_always_inline व्योम emms_c(व्योम)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#अगर !defined(__MMX__)
    अगर(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#पूर्ण_अगर
        __asm__ अस्थिर ("emms" ::: "memory");
}

अटल अंतरभूत व्योम ff_assert0_fpu(स्थिर अक्षर *file, पूर्णांक पंक्ति_संख्या)
{
    uint16_t state[14];
     __asm__ अस्थिर (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    अगर ((state[4] & 3) != 3) {
        emms_c();
        av_log(शून्य, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               पंक्ति_संख्या, file);
        पात();
    }
}

#घोषणा ff_assert0_fpu() ff_assert0_fpu(__खाता__, __LINE__)

#या_अगर HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#या_अगर HAVE_MMX_EXTERNAL
व्योम ff_emms_asm(व्योम);
#   define emms_c ff_emms_asm
#पूर्ण_अगर /* HAVE_MMX_INLINE */

#पूर्ण_अगर /* ARCH_X86 */

#अगर_अघोषित emms_c
#   define emms_c() करो {} जबतक(0)
#पूर्ण_अगर

#अगर_अघोषित ff_assert0_fpu
#घोषणा ff_assert0_fpu() ((व्योम)0)
#पूर्ण_अगर

#अगर defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#घोषणा ff_assert1_fpu() ff_assert0_fpu()
#अन्यथा
#घोषणा ff_assert1_fpu() ((व्योम)0)
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_EMMS_H */
