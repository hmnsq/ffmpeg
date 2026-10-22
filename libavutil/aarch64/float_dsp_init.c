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

#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "libavutil/attributes.h"
#അന്തര്ഭാവ "libavutil/cpu.h"
#അന്തര്ഭാവ "libavutil/float_dsp.h"
#അന്തര്ഭാവ "cpu.h"

ശൂന്യം ff_vector_fmul_neon(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                         പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmac_scalar_neon(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_scalar_neon(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_dmul_scalar_neon(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_window_neon(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_add_neon(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                             സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_vector_fmul_reverse_neon(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                 സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len);

ശൂന്യം ff_butterflies_float_neon(ദശാംശം *v1, ദശാംശം *v2, പൂർണ്ണസംഖ്യ len);

ദശാംശം ff_scalarproduct_float_neon(സ്ഥിരം ദശാംശം *v1, സ്ഥിരം ദശാംശം *v2, പൂർണ്ണസംഖ്യ len);

av_cold ശൂന്യം ff_float_dsp_init_aarch64(AVFloatDSPContext *fdsp)
{
    പൂർണ്ണസംഖ്യ cpu_flags = av_get_cpu_flags();

    എങ്കിൽ (have_neon(cpu_flags)) {
        fdsp->butterflies_float   = ff_butterflies_float_neon;
        fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
        fdsp->vector_dmul_scalar  = ff_vector_dmul_scalar_neon;
        fdsp->vector_fmul         = ff_vector_fmul_neon;
        fdsp->vector_fmac_scalar  = ff_vector_fmac_scalar_neon;
        fdsp->vector_fmul_add     = ff_vector_fmul_add_neon;
        fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_neon;
        fdsp->vector_fmul_scalar  = ff_vector_fmul_scalar_neon;
        fdsp->vector_fmul_window  = ff_vector_fmul_window_neon;
    }
}
