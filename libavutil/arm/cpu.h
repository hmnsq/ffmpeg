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

#अगर_अघोषित AVUTIL_ARM_CPU_H
#घोषणा AVUTIL_ARM_CPU_H

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"

#घोषणा have_armv5te(flags) CPUEXT(flags, ARMV5TE)
#घोषणा have_armv6(flags)   CPUEXT(flags, ARMV6)
#घोषणा have_armv6t2(flags) CPUEXT(flags, ARMV6T2)
#घोषणा have_vfp(flags)     CPUEXT(flags, VFP)
#घोषणा have_vfpv3(flags)   CPUEXT(flags, VFPV3)
#घोषणा have_neon(flags)    CPUEXT(flags, NEON)
#घोषणा have_setend(flags)  CPUEXT(flags, SETEND)

/* some functions use the VFPv2 vector mode which is deprecated in ARMv7-A
 * and might trap on such CPU depending on the OS configuration */
#घोषणा have_vfp_vm(flags)                                              \
    (HAVE_VFP && ((flags) & AV_CPU_FLAG_VFP_VM))

#पूर्ण_अगर /* AVUTIL_ARM_CPU_H */
