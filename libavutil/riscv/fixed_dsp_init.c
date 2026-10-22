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

#অন্তর্ভাৱ <stdint.h>

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "libavutil/attributes.h"
#অন্তর্ভাৱ "libavutil/cpu.h"
#অন্তর্ভাৱ "libavutil/fixed_dsp.h"

শূন্য ff_vector_fmul_window_scaled_rvv(int16_t *dst, ধ্রুৱ int32_t *src0,
                                      ধ্রুৱ int32_t *src1, ধ্রুৱ int32_t *win,
                                      পূর্ণাঙ্ক len, uint8_t bits);
শূন্য ff_vector_fmul_window_fixed_rvv(int32_t *dst, ধ্রুৱ int32_t *src0,
                                     ধ্রুৱ int32_t *src1, ধ্রুৱ int32_t *win,
                                     পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_fixed_rvv(পূর্ণাঙ্ক *dst, ধ্রুৱ পূর্ণাঙ্ক *src0, ধ্রুৱ পূর্ণাঙ্ক *src1,
                              পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_reverse_fixed_rvv(পূর্ণাঙ্ক *dst, ধ্রুৱ পূর্ণাঙ্ক *src0,
                                      ধ্রুৱ পূর্ণাঙ্ক *src1, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_add_fixed_rvv(পূর্ণাঙ্ক *dst, ধ্রুৱ পূর্ণাঙ্ক *src0, ধ্রুৱ পূর্ণাঙ্ক *src1,
                                  ধ্রুৱ পূর্ণাঙ্ক *src2, পূর্ণাঙ্ক len);
পূর্ণাঙ্ক ff_scalarproduct_fixed_rvv(ধ্রুৱ পূর্ণাঙ্ক *v1, ধ্রুৱ পূর্ণাঙ্ক *v2, পূর্ণাঙ্ক len);
শূন্য ff_butterflies_fixed_rvv(পূর্ণাঙ্ক *v1, পূর্ণাঙ্ক *v2, পূর্ণাঙ্ক len);

av_cold শূন্য ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#যদি HAVE_RVV
    পূর্ণাঙ্ক flags = av_get_cpu_flags();

    যদি ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        যদি (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        যদি (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
