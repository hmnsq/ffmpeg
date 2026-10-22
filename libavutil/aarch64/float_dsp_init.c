/*
 * ARM NEON optimised Float DSP functions
 * Copyright (c) 2008 Mans Rullgard <mans@mansr.com>
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

#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/float_dsp.h"
#అన్తర్భావ "cpu.h"

శూన్య ff_సదిశ_fmul_neon(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                         పూర్ణాంకం len);

శూన్య ff_సదిశ_fmac_scalar_neon(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_scalar_neon(దశాంశం *dst, స్థిరరాశి దశాంశం *src, దశాంశం mul,
                                పూర్ణాంకం len);

శూన్య ff_సదిశ_dmul_scalar_neon(ద్విగుణ *dst, స్థిరరాశి ద్విగుణ *src, ద్విగుణ mul,
                                పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_కిటికీ_neon(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                స్థిరరాశి దశాంశం *src1, స్థిరరాశి దశాంశం *win, పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_కూడు_neon(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                             స్థిరరాశి దశాంశం *src2, పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_తిరగేయి_neon(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                 స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);

శూన్య ff_butterflies_float_neon(దశాంశం *v1, దశాంశం *v2, పూర్ణాంకం len);

దశాంశం ff_scalarproduct_float_neon(స్థిరరాశి దశాంశం *v1, స్థిరరాశి దశాంశం *v2, పూర్ణాంకం len);

av_cold శూన్య ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    ఒకవేళ (have_neon(cpu_flags)) {
        fdsp->butterflies_float   = ff_butterflies_float_neon;
        fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
        fdsp->సదిశ_dmul_scalar  = ff_సదిశ_dmul_scalar_neon;
        fdsp->సదిశ_fmul         = ff_సదిశ_fmul_neon;
        fdsp->సదిశ_fmac_scalar  = ff_సదిశ_fmac_scalar_neon;
        fdsp->సదిశ_fmul_కూడు     = ff_సదిశ_fmul_కూడు_neon;
        fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_neon;
        fdsp->సదిశ_fmul_scalar  = ff_సదిశ_fmul_scalar_neon;
        fdsp->సదిశ_fmul_కిటికీ  = ff_సదిశ_fmul_కిటికీ_neon;
    }
}
