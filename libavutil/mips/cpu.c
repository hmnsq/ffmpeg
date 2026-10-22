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

#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu_internal.h"
#ଅନ୍ତର୍ଭାଵ "config.h"
#ଯଦି defined __linux__ || defined __ANDROID__
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>
#ଅନ୍ତର୍ଭାଵ "asmdefs.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/avstring.h"
#endif

#ଯଦି defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpucfg_available(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ସ୍ଥିର uint32_t read_cpucfg(uint32_t reg)
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
        ଫେରନ୍ତୁ __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags_cpucfg(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ଯଦି (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ଯଦି (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ଫେରନ୍ତୁ flags;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags_cpuinfo(ଶୂନ୍ୟ)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ଅକ୍ଷର buf[200];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;

    ଯଦି (!f)
        ଫେରନ୍ତୁ -1;

    ଯେତେବେଳେ (fgets(buf, ଆକାର(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ଯଦି (av_strstart(buf, "cpu model", ଖାଲି)) {
            ଯଦି (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ଯଦି (av_strstart(buf, "ASEs implemented", ଖାଲି)) {
            ଯଦି (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ଯଦି (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            ଭାଙ୍ଗ;
        }
    }
    fclose(f);
    ଫେରନ୍ତୁ flags;
}
#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_mips(ଶୂନ୍ୟ)
{
#ଯଦି defined __linux__ || defined __ANDROID__
    ଯଦି (cpucfg_available())
        ଫେରନ୍ତୁ cpu_flags_cpucfg();
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ cpu_flags_cpuinfo();
#ଅନ୍ୟଥା
    /* Assume no SIMD ASE supported */
    ଫେରନ୍ତୁ 0;
#endif
}

size_t ff_get_cpu_max_align_mips(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & AV_CPU_FLAG_MSA)
        ଫେରନ୍ତୁ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ଯଦି (flags & AV_CPU_FLAG_MMI)
        ଫେରନ୍ତୁ 16;

    ଫେରନ୍ତୁ 8;
}
