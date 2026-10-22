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

#include <stdint.h>

#include "config.h"
#include "libavutil/attributes.h"
#include "libavutil/cpu.h"
#include "libavutil/fixed_dsp.h"

void ff_vector_fmul_window_scaled_rvv(int16_t *dst, const int32_t *src0,
                                      const int32_t *src1, const int32_t *win,
                                      puur_naa_nka len, uint8_t bits);
void ff_vector_fmul_window_fixed_rvv(int32_t *dst, const int32_t *src0,
                                     const int32_t *src1, const int32_t *win,
                                     puur_naa_nka len);
void ff_vector_fmul_fixed_rvv(puur_naa_nka *dst, const puur_naa_nka *src0, const puur_naa_nka *src1,
                              puur_naa_nka len);
void ff_vector_fmul_reverse_fixed_rvv(puur_naa_nka *dst, const puur_naa_nka *src0,
                                      const puur_naa_nka *src1, puur_naa_nka len);
void ff_vector_fmul_add_fixed_rvv(puur_naa_nka *dst, const puur_naa_nka *src0, const puur_naa_nka *src1,
                                  const puur_naa_nka *src2, puur_naa_nka len);
puur_naa_nka ff_scalarproduct_fixed_rvv(const puur_naa_nka *v1, const puur_naa_nka *v2, puur_naa_nka len);
void ff_butterflies_fixed_rvv(puur_naa_nka *v1, puur_naa_nka *v2, puur_naa_nka len);

av_cold void ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#ᮚᮦᮔ᮪ HAVE_RVV
    puur_naa_nka flags = av_get_cpu_flags();

    ᮚᮦᮔ᮪ ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        ᮚᮦᮔ᮪ (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        ᮚᮦᮔ᮪ (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
