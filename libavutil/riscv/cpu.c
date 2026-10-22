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

#اگر_غیر_تعریف_شدہ GNU_ماخذ
# define GNU_ماخذ
#اگر_ختم
#شامل "libavutil/cpu.h"
#شامل "libavutil/riscv/cpu.h"
#شامل "libavutil/cpu_internal.h"
#شامل "libavutil/macros.h"
#شامل "libavutil/log.h"
#شامل "config.h"

#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#شامل <sys/auxv.h>
#تعریف_کرو HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#اگر_ختم
#اگر HAVE_SYS_HWPROBE_H
#شامل <sys/hwprobe.h>
#وگرنہ_اگر HAVE_ASM_HWPROBE_H
#شامل <asm/hwprobe.h>
#شامل <asm/unistd.h>
#شامل <sys/syscall.h>
#شامل <unistd.h>

ساکن صحیح __riscv_hwprobe(ساخت riscv_hwprobe *جوڑے, size_t pair_گنتی,
                           size_t cpu_گنتی, غیرعلامتی طویل *cpus,
                           غیرعلامتی صحیح flags)
{
        واپس syscall(__NR_riscv_hwprobe, جوڑے, pair_گنتی, cpu_گنتی, cpus,
                       flags);
}
#اگر_ختم

صحیح ff_get_cpu_flags_riscv(خالی)
{
    صحیح ret = 0;
#اگر HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ساخت riscv_hwprobe جوڑے[] = {
        { RISCV_HWPROBE_کلید_بنیاد_BEHAVIOR, 0 },
        { RISCV_HWPROBE_کلید_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_کلید_CPUPERF_0, 0 },
    };

    اگر (__riscv_hwprobe(جوڑے, FF_ARRAY_ELEMS(جوڑے), 0, تہی, 0) == 0) {
        اگر (جوڑے[0].قدر & RISCV_HWPROBE_بنیاد_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#اگر_تعریف_شدہ RISCV_HWPROBE_IMA_V
        اگر (جوڑے[1].قدر & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#اگر_تعریف_شدہ RISCV_HWPROBE_EXT_ZVE32X
        ورنہ اگر ((جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            اگر (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            اگر (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                اگر (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#اگر_ختم
#اگر_ختم
#اگر_تعریف_شدہ RISCV_HWPROBE_EXT_ZBB
        اگر (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#اگر defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        اگر ((جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZBA) &&
            (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZBB) &&
            (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#اگر_ختم
#اگر_ختم
#اگر_تعریف_شدہ RISCV_HWPROBE_EXT_ZVBB
        اگر (جوڑے[1].قدر & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#اگر_ختم
        انتخاب (جوڑے[2].قدر & RISCV_HWPROBE_MISALIGNED_نقاب) {
            حالت RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                توڑو;
            طےشدہ:
                ; /* do nothing */
        }
    }
#وگرنہ_اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ثابت غیرعلامتی طویل hwcap = ff_getauxval(AT_HWCAP);

        اگر (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        اگر (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        اگر (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#اگر_ختم

#اگر_تعریف_شدہ __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#اگر_ختم

#اگر_تعریف_شدہ __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#اگر_ختم
#اگر defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#اگر_ختم

    /* If RV-V is enabled statically at compile-time, check the details. */
#اگر_تعریف_شدہ __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#اگر __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#اگر_ختم
#اگر __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#اگر __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#اگر_ختم
#اگر_ختم
#اگر_ختم
#اگر_تعریف_شدہ __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#اگر_ختم

    واپس ret;
}
