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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/float_dsp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "float_dsp_arm.h"

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_vfp(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                        ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_vfp(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                               ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਅਚਲ ਦਸ਼ਮਲਵ *win, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_vfp(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len);

ਖਾਲੀ ff_butterflies_float_vfp(ਦਸ਼ਮਲਵ *ਸੀਮਿਤ v1, ਦਸ਼ਮਲਵ *ਸੀਮਿਤ v2, ਪੂਰਨ len);

av_cold ਖਾਲੀ ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, ਪੂਰਨ cpu_flags)
{
    ਜੇ (have_vfp_vm(cpu_flags)) {
        fdsp->ਸਦਿਸ਼_fmul = ff_ਸਦਿਸ਼_fmul_vfp;
        fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ = ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_vfp;
    }
    fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_vfp;
    ਜੇ (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
