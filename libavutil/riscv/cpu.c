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
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/riscv/cpu.h"
#அந்தர்பாவ "libavutil/cpu_internal.h"
#அந்தர்பாவ "libavutil/macros.h"
#அந்தர்பாவ "libavutil/log.h"
#அந்தர்பாவ "config.h"

#எனில் HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#அந்தர்பாவ <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#எனில் HAVE_SYS_HWPROBE_H
#அந்தர்பாவ <sys/hwprobe.h>
#அல்லதெனில் HAVE_ASM_HWPROBE_H
#அந்தர்பாவ <asm/hwprobe.h>
#அந்தர்பாவ <asm/unistd.h>
#அந்தர்பாவ <sys/syscall.h>
#அந்தர்பாவ <unistd.h>

நிலையான முழு __riscv_hwprobe(கட்டமைப்பு riscv_hwprobe *pairs, size_t pair_மொத்தம்,
                           size_t cpu_மொத்தம், unsigned long *cpus,
                           unsigned முழு flags)
{
        திரும்பு syscall(__NR_riscv_hwprobe, pairs, pair_மொத்தம், cpu_மொத்தம், cpus,
                       flags);
}
#endif

முழு ff_get_cpu_flags_riscv(வெறுமை)
{
    முழு ret = 0;
#எனில் HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    கட்டமைப்பு riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_சாவி_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_சாவி_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_சாவி_CPUPERF_0, 0 },
    };

    எனில் (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, வெற்று, 0) == 0) {
        எனில் (pairs[0].மதிப்பு & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        எனில் (pairs[1].மதிப்பு & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        இல்லையெனில் எனில் ((pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            எனில் (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            எனில் (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                எனில் (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        எனில் (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#எனில் defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        எனில் ((pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        எனில் (pairs[1].மதிப்பு & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        தேர்வு (pairs[2].மதிப்பு & RISCV_HWPROBE_MISALIGNED_MASK) {
            நிலை RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                நிறுத்து;
            இயல்பு:
                ; /* do nothing */
        }
    }
#அல்லதெனில் HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        மாறிலி unsigned long hwcap = ff_getauxval(AT_HWCAP);

        எனில் (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        எனில் (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        எனில் (hwcap & HWCAP_RV('V'))
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
#எனில் defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#எனில் __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#எனில் __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#எனில் __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    திரும்பு ret;
}
