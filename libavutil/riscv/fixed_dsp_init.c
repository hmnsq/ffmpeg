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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/fixed_dsp.h"

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_scaled_rvv(int16_t *dst, ਅਚਲ int32_t *src0,
                                      ਅਚਲ int32_t *src1, ਅਚਲ int32_t *win,
                                      ਪੂਰਨ len, uint8_t ਬਿੱਟ);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_fixed_rvv(int32_t *dst, ਅਚਲ int32_t *src0,
                                     ਅਚਲ int32_t *src1, ਅਚਲ int32_t *win,
                                     ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_fixed_rvv(ਪੂਰਨ *dst, ਅਚਲ ਪੂਰਨ *src0, ਅਚਲ ਪੂਰਨ *src1,
                              ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_fixed_rvv(ਪੂਰਨ *dst, ਅਚਲ ਪੂਰਨ *src0,
                                      ਅਚਲ ਪੂਰਨ *src1, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_fixed_rvv(ਪੂਰਨ *dst, ਅਚਲ ਪੂਰਨ *src0, ਅਚਲ ਪੂਰਨ *src1,
                                  ਅਚਲ ਪੂਰਨ *src2, ਪੂਰਨ len);
ਪੂਰਨ ff_scalarproduct_fixed_rvv(ਅਚਲ ਪੂਰਨ *v1, ਅਚਲ ਪੂਰਨ *v2, ਪੂਰਨ len);
ਖਾਲੀ ff_butterflies_fixed_rvv(ਪੂਰਨ *v1, ਪੂਰਨ *v2, ਪੂਰਨ len);

av_cold ਖਾਲੀ ff_fixed_dsp_init_riscv(AVFixedDSPContext *fdsp)
{
#ਜੇ HAVE_RVV
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ ((flags & AV_CPU_FLAG_RVV_I32) && (flags & AV_CPU_FLAG_RVB)) {
        ਜੇ (flags & AV_CPU_FLAG_RVV_I64) {
            fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_scaled = ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_scaled_rvv;
            fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ = ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_fixed_rvv;
        }

        fdsp->ਸਦਿਸ਼_fmul = ff_ਸਦਿਸ਼_fmul_fixed_rvv;
        fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_fixed_rvv;
        fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ = ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_fixed_rvv;

        ਜੇ (flags & AV_CPU_FLAG_RVV_I64)
            fdsp->scalarproduct_fixed = ff_scalarproduct_fixed_rvv;

        fdsp->butterflies_fixed = ff_butterflies_fixed_rvv;
    }
#ਜੇ_ਅੰਤ
}
