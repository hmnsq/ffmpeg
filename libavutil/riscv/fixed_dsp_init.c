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

#समावेश <stdint.h>

#समावेश "config.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/fixed_dsp.h"

व्योम ff_vector_fmul_window_scaled_rvv(int16_t *dst, स्थिर int32_t *src0,
                                      स्थिर int32_t *src1, स्थिर int32_t *win,
                                      पूर्णांक len, uint8_t bits);
व्योम ff_vector_fmul_window_fixed_rvv(int32_t *dst, स्थिर int32_t *src0,
                                     स्थिर int32_t *src1, स्थिर int32_t *win,
                                     पूर्णांक len);
व्योम ff_vector_fmul_fixed_rvv(पूर्णांक *dst, स्थिर पूर्णांक *src0, स्थिर पूर्णांक *src1,
                              पूर्णांक len);
व्योम ff_vector_fmul_reverse_fixed_rvv(पूर्णांक *dst, स्थिर पूर्णांक *src0,
                                      स्थिर पूर्णांक *src1, पूर्णांक len);
व्योम ff_vector_fmul_add_fixed_rvv(पूर्णांक *dst, स्थिर पूर्णांक *src0, स्थिर पूर्णांक *src1,
                                  स्थिर पूर्णांक *src2, पूर्णांक len);
पूर्णांक ff_scalarproduct_fixed_rvv(स्थिर पूर्णांक *v1, स्थिर पूर्णांक *v2, पूर्णांक len);
व्योम ff_butterflies_fixed_rvv(पूर्णांक *v1, पूर्णांक *v2, पूर्णांक len);

av_cold व्योम ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#अगर HAVE_RVV
    पूर्णांक flags = av_get_cpu_flags();

    अगर ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        अगर (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        अगर (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#पूर्ण_अगर
}
