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

#تعریف_کرو CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#تعریف_کرو CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#اگر defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#شامل <stdint.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل "libavutil/avstring.h"

#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#شامل <sys/auxv.h>
#اگر_ختم

#اگر_غیر_تعریف_شدہ AT_HWCAP
#تعریف_کرو AT_HWCAP        16
#اگر_ختم

/* Relevant HWCAP values from <sys/auxv.h> that includes <bits/hwcap.h> */
#اگر_غیر_تعریف_شدہ HWCAP_ARM_VFP
#تعریف_کرو HWCAP_ARM_VFP     (1 << 6)
#اگر_ختم
#اگر_غیر_تعریف_شدہ HWCAP_ARM_EDSP
#تعریف_کرو HWCAP_ARM_EDSP    (1 << 7)
#اگر_ختم
#اگر_غیر_تعریف_شدہ HWCAP_ARM_THUMBEE
#تعریف_کرو HWCAP_ARM_THUMBEE (1 << 11)
#اگر_ختم
#اگر_غیر_تعریف_شدہ HWCAP_ARM_NEON
#تعریف_کرو HWCAP_ARM_NEON    (1 << 12)
#اگر_ختم
#اگر_غیر_تعریف_شدہ HWCAP_ARM_VFPv3
#تعریف_کرو HWCAP_ARM_VFPv3   (1 << 13)
#اگر_ختم
#اگر_غیر_تعریف_شدہ HWCAP_ARM_TLS
#تعریف_کرو HWCAP_ARM_TLS     (1 << 15)
#اگر_ختم

ساکن صحیح get_auxval(uint32_t *hwcap)
{
#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    غیرعلامتی طویل ret = ff_getauxval(AT_HWCAP);
    اگر (ret == 0)
        واپس -1;
    *hwcap = ret;
    واپس 0;
#ورنہ
    واپس -1;
#اگر_ختم
}

#اگر defined __linux__ || defined __ANDROID__
ساکن صحیح get_hwcap(uint32_t *hwcap)
{
    ساخت { uint32_t a_type; uint32_t a_val; } auxv;
    FILE *f = fopen("/proc/self/auxv", "r");
    صحیح err = -1;

    اگر (!f)
        واپس -1;

    جب (fread(&auxv, حجم(auxv), 1, f) > 0) {
        اگر (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            توڑو;
        }
    }

    fclose(f);
    واپس err;
}

ساکن صحیح get_cpuinfo(uint32_t *hwcap)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    حرف buf[200];

    اگر (!f)
        واپس -1;

    *hwcap = 0;
    جب (fgets(buf, حجم(buf), f)) {
        اگر (av_strstart(buf, "Features", تہی)) {
            اگر (لڑی_تلاش(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            اگر (لڑی_تلاش(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            اگر (لڑی_تلاش(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            اگر (لڑی_تلاش(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            اگر (لڑی_تلاش(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            اگر (لڑی_تلاش(buf, " neon ") || لڑی_تلاش(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            اگر (لڑی_تلاش(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            توڑو;
        }
    }
    fclose(f);
    واپس 0;
}
#اگر_ختم

صحیح ff_get_cpu_flags_arm(خالی)
{
    صحیح flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    اگر (get_auxval(&hwcap) < 0)
#اگر defined __linux__ || defined __ANDROID__
        اگر (get_hwcap(&hwcap) < 0)
            اگر (get_cpuinfo(&hwcap) < 0)
#اگر_ختم
                واپس flags;

#تعریف_کرو check_cap(cap, flag) کرو {               \
        اگر (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } جب (0)

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
    اگر (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    ورنہ اگر (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    اگر (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    اگر ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    واپس flags;
}

#ورنہ

صحیح ff_get_cpu_flags_arm(خالی)
{
    واپس AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#اگر_ختم

size_t ff_get_cpu_max_align_arm(خالی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_NEON)
        واپس 16;

    واپس 8;
}
