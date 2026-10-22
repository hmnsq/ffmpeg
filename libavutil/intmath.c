/*
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

#समावेश "intmath.h"

/* undef these to get the function prototypes from common.h */
#अघोषित av_log2
#अघोषित av_log2_16bit
#समावेश "common.h"

पूर्णांक av_log2(अचिन्हित v)
{
    वापस ff_log2(v);
}

पूर्णांक av_log2_16bit(अचिन्हित v)
{
    वापस ff_log2_16bit(v);
}
