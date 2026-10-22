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
#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/riscv/cpu.h"
#અન્તર્ભાવ "libavutil/cpu_internal.h"
#અન્તર્ભાવ "libavutil/macros.h"
#અન્તર્ભાવ "libavutil/log.h"
#અન્તર્ભાવ "config.h"

#જો HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#અન્તર્ભાવ <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#જો HAVE_SYS_HWPROBE_H
#અન્તર્ભાવ <sys/hwprobe.h>
#અથવાજો HAVE_ASM_HWPROBE_H
#અન્તર્ભાવ <asm/hwprobe.h>
#અન્તર્ભાવ <asm/unistd.h>
#અન્તર્ભાવ <sys/syscall.h>
#અન્તર્ભાવ <unistd.h>

સ્થિર પૂર્ણાંક __riscv_hwprobe(સંરચના riscv_hwprobe *pairs, size_t pair_ગણતરી,
                           size_t cpu_ગણતરી, unsigned long *cpus,
                           unsigned પૂર્ણાંક flags)
{
        પાછા syscall(__NR_riscv_hwprobe, pairs, pair_ગણતરી, cpu_ગણતરી, cpus,
                       flags);
}
#endif

પૂર્ણાંક ff_get_cpu_flags_riscv(શૂન્ય)
{
    પૂર્ણાંક ret = 0;
#જો HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    સંરચના riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_ચાવી_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_ચાવી_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_ચાવી_CPUPERF_0, 0 },
    };

    જો (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, ખાલી, 0) == 0) {
        જો (pairs[0].કિંમત & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        જો (pairs[1].કિંમત & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        નહીંતર જો ((pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            જો (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            જો (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                જો (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        જો (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#જો defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        જો ((pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        જો (pairs[1].કિંમત & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        પસંદગી (pairs[2].કિંમત & RISCV_HWPROBE_MISALIGNED_MASK) {
            સ્થિતિ RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                તોડો;
            મૂળભૂત:
                ; /* do nothing */
        }
    }
#અથવાજો HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        અચલ unsigned long hwcap = ff_getauxval(AT_HWCAP);

        જો (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        જો (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        જો (hwcap & HWCAP_RV('V'))
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
#જો defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#જો __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#જો __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#જો __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    પાછા ret;
}
