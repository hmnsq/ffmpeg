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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "float_dsp.h"
#অন্তর্ভাব "mem.h"

স্থির শূন্য vector_fmul_c(দশমিক *dst, ধ্রুবক দশমিক *src0, ধ্রুবক দশমিক *src1,
                          পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

স্থির শূন্য vector_dmul_c(দ্বিগুণ *dst, ধ্রুবক দ্বিগুণ *src0, ধ্রুবক দ্বিগুণ *src1,
                          পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

স্থির শূন্য vector_fmac_scalar_c(দশমিক *dst, ধ্রুবক দশমিক *src, দশমিক mul,
                                 পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

স্থির শূন্য vector_dmac_scalar_c(দ্বিগুণ *dst, ধ্রুবক দ্বিগুণ *src, দ্বিগুণ mul,
                                 পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

স্থির শূন্য vector_fmul_scalar_c(দশমিক *dst, ধ্রুবক দশমিক *src, দশমিক mul,
                                 পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

স্থির শূন্য vector_dmul_scalar_c(দ্বিগুণ *dst, ধ্রুবক দ্বিগুণ *src, দ্বিগুণ mul,
                                 পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

স্থির শূন্য vector_fmul_window_c(দশমিক *dst, ধ্রুবক দশমিক *src0,
                                 ধ্রুবক দশমিক *src1, ধ্রুবক দশমিক *win, পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i, j;

    dst  += len;
    win  += len;
    src0 += len;

    জন্য (i = -len, j = len - 1; i < 0; i++, j--) {
        দশমিক s0 = src0[i];
        দশমিক s1 = src1[j];
        দশমিক wi = win[i];
        দশমিক wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

স্থির শূন্য vector_fmul_add_c(দশমিক *dst, ধ্রুবক দশমিক *src0, ধ্রুবক দশমিক *src1,
                              ধ্রুবক দশমিক *src2, পূর্ণসংখ্যা len){
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

স্থির শূন্য vector_fmul_reverse_c(দশমিক *dst, ধ্রুবক দশমিক *src0,
                                  ধ্রুবক দশমিক *src1, পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;

    src1 += len-1;
    জন্য (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

স্থির শূন্য butterflies_float_c(দশমিক *restrict v1, দশমিক *restrict v2,
                                পূর্ণসংখ্যা len)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < len; i++) {
        দশমিক t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

দ্বিগুণ ff_scalarproduct_double_c(ধ্রুবক দ্বিগুণ *v1, ধ্রুবক দ্বিগুণ *v2,
                                 size_t len)
{
    দ্বিগুণ p = 0.0;

    জন্য (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ফেরত p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(পূর্ণসংখ্যা bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(আকার(AVFloatDSPContext));
    যদি (!fdsp)
        ফেরত ফাঁকা;

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

#যদি ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#নতুবা_যদি ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#নতুবা_যদি ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#নতুবা_যদি ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#নতুবা_যদি ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#নতুবা_যদি ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    ফেরত fdsp;
}
