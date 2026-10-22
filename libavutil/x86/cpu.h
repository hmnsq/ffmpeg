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

#यदि_अपरिभाषितम् AVUTIL_X86_CPU_H
#परिभाषय AVUTIL_X86_CPU_H

#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/cpu_internal.h"

#परिभाषय X86_MMX(flags)              CPUEXT(flags, MMX)
#परिभाषय X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#परिभाषय X86_SSE(flags)              CPUEXT(flags, SSE)
#परिभाषय X86_SSE2(flags)             CPUEXT(flags, SSE2)
#परिभाषय X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#परिभाषय X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#परिभाषय X86_SSE3(flags)             CPUEXT(flags, SSE3)
#परिभाषय X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#परिभाषय X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#परिभाषय X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#परिभाषय X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#परिभाषय X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#परिभाषय X86_SSE4(flags)             CPUEXT(flags, SSE4)
#परिभाषय X86_SSE42(flags)            CPUEXT(flags, SSE42)
#परिभाषय X86_AVX(flags)              CPUEXT(flags, AVX)
#परिभाषय X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#परिभाषय X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#परिभाषय X86_XOP(flags)              CPUEXT(flags, XOP)
#परिभाषय X86_FMA3(flags)             CPUEXT(flags, FMA3)
#परिभाषय X86_FMA4(flags)             CPUEXT(flags, FMA4)
#परिभाषय X86_AVX2(flags)             CPUEXT(flags, AVX2)
#परिभाषय X86_AESNI(flags)            CPUEXT(flags, AESNI)
#परिभाषय X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#परिभाषय X86_AVX512(flags)           CPUEXT(flags, AVX512)

#परिभाषय EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#परिभाषय EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#परिभाषय EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#परिभाषय EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#परिभाषय EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#परिभाषय EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#परिभाषय EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#परिभाषय EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#परिभाषय EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#परिभाषय EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#परिभाषय EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#परिभाषय EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#परिभाषय EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#परिभाषय EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#परिभाषय EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#परिभाषय EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#परिभाषय EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#परिभाषय EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#परिभाषय EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#परिभाषय EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#परिभाषय EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#परिभाषय EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#परिभाषय EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#परिभाषय EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#परिभाषय EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#परिभाषय EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#परिभाषय EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#परिभाषय EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#परिभाषय EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#परिभाषय INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#परिभाषय INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#परिभाषय INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#परिभाषय INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#परिभाषय INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#परिभाषय INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#परिभाषय INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#परिभाषय INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#परिभाषय INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#परिभाषय INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#परिभाषय INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#परिभाषय INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#परिभाषय INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#परिभाषय INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#परिभाषय INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#परिभाषय INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#परिभाषय INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#परिभाषय INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#परिभाषय INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#परिभाषय INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#परिभाषय INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#परिभाषय INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

शून्य ff_cpu_cpuid(पूर्णाङ्क सूचकांक, पूर्णाङ्क *eax, पूर्णाङ्क *ebx, पूर्णाङ्क *ecx, पूर्णाङ्क *edx);
शून्य ff_cpu_xgetbv(पूर्णाङ्क op, पूर्णाङ्क *eax, पूर्णाङ्क *edx);
पूर्णाङ्क  ff_cpu_cpuid_test(शून्य);

#यदि_अन्तः /* AVUTIL_X86_CPU_H */
