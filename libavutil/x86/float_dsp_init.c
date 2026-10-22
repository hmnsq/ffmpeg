/*
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
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/float_dsp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_sse(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                        ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_avx(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                        ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_sse2(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src0, ਅਚਲ ਦੁੱਗਣਾ *src1,
                         ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_avx(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src0, ਅਚਲ ਦੁੱਗਣਾ *src1,
                        ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmac_scalar_sse(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                               ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmac_scalar_avx(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                               ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmac_scalar_fma3(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                                ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_scalar_sse(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src, ਦਸ਼ਮਲਵ mul,
                               ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_dmac_scalar_sse2(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_dmac_scalar_avx(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                               ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_dmac_scalar_fma3(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src, ਦੁੱਗਣਾ mul,
                                ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_scalar_sse2(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src,
                                ਦੁੱਗਣਾ mul, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_dmul_scalar_avx(ਦੁੱਗਣਾ *dst, ਅਚਲ ਦੁੱਗਣਾ *src,
                               ਦੁੱਗਣਾ mul, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_sse(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                               ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਅਚਲ ਦਸ਼ਮਲਵ *win, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_sse(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                            ਅਚਲ ਦਸ਼ਮਲਵ *src2, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_avx(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                            ਅਚਲ ਦਸ਼ਮਲਵ *src2, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_fma3(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0, ਅਚਲ ਦਸ਼ਮਲਵ *src1,
                             ਅਚਲ ਦਸ਼ਮਲਵ *src2, ਪੂਰਨ len);

ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_sse(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_avx(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len);
ਖਾਲੀ ff_ਸਦਿਸ਼_fmul_ਉਲਟ_avx2(ਦਸ਼ਮਲਵ *dst, ਅਚਲ ਦਸ਼ਮਲਵ *src0,
                                 ਅਚਲ ਦਸ਼ਮਲਵ *src1, ਪੂਰਨ len);

ਦਸ਼ਮਲਵ ff_scalarproduct_float_sse(ਅਚਲ ਦਸ਼ਮਲਵ *v1, ਅਚਲ ਦਸ਼ਮਲਵ *v2, ਪੂਰਨ ਕ੍ਰਮ);
ਦਸ਼ਮਲਵ ff_scalarproduct_float_fma3(ਅਚਲ ਦਸ਼ਮਲਵ *v1, ਅਚਲ ਦਸ਼ਮਲਵ *v2, ਪੂਰਨ ਕ੍ਰਮ);

ਦੁੱਗਣਾ ff_scalarproduct_double_sse2(ਅਚਲ ਦੁੱਗਣਾ *v1, ਅਚਲ ਦੁੱਗਣਾ *v2, size_t ਕ੍ਰਮ);
ਦੁੱਗਣਾ ff_scalarproduct_double_avx(ਅਚਲ ਦੁੱਗਣਾ *v1, ਅਚਲ ਦੁੱਗਣਾ *v2, size_t ਕ੍ਰਮ);

ਖਾਲੀ ff_butterflies_float_sse(ਦਸ਼ਮਲਵ *ਸੀਮਿਤ src0, ਦਸ਼ਮਲਵ *ਸੀਮਿਤ src1, ਪੂਰਨ len);

av_cold ਖਾਲੀ ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (EXTERNAL_SSE(cpu_flags)) {
        fdsp->ਸਦਿਸ਼_fmul = ff_ਸਦਿਸ਼_fmul_sse;
        fdsp->ਸਦਿਸ਼_fmac_scalar = ff_ਸਦਿਸ਼_fmac_scalar_sse;
        fdsp->ਸਦਿਸ਼_fmul_scalar = ff_ਸਦਿਸ਼_fmul_scalar_sse;
        fdsp->ਸਦਿਸ਼_fmul_ਖਿੜਕੀ = ff_ਸਦਿਸ਼_fmul_ਖਿੜਕੀ_sse;
        fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ    = ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_sse;
        fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    ਜੇ (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->ਸਦਿਸ਼_dmul = ff_ਸਦਿਸ਼_dmul_sse2;
        fdsp->ਸਦਿਸ਼_dmac_scalar = ff_ਸਦਿਸ਼_dmac_scalar_sse2;
        fdsp->ਸਦਿਸ਼_dmul_scalar = ff_ਸਦਿਸ਼_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    ਜੇ (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->ਸਦਿਸ਼_fmul = ff_ਸਦਿਸ਼_fmul_avx;
        fdsp->ਸਦਿਸ਼_dmul = ff_ਸਦਿਸ਼_dmul_avx;
        fdsp->ਸਦਿਸ਼_fmac_scalar = ff_ਸਦਿਸ਼_fmac_scalar_avx;
        fdsp->ਸਦਿਸ਼_dmul_scalar = ff_ਸਦਿਸ਼_dmul_scalar_avx;
        fdsp->ਸਦਿਸ਼_dmac_scalar = ff_ਸਦਿਸ਼_dmac_scalar_avx;
        fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ    = ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_avx;
        fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    ਜੇ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->ਸਦਿਸ਼_fmul_ਉਲਟ = ff_ਸਦਿਸ਼_fmul_ਉਲਟ_avx2;
    }
    ਜੇ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->ਸਦਿਸ਼_fmac_scalar = ff_ਸਦਿਸ਼_fmac_scalar_fma3;
        fdsp->ਸਦਿਸ਼_fmul_ਜੋੜੋ    = ff_ਸਦਿਸ਼_fmul_ਜੋੜੋ_fma3;
        fdsp->ਸਦਿਸ਼_dmac_scalar = ff_ਸਦਿਸ਼_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
