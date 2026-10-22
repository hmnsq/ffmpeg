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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_EMMS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_EMMS_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"

#ਜੇ ARCH_X86

#ਜੇ HAVE_MMX_INLINE
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __MMX__
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਜੇ_ਅੰਤ

#   define emms_c emms_c
/**
 * Empty mmx state.
 * this must be called between any dsp function and float/double code.
 * for example sin(); dsp->idct_put(); emms_c(); cos()
 * Note, *alloc() and *free() also use float code in some libc implementations
 * thus this also applies to them or any function using them.
 */
ਸਥਿਰ av_always_inline ਖਾਲੀ emms_c(ਖਾਲੀ)
{
/* Some inlined functions may also use mmx instructions regardless of
 * runtime cpuflags. With that in mind, we unconditionally empty the
 * mmx state if the target cpu chosen at configure time supports it.
 */
#ਜੇ !defined(__MMX__)
    ਜੇ(av_get_cpu_flags() & AV_CPU_FLAG_MMX)
#ਜੇ_ਅੰਤ
        __asm__ ਅਸਥਿਰ ("emms" ::: "memory");
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ff_assert0_fpu(ਅਚਲ ਅੱਖਰ *file, ਪੂਰਨ ਸਤਰ_ਸੰਖਿਆ)
{
    uint16_t state[14];
     __asm__ ਅਸਥਿਰ (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    ਜੇ ((state[4] & 3) != 3) {
        emms_c();
        av_log(ਨਿਰਾ, AV_LOG_PANIC,
               "Invalid floating point state assertion "
               "triggered at line %u in file %s\n",
               ਸਤਰ_ਸੰਖਿਆ, file);
        abort();
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_assert0_fpu() ff_assert0_fpu(__FILE__, __LINE__)

#ਜਾਂਜੇ HAVE_MMX && HAVE_MM_ਖਾਲੀ_ਥਾਵਾਂ
#   include <mmintrin.h>
#   define emms_c mm_ਖਾਲੀ_ਥਾਵਾਂ
#ਜਾਂਜੇ HAVE_MMX_EXTERNAL
ਖਾਲੀ ff_emms_asm(ਖਾਲੀ);
#   define emms_c ff_emms_asm
#ਜੇ_ਅੰਤ /* HAVE_MMX_INLINE */

#ਜੇ_ਅੰਤ /* ARCH_X86 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ emms_c
#   define emms_c() ਕਰੋ {} ਜਦੋਂ(0)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ff_assert0_fpu
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_assert0_fpu() ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ

#ਜੇ defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_assert1_fpu() ff_assert0_fpu()
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_assert1_fpu() ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_EMMS_H */
