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

#ضمن <assert.h>
#ضمن <stdint.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/riscv/cpu.h"
#ضمن "libavutil/lls.h"

فراغ ff_lls_update_covariance_rvv(مزدوج covar[][36], ثابت مزدوج *var,
                                  صحيح count);
مزدوج ff_scalarproduct_double_rvv(ثابت مزدوج *, ثابت مزدوج *, size_t);

ساكن فراغ ff_lls_update_rvv(بنية LLSModel *m, ثابت مزدوج *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_count + 1);
}

ساكن مزدوج ff_lls_evaluate_rvv(بنية LLSModel *m, ثابت مزدوج *var,
                                  صحيح order)
{
    أرجع ff_scalarproduct_double_rvv(m->coeff[order], var, order + 1);
}

av_cold فراغ ff_init_lls_riscv(LLSModel *m)
{
#𐤀𐤌 HAVE_RVV
    صحيح flags = av_get_cpu_flags();

    𐤀𐤌 ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        𐤀𐤌 (ff_get_rv_vlenb() > m->indep_count)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#endif
}
