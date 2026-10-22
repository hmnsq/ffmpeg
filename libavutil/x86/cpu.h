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

#اگر_تعریف_نشده AVUTIL_X86_CPU_H
#تعریف_کن AVUTIL_X86_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کن X86_MMX(flags)              CPUEXT(flags, MMX)
#تعریف_کن X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#تعریف_کن X86_SSE(flags)              CPUEXT(flags, SSE)
#تعریف_کن X86_SSE2(flags)             CPUEXT(flags, SSE2)
#تعریف_کن X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#تعریف_کن X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#تعریف_کن X86_SSE3(flags)             CPUEXT(flags, SSE3)
#تعریف_کن X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#تعریف_کن X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#تعریف_کن X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#تعریف_کن X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#تعریف_کن X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#تعریف_کن X86_SSE4(flags)             CPUEXT(flags, SSE4)
#تعریف_کن X86_SSE42(flags)            CPUEXT(flags, SSE42)
#تعریف_کن X86_AVX(flags)              CPUEXT(flags, AVX)
#تعریف_کن X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#تعریف_کن X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#تعریف_کن X86_XOP(flags)              CPUEXT(flags, XOP)
#تعریف_کن X86_FMA3(flags)             CPUEXT(flags, FMA3)
#تعریف_کن X86_FMA4(flags)             CPUEXT(flags, FMA4)
#تعریف_کن X86_AVX2(flags)             CPUEXT(flags, AVX2)
#تعریف_کن X86_AESNI(flags)            CPUEXT(flags, AESNI)
#تعریف_کن X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#تعریف_کن X86_AVX512(flags)           CPUEXT(flags, AVX512)

#تعریف_کن EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#تعریف_کن EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#تعریف_کن EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#تعریف_کن EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#تعریف_کن EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#تعریف_کن EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#تعریف_کن EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#تعریف_کن EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#تعریف_کن EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#تعریف_کن EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#تعریف_کن EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#تعریف_کن EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#تعریف_کن EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#تعریف_کن EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#تعریف_کن EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#تعریف_کن EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#تعریف_کن EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#تعریف_کن EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#تعریف_کن EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#تعریف_کن EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#تعریف_کن EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#تعریف_کن EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#تعریف_کن EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#تعریف_کن EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#تعریف_کن EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#تعریف_کن EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#تعریف_کن EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#تعریف_کن EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#تعریف_کن EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#تعریف_کن INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#تعریف_کن INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#تعریف_کن INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#تعریف_کن INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#تعریف_کن INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#تعریف_کن INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#تعریف_کن INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#تعریف_کن INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#تعریف_کن INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#تعریف_کن INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#تعریف_کن INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#تعریف_کن INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#تعریف_کن INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#تعریف_کن INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#تعریف_کن INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#تعریف_کن INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#تعریف_کن INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#تعریف_کن INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#تعریف_کن INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#تعریف_کن INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#تعریف_کن INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#تعریف_کن INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

فراغ ff_cpu_cpuid(صحيح شاخص, صحيح *eax, صحيح *ebx, صحيح *ecx, صحيح *edx);
فراغ ff_cpu_xgetbv(صحيح op, صحيح *eax, صحيح *edx);
صحيح  ff_cpu_cpuid_test(فراغ);

#پایان_اگر /* AVUTIL_X86_CPU_H */
