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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdlib.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/log.h"

#എങ്കിൽ ARCH_X86

#എങ്കിൽ HAVE_MMX_INLINE
#ifndef __MMX__
#അന്തര്ഭാവ "libavutil/cpu.h"
#endif

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
സ്ഥിതം av_always_inline ശൂന്യം emms_c(ശൂന്യം)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#എങ്കിൽ !defined(__MMX__)
    എങ്കിൽ(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#endif
        __asm__ അസ്ഥിര ("emms" ::: "memory");
}

സ്ഥിതം വരിയിൽ ശൂന്യം ff_assert0_fpu(സ്ഥിരം അക്ഷരം *file, പൂർണ്ണസംഖ്യ വരി_സംഖ്യ)
{
    uint16_t state[14];
     __asm__ അസ്ഥിര (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    എങ്കിൽ ((state[4] & 3) != 3) {
        emms_c();
        av_log(ശൂന്യ, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               വരി_സംഖ്യ, file);
        abort();
    }
}

#define ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#അല്ലെങ്കിലെങ്കിൽ HAVE_MMX && HAVE_MM_EMPTY
#   include <mmintrin.h>
#   define emms_c _mm_empty
#അല്ലെങ്കിലെങ്കിൽ HAVE_MMX_EXTERNAL
ശൂന്യം ff_emms_asm(ശൂന്യം);
#   define emms_c ff_emms_asm
#endif /* HAVE_MMX_INLINE */

#endif /* ARCH_X86 */

#ifndef emms_c
#   define emms_c() ചെയ്യുക {} ആകുമ്പോൾ(0)
#endif

#ifndef ff_assert0_fpu
#define ff_assert0_fpu() ((ശൂന്യം)0)
#endif

#എങ്കിൽ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#define ff_assert1_fpu() ff_assert0_fpu()
#അല്ലെങ്കിൽ
#define ff_assert1_fpu() ((ശൂന്യം)0)
#endif

#endif /* AVUTIL_EMMS_H */
