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

#ضمن <stdint.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/fixed_dsp.h"

فراغ ff_vector_fmul_window_scaled_rvv(int16_t *dst, ثابت int32_t *src0,
                                      ثابت int32_t *src1, ثابت int32_t *win,
                                      صحيح len, uint8_t bits);
فراغ ff_vector_fmul_window_fixed_rvv(int32_t *dst, ثابت int32_t *src0,
                                     ثابت int32_t *src1, ثابت int32_t *win,
                                     صحيح len);
فراغ ff_vector_fmul_fixed_rvv(صحيح *dst, ثابت صحيح *src0, ثابت صحيح *src1,
                              صحيح len);
فراغ ff_vector_fmul_reverse_fixed_rvv(صحيح *dst, ثابت صحيح *src0,
                                      ثابت صحيح *src1, صحيح len);
فراغ ff_vector_fmul_add_fixed_rvv(صحيح *dst, ثابت صحيح *src0, ثابت صحيح *src1,
                                  ثابت صحيح *src2, صحيح len);
صحيح ff_scalarproduct_fixed_rvv(ثابت صحيح *v1, ثابت صحيح *v2, صحيح len);
فراغ ff_butterflies_fixed_rvv(صحيح *v1, صحيح *v2, صحيح len);

av_cold فراغ ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#𐡄𐡍 HAVE_RVV
    صحيح flags = av_get_cpu_flags();

    𐡄𐡍 ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        𐡄𐡍 (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        𐡄𐡍 (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
