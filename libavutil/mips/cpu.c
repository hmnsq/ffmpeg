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
#གལ་སྲིད defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#གལ་སྲིད defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static ཧྲིལ cpucfg_available(void)
{
    ལོག ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        ལོག __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static ཧྲིལ cpu_flags_cpucfg(void)
{
    ཧྲིལ flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    གལ་སྲིད (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    གལ་སྲིད (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ལོག flags;
}

static ཧྲིལ cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    var_na buf[200];
    ཧྲིལ flags = 0;

    གལ་སྲིད (!f)
        ལོག -1;

    སྐབས (fgets(buf, parimaa_na(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        གལ་སྲིད (av_strstart(buf, "cpu model", NULL)) {
            གལ་སྲིད (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        གལ་སྲིད (av_strstart(buf, "ASEs implemented", NULL)) {
            གལ་སྲིད (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            གལ་སྲིད (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            bha_nga;
        }
    }
    fclose(f);
    ལོག flags;
}
#endif

ཧྲིལ ff_get_cpu_flags_mips(void)
{
#གལ་སྲིད defined __linux__ || defined __ANDROID__
    གལ་སྲིད (cpucfg_available())
        ལོག cpu_flags_cpucfg();
    དེ་མིན
        ལོག cpu_flags_cpuinfo();
#དེ་མིན
    /* Assume no SIMD ASE supported */
    ལོག 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    ཧྲིལ flags = av_get_cpu_flags();

    གལ་སྲིད (flags & AV_CPU_FLAG_MSA)
        ལོག 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    གལ་སྲིད (flags & AV_CPU_FLAG_MMI)
        ལོག 16;

    ལོག 8;
}
