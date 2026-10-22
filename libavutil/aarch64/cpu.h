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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_AARCH64_CPU_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_AARCH64_CPU_H

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"

#ವ್ಯಾಖ್ಯಾನಿಸು have_armv8(flags)   CPUEXT(flags, ARMV8)
#ವ್ಯಾಖ್ಯಾನಿಸು have_neon(flags)    CPUEXT(flags, NEON)
#ವ್ಯಾಖ್ಯಾನಿಸು have_vfp(flags)     CPUEXT(flags, VFP)
#ವ್ಯಾಖ್ಯಾನಿಸು have_arm_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(flags) CPUEXT(flags, ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ)
#ವ್ಯಾಖ್ಯಾನಿಸು have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#ವ್ಯಾಖ್ಯಾನಿಸು have_pmull(flags)   CPUEXT(flags, PMULL)
#ವ್ಯಾಖ್ಯಾನಿಸು have_eor3(flags)    CPUEXT(flags, EOR3)
#ವ್ಯಾಖ್ಯಾನಿಸು have_dotprod(flags) CPUEXT(flags, DOTPROD)
#ವ್ಯಾಖ್ಯಾನಿಸು have_i8mm(flags)    CPUEXT(flags, I8MM)
#ವ್ಯಾಖ್ಯಾನಿಸು have_sve(flags)     CPUEXT(flags, SVE)
#ವ್ಯಾಖ್ಯಾನಿಸು have_sve2(flags)    CPUEXT(flags, SVE2)
#ವ್ಯಾಖ್ಯಾನಿಸು have_sme(flags)     CPUEXT(flags, SME)
#ವ್ಯಾಖ್ಯಾನಿಸು have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#ವ್ಯಾಖ್ಯಾನಿಸು have_sme2(flags)    CPUEXT(flags, SME2)

#ಆದರೆ HAVE_SVE
ಪೂರ್ಣಾಂಕ ff_aarch64_sve_ಉದ್ದಳತೆ(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_SME
ಪೂರ್ಣಾಂಕ ff_aarch64_sme_ಉದ್ದಳತೆ(ಶೂನ್ಯ);
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_AARCH64_CPU_H */
