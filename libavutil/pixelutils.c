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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixelutils.h"

#ਜੇ CONFIG_PIXELUTILS
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

#ਜੇ ARCH_AARCH64 && HAVE_NEON
#ਅਨ੍ਤਰ੍ਭਾਵ "aarch64/pixelutils.h"
#ਜਾਂਜੇ ARCH_ARM && HAVE_ARMV6
#ਅਨ੍ਤਰ੍ਭਾਵ "arm/pixelutils.h"
#ਜਾਂਜੇ ARCH_MIPS && HAVE_MSA
#ਅਨ੍ਤਰ੍ਭਾਵ "mips/pixelutils.h"
#ਜਾਂਜੇ ARCH_RISCV
#ਅਨ੍ਤਰ੍ਭਾਵ "riscv/pixelutils.h"
#ਜਾਂਜੇ ARCH_X86 && HAVE_X86ASM
#ਅਨ੍ਤਰ੍ਭਾਵ "x86/pixelutils.h"
#ਜੇ_ਅੰਤ

ਸਥਿਰ av_always_inline ਪੂਰਨ sad_wxh(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,
                                    ਅਚਲ uint8_t *src2, ptrdiff_t stride2,
                                    ਪੂਰਨ w, ਪੂਰਨ h)
{
    ਪੂਰਨ x, y, ਜੋੜ = 0;

    ਲਈ (y = 0; y < h; y++) {
        ਲਈ (x = 0; x < w; x++)
            ਜੋੜ += ਨਿਰਪੇਖ(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    ਵਾਪਸ ਜੋੜ;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DECLARE_ਖੰਡ_FUNCTIONS(ਮਾਪ)                                               \
ਸਥਿਰ ਪੂਰਨ ਖੰਡ_sad##size##x##size##_c(ਅਚਲ uint8_t *src1, ptrdiff_t stride1,    \
                                         ਅਚਲ uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    ਵਾਪਸ sad_wxh(src1, stride1, src2, stride2, ਮਾਪ, ਮਾਪ);                       \
}

DECLARE_ਖੰਡ_FUNCTIONS(2)
DECLARE_ਖੰਡ_FUNCTIONS(4)
DECLARE_ਖੰਡ_FUNCTIONS(8)
DECLARE_ਖੰਡ_FUNCTIONS(16)
DECLARE_ਖੰਡ_FUNCTIONS(32)

ਸਥਿਰ ਅਚਲ av_pixelutils_sad_fn sad_c[] = {
    ਖੰਡ_sad_2x2_c,
    ਖੰਡ_sad_4x4_c,
    ਖੰਡ_sad_8x8_c,
    ਖੰਡ_sad_16x16_c,
    ਖੰਡ_sad_32x32_c,
};
#ਨਹੀਂਤਾਂ
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਜੇ_ਅੰਤ /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(ਪੂਰਨ w_ਬਿੱਟ, ਪੂਰਨ h_ਬਿੱਟ, ਪੂਰਨ aligned, ਖਾਲੀ *log_ctx)
{
#ਜੇ !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    ਵਾਪਸ ਨਿਰਾ;
#ਨਹੀਂਤਾਂ
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(sad, sad_c, ਆਕਾਰ(sad));

    ਜੇ (w_ਬਿੱਟ < 1 || w_ਬਿੱਟ > FF_ARRAY_ELEMS(sad) ||
        h_ਬਿੱਟ < 1 || h_ਬਿੱਟ > FF_ARRAY_ELEMS(sad))
        ਵਾਪਸ ਨਿਰਾ;
    ਜੇ (w_ਬਿੱਟ != h_ਬਿੱਟ) // only squared sad for now
        ਵਾਪਸ ਨਿਰਾ;

#ਜੇ ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#ਜਾਂਜੇ ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#ਜਾਂਜੇ ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#ਜਾਂਜੇ ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#ਜਾਂਜੇ ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ sad[w_ਬਿੱਟ - 1];
#ਜੇ_ਅੰਤ
}
