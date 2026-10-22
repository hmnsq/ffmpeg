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

#जर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अन्तर्भाव <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#जर HAVE_SYS_HWPROBE_H
#अन्तर्भाव <sys/hwprobe.h>
#किंवाजर HAVE_ASM_HWPROBE_H
#अन्तर्भाव <asm/hwprobe.h>
#अन्तर्भाव <asm/unistd.h>
#अन्तर्भाव <sys/syscall.h>
#अन्तर्भाव <unistd.h>

स्थिर पूर्णांक __riscv_hwprobe(संरचना riscv_hwprobe *pairs, माप_प्रकार pair_मोजणी,
                           माप_प्रकार cpu_मोजणी, अचिन्हित दीर्घ *cpus,
                           अचिन्हित पूर्णांक flags)
{
        परत syscall(__NR_riscv_hwprobe, pairs, pair_मोजणी, cpu_मोजणी, cpus,
                       flags);
}
#endif

पूर्णांक ff_get_cpu_flags_riscv(शून्य)
{
    पूर्णांक ret = 0;
#जर HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    संरचना riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_किल्ली_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_किल्ली_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_किल्ली_CPUPERF_0, 0 },
    };

    जर (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, रिक्त, 0) == 0) {
        जर (pairs[0].मूल्य & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        जर (pairs[1].मूल्य & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        अन्यथा जर ((pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            जर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            जर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                जर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        जर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#जर defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        जर ((pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        जर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        निवड (pairs[2].मूल्य & RISCV_HWPROBE_MISALIGNED_MASK) {
            स्थिती RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                थांबा;
            पूर्वनिर्धारित:
                ; /* do nothing */
        }
    }
#किंवाजर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        स्थिरांक अचिन्हित दीर्घ hwcap = ff_getauxval(AT_HWCAP);

        जर (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        जर (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        जर (hwcap & HWCAP_RV('V'))
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
#जर defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#जर __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#जर __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#जर __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    परत ret;
}
