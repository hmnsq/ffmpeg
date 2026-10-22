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

#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/float_dsp.h"
#அந்தர்பாவ "cpu.h"

வெறுமை ff_vector_fmul_sse(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                        முழு len);
வெறுமை ff_vector_fmul_avx(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                        முழு len);

வெறுமை ff_vector_dmul_sse2(இரட்டை *dst, மாறிலி இரட்டை *src0, மாறிலி இரட்டை *src1,
                         முழு len);
வெறுமை ff_vector_dmul_avx(இரட்டை *dst, மாறிலி இரட்டை *src0, மாறிலி இரட்டை *src1,
                        முழு len);

வெறுமை ff_vector_fmac_scalar_sse(தசம *dst, மாறிலி தசம *src, தசம mul,
                               முழு len);
வெறுமை ff_vector_fmac_scalar_avx(தசம *dst, மாறிலி தசம *src, தசம mul,
                               முழு len);
வெறுமை ff_vector_fmac_scalar_fma3(தசம *dst, மாறிலி தசம *src, தசம mul,
                                முழு len);

வெறுமை ff_vector_fmul_scalar_sse(தசம *dst, மாறிலி தசம *src, தசம mul,
                               முழு len);

வெறுமை ff_vector_dmac_scalar_sse2(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                முழு len);
வெறுமை ff_vector_dmac_scalar_avx(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                               முழு len);
வெறுமை ff_vector_dmac_scalar_fma3(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                முழு len);

வெறுமை ff_vector_dmul_scalar_sse2(இரட்டை *dst, மாறிலி இரட்டை *src,
                                இரட்டை mul, முழு len);
வெறுமை ff_vector_dmul_scalar_avx(இரட்டை *dst, மாறிலி இரட்டை *src,
                               இரட்டை mul, முழு len);

வெறுமை ff_vector_fmul_window_sse(தசம *dst, மாறிலி தசம *src0,
                               மாறிலி தசம *src1, மாறிலி தசம *win, முழு len);

வெறுமை ff_vector_fmul_add_sse(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                            மாறிலி தசம *src2, முழு len);
வெறுமை ff_vector_fmul_add_avx(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                            மாறிலி தசம *src2, முழு len);
வெறுமை ff_vector_fmul_add_fma3(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                             மாறிலி தசம *src2, முழு len);

வெறுமை ff_vector_fmul_reverse_sse(தசம *dst, மாறிலி தசம *src0,
                                மாறிலி தசம *src1, முழு len);
வெறுமை ff_vector_fmul_reverse_avx(தசம *dst, மாறிலி தசம *src0,
                                மாறிலி தசம *src1, முழு len);
வெறுமை ff_vector_fmul_reverse_avx2(தசம *dst, மாறிலி தசம *src0,
                                 மாறிலி தசம *src1, முழு len);

தசம ff_scalarproduct_float_sse(மாறிலி தசம *v1, மாறிலி தசம *v2, முழு order);
தசம ff_scalarproduct_float_fma3(மாறிலி தசம *v1, மாறிலி தசம *v2, முழு order);

இரட்டை ff_scalarproduct_double_sse2(மாறிலி இரட்டை *v1, மாறிலி இரட்டை *v2, size_t order);
இரட்டை ff_scalarproduct_double_avx(மாறிலி இரட்டை *v1, மாறிலி இரட்டை *v2, size_t order);

வெறுமை ff_butterflies_float_sse(தசம *restrict src0, தசம *restrict src1, முழு len);

av_cold வெறுமை ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    முழு cpu_flags = av_get_cpu_flags();

    எனில் (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    எனில் (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    எனில் (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    எனில் (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    எனில் (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
