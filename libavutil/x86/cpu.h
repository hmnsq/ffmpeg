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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_CPU_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_CPU_H

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"

#ವ್ಯಾಖ್ಯಾನಿಸು X86_MMX(flags)              CPUEXT(flags, MMX)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE(flags)              CPUEXT(flags, SSE)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE2(flags)             CPUEXT(flags, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE3(flags)             CPUEXT(flags, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE4(flags)             CPUEXT(flags, SSE4)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_SSE42(flags)            CPUEXT(flags, SSE42)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_AVX(flags)              CPUEXT(flags, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_XOP(flags)              CPUEXT(flags, XOP)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_FMA3(flags)             CPUEXT(flags, FMA3)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_FMA4(flags)             CPUEXT(flags, FMA4)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_AVX2(flags)             CPUEXT(flags, AVX2)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_AESNI(flags)            CPUEXT(flags, AESNI)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#ವ್ಯಾಖ್ಯಾನಿಸು X86_AVX512(flags)           CPUEXT(flags, AVX512)

#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#ವ್ಯಾಖ್ಯಾನಿಸು EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#ವ್ಯಾಖ್ಯಾನಿಸು INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

ಶೂನ್ಯ ff_cpu_cpuid(ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ, ಪೂರ್ಣಾಂಕ *eax, ಪೂರ್ಣಾಂಕ *ebx, ಪೂರ್ಣಾಂಕ *ecx, ಪೂರ್ಣಾಂಕ *edx);
ಶೂನ್ಯ ff_cpu_xgetbv(ಪೂರ್ಣಾಂಕ op, ಪೂರ್ಣಾಂಕ *eax, ಪೂರ್ಣಾಂಕ *edx);
ಪೂರ್ಣಾಂಕ  ff_cpu_cpuid_test(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_CPU_H */
