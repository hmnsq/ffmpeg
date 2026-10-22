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

#اگر_تعریف_شدہ __APPLE__
#شامل <sys/sysctl.h>
#وگرنہ_اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#اگر_تعریف_شدہ __FreeBSD__
#شامل <machine/cpu.h>
#اگر_ختم
#شامل <sys/auxv.h>
#وگرنہ_اگر defined(__linux__)
#شامل <asm/cputable.h>
#شامل <linux/auxvec.h>
#شامل <fcntl.h>
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#اگر_ختم
#وگرنہ_اگر defined(__NetBSD__) || defined(__OpenBSD__)
#شامل <sys/types.h>
#شامل <sys/sysctl.h>
#شامل <machine/cpu.h>
#وگرنہ_اگر defined(__AMIGAOS4__)
#شامل <exec/exec.h>
#شامل <interfaces/exec.h>
#شامل <proto/exec.h>
#اگر_ختم /* __APPLE__ */

#شامل "libavutil/avassert.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/cpu_internal.h"

#اگر_غیر_تعریف_شدہ AT_HWCAP
#تعریف_کرو AT_HWCAP             16
#اگر_ختم
#اگر_غیر_تعریف_شدہ AT_HWCAP2
#تعریف_کرو AT_HWCAP2            26
#اگر_ختم

#تعریف_کرو HWCAP_PPC_VSX        (1U << 7)
#تعریف_کرو HWCAP_PPC_ALTIVEC    (1U << 28)
#تعریف_کرو HWCAP2_PPC_ARCH_2_07 (1U << 31)

/**
 * This function MAY rely on signal() or fork() in order to make sure AltiVec
 * is present.
 */
صحیح ff_get_cpu_flags_ppc(خالی)
{
#اگر HAVE_ALTIVEC
#اگر_تعریف_شدہ __AMIGAOS4__
    ULONG نتیجہ = 0;
    خارجی ساخت ExecIFace *IExec;

    IExec->Get_CPUInfo_لیبل_فہرست(GCIT_سمتیہ_Unit, &نتیجہ, لیبل_مکمل);
    اگر (نتیجہ == VECTORTYPE_ALTIVEC)
        واپس AV_CPU_FLAG_ALTIVEC;
    واپس 0;
#وگرنہ_اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    صحیح flags = 0;

    غیرعلامتی طویل hwcap = ff_getauxval(AT_HWCAP);
    غیرعلامتی طویل hwcap2 = ff_getauxval(AT_HWCAP2);

    اگر (hwcap & HWCAP_PPC_ALTIVEC)
       flags |= AV_CPU_FLAG_ALTIVEC;
    اگر (hwcap & HWCAP_PPC_VSX)
       flags |= AV_CPU_FLAG_VSX;
    اگر (hwcap2 & HWCAP2_PPC_ARCH_2_07)
       flags |= AV_CPU_FLAG_POWER8;

    واپس flags;
#وگرنہ_اگر defined(__APPLE__) || defined(__NetBSD__) || defined(__OpenBSD__)
#اگر defined(__NetBSD__) || defined(__OpenBSD__)
    صحیح sels[2] = {CTL_MACHDEP, CPU_ALTIVEC};
#ورنہ
    صحیح sels[2] = {CTL_HW, HW_VECTORUNIT};
#اگر_ختم
    صحیح has_vu = 0;
    size_t len = حجم(has_vu);
    صحیح err;

    err = sysctl(sels, 2, &has_vu, &len, تہی, 0);

    اگر (err == 0)
        واپس has_vu ? AV_CPU_FLAG_ALTIVEC : 0;
    واپس 0;
#وگرنہ_اگر defined(__linux__)
    // The linux kernel could have the altivec support disabled
    // even if the cpu has it.
    صحیح i, ret = 0;
    صحیح fd = open("/proc/self/auxv", O_RDONLY);
    غیرعلامتی طویل buf[64] = { 0 };
    ssize_t گنتی;

    اگر (fd < 0)
        واپس 0;

    جب ((گنتی = اقرأ(fd, buf, حجم(buf))) > 0) {
        برائے (i = 0; i < گنتی / حجم(*buf); i += 2) {
            اگر (buf[i] == AT_NULL)
                جاؤ برآمد;
            اگر (buf[i] == AT_HWCAP) {
                اگر (buf[i + 1] & HWCAP_PPC_ALTIVEC)
                    ret = AV_CPU_FLAG_ALTIVEC;
                اگر (buf[i + 1] & HWCAP_PPC_VSX)
                    ret |= AV_CPU_FLAG_VSX;
                اگر (ret & AV_CPU_FLAG_VSX)
                    av_assert0(ret & AV_CPU_FLAG_ALTIVEC);
            }
            ورنہ اگر (buf[i] == AT_HWCAP2) {
                اگر (buf[i + 1] & HWCAP2_PPC_ARCH_2_07)
                    ret |= AV_CPU_FLAG_POWER8;
            }
        }
    }

برآمد:
    close(fd);
    واپس ret;
#ورنہ
    // Since we were compiled for AltiVec, just assume we have it
    // until someone comes up with a proper way (not involving signal hacks).
    واپس AV_CPU_FLAG_ALTIVEC;
#اگر_ختم /* __AMIGAOS4__ */
#اگر_ختم /* HAVE_ALTIVEC */
    واپس 0;
}

size_t ff_get_cpu_max_align_ppc(خالی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & (AV_CPU_FLAG_ALTIVEC   |
                 AV_CPU_FLAG_VSX       |
                 AV_CPU_FLAG_POWER8))
        واپس 16;

    واپس 8;
}
