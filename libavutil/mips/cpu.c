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
#nếu defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#nếu defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static số_nguyên cpucfg_available(void)
{
    trả_về ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        trả_về __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static số_nguyên cpu_flags_cpucfg(void)
{
    số_nguyên flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    nếu (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    nếu (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    trả_về flags;
}

static số_nguyên cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char buf[200];
    số_nguyên flags = 0;

    nếu (!f)
        trả_về -1;

    trong_khi (fgets(buf, sizeof(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        nếu (av_strstart(buf, "cpu model", NULL)) {
            nếu (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        nếu (av_strstart(buf, "ASEs implemented", NULL)) {
            nếu (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            nếu (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            break;
        }
    }
    fclose(f);
    trả_về flags;
}
#endif

số_nguyên ff_get_cpu_flags_mips(void)
{
#nếu defined __linux__ || defined __ANDROID__
    nếu (cpucfg_available())
        trả_về cpu_flags_cpucfg();
    không_thì
        trả_về cpu_flags_cpuinfo();
#không_thì
    /* Assume no SIMD ASE supported */
    trả_về 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    số_nguyên flags = av_get_cpu_flags();

    nếu (flags & AV_CPU_FLAG_MSA)
        trả_về 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    nếu (flags & AV_CPU_FLAG_MMI)
        trả_về 16;

    trả_về 8;
}
