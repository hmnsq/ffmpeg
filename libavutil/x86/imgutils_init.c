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

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "libavutil/cpu.h"
#ضمن "libavutil/error.h"
#ضمن "libavutil/imgutils_internal.h"
#ضمن "libavutil/macros.h"

#ضمن "cpu.h"

فراغ ff_image_copy_plane_uc_from_sse4(uint8_t *dst, ptrdiff_t dst_linesize,
                                      ثابت uint8_t *src, ptrdiff_t src_linesize,
                                      ptrdiff_t bytewidth, صحيح ارتفاع);

صحيح ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    ثابت uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, صحيح ارتفاع)
{
    صحيح cpu_flags = av_get_cpu_flags();
    ptrdiff_t bw_aligned = FFALIGN(bytewidth, 64);

    إذا (EXTERNAL_SSE4(cpu_flags) &&
        bw_aligned <= dst_linesize && bw_aligned <= src_linesize)
        ff_image_copy_plane_uc_from_sse4(dst, dst_linesize, src, src_linesize,
                                         bw_aligned, ارتفاع);
    وإلا
        أرجع AVERROR(ENOSYS);

    أرجع 0;
}
