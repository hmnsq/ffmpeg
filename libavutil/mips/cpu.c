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

#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/cpu_internal.h"
#অন্তর্ভাব "config.h"
#যদি defined __linux__ || defined __ANDROID__
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব <sys/auxv.h>
#অন্তর্ভাব "asmdefs.h"
#অন্তর্ভাব "libavutil/avstring.h"
#endif

#যদি defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

স্থির পূর্ণসংখ্যা cpucfg_available(শূন্য)
{
    ফেরত ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
স্থির uint32_t read_cpucfg(uint32_t reg)
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
        ফেরত __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

স্থির পূর্ণসংখ্যা cpu_flags_cpucfg(শূন্য)
{
    পূর্ণসংখ্যা flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    যদি (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    যদি (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ফেরত flags;
}

স্থির পূর্ণসংখ্যা cpu_flags_cpuinfo(শূন্য)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    অক্ষর buf[200];
    পূর্ণসংখ্যা flags = 0;

    যদি (!f)
        ফেরত -1;

    যখন (fgets(buf, আকার(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        যদি (av_strstart(buf, "cpu model", ফাঁকা)) {
            যদি (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        যদি (av_strstart(buf, "ASEs implemented", ফাঁকা)) {
            যদি (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            যদি (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            বিরতি;
        }
    }
    fclose(f);
    ফেরত flags;
}
#endif

পূর্ণসংখ্যা ff_get_cpu_flags_mips(শূন্য)
{
#যদি defined __linux__ || defined __ANDROID__
    যদি (cpucfg_available())
        ফেরত cpu_flags_cpucfg();
    অন্যথা
        ফেরত cpu_flags_cpuinfo();
#অন্যথা
    /* Assume no SIMD ASE supported */
    ফেরত 0;
#endif
}

size_t ff_get_cpu_max_align_mips(শূন্য)
{
    পূর্ণসংখ্যা flags = av_get_cpu_flags();

    যদি (flags & AV_CPU_FLAG_MSA)
        ফেরত 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    যদি (flags & AV_CPU_FLAG_MMI)
        ফেরত 16;

    ফেরত 8;
}
