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

#شامل <stdint.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/float_dsp.h"

تهی ff_vector_fmul_rvv(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                         صحیح len);
تهی ff_vector_fmac_scalar_rvv(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);
تهی ff_vector_fmul_scalar_rvv(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);
تهی ff_vector_fmul_window_rvv(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);
تهی ff_vector_fmul_add_rvv(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                             ثابت اعشاری *src2, صحیح len);
تهی ff_vector_fmul_reverse_rvv(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, صحیح len);
تهی ff_butterflies_float_rvv(اعشاری *v1, اعشاری *v2, صحیح len);
اعشاری ff_scalarproduct_float_rvv(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح len);

تهی ff_vector_dmul_rvv(دوگانه *dst, ثابت دوگانه *src0, ثابت دوگانه *src1,
                         صحیح len);
تهی ff_vector_dmac_scalar_rvv(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                                صحیح len);
تهی ff_vector_dmul_scalar_rvv(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                                صحیح len);
دوگانه ff_scalarproduct_double_rvv(ثابت دوگانه *v1, ثابت دوگانه *v2,
                                   size_t len);

av_cold تهی ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#اگر HAVE_RVV
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_RVB) {
        اگر (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        اگر (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
