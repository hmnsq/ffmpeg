/*
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

#ifndef AVUTIL_AARCH64_PIXELUTILS_H
#define AVUTIL_AARCH64_PIXELUTILS_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixelutils.h"

ಪೂರ್ಣಾಙ್ಕ ff_pixelutils_sad8_neon (ಧ್ರುವ uint8_t *src1, ptrdiff_t stride1,
                             ಧ್ರುವ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಙ್ಕ ff_pixelutils_sad16_neon(ಧ್ರುವ uint8_t *src1, ptrdiff_t stride1,
                             ಧ್ರುವ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಙ್ಕ ff_pixelutils_sad32_neon(ಧ್ರುವ uint8_t *src1, ptrdiff_t stride1,
                             ಧ್ರುವ uint8_t *src2, ptrdiff_t stride2);

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_cold ಶೂನ್ಯ ff_pixelutils_sad_init_aarch64(av_pixelutils_sad_fn *sad, ಪೂರ್ಣಾಙ್ಕ aligned)
{
    ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();

    ಯದಿ (have_neon(cpu_flags)) {
        sad[2] = ff_pixelutils_sad8_neon;
        sad[3] = ff_pixelutils_sad16_neon;
        sad[4] = ff_pixelutils_sad32_neon;
    }
}
#endif
