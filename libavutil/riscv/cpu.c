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

#నిర్వచితం_కాకపోతే GNU_ఆధారం
# define GNU_ఆధారం
#అయితే_ముగింపు
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/riscv/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#అన్తర్భావ <sys/auxv.h>
#నిర్వచించు HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#అయితే_ముగింపు
#ఒకవేళ HAVE_SYS_HWPROBE_H
#అన్తర్భావ <sys/hwprobe.h>
#లేదావేళ HAVE_ASM_HWPROBE_H
#అన్తర్భావ <asm/hwprobe.h>
#అన్తర్భావ <asm/unistd.h>
#అన్తర్భావ <sys/syscall.h>
#అన్తర్భావ <unistd.h>

స్థిర పూర్ణాంకం __riscv_hwprobe(నిర్మాణం riscv_hwprobe *జతలు, size_t pair_లెక్క,
                           size_t cpu_లెక్క, గుర్తులేని దీర్ఘ *cpus,
                           గుర్తులేని పూర్ణాంకం flags)
{
        తిరిగి syscall(__NR_riscv_hwprobe, జతలు, pair_లెక్క, cpu_లెక్క, cpus,
                       flags);
}
#అయితే_ముగింపు

పూర్ణాంకం ff_get_cpu_flags_riscv(శూన్య)
{
    పూర్ణాంకం ret = 0;
#ఒకవేళ HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    నిర్మాణం riscv_hwprobe జతలు[] = {
        { RISCV_HWPROBE_కీలకం_పునాది_BEHAVIOR, 0 },
        { RISCV_HWPROBE_కీలకం_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_కీలకం_CPUPERF_0, 0 },
    };

    ఒకవేళ (__riscv_hwprobe(జతలు, FF_ARRAY_ELEMS(జతలు), 0, ఖాళీ, 0) == 0) {
        ఒకవేళ (జతలు[0].విలువ & RISCV_HWPROBE_పునాది_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#నిర్వచితమైతే RISCV_HWPROBE_IMA_V
        ఒకవేళ (జతలు[1].విలువ & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#నిర్వచితమైతే RISCV_HWPROBE_EXT_ZVE32X
        లేకపోతే ఒకవేళ ((జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            ఒకవేళ (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            ఒకవేళ (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                ఒకవేళ (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#అయితే_ముగింపు
#అయితే_ముగింపు
#నిర్వచితమైతే RISCV_HWPROBE_EXT_ZBB
        ఒకవేళ (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#ఒకవేళ defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        ఒకవేళ ((జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZBA) &&
            (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZBB) &&
            (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#అయితే_ముగింపు
#అయితే_ముగింపు
#నిర్వచితమైతే RISCV_HWPROBE_EXT_ZVBB
        ఒకవేళ (జతలు[1].విలువ & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#అయితే_ముగింపు
        ఎంపిక (జతలు[2].విలువ & RISCV_HWPROBE_MISALIGNED_ముసుగు) {
            స్థితి RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                ఆపు;
            అప్రమేయ:
                ; /* do nothing */
        }
    }
#లేదావేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        స్థిరరాశి గుర్తులేని దీర్ఘ hwcap = ff_getauxval(AT_HWCAP);

        ఒకవేళ (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        ఒకవేళ (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        ఒకవేళ (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#అయితే_ముగింపు

#నిర్వచితమైతే __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#అయితే_ముగింపు

#నిర్వచితమైతే __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#అయితే_ముగింపు
#ఒకవేళ defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#అయితే_ముగింపు

    /* If RV-V is enabled statically at compile-time, check the details. */
#నిర్వచితమైతే __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#ఒకవేళ __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#అయితే_ముగింపు
#ఒకవేళ __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#ఒకవేళ __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#అయితే_ముగింపు
#అయితే_ముగింపు
#అయితే_ముగింపు
#నిర్వచితమైతే __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#అయితే_ముగింపు

    తిరిగి ret;
}
