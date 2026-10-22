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

#অন্তর্ভাৱ "config.h"

#ifdef __APPLE__
#অন্তর্ভাৱ <sys/sysctl.h>
#নোচেদ্যদি HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#অন্তর্ভাৱ <machine/cpu.h>
#endif
#অন্তর্ভাৱ <sys/auxv.h>
#নোচেদ্যদি defined(__linux__)
#অন্তর্ভাৱ <asm/cputable.h>
#অন্তর্ভাৱ <linux/auxvec.h>
#অন্তর্ভাৱ <fcntl.h>
#যদি HAVE_UNISTD_H
#অন্তর্ভাৱ <unistd.h>
#endif
#নোচেদ্যদি defined(__NetBSD__) || defined(__OpenBSD__)
#অন্তর্ভাৱ <sys/types.h>
#অন্তর্ভাৱ <sys/sysctl.h>
#অন্তর্ভাৱ <machine/cpu.h>
#নোচেদ্যদি defined(__AMIGAOS4__)
#অন্তর্ভাৱ <exec/exec.h>
#অন্তর্ভাৱ <interfaces/exec.h>
#অন্তর্ভাৱ <proto/exec.h>
#endif /* __APPLE__ */

#অন্তর্ভাৱ "libavutil/avassert.h"
#অন্তর্ভাৱ "libavutil/cpu.h"
#অন্তর্ভাৱ "libavutil/cpu_internal.h"

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
পূর্ণাঙ্ক ff_get_cpu_flags_ppc(শূন্য)
{
#যদি HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    বাহ্য সংরচনা ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    যদি (result == VECTORTYPE_ALTIVEC)
        ঘূৰাই AV_CPU_FLAG_ALTIVEC;
    ঘূৰাই 0;
#নোচেদ্যদি HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    পূর্ণাঙ্ক flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    যদি (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    যদি (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    যদি (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ঘূৰাই flags;
#নোচেদ্যদি defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#যদি defined(__NetBSD__) || defined(__OpenBSD__)
    পূর্ণাঙ্ক sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#অন্যথা
    পূর্ণাঙ্ক sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    পূর্ণাঙ্ক has_vu = 0;
    size_t len = পরিমাণ(has_vu);
    পূর্ণাঙ্ক err;

    err = sysctl(sels, 2, &has_vu, &len, রিক্ত, 0);

    যদি (err == 0)
        ঘূৰাই has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ঘূৰাই 0;
#নোচেদ্যদি defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    পূর্ণাঙ্ক i, ret = 0;
    পূর্ণাঙ্ক fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t গুনতি;

    যদি (fd < 0)
        ঘূৰাই 0;

    যেতিয়ালৈ ((গুনতি = পঠ(fd, buf, পরিমাণ(buf))) > 0) {
        বাবে (i = 0; i < গুনতি / পরিমাণ(*buf); i += 2) {
            যদি (buf[i] == AT_NULL)
                গচ্ছ out;
            যদি (buf[i] == AT_HWCAP) {
                যদি (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                যদি (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                যদি (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            অন্যথা যদি (buf[i] == AT_HWCAP2) {
                যদি (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    ঘূৰাই ret;
#অন্যথা
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ঘূৰাই AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    ঘূৰাই 0;
}

size_t ff_get_cpu_max_align_ppc(শূন্য)
{
    পূর্ণাঙ্ক flags = av_get_cpu_flags();

    যদি (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ঘূৰাই 16;

    ঘূৰাই 8;
}
