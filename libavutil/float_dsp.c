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

#समावेश "config.h"
#समावेश "attributes.h"
#समावेश "float_dsp.h"
#समावेश "mem.h"

अटल व्योम vector_fmul_c(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                          पूर्णांक len)
{
    पूर्णांक i;
    क्रम (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

अटल व्योम vector_dmul_c(द्विगुन *dst, स्थिर द्विगुन *src0, स्थिर द्विगुन *src1,
                          पूर्णांक len)
{
    पूर्णांक i;
    क्रम (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

अटल व्योम vector_fmac_scalar_c(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    क्रम (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

अटल व्योम vector_dmac_scalar_c(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    क्रम (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

अटल व्योम vector_fmul_scalar_c(भग्न *dst, स्थिर भग्न *src, भग्न mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    क्रम (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

अटल व्योम vector_dmul_scalar_c(द्विगुन *dst, स्थिर द्विगुन *src, द्विगुन mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    क्रम (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

अटल व्योम vector_fmul_window_c(भग्न *dst, स्थिर भग्न *src0,
                                 स्थिर भग्न *src1, स्थिर भग्न *win, पूर्णांक len)
{
    पूर्णांक i, j;

    dst  += len;
    win  += len;
    src0 += len;

    क्रम (i = -len, j = len - 1; i < 0; i++, j--) {
        भग्न s0 = src0[i];
        भग्न s1 = src1[j];
        भग्न wi = win[i];
        भग्न wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

अटल व्योम vector_fmul_add_c(भग्न *dst, स्थिर भग्न *src0, स्थिर भग्न *src1,
                              स्थिर भग्न *src2, पूर्णांक len){
    पूर्णांक i;

    क्रम (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

अटल व्योम vector_fmul_reverse_c(भग्न *dst, स्थिर भग्न *src0,
                                  स्थिर भग्न *src1, पूर्णांक len)
{
    पूर्णांक i;

    src1 += len-1;
    क्रम (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

अटल व्योम butterflies_float_c(भग्न *restrict v1, भग्न *restrict v2,
                                पूर्णांक len)
{
    पूर्णांक i;

    क्रम (i = 0; i < len; i++) {
        भग्न t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

द्विगुन ff_scalarproduct_double_c(स्थिर द्विगुन *v1, स्थिर द्विगुन *v2,
                                 माप_प्रकार len)
{
    द्विगुन p = 0.0;

    क्रम (माप_प्रकार i = 0; i < len; i++)
        p += v1[i] * v2[i];

    वापस p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(पूर्णांक bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(माप(AVFloatDSPContext));
    अगर (!fdsp)
        वापस शून्य;

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

#अगर ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#या_अगर ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#या_अगर ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#या_अगर ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#या_अगर ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#या_अगर ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#पूर्ण_अगर
    वापस fdsp;
}
