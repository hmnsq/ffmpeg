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

#include <stddef.h>

#include "config.h"
#include "pixelutils.h"

#nếu CONFIG_PIXELUTILS
#include <stdlib.h>
#include <string.h>

#include "attributes.h"
#include "macros.h"

#nếu ARCH_AARCH64 && HAVE_NEON
#include "aarch64/pixelutils.h"
#elif ARCH_ARM && HAVE_ARMV6
#include "arm/pixelutils.h"
#elif ARCH_MIPS && HAVE_MSA
#include "mips/pixelutils.h"
#elif ARCH_RISCV
#include "riscv/pixelutils.h"
#elif ARCH_X86 && HAVE_X86ASM
#include "x86/pixelutils.h"
#endif

static av_always_inline số_nguyên sad_wxh(const uint8_t *src1, ptrdiff_t stride1,
                                    const uint8_t *src2, ptrdiff_t stride2,
                                    số_nguyên w, số_nguyên h)
{
    số_nguyên x, y, sum = 0;

    cho (y = 0; y < h; y++) {
        cho (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    trả_về sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
static số_nguyên block_sad_##size##x##size##_c(const uint8_t *src1, ptrdiff_t stride1,    \
                                         const uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    trả_về sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

static const av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#không_thì
#include "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(số_nguyên w_bits, số_nguyên h_bits, số_nguyên aligned, void *log_ctx)
{
#nếu !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    trả_về NULL;
#không_thì
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, sizeof(sad));

    nếu (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        trả_về NULL;
    nếu (w_bits != h_bits) // only squared sad for now
        trả_về NULL;

#nếu ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#elif ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#elif ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#elif ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#elif ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    trả_về sad[w_bits - 1];
#endif
}
