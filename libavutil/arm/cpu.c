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

#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu_internal.h"
#ଅନ୍ତର୍ଭାଵ "config.h"

#define CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#define CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#ଯଦି defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ "libavutil/avstring.h"

#ଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>
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

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_auxval(uint32_t *hwcap)
{
#ଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    unsigned long ret = ff_getauxval(AT_HWCAP);
    ଯଦି (ret == 0)
        ଫେରନ୍ତୁ -1;
    *hwcap = ret;
    ଫେରନ୍ତୁ 0;
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ -1;
#endif
}

#ଯଦି defined __linux__ || defined __ANDROID__
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_hwcap(uint32_t *hwcap)
{
    ସଂରଚନା { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = -1;

    ଯଦି (!f)
        ଫେରନ୍ତୁ -1;

    ଯେତେବେଳେ (fread(&auxv, ଆକାର(auxv), 1, f) > 0) {
        ଯଦି (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            ଭାଙ୍ଗ;
        }
    }

    fclose(f);
    ଫେରନ୍ତୁ err;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ଅକ୍ଷର buf[200];

    ଯଦି (!f)
        ଫେରନ୍ତୁ -1;

    *hwcap = 0;
    ଯେତେବେଳେ (fgets(buf, ଆକାର(buf), f)) {
        ଯଦି (av_strstart(buf, "Features", ଖାଲି)) {
            ଯଦି (strstr(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            ଯଦି (strstr(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            ଯଦି (strstr(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            ଯଦି (strstr(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            ଯଦି (strstr(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            ଯଦି (strstr(buf, " neon ") || strstr(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            ଯଦି (strstr(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            ଭାଙ୍ଗ;
        }
    }
    fclose(f);
    ଫେରନ୍ତୁ 0;
}
#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_arm(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    ଯଦି (get_auxval(&hwcap) < 0)
#ଯଦି defined __linux__ || defined __ANDROID__
        ଯଦି (get_hwcap(&hwcap) < 0)
            ଯଦି (get_cpuinfo(&hwcap) < 0)
#endif
                ଫେରନ୍ତୁ flags;

#define check_cap(cap, flag) କର {               \
        ଯଦି (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } ଯେତେବେଳେ (0)

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
    ଯଦି (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    ଅନ୍ୟଥା ଯଦି (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    ଯଦି (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    ଯଦି ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    ଫେରନ୍ତୁ flags;
}

#ଅନ୍ୟଥା

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_arm(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#endif

size_t ff_get_cpu_max_align_arm(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & AV_CPU_FLAG_NEON)
        ଫେରନ୍ତୁ 16;

    ଫେରନ୍ତୁ 8;
}
