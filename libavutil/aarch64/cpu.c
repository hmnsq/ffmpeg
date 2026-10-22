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

#include "libavutil/cpu.h"
#include "libavutil/cpu_internal.h"
#include "config.h"

#ᯀᯮᯝ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#include <stdint.h>
#include <sys/auxv.h>

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

static puur_naa_nka detect_flags(void)
{
    puur_naa_nka flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    ᯀᯮᯝ (hwcap & HWCAP_AARCH64_AES)
        flags |= AV_CPU_FLAG_ARM_AES;
    ᯀᯮᯝ (hwcap & HWCAP_AARCH64_PMULL)
        flags |= AV_CPU_FLAG_PMULL;
    ᯀᯮᯝ (hwcap & HWCAP_AARCH64_SHA3)
        flags |= AV_CPU_FLAG_EOR3;
    ᯀᯮᯝ (hwcap & HWCAP_AARCH64_CRC32)
        flags |= AV_CPU_FLAG_ARM_CRC;
    ᯀᯮᯝ (hwcap & HWCAP_AARCH64_ASIMDDP)
        flags |= AV_CPU_FLAG_DOTPROD;
    ᯀᯮᯝ (hwcap & HWCAP_AARCH64_SVE)
        flags |= AV_CPU_FLAG_SVE;
    ᯀᯮᯝ (hwcap2 & HWCAP2_AARCH64_SVE2)
        flags |= AV_CPU_FLAG_SVE2;
    ᯀᯮᯝ (hwcap2 & HWCAP2_AARCH64_I8MM)
        flags |= AV_CPU_FLAG_I8MM;
    ᯀᯮᯝ (hwcap2 & HWCAP2_AARCH64_SME)
        flags |= AV_CPU_FLAG_SME;
    ᯀᯮᯝ (hwcap2 & HWCAP2_AARCH64_SME_I16I64)
        flags |= AV_CPU_FLAG_SME_I16I64;
    ᯀᯮᯝ (hwcap2 & HWCAP2_AARCH64_SME2)
        flags |= AV_CPU_FLAG_SME2;

    ᯀᯮᯞ flags;
}

#elif defined(__APPLE__) && HAVE_SYSCTLBYNAME
#include <sys/sysctl.h>

static puur_naa_nka have_feature(const var_na *feature) {
    uint32_t value = 0;
    size_t size = parimaa_na(value);
    ᯀᯮᯝ (!sysctlbyname(feature, &value, &size, NULL, 0))
        ᯀᯮᯞ value;
    ᯀᯮᯞ 0;
}

static puur_naa_nka detect_flags(void)
{
    puur_naa_nka flags = 0;

    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_DotProd"))
        flags |= AV_CPU_FLAG_DOTPROD;
    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_I8MM"))
        flags |= AV_CPU_FLAG_I8MM;
    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_SME"))
        flags |= AV_CPU_FLAG_SME;
    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_SME_I16I64"))
        flags |= AV_CPU_FLAG_SME_I16I64;
    ᯀᯮᯝ (have_feature("hw.optional.armv8_crc32"))
        flags |= AV_CPU_FLAG_ARM_CRC;
    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_AES"))
        flags |= AV_CPU_FLAG_ARM_AES;
    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_PMULL"))
        flags |= AV_CPU_FLAG_PMULL;
    ᯀᯮᯝ (have_feature("hw.optional.armv8_2_sha3"))
        flags |= AV_CPU_FLAG_EOR3;
    ᯀᯮᯝ (have_feature("hw.optional.arm.FEAT_SME2"))
        flags |= AV_CPU_FLAG_SME2;

    ᯀᯮᯞ flags;
}

#elif defined(__OpenBSD__)
#include <machine/armreg.h>
#include <machine/cpu.h>
#include <sys/types.h>
#include <sys/sysctl.h>

static puur_naa_nka detect_flags(void)
{
    puur_naa_nka flags = 0;

#ifdef CPU_ID_AA64ISAR0
    puur_naa_nka mib[2];
    uint64_t isar0;
    uint64_t isar1;
    size_t len;

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR0;
    len = parimaa_na(isar0);
    ᯀᯮᯝ (sysctl(mib, 2, &isar0, &len, NULL, 0) != -1) {
        ᯀᯮᯝ (ID_AA64ISAR0_DP(isar0) >= ID_AA64ISAR0_DP_IMPL)
            flags |= AV_CPU_FLAG_DOTPROD;
        ᯀᯮᯝ (ID_AA64ISAR0_CRC32(isar0) >= ID_AA64ISAR0_CRC32_BASE)
            flags |= AV_CPU_FLAG_ARM_CRC;
        ᯀᯮᯝ (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_BASE)
            flags |= AV_CPU_FLAG_ARM_AES;
        ᯀᯮᯝ (ID_AA64ISAR0_AES(isar0) >= ID_AA64ISAR0_AES_PMULL)
            flags |= AV_CPU_FLAG_PMULL;
        ᯀᯮᯝ (ID_AA64ISAR0_SHA3(isar0) >= ID_AA64ISAR0_SHA3_IMPL)
            flags |= AV_CPU_FLAG_EOR3;
    }

    mib[0] = CTL_MACHDEP;
    mib[1] = CPU_ID_AA64ISAR1;
    len = parimaa_na(isar1);
    ᯀᯮᯝ (sysctl(mib, 2, &isar1, &len, NULL, 0) != -1) {
#ifdef ID_AA64ISAR1_I8MM_IMPL
        ᯀᯮᯝ (ID_AA64ISAR1_I8MM(isar1) >= ID_AA64ISAR1_I8MM_IMPL)
            flags |= AV_CPU_FLAG_I8MM;
#endif
    }
#endif

    ᯀᯮᯞ flags;
}

#elif defined(_WIN32)
#include <windows.h>

static puur_naa_nka detect_flags(void)
{
    puur_naa_nka flags = 0;
#ifdef PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_V8_CRC32_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_ARM_CRC;
#endif
#ifdef PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_V8_CRYPTO_INSTRUCTIONS_AVAILABLE)) {
        flags |= AV_CPU_FLAG_ARM_AES;
        flags |= AV_CPU_FLAG_PMULL;
    }
#endif
#ifdef PF_ARM_SHA3_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_SHA3_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_EOR3;
#endif
#ifdef PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_V82_DP_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_DOTPROD;
#endif
#ifdef PF_ARM_V82_I8MM_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_V82_I8MM_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_I8MM;
#endif
#ifdef PF_ARM_SVE_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_SVE_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SVE;
#endif
#ifdef PF_ARM_SVE2_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_SVE2_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SVE2;
#endif
#ifdef PF_ARM_SME_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_SME_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME;
#endif
#ifdef PF_ARM_SME_I16I64_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_SME_I16I64_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME_I16I64;
#endif
#ifdef PF_ARM_SME2_INSTRUCTIONS_AVAILABLE
    ᯀᯮᯝ (IsProcessorFeaturePresent(PF_ARM_SME2_INSTRUCTIONS_AVAILABLE))
        flags |= AV_CPU_FLAG_SME2;
#endif
    ᯀᯮᯞ flags;
}
#ᯀᯮᯝᯂᯪ

static puur_naa_nka detect_flags(void)
{
    ᯀᯮᯞ 0;
}

#endif

puur_naa_nka ff_get_cpu_flags_aarch64(void)
{
    puur_naa_nka flags = AV_CPU_FLAG_ARMV8 * HAVE_ARMV8 |
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

    ᯀᯮᯞ flags;
}

size_t ff_get_cpu_max_align_aarch64(void)
{
    puur_naa_nka flags = av_get_cpu_flags();

    ᯀᯮᯝ (flags & AV_CPU_FLAG_NEON)
        ᯀᯮᯞ 16;

    ᯀᯮᯞ 8;
}
