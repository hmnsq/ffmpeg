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
static ចំនួនគត់ cpu_flags_getauxval(void)
{
    ចំនួនគត់ flags = 0;
    ចំនួនគត់ flag  = (ចំនួនគត់)ff_getauxval(AT_HWCAP);

    ប្រសិនបើ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ប្រសិនបើ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ត្រឡប់ flags;
}

ចំនួនគត់ ff_get_cpu_flags_loongarch(void)
{
#ប្រសិនបើ defined __linux__
    ត្រឡប់ cpu_flags_getauxval();
#បើមិនដូច្នេះ
    /* Assume no SIMD ASE supported */
    ត្រឡប់ 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(void)
{
    ចំនួនគត់ flags = av_get_cpu_flags();

    ប្រសិនបើ (flags & AV_CPU_FLAG_LASX)
        ត្រឡប់ 32;
    ប្រសិនបើ (flags & AV_CPU_FLAG_LSX)
        ត្រឡប់ 16;

    ត្រឡប់ 8;
}
