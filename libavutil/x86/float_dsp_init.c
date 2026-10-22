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

#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/cpu.h"
#અન્તર્ભાવ "libavutil/float_dsp.h"
#અન્તર્ભાવ "cpu.h"

શૂન્ય ff_vector_fmul_sse(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                        પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_avx(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                        પૂર્ણાંક len);

શૂન્ય ff_vector_dmul_sse2(દ્વિગુણ *dst, અચલ દ્વિગુણ *src0, અચલ દ્વિગુણ *src1,
                         પૂર્ણાંક len);
શૂન્ય ff_vector_dmul_avx(દ્વિગુણ *dst, અચલ દ્વિગુણ *src0, અચલ દ્વિગુણ *src1,
                        પૂર્ણાંક len);

શૂન્ય ff_vector_fmac_scalar_sse(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                               પૂર્ણાંક len);
શૂન્ય ff_vector_fmac_scalar_avx(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                               પૂર્ણાંક len);
શૂન્ય ff_vector_fmac_scalar_fma3(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_scalar_sse(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                               પૂર્ણાંક len);

શૂન્ય ff_vector_dmac_scalar_sse2(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                                પૂર્ણાંક len);
શૂન્ય ff_vector_dmac_scalar_avx(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                               પૂર્ણાંક len);
શૂન્ય ff_vector_dmac_scalar_fma3(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                                પૂર્ણાંક len);

શૂન્ય ff_vector_dmul_scalar_sse2(દ્વિગુણ *dst, અચલ દ્વિગુણ *src,
                                દ્વિગુણ mul, પૂર્ણાંક len);
શૂન્ય ff_vector_dmul_scalar_avx(દ્વિગુણ *dst, અચલ દ્વિગુણ *src,
                               દ્વિગુણ mul, પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_window_sse(દશાંશ *dst, અચલ દશાંશ *src0,
                               અચલ દશાંશ *src1, અચલ દશાંશ *win, પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_add_sse(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                            અચલ દશાંશ *src2, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_add_avx(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                            અચલ દશાંશ *src2, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_add_fma3(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                             અચલ દશાંશ *src2, પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_reverse_sse(દશાંશ *dst, અચલ દશાંશ *src0,
                                અચલ દશાંશ *src1, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_reverse_avx(દશાંશ *dst, અચલ દશાંશ *src0,
                                અચલ દશાંશ *src1, પૂર્ણાંક len);
શૂન્ય ff_vector_fmul_reverse_avx2(દશાંશ *dst, અચલ દશાંશ *src0,
                                 અચલ દશાંશ *src1, પૂર્ણાંક len);

દશાંશ ff_scalarproduct_float_sse(અચલ દશાંશ *v1, અચલ દશાંશ *v2, પૂર્ણાંક order);
દશાંશ ff_scalarproduct_float_fma3(અચલ દશાંશ *v1, અચલ દશાંશ *v2, પૂર્ણાંક order);

દ્વિગુણ ff_scalarproduct_double_sse2(અચલ દ્વિગુણ *v1, અચલ દ્વિગુણ *v2, size_t order);
દ્વિગુણ ff_scalarproduct_double_avx(અચલ દ્વિગુણ *v1, અચલ દ્વિગુણ *v2, size_t order);

શૂન્ય ff_butterflies_float_sse(દશાંશ *restrict src0, દશાંશ *restrict src1, પૂર્ણાંક len);

av_cold શૂન્ય ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    પૂર્ણાંક cpu_flags = av_get_cpu_flags();

    જો (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    જો (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    જો (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    જો (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    જો (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
