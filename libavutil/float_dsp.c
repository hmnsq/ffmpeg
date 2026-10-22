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

#ضمن "config.h"
#ضمن "attributes.h"
#ضمن "float_dsp.h"
#ضمن "mem.h"

ساكن فراغ vector_fmul_c(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                          صحيح len)
{
    صحيح i;
    עבור (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ساكن فراغ vector_dmul_c(مزدوج *dst, ثابت مزدوج *src0, ثابت مزدوج *src1,
                          صحيح len)
{
    صحيح i;
    עבור (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ساكن فراغ vector_fmac_scalar_c(عائم *dst, ثابت عائم *src, عائم mul,
                                 صحيح len)
{
    صحيح i;
    עבור (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ساكن فراغ vector_dmac_scalar_c(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                 صحيح len)
{
    صحيح i;
    עבור (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ساكن فراغ vector_fmul_scalar_c(عائم *dst, ثابت عائم *src, عائم mul,
                                 صحيح len)
{
    صحيح i;
    עבור (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ساكن فراغ vector_dmul_scalar_c(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                 صحيح len)
{
    صحيح i;
    עבור (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ساكن فراغ vector_fmul_window_c(عائم *dst, ثابت عائم *src0,
                                 ثابت عائم *src1, ثابت عائم *win, صحيح len)
{
    صحيح i, j;

    dst  += len;
    win  += len;
    src0 += len;

    עבור (i = -len, j = len - 1; i < 0; i++, j--) {
        عائم s0 = src0[i];
        عائم s1 = src1[j];
        عائم wi = win[i];
        عائم wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ساكن فراغ vector_fmul_add_c(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                              ثابت عائم *src2, صحيح len){
    صحيح i;

    עבור (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ساكن فراغ vector_fmul_reverse_c(عائم *dst, ثابت عائم *src0,
                                  ثابت عائم *src1, صحيح len)
{
    صحيح i;

    src1 += len-1;
    עבור (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ساكن فراغ butterflies_float_c(عائم *restrict v1, عائم *restrict v2,
                                صحيح len)
{
    صحيح i;

    עבור (i = 0; i < len; i++) {
        عائم t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

مزدوج ff_scalarproduct_double_c(ثابت مزدوج *v1, ثابت مزدوج *v2,
                                 size_t len)
{
    مزدوج p = 0.0;

    עבור (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    החזר p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(صحيح bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(حجم(AVFloatDSPContext));
    אם (!fdsp)
        החזר عدم;

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

#אם ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#وإلاإذا ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#وإلاإذا ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#وإلاإذا ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#وإلاإذا ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#وإلاإذا ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    החזר fdsp;
}
