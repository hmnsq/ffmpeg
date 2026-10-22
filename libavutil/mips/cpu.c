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
#जइ defined __linux__ || defined __ANDROID__
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/auxv.h>
#अन्तर्भाव "asmdefs.h"
#अन्तर्भाव "libavutil/avstring.h"
#endif

#जइ defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

स्थिर पूर्णाङ्क cpucfg_available(शून्य)
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

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

स्थिर पूर्णाङ्क cpu_flags_cpucfg(शून्य)
{
    पूर्णाङ्क flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    जइ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    जइ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    प्रत्यागम flags;
}

स्थिर पूर्णाङ्क cpu_flags_cpuinfo(शून्य)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    वर्ण buf[200];
    पूर्णाङ्क flags = 0;

    जइ (!f)
        प्रत्यागम -1;

    जाव (fgets(buf, परिमाण(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        जइ (av_strstart(buf, "cpu model", रिक्त)) {
            जइ (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        जइ (av_strstart(buf, "ASEs implemented", रिक्त)) {
            जइ (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            जइ (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            भङ्ग;
        }
    }
    fclose(f);
    प्रत्यागम flags;
}
#endif

पूर्णाङ्क ff_get_cpu_flags_mips(शून्य)
{
#जइ defined __linux__ || defined __ANDROID__
    जइ (cpucfg_available())
        प्रत्यागम cpu_flags_cpucfg();
    अण्णहा
        प्रत्यागम cpu_flags_cpuinfo();
#अण्णहा
    /* Assume no SIMD ASE supported */
    प्रत्यागम 0;
#endif
}

size_t ff_get_cpu_max_align_mips(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    जइ (flags & AV_CPU_FLAG_MSA)
        प्रत्यागम 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    जइ (flags & AV_CPU_FLAG_MMI)
        प्रत्यागम 16;

    प्रत्यागम 8;
}
