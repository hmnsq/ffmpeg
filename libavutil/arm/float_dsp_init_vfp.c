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

#অন্তর্ভাব "libavutil/attributes.h"
#অন্তর্ভাব "libavutil/float_dsp.h"
#অন্তর্ভাব "cpu.h"
#অন্তর্ভাব "float_dsp_arm.h"

শূন্য ff_vector_fmul_vfp(দশমিক *dst, ধ্রুবক দশমিক *src0, ধ্রুবক দশমিক *src1,
                        পূর্ণসংখ্যা len);

শূন্য ff_vector_fmul_window_vfp(দশমিক *dst, ধ্রুবক দশমিক *src0,
                               ধ্রুবক দশমিক *src1, ধ্রুবক দশমিক *win, পূর্ণসংখ্যা len);

শূন্য ff_vector_fmul_reverse_vfp(দশমিক *dst, ধ্রুবক দশমিক *src0,
                                ধ্রুবক দশমিক *src1, পূর্ণসংখ্যা len);

শূন্য ff_butterflies_float_vfp(দশমিক *restrict v1, দশমিক *restrict v2, পূর্ণসংখ্যা len);

av_cold শূন্য ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, পূর্ণসংখ্যা cpu_flags)
{
    যদি (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    যদি (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
