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
#ಅನ್ತರ್ಭಾವ "libavutil/float_dsp.h"

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_rvv(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                         ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmac_scalar_rvv(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_scalar_rvv(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_rvv(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *win, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_rvv(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                             ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_rvv(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                 ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_butterflies_float_rvv(ದಶಮಾಂಶ *v1, ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len);
ದಶಮಾಂಶ ff_scalarproduct_float_rvv(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_dmul_rvv(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src0, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src1,
                         ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_dmac_scalar_rvv(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಂಕ len);
ಶೂನ್ಯ ff_ಸದಿಶ_dmul_scalar_rvv(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಂಕ len);
ದ್ವಿಗುಣ ff_scalarproduct_double_rvv(ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v1, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *v2,
                                   size_t len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#ಆದರೆ HAVE_RVV
    ಪೂರ್ಣಾಂಕ flags = av_get_cpu_flags();

    ಆದರೆ (flags & AV_CPU_FLAG_RVB) {
        ಆದರೆ (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->ಸದಿಶ_fmul = ff_ಸದಿಶ_fmul_rvv;
            fdsp->ಸದಿಶ_fmac_scalar = ff_ಸದಿಶ_fmac_scalar_rvv;
            fdsp->ಸದಿಶ_fmul_scalar = ff_ಸದಿಶ_fmul_scalar_rvv;
            fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ = ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_rvv;
            fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು = ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_rvv;
            fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        ಆದರೆ (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->ಸದಿಶ_dmul = ff_ಸದಿಶ_dmul_rvv;
            fdsp->ಸದಿಶ_dmac_scalar = ff_ಸದಿಶ_dmac_scalar_rvv;
            fdsp->ಸದಿಶ_dmul_scalar = ff_ಸದಿಶ_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
}
