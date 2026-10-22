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

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"
#ضمن "config.h"

#إذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ضمن <stdint.h>
#ضمن <sys/auxv.h>

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

ساكن صحيح detect_flags(فراغ)
{
    صحيح flags = 0;

    بنانشانی لما hwcap = ff_getauxval(AT_HWCAP);
    بنانشانی لما hwcap2 = ff_getauxval(AT_HWCAP2);

    إذا (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    إذا (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    إذا (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    إذا (hwcap & HWCAP_AARCH64_چکری_جانچ_32)
        flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
    إذا (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    إذا (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    إذا (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    إذا (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    إذا (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    إذا (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    إذا (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    أرجع flags;
}

#وإلاإذا defined(__APPLE__) && HAVE_SYSCTLBYNAME
#ضمن <sys/sysctl.h>

ساكن صحيح have_feature(ثابت حرف *feature) {
    uint32_t قدر = 0;
    size_t ناپ = حجم(قدر);
    إذا (!sysctlbyname(feature, &قدر, &ناپ, عدم, 0))
        أرجع قدر;
    أرجع 0;
}

ساكن صحيح detect_flags(فراغ)
{
    صحيح flags = 0;

    إذا (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    إذا (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    إذا (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    إذا (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    إذا (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
    إذا (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    إذا (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    إذا (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    إذا (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    أرجع flags;
}

#وإلاإذا defined(__OpenBSD__)
#ضمن <machine/armreg.h>
#ضمن <machine/cpu.h>
#ضمن <sys/types.h>
#ضمن <sys/sysctl.h>

ساكن صحيح detect_flags(فراغ)
{
    صحيح flags = 0;

#جے_تعریف_شدہ CPU_ID_AA64ISAR0
    صحيح mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = حجم(isar0);
    إذا (sysctl(mib, 2, &isar0, &len, عدم, 0) != -1) {
        إذا (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        إذا (ID_AA64_ISAR0_چکری_جانچ_32(isar0) >= ID_AA64_ISAR0_چکری_جانچ_32_ادھار)
            flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
        إذا (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_ادھار)
            flags |= AV_CPU_FLAG_ARM_AES;
        إذا (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        إذا (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = حجم(isar1);
    إذا (sysctl(mib, 2, &isar1, &len, عدم, 0) != -1) {
#جے_تعریف_شدہ ID_AA64ISAR1_I8MM_IMPL
        إذا (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#جے_انت
    }
#جے_انت

    أرجع flags;
}

#وإلاإذا defined(_WIN32)
#ضمن <windows.h>

ساكن صحيح detect_flags(فراغ)
{
    صحيح flags = 0;
#جے_تعریف_شدہ PF_ARM_V8_چکری_جانچ_32_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_V8_چکری_جانچ_32_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
#جے_انت
#جے_تعریف_شدہ PF_ARM_V8_CRYPTO_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_دستیاب)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#جے_انت
#جے_تعریف_شدہ PF_ARM_SHA3_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_EOR3;
#جے_انت
#جے_تعریف_شدہ PF_ARM_V82_DP_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_DOTPROD;
#جے_انت
#جے_تعریف_شدہ PF_ARM_V82_I8_MM_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_I8MM;
#جے_انت
#جے_تعریف_شدہ PF_ARM_SVE_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SVE;
#جے_انت
#جے_تعریف_شدہ PF_ARM_SVE2_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SVE2;
#جے_انت
#جے_تعریف_شدہ PF_ARM_SME_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SME;
#جے_انت
#جے_تعریف_شدہ PF_ARM_SME_I16_I64_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SME_I16I64;
#جے_انت
#جے_تعریف_شدہ PF_ARM_SME2_INSTRUCTIONS_دستیاب
    إذا (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_دستیاب))
        flags |= AV_CPU_FLAG_SME2;
#جے_انت
    أرجع flags;
}
#وإلا

ساكن صحيح detect_flags(فراغ)
{
    أرجع 0;
}

#جے_انت

صحيح ff_get_cpu_flags_aarch64(فراغ)
{
    صحيح flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#جے_تعریف_شدہ __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_چکری_جانچ;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#جے_انت
#جے_تعریف_شدہ __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#جے_انت

    flags |= detect_flags();

    أرجع flags;
}

size_t ff_get_cpu_max_align_aarch64(فراغ)
{
    صحيح flags = av_get_cpu_flags();

    إذا (flags & AV_CPU_FLAG_NEON)
        أرجع 16;

    أرجع 8;
}
