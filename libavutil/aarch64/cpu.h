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

#که_نه_تعریف_شوی AVUTIL_AARCH64_CPU_H
#تعریف_کړه AVUTIL_AARCH64_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کړه have_armv8(flags)   CPUEXT(flags, ARMV8)
#تعریف_کړه have_neon(flags)    CPUEXT(flags, NEON)
#تعریف_کړه have_vfp(flags)     CPUEXT(flags, VFP)
#تعریف_کړه have_arm_دوراني_ازموینه(flags) CPUEXT(flags, ARM_دوراني_ازموینه)
#تعریف_کړه have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#تعریف_کړه have_pmull(flags)   CPUEXT(flags, PMULL)
#تعریف_کړه have_eor3(flags)    CPUEXT(flags, EOR3)
#تعریف_کړه have_dotprod(flags) CPUEXT(flags, DOTPROD)
#تعریف_کړه have_i8mm(flags)    CPUEXT(flags, I8MM)
#تعریف_کړه have_sve(flags)     CPUEXT(flags, SVE)
#تعریف_کړه have_sve2(flags)    CPUEXT(flags, SVE2)
#تعریف_کړه have_sme(flags)     CPUEXT(flags, SME)
#تعریف_کړه have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#تعریف_کړه have_sme2(flags)    CPUEXT(flags, SME2)

#إذا HAVE_SVE
صحيح ff_aarch64_sve_اوږدتیا(فراغ);
#د_که_پای

#إذا HAVE_SME
صحيح ff_aarch64_sme_اوږدتیا(فراغ);
#د_که_پای

#د_که_پای /* AVUTIL_AARCH64_CPU_H */
