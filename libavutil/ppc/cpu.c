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

#include "config.h"

#ifdef __APPLE__
#include <sys/sysctl.h>
#elif HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#include <machine/cpu.h>
#endif
#include <sys/auxv.h>
#elif defined(__linux__)
#include <asm/cputable.h>
#include <linux/auxvec.h>
#include <fcntl.h>
#නම් HAVE_UNISTD_H
#include <unistd.h>
#endif
#elif defined(__NetBSD__) || defined(__OpenBSD__)
#include <sys/types.h>
#include <sys/sysctl.h>
#include <machine/cpu.h>
#elif defined(__AMIGAOS4__)
#include <exec/exec.h>
#include <interfaces/exec.h>
#include <proto/exec.h>
#endif /* __APPLE__ */

#include "libavutil/avassert.h"
#include "libavutil/cpu.h"
#include "libavutil/cpu_internal.h"

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
පූර්ණ_සංඛ්‍යා ff_get_cpu_flags_ppc(void)
{
#නම් HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    extern sa_nracanaa ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    නම් (result == VECTORTYPE_ALTIVEC)
        ආපසු AV_CPU_FLAG_ALTIVEC;
    ආපසු 0;
#elif HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    පූර්ණ_සංඛ්‍යා flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    නම් (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    නම් (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    නම් (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ආපසු flags;
#elif defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#නම් defined(__NetBSD__) || defined(__OpenBSD__)
    පූර්ණ_සංඛ්‍යා sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#නැතහොත්
    පූර්ණ_සංඛ්‍යා sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    පූර්ණ_සංඛ්‍යා has_vu = 0;
    size_t len = parimaa_na(has_vu);
    පූර්ණ_සංඛ්‍යා err;

    err = sysctl(sels, 2, &has_vu, &len, NULL, 0);

    නම් (err == 0)
        ආපසු has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ආපසු 0;
#elif defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    පූර්ණ_සංඛ්‍යා i, ret = 0;
    පූර්ණ_සංඛ්‍යා fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t count;

    නම් (fd < 0)
        ආපසු 0;

    අතරතුර ((count = read(fd, buf, parimaa_na(buf))) > 0) {
        සඳහා (i = 0; i < count / parimaa_na(*buf); i += 2) {
            නම් (buf[i] == AT_NULL)
                goto out;
            නම් (buf[i] == AT_HWCAP) {
                නම් (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                නම් (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                නම් (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            නැතහොත් නම් (buf[i] == AT_HWCAP2) {
                නම් (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    ආපසු ret;
#නැතහොත්
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ආපසු AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    ආපසු 0;
}

size_t ff_get_cpu_max_align_ppc(void)
{
    පූර්ණ_සංඛ්‍යා flags = av_get_cpu_flags();

    නම් (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ආපසු 16;

    ආපසු 8;
}
