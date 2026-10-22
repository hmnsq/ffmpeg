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

#अन्तर्भाव "config.h"
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "float_dsp.h"
#अन्तर्भाव "mem.h"

स्थिर शून्य vector_fmul_c(दशांश *dst, स्थिरांक दशांश *src0, स्थिरांक दशांश *src1,
                          पूर्णांक len)
{
    पूर्णांक i;
    साठी (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

स्थिर शून्य vector_dmul_c(द्विगुण *dst, स्थिरांक द्विगुण *src0, स्थिरांक द्विगुण *src1,
                          पूर्णांक len)
{
    पूर्णांक i;
    साठी (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

स्थिर शून्य vector_fmac_scalar_c(दशांश *dst, स्थिरांक दशांश *src, दशांश mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    साठी (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

स्थिर शून्य vector_dmac_scalar_c(द्विगुण *dst, स्थिरांक द्विगुण *src, द्विगुण mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    साठी (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

स्थिर शून्य vector_fmul_scalar_c(दशांश *dst, स्थिरांक दशांश *src, दशांश mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    साठी (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

स्थिर शून्य vector_dmul_scalar_c(द्विगुण *dst, स्थिरांक द्विगुण *src, द्विगुण mul,
                                 पूर्णांक len)
{
    पूर्णांक i;
    साठी (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

स्थिर शून्य vector_fmul_window_c(दशांश *dst, स्थिरांक दशांश *src0,
                                 स्थिरांक दशांश *src1, स्थिरांक दशांश *win, पूर्णांक len)
{
    पूर्णांक i, j;

    dst  += len;
    win  += len;
    src0 += len;

    साठी (i = -len, j = len - 1; i < 0; i++, j--) {
        दशांश s0 = src0[i];
        दशांश s1 = src1[j];
        दशांश wi = win[i];
        दशांश wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

स्थिर शून्य vector_fmul_add_c(दशांश *dst, स्थिरांक दशांश *src0, स्थिरांक दशांश *src1,
                              स्थिरांक दशांश *src2, पूर्णांक len){
    पूर्णांक i;

    साठी (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

स्थिर शून्य vector_fmul_reverse_c(दशांश *dst, स्थिरांक दशांश *src0,
                                  स्थिरांक दशांश *src1, पूर्णांक len)
{
    पूर्णांक i;

    src1 += len-1;
    साठी (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

स्थिर शून्य butterflies_float_c(दशांश *restrict v1, दशांश *restrict v2,
                                पूर्णांक len)
{
    पूर्णांक i;

    साठी (i = 0; i < len; i++) {
        दशांश t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

द्विगुण ff_scalarproduct_double_c(स्थिरांक द्विगुण *v1, स्थिरांक द्विगुण *v2,
                                 माप_प्रकार len)
{
    द्विगुण p = 0.0;

    साठी (माप_प्रकार i = 0; i < len; i++)
        p += v1[i] * v2[i];

    परत p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(पूर्णांक bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(आकार(AVFloatDSPContext));
    जर (!fdsp)
        परत रिक्त;

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

#जर ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#किंवाजर ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#किंवाजर ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#किंवाजर ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#किंवाजर ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#किंवाजर ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    परत fdsp;
}
