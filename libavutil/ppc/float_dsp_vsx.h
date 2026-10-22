/*
 * Copyright (c) 2015 Luca Barbato <lu_zero@gentoo.org>
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

#अगर_अघोषित AVUTIL_PPC_FLOAT_DSP_VSX_H
#घोषणा AVUTIL_PPC_FLOAT_DSP_VSX_H

व्योम ff_vector_fmul_vsx(भग्न *dst, स्थिर भग्न *src0,
                        स्थिर भग्न *src1, पूर्णांक len);

व्योम ff_vector_fmul_window_vsx(भग्न *dst, स्थिर भग्न *src0,
                               स्थिर भग्न *src1, स्थिर भग्न *win,
                               पूर्णांक len);

व्योम ff_vector_fmul_add_vsx(भग्न *dst, स्थिर भग्न *src0,
                            स्थिर भग्न *src1, स्थिर भग्न *src2,
                            पूर्णांक len);

व्योम ff_vector_fmul_reverse_vsx(भग्न *dst, स्थिर भग्न *src0,
                                स्थिर भग्न *src1, पूर्णांक len);

#पूर्ण_अगर /* AVUTIL_PPC_FLOAT_DSP_VSX_H */
