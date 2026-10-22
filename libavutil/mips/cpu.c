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
#නම් defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#නම් defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static පූර්ණ_සංඛ්‍යා cpucfg_available(void)
{
    ආපසු ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        ආපසු __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static පූර්ණ_සංඛ්‍යා cpu_flags_cpucfg(void)
{
    පූර්ණ_සංඛ්‍යා flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    නම් (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    නම් (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ආපසු flags;
}

static පූර්ණ_සංඛ්‍යා cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    var_na buf[200];
    පූර්ණ_සංඛ්‍යා flags = 0;

    නම් (!f)
        ආපසු -1;

    අතරතුර (fgets(buf, parimaa_na(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        නම් (av_strstart(buf, "cpu model", NULL)) {
            නම් (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        නම් (av_strstart(buf, "ASEs implemented", NULL)) {
            නම් (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            නම් (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            bha_nga;
        }
    }
    fclose(f);
    ආපසු flags;
}
#endif

පූර්ණ_සංඛ්‍යා ff_get_cpu_flags_mips(void)
{
#නම් defined __linux__ || defined __ANDROID__
    නම් (cpucfg_available())
        ආපසු cpu_flags_cpucfg();
    නැතහොත්
        ආපසු cpu_flags_cpuinfo();
#නැතහොත්
    /* Assume no SIMD ASE supported */
    ආපසු 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    පූර්ණ_සංඛ්‍යා flags = av_get_cpu_flags();

    නම් (flags & AV_CPU_FLAG_MSA)
        ආපසු 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    නම් (flags & AV_CPU_FLAG_MMI)
        ආපසු 16;

    ආපසු 8;
}
