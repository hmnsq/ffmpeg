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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
நிலையான முழு cpu_flags_getauxval(வெறுமை)
{
    முழு flags = 0;
    முழு flag  = (முழு)ff_getauxval(AT_HWCAP);

    எனில் (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    எனில் (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    திரும்பு flags;
}

முழு ff_get_cpu_flags_loongarch(வெறுமை)
{
#எனில் defined __linux__
    திரும்பு cpu_flags_getauxval();
#இல்லையெனில்
    /* Assume no SIMD ASE supported */
    திரும்பு 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(வெறுமை)
{
    முழு flags = av_get_cpu_flags();

    எனில் (flags & AV_CPU_FLAG_LASX)
        திரும்பு 32;
    எனில் (flags & AV_CPU_FLAG_LSX)
        திரும்பு 16;

    திரும்பு 8;
}
