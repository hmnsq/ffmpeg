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

#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "libavutil/attributes.h"
#અન્તર્ભાવ "libavutil/float_dsp.h"
#અન્તર્ભાવ "float_dsp_arm.h"

શૂન્ય ff_vector_fmul_neon(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1, પૂર્ણાંક len);

શૂન્ય ff_vector_fmac_scalar_neon(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_scalar_neon(દશાંશ *dst, અચલ દશાંશ *src, દશાંશ mul,
                                પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_window_neon(દશાંશ *dst, અચલ દશાંશ *src0,
                                અચલ દશાંશ *src1, અચલ દશાંશ *win, પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_add_neon(દશાંશ *dst, અચલ દશાંશ *src0, અચલ દશાંશ *src1,
                             અચલ દશાંશ *src2, પૂર્ણાંક len);

શૂન્ય ff_vector_fmul_reverse_neon(દશાંશ *dst, અચલ દશાંશ *src0,
                                 અચલ દશાંશ *src1, પૂર્ણાંક len);

શૂન્ય ff_butterflies_float_neon(દશાંશ *v1, દશાંશ *v2, પૂર્ણાંક len);

દશાંશ ff_scalarproduct_float_neon(અચલ દશાંશ *v1, અચલ દશાંશ *v2, પૂર્ણાંક len);

av_cold શૂન્ય ff_float_dsp_init_neon(AVFloatDSPContext *fdsp)
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
