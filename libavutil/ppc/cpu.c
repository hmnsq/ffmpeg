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
#ຖ້າ HAVE_UNISTD_H
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
ຈຳນວນເຕັມ ff_get_cpu_flags_ppc(void)
{
#ຖ້າ HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    extern sa_nracanaa ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    ຖ້າ (result == VECTORTYPE_ALTIVEC)
        ສົ່ງຄືນ AV_CPU_FLAG_ALTIVEC;
    ສົ່ງຄືນ 0;
#elif HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ຈຳນວນເຕັມ flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    ຖ້າ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    ຖ້າ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    ຖ້າ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ສົ່ງຄືນ flags;
#elif defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#ຖ້າ defined(__NetBSD__) || defined(__OpenBSD__)
    ຈຳນວນເຕັມ sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#ບໍ່ດັ່ງນັ້ນ
    ຈຳນວນເຕັມ sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    ຈຳນວນເຕັມ has_vu = 0;
    size_t len = parimaa_na(has_vu);
    ຈຳນວນເຕັມ err;

    err = sysctl(sels, 2, &has_vu, &len, NULL, 0);

    ຖ້າ (err == 0)
        ສົ່ງຄືນ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ສົ່ງຄືນ 0;
#elif defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    ຈຳນວນເຕັມ i, ret = 0;
    ຈຳນວນເຕັມ fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t count;

    ຖ້າ (fd < 0)
        ສົ່ງຄືນ 0;

    ໃນຂະນະທີ່ ((count = read(fd, buf, parimaa_na(buf))) > 0) {
        ສຳລັບ (i = 0; i < count / parimaa_na(*buf); i += 2) {
            ຖ້າ (buf[i] == AT_NULL)
                goto out;
            ຖ້າ (buf[i] == AT_HWCAP) {
                ຖ້າ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                ຖ້າ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                ຖ້າ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            ບໍ່ດັ່ງນັ້ນ ຖ້າ (buf[i] == AT_HWCAP2) {
                ຖ້າ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    ສົ່ງຄືນ ret;
#ບໍ່ດັ່ງນັ້ນ
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ສົ່ງຄືນ AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    ສົ່ງຄືນ 0;
}

size_t ff_get_cpu_max_align_ppc(void)
{
    ຈຳນວນເຕັມ flags = av_get_cpu_flags();

    ຖ້າ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ສົ່ງຄືນ 16;

    ສົ່ງຄືນ 8;
}
