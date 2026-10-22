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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __APPLE__
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/sysctl.h>
#ਜਾਂਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __FreeBSD__
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/cpu.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>
#ਜਾਂਜੇ defined(__linux__)
#ਅਨ੍ਤਰ੍ਭਾਵ <asm/cputable.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <linux/auxvec.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜਾਂਜੇ defined(__NetBSD__) || defined(__OpenBSD__)
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/sysctl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <machine/cpu.h>
#ਜਾਂਜੇ defined(__AMIGAOS4__)
#ਅਨ੍ਤਰ੍ਭਾਵ <exec/exec.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <interfaces/exec.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <proto/exec.h>
#ਜੇ_ਅੰਤ /* __APPLE__ */

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AT_HWCAP
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT_HWCAP             16
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AT_HWCAP2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AT_HWCAP2            26
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_PPC_VSX        (1U << 7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_PPC_ALTIVEC    (1U << 28)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
ਪੂਰਨ ff_get_cpu_flags_ppc(ਖਾਲੀ)
{
#ਜੇ HAVE_ALTIVEC
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __AMIGAOS4__
    ULONG ਨਤੀਜਾ = 0;
    ਬਾਹਰੀ ਬਣਤਰ ExecIFace *IExec;

    IExec->Get_CPUInfo_ਟੈਗ_ਸੂਚੀ(GCIT_ਸਦਿਸ਼_Unit, &ਨਤੀਜਾ, ਟੈਗ_ਪੂਰਾ);
    ਜੇ (ਨਤੀਜਾ == VECTORTYPE_ALTIVEC)
        ਵਾਪਸ AV_CPU_FLAG_ALTIVEC;
    ਵਾਪਸ 0;
#ਜਾਂਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    ਪੂਰਨ flags = 0;

    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ hwcap = ff_getauxval(AT_HWCAP);
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ hwcap2 = ff_getauxval(AT_HWCAP2);

    ਜੇ (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    ਜੇ (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    ਜੇ (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    ਵਾਪਸ flags;
#ਜਾਂਜੇ defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#ਜੇ defined(__NetBSD__) || defined(__OpenBSD__)
    ਪੂਰਨ sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ sels[2] = {CTL_HW, HW_VECTORUNIT};
#ਜੇ_ਅੰਤ
    ਪੂਰਨ has_vu = 0;
    size_t len = ਆਕਾਰ(has_vu);
    ਪੂਰਨ err;

    err = sysctl(sels, 2, &has_vu, &len, ਨਿਰਾ, 0);

    ਜੇ (err == 0)
        ਵਾਪਸ has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    ਵਾਪਸ 0;
#ਜਾਂਜੇ defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    ਪੂਰਨ i, ret = 0;
    ਪੂਰਨ fd = open("/proc/self/auxv", O_RDONLY);
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ buf[64] = { 0 };
    ssize_t ਗਿਣਤੀ_2;

    ਜੇ (fd < 0)
        ਵਾਪਸ 0;

    ਜਦੋਂ ((ਗਿਣਤੀ_2 = ਪਠ(fd, buf, ਆਕਾਰ(buf))) > 0) {
        ਲਈ (i = 0; i < ਗਿਣਤੀ_2 / ਆਕਾਰ(*buf); i += 2) {
            ਜੇ (buf[i] == AT_NULL)
                ਜਾਓ ਬਾਹਰਲਾ;
            ਜੇ (buf[i] == AT_HWCAP) {
                ਜੇ (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                ਜੇ (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                ਜੇ (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            ਨਹੀਂਤਾਂ ਜੇ (buf[i] == AT_HWCAP2) {
                ਜੇ (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

ਬਾਹਰਲਾ:
    close(fd);
    ਵਾਪਸ ret;
#ਨਹੀਂਤਾਂ
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    ਵਾਪਸ AV_CPU_FLAG_ALTIVEC;
#ਜੇ_ਅੰਤ /* __AMIGAOS4__ */
#ਜੇ_ਅੰਤ /* HAVE_ALTIVEC */
    ਵਾਪਸ 0;
}

size_t ff_get_cpu_max_align_ppc(ਖਾਲੀ)
{
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        ਵਾਪਸ 16;

    ਵਾਪਸ 8;
}
