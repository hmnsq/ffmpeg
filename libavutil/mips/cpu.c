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
#endif

#اگر defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

ایستا صحیح cpucfg_available(تهی)
{
    بازگشت ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ایستا uint32_t read_cpucfg(uint32_t reg)
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
        بازگشت __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

ایستا صحیح cpu_flags_cpucfg(تهی)
{
    صحیح flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    اگر (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    اگر (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    بازگشت flags;
}

ایستا صحیح cpu_flags_cpuinfo(تهی)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    نویسه buf[200];
    صحیح flags = 0;

    اگر (!f)
        بازگشت -1;

    وقتی (fgets(buf, اندازه(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        اگر (av_strstart(buf, "cpu model", پوچ)) {
            اگر (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        اگر (av_strstart(buf, "ASEs implemented", پوچ)) {
            اگر (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            اگر (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            بشکن;
        }
    }
    fclose(f);
    بازگشت flags;
}
#endif

صحیح ff_get_cpu_flags_mips(تهی)
{
#اگر defined __linux__ || defined __ANDROID__
    اگر (cpucfg_available())
        بازگشت cpu_flags_cpucfg();
    وگرنه
        بازگشت cpu_flags_cpuinfo();
#وگرنه
    /* Assume no SIMD ASE supported */
    بازگشت 0;
#endif
}

size_t ff_get_cpu_max_align_mips(تهی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_MSA)
        بازگشت 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    اگر (flags & AV_CPU_FLAG_MMI)
        بازگشت 16;

    بازگشت 8;
}
