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
#अथवायदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#अन्तर्भाव <machine/cpu.h>
#endif
#अन्तर्भाव <sys/auxv.h>
#अथवायदि defined(__linux__)
#अन्तर्भाव <asm/cputable.h>
#अन्तर्भाव <linux/auxvec.h>
#अन्तर्भाव <fcntl.h>
#यदि HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#अथवायदि defined(__NetBSD__) || defined(__OpenBSD__)
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/sysctl.h>
#अन्तर्भाव <machine/cpu.h>
#अथवायदि defined(__AMIGAOS4__)
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
#यदि HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    बाह्य संरचना ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    यदि (result == VECTORTYPE_ALTIVEC)
        फर्काऊ AV_CPU_FLAG_ALTIVEC;
    फर्काऊ 0;
#अथवायदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    पूर्णाङ्क flags = 0;

    अचिन्हित दीर्घ hwcap = ff_getauxval(AT_HWCAP);
    अचिन्हित दीर्घ hwcap2 = ff_getauxval(AT_HWCAP2);

    यदि (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    यदि (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    यदि (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    फर्काऊ flags;
#अथवायदि defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#यदि defined(__NetBSD__) || defined(__OpenBSD__)
    पूर्णाङ्क sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#अन्यथा
    पूर्णाङ्क sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    पूर्णाङ्क has_vu = 0;
    माप_प्रकार len = परिमाण(has_vu);
    पूर्णाङ्क err;

    err = sysctl(sels, 2, &has_vu, &len, रिक्त, 0);

    यदि (err == 0)
        फर्काऊ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    फर्काऊ 0;
#अथवायदि defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    पूर्णाङ्क i, ret = 0;
    पूर्णाङ्क fd = खोलो("/proc/self/auxv", O_RDONLY);
    अचिन्हित दीर्घ buf[64] = { 0 };
    ssize_t गन्ती;

    यदि (fd < 0)
        फर्काऊ 0;

    जबसम्म ((गन्ती = पठ(fd, buf, परिमाण(buf))) > 0) {
        लागि (i = 0; i < गन्ती / परिमाण(*buf); i += 2) {
            यदि (buf[i] == AT_NULL)
                गच्छ out;
            यदि (buf[i] == AT_HWCAP) {
                यदि (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                यदि (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                यदि (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            अन्यथा यदि (buf[i] == AT_HWCAP2) {
                यदि (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    बंद(fd);
    फर्काऊ ret;
#अन्यथा
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    फर्काऊ AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    फर्काऊ 0;
}

माप_प्रकार ff_get_cpu_max_align_ppc(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        फर्काऊ 16;

    फर्काऊ 8;
}
