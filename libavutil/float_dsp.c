/*
 * Copyright 2005 Balatoni Denes
 * Copyright 2006 Loren Merritt
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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "float_dsp.h"
#അന്തര്ഭാവ "mem.h"

സ്ഥിതം ശൂന്യം vector_fmul_c(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                          പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

സ്ഥിതം ശൂന്യം vector_dmul_c(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src0, സ്ഥിരം ഇരട്ട *src1,
                          പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

സ്ഥിതം ശൂന്യം vector_fmac_scalar_c(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                 പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

സ്ഥിതം ശൂന്യം vector_dmac_scalar_c(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                 പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

സ്ഥിതം ശൂന്യം vector_fmul_scalar_c(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src, ദശാംശം mul,
                                 പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

സ്ഥിതം ശൂന്യം vector_dmul_scalar_c(ഇരട്ട *dst, സ്ഥിരം ഇരട്ട *src, ഇരട്ട mul,
                                 പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

സ്ഥിതം ശൂന്യം vector_fmul_window_c(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                 സ്ഥിരം ദശാംശം *src1, സ്ഥിരം ദശാംശം *win, പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i, j;

    dst  += len;
    win  += len;
    src0 += len;

    വേണ്ടി (i = -len, j = len - 1; i < 0; i++, j--) {
        ദശാംശം s0 = src0[i];
        ദശാംശം s1 = src1[j];
        ദശാംശം wi = win[i];
        ദശാംശം wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

സ്ഥിതം ശൂന്യം vector_fmul_add_c(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0, സ്ഥിരം ദശാംശം *src1,
                              സ്ഥിരം ദശാംശം *src2, പൂർണ്ണസംഖ്യ len){
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

സ്ഥിതം ശൂന്യം vector_fmul_reverse_c(ദശാംശം *dst, സ്ഥിരം ദശാംശം *src0,
                                  സ്ഥിരം ദശാംശം *src1, പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;

    src1 += len-1;
    വേണ്ടി (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

സ്ഥിതം ശൂന്യം butterflies_float_c(ദശാംശം *restrict v1, ദശാംശം *restrict v2,
                                പൂർണ്ണസംഖ്യ len)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < len; i++) {
        ദശാംശം t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

ഇരട്ട ff_scalarproduct_double_c(സ്ഥിരം ഇരട്ട *v1, സ്ഥിരം ഇരട്ട *v2,
                                 size_t len)
{
    ഇരട്ട p = 0.0;

    വേണ്ടി (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    തിരികെ p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(പൂർണ്ണസംഖ്യ bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(വലുപ്പം(AVFloatDSPContext));
    എങ്കിൽ (!fdsp)
        തിരികെ ശൂന്യ;

    fdsp->vector_fmul = vector_fmul_c;
    fdsp->vector_dmul = vector_dmul_c;
    fdsp->vector_fmac_scalar = vector_fmac_scalar_c;
    fdsp->vector_fmul_scalar = vector_fmul_scalar_c;
    fdsp->vector_dmac_scalar = vector_dmac_scalar_c;
    fdsp->vector_dmul_scalar = vector_dmul_scalar_c;
    fdsp->vector_fmul_window = vector_fmul_window_c;
    fdsp->vector_fmul_add = vector_fmul_add_c;
    fdsp->vector_fmul_reverse = vector_fmul_reverse_c;
    fdsp->butterflies_float = butterflies_float_c;
    fdsp->scalarproduct_float = ff_scalarproduct_float_c;
    fdsp->scalarproduct_double = ff_scalarproduct_double_c;

#എങ്കിൽ ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#അല്ലെങ്കിലെങ്കിൽ ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#അല്ലെങ്കിലെങ്കിൽ ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#അല്ലെങ്കിലെങ്കിൽ ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#അല്ലെങ്കിലെങ്കിൽ ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#അല്ലെങ്കിലെങ്കിൽ ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    തിരികെ fdsp;
}
