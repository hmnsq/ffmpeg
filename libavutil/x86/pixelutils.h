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

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/pixelutils.h"

പൂർണ്ണസംഖ്യ ff_pixelutils_sad_8x8_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                               സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);

പൂർണ്ണസംഖ്യ ff_pixelutils_sad_16x16_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                 സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);
പൂർണ്ണസംഖ്യ ff_pixelutils_sad_a_16x16_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                   സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);
പൂർണ്ണസംഖ്യ ff_pixelutils_sad_u_16x16_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                   സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);

പൂർണ്ണസംഖ്യ ff_pixelutils_sad_32x32_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                 സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);
പൂർണ്ണസംഖ്യ ff_pixelutils_sad_a_32x32_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                   സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);
പൂർണ്ണസംഖ്യ ff_pixelutils_sad_u_32x32_sse2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                   സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);

പൂർണ്ണസംഖ്യ ff_pixelutils_sad_32x32_avx2(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                 സ്ഥിരം uint8_t *src2, ptrdiff_t stride2);

സ്ഥിതം വരിയിൽ av_cold ശൂന്യം ff_pixelutils_sad_init_x86(av_pixelutils_sad_fn *sad, പൂർണ്ണസംഖ്യ aligned)
{
    പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();

    എങ്കിൽ (EXTERNAL_SSE2(cpu_flags)) {
        sad[2] = ff_pixelutils_sad_8x8_sse2;
        തിരഞ്ഞെടുപ്പ് (aligned) {
        അവസ്ഥ 0: sad[3] = ff_pixelutils_sad_16x16_sse2;   നിർത്തുക; // src1 unaligned, src2 unaligned
        അവസ്ഥ 1: sad[3] = ff_pixelutils_sad_u_16x16_sse2; നിർത്തുക; // src1   aligned, src2 unaligned
        അവസ്ഥ 2: sad[3] = ff_pixelutils_sad_a_16x16_sse2; നിർത്തുക; // src1   aligned, src2   aligned
        }
    }

    എങ്കിൽ (EXTERNAL_SSE2(cpu_flags)) {
        തിരഞ്ഞെടുപ്പ് (aligned) {
        അവസ്ഥ 0: sad[4] = ff_pixelutils_sad_32x32_sse2;   നിർത്തുക; // src1 unaligned, src2 unaligned
        അവസ്ഥ 1: sad[4] = ff_pixelutils_sad_u_32x32_sse2; നിർത്തുക; // src1   aligned, src2 unaligned
        അവസ്ഥ 2: sad[4] = ff_pixelutils_sad_a_32x32_sse2; നിർത്തുക; // src1   aligned, src2   aligned
        }
    }

#എങ്കിൽ HAVE_AVX2_EXTERNAL
    എങ്കിൽ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        sad[4] = ff_pixelutils_sad_32x32_avx2;
    }
#endif
}
#endif
