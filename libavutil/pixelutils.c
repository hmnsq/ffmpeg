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

#అన్తర్భావ <stddef.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "pixelutils.h"

#ఒకవేళ CONFIG_PIXELUTILS
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "macros.h"

#ఒకవేళ ARCH_AARCH64 && HAVE_NEON
#అన్తర్భావ "aarch64/pixelutils.h"
#లేదావేళ ARCH_ARM && HAVE_ARMV6
#అన్తర్భావ "arm/pixelutils.h"
#లేదావేళ ARCH_MIPS && HAVE_MSA
#అన్తర్భావ "mips/pixelutils.h"
#లేదావేళ ARCH_RISCV
#అన్తర్భావ "riscv/pixelutils.h"
#లేదావేళ ARCH_X86 && HAVE_X86ASM
#అన్తర్భావ "x86/pixelutils.h"
#అయితే_ముగింపు

స్థిర av_always_inline పూర్ణాంకం sad_wxh(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                                    స్థిరరాశి uint8_t *src2, ptrdiff_t stride2,
                                    పూర్ణాంకం w, పూర్ణాంకం h)
{
    పూర్ణాంకం x, y, కూడిక = 0;

    కొరకు (y = 0; y < h; y++) {
        కొరకు (x = 0; x < w; x++)
            కూడిక += నిరపేక్ష(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    తిరిగి కూడిక;
}

#నిర్వచించు DECLARE_ఖండం_FUNCTIONS(కొలత)                                               \
స్థిర పూర్ణాంకం ఖండం_sad##size##x##size##_c(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,    \
                                         స్థిరరాశి uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    తిరిగి sad_wxh(src1, stride1, src2, stride2, కొలత, కొలత);                       \
}

DECLARE_ఖండం_FUNCTIONS(2)
DECLARE_ఖండం_FUNCTIONS(4)
DECLARE_ఖండం_FUNCTIONS(8)
DECLARE_ఖండం_FUNCTIONS(16)
DECLARE_ఖండం_FUNCTIONS(32)

స్థిర స్థిరరాశి av_pixelutils_sad_fn sad_c[] = {
    ఖండం_sad_2x2_c,
    ఖండం_sad_4x4_c,
    ఖండం_sad_8x8_c,
    ఖండం_sad_16x16_c,
    ఖండం_sad_32x32_c,
};
#లేకపోతే
#అన్తర్భావ "log.h"
#అయితే_ముగింపు /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(పూర్ణాంకం w_బిట్లు, పూర్ణాంకం h_బిట్లు, పూర్ణాంకం aligned, శూన్య *log_ctx)
{
#ఒకవేళ !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    తిరిగి ఖాళీ;
#లేకపోతే
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    జ్ఞాపకం_నకలు(sad, sad_c, పరిమాణం(sad));

    ఒకవేళ (w_బిట్లు < 1 || w_బిట్లు > FF_ARRAY_ELEMS(sad) ||
        h_బిట్లు < 1 || h_బిట్లు > FF_ARRAY_ELEMS(sad))
        తిరిగి ఖాళీ;
    ఒకవేళ (w_బిట్లు != h_బిట్లు) // only squared sad for now
        తిరిగి ఖాళీ;

#ఒకవేళ ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#లేదావేళ ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#లేదావేళ ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#లేదావేళ ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#లేదావేళ ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#అయితే_ముగింపు

    తిరిగి sad[w_బిట్లు - 1];
#అయితే_ముగింపు
}
