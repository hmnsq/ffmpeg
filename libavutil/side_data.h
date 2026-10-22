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

#اگر_تعریف_نشده AVUTIL_SIDE_داده_H
#تعریف_کن AVUTIL_SIDE_داده_H

#ضمن "buffer.h"
#ضمن "frame.h"

AVFrame_Side_داده *ff_قاب_side_داده_جمع_کن_from_buf(AVFrame_Side_داده ***sd,
                                                 صحيح *nb_sd,
                                                 تعداد AVFrame_Side_داده_Type type,
                                                 AVBufferRef *buf);

#پایان_اگر // AVUTIL_SIDE_DATA_H
