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

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/error.h"
#അന്തര്ഭാവ "libavutil/imgutils_internal.h"
#അന്തര്ഭാവ "libavutil/macros.h"

#അന്തര്ഭാവ "cpu.h"

ശൂന്യം ff_image_copy_plane_uc_from_sse4(uint8_t *dst, ptrdiff_t dst_linesize,
                                      സ്ഥിരം uint8_t *src, ptrdiff_t src_linesize,
                                      ptrdiff_t bytewidth, പൂർണ്ണസംഖ്യ height);

പൂർണ്ണസംഖ്യ ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    സ്ഥിരം uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, പൂർണ്ണസംഖ്യ height)
{
    പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();
    ptrdiff_t bw_aligned = FFALIGN(bytewidth, 64);

    എങ്കിൽ (EXTERNAL_SSE4(cpu_flags) &&
        bw_aligned <= dst_linesize && bw_aligned <= src_linesize)
        ff_image_copy_plane_uc_from_sse4(dst, dst_linesize, src, src_linesize,
                                         bw_aligned, height);
    അല്ലെങ്കിൽ
        തിരികെ AVERROR(ENOSYS);

    തിരികെ 0;
}
