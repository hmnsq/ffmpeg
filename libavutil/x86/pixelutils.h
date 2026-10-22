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

#اگر_غیر_تعریف_شدہ AVUTIL_X86_PIXELUTILS_H
#تعریف_کرو AVUTIL_X86_PIXELUTILS_H

#شامل <stddef.h>
#شامل <stdint.h>

#شامل "config.h"

#شامل "cpu.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/pixelutils.h"

صحیح ff_pixelutils_sad_8x8_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                               ثابت uint8_t *src2, ptrdiff_t stride2);

صحیح ff_pixelutils_sad_16x16_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                 ثابت uint8_t *src2, ptrdiff_t stride2);
صحیح ff_pixelutils_sad_a_16x16_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);
صحیح ff_pixelutils_sad_u_16x16_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);

صحیح ff_pixelutils_sad_32x32_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                 ثابت uint8_t *src2, ptrdiff_t stride2);
صحیح ff_pixelutils_sad_a_32x32_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);
صحیح ff_pixelutils_sad_u_32x32_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);

صحیح ff_pixelutils_sad_32x32_avx2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                 ثابت uint8_t *src2, ptrdiff_t stride2);

ساکن اندرونی av_cold خالی ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, صحیح aligned)
{
    صحیح cpu_flags = av_get_cpu_flags();

    اگر (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        انتخاب (aligned) {
        حالت 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   توڑو; // src1 unaligned, src2 unaligned
        حالت 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; توڑو; // src1   aligned, src2 unaligned
        حالت 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; توڑو; // src1   aligned, src2   aligned
        }
    }

    اگر (EXTERNAL_SSE2(cpu_flags)) {
        انتخاب (aligned) {
        حالت 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   توڑو; // src1 unaligned, src2 unaligned
        حالت 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; توڑو; // src1   aligned, src2 unaligned
        حالت 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; توڑو; // src1   aligned, src2   aligned
        }
    }

#اگر HAVE_AVX2_EXTERNAL
    اگر (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#اگر_ختم
}
#اگر_ختم
