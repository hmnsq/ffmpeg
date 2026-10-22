/*
 * Copyright (c) 2000, 2001, 2002 Fabrice Bellard
 *
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

#నిర్వచితం_కాకపోతే AVUTIL_CPU_H
#నిర్వచించు AVUTIL_CPU_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ "version.h"

#ఒకవేళ FF_API_CPU_FLAG_FORCE
#నిర్వచించు AV_CPU_FLAG_FORCE    0x80000000 /* @deprecated, should not be used */
#అయితే_ముగింపు

    /* lower 16 bits - CPU features */
#నిర్వచించు AV_CPU_FLAG_MMX          0x0001 ///< standard MMX
#నిర్వచించు AV_CPU_FLAG_MMXEXT       0x0002 ///< SSE integer functions or AMD MMX ext
#నిర్వచించు AV_CPU_FLAG_MMX2         0x0002 ///< SSE integer functions or AMD MMX ext
#నిర్వచించు AV_CPU_FLAG_3DNOW        0x0004 ///< AMD 3DNOW
#నిర్వచించు AV_CPU_FLAG_SSE          0x0008 ///< SSE functions
#నిర్వచించు AV_CPU_FLAG_SSE2         0x0010 ///< PIV SSE2 functions
#నిర్వచించు AV_CPU_FLAG_SSE2SLOW 0x40000000 ///< SSE2 supported, but usually not faster
                                        ///< than regular MMX/SSE (e.g. Core1)
#నిర్వచించు AV_CPU_FLAG_3DNOWEXT     0x0020 ///< AMD 3DNowExt
#నిర్వచించు AV_CPU_FLAG_SSE3         0x0040 ///< Prescott SSE3 functions
#నిర్వచించు AV_CPU_FLAG_SSE3SLOW 0x20000000 ///< SSE3 supported, but usually not faster
                                        ///< than regular MMX/SSE (e.g. Core1)
#నిర్వచించు AV_CPU_FLAG_SSSE3        0x0080 ///< Conroe SSSE3 functions
#నిర్వచించు AV_CPU_FLAG_SSSE3SLOW 0x4000000 ///< SSSE3 supported, but usually not faster
#నిర్వచించు AV_CPU_FLAG_ATOM     0x10000000 ///< Atom processor, some SSSE3 instructions are slower
#నిర్వచించు AV_CPU_FLAG_SSE4         0x0100 ///< Penryn SSE4.1 functions
#నిర్వచించు AV_CPU_FLAG_SSE42        0x0200 ///< Nehalem SSE4.2 functions
#నిర్వచించు AV_CPU_FLAG_AESNI       0x80000 ///< Advanced Encryption Standard functions
#నిర్వచించు AV_CPU_FLAG_CLMUL      0x400000 ///< Carry-less Multiplication instruction
#నిర్వచించు AV_CPU_FLAG_AVX          0x4000 ///< AVX functions: requires OS support even if YMM registers aren't used
#నిర్వచించు AV_CPU_FLAG_AVXSLOW   0x8000000 ///< AVX supported, but slow when using YMM registers (e.g. Bulldozer)
#నిర్వచించు AV_CPU_FLAG_XOP          0x0400 ///< Bulldozer XOP functions
#నిర్వచించు AV_CPU_FLAG_FMA4         0x0800 ///< Bulldozer FMA4 functions
#నిర్వచించు AV_CPU_FLAG_CMOV         0x1000 ///< supports cmov instruction
#నిర్వచించు AV_CPU_FLAG_AVX2         0x8000 ///< AVX2 functions: requires OS support even if YMM registers aren't used
#నిర్వచించు AV_CPU_FLAG_FMA3        0x10000 ///< Haswell FMA3 functions
#నిర్వచించు AV_CPU_FLAG_BMI1        0x20000 ///< Bit Manipulation Instruction Set 1
#నిర్వచించు AV_CPU_FLAG_BMI2        0x40000 ///< Bit Manipulation Instruction Set 2
#నిర్వచించు AV_CPU_FLAG_AVX512     0x100000 ///< AVX-512 functions: requires OS support even if YMM/ZMM registers aren't used
#నిర్వచించు AV_CPU_FLAG_AVX512ICL  0x200000 ///< F/CD/BW/DQ/VL/VNNI/IFMA/VBMI/VBMI2/VPOPCNTDQ/BITALG/GFNI/VAES/VPCLMULQDQ
#నిర్వచించు AV_CPU_FLAG_SLOW_GATHER  0x2000000 ///< CPU has slow gathers.

#నిర్వచించు AV_CPU_FLAG_ALTIVEC      0x0001 ///< standard
#నిర్వచించు AV_CPU_FLAG_VSX          0x0002 ///< ISA 2.06
#నిర్వచించు AV_CPU_FLAG_POWER8       0x0004 ///< ISA 2.07

#నిర్వచించు AV_CPU_FLAG_ARMV5TE      (1 << 0)
#నిర్వచించు AV_CPU_FLAG_ARMV6        (1 << 1)
#నిర్వచించు AV_CPU_FLAG_ARMV6T2      (1 << 2)
#నిర్వచించు AV_CPU_FLAG_VFP          (1 << 3)
#నిర్వచించు AV_CPU_FLAG_VFPV3        (1 << 4)
#నిర్వచించు AV_CPU_FLAG_NEON         (1 << 5)
#నిర్వచించు AV_CPU_FLAG_ARMV8        (1 << 6)
#నిర్వచించు AV_CPU_FLAG_VFP_VM       (1 << 7) ///< VFPv2 vector mode, deprecated in ARMv7-A and unavailable in various CPUs implementations
#నిర్వచించు AV_CPU_FLAG_DOTPROD      (1 << 8)
#నిర్వచించు AV_CPU_FLAG_I8MM         (1 << 9)
#నిర్వచించు AV_CPU_FLAG_SVE          (1 <<10)
#నిర్వచించు AV_CPU_FLAG_SVE2         (1 <<11)
#నిర్వచించు AV_CPU_FLAG_SME          (1 <<12)
#నిర్వచించు AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ      (1 <<13)
#నిర్వచించు AV_CPU_FLAG_SME2         (1 <<14)
#నిర్వచించు AV_CPU_FLAG_SME_I16I64   (1 <<15)
#నిర్వచించు AV_CPU_FLAG_SETEND       (1 <<16)
#నిర్వచించు AV_CPU_FLAG_PMULL        (1 <<17)
#నిర్వచించు AV_CPU_FLAG_EOR3         (1 <<18)
#నిర్వచించు AV_CPU_FLAG_ARM_AES      (1 <<19)

#నిర్వచించు AV_CPU_FLAG_MMI          (1 << 0)
#నిర్వచించు AV_CPU_FLAG_MSA          (1 << 1)

//Loongarch SIMD extension.
#నిర్వచించు AV_CPU_FLAG_LSX          (1 << 0)
#నిర్వచించు AV_CPU_FLAG_LASX         (1 << 1)

// RISC-V extensions
#నిర్వచించు AV_CPU_FLAG_RVI          (1 << 0) ///< I (full GPR bank)
#నిర్వచించు AV_CPU_FLAG_RVV_I32      (1 << 3) ///< Vectors of 8/16/32-bit int's */
#నిర్వచించు AV_CPU_FLAG_RVV_F32      (1 << 4) ///< Vectors of float's */
#నిర్వచించు AV_CPU_FLAG_RVV_I64      (1 << 5) ///< Vectors of 64-bit int's */
#నిర్వచించు AV_CPU_FLAG_RVV_F64      (1 << 6) ///< Vectors of double's
#నిర్వచించు AV_CPU_FLAG_RVB_BASIC    (1 << 7) ///< Basic bit-manipulations
#నిర్వచించు AV_CPU_FLAG_RV_ZVBB      (1 << 9) ///< Vector basic bit-manipulations
#నిర్వచించు AV_CPU_FLAG_RV_MISALIGNED (1 <<10) ///< Fast misaligned accesses
#నిర్వచించు AV_CPU_FLAG_RVB          (1 <<11) ///< B (bit manipulations)

// WASM extensions
#నిర్వచించు AV_CPU_FLAG_SIMD128      (1 << 0)

/**
 * Return the flags which specify extensions supported by the CPU.
 * The returned value is affected by av_force_cpu_flags() if that was used
 * before. So av_get_cpu_flags() can easily be used in an application to
 * detect the enabled cpu flags.
 */
పూర్ణాంకం av_get_cpu_flags(శూన్య);

/**
 * Disables cpu detection and forces the specified flags.
 * -1 is a special case that disables forcing of specific flags.
 */
శూన్య av_force_cpu_flags(పూర్ణాంకం flags);

/**
 * Parse CPU caps from a string and update the given AV_CPU_* flags based on that.
 *
 * @return negative on error.
 */
పూర్ణాంకం av_parse_cpu_caps(గుర్తులేని *flags, స్థిరరాశి అక్షరం *s);

/**
 * @return the number of logical CPU cores present.
 */
పూర్ణాంకం av_cpu_లెక్క(శూన్య);

/**
 * Overrides cpu count detection and forces the specified count.
 * Count < 1 disables forcing of specific count.
 */
శూన్య av_cpu_force_లెక్క(పూర్ణాంకం లెక్క);

/**
 * Get the maximum data alignment that may be required by FFmpeg.
 *
 * Note that this is affected by the build configuration and the CPU flags mask,
 * so e.g. if the CPU supports AVX, but libavutil has been built with
 * --disable-avx or the AV_CPU_FLAG_AVX flag has been disabled through
 *  av_set_cpu_flags_mask(), then this function will behave as if AVX is not
 *  present.
 */
size_t av_cpu_max_align(శూన్య);

#అయితే_ముగింపు /* AVUTIL_CPU_H */
