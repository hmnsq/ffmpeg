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

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/float_dsp.h"
#अन्तर्भाव "float_dsp_arm.h"

शून्य ff_vector_fmul_neon(दशांश *dst, स्थिरांक दशांश *src0, स्थिरांक दशांश *src1, पूर्णांक len);

शून्य ff_vector_fmac_scalar_neon(दशांश *dst, स्थिरांक दशांश *src, दशांश mul,
                                पूर्णांक len);

शून्य ff_vector_fmul_scalar_neon(दशांश *dst, स्थिरांक दशांश *src, दशांश mul,
                                पूर्णांक len);

शून्य ff_vector_fmul_window_neon(दशांश *dst, स्थिरांक दशांश *src0,
                                स्थिरांक दशांश *src1, स्थिरांक दशांश *win, पूर्णांक len);

शून्य ff_vector_fmul_add_neon(दशांश *dst, स्थिरांक दशांश *src0, स्थिरांक दशांश *src1,
                             स्थिरांक दशांश *src2, पूर्णांक len);

शून्य ff_vector_fmul_reverse_neon(दशांश *dst, स्थिरांक दशांश *src0,
                                 स्थिरांक दशांश *src1, पूर्णांक len);

शून्य ff_butterflies_float_neon(दशांश *v1, दशांश *v2, पूर्णांक len);

दशांश ff_scalarproduct_float_neon(स्थिरांक दशांश *v1, स्थिरांक दशांश *v2, पूर्णांक len);

av_cold शून्य ff_float_dsp_init_neon(AVFloatDSPContext *fdsp)
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
