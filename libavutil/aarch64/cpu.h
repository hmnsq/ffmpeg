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

#यदि_अपरिभाषितम् AVUTIL_AARCH64_CPU_H
#परिभाषय AVUTIL_AARCH64_CPU_H

#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/cpu_internal.h"

#परिभाषय have_armv8(flags)   CPUEXT(flags, ARMV8)
#परिभाषय have_neon(flags)    CPUEXT(flags, NEON)
#परिभाषय have_vfp(flags)     CPUEXT(flags, VFP)
#परिभाषय have_arm_crc(flags) CPUEXT(flags, ARM_CRC)
#परिभाषय have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#परिभाषय have_pmull(flags)   CPUEXT(flags, PMULL)
#परिभाषय have_eor3(flags)    CPUEXT(flags, EOR3)
#परिभाषय have_dotprod(flags) CPUEXT(flags, DOTPROD)
#परिभाषय have_i8mm(flags)    CPUEXT(flags, I8MM)
#परिभाषय have_sve(flags)     CPUEXT(flags, SVE)
#परिभाषय have_sve2(flags)    CPUEXT(flags, SVE2)
#परिभाषय have_sme(flags)     CPUEXT(flags, SME)
#परिभाषय have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#परिभाषय have_sme2(flags)    CPUEXT(flags, SME2)

#यदि HAVE_SVE
पूर्णाङ्क ff_aarch64_sve_दीर्घता(शून्य);
#यदि_अन्तः

#यदि HAVE_SME
पूर्णाङ्क ff_aarch64_sme_दीर्घता(शून्य);
#यदि_अन्तः

#यदि_अन्तः /* AVUTIL_AARCH64_CPU_H */
