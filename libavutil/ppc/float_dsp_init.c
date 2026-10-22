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

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/float_dsp.h"
#شامل "libavutil/ppc/cpu.h"
#شامل "float_dsp_altivec.h"
#شامل "float_dsp_vsx.h"

av_cold خالی ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, صحیح ثنائی_ہندسہ_exact)
{
    اگر (PPC_ALTIVEC(av_get_cpu_flags())) {
        fdsp->سمتیہ_fmul = ff_سمتیہ_fmul_altivec;
        fdsp->سمتیہ_fmul_جوڑو = ff_سمتیہ_fmul_جوڑو_altivec;
        fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_altivec;

        اگر (!ثنائی_ہندسہ_exact) {
            fdsp->سمتیہ_fmul_کھڑکی = ff_سمتیہ_fmul_کھڑکی_altivec;
        }
    }

    // The disabled function below are near identical to altivec and have
    // been disabled to reduce code duplication
    اگر (PPC_VSX(av_get_cpu_flags())) {
//         fdsp->vector_fmul = ff_vector_fmul_vsx;
        fdsp->سمتیہ_fmul_جوڑو = ff_سمتیہ_fmul_جوڑو_vsx;
//         fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vsx;

//         if (!bit_exact) {
//             fdsp->vector_fmul_window = ff_vector_fmul_window_vsx;
//         }
    }
}
