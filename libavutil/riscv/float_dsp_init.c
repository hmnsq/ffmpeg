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
#அந்தர்பாவ "libavutil/float_dsp.h"

வெறுமை ff_vector_fmul_rvv(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                         முழு len);
வெறுமை ff_vector_fmac_scalar_rvv(தசம *dst, மாறிலி தசம *src, தசம mul,
                                முழு len);
வெறுமை ff_vector_fmul_scalar_rvv(தசம *dst, மாறிலி தசம *src, தசம mul,
                                முழு len);
வெறுமை ff_vector_fmul_window_rvv(தசம *dst, மாறிலி தசம *src0,
                                மாறிலி தசம *src1, மாறிலி தசம *win, முழு len);
வெறுமை ff_vector_fmul_add_rvv(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                             மாறிலி தசம *src2, முழு len);
வெறுமை ff_vector_fmul_reverse_rvv(தசம *dst, மாறிலி தசம *src0,
                                 மாறிலி தசம *src1, முழு len);
வெறுமை ff_butterflies_float_rvv(தசம *v1, தசம *v2, முழு len);
தசம ff_scalarproduct_float_rvv(மாறிலி தசம *v1, மாறிலி தசம *v2, முழு len);

வெறுமை ff_vector_dmul_rvv(இரட்டை *dst, மாறிலி இரட்டை *src0, மாறிலி இரட்டை *src1,
                         முழு len);
வெறுமை ff_vector_dmac_scalar_rvv(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                முழு len);
வெறுமை ff_vector_dmul_scalar_rvv(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                முழு len);
இரட்டை ff_scalarproduct_double_rvv(மாறிலி இரட்டை *v1, மாறிலி இரட்டை *v2,
                                   size_t len);

av_cold வெறுமை ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#எனில் HAVE_RVV
    முழு flags = av_get_cpu_flags();

    எனில் (flags & AV_CPU_FLAG_RVB) {
        எனில் (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        எனில் (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
