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
स्थिर पूर्णाङ्क cpu_flags_getauxval(शून्य)
{
    पूर्णाङ्क flags = 0;
    पूर्णाङ्क flag  = (पूर्णाङ्क)ff_getauxval(AT_HWCAP);

    जइ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    जइ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    प्रत्यागम flags;
}

पूर्णाङ्क ff_get_cpu_flags_loongarch(शून्य)
{
#जइ defined __linux__
    प्रत्यागम cpu_flags_getauxval();
#अण्णहा
    /* Assume no SIMD ASE supported */
    प्रत्यागम 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(शून्य)
{
    पूर्णाङ्क flags = av_get_cpu_flags();

    जइ (flags & AV_CPU_FLAG_LASX)
        प्रत्यागम 32;
    जइ (flags & AV_CPU_FLAG_LSX)
        प्रत्यागम 16;

    प्रत्यागम 8;
}
