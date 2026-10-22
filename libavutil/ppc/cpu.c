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

#ضمن "config.h"

#جيڪڏهن_وصف_ٿيل __APPLE__
#ضمن <sys/sysctl.h>
#وإلاإذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#جيڪڏهن_وصف_ٿيل __FreeBSD__
#ضمن <machine/cpu.h>
#جيڪڏهن_پورو
#ضمن <sys/auxv.h>
#وإلاإذا defined(__linux__)
#ضمن <asm/cputable.h>
#ضمن <linux/auxvec.h>
#ضمن <fcntl.h>
#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#جيڪڏهن_پورو
#وإلاإذا defined(__NetBSD__) || defined(__OpenBSD__)
#ضمن <sys/types.h>
#ضمن <sys/sysctl.h>
#ضمن <machine/cpu.h>
#وإلاإذا defined(__AMIGAOS4__)
#ضمن <exec/exec.h>
#ضمن <interfaces/exec.h>
#ضمن <proto/exec.h>
#جيڪڏهن_پورو /* __APPLE__ */

#ضمن "libavutil/avassert.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"

#جيڪڏهن_وصف_نه_ٿيل AT_HWCAP
#وصف_ڪريو AT_HWCAP             16
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل AT_HWCAP2
#وصف_ڪريو AT_HWCAP2            26
#جيڪڏهن_پورو

#وصف_ڪريو HWCAP_PPC_VSX        (1U << 7)
#وصف_ڪريو HWCAP_PPC_ALTIVEC    (1U << 28)
#وصف_ڪريو HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
صحيح ff_get_cpu_flags_ppc(فراغ)
{
#إذا HAVE_ALTIVEC
#جيڪڏهن_وصف_ٿيل __AMIGAOS4__
    ULONG نتيجو = 0;
    خارجي بنية ExecIFace *IExec;

    IExec->Get_CPUInfo_ٽيگ_فهرست(GCIT_ويڪٽر_Unit, &نتيجو, ٽيگ_پورو);
    إذا (نتيجو == VECTORTYPE_ALTIVEC)
        أرجع AV_CPU_FLAG_ALTIVEC;
    أرجع 0;
#وإلاإذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    صحيح flags = 0;

    بنانشان ڊگهو hwcap = ff_getauxval(AT_HWCAP);
    بنانشان ڊگهو hwcap2 = ff_getauxval(AT_HWCAP2);

    إذا (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    إذا (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    إذا (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    أرجع flags;
#وإلاإذا defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#إذا defined(__NetBSD__) || defined(__OpenBSD__)
    صحيح sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#وإلا
    صحيح sels[2] = {CTL_HW, HW_VECTORUNIT};
#جيڪڏهن_پورو
    صحيح has_vu = 0;
    size_t len = حجم(has_vu);
    صحيح err;

    err = sysctl(sels, 2, &has_vu, &len, عدم, 0);

    إذا (err == 0)
        أرجع has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    أرجع 0;
#وإلاإذا defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    صحيح i, ret = 0;
    صحيح fd = open("/proc/self/auxv", O_RDONLY);
    بنانشان ڊگهو buf[64] = { 0 };
    ssize_t ڳڻپ;

    إذا (fd < 0)
        أرجع 0;

    طالما ((ڳڻپ = اقرأ(fd, buf, حجم(buf))) > 0) {
        لكل (i = 0; i < ڳڻپ / حجم(*buf); i += 2) {
            إذا (buf[i] == AT_NULL)
                اذهب ٻاهريون;
            إذا (buf[i] == AT_HWCAP) {
                إذا (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                إذا (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                إذا (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            وإلا إذا (buf[i] == AT_HWCAP2) {
                إذا (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

ٻاهريون:
    close(fd);
    أرجع ret;
#وإلا
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    أرجع AV_CPU_FLAG_ALTIVEC;
#جيڪڏهن_پورو /* __AMIGAOS4__ */
#جيڪڏهن_پورو /* HAVE_ALTIVEC */
    أرجع 0;
}

size_t ff_get_cpu_max_align_ppc(فراغ)
{
    صحيح flags = av_get_cpu_flags();

    إذا (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        أرجع 16;

    أرجع 8;
}
