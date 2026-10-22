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

#اگر_تعریف_نشده AVUTIL_ARM_CPU_H
#تعریف_کن AVUTIL_ARM_CPU_H

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#تعریف_کن have_armv5te(flags) CPUEXT(flags, ARMV5TE)
#تعریف_کن have_armv6(flags)   CPUEXT(flags, ARMV6)
#تعریف_کن have_armv6t2(flags) CPUEXT(flags, ARMV6T2)
#تعریف_کن have_vfp(flags)     CPUEXT(flags, VFP)
#تعریف_کن have_vfpv3(flags)   CPUEXT(flags, VFPV3)
#تعریف_کن have_neon(flags)    CPUEXT(flags, NEON)
#تعریف_کن have_setend(flags)  CPUEXT(flags, SETEND)

/* some functions use the VFPv2 vector mode which is deprecated in ARMv7-A
 * and might trap on such CPU depending on the OS configuration */
#تعریف_کن have_vfp_vm(flags)                                              \
    (HAVE_VFP && ((flags) & AV_CPU_FLAG_VFP_VM))

#پایان_اگر /* AVUTIL_ARM_CPU_H */
