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

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"
#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <sys/auxv.h>

#నిర్వచించు HWCAP_AARCH64_AES     (1 << 3)
#నిర్వచించు HWCAP_AARCH64_PMULL   (1 << 4)
#నిర్వచించు HWCAP_AARCH64_చక్రీయ_తనిఖీ_32   (1 << 7)
#నిర్వచించు HWCAP_AARCH64_SHA3    (1 << 17)
#నిర్వచించు HWCAP_AARCH64_ASIMDDP (1 << 20)
#నిర్వచించు HWCAP_AARCH64_SVE     (1 << 22)
#నిర్వచించు HWCAP2_AARCH64_SVE2   (1 << 1)
#నిర్వచించు HWCAP2_AARCH64_I8MM   (1 << 13)
#నిర్వచించు HWCAP2_AARCH64_SME    (1 << 23)
#నిర్వచించు HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#నిర్వచించు HWCAP2_AARCH64_SME2   (1ULL << 37)

స్థిర పూర్ణాంకం detect_flags(శూన్య)
{
    పూర్ణాంకం flags = 0;

    గుర్తులేని దీర్ఘ hwcap = ff_getauxval(AT_HWCAP);
    గుర్తులేని దీర్ఘ hwcap2 = ff_getauxval(AT_HWCAP2);

    ఒకవేళ (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    ఒకవేళ (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    ఒకవేళ (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    ఒకవేళ (hwcap & HWCAP_AARCH64_చక్రీయ_తనిఖీ_32)
        flags |= AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ;
    ఒకవేళ (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    ఒకవేళ (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    ఒకవేళ (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    ఒకవేళ (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    ఒకవేళ (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    ఒకవేళ (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    ఒకవేళ (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    తిరిగి flags;
}

#లేదావేళ defined(__APPLE__) && HAVE_SYSCTLBYNAME
#అన్తర్భావ <sys/sysctl.h>

స్థిర పూర్ణాంకం have_feature(స్థిరరాశి అక్షరం *feature) {
    uint32_t విలువ = 0;
    size_t కొలత = పరిమాణం(విలువ);
    ఒకవేళ (!sysctlbyname(feature, &విలువ, &కొలత, ఖాళీ, 0))
        తిరిగి విలువ;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం detect_flags(శూన్య)
{
    పూర్ణాంకం flags = 0;

    ఒకవేళ (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    ఒకవేళ (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    ఒకవేళ (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    ఒకవేళ (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    ఒకవేళ (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ;
    ఒకవేళ (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    ఒకవేళ (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    ఒకవేళ (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    ఒకవేళ (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    తిరిగి flags;
}

#లేదావేళ defined(__OpenBSD__)
#అన్తర్భావ <machine/armreg.h>
#అన్తర్భావ <machine/cpu.h>
#అన్తర్భావ <sys/types.h>
#అన్తర్భావ <sys/sysctl.h>

స్థిర పూర్ణాంకం detect_flags(శూన్య)
{
    పూర్ణాంకం flags = 0;

#నిర్వచితమైతే CPU_ID_AA64ISAR0
    పూర్ణాంకం mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = పరిమాణం(isar0);
    ఒకవేళ (sysctl(mib, 2, &isar0, &len, ఖాళీ, 0) != -1) {
        ఒకవేళ (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        ఒకవేళ (ID_AA64_ISAR0_చక్రీయ_తనిఖీ_32(isar0) >= ID_AA64_ISAR0_చక్రీయ_తనిఖీ_32_పునాది)
            flags |= AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ;
        ఒకవేళ (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_పునాది)
            flags |= AV_CPU_FLAG_ARM_AES;
        ఒకవేళ (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        ఒకవేళ (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = పరిమాణం(isar1);
    ఒకవేళ (sysctl(mib, 2, &isar1, &len, ఖాళీ, 0) != -1) {
#నిర్వచితమైతే ID_AA64ISAR1_I8MM_IMPL
        ఒకవేళ (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#అయితే_ముగింపు
    }
#అయితే_ముగింపు

    తిరిగి flags;
}

#లేదావేళ defined(_WIN32)
#అన్తర్భావ <windows.h>

స్థిర పూర్ణాంకం detect_flags(శూన్య)
{
    పూర్ణాంకం flags = 0;
#నిర్వచితమైతే PF_ARM_V8_చక్రీయ_తనిఖీ_32_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_V8_చక్రీయ_తనిఖీ_32_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_V8_CRYPTO_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_అందుబాటు)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_SHA3_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_EOR3;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_V82_DP_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_DOTPROD;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_V82_I8_MM_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_I8MM;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_SVE_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_SVE;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_SVE2_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_SVE2;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_SME_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_SME;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_SME_I16_I64_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_SME_I16I64;
#అయితే_ముగింపు
#నిర్వచితమైతే PF_ARM_SME2_INSTRUCTIONS_అందుబాటు
    ఒకవేళ (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_అందుబాటు))
        flags |= AV_CPU_FLAG_SME2;
#అయితే_ముగింపు
    తిరిగి flags;
}
#లేకపోతే

స్థిర పూర్ణాంకం detect_flags(శూన్య)
{
    తిరిగి 0;
}

#అయితే_ముగింపు

పూర్ణాంకం ff_get_cpu_flags_aarch64(శూన్య)
{
    పూర్ణాంకం flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#నిర్వచితమైతే __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#అయితే_ముగింపు
#నిర్వచితమైతే __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#అయితే_ముగింపు

    flags |= detect_flags();

    తిరిగి flags;
}

size_t ff_get_cpu_max_align_aarch64(శూన్య)
{
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & AV_CPU_FLAG_NEON)
        తిరిగి 16;

    తిరిగి 8;
}
