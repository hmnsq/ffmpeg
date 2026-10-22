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

#अगर_अघोषित AVUTIL_AARCH64_CPU_H
#घोषणा AVUTIL_AARCH64_CPU_H

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"

#घोषणा have_armv8(flags)   CPUEXT(flags, ARMV8)
#घोषणा have_neon(flags)    CPUEXT(flags, NEON)
#घोषणा have_vfp(flags)     CPUEXT(flags, VFP)
#घोषणा have_arm_crc(flags) CPUEXT(flags, ARM_CRC)
#घोषणा have_arm_aes(flags) CPUEXT(flags, ARM_AES)
#घोषणा have_pmull(flags)   CPUEXT(flags, PMULL)
#घोषणा have_eor3(flags)    CPUEXT(flags, EOR3)
#घोषणा have_dotprod(flags) CPUEXT(flags, DOTPROD)
#घोषणा have_i8mm(flags)    CPUEXT(flags, I8MM)
#घोषणा have_sve(flags)     CPUEXT(flags, SVE)
#घोषणा have_sve2(flags)    CPUEXT(flags, SVE2)
#घोषणा have_sme(flags)     CPUEXT(flags, SME)
#घोषणा have_sme_i16i64(flags) CPUEXT(flags, SME_I16I64)
#घोषणा have_sme2(flags)    CPUEXT(flags, SME2)

#अगर HAVE_SVE
पूर्णांक ff_aarch64_sve_लंबाई(व्योम);
#पूर्ण_अगर

#अगर HAVE_SME
पूर्णांक ff_aarch64_sme_लंबाई(व्योम);
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_AARCH64_CPU_H */
