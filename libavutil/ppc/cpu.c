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

#شامل "config.h"

#ifdef __APPLE__
#شامل <sys/sysctl.h>
#وگرنهاگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ifdef __FreeBSD__
#شامل <machine/cpu.h>
#endif
#شامل <sys/auxv.h>
#وگرنهاگر defined(__linux__)
#شامل <asm/cputable.h>
#شامل <linux/auxvec.h>
#شامل <fcntl.h>
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#endif
#وگرنهاگر defined(__NetBSD__) || defined(__OpenBSD__)
#شامل <sys/types.h>
#شامل <sys/sysctl.h>
#شامل <machine/cpu.h>
#وگرنهاگر defined(__AMIGAOS4__)
#شامل <exec/exec.h>
#شامل <interfaces/exec.h>
#شامل <proto/exec.h>
#endif /* __APPLE__ */

#شامل "libavutil/avassert.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/cpu_internal.h"

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
صحیح ff_get_cpu_flags_ppc(تهی)
{
#اگر HAVE_ALTIVEC
#ifdef __AMIGAOS4__
    ULONG result = 0;
    بیرونی ساختار ExecIFace *IExec;

    IExec->GetCPUInfoTags(GCIT_VectorUnit, &result, TAG_DONE);
    اگر (result == VECTORTYPE_ALTIVEC)
        بازگشت AV_CPU_FLAG_ALTIVEC;
    بازگشت 0;
#وگرنهاگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    صحیح flags = 0;

    unsigned long hwcap = ff_getauxval(AT_HWCAP);
    unsigned long hwcap2 = ff_getauxval(AT_HWCAP2);

    اگر (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    اگر (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    اگر (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    بازگشت flags;
#وگرنهاگر defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#اگر defined(__NetBSD__) || defined(__OpenBSD__)
    صحیح sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#وگرنه
    صحیح sels[2] = {CTL_HW, HW_VECTORUNIT};
#endif
    صحیح has_vu = 0;
    size_t len = اندازه(has_vu);
    صحیح err;

    err = sysctl(sels, 2, &has_vu, &len, پوچ, 0);

    اگر (err == 0)
        بازگشت has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    بازگشت 0;
#وگرنهاگر defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    صحیح i, ret = 0;
    صحیح fd = open("/proc/self/auxv", O_RDONLY);
    unsigned long buf[64] = { 0 };
    ssize_t شمار;

    اگر (fd < 0)
        بازگشت 0;

    وقتی ((شمار = اقرأ(fd, buf, اندازه(buf))) > 0) {
        برای (i = 0; i < شمار / اندازه(*buf); i += 2) {
            اگر (buf[i] == AT_NULL)
                برو out;
            اگر (buf[i] == AT_HWCAP) {
                اگر (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                اگر (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                اگر (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            وگرنه اگر (buf[i] == AT_HWCAP2) {
                اگر (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

out:
    close(fd);
    بازگشت ret;
#وگرنه
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    بازگشت AV_CPU_FLAG_ALTIVEC;
#endif /* __AMIGAOS4__ */
#endif /* HAVE_ALTIVEC */
    بازگشت 0;
}

size_t ff_get_cpu_max_align_ppc(تهی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        بازگشت 16;

    بازگشت 8;
}
