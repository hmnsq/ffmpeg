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

#شامل "libavutil/cpu.h"
#شامل "libavutil/cpu_internal.h"
#شامل "config.h"

#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#شامل <stdint.h>
#شامل <sys/auxv.h>

#تعریف_کرو HWCAP_AARCH64_AES     (1 << 3)
#تعریف_کرو HWCAP_AARCH64_PMULL   (1 << 4)
#تعریف_کرو HWCAP_AARCH64_چکری_جانچ_32   (1 << 7)
#تعریف_کرو HWCAP_AARCH64_SHA3    (1 << 17)
#تعریف_کرو HWCAP_AARCH64_ASIMDDP (1 << 20)
#تعریف_کرو HWCAP_AARCH64_SVE     (1 << 22)
#تعریف_کرو HWCAP2_AARCH64_SVE2   (1 << 1)
#تعریف_کرو HWCAP2_AARCH64_I8MM   (1 << 13)
#تعریف_کرو HWCAP2_AARCH64_SME    (1 << 23)
#تعریف_کرو HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#تعریف_کرو HWCAP2_AARCH64_SME2   (1ULL << 37)

ساکن صحیح detect_flags(خالی)
{
    صحیح flags = 0;

    غیرعلامتی طویل hwcap = ff_getauxval(AT_HWCAP);
    غیرعلامتی طویل hwcap2 = ff_getauxval(AT_HWCAP2);

    اگر (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    اگر (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    اگر (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    اگر (hwcap & HWCAP_AARCH64_چکری_جانچ_32)
        flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
    اگر (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    اگر (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    اگر (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    اگر (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    اگر (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    اگر (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    اگر (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    واپس flags;
}

#وگرنہ_اگر defined(__APPLE__) && HAVE_SYSCTLBYNAME
#شامل <sys/sysctl.h>

ساکن صحیح have_feature(ثابت حرف *feature) {
    uint32_t قدر = 0;
    size_t سائز = حجم(قدر);
    اگر (!sysctlbyname(feature, &قدر, &سائز, تہی, 0))
        واپس قدر;
    واپس 0;
}

ساکن صحیح detect_flags(خالی)
{
    صحیح flags = 0;

    اگر (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    اگر (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    اگر (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    اگر (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    اگر (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
    اگر (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    اگر (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    اگر (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    اگر (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    واپس flags;
}

#وگرنہ_اگر defined(__OpenBSD__)
#شامل <machine/armreg.h>
#شامل <machine/cpu.h>
#شامل <sys/types.h>
#شامل <sys/sysctl.h>

ساکن صحیح detect_flags(خالی)
{
    صحیح flags = 0;

#اگر_تعریف_شدہ CPU_ID_AA64ISAR0
    صحیح mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = حجم(isar0);
    اگر (sysctl(mib, 2, &isar0, &len, تہی, 0) != -1) {
        اگر (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        اگر (ID_AA64_ISAR0_چکری_جانچ_32(isar0) >= ID_AA64_ISAR0_چکری_جانچ_32_بنیاد)
            flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
        اگر (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_بنیاد)
            flags |= AV_CPU_FLAG_ARM_AES;
        اگر (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        اگر (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = حجم(isar1);
    اگر (sysctl(mib, 2, &isar1, &len, تہی, 0) != -1) {
#اگر_تعریف_شدہ ID_AA64ISAR1_I8MM_IMPL
        اگر (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#اگر_ختم
    }
#اگر_ختم

    واپس flags;
}

#وگرنہ_اگر defined(_WIN32)
#شامل <windows.h>

ساکن صحیح detect_flags(خالی)
{
    صحیح flags = 0;
#اگر_تعریف_شدہ PF_ARM_V8_چکری_جانچ_32_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_V8_چکری_جانچ_32_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_V8_CRYPTO_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_دستیاب)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_SHA3_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_EOR3;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_V82_DP_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_DOTPROD;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_V82_I8_MM_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_I8MM;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_SVE_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SVE;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_SVE2_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SVE2;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_SME_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SME;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_SME_I16_I64_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SME_I16I64;
#اگر_ختم
#اگر_تعریف_شدہ PF_ARM_SME2_INSTRUCTIONS_دستیاب
    اگر (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SME2;
#اگر_ختم
    واپس flags;
}
#ورنہ

ساکن صحیح detect_flags(خالی)
{
    واپس 0;
}

#اگر_ختم

صحیح ff_get_cpu_flags_aarch64(خالی)
{
    صحیح flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#اگر_تعریف_شدہ __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#اگر_ختم
#اگر_تعریف_شدہ __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#اگر_ختم

    flags |= detect_flags();

    واپس flags;
}

size_t ff_get_cpu_max_align_aarch64(خالی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_NEON)
        واپس 16;

    واپس 8;
}
