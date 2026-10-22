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

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"
#समावेश "config.h"

#घोषणा CORE_FLAG(f) \
    (AV_CPU_FLAG_ ## f * (HAVE_ ## f ## _EXTERNAL || HAVE_ ## f ## _INLINE))

#घोषणा CORE_CPU_FLAGS                          \
    (CORE_FLAG(ARMV5TE) |                       \
     CORE_FLAG(ARMV6)   |                       \
     CORE_FLAG(ARMV6T2) |                       \
     CORE_FLAG(VFP)     |                       \
     CORE_FLAG(VFPV3)   |                       \
     CORE_FLAG(NEON))

#अगर defined __linux__ || defined __ANDROID__ || HAVE_ELF_AUX_INFO

#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश "libavutil/avstring.h"

#अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#समावेश <sys/auxv.h>
#पूर्ण_अगर

#अगर_अघोषित AT_HWCAP
#घोषणा AT_HWCAP        16
#पूर्ण_अगर

/* Relevant HWCAP values from <sys/auxv.h> that includes <bits/hwcap.h> */
#अगर_अघोषित HWCAP_ARM_VFP
#घोषणा HWCAP_ARM_VFP     (1 << 6)
#पूर्ण_अगर
#अगर_अघोषित HWCAP_ARM_EDSP
#घोषणा HWCAP_ARM_EDSP    (1 << 7)
#पूर्ण_अगर
#अगर_अघोषित HWCAP_ARM_THUMBEE
#घोषणा HWCAP_ARM_THUMBEE (1 << 11)
#पूर्ण_अगर
#अगर_अघोषित HWCAP_ARM_NEON
#घोषणा HWCAP_ARM_NEON    (1 << 12)
#पूर्ण_अगर
#अगर_अघोषित HWCAP_ARM_VFPv3
#घोषणा HWCAP_ARM_VFPv3   (1 << 13)
#पूर्ण_अगर
#अगर_अघोषित HWCAP_ARM_TLS
#घोषणा HWCAP_ARM_TLS     (1 << 15)
#पूर्ण_अगर

अटल पूर्णांक get_auxval(uint32_t *hwcap)
{
#अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    अचिन्हित दीर्घ ret = ff_getauxval(AT_HWCAP);
    अगर (ret == 0)
        वापस -1;
    *hwcap = ret;
    वापस 0;
#अन्यथा
    वापस -1;
#पूर्ण_अगर
}

#अगर defined __linux__ || defined __ANDROID__
अटल पूर्णांक get_hwcap(uint32_t *hwcap)
{
    काष्ठा { uint32_t a_type; uint32_t a_val; } auxv;
    खाता *f = ख_खोलो("/proc/self/auxv", "r");
    पूर्णांक err = -1;

    अगर (!f)
        वापस -1;

    जबतक (ख_पढ़ो(&auxv, माप(auxv), 1, f) > 0) {
        अगर (auxv.a_type == AT_HWCAP) {
            *hwcap = auxv.a_val;
            err = 0;
            अवरोध;
        }
    }

    ख_बंद(f);
    वापस err;
}

अटल पूर्णांक get_cpuinfo(uint32_t *hwcap)
{
    खाता *f = ख_खोलो("/proc/cpuinfo", "r");
    अक्षर buf[200];

    अगर (!f)
        वापस -1;

    *hwcap = 0;
    जबतक (ख_माला_लो(buf, माप(buf), f)) {
        अगर (av_strstart(buf, "Features", शून्य)) {
            अगर (म_माला(buf, " edsp "))
                *hwcap |= HWCAP_ARM_EDSP;
            अगर (म_माला(buf, " tls "))
                *hwcap |= HWCAP_ARM_TLS;
            अगर (म_माला(buf, " thumbee "))
                *hwcap |= HWCAP_ARM_THUMBEE;
            अगर (म_माला(buf, " vfp "))
                *hwcap |= HWCAP_ARM_VFP;
            अगर (म_माला(buf, " vfpv3 "))
                *hwcap |= HWCAP_ARM_VFPv3;
            अगर (म_माला(buf, " neon ") || म_माला(buf, " asimd "))
                *hwcap |= HWCAP_ARM_NEON;
            अगर (म_माला(buf, " fp ")) // Listed on 64 bit ARMv8 kernels
                *hwcap |= HWCAP_ARM_VFP | HWCAP_ARM_VFPv3;
            अवरोध;
        }
    }
    ख_बंद(f);
    वापस 0;
}
#पूर्ण_अगर

पूर्णांक ff_get_cpu_flags_arm(व्योम)
{
    पूर्णांक flags = CORE_CPU_FLAGS;
    uint32_t hwcap;

    अगर (get_auxval(&hwcap) < 0)
#अगर defined __linux__ || defined __ANDROID__
        अगर (get_hwcap(&hwcap) < 0)
            अगर (get_cpuinfo(&hwcap) < 0)
#पूर्ण_अगर
                वापस flags;

#घोषणा check_cap(cap, flag) करो {               \
        अगर (hwcap & HWCAP_ARM_ ## cap)          \
            flags |= AV_CPU_FLAG_ ## flag;      \
    } जबतक (0)

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
    अगर (flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON))
        flags |= AV_CPU_FLAG_ARMV6T2;
    अन्यथा अगर (flags & (AV_CPU_FLAG_ARMV6T2 | AV_CPU_FLAG_ARMV6))
    /* Some functions use the 'setend' instruction which is deprecated on ARMv8
     * and serializing on some ARMv7 cores. This ensures such functions
     * are only enabled on ARMv6. */
        flags |= AV_CPU_FLAG_SETEND;

    अगर (flags & AV_CPU_FLAG_ARMV6T2)
        flags |= AV_CPU_FLAG_ARMV6;

    /* set the virtual VFPv2 vector mode flag */
    अगर ((flags & AV_CPU_FLAG_VFP) && !(flags & (AV_CPU_FLAG_VFPV3 | AV_CPU_FLAG_NEON)))
        flags |= AV_CPU_FLAG_VFP_VM;

    वापस flags;
}

#अन्यथा

पूर्णांक ff_get_cpu_flags_arm(व्योम)
{
    वापस AV_CPU_FLAG_ARMV5TE * HAVE_ARMV5TE |
           AV_CPU_FLAG_ARMV6   * HAVE_ARMV6   |
           AV_CPU_FLAG_ARMV6T2 * HAVE_ARMV6T2 |
           AV_CPU_FLAG_VFP     * HAVE_VFP     |
           AV_CPU_FLAG_VFPV3   * HAVE_VFPV3   |
           AV_CPU_FLAG_NEON    * HAVE_NEON    |
           AV_CPU_FLAG_SETEND  * !(HAVE_NEON | HAVE_VFPV3);
}

#पूर्ण_अगर

माप_प्रकार ff_get_cpu_max_align_arm(व्योम)
{
    पूर्णांक flags = av_get_cpu_flags();

    अगर (flags & AV_CPU_FLAG_NEON)
        वापस 16;

    वापस 8;
}
