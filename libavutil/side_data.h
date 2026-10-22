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

#اگر_غیر_تعریف_شدہ AVUTIL_SIDE_ڈیٹا_H
#تعریف_کرو AVUTIL_SIDE_ڈیٹا_H

#شامل "buffer.h"
#شامل "frame.h"

AVFrame_Side_ڈیٹا *ff_چوکھٹا_side_ڈیٹا_جوڑو_from_buf(AVFrame_Side_ڈیٹا ***sd,
                                                 صحیح *nb_sd,
                                                 شمار AVFrame_Side_ڈیٹا_Type type,
                                                 AVBufferRef *buf);

#اگر_ختم // AVUTIL_SIDE_DATA_H
