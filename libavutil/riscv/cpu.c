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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GNU_ಮೂಲ
# define GNU_ಮೂಲ
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/riscv/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_SYS_HWPROBE_H
#ಅನ್ತರ್ಭಾವ <sys/hwprobe.h>
#ಅಥವಾಆದರೆ HAVE_ASM_HWPROBE_H
#ಅನ್ತರ್ಭಾವ <asm/hwprobe.h>
#ಅನ್ತರ್ಭಾವ <asm/unistd.h>
#ಅನ್ತರ್ಭಾವ <sys/syscall.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ __riscv_hwprobe(ರಚನೆ riscv_hwprobe *ಜೋಡಿಗಳು, size_t pair_ಎಣಿಕೆ,
                           size_t cpu_ಎಣಿಕೆ, ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ *cpus,
                           ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ flags)
{
        ಹಿಂತಿರುಗಿ syscall(__NR_riscv_hwprobe, ಜೋಡಿಗಳು, pair_ಎಣಿಕೆ, cpu_ಎಣಿಕೆ, cpus,
                       flags);
}
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_riscv(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ ret = 0;
#ಆದರೆ HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ರಚನೆ riscv_hwprobe ಜೋಡಿಗಳು[] = {
        { RISCV_HWPROBE_ಕೀಲಿ_ತಳ_BEHAVIOR, 0 },
        { RISCV_HWPROBE_ಕೀಲಿ_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_ಕೀಲಿ_CPUPERF_0, 0 },
    };

    ಆದರೆ (__riscv_hwprobe(ಜೋಡಿಗಳು, FF_ARRAY_ELEMS(ಜೋಡಿಗಳು), 0, ಖಾಲಿ, 0) == 0) {
        ಆದರೆ (ಜೋಡಿಗಳು[0].ಮೌಲ್ಯ & RISCV_HWPROBE_ತಳ_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ RISCV_HWPROBE_IMA_V
        ಆದರೆ (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ RISCV_HWPROBE_EXT_ZVE32X
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            ಆದರೆ (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            ಆದರೆ (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                ಆದರೆ (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ RISCV_HWPROBE_EXT_ZBB
        ಆದರೆ (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#ಆದರೆ defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        ಆದರೆ ((ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBA) &&
            (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBB) &&
            (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ RISCV_HWPROBE_EXT_ZVBB
        ಆದರೆ (ಜೋಡಿಗಳು[1].ಮೌಲ್ಯ & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#ಆದರೆ_ಅಂತ್ಯ
        ಆಯ್ಕೆ (ಜೋಡಿಗಳು[2].ಮೌಲ್ಯ & RISCV_HWPROBE_MISALIGNED_ಮುಖವಾಡ) {
            ಸ್ಥಿತಿ RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ; /* do nothing */
        }
    }
#ಅಥವಾಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ hwcap = ff_getauxval(AT_HWCAP);

        ಆದರೆ (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        ಆದರೆ (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        ಆದರೆ (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#ಆದರೆ_ಅಂತ್ಯ

    /* If RV-V is enabled statically at compile-time, check the details. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#ಆದರೆ __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#ಆದರೆ __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ret;
}
