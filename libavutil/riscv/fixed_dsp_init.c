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

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_scaled_rvv(int16_t *dst, ಸ್ಥಿರಾಂಕ int32_t *src0,
                                      ಸ್ಥಿರಾಂಕ int32_t *src1, ಸ್ಥಿರಾಂಕ int32_t *win,
                                      ಪೂರ್ಣಾಂಕ len, uint8_t ಬಿಟ್ಟುಗಳು);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_fixed_rvv(int32_t *dst, ಸ್ಥಿರಾಂಕ int32_t *src0,
                                     ಸ್ಥಿರಾಂಕ int32_t *src1, ಸ್ಥಿರಾಂಕ int32_t *win,
                                     ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_fixed_rvv(ಪೂರ್ಣಾಂಕ *dst, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src0, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src1,
                              ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_fixed_rvv(ಪೂರ್ಣಾಂಕ *dst, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src0,
                                      ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src1, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_fixed_rvv(ಪೂರ್ಣಾಂಕ *dst, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src0, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src1,
                                  ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *src2, ಪೂರ್ಣಾಂಕ len);
ಪೂರ್ಣಾಂಕ ff_scalarproduct_fixed_rvv(ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *v1, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ *v2, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_butterflies_fixed_rvv(ಪೂರ್ಣಾಂಕ *v1, ಪೂರ್ಣಾಂಕ *v2, ಪೂರ್ಣಾಂಕ len);

av_cold ಶೂನ್ಯ ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#ಆದರೆ HAVE_RVV
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        ಆದರೆ (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ_scaled = ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_scaled_rvv;
            fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ = ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_fixed_rvv;
        }

        fdsp->ಸದಿಶ_fmul = ff_ಸದಿಶ_fmul_fixed_rvv;
        fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_fixed_rvv;
        fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು = ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_fixed_rvv;

        ಆದರೆ (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#ಆದರೆ_ಅಂತ್ಯ
}
