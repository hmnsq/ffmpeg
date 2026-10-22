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

#ವ್ಯಾಖ್ಯಾನಿಸು LA_HWCAP_LSX    (1<<4)
#ವ್ಯಾಖ್ಯಾನಿಸು LA_HWCAP_LASX   (1<<5)
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cpu_flags_getauxval(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = 0;
    ಪೂರ್ಣಾಂಕ flag  = (ಪೂರ್ಣಾಂಕ)ff_getauxval(AT_HWCAP);

    ಆದರೆ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    ಆದರೆ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    ಹಿಂತಿರುಗಿ flags;
}

ಪೂರ್ಣಾಂಕ ff_get_cpu_flags_loongarch(ಶೂನ್ಯ)
{
#ಆದರೆ defined __linux__
    ಹಿಂತಿರುಗಿ cpu_flags_getauxval();
#ಇಲ್ಲದಿದ್ದರೆ
    /* Assume no SIMD ASE supported */
    ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
}

size_t ff_get_cpu_max_align_loongarch(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & AV_CPU_FLAG_LASX)
        ಹಿಂತಿರುಗಿ 32;
    ಆದರೆ (flags & AV_CPU_FLAG_LSX)
        ಹಿಂತಿರುಗಿ 16;

    ಹಿಂತಿರುಗಿ 8;
}
