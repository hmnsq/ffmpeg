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

#اگر_تعریف_نشده AVUTIL_IMGUTILS_داخلی_H
#تعریف_کن AVUTIL_IMGUTILS_داخلی_H

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "pixfmt.h"

صحيح avpriv_مجموعه_systematic_pal2(uint32_t pal[256], تعداد AVPixelFormat pix_fmt);

صحيح ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    ثابت uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, صحيح ارتفاع);


#پایان_اگر /* AVUTIL_IMGUTILS_INTERNAL_H */
