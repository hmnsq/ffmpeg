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

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/cpu_internal.h"
#ضمن "config.h"
#إذا defined __linux__ || defined __ANDROID__
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن <sys/auxv.h>
#ضمن "asmdefs.h"
#ضمن "libavutil/avstring.h"
#endif

#إذا defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

ساكن صحيح cpucfg_available(فراغ)
{
    إرجاع ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ساكن uint32_t read_cpucfg(uint32_t reg)
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
        إرجاع __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

ساكن صحيح cpu_flags_cpucfg(فراغ)
{
    صحيح flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    إذا (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    إذا (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    إرجاع flags;
}

ساكن صحيح cpu_flags_cpuinfo(فراغ)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    حرف buf[200];
    صحيح flags = 0;

    إذا (!f)
        إرجاع -1;

    بينما (fgets(buf, حجم(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        إذا (av_strstart(buf, "cpu model", عدم)) {
            إذا (strstr(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        إذا (av_strstart(buf, "ASEs implemented", عدم)) {
            إذا (strstr(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            إذا (strstr(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            اكسر;
        }
    }
    fclose(f);
    إرجاع flags;
}
#endif

صحيح ff_get_cpu_flags_mips(فراغ)
{
#إذا defined __linux__ || defined __ANDROID__
    إذا (cpucfg_available())
        إرجاع cpu_flags_cpucfg();
    وإلا
        إرجاع cpu_flags_cpuinfo();
#وإلا
    /* Assume no SIMD ASE supported */
    إرجاع 0;
#endif
}

size_t ff_get_cpu_max_align_mips(فراغ)
{
    صحيح flags = av_get_cpu_flags();

    إذا (flags & AV_CPU_FLAG_MSA)
        إرجاع 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    إذا (flags & AV_CPU_FLAG_MMI)
        إرجاع 16;

    إرجاع 8;
}
