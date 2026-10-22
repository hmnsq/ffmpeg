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

#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/fixed_dsp.h"

શૂન્ય ff_vector_fmul_window_scaled_rvv(int16_t *dst, અચલ int32_t *src0,
                                      અચલ int32_t *src1, અચલ int32_t *win,
                                      પૂર્ણાંક len, uint8_t bits);
શૂન્ય ff_vector_fmul_window_fixed_rvv(int32_t *dst, અચલ int32_t *src0,
                                     અચલ int32_t *src1, અચલ int32_t *win,
                                     પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_fixed_rvv(પૂર્ણાંક *dst, અચલ પૂર્ણાંક *src0, અચલ પૂર્ણાંક *src1,
                              પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_reverse_fixed_rvv(પૂર્ણાંક *dst, અચલ પૂર્ણાંક *src0,
                                      અચલ પૂર્ણાંક *src1, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_add_fixed_rvv(પૂર્ણાંક *dst, અચલ પૂર્ણાંક *src0, અચલ પૂર્ણાંક *src1,
                                  અચલ પૂર્ણાંક *src2, પૂર્ણાંક len);
પૂર્ણાંક ff_scalarproduct_fixed_rvv(અચલ પૂર્ણાંક *v1, અચલ પૂર્ણાંક *v2, પૂર્ણાંક len);
શૂન્ય ff_butterflies_fixed_rvv(પૂર્ણાંક *v1, પૂર્ણાંક *v2, પૂર્ણાંક len);

av_cold શૂન્ય ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#જો HAVE_RVV
    પૂર્ણાંક flags = av_get_cpu_flags();

    જો ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        જો (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        જો (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
