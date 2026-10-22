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
#include "libavutil/cpu.h"
#include "libavutil/riscv/cpu.h"
#include "libavutil/cpu_internal.h"
#include "libavutil/macros.h"
#include "libavutil/log.h"
#include "config.h"

#만약 HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#include <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#만약 HAVE_SYS_HWPROBE_H
#include <sys/hwprobe.h>
#elif HAVE_ASM_HWPROBE_H
#include <asm/hwprobe.h>
#include <asm/unistd.h>
#include <sys/syscall.h>
#include <unistd.h>

static 정수 __riscv_hwprobe(struct riscv_hwprobe *pairs, size_t pair_count,
                           size_t cpu_count, unsigned long *cpus,
                           unsigned 정수 flags)
{
        반환 syscall(__NR_riscv_hwprobe, pairs, pair_count, cpu_count, cpus,
                       flags);
}
#endif

정수 ff_get_cpu_flags_riscv(void)
{
    정수 ret = 0;
#만약 HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    struct riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_KEY_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_KEY_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_KEY_CPUPERF_0, 0 },
    };

    만약 (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, NULL, 0) == 0) {
        만약 (pairs[0].value & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        만약 (pairs[1].value & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        아니면 만약 ((pairs[1].value & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            만약 (pairs[1].value & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            만약 (pairs[1].value & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                만약 (pairs[1].value & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        만약 (pairs[1].value & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#만약 defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        만약 ((pairs[1].value & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].value & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].value & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        만약 (pairs[1].value & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        switch (pairs[2].value & RISCV_HWPROBE_MISALIGNED_MASK) {
            case RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                break;
            default:
                ; /* do nothing */
        }
    }
#elif HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        const unsigned long hwcap = ff_getauxval(AT_HWCAP);

        만약 (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        만약 (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        만약 (hwcap & HWCAP_RV('V'))
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
#만약 defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#만약 __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#만약 __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#만약 __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    반환 ret;
}
