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

#شامل "libavutil/attributes.h"
#شامل "libavutil/float_dsp.h"
#شامل "cpu.h"
#شامل "float_dsp_arm.h"

تهی ff_vector_fmul_vfp(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                        صحیح len);

تهی ff_vector_fmul_window_vfp(اعشاری *dst, ثابت اعشاری *src0,
                               ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);

تهی ff_vector_fmul_reverse_vfp(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);

تهی ff_butterflies_float_vfp(اعشاری *restrict v1, اعشاری *restrict v2, صحیح len);

av_cold تهی ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, صحیح cpu_flags)
{
    اگر (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    اگر (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
