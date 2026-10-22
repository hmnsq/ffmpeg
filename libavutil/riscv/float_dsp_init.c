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

#समावेश <stdint.h>

#समावेश "config.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/float_dsp.h"

व्योम ff_vector_fmul_rvv(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                         पूर्णांक len);
व्योम ff_vector_fmac_scalar_rvv(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                पूर्णांक len);
व्योम ff_vector_fmul_scalar_rvv(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                पूर्णांक len);
व्योम ff_vector_fmul_window_rvv(भग्न *dst, स्थिर भग्न *src0,
                                स्थिर भग्न *src1, स्थिर भग्न *win, पूर्णांक len);
व्योम ff_vector_fmul_add_rvv(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                             स्थिर भग्न *src2, पूर्णांक len);
व्योम ff_vector_fmul_reverse_rvv(भग्न *dst, स्थिर भग्न *src0,
                                 स्थिर भग्न *src1, पूर्णांक len);
व्योम ff_butterflies_float_rvv(भग्न *v1, भग्न *v2, पूर्णांक len);
भग्न ff_scalarproduct_float_rvv(स्थिर भग्न *v1, स्थिर भग्न *v2, पूर्णांक len);

व्योम ff_vector_dmul_rvv(द्विगुन *dst, स्थिर द्विगुन *src0, स्थिर द्विगुन *src1,
                         पूर्णांक len);
व्योम ff_vector_dmac_scalar_rvv(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                पूर्णांक len);
व्योम ff_vector_dmul_scalar_rvv(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                पूर्णांक len);
द्विगुन ff_scalarproduct_double_rvv(स्थिर द्विगुन *v1, स्थिर द्विगुन *v2,
                                   माप_प्रकार len);

av_cold व्योम ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#अगर HAVE_RVV
    पूर्णांक flags = av_get_cpu_flags();

    अगर (flags & AV_CPU_FLAG_RVB) {
        अगर (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        अगर (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#पूर्ण_अगर
}
