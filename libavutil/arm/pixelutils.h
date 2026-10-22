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

#ifndef AVUTIL_ARM_PIXELUTILS_H
#define AVUTIL_ARM_PIXELUTILS_H

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "cpu.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/pixelutils.h"

पूर्णाङ्क ff_pixelutils_sad16_armv6(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                              ध्रुव uint8_t *src2, ptrdiff_t stride2);
पूर्णाङ्क ff_pixelutils_sad8_armv6 (ध्रुव uint8_t *src1, ptrdiff_t stride1,
                              ध्रुव uint8_t *src2, ptrdiff_t stride2);

स्थिर अन्तःस्थ av_cold शून्य ff_pixelutils_sad_init_arm(av_pixelutils_sad_fn *sad, पूर्णाङ्क aligned)
{
    पूर्णाङ्क cpu_flags = av_get_cpu_flags();

    सचे (have_armv6(cpu_flags)) {
        सचे (aligned != 0) {
            sad[2] = ff_pixelutils_sad8_armv6;
            sad[3] = ff_pixelutils_sad16_armv6;
        }
    }
}
#endif
