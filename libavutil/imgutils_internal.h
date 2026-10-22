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

#నిర్వచితం_కాకపోతే AVUTIL_IMGUTILS_అంతర్గత_H
#నిర్వచించు AVUTIL_IMGUTILS_అంతర్గత_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "pixfmt.h"

పూర్ణాంకం avpriv_సమితి_systematic_pal2(uint32_t pal[256], గణన AVPixelFormat pix_fmt);

పూర్ణాంకం ff_image_copy_plane_uc_from_x86(uint8_t       *dst, ptrdiff_t dst_linesize,
                                    స్థిరరాశి uint8_t *src, ptrdiff_t src_linesize,
                                    ptrdiff_t bytewidth, పూర్ణాంకం ఎత్తు);


#అయితే_ముగింపు /* AVUTIL_IMGUTILS_INTERNAL_H */
