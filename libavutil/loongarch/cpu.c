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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ "cpu.h"
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags_getauxval(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flag  = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)ff_getauxval(AT_HWCAP);

    ଯଦି (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ଯଦି (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ଫେରନ୍ତୁ flags;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_loongarch(ଶୂନ୍ୟ)
{
#ଯଦି defined __linux__
    ଫେରନ୍ତୁ cpu_flags_getauxval();
#ଅନ୍ୟଥା
    /* Assume no SIMD ASE supported */
    ଫେରନ୍ତୁ 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & AV_CPU_FLAG_LASX)
        ଫେରନ୍ତୁ 32;
    ଯଦି (flags & AV_CPU_FLAG_LSX)
        ଫେରନ୍ତୁ 16;

    ଫେରନ୍ତୁ 8;
}
