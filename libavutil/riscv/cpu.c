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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GNU_ਸਰੋਤ
# define GNU_ਸਰੋਤ
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/riscv/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_SYS_HWPROBE_H
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/hwprobe.h>
#ਜਾਂਜੇ HAVE_ASM_HWPROBE_H
#ਅਨ੍ਤਰ੍ਭਾਵ <asm/hwprobe.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <asm/unistd.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/syscall.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

ਸਥਿਰ ਪੂਰਨ __riscv_hwprobe(ਬਣਤਰ riscv_hwprobe *ਜੋੜੇ, size_t pair_ਗਿਣਤੀ,
                           size_t cpu_ਗਿਣਤੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ *cpus,
                           ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ flags)
{
        ਵਾਪਸ syscall(__NR_riscv_hwprobe, ਜੋੜੇ, pair_ਗਿਣਤੀ, cpu_ਗਿਣਤੀ, cpus,
                       flags);
}
#ਜੇ_ਅੰਤ

ਪੂਰਨ ff_get_cpu_flags_riscv(ਖਾਲੀ)
{
    ਪੂਰਨ ret = 0;
#ਜੇ HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ਬਣਤਰ riscv_hwprobe ਜੋੜੇ[] = {
        { RISCV_HWPROBE_ਕੁੰਜੀ_ਅਧਾਰ_BEHAVIOR, 0 },
        { RISCV_HWPROBE_ਕੁੰਜੀ_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_ਕੁੰਜੀ_CPUPERF_0, 0 },
    };

    ਜੇ (__riscv_hwprobe(ਜੋੜੇ, FF_ARRAY_ELEMS(ਜੋੜੇ), 0, ਨਿਰਾ, 0) == 0) {
        ਜੇ (ਜੋੜੇ[0].ਮੁੱਲ & RISCV_HWPROBE_ਅਧਾਰ_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ RISCV_HWPROBE_IMA_V
        ਜੇ (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ RISCV_HWPROBE_EXT_ZVE32X
        ਨਹੀਂਤਾਂ ਜੇ ((ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            ਜੇ (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            ਜੇ (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                ਜੇ (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ RISCV_HWPROBE_EXT_ZBB
        ਜੇ (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#ਜੇ defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        ਜੇ ((ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZBA) &&
            (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZBB) &&
            (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ RISCV_HWPROBE_EXT_ZVBB
        ਜੇ (ਜੋੜੇ[1].ਮੁੱਲ & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#ਜੇ_ਅੰਤ
        ਚੋਣ (ਜੋੜੇ[2].ਮੁੱਲ & RISCV_HWPROBE_MISALIGNED_ਨਕਾਬ) {
            ਹਾਲਤ RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                ਰੋਕੋ;
            ਮੂਲ:
                ; /* do nothing */
        }
    }
#ਜਾਂਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ hwcap = ff_getauxval(AT_HWCAP);

        ਜੇ (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        ਜੇ (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        ਜੇ (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#ਜੇ_ਅੰਤ
#ਜੇ defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#ਜੇ_ਅੰਤ

    /* If RV-V is enabled statically at compile-time, check the details. */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#ਜੇ __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#ਜੇ_ਅੰਤ
#ਜੇ __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#ਜੇ __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ret;
}
