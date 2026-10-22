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

#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/float_dsp.h"

ശൂന്യം ff_vector_fmul_rvv(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                         പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmac_scalar_rvv(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_scalar_rvv(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_window_rvv(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_add_rvv(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                             സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_fmul_reverse_rvv(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                 സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_butterflies_float_rvv(ദശാംശം *v1, ദശാംശം *v2, പൂർണ്ണസംഖ്യ len);
ദശാംശം ff_scalarproduct_float_rvv(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_dmul_rvv(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src0, സ്ഥിരം ഇരട്ട *src1,
                         പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_dmac_scalar_rvv(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                പൂർണ്ണസംഖ്യ len);
ശൂന്യം ff_vector_dmul_scalar_rvv(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                പൂർണ്ണസംഖ്യ len);
ഇരട്ട ff_scalarproduct_double_rvv(സ്ഥിരം ഇരട്ട *v1, സ്ഥിരം ഇരട്ട *v2,
                                   size_t len);

av_cold ശൂന്യം ff_float_dsp_init_riscv(AVFloatDSPContext *fdsp)
{
#എങ്കിൽ HAVE_RVV
    പൂർണ്ണസംഖ്യ flags = av_get_cpu_flags();

    എങ്കിൽ (flags & AV_CPU_FLAG_RVB) {
        എങ്കിൽ (flags & AV_CPU_FLAG_RVV_F32) {
            fdsp->vector_fmul = ff_vector_fmul_rvv;
            fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_rvv;
            fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_rvv;
            fdsp->vector_fmul_window = ff_vector_fmul_window_rvv;
            fdsp->vector_fmul_add = ff_vector_fmul_add_rvv;
            fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_rvv;
            fdsp->butterflies_float = ff_butterflies_float_rvv;
            fdsp->scalarproduct_float = ff_scalarproduct_float_rvv;
        }

        എങ്കിൽ (flags & AV_CPU_FLAG_RVV_F64) {
            fdsp->vector_dmul = ff_vector_dmul_rvv;
            fdsp->vector_dmac_scalar = ff_vector_dmac_scalar_rvv;
            fdsp->vector_dmul_scalar = ff_vector_dmul_scalar_rvv;
            fdsp->scalarproduct_double = ff_scalarproduct_double_rvv;
        }
    }
#endif
}
