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

#اگر_تعریف_نشده AVUTIL_AARCH64_CPU_H
#تعریف_کن AVUTIL_AARCH64_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کن have_armv8(flags)   CPUEXT(flags, ARMV8)
#تعریف_کن have_neon(flags)    CPUEXT(flags, NEON)
#تعریف_کن have_vfp(flags)     CPUEXT(flags, VFP)
#تعریف_کن have_arm_بررسی_چرخهای(flags) CPUEXT(flags, ARM_بررسی_چرخهای)
#تعریف_کن have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#تعریف_کن have_pmull(flags)   CPUEXT(flags, PMULL)
#تعریف_کن have_eor3(flags)    CPUEXT(flags, EOR3)
#تعریف_کن have_dotprod(flags) CPUEXT(flags, DOTPROD)
#تعریف_کن have_i8mm(flags)    CPUEXT(flags, I8MM)
#تعریف_کن have_sve(flags)     CPUEXT(flags, SVE)
#تعریف_کن have_sve2(flags)    CPUEXT(flags, SVE2)
#تعریف_کن have_sme(flags)     CPUEXT(flags, SME)
#تعریف_کن have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#تعریف_کن have_sme2(flags)    CPUEXT(flags, SME2)

#إذا HAVE_SVE
صحيح ff_aarch64_sve_درازی(فراغ);
#پایان_اگر

#إذا HAVE_SME
صحيح ff_aarch64_sme_درازی(فراغ);
#پایان_اگر

#پایان_اگر /* AVUTIL_AARCH64_CPU_H */
