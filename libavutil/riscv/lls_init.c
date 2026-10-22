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

#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/riscv/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/lls.h"

ਖਾਲੀ ff_lls_update_covariance_rvv(ਦੁੱਗਣਾ covar[][36], ਅਚਲ ਦੁੱਗਣਾ *var,
                                  ਪੂਰਨ ਗਿਣਤੀ_2);
ਦੁੱਗਣਾ ff_scalarproduct_double_rvv(ਅਚਲ ਦੁੱਗਣਾ *, ਅਚਲ ਦੁੱਗਣਾ *, size_t);

ਸਥਿਰ ਖਾਲੀ ff_lls_update_rvv(ਬਣਤਰ LLSModel *m, ਅਚਲ ਦੁੱਗਣਾ *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_ਗਿਣਤੀ + 1);
}

ਸਥਿਰ ਦੁੱਗਣਾ ff_lls_evaluate_rvv(ਬਣਤਰ LLSModel *m, ਅਚਲ ਦੁੱਗਣਾ *var,
                                  ਪੂਰਨ ਕ੍ਰਮ)
{
    ਵਾਪਸ ff_scalarproduct_double_rvv(m->coeff[ਕ੍ਰਮ], var, ਕ੍ਰਮ + 1);
}

av_cold ਖਾਲੀ ff_init_lls_riscv(LLSModel *m)
{
#ਜੇ HAVE_RVV
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        ਜੇ (ff_get_rv_vlenb() > m->indep_ਗਿਣਤੀ)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#ਜੇ_ਅੰਤ
}
