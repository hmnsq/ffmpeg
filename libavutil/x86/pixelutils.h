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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "config.h"

#অন্তর্ভাব "cpu.h"
#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/pixelutils.h"

পূর্ণসংখ্যা ff_pixelutils_sad_8x8_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                               ধ্রুবক uint8_t *src2, ptrdiff_t stride2);

পূর্ণসংখ্যা ff_pixelutils_sad_16x16_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                 ধ্রুবক uint8_t *src2, ptrdiff_t stride2);
পূর্ণসংখ্যা ff_pixelutils_sad_a_16x16_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                   ধ্রুবক uint8_t *src2, ptrdiff_t stride2);
পূর্ণসংখ্যা ff_pixelutils_sad_u_16x16_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                   ধ্রুবক uint8_t *src2, ptrdiff_t stride2);

পূর্ণসংখ্যা ff_pixelutils_sad_32x32_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                 ধ্রুবক uint8_t *src2, ptrdiff_t stride2);
পূর্ণসংখ্যা ff_pixelutils_sad_a_32x32_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                   ধ্রুবক uint8_t *src2, ptrdiff_t stride2);
পূর্ণসংখ্যা ff_pixelutils_sad_u_32x32_sse2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                   ধ্রুবক uint8_t *src2, ptrdiff_t stride2);

পূর্ণসংখ্যা ff_pixelutils_sad_32x32_avx2(ধ্রুবক uint8_t *src1, ptrdiff_t stride1,
                                 ধ্রুবক uint8_t *src2, ptrdiff_t stride2);

স্থির অন্তঃরেখ av_cold শূন্য ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, পূর্ণসংখ্যা aligned)
{
    পূর্ণসংখ্যা cpu_flags = av_get_cpu_flags();

    যদি (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        নির্বাচন (aligned) {
        ক্ষেত্র 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   বিরতি; // src1 unaligned, src2 unaligned
        ক্ষেত্র 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; বিরতি; // src1   aligned, src2 unaligned
        ক্ষেত্র 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; বিরতি; // src1   aligned, src2   aligned
        }
    }

    যদি (EXTERNAL_SSE2(cpu_flags)) {
        নির্বাচন (aligned) {
        ক্ষেত্র 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   বিরতি; // src1 unaligned, src2 unaligned
        ক্ষেত্র 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; বিরতি; // src1   aligned, src2 unaligned
        ক্ষেত্র 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; বিরতি; // src1   aligned, src2   aligned
        }
    }

#যদি HAVE_AVX2_EXTERNAL
    যদি (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#endif
}
#endif
