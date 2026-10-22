/*
 * Copyright © 2022 Rémi Denis-Courmont.
 *
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

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/float_dsp.h"

शून्य ff_सदिशम्_fmul_rvv(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                         पूर्णाङ्क len);
शून्य ff_सदिशम्_fmac_scalar_rvv(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                                पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_scalar_rvv(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                                पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_गवाक्षः_rvv(भिन्न *dst, ध्रुव भिन्न *src0,
                                ध्रुव भिन्न *src1, ध्रुव भिन्न *win, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_सङ्कलय_rvv(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                             ध्रुव भिन्न *src2, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_reverse_rvv(भिन्न *dst, ध्रुव भिन्न *src0,
                                 ध्रुव भिन्न *src1, पूर्णाङ्क len);
शून्य ff_butterflies_float_rvv(भिन्न *v1, भिन्न *v2, पूर्णाङ्क len);
भिन्न ff_scalarproduct_float_rvv(ध्रुव भिन्न *v1, ध्रुव भिन्न *v2, पूर्णाङ्क len);

शून्य ff_सदिशम्_dmul_rvv(द्विगुण *dst, ध्रुव द्विगुण *src0, ध्रुव द्विगुण *src1,
                         पूर्णाङ्क len);
शून्य ff_सदिशम्_dmac_scalar_rvv(द्विगुण *dst, ध्रुव द्विगुण *src, द्विगुण mul,
                                पूर्णाङ्क len);
शून्य ff_सदिशम्_dmul_scalar_rvv(द्विगुण *dst, ध्रुव द्विगुण *src, द्विगुण mul,
                                पूर्णाङ्क len);
द्विगुण ff_scalarproduct_double_rvv(ध्रुव द्विगुण *v1, ध्रुव द्विगुण *v2,
                                   size_t len);

av_cold शून्य ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#यदि HAVE_RVV
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि (flags & AV_CPU_FLAG_RVB) {
        यदि (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->सदिशम्_fmul = ff_सदिशम्_fmul_rvv;
            fdsp->सदिशम्_fmac_scalar = ff_सदिशम्_fmac_scalar_rvv;
            fdsp->सदिशम्_fmul_scalar = ff_सदिशम्_fmul_scalar_rvv;
            fdsp->सदिशम्_fmul_गवाक्षः = ff_सदिशम्_fmul_गवाक्षः_rvv;
            fdsp->सदिशम्_fmul_सङ्कलय = ff_सदिशम्_fmul_सङ्कलय_rvv;
            fdsp->सदिशम्_fmul_reverse = ff_सदिशम्_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        यदि (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->सदिशम्_dmul = ff_सदिशम्_dmul_rvv;
            fdsp->सदिशम्_dmac_scalar = ff_सदिशम्_dmac_scalar_rvv;
            fdsp->सदिशम्_dmul_scalar = ff_सदिशम्_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#यदि_अन्तः
}
