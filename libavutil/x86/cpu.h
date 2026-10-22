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

#నిర్వచితం_కాకపోతే AVUTIL_X86_CPU_H
#నిర్వచించు AVUTIL_X86_CPU_H

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"

#నిర్వచించు X86_MMX(flags)              CPUEXT(flags, MMX)
#నిర్వచించు X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#నిర్వచించు X86_SSE(flags)              CPUEXT(flags, SSE)
#నిర్వచించు X86_SSE2(flags)             CPUEXT(flags, SSE2)
#నిర్వచించు X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#నిర్వచించు X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#నిర్వచించు X86_SSE3(flags)             CPUEXT(flags, SSE3)
#నిర్వచించు X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#నిర్వచించు X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#నిర్వచించు X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#నిర్వచించు X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#నిర్వచించు X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#నిర్వచించు X86_SSE4(flags)             CPUEXT(flags, SSE4)
#నిర్వచించు X86_SSE42(flags)            CPUEXT(flags, SSE42)
#నిర్వచించు X86_AVX(flags)              CPUEXT(flags, AVX)
#నిర్వచించు X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#నిర్వచించు X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#నిర్వచించు X86_XOP(flags)              CPUEXT(flags, XOP)
#నిర్వచించు X86_FMA3(flags)             CPUEXT(flags, FMA3)
#నిర్వచించు X86_FMA4(flags)             CPUEXT(flags, FMA4)
#నిర్వచించు X86_AVX2(flags)             CPUEXT(flags, AVX2)
#నిర్వచించు X86_AESNI(flags)            CPUEXT(flags, AESNI)
#నిర్వచించు X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#నిర్వచించు X86_AVX512(flags)           CPUEXT(flags, AVX512)

#నిర్వచించు EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#నిర్వచించు EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#నిర్వచించు EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#నిర్వచించు EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#నిర్వచించు EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#నిర్వచించు EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#నిర్వచించు EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#నిర్వచించు EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#నిర్వచించు EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#నిర్వచించు EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#నిర్వచించు EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#నిర్వచించు EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#నిర్వచించు EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#నిర్వచించు EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#నిర్వచించు EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#నిర్వచించు EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#నిర్వచించు EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#నిర్వచించు EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#నిర్వచించు EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#నిర్వచించు EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#నిర్వచించు EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#నిర్వచించు EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#నిర్వచించు EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#నిర్వచించు EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#నిర్వచించు EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#నిర్వచించు EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#నిర్వచించు EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#నిర్వచించు EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#నిర్వచించు EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#నిర్వచించు INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#నిర్వచించు INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#నిర్వచించు INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#నిర్వచించు INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#నిర్వచించు INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#నిర్వచించు INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#నిర్వచించు INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#నిర్వచించు INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#నిర్వచించు INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#నిర్వచించు INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#నిర్వచించు INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#నిర్వచించు INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#నిర్వచించు INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#నిర్వచించు INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#నిర్వచించు INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#నిర్వచించు INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#నిర్వచించు INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#నిర్వచించు INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#నిర్వచించు INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#నిర్వచించు INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#నిర్వచించు INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#నిర్వచించు INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

శూన్య ff_cpu_cpuid(పూర్ణాంకం సూచీ, పూర్ణాంకం *eax, పూర్ణాంకం *ebx, పూర్ణాంకం *ecx, పూర్ణాంకం *edx);
శూన్య ff_cpu_xgetbv(పూర్ణాంకం op, పూర్ణాంకం *eax, పూర్ణాంకం *edx);
పూర్ణాంకం  ff_cpu_cpuid_test(శూన్య);

#అయితే_ముగింపు /* AVUTIL_X86_CPU_H */
