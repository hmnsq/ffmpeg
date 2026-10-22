/*
 * Copyright © 2022 Rémi Denis-Courmont.
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

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/float_dsp.h"

శూన్య ff_సదిశ_fmul_rvv(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                         పూర్ణాంకం len);
శూన్య ff_సదిశ_fmac_scalar_rvv(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_scalar_rvv(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_కిటికీ_rvv(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                స్థిరరాశి దశాంశం *src1, స్థిరరాశి దశాంశం *win, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_కూడు_rvv(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                             స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_తిరగేయి_rvv(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                 స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);
శూన్య ff_butterflies_float_rvv(దశాంశం *v1, దశాంశం *v2, పూర్ణాంకం len);
దశాంశం ff_scalarproduct_float_rvv(స్థిరరాశి దశాంశం *v1, స్థిరరాశి దశాంశం *v2, పూర్ణాంకం len);

శూన్య ff_సదిశ_dmul_rvv(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src0, స్థిరరాశి ద్విగుణ *src1,
                         పూర్ణాంకం len);
శూన్య ff_సదిశ_dmac_scalar_rvv(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                పూర్ణాంకం len);
శూన్య ff_సదిశ_dmul_scalar_rvv(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                పూర్ణాంకం len);
ద్విగుణ ff_scalarproduct_double_rvv(స్థిరరాశి ద్విగుణ *v1, స్థిరరాశి ద్విగుణ *v2,
                                   size_t len);

av_cold శూన్య ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#ఒకవేళ HAVE_RVV
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & AV_CPU_FLAG_RVB) {
        ఒకవేళ (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->సదిశ_fmul = ff_సదిశ_fmul_rvv;
            fdsp->సదిశ_fmac_scalar = ff_సదిశ_fmac_scalar_rvv;
            fdsp->సదిశ_fmul_scalar = ff_సదిశ_fmul_scalar_rvv;
            fdsp->సదిశ_fmul_కిటికీ = ff_సదిశ_fmul_కిటికీ_rvv;
            fdsp->సదిశ_fmul_కూడు = ff_సదిశ_fmul_కూడు_rvv;
            fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        ఒకవేళ (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->సదిశ_dmul = ff_సదిశ_dmul_rvv;
            fdsp->సదిశ_dmac_scalar = ff_సదిశ_dmac_scalar_rvv;
            fdsp->సదిశ_dmul_scalar = ff_సదిశ_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#అయితే_ముగింపు
}
