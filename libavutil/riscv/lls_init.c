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

#شامل <assert.h>
#شامل <stdint.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/riscv/cpu.h"
#شامل "libavutil/lls.h"

خالی ff_lls_update_covariance_rvv(دوہرا covar[][36], ثابت دوہرا *var,
                                  صحیح گنتی);
دوہرا ff_scalarproduct_double_rvv(ثابت دوہرا *, ثابت دوہرا *, size_t);

ساکن خالی ff_lls_update_rvv(ساخت LLSModel *m, ثابت دوہرا *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_گنتی + 1);
}

ساکن دوہرا ff_lls_evaluate_rvv(ساخت LLSModel *m, ثابت دوہرا *var,
                                  صحیح ترتیب)
{
    واپس ff_scalarproduct_double_rvv(m->coeff[ترتیب], var, ترتیب + 1);
}

av_cold خالی ff_init_lls_riscv(LLSModel *m)
{
#اگر HAVE_RVV
    صحیح flags = av_get_cpu_flags();

    اگر ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        اگر (ff_get_rv_vlenb() > m->indep_گنتی)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#اگر_ختم
}
