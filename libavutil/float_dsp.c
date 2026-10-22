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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "attributes.h"
#অন্তর্ভাৱ "float_dsp.h"
#অন্তর্ভাৱ "mem.h"

স্থির শূন্য vector_fmul_c(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0, ধ্রুৱ ভিন্ন *src1,
                          পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

স্থির শূন্য vector_dmul_c(দ্ৱিগুণ *dst, ধ্রুৱ দ্ৱিগুণ *src0, ধ্রুৱ দ্ৱিগুণ *src1,
                          পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

স্থির শূন্য vector_fmac_scalar_c(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src, ভিন্ন mul,
                                 পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

স্থির শূন্য vector_dmac_scalar_c(দ্ৱিগুণ *dst, ধ্রুৱ দ্ৱিগুণ *src, দ্ৱিগুণ mul,
                                 পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

স্থির শূন্য vector_fmul_scalar_c(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src, ভিন্ন mul,
                                 পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

স্থির শূন্য vector_dmul_scalar_c(দ্ৱিগুণ *dst, ধ্রুৱ দ্ৱিগুণ *src, দ্ৱিগুণ mul,
                                 পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;
    বাবে (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

স্থির শূন্য vector_fmul_window_c(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0,
                                 ধ্রুৱ ভিন্ন *src1, ধ্রুৱ ভিন্ন *win, পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i, j;

    dst  += len;
    win  += len;
    src0 += len;

    বাবে (i = -len, j = len - 1; i < 0; i++, j--) {
        ভিন্ন s0 = src0[i];
        ভিন্ন s1 = src1[j];
        ভিন্ন wi = win[i];
        ভিন্ন wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

স্থির শূন্য vector_fmul_add_c(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0, ধ্রুৱ ভিন্ন *src1,
                              ধ্রুৱ ভিন্ন *src2, পূর্ণাঙ্ক len){
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

স্থির শূন্য vector_fmul_reverse_c(ভিন্ন *dst, ধ্রুৱ ভিন্ন *src0,
                                  ধ্রুৱ ভিন্ন *src1, পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;

    src1 += len-1;
    বাবে (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

স্থির শূন্য butterflies_float_c(ভিন্ন *restrict v1, ভিন্ন *restrict v2,
                                পূর্ণাঙ্ক len)
{
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < len; i++) {
        ভিন্ন t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

দ্ৱিগুণ ff_scalarproduct_double_c(ধ্রুৱ দ্ৱিগুণ *v1, ধ্রুৱ দ্ৱিগুণ *v2,
                                 size_t len)
{
    দ্ৱিগুণ p = 0.0;

    বাবে (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    ঘূৰাই p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(পূর্ণাঙ্ক bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(পরিমাণ(AVFloatDSPContext));
    যদি (!fdsp)
        ঘূৰাই রিক্ত;

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

#যদি ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#নোচেদ্যদি ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#নোচেদ্যদি ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#নোচেদ্যদি ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#নোচেদ্যদি ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#নোচেদ্যদি ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    ঘূৰাই fdsp;
}
