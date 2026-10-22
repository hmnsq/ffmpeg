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

#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/float_dsp.h"
#شامل "cpu.h"

تهی ff_vector_fmul_sse(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                        صحیح len);
تهی ff_vector_fmul_avx(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                        صحیح len);

تهی ff_vector_dmul_sse2(دوگانه *dst, ثابت دوگانه *src0, ثابت دوگانه *src1,
                         صحیح len);
تهی ff_vector_dmul_avx(دوگانه *dst, ثابت دوگانه *src0, ثابت دوگانه *src1,
                        صحیح len);

تهی ff_vector_fmac_scalar_sse(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                               صحیح len);
تهی ff_vector_fmac_scalar_avx(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                               صحیح len);
تهی ff_vector_fmac_scalar_fma3(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);

تهی ff_vector_fmul_scalar_sse(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                               صحیح len);

تهی ff_vector_dmac_scalar_sse2(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                                صحیح len);
تهی ff_vector_dmac_scalar_avx(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                               صحیح len);
تهی ff_vector_dmac_scalar_fma3(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                                صحیح len);

تهی ff_vector_dmul_scalar_sse2(دوگانه *dst, ثابت دوگانه *src,
                                دوگانه mul, صحیح len);
تهی ff_vector_dmul_scalar_avx(دوگانه *dst, ثابت دوگانه *src,
                               دوگانه mul, صحیح len);

تهی ff_vector_fmul_window_sse(اعشاری *dst, ثابت اعشاری *src0,
                               ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);

تهی ff_vector_fmul_add_sse(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                            ثابت اعشاری *src2, صحیح len);
تهی ff_vector_fmul_add_avx(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                            ثابت اعشاری *src2, صحیح len);
تهی ff_vector_fmul_add_fma3(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                             ثابت اعشاری *src2, صحیح len);

تهی ff_vector_fmul_reverse_sse(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);
تهی ff_vector_fmul_reverse_avx(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);
تهی ff_vector_fmul_reverse_avx2(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, صحیح len);

اعشاری ff_scalarproduct_float_sse(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح order);
اعشاری ff_scalarproduct_float_fma3(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح order);

دوگانه ff_scalarproduct_double_sse2(ثابت دوگانه *v1, ثابت دوگانه *v2, size_t order);
دوگانه ff_scalarproduct_double_avx(ثابت دوگانه *v1, ثابت دوگانه *v2, size_t order);

تهی ff_butterflies_float_sse(اعشاری *restrict src0, اعشاری *restrict src1, صحیح len);

av_cold تهی ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    صحیح cpu_flags = av_get_cpu_flags();

    اگر (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    اگر (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    اگر (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    اگر (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    اگر (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
