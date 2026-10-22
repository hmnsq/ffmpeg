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

#اگر_غیر_تعریف_شدہ AVUTIL_MIPS_PIXELUTILS_H
#تعریف_کرو AVUTIL_MIPS_PIXELUTILS_H

#شامل <stddef.h>
#شامل <stdint.h>

#شامل "cpu.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/pixelutils.h"

صحیح ff_pixelutils_sad16_msa(ثابت uint8_t *src1, ptrdiff_t stride1,
                            ثابت uint8_t *src2, ptrdiff_t stride2);

ساکن اندرونی av_cold خالی ff_pixelutils_sad_init_mips(av_pixelutils_sad_fn *sad, صحیح aligned)
{
    صحیح cpu_flags = av_get_cpu_flags();

    اگر (have_msa(cpu_flags)) {
        sad[3] = ff_pixelutils_sad16_msa;
    }
}
#اگر_ختم
