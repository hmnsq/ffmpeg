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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "config.h"

#अन्तर्भाव "cpu.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/pixelutils.h"

पूर्णाङ्क ff_pixelutils_sad_8x8_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                               ध्रुव uint8_t *src2, ptrdiff_t stride2);

पूर्णाङ्क ff_pixelutils_sad_16x16_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                 ध्रुव uint8_t *src2, ptrdiff_t stride2);
पूर्णाङ्क ff_pixelutils_sad_a_16x16_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                   ध्रुव uint8_t *src2, ptrdiff_t stride2);
पूर्णाङ्क ff_pixelutils_sad_u_16x16_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                   ध्रुव uint8_t *src2, ptrdiff_t stride2);

पूर्णाङ्क ff_pixelutils_sad_32x32_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                 ध्रुव uint8_t *src2, ptrdiff_t stride2);
पूर्णाङ्क ff_pixelutils_sad_a_32x32_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                   ध्रुव uint8_t *src2, ptrdiff_t stride2);
पूर्णाङ्क ff_pixelutils_sad_u_32x32_sse2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                   ध्रुव uint8_t *src2, ptrdiff_t stride2);

पूर्णाङ्क ff_pixelutils_sad_32x32_avx2(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                 ध्रुव uint8_t *src2, ptrdiff_t stride2);

स्थिर अन्तःस्थ av_cold शून्य ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, पूर्णाङ्क aligned)
{
    पूर्णाङ्क cpu_flags = av_get_cpu_flags();

    सचे (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        विकल्प (aligned) {
        पक्ष 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   भङ्ग; // src1 unaligned, src2 unaligned
        पक्ष 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; भङ्ग; // src1   aligned, src2 unaligned
        पक्ष 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; भङ्ग; // src1   aligned, src2   aligned
        }
    }

    सचे (EXTERNAL_SSE2(cpu_flags)) {
        विकल्प (aligned) {
        पक्ष 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   भङ्ग; // src1 unaligned, src2 unaligned
        पक्ष 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; भङ्ग; // src1   aligned, src2 unaligned
        पक्ष 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; भङ्ग; // src1   aligned, src2   aligned
        }
    }

#सचे HAVE_AVX2_EXTERNAL
    सचे (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#endif
}
#endif
