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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "float_dsp.h"
#அந்தர்பாவ "mem.h"

நிலையான வெறுமை vector_fmul_c(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                          முழு len)
{
    முழு i;
    க்கு (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

நிலையான வெறுமை vector_dmul_c(இரட்டை *dst, மாறிலி இரட்டை *src0, மாறிலி இரட்டை *src1,
                          முழு len)
{
    முழு i;
    க்கு (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

நிலையான வெறுமை vector_fmac_scalar_c(தசம *dst, மாறிலி தசம *src, தசம mul,
                                 முழு len)
{
    முழு i;
    க்கு (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

நிலையான வெறுமை vector_dmac_scalar_c(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                 முழு len)
{
    முழு i;
    க்கு (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

நிலையான வெறுமை vector_fmul_scalar_c(தசம *dst, மாறிலி தசம *src, தசம mul,
                                 முழு len)
{
    முழு i;
    க்கு (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

நிலையான வெறுமை vector_dmul_scalar_c(இரட்டை *dst, மாறிலி இரட்டை *src, இரட்டை mul,
                                 முழு len)
{
    முழு i;
    க்கு (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

நிலையான வெறுமை vector_fmul_window_c(தசம *dst, மாறிலி தசம *src0,
                                 மாறிலி தசம *src1, மாறிலி தசம *win, முழு len)
{
    முழு i, j;

    dst  += len;
    win  += len;
    src0 += len;

    க்கு (i = -len, j = len - 1; i < 0; i++, j--) {
        தசம s0 = src0[i];
        தசம s1 = src1[j];
        தசம wi = win[i];
        தசம wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

நிலையான வெறுமை vector_fmul_add_c(தசம *dst, மாறிலி தசம *src0, மாறிலி தசம *src1,
                              மாறிலி தசம *src2, முழு len){
    முழு i;

    க்கு (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

நிலையான வெறுமை vector_fmul_reverse_c(தசம *dst, மாறிலி தசம *src0,
                                  மாறிலி தசம *src1, முழு len)
{
    முழு i;

    src1 += len-1;
    க்கு (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

நிலையான வெறுமை butterflies_float_c(தசம *restrict v1, தசம *restrict v2,
                                முழு len)
{
    முழு i;

    க்கு (i = 0; i < len; i++) {
        தசம t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

இரட்டை ff_scalarproduct_double_c(மாறிலி இரட்டை *v1, மாறிலி இரட்டை *v2,
                                 size_t len)
{
    இரட்டை p = 0.0;

    க்கு (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    திரும்பு p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(முழு bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(அளவு(AVFloatDSPContext));
    எனில் (!fdsp)
        திரும்பு வெற்று;

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

#எனில் ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#அல்லதெனில் ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#அல்லதெனில் ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#அல்லதெனில் ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#அல்லதெனில் ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#அல்லதெனில் ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    திரும்பு fdsp;
}
