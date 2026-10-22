/*
 * ARM NEON optimised Float DSP functions
 * Copyright (c) 2008 Mans Rullgard <mans@mansr.com>
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

#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/float_dsp.h"
#ಅನ್ತರ್ಭಾವ "cpu.h"

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_neon(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                         ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmac_scalar_neon(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_scalar_neon(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src, ದಶಮಾಂಶ mul,
                                ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_dmul_scalar_neon(ದ್ವಿಗುಣ *dst, ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *src, ದ್ವಿಗುಣ mul,
                                ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_neon(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *win, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_neon(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                             ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src2, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_neon(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                 ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_butterflies_float_neon(ದಶಮಾಂಶ *v1, ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len);

ದಶಮಾಂಶ ff_scalarproduct_float_neon(ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *v2, ಪೂರ್ಣಾಂಕ len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();

    ಆದರೆ (have_neon(cpu_flags)) {
        fdsp->butterflies_float   = ff_butterflies_float_neon;
        fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
        fdsp->ಸದಿಶ_dmul_scalar  = ff_ಸದಿಶ_dmul_scalar_neon;
        fdsp->ಸದಿಶ_fmul         = ff_ಸದಿಶ_fmul_neon;
        fdsp->ಸದಿಶ_fmac_scalar  = ff_ಸದಿಶ_fmac_scalar_neon;
        fdsp->ಸದಿಶ_fmul_ಕೂಡಿಸು     = ff_ಸದಿಶ_fmul_ಕೂಡಿಸು_neon;
        fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_neon;
        fdsp->ಸದಿಶ_fmul_scalar  = ff_ಸದಿಶ_fmul_scalar_neon;
        fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ  = ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_neon;
    }
}
