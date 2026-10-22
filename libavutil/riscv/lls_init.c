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

#અન્તર્ભાવ <assert.h>
#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/riscv/cpu.h"
#અન્તર્ભાવ "libavutil/lls.h"

શૂન્ય ff_lls_update_covariance_rvv(દ્વિગુણ covar[][36], અચલ દ્વિગુણ *var,
                                  પૂર્ણાંક ગણતરી);
દ્વિગુણ ff_scalarproduct_double_rvv(અચલ દ્વિગુણ *, અચલ દ્વિગુણ *, size_t);

સ્થિર શૂન્ય ff_lls_update_rvv(સંરચના LLSModel *m, અચલ દ્વિગુણ *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_ગણતરી + 1);
}

સ્થિર દ્વિગુણ ff_lls_evaluate_rvv(સંરચના LLSModel *m, અચલ દ્વિગુણ *var,
                                  પૂર્ણાંક order)
{
    પાછા ff_scalarproduct_double_rvv(m->coeff[order], var, order + 1);
}

av_cold શૂન્ય ff_init_lls_riscv(LLSModel *m)
{
#જો HAVE_RVV
    પૂર્ણાંક flags = av_get_cpu_flags();

    જો ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        જો (ff_get_rv_vlenb() > m->indep_ગણતરી)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#endif
}
