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

#నిర్వచితం_కాకపోతే AVUTIL_X86_PIXELUTILS_H
#నిర్వచించు AVUTIL_X86_PIXELUTILS_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"

#అన్తర్భావ "cpu.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/pixelutils.h"

పూర్ణాంకం ff_pixelutils_sad_8x8_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                               స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);

పూర్ణాంకం ff_pixelutils_sad_16x16_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                 స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);
పూర్ణాంకం ff_pixelutils_sad_a_16x16_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                   స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);
పూర్ణాంకం ff_pixelutils_sad_u_16x16_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                   స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);

పూర్ణాంకం ff_pixelutils_sad_32x32_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                 స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);
పూర్ణాంకం ff_pixelutils_sad_a_32x32_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                   స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);
పూర్ణాంకం ff_pixelutils_sad_u_32x32_sse2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                   స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);

పూర్ణాంకం ff_pixelutils_sad_32x32_avx2(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                 స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);

స్థిర అంతఃవరుస av_cold శూన్య ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, పూర్ణాంకం aligned)
{
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    ఒకవేళ (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        ఎంపిక (aligned) {
        స్థితి 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   ఆపు; // src1 unaligned, src2 unaligned
        స్థితి 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; ఆపు; // src1   aligned, src2 unaligned
        స్థితి 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; ఆపు; // src1   aligned, src2   aligned
        }
    }

    ఒకవేళ (EXTERNAL_SSE2(cpu_flags)) {
        ఎంపిక (aligned) {
        స్థితి 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   ఆపు; // src1 unaligned, src2 unaligned
        స్థితి 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; ఆపు; // src1   aligned, src2 unaligned
        స్థితి 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; ఆపు; // src1   aligned, src2   aligned
        }
    }

#ఒకవేళ HAVE_AVX2_EXTERNAL
    ఒకవేళ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#అయితే_ముగింపు
}
#అయితే_ముగింపు
