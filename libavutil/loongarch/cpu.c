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

#ضمن <stdint.h>
#ضمن "cpu.h"
#ضمن <sys/auxv.h>

#تعریف_کن LA_HWCAP_LSX    (1<<4)
#تعریف_کن LA_HWCAP_LASX   (1<<5)
ساكن صحيح cpu_flags_getauxval(فراغ)
{
    صحيح flags = 0;
    صحيح flag  = (صحيح)ff_getauxval(AT_HWCAP);

    إذا (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    إذا (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    أرجع flags;
}

صحيح ff_get_cpu_flags_loongarch(فراغ)
{
#إذا defined __linux__
    أرجع cpu_flags_getauxval();
#وإلا
    /* Assume no SIMD ASE supported */
    أرجع 0;
#پایان_اگر
}

size_t ff_get_cpu_max_align_loongarch(فراغ)
{
    صحيح flags = av_get_cpu_flags();

    إذا (flags & AV_CPU_FLAG_LASX)
        أرجع 32;
    إذا (flags & AV_CPU_FLAG_LSX)
        أرجع 16;

    أرجع 8;
}
