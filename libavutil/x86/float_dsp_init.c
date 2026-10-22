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

शून्य ff_सदिशम्_fmul_sse(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                        पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_avx(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                        पूर्णाङ्क len);

शून्य ff_सदिशम्_dmul_sse2(द्विगुण *dst, ध्रुव द्विगुण *src0, ध्रुव द्विगुण *src1,
                         पूर्णाङ्क len);
शून्य ff_सदिशम्_dmul_avx(द्विगुण *dst, ध्रुव द्विगुण *src0, ध्रुव द्विगुण *src1,
                        पूर्णाङ्क len);

शून्य ff_सदिशम्_fmac_scalar_sse(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                               पूर्णाङ्क len);
शून्य ff_सदिशम्_fmac_scalar_avx(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                               पूर्णाङ्क len);
शून्य ff_सदिशम्_fmac_scalar_fma3(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                                पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_scalar_sse(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                               पूर्णाङ्क len);

शून्य ff_सदिशम्_dmac_scalar_sse2(द्विगुण *dst, ध्रुव द्विगुण *src, द्विगुण mul,
                                पूर्णाङ्क len);
शून्य ff_सदिशम्_dmac_scalar_avx(द्विगुण *dst, ध्रुव द्विगुण *src, द्विगुण mul,
                               पूर्णाङ्क len);
शून्य ff_सदिशम्_dmac_scalar_fma3(द्विगुण *dst, ध्रुव द्विगुण *src, द्विगुण mul,
                                पूर्णाङ्क len);

शून्य ff_सदिशम्_dmul_scalar_sse2(द्विगुण *dst, ध्रुव द्विगुण *src,
                                द्विगुण mul, पूर्णाङ्क len);
शून्य ff_सदिशम्_dmul_scalar_avx(द्विगुण *dst, ध्रुव द्विगुण *src,
                               द्विगुण mul, पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_गवाक्षः_sse(भिन्न *dst, ध्रुव भिन्न *src0,
                               ध्रुव भिन्न *src1, ध्रुव भिन्न *win, पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_सङ्कलय_sse(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                            ध्रुव भिन्न *src2, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_सङ्कलय_avx(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                            ध्रुव भिन्न *src2, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_सङ्कलय_fma3(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                             ध्रुव भिन्न *src2, पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_reverse_sse(भिन्न *dst, ध्रुव भिन्न *src0,
                                ध्रुव भिन्न *src1, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_reverse_avx(भिन्न *dst, ध्रुव भिन्न *src0,
                                ध्रुव भिन्न *src1, पूर्णाङ्क len);
शून्य ff_सदिशम्_fmul_reverse_avx2(भिन्न *dst, ध्रुव भिन्न *src0,
                                 ध्रुव भिन्न *src1, पूर्णाङ्क len);

भिन्न ff_scalarproduct_float_sse(ध्रुव भिन्न *v1, ध्रुव भिन्न *v2, पूर्णाङ्क क्रमः);
भिन्न ff_scalarproduct_float_fma3(ध्रुव भिन्न *v1, ध्रुव भिन्न *v2, पूर्णाङ्क क्रमः);

द्विगुण ff_scalarproduct_double_sse2(ध्रुव द्विगुण *v1, ध्रुव द्विगुण *v2, size_t क्रमः);
द्विगुण ff_scalarproduct_double_avx(ध्रुव द्विगुण *v1, ध्रुव द्विगुण *v2, size_t क्रमः);

शून्य ff_butterflies_float_sse(भिन्न *सीमित src0, भिन्न *सीमित src1, पूर्णाङ्क len);

av_cold शून्य ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    पूर्णाङ्क cpu_flags = av_get_cpu_flags();

    यदि (EXTERNAL_SSE(cpu_flags)) {
        fdsp->सदिशम्_fmul = ff_सदिशम्_fmul_sse;
        fdsp->सदिशम्_fmac_scalar = ff_सदिशम्_fmac_scalar_sse;
        fdsp->सदिशम्_fmul_scalar = ff_सदिशम्_fmul_scalar_sse;
        fdsp->सदिशम्_fmul_गवाक्षः = ff_सदिशम्_fmul_गवाक्षः_sse;
        fdsp->सदिशम्_fmul_सङ्कलय    = ff_सदिशम्_fmul_सङ्कलय_sse;
        fdsp->सदिशम्_fmul_reverse = ff_सदिशम्_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    यदि (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->सदिशम्_dmul = ff_सदिशम्_dmul_sse2;
        fdsp->सदिशम्_dmac_scalar = ff_सदिशम्_dmac_scalar_sse2;
        fdsp->सदिशम्_dmul_scalar = ff_सदिशम्_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    यदि (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->सदिशम्_fmul = ff_सदिशम्_fmul_avx;
        fdsp->सदिशम्_dmul = ff_सदिशम्_dmul_avx;
        fdsp->सदिशम्_fmac_scalar = ff_सदिशम्_fmac_scalar_avx;
        fdsp->सदिशम्_dmul_scalar = ff_सदिशम्_dmul_scalar_avx;
        fdsp->सदिशम्_dmac_scalar = ff_सदिशम्_dmac_scalar_avx;
        fdsp->सदिशम्_fmul_सङ्कलय    = ff_सदिशम्_fmul_सङ्कलय_avx;
        fdsp->सदिशम्_fmul_reverse = ff_सदिशम्_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    यदि (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->सदिशम्_fmul_reverse = ff_सदिशम्_fmul_reverse_avx2;
    }
    यदि (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->सदिशम्_fmac_scalar = ff_सदिशम्_fmac_scalar_fma3;
        fdsp->सदिशम्_fmul_सङ्कलय    = ff_सदिशम्_fmul_सङ्कलय_fma3;
        fdsp->सदिशम्_dmac_scalar = ff_सदिशम्_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
