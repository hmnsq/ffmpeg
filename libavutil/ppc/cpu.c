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

#അന്തര്ഭാവ "config.h"

#ifdef __APPLE__
#അന്തര്ഭാവ <sys/sysctl.h>
#അല്ലെങ്കിലെങ്കിൽ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#അന്തര്ഭാവ <machine/cpu.h>
#endif
#അന്തര്ഭാവ <sys/auxv.h>
#അല്ലെങ്കിലെങ്കിൽ defined(__linux__)
#അന്തര്ഭാവ <asm/cputable.h>
#അന്തര്ഭാവ <linux/auxvec.h>
#അന്തര്ഭാവ <fcntl.h>
#എങ്കിൽ HAVE_UNISTD_H
#അന്തര്ഭാവ <unistd.h>
#endif
#അല്ലെങ്കിലെങ്കിൽ defined(__NetBSD__) || defined(__OpenBSD__)
#അന്തര്ഭാവ <sys/types.h>
#അന്തര്ഭാവ <sys/sysctl.h>
#അന്തര്ഭാവ <machine/cpu.h>
#അല്ലെങ്കിലെങ്കിൽ defined(__AMIGAOS4__)
#അന്തര്ഭാവ <exec/exec.h>
#അന്തര്ഭാവ <interfaces/exec.h>
#അന്തര്ഭാവ <proto/exec.h>
#endif /* __APPLE__ */

#അന്തര്ഭാവ "libavutil/avassert.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/cpu_internal.h"

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
പൂർണ്ണസംഖ്യ ff_get_cpu_flags_ppc(ശൂന്യം)
{
#എങ്കിൽ HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    ബാഹ്യ ഘടന ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    എങ്കിൽ (result == VECTORTYPE_ALTIVEC)
        തിരികെ AV_CPU_FLAG_ALTIVEC;
    തിരികെ 0;
#അല്ലെങ്കിലെങ്കിൽ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    പൂർണ്ണസംഖ്യ flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    എങ്കിൽ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    എങ്കിൽ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    എങ്കിൽ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    തിരികെ flags;
#അല്ലെങ്കിലെങ്കിൽ defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#എങ്കിൽ defined(__NetBSD__) || defined(__OpenBSD__)
    പൂർണ്ണസംഖ്യ sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#അല്ലെങ്കിൽ
    പൂർണ്ണസംഖ്യ sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    പൂർണ്ണസംഖ്യ has_vu = 0;
    size_t len = വലുപ്പം(has_vu);
    പൂർണ്ണസംഖ്യ err;

    err = sysctl(sels, 2, &has_vu, &len, ശൂന്യ, 0);

    എങ്കിൽ (err == 0)
        തിരികെ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    തിരികെ 0;
#അല്ലെങ്കിലെങ്കിൽ defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    പൂർണ്ണസംഖ്യ i, ret = 0;
    പൂർണ്ണസംഖ്യ fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t എണ്ണം;

    എങ്കിൽ (fd < 0)
        തിരികെ 0;

    ആകുമ്പോൾ ((എണ്ണം = പഠ(fd, buf, വലുപ്പം(buf))) > 0) {
        വേണ്ടി (i = 0; i < എണ്ണം / വലുപ്പം(*buf); i += 2) {
            എങ്കിൽ (buf[i] == AT_NULL)
                പോകുക out;
            എങ്കിൽ (buf[i] == AT_HWCAP) {
                എങ്കിൽ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                എങ്കിൽ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                എങ്കിൽ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            അല്ലെങ്കിൽ എങ്കിൽ (buf[i] == AT_HWCAP2) {
                എങ്കിൽ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    തിരികെ ret;
#അല്ലെങ്കിൽ
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    തിരികെ AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    തിരികെ 0;
}

size_t ff_get_cpu_max_align_ppc(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ flags = av_get_cpu_flags();

    എങ്കിൽ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        തിരികെ 16;

    തിരികെ 8;
}
