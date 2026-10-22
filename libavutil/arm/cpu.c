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

#ವ್ಯಾಖ್ಯಾನಿಸು CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#ವ್ಯಾಖ್ಯಾನಿಸು CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#ಆದರೆ defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "libavutil/avstring.h"

#ಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AT_HWCAP
#ವ್ಯಾಖ್ಯಾನಿಸು AT_HWCAP        16
#ಆದರೆ_ಅಂತ್ಯ

/* Relevant HWCAP values from <sys/auxv.h> that includes <bits/hwcap.h> */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HWCAP_ARM_VFP
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_ARM_VFP     (1 << 6)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HWCAP_ARM_EDSP
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_ARM_EDSP    (1 << 7)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HWCAP_ARM_THUMBEE
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_ARM_THUMBEE (1 << 11)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HWCAP_ARM_NEON
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_ARM_NEON    (1 << 12)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HWCAP_ARM_VFPv3
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_ARM_VFPv3   (1 << 13)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HWCAP_ARM_TLS
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_ARM_TLS     (1 << 15)
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_auxval(uint32_t *hwcap)
{
#ಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ret = ff_getauxval(AT_HWCAP);
    ಆದರೆ (ret == 0)
        ಹಿಂತಿರುಗಿ -1;
    *hwcap = ret;
    ಹಿಂತಿರುಗಿ 0;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ -1;
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ defined __linux__ || defined __ANDROID__
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_hwcap(uint32_t *hwcap)
{
    ರಚನೆ { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    ಪೂರ್ಣಾಂಕ err = -1;

    ಆದರೆ (!f)
        ಹಿಂತಿರುಗಿ -1;

    ಆಗ (fread(&auxv, ಗಾತ್ರ(auxv), 1, f) > 0) {
        ಆದರೆ (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            ನಿಲ್ಲಿಸು;
        }
    }

    fclose(f);
    ಹಿಂತಿರುಗಿ err;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ಅಕ್ಷರ buf[200];

    ಆದರೆ (!f)
        ಹಿಂತಿರುಗಿ -1;

    *hwcap = 0;
    ಆಗ (fgets(buf, ಗಾತ್ರ(buf), f)) {
        ಆದರೆ (av_strstart(buf, "Features", ಖಾಲಿ)) {
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " neon ") || ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            ನಿಲ್ಲಿಸು;
        }
    }
    fclose(f);
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_arm(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    ಆದರೆ (get_auxval(&hwcap) < 0)
#ಆದರೆ defined __linux__ || defined __ANDROID__
        ಆದರೆ (get_hwcap(&hwcap) < 0)
            ಆದರೆ (get_cpuinfo(&hwcap) < 0)
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ flags;

#ವ್ಯಾಖ್ಯಾನಿಸು check_cap(cap, flag) ಮಾಡು {               \
        ಆದರೆ (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } ಆಗ (0)

    /* No flags explicitly indicate v6 or v6T2 so check others which
       imply support. */
    check_cap(EDSP,    ARMV5TE);
    check_cap(TLS,     ARMV6);
    check_cap(THUMBEE, ARMV6T2);
    check_cap(VFP,     VFP);
    check_cap(VFPv3,   VFPV3);
    check_cap(NEON,    NEON);

    /* The v6 checks above are not reliable so let higher flags
       trickle down. */
    ಆದರೆ (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    ಆದರೆ (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    ಆದರೆ ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    ಹಿಂತಿರುಗಿ flags;
}

#ಇಲ್ಲದಿದ್ದರೆ

ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_arm(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#ಆದರೆ_ಅಂತ್ಯ

size_t ff_get_cpu_max_align_arm(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & AV_CPU_FLAG_NEON)
        ಹಿಂತಿರುಗಿ 16;

    ಹಿಂತಿರುಗಿ 8;
}
