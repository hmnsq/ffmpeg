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

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/cpu_internal.h"
#అన్తర్భావ "config.h"
#ఒకవేళ defined __linux__ || defined __ANDROID__
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/auxv.h>
#అన్తర్భావ "asmdefs.h"
#అన్తర్భావ "libavutil/avstring.h"
#అయితే_ముగింపు

#ఒకవేళ defined __linux__ || defined __ANDROID__

#నిర్వచించు HWCAP_LOONGSON_CPUCFG (1 << 14)

స్థిర పూర్ణాంకం cpucfg_అందుబాటు(శూన్య)
{
    తిరిగి ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
స్థిర uint32_t read_cpucfg(uint32_t reg)
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
        తిరిగి __res;
}

#నిర్వచించు LOONGSON_CFG1 0x1

#నిర్వచించు LOONGSON_CFG1_MMI    (1 << 4)
#నిర్వచించు LOONGSON_CFG1_MSA1   (1 << 5)

స్థిర పూర్ణాంకం cpu_flags_cpucfg(శూన్య)
{
    పూర్ణాంకం flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ఒకవేళ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ఒకవేళ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    తిరిగి flags;
}

స్థిర పూర్ణాంకం cpu_flags_cpuinfo(శూన్య)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    అక్షరం buf[200];
    పూర్ణాంకం flags = 0;

    ఒకవేళ (!f)
        తిరిగి -1;

    అయితే (fgets(buf, పరిమాణం(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ఒకవేళ (av_strstart(buf, "cpu model", ఖాళీ)) {
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ఒకవేళ (av_strstart(buf, "ASEs implemented", ఖాళీ)) {
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ఒకవేళ (అక్షరశ్రేణి_శోధన(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            ఆపు;
        }
    }
    fclose(f);
    తిరిగి flags;
}
#అయితే_ముగింపు

పూర్ణాంకం ff_get_cpu_flags_mips(శూన్య)
{
#ఒకవేళ defined __linux__ || defined __ANDROID__
    ఒకవేళ (cpucfg_అందుబాటు())
        తిరిగి cpu_flags_cpucfg();
    లేకపోతే
        తిరిగి cpu_flags_cpuinfo();
#లేకపోతే
    /* Assume no SIMD ASE supported */
    తిరిగి 0;
#అయితే_ముగింపు
}

size_t ff_get_cpu_max_align_mips(శూన్య)
{
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & AV_CPU_FLAG_MSA)
        తిరిగి 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ఒకవేళ (flags & AV_CPU_FLAG_MMI)
        తిరిగి 16;

    తిరిగి 8;
}
