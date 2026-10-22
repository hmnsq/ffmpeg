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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_AARCH64_AES     (1 << 3)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_AARCH64_PMULL   (1 << 4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_AARCH64_ਚੱਕਰੀ_ਜਾਂਚ_32   (1 << 7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_AARCH64_SHA3    (1 << 17)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_AARCH64_ASIMDDP (1 << 20)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_AARCH64_SVE     (1 << 22)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP2_AARCH64_SVE2   (1 << 1)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP2_AARCH64_I8MM   (1 << 13)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP2_AARCH64_SME    (1 << 23)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP2_AARCH64_SME2   (1ULL << 37)

ਸਥਿਰ ਪੂਰਨ detect_flags(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ hwcap = ff_getauxval(AT_HWCAP);
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ hwcap2 = ff_getauxval(AT_HWCAP2);

    ਜੇ (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    ਜੇ (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    ਜੇ (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    ਜੇ (hwcap & HWCAP_AARCH64_ਚੱਕਰੀ_ਜਾਂਚ_32)
        flags |= AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ;
    ਜੇ (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    ਜੇ (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    ਜੇ (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    ਜੇ (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    ਜੇ (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    ਜੇ (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    ਜੇ (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    ਵਾਪਸ flags;
}

#ਜਾਂਜੇ defined(__APPLE__) && HAVE_SYSCTLBYNAME
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/sysctl.h>

ਸਥਿਰ ਪੂਰਨ have_feature(ਅਚਲ ਅੱਖਰ *feature) {
    uint32_t ਮੁੱਲ = 0;
    size_t ਮਾਪ = ਆਕਾਰ(ਮੁੱਲ);
    ਜੇ (!sysctlbyname(feature, &ਮੁੱਲ, &ਮਾਪ, ਨਿਰਾ, 0))
        ਵਾਪਸ ਮੁੱਲ;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ detect_flags(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;

    ਜੇ (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    ਜੇ (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    ਜੇ (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    ਜੇ (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    ਜੇ (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ;
    ਜੇ (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    ਜੇ (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    ਜੇ (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    ਜੇ (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    ਵਾਪਸ flags;
}

#ਜਾਂਜੇ defined(__OpenBSD__)
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/armreg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/cpu.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/sysctl.h>

ਸਥਿਰ ਪੂਰਨ detect_flags(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ CPU_ID_AA64ISAR0
    ਪੂਰਨ mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = ਆਕਾਰ(isar0);
    ਜੇ (sysctl(mib, 2, &isar0, &len, ਨਿਰਾ, 0) != -1) {
        ਜੇ (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        ਜੇ (ID_AA64_ISAR0_ਚੱਕਰੀ_ਜਾਂਚ_32(isar0) >= ID_AA64_ISAR0_ਚੱਕਰੀ_ਜਾਂਚ_32_ਅਧਾਰ)
            flags |= AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ;
        ਜੇ (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_ਅਧਾਰ)
            flags |= AV_CPU_FLAG_ARM_AES;
        ਜੇ (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        ਜੇ (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = ਆਕਾਰ(isar1);
    ਜੇ (sysctl(mib, 2, &isar1, &len, ਨਿਰਾ, 0) != -1) {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ID_AA64ISAR1_I8MM_IMPL
        ਜੇ (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#ਜੇ_ਅੰਤ
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ flags;
}

#ਜਾਂਜੇ defined(_WIN32)
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>

ਸਥਿਰ ਪੂਰਨ detect_flags(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_V8_ਚੱਕਰੀ_ਜਾਂਚ_32_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_V8_ਚੱਕਰੀ_ਜਾਂਚ_32_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_V8_CRYPTO_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_ਉਪਲਬਧ)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_SHA3_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_EOR3;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_V82_DP_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_DOTPROD;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_V82_I8_MM_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_I8MM;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_SVE_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_SVE;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_SVE2_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_SVE2;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_SME_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_SME;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_SME_I16_I64_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_SME_I16I64;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ PF_ARM_SME2_INSTRUCTIONS_ਉਪਲਬਧ
    ਜੇ (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_ਉਪਲਬਧ))
        flags |= AV_CPU_FLAG_SME2;
#ਜੇ_ਅੰਤ
    ਵਾਪਸ flags;
}
#ਨਹੀਂਤਾਂ

ਸਥਿਰ ਪੂਰਨ detect_flags(ਖਾਲੀ)
{
    ਵਾਪਸ 0;
}

#ਜੇ_ਅੰਤ

ਪੂਰਨ ff_get_cpu_flags_aarch64(ਖਾਲੀ)
{
    ਪੂਰਨ flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#ਜੇ_ਅੰਤ

    flags |= detect_flags();

    ਵਾਪਸ flags;
}

size_t ff_get_cpu_max_align_aarch64(ਖਾਲੀ)
{
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ (flags & AV_CPU_FLAG_NEON)
        ਵਾਪਸ 16;

    ਵਾਪਸ 8;
}
