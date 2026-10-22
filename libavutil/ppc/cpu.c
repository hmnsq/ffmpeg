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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __APPLE__
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>
#ಅಥವಾಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __FreeBSD__
#ಅನ್ತರ್ಭಾವ <machine/cpu.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ಅಥವಾಆದರೆ defined(__linux__)
#ಅನ್ತರ್ಭಾವ <asm/cputable.h>
#ಅನ್ತರ್ಭಾವ <linux/auxvec.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಆದರೆ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅಥವಾಆದರೆ defined(__NetBSD__) || defined(__OpenBSD__)
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>
#ಅನ್ತರ್ಭಾವ <machine/cpu.h>
#ಅಥವಾಆದರೆ defined(__AMIGAOS4__)
#ಅನ್ತರ್ಭಾವ <exec/exec.h>
#ಅನ್ತರ್ಭಾವ <interfaces/exec.h>
#ಅನ್ತರ್ಭಾವ <proto/exec.h>
#ಆದರೆ_ಅಂತ್ಯ /* __APPLE__ */

#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AT_HWCAP
#ವ್ಯಾಖ್ಯಾನಿಸು AT_HWCAP             16
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AT_HWCAP2
#ವ್ಯಾಖ್ಯಾನಿಸು AT_HWCAP2            26
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_PPC_VSX        (1U << 7)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_PPC_ALTIVEC    (1U << 28)
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_ppc(ಶೂನ್ಯ)
{
#ಆದರೆ HAVE_ALTIVEC
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __AMIGAOS4__
    ULONG ಫಲಿತಾಂಶ = 0;
    ಬಾಹ್ಯ ರಚನೆ ExecIFace *IExec;

    IExec->Get_CPUInfo_ಟ್ಯಾಗುಗಳು(GCIT_ಸದಿಶ_Unit, &ಫಲಿತಾಂಶ, ಟ್ಯಾಗ್_ಮುಗಿದ);
    ಆದರೆ (ಫಲಿತಾಂಶ == VECTORTYPE_ALTIVEC)
        ಹಿಂತಿರುಗಿ AV_CPU_FLAG_ALTIVEC;
    ಹಿಂತಿರುಗಿ 0;
#ಅಥವಾಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ಪೂರ್ಣಾಂಕ flags = 0;

    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ hwcap = ff_getauxval(AT_HWCAP);
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ hwcap2 = ff_getauxval(AT_HWCAP2);

    ಆದರೆ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    ಆದರೆ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    ಆದರೆ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ಹಿಂತಿರುಗಿ flags;
#ಅಥವಾಆದರೆ defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#ಆದರೆ defined(__NetBSD__) || defined(__OpenBSD__)
    ಪೂರ್ಣಾಂಕ sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ sels[2] = {CTL_HW, HW_VECTORUNIT};
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ಣಾಂಕ has_vu = 0;
    size_t len = ಗಾತ್ರ(has_vu);
    ಪೂರ್ಣಾಂಕ err;

    err = sysctl(sels, 2, &has_vu, &len, ಖಾಲಿ, 0);

    ಆದರೆ (err == 0)
        ಹಿಂತಿರುಗಿ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ಹಿಂತಿರುಗಿ 0;
#ಅಥವಾಆದರೆ defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    ಪೂರ್ಣಾಂಕ i, ret = 0;
    ಪೂರ್ಣಾಂಕ fd = open("/proc/self/auxv", O_RDONLY);
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ buf[64] = { 0 };
    ssize_t ಎಣಿಕೆ_2;

    ಆದರೆ (fd < 0)
        ಹಿಂತಿರುಗಿ 0;

    ಆಗ ((ಎಣಿಕೆ_2 = ಪಠ(fd, buf, ಗಾತ್ರ(buf))) > 0) {
        ಗಾಗಿ (i = 0; i < ಎಣಿಕೆ_2 / ಗಾತ್ರ(*buf); i += 2) {
            ಆದರೆ (buf[i] == AT_NULL)
                ಹೋಗು ಹೊರಹೋಗು;
            ಆದರೆ (buf[i] == AT_HWCAP) {
                ಆದರೆ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                ಆದರೆ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                ಆದರೆ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (buf[i] == AT_HWCAP2) {
                ಆದರೆ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

ಹೊರಹೋಗು:
    close(fd);
    ಹಿಂತಿರುಗಿ ret;
#ಇಲ್ಲದಿದ್ದರೆ
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ಹಿಂತಿರುಗಿ AV_CPU_FLAG_ALTIVEC;
#ಆದರೆ_ಅಂತ್ಯ /* __AMIGAOS4__ */
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_ALTIVEC */
    ಹಿಂತಿರುಗಿ 0;
}

size_t ff_get_cpu_max_align_ppc(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ಹಿಂತಿರುಗಿ 16;

    ಹಿಂತಿರುಗಿ 8;
}
