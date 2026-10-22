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

#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/float_dsp.h"
#অন্তর্ভাব "cpu.h"

শূন্য ff_vector_fmul_neon(দশমিক *dst, ধ্রুবক দশমিক *src0, ধ্রুবক দশমিক *src1,
                         পূর্ণসংখ্যা len);

শূন্য ff_vector_fmac_scalar_neon(দশমিক *dst, ধ্রুবক দশমিক *src, দশমিক mul,
                                পূর্ণসংখ্যা len);

শূন্য ff_vector_fmul_scalar_neon(দশমিক *dst, ধ্রুবক দশমিক *src, দশমিক mul,
                                পূর্ণসংখ্যা len);

শূন্য ff_vector_dmul_scalar_neon(দ্বিগুণ *dst, ধ্রুবক দ্বিগুণ *src, দ্বিগুণ mul,
                                পূর্ণসংখ্যা len);

শূন্য ff_vector_fmul_window_neon(দশমিক *dst, ধ্রুবক দশমিক *src0,
                                ধ্রুবক দশমিক *src1, ধ্রুবক দশমিক *win, পূর্ণসংখ্যা len);

শূন্য ff_vector_fmul_add_neon(দশমিক *dst, ধ্রুবক দশমিক *src0, ধ্রুবক দশমিক *src1,
                             ধ্রুবক দশমিক *src2, পূর্ণসংখ্যা len);

শূন্য ff_vector_fmul_reverse_neon(দশমিক *dst, ধ্রুবক দশমিক *src0,
                                 ধ্রুবক দশমিক *src1, পূর্ণসংখ্যা len);

শূন্য ff_butterflies_float_neon(দশমিক *v1, দশমিক *v2, পূর্ণসংখ্যা len);

দশমিক ff_scalarproduct_float_neon(ধ্রুবক দশমিক *v1, ধ্রুবক দশমিক *v2, পূর্ণসংখ্যা len);

av_cold শূন্য ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    পূর্ণসংখ্যা cpu_flags = av_get_cpu_flags();

    যদি (have_neon(cpu_flags)) {
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
