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

#include "libavutil/cpu.h"
#include "libavutil/cpu_internal.h"
#include "config.h"
#если defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#если defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static целое cpucfg_available(void)
{
    вернуть ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
static uint32_t read_cpucfg(uint32_t reg)
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
        вернуть __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static целое cpu_flags_cpucfg(void)
{
    целое flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    если (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    если (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    вернуть flags;
}

static целое cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char buf[200];
    целое flags = 0;

    если (!f)
        вернуть -1;

    пока (fgets(buf, sizeof(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        если (av_strstart(buf, "cpu model", NULL)) {
            если (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        если (av_strstart(buf, "ASEs implemented", NULL)) {
            если (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            если (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            break;
        }
    }
    fclose(f);
    вернуть flags;
}
#endif

целое ff_get_cpu_flags_mips(void)
{
#если defined __linux__ || defined __ANDROID__
    если (cpucfg_available())
        вернуть cpu_flags_cpucfg();
    иначе
        вернуть cpu_flags_cpuinfo();
#иначе
    /* Assume no SIMD ASE supported */
    вернуть 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    целое flags = av_get_cpu_flags();

    если (flags & AV_CPU_FLAG_MSA)
        вернуть 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    если (flags & AV_CPU_FLAG_MMI)
        вернуть 16;

    вернуть 8;
}
