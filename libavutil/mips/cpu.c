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
#만약 defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#만약 defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static 정수 cpucfg_available(void)
{
    반환 ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        반환 __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static 정수 cpu_flags_cpucfg(void)
{
    정수 flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    만약 (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    만약 (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    반환 flags;
}

static 정수 cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    char buf[200];
    정수 flags = 0;

    만약 (!f)
        반환 -1;

    동안 (fgets(buf, sizeof(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        만약 (av_strstart(buf, "cpu model", NULL)) {
            만약 (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        만약 (av_strstart(buf, "ASEs implemented", NULL)) {
            만약 (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            만약 (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            break;
        }
    }
    fclose(f);
    반환 flags;
}
#endif

정수 ff_get_cpu_flags_mips(void)
{
#만약 defined __linux__ || defined __ANDROID__
    만약 (cpucfg_available())
        반환 cpu_flags_cpucfg();
    아니면
        반환 cpu_flags_cpuinfo();
#아니면
    /* Assume no SIMD ASE supported */
    반환 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    정수 flags = av_get_cpu_flags();

    만약 (flags & AV_CPU_FLAG_MSA)
        반환 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    만약 (flags & AV_CPU_FLAG_MMI)
        반환 16;

    반환 8;
}
