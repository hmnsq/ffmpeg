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

#شامل "config.h"
#شامل "attributes.h"
#شامل "float_dsp.h"
#شامل "mem.h"

ایستا تهی vector_fmul_c(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                          صحیح len)
{
    صحیح i;
    برای (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ایستا تهی vector_dmul_c(دوگانه *dst, ثابت دوگانه *src0, ثابت دوگانه *src1,
                          صحیح len)
{
    صحیح i;
    برای (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ایستا تهی vector_fmac_scalar_c(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                 صحیح len)
{
    صحیح i;
    برای (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ایستا تهی vector_dmac_scalar_c(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                                 صحیح len)
{
    صحیح i;
    برای (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ایستا تهی vector_fmul_scalar_c(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                 صحیح len)
{
    صحیح i;
    برای (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ایستا تهی vector_dmul_scalar_c(دوگانه *dst, ثابت دوگانه *src, دوگانه mul,
                                 صحیح len)
{
    صحیح i;
    برای (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ایستا تهی vector_fmul_window_c(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len)
{
    صحیح i, j;

    dst  += len;
    win  += len;
    src0 += len;

    برای (i = -len, j = len - 1; i < 0; i++, j--) {
        اعشاری s0 = src0[i];
        اعشاری s1 = src1[j];
        اعشاری wi = win[i];
        اعشاری wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ایستا تهی vector_fmul_add_c(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                              ثابت اعشاری *src2, صحیح len){
    صحیح i;

    برای (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ایستا تهی vector_fmul_reverse_c(اعشاری *dst, ثابت اعشاری *src0,
                                  ثابت اعشاری *src1, صحیح len)
{
    صحیح i;

    src1 += len-1;
    برای (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ایستا تهی butterflies_float_c(اعشاری *restrict v1, اعشاری *restrict v2,
                                صحیح len)
{
    صحیح i;

    برای (i = 0; i < len; i++) {
        اعشاری t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

دوگانه ff_scalarproduct_double_c(ثابت دوگانه *v1, ثابت دوگانه *v2,
                                 size_t len)
{
    دوگانه p = 0.0;

    برای (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    بازگشت p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(صحیح bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(اندازه(AVFloatDSPContext));
    اگر (!fdsp)
        بازگشت پوچ;

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

#اگر ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#وگرنهاگر ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#وگرنهاگر ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#وگرنهاگر ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#وگرنهاگر ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#وگرنهاگر ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    بازگشت fdsp;
}
