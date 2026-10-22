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

#અન્તર્ભાવ <stddef.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "pixelutils.h"

#જો CONFIG_PIXELUTILS
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "macros.h"

#જો ARCH_AARCH64 && HAVE_NEON
#અન્તર્ભાવ "aarch64/pixelutils.h"
#અથવાજો ARCH_ARM && HAVE_ARMV6
#અન્તર્ભાવ "arm/pixelutils.h"
#અથવાજો ARCH_MIPS && HAVE_MSA
#અન્તર્ભાવ "mips/pixelutils.h"
#અથવાજો ARCH_RISCV
#અન્તર્ભાવ "riscv/pixelutils.h"
#અથવાજો ARCH_X86 && HAVE_X86ASM
#અન્તર્ભાવ "x86/pixelutils.h"
#endif

સ્થિર av_always_inline પૂર્ણાંક sad_wxh(અચલ uint8_t *src1, ptrdiff_t stride1,
                                    અચલ uint8_t *src2, ptrdiff_t stride2,
                                    પૂર્ણાંક w, પૂર્ણાંક h)
{
    પૂર્ણાંક x, y, sum = 0;

    માટે (y = 0; y < h; y++) {
        માટે (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    પાછા sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
સ્થિર પૂર્ણાંક block_sad_##size##x##size##_c(અચલ uint8_t *src1, ptrdiff_t stride1,    \
                                         અચલ uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    પાછા sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

સ્થિર અચલ av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#નહીંતર
#અન્તર્ભાવ "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(પૂર્ણાંક w_bits, પૂર્ણાંક h_bits, પૂર્ણાંક aligned, શૂન્ય *log_ctx)
{
#જો !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    પાછા ખાલી;
#નહીંતર
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, કદ(sad));

    જો (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        પાછા ખાલી;
    જો (w_bits != h_bits) // only squared sad for now
        પાછા ખાલી;

#જો ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#અથવાજો ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#અથવાજો ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#અથવાજો ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#અથવાજો ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    પાછા sad[w_bits - 1];
#endif
}
