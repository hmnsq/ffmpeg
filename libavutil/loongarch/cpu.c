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
static ကိန်းပြည့် cpu_flags_getauxval(void)
{
    ကိန်းပြည့် flags = 0;
    ကိန်းပြည့် flag  = (ကိန်းပြည့်)ff_getauxval(AT_HWCAP);

    အကယ်၍ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    အကယ်၍ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ပြန်ပေး flags;
}

ကိန်းပြည့် ff_get_cpu_flags_loongarch(void)
{
#အကယ်၍ defined __linux__
    ပြန်ပေး cpu_flags_getauxval();
#မဟုတ်ပါက
    /* Assume no SIMD ASE supported */
    ပြန်ပေး 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(void)
{
    ကိန်းပြည့် flags = av_get_cpu_flags();

    အကယ်၍ (flags & AV_CPU_FLAG_LASX)
        ပြန်ပေး 32;
    အကယ်၍ (flags & AV_CPU_FLAG_LSX)
        ပြန်ပေး 16;

    ပြန်ပေး 8;
}
