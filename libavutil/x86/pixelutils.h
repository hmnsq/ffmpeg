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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_PIXELUTILS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_PIXELUTILS_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixelutils.h"

ਪੂਰਨ ff_pixelutils_sad_8x8_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                               ਅਚਲ uint8_t *src2, ptrdiff_t stride2);

ਪੂਰਨ ff_pixelutils_sad_16x16_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                 ਅਚਲ uint8_t *src2, ptrdiff_t stride2);
ਪੂਰਨ ff_pixelutils_sad_a_16x16_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                   ਅਚਲ uint8_t *src2, ptrdiff_t stride2);
ਪੂਰਨ ff_pixelutils_sad_u_16x16_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                   ਅਚਲ uint8_t *src2, ptrdiff_t stride2);

ਪੂਰਨ ff_pixelutils_sad_32x32_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                 ਅਚਲ uint8_t *src2, ptrdiff_t stride2);
ਪੂਰਨ ff_pixelutils_sad_a_32x32_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                   ਅਚਲ uint8_t *src2, ptrdiff_t stride2);
ਪੂਰਨ ff_pixelutils_sad_u_32x32_sse2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                   ਅਚਲ uint8_t *src2, ptrdiff_t stride2);

ਪੂਰਨ ff_pixelutils_sad_32x32_avx2(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                 ਅਚਲ uint8_t *src2, ptrdiff_t stride2);

ਸਥਿਰ ਸਤਰਅੰਦਰ av_cold ਖਾਲੀ ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, ਪੂਰਨ aligned)
{
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        ਚੋਣ (aligned) {
        ਹਾਲਤ 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   ਰੋਕੋ; // src1 unaligned, src2 unaligned
        ਹਾਲਤ 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; ਰੋਕੋ; // src1   aligned, src2 unaligned
        ਹਾਲਤ 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; ਰੋਕੋ; // src1   aligned, src2   aligned
        }
    }

    ਜੇ (EXTERNAL_SSE2(cpu_flags)) {
        ਚੋਣ (aligned) {
        ਹਾਲਤ 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   ਰੋਕੋ; // src1 unaligned, src2 unaligned
        ਹਾਲਤ 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; ਰੋਕੋ; // src1   aligned, src2 unaligned
        ਹਾਲਤ 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; ਰੋਕੋ; // src1   aligned, src2   aligned
        }
    }

#ਜੇ HAVE_AVX2_EXTERNAL
    ਜੇ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#ਜੇ_ਅੰਤ
}
#ਜੇ_ਅੰਤ
