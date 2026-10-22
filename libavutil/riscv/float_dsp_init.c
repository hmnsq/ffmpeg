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
#અન્તર્ભાવ "libavutil/float_dsp.h"

શૂન્ય ff_vector_fmul_rvv(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                         પૂર્ણાંક len);
શૂન્ય ff_vector_fmac_scalar_rvv(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_scalar_rvv(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_window_rvv(દશાંશ *dst, અચલ દશાંશ *src0,
                                અચલ દશાંશ *src1, અચલ દશાંશ *win, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_add_rvv(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                             અચલ દશાંશ *src2, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_reverse_rvv(દશાંશ *dst, અચલ દશાંશ *src0,
                                 અચલ દશાંશ *src1, પૂર્ણાંક len);
શૂન્ય ff_butterflies_float_rvv(દશાંશ *v1, દશાંશ *v2, પૂર્ણાંક len);
દશાંશ ff_scalarproduct_float_rvv(અચલ દશાંશ *v1, અચલ દશાંશ *v2, પૂર્ણાંક len);

શૂન્ય ff_vector_dmul_rvv(દ્વિગુણ *dst, અચલ દ્વિગુણ *src0, અચલ દ્વિગુણ *src1,
                         પૂર્ણાંક len);
શૂન્ય ff_vector_dmac_scalar_rvv(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                                પૂર્ણાંક len);
શૂન્ય ff_vector_dmul_scalar_rvv(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                                પૂર્ણાંક len);
દ્વિગુણ ff_scalarproduct_double_rvv(અચલ દ્વિગુણ *v1, અચલ દ્વિગુણ *v2,
                                   size_t len);

av_cold શૂન્ય ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#જો HAVE_RVV
    પૂર્ણાંક flags = av_get_cpu_flags();

    જો (flags & AV_CPU_FLAG_RVB) {
        જો (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        જો (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
