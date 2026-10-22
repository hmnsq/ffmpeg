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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "config.h"

#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/pixelutils.h"

முழு ff_pixelutils_sad_8x8_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                               மாறிலி uint8_t *src2, ptrdiff_t stride2);

முழு ff_pixelutils_sad_16x16_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                 மாறிலி uint8_t *src2, ptrdiff_t stride2);
முழு ff_pixelutils_sad_a_16x16_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                   மாறிலி uint8_t *src2, ptrdiff_t stride2);
முழு ff_pixelutils_sad_u_16x16_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                   மாறிலி uint8_t *src2, ptrdiff_t stride2);

முழு ff_pixelutils_sad_32x32_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                 மாறிலி uint8_t *src2, ptrdiff_t stride2);
முழு ff_pixelutils_sad_a_32x32_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                   மாறிலி uint8_t *src2, ptrdiff_t stride2);
முழு ff_pixelutils_sad_u_32x32_sse2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                   மாறிலி uint8_t *src2, ptrdiff_t stride2);

முழு ff_pixelutils_sad_32x32_avx2(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                 மாறிலி uint8_t *src2, ptrdiff_t stride2);

நிலையான உள்வரி av_cold வெறுமை ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, முழு aligned)
{
    முழு cpu_flags = av_get_cpu_flags();

    எனில் (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        தேர்வு (aligned) {
        நிலை 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   நிறுத்து; // src1 unaligned, src2 unaligned
        நிலை 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; நிறுத்து; // src1   aligned, src2 unaligned
        நிலை 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; நிறுத்து; // src1   aligned, src2   aligned
        }
    }

    எனில் (EXTERNAL_SSE2(cpu_flags)) {
        தேர்வு (aligned) {
        நிலை 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   நிறுத்து; // src1 unaligned, src2 unaligned
        நிலை 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; நிறுத்து; // src1   aligned, src2 unaligned
        நிலை 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; நிறுத்து; // src1   aligned, src2   aligned
        }
    }

#எனில் HAVE_AVX2_EXTERNAL
    எனில் (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#endif
}
#endif
