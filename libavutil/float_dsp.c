/*
 * Copyright 2005 Balatoni Denes
 * Copyright 2006 Loren Merritt
 *
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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "float_dsp.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_fmul_c(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                          ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_dmul_c(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src0, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src1,
                          ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_fmac_scalar_c(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                 ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_dmac_scalar_c(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                 ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_fmul_scalar_c(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                 ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_dmul_scalar_c(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                 ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_fmul_ಕಿಟಕಿ_c(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                 ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *win, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i, j;

    dst  += len;
    win  += len;
    src0 += len;

    ಗಾಗಿ (i = -len, j = len - 1; i < 0; i++, j--) {
        ದಶಮಾಂಶ s0 = src0[i];
        ದಶಮಾಂಶ s1 = src1[j];
        ದಶಮಾಂಶ wi = win[i];
        ದಶಮಾಂಶ wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_fmul_ಕೂಡಿಸು_c(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                              ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len){
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ಸ್ಥಿರ ಶೂನ್ಯ ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_c(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                  ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;

    src1 += len-1;
    ಗಾಗಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ಸ್ಥಿರ ಶೂನ್ಯ butterflies_float_c(ದಶಮಾಂಶ *ಸೀಮಿತ v1, ದಶಮಾಂಶ *ಸೀಮಿತ v2,
                                ಪೂರ್ಣಾಂಕ len)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < len; i++) {
        ದಶಮಾಂಶ t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

ದ್ವಿಗುಣ ff_scalarproduct_double_c(ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v1, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v2,
                                 size_t len)
{
    ದ್ವಿಗುಣ p = 0.0;

    ಗಾಗಿ (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ಹಿಂತಿರುಗಿ p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(ಪೂರ್ಣಾಂಕ ಬಿಟ್_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(ಗಾತ್ರ(AVFloatDSPContext));
    ಆದರೆ (!fdsp)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    fdsp->ಸದಿಶ_fmul = ಸದಿಶ_fmul_c;
    fdsp->ಸದಿಶ_dmul = ಸದಿಶ_dmul_c;
    fdsp->ಸದಿಶ_fmac_scalar = ಸದಿಶ_fmac_scalar_c;
    fdsp->ಸದಿಶ_fmul_scalar = ಸದಿಶ_fmul_scalar_c;
    fdsp->ಸದಿಶ_dmac_scalar = ಸದಿಶ_dmac_scalar_c;
    fdsp->ಸದಿಶ_dmul_scalar = ಸದಿಶ_dmul_scalar_c;
    fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ = ಸದಿಶ_fmul_ಕಿಟಕಿ_c;
    fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು = ಸದಿಶ_fmul_ಕೂಡಿಸು_c;
    fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_c;
    fdsp->butterflies_float = butterflies_float_c;
    fdsp->scalarproduct_float = ff_scalarproduct_float_c;
    fdsp->scalarproduct_double = ff_scalarproduct_double_c;

#ಆದರೆ ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#ಅಥವಾಆದರೆ ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#ಅಥವಾಆದರೆ ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, ಬಿಟ್_exact);
#ಅಥವಾಆದರೆ ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#ಅಥವಾಆದರೆ ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#ಅಥವಾಆದರೆ ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ fdsp;
}
