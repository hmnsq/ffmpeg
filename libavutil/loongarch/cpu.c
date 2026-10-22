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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "cpu.h"
#অন্তর্ভাব <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
স্থির পূর্ণসংখ্যা cpu_flags_getauxval(শূন্য)
{
    পূর্ণসংখ্যা flags = 0;
    পূর্ণসংখ্যা flag  = (পূর্ণসংখ্যা)ff_getauxval(AT_HWCAP);

    যদি (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    যদি (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ফেরত flags;
}

পূর্ণসংখ্যা ff_get_cpu_flags_loongarch(শূন্য)
{
#যদি defined __linux__
    ফেরত cpu_flags_getauxval();
#অন্যথা
    /* Assume no SIMD ASE supported */
    ফেরত 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(শূন্য)
{
    পূর্ণসংখ্যা flags = av_get_cpu_flags();

    যদি (flags & AV_CPU_FLAG_LASX)
        ফেরত 32;
    যদি (flags & AV_CPU_FLAG_LSX)
        ফেরত 16;

    ফেরত 8;
}
