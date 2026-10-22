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

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/error.h"
#समावेश "libavutil/imgutils_internal.h"
#समावेश "libavutil/macros.h"

#समावेश "cpu.h"

व्योम ff_image_copy_plane_uc_from_sse4(uint8_t *dst, सूचक_भेद_प्रकार dst_linesize,
                                      स्थिर uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                                      सूचक_भेद_प्रकार bytewidth, पूर्णांक height);

पूर्णांक ff_image_copy_plane_uc_from_x86(uint8_t       *dst, सूचक_भेद_प्रकार dst_linesize,
                                    स्थिर uint8_t *src, सूचक_भेद_प्रकार src_linesize,
                                    सूचक_भेद_प्रकार bytewidth, पूर्णांक height)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();
    सूचक_भेद_प्रकार bw_aligned = FFALIGN(bytewidth, 64);

    अगर (EXTERNAL_SSE4(cpu_flags) &&
        bw_aligned <= dst_linesize && bw_aligned <= src_linesize)
        ff_image_copy_plane_uc_from_sse4(dst, dst_linesize, src, src_linesize,
                                         bw_aligned, height);
    अन्यथा
        वापस AVERROR(ENOSYS);

    वापस 0;
}
