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

#అన్తర్భావ "config.h"
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "float_dsp.h"
#అన్తర్భావ "mem.h"

స్థిర శూన్య సదిశ_fmul_c(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                          పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

స్థిర శూన్య సదిశ_dmul_c(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src0, స్థిరరాశి ద్విగుణ *src1,
                          పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

స్థిర శూన్య సదిశ_fmac_scalar_c(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                 పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

స్థిర శూన్య సదిశ_dmac_scalar_c(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                 పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

స్థిర శూన్య సదిశ_fmul_scalar_c(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                 పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

స్థిర శూన్య సదిశ_dmul_scalar_c(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                 పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

స్థిర శూన్య సదిశ_fmul_కిటికీ_c(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                 స్థిరరాశి దశాంశం *src1, స్థిరరాశి దశాంశం *win, పూర్ణాంకం len)
{
    పూర్ణాంకం i, j;

    dst  += len;
    win  += len;
    src0 += len;

    కొరకు (i = -len, j = len - 1; i < 0; i++, j--) {
        దశాంశం s0 = src0[i];
        దశాంశం s1 = src1[j];
        దశాంశం wi = win[i];
        దశాంశం wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

స్థిర శూన్య సదిశ_fmul_కూడు_c(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                              స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len){
    పూర్ణాంకం i;

    కొరకు (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

స్థిర శూన్య సదిశ_fmul_తిరగేయి_c(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                  స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len)
{
    పూర్ణాంకం i;

    src1 += len-1;
    కొరకు (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

స్థిర శూన్య butterflies_float_c(దశాంశం *పరిమిత v1, దశాంశం *పరిమిత v2,
                                పూర్ణాంకం len)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < len; i++) {
        దశాంశం t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

ద్విగుణ ff_scalarproduct_double_c(స్థిరరాశి ద్విగుణ *v1, స్థిరరాశి ద్విగుణ *v2,
                                 size_t len)
{
    ద్విగుణ p = 0.0;

    కొరకు (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    తిరిగి p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(పూర్ణాంకం బిట్టు_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(పరిమాణం(AVFloatDSPContext));
    ఒకవేళ (!fdsp)
        తిరిగి ఖాళీ;

    fdsp->సదిశ_fmul = సదిశ_fmul_c;
    fdsp->సదిశ_dmul = సదిశ_dmul_c;
    fdsp->సదిశ_fmac_scalar = సదిశ_fmac_scalar_c;
    fdsp->సదిశ_fmul_scalar = సదిశ_fmul_scalar_c;
    fdsp->సదిశ_dmac_scalar = సదిశ_dmac_scalar_c;
    fdsp->సదిశ_dmul_scalar = సదిశ_dmul_scalar_c;
    fdsp->సదిశ_fmul_కిటికీ = సదిశ_fmul_కిటికీ_c;
    fdsp->సదిశ_fmul_కూడు = సదిశ_fmul_కూడు_c;
    fdsp->సదిశ_fmul_తిరగేయి = సదిశ_fmul_తిరగేయి_c;
    fdsp->butterflies_float = butterflies_float_c;
    fdsp->scalarproduct_float = ff_scalarproduct_float_c;
    fdsp->scalarproduct_double = ff_scalarproduct_double_c;

#ఒకవేళ ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#లేదావేళ ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#లేదావేళ ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, బిట్టు_exact);
#లేదావేళ ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#లేదావేళ ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#లేదావేళ ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#అయితే_ముగింపు
    తిరిగి fdsp;
}
