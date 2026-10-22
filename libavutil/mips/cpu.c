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

#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/cpu_internal.h"
#അന്തര്ഭാവ "config.h"
#എങ്കിൽ defined __linux__ || defined __ANDROID__
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/auxv.h>
#അന്തര്ഭാവ "asmdefs.h"
#അന്തര്ഭാവ "libavutil/avstring.h"
#endif

#എങ്കിൽ defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

സ്ഥിതം പൂർണ്ണസംഖ്യ cpucfg_available(ശൂന്യം)
{
    തിരികെ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
സ്ഥിതം uint32_t read_cpucfg(uint32_t reg)
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
        തിരികെ __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

സ്ഥിതം പൂർണ്ണസംഖ്യ cpu_flags_cpucfg(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    എങ്കിൽ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    എങ്കിൽ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    തിരികെ flags;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ cpu_flags_cpuinfo(ശൂന്യം)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    അക്ഷരം buf[200];
    പൂർണ്ണസംഖ്യ flags = 0;

    എങ്കിൽ (!f)
        തിരികെ -1;

    ആകുമ്പോൾ (fgets(buf, വലുപ്പം(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        എങ്കിൽ (av_strstart(buf, "cpu model", ശൂന്യ)) {
            എങ്കിൽ (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        എങ്കിൽ (av_strstart(buf, "ASEs implemented", ശൂന്യ)) {
            എങ്കിൽ (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            എങ്കിൽ (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            നിർത്തുക;
        }
    }
    fclose(f);
    തിരികെ flags;
}
#endif

പൂർണ്ണസംഖ്യ ff_get_cpu_flags_mips(ശൂന്യം)
{
#എങ്കിൽ defined __linux__ || defined __ANDROID__
    എങ്കിൽ (cpucfg_available())
        തിരികെ cpu_flags_cpucfg();
    അല്ലെങ്കിൽ
        തിരികെ cpu_flags_cpuinfo();
#അല്ലെങ്കിൽ
    /* Assume no SIMD ASE supported */
    തിരികെ 0;
#endif
}

size_t ff_get_cpu_max_align_mips(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ flags = av_get_cpu_flags();

    എങ്കിൽ (flags & AV_CPU_FLAG_MSA)
        തിരികെ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    എങ്കിൽ (flags & AV_CPU_FLAG_MMI)
        തിരികെ 16;

    തിരികെ 8;
}
