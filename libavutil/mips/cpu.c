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
#जर defined __linux__ || defined __ANDROID__
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/auxv.h>
#अन्तर्भाव "asmdefs.h"
#अन्तर्भाव "libavutil/avstring.h"
#endif

#जर defined __linux__ || defined __ANDROID__

#define HWCAP_LOONGSON_CPUCFG (1 << 14)

स्थिर पूर्णांक cpucfg_available(शून्य)
{
    परत ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
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
        परत __res;
}

#define LOONGSON_CFG1 0x1

#define LOONGSON_CFG1_MMI    (1 << 4)
#define LOONGSON_CFG1_MSA1   (1 << 5)

स्थिर पूर्णांक cpu_flags_cpucfg(शून्य)
{
    पूर्णांक flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    जर (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    जर (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    परत flags;
}

स्थिर पूर्णांक cpu_flags_cpuinfo(शून्य)
{
    खाता *f = ख_खोलो("/proc/cpuinfo", "r");
    अक्षर buf[200];
    पूर्णांक flags = 0;

    जर (!f)
        परत -1;

    पर्यंत (ख_माला_लो(buf, आकार(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        जर (av_strstart(buf, "cpu model", रिक्त)) {
            जर (म_माला(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        जर (av_strstart(buf, "ASEs implemented", रिक्त)) {
            जर (म_माला(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            जर (म_माला(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            थांबा;
        }
    }
    ख_बंद(f);
    परत flags;
}
#endif

पूर्णांक ff_get_cpu_flags_mips(शून्य)
{
#जर defined __linux__ || defined __ANDROID__
    जर (cpucfg_available())
        परत cpu_flags_cpucfg();
    अन्यथा
        परत cpu_flags_cpuinfo();
#अन्यथा
    /* Assume no SIMD ASE supported */
    परत 0;
#endif
}

माप_प्रकार ff_get_cpu_max_align_mips(शून्य)
{
    पूर्णांक flags = av_get_cpu_flags();

    जर (flags & AV_CPU_FLAG_MSA)
        परत 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    जर (flags & AV_CPU_FLAG_MMI)
        परत 16;

    परत 8;
}
