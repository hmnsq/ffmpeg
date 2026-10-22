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

#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/fixed_dsp.h"

ଶୂନ୍ୟ ff_vector_fmul_window_scaled_rvv(int16_t *dst, ଅଚଳ int32_t *src0,
                                      ଅଚଳ int32_t *src1, ଅଚଳ int32_t *win,
                                      ପୂର୍ଣ୍ଣସଂଖ୍ୟା len, uint8_t bits);
ଶୂନ୍ୟ ff_vector_fmul_window_fixed_rvv(int32_t *dst, ଅଚଳ int32_t *src0,
                                     ଅଚଳ int32_t *src1, ଅଚଳ int32_t *win,
                                     ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_fixed_rvv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src0, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src1,
                              ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_reverse_fixed_rvv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src0,
                                      ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_vector_fmul_add_fixed_rvv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src0, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src1,
                                  ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_scalarproduct_fixed_rvv(ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *v1, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);
ଶୂନ୍ୟ ff_butterflies_fixed_rvv(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *v1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

av_cold ଶୂନ୍ୟ ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#ଯଦି HAVE_RVV
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        ଯଦି (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        ଯଦି (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
