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
#якщо HAVE_UNISTD_H
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
ціле ff_get_cpu_flags_ppc(void)
{
#якщо HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    extern struct ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    якщо (result == VECTORTYPE_ALTIVEC)
        повернути AV_CPU_FLAG_ALTIVEC;
    повернути 0;
#elif HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ціле flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    якщо (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    якщо (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    якщо (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    повернути flags;
#elif defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#якщо defined(__NetBSD__) || defined(__OpenBSD__)
    ціле sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#інакше
    ціле sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    ціле has_vu = 0;
    size_t len = sizeof(has_vu);
    ціле err;

    err = sysctl(sels, 2, &has_vu, &len, NULL, 0);

    якщо (err == 0)
        повернути has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    повернути 0;
#elif defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    ціле i, ret = 0;
    ціле fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t count;

    якщо (fd < 0)
        повернути 0;

    поки ((count = read(fd, buf, sizeof(buf))) > 0) {
        для (i = 0; i < count / sizeof(*buf); i += 2) {
            якщо (buf[i] == AT_NULL)
                goto out;
            якщо (buf[i] == AT_HWCAP) {
                якщо (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                якщо (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                якщо (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            інакше якщо (buf[i] == AT_HWCAP2) {
                якщо (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    повернути ret;
#інакше
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    повернути AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    повернути 0;
}

size_t ff_get_cpu_max_align_ppc(void)
{
    ціле flags = av_get_cpu_flags();

    якщо (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        повернути 16;

    повернути 8;
}
