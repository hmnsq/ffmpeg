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

#ضمن <stdint.h>

#ضمن "libavutil/attributes.h"
#ضمن "libavutil/float_dsp.h"
#ضمن "float_dsp_arm.h"

فراغ ff_vector_fmul_neon(عائم *dst, ثابت عائم *src0, ثابت عائم *src1, صحيح len);

فراغ ff_vector_fmac_scalar_neon(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);

فراغ ff_vector_fmul_scalar_neon(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);

فراغ ff_vector_fmul_window_neon(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, ثابت عائم *win, صحيح len);

فراغ ff_vector_fmul_add_neon(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                             ثابت عائم *src2, صحيح len);

فراغ ff_vector_fmul_reverse_neon(عائم *dst, ثابت عائم *src0,
                                 ثابت عائم *src1, صحيح len);

فراغ ff_butterflies_float_neon(عائم *v1, عائم *v2, صحيح len);

عائم ff_scalarproduct_float_neon(ثابت عائم *v1, ثابت عائم *v2, صحيح len);

av_cold فراغ ff_float_dsp_init_neon(AVFloatDSPContext *fdsp)
{
    fdsp->vector_fmul = ff_vector_fmul_neon;
    fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_neon;
    fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_neon;
    fdsp->vector_fmul_window = ff_vector_fmul_window_neon;
    fdsp->vector_fmul_add    = ff_vector_fmul_add_neon;
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_neon;
    fdsp->butterflies_float = ff_butterflies_float_neon;
    fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
}
