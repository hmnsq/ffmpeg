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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ "cpu.h"
#અન્તર્ભાવ <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
સ્થિર પૂર્ણાંક cpu_flags_getauxval(શૂન્ય)
{
    પૂર્ણાંક flags = 0;
    પૂર્ણાંક flag  = (પૂર્ણાંક)ff_getauxval(AT_HWCAP);

    જો (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    જો (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    પાછા flags;
}

પૂર્ણાંક ff_get_cpu_flags_loongarch(શૂન્ય)
{
#જો defined __linux__
    પાછા cpu_flags_getauxval();
#નહીંતર
    /* Assume no SIMD ASE supported */
    પાછા 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(શૂન્ય)
{
    પૂર્ણાંક flags = av_get_cpu_flags();

    જો (flags & AV_CPU_FLAG_LASX)
        પાછા 32;
    જો (flags & AV_CPU_FLAG_LSX)
        પાછા 16;

    પાછા 8;
}
