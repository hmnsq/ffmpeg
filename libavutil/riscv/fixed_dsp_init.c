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
#అన్తర్భావ "libavutil/fixed_dsp.h"

శూన్య ff_సదిశ_fmul_కిటికీ_scaled_rvv(int16_t *dst, స్థిరరాశి int32_t *src0,
                                      స్థిరరాశి int32_t *src1, స్థిరరాశి int32_t *win,
                                      పూర్ణాంకం len, uint8_t బిట్లు);
శూన్య ff_సదిశ_fmul_కిటికీ_fixed_rvv(int32_t *dst, స్థిరరాశి int32_t *src0,
                                     స్థిరరాశి int32_t *src1, స్థిరరాశి int32_t *win,
                                     పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_fixed_rvv(పూర్ణాంకం *dst, స్థిరరాశి పూర్ణాంకం *src0, స్థిరరాశి పూర్ణాంకం *src1,
                              పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_తిరగేయి_fixed_rvv(పూర్ణాంకం *dst, స్థిరరాశి పూర్ణాంకం *src0,
                                      స్థిరరాశి పూర్ణాంకం *src1, పూర్ణాంకం len);
శూన్య ff_సదిశ_fmul_కూడు_fixed_rvv(పూర్ణాంకం *dst, స్థిరరాశి పూర్ణాంకం *src0, స్థిరరాశి పూర్ణాంకం *src1,
                                  స్థిరరాశి పూర్ణాంకం *src2, పూర్ణాంకం len);
పూర్ణాంకం ff_scalarproduct_fixed_rvv(స్థిరరాశి పూర్ణాంకం *v1, స్థిరరాశి పూర్ణాంకం *v2, పూర్ణాంకం len);
శూన్య ff_butterflies_fixed_rvv(పూర్ణాంకం *v1, పూర్ణాంకం *v2, పూర్ణాంకం len);

av_cold శూన్య ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#ఒకవేళ HAVE_RVV
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        ఒకవేళ (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->సదిశ_fmul_కిటికీ_scaled = ff_సదిశ_fmul_కిటికీ_scaled_rvv;
            fdsp->సదిశ_fmul_కిటికీ = ff_సదిశ_fmul_కిటికీ_fixed_rvv;
        }

        fdsp->సదిశ_fmul = ff_సదిశ_fmul_fixed_rvv;
        fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_fixed_rvv;
        fdsp->సదిశ_fmul_కూడు = ff_సదిశ_fmul_కూడు_fixed_rvv;

        ఒకవేళ (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#అయితే_ముగింపు
}
