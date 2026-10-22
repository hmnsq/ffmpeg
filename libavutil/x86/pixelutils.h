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

#ifndef AVUTIL_X86_PIXELUTILS_H
#define AVUTIL_X86_PIXELUTILS_H

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ "cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/pixelutils.h"

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_8x8_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                               ଅଚଳ uint8_t *src2, ptrdiff_t stride2);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_16x16_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                 ଅଚଳ uint8_t *src2, ptrdiff_t stride2);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_a_16x16_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                   ଅଚଳ uint8_t *src2, ptrdiff_t stride2);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_u_16x16_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                   ଅଚଳ uint8_t *src2, ptrdiff_t stride2);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_32x32_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                 ଅଚଳ uint8_t *src2, ptrdiff_t stride2);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_a_32x32_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                   ଅଚଳ uint8_t *src2, ptrdiff_t stride2);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_u_32x32_sse2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                   ଅଚଳ uint8_t *src2, ptrdiff_t stride2);

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_pixelutils_sad_32x32_avx2(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                 ଅଚଳ uint8_t *src2, ptrdiff_t stride2);

ସ୍ଥିର ଧାଡ଼ିଭିତରେ av_cold ଶୂନ୍ୟ ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, ପୂର୍ଣ୍ଣସଂଖ୍ୟା aligned)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags = av_get_cpu_flags();

    ଯଦି (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        ବାଛ (aligned) {
        ସ୍ଥିତି 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   ଭାଙ୍ଗ; // src1 unaligned, src2 unaligned
        ସ୍ଥିତି 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; ଭାଙ୍ଗ; // src1   aligned, src2 unaligned
        ସ୍ଥିତି 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; ଭାଙ୍ଗ; // src1   aligned, src2   aligned
        }
    }

    ଯଦି (EXTERNAL_SSE2(cpu_flags)) {
        ବାଛ (aligned) {
        ସ୍ଥିତି 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   ଭାଙ୍ଗ; // src1 unaligned, src2 unaligned
        ସ୍ଥିତି 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; ଭାଙ୍ଗ; // src1   aligned, src2 unaligned
        ସ୍ଥିତି 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; ଭାଙ୍ଗ; // src1   aligned, src2   aligned
        }
    }

#ଯଦି HAVE_AVX2_EXTERNAL
    ଯଦି (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#endif
}
#endif
