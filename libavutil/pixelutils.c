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

#अन्तर्भाव <stddef.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "pixelutils.h"

#यदि CONFIG_PIXELUTILS
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "macros.h"

#यदि ARCH_AARCH64 && HAVE_NEON
#अन्तर्भाव "aarch64/pixelutils.h"
#नोचेद्यदि ARCH_ARM && HAVE_ARMV6
#अन्तर्भाव "arm/pixelutils.h"
#नोचेद्यदि ARCH_MIPS && HAVE_MSA
#अन्तर्भाव "mips/pixelutils.h"
#नोचेद्यदि ARCH_RISCV
#अन्तर्भाव "riscv/pixelutils.h"
#नोचेद्यदि ARCH_X86 && HAVE_X86ASM
#अन्तर्भाव "x86/pixelutils.h"
#यदि_अन्तः

स्थिर av_always_inline पूर्णाङ्क sad_wxh(ध्रुव uint8_t *src1, ptrdiff_t stride1,
                                    ध्रुव uint8_t *src2, ptrdiff_t stride2,
                                    पूर्णाङ्क w, पूर्णाङ्क h)
{
    पूर्णाङ्क x, y, योग = 0;

    प्रति (y = 0; y < h; y++) {
        प्रति (x = 0; x < w; x++)
            योग += निरपेक्षम्(src1[x] - src2[x]);
        src1 += stride1;
        src2 += stride2;
    }
    प्रत्यागम योग;
}

#परिभाषय DECLARE_खण्डम्_FUNCTIONS(आकार)                                               \
स्थिर पूर्णाङ्क खण्डम्_sad##size##x##size##_c(ध्रुव uint8_t *src1, ptrdiff_t stride1,    \
                                         ध्रुव uint8_t *src2, ptrdiff_t stride2)    \
{                                                                                   \
    प्रत्यागम sad_wxh(src1, stride1, src2, stride2, आकार, आकार);                       \
}

DECLARE_खण्डम्_FUNCTIONS(2)
DECLARE_खण्डम्_FUNCTIONS(4)
DECLARE_खण्डम्_FUNCTIONS(8)
DECLARE_खण्डम्_FUNCTIONS(16)
DECLARE_खण्डम्_FUNCTIONS(32)

स्थिर ध्रुव av_pixelutils_sad_fn sad_c[] = {
    खण्डम्_sad_2x2_c,
    खण्डम्_sad_4x4_c,
    खण्डम्_sad_8x8_c,
    खण्डम्_sad_16x16_c,
    खण्डम्_sad_32x32_c,
};
#अन्यथा
#अन्तर्भाव "log.h"
#यदि_अन्तः /* CONFIG_PIXELUTILS */

av_pixelutils_sad_fn av_pixelutils_get_sad_fn(पूर्णाङ्क w_द्वयङ्काः, पूर्णाङ्क h_द्वयङ्काः, पूर्णाङ्क aligned, शून्य *log_ctx)
{
#यदि !CONFIG_PIXELUTILS
    av_log(log_ctx, AV_LOG_ERROR, "pixelutils support is required "
           "but libavutil is not compiled with it\n");
    प्रत्यागम रिक्त;
#अन्यथा
    av_pixelutils_sad_fn sad[FF_ARRAY_ELEMS(sad_c)];

    स्मृतिं_प्रतिलिख(sad, sad_c, परिमाण(sad));

    यदि (w_द्वयङ्काः < 1 || w_द्वयङ्काः > FF_ARRAY_ELEMS(sad) ||
        h_द्वयङ्काः < 1 || h_द्वयङ्काः > FF_ARRAY_ELEMS(sad))
        प्रत्यागम रिक्त;
    यदि (w_द्वयङ्काः != h_द्वयङ्काः) // only squared sad for now
        प्रत्यागम रिक्त;

#यदि ARCH_AARCH64 && HAVE_NEON
    ff_pixelutils_sad_init_aarch64(sad, aligned);
#नोचेद्यदि ARCH_ARM
    ff_pixelutils_sad_init_arm(sad, aligned);
#नोचेद्यदि ARCH_MIPS && HAVE_MSA
    ff_pixelutils_sad_init_mips(sad, aligned);
#नोचेद्यदि ARCH_RISCV
    ff_pixelutils_init_riscv(sad, aligned);
#नोचेद्यदि ARCH_X86 && HAVE_X86ASM
    ff_pixelutils_sad_init_x86(sad, aligned);
#यदि_अन्तः

    प्रत्यागम sad[w_द्वयङ्काः - 1];
#यदि_अन्तः
}
