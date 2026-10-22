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

#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/cpu_internal.h"
#अन्तर्भाव "config.h"

#यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <sys/auxv.h>

#परिभाषय HWCAP_AARCH64_AES     (1 << 3)
#परिभाषय HWCAP_AARCH64_PMULL   (1 << 4)
#परिभाषय HWCAP_AARCH64_चक्रीयपरीक्षा_32   (1 << 7)
#परिभाषय HWCAP_AARCH64_SHA3    (1 << 17)
#परिभाषय HWCAP_AARCH64_ASIMDDP (1 << 20)
#परिभाषय HWCAP_AARCH64_SVE     (1 << 22)
#परिभाषय HWCAP2_AARCH64_SVE2   (1 << 1)
#परिभाषय HWCAP2_AARCH64_I8MM   (1 << 13)
#परिभाषय HWCAP2_AARCH64_SME    (1 << 23)
#परिभाषय HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#परिभाषय HWCAP2_AARCH64_SME2   (1ULL << 37)

स्थिर पूर्णाङ्क detect_flags(शून्य)
{
    पूर्णाङ्क flags = 0;

    अचिह्नित दीर्घ hwcap = ff_getauxval(AT_HWCAP);
    अचिह्नित दीर्घ hwcap2 = ff_getauxval(AT_HWCAP2);

    यदि (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    यदि (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    यदि (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    यदि (hwcap & HWCAP_AARCH64_चक्रीयपरीक्षा_32)
        flags |= AV_CPU_FLAG_ARM_CRC;
    यदि (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    यदि (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    यदि (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    यदि (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    यदि (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    यदि (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    यदि (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    प्रत्यागम flags;
}

#नोचेद्यदि defined(__APPLE__) && HAVE_SYSCTLBYNAME
#अन्तर्भाव <sys/sysctl.h>

स्थिर पूर्णाङ्क have_feature(ध्रुव वर्ण *feature) {
    uint32_t मानम् = 0;
    size_t आकार = परिमाण(मानम्);
    यदि (!sysctlbyname(feature, &मानम्, &आकार, रिक्त, 0))
        प्रत्यागम मानम्;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क detect_flags(शून्य)
{
    पूर्णाङ्क flags = 0;

    यदि (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    यदि (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    यदि (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    यदि (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    यदि (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_CRC;
    यदि (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    यदि (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    यदि (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    यदि (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    प्रत्यागम flags;
}

#नोचेद्यदि defined(__OpenBSD__)
#अन्तर्भाव <machine/armreg.h>
#अन्तर्भाव <machine/cpu.h>
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/sysctl.h>

स्थिर पूर्णाङ्क detect_flags(शून्य)
{
    पूर्णाङ्क flags = 0;

#यदि_परिभाषितम् CPU_ID_AA64ISAR0
    पूर्णाङ्क mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = परिमाण(isar0);
    यदि (sysctl(mib, 2, &isar0, &len, रिक्त, 0) != -1) {
        यदि (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        यदि (ID_AA64_ISAR0_चक्रीयपरीक्षा_32(isar0) >= ID_AA64_ISAR0_चक्रीयपरीक्षा_32_आधारः)
            flags |= AV_CPU_FLAG_ARM_CRC;
        यदि (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_आधारः)
            flags |= AV_CPU_FLAG_ARM_AES;
        यदि (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        यदि (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = परिमाण(isar1);
    यदि (sysctl(mib, 2, &isar1, &len, रिक्त, 0) != -1) {
#यदि_परिभाषितम् ID_AA64ISAR1_I8MM_IMPL
        यदि (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#यदि_अन्तः
    }
#यदि_अन्तः

    प्रत्यागम flags;
}

#नोचेद्यदि defined(_WIN32)
#अन्तर्भाव <windows.h>

स्थिर पूर्णाङ्क detect_flags(शून्य)
{
    पूर्णाङ्क flags = 0;
#यदि_परिभाषितम् PF_ARM_V8_चक्रीयपरीक्षा_32_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_V8_चक्रीयपरीक्षा_32_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_ARM_CRC;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_V8_CRYPTO_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_उपलब्धम्)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_SHA3_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_EOR3;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_V82_DP_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_DOTPROD;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_V82_I8_MM_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_I8MM;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_SVE_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_SVE;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_SVE2_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_SVE2;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_SME_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_SME;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_SME_I16_I64_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_SME_I16I64;
#यदि_अन्तः
#यदि_परिभाषितम् PF_ARM_SME2_INSTRUCTIONS_उपलब्धम्
    यदि (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_उपलब्धम्))
        flags |= AV_CPU_FLAG_SME2;
#यदि_अन्तः
    प्रत्यागम flags;
}
#अन्यथा

स्थिर पूर्णाङ्क detect_flags(शून्य)
{
    प्रत्यागम 0;
}

#यदि_अन्तः

पूर्णाङ्क ff_get_cpu_flags_aarch64(शून्य)
{
    पूर्णाङ्क flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#यदि_परिभाषितम् __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_CRC;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#यदि_अन्तः
#यदि_परिभाषितम् __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#यदि_अन्तः

    flags |= detect_flags();

    प्रत्यागम flags;
}

size_t ff_get_cpu_max_align_aarch64(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि (flags & AV_CPU_FLAG_NEON)
        प्रत्यागम 16;

    प्रत्यागम 8;
}
