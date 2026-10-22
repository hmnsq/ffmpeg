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

ಶೂನ್ಯ ff_vector_fmul_vfp(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0, ಧ್ರುವ ಭಿನ್ನ *src1,
                        ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmul_window_vfp(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                               ಧ್ರುವ ಭಿನ್ನ *src1, ಧ್ರುವ ಭಿನ್ನ *win, ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_vector_fmul_reverse_vfp(ಭಿನ್ನ *dst, ಧ್ರುವ ಭಿನ್ನ *src0,
                                ಧ್ರುವ ಭಿನ್ನ *src1, ಪೂರ್ಣಾಙ್ಕ len);

ಶೂನ್ಯ ff_butterflies_float_vfp(ಭಿನ್ನ *restrict v1, ಭಿನ್ನ *restrict v2, ಪೂರ್ಣಾಙ್ಕ len);

av_cold ಶೂನ್ಯ ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, ಪೂರ್ಣಾಙ್ಕ cpu_flags)
{
    ಯದಿ (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    ಯದಿ (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
