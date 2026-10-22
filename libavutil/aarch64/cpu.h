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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_AARCH64_CPU_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_AARCH64_CPU_H

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_armv8(flags)   CPUEXT(flags, ARMV8)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_neon(flags)    CPUEXT(flags, NEON)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_vfp(flags)     CPUEXT(flags, VFP)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_arm_ਚੱਕਰੀ_ਜਾਂਚ(flags) CPUEXT(flags, ARM_ਚੱਕਰੀ_ਜਾਂਚ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_pmull(flags)   CPUEXT(flags, PMULL)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_eor3(flags)    CPUEXT(flags, EOR3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_dotprod(flags) CPUEXT(flags, DOTPROD)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_i8mm(flags)    CPUEXT(flags, I8MM)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_sve(flags)     CPUEXT(flags, SVE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_sve2(flags)    CPUEXT(flags, SVE2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_sme(flags)     CPUEXT(flags, SME)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ have_sme2(flags)    CPUEXT(flags, SME2)

#ਜੇ HAVE_SVE
ਪੂਰਨ ff_aarch64_sve_ਲੰਮਾਈ(ਖਾਲੀ);
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_SME
ਪੂਰਨ ff_aarch64_sme_ਲੰਮਾਈ(ਖਾਲੀ);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_AARCH64_CPU_H */
