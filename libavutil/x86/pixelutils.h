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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_X86_PIXELUTILS_H
#وصف_ڪريو AVUTIL_X86_PIXELUTILS_H

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "config.h"

#ضمن "cpu.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/pixelutils.h"

صحيح ff_pixelutils_sad_8x8_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                               ثابت uint8_t *src2, ptrdiff_t stride2);

صحيح ff_pixelutils_sad_16x16_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                 ثابت uint8_t *src2, ptrdiff_t stride2);
صحيح ff_pixelutils_sad_a_16x16_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);
صحيح ff_pixelutils_sad_u_16x16_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);

صحيح ff_pixelutils_sad_32x32_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                 ثابت uint8_t *src2, ptrdiff_t stride2);
صحيح ff_pixelutils_sad_a_32x32_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);
صحيح ff_pixelutils_sad_u_32x32_sse2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                   ثابت uint8_t *src2, ptrdiff_t stride2);

صحيح ff_pixelutils_sad_32x32_avx2(ثابت uint8_t *src1, ptrdiff_t stride1,
                                 ثابت uint8_t *src2, ptrdiff_t stride2);

ساكن مضمن av_cold فراغ ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, صحيح aligned)
{
    صحيح cpu_flags = av_get_cpu_flags();

    إذا (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        بدل (aligned) {
        حالة 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   اكسر; // src1 unaligned, src2 unaligned
        حالة 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; اكسر; // src1   aligned, src2 unaligned
        حالة 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; اكسر; // src1   aligned, src2   aligned
        }
    }

    إذا (EXTERNAL_SSE2(cpu_flags)) {
        بدل (aligned) {
        حالة 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   اكسر; // src1 unaligned, src2 unaligned
        حالة 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; اكسر; // src1   aligned, src2 unaligned
        حالة 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; اكسر; // src1   aligned, src2   aligned
        }
    }

#إذا HAVE_AVX2_EXTERNAL
    إذا (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#جيڪڏهن_پورو
}
#جيڪڏهن_پورو
