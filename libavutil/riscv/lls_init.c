/*
 * Copyright © 2024 Rémi Denis-Courmont.
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

#అన్తర్భావ <assert.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/riscv/cpu.h"
#అన్తర్భావ "libavutil/lls.h"

శూన్య ff_lls_update_covariance_rvv(ద్విగుణ covar[][36], స్థిరరాశి ద్విగుణ *var,
                                  పూర్ణాంకం లెక్క);
ద్విగుణ ff_scalarproduct_double_rvv(స్థిరరాశి ద్విగుణ *, స్థిరరాశి ద్విగుణ *, size_t);

స్థిర శూన్య ff_lls_update_rvv(నిర్మాణం LLSModel *m, స్థిరరాశి ద్విగుణ *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_లెక్క + 1);
}

స్థిర ద్విగుణ ff_lls_evaluate_rvv(నిర్మాణం LLSModel *m, స్థిరరాశి ద్విగుణ *var,
                                  పూర్ణాంకం క్రమం)
{
    తిరిగి ff_scalarproduct_double_rvv(m->coeff[క్రమం], var, క్రమం + 1);
}

av_cold శూన్య ff_init_lls_riscv(LLSModel *m)
{
#ఒకవేళ HAVE_RVV
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        ఒకవేళ (ff_get_rv_vlenb() > m->indep_లెక్క)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#అయితే_ముగింపు
}
