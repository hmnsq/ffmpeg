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

#تعریف_کړه HWCAP_AARCH64_AES     (1 << 3)
#تعریف_کړه HWCAP_AARCH64_PMULL   (1 << 4)
#تعریف_کړه HWCAP_AARCH64_دوراني_ازموینه_32   (1 << 7)
#تعریف_کړه HWCAP_AARCH64_SHA3    (1 << 17)
#تعریف_کړه HWCAP_AARCH64_ASIMDDP (1 << 20)
#تعریف_کړه HWCAP_AARCH64_SVE     (1 << 22)
#تعریف_کړه HWCAP2_AARCH64_SVE2   (1 << 1)
#تعریف_کړه HWCAP2_AARCH64_I8MM   (1 << 13)
#تعریف_کړه HWCAP2_AARCH64_SME    (1 << 23)
#تعریف_کړه HWCAP2_AARCH64_SME_I16I64 (1 << 24)
#تعریف_کړه HWCAP2_AARCH64_SME2   (1ULL << 37)

ساكن صحيح detect_flags(فراغ)
{
    صحيح flags = 0;

    بینښه اوږد hwcap = ff_getauxval(AT_HWCAP);
    بینښه اوږد hwcap2 = ff_getauxval(AT_HWCAP2);

    إذا (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    إذا (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    إذا (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    إذا (hwcap & HWCAP_AARCH64_دوراني_ازموینه_32)
        flags |= AV_CPU_FLAG_ARM_دوراني_ازموینه;
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
    uint32_t ارزښت = 0;
    size_t اندازه = حجم(ارزښت);
    إذا (!sysctlbyname(feature, &ارزښت, &اندازه, عدم, 0))
        أرجع ارزښت;
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
        flags |= AV_CPU_FLAG_ARM_دوراني_ازموینه;
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

#که_تعریف_شوی CPU_ID_AA64ISAR0
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
        إذا (ID_AA64_ISAR0_دوراني_ازموینه_32(isar0) >= ID_AA64_ISAR0_دوراني_ازموینه_32_بنسټ)
            flags |= AV_CPU_FLAG_ARM_دوراني_ازموینه;
        إذا (ID_AA64ISAR0_AES(isar0) >= ID_AA64_ISAR0_AES_بنسټ)
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
#که_تعریف_شوی ID_AA64ISAR1_I8MM_IMPL
        إذا (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#د_که_پای
    }
#د_که_پای

    أرجع flags;
}

#وإلاإذا defined(_WIN32)
#ضمن <windows.h>

ساكن صحيح detect_flags(فراغ)
{
    صحيح flags = 0;
#که_تعریف_شوی PF_ARM_V8_دوراني_ازموینه_32_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_V8_دوراني_ازموینه_32_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_ARM_دوراني_ازموینه;
#د_که_پای
#که_تعریف_شوی PF_ARM_V8_CRYPTO_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_شته)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#د_که_پای
#که_تعریف_شوی PF_ARM_SHA3_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_EOR3;
#د_که_پای
#که_تعریف_شوی PF_ARM_V82_DP_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_DOTPROD;
#د_که_پای
#که_تعریف_شوی PF_ARM_V82_I8_MM_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_V82_I8_MM_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_I8MM;
#د_که_پای
#که_تعریف_شوی PF_ARM_SVE_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_SVE;
#د_که_پای
#که_تعریف_شوی PF_ARM_SVE2_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_SVE2;
#د_که_پای
#که_تعریف_شوی PF_ARM_SME_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_SME;
#د_که_پای
#که_تعریف_شوی PF_ARM_SME_I16_I64_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_SME_I16_I64_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_SME_I16I64;
#د_که_پای
#که_تعریف_شوی PF_ARM_SME2_INSTRUCTIONS_شته
    إذا (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_شته))
        flags |= AV_CPU_FLAG_SME2;
#د_که_پای
    أرجع flags;
}
#وإلا

ساكن صحيح detect_flags(فراغ)
{
    أرجع 0;
}

#د_که_پای

صحيح ff_get_cpu_flags_aarch64(فراغ)
{
    صحيح flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
                AV_CPU_FLAG_NEON  * HAVE_NEON;

#که_تعریف_شوی __ARM_FEATURE_DOTPROD
    flags |= AV_CPU_FLAG_DOTPROD;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_MATMUL_INT8
    flags |= AV_CPU_FLAG_I8MM;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_SVE
    flags |= AV_CPU_FLAG_SVE;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_SVE2
    flags |= AV_CPU_FLAG_SVE2;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_SME
    flags |= AV_CPU_FLAG_SME;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_CRC32
    flags |= AV_CPU_FLAG_ARM_دوراني_ازموینه;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_AES
    flags |= AV_CPU_FLAG_ARM_AES;
    flags |= AV_CPU_FLAG_PMULL;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_SHA3
    flags |= AV_CPU_FLAG_EOR3;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_SME_I16I64
    flags |= AV_CPU_FLAG_SME_I16I64;
#د_که_پای
#که_تعریف_شوی __ARM_FEATURE_SME2
    flags |= AV_CPU_FLAG_SME2;
#د_که_پای

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
