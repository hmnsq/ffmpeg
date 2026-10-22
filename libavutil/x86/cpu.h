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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_CPU_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_CPU_H

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_MMX(flags)              CPUEXT(flags, MMX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_MMXEXT(flags)           CPUEXT(flags, MMXEXT)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE(flags)              CPUEXT(flags, SSE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE2(flags)             CPUEXT(flags, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE2_FAST(flags)        CPUEXT_FAST(flags, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE2_SLOW(flags)        CPUEXT_SLOW(flags, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE3(flags)             CPUEXT(flags, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE3_FAST(flags)        CPUEXT_FAST(flags, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE3_SLOW(flags)        CPUEXT_SLOW(flags, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSSE3(flags)            CPUEXT(flags, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSSE3_FAST(flags)       CPUEXT_FAST(flags, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSSE3_SLOW(flags)       CPUEXT_SLOW(flags, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE4(flags)             CPUEXT(flags, SSE4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_SSE42(flags)            CPUEXT(flags, SSE42)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_AVX(flags)              CPUEXT(flags, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_AVX_FAST(flags)         CPUEXT_FAST(flags, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_AVX_SLOW(flags)         CPUEXT_SLOW(flags, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_XOP(flags)              CPUEXT(flags, XOP)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_FMA3(flags)             CPUEXT(flags, FMA3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_FMA4(flags)             CPUEXT(flags, FMA4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_AVX2(flags)             CPUEXT(flags, AVX2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_AESNI(flags)            CPUEXT(flags, AESNI)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_CLMUL(flags)            CPUEXT(flags, CLMUL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ X86_AVX512(flags)           CPUEXT(flags, AVX512)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_MMX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, MMX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_MMXEXT(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, MMXEXT)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, SSE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE2_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE2_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE3_FAST(flags)   CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE3_SLOW(flags)   CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSSE3(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSSE3_FAST(flags)  CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSSE3_SLOW(flags)  CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, SSE4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_SSE42(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, SSE42)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _EXTERNAL, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _EXTERNAL, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_XOP(flags)         CPUEXT_SUFFIX(flags, _EXTERNAL, XOP)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_FMA3(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_FMA3_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, FMA3, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_FMA3_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, FMA3, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_FMA4(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, FMA4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX2(flags)        CPUEXT_SUFFIX(flags, _EXTERNAL, AVX2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX2_FAST(flags)   CPUEXT_SUFFIX_FAST2(flags, _EXTERNAL, AVX2, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX2_SLOW(flags)   CPUEXT_SUFFIX_SLOW2(flags, _EXTERNAL, AVX2, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AESNI(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, AESNI)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_CLMUL(flags)       CPUEXT_SUFFIX(flags, _EXTERNAL, CLMUL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX512(flags)      CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ EXTERNAL_AVX512ICL(flags)   CPUEXT_SUFFIX(flags, _EXTERNAL, AVX512ICL)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_MMX(flags)           CPUEXT_SUFFIX(flags, _INLINE, MMX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_MMXEXT(flags)        CPUEXT_SUFFIX(flags, _INLINE, MMXEXT)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE(flags)           CPUEXT_SUFFIX(flags, _INLINE, SSE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE2(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE2_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE2_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE3(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE3_FAST(flags)     CPUEXT_SUFFIX_FAST(flags, _INLINE, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE3_SLOW(flags)     CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSSE3(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSSE3_FAST(flags)    CPUEXT_SUFFIX_FAST(flags, _INLINE, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSSE3_SLOW(flags)    CPUEXT_SUFFIX_SLOW(flags, _INLINE, SSSE3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE4(flags)          CPUEXT_SUFFIX(flags, _INLINE, SSE4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_SSE42(flags)         CPUEXT_SUFFIX(flags, _INLINE, SSE42)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_AVX(flags)           CPUEXT_SUFFIX(flags, _INLINE, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_AVX_FAST(flags)      CPUEXT_SUFFIX_FAST(flags, _INLINE, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_AVX_SLOW(flags)      CPUEXT_SUFFIX_SLOW(flags, _INLINE, AVX)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_XOP(flags)           CPUEXT_SUFFIX(flags, _INLINE, XOP)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_FMA3(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_FMA4(flags)          CPUEXT_SUFFIX(flags, _INLINE, FMA4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_AVX2(flags)          CPUEXT_SUFFIX(flags, _INLINE, AVX2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INLINE_AESNI(flags)         CPUEXT_SUFFIX(flags, _INLINE, AESNI)

ਖਾਲੀ ff_cpu_cpuid(ਪੂਰਨ ਸੂਚਕਾਂਕ, ਪੂਰਨ *eax, ਪੂਰਨ *ebx, ਪੂਰਨ *ecx, ਪੂਰਨ *edx);
ਖਾਲੀ ff_cpu_xgetbv(ਪੂਰਨ op, ਪੂਰਨ *eax, ਪੂਰਨ *edx);
ਪੂਰਨ  ff_cpu_cpuid_test(ਖਾਲੀ);

#ਜੇ_ਅੰਤ /* AVUTIL_X86_CPU_H */
