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
#किंवाजर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#अन्तर्भाव <machine/cpu.h>
#endif
#अन्तर्भाव <sys/auxv.h>
#किंवाजर defined(__linux__)
#अन्तर्भाव <asm/cputable.h>
#अन्तर्भाव <linux/auxvec.h>
#अन्तर्भाव <fcntl.h>
#जर HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#किंवाजर defined(__NetBSD__) || defined(__OpenBSD__)
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/sysctl.h>
#अन्तर्भाव <machine/cpu.h>
#किंवाजर defined(__AMIGAOS4__)
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
पूर्णांक ff_get_cpu_flags_ppc(शून्य)
{
#जर HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    बाह्य संरचना ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    जर (result == VECTORTYPE_ALTIVEC)
        परत AV_CPU_FLAG_ALTIVEC;
    परत 0;
#किंवाजर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    पूर्णांक flags = 0;

    अचिन्हित दीर्घ hwcap = ff_getauxval(AT_HWCAP);
    अचिन्हित दीर्घ hwcap2 = ff_getauxval(AT_HWCAP2);

    जर (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    जर (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    जर (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    परत flags;
#किंवाजर defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#जर defined(__NetBSD__) || defined(__OpenBSD__)
    पूर्णांक sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#अन्यथा
    पूर्णांक sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    पूर्णांक has_vu = 0;
    माप_प्रकार len = आकार(has_vu);
    पूर्णांक err;

    err = sysctl(sels, 2, &has_vu, &len, रिक्त, 0);

    जर (err == 0)
        परत has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    परत 0;
#किंवाजर defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    पूर्णांक i, ret = 0;
    पूर्णांक fd = खोलो("/proc/self/auxv", O_RDONLY);
    अचिन्हित दीर्घ buf[64] = { 0 };
    ssize_t मोजणी;

    जर (fd < 0)
        परत 0;

    पर्यंत ((मोजणी = पठ(fd, buf, आकार(buf))) > 0) {
        साठी (i = 0; i < मोजणी / आकार(*buf); i += 2) {
            जर (buf[i] == AT_NULL)
                जा out;
            जर (buf[i] == AT_HWCAP) {
                जर (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                जर (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                जर (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            अन्यथा जर (buf[i] == AT_HWCAP2) {
                जर (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    बंद(fd);
    परत ret;
#अन्यथा
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    परत AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    परत 0;
}

माप_प्रकार ff_get_cpu_max_align_ppc(शून्य)
{
    पूर्णांक flags = av_get_cpu_flags();

    जर (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        परत 16;

    परत 8;
}
