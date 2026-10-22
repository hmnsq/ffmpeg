/*
 * Copyright (c) 2023 Loongson Technology Corporation Limited
 * Contributed by Hecai Yuan <yuanhecai@loongson.cn>
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_LOONGARCH_TIMER_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_LOONGARCH_TIMER_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_INLINE_ASM

#ವ್ಯಾಖ್ಯಾನಿಸು AV_READ_ಸಮಯ read_ಸಮಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t read_ಸಮಯ(ಶೂನ್ಯ)
{

#ಆದರೆ ARCH_LOONGARCH64
    uint64_t a, id;
    __asm__ ಅಸ್ಥಿರ ( "rdtime.d  %0, %1" : "=r"(a), "=r"(id) :: );
    ಹಿಂತಿರುಗಿ a;
#ಇಲ್ಲದಿದ್ದರೆ
    uint32_t a, id;
    __asm__ ಅಸ್ಥಿರ ( "rdtimel.w  %0, %1" : "=r"(a), "=r"(id) :: );
    ಹಿಂತಿರುಗಿ (uint64_t)a;
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_INLINE_ASM */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_LOONGARCH_TIMER_H */
