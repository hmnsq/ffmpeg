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

#ಅನ್ತರ್ಭಾವ "config.h"

#ifdef __APPLE__
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>
#ನೋಚೇದ್ಯದಿ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#ಅನ್ತರ್ಭಾವ <machine/cpu.h>
#endif
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ನೋಚೇದ್ಯದಿ defined(__linux__)
#ಅನ್ತರ್ಭಾವ <asm/cputable.h>
#ಅನ್ತರ್ಭಾವ <linux/auxvec.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಯದಿ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif
#ನೋಚೇದ್ಯದಿ defined(__NetBSD__) || defined(__OpenBSD__)
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>
#ಅನ್ತರ್ಭಾವ <machine/cpu.h>
#ನೋಚೇದ್ಯದಿ defined(__AMIGAOS4__)
#ಅನ್ತರ್ಭಾವ <exec/exec.h>
#ಅನ್ತರ್ಭಾವ <interfaces/exec.h>
#ಅನ್ತರ್ಭಾವ <proto/exec.h>
#endif /* __APPLE__ */

#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"

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
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_ppc(ಶೂನ್ಯ)
{
#ಯದಿ HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    ಬಾಹ್ಯ ಸಂರಚನಾ ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    ಯದಿ (result == VECTORTYPE_ALTIVEC)
        ಪ್ರತ್ಯಾಗಮ AV_CPU_FLAG_ALTIVEC;
    ಪ್ರತ್ಯಾಗಮ 0;
#ನೋಚೇದ್ಯದಿ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ಪೂರ್ಣಾಙ್ಕ flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    ಯದಿ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    ಯದಿ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    ಯದಿ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ಪ್ರತ್ಯಾಗಮ flags;
#ನೋಚೇದ್ಯದಿ defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#ಯದಿ defined(__NetBSD__) || defined(__OpenBSD__)
    ಪೂರ್ಣಾಙ್ಕ sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#ಅನ್ಯಥಾ
    ಪೂರ್ಣಾಙ್ಕ sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    ಪೂರ್ಣಾಙ್ಕ has_vu = 0;
    size_t len = ಪರಿಮಾಣ(has_vu);
    ಪೂರ್ಣಾಙ್ಕ err;

    err = sysctl(sels, 2, &has_vu, &len, ರಿಕ್ತ, 0);

    ಯದಿ (err == 0)
        ಪ್ರತ್ಯಾಗಮ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ಪ್ರತ್ಯಾಗಮ 0;
#ನೋಚೇದ್ಯದಿ defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    ಪೂರ್ಣಾಙ್ಕ i, ret = 0;
    ಪೂರ್ಣಾಙ್ಕ fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t ಎಣಿಕೆ;

    ಯದಿ (fd < 0)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯಾವತ್ ((ಎಣಿಕೆ = ಪಠ(fd, buf, ಪರಿಮಾಣ(buf))) > 0) {
        ಪ್ರತಿ (i = 0; i < ಎಣಿಕೆ / ಪರಿಮಾಣ(*buf); i += 2) {
            ಯದಿ (buf[i] == AT_NULL)
                ಗಚ್ಛ out;
            ಯದಿ (buf[i] == AT_HWCAP) {
                ಯದಿ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                ಯದಿ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                ಯದಿ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            ಅನ್ಯಥಾ ಯದಿ (buf[i] == AT_HWCAP2) {
                ಯದಿ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    ಪ್ರತ್ಯಾಗಮ ret;
#ಅನ್ಯಥಾ
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ಪ್ರತ್ಯಾಗಮ AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    ಪ್ರತ್ಯಾಗಮ 0;
}

size_t ff_get_cpu_max_align_ppc(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = av_get_cpu_flags();

    ಯದಿ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ಪ್ರತ್ಯಾಗಮ 16;

    ಪ್ರತ್ಯಾಗಮ 8;
}
