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

#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/float_dsp.h"
#ଅନ୍ତର୍ଭାଵ "cpu.h"

ଶୂନ୍ୟ ff_vector_fmul_sse(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_avx(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_dmul_sse2(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src0, ଅଚଳ ଦ୍ୱିଗୁଣ *src1,
                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_dmul_avx(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src0, ଅଚଳ ଦ୍ୱିଗୁଣ *src1,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmac_scalar_sse(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmac_scalar_avx(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmac_scalar_fma3(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_scalar_sse(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_dmac_scalar_sse2(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_dmac_scalar_avx(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_dmac_scalar_fma3(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_dmul_scalar_sse2(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src,
                                ଦ୍ୱିଗୁଣ mul, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_dmul_scalar_avx(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src,
                               ଦ୍ୱିଗୁଣ mul, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_window_sse(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                               ଅଚଳ ଦଶମିକ *src1, ଅଚଳ ଦଶମିକ *win, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_add_sse(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                            ଅଚଳ ଦଶମିକ *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_add_avx(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                            ଅଚଳ ଦଶମିକ *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_add_fma3(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                             ଅଚଳ ଦଶମିକ *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_reverse_sse(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_reverse_avx(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_reverse_avx2(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                 ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଦଶମିକ ff_scalarproduct_float_sse(ଅଚଳ ଦଶମିକ *v1, ଅଚଳ ଦଶମିକ *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା order);
ଦଶମିକ ff_scalarproduct_float_fma3(ଅଚଳ ଦଶମିକ *v1, ଅଚଳ ଦଶମିକ *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା order);

ଦ୍ୱିଗୁଣ ff_scalarproduct_double_sse2(ଅଚଳ ଦ୍ୱିଗୁଣ *v1, ଅଚଳ ଦ୍ୱିଗୁଣ *v2, size_t order);
ଦ୍ୱିଗୁଣ ff_scalarproduct_double_avx(ଅଚଳ ଦ୍ୱିଗୁଣ *v1, ଅଚଳ ଦ୍ୱିଗୁଣ *v2, size_t order);

ଶୂନ୍ୟ ff_butterflies_float_sse(ଦଶମିକ *restrict src0, ଦଶମିକ *restrict src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

av_cold ଶୂନ୍ୟ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags = av_get_cpu_flags();

    ଯଦି (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    ଯଦି (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    ଯଦି (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    ଯଦି (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    ଯଦି (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
