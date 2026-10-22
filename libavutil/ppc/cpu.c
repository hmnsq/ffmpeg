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

#समावेश "config.h"

#अगर_घोषित __APPLE__
#समावेश <sys/sysctl.h>
#या_अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अगर_घोषित __FreeBSD__
#समावेश <machine/cpu.h>
#पूर्ण_अगर
#समावेश <sys/auxv.h>
#या_अगर defined(__linux__)
#समावेश <asm/cputable.h>
#समावेश <linux/auxvec.h>
#समावेश <fcntl.h>
#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#या_अगर defined(__NetBSD__) || defined(__OpenBSD__)
#समावेश <sys/types.h>
#समावेश <sys/sysctl.h>
#समावेश <machine/cpu.h>
#या_अगर defined(__AMIGAOS4__)
#समावेश <exec/exec.h>
#समावेश <interfaces/exec.h>
#समावेश <proto/exec.h>
#पूर्ण_अगर /* __APPLE__ */

#समावेश "libavutil/avassert.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"

#अगर_अघोषित AT_HWCAP
#घोषणा AT_HWCAP             16
#पूर्ण_अगर
#अगर_अघोषित AT_HWCAP2
#घोषणा AT_HWCAP2            26
#पूर्ण_अगर

#घोषणा HWCAP_PPC_VSX        (1U << 7)
#घोषणा HWCAP_PPC_ALTIVEC    (1U << 28)
#घोषणा HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
पूर्णांक ff_get_cpu_flags_ppc(व्योम)
{
#अगर HAVE_ALTIVEC
#अगर_घोषित __AMIGAOS4__
    ULONG परिणाम = 0;
    बाह्य काष्ठा ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &परिणाम, TAG_DONE);
    अगर (परिणाम == VECTORTYPE_ALTIVEC)
        वापस AV_CPU_FLAG_ALTIVEC;
    वापस 0;
#या_अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    पूर्णांक flags = 0;

    अचिन्हित दीर्घ hwcap = ff_getauxval(AT_HWCAP);
    अचिन्हित दीर्घ hwcap2 = ff_getauxval(AT_HWCAP2);

    अगर (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    अगर (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    अगर (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    वापस flags;
#या_अगर defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#अगर defined(__NetBSD__) || defined(__OpenBSD__)
    पूर्णांक sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#अन्यथा
    पूर्णांक sels[2] = {CTL_HW, HW_VECTORUNIT};
#पूर्ण_अगर
    पूर्णांक has_vu = 0;
    माप_प्रकार len = माप(has_vu);
    पूर्णांक err;

    err = sysctl(sels, 2, &has_vu, &len, शून्य, 0);

    अगर (err == 0)
        वापस has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    वापस 0;
#या_अगर defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    पूर्णांक i, ret = 0;
    पूर्णांक fd = खोलो("/proc/self/auxv", O_RDONLY);
    अचिन्हित दीर्घ buf[64] = { 0 };
    ssize_t गिनती;

    अगर (fd < 0)
        वापस 0;

    जबतक ((गिनती = पढ़ो(fd, buf, माप(buf))) > 0) {
        क्रम (i = 0; i < गिनती / माप(*buf); i += 2) {
            अगर (buf[i] == AT_NULL)
                जाओ out;
            अगर (buf[i] == AT_HWCAP) {
                अगर (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                अगर (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                अगर (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            अन्यथा अगर (buf[i] == AT_HWCAP2) {
                अगर (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    बंद(fd);
    वापस ret;
#अन्यथा
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    वापस AV_CPU_FLAG_ALTIVEC;
#पूर्ण_अगर /* __AMIGAOS4__ */
#पूर्ण_अगर /* HAVE_ALTIVEC */
    वापस 0;
}

माप_प्रकार ff_get_cpu_max_align_ppc(व्योम)
{
    पूर्णांक flags = av_get_cpu_flags();

    अगर (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        वापस 16;

    वापस 8;
}
