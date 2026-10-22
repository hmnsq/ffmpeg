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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdlib.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/log.h"

#જો ARCH_X86

#જો HAVE_MMX_INLINE
#ifndef __MMX__
#અન્તર્ભાવ "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
સ્થિર av_always_inline શૂન્ય emms_c(શૂન્ય)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#જો !defined(__MMX__)
    જો(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ અસ્થિર ("emms" ::: "memory");
}

સ્થિર અંતઃરેખ શૂન્ય ff_assert0_fpu(અચલ અક્ષર *file, પૂર્ણાંક લીટી_સંખ્યા)
{
    uint16_t state[14];
     __asm__ અસ્થિર (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    જો ((state[4] & 3) != 3) {
        emms_c();
        av_log(ખાલી, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               લીટી_સંખ્યા, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#અથવાજો HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#અથવાજો HAVE_MMX_EXTERNAL
શૂન્ય ff_emms_asm(શૂન્ય);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() કરો {} જ્યારે(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((શૂન્ય)0)
#endif

#જો defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#નહીંતર
#define ff_assert1_fpu() ((શૂન્ય)0)
#endif

#endif /* AVUTIL_EMMS_H */
