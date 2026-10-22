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

#অন্তর্ভাৱ <stddef.h>

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "pixelutils.h"

#যদি CONFIG_PIXELUTILS
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "attributes.h"
#অন্তর্ভাৱ "macros.h"

#যদি ARCH_AARCH64 && HAVE_NEON
#অন্তর্ভাৱ "aarch64/pixelutils.h"
#নোচেদ্যদি ARCH_ARM && HAVE_ARMV6
#অন্তর্ভাৱ "arm/pixelutils.h"
#নোচেদ্যদি ARCH_MIPS && HAVE_MSA
#অন্তর্ভাৱ "mips/pixelutils.h"
#নোচেদ্যদি ARCH_RISCV
#অন্তর্ভাৱ "riscv/pixelutils.h"
#নোচেদ্যদি ARCH_X86 && HAVE_X86ASM
#অন্তর্ভাৱ "x86/pixelutils.h"
#endif

স্থির av_always_inline পূর্ণাঙ্ক sad_wxh(ধ্রুৱ uint8_t *src1, ptrdiff_t stride1,
                                    ধ্রুৱ uint8_t *src2, ptrdiff_t stride2,
                                    পূর্ণাঙ্ক w, পূর্ণাঙ্ক h)
{
    পূর্ণাঙ্ক x, y, sum = 0;

    বাবে (y = 0; y < h; y++) {
        বাবে (x = 0; x < w; x++)
            sum += abs(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    ঘূৰাই sum;
}

#define DECLARE_BLOCK_FUNCTIONS(size)                                               \
স্থির পূর্ণাঙ্ক block_sad_##size##x##size##_c(ধ্রুৱ uint8_t *src1, ptrdiff_t stride1,    \
                                         ধ্রুৱ uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    ঘূৰাই sad_wxh(src1, stride1, src2, stride2, size, size);                       \
}

DECLARE_BLOCK_FUNCTIONS(2)
DECLARE_BLOCK_FUNCTIONS(4)
DECLARE_BLOCK_FUNCTIONS(8)
DECLARE_BLOCK_FUNCTIONS(16)
DECLARE_BLOCK_FUNCTIONS(32)

স্থির ধ্রুৱ av_pixelutils_sad_fn sad_c[] = {
    block_sad_2x2_c,
    block_sad_4x4_c,
    block_sad_8x8_c,
    block_sad_16x16_c,
    block_sad_32x32_c,
};
#অন্যথা
#অন্তর্ভাৱ "log.h"
#endif /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(পূর্ণাঙ্ক w_bits, পূর্ণাঙ্ক h_bits, পূর্ণাঙ্ক aligned, শূন্য *log_ctx)
{
#যদি !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    ঘূৰাই রিক্ত;
#অন্যথা
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    memcpy(sad, sad_c, পরিমাণ(sad));

    যদি (w_bits < 1 || w_bits > FF_ARRAY_ELEMS(sad) ||
        h_bits < 1 || h_bits > FF_ARRAY_ELEMS(sad))
        ঘূৰাই রিক্ত;
    যদি (w_bits != h_bits) // only squared sad for now
        ঘূৰাই রিক্ত;

#যদি ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#নোচেদ্যদি ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#নোচেদ্যদি ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#নোচেদ্যদি ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#নোচেদ্যদি ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#endif

    ঘূৰাই sad[w_bits - 1];
#endif
}
