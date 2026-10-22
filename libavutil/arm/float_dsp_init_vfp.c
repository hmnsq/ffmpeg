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

#ضمن "libavutil/attributes.h"
#ضمن "libavutil/float_dsp.h"
#ضمن "cpu.h"
#ضمن "float_dsp_arm.h"

فراغ ff_vector_fmul_vfp(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                        صحيح len);

فراغ ff_vector_fmul_window_vfp(عائم *dst, ثابت عائم *src0,
                               ثابت عائم *src1, ثابت عائم *win, صحيح len);

فراغ ff_vector_fmul_reverse_vfp(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, صحيح len);

فراغ ff_butterflies_float_vfp(عائم *restrict v1, عائم *restrict v2, صحيح len);

av_cold فراغ ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, صحيح cpu_flags)
{
    𐡄𐡍 (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    𐡄𐡍 (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
