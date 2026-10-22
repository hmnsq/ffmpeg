/*
 * Copyright (c) 2020 Loongson Technology Corporation Limited
 * Contributed by Shiyou Yin <yinshiyou-hf@loongson.cn>
 *
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

#समावेश <stdint.h>
#समावेश "cpu.h"
#समावेश <sys/auxv.h>

#घोषणा LA_HWCAP_LSX    (1<<4)
#घोषणा LA_HWCAP_LASX   (1<<5)
अटल पूर्णांक cpu_flags_getauxval(व्योम)
{
    पूर्णांक flags = 0;
    पूर्णांक flag  = (पूर्णांक)ff_getauxval(AT_HWCAP);

    अगर (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    अगर (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    वापस flags;
}

पूर्णांक ff_get_cpu_flags_loongarch(व्योम)
{
#अगर defined __linux__
    वापस cpu_flags_getauxval();
#अन्यथा
    /* Assume no SIMD ASE supported */
    वापस 0;
#पूर्ण_अगर
}

माप_प्रकार ff_get_cpu_max_align_loongarch(व्योम)
{
    पूर्णांक flags = av_get_cpu_flags();

    अगर (flags & AV_CPU_FLAG_LASX)
        वापस 32;
    अगर (flags & AV_CPU_FLAG_LSX)
        वापस 16;

    वापस 8;
}
