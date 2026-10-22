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

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/cpu_internal.h"
#समावेश "config.h"
#अगर defined __linux__ || defined __ANDROID__
#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश <sys/auxv.h>
#समावेश "asmdefs.h"
#समावेश "libavutil/avstring.h"
#पूर्ण_अगर

#अगर defined __linux__ || defined __ANDROID__

#घोषणा HWCAP_LOONGSON_CPUCFG (1 << 14)

अटल पूर्णांक cpucfg_available(व्योम)
{
    वापस ff_getauxval(AT_HWCAP) & HWCAP_LOONGSON_CPUCFG;
}

/* Most toolchains have no CPUCFG support yet */
अटल uint32_t read_cpucfg(uint32_t reg)
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
        वापस __res;
}

#घोषणा LOONGSON_CFG1 0x1

#घोषणा LOONGSON_CFG1_MMI    (1 << 4)
#घोषणा LOONGSON_CFG1_MSA1   (1 << 5)

अटल पूर्णांक cpu_flags_cpucfg(व्योम)
{
    पूर्णांक flags = 0;
    uint32_t cfg1 = read_cpucfg(LOONGSON_CFG1);

    अगर (cfg1 & LOONGSON_CFG1_MMI)
        flags |= AV_CPU_FLAG_MMI;

    अगर (cfg1 & LOONGSON_CFG1_MSA1)
        flags |= AV_CPU_FLAG_MSA;

    वापस flags;
}

अटल पूर्णांक cpu_flags_cpuinfo(व्योम)
{
    खाता *f = ख_खोलो("/proc/cpuinfo", "r");
    अक्षर buf[200];
    पूर्णांक flags = 0;

    अगर (!f)
        वापस -1;

    जबतक (ख_माला_लो(buf, माप(buf), f)) {
        /* Legacy kernel may not export MMI in ASEs implemented */
        अगर (av_strstart(buf, "cpu model", शून्य)) {
            अगर (म_माला(buf, "Loongson-3 "))
                flags |= AV_CPU_FLAG_MMI;
        }

        अगर (av_strstart(buf, "ASEs implemented", शून्य)) {
            अगर (म_माला(buf, " loongson-mmi"))
                flags |= AV_CPU_FLAG_MMI;
            अगर (म_माला(buf, " msa"))
                flags |= AV_CPU_FLAG_MSA;

            अवरोध;
        }
    }
    ख_बंद(f);
    वापस flags;
}
#पूर्ण_अगर

पूर्णांक ff_get_cpu_flags_mips(व्योम)
{
#अगर defined __linux__ || defined __ANDROID__
    अगर (cpucfg_available())
        वापस cpu_flags_cpucfg();
    अन्यथा
        वापस cpu_flags_cpuinfo();
#अन्यथा
    /* Assume no SIMD ASE supported */
    वापस 0;
#पूर्ण_अगर
}

माप_प्रकार ff_get_cpu_max_align_mips(व्योम)
{
    पूर्णांक flags = av_get_cpu_flags();

    अगर (flags & AV_CPU_FLAG_MSA)
        वापस 16;

    /*
     * MMI itself is 64-bit but quad word load & store
     * needs 128-bit align.
     */
    अगर (flags & AV_CPU_FLAG_MMI)
        वापस 16;

    वापस 8;
}
