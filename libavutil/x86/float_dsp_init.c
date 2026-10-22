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

#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/float_dsp.h"
#ಅನ್ತರ್ಭಾವ "cpu.h"

ಶೂನ್ಯ ff_vector_fmul_sse(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                        ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_avx(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                        ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_dmul_sse2(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src0, ಧ್ರುವ ದ್ವಿಗುಣ *src1,
                         ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_dmul_avx(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src0, ಧ್ರುವ ದ್ವಿಗುಣ *src1,
                        ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmac_scalar_sse(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmac_scalar_avx(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmac_scalar_fma3(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmul_scalar_sse(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_dmac_scalar_sse2(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_dmac_scalar_avx(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                               ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_dmac_scalar_fma3(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_dmul_scalar_sse2(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src,
                                ದ್ವಿಗುಣ mul, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_dmul_scalar_avx(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src,
                               ದ್ವಿಗುಣ mul, ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmul_window_sse(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                               ಧ್ರುವ ಭಿನ್ನ *src1, ಧ್ರುವ ಭಿನ್ನ *win, ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmul_add_sse(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                            ಧ್ರುವ ಭಿನ್ನ *src2, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_add_avx(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                            ಧ್ರುವ ಭಿನ್ನ *src2, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_add_fma3(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                             ಧ್ರುವ ಭಿನ್ನ *src2, ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmul_reverse_sse(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_reverse_avx(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_reverse_avx2(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                 ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len);

ಭಿನ್ನ ff_scalarproduct_float_sse(ಧ್ರುವ ಭಿನ್ನ *v1, ಧ್ರುವ ಭಿನ್ನ *v2, ಪೂರ್ಣಾಙ್ಕ order);
ಭಿನ್ನ ff_scalarproduct_float_fma3(ಧ್ರುವ ಭಿನ್ನ *v1, ಧ್ರುವ ಭಿನ್ನ *v2, ಪೂರ್ಣಾಙ್ಕ order);

ದ್ವಿಗುಣ ff_scalarproduct_double_sse2(ಧ್ರುವ ದ್ವಿಗುಣ *v1, ಧ್ರುವ ದ್ವಿಗುಣ *v2, size_t order);
ದ್ವಿಗುಣ ff_scalarproduct_double_avx(ಧ್ರುವ ದ್ವಿಗುಣ *v1, ಧ್ರುವ ದ್ವಿಗುಣ *v2, size_t order);

ಶೂನ್ಯ ff_butterflies_float_sse(ಭಿನ್ನ *restrict src0, ಭಿನ್ನ *restrict src1, ಪೂರ್ಣಾಙ್ಕ len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();

    ಯದಿ (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    ಯದಿ (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    ಯದಿ (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    ಯದಿ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    ಯದಿ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
