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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LA_HWCAP_LSX    (1<<4)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LA_HWCAP_LASX   (1<<5)
ਸਥਿਰ ਪੂਰਨ cpu_flags_getauxval(ਖਾਲੀ)
{
    ਪੂਰਨ flags = 0;
    ਪੂਰਨ flag  = (ਪੂਰਨ)ff_getauxval(AT_HWCAP);

    ਜੇ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ਜੇ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ਵਾਪਸ flags;
}

ਪੂਰਨ ff_get_cpu_flags_loongarch(ਖਾਲੀ)
{
#ਜੇ defined __linux__
    ਵਾਪਸ cpu_flags_getauxval();
#ਨਹੀਂਤਾਂ
    /* Assume no SIMD ASE supported */
    ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
}

size_t ff_get_cpu_max_align_loongarch(ਖਾਲੀ)
{
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ (flags & AV_CPU_FLAG_LASX)
        ਵਾਪਸ 32;
    ਜੇ (flags & AV_CPU_FLAG_LSX)
        ਵਾਪਸ 16;

    ਵਾਪਸ 8;
}
