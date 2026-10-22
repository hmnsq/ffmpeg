/*
 * Copyright (c) 2006 Luca Barbato <lu_zero@gentoo.org>
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

#ifndef AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H
#define AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H

வெறுமை ff_vector_fmul_altivec(தசம *dst, மாறிலி தசம *src0,
                            மாறிலி தசம *src1, முழு len);

வெறுமை ff_vector_fmul_window_altivec(தசம *dst, மாறிலி தசம *src0,
                                   மாறிலி தசம *src1, மாறிலி தசம *win,
                                   முழு len);

வெறுமை ff_vector_fmul_add_altivec(தசம *dst, மாறிலி தசம *src0,
                                மாறிலி தசம *src1, மாறிலி தசம *src2,
                                முழு len);

வெறுமை ff_vector_fmul_reverse_altivec(தசம *dst, மாறிலி தசம *src0,
                                    மாறிலி தசம *src1, முழு len);

#endif /* AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H */
