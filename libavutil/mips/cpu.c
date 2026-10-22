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
#ถ้า defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#ถ้า defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static จำนวนเต็ม cpucfg_available(void)
{
    คืน ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        คืน __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static จำนวนเต็ม cpu_flags_cpucfg(void)
{
    จำนวนเต็ม flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ถ้า (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ถ้า (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    คืน flags;
}

static จำนวนเต็ม cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    var_na buf[200];
    จำนวนเต็ม flags = 0;

    ถ้า (!f)
        คืน -1;

    ขณะ (fgets(buf, parimaa_na(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ถ้า (av_strstart(buf, "cpu model", NULL)) {
            ถ้า (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ถ้า (av_strstart(buf, "ASEs implemented", NULL)) {
            ถ้า (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ถ้า (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            bha_nga;
        }
    }
    fclose(f);
    คืน flags;
}
#endif

จำนวนเต็ม ff_get_cpu_flags_mips(void)
{
#ถ้า defined __linux__ || defined __ANDROID__
    ถ้า (cpucfg_available())
        คืน cpu_flags_cpucfg();
    มิฉะนั้น
        คืน cpu_flags_cpuinfo();
#มิฉะนั้น
    /* Assume no SIMD ASE supported */
    คืน 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    จำนวนเต็ม flags = av_get_cpu_flags();

    ถ้า (flags & AV_CPU_FLAG_MSA)
        คืน 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ถ้า (flags & AV_CPU_FLAG_MMI)
        คืน 16;

    คืน 8;
}
