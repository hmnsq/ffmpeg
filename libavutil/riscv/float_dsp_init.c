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
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/float_dsp.h"

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_rvv(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                         ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmac_scalar_rvv(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_scalar_rvv(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_rvv(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਅਚਲ ਦਸ਼ਮਲਵ *win, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_rvv(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                             ਅਚਲ ਦਸ਼ਮਲਵ *src2, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_rvv(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                 ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len);
ਖਾਲੀ ff_butterflies_float_rvv(ਦਸ਼ਮਲਵ *v1, ਦਸ਼ਮਲਵ *v2, ਪੂਰਨ len);
ਦਸ਼ਮਲਵ ff_scalarproduct_float_rvv(ਅਚਲ ਦਸ਼ਮਲਵ *v1, ਅਚਲ ਦਸ਼ਮਲਵ *v2, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_rvv(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src0, ਅਚਲ ਦੁੱਗਣਾ *src1,
                         ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_dmac_scalar_rvv(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_scalar_rvv(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                ਪੂਰਨ len);
ਦੁੱਗਣਾ ff_scalarproduct_double_rvv(ਅਚਲ ਦੁੱਗਣਾ *v1, ਅਚਲ ਦੁੱਗਣਾ *v2,
                                   size_t len);

av_cold ਖਾਲੀ ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#ਜੇ HAVE_RVV
    ਪੂਰਨ flags = av_get_cpu_flags();

    ਜੇ (flags & AV_CPU_FLAG_RVB) {
        ਜੇ (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->ਸਦਿਸ਼_fmul = ff_ਸਦਿਸ਼_fmul_rvv;
            fdsp->ਸਦਿਸ਼_fmac_scalar = ff_ਸਦਿਸ਼_fmac_scalar_rvv;
            fdsp->ਸਦਿਸ਼_fmul_scalar = ff_ਸਦਿਸ਼_fmul_scalar_rvv;
            fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ = ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_rvv;
            fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ = ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_rvv;
            fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        ਜੇ (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->ਸਦਿਸ਼_dmul = ff_ਸਦਿਸ਼_dmul_rvv;
            fdsp->ਸਦਿਸ਼_dmac_scalar = ff_ਸਦਿਸ਼_dmac_scalar_rvv;
            fdsp->ਸਦਿਸ਼_dmul_scalar = ff_ਸਦਿਸ਼_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#ਜੇ_ਅੰਤ
}
