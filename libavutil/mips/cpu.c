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
#ຖ້າ defined __linux__ || defined __ANDROID__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/auxv.h>
#include "asmdefs.h"
#include "libavutil/avstring.h"
#endif

#ຖ້າ defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

static ຈຳນວນເຕັມ cpucfg_available(void)
{
    ສົ່ງຄືນ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        ສົ່ງຄືນ __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

static ຈຳນວນເຕັມ cpu_flags_cpucfg(void)
{
    ຈຳນວນເຕັມ flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ຖ້າ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ຖ້າ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ສົ່ງຄືນ flags;
}

static ຈຳນວນເຕັມ cpu_flags_cpuinfo(void)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    var_na buf[200];
    ຈຳນວນເຕັມ flags = 0;

    ຖ້າ (!f)
        ສົ່ງຄືນ -1;

    ໃນຂະນະທີ່ (fgets(buf, parimaa_na(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ຖ້າ (av_strstart(buf, "cpu model", NULL)) {
            ຖ້າ (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ຖ້າ (av_strstart(buf, "ASEs implemented", NULL)) {
            ຖ້າ (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ຖ້າ (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            bha_nga;
        }
    }
    fclose(f);
    ສົ່ງຄືນ flags;
}
#endif

ຈຳນວນເຕັມ ff_get_cpu_flags_mips(void)
{
#ຖ້າ defined __linux__ || defined __ANDROID__
    ຖ້າ (cpucfg_available())
        ສົ່ງຄືນ cpu_flags_cpucfg();
    ບໍ່ດັ່ງນັ້ນ
        ສົ່ງຄືນ cpu_flags_cpuinfo();
#ບໍ່ດັ່ງນັ້ນ
    /* Assume no SIMD ASE supported */
    ສົ່ງຄືນ 0;
#endif
}

size_t ff_get_cpu_max_align_mips(void)
{
    ຈຳນວນເຕັມ flags = av_get_cpu_flags();

    ຖ້າ (flags & AV_CPU_FLAG_MSA)
        ສົ່ງຄືນ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ຖ້າ (flags & AV_CPU_FLAG_MMI)
        ສົ່ງຄືນ 16;

    ສົ່ງຄືນ 8;
}
