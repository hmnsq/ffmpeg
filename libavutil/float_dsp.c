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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "float_dsp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_fmul_c(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                          ਪੂਰਨ len)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_dmul_c(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src0, ਅਚਲ ਦੁੱਗਣਾ *src1,
                          ਪੂਰਨ len)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_fmac_scalar_c(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                 ਪੂਰਨ len)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_dmac_scalar_c(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                 ਪੂਰਨ len)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_fmul_scalar_c(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                 ਪੂਰਨ len)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_dmul_scalar_c(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                 ਪੂਰਨ len)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_c(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                 ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਅਚਲ ਦਸ਼ਮਲਵ *win, ਪੂਰਨ len)
{
    ਪੂਰਨ i, j;

    dst  += len;
    win  += len;
    src0 += len;

    ਲਈ (i = -len, j = len - 1; i < 0; i++, j--) {
        ਦਸ਼ਮਲਵ s0 = src0[i];
        ਦਸ਼ਮਲਵ s1 = src1[j];
        ਦਸ਼ਮਲਵ wi = win[i];
        ਦਸ਼ਮਲਵ wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_fmul_ਜੋੜੋ_c(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                              ਅਚਲ ਦਸ਼ਮਲਵ *src2, ਪੂਰਨ len){
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ਸਥਿਰ ਖਾਲੀ ਸਦਿਸ਼_fmul_ਉਲਟ_c(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                  ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len)
{
    ਪੂਰਨ i;

    src1 += len-1;
    ਲਈ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ਸਥਿਰ ਖਾਲੀ butterflies_float_c(ਦਸ਼ਮਲਵ *ਸੀਮਿਤ v1, ਦਸ਼ਮਲਵ *ਸੀਮਿਤ v2,
                                ਪੂਰਨ len)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < len; i++) {
        ਦਸ਼ਮਲਵ t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

ਦੁੱਗਣਾ ff_scalarproduct_double_c(ਅਚਲ ਦੁੱਗਣਾ *v1, ਅਚਲ ਦੁੱਗਣਾ *v2,
                                 size_t len)
{
    ਦੁੱਗਣਾ p = 0.0;

    ਲਈ (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ਵਾਪਸ p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(ਆਕਾਰ(AVFloatDSPContext));
    ਜੇ (!fdsp)
        ਵਾਪਸ ਨਿਰਾ;

    fdsp->ਸਦਿਸ਼_fmul = ਸਦਿਸ਼_fmul_c;
    fdsp->ਸਦਿਸ਼_dmul = ਸਦਿਸ਼_dmul_c;
    fdsp->ਸਦਿਸ਼_fmac_scalar = ਸਦਿਸ਼_fmac_scalar_c;
    fdsp->ਸਦਿਸ਼_fmul_scalar = ਸਦਿਸ਼_fmul_scalar_c;
    fdsp->ਸਦਿਸ਼_dmac_scalar = ਸਦਿਸ਼_dmac_scalar_c;
    fdsp->ਸਦਿਸ਼_dmul_scalar = ਸਦਿਸ਼_dmul_scalar_c;
    fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ = ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_c;
    fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ = ਸਦਿਸ਼_fmul_ਜੋੜੋ_c;
    fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ਸਦਿਸ਼_fmul_ਉਲਟ_c;
    fdsp->butterflies_float = butterflies_float_c;
    fdsp->scalarproduct_float = ff_scalarproduct_float_c;
    fdsp->scalarproduct_double = ff_scalarproduct_double_c;

#ਜੇ ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#ਜਾਂਜੇ ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#ਜਾਂਜੇ ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, ਦੋਆਧਾਰੀ_ਅੰਕ_exact);
#ਜਾਂਜੇ ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#ਜਾਂਜੇ ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#ਜਾਂਜੇ ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ fdsp;
}
