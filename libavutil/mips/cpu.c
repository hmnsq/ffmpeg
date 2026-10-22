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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਜੇ defined __linux__ || defined __ANDROID__
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "asmdefs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avstring.h"
#ਜੇ_ਅੰਤ

#ਜੇ defined __linux__ || defined __ANDROID__

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HWCAP_LOONGSON_CPUCFG (1 << 14)

ਸਥਿਰ ਪੂਰਨ cpucfg_ਉਪਲਬਧ(ਖਾਲੀ)
{
    ਵਾਪਸ ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
ਸਥਿਰ uint32_t read_cpucfg(uint32_t reg)
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
        ਵਾਪਸ __res;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOONGSON_CFG1 0x1

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOONGSON_CFG1_MMI    (1 << 4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOONGSON_CFG1_MSA1   (1 << 5)

ਸਥਿਰ ਪੂਰਨ cpu_flags_cpucfg(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    ਜੇ (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    ਜੇ (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    ਵਾਪਸ flags;
}

ਸਥਿਰ ਪੂਰਨ cpu_flags_cpuinfo(ਖਾਲੀ)
{
    FILE *f = fopen("/proc/cpuinfo", "r");
    ਅੱਖਰ buf[200];
    ਪੂਰਨ flags = 0;

    ਜੇ (!f)
        ਵਾਪਸ -1;

    ਜਦੋਂ (fgets(buf, ਆਕਾਰ(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        ਜੇ (av_strstart(buf, "cpu model", ਨਿਰਾ)) {
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        ਜੇ (av_strstart(buf, "ASEs implemented", ਨਿਰਾ)) {
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            ਜੇ (ਲੜੀ_ਖੋਜ(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            ਰੋਕੋ;
        }
    }
    fclose(f);
    ਵਾਪਸ flags;
}
#ਜੇ_ਅੰਤ

ਪੂਰਨ ff_get_cpu_flags_mips(ਖਾਲੀ)
{
#ਜੇ defined __linux__ || defined __ANDROID__
    ਜੇ (cpucfg_ਉਪਲਬਧ())
        ਵਾਪਸ cpu_flags_cpucfg();
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ cpu_flags_cpuinfo();
#ਨਹੀਂਤਾਂ
    /* Assume no SIMD ASE supported */
    ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
}

size_t ff_get_cpu_max_align_mips(ਖਾਲੀ)
{
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ (flags & AV_CPU_FLAG_MSA)
        ਵਾਪਸ 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    ਜੇ (flags & AV_CPU_FLAG_MMI)
        ਵਾਪਸ 16;

    ਵਾਪਸ 8;
}
