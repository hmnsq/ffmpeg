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
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/riscv/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu_internal.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/macros.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"
#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#ଯଦି HAVE_SYS_HWPROBE_H
#ଅନ୍ତର୍ଭାଵ <sys/hwprobe.h>
#ନଚେତଯଦି HAVE_ASM_HWPROBE_H
#ଅନ୍ତର୍ଭାଵ <asm/hwprobe.h>
#ଅନ୍ତର୍ଭାଵ <asm/unistd.h>
#ଅନ୍ତର୍ଭାଵ <sys/syscall.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା __riscv_hwprobe(ସଂରଚନା riscv_hwprobe *pairs, size_t pair_ଗଣନା,
                           size_t cpu_ଗଣନା, unsigned long *cpus,
                           unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
        ଫେରନ୍ତୁ syscall(__NR_riscv_hwprobe, pairs, pair_ଗଣନା, cpu_ଗଣନା, cpus,
                       flags);
}
#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_riscv(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;
#ଯଦି HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ସଂରଚନା riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_ଚାବି_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_ଚାବି_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_ଚାବି_CPUPERF_0, 0 },
    };

    ଯଦି (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, ଖାଲି, 0) == 0) {
        ଯଦି (pairs[0].ମୂଲ୍ୟ & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        ଯଦି (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        ଅନ୍ୟଥା ଯଦି ((pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            ଯଦି (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            ଯଦି (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                ଯଦି (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        ଯଦି (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#ଯଦି defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        ଯଦି ((pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        ଯଦି (pairs[1].ମୂଲ୍ୟ & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        ବାଛ (pairs[2].ମୂଲ୍ୟ & RISCV_HWPROBE_MISALIGNED_MASK) {
            ସ୍ଥିତି RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                ଭାଙ୍ଗ;
            ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                ; /* do nothing */
        }
    }
#ନଚେତଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ଅଚଳ unsigned long hwcap = ff_getauxval(AT_HWCAP);

        ଯଦି (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        ଯଦି (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        ଯଦି (hwcap & HWCAP_RV('V'))
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
#ଯଦି defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#ଯଦି __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#ଯଦି __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#ଯଦି __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    ଫେରନ୍ତୁ ret;
}
