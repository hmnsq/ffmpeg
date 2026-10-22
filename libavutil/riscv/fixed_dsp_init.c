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
#ضمن "libavutil/fixed_dsp.h"

فراغ ff_ويڪٽر_fmul_دري_scaled_rvv(int16_t *dst, ثابت int32_t *src0,
                                      ثابت int32_t *src1, ثابت int32_t *win,
                                      صحيح len, uint8_t بٽ);
فراغ ff_ويڪٽر_fmul_دري_fixed_rvv(int32_t *dst, ثابت int32_t *src0,
                                     ثابت int32_t *src1, ثابت int32_t *win,
                                     صحيح len);
فراغ ff_ويڪٽر_fmul_fixed_rvv(صحيح *dst, ثابت صحيح *src0, ثابت صحيح *src1,
                              صحيح len);
فراغ ff_ويڪٽر_fmul_ابتو_fixed_rvv(صحيح *dst, ثابت صحيح *src0,
                                      ثابت صحيح *src1, صحيح len);
فراغ ff_ويڪٽر_fmul_جوڙيو_fixed_rvv(صحيح *dst, ثابت صحيح *src0, ثابت صحيح *src1,
                                  ثابت صحيح *src2, صحيح len);
صحيح ff_scalarproduct_fixed_rvv(ثابت صحيح *v1, ثابت صحيح *v2, صحيح len);
فراغ ff_butterflies_fixed_rvv(صحيح *v1, صحيح *v2, صحيح len);

av_cold فراغ ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#إذا HAVE_RVV
    صحيح flags = av_get_cpu_flags();

    إذا ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        إذا (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->ويڪٽر_fmul_دري_scaled = ff_ويڪٽر_fmul_دري_scaled_rvv;
            fdsp->ويڪٽر_fmul_دري = ff_ويڪٽر_fmul_دري_fixed_rvv;
        }

        fdsp->ويڪٽر_fmul = ff_ويڪٽر_fmul_fixed_rvv;
        fdsp->ويڪٽر_fmul_ابتو = ff_ويڪٽر_fmul_ابتو_fixed_rvv;
        fdsp->ويڪٽر_fmul_جوڙيو = ff_ويڪٽر_fmul_جوڙيو_fixed_rvv;

        إذا (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#جيڪڏهن_پورو
}
