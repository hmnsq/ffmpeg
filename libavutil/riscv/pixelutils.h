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

#ifndef AVUTIL_RISCV_PIXELUTILS_H
#define AVUTIL_RISCV_PIXELUTILS_H

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "config.h"

#अन्तर्भाव "cpu.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/pixelutils.h"

पूर्णाङ्क ff_pixelutils_sad16_rvv(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                            ध्रुव uint8_t *src2, ptrdiff_t stride2);
पूर्णाङ्क ff_pixelutils_sad8_rvv (ध्रुव uint8_t *src1, ptrdiff_t stride1,
                            ध्रुव uint8_t *src2, ptrdiff_t stride2);

स्थिर अन्तःस्थ av_cold शून्य ff_pixelutils_init_riscv(av_pixelutils_sad_fn *sad, पूर्णाङ्क aligned)
{
#जइ HAVE_RVV
    पूर्णाङ्क flags = av_get_cpu_flags();

    जइ (flags & AV_CPU_FLAG_RVV_I32 && ff_rv_vlen_least(128)) {
        sad[3] = ff_pixelutils_sad16_rvv;
        sad[2] = ff_pixelutils_sad8_rvv;
    }
#endif
}
#endif
