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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ARM_CPU_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ARM_CPU_H

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_armv5te(flags) CPUEXT(flags, ARMV5TE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_armv6(flags)   CPUEXT(flags, ARMV6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_armv6t2(flags) CPUEXT(flags, ARMV6T2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_vfp(flags)     CPUEXT(flags, VFP)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_vfpv3(flags)   CPUEXT(flags, VFPV3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_neon(flags)    CPUEXT(flags, NEON)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_setend(flags)  CPUEXT(flags, SETEND)

/* some functions use the VFPv2 vector mode which is deprecated in ARMv7-A
 * and might trap on such CPU depending on the OS configuration */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_vfp_vm(flags)                                              \
    (HAVE_VFP && ((flags) & AV_CPU_FLAG_VFP_VM))

#ਜੇ_ਅੰਤ /* AVUTIL_ARM_CPU_H */
