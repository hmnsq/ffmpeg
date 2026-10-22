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

#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/float_dsp.h"
#समावेश "cpu.h"

व्योम ff_vector_fmul_sse(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                        पूर्णांक len);
व्योम ff_vector_fmul_avx(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                        पूर्णांक len);

व्योम ff_vector_dmul_sse2(द्विगुन *dst, स्थिर द्विगुन *src0, स्थिर द्विगुन *src1,
                         पूर्णांक len);
व्योम ff_vector_dmul_avx(द्विगुन *dst, स्थिर द्विगुन *src0, स्थिर द्विगुन *src1,
                        पूर्णांक len);

व्योम ff_vector_fmac_scalar_sse(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                               पूर्णांक len);
व्योम ff_vector_fmac_scalar_avx(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                               पूर्णांक len);
व्योम ff_vector_fmac_scalar_fma3(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                पूर्णांक len);

व्योम ff_vector_fmul_scalar_sse(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                               पूर्णांक len);

व्योम ff_vector_dmac_scalar_sse2(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                पूर्णांक len);
व्योम ff_vector_dmac_scalar_avx(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                               पूर्णांक len);
व्योम ff_vector_dmac_scalar_fma3(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                पूर्णांक len);

व्योम ff_vector_dmul_scalar_sse2(द्विगुन *dst, स्थिर द्विगुन *src,
                                द्विगुन mul, पूर्णांक len);
व्योम ff_vector_dmul_scalar_avx(द्विगुन *dst, स्थिर द्विगुन *src,
                               द्विगुन mul, पूर्णांक len);

व्योम ff_vector_fmul_window_sse(भग्न *dst, स्थिर भग्न *src0,
                               स्थिर भग्न *src1, स्थिर भग्न *win, पूर्णांक len);

व्योम ff_vector_fmul_add_sse(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                            स्थिर भग्न *src2, पूर्णांक len);
व्योम ff_vector_fmul_add_avx(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                            स्थिर भग्न *src2, पूर्णांक len);
व्योम ff_vector_fmul_add_fma3(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                             स्थिर भग्न *src2, पूर्णांक len);

व्योम ff_vector_fmul_reverse_sse(भग्न *dst, स्थिर भग्न *src0,
                                स्थिर भग्न *src1, पूर्णांक len);
व्योम ff_vector_fmul_reverse_avx(भग्न *dst, स्थिर भग्न *src0,
                                स्थिर भग्न *src1, पूर्णांक len);
व्योम ff_vector_fmul_reverse_avx2(भग्न *dst, स्थिर भग्न *src0,
                                 स्थिर भग्न *src1, पूर्णांक len);

भग्न ff_scalarproduct_float_sse(स्थिर भग्न *v1, स्थिर भग्न *v2, पूर्णांक order);
भग्न ff_scalarproduct_float_fma3(स्थिर भग्न *v1, स्थिर भग्न *v2, पूर्णांक order);

द्विगुन ff_scalarproduct_double_sse2(स्थिर द्विगुन *v1, स्थिर द्विगुन *v2, माप_प्रकार order);
द्विगुन ff_scalarproduct_double_avx(स्थिर द्विगुन *v1, स्थिर द्विगुन *v2, माप_प्रकार order);

व्योम ff_butterflies_float_sse(भग्न *restrict src0, भग्न *restrict src1, पूर्णांक len);

av_cold व्योम ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();

    अगर (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    अगर (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    अगर (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    अगर (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    अगर (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
