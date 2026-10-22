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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/float_dsp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_neon(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                         ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmac_scalar_neon(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_scalar_neon(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_scalar_neon(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_neon(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਅਚਲ ਦਸ਼ਮਲਵ *win, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_neon(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                             ਅਚਲ ਦਸ਼ਮਲਵ *src2, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_neon(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                 ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len);

ਖਾਲੀ ff_butterflies_float_neon(ਦਸ਼ਮਲਵ *v1, ਦਸ਼ਮਲਵ *v2, ਪੂਰਨ len);

ਦਸ਼ਮਲਵ ff_scalarproduct_float_neon(ਅਚਲ ਦਸ਼ਮਲਵ *v1, ਅਚਲ ਦਸ਼ਮਲਵ *v2, ਪੂਰਨ len);

av_cold ਖਾਲੀ ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (have_neon(cpu_flags)) {
        fdsp->butterflies_float   = ff_butterflies_float_neon;
        fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
        fdsp->ਸਦਿਸ਼_dmul_scalar  = ff_ਸਦਿਸ਼_dmul_scalar_neon;
        fdsp->ਸਦਿਸ਼_fmul         = ff_ਸਦਿਸ਼_fmul_neon;
        fdsp->ਸਦਿਸ਼_fmac_scalar  = ff_ਸਦਿਸ਼_fmac_scalar_neon;
        fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ     = ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_neon;
        fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_neon;
        fdsp->ਸਦਿਸ਼_fmul_scalar  = ff_ਸਦਿਸ਼_fmul_scalar_neon;
        fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ  = ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_neon;
    }
}
