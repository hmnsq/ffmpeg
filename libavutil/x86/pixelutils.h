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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_PIXELUTILS_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_PIXELUTILS_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixelutils.h"

ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_8x8_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                               ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);

ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_16x16_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                 ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_a_16x16_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                   ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_u_16x16_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                   ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);

ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_32x32_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                 ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_a_32x32_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                   ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);
ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_u_32x32_sse2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                   ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);

ಪೂರ್ಣಾಂಕ ff_pixelutils_sad_32x32_avx2(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                 ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2);

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_cold ಶೂನ್ಯ ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, ಪೂರ್ಣಾಂಕ aligned)
{
    ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();

    ಆದರೆ (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        ಆಯ್ಕೆ (aligned) {
        ಸ್ಥಿತಿ 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   ನಿಲ್ಲಿಸು; // src1 unaligned, src2 unaligned
        ಸ್ಥಿತಿ 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; ನಿಲ್ಲಿಸು; // src1   aligned, src2 unaligned
        ಸ್ಥಿತಿ 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; ನಿಲ್ಲಿಸು; // src1   aligned, src2   aligned
        }
    }

    ಆದರೆ (EXTERNAL_SSE2(cpu_flags)) {
        ಆಯ್ಕೆ (aligned) {
        ಸ್ಥಿತಿ 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   ನಿಲ್ಲಿಸು; // src1 unaligned, src2 unaligned
        ಸ್ಥಿತಿ 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; ನಿಲ್ಲಿಸು; // src1   aligned, src2 unaligned
        ಸ್ಥಿತಿ 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; ನಿಲ್ಲಿಸು; // src1   aligned, src2   aligned
        }
    }

#ಆದರೆ HAVE_AVX2_EXTERNAL
    ಆದರೆ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#ಆದರೆ_ಅಂತ್ಯ
}
#ಆದರೆ_ಅಂತ್ಯ
