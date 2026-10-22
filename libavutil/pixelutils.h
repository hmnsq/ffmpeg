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

#నిర్వచితం_కాకపోతే AVUTIL_PIXELUTILS_H
#నిర్వచించు AVUTIL_PIXELUTILS_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

/**
 * Sum of abs(src1[x] - src2[x])
 */
రకనిర్వచనం పూర్ణాంకం (*av_pixelutils_sad_fn)(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                    స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);

/**
 * Get a potentially optimized pointer to a Sum-of-absolute-differences
 * function (see the av_pixelutils_sad_fn prototype).
 *
 * @param w_bits  1<<w_bits is the requested width of the block size
 * @param h_bits  1<<h_bits is the requested height of the block size
 * @param aligned If set to 2, the returned sad function will assume src1 and
 *                src2 addresses are aligned on the block size.
 *                If set to 1, the returned sad function will assume src1 is
 *                aligned on the block size.
 *                If set to 0, the returned sad function assume no particular
 *                alignment.
 * @param log_ctx context used for logging, can be NULL
 *
 * @return a pointer to the SAD function or NULL in case of error (because of
 *         invalid parameters)
 */
av_pixelutils_sad_fn av_pixelutils_get_sad_fn(పూర్ణాంకం w_బిట్లు, పూర్ణాంకం h_బిట్లు,
                                              పూర్ణాంకం aligned, శూన్య *log_ctx);

#అయితే_ముగింపు /* AVUTIL_PIXELUTILS_H */
