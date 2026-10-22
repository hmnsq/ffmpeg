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

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu_internal.h"
#ಅನ್ತರ್ಭಾವ "config.h"
#ಯದಿ defined __linux__ || defined __ANDROID__
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ಅನ್ತರ್ಭಾವ "asmdefs.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avstring.h"
#endif

#ಯದಿ defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cpucfg_available(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ಸ್ಥಿರ uint32_t read_cpucfg(uint32_t reg)
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
        ಪ್ರತ್ಯಾಗಮ __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cpu_flags_cpucfg(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ಯದಿ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ಯದಿ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ಪ್ರತ್ಯಾಗಮ flags;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cpu_flags_cpuinfo(ಶೂನ್ಯ)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ವರ್ಣ buf[200];
    ಪೂರ್ಣಾಙ್ಕ flags = 0;

    ಯದಿ (!f)
        ಪ್ರತ್ಯಾಗಮ -1;

    ಯಾವತ್ (fgets(buf, ಪರಿಮಾಣ(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ಯದಿ (av_strstart(buf, "cpu model", ರಿಕ್ತ)) {
            ಯದಿ (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ಯದಿ (av_strstart(buf, "ASEs implemented", ರಿಕ್ತ)) {
            ಯದಿ (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ಯದಿ (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            ಭಙ್ಗ;
        }
    }
    fclose(f);
    ಪ್ರತ್ಯಾಗಮ flags;
}
#endif

ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_mips(ಶೂನ್ಯ)
{
#ಯದಿ defined __linux__ || defined __ANDROID__
    ಯದಿ (cpucfg_available())
        ಪ್ರತ್ಯಾಗಮ cpu_flags_cpucfg();
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ cpu_flags_cpuinfo();
#ಅನ್ಯಥಾ
    /* Assume no SIMD ASE supported */
    ಪ್ರತ್ಯಾಗಮ 0;
#endif
}

size_t ff_get_cpu_max_align_mips(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = av_get_cpu_flags();

    ಯದಿ (flags & AV_CPU_FLAG_MSA)
        ಪ್ರತ್ಯಾಗಮ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ಯದಿ (flags & AV_CPU_FLAG_MMI)
        ಪ್ರತ್ಯಾಗಮ 16;

    ಪ್ರತ್ಯಾಗಮ 8;
}
