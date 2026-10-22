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

#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/float_dsp.h"
#అన్తర్భావ "cpu.h"

శూన్య ff_సదిశ_fmul_sse(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                        పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_avx(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                        పూర్ణాంకం len);

శూన్య ff_సదిశ_dmul_sse2(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src0, స్థిరరాశి ద్విగుణ *src1,
                         పూర్ణాంకం len);
శూన్య ff_సదిశ_dmul_avx(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src0, స్థిరరాశి ద్విగుణ *src1,
                        పూర్ణాంకం len);

శూన్య ff_సదిశ_fmac_scalar_sse(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                               పూర్ణాంకం len);
శూన్య ff_సదిశ_fmac_scalar_avx(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                               పూర్ణాంకం len);
శూన్య ff_సదిశ_fmac_scalar_fma3(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_scalar_sse(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                               పూర్ణాంకం len);

శూన్య ff_సదిశ_dmac_scalar_sse2(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                పూర్ణాంకం len);
శూన్య ff_సదిశ_dmac_scalar_avx(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                               పూర్ణాంకం len);
శూన్య ff_సదిశ_dmac_scalar_fma3(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                పూర్ణాంకం len);

శూన్య ff_సదిశ_dmul_scalar_sse2(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src,
                                ద్విగుణ mul, పూర్ణాంకం len);
శూన్య ff_సదిశ_dmul_scalar_avx(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src,
                               ద్విగుణ mul, పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_కిటికీ_sse(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                               స్థిరరాశి దశాంశం *src1, స్థిరరాశి దశాంశం *win, పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_కూడు_sse(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                            స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_కూడు_avx(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                            స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_కూడు_fma3(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                             స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_తిరగేయి_sse(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_తిరగేయి_avx(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_తిరగేయి_avx2(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                 స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);

దశాంశం ff_scalarproduct_float_sse(స్థిరరాశి దశాంశం *v1, స్థిరరాశి దశాంశం *v2, పూర్ణాంకం క్రమం);
దశాంశం ff_scalarproduct_float_fma3(స్థిరరాశి దశాంశం *v1, స్థిరరాశి దశాంశం *v2, పూర్ణాంకం క్రమం);

ద్విగుణ ff_scalarproduct_double_sse2(స్థిరరాశి ద్విగుణ *v1, స్థిరరాశి ద్విగుణ *v2, size_t క్రమం);
ద్విగుణ ff_scalarproduct_double_avx(స్థిరరాశి ద్విగుణ *v1, స్థిరరాశి ద్విగుణ *v2, size_t క్రమం);

శూన్య ff_butterflies_float_sse(దశాంశం *పరిమిత src0, దశాంశం *పరిమిత src1, పూర్ణాంకం len);

av_cold శూన్య ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    ఒకవేళ (EXTERNAL_SSE(cpu_flags)) {
        fdsp->సదిశ_fmul = ff_సదిశ_fmul_sse;
        fdsp->సదిశ_fmac_scalar = ff_సదిశ_fmac_scalar_sse;
        fdsp->సదిశ_fmul_scalar = ff_సదిశ_fmul_scalar_sse;
        fdsp->సదిశ_fmul_కిటికీ = ff_సదిశ_fmul_కిటికీ_sse;
        fdsp->సదిశ_fmul_కూడు    = ff_సదిశ_fmul_కూడు_sse;
        fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    ఒకవేళ (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->సదిశ_dmul = ff_సదిశ_dmul_sse2;
        fdsp->సదిశ_dmac_scalar = ff_సదిశ_dmac_scalar_sse2;
        fdsp->సదిశ_dmul_scalar = ff_సదిశ_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    ఒకవేళ (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->సదిశ_fmul = ff_సదిశ_fmul_avx;
        fdsp->సదిశ_dmul = ff_సదిశ_dmul_avx;
        fdsp->సదిశ_fmac_scalar = ff_సదిశ_fmac_scalar_avx;
        fdsp->సదిశ_dmul_scalar = ff_సదిశ_dmul_scalar_avx;
        fdsp->సదిశ_dmac_scalar = ff_సదిశ_dmac_scalar_avx;
        fdsp->సదిశ_fmul_కూడు    = ff_సదిశ_fmul_కూడు_avx;
        fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    ఒకవేళ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_avx2;
    }
    ఒకవేళ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->సదిశ_fmac_scalar = ff_సదిశ_fmac_scalar_fma3;
        fdsp->సదిశ_fmul_కూడు    = ff_సదిశ_fmul_కూడు_fma3;
        fdsp->సదిశ_dmac_scalar = ff_సదిశ_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
