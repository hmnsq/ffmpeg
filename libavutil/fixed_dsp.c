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

#అన్తర్భావ "common.h"
#అన్తర్భావ "fixed_dsp.h"
#అన్తర్భావ "mem.h"

స్థిర శూన్య సదిశ_fmul_కూడు_c(పూర్ణాంకం *dst, స్థిరరాశి పూర్ణాంకం *src0, స్థిరరాశి పూర్ణాంకం *src1, స్థిరరాశి పూర్ణాంకం *src2, పూర్ణాంకం len){
    పూర్ణాంకం i;
    int64_t accu;

    కొరకు (i=0; i<len; i++) {
        accu = (int64_t)src0[i] * src1[i];
        dst[i] = src2[i] + (పూర్ణాంకం)((accu + 0x40000000) >> 31);
    }
}

స్థిర శూన్య సదిశ_fmul_తిరగేయి_c(పూర్ణాంకం *dst, స్థిరరాశి పూర్ణాంకం *src0, స్థిరరాశి పూర్ణాంకం *src1, పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    int64_t accu;

    src1 += len-1;
    కొరకు (i=0; i<len; i++) {
        accu = (int64_t)src0[i] * src1[-i];
        dst[i] = (పూర్ణాంకం)((accu+0x40000000) >> 31);
    }
}

స్థిర శూన్య సదిశ_fmul_కిటికీ_scaled_c(int16_t *dst, స్థిరరాశి int32_t *src0,
                                       స్థిరరాశి int32_t *src1, స్థిరరాశి int32_t *win,
                                       పూర్ణాంకం len, uint8_t బిట్లు)
{
    int32_t s0, s1, wi, wj, i,j, round;

    dst += len;
    win += len;
    src0+= len;
    round = బిట్లు? 1 << (బిట్లు-1) : 0;

    కొరకు (i=-len, j=len-1; i<0; i++, j--) {
        s0 = src0[i];
        s1 = src1[j];
        wi = win[i];
        wj = win[j];
        dst[i] = av_clip_int16(((((int64_t)s0*wj - (int64_t)s1*wi + 0x40000000) >> 31) + round) >> బిట్లు);
        dst[j] = av_clip_int16(((((int64_t)s0*wi + (int64_t)s1*wj + 0x40000000) >> 31) + round) >> బిట్లు);
    }
}

స్థిర శూన్య సదిశ_fmul_కిటికీ_c(int32_t *dst, స్థిరరాశి int32_t *src0,
                                       స్థిరరాశి int32_t *src1, స్థిరరాశి int32_t *win,
                                       పూర్ణాంకం len)
{
    int32_t s0, s1, wi, wj, i, j;

    dst += len;
    win += len;
    src0+= len;

    కొరకు (i=-len, j=len-1; i<0; i++, j--) {
        s0 = src0[i];
        s1 = src1[j];
        wi = win[i];
        wj = win[j];
        dst[i] = ((int64_t)s0*wj - (int64_t)s1*wi + 0x40000000) >> 31;
        dst[j] = ((int64_t)s0*wi + (int64_t)s1*wj + 0x40000000) >> 31;
    }
}

స్థిర శూన్య సదిశ_fmul_c(పూర్ణాంకం *dst, స్థిరరాశి పూర్ణాంకం *src0, స్థిరరాశి పూర్ణాంకం *src1, పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    int64_t accu;

    కొరకు (i = 0; i < len; i++){
        accu = (int64_t)src0[i] * src1[i];
        dst[i] = (పూర్ణాంకం)((accu+0x40000000) >> 31);
    }
}

స్థిర పూర్ణాంకం scalarproduct_fixed_c(స్థిరరాశి పూర్ణాంకం *v1, స్థిరరాశి పూర్ణాంకం *v2, పూర్ణాంకం len)
{
    /** p is initialized with 0x40000000 so that the proper rounding will occur
      * at the end */
    int64_t p = 0x40000000;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < len; i++)
        p += (int64_t)v1[i] * v2[i];

    తిరిగి (పూర్ణాంకం)(p >> 31);
}

స్థిర శూన్య butterflies_fixed_c(పూర్ణాంకం *పరిమిత v1s, పూర్ణాంకం *పరిమిత v2, పూర్ణాంకం len)
{
    పూర్ణాంకం i;
    గుర్తులేని పూర్ణాంకం *v1 = v1s;

    కొరకు (i = 0; i < len; i++){
        పూర్ణాంకం t = v1[i] - v2[i];
        v1[i] += v2[i];
        v2[i] = t;
    }
}

AVFixedDSPContext * avpriv_alloc_fixed_dsp(పూర్ణాంకం బిట్టు_exact)
{
    AVFixedDSPContext * fdsp = av_malloc(పరిమాణం(AVFixedDSPContext));

    ఒకవేళ (!fdsp)
        తిరిగి ఖాళీ;

    fdsp->సదిశ_fmul_కిటికీ_scaled = సదిశ_fmul_కిటికీ_scaled_c;
    fdsp->సదిశ_fmul_కిటికీ = సదిశ_fmul_కిటికీ_c;
    fdsp->సదిశ_fmul = సదిశ_fmul_c;
    fdsp->సదిశ_fmul_కూడు = సదిశ_fmul_కూడు_c;
    fdsp->సదిశ_fmul_తిరగేయి = సదిశ_fmul_తిరగేయి_c;
    fdsp->butterflies_fixed = butterflies_fixed_c;
    fdsp->scalarproduct_fixed = scalarproduct_fixed_c;

#ఒకవేళ ARCH_RISCV
    ff_fixed_dsp_init_riscv(fdsp);
#లేదావేళ ARCH_X86 && HAVE_X86ASM
    ff_fixed_dsp_init_x86(fdsp);
#అయితే_ముగింపు

    తిరిగి fdsp;
}
