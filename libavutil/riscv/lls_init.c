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

#அந்தர்பாவ <assert.h>
#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/riscv/cpu.h"
#அந்தர்பாவ "libavutil/lls.h"

வெறுமை ff_lls_update_covariance_rvv(இரட்டை covar[][36], மாறிலி இரட்டை *var,
                                  முழு மொத்தம்);
இரட்டை ff_scalarproduct_double_rvv(மாறிலி இரட்டை *, மாறிலி இரட்டை *, size_t);

நிலையான வெறுமை ff_lls_update_rvv(கட்டமைப்பு LLSModel *m, மாறிலி இரட்டை *var)
{
    ff_lls_update_covariance_rvv(m->covariance, var, m->indep_மொத்தம் + 1);
}

நிலையான இரட்டை ff_lls_evaluate_rvv(கட்டமைப்பு LLSModel *m, மாறிலி இரட்டை *var,
                                  முழு order)
{
    திரும்பு ff_scalarproduct_double_rvv(m->coeff[order], var, order + 1);
}

av_cold வெறுமை ff_init_lls_riscv(LLSModel *m)
{
#எனில் HAVE_RVV
    முழு flags = av_get_cpu_flags();

    எனில் ((flags & AV_CPU_FLAG_RVB) && (flags & AV_CPU_FLAG_RVV_F64)) {
        எனில் (ff_get_rv_vlenb() > m->indep_மொத்தம்)
            m->update_lls = ff_lls_update_rvv;
        m->evaluate_lls = ff_lls_evaluate_rvv;
    }
#endif
}
