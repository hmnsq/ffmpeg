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

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/error.h"
#అన్తర్భావ "libavutil/imgutils_internal.h"
#అన్తర్భావ "libavutil/macros.h"

#అన్తర్భావ "cpu.h"

శూన్య ff_image_copy_plane_uc_from_sse4(uint8_t *dst, ptrdiff_t dst_linesize,
                                      స్థిరరాశి uint8_t *src, ptrdiff_t src_linesize,
                                      ptrdiff_t bytewidth, పూర్ణాంకం ఎత్తు);

పూర్ణాంకం ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    స్థిరరాశి uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, పూర్ణాంకం ఎత్తు)
{
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();
    ptrdiff_t bw_aligned = FFALIGN(bytewidth, 64);

    ఒకవేళ (EXTERNAL_SSE4(cpu_flags) &&
        bw_aligned <= dst_linesize && bw_aligned <= src_linesize)
        ff_image_copy_plane_uc_from_sse4(dst, dst_linesize, src, src_linesize,
                                         bw_aligned, ఎత్తు);
    లేకపోతే
        తిరిగి AVERROR(ENOSYS);

    తిరిగి 0;
}
