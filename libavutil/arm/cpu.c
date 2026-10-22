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

#నిర్వచించు CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#నిర్వచించు CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#ఒకవేళ defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ "libavutil/avstring.h"

#ఒకవేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#అన్తర్భావ <sys/auxv.h>
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే AT_HWCAP
#నిర్వచించు AT_HWCAP        16
#అయితే_ముగింపు

/* Relevant HWCAP values from <sys/auxv.h> that includes <bits/hwcap.h> */
#నిర్వచితం_కాకపోతే HWCAP_ARM_VFP
#నిర్వచించు HWCAP_ARM_VFP     (1 << 6)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HWCAP_ARM_EDSP
#నిర్వచించు HWCAP_ARM_EDSP    (1 << 7)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HWCAP_ARM_THUMBEE
#నిర్వచించు HWCAP_ARM_THUMBEE (1 << 11)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HWCAP_ARM_NEON
#నిర్వచించు HWCAP_ARM_NEON    (1 << 12)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HWCAP_ARM_VFPv3
#నిర్వచించు HWCAP_ARM_VFPv3   (1 << 13)
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HWCAP_ARM_TLS
#నిర్వచించు HWCAP_ARM_TLS     (1 << 15)
#అయితే_ముగింపు

స్థిర పూర్ణాంకం get_auxval(uint32_t *hwcap)
{
#ఒకవేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    గుర్తులేని దీర్ఘ ret = ff_getauxval(AT_HWCAP);
    ఒకవేళ (ret == 0)
        తిరిగి -1;
    *hwcap = ret;
    తిరిగి 0;
#లేకపోతే
    తిరిగి -1;
#అయితే_ముగింపు
}

#ఒకవేళ defined __linux__ || defined __ANDROID__
స్థిర పూర్ణాంకం get_hwcap(uint32_t *hwcap)
{
    నిర్మాణం { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    పూర్ణాంకం err = -1;

    ఒకవేళ (!f)
        తిరిగి -1;

    అయితే (fread(&auxv, పరిమాణం(auxv), 1, f) > 0) {
        ఒకవేళ (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            ఆపు;
        }
    }

    fclose(f);
    తిరిగి err;
}

స్థిర పూర్ణాంకం get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    అక్షరం buf[200];

    ఒకవేళ (!f)
        తిరిగి -1;

    *hwcap = 0;
    అయితే (fgets(buf, పరిమాణం(buf), f)) {
        ఒకవేళ (av_strstart(buf, "Features", ఖాళీ)) {
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " neon ") || అక్షరశ్రేణి_శోధన(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            ఆపు;
        }
    }
    fclose(f);
    తిరిగి 0;
}
#అయితే_ముగింపు

పూర్ణాంకం ff_get_cpu_flags_arm(శూన్య)
{
    పూర్ణాంకం flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    ఒకవేళ (get_auxval(&hwcap) < 0)
#ఒకవేళ defined __linux__ || defined __ANDROID__
        ఒకవేళ (get_hwcap(&hwcap) < 0)
            ఒకవేళ (get_cpuinfo(&hwcap) < 0)
#అయితే_ముగింపు
                తిరిగి flags;

#నిర్వచించు check_cap(cap, flag) చేయి {               \
        ఒకవేళ (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } అయితే (0)

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
    ఒకవేళ (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    లేకపోతే ఒకవేళ (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    ఒకవేళ (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    ఒకవేళ ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    తిరిగి flags;
}

#లేకపోతే

పూర్ణాంకం ff_get_cpu_flags_arm(శూన్య)
{
    తిరిగి AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#అయితే_ముగింపు

size_t ff_get_cpu_max_align_arm(శూన్య)
{
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & AV_CPU_FLAG_NEON)
        తిరిగి 16;

    తిరిగి 8;
}
