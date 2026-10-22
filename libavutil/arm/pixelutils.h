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

#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ <stdint.h>

#অন্তর্ভাৱ "cpu.h"
#অন্তর্ভাৱ "libavutil/attributes.h"
#অন্তর্ভাৱ "libavutil/cpu.h"
#অন্তর্ভাৱ "libavutil/pixelutils.h"

পূর্ণাঙ্ক ff_pixelutils_sad16_armv6(ধ্রুৱ uint8_t *src1, ptrdiff_t stride1,
                              ধ্রুৱ uint8_t *src2, ptrdiff_t stride2);
পূর্ণাঙ্ক ff_pixelutils_sad8_armv6 (ধ্রুৱ uint8_t *src1, ptrdiff_t stride1,
                              ধ্রুৱ uint8_t *src2, ptrdiff_t stride2);

স্থির অন্তঃস্থ av_cold শূন্য ff_pixelutils_sad_init_arm(av_pixelutils_sad_fn *sad, পূর্ণাঙ্ক aligned)
{
    পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();

    যদি (have_armv6(cpu_flags)) {
        যদি (aligned != 0) {
            sad[2] = ff_pixelutils_sad8_armv6;
            sad[3] = ff_pixelutils_sad16_armv6;
        }
    }
}
#endif
