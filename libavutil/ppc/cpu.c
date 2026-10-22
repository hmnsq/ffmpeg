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

#அந்தர்பாவ "config.h"

#ifdef __APPLE__
#அந்தர்பாவ <sys/sysctl.h>
#அல்லதெனில் HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#அந்தர்பாவ <machine/cpu.h>
#endif
#அந்தர்பாவ <sys/auxv.h>
#அல்லதெனில் defined(__linux__)
#அந்தர்பாவ <asm/cputable.h>
#அந்தர்பாவ <linux/auxvec.h>
#அந்தர்பாவ <fcntl.h>
#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif
#அல்லதெனில் defined(__NetBSD__) || defined(__OpenBSD__)
#அந்தர்பாவ <sys/types.h>
#அந்தர்பாவ <sys/sysctl.h>
#அந்தர்பாவ <machine/cpu.h>
#அல்லதெனில் defined(__AMIGAOS4__)
#அந்தர்பாவ <exec/exec.h>
#அந்தர்பாவ <interfaces/exec.h>
#அந்தர்பாவ <proto/exec.h>
#endif /* __APPLE__ */

#அந்தர்பாவ "libavutil/avassert.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/cpu_internal.h"

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
முழு ff_get_cpu_flags_ppc(வெறுமை)
{
#எனில் HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    வெளி கட்டமைப்பு ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    எனில் (result == VECTORTYPE_ALTIVEC)
        திரும்பு AV_CPU_FLAG_ALTIVEC;
    திரும்பு 0;
#அல்லதெனில் HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    முழு flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    எனில் (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    எனில் (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    எனில் (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    திரும்பு flags;
#அல்லதெனில் defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#எனில் defined(__NetBSD__) || defined(__OpenBSD__)
    முழு sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#இல்லையெனில்
    முழு sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    முழு has_vu = 0;
    size_t len = அளவு(has_vu);
    முழு err;

    err = sysctl(sels, 2, &has_vu, &len, வெற்று, 0);

    எனில் (err == 0)
        திரும்பு has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    திரும்பு 0;
#அல்லதெனில் defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    முழு i, ret = 0;
    முழு fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t மொத்தம்;

    எனில் (fd < 0)
        திரும்பு 0;

    போது ((மொத்தம் = பட(fd, buf, அளவு(buf))) > 0) {
        க்கு (i = 0; i < மொத்தம் / அளவு(*buf); i += 2) {
            எனில் (buf[i] == AT_NULL)
                செல் out;
            எனில் (buf[i] == AT_HWCAP) {
                எனில் (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                எனில் (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                எனில் (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            இல்லையெனில் எனில் (buf[i] == AT_HWCAP2) {
                எனில் (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    திரும்பு ret;
#இல்லையெனில்
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    திரும்பு AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    திரும்பு 0;
}

size_t ff_get_cpu_max_align_ppc(வெறுமை)
{
    முழு flags = av_get_cpu_flags();

    எனில் (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        திரும்பு 16;

    திரும்பு 8;
}
