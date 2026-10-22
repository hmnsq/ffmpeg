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

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/float_dsp.h"
#అన్తర్భావ "libavutil/ppc/cpu.h"
#అన్తర్భావ "float_dsp_altivec.h"
#అన్తర్భావ "float_dsp_vsx.h"

av_cold శూన్య ff_float_dsp_init_ppc(AVFloatDSPContext *fdsp, పూర్ణాంకం బిట్టు_exact)
{
    ఒకవేళ (PPC_ALTIVEC(av_get_cpu_flags())) {
        fdsp->సదిశ_fmul = ff_సదిశ_fmul_altivec;
        fdsp->సదిశ_fmul_కూడు = ff_సదిశ_fmul_కూడు_altivec;
        fdsp->సదిశ_fmul_తిరగేయి = ff_సదిశ_fmul_తిరగేయి_altivec;

        ఒకవేళ (!బిట్టు_exact) {
            fdsp->సదిశ_fmul_కిటికీ = ff_సదిశ_fmul_కిటికీ_altivec;
        }
    }

    // The disabled function below are near identical to altivec and have
    // been disabled to reduce code duplication
    ఒకవేళ (PPC_VSX(av_get_cpu_flags())) {
//         fdsp->vector_fmul = ff_vector_fmul_vsx;
        fdsp->సదిశ_fmul_కూడు = ff_సదిశ_fmul_కూడు_vsx;
//         fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vsx;

//         if (!bit_exact) {
//             fdsp->vector_fmul_window = ff_vector_fmul_window_vsx;
//         }
    }
}
