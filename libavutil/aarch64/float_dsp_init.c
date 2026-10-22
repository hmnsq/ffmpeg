/*
 * ARM NEON optimised Float DSP functions
 * Copyright (c) 2008 Mans Rullgard <mans@mansr.com>
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

#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/float_dsp.h"
#समावेश "cpu.h"

व्योम ff_vector_fmul_neon(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                         पूर्णांक len);

व्योम ff_vector_fmac_scalar_neon(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                पूर्णांक len);

व्योम ff_vector_fmul_scalar_neon(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                पूर्णांक len);

व्योम ff_vector_dmul_scalar_neon(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                पूर्णांक len);

व्योम ff_vector_fmul_window_neon(भग्न *dst, स्थिर भग्न *src0,
                                स्थिर भग्न *src1, स्थिर भग्न *win, पूर्णांक len);

व्योम ff_vector_fmul_add_neon(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                             स्थिर भग्न *src2, पूर्णांक len);

व्योम ff_vector_fmul_reverse_neon(भग्न *dst, स्थिर भग्न *src0,
                                 स्थिर भग्न *src1, पूर्णांक len);

व्योम ff_butterflies_float_neon(भग्न *v1, भग्न *v2, पूर्णांक len);

भग्न ff_scalarproduct_float_neon(स्थिर भग्न *v1, स्थिर भग्न *v2, पूर्णांक len);

av_cold व्योम ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();

    अगर (have_neon(cpu_flags)) {
        fdsp->butterflies_float   = ff_butterflies_float_neon;
        fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
        fdsp->vector_dmul_scalar  = ff_vector_dmul_scalar_neon;
        fdsp->vector_fmul         = ff_vector_fmul_neon;
        fdsp->vector_fmac_scalar  = ff_vector_fmac_scalar_neon;
        fdsp->vector_fmul_add     = ff_vector_fmul_add_neon;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_neon;
        fdsp->vector_fmul_scalar  = ff_vector_fmul_scalar_neon;
        fdsp->vector_fmul_window  = ff_vector_fmul_window_neon;
    }
}
