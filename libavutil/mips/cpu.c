/*
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

#شامل "libavutil/cpu.h"
#شامل "libavutil/cpu_internal.h"
#شامل "config.h"
#اگر defined __linux__ || defined __ANDROID__
#شامل <stdint.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل <sys/auxv.h>
#شامل "asmdefs.h"
#شامل "libavutil/avstring.h"
#اگر_ختم

#اگر defined __linux__ || defined __ANDROID__

#تعریف_کرو HWCAP_LOONGSON_CPUCFG (1 << 14)

ساکن صحیح cpucfg_دستیاب(خالی)
{
    واپس ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ساکن uint32_t read_cpucfg(uint32_t reg)
{
        uint32_t __res;

        __asm__ __volatile__(
                "parse_r __res,%0\n\t"
                "parse_r reg,%1\n\t"
                ".insn \n\t"
                ".word (0xc8080118 | (reg << 21) | (__res << 11))\n\t"
                :"=r"(__res)
                :"r"(reg)
                :
                );
        واپس __res;
}

#تعریف_کرو LOONGSON_CFG1 0x1

#تعریف_کرو LOONGSON_CFG1_MMI    (1 << 4)
#تعریف_کرو LOONGSON_CFG1_MSA1   (1 << 5)

ساکن صحیح cpu_flags_cpucfg(خالی)
{
    صحیح flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    اگر (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    اگر (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    واپس flags;
}

ساکن صحیح cpu_flags_cpuinfo(خالی)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    حرف buf[200];
    صحیح flags = 0;

    اگر (!f)
        واپس -1;

    جب (fgets(buf, حجم(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        اگر (av_strstart(buf, "cpu model", تہی)) {
            اگر (لڑی_تلاش(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        اگر (av_strstart(buf, "ASEs implemented", تہی)) {
            اگر (لڑی_تلاش(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            اگر (لڑی_تلاش(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            توڑو;
        }
    }
    fclose(f);
    واپس flags;
}
#اگر_ختم

صحیح ff_get_cpu_flags_mips(خالی)
{
#اگر defined __linux__ || defined __ANDROID__
    اگر (cpucfg_دستیاب())
        واپس cpu_flags_cpucfg();
    ورنہ
        واپس cpu_flags_cpuinfo();
#ورنہ
    /* Assume no SIMD ASE supported */
    واپس 0;
#اگر_ختم
}

size_t ff_get_cpu_max_align_mips(خالی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_MSA)
        واپس 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    اگر (flags & AV_CPU_FLAG_MMI)
        واپس 16;

    واپس 8;
}
