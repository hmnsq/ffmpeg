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

#شامل <stddef.h>

#شامل "config.h"
#شامل "pixelutils.h"

#اگر CONFIG_PIXELUTILS
#شامل <stdlib.h>
#شامل <string.h>

#شامل "attributes.h"
#شامل "macros.h"

#اگر ARCH_AARCH64 && HAVE_NEON
#شامل "aarch64/pixelutils.h"
#وگرنهاگر ARCH_ARM && HAVE_ARMV6
#شامل "arm/pixelutils.h"
#وگرنهاگر ARCH_MIPS && HAVE_MSA
#شامل "mips/pixelutils.h"
#وگرنهاگر ARCH_RISCV
#شامل "riscv/pixelutils.h"
#وگرنهاگر ARCH_X86 && HAVE_X86ASM
#شامل "x86/pixelutils.h"
#endif

ایستا av_always_inline صحیح sad_wxh(ثابت uint8_t *src1, ptrdiff_t stride1,
                                    ثابت uint8_t *src2, ptrdiff_t stride2,
                                    صحیح w, صحیح h)
{
    صحیح x, y, sum = 0;

    برای (y = 0; y < h; y++) {
        برای (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    بازگشت sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
ایستا صحیح block_sad_##size##x##size##_c(ثابت uint8_t *src1, ptrdiff_t stride1,    \
                                         ثابت uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    بازگشت sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

ایستا ثابت av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#وگرنه
#شامل "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(صحیح w_bits, صحیح h_bits, صحیح aligned, تهی *log_ctx)
{
#اگر !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    بازگشت پوچ;
#وگرنه
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, اندازه(sad));

    اگر (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        بازگشت پوچ;
    اگر (w_bits != h_bits) // only squared sad for now
        بازگشت پوچ;

#اگر ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#وگرنهاگر ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#وگرنهاگر ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#وگرنهاگر ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#وگرنهاگر ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    بازگشت sad[w_bits - 1];
#endif
}
