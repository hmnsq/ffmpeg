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

#నిర్వచితం_కాకపోతే AVUTIL_ARM_CPU_H
#నిర్వచించు AVUTIL_ARM_CPU_H

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"

#నిర్వచించు have_armv5te(flags) CPUEXT(flags, ARMV5TE)
#నిర్వచించు have_armv6(flags)   CPUEXT(flags, ARMV6)
#నిర్వచించు have_armv6t2(flags) CPUEXT(flags, ARMV6T2)
#నిర్వచించు have_vfp(flags)     CPUEXT(flags, VFP)
#నిర్వచించు have_vfpv3(flags)   CPUEXT(flags, VFPV3)
#నిర్వచించు have_neon(flags)    CPUEXT(flags, NEON)
#నిర్వచించు have_setend(flags)  CPUEXT(flags, SETEND)

/* some functions use the VFPv2 vector mode which is deprecated in ARMv7-A
 * and might trap on such CPU depending on the OS configuration */
#నిర్వచించు have_vfp_vm(flags)                                              \
    (HAVE_VFP && ((flags) & AV_CPU_FLAG_VFP_VM))

#అయితే_ముగింపు /* AVUTIL_ARM_CPU_H */
