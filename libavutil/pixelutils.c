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

#ضمن <stddef.h>

#ضمن "config.h"
#ضمن "pixelutils.h"

#إذا CONFIG_PIXELUTILS
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "attributes.h"
#ضمن "macros.h"

#إذا ARCH_AARCH64 && HAVE_NEON
#ضمن "aarch64/pixelutils.h"
#وإلاإذا ARCH_ARM && HAVE_ARMV6
#ضمن "arm/pixelutils.h"
#وإلاإذا ARCH_MIPS && HAVE_MSA
#ضمن "mips/pixelutils.h"
#وإلاإذا ARCH_RISCV
#ضمن "riscv/pixelutils.h"
#وإلاإذا ARCH_X86 && HAVE_X86ASM
#ضمن "x86/pixelutils.h"
#جيڪڏهن_پورو

ساكن av_always_inline صحيح sad_wxh(ثابت uint8_t *src1, ptrdiff_t stride1,
                                    ثابت uint8_t *src2, ptrdiff_t stride2,
                                    صحيح w, صحيح h)
{
    صحيح x, y, جوڙ = 0;

    لكل (y = 0; y < h; y++) {
        لكل (x = 0; x < w; x++)
            جوڙ += مطلق_قدر(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    أرجع جوڙ;
}

#وصف_ڪريو DECLARE_بلاڪ_FUNCTIONS(سائيز)                                               \
ساكن صحيح بلاڪ_sad##size##x##size##_c(ثابت uint8_t *src1, ptrdiff_t stride1,    \
                                         ثابت uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    أرجع sad_wxh(src1, stride1, src2, stride2, سائيز, سائيز);                       \
}

DECLARE_بلاڪ_FUNCTIONS(2)
DECLARE_بلاڪ_FUNCTIONS(4)
DECLARE_بلاڪ_FUNCTIONS(8)
DECLARE_بلاڪ_FUNCTIONS(16)
DECLARE_بلاڪ_FUNCTIONS(32)

ساكن ثابت av_pixelutils_sad_fn sad_c[] = {
    بلاڪ_sad_2x2_c,
    بلاڪ_sad_4x4_c,
    بلاڪ_sad_8x8_c,
    بلاڪ_sad_16x16_c,
    بلاڪ_sad_32x32_c,
};
#وإلا
#ضمن "log.h"
#جيڪڏهن_پورو /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(صحيح w_بٽ, صحيح h_بٽ, صحيح aligned, فراغ *log_ctx)
{
#إذا !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    أرجع عدم;
#وإلا
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    يادگيري_نقل(sad, sad_c, حجم(sad));

    إذا (w_بٽ < 1 || w_بٽ > FF_ARRAY_ELEMS(sad) ||
        h_بٽ < 1 || h_بٽ > FF_ARRAY_ELEMS(sad))
        أرجع عدم;
    إذا (w_بٽ != h_بٽ) // only squared sad for now
        أرجع عدم;

#إذا ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#وإلاإذا ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#وإلاإذا ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#وإلاإذا ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#وإلاإذا ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#جيڪڏهن_پورو

    أرجع sad[w_بٽ - 1];
#جيڪڏهن_پورو
}
