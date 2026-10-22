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

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_sse(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                        ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_avx(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                        ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_dmul_sse2(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src0, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src1,
                         ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_dmul_avx(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src0, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src1,
                        ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmac_scalar_sse(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                               ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmac_scalar_avx(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                               ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmac_scalar_fma3(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_scalar_sse(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                               ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_dmac_scalar_sse2(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_dmac_scalar_avx(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                               ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_dmac_scalar_fma3(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_dmul_scalar_sse2(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src,
                                ದ್ವಿಗುಣ mul, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_dmul_scalar_avx(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src,
                               ದ್ವಿಗುಣ mul, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_sse(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                               ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *win, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_sse(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_avx(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_fma3(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                             ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_sse(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_avx(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_avx2(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                 ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);

ದಶಮಾಂಶ ff_scalarproduct_float_sse(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ ಕ್ರಮ);
ದಶಮಾಂಶ ff_scalarproduct_float_fma3(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ ಕ್ರಮ);

ದ್ವಿಗುಣ ff_scalarproduct_double_sse2(ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v1, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v2, size_t ಕ್ರಮ);
ದ್ವಿಗುಣ ff_scalarproduct_double_avx(ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v1, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v2, size_t ಕ್ರಮ);

ಶೂನ್ಯ ff_butterflies_float_sse(ದಶಮಾಂಶ *ಸೀಮಿತ src0, ದಶಮಾಂಶ *ಸೀಮಿತ src1, ಪೂರ್ಣಾಂಕ len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();

    ಆದರೆ (EXTERNAL_SSE(cpu_flags)) {
        fdsp->ಸದಿಶ_fmul = ff_ಸದಿಶ_fmul_sse;
        fdsp->ಸದಿಶ_fmac_scalar = ff_ಸದಿಶ_fmac_scalar_sse;
        fdsp->ಸದಿಶ_fmul_scalar = ff_ಸದಿಶ_fmul_scalar_sse;
        fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ = ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_sse;
        fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು    = ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_sse;
        fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    ಆದರೆ (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->ಸದಿಶ_dmul = ff_ಸದಿಶ_dmul_sse2;
        fdsp->ಸದಿಶ_dmac_scalar = ff_ಸದಿಶ_dmac_scalar_sse2;
        fdsp->ಸದಿಶ_dmul_scalar = ff_ಸದಿಶ_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    ಆದರೆ (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->ಸದಿಶ_fmul = ff_ಸದಿಶ_fmul_avx;
        fdsp->ಸದಿಶ_dmul = ff_ಸದಿಶ_dmul_avx;
        fdsp->ಸದಿಶ_fmac_scalar = ff_ಸದಿಶ_fmac_scalar_avx;
        fdsp->ಸದಿಶ_dmul_scalar = ff_ಸದಿಶ_dmul_scalar_avx;
        fdsp->ಸದಿಶ_dmac_scalar = ff_ಸದಿಶ_dmac_scalar_avx;
        fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು    = ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_avx;
        fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    ಆದರೆ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_avx2;
    }
    ಆದರೆ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->ಸದಿಶ_fmac_scalar = ff_ಸದಿಶ_fmac_scalar_fma3;
        fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು    = ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_fma3;
        fdsp->ಸದಿಶ_dmac_scalar = ff_ಸದಿಶ_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
