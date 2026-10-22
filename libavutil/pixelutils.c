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

#ಆದರೆ CONFIG_PIXELUTILS
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#ಆದರೆ ARCH_AARCH64 && HAVE_NEON
#ಅನ್ತರ್ಭಾವ "aarch64/pixelutils.h"
#ಅಥವಾಆದರೆ ARCH_ARM && HAVE_ARMV6
#ಅನ್ತರ್ಭಾವ "arm/pixelutils.h"
#ಅಥವಾಆದರೆ ARCH_MIPS && HAVE_MSA
#ಅನ್ತರ್ಭಾವ "mips/pixelutils.h"
#ಅಥವಾಆದರೆ ARCH_RISCV
#ಅನ್ತರ್ಭಾವ "riscv/pixelutils.h"
#ಅಥವಾಆದರೆ ARCH_X86 && HAVE_X86ASM
#ಅನ್ತರ್ಭಾವ "x86/pixelutils.h"
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ av_always_inline ಪೂರ್ಣಾಂಕ sad_wxh(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,
                                    ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2,
                                    ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h)
{
    ಪೂರ್ಣಾಂಕ x, y, ಮೊತ್ತ = 0;

    ಗಾಗಿ (y = 0; y < h; y++) {
        ಗಾಗಿ (x = 0; x < w; x++)
            ಮೊತ್ತ += ನಿರಪೇಕ್ಷ(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    ಹಿಂತಿರುಗಿ ಮೊತ್ತ;
}

#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_ಖಂಡ_FUNCTIONS(ಗಾತ್ರ_2)                                               \
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಖಂಡ_sad##size##x##size##_c(ಸ್ಥಿರಾಂಕ uint8_t *src1, ptrdiff_t stride1,    \
                                         ಸ್ಥಿರಾಂಕ uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    ಹಿಂತಿರುಗಿ sad_wxh(src1, stride1, src2, stride2, ಗಾತ್ರ_2, ಗಾತ್ರ_2);                       \
}

DECLARE_ಖಂಡ_FUNCTIONS(2)
DECLARE_ಖಂಡ_FUNCTIONS(4)
DECLARE_ಖಂಡ_FUNCTIONS(8)
DECLARE_ಖಂಡ_FUNCTIONS(16)
DECLARE_ಖಂಡ_FUNCTIONS(32)

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ av_pixelutils_sad_fn sad_c[] = {
    ಖಂಡ_sad_2x2_c,
    ಖಂಡ_sad_4x4_c,
    ಖಂಡ_sad_8x8_c,
    ಖಂಡ_sad_16x16_c,
    ಖಂಡ_sad_32x32_c,
};
#ಇಲ್ಲದಿದ್ದರೆ
#ಅನ್ತರ್ಭಾವ "log.h"
#ಆದರೆ_ಅಂತ್ಯ /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(ಪೂರ್ಣಾಂಕ w_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ h_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ aligned, ಶೂನ್ಯ *log_ctx)
{
#ಆದರೆ !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
#ಇಲ್ಲದಿದ್ದರೆ
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    ಸ್ಮರಣೆ_ನಕಲು(sad, sad_c, ಗಾತ್ರ(sad));

    ಆದರೆ (w_ಬಿಟ್ಟುಗಳು < 1 || w_ಬಿಟ್ಟುಗಳು > FF_ARRAY_ELEMS(sad) ||
        h_ಬಿಟ್ಟುಗಳು < 1 || h_ಬಿಟ್ಟುಗಳು > FF_ARRAY_ELEMS(sad))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆದರೆ (w_ಬಿಟ್ಟುಗಳು != h_ಬಿಟ್ಟುಗಳು) // only squared sad for now
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

#ಆದರೆ ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#ಅಥವಾಆದರೆ ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#ಅಥವಾಆದರೆ ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#ಅಥವಾಆದರೆ ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#ಅಥವಾಆದರೆ ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ sad[w_ಬಿಟ್ಟುಗಳು - 1];
#ಆದರೆ_ಅಂತ್ಯ
}
