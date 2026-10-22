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

ಸ್ಥಿರ ಶೂನ್ಯ vector_fmul_c(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                          ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_dmul_c(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src0, ಧ್ರುವ ದ್ವಿಗುಣ *src1,
                          ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_fmac_scalar_c(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                                 ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_dmac_scalar_c(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                 ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_fmul_scalar_c(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src, ಭಿನ್ನ mul,
                                 ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_dmul_scalar_c(ದ್ವಿಗುಣ *dst, ಧ್ರುವ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                 ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_fmul_window_c(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                 ಧ್ರುವ ಭಿನ್ನ *src1, ಧ್ರುವ ಭಿನ್ನ *win, ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i, j;

    dst  += len;
    win  += len;
    src0 += len;

    ಪ್ರತಿ (i = -len, j = len - 1; i < 0; i++, j--) {
        ಭಿನ್ನ s0 = src0[i];
        ಭಿನ್ನ s1 = src1[j];
        ಭಿನ್ನ wi = win[i];
        ಭಿನ್ನ wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_fmul_add_c(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                              ಧ್ರುವ ಭಿನ್ನ *src2, ಪೂರ್ಣಾಙ್ಕ len){
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ಸ್ಥಿರ ಶೂನ್ಯ vector_fmul_reverse_c(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                  ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    src1 += len-1;
    ಪ್ರತಿ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ಸ್ಥಿರ ಶೂನ್ಯ butterflies_float_c(ಭಿನ್ನ *restrict v1, ಭಿನ್ನ *restrict v2,
                                ಪೂರ್ಣಾಙ್ಕ len)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < len; i++) {
        ಭಿನ್ನ t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

ದ್ವಿಗುಣ ff_scalarproduct_double_c(ಧ್ರುವ ದ್ವಿಗುಣ *v1, ಧ್ರುವ ದ್ವಿಗುಣ *v2,
                                 size_t len)
{
    ದ್ವಿಗುಣ p = 0.0;

    ಪ್ರತಿ (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ಪ್ರತ್ಯಾಗಮ p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(ಪೂರ್ಣಾಙ್ಕ bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(ಪರಿಮಾಣ(AVFloatDSPContext));
    ಯದಿ (!fdsp)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    fdsp->vector_fmul = vector_fmul_c;
    fdsp->vector_dmul = vector_dmul_c;
    fdsp->vector_fmac_scalar = vector_fmac_scalar_c;
    fdsp->vector_fmul_scalar = vector_fmul_scalar_c;
    fdsp->vector_dmac_scalar = vector_dmac_scalar_c;
    fdsp->vector_dmul_scalar = vector_dmul_scalar_c;
    fdsp->vector_fmul_window = vector_fmul_window_c;
    fdsp->vector_fmul_add = vector_fmul_add_c;
    fdsp->vector_fmul_reverse = vector_fmul_reverse_c;
    fdsp->butterflies_float = butterflies_float_c;
    fdsp->scalarproduct_float = ff_scalarproduct_float_c;
    fdsp->scalarproduct_double = ff_scalarproduct_double_c;

#ಯದಿ ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#ನೋಚೇದ್ಯದಿ ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#ನೋಚೇದ್ಯದಿ ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#ನೋಚೇದ್ಯದಿ ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#ನೋಚೇದ್ಯದಿ ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    ಪ್ರತ್ಯಾಗಮ fdsp;
}
