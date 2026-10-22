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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_AARCH64_CPU_H
#وصف_ڪريو AVUTIL_AARCH64_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#وصف_ڪريو have_armv8(flags)   CPUEXT(flags, ARMV8)
#وصف_ڪريو have_neon(flags)    CPUEXT(flags, NEON)
#وصف_ڪريو have_vfp(flags)     CPUEXT(flags, VFP)
#وصف_ڪريو have_arm_چڪري_جاچ(flags) CPUEXT(flags, ARM_چڪري_جاچ)
#وصف_ڪريو have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#وصف_ڪريو have_pmull(flags)   CPUEXT(flags, PMULL)
#وصف_ڪريو have_eor3(flags)    CPUEXT(flags, EOR3)
#وصف_ڪريو have_dotprod(flags) CPUEXT(flags, DOTPROD)
#وصف_ڪريو have_i8mm(flags)    CPUEXT(flags, I8MM)
#وصف_ڪريو have_sve(flags)     CPUEXT(flags, SVE)
#وصف_ڪريو have_sve2(flags)    CPUEXT(flags, SVE2)
#وصف_ڪريو have_sme(flags)     CPUEXT(flags, SME)
#وصف_ڪريو have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#وصف_ڪريو have_sme2(flags)    CPUEXT(flags, SME2)

#إذا HAVE_SVE
صحيح ff_aarch64_sve_ڊيگهائي(فراغ);
#جيڪڏهن_پورو

#إذا HAVE_SME
صحيح ff_aarch64_sme_ڊيگهائي(فراغ);
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* AVUTIL_AARCH64_CPU_H */
