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

#شامل "libavutil/attributes.h"
#شامل "libavutil/cpu.h"
#شامل "libavutil/float_dsp.h"
#شامل "cpu.h"

خالی ff_سمتیہ_fmul_sse(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                        صحیح len);
خالی ff_سمتیہ_fmul_avx(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                        صحیح len);

خالی ff_سمتیہ_dmul_sse2(دوہرا *dst, ثابت دوہرا *src0, ثابت دوہرا *src1,
                         صحیح len);
خالی ff_سمتیہ_dmul_avx(دوہرا *dst, ثابت دوہرا *src0, ثابت دوہرا *src1,
                        صحیح len);

خالی ff_سمتیہ_fmac_scalar_sse(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                               صحیح len);
خالی ff_سمتیہ_fmac_scalar_avx(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                               صحیح len);
خالی ff_سمتیہ_fmac_scalar_fma3(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                                صحیح len);

خالی ff_سمتیہ_fmul_scalar_sse(اعشاری *dst, ثابت اعشاری *src, اعشاری mul,
                               صحیح len);

خالی ff_سمتیہ_dmac_scalar_sse2(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                صحیح len);
خالی ff_سمتیہ_dmac_scalar_avx(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                               صحیح len);
خالی ff_سمتیہ_dmac_scalar_fma3(دوہرا *dst, ثابت دوہرا *src, دوہرا mul,
                                صحیح len);

خالی ff_سمتیہ_dmul_scalar_sse2(دوہرا *dst, ثابت دوہرا *src,
                                دوہرا mul, صحیح len);
خالی ff_سمتیہ_dmul_scalar_avx(دوہرا *dst, ثابت دوہرا *src,
                               دوہرا mul, صحیح len);

خالی ff_سمتیہ_fmul_کھڑکی_sse(اعشاری *dst, ثابت اعشاری *src0,
                               ثابت اعشاری *src1, ثابت اعشاری *win, صحیح len);

خالی ff_سمتیہ_fmul_جوڑو_sse(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                            ثابت اعشاری *src2, صحیح len);
خالی ff_سمتیہ_fmul_جوڑو_avx(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                            ثابت اعشاری *src2, صحیح len);
خالی ff_سمتیہ_fmul_جوڑو_fma3(اعشاری *dst, ثابت اعشاری *src0, ثابت اعشاری *src1,
                             ثابت اعشاری *src2, صحیح len);

خالی ff_سمتیہ_fmul_الٹ_sse(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);
خالی ff_سمتیہ_fmul_الٹ_avx(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);
خالی ff_سمتیہ_fmul_الٹ_avx2(اعشاری *dst, ثابت اعشاری *src0,
                                 ثابت اعشاری *src1, صحیح len);

اعشاری ff_scalarproduct_float_sse(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح ترتیب);
اعشاری ff_scalarproduct_float_fma3(ثابت اعشاری *v1, ثابت اعشاری *v2, صحیح ترتیب);

دوہرا ff_scalarproduct_double_sse2(ثابت دوہرا *v1, ثابت دوہرا *v2, size_t ترتیب);
دوہرا ff_scalarproduct_double_avx(ثابت دوہرا *v1, ثابت دوہرا *v2, size_t ترتیب);

خالی ff_butterflies_float_sse(اعشاری *محدود src0, اعشاری *محدود src1, صحیح len);

av_cold خالی ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    صحیح cpu_flags = av_get_cpu_flags();

    اگر (EXTERNAL_SSE(cpu_flags)) {
        fdsp->سمتیہ_fmul = ff_سمتیہ_fmul_sse;
        fdsp->سمتیہ_fmac_scalar = ff_سمتیہ_fmac_scalar_sse;
        fdsp->سمتیہ_fmul_scalar = ff_سمتیہ_fmul_scalar_sse;
        fdsp->سمتیہ_fmul_کھڑکی = ff_سمتیہ_fmul_کھڑکی_sse;
        fdsp->سمتیہ_fmul_جوڑو    = ff_سمتیہ_fmul_جوڑو_sse;
        fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    اگر (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->سمتیہ_dmul = ff_سمتیہ_dmul_sse2;
        fdsp->سمتیہ_dmac_scalar = ff_سمتیہ_dmac_scalar_sse2;
        fdsp->سمتیہ_dmul_scalar = ff_سمتیہ_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    اگر (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->سمتیہ_fmul = ff_سمتیہ_fmul_avx;
        fdsp->سمتیہ_dmul = ff_سمتیہ_dmul_avx;
        fdsp->سمتیہ_fmac_scalar = ff_سمتیہ_fmac_scalar_avx;
        fdsp->سمتیہ_dmul_scalar = ff_سمتیہ_dmul_scalar_avx;
        fdsp->سمتیہ_dmac_scalar = ff_سمتیہ_dmac_scalar_avx;
        fdsp->سمتیہ_fmul_جوڑو    = ff_سمتیہ_fmul_جوڑو_avx;
        fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    اگر (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->سمتیہ_fmul_الٹ = ff_سمتیہ_fmul_الٹ_avx2;
    }
    اگر (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->سمتیہ_fmac_scalar = ff_سمتیہ_fmac_scalar_fma3;
        fdsp->سمتیہ_fmul_جوڑو    = ff_سمتیہ_fmul_جوڑو_fma3;
        fdsp->سمتیہ_dmac_scalar = ff_سمتیہ_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
