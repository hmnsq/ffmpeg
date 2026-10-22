/*
 * Copyright (c) 2012
 *      MIPS Technologies, Inc., California.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the MIPS Technologies, Inc., nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE MIPS TECHNOLOGIES, INC. ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE MIPS TECHNOLOGIES, INC. BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Author:  Nedeljko Babic (nedeljko.babic imgtec com)
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

#अन्तर्भाव "common.h"
#अन्तर्भाव "fixed_dsp.h"
#अन्तर्भाव "mem.h"

स्थिर शून्य vector_fmul_add_c(पूर्णाङ्क *dst, ध्रुव पूर्णाङ्क *src0, ध्रुव पूर्णाङ्क *src1, ध्रुव पूर्णाङ्क *src2, पूर्णाङ्क len){
    पूर्णाङ्क i;
    int64_t accu;

    प्रति (i=0; i<len; i++) {
        accu = (int64_t)src0[i] * src1[i];
        dst[i] = src2[i] + (पूर्णाङ्क)((accu + 0x40000000) >> 31);
    }
}

स्थिर शून्य vector_fmul_reverse_c(पूर्णाङ्क *dst, ध्रुव पूर्णाङ्क *src0, ध्रुव पूर्णाङ्क *src1, पूर्णाङ्क len)
{
    पूर्णाङ्क i;
    int64_t accu;

    src1 += len-1;
    प्रति (i=0; i<len; i++) {
        accu = (int64_t)src0[i] * src1[-i];
        dst[i] = (पूर्णाङ्क)((accu+0x40000000) >> 31);
    }
}

स्थिर शून्य vector_fmul_window_scaled_c(int16_t *dst, ध्रुव int32_t *src0,
                                       ध्रुव int32_t *src1, ध्रुव int32_t *win,
                                       पूर्णाङ्क len, uint8_t bits)
{
    int32_t s0, s1, wi, wj, i,j, round;

    dst += len;
    win += len;
    src0+= len;
    round = bits? 1 << (bits-1) : 0;

    प्रति (i=-len, j=len-1; i<0; i++, j--) {
        s0 = src0[i];
        s1 = src1[j];
        wi = win[i];
        wj = win[j];
        dst[i] = av_clip_int16(((((int64_t)s0*wj - (int64_t)s1*wi + 0x40000000) >> 31) + round) >> bits);
        dst[j] = av_clip_int16(((((int64_t)s0*wi + (int64_t)s1*wj + 0x40000000) >> 31) + round) >> bits);
    }
}

स्थिर शून्य vector_fmul_window_c(int32_t *dst, ध्रुव int32_t *src0,
                                       ध्रुव int32_t *src1, ध्रुव int32_t *win,
                                       पूर्णाङ्क len)
{
    int32_t s0, s1, wi, wj, i, j;

    dst += len;
    win += len;
    src0+= len;

    प्रति (i=-len, j=len-1; i<0; i++, j--) {
        s0 = src0[i];
        s1 = src1[j];
        wi = win[i];
        wj = win[j];
        dst[i] = ((int64_t)s0*wj - (int64_t)s1*wi + 0x40000000) >> 31;
        dst[j] = ((int64_t)s0*wi + (int64_t)s1*wj + 0x40000000) >> 31;
    }
}

स्थिर शून्य vector_fmul_c(पूर्णाङ्क *dst, ध्रुव पूर्णाङ्क *src0, ध्रुव पूर्णाङ्क *src1, पूर्णाङ्क len)
{
    पूर्णाङ्क i;
    int64_t accu;

    प्रति (i = 0; i < len; i++){
        accu = (int64_t)src0[i] * src1[i];
        dst[i] = (पूर्णाङ्क)((accu+0x40000000) >> 31);
    }
}

स्थिर पूर्णाङ्क scalarproduct_fixed_c(ध्रुव पूर्णाङ्क *v1, ध्रुव पूर्णाङ्क *v2, पूर्णाङ्क len)
{
    /** p is initialized with 0x40000000 so that the proper rounding will occur
      * at the end */
    int64_t p = 0x40000000;
    पूर्णाङ्क i;

    प्रति (i = 0; i < len; i++)
        p += (int64_t)v1[i] * v2[i];

    प्रत्यागम (पूर्णाङ्क)(p >> 31);
}

स्थिर शून्य butterflies_fixed_c(पूर्णाङ्क *restrict v1s, पूर्णाङ्क *restrict v2, पूर्णाङ्क len)
{
    पूर्णाङ्क i;
    unsigned पूर्णाङ्क *v1 = v1s;

    प्रति (i = 0; i < len; i++){
        पूर्णाङ्क t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

AVFixedDSPContext * avpriv_alloc_fixed_dsp(पूर्णाङ्क bit_exact)
{
    AVFixedDSPContext * fdsp = av_malloc(परिमाण(AVFixedDSPContext));

    जइ (!fdsp)
        प्रत्यागम रिक्त;

    fdsp->vector_fmul_window_scaled = vector_fmul_window_scaled_c;
    fdsp->vector_fmul_window = vector_fmul_window_c;
    fdsp->vector_fmul = vector_fmul_c;
    fdsp->vector_fmul_add = vector_fmul_add_c;
    fdsp->vector_fmul_reverse = vector_fmul_reverse_c;
    fdsp->butterflies_fixed = butterflies_fixed_c;
    fdsp->scalarproduct_fixed = scalarproduct_fixed_c;

#जइ ARCH_RISCV
    ff_fixed_dsp_init_riscv(fdsp);
#नोचेद्यदि ARCH_X86 && HAVE_X86ASM
    ff_fixed_dsp_init_x86(fdsp);
#endif

    प्रत्यागम fdsp;
}
