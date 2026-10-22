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

خالی ff_سمتیہ_fmul_vfp(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                        صحیح len);

خالی ff_سمتیہ_fmul_کھڑکی_vfp(اعشاری *dst, ثابت اعشاری *src0,
                               ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);

خالی ff_سمتیہ_fmul_الٹ_vfp(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);

خالی ff_butterflies_float_vfp(اعشاری *محدود v1, اعشاری *محدود v2, صحیح len);

av_cold خالی ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, صحیح cpu_flags)
{
    اگر (have_vfp_vm(cpu_flags)) {
        fdsp->سمتیہ_fmul = ff_سمتیہ_fmul_vfp;
        fdsp->سمتیہ_fmul_کھڑکی = ff_سمتیہ_fmul_کھڑکی_vfp;
    }
    fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_vfp;
    اگر (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
