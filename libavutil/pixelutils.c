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

#ଅନ୍ତର୍ଭାଵ <stddef.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "pixelutils.h"

#ଯଦି CONFIG_PIXELUTILS
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"

#ଯଦି ARCH_AARCH64 && HAVE_NEON
#ଅନ୍ତର୍ଭାଵ "aarch64/pixelutils.h"
#ନଚେତଯଦି ARCH_ARM && HAVE_ARMV6
#ଅନ୍ତର୍ଭାଵ "arm/pixelutils.h"
#ନଚେତଯଦି ARCH_MIPS && HAVE_MSA
#ଅନ୍ତର୍ଭାଵ "mips/pixelutils.h"
#ନଚେତଯଦି ARCH_RISCV
#ଅନ୍ତର୍ଭାଵ "riscv/pixelutils.h"
#ନଚେତଯଦି ARCH_X86 && HAVE_X86ASM
#ଅନ୍ତର୍ଭାଵ "x86/pixelutils.h"
#endif

ସ୍ଥିର av_always_inline ପୂର୍ଣ୍ଣସଂଖ୍ୟା sad_wxh(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,
                                    ଅଚଳ uint8_t *src2, ptrdiff_t stride2,
                                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, y, sum = 0;

    ପାଇଁ (y = 0; y < h; y++) {
        ପାଇଁ (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    ଫେରନ୍ତୁ sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା block_sad_##size##x##size##_c(ଅଚଳ uint8_t *src1, ptrdiff_t stride1,    \
                                         ଅଚଳ uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    ଫେରନ୍ତୁ sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

ସ୍ଥିର ଅଚଳ av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#ଅନ୍ୟଥା
#ଅନ୍ତର୍ଭାଵ "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(ପୂର୍ଣ୍ଣସଂଖ୍ୟା w_bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା h_bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା aligned, ଶୂନ୍ୟ *log_ctx)
{
#ଯଦି !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    ଫେରନ୍ତୁ ଖାଲି;
#ଅନ୍ୟଥା
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, ଆକାର(sad));

    ଯଦି (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        ଫେରନ୍ତୁ ଖାଲି;
    ଯଦି (w_bits != h_bits) // only squared sad for now
        ଫେରନ୍ତୁ ଖାଲି;

#ଯଦି ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#ନଚେତଯଦି ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#ନଚେତଯଦି ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#ନଚେତଯଦି ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#ନଚେତଯଦି ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    ଫେରନ୍ତୁ sad[w_bits - 1];
#endif
}
