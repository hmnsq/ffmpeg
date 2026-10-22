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

#شامل <stdint.h>

#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/float_dsp.h"
#شامل "cpu.h"

خالی ff_سمتیہ_fmul_neon(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                         صحیح len);

خالی ff_سمتیہ_fmac_scalar_neon(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);

خالی ff_سمتیہ_fmul_scalar_neon(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);

خالی ff_سمتیہ_dmul_scalar_neon(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                صحیح len);

خالی ff_سمتیہ_fmul_کھڑکی_neon(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);

خالی ff_سمتیہ_fmul_جوڑو_neon(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                             ثابت اعشاری *src2, صحیح len);

خالی ff_سمتیہ_fmul_الٹ_neon(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, صحیح len);

خالی ff_butterflies_float_neon(اعشاری *v1, اعشاری *v2, صحیح len);

اعشاری ff_scalarproduct_float_neon(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح len);

av_cold خالی ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    صحیح cpu_flags = av_get_cpu_flags();

    اگر (have_neon(cpu_flags)) {
        fdsp->butterflies_float   = ff_butterflies_float_neon;
        fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
        fdsp->سمتیہ_dmul_scalar  = ff_سمتیہ_dmul_scalar_neon;
        fdsp->سمتیہ_fmul         = ff_سمتیہ_fmul_neon;
        fdsp->سمتیہ_fmac_scalar  = ff_سمتیہ_fmac_scalar_neon;
        fdsp->سمتیہ_fmul_جوڑو     = ff_سمتیہ_fmul_جوڑو_neon;
        fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_neon;
        fdsp->سمتیہ_fmul_scalar  = ff_سمتیہ_fmul_scalar_neon;
        fdsp->سمتیہ_fmul_کھڑکی  = ff_سمتیہ_fmul_کھڑکی_neon;
    }
}
