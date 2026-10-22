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

#అన్తర్భావ "config.h"

#నిర్వచితమైతే __APPLE__
#అన్తర్భావ <sys/sysctl.h>
#లేదావేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#నిర్వచితమైతే __FreeBSD__
#అన్తర్భావ <machine/cpu.h>
#అయితే_ముగింపు
#అన్తర్భావ <sys/auxv.h>
#లేదావేళ defined(__linux__)
#అన్తర్భావ <asm/cputable.h>
#అన్తర్భావ <linux/auxvec.h>
#అన్తర్భావ <fcntl.h>
#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#లేదావేళ defined(__NetBSD__) || defined(__OpenBSD__)
#అన్తర్భావ <sys/types.h>
#అన్తర్భావ <sys/sysctl.h>
#అన్తర్భావ <machine/cpu.h>
#లేదావేళ defined(__AMIGAOS4__)
#అన్తర్భావ <exec/exec.h>
#అన్తర్భావ <interfaces/exec.h>
#అన్తర్భావ <proto/exec.h>
#అయితే_ముగింపు /* __APPLE__ */

#అన్తర్భావ "libavutil/avassert.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"

#నిర్వచితం_కాకపోతే AT_HWCAP
#నిర్వచించు AT_HWCAP             16
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే AT_HWCAP2
#నిర్వచించు AT_HWCAP2            26
#అయితే_ముగింపు

#నిర్వచించు HWCAP_PPC_VSX        (1U << 7)
#నిర్వచించు HWCAP_PPC_ALTIVEC    (1U << 28)
#నిర్వచించు HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
పూర్ణాంకం ff_get_cpu_flags_ppc(శూన్య)
{
#ఒకవేళ HAVE_ALTIVEC
#నిర్వచితమైతే __AMIGAOS4__
    ULONG ఫలితం = 0;
    బాహ్య నిర్మాణం ExecIFace *IExec;

    IExec->Get_CPUInfo_ట్యాగులు(GCIT_సదిశ_Unit, &ఫలితం, ట్యాగ్_పూర్తి);
    ఒకవేళ (ఫలితం == VECTORTYPE_ALTIVEC)
        తిరిగి AV_CPU_FLAG_ALTIVEC;
    తిరిగి 0;
#లేదావేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    పూర్ణాంకం flags = 0;

    గుర్తులేని దీర్ఘ hwcap = ff_getauxval(AT_HWCAP);
    గుర్తులేని దీర్ఘ hwcap2 = ff_getauxval(AT_HWCAP2);

    ఒకవేళ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    ఒకవేళ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    ఒకవేళ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    తిరిగి flags;
#లేదావేళ defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#ఒకవేళ defined(__NetBSD__) || defined(__OpenBSD__)
    పూర్ణాంకం sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#లేకపోతే
    పూర్ణాంకం sels[2] = {CTL_HW, HW_VECTORUNIT};
#అయితే_ముగింపు
    పూర్ణాంకం has_vu = 0;
    size_t len = పరిమాణం(has_vu);
    పూర్ణాంకం err;

    err = sysctl(sels, 2, &has_vu, &len, ఖాళీ, 0);

    ఒకవేళ (err == 0)
        తిరిగి has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    తిరిగి 0;
#లేదావేళ defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    పూర్ణాంకం i, ret = 0;
    పూర్ణాంకం fd = open("/proc/self/auxv", O_RDONLY);
    గుర్తులేని దీర్ఘ buf[64] = { 0 };
    ssize_t లెక్క;

    ఒకవేళ (fd < 0)
        తిరిగి 0;

    అయితే ((లెక్క = పఠ(fd, buf, పరిమాణం(buf))) > 0) {
        కొరకు (i = 0; i < లెక్క / పరిమాణం(*buf); i += 2) {
            ఒకవేళ (buf[i] == AT_NULL)
                వెళ్ళు బహిర్గతం;
            ఒకవేళ (buf[i] == AT_HWCAP) {
                ఒకవేళ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                ఒకవేళ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                ఒకవేళ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            లేకపోతే ఒకవేళ (buf[i] == AT_HWCAP2) {
                ఒకవేళ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

బహిర్గతం:
    close(fd);
    తిరిగి ret;
#లేకపోతే
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    తిరిగి AV_CPU_FLAG_ALTIVEC;
#అయితే_ముగింపు /* __AMIGAOS4__ */
#అయితే_ముగింపు /* HAVE_ALTIVEC */
    తిరిగి 0;
}

size_t ff_get_cpu_max_align_ppc(శూన్య)
{
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        తిరిగి 16;

    తిరిగి 8;
}
