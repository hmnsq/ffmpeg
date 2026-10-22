/*
 * Copyright © 2022 Rémi Denis-Courmont.
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_RISCV_CPU_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_RISCV_CPU_H

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ <stdbool.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ "libavutil/attributes_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_zbb
ಬಾಹ್ಯ attribute_visibility_hidden bool ff_rv_zbb_supported;
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const bool ff_rv_zbb_support(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_zbb
    ಹಿಂತಿರುಗಿ ff_rv_zbb_supported;
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const size_t ff_get_rv_vlenb(ಶೂನ್ಯ)
{
    size_t vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    ಹಿಂತಿರುಗಿ vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_const bool ff_rv_vlen_ಕನಿಷ್ಠ(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __riscv_v_min_vlen
    ಆದರೆ (ಬಿಟ್ಟುಗಳು <= __riscv_v_min_vlen)
        ಹಿಂತಿರುಗಿ true;
#ಇಲ್ಲದಿದ್ದರೆ
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    ಆದರೆ (ಬಿಟ್ಟುಗಳು <= 128)
        ಹಿಂತಿರುಗಿ true;
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ಬಿಟ್ಟುಗಳು <= (8 * ff_get_rv_vlenb());
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_RVV */
