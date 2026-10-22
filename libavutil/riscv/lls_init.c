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

#अन्तर्भाव <assert.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/riscv/cpu.h"
#अन्तर्भाव "libavutil/lls.h"

शून्य ff_lls_update_covariance_rvv(द्विगुण covar[][36], ध्रुव द्विगुण *var,
                                  पूर्णाङ्क मोजणी);
द्विगुण ff_scalarproduct_double_rvv(ध्रुव द्विगुण *, ध्रुव द्विगुण *, size_t);

स्थिर शून्य ff_lls_update_rvv(संरचना LLSModel *m, ध्रुव द्विगुण *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_मोजणी + 1);
}

स्थिर द्विगुण ff_lls_evaluate_rvv(संरचना LLSModel *m, ध्रुव द्विगुण *var,
                                  पूर्णाङ्क order)
{
    प्रत्यागम ff_scalarproduct_double_rvv(m->coeff[order], var, order + 1);
}

av_cold शून्य ff_init_lls_riscv(LLSModel *m)
{
#यदि HAVE_RVV
    पूर्णाङ्क flags = av_get_cpu_flags();

    यदि ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        यदि (ff_get_rv_vlenb() > m->indep_मोजणी)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#endif
}
