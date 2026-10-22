/*
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

#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/cpu.h"
#অন্তর্ভাব "libavutil/float_dsp.h"
#অন্তর্ভাব "cpu.h"

শূন্য ff_vector_fmul_sse(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                        পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_avx(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                        পূর্ণাঙ্ক len);

শূন্য ff_vector_dmul_sse2(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src0, ধ্রুব দ্বিগুণ *src1,
                         পূর্ণাঙ্ক len);
শূন্য ff_vector_dmul_avx(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src0, ধ্রুব দ্বিগুণ *src1,
                        পূর্ণাঙ্ক len);

শূন্য ff_vector_fmac_scalar_sse(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                               পূর্ণাঙ্ক len);
শূন্য ff_vector_fmac_scalar_avx(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                               পূর্ণাঙ্ক len);
শূন্য ff_vector_fmac_scalar_fma3(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                                পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_scalar_sse(ভিন্ন *dst, ধ্রুব ভিন্ন *src, ভিন্ন mul,
                               পূর্ণাঙ্ক len);

শূন্য ff_vector_dmac_scalar_sse2(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                                পূর্ণাঙ্ক len);
শূন্য ff_vector_dmac_scalar_avx(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                               পূর্ণাঙ্ক len);
শূন্য ff_vector_dmac_scalar_fma3(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src, দ্বিগুণ mul,
                                পূর্ণাঙ্ক len);

শূন্য ff_vector_dmul_scalar_sse2(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src,
                                দ্বিগুণ mul, পূর্ণাঙ্ক len);
শূন্য ff_vector_dmul_scalar_avx(দ্বিগুণ *dst, ধ্রুব দ্বিগুণ *src,
                               দ্বিগুণ mul, পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_window_sse(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                               ধ্রুব ভিন্ন *src1, ধ্রুব ভিন্ন *win, পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_add_sse(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                            ধ্রুব ভিন্ন *src2, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_add_avx(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                            ধ্রুব ভিন্ন *src2, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_add_fma3(ভিন্ন *dst, ধ্রুব ভিন্ন *src0, ধ্রুব ভিন্ন *src1,
                             ধ্রুব ভিন্ন *src2, পূর্ণাঙ্ক len);

শূন্য ff_vector_fmul_reverse_sse(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                                ধ্রুব ভিন্ন *src1, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_reverse_avx(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                                ধ্রুব ভিন্ন *src1, পূর্ণাঙ্ক len);
শূন্য ff_vector_fmul_reverse_avx2(ভিন্ন *dst, ধ্রুব ভিন্ন *src0,
                                 ধ্রুব ভিন্ন *src1, পূর্ণাঙ্ক len);

ভিন্ন ff_scalarproduct_float_sse(ধ্রুব ভিন্ন *v1, ধ্রুব ভিন্ন *v2, পূর্ণাঙ্ক order);
ভিন্ন ff_scalarproduct_float_fma3(ধ্রুব ভিন্ন *v1, ধ্রুব ভিন্ন *v2, পূর্ণাঙ্ক order);

দ্বিগুণ ff_scalarproduct_double_sse2(ধ্রুব দ্বিগুণ *v1, ধ্রুব দ্বিগুণ *v2, size_t order);
দ্বিগুণ ff_scalarproduct_double_avx(ধ্রুব দ্বিগুণ *v1, ধ্রুব দ্বিগুণ *v2, size_t order);

শূন্য ff_butterflies_float_sse(ভিন্ন *restrict src0, ভিন্ন *restrict src1, পূর্ণাঙ্ক len);

av_cold শূন্য ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    পূর্ণাঙ্ক cpu_flags = av_get_cpu_flags();

    যদি (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    যদি (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    যদি (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    যদি (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    যদি (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
