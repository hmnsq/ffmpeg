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

#ifndef AVUTIL_SIDE_তথ্য_H
#define AVUTIL_SIDE_তথ্য_H

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "frame.h"

AVFrame_Side_তথ্য *ff_frame_side_তথ্য_add_from_buf(AVFrame_Side_তথ্য ***sd,
                                                 পূর্ণসংখ্যা *nb_sd,
                                                 গণনা AVFrame_Side_তথ্য_Type type,
                                                 AVBufferRef *buf);

#endif // AVUTIL_SIDE_DATA_H
