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
#अन्तर्भाव "libavutil/fixed_dsp.h"

शून्य ff_सदिशम्_fmul_गवाक्षः_scaled_rvv(int16_t *dst, ध्रुव int32_t *src0,
                                      ध्रुव int32_t *src1, ध्रुव int32_t *win,
                                      पूर्णाङ्क len, uint8_t द्वयङ्काः);
शून्य ff_सदिशम्_fmul_गवाक्षः_fixed_rvv(int32_t *dst, ध्रुव int32_t *src0,
                                     ध्रुव int32_t *src1, ध्रुव int32_t *win,
                                     पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_fixed_rvv(पूर्णाङ्क *dst, ध्रुव पूर्णाङ्क *src0, ध्रुव पूर्णाङ्क *src1,
                              पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_reverse_fixed_rvv(पूर्णाङ्क *dst, ध्रुव पूर्णाङ्क *src0,
                                      ध्रुव पूर्णाङ्क *src1, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_सङ्कलय_fixed_rvv(पूर्णाङ्क *dst, ध्रुव पूर्णाङ्क *src0, ध्रुव पूर्णाङ्क *src1,
                                  ध्रुव पूर्णाङ्क *src2, पूर्णाङ्क len);
पूर्णाङ्क ff_scalarproduct_fixed_rvv(ध्रुव पूर्णाङ्क *v1, ध्रुव पूर्णाङ्क *v2, पूर्णाङ्क len);
शून्य ff_butterflies_fixed_rvv(पूर्णाङ्क *v1, पूर्णाङ्क *v2, पूर्णाङ्क len);

av_cold शून्य ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#यदि HAVE_RVV
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        यदि (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->सदिशम्_fmul_गवाक्षः_scaled = ff_सदिशम्_fmul_गवाक्षः_scaled_rvv;
            fdsp->सदिशम्_fmul_गवाक्षः = ff_सदिशम्_fmul_गवाक्षः_fixed_rvv;
        }

        fdsp->सदिशम्_fmul = ff_सदिशम्_fmul_fixed_rvv;
        fdsp->सदिशम्_fmul_reverse = ff_सदिशम्_fmul_reverse_fixed_rvv;
        fdsp->सदिशम्_fmul_सङ्कलय = ff_सदिशम्_fmul_सङ्कलय_fixed_rvv;

        यदि (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#यदि_अन्तः
}
