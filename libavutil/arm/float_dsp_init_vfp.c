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

#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/float_dsp.h"
#अन्तर्भाव "cpu.h"
#अन्तर्भाव "float_dsp_arm.h"

शून्य ff_vector_fmul_vfp(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                        पूर्णाङ्क len);

शून्य ff_vector_fmul_window_vfp(भिन्न *dst, ध्रुव भिन्न *src0,
                               ध्रुव भिन्न *src1, ध्रुव भिन्न *win, पूर्णाङ्क len);

शून्य ff_vector_fmul_reverse_vfp(भिन्न *dst, ध्रुव भिन्न *src0,
                                ध्रुव भिन्न *src1, पूर्णाङ्क len);

शून्य ff_butterflies_float_vfp(भिन्न *restrict v1, भिन्न *restrict v2, पूर्णाङ्क len);

av_cold शून्य ff_float_dsp_init_vfp(AVFloatDSPContext *fdsp, पूर्णाङ्क cpu_flags)
{
    जइ (have_vfp_vm(cpu_flags)) {
        fdsp->vector_fmul = ff_vector_fmul_vfp;
        fdsp->vector_fmul_window = ff_vector_fmul_window_vfp;
    }
    fdsp->vector_fmul_reverse = ff_vector_fmul_reverse_vfp;
    जइ (have_vfp_vm(cpu_flags))
        fdsp->butterflies_float = ff_butterflies_float_vfp;
}
