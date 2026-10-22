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
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/riscv/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "config.h"

#ಯದಿ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#ಯದಿ HAVE_SYS_HWPROBE_H
#ಅನ್ತರ್ಭಾವ <sys/hwprobe.h>
#ನೋಚೇದ್ಯದಿ HAVE_ASM_HWPROBE_H
#ಅನ್ತರ್ಭಾವ <asm/hwprobe.h>
#ಅನ್ತರ್ಭಾವ <asm/unistd.h>
#ಅನ್ತರ್ಭಾವ <sys/syscall.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ __riscv_hwprobe(ಸಂರಚನಾ riscv_hwprobe *pairs, size_t pair_ಎಣಿಕೆ,
                           size_t cpu_ಎಣಿಕೆ, unsigned long *cpus,
                           unsigned ಪೂರ್ಣಾಙ್ಕ flags)
{
        ಪ್ರತ್ಯಾಗಮ syscall(__NR_riscv_hwprobe, pairs, pair_ಎಣಿಕೆ, cpu_ಎಣಿಕೆ, cpus,
                       flags);
}
#endif

ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_riscv(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ ret = 0;
#ಯದಿ HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ಸಂರಚನಾ riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_ಕೀಲಿ_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_ಕೀಲಿ_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_ಕೀಲಿ_CPUPERF_0, 0 },
    };

    ಯದಿ (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, ರಿಕ್ತ, 0) == 0) {
        ಯದಿ (pairs[0].ಮೌಲ್ಯ & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        ಯದಿ (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        ಅನ್ಯಥಾ ಯದಿ ((pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            ಯದಿ (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            ಯದಿ (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                ಯದಿ (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        ಯದಿ (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#ಯದಿ defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        ಯದಿ ((pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        ಯದಿ (pairs[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        ವಿಕಲ್ಪ (pairs[2].ಮೌಲ್ಯ & RISCV_HWPROBE_MISALIGNED_MASK) {
            ಪಕ್ಷ RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                ಭಙ್ಗ;
            ಸ್ವಭಾವ:
                ; /* do nothing */
        }
    }
#ನೋಚೇದ್ಯದಿ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ಧ್ರುವ unsigned long hwcap = ff_getauxval(AT_HWCAP);

        ಯದಿ (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        ಯದಿ (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        ಯದಿ (hwcap & HWCAP_RV('V'))
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
#ಯದಿ defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#ಯದಿ __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#ಯದಿ __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#ಯದಿ __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    ಪ್ರತ್ಯಾಗಮ ret;
}
