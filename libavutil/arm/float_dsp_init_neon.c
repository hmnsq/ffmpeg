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

#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/float_dsp.h"
#ଅନ୍ତର୍ଭାଵ "float_dsp_arm.h"

ଶୂନ୍ୟ ff_vector_fmul_neon(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmac_scalar_neon(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_scalar_neon(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src, ଦଶମିକ mul,
                                ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_window_neon(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                ଅଚଳ ଦଶମିକ *src1, ଅଚଳ ଦଶମିକ *win, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_add_neon(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                             ଅଚଳ ଦଶମିକ *src2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_reverse_neon(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                 ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_butterflies_float_neon(ଦଶମିକ *v1, ଦଶମିକ *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଦଶମିକ ff_scalarproduct_float_neon(ଅଚଳ ଦଶମିକ *v1, ଅଚଳ ଦଶମିକ *v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

av_cold ଶୂନ୍ୟ ff_float_dsp_init_neon(AVFloatDSPContext *fdsp)
{
    fdsp->vector_fmul = ff_vector_fmul_neon;
    fdsp->vector_fmac_scalar = ff_vector_fmac_scalar_neon;
    fdsp->vector_fmul_scalar = ff_vector_fmul_scalar_neon;
    fdsp->vector_fmul_window = ff_vector_fmul_window_neon;
    fdsp->vector_fmul_add    = ff_vector_fmul_add_neon;
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_neon;
    fdsp->butterflies_float = ff_butterflies_float_neon;
    fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
}
