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

#अन्तर्भाव "config.h"

#ifdef __APPLE__
#अन्तर्भाव <sys/sysctl.h>
#नोचेद्यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#अन्तर्भाव <machine/cpu.h>
#endif
#अन्तर्भाव <sys/auxv.h>
#नोचेद्यदि defined(__linux__)
#अन्तर्भाव <asm/cputable.h>
#अन्तर्भाव <linux/auxvec.h>
#अन्तर्भाव <fcntl.h>
#जइ HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#नोचेद्यदि defined(__NetBSD__) || defined(__OpenBSD__)
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/sysctl.h>
#अन्तर्भाव <machine/cpu.h>
#नोचेद्यदि defined(__AMIGAOS4__)
#अन्तर्भाव <exec/exec.h>
#अन्तर्भाव <interfaces/exec.h>
#अन्तर्भाव <proto/exec.h>
#endif /* __APPLE__ */

#अन्तर्भाव "libavutil/avassert.h"
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/cpu_internal.h"

#ifndef AT_HWCAP
#define AT_HWCAP             16
#endif
#ifndef AT_HWCAP2
#define AT_HWCAP2            26
#endif

#define HWCAP_PPC_VSX        (1U << 7)
#define HWCAP_PPC_ALTIVEC    (1U << 28)
#define HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
पूर्णाङ्क ff_get_cpu_flags_ppc(शून्य)
{
#जइ HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    बाह्य संरचना ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    जइ (result == VECTORTYPE_ALTIVEC)
        प्रत्यागम AV_CPU_FLAG_ALTIVEC;
    प्रत्यागम 0;
#नोचेद्यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    पूर्णाङ्क flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    जइ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    जइ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    जइ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    प्रत्यागम flags;
#नोचेद्यदि defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#जइ defined(__NetBSD__) || defined(__OpenBSD__)
    पूर्णाङ्क sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#अण्णहा
    पूर्णाङ्क sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    पूर्णाङ्क has_vu = 0;
    size_t len = परिमाण(has_vu);
    पूर्णाङ्क err;

    err = sysctl(sels, 2, &has_vu, &len, रिक्त, 0);

    जइ (err == 0)
        प्रत्यागम has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    प्रत्यागम 0;
#नोचेद्यदि defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    पूर्णाङ्क i, ret = 0;
    पूर्णाङ्क fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t गणनम्;

    जइ (fd < 0)
        प्रत्यागम 0;

    जाव ((गणनम् = पठ(fd, buf, परिमाण(buf))) > 0) {
        प्रति (i = 0; i < गणनम् / परिमाण(*buf); i += 2) {
            जइ (buf[i] == AT_NULL)
                गच्छ out;
            जइ (buf[i] == AT_HWCAP) {
                जइ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                जइ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                जइ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            अण्णहा जइ (buf[i] == AT_HWCAP2) {
                जइ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    प्रत्यागम ret;
#अण्णहा
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    प्रत्यागम AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    प्रत्यागम 0;
}

size_t ff_get_cpu_max_align_ppc(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    जइ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        प्रत्यागम 16;

    प्रत्यागम 8;
}
