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

#অন্তর্ভাৱ <stdint.h>

#অন্তর্ভাৱ "libavutil/attributes.h"
#অন্তর্ভাৱ "libavutil/cpu.h"
#অন্তর্ভাৱ "libavutil/float_dsp.h"
#অন্তর্ভাৱ "cpu.h"

শূন্য ff_vector_fmul_neon(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0, ধ্রুৱ ভিন্ন *src1,
                         পূর্ণাঙ্ক len);

শূন্য ff_vector_fmac_scalar_neon(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src, ভিন্ন mul,
                                পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_scalar_neon(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src, ভিন্ন mul,
                                পূর্ণাঙ্ক len);

শূন্য ff_vector_dmul_scalar_neon(দ্ৱিগুণ *dst, ধ্রুৱ দ্ৱিগুণ *src, দ্ৱিগুণ mul,
                                পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_window_neon(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0,
                                ধ্রুৱ ভিন্ন *src1, ধ্রুৱ ভিন্ন *win, পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_add_neon(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0, ধ্রুৱ ভিন্ন *src1,
                             ধ্রুৱ ভিন্ন *src2, পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_reverse_neon(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0,
                                 ধ্রুৱ ভিন্ন *src1, পূর্ণাঙ্ক len);

শূন্য ff_butterflies_float_neon(ভিন্ন *v1, ভিন্ন *v2, পূর্ণাঙ্ক len);

ভিন্ন ff_scalarproduct_float_neon(ধ্রুৱ ভিন্ন *v1, ধ্রুৱ ভিন্ন *v2, পূর্ণাঙ্ক len);

av_cold শূন্য ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();

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
