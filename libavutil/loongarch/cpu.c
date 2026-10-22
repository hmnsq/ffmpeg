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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ cpu_flags_getauxval(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = 0;
    ಪೂರ್ಣಾಙ್ಕ flag  = (ಪೂರ್ಣಾಙ್ಕ)ff_getauxval(AT_HWCAP);

    ಯದಿ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ಯದಿ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ಪ್ರತ್ಯಾಗಮ flags;
}

ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_loongarch(ಶೂನ್ಯ)
{
#ಯದಿ defined __linux__
    ಪ್ರತ್ಯಾಗಮ cpu_flags_getauxval();
#ಅನ್ಯಥಾ
    /* Assume no SIMD ASE supported */
    ಪ್ರತ್ಯಾಗಮ 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = av_get_cpu_flags();

    ಯದಿ (flags & AV_CPU_FLAG_LASX)
        ಪ್ರತ್ಯಾಗಮ 32;
    ಯದಿ (flags & AV_CPU_FLAG_LSX)
        ಪ್ರತ್ಯಾಗಮ 16;

    ಪ್ರತ್ಯಾಗಮ 8;
}
