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

#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/float_dsp.h"

শূন্য ff_vector_fmul_rvv(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                         পূর্ণাঙ্ক len);
শূন্য ff_vector_fmac_scalar_rvv(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                                পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_scalar_rvv(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                                পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_window_rvv(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                                ধ্রুব ভিন্ন *src1, ধ্রুব ভিন্ন *win, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_add_rvv(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                             ধ্রুব ভিন্ন *src2, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_reverse_rvv(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                                 ধ্রুব ভিন্ন *src1, পূর্ণাঙ্ক len);
শূন্য ff_butterflies_float_rvv(ভিন্ন *v1, ভিন্ন *v2, পূর্ণাঙ্ক len);
ভিন্ন ff_scalarproduct_float_rvv(ধ্রুব ভিন্ন *v1, ধ্রুব ভিন্ন *v2, পূর্ণাঙ্ক len);

শূন্য ff_vector_dmul_rvv(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src0, ধ্রুব দ্বিগুণ *src1,
                         পূর্ণাঙ্ক len);
শূন্য ff_vector_dmac_scalar_rvv(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                                পূর্ণাঙ্ক len);
শূন্য ff_vector_dmul_scalar_rvv(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                                পূর্ণাঙ্ক len);
দ্বিগুণ ff_scalarproduct_double_rvv(ধ্রুব দ্বিগুণ *v1, ধ্রুব দ্বিগুণ *v2,
                                   size_t len);

av_cold শূন্য ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#যদি HAVE_RVV
    পূর্ণাঙ্ক flags = av_get_cpu_flags();

    যদি (flags & AV_CPU_FLAG_RVB) {
        যদি (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        যদি (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
