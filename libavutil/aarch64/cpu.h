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

#اگر_غیر_تعریف_شدہ AVUTIL_AARCH64_CPU_H
#تعریف_کرو AVUTIL_AARCH64_CPU_H

#شامل "libavutil/cpu.h"
#شامل "libavutil/cpu_internal.h"

#تعریف_کرو have_armv8(flags)   CPUEXT(flags, ARMV8)
#تعریف_کرو have_neon(flags)    CPUEXT(flags, NEON)
#تعریف_کرو have_vfp(flags)     CPUEXT(flags, VFP)
#تعریف_کرو have_arm_چکری_جانچ(flags) CPUEXT(flags, ARM_چکری_جانچ)
#تعریف_کرو have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#تعریف_کرو have_pmull(flags)   CPUEXT(flags, PMULL)
#تعریف_کرو have_eor3(flags)    CPUEXT(flags, EOR3)
#تعریف_کرو have_dotprod(flags) CPUEXT(flags, DOTPROD)
#تعریف_کرو have_i8mm(flags)    CPUEXT(flags, I8MM)
#تعریف_کرو have_sve(flags)     CPUEXT(flags, SVE)
#تعریف_کرو have_sve2(flags)    CPUEXT(flags, SVE2)
#تعریف_کرو have_sme(flags)     CPUEXT(flags, SME)
#تعریف_کرو have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#تعریف_کرو have_sme2(flags)    CPUEXT(flags, SME2)

#اگر HAVE_SVE
صحیح ff_aarch64_sve_لمبائی(خالی);
#اگر_ختم

#اگر HAVE_SME
صحیح ff_aarch64_sme_لمبائی(خالی);
#اگر_ختم

#اگر_ختم /* AVUTIL_AARCH64_CPU_H */
