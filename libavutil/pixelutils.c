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

#അന്തര്ഭാവ <stddef.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "pixelutils.h"

#എങ്കിൽ CONFIG_PIXELUTILS
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "macros.h"

#എങ്കിൽ ARCH_AARCH64 && HAVE_NEON
#അന്തര്ഭാവ "aarch64/pixelutils.h"
#അല്ലെങ്കിലെങ്കിൽ ARCH_ARM && HAVE_ARMV6
#അന്തര്ഭാവ "arm/pixelutils.h"
#അല്ലെങ്കിലെങ്കിൽ ARCH_MIPS && HAVE_MSA
#അന്തര്ഭാവ "mips/pixelutils.h"
#അല്ലെങ്കിലെങ്കിൽ ARCH_RISCV
#അന്തര്ഭാവ "riscv/pixelutils.h"
#അല്ലെങ്കിലെങ്കിൽ ARCH_X86 && HAVE_X86ASM
#അന്തര്ഭാവ "x86/pixelutils.h"
#endif

സ്ഥിതം av_always_inline പൂർണ്ണസംഖ്യ sad_wxh(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,
                                    സ്ഥിരം uint8_t *src2, ptrdiff_t stride2,
                                    പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h)
{
    പൂർണ്ണസംഖ്യ x, y, sum = 0;

    വേണ്ടി (y = 0; y < h; y++) {
        വേണ്ടി (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    തിരികെ sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
സ്ഥിതം പൂർണ്ണസംഖ്യ block_sad_##size##x##size##_c(സ്ഥിരം uint8_t *src1, ptrdiff_t stride1,    \
                                         സ്ഥിരം uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    തിരികെ sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

സ്ഥിതം സ്ഥിരം av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#അല്ലെങ്കിൽ
#അന്തര്ഭാവ "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(പൂർണ്ണസംഖ്യ w_bits, പൂർണ്ണസംഖ്യ h_bits, പൂർണ്ണസംഖ്യ aligned, ശൂന്യം *log_ctx)
{
#എങ്കിൽ !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    തിരികെ ശൂന്യ;
#അല്ലെങ്കിൽ
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, വലുപ്പം(sad));

    എങ്കിൽ (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        തിരികെ ശൂന്യ;
    എങ്കിൽ (w_bits != h_bits) // only squared sad for now
        തിരികെ ശൂന്യ;

#എങ്കിൽ ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#അല്ലെങ്കിലെങ്കിൽ ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#അല്ലെങ്കിലെങ്കിൽ ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#അല്ലെങ്കിലെങ്കിൽ ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#അല്ലെങ്കിലെങ്കിൽ ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    തിരികെ sad[w_bits - 1];
#endif
}
