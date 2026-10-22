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
#ಆದರೆ defined __linux__ || defined __ANDROID__
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ಅನ್ತರ್ಭಾವ "asmdefs.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avstring.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined __linux__ || defined __ANDROID__

#ವ್ಯಾಖ್ಯಾನಿಸು HWCAP_LOONGSON_CPUCFG (1 << 14)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cpucfg_ಲಭ್ಯ(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        ಹಿಂತಿರುಗಿ __res;
}

#ವ್ಯಾಖ್ಯಾನಿಸು LOONGSON_CFG1 0x1

#ವ್ಯಾಖ್ಯಾನಿಸು LOONGSON_CFG1_MMI    (1 << 4)
#ವ್ಯಾಖ್ಯಾನಿಸು LOONGSON_CFG1_MSA1   (1 << 5)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cpu_flags_cpucfg(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ಆದರೆ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ಆದರೆ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ಹಿಂತಿರುಗಿ flags;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cpu_flags_cpuinfo(ಶೂನ್ಯ)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ಅಕ್ಷರ buf[200];
    ಪೂರ್ಣಾಂಕ flags = 0;

    ಆದರೆ (!f)
        ಹಿಂತಿರುಗಿ -1;

    ಆಗ (fgets(buf, ಗಾತ್ರ(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ಆದರೆ (av_strstart(buf, "cpu model", ಖಾಲಿ)) {
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ಆದರೆ (av_strstart(buf, "ASEs implemented", ಖಾಲಿ)) {
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಹುಡುಕು(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            ನಿಲ್ಲಿಸು;
        }
    }
    fclose(f);
    ಹಿಂತಿರುಗಿ flags;
}
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_mips(ಶೂನ್ಯ)
{
#ಆದರೆ defined __linux__ || defined __ANDROID__
    ಆದರೆ (cpucfg_ಲಭ್ಯ())
        ಹಿಂತಿರುಗಿ cpu_flags_cpucfg();
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ cpu_flags_cpuinfo();
#ಇಲ್ಲದಿದ್ದರೆ
    /* Assume no SIMD ASE supported */
    ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
}

size_t ff_get_cpu_max_align_mips(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & AV_CPU_FLAG_MSA)
        ಹಿಂತಿರುಗಿ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ಆದರೆ (flags & AV_CPU_FLAG_MMI)
        ಹಿಂತಿರುಗಿ 16;

    ಹಿಂತಿರುಗಿ 8;
}
