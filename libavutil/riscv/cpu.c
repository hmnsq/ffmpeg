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
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/riscv/cpu.h"
#अन्तर्भाव "libavutil/cpu_internal.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "config.h"

#यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अन्तर्भाव <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#यदि HAVE_SYS_HWPROBE_H
#अन्तर्भाव <sys/hwprobe.h>
#नोचेद्यदि HAVE_ASM_HWPROBE_H
#अन्तर्भाव <asm/hwprobe.h>
#अन्तर्भाव <asm/unistd.h>
#अन्तर्भाव <sys/syscall.h>
#अन्तर्भाव <unistd.h>

स्थिर पूर्णाङ्क __riscv_hwprobe(संरचना riscv_hwprobe *pairs, size_t pair_मोजणी,
                           size_t cpu_मोजणी, unsigned long *cpus,
                           unsigned पूर्णाङ्क flags)
{
        प्रत्यागम syscall(__NR_riscv_hwprobe, pairs, pair_मोजणी, cpu_मोजणी, cpus,
                       flags);
}
#endif

पूर्णाङ्क ff_get_cpu_flags_riscv(शून्य)
{
    पूर्णाङ्क ret = 0;
#यदि HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    संरचना riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_किल्ली_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_किल्ली_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_किल्ली_CPUPERF_0, 0 },
    };

    यदि (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, रिक्त, 0) == 0) {
        यदि (pairs[0].मूल्य & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        यदि (pairs[1].मूल्य & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        अन्यथा यदि ((pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            यदि (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            यदि (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                यदि (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        यदि (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#यदि defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        यदि ((pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        यदि (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        विकल्प (pairs[2].मूल्य & RISCV_HWPROBE_MISALIGNED_MASK) {
            पक्ष RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                भङ्ग;
            स्वभाव:
                ; /* do nothing */
        }
    }
#नोचेद्यदि HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ध्रुव unsigned long hwcap = ff_getauxval(AT_HWCAP);

        यदि (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        यदि (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        यदि (hwcap & HWCAP_RV('V'))
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
#यदि defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#यदि __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#यदि __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#यदि __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    प्रत्यागम ret;
}
