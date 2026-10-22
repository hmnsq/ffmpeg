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

#অন্তর্ভাব "config.h"

#ifdef __APPLE__
#অন্তর্ভাব <sys/sysctl.h>
#নতুবা_যদি HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#অন্তর্ভাব <machine/cpu.h>
#endif
#অন্তর্ভাব <sys/auxv.h>
#নতুবা_যদি defined(__linux__)
#অন্তর্ভাব <asm/cputable.h>
#অন্তর্ভাব <linux/auxvec.h>
#অন্তর্ভাব <fcntl.h>
#যদি HAVE_UNISTD_H
#অন্তর্ভাব <unistd.h>
#endif
#নতুবা_যদি defined(__NetBSD__) || defined(__OpenBSD__)
#অন্তর্ভাব <sys/types.h>
#অন্তর্ভাব <sys/sysctl.h>
#অন্তর্ভাব <machine/cpu.h>
#নতুবা_যদি defined(__AMIGAOS4__)
#অন্তর্ভাব <exec/exec.h>
#অন্তর্ভাব <interfaces/exec.h>
#অন্তর্ভাব <proto/exec.h>
#endif /* __APPLE__ */

#অন্তর্ভাব "libavutil/avassert.h"
#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/cpu_internal.h"

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
পূর্ণসংখ্যা ff_get_cpu_flags_ppc(শূন্য)
{
#যদি HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG ফলাফল = 0;
    বাহ্যিক কাঠামো ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &ফলাফল, TAG_DONE);
    যদি (ফলাফল == VECTORTYPE_ALTIVEC)
        ফেরত AV_CPU_FLAG_ALTIVEC;
    ফেরত 0;
#নতুবা_যদি HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    পূর্ণসংখ্যা flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    যদি (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    যদি (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    যদি (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ফেরত flags;
#নতুবা_যদি defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#যদি defined(__NetBSD__) || defined(__OpenBSD__)
    পূর্ণসংখ্যা sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#অন্যথা
    পূর্ণসংখ্যা sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    পূর্ণসংখ্যা has_vu = 0;
    size_t len = আকার(has_vu);
    পূর্ণসংখ্যা err;

    err = sysctl(sels, 2, &has_vu, &len, ফাঁকা, 0);

    যদি (err == 0)
        ফেরত has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ফেরত 0;
#নতুবা_যদি defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    পূর্ণসংখ্যা i, ret = 0;
    পূর্ণসংখ্যা fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t গুনতি;

    যদি (fd < 0)
        ফেরত 0;

    যখন ((গুনতি = পঠ(fd, buf, আকার(buf))) > 0) {
        জন্য (i = 0; i < গুনতি / আকার(*buf); i += 2) {
            যদি (buf[i] == AT_NULL)
                যাও out;
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
    ফেরত ret;
#অন্যথা
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ফেরত AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    ফেরত 0;
}

size_t ff_get_cpu_max_align_ppc(শূন্য)
{
    পূর্ণসংখ্যা flags = av_get_cpu_flags();

    যদি (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ফেরত 16;

    ফেরত 8;
}
