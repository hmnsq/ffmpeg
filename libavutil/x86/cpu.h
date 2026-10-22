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

#अगर_अघोषित AVUTIL_X86_CPU_H
#घोषणा AVUTIL_X86_CPU_H

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"

#घोषणा X86_MMX(flags)              CPUEXT(flags, MMX)
#घोषणा X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#घोषणा X86_SSE(flags)              CPUEXT(flags, SSE)
#घोषणा X86_SSE2(flags)             CPUEXT(flags, SSE2)
#घोषणा X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#घोषणा X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#घोषणा X86_SSE3(flags)             CPUEXT(flags, SSE3)
#घोषणा X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#घोषणा X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#घोषणा X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#घोषणा X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#घोषणा X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#घोषणा X86_SSE4(flags)             CPUEXT(flags, SSE4)
#घोषणा X86_SSE42(flags)            CPUEXT(flags, SSE42)
#घोषणा X86_AVX(flags)              CPUEXT(flags, AVX)
#घोषणा X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#घोषणा X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#घोषणा X86_XOP(flags)              CPUEXT(flags, XOP)
#घोषणा X86_FMA3(flags)             CPUEXT(flags, FMA3)
#घोषणा X86_FMA4(flags)             CPUEXT(flags, FMA4)
#घोषणा X86_AVX2(flags)             CPUEXT(flags, AVX2)
#घोषणा X86_AESNI(flags)            CPUEXT(flags, AESNI)
#घोषणा X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#घोषणा X86_AVX512(flags)           CPUEXT(flags, AVX512)

#घोषणा EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#घोषणा EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#घोषणा EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#घोषणा EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#घोषणा EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#घोषणा EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#घोषणा EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#घोषणा EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#घोषणा EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#घोषणा EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#घोषणा EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#घोषणा EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#घोषणा EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#घोषणा EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#घोषणा EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#घोषणा EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#घोषणा EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#घोषणा EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#घोषणा EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#घोषणा EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#घोषणा EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#घोषणा EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#घोषणा EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#घोषणा EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#घोषणा EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#घोषणा EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#घोषणा EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#घोषणा EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#घोषणा EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#घोषणा INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#घोषणा INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#घोषणा INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#घोषणा INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#घोषणा INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#घोषणा INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#घोषणा INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#घोषणा INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#घोषणा INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#घोषणा INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#घोषणा INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#घोषणा INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#घोषणा INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#घोषणा INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#घोषणा INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#घोषणा INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#घोषणा INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#घोषणा INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#घोषणा INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#घोषणा INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#घोषणा INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#घोषणा INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

व्योम ff_cpu_cpuid(पूर्णांक सूचकांक, पूर्णांक *eax, पूर्णांक *ebx, पूर्णांक *ecx, पूर्णांक *edx);
व्योम ff_cpu_xgetbv(पूर्णांक op, पूर्णांक *eax, पूर्णांक *edx);
पूर्णांक  ff_cpu_cpuid_test(व्योम);

#पूर्ण_अगर /* AVUTIL_X86_CPU_H */
