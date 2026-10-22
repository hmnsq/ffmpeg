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

#اگر_تعریف_نشده AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H
#تعریف_کن AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H

فراغ ff_وکتور_fmul_altivec(عائم *dst, ثابت عائم *src0,
                            ثابت عائم *src1, صحيح len);

فراغ ff_وکتور_fmul_پنجره_altivec(عائم *dst, ثابت عائم *src0,
                                   ثابت عائم *src1, ثابت عائم *win,
                                   صحيح len);

فراغ ff_وکتور_fmul_جمع_کن_altivec(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, ثابت عائم *src2,
                                صحيح len);

فراغ ff_وکتور_fmul_معکوس_altivec(عائم *dst, ثابت عائم *src0,
                                    ثابت عائم *src1, صحيح len);

#پایان_اگر /* AVUTIL_PPC_FLOAT_DSP_ALTIVEC_H */
