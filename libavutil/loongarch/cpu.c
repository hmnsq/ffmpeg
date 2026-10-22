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

#include <stdint.h>
#include "cpu.h"
#include <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
static ціле cpu_flags_getauxval(void)
{
    ціле flags = 0;
    ціле flag  = (ціле)ff_getauxval(AT_HWCAP);

    якщо (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    якщо (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    повернути flags;
}

ціле ff_get_cpu_flags_loongarch(void)
{
#якщо defined __linux__
    повернути cpu_flags_getauxval();
#інакше
    /* Assume no SIMD ASE supported */
    повернути 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(void)
{
    ціле flags = av_get_cpu_flags();

    якщо (flags & AV_CPU_FLAG_LASX)
        повернути 32;
    якщо (flags & AV_CPU_FLAG_LSX)
        повернути 16;

    повернути 8;
}
