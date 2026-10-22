/*
 * Copyright (c) 2008 Siarhei Siamashka <ssvb@users.sourceforge.net>
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

#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/float_dsp.h"
#అన్తర్భావ "cpu.h"
#అన్తర్భావ "float_dsp_arm.h"

శూన్య ff_సదిశ_fmul_vfp(దశాంశం *dst, స్థిరరాశి దశాంశం *src0, స్థిరరాశి దశాంశం *src1,
                        పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_కిటికీ_vfp(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                               స్థిరరాశి దశాంశం *src1, స్థిరరాశి దశాంశం *win, పూర్ణాంకం len);

శూన్య ff_సదిశ_fmul_తిరగేయి_vfp(దశాంశం *dst, స్థిరరాశి దశాంశం *src0,
                                స్థిరరాశి దశాంశం *src1, పూర్ణాంకం len);

శూన్య ff_butterflies_float_vfp(దశాంశం *పరిమిత v1, దశాంశం *పరిమిత v2, పూర్ణాంకం len);

av_cold శూన్య ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, పూర్ణాంకం cpu_flags)
{
    ఒకవేళ (have_vfp_vm(cpu_flags)) {
        fdsp->సదిశ_fmul = ff_సదిశ_fmul_vfp;
        fdsp->సదిశ_fmul_కిటికీ = ff_సదిశ_fmul_కిటికీ_vfp;
    }
    fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_vfp;
    ఒకవేళ (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
