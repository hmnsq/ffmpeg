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

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"
#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>

#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_AARCH64_AES     (1 << 3)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_AARCH64_PMULL   (1 << 4)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_AARCH64_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32   (1 << 7)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_AARCH64_SHA3    (1 << 17)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_AARCH64_ASIMDDP (1 << 20)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_AARCH64_SVE     (1 << 22)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP2_AARCH64_SVE2   (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP2_AARCH64_I8MM   (1 << 13)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP2_AARCH64_SME    (1 << 23)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP2_AARCH64_SME2   (1ULL << 37)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ detect_flags(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = 0;

    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ hwcap = ff_getauxval(AT_HWCAP);
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ hwcap2 = ff_getauxval(AT_HWCAP2);

    ಆದರೆ (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    ಆದರೆ (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    ಆದರೆ (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    ಆದರೆ (hwcap & HWCAP_AARCH64_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32)
        flags |= AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
    ಆದರೆ (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    ಆದರೆ (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    ಆದರೆ (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    ಆದರೆ (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    ಆದರೆ (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    ಆದರೆ (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    ಆದರೆ (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    ಹಿಂತಿರುಗಿ flags;
}

#ಅಥವಾಆದರೆ defined(__APPLE__) && HAVE_SYSCTLBYNAME
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ have_feature(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *feature) {
    uint32_t ಮೌಲ್ಯ = 0;
    size_t ಗಾತ್ರ_2 = ಗಾತ್ರ(ಮೌಲ್ಯ);
    ಆದರೆ (!sysctlbyname(feature, &ಮೌಲ್ಯ, &ಗಾತ್ರ_2, ಖಾಲಿ, 0))
        ಹಿಂತಿರುಗಿ ಮೌಲ್ಯ;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ detect_flags(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = 0;

    ಆದರೆ (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    ಆದರೆ (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    ಆದರೆ (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    ಆದರೆ (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    ಆದರೆ (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
    ಆದರೆ (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    ಆದರೆ (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    ಆದರೆ (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    ಆದರೆ (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    ಹಿಂತಿರುಗಿ flags;
}

#ಅಥವಾಆದರೆ defined(__OpenBSD__)
#ಅನ್ತರ್ಭಾವ <machine/armreg.h>
#ಅನ್ತರ್ಭಾವ <machine/cpu.h>
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ detect_flags(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = 0;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ CPU_ID_AA64ISAR0
    ಪೂರ್ಣಾಂಕ mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = ಗಾತ್ರ(isar0);
    ಆದರೆ (sysctl(mib, 2, &isar0, &len, ಖಾಲಿ, 0) != -1) {
        ಆದರೆ (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        ಆದರೆ (ID_AA64_ISAR0_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(isar0) >= ID_AA64_ISAR0_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_ತಳ)
            flags |= AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
        ಆದರೆ (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_ತಳ)
            flags |= AV_CPU_FLAG_ARM_AES;
        ಆದರೆ (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        ಆದರೆ (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = ಗಾತ್ರ(isar1);
    ಆದರೆ (sysctl(mib, 2, &isar1, &len, ಖಾಲಿ, 0) != -1) {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ID_AA64ISAR1_I8MM_IMPL
        ಆದರೆ (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#ಆದರೆ_ಅಂತ್ಯ
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ flags;
}

#ಅಥವಾಆದರೆ defined(_WIN32)
#ಅನ್ತರ್ಭಾವ <windows.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ detect_flags(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = 0;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_V8_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_V8_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_V8_CRYPTO_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_ಲಭ್ಯ)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_SHA3_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_EOR3;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_V82_DP_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_DOTPROD;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_V82_I8_MM_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_I8MM;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_SVE_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_SVE;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_SVE2_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_SVE2;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_SME_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_SME;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_SME_I16_I64_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_SME_I16I64;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ PF_ARM_SME2_INSTRUCTIONS_ಲಭ್ಯ
    ಆದರೆ (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_ಲಭ್ಯ))
        flags |= AV_CPU_FLAG_SME2;
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ flags;
}
#ಇಲ್ಲದಿದ್ದರೆ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ detect_flags(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_aarch64(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#ಆದರೆ_ಅಂತ್ಯ

    flags |= detect_flags();

    ಹಿಂತಿರುಗಿ flags;
}

size_t ff_get_cpu_max_align_aarch64(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & AV_CPU_FLAG_NEON)
        ಹಿಂತಿರುಗಿ 16;

    ಹಿಂತಿರುಗಿ 8;
}
