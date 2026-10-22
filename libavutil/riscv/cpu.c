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

#अगर_अघोषित _GNU_SOURCE
# define _GNU_SOURCE
#पूर्ण_अगर
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/riscv/cpu.h"
#समावेश "libavutil/cpu_internal.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/log.h"
#समावेश "config.h"

#अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#समावेश <sys/auxv.h>
#घोषणा HWCAP_RV(letter) (1ul << ((letter) - 'A'))
#पूर्ण_अगर
#अगर HAVE_SYS_HWPROBE_H
#समावेश <sys/hwprobe.h>
#या_अगर HAVE_ASM_HWPROBE_H
#समावेश <asm/hwprobe.h>
#समावेश <asm/unistd.h>
#समावेश <sys/syscall.h>
#समावेश <unistd.h>

अटल पूर्णांक __riscv_hwprobe(काष्ठा riscv_hwprobe *pairs, माप_प्रकार pair_गिनती,
                           माप_प्रकार cpu_गिनती, अचिन्हित दीर्घ *cpus,
                           अचिन्हित पूर्णांक flags)
{
        वापस syscall(__NR_riscv_hwprobe, pairs, pair_गिनती, cpu_गिनती, cpus,
                       flags);
}
#पूर्ण_अगर

पूर्णांक ff_get_cpu_flags_riscv(व्योम)
{
    पूर्णांक ret = 0;
#अगर HAVE_SYS_HWPROBE_H || HAVE_ASM_HWPROBE_H
    काष्ठा riscv_hwprobe pairs[] = {
        { RISCV_HWPROBE_कुंजी_BASE_BEHAVIOR, 0 },
        { RISCV_HWPROBE_कुंजी_IMA_EXT_0, 0 },
        { RISCV_HWPROBE_कुंजी_CPUPERF_0, 0 },
    };

    अगर (__riscv_hwprobe(pairs, FF_ARRAY_ELEMS(pairs), 0, शून्य, 0) == 0) {
        अगर (pairs[0].मूल्य & RISCV_HWPROBE_BASE_BEHAVIOR_IMA)
            ret |= AV_CPU_FLAG_RVI;
#अगर_घोषित RISCV_HWPROBE_IMA_V
        अगर (pairs[1].मूल्य & RISCV_HWPROBE_IMA_V)
            ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                 | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
#अगर_घोषित RISCV_HWPROBE_EXT_ZVE32X
        अन्यथा अगर ((pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE32X) &&
                 ff_get_rv_vlenb() >= 16) { // runtime detect assumes 128+ bits
            ret |= AV_CPU_FLAG_RVV_I32;

            अगर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE32F)
                ret |= AV_CPU_FLAG_RVV_F32;
            अगर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE64X) {
                ret |= AV_CPU_FLAG_RVV_I64;

                अगर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVE64D)
                    ret |= AV_CPU_FLAG_RVV_F64;
            }
        }
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित RISCV_HWPROBE_EXT_ZBB
        अगर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBB)
            ret |= AV_CPU_FLAG_RVB_BASIC;
#अगर defined (RISCV_HWPROBE_EXT_ZBA) && defined (RISCV_HWPROBE_EXT_ZBS)
        अगर ((pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBA) &&
            (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBB) &&
            (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZBS))
            ret |= AV_CPU_FLAG_RVB;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित RISCV_HWPROBE_EXT_ZVBB
        अगर (pairs[1].मूल्य & RISCV_HWPROBE_EXT_ZVBB)
            ret |= AV_CPU_FLAG_RV_ZVBB;
#पूर्ण_अगर
        चयन (pairs[2].मूल्य & RISCV_HWPROBE_MISALIGNED_MASK) {
            हाल RISCV_HWPROBE_MISALIGNED_FAST:
                ret |= AV_CPU_FLAG_RV_MISALIGNED;
                अवरोध;
            शेष:
                ; /* do nothing */
        }
    }
#या_अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
    {
        स्थिर अचिन्हित दीर्घ hwcap = ff_getauxval(AT_HWCAP);

        अगर (hwcap & HWCAP_RV('I'))
            ret |= AV_CPU_FLAG_RVI;
        अगर (hwcap & HWCAP_RV('B'))
            ret |= AV_CPU_FLAG_RVB_BASIC | AV_CPU_FLAG_RVB;

        /* The V extension implies all Zve* functional subsets */
        अगर (hwcap & HWCAP_RV('V'))
             ret |= AV_CPU_FLAG_RVV_I32 | AV_CPU_FLAG_RVV_I64
                  | AV_CPU_FLAG_RVV_F32 | AV_CPU_FLAG_RVV_F64;
    }
#पूर्ण_अगर

#अगर_घोषित __riscv_i
    ret |= AV_CPU_FLAG_RVI;
#पूर्ण_अगर

#अगर_घोषित __riscv_zbb
    ret |= AV_CPU_FLAG_RVB_BASIC;
#पूर्ण_अगर
#अगर defined (__riscv_b) || \
    (defined (__riscv_zba) && defined (__riscv_zbb) && defined (__riscv_zbs))
    ret |= AV_CPU_FLAG_RVB;
#पूर्ण_अगर

    /* If RV-V is enabled statically at compile-time, check the details. */
#अगर_घोषित __riscv_vector
    ret |= AV_CPU_FLAG_RVV_I32;
#अगर __riscv_v_elen >= 64
    ret |= AV_CPU_FLAG_RVV_I64;
#पूर्ण_अगर
#अगर __riscv_v_elen_fp >= 32
    ret |= AV_CPU_FLAG_RVV_F32;
#अगर __riscv_v_elen_fp >= 64
    ret |= AV_CPU_FLAG_RVV_F64;
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित __riscv_zvbb
    ret |= AV_CPU_FLAG_RV_ZVBB;
#पूर्ण_अगर

    वापस ret;
}
