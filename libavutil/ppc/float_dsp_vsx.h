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

#ifndef AVUTIL_PPC_FLOAT_DSP_VSX_H
#define AVUTIL_PPC_FLOAT_DSP_VSX_H

تهی ff_vector_fmul_vsx(اعشاری *dst, ثابت اعشاری *src0,
                        ثابت اعشاری *src1, صحیح len);

تهی ff_vector_fmul_window_vsx(اعشاری *dst, ثابت اعشاری *src0,
                               ثابت اعشاری *src1, ثابت اعشاری *win,
                               صحیح len);

تهی ff_vector_fmul_add_vsx(اعشاری *dst, ثابت اعشاری *src0,
                            ثابت اعشاری *src1, ثابت اعشاری *src2,
                            صحیح len);

تهی ff_vector_fmul_reverse_vsx(اعشاری *dst, ثابت اعشاری *src0,
                                ثابت اعشاری *src1, صحیح len);

#endif /* AVUTIL_PPC_FLOAT_DSP_VSX_H */
