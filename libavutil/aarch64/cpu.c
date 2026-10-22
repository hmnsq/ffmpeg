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

#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu_internal.h"
#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>

#define HWCAP_AARCH64_AES     (1 << 3)
#define HWCAP_AARCH64_PMULL   (1 << 4)
#define HWCAP_AARCH64_CRC32   (1 << 7)
#define HWCAP_AARCH64_SHA3    (1 << 17)
#define HWCAP_AARCH64_ASIMDDP (1 << 20)
#define HWCAP_AARCH64_SVE     (1 << 22)
#define HWCAP2_AARCH64_SVE2   (1 << 1)
#define HWCAP2_AARCH64_I8MM   (1 << 13)
#define HWCAP2_AARCH64_SME    (1 << 23)
#define HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#define HWCAP2_AARCH64_SME2   (1ULL << 37)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା detect_flags(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    ଯଦି (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    ଯଦି (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    ଯଦି (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    ଯଦି (hwcap & HWCAP_AARCH64_CRC32)
        flags |= AV_CPU_FLAG_ARM_CRC;
    ଯଦି (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    ଯଦି (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    ଯଦି (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    ଯଦି (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    ଯଦି (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    ଯଦି (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    ଯଦି (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    ଫେରନ୍ତୁ flags;
}

#ନଚେତଯଦି defined(__APPLE__) && HAVE_SYSCTLBYNAME
#ଅନ୍ତର୍ଭାଵ <sys/sysctl.h>

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା have_feature(ଅଚଳ ଅକ୍ଷର *feature) {
    uint32_t ମୂଲ୍ୟ = 0;
    size_t size = ଆକାର(ମୂଲ୍ୟ);
    ଯଦି (!sysctlbyname(feature, &ମୂଲ୍ୟ, &size, ଖାଲି, 0))
        ଫେରନ୍ତୁ ମୂଲ୍ୟ;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା detect_flags(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;

    ଯଦି (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    ଯଦି (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    ଯଦି (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    ଯଦି (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    ଯଦି (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_CRC;
    ଯଦି (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    ଯଦି (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    ଯଦି (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    ଯଦି (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    ଫେରନ୍ତୁ flags;
}

#ନଚେତଯଦି defined(__OpenBSD__)
#ଅନ୍ତର୍ଭାଵ <machine/armreg.h>
#ଅନ୍ତର୍ଭାଵ <machine/cpu.h>
#ଅନ୍ତର୍ଭାଵ <sys/types.h>
#ଅନ୍ତର୍ଭାଵ <sys/sysctl.h>

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା detect_flags(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;

#ifdef CPU_ID_AA64ISAR0
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = ଆକାର(isar0);
    ଯଦି (sysctl(mib, 2, &isar0, &len, ଖାଲି, 0) != -1) {
        ଯଦି (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        ଯଦି (ID_AA64ISAR0_CRC32(isar0) >= ID_AA64ISAR0_CRC32_BASE)
            flags |= AV_CPU_FLAG_ARM_CRC;
        ଯଦି (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_BASE)
            flags |= AV_CPU_FLAG_ARM_AES;
        ଯଦି (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        ଯଦି (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = ଆକାର(isar1);
    ଯଦି (sysctl(mib, 2, &isar1, &len, ଖାଲି, 0) != -1) {
#ifdef ID_AA64ISAR1_I8MM_IMPL
        ଯଦି (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#endif
    }
#endif

    ଫେରନ୍ତୁ flags;
}

#ନଚେତଯଦି defined(_WIN32)
#ଅନ୍ତର୍ଭାଵ <windows.h>

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା detect_flags(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;
#ifdef PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_ARM_CRC;
#endif
#ifdef PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#endif
#ifdef PF_ARM_SHA3_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_EOR3;
#endif
#ifdef PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_DOTPROD;
#endif
#ifdef PF_ARM_V82_I8MM_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_V82_I8MM_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_I8MM;
#endif
#ifdef PF_ARM_SVE_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SVE;
#endif
#ifdef PF_ARM_SVE2_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SVE2;
#endif
#ifdef PF_ARM_SME_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME;
#endif
#ifdef PF_ARM_SME_I16I64_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_SME_I16I64_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME_I16I64;
#endif
#ifdef PF_ARM_SME2_INSTRUCTIONS_AVAILABLE
    ଯଦି (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME2;
#endif
    ଫେରନ୍ତୁ flags;
}
#ଅନ୍ୟଥା

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା detect_flags(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ 0;
}

#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_aarch64(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#ifdef __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#endif
#ifdef __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#endif
#ifdef __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#endif
#ifdef __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#endif
#ifdef __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#endif
#ifdef __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_CRC;
#endif
#ifdef __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#endif
#ifdef __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#endif
#ifdef __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#endif
#ifdef __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#endif

    flags |= detect_flags();

    ଫେରନ୍ତୁ flags;
}

size_t ff_get_cpu_max_align_aarch64(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & AV_CPU_FLAG_NEON)
        ଫେରନ୍ତୁ 16;

    ଫେରନ୍ତୁ 8;
}
