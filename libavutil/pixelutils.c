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

#समावेश <stddef.h>

#समावेश "config.h"
#समावेश "pixelutils.h"

#अगर CONFIG_PIXELUTILS
#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "attributes.h"
#समावेश "macros.h"

#अगर ARCH_AARCH64 && HAVE_NEON
#समावेश "aarch64/pixelutils.h"
#या_अगर ARCH_ARM && HAVE_ARMV6
#समावेश "arm/pixelutils.h"
#या_अगर ARCH_MIPS && HAVE_MSA
#समावेश "mips/pixelutils.h"
#या_अगर ARCH_RISCV
#समावेश "riscv/pixelutils.h"
#या_अगर ARCH_X86 && HAVE_X86ASM
#समावेश "x86/pixelutils.h"
#पूर्ण_अगर

अटल av_always_inline पूर्णांक sad_wxh(स्थिर uint8_t *src1, सूचक_भेद_प्रकार stride1,
                                    स्थिर uint8_t *src2, सूचक_भेद_प्रकार stride2,
                                    पूर्णांक w, पूर्णांक h)
{
    पूर्णांक x, y, योग = 0;

    क्रम (y = 0; y < h; y++) {
        क्रम (x = 0; x < w; x++)
            योग += असल(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    वापस योग;
}

#घोषणा DECLARE_BLOCK_FUNCTIONS(आकार)                                               \
अटल पूर्णांक block_sad_##size##x##size##_c(स्थिर uint8_t *src1, सूचक_भेद_प्रकार stride1,    \
                                         स्थिर uint8_t *src2, सूचक_भेद_प्रकार stride2)    \
{                                                                                   \
    वापस sad_wxh(src1, stride1, src2, stride2, आकार, आकार);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

अटल स्थिर av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#अन्यथा
#समावेश "log.h"
#पूर्ण_अगर /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(पूर्णांक w_bits, पूर्णांक h_bits, पूर्णांक aligned, व्योम *log_ctx)
{
#अगर !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    वापस शून्य;
#अन्यथा
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    स_नकल(sad, sad_c, माप(sad));

    अगर (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        वापस शून्य;
    अगर (w_bits != h_bits) // only squared sad for now
        वापस शून्य;

#अगर ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#या_अगर ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#या_अगर ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#या_अगर ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#या_अगर ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#पूर्ण_अगर

    वापस sad[w_bits - 1];
#पूर्ण_अगर
}
