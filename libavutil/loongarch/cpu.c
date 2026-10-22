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

#شامل <stdint.h>
#شامل "cpu.h"
#شامل <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
ایستا صحیح cpu_flags_getauxval(تهی)
{
    صحیح flags = 0;
    صحیح flag  = (صحیح)ff_getauxval(AT_HWCAP);

    اگر (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    اگر (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    بازگشت flags;
}

صحیح ff_get_cpu_flags_loongarch(تهی)
{
#اگر defined __linux__
    بازگشت cpu_flags_getauxval();
#وگرنه
    /* Assume no SIMD ASE supported */
    بازگشت 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(تهی)
{
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_LASX)
        بازگشت 32;
    اگر (flags & AV_CPU_FLAG_LSX)
        بازگشت 16;

    بازگشت 8;
}
