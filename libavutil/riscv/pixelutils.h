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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "config.h"

#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/pixelutils.h"

முழு ff_pixelutils_sad16_rvv(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                            மாறிலி uint8_t *src2, ptrdiff_t stride2);
முழு ff_pixelutils_sad8_rvv (மாறிலி uint8_t *src1, ptrdiff_t stride1,
                            மாறிலி uint8_t *src2, ptrdiff_t stride2);

நிலையான உள்வரி av_cold வெறுமை ff_pixelutils_init_riscv(av_pixelutils_sad_fn *sad, முழு aligned)
{
#எனில் HAVE_RVV
    முழு flags = av_get_cpu_flags();

    எனில் (flags & AV_CPU_FLAG_RVV_I32 && ff_rv_vlen_least(128)) {
        sad[3] = ff_pixelutils_sad16_rvv;
        sad[2] = ff_pixelutils_sad8_rvv;
    }
#endif
}
#endif
