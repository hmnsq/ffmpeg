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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_CPU_H
#وصف_ڪريو AVUTIL_CPU_H

#ضمن <stddef.h>
#ضمن "version.h"

#إذا FF_API_CPU_FLAG_FORCE
#وصف_ڪريو AV_CPU_FLAG_FORCE    0x80000000 /* @deprecated, should not be used */
#جيڪڏهن_پورو

    /* lower 16 bits - CPU features */
#وصف_ڪريو AV_CPU_FLAG_MMX          0x0001 ///< standard MMX
#وصف_ڪريو AV_CPU_FLAG_MMXEXT       0x0002 ///< SSE integer functions or AMD MMX ext
#وصف_ڪريو AV_CPU_FLAG_MMX2         0x0002 ///< SSE integer functions or AMD MMX ext
#وصف_ڪريو AV_CPU_FLAG_3DNOW        0x0004 ///< AMD 3DNOW
#وصف_ڪريو AV_CPU_FLAG_SSE          0x0008 ///< SSE functions
#وصف_ڪريو AV_CPU_FLAG_SSE2         0x0010 ///< PIV SSE2 functions
#وصف_ڪريو AV_CPU_FLAG_SSE2SLOW 0x40000000 ///< SSE2 supported, but usually not faster
                                        ///< than regular MMX/SSE (e.g. Core1)
#وصف_ڪريو AV_CPU_FLAG_3DNOWEXT     0x0020 ///< AMD 3DNowExt
#وصف_ڪريو AV_CPU_FLAG_SSE3         0x0040 ///< Prescott SSE3 functions
#وصف_ڪريو AV_CPU_FLAG_SSE3SLOW 0x20000000 ///< SSE3 supported, but usually not faster
                                        ///< than regular MMX/SSE (e.g. Core1)
#وصف_ڪريو AV_CPU_FLAG_SSSE3        0x0080 ///< Conroe SSSE3 functions
#وصف_ڪريو AV_CPU_FLAG_SSSE3SLOW 0x4000000 ///< SSSE3 supported, but usually not faster
#وصف_ڪريو AV_CPU_FLAG_ATOM     0x10000000 ///< Atom processor, some SSSE3 instructions are slower
#وصف_ڪريو AV_CPU_FLAG_SSE4         0x0100 ///< Penryn SSE4.1 functions
#وصف_ڪريو AV_CPU_FLAG_SSE42        0x0200 ///< Nehalem SSE4.2 functions
#وصف_ڪريو AV_CPU_FLAG_AESNI       0x80000 ///< Advanced Encryption Standard functions
#وصف_ڪريو AV_CPU_FLAG_CLMUL      0x400000 ///< Carry-less Multiplication instruction
#وصف_ڪريو AV_CPU_FLAG_AVX          0x4000 ///< AVX functions: requires OS support even if YMM registers aren't used
#وصف_ڪريو AV_CPU_FLAG_AVXSLOW   0x8000000 ///< AVX supported, but slow when using YMM registers (e.g. Bulldozer)
#وصف_ڪريو AV_CPU_FLAG_XOP          0x0400 ///< Bulldozer XOP functions
#وصف_ڪريو AV_CPU_FLAG_FMA4         0x0800 ///< Bulldozer FMA4 functions
#وصف_ڪريو AV_CPU_FLAG_CMOV         0x1000 ///< supports cmov instruction
#وصف_ڪريو AV_CPU_FLAG_AVX2         0x8000 ///< AVX2 functions: requires OS support even if YMM registers aren't used
#وصف_ڪريو AV_CPU_FLAG_FMA3        0x10000 ///< Haswell FMA3 functions
#وصف_ڪريو AV_CPU_FLAG_BMI1        0x20000 ///< Bit Manipulation Instruction Set 1
#وصف_ڪريو AV_CPU_FLAG_BMI2        0x40000 ///< Bit Manipulation Instruction Set 2
#وصف_ڪريو AV_CPU_FLAG_AVX512     0x100000 ///< AVX-512 functions: requires OS support even if YMM/ZMM registers aren't used
#وصف_ڪريو AV_CPU_FLAG_AVX512ICL  0x200000 ///< F/CD/BW/DQ/VL/VNNI/IFMA/VBMI/VBMI2/VPOPCNTDQ/BITALG/GFNI/VAES/VPCLMULQDQ
#وصف_ڪريو AV_CPU_FLAG_SLOW_GATHER  0x2000000 ///< CPU has slow gathers.

#وصف_ڪريو AV_CPU_FLAG_ALTIVEC      0x0001 ///< standard
#وصف_ڪريو AV_CPU_FLAG_VSX          0x0002 ///< ISA 2.06
#وصف_ڪريو AV_CPU_FLAG_POWER8       0x0004 ///< ISA 2.07

#وصف_ڪريو AV_CPU_FLAG_ARMV5TE      (1 << 0)
#وصف_ڪريو AV_CPU_FLAG_ARMV6        (1 << 1)
#وصف_ڪريو AV_CPU_FLAG_ARMV6T2      (1 << 2)
#وصف_ڪريو AV_CPU_FLAG_VFP          (1 << 3)
#وصف_ڪريو AV_CPU_FLAG_VFPV3        (1 << 4)
#وصف_ڪريو AV_CPU_FLAG_NEON         (1 << 5)
#وصف_ڪريو AV_CPU_FLAG_ARMV8        (1 << 6)
#وصف_ڪريو AV_CPU_FLAG_VFP_VM       (1 << 7) ///< VFPv2 vector mode, deprecated in ARMv7-A and unavailable in various CPUs implementations
#وصف_ڪريو AV_CPU_FLAG_DOTPROD      (1 << 8)
#وصف_ڪريو AV_CPU_FLAG_I8MM         (1 << 9)
#وصف_ڪريو AV_CPU_FLAG_SVE          (1 <<10)
#وصف_ڪريو AV_CPU_FLAG_SVE2         (1 <<11)
#وصف_ڪريو AV_CPU_FLAG_SME          (1 <<12)
#وصف_ڪريو AV_CPU_FLAG_ARM_چڪري_جاچ      (1 <<13)
#وصف_ڪريو AV_CPU_FLAG_SME2         (1 <<14)
#وصف_ڪريو AV_CPU_FLAG_SME_I16I64   (1 <<15)
#وصف_ڪريو AV_CPU_FLAG_SETEND       (1 <<16)
#وصف_ڪريو AV_CPU_FLAG_PMULL        (1 <<17)
#وصف_ڪريو AV_CPU_FLAG_EOR3         (1 <<18)
#وصف_ڪريو AV_CPU_FLAG_ARM_AES      (1 <<19)

#وصف_ڪريو AV_CPU_FLAG_MMI          (1 << 0)
#وصف_ڪريو AV_CPU_FLAG_MSA          (1 << 1)

//Loongarch SIMD extension.
#وصف_ڪريو AV_CPU_FLAG_LSX          (1 << 0)
#وصف_ڪريو AV_CPU_FLAG_LASX         (1 << 1)

// RISC-V extensions
#وصف_ڪريو AV_CPU_FLAG_RVI          (1 << 0) ///< I (full GPR bank)
#وصف_ڪريو AV_CPU_FLAG_RVV_I32      (1 << 3) ///< Vectors of 8/16/32-bit int's */
#وصف_ڪريو AV_CPU_FLAG_RVV_F32      (1 << 4) ///< Vectors of float's */
#وصف_ڪريو AV_CPU_FLAG_RVV_I64      (1 << 5) ///< Vectors of 64-bit int's */
#وصف_ڪريو AV_CPU_FLAG_RVV_F64      (1 << 6) ///< Vectors of double's
#وصف_ڪريو AV_CPU_FLAG_RVB_BASIC    (1 << 7) ///< Basic bit-manipulations
#وصف_ڪريو AV_CPU_FLAG_RV_ZVBB      (1 << 9) ///< Vector basic bit-manipulations
#وصف_ڪريو AV_CPU_FLAG_RV_MISALIGNED (1 <<10) ///< Fast misaligned accesses
#وصف_ڪريو AV_CPU_FLAG_RVB          (1 <<11) ///< B (bit manipulations)

// WASM extensions
#وصف_ڪريو AV_CPU_FLAG_SIMD128      (1 << 0)

/**
 * Return the flags which specify extensions supported by the CPU.
 * The returned value is affected by av_force_cpu_flags() if that was used
 * before. So av_get_cpu_flags() can easily be used in an application to
 * detect the enabled cpu flags.
 */
صحيح av_get_cpu_flags(فراغ);

/**
 * Disables cpu detection and forces the specified flags.
 * -1 is a special case that disables forcing of specific flags.
 */
فراغ av_force_cpu_flags(صحيح flags);

/**
 * Parse CPU caps from a string and update the given AV_CPU_* flags based on that.
 *
 * @return negative on error.
 */
صحيح av_parse_cpu_caps(بنانشان *flags, ثابت حرف *s);

/**
 * @return the number of logical CPU cores present.
 */
صحيح av_cpu_ڳڻپ(فراغ);

/**
 * Overrides cpu count detection and forces the specified count.
 * Count < 1 disables forcing of specific count.
 */
فراغ av_cpu_force_ڳڻپ(صحيح ڳڻپ);

/**
 * Get the maximum data alignment that may be required by FFmpeg.
 *
 * Note that this is affected by the build configuration and the CPU flags mask,
 * so e.g. if the CPU supports AVX, but libavutil has been built with
 * --disable-avx or the AV_CPU_FLAG_AVX flag has been disabled through
 *  av_set_cpu_flags_mask(), then this function will behave as if AVX is not
 *  present.
 */
size_t av_cpu_max_align(فراغ);

#جيڪڏهن_پورو /* AVUTIL_CPU_H */
