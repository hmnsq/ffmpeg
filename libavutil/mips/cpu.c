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

#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/cpu_internal.h"
#अन्तर्भाव "config.h"
#यदि defined __linux__ || defined __ANDROID__
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/auxv.h>
#अन्तर्भाव "asmdefs.h"
#अन्तर्भाव "libavutil/avstring.h"
#यदि_अन्तः

#यदि defined __linux__ || defined __ANDROID__

#परिभाषय HWCAP_LOONGSON_CPUCFG (1 << 14)

स्थिर पूर्णाङ्क cpucfg_उपलब्धम्(शून्य)
{
    प्रत्यागम ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
स्थिर uint32_t read_cpucfg(uint32_t reg)
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
        प्रत्यागम __res;
}

#परिभाषय LOONGSON_CFG1 0x1

#परिभाषय LOONGSON_CFG1_MMI    (1 << 4)
#परिभाषय LOONGSON_CFG1_MSA1   (1 << 5)

स्थिर पूर्णाङ्क cpu_flags_cpucfg(शून्य)
{
    पूर्णाङ्क flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    यदि (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    यदि (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    प्रत्यागम flags;
}

स्थिर पूर्णाङ्क cpu_flags_cpuinfo(शून्य)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    वर्ण buf[200];
    पूर्णाङ्क flags = 0;

    यदि (!f)
        प्रत्यागम -1;

    यावत् (fgets(buf, परिमाण(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        यदि (av_strstart(buf, "cpu model", रिक्त)) {
            यदि (वाक्ये_अन्विष(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        यदि (av_strstart(buf, "ASEs implemented", रिक्त)) {
            यदि (वाक्ये_अन्विष(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            यदि (वाक्ये_अन्विष(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            भङ्ग;
        }
    }
    fclose(f);
    प्रत्यागम flags;
}
#यदि_अन्तः

पूर्णाङ्क ff_get_cpu_flags_mips(शून्य)
{
#यदि defined __linux__ || defined __ANDROID__
    यदि (cpucfg_उपलब्धम्())
        प्रत्यागम cpu_flags_cpucfg();
    अन्यथा
        प्रत्यागम cpu_flags_cpuinfo();
#अन्यथा
    /* Assume no SIMD ASE supported */
    प्रत्यागम 0;
#यदि_अन्तः
}

size_t ff_get_cpu_max_align_mips(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि (flags & AV_CPU_FLAG_MSA)
        प्रत्यागम 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    यदि (flags & AV_CPU_FLAG_MMI)
        प्रत्यागम 16;

    प्रत्यागम 8;
}
