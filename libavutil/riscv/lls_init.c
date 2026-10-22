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

#അന്തര്ഭാവ <assert.h>
#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/riscv/cpu.h"
#അന്തര്ഭാവ "libavutil/lls.h"

ശൂന്യം ff_lls_update_covariance_rvv(ഇരട്ട covar[][36], സ്ഥിരം ഇരട്ട *var,
                                  പൂർണ്ണസംഖ്യ എണ്ണം);
ഇരട്ട ff_scalarproduct_double_rvv(സ്ഥിരം ഇരട്ട *, സ്ഥിരം ഇരട്ട *, size_t);

സ്ഥിതം ശൂന്യം ff_lls_update_rvv(ഘടന LLSModel *m, സ്ഥിരം ഇരട്ട *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_എണ്ണം + 1);
}

സ്ഥിതം ഇരട്ട ff_lls_evaluate_rvv(ഘടന LLSModel *m, സ്ഥിരം ഇരട്ട *var,
                                  പൂർണ്ണസംഖ്യ order)
{
    തിരികെ ff_scalarproduct_double_rvv(m->coeff[order], var, order + 1);
}

av_cold ശൂന്യം ff_init_lls_riscv(LLSModel *m)
{
#എങ്കിൽ HAVE_RVV
    പൂർണ്ണസംഖ്യ flags = av_get_cpu_flags();

    എങ്കിൽ ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        എങ്കിൽ (ff_get_rv_vlenb() > m->indep_എണ്ണം)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#endif
}
