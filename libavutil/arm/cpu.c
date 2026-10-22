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

#define CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#define CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#यदि defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "libavutil/avstring.h"

#यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अन्तर्भाव <sys/auxv.h>
#endif

#ifndef AT_HWCAP
#define AT_HWCAP        16
#endif

/* Relevant HWCAP values from <sys/auxv.h> that includes <bits/hwcap.h> */
#ifndef HWCAP_ARM_VFP
#define HWCAP_ARM_VFP     (1 << 6)
#endif
#ifndef HWCAP_ARM_EDSP
#define HWCAP_ARM_EDSP    (1 << 7)
#endif
#ifndef HWCAP_ARM_THUMBEE
#define HWCAP_ARM_THUMBEE (1 << 11)
#endif
#ifndef HWCAP_ARM_NEON
#define HWCAP_ARM_NEON    (1 << 12)
#endif
#ifndef HWCAP_ARM_VFPv3
#define HWCAP_ARM_VFPv3   (1 << 13)
#endif
#ifndef HWCAP_ARM_TLS
#define HWCAP_ARM_TLS     (1 << 15)
#endif

स्थिर पूर्णाङ्क get_auxval(uint32_t *hwcap)
{
#यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    unsigned long ret = ff_getauxval(AT_HWCAP);
    यदि (ret == 0)
        प्रत्यागम -1;
    *hwcap = ret;
    प्रत्यागम 0;
#अन्यथा
    प्रत्यागम -1;
#endif
}

#यदि defined __linux__ || defined __ANDROID__
स्थिर पूर्णाङ्क get_hwcap(uint32_t *hwcap)
{
    संरचना { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    पूर्णाङ्क err = -1;

    यदि (!f)
        प्रत्यागम -1;

    यावत् (fread(&auxv, परिमाण(auxv), 1, f) > 0) {
        यदि (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            भङ्ग;
        }
    }

    fclose(f);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    वर्ण buf[200];

    यदि (!f)
        प्रत्यागम -1;

    *hwcap = 0;
    यावत् (fgets(buf, परिमाण(buf), f)) {
        यदि (av_strstart(buf, "Features", रिक्त)) {
            यदि (strstr(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            यदि (strstr(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            यदि (strstr(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            यदि (strstr(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            यदि (strstr(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            यदि (strstr(buf, " neon ") || strstr(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            यदि (strstr(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            भङ्ग;
        }
    }
    fclose(f);
    प्रत्यागम 0;
}
#endif

पूर्णाङ्क ff_get_cpu_flags_arm(शून्य)
{
    पूर्णाङ्क flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    यदि (get_auxval(&hwcap) < 0)
#यदि defined __linux__ || defined __ANDROID__
        यदि (get_hwcap(&hwcap) < 0)
            यदि (get_cpuinfo(&hwcap) < 0)
#endif
                प्रत्यागम flags;

#define check_cap(cap, flag) कुरु {               \
        यदि (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } यावत् (0)

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
    यदि (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    अन्यथा यदि (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    यदि (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    यदि ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    प्रत्यागम flags;
}

#अन्यथा

पूर्णाङ्क ff_get_cpu_flags_arm(शून्य)
{
    प्रत्यागम AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#endif

size_t ff_get_cpu_max_align_arm(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि (flags & AV_CPU_FLAG_NEON)
        प्रत्यागम 16;

    प्रत्यागम 8;
}
