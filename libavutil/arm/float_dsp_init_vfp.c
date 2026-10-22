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

#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/float_dsp.h"
#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ "float_dsp_arm.h"

வெறுமை ff_vector_fmul_vfp(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                        முழு len);

வெறுமை ff_vector_fmul_window_vfp(தசம *dst, மாறிலி தசம *src0,
                               மாறிலி தசம *src1, மாறிலி தசம *win, முழு len);

வெறுமை ff_vector_fmul_reverse_vfp(தசம *dst, மாறிலி தசம *src0,
                                மாறிலி தசம *src1, முழு len);

வெறுமை ff_butterflies_float_vfp(தசம *restrict v1, தசம *restrict v2, முழு len);

av_cold வெறுமை ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, முழு cpu_flags)
{
    எனில் (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    எனில் (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
