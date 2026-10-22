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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_IMGUTILS_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_IMGUTILS_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "pixfmt.h"

ಪೂರ್ಣಾಂಕ avpriv_ಗಣ_systematic_pal2(uint32_t pal[256], ಎಣಿಕೆ AVPixelFormat pix_fmt);

ಪೂರ್ಣಾಂಕ ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    ಸ್ಥಿರಾಂಕ uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, ಪೂರ್ಣಾಂಕ ಎತ್ತರ);


#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_IMGUTILS_INTERNAL_H */
