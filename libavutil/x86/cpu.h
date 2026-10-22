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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_X86_CPU_H
#وصف_ڪريو AVUTIL_X86_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#وصف_ڪريو X86_MMX(flags)              CPUEXT(flags, MMX)
#وصف_ڪريو X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#وصف_ڪريو X86_SSE(flags)              CPUEXT(flags, SSE)
#وصف_ڪريو X86_SSE2(flags)             CPUEXT(flags, SSE2)
#وصف_ڪريو X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#وصف_ڪريو X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#وصف_ڪريو X86_SSE3(flags)             CPUEXT(flags, SSE3)
#وصف_ڪريو X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#وصف_ڪريو X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#وصف_ڪريو X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#وصف_ڪريو X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#وصف_ڪريو X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#وصف_ڪريو X86_SSE4(flags)             CPUEXT(flags, SSE4)
#وصف_ڪريو X86_SSE42(flags)            CPUEXT(flags, SSE42)
#وصف_ڪريو X86_AVX(flags)              CPUEXT(flags, AVX)
#وصف_ڪريو X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#وصف_ڪريو X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#وصف_ڪريو X86_XOP(flags)              CPUEXT(flags, XOP)
#وصف_ڪريو X86_FMA3(flags)             CPUEXT(flags, FMA3)
#وصف_ڪريو X86_FMA4(flags)             CPUEXT(flags, FMA4)
#وصف_ڪريو X86_AVX2(flags)             CPUEXT(flags, AVX2)
#وصف_ڪريو X86_AESNI(flags)            CPUEXT(flags, AESNI)
#وصف_ڪريو X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#وصف_ڪريو X86_AVX512(flags)           CPUEXT(flags, AVX512)

#وصف_ڪريو EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#وصف_ڪريو EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#وصف_ڪريو EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#وصف_ڪريو EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#وصف_ڪريو EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#وصف_ڪريو EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#وصف_ڪريو EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#وصف_ڪريو EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#وصف_ڪريو EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#وصف_ڪريو EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#وصف_ڪريو EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#وصف_ڪريو EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#وصف_ڪريو EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#وصف_ڪريو EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#وصف_ڪريو EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#وصف_ڪريو EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#وصف_ڪريو EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#وصف_ڪريو EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#وصف_ڪريو EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#وصف_ڪريو EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#وصف_ڪريو EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#وصف_ڪريو EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#وصف_ڪريو EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#وصف_ڪريو EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#وصف_ڪريو EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#وصف_ڪريو EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#وصف_ڪريو EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#وصف_ڪريو EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#وصف_ڪريو EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#وصف_ڪريو INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#وصف_ڪريو INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#وصف_ڪريو INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#وصف_ڪريو INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#وصف_ڪريو INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#وصف_ڪريو INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#وصف_ڪريو INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#وصف_ڪريو INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#وصف_ڪريو INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#وصف_ڪريو INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#وصف_ڪريو INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#وصف_ڪريو INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#وصف_ڪريو INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#وصف_ڪريو INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#وصف_ڪريو INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#وصف_ڪريو INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#وصف_ڪريو INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#وصف_ڪريو INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#وصف_ڪريو INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#وصف_ڪريو INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#وصف_ڪريو INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#وصف_ڪريو INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

فراغ ff_cpu_cpuid(صحيح اشاريو, صحيح *eax, صحيح *ebx, صحيح *ecx, صحيح *edx);
فراغ ff_cpu_xgetbv(صحيح op, صحيح *eax, صحيح *edx);
صحيح  ff_cpu_cpuid_test(فراغ);

#جيڪڏهن_پورو /* AVUTIL_X86_CPU_H */
