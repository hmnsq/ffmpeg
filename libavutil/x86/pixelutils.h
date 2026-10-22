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

पूर्णांक ff_pixelutils_sad_8x8_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                               स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);

पूर्णांक ff_pixelutils_sad_16x16_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                 स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);
पूर्णांक ff_pixelutils_sad_a_16x16_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                   स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);
पूर्णांक ff_pixelutils_sad_u_16x16_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                   स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);

पूर्णांक ff_pixelutils_sad_32x32_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                 स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);
पूर्णांक ff_pixelutils_sad_a_32x32_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                   स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);
पूर्णांक ff_pixelutils_sad_u_32x32_sse2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                   स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);

पूर्णांक ff_pixelutils_sad_32x32_avx2(स्थिरांक uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                 स्थिरांक uint8_t *src2, सूचक_भेद_प्रकार stride2);

स्थिर ओळीत av_cold शून्य ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, पूर्णांक aligned)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();

    जर (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        निवड (aligned) {
        स्थिती 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   थांबा; // src1 unaligned, src2 unaligned
        स्थिती 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; थांबा; // src1   aligned, src2 unaligned
        स्थिती 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; थांबा; // src1   aligned, src2   aligned
        }
    }

    जर (EXTERNAL_SSE2(cpu_flags)) {
        निवड (aligned) {
        स्थिती 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   थांबा; // src1 unaligned, src2 unaligned
        स्थिती 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; थांबा; // src1   aligned, src2 unaligned
        स्थिती 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; थांबा; // src1   aligned, src2   aligned
        }
    }

#जर HAVE_AVX2_EXTERNAL
    जर (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#endif
}
#endif
