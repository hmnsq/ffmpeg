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

#నిర్వచితం_కాకపోతే AVUTIL_AARCH64_CPU_H
#నిర్వచించు AVUTIL_AARCH64_CPU_H

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"

#నిర్వచించు have_armv8(flags)   CPUEXT(flags, ARMV8)
#నిర్వచించు have_neon(flags)    CPUEXT(flags, NEON)
#నిర్వచించు have_vfp(flags)     CPUEXT(flags, VFP)
#నిర్వచించు have_arm_చక్రీయ_తనిఖీ(flags) CPUEXT(flags, ARM_చక్రీయ_తనిఖీ)
#నిర్వచించు have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#నిర్వచించు have_pmull(flags)   CPUEXT(flags, PMULL)
#నిర్వచించు have_eor3(flags)    CPUEXT(flags, EOR3)
#నిర్వచించు have_dotprod(flags) CPUEXT(flags, DOTPROD)
#నిర్వచించు have_i8mm(flags)    CPUEXT(flags, I8MM)
#నిర్వచించు have_sve(flags)     CPUEXT(flags, SVE)
#నిర్వచించు have_sve2(flags)    CPUEXT(flags, SVE2)
#నిర్వచించు have_sme(flags)     CPUEXT(flags, SME)
#నిర్వచించు have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#నిర్వచించు have_sme2(flags)    CPUEXT(flags, SME2)

#ఒకవేళ HAVE_SVE
పూర్ణాంకం ff_aarch64_sve_నిడివి(శూన్య);
#అయితే_ముగింపు

#ఒకవేళ HAVE_SME
పూర్ణాంకం ff_aarch64_sme_నిడివి(శూన్య);
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_AARCH64_CPU_H */
