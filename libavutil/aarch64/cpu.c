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

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"
#समावेश "config.h"

#अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#समावेश <stdint.h>
#समावेश <sys/auxv.h>

#घोषणा HWCAP_AARCH64_AES     (1 << 3)
#घोषणा HWCAP_AARCH64_PMULL   (1 << 4)
#घोषणा HWCAP_AARCH64_CRC32   (1 << 7)
#घोषणा HWCAP_AARCH64_SHA3    (1 << 17)
#घोषणा HWCAP_AARCH64_ASIMDDP (1 << 20)
#घोषणा HWCAP_AARCH64_SVE     (1 << 22)
#घोषणा HWCAP2_AARCH64_SVE2   (1 << 1)
#घोषणा HWCAP2_AARCH64_I8MM   (1 << 13)
#घोषणा HWCAP2_AARCH64_SME    (1 << 23)
#घोषणा HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#घोषणा HWCAP2_AARCH64_SME2   (1ULL << 37)

अटल पूर्णांक detect_flags(व्योम)
{
    पूर्णांक flags = 0;

    अचिन्हित दीर्घ hwcap = ff_getauxval(AT_HWCAP);
    अचिन्हित दीर्घ hwcap2 = ff_getauxval(AT_HWCAP2);

    अगर (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    अगर (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    अगर (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    अगर (hwcap & HWCAP_AARCH64_CRC32)
        flags |= AV_CPU_FLAG_ARM_CRC;
    अगर (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    अगर (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    अगर (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    अगर (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    अगर (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    अगर (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    अगर (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    वापस flags;
}

#या_अगर defined(__APPLE__) && HAVE_SYSCTLBYNAME
#समावेश <sys/sysctl.h>

अटल पूर्णांक have_feature(स्थिर अक्षर *feature) {
    uint32_t मूल्य = 0;
    माप_प्रकार आकार = माप(मूल्य);
    अगर (!sysctlbyname(feature, &मूल्य, &आकार, शून्य, 0))
        वापस मूल्य;
    वापस 0;
}

अटल पूर्णांक detect_flags(व्योम)
{
    पूर्णांक flags = 0;

    अगर (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    अगर (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    अगर (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    अगर (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    अगर (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_CRC;
    अगर (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    अगर (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    अगर (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    अगर (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    वापस flags;
}

#या_अगर defined(__OpenBSD__)
#समावेश <machine/armreg.h>
#समावेश <machine/cpu.h>
#समावेश <sys/types.h>
#समावेश <sys/sysctl.h>

अटल पूर्णांक detect_flags(व्योम)
{
    पूर्णांक flags = 0;

#अगर_घोषित CPU_ID_AA64ISAR0
    पूर्णांक mib[2];
    uint64_t isar0;
    uint64_t isar1;
    माप_प्रकार len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = माप(isar0);
    अगर (sysctl(mib, 2, &isar0, &len, शून्य, 0) != -1) {
        अगर (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        अगर (ID_AA64ISAR0_CRC32(isar0) >= ID_AA64ISAR0_CRC32_BASE)
            flags |= AV_CPU_FLAG_ARM_CRC;
        अगर (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_BASE)
            flags |= AV_CPU_FLAG_ARM_AES;
        अगर (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        अगर (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = माप(isar1);
    अगर (sysctl(mib, 2, &isar1, &len, शून्य, 0) != -1) {
#अगर_घोषित ID_AA64ISAR1_I8MM_IMPL
        अगर (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#पूर्ण_अगर
    }
#पूर्ण_अगर

    वापस flags;
}

#या_अगर defined(_WIN32)
#समावेश <windows.h>

अटल पूर्णांक detect_flags(व्योम)
{
    पूर्णांक flags = 0;
#अगर_घोषित PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_ARM_CRC;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#पूर्ण_अगर
#अगर_घोषित PF_ARM_SHA3_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_EOR3;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_DOTPROD;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_V82_I8MM_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_V82_I8MM_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_I8MM;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_SVE_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SVE;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_SVE2_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SVE2;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_SME_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_SME_I16I64_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_SME_I16I64_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME_I16I64;
#पूर्ण_अगर
#अगर_घोषित PF_ARM_SME2_INSTRUCTIONS_AVAILABLE
    अगर (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME2;
#पूर्ण_अगर
    वापस flags;
}
#अन्यथा

अटल पूर्णांक detect_flags(व्योम)
{
    वापस 0;
}

#पूर्ण_अगर

पूर्णांक ff_get_cpu_flags_aarch64(व्योम)
{
    पूर्णांक flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#अगर_घोषित __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_CRC;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#पूर्ण_अगर
#अगर_घोषित __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#पूर्ण_अगर

    flags |= detect_flags();

    वापस flags;
}

माप_प्रकार ff_get_cpu_max_align_aarch64(व्योम)
{
    पूर्णांक flags = av_get_cpu_flags();

    अगर (flags & AV_CPU_FLAG_NEON)
        वापस 16;

    वापस 8;
}
