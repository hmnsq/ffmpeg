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
#شامل "libavutil/cpu.h"
#شامل "libavutil/riscv/cpu.h"
#شامل "libavutil/cpu_internal.h"
#شامل "libavutil/macros.h"
#شامل "libavutil/log.h"
#شامل "config.h"

#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#شامل <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#اگر HAVE_SYS_HWPROBE_H
#شامل <sys/hwprobe.h>
#وگرنهاگر HAVE_ASM_HWPROBE_H
#شامل <asm/hwprobe.h>
#شامل <asm/unistd.h>
#شامل <sys/syscall.h>
#شامل <unistd.h>

ایستا صحیح __riscv_hwprobe(ساختار riscv_hwprobe *pairs, size_t pair_شمار,
                           size_t cpu_شمار, unsigned long *cpus,
                           unsigned صحیح flags)
{
        بازگشت syscall(__NR_riscv_hwprobe, pairs, pair_شمار, cpu_شمار, cpus,
                       flags);
}
#endif

صحیح ff_get_cpu_flags_riscv(تهی)
{
    صحیح ret = 0;
#اگر HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ساختار riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_کلید_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_کلید_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_کلید_CPUPERF_0, 0 },
    };

    اگر (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, پوچ, 0) == 0) {
        اگر (pairs[0].مقدار & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        اگر (pairs[1].مقدار & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        وگرنه اگر ((pairs[1].مقدار & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            اگر (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            اگر (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                اگر (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        اگر (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#اگر defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        اگر ((pairs[1].مقدار & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        اگر (pairs[1].مقدار & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        انتخاب (pairs[2].مقدار & RISCV_HWPROBE_MISALIGNED_MASK) {
            حالت RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                بشکن;
            پیشفرض:
                ; /* do nothing */
        }
    }
#وگرنهاگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ثابت unsigned long hwcap = ff_getauxval(AT_HWCAP);

        اگر (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        اگر (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        اگر (hwcap & HWCAP_RV('V'))
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
#اگر defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#اگر __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#اگر __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#اگر __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    بازگشت ret;
}
