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

#ضمن <stdint.h>

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/float_dsp.h"

فراغ ff_وکتور_fmul_rvv(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                         صحيح len);
فراغ ff_وکتور_fmac_scalar_rvv(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);
فراغ ff_وکتور_fmul_scalar_rvv(عائم *dst, ثابت عائم *src, عائم mul,
                                صحيح len);
فراغ ff_وکتور_fmul_پنجره_rvv(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, ثابت عائم *win, صحيح len);
فراغ ff_وکتور_fmul_جمع_کن_rvv(عائم *dst, ثابت عائم *src0, ثابت عائم *src1,
                             ثابت عائم *src2, صحيح len);
فراغ ff_وکتور_fmul_معکوس_rvv(عائم *dst, ثابت عائم *src0,
                                 ثابت عائم *src1, صحيح len);
فراغ ff_butterflies_float_rvv(عائم *v1, عائم *v2, صحيح len);
عائم ff_scalarproduct_float_rvv(ثابت عائم *v1, ثابت عائم *v2, صحيح len);

فراغ ff_وکتور_dmul_rvv(مزدوج *dst, ثابت مزدوج *src0, ثابت مزدوج *src1,
                         صحيح len);
فراغ ff_وکتور_dmac_scalar_rvv(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                صحيح len);
فراغ ff_وکتور_dmul_scalar_rvv(مزدوج *dst, ثابت مزدوج *src, مزدوج mul,
                                صحيح len);
مزدوج ff_scalarproduct_double_rvv(ثابت مزدوج *v1, ثابت مزدوج *v2,
                                   size_t len);

av_cold فراغ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#إذا HAVE_RVV
    صحيح flags = av_get_cpu_flags();

    إذا (flags & AV_CPU_FLAG_RVB) {
        إذا (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->وکتور_fmul = ff_وکتور_fmul_rvv;
            fdsp->وکتور_fmac_scalar = ff_وکتور_fmac_scalar_rvv;
            fdsp->وکتور_fmul_scalar = ff_وکتور_fmul_scalar_rvv;
            fdsp->وکتور_fmul_پنجره = ff_وکتور_fmul_پنجره_rvv;
            fdsp->وکتور_fmul_جمع_کن = ff_وکتور_fmul_جمع_کن_rvv;
            fdsp->وکتور_fmul_معکوس = ff_وکتور_fmul_معکوس_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        إذا (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->وکتور_dmul = ff_وکتور_dmul_rvv;
            fdsp->وکتور_dmac_scalar = ff_وکتور_dmac_scalar_rvv;
            fdsp->وکتور_dmul_scalar = ff_وکتور_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#پایان_اگر
}
