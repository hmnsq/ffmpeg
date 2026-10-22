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

#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/float_dsp.h"
#அந்தர்பாவ "cpu.h"

வெறுமை ff_vector_fmul_neon(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                         முழு len);

வெறுமை ff_vector_fmac_scalar_neon(தசம *dst, மாறிலி தசம *src, தசம mul,
                                முழு len);

வெறுமை ff_vector_fmul_scalar_neon(தசம *dst, மாறிலி தசம *src, தசம mul,
                                முழு len);

வெறுமை ff_vector_dmul_scalar_neon(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                முழு len);

வெறுமை ff_vector_fmul_window_neon(தசம *dst, மாறிலி தசம *src0,
                                மாறிலி தசம *src1, மாறிலி தசம *win, முழு len);

வெறுமை ff_vector_fmul_add_neon(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                             மாறிலி தசம *src2, முழு len);

வெறுமை ff_vector_fmul_reverse_neon(தசம *dst, மாறிலி தசம *src0,
                                 மாறிலி தசம *src1, முழு len);

வெறுமை ff_butterflies_float_neon(தசம *v1, தசம *v2, முழு len);

தசம ff_scalarproduct_float_neon(மாறிலி தசம *v1, மாறிலி தசம *v2, முழு len);

av_cold வெறுமை ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    முழு cpu_flags = av_get_cpu_flags();

    எனில் (have_neon(cpu_flags)) {
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
