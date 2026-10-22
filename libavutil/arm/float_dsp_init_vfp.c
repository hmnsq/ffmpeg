/*
 * Copyright (c) 2008 Siarhei Siamashka <ssvb@users.sourceforge.net>
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

#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/float_dsp.h"
#ଅନ୍ତର୍ଭାଵ "cpu.h"
#ଅନ୍ତର୍ଭାଵ "float_dsp_arm.h"

ଶୂନ୍ୟ ff_vector_fmul_vfp(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0, ଅଚଳ ଦଶମିକ *src1,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_window_vfp(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                               ଅଚଳ ଦଶମିକ *src1, ଅଚଳ ଦଶମିକ *win, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_vector_fmul_reverse_vfp(ଦଶମିକ *dst, ଅଚଳ ଦଶମିକ *src0,
                                ଅଚଳ ଦଶମିକ *src1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

ଶୂନ୍ୟ ff_butterflies_float_vfp(ଦଶମିକ *restrict v1, ଦଶମିକ *restrict v2, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len);

av_cold ଶୂନ୍ୟ ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags)
{
    ଯଦି (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    ଯଦି (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
