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

ساکن خالی سمتیہ_fmul_c(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                          صحیح len)
{
    صحیح i;
    برائے (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ساکن خالی سمتیہ_dmul_c(دوہرا *dst, ثابت دوہرا *src0, ثابت دوہرا *src1,
                          صحیح len)
{
    صحیح i;
    برائے (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ساکن خالی سمتیہ_fmac_scalar_c(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                 صحیح len)
{
    صحیح i;
    برائے (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ساکن خالی سمتیہ_dmac_scalar_c(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                 صحیح len)
{
    صحیح i;
    برائے (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ساکن خالی سمتیہ_fmul_scalar_c(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                 صحیح len)
{
    صحیح i;
    برائے (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ساکن خالی سمتیہ_dmul_scalar_c(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                 صحیح len)
{
    صحیح i;
    برائے (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ساکن خالی سمتیہ_fmul_کھڑکی_c(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len)
{
    صحیح i, j;

    dst  += len;
    win  += len;
    src0 += len;

    برائے (i = -len, j = len - 1; i < 0; i++, j--) {
        اعشاری s0 = src0[i];
        اعشاری s1 = src1[j];
        اعشاری wi = win[i];
        اعشاری wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ساکن خالی سمتیہ_fmul_جوڑو_c(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                              ثابت اعشاری *src2, صحیح len){
    صحیح i;

    برائے (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ساکن خالی سمتیہ_fmul_الٹ_c(اعشاری *dst, ثابت اعشاری *src0,
                                  ثابت اعشاری *src1, صحیح len)
{
    صحیح i;

    src1 += len-1;
    برائے (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ساکن خالی butterflies_float_c(اعشاری *محدود v1, اعشاری *محدود v2,
                                صحیح len)
{
    صحیح i;

    برائے (i = 0; i < len; i++) {
        اعشاری t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

دوہرا ff_scalarproduct_double_c(ثابت دوہرا *v1, ثابت دوہرا *v2,
                                 size_t len)
{
    دوہرا p = 0.0;

    برائے (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    واپس p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(صحیح ثنائی_ہندسہ_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(حجم(AVFloatDSPContext));
    اگر (!fdsp)
        واپس تہی;

    fdsp->سمتیہ_fmul = سمتیہ_fmul_c;
    fdsp->سمتیہ_dmul = سمتیہ_dmul_c;
    fdsp->سمتیہ_fmac_scalar = سمتیہ_fmac_scalar_c;
    fdsp->سمتیہ_fmul_scalar = سمتیہ_fmul_scalar_c;
    fdsp->سمتیہ_dmac_scalar = سمتیہ_dmac_scalar_c;
    fdsp->سمتیہ_dmul_scalar = سمتیہ_dmul_scalar_c;
    fdsp->سمتیہ_fmul_کھڑکی = سمتیہ_fmul_کھڑکی_c;
    fdsp->سمتیہ_fmul_جوڑو = سمتیہ_fmul_جوڑو_c;
    fdsp->سمتیہ_fmul_الٹ = سمتیہ_fmul_الٹ_c;
    fdsp->butterflies_float = butterflies_float_c;
    fdsp->scalarproduct_float = ff_scalarproduct_float_c;
    fdsp->scalarproduct_double = ff_scalarproduct_double_c;

#اگر ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#وگرنہ_اگر ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#وگرنہ_اگر ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, ثنائی_ہندسہ_exact);
#وگرنہ_اگر ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#وگرنہ_اگر ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#وگرنہ_اگر ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#اگر_ختم
    واپس fdsp;
}
