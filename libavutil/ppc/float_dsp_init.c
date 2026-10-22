/*
 * Copyright (c) 2006 Luca Barbato <lu_zero@gentoo.org>
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

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/float_dsp.h"
#ضمن "libavutil/ppc/cpu.h"
#ضمن "float_dsp_altivec.h"
#ضمن "float_dsp_vsx.h"

av_cold فراغ ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, صحيح بیت_exact)
{
    إذا (PPC_ALTIVEC(av_get_cpu_flags())) {
        fdsp->وکتور_fmul = ff_وکتور_fmul_altivec;
        fdsp->وکتور_fmul_جمع_کن = ff_وکتور_fmul_جمع_کن_altivec;
        fdsp->وکتور_fmul_معکوس = ff_وکتور_fmul_معکوس_altivec;

        إذا (!بیت_exact) {
            fdsp->وکتور_fmul_پنجره = ff_وکتور_fmul_پنجره_altivec;
        }
    }

    // The disabled function below are near identical to altivec and have
    // been disabled to reduce code duplication
    إذا (PPC_VSX(av_get_cpu_flags())) {
//         fdsp->vector_fmul = ff_vector_fmul_vsx;
        fdsp->وکتور_fmul_جمع_کن = ff_وکتور_fmul_جمع_کن_vsx;
//         fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vsx;

//         if (!bit_exact) {
//             fdsp->vector_fmul_window = ff_vector_fmul_window_vsx;
//         }
    }
}
