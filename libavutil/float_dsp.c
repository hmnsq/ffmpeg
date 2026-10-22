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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "float_dsp.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

ସ୍ଥିର ଶୂନ୍ୟ vector_fmul_c(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ସ୍ଥିର ଶୂନ୍ୟ vector_dmul_c(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src0, ଅଚଳ ଦ୍ୱିଗୁଣ *src1,
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

ସ୍ଥିର ଶୂନ୍ୟ vector_fmac_scalar_c(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ସ୍ଥିର ଶୂନ୍ୟ vector_dmac_scalar_c(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

ସ୍ଥିର ଶୂନ୍ୟ vector_fmul_scalar_c(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ସ୍ଥିର ଶୂନ୍ୟ vector_dmul_scalar_c(ଦ୍ୱିଗୁଣ *dst, ଅଚଳ ଦ୍ୱିଗୁଣ *src, ଦ୍ୱିଗୁଣ mul,
                                 ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

ସ୍ଥିର ଶୂନ୍ୟ vector_fmul_window_c(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                 ଅଚଳ ଦଶମିକ *src1, ଅଚଳ ଦଶମିକ *win, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;

    dst  += len;
    win  += len;
    src0 += len;

    ପାଇଁ (i = -len, j = len - 1; i < 0; i++, j--) {
        ଦଶମିକ s0 = src0[i];
        ଦଶମିକ s1 = src1[j];
        ଦଶମିକ wi = win[i];
        ଦଶମିକ wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ vector_fmul_add_c(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                              ଅଚଳ ଦଶମିକ *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len){
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

ସ୍ଥିର ଶୂନ୍ୟ vector_fmul_reverse_c(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                  ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    src1 += len-1;
    ପାଇଁ (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

ସ୍ଥିର ଶୂନ୍ୟ butterflies_float_c(ଦଶମିକ *restrict v1, ଦଶମିକ *restrict v2,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < len; i++) {
        ଦଶମିକ t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

ଦ୍ୱିଗୁଣ ff_scalarproduct_double_c(ଅଚଳ ଦ୍ୱିଗୁଣ *v1, ଅଚଳ ଦ୍ୱିଗୁଣ *v2,
                                 size_t len)
{
    ଦ୍ୱିଗୁଣ p = 0.0;

    ପାଇଁ (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ଫେରନ୍ତୁ p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(ପୂର୍ଣ୍ଣସଂଖ୍ୟା bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(ଆକାର(AVFloatDSPContext));
    ଯଦି (!fdsp)
        ଫେରନ୍ତୁ ଖାଲି;

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

#ଯଦି ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#ନଚେତଯଦି ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#ନଚେତଯଦି ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#ନଚେତଯଦି ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#ନଚେତଯଦି ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#ନଚେତଯଦି ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    ଫେରନ୍ତୁ fdsp;
}
