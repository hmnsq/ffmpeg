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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ARM_PIXELUTILS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ARM_PIXELUTILS_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixelutils.h"

ਪੂਰਨ ff_pixelutils_sad16_armv6(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                              ਅਚਲ uint8_t *src2, ptrdiff_t stride2);
ਪੂਰਨ ff_pixelutils_sad8_armv6 (ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                              ਅਚਲ uint8_t *src2, ptrdiff_t stride2);

ਸਥਿਰ ਸਤਰਅੰਦਰ av_cold ਖਾਲੀ ff_pixelutils_sad_init_arm(av_pixelutils_sad_fn *sad, ਪੂਰਨ aligned)
{
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (have_armv6(cpu_flags)) {
        ਜੇ (aligned != 0) {
            sad[2] = ff_pixelutils_sad8_armv6;
            sad[3] = ff_pixelutils_sad16_armv6;
        }
    }
}
#ਜੇ_ਅੰਤ
