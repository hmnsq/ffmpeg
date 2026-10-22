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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "float_dsp.h"
#અન્તર્ભાવ "mem.h"

સ્થિર શૂન્ય vector_fmul_c(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                          પૂર્ણાંક len)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

સ્થિર શૂન્ય vector_dmul_c(દ્વિગુણ *dst, અચલ દ્વિગુણ *src0, અચલ દ્વિગુણ *src1,
                          પૂર્ણાંક len)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i];
}

સ્થિર શૂન્ય vector_fmac_scalar_c(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                 પૂર્ણાંક len)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

સ્થિર શૂન્ય vector_dmac_scalar_c(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                                 પૂર્ણાંક len)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < len; i++)
        dst[i] += src[i] * mul;
}

સ્થિર શૂન્ય vector_fmul_scalar_c(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                 પૂર્ણાંક len)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

સ્થિર શૂન્ય vector_dmul_scalar_c(દ્વિગુણ *dst, અચલ દ્વિગુણ *src, દ્વિગુણ mul,
                                 પૂર્ણાંક len)
{
    પૂર્ણાંક i;
    માટે (i = 0; i < len; i++)
        dst[i] = src[i] * mul;
}

સ્થિર શૂન્ય vector_fmul_window_c(દશાંશ *dst, અચલ દશાંશ *src0,
                                 અચલ દશાંશ *src1, અચલ દશાંશ *win, પૂર્ણાંક len)
{
    પૂર્ણાંક i, j;

    dst  += len;
    win  += len;
    src0 += len;

    માટે (i = -len, j = len - 1; i < 0; i++, j--) {
        દશાંશ s0 = src0[i];
        દશાંશ s1 = src1[j];
        દશાંશ wi = win[i];
        દશાંશ wj = win[j];
        dst[i] = s0 * wj - s1 * wi;
        dst[j] = s0 * wi + s1 * wj;
    }
}

સ્થિર શૂન્ય vector_fmul_add_c(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                              અચલ દશાંશ *src2, પૂર્ણાંક len){
    પૂર્ણાંક i;

    માટે (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[i] + src2[i];
}

સ્થિર શૂન્ય vector_fmul_reverse_c(દશાંશ *dst, અચલ દશાંશ *src0,
                                  અચલ દશાંશ *src1, પૂર્ણાંક len)
{
    પૂર્ણાંક i;

    src1 += len-1;
    માટે (i = 0; i < len; i++)
        dst[i] = src0[i] * src1[-i];
}

સ્થિર શૂન્ય butterflies_float_c(દશાંશ *restrict v1, દશાંશ *restrict v2,
                                પૂર્ણાંક len)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < len; i++) {
        દશાંશ t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

દ્વિગુણ ff_scalarproduct_double_c(અચલ દ્વિગુણ *v1, અચલ દ્વિગુણ *v2,
                                 size_t len)
{
    દ્વિગુણ p = 0.0;

    માટે (size_t i = 0; i < len; i++)
        p += v1[i] * v2[i];

    પાછા p;
}

av_cold AVFloatDSPContext *avpriv_float_dsp_alloc(પૂર્ણાંક bit_exact)
{
    AVFloatDSPContext *fdsp = av_mallocz(કદ(AVFloatDSPContext));
    જો (!fdsp)
        પાછા ખાલી;

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

#જો ARCH_AARCH64
    ff_float_dsp_init_aarch64(fdsp);
#અથવાજો ARCH_ARM
    ff_float_dsp_init_arm(fdsp);
#અથવાજો ARCH_PPC
    ff_float_dsp_init_ppc(fdsp, bit_exact);
#અથવાજો ARCH_RISCV
    ff_float_dsp_init_riscv(fdsp);
#અથવાજો ARCH_X86 && HAVE_X86ASM
    ff_float_dsp_init_x86(fdsp);
#અથવાજો ARCH_MIPS
    ff_float_dsp_init_mips(fdsp);
#endif
    પાછા fdsp;
}
