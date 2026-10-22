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
static 整数 cpu_flags_getauxval(void)
{
    整数 flags = 0;
    整数 flag  = (整数)ff_getauxval(AT_HWCAP);

    如果 (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    如果 (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    返回 flags;
}

整数 ff_get_cpu_flags_loongarch(void)
{
#如果 defined __linux__
    返回 cpu_flags_getauxval();
#否则
    /* Assume no SIMD ASE supported */
    返回 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(void)
{
    整数 flags = av_get_cpu_flags();

    如果 (flags & AV_CPU_FLAG_LASX)
        返回 32;
    如果 (flags & AV_CPU_FLAG_LSX)
        返回 16;

    返回 8;
}
