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

#ضمن "libavutil/attributes.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/float_dsp.h"
#ضمن "cpu.h"

فراغ ff_vector_fmul_sse(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                        صحيح len);
فراغ ff_vector_fmul_avx(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                        صحيح len);

فراغ ff_vector_dmul_sse2(مزدوج *dst, ثابت مزدوج *src0, ثابت مزدوج *src1,
                         صحيح len);
فراغ ff_vector_dmul_avx(مزدوج *dst, ثابت مزدوج *src0, ثابت مزدوج *src1,
                        صحيح len);

فراغ ff_vector_fmac_scalar_sse(عائم *dst, ثابت عائم *src, عائم mul,
                               صحيح len);
فراغ ff_vector_fmac_scalar_avx(عائم *dst, ثابت عائم *src, عائم mul,
                               صحيح len);
فراغ ff_vector_fmac_scalar_fma3(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);

فراغ ff_vector_fmul_scalar_sse(عائم *dst, ثابت عائم *src, عائم mul,
                               صحيح len);

فراغ ff_vector_dmac_scalar_sse2(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                صحيح len);
فراغ ff_vector_dmac_scalar_avx(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                               صحيح len);
فراغ ff_vector_dmac_scalar_fma3(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                صحيح len);

فراغ ff_vector_dmul_scalar_sse2(مزدوج *dst, ثابت مزدوج *src,
                                مزدوج mul, صحيح len);
فراغ ff_vector_dmul_scalar_avx(مزدوج *dst, ثابت مزدوج *src,
                               مزدوج mul, صحيح len);

فراغ ff_vector_fmul_window_sse(عائم *dst, ثابت عائم *src0,
                               ثابت عائم *src1, ثابت عائم *win, صحيح len);

فراغ ff_vector_fmul_add_sse(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                            ثابت عائم *src2, صحيح len);
فراغ ff_vector_fmul_add_avx(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                            ثابت عائم *src2, صحيح len);
فراغ ff_vector_fmul_add_fma3(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                             ثابت عائم *src2, صحيح len);

فراغ ff_vector_fmul_reverse_sse(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, صحيح len);
فراغ ff_vector_fmul_reverse_avx(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, صحيح len);
فراغ ff_vector_fmul_reverse_avx2(عائم *dst, ثابت عائم *src0,
                                 ثابت عائم *src1, صحيح len);

عائم ff_scalarproduct_float_sse(ثابت عائم *v1, ثابت عائم *v2, صحيح order);
عائم ff_scalarproduct_float_fma3(ثابت عائم *v1, ثابت عائم *v2, صحيح order);

مزدوج ff_scalarproduct_double_sse2(ثابت مزدوج *v1, ثابت مزدوج *v2, size_t order);
مزدوج ff_scalarproduct_double_avx(ثابت مزدوج *v1, ثابت مزدوج *v2, size_t order);

فراغ ff_butterflies_float_sse(عائم *restrict src0, عائم *restrict src1, صحيح len);

av_cold فراغ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    صحيح cpu_flags = av_get_cpu_flags();

    𐤀𐤌 (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    𐤀𐤌 (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    𐤀𐤌 (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    𐤀𐤌 (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    𐤀𐤌 (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
