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

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/float_dsp.h"
#अन्तर्भाव "float_dsp_arm.h"

शून्य ff_सदिशम्_fmul_neon(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1, पूर्णाङ्क len);

शून्य ff_सदिशम्_fmac_scalar_neon(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                                पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_scalar_neon(भिन्न *dst, ध्रुव भिन्न *src, भिन्न mul,
                                पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_गवाक्षः_neon(भिन्न *dst, ध्रुव भिन्न *src0,
                                ध्रुव भिन्न *src1, ध्रुव भिन्न *win, पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_सङ्कलय_neon(भिन्न *dst, ध्रुव भिन्न *src0, ध्रुव भिन्न *src1,
                             ध्रुव भिन्न *src2, पूर्णाङ्क len);

शून्य ff_सदिशम्_fmul_reverse_neon(भिन्न *dst, ध्रुव भिन्न *src0,
                                 ध्रुव भिन्न *src1, पूर्णाङ्क len);

शून्य ff_butterflies_float_neon(भिन्न *v1, भिन्न *v2, पूर्णाङ्क len);

भिन्न ff_scalarproduct_float_neon(ध्रुव भिन्न *v1, ध्रुव भिन्न *v2, पूर्णाङ्क len);

av_cold शून्य ff_float_dsp_init_neon(AVFloatDSPContext *fdsp)
{
    fdsp->सदिशम्_fmul = ff_सदिशम्_fmul_neon;
    fdsp->सदिशम्_fmac_scalar = ff_सदिशम्_fmac_scalar_neon;
    fdsp->सदिशम्_fmul_scalar = ff_सदिशम्_fmul_scalar_neon;
    fdsp->सदिशम्_fmul_गवाक्षः = ff_सदिशम्_fmul_गवाक्षः_neon;
    fdsp->सदिशम्_fmul_सङ्कलय    = ff_सदिशम्_fmul_सङ्कलय_neon;
    fdsp->सदिशम्_fmul_reverse = ff_सदिशम्_fmul_reverse_neon;
    fdsp->butterflies_float = ff_butterflies_float_neon;
    fdsp->scalarproduct_float = ff_scalarproduct_float_neon;
}
