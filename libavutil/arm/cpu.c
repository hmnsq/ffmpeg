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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#ਜੇ defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avstring.h"

#ਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AT_HWCAP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT_HWCAP        16
#ਜੇ_ਅੰਤ

/* Relevant HWCAP values from <sys/auxv.h> that includes <bits/hwcap.h> */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HWCAP_ARM_VFP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_ARM_VFP     (1 << 6)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HWCAP_ARM_EDSP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_ARM_EDSP    (1 << 7)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HWCAP_ARM_THUMBEE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_ARM_THUMBEE (1 << 11)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HWCAP_ARM_NEON
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_ARM_NEON    (1 << 12)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HWCAP_ARM_VFPv3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_ARM_VFPv3   (1 << 13)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HWCAP_ARM_TLS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_ARM_TLS     (1 << 15)
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ get_auxval(uint32_t *hwcap)
{
#ਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ret = ff_getauxval(AT_HWCAP);
    ਜੇ (ret == 0)
        ਵਾਪਸ -1;
    *hwcap = ret;
    ਵਾਪਸ 0;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ -1;
#ਜੇ_ਅੰਤ
}

#ਜੇ defined __linux__ || defined __ANDROID__
ਸਥਿਰ ਪੂਰਨ get_hwcap(uint32_t *hwcap)
{
    ਬਣਤਰ { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    ਪੂਰਨ err = -1;

    ਜੇ (!f)
        ਵਾਪਸ -1;

    ਜਦੋਂ (fread(&auxv, ਆਕਾਰ(auxv), 1, f) > 0) {
        ਜੇ (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            ਰੋਕੋ;
        }
    }

    fclose(f);
    ਵਾਪਸ err;
}

ਸਥਿਰ ਪੂਰਨ get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ਅੱਖਰ buf[200];

    ਜੇ (!f)
        ਵਾਪਸ -1;

    *hwcap = 0;
    ਜਦੋਂ (fgets(buf, ਆਕਾਰ(buf), f)) {
        ਜੇ (av_strstart(buf, "Features", ਨਿਰਾ)) {
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " neon ") || ਲੜੀ_ਖੋਜ(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            ਰੋਕੋ;
        }
    }
    fclose(f);
    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

ਪੂਰਨ ff_get_cpu_flags_arm(ਖਾਲੀ)
{
    ਪੂਰਨ flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    ਜੇ (get_auxval(&hwcap) < 0)
#ਜੇ defined __linux__ || defined __ANDROID__
        ਜੇ (get_hwcap(&hwcap) < 0)
            ਜੇ (get_cpuinfo(&hwcap) < 0)
#ਜੇ_ਅੰਤ
                ਵਾਪਸ flags;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ check_cap(cap, flag) ਕਰੋ {               \
        ਜੇ (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } ਜਦੋਂ (0)

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
    ਜੇ (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    ਨਹੀਂਤਾਂ ਜੇ (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    ਜੇ (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    ਜੇ ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    ਵਾਪਸ flags;
}

#ਨਹੀਂਤਾਂ

ਪੂਰਨ ff_get_cpu_flags_arm(ਖਾਲੀ)
{
    ਵਾਪਸ AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#ਜੇ_ਅੰਤ

size_t ff_get_cpu_max_align_arm(ਖਾਲੀ)
{
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ (flags & AV_CPU_FLAG_NEON)
        ਵਾਪਸ 16;

    ਵਾਪਸ 8;
}
