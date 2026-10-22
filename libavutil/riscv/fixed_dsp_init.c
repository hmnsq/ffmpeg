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

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/fixed_dsp.h"

ಶೂನ್ಯ ff_vector_fmul_window_scaled_rvv(int16_t *dst, ಧ್ರುವ int32_t *src0,
                                      ಧ್ರುವ int32_t *src1, ಧ್ರುವ int32_t *win,
                                      ಪೂರ್ಣಾಙ್ಕ len, uint8_t bits);
ಶೂನ್ಯ ff_vector_fmul_window_fixed_rvv(int32_t *dst, ಧ್ರುವ int32_t *src0,
                                     ಧ್ರುವ int32_t *src1, ಧ್ರುವ int32_t *win,
                                     ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_fixed_rvv(ಪೂರ್ಣಾಙ್ಕ *dst, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src0, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src1,
                              ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_reverse_fixed_rvv(ಪೂರ್ಣಾಙ್ಕ *dst, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src0,
                                      ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src1, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_vector_fmul_add_fixed_rvv(ಪೂರ್ಣಾಙ್ಕ *dst, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src0, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src1,
                                  ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *src2, ಪೂರ್ಣಾಙ್ಕ len);
ಪೂರ್ಣಾಙ್ಕ ff_scalarproduct_fixed_rvv(ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *v1, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ *v2, ಪೂರ್ಣಾಙ್ಕ len);
ಶೂನ್ಯ ff_butterflies_fixed_rvv(ಪೂರ್ಣಾಙ್ಕ *v1, ಪೂರ್ಣಾಙ್ಕ *v2, ಪೂರ್ಣಾಙ್ಕ len);

av_cold ಶೂನ್ಯ ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#ಯದಿ HAVE_RVV
    ಪೂರ್ಣಾಙ್ಕ flags = av_get_cpu_flags();

    ಯದಿ ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        ಯದಿ (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->vector_fmul_window_scaled = ff_vector_fmul_window_scaled_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_fixed_rvv;
        }

        fdsp->vector_fmul = ff_vector_fmul_fixed_rvv;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_fixed_rvv;
        fdsp->vector_fmul_add = ff_vector_fmul_add_fixed_rvv;

        ಯದಿ (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#endif
}
