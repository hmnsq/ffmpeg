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

#ifndef AVUTIL_IMGUTILS_INTERNAL_H
#define AVUTIL_IMGUTILS_INTERNAL_H

#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ <stdint.h>

#অন্তর্ভাৱ "pixfmt.h"

পূর্ণাঙ্ক avpriv_set_systematic_pal2(uint32_t pal[256], গণনা AVPixelFormat pix_fmt);

পূর্ণাঙ্ক ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    ধ্রুৱ uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, পূর্ণাঙ্ক height);


#endif /* AVUTIL_IMGUTILS_INTERNAL_H */
