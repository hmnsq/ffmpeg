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
#ꦪꦼꦤ꧀ defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#ꦪꦼꦤ꧀ defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static puur_naa_nka cpucfg_available(void)
{
    ꦮꦭꦶ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        ꦮꦭꦶ __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static puur_naa_nka cpu_flags_cpucfg(void)
{
    puur_naa_nka flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ꦪꦼꦤ꧀ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ꦪꦼꦤ꧀ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ꦮꦭꦶ flags;
}

static puur_naa_nka cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    var_na buf[200];
    puur_naa_nka flags = 0;

    ꦪꦼꦤ꧀ (!f)
        ꦮꦭꦶ -1;

    ꦱꦼꦢꦼꦭ (fgets(buf, parimaa_na(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ꦪꦼꦤ꧀ (av_strstart(buf, "cpu model", NULL)) {
            ꦪꦼꦤ꧀ (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ꦪꦼꦤ꧀ (av_strstart(buf, "ASEs implemented", NULL)) {
            ꦪꦼꦤ꧀ (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ꦪꦼꦤ꧀ (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            bha_nga;
        }
    }
    fclose(f);
    ꦮꦭꦶ flags;
}
#endif

puur_naa_nka ff_get_cpu_flags_mips(void)
{
#ꦪꦼꦤ꧀ defined __linux__ || defined __ANDROID__
    ꦪꦼꦤ꧀ (cpucfg_available())
        ꦮꦭꦶ cpu_flags_cpucfg();
    ꦭꦶꦪ
        ꦮꦭꦶ cpu_flags_cpuinfo();
#ꦭꦶꦪ
    /* Assume no SIMD ASE supported */
    ꦮꦭꦶ 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    puur_naa_nka flags = av_get_cpu_flags();

    ꦪꦼꦤ꧀ (flags & AV_CPU_FLAG_MSA)
        ꦮꦭꦶ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ꦪꦼꦤ꧀ (flags & AV_CPU_FLAG_MMI)
        ꦮꦭꦶ 16;

    ꦮꦭꦶ 8;
}
