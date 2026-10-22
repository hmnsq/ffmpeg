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

#جيڪڏهن_وصف_نه_ٿيل GNU_ذريعو
# define GNU_ذريعو
#جيڪڏهن_پورو
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/riscv/cpu.h"
#ضمن "libavutil/cpu_internal.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/log.h"
#ضمن "config.h"

#إذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ضمن <sys/auxv.h>
#وصف_ڪريو HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#جيڪڏهن_پورو
#إذا HAVE_SYS_HWPROBE_H
#ضمن <sys/hwprobe.h>
#وإلاإذا HAVE_ASM_HWPROBE_H
#ضمن <asm/hwprobe.h>
#ضمن <asm/unistd.h>
#ضمن <sys/syscall.h>
#ضمن <unistd.h>

ساكن صحيح __riscv_hwprobe(بنية riscv_hwprobe *جوڙا, size_t pair_ڳڻپ,
                           size_t cpu_ڳڻپ, بنانشان ڊگهو *cpus,
                           بنانشان صحيح flags)
{
        أرجع syscall(__NR_riscv_hwprobe, جوڙا, pair_ڳڻپ, cpu_ڳڻپ, cpus,
                       flags);
}
#جيڪڏهن_پورو

صحيح ff_get_cpu_flags_riscv(فراغ)
{
    صحيح ret = 0;
#إذا HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    بنية riscv_hwprobe جوڙا[] = {
        { RISCV_HWPROBE_ڪنجي_بنياد_BEHAVIOR, 0 },
        { RISCV_HWPROBE_ڪنجي_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_ڪنجي_CPUPERF_0, 0 },
    };

    إذا (__riscv_hwprobe(جوڙا, FF_ARRAY_ELEMS(جوڙا), 0, عدم, 0) == 0) {
        إذا (جوڙا[0].قدر & RISCV_HWPROBE_بنياد_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#جيڪڏهن_وصف_ٿيل RISCV_HWPROBE_IMA_V
        إذا (جوڙا[1].قدر & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#جيڪڏهن_وصف_ٿيل RISCV_HWPROBE_EXT_ZVE32X
        وإلا إذا ((جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            إذا (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            إذا (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                إذا (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل RISCV_HWPROBE_EXT_ZBB
        إذا (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#إذا defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        إذا ((جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZBA) &&
            (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZBB) &&
            (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل RISCV_HWPROBE_EXT_ZVBB
        إذا (جوڙا[1].قدر & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#جيڪڏهن_پورو
        بدل (جوڙا[2].قدر & RISCV_HWPROBE_MISALIGNED_نقاب) {
            حالة RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                اكسر;
            افتراضي:
                ; /* do nothing */
        }
    }
#وإلاإذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ثابت بنانشان ڊگهو hwcap = ff_getauxval(AT_HWCAP);

        إذا (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        إذا (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        إذا (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#جيڪڏهن_پورو
#إذا defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#جيڪڏهن_پورو

    /* If RV-V is enabled statically at compile-time, check the details. */
#جيڪڏهن_وصف_ٿيل __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#إذا __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#جيڪڏهن_پورو
#إذا __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#إذا __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#جيڪڏهن_پورو

    أرجع ret;
}
