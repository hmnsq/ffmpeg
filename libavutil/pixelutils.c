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

#अन्तर्भाव <stddef.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "pixelutils.h"

#यदि CONFIG_PIXELUTILS
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "macros.h"

#यदि ARCH_AARCH64 && HAVE_NEON
#अन्तर्भाव "aarch64/pixelutils.h"
#अथवायदि ARCH_ARM && HAVE_ARMV6
#अन्तर्भाव "arm/pixelutils.h"
#अथवायदि ARCH_MIPS && HAVE_MSA
#अन्तर्भाव "mips/pixelutils.h"
#अथवायदि ARCH_RISCV
#अन्तर्भाव "riscv/pixelutils.h"
#अथवायदि ARCH_X86 && HAVE_X86ASM
#अन्तर्भाव "x86/pixelutils.h"
#endif

स्थिर av_always_inline पूर्णाङ्क sad_wxh(अचर uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                    अचर uint8_t *src2, सूचक_भेद_प्रकार stride2,
                                    पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क x, y, sum = 0;

    लागि (y = 0; y < h; y++) {
        लागि (x = 0; x < w; x++)
            sum += असल(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    फर्काऊ sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
स्थिर पूर्णाङ्क block_sad_##size##x##size##_c(अचर uint8_t *src1, सूचक_भेद_प्रकार stride1,    \
                                         अचर uint8_t *src2, सूचक_भेद_प्रकार stride2)    \
{                                                                                   \
    फर्काऊ sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

स्थिर अचर av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#अन्यथा
#अन्तर्भाव "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(पूर्णाङ्क w_bits, पूर्णाङ्क h_bits, पूर्णाङ्क aligned, शून्य *log_ctx)
{
#यदि !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    फर्काऊ रिक्त;
#अन्यथा
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    स_नकल(sad, sad_c, परिमाण(sad));

    यदि (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        फर्काऊ रिक्त;
    यदि (w_bits != h_bits) // only squared sad for now
        फर्काऊ रिक्त;

#यदि ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#अथवायदि ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#अथवायदि ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#अथवायदि ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#अथवायदि ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    फर्काऊ sad[w_bits - 1];
#endif
}
