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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"

#ଯଦି ARCH_X86

#ଯଦି HAVE_MMX_INLINE
#ifndef __MMX__
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
ସ୍ଥିର av_always_inline ଶୂନ୍ୟ emms_c(ଶୂନ୍ୟ)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#ଯଦି !defined(__MMX__)
    ଯଦି(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ ଅସ୍ଥିର ("emms" ::: "memory");
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ ff_assert0_fpu(ଅଚଳ ଅକ୍ଷର *file, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଧାଡ଼ି_ସଂଖ୍ୟା)
{
    uint16_t state[14];
     __asm__ ଅସ୍ଥିର (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    ଯଦି ((state[4] & 3) != 3) {
        emms_c();
        av_log(ଖାଲି, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               ଧାଡ଼ି_ସଂଖ୍ୟା, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#ନଚେତଯଦି HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#ନଚେତଯଦି HAVE_MMX_EXTERNAL
ଶୂନ୍ୟ ff_emms_asm(ଶୂନ୍ୟ);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() କର {} ଯେତେବେଳେ(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((ଶୂନ୍ୟ)0)
#endif

#ଯଦି defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#ଅନ୍ୟଥା
#define ff_assert1_fpu() ((ଶୂନ୍ୟ)0)
#endif

#endif /* AVUTIL_EMMS_H */
