/*
 * Copyright © 2022 Rémi Denis-Courmont.
 *
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

#که_نه_تعریف_شوی GNU_سرچینه
# define GNU_سرچینه
#د_که_پای
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/riscv/cpu.h"
#ضمن "libavutil/cpu_internal.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/log.h"
#ضمن "config.h"

#إذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ضمن <sys/auxv.h>
#تعریف_کړه HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#د_که_پای
#إذا HAVE_SYS_HWPROBE_H
#ضمن <sys/hwprobe.h>
#وإلاإذا HAVE_ASM_HWPROBE_H
#ضمن <asm/hwprobe.h>
#ضمن <asm/unistd.h>
#ضمن <sys/syscall.h>
#ضمن <unistd.h>

ساكن صحيح __riscv_hwprobe(بنية riscv_hwprobe *جوړې, size_t pair_شمېر,
                           size_t cpu_شمېر, بینښه اوږد *cpus,
                           بینښه صحيح flags)
{
        أرجع syscall(__NR_riscv_hwprobe, جوړې, pair_شمېر, cpu_شمېر, cpus,
                       flags);
}
#د_که_پای

صحيح ff_get_cpu_flags_riscv(فراغ)
{
    صحيح ret = 0;
#إذا HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    بنية riscv_hwprobe جوړې[] = {
        { RISCV_HWPROBE_کلی_بنسټ_BEHAVIOR, 0 },
        { RISCV_HWPROBE_کلی_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_کلی_CPUPERF_0, 0 },
    };

    إذا (__riscv_hwprobe(جوړې, FF_ARRAY_ELEMS(جوړې), 0, عدم, 0) == 0) {
        إذا (جوړې[0].ارزښت & RISCV_HWPROBE_بنسټ_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#که_تعریف_شوی RISCV_HWPROBE_IMA_V
        إذا (جوړې[1].ارزښت & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#که_تعریف_شوی RISCV_HWPROBE_EXT_ZVE32X
        وإلا إذا ((جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            إذا (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            إذا (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                إذا (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#د_که_پای
#د_که_پای
#که_تعریف_شوی RISCV_HWPROBE_EXT_ZBB
        إذا (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#إذا defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        إذا ((جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZBA) &&
            (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZBB) &&
            (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#د_که_پای
#د_که_پای
#که_تعریف_شوی RISCV_HWPROBE_EXT_ZVBB
        إذا (جوړې[1].ارزښت & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#د_که_پای
        بدل (جوړې[2].ارزښت & RISCV_HWPROBE_MISALIGNED_ماسک) {
            حالة RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                اكسر;
            افتراضي:
                ; /* do nothing */
        }
    }
#وإلاإذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ثابت بینښه اوږد hwcap = ff_getauxval(AT_HWCAP);

        إذا (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        إذا (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        إذا (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#د_که_پای

#که_تعریف_شوی __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#د_که_پای

#که_تعریف_شوی __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#د_که_پای
#إذا defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#د_که_پای

    /* If RV-V is enabled statically at compile-time, check the details. */
#که_تعریف_شوی __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#إذا __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#د_که_پای
#إذا __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#إذا __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#د_که_پای
#د_که_پای
#د_که_پای
#که_تعریف_شوی __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#د_که_پای

    أرجع ret;
}
