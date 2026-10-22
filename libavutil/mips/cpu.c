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

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"
#ضمن "config.h"
#ܐܢ defined __linux__ || defined __ANDROID__
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <sys/auxv.h>
#ضمن "asmdefs.h"
#ضمن "libavutil/avstring.h"
#endif

#ܐܢ defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

ساكن صحيح cpucfg_available(فراغ)
{
    ܦܢܐ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ساكن uint32_t read_cpucfg(uint32_t reg)
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
        ܦܢܐ __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

ساكن صحيح cpu_flags_cpucfg(فراغ)
{
    صحيح flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ܐܢ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ܐܢ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ܦܢܐ flags;
}

ساكن صحيح cpu_flags_cpuinfo(فراغ)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    حرف buf[200];
    صحيح flags = 0;

    ܐܢ (!f)
        ܦܢܐ -1;

    ܟܡܐ (fgets(buf, حجم(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ܐܢ (av_strstart(buf, "cpu model", عدم)) {
            ܐܢ (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ܐܢ (av_strstart(buf, "ASEs implemented", عدم)) {
            ܐܢ (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ܐܢ (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            اكسر;
        }
    }
    fclose(f);
    ܦܢܐ flags;
}
#endif

صحيح ff_get_cpu_flags_mips(فراغ)
{
#ܐܢ defined __linux__ || defined __ANDROID__
    ܐܢ (cpucfg_available())
        ܦܢܐ cpu_flags_cpucfg();
    ܐܚܪܢܐ
        ܦܢܐ cpu_flags_cpuinfo();
#ܐܚܪܢܐ
    /* Assume no SIMD ASE supported */
    ܦܢܐ 0;
#endif
}

size_t ff_get_cpu_max_align_mips(فراغ)
{
    صحيح flags = av_get_cpu_flags();

    ܐܢ (flags & AV_CPU_FLAG_MSA)
        ܦܢܐ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ܐܢ (flags & AV_CPU_FLAG_MMI)
        ܦܢܐ 16;

    ܦܢܐ 8;
}
