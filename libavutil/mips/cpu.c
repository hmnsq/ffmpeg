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

#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/cpu_internal.h"
#અન્તર્ભાવ "config.h"
#જો defined __linux__ || defined __ANDROID__
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <sys/auxv.h>
#અન્તર્ભાવ "asmdefs.h"
#અન્તર્ભાવ "libavutil/avstring.h"
#endif

#જો defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

સ્થિર પૂર્ણાંક cpucfg_available(શૂન્ય)
{
    પાછા ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
સ્થિર uint32_t read_cpucfg(uint32_t reg)
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
        પાછા __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

સ્થિર પૂર્ણાંક cpu_flags_cpucfg(શૂન્ય)
{
    પૂર્ણાંક flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    જો (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    જો (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    પાછા flags;
}

સ્થિર પૂર્ણાંક cpu_flags_cpuinfo(શૂન્ય)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    અક્ષર buf[200];
    પૂર્ણાંક flags = 0;

    જો (!f)
        પાછા -1;

    જ્યારે (fgets(buf, કદ(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        જો (av_strstart(buf, "cpu model", ખાલી)) {
            જો (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        જો (av_strstart(buf, "ASEs implemented", ખાલી)) {
            જો (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            જો (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            તોડો;
        }
    }
    fclose(f);
    પાછા flags;
}
#endif

પૂર્ણાંક ff_get_cpu_flags_mips(શૂન્ય)
{
#જો defined __linux__ || defined __ANDROID__
    જો (cpucfg_available())
        પાછા cpu_flags_cpucfg();
    નહીંતર
        પાછા cpu_flags_cpuinfo();
#નહીંતર
    /* Assume no SIMD ASE supported */
    પાછા 0;
#endif
}

size_t ff_get_cpu_max_align_mips(શૂન્ય)
{
    પૂર્ણાંક flags = av_get_cpu_flags();

    જો (flags & AV_CPU_FLAG_MSA)
        પાછા 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    જો (flags & AV_CPU_FLAG_MMI)
        પાછા 16;

    પાછા 8;
}
