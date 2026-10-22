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
#ضمن "libavutil/float_dsp.h"

فراغ ff_vector_fmul_rvv(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                         صحيح len);
فراغ ff_vector_fmac_scalar_rvv(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);
فراغ ff_vector_fmul_scalar_rvv(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);
فراغ ff_vector_fmul_window_rvv(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, ثابت عائم *win, صحيح len);
فراغ ff_vector_fmul_add_rvv(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                             ثابت عائم *src2, صحيح len);
فراغ ff_vector_fmul_reverse_rvv(عائم *dst, ثابت عائم *src0,
                                 ثابت عائم *src1, صحيح len);
فراغ ff_butterflies_float_rvv(عائم *v1, عائم *v2, صحيح len);
عائم ff_scalarproduct_float_rvv(ثابت عائم *v1, ثابت عائم *v2, صحيح len);

فراغ ff_vector_dmul_rvv(مزدوج *dst, ثابت مزدوج *src0, ثابت مزدوج *src1,
                         صحيح len);
فراغ ff_vector_dmac_scalar_rvv(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                صحيح len);
فراغ ff_vector_dmul_scalar_rvv(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                صحيح len);
مزدوج ff_scalarproduct_double_rvv(ثابت مزدوج *v1, ثابت مزدوج *v2,
                                   size_t len);

av_cold فراغ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#𐡄𐡍 HAVE_RVV
    صحيح flags = av_get_cpu_flags();

    𐡄𐡍 (flags & AV_CPU_FLAG_RVB) {
        𐡄𐡍 (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        𐡄𐡍 (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
