/*
 * Copyright © 2022 Rémi Denis-Courmont.
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

#شامل "config.h"
#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/float_dsp.h"

خالی ff_سمتیہ_fmul_rvv(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                         صحیح len);
خالی ff_سمتیہ_fmac_scalar_rvv(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);
خالی ff_سمتیہ_fmul_scalar_rvv(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);
خالی ff_سمتیہ_fmul_کھڑکی_rvv(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);
خالی ff_سمتیہ_fmul_جوڑو_rvv(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                             ثابت اعشاری *src2, صحیح len);
خالی ff_سمتیہ_fmul_الٹ_rvv(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, صحیح len);
خالی ff_butterflies_float_rvv(اعشاری *v1, اعشاری *v2, صحیح len);
اعشاری ff_scalarproduct_float_rvv(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح len);

خالی ff_سمتیہ_dmul_rvv(دوہرا *dst, ثابت دوہرا *src0, ثابت دوہرا *src1,
                         صحیح len);
خالی ff_سمتیہ_dmac_scalar_rvv(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                صحیح len);
خالی ff_سمتیہ_dmul_scalar_rvv(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                صحیح len);
دوہرا ff_scalarproduct_double_rvv(ثابت دوہرا *v1, ثابت دوہرا *v2,
                                   size_t len);

av_cold خالی ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#اگر HAVE_RVV
    صحیح flags = av_get_cpu_flags();

    اگر (flags & AV_CPU_FLAG_RVB) {
        اگر (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->سمتیہ_fmul = ff_سمتیہ_fmul_rvv;
            fdsp->سمتیہ_fmac_scalar = ff_سمتیہ_fmac_scalar_rvv;
            fdsp->سمتیہ_fmul_scalar = ff_سمتیہ_fmul_scalar_rvv;
            fdsp->سمتیہ_fmul_کھڑکی = ff_سمتیہ_fmul_کھڑکی_rvv;
            fdsp->سمتیہ_fmul_جوڑو = ff_سمتیہ_fmul_جوڑو_rvv;
            fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        اگر (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->سمتیہ_dmul = ff_سمتیہ_dmul_rvv;
            fdsp->سمتیہ_dmac_scalar = ff_سمتیہ_dmac_scalar_rvv;
            fdsp->سمتیہ_dmul_scalar = ff_سمتیہ_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#اگر_ختم
}
