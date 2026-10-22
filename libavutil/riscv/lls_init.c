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

#समावेश <assert.h>
#समावेश <stdint.h>

#समावेश "config.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/riscv/cpu.h"
#समावेश "libavutil/lls.h"

व्योम ff_lls_update_covariance_rvv(द्विगुन covar[][36], स्थिर द्विगुन *var,
                                  पूर्णांक गिनती);
द्विगुन ff_scalarproduct_double_rvv(स्थिर द्विगुन *, स्थिर द्विगुन *, माप_प्रकार);

अटल व्योम ff_lls_update_rvv(काष्ठा LLSModel *m, स्थिर द्विगुन *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_गिनती + 1);
}

अटल द्विगुन ff_lls_evaluate_rvv(काष्ठा LLSModel *m, स्थिर द्विगुन *var,
                                  पूर्णांक order)
{
    वापस ff_scalarproduct_double_rvv(m->coeff[order], var, order + 1);
}

av_cold व्योम ff_init_lls_riscv(LLSModel *m)
{
#अगर HAVE_RVV
    पूर्णांक flags = av_get_cpu_flags();

    अगर ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        अगर (ff_get_rv_vlenb() > m->indep_गिनती)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#पूर्ण_अगर
}
