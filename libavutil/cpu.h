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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_CPU_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_CPU_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ "version.h"

#ಆದರೆ FF_API_CPU_FLAG_FORCE
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_FORCE    0x80000000 /* @deprecated, should not be used */
#ಆದರೆ_ಅಂತ್ಯ

    /* lower 16 bits - CPU features */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_MMX          0x0001 ///< standard MMX
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_MMXEXT       0x0002 ///< SSE integer functions or AMD MMX ext
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_MMX2         0x0002 ///< SSE integer functions or AMD MMX ext
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_3DNOW        0x0004 ///< AMD 3DNOW
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE          0x0008 ///< SSE functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE2         0x0010 ///< PIV SSE2 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE2SLOW 0x40000000 ///< SSE2 supported, but usually not faster
                                        ///< than regular MMX/SSE (e.g. Core1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_3DNOWEXT     0x0020 ///< AMD 3DNowExt
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE3         0x0040 ///< Prescott SSE3 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE3SLOW 0x20000000 ///< SSE3 supported, but usually not faster
                                        ///< than regular MMX/SSE (e.g. Core1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSSE3        0x0080 ///< Conroe SSSE3 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSSE3SLOW 0x4000000 ///< SSSE3 supported, but usually not faster
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ATOM     0x10000000 ///< Atom processor, some SSSE3 instructions are slower
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE4         0x0100 ///< Penryn SSE4.1 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SSE42        0x0200 ///< Nehalem SSE4.2 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_AESNI       0x80000 ///< Advanced Encryption Standard functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_CLMUL      0x400000 ///< Carry-less Multiplication instruction
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_AVX          0x4000 ///< AVX functions: requires OS support even if YMM registers aren't used
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_AVXSLOW   0x8000000 ///< AVX supported, but slow when using YMM registers (e.g. Bulldozer)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_XOP          0x0400 ///< Bulldozer XOP functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_FMA4         0x0800 ///< Bulldozer FMA4 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_CMOV         0x1000 ///< supports cmov instruction
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_AVX2         0x8000 ///< AVX2 functions: requires OS support even if YMM registers aren't used
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_FMA3        0x10000 ///< Haswell FMA3 functions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_BMI1        0x20000 ///< Bit Manipulation Instruction Set 1
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_BMI2        0x40000 ///< Bit Manipulation Instruction Set 2
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_AVX512     0x100000 ///< AVX-512 functions: requires OS support even if YMM/ZMM registers aren't used
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_AVX512ICL  0x200000 ///< F/CD/BW/DQ/VL/VNNI/IFMA/VBMI/VBMI2/VPOPCNTDQ/BITALG/GFNI/VAES/VPCLMULQDQ
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SLOW_GATHER  0x2000000 ///< CPU has slow gathers.

#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ALTIVEC      0x0001 ///< standard
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_VSX          0x0002 ///< ISA 2.06
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_POWER8       0x0004 ///< ISA 2.07

#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ARMV5TE      (1 << 0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ARMV6        (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ARMV6T2      (1 << 2)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_VFP          (1 << 3)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_VFPV3        (1 << 4)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_NEON         (1 << 5)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ARMV8        (1 << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_VFP_VM       (1 << 7) ///< VFPv2 vector mode, deprecated in ARMv7-A and unavailable in various CPUs implementations
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_DOTPROD      (1 << 8)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_I8MM         (1 << 9)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SVE          (1 <<10)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SVE2         (1 <<11)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SME          (1 <<12)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ      (1 <<13)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SME2         (1 <<14)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SME_I16I64   (1 <<15)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SETEND       (1 <<16)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_PMULL        (1 <<17)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_EOR3         (1 <<18)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_ARM_AES      (1 <<19)

#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_MMI          (1 << 0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_MSA          (1 << 1)

//Loongarch SIMD extension.
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_LSX          (1 << 0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_LASX         (1 << 1)

// RISC-V extensions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVI          (1 << 0) ///< I (full GPR bank)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVV_I32      (1 << 3) ///< Vectors of 8/16/32-bit int's */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVV_F32      (1 << 4) ///< Vectors of float's */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVV_I64      (1 << 5) ///< Vectors of 64-bit int's */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVV_F64      (1 << 6) ///< Vectors of double's
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVB_BASIC    (1 << 7) ///< Basic bit-manipulations
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RV_ZVBB      (1 << 9) ///< Vector basic bit-manipulations
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RV_MISALIGNED (1 <<10) ///< Fast misaligned accesses
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_RVB          (1 <<11) ///< B (bit manipulations)

// WASM extensions
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CPU_FLAG_SIMD128      (1 << 0)

/**
 * Return the flags which specify extensions supported by the CPU.
 * The returned value is affected by av_force_cpu_flags() if that was used
 * before. So av_get_cpu_flags() can easily be used in an application to
 * detect the enabled cpu flags.
 */
ಪೂರ್ಣಾಂಕ av_get_cpu_flags(ಶೂನ್ಯ);

/**
 * Disables cpu detection and forces the specified flags.
 * -1 is a special case that disables forcing of specific flags.
 */
ಶೂನ್ಯ av_force_cpu_flags(ಪೂರ್ಣಾಂಕ flags);

/**
 * Parse CPU caps from a string and update the given AV_CPU_* flags based on that.
 *
 * @return negative on error.
 */
ಪೂರ್ಣಾಂಕ av_parse_cpu_caps(ಚಿಹ್ನೆರಹಿತ *flags, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s);

/**
 * @return the number of logical CPU cores present.
 */
ಪೂರ್ಣಾಂಕ av_cpu_ಎಣಿಕೆ(ಶೂನ್ಯ);

/**
 * Overrides cpu count detection and forces the specified count.
 * Count < 1 disables forcing of specific count.
 */
ಶೂನ್ಯ av_cpu_force_ಎಣಿಕೆ(ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2);

/**
 * Get the maximum data alignment that may be required by FFmpeg.
 *
 * Note that this is affected by the build configuration and the CPU flags mask,
 * so e.g. if the CPU supports AVX, but libavutil has been built with
 * --disable-avx or the AV_CPU_FLAG_AVX flag has been disabled through
 *  av_set_cpu_flags_mask(), then this function will behave as if AVX is not
 *  present.
 */
size_t av_cpu_max_align(ಶೂನ್ಯ);

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_CPU_H */
