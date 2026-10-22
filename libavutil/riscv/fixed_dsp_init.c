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

#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/cpu.h"
#அந்தர்பாவ "libavutil/fixed_dsp.h"

வெறுமை ff_vector_fmul_window_scaled_rvv(int16_t *dst, மாறிலி int32_t *src0,
                                      மாறிலி int32_t *src1, மாறிலி int32_t *win,
                                      முழு len, uint8_t bits);
வெறுமை ff_vector_fmul_window_fixed_rvv(int32_t *dst, மாறிலி int32_t *src0,
                                     மாறிலி int32_t *src1, மாறிலி int32_t *win,
                                     முழு len);
வெறுமை ff_vector_fmul_fixed_rvv(முழு *dst, மாறிலி முழு *src0, மாறிலி முழு *src1,
                              முழு len);
வெறுமை ff_vector_fmul_reverse_fixed_rvv(முழு *dst, மாறிலி முழு *src0,
                                      மாறிலி முழு *src1, முழு len);
வெறுமை ff_vector_fmul_add_fixed_rvv(முழு *dst, மாறிலி முழு *src0, மாறிலி முழு *src1,
                                  மாறிலி முழு *src2, முழு len);
முழு ff_scalarproduct_fixed_rvv(மாறிலி முழு *v1, மாறிலி முழு *v2, முழு len);
வெறுமை ff_butterflies_fixed_rvv(முழு *v1, முழு *v2, முழு len);

av_cold வெறுமை ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#எனில் HAVE_RVV
    முழு flags = av_get_cpu_flags();

    எனில் ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        எனில் (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        எனில் (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
