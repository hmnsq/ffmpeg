/*
 * Copyright (c) 2008 Siarhei Siamashka <ssvb@users.sourceforge.net>
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

#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/float_dsp.h"
#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "float_dsp_arm.h"

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_vfp(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1,
                        ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_vfp(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                               ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *win, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_vfp(ದಶಮಾಂಶ *dst, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src0,
                                ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *src1, ಪೂರ್ಣಾಂಕ len);

ಶೂನ್ಯ ff_butterflies_float_vfp(ದಶಮಾಂಶ *ಸೀಮಿತ v1, ದಶಮಾಂಶ *ಸೀಮಿತ v2, ಪೂರ್ಣಾಂಕ len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, ಪೂರ್ಣಾಂಕ cpu_flags)
{
    ಆದರೆ (have_vfp_vm(cpu_flags)) {
        fdsp->ಸದಿಶ_fmul = ff_ಸದಿಶ_fmul_vfp;
        fdsp->ಸದಿಶ_fmul_ಕಿಟಕಿ = ff_ಸದಿಶ_fmul_ಕಿಟಕಿ_vfp;
    }
    fdsp->ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ = ff_ಸದಿಶ_fmul_ಹಿಮ್ಮುಖ_vfp;
    ಆದರೆ (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
