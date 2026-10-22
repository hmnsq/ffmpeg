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

#define CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#define CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#ถ้า defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "libavutil/avstring.h"

#ถ้า HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#include <sys/auxv.h>
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

static จำนวนเต็ม get_auxval(uint32_t *hwcap)
{
#ถ้า HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    unsigned long ret = ff_getauxval(AT_HWCAP);
    ถ้า (ret == 0)
        คืน -1;
    *hwcap = ret;
    คืน 0;
#มิฉะนั้น
    คืน -1;
#endif
}

#ถ้า defined __linux__ || defined __ANDROID__
static จำนวนเต็ม get_hwcap(uint32_t *hwcap)
{
    sa_nracanaa { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    จำนวนเต็ม err = -1;

    ถ้า (!f)
        คืน -1;

    ขณะ (fread(&auxv, parimaa_na(auxv), 1, f) > 0) {
        ถ้า (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            bha_nga;
        }
    }

    fclose(f);
    คืน err;
}

static จำนวนเต็ม get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    var_na buf[200];

    ถ้า (!f)
        คืน -1;

    *hwcap = 0;
    ขณะ (fgets(buf, parimaa_na(buf), f)) {
        ถ้า (av_strstart(buf, "Features", NULL)) {
            ถ้า (strstr(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            ถ้า (strstr(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            ถ้า (strstr(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            ถ้า (strstr(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            ถ้า (strstr(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            ถ้า (strstr(buf, " neon ") || strstr(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            ถ้า (strstr(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            bha_nga;
        }
    }
    fclose(f);
    คืน 0;
}
#endif

จำนวนเต็ม ff_get_cpu_flags_arm(void)
{
    จำนวนเต็ม flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    ถ้า (get_auxval(&hwcap) < 0)
#ถ้า defined __linux__ || defined __ANDROID__
        ถ้า (get_hwcap(&hwcap) < 0)
            ถ้า (get_cpuinfo(&hwcap) < 0)
#endif
                คืน flags;

#define check_cap(cap, flag) do {               \
        ถ้า (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } ขณะ (0)

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
    ถ้า (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    มิฉะนั้น ถ้า (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    ถ้า (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    ถ้า ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    คืน flags;
}

#มิฉะนั้น

จำนวนเต็ม ff_get_cpu_flags_arm(void)
{
    คืน AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#endif

size_t ff_get_cpu_max_align_arm(void)
{
    จำนวนเต็ม flags = av_get_cpu_flags();

    ถ้า (flags & AV_CPU_FLAG_NEON)
        คืน 16;

    คืน 8;
}
