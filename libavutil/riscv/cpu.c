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

#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/riscv/cpu.h"
#ضمن "libavutil/cpu_internal.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/log.h"
#ضمن "config.h"

#إذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ضمن <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#إذا HAVE_SYS_HWPROBE_H
#ضمن <sys/hwprobe.h>
#وإلاإذا HAVE_ASM_HWPROBE_H
#ضمن <asm/hwprobe.h>
#ضمن <asm/unistd.h>
#ضمن <sys/syscall.h>
#ضمن <unistd.h>

ساكن صحيح __riscv_hwprobe(بنية riscv_hwprobe *pairs, size_t pair_تعداد,
                           size_t cpu_تعداد, unsigned long *cpus,
                           unsigned صحيح flags)
{
        إرجاع syscall(__NR_riscv_hwprobe, pairs, pair_تعداد, cpu_تعداد, cpus,
                       flags);
}
#endif

صحيح ff_get_cpu_flags_riscv(فراغ)
{
    صحيح ret = 0;
#إذا HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    بنية riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_مفتاح_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_مفتاح_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_مفتاح_CPUPERF_0, 0 },
    };

    إذا (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, عدم, 0) == 0) {
        إذا (pairs[0].قيمة & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        إذا (pairs[1].قيمة & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        وإلا إذا ((pairs[1].قيمة & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            إذا (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            إذا (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                إذا (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        إذا (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#إذا defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        إذا ((pairs[1].قيمة & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        إذا (pairs[1].قيمة & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        بدل (pairs[2].قيمة & RISCV_HWPROBE_MISALIGNED_MASK) {
            حالة RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                اكسر;
            افتراضي:
                ; /* do nothing */
        }
    }
#وإلاإذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ثابت unsigned long hwcap = ff_getauxval(AT_HWCAP);

        إذا (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        إذا (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        إذا (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#endif

#ifdef __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#endif

#ifdef __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#endif
#إذا defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#إذا __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#إذا __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#إذا __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    إرجاع ret;
}
