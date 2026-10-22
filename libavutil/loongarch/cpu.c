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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "cpu.h"
#అన్తర్భావ <sys/auxv.h>

#నిర్వచించు LA_HWCAP_LSX    (1<<4)
#నిర్వచించు LA_HWCAP_LASX   (1<<5)
స్థిర పూర్ణాంకం cpu_flags_getauxval(శూన్య)
{
    పూర్ణాంకం flags = 0;
    పూర్ణాంకం flag  = (పూర్ణాంకం)ff_getauxval(AT_HWCAP);

    ఒకవేళ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ఒకవేళ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    తిరిగి flags;
}

పూర్ణాంకం ff_get_cpu_flags_loongarch(శూన్య)
{
#ఒకవేళ defined __linux__
    తిరిగి cpu_flags_getauxval();
#లేకపోతే
    /* Assume no SIMD ASE supported */
    తిరిగి 0;
#అయితే_ముగింపు
}

size_t ff_get_cpu_max_align_loongarch(శూన్య)
{
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & AV_CPU_FLAG_LASX)
        తిరిగి 32;
    ఒకవేళ (flags & AV_CPU_FLAG_LSX)
        తిరిగి 16;

    తిరిగి 8;
}
