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
#وگرنہ_اگر ARCH_ARM && HAVE_ARMV6
#شامل "arm/pixelutils.h"
#وگرنہ_اگر ARCH_MIPS && HAVE_MSA
#شامل "mips/pixelutils.h"
#وگرنہ_اگر ARCH_RISCV
#شامل "riscv/pixelutils.h"
#وگرنہ_اگر ARCH_X86 && HAVE_X86ASM
#شامل "x86/pixelutils.h"
#اگر_ختم

ساکن av_always_inline صحیح sad_wxh(ثابت uint8_t *src1, ptrdiff_t stride1,
                                    ثابت uint8_t *src2, ptrdiff_t stride2,
                                    صحیح w, صحیح h)
{
    صحیح x, y, مجموع = 0;

    برائے (y = 0; y < h; y++) {
        برائے (x = 0; x < w; x++)
            مجموع += مطلق_قدر(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    واپس مجموع;
}

#تعریف_کرو DECLARE_بلاک_FUNCTIONS(سائز)                                               \
ساکن صحیح بلاک_sad##size##x##size##_c(ثابت uint8_t *src1, ptrdiff_t stride1,    \
                                         ثابت uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    واپس sad_wxh(src1, stride1, src2, stride2, سائز, سائز);                       \
}

DECLARE_بلاک_FUNCTIONS(2)
DECLARE_بلاک_FUNCTIONS(4)
DECLARE_بلاک_FUNCTIONS(8)
DECLARE_بلاک_FUNCTIONS(16)
DECLARE_بلاک_FUNCTIONS(32)

ساکن ثابت av_pixelutils_sad_fn sad_c[] = {
    بلاک_sad_2x2_c,
    بلاک_sad_4x4_c,
    بلاک_sad_8x8_c,
    بلاک_sad_16x16_c,
    بلاک_sad_32x32_c,
};
#ورنہ
#شامل "log.h"
#اگر_ختم /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(صحیح w_بٹ, صحیح h_بٹ, صحیح aligned, خالی *log_ctx)
{
#اگر !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    واپس تہی;
#ورنہ
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    حافظہ_نقل(sad, sad_c, حجم(sad));

    اگر (w_بٹ < 1 || w_بٹ > FF_ARRAY_ELEMS(sad) ||
        h_بٹ < 1 || h_بٹ > FF_ARRAY_ELEMS(sad))
        واپس تہی;
    اگر (w_بٹ != h_بٹ) // only squared sad for now
        واپس تہی;

#اگر ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#وگرنہ_اگر ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#وگرنہ_اگر ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#وگرنہ_اگر ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#وگرنہ_اگر ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#اگر_ختم

    واپس sad[w_بٹ - 1];
#اگر_ختم
}
