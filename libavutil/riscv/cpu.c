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
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/riscv/cpu.h"
#അന്തര്ഭാവ "libavutil/cpu_internal.h"
#അന്തര്ഭാവ "libavutil/macros.h"
#അന്തര്ഭാവ "libavutil/log.h"
#അന്തര്ഭാവ "config.h"

#എങ്കിൽ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#അന്തര്ഭാവ <sys/auxv.h>
#define HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#endif
#എങ്കിൽ HAVE_SYS_HWPROBE_H
#അന്തര്ഭാവ <sys/hwprobe.h>
#അല്ലെങ്കിലെങ്കിൽ HAVE_ASM_HWPROBE_H
#അന്തര്ഭാവ <asm/hwprobe.h>
#അന്തര്ഭാവ <asm/unistd.h>
#അന്തര്ഭാവ <sys/syscall.h>
#അന്തര്ഭാവ <unistd.h>

സ്ഥിതം പൂർണ്ണസംഖ്യ __riscv_hwprobe(ഘടന riscv_hwprobe *pairs, size_t pair_എണ്ണം,
                           size_t cpu_എണ്ണം, unsigned long *cpus,
                           unsigned പൂർണ്ണസംഖ്യ flags)
{
        തിരികെ syscall(__NR_riscv_hwprobe, pairs, pair_എണ്ണം, cpu_എണ്ണം, cpus,
                       flags);
}
#endif

പൂർണ്ണസംഖ്യ ff_get_cpu_flags_riscv(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ ret = 0;
#എങ്കിൽ HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    ഘടന riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_താക്കോൽ_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_താക്കോൽ_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_താക്കോൽ_CPUPERF_0, 0 },
    };

    എങ്കിൽ (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, ശൂന്യ, 0) == 0) {
        എങ്കിൽ (pairs[0].മൂല്യം & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#ifdef RISCV_HWPROBE_IMA_V
        എങ്കിൽ (pairs[1].മൂല്യം & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#ifdef RISCV_HWPROBE_EXT_ZVE32X
        അല്ലെങ്കിൽ എങ്കിൽ ((pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            എങ്കിൽ (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            എങ്കിൽ (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                എങ്കിൽ (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZBB
        എങ്കിൽ (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#എങ്കിൽ defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        എങ്കിൽ ((pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#endif
#endif
#ifdef RISCV_HWPROBE_EXT_ZVBB
        എങ്കിൽ (pairs[1].മൂല്യം & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#endif
        തിരഞ്ഞെടുപ്പ് (pairs[2].മൂല്യം & RISCV_HWPROBE_MISALIGNED_MASK) {
            അവസ്ഥ RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                നിർത്തുക;
            സ്ഥിരസ്ഥിതി:
                ; /* do nothing */
        }
    }
#അല്ലെങ്കിലെങ്കിൽ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        സ്ഥിരം unsigned long hwcap = ff_getauxval(AT_HWCAP);

        എങ്കിൽ (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        എങ്കിൽ (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        എങ്കിൽ (hwcap & HWCAP_RV('V'))
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
#എങ്കിൽ defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#endif

    /* If RV-V is enabled statically at compile-time, check the details. */
#ifdef __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#എങ്കിൽ __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#endif
#എങ്കിൽ __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#എങ്കിൽ __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#endif
#endif
#endif
#ifdef __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#endif

    തിരികെ ret;
}
