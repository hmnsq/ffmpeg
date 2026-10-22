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

#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/float_dsp.h"
#अन्तर्भाव "cpu.h"

शून्य ff_vector_fmul_sse(भिन्न *dst, अचर भिन्न *src0, अचर भिन्न *src1,
                        पूर्णाङ्क len);
शून्य ff_vector_fmul_avx(भिन्न *dst, अचर भिन्न *src0, अचर भिन्न *src1,
                        पूर्णाङ्क len);

शून्य ff_vector_dmul_sse2(द्विगुण *dst, अचर द्विगुण *src0, अचर द्विगुण *src1,
                         पूर्णाङ्क len);
शून्य ff_vector_dmul_avx(द्विगुण *dst, अचर द्विगुण *src0, अचर द्विगुण *src1,
                        पूर्णाङ्क len);

शून्य ff_vector_fmac_scalar_sse(भिन्न *dst, अचर भिन्न *src, भिन्न mul,
                               पूर्णाङ्क len);
शून्य ff_vector_fmac_scalar_avx(भिन्न *dst, अचर भिन्न *src, भिन्न mul,
                               पूर्णाङ्क len);
शून्य ff_vector_fmac_scalar_fma3(भिन्न *dst, अचर भिन्न *src, भिन्न mul,
                                पूर्णाङ्क len);

शून्य ff_vector_fmul_scalar_sse(भिन्न *dst, अचर भिन्न *src, भिन्न mul,
                               पूर्णाङ्क len);

शून्य ff_vector_dmac_scalar_sse2(द्विगुण *dst, अचर द्विगुण *src, द्विगुण mul,
                                पूर्णाङ्क len);
शून्य ff_vector_dmac_scalar_avx(द्विगुण *dst, अचर द्विगुण *src, द्विगुण mul,
                               पूर्णाङ्क len);
शून्य ff_vector_dmac_scalar_fma3(द्विगुण *dst, अचर द्विगुण *src, द्विगुण mul,
                                पूर्णाङ्क len);

शून्य ff_vector_dmul_scalar_sse2(द्विगुण *dst, अचर द्विगुण *src,
                                द्विगुण mul, पूर्णाङ्क len);
शून्य ff_vector_dmul_scalar_avx(द्विगुण *dst, अचर द्विगुण *src,
                               द्विगुण mul, पूर्णाङ्क len);

शून्य ff_vector_fmul_window_sse(भिन्न *dst, अचर भिन्न *src0,
                               अचर भिन्न *src1, अचर भिन्न *win, पूर्णाङ्क len);

शून्य ff_vector_fmul_add_sse(भिन्न *dst, अचर भिन्न *src0, अचर भिन्न *src1,
                            अचर भिन्न *src2, पूर्णाङ्क len);
शून्य ff_vector_fmul_add_avx(भिन्न *dst, अचर भिन्न *src0, अचर भिन्न *src1,
                            अचर भिन्न *src2, पूर्णाङ्क len);
शून्य ff_vector_fmul_add_fma3(भिन्न *dst, अचर भिन्न *src0, अचर भिन्न *src1,
                             अचर भिन्न *src2, पूर्णाङ्क len);

शून्य ff_vector_fmul_reverse_sse(भिन्न *dst, अचर भिन्न *src0,
                                अचर भिन्न *src1, पूर्णाङ्क len);
शून्य ff_vector_fmul_reverse_avx(भिन्न *dst, अचर भिन्न *src0,
                                अचर भिन्न *src1, पूर्णाङ्क len);
शून्य ff_vector_fmul_reverse_avx2(भिन्न *dst, अचर भिन्न *src0,
                                 अचर भिन्न *src1, पूर्णाङ्क len);

भिन्न ff_scalarproduct_float_sse(अचर भिन्न *v1, अचर भिन्न *v2, पूर्णाङ्क order);
भिन्न ff_scalarproduct_float_fma3(अचर भिन्न *v1, अचर भिन्न *v2, पूर्णाङ्क order);

द्विगुण ff_scalarproduct_double_sse2(अचर द्विगुण *v1, अचर द्विगुण *v2, माप_प्रकार order);
द्विगुण ff_scalarproduct_double_avx(अचर द्विगुण *v1, अचर द्विगुण *v2, माप_प्रकार order);

शून्य ff_butterflies_float_sse(भिन्न *restrict src0, भिन्न *restrict src1, पूर्णाङ्क len);

av_cold शून्य ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    पूर्णाङ्क cpu_flags = av_get_cpu_flags();

    यदि (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    यदि (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    यदि (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    यदि (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    यदि (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
