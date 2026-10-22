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

#அந்தர்பாவ <stddef.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "pixelutils.h"

#எனில் CONFIG_PIXELUTILS
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "macros.h"

#எனில் ARCH_AARCH64 && HAVE_NEON
#அந்தர்பாவ "aarch64/pixelutils.h"
#அல்லதெனில் ARCH_ARM && HAVE_ARMV6
#அந்தர்பாவ "arm/pixelutils.h"
#அல்லதெனில் ARCH_MIPS && HAVE_MSA
#அந்தர்பாவ "mips/pixelutils.h"
#அல்லதெனில் ARCH_RISCV
#அந்தர்பாவ "riscv/pixelutils.h"
#அல்லதெனில் ARCH_X86 && HAVE_X86ASM
#அந்தர்பாவ "x86/pixelutils.h"
#endif

நிலையான av_always_inline முழு sad_wxh(மாறிலி uint8_t *src1, ptrdiff_t stride1,
                                    மாறிலி uint8_t *src2, ptrdiff_t stride2,
                                    முழு w, முழு h)
{
    முழு x, y, sum = 0;

    க்கு (y = 0; y < h; y++) {
        க்கு (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    திரும்பு sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
நிலையான முழு block_sad_##size##x##size##_c(மாறிலி uint8_t *src1, ptrdiff_t stride1,    \
                                         மாறிலி uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    திரும்பு sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

நிலையான மாறிலி av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#இல்லையெனில்
#அந்தர்பாவ "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(முழு w_bits, முழு h_bits, முழு aligned, வெறுமை *log_ctx)
{
#எனில் !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    திரும்பு வெற்று;
#இல்லையெனில்
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, அளவு(sad));

    எனில் (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        திரும்பு வெற்று;
    எனில் (w_bits != h_bits) // only squared sad for now
        திரும்பு வெற்று;

#எனில் ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#அல்லதெனில் ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#அல்லதெனில் ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#அல்லதெனில் ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#அல்லதெனில் ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    திரும்பு sad[w_bits - 1];
#endif
}
