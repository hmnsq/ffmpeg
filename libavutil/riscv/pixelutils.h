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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_RISCV_PIXELUTILS_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_RISCV_PIXELUTILS_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixelutils.h"

ಪೂರ್ಣಾಂಕ ff_pixelutils_sad16_rvv(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                            ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಂಕ ff_pixelutils_sad8_rvv (ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                            ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_cold ಶೂನ್ಯ ff_pixelutils_init_riscv(av_pixelutils_sad_fn *sad, ಪೂರ್ಣಾಂಕ aligned)
{
#ಆದರೆ HAVE_RVV
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & AV_CPU_FLAG_RVV_I32 && ff_rv_vlen_ಕನಿಷ್ಠ(128)) {
        sad[3] = ff_pixelutils_sad16_rvv;
        sad[2] = ff_pixelutils_sad8_rvv;
    }
#ಆದರೆ_ಅಂತ್ಯ
}
#ಆದರೆ_ಅಂತ್ಯ
