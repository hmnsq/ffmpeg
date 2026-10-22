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

#که_نه_تعریف_شوی AVUTIL_X86_CPU_H
#تعریف_کړه AVUTIL_X86_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کړه X86_MMX(flags)              CPUEXT(flags, MMX)
#تعریف_کړه X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#تعریف_کړه X86_SSE(flags)              CPUEXT(flags, SSE)
#تعریف_کړه X86_SSE2(flags)             CPUEXT(flags, SSE2)
#تعریف_کړه X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#تعریف_کړه X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#تعریف_کړه X86_SSE3(flags)             CPUEXT(flags, SSE3)
#تعریف_کړه X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#تعریف_کړه X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#تعریف_کړه X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#تعریف_کړه X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#تعریف_کړه X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#تعریف_کړه X86_SSE4(flags)             CPUEXT(flags, SSE4)
#تعریف_کړه X86_SSE42(flags)            CPUEXT(flags, SSE42)
#تعریف_کړه X86_AVX(flags)              CPUEXT(flags, AVX)
#تعریف_کړه X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#تعریف_کړه X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#تعریف_کړه X86_XOP(flags)              CPUEXT(flags, XOP)
#تعریف_کړه X86_FMA3(flags)             CPUEXT(flags, FMA3)
#تعریف_کړه X86_FMA4(flags)             CPUEXT(flags, FMA4)
#تعریف_کړه X86_AVX2(flags)             CPUEXT(flags, AVX2)
#تعریف_کړه X86_AESNI(flags)            CPUEXT(flags, AESNI)
#تعریف_کړه X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#تعریف_کړه X86_AVX512(flags)           CPUEXT(flags, AVX512)

#تعریف_کړه EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#تعریف_کړه EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#تعریف_کړه EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#تعریف_کړه EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#تعریف_کړه EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#تعریف_کړه EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#تعریف_کړه EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#تعریف_کړه EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#تعریف_کړه EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#تعریف_کړه EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#تعریف_کړه EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#تعریف_کړه EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#تعریف_کړه EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#تعریف_کړه EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#تعریف_کړه EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#تعریف_کړه EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#تعریف_کړه EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#تعریف_کړه EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#تعریف_کړه EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#تعریف_کړه EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#تعریف_کړه EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#تعریف_کړه EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#تعریف_کړه EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#تعریف_کړه EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#تعریف_کړه EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#تعریف_کړه EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#تعریف_کړه EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#تعریف_کړه EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#تعریف_کړه EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#تعریف_کړه INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#تعریف_کړه INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#تعریف_کړه INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#تعریف_کړه INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#تعریف_کړه INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#تعریف_کړه INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#تعریف_کړه INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#تعریف_کړه INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#تعریف_کړه INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#تعریف_کړه INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#تعریف_کړه INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#تعریف_کړه INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#تعریف_کړه INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#تعریف_کړه INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#تعریف_کړه INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#تعریف_کړه INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#تعریف_کړه INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#تعریف_کړه INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#تعریف_کړه INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#تعریف_کړه INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#تعریف_کړه INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#تعریف_کړه INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

فراغ ff_cpu_cpuid(صحيح شاخص, صحيح *eax, صحيح *ebx, صحيح *ecx, صحيح *edx);
فراغ ff_cpu_xgetbv(صحيح op, صحيح *eax, صحيح *edx);
صحيح  ff_cpu_cpuid_test(فراغ);

#د_که_پای /* AVUTIL_X86_CPU_H */
