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
#شامل "libavutil/fixed_dsp.h"

خالی ff_سمتیہ_fmul_کھڑکی_scaled_rvv(int16_t *dst, ثابت int32_t *src0,
                                      ثابت int32_t *src1, ثابت int32_t *win,
                                      صحیح len, uint8_t بٹ);
خالی ff_سمتیہ_fmul_کھڑکی_fixed_rvv(int32_t *dst, ثابت int32_t *src0,
                                     ثابت int32_t *src1, ثابت int32_t *win,
                                     صحیح len);
خالی ff_سمتیہ_fmul_fixed_rvv(صحیح *dst, ثابت صحیح *src0, ثابت صحیح *src1,
                              صحیح len);
خالی ff_سمتیہ_fmul_الٹ_fixed_rvv(صحیح *dst, ثابت صحیح *src0,
                                      ثابت صحیح *src1, صحیح len);
خالی ff_سمتیہ_fmul_جوڑو_fixed_rvv(صحیح *dst, ثابت صحیح *src0, ثابت صحیح *src1,
                                  ثابت صحیح *src2, صحیح len);
صحیح ff_scalarproduct_fixed_rvv(ثابت صحیح *v1, ثابت صحیح *v2, صحیح len);
خالی ff_butterflies_fixed_rvv(صحیح *v1, صحیح *v2, صحیح len);

av_cold خالی ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#اگر HAVE_RVV
    صحیح flags = av_get_cpu_flags();

    اگر ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        اگر (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->سمتیہ_fmul_کھڑکی_scaled = ff_سمتیہ_fmul_کھڑکی_scaled_rvv;
            fdsp->سمتیہ_fmul_کھڑکی = ff_سمتیہ_fmul_کھڑکی_fixed_rvv;
        }

        fdsp->سمتیہ_fmul = ff_سمتیہ_fmul_fixed_rvv;
        fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_fixed_rvv;
        fdsp->سمتیہ_fmul_جوڑو = ff_سمتیہ_fmul_جوڑو_fixed_rvv;

        اگر (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#اگر_ختم
}
