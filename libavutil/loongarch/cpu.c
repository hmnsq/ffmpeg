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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "cpu.h"
#अन्तर्भाव <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
स्थिर पूर्णांक cpu_flags_getauxval(शून्य)
{
    पूर्णांक flags = 0;
    पूर्णांक flag  = (पूर्णांक)ff_getauxval(AT_HWCAP);

    जर (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    जर (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    परत flags;
}

पूर्णांक ff_get_cpu_flags_loongarch(शून्य)
{
#जर defined __linux__
    परत cpu_flags_getauxval();
#अन्यथा
    /* Assume no SIMD ASE supported */
    परत 0;
#endif
}

माप_प्रकार ff_get_cpu_max_align_loongarch(शून्य)
{
    पूर्णांक flags = av_get_cpu_flags();

    जर (flags & AV_CPU_FLAG_LASX)
        परत 32;
    जर (flags & AV_CPU_FLAG_LSX)
        परत 16;

    परत 8;
}
