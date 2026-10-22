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

#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "pixelutils.h"

#ಯದಿ CONFIG_PIXELUTILS
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#ಯದಿ ARCH_AARCH64 && HAVE_NEON
#ಅನ್ತರ್ಭಾವ "aarch64/pixelutils.h"
#ನೋಚೇದ್ಯದಿ ARCH_ARM && HAVE_ARMV6
#ಅನ್ತರ್ಭಾವ "arm/pixelutils.h"
#ನೋಚೇದ್ಯದಿ ARCH_MIPS && HAVE_MSA
#ಅನ್ತರ್ಭಾವ "mips/pixelutils.h"
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
#ಅನ್ತರ್ಭಾವ "riscv/pixelutils.h"
#ನೋಚೇದ್ಯದಿ ARCH_X86 && HAVE_X86ASM
#ಅನ್ತರ್ಭಾವ "x86/pixelutils.h"
#endif

ಸ್ಥಿರ av_always_inline ಪೂರ್ಣಾಙ್ಕ sad_wxh(ಧ್ರುವ uint8_t *src1, ptrdiff_t stride1,
                                    ಧ್ರುವ uint8_t *src2, ptrdiff_t stride2,
                                    ಪೂರ್ಣಾಙ್ಕ w, ಪೂರ್ಣಾಙ್ಕ h)
{
    ಪೂರ್ಣಾಙ್ಕ x, y, sum = 0;

    ಪ್ರತಿ (y = 0; y < h; y++) {
        ಪ್ರತಿ (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    ಪ್ರತ್ಯಾಗಮ sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ block_sad_##size##x##size##_c(ಧ್ರುವ uint8_t *src1, ptrdiff_t stride1,    \
                                         ಧ್ರುವ uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    ಪ್ರತ್ಯಾಗಮ sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

ಸ್ಥಿರ ಧ್ರುವ av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#ಅನ್ಯಥಾ
#ಅನ್ತರ್ಭಾವ "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(ಪೂರ್ಣಾಙ್ಕ w_bits, ಪೂರ್ಣಾಙ್ಕ h_bits, ಪೂರ್ಣಾಙ್ಕ aligned, ಶೂನ್ಯ *log_ctx)
{
#ಯದಿ !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
#ಅನ್ಯಥಾ
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, ಪರಿಮಾಣ(sad));

    ಯದಿ (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಯದಿ (w_bits != h_bits) // only squared sad for now
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

#ಯದಿ ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#ನೋಚೇದ್ಯದಿ ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#ನೋಚೇದ್ಯದಿ ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#ನೋಚೇದ್ಯದಿ ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    ಪ್ರತ್ಯಾಗಮ sad[w_bits - 1];
#endif
}
