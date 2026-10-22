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

#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/float_dsp.h"
#അന്തര്ഭാവ "cpu.h"

ശൂന്യം ff_vector_fmul_sse(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                        പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_avx(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                        പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_dmul_sse2(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src0, സ്ഥിരം ഇരട്ട *src1,
                         പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_dmul_avx(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src0, സ്ഥിരം ഇരട്ട *src1,
                        പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmac_scalar_sse(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                               പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmac_scalar_avx(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                               പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmac_scalar_fma3(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_scalar_sse(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                               പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_dmac_scalar_sse2(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_dmac_scalar_avx(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                               പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_dmac_scalar_fma3(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_dmul_scalar_sse2(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src,
                                ഇരട്ട mul, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_dmul_scalar_avx(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src,
                               ഇരട്ട mul, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_window_sse(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                               സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_add_sse(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                            സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_add_avx(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                            സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_add_fma3(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                             സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_reverse_sse(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_reverse_avx(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_reverse_avx2(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                 സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);

ദശാംശം ff_scalarproduct_float_sse(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ order);
ദശാംശം ff_scalarproduct_float_fma3(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ order);

ഇരട്ട ff_scalarproduct_double_sse2(സ്ഥിരം ഇരട്ട *v1, സ്ഥിരം ഇരട്ട *v2, size_t order);
ഇരട്ട ff_scalarproduct_double_avx(സ്ഥിരം ഇരട്ട *v1, സ്ഥിരം ഇരട്ട *v2, size_t order);

ശൂന്യം ff_butterflies_float_sse(ദശാംശം *restrict src0, ദശാംശം *restrict src1, പൂർണ്ണസംഖ്യ len);

av_cold ശൂന്യം ff_float_dsp_init_x86(AVFloatDSPContext *fdsp)
{
    പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();

    എങ്കിൽ (EXTERNAL_SSE(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_sse;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_sse;
        fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_sse;
        fdsp->vector_fmul_window = ff_vector_fmul_window_sse;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_sse;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_sse;
        fdsp->scalarproduct_float = ff_scalarproduct_float_sse;
        fdsp->butterflies_float   = ff_butterflies_float_sse;
    }
    എങ്കിൽ (EXTERNAL_SSE2(cpu_flags)) {
        fdsp->vector_dmul = ff_vector_dmul_sse2;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_sse2;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_sse2;
        fdsp->scalarproduct_double = ff_scalarproduct_double_sse2;
    }
    എങ്കിൽ (EXTERNAL_AVX_FAST(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_avx;
        fdsp->vector_dmul = ff_vector_dmul_avx;
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_avx;
        fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_avx;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_avx;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_avx;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx;
        fdsp->scalarproduct_double = ff_scalarproduct_double_avx;
    }
    എങ്കിൽ (EXTERNAL_AVX2_FAST(cpu_flags)) {
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_avx2;
    }
    എങ്കിൽ (EXTERNAL_FMA3_FAST(cpu_flags)) {
        fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_fma3;
        fdsp->vector_fmul_add    = ff_vector_fmul_add_fma3;
        fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_fma3;
        fdsp->scalarproduct_float = ff_scalarproduct_float_fma3;
    }
}
