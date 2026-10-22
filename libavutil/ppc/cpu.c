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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ifdef __APPLE__
#ଅନ୍ତର୍ଭାଵ <sys/sysctl.h>
#ନଚେତଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#ଅନ୍ତର୍ଭାଵ <machine/cpu.h>
#endif
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>
#ନଚେତଯଦି defined(__linux__)
#ଅନ୍ତର୍ଭାଵ <asm/cputable.h>
#ଅନ୍ତର୍ଭାଵ <linux/auxvec.h>
#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif
#ନଚେତଯଦି defined(__NetBSD__) || defined(__OpenBSD__)
#ଅନ୍ତର୍ଭାଵ <sys/types.h>
#ଅନ୍ତର୍ଭାଵ <sys/sysctl.h>
#ଅନ୍ତର୍ଭାଵ <machine/cpu.h>
#ନଚେତଯଦି defined(__AMIGAOS4__)
#ଅନ୍ତର୍ଭାଵ <exec/exec.h>
#ଅନ୍ତର୍ଭାଵ <interfaces/exec.h>
#ଅନ୍ତର୍ଭାଵ <proto/exec.h>
#endif /* __APPLE__ */

#ଅନ୍ତର୍ଭାଵ "libavutil/avassert.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu_internal.h"

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
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_ppc(ଶୂନ୍ୟ)
{
#ଯଦି HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    ବାହ୍ୟ ସଂରଚନା ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    ଯଦି (result == VECTORTYPE_ALTIVEC)
        ଫେରନ୍ତୁ AV_CPU_FLAG_ALTIVEC;
    ଫେରନ୍ତୁ 0;
#ନଚେତଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    ଯଦି (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    ଯଦି (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    ଯଦି (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ଫେରନ୍ତୁ flags;
#ନଚେତଯଦି defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#ଯଦି defined(__NetBSD__) || defined(__OpenBSD__)
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#ଅନ୍ୟଥା
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା has_vu = 0;
    size_t len = ଆକାର(has_vu);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    err = sysctl(sels, 2, &has_vu, &len, ଖାଲି, 0);

    ଯଦି (err == 0)
        ଫେରନ୍ତୁ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ଫେରନ୍ତୁ 0;
#ନଚେତଯଦି defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t ଗଣନା_2;

    ଯଦି (fd < 0)
        ଫେରନ୍ତୁ 0;

    ଯେତେବେଳେ ((ଗଣନା_2 = ପଠ(fd, buf, ଆକାର(buf))) > 0) {
        ପାଇଁ (i = 0; i < ଗଣନା_2 / ଆକାର(*buf); i += 2) {
            ଯଦି (buf[i] == AT_NULL)
                ଯାଅ out;
            ଯଦି (buf[i] == AT_HWCAP) {
                ଯଦି (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                ଯଦି (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                ଯଦି (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            ଅନ୍ୟଥା ଯଦି (buf[i] == AT_HWCAP2) {
                ଯଦି (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    ଫେରନ୍ତୁ ret;
#ଅନ୍ୟଥା
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ଫେରନ୍ତୁ AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    ଫେରନ୍ତୁ 0;
}

size_t ff_get_cpu_max_align_ppc(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ଫେରନ୍ତୁ 16;

    ଫେରନ୍ତୁ 8;
}
