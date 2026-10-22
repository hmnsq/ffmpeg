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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_PPC_FLOAT_DSP_VSX_H
#وصف_ڪريو AVUTIL_PPC_FLOAT_DSP_VSX_H

فراغ ff_ويڪٽر_fmul_vsx(عائم *dst, ثابت عائم *src0,
                        ثابت عائم *src1, صحيح len);

فراغ ff_ويڪٽر_fmul_دري_vsx(عائم *dst, ثابت عائم *src0,
                               ثابت عائم *src1, ثابت عائم *win,
                               صحيح len);

فراغ ff_ويڪٽر_fmul_جوڙيو_vsx(عائم *dst, ثابت عائم *src0,
                            ثابت عائم *src1, ثابت عائم *src2,
                            صحيح len);

فراغ ff_ويڪٽر_fmul_ابتو_vsx(عائم *dst, ثابت عائم *src0,
                                ثابت عائم *src1, صحيح len);

#جيڪڏهن_پورو /* AVUTIL_PPC_FLOAT_DSP_VSX_H */
