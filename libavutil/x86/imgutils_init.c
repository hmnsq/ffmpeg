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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/error.h"
#অন্তর্ভাব "libavutil/imgutils_internal.h"
#অন্তর্ভাব "libavutil/macros.h"

#অন্তর্ভাব "cpu.h"

শূন্য ff_image_copy_plane_uc_from_sse4(uint8_t *dst, ptrdiff_t dst_linesize,
                                      ধ্রুব uint8_t *src, ptrdiff_t src_linesize,
                                      ptrdiff_t bytewidth, পূর্ণাঙ্ক height);

পূর্ণাঙ্ক ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    ধ্রুব uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, পূর্ণাঙ্ক height)
{
    পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();
    ptrdiff_t bw_aligned = FFALIGN(bytewidth, 64);

    যদি (EXTERNAL_SSE4(cpu_flags) &&
        bw_aligned <= dst_linesize && bw_aligned <= src_linesize)
        ff_image_copy_plane_uc_from_sse4(dst, dst_linesize, src, src_linesize,
                                         bw_aligned, height);
    অন্যথা
        প্রত্যাগম AVERROR(ENOSYS);

    প্রত্যাগম 0;
}
