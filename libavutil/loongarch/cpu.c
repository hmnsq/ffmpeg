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
static puur_naa_nka cpu_flags_getauxval(void)
{
    puur_naa_nka flags = 0;
    puur_naa_nka flag  = (puur_naa_nka)ff_getauxval(AT_HWCAP);

    ပေႃး (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ပေႃး (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ပွၵ်ႈ flags;
}

puur_naa_nka ff_get_cpu_flags_loongarch(void)
{
#ပေႃး defined __linux__
    ပွၵ်ႈ cpu_flags_getauxval();
#ပေႃးဢမ်ႇ
    /* Assume no SIMD ASE supported */
    ပွၵ်ႈ 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(void)
{
    puur_naa_nka flags = av_get_cpu_flags();

    ပေႃး (flags & AV_CPU_FLAG_LASX)
        ပွၵ်ႈ 32;
    ပေႃး (flags & AV_CPU_FLAG_LSX)
        ပွၵ်ႈ 16;

    ပွၵ်ႈ 8;
}
