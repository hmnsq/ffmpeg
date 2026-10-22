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

#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/cpu_internal.h"
#அந்தர்பாவ "config.h"
#எனில் defined __linux__ || defined __ANDROID__
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <sys/auxv.h>
#அந்தர்பாவ "asmdefs.h"
#அந்தர்பாவ "libavutil/avstring.h"
#endif

#எனில் defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

நிலையான முழு cpucfg_available(வெறுமை)
{
    திரும்பு ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
நிலையான uint32_t read_cpucfg(uint32_t reg)
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
        திரும்பு __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

நிலையான முழு cpu_flags_cpucfg(வெறுமை)
{
    முழு flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    எனில் (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    எனில் (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    திரும்பு flags;
}

நிலையான முழு cpu_flags_cpuinfo(வெறுமை)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    எழுத்து buf[200];
    முழு flags = 0;

    எனில் (!f)
        திரும்பு -1;

    போது (fgets(buf, அளவு(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        எனில் (av_strstart(buf, "cpu model", வெற்று)) {
            எனில் (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        எனில் (av_strstart(buf, "ASEs implemented", வெற்று)) {
            எனில் (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            எனில் (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            நிறுத்து;
        }
    }
    fclose(f);
    திரும்பு flags;
}
#endif

முழு ff_get_cpu_flags_mips(வெறுமை)
{
#எனில் defined __linux__ || defined __ANDROID__
    எனில் (cpucfg_available())
        திரும்பு cpu_flags_cpucfg();
    இல்லையெனில்
        திரும்பு cpu_flags_cpuinfo();
#இல்லையெனில்
    /* Assume no SIMD ASE supported */
    திரும்பு 0;
#endif
}

size_t ff_get_cpu_max_align_mips(வெறுமை)
{
    முழு flags = av_get_cpu_flags();

    எனில் (flags & AV_CPU_FLAG_MSA)
        திரும்பு 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    எனில் (flags & AV_CPU_FLAG_MMI)
        திரும்பு 16;

    திரும்பு 8;
}
