/*
 * Copyright 2023 Elias Carotti <eliascrt at amazon dot it>
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

#अन्तर्भाव <string.h>

#अन्तर्भाव "avstring.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "video_hint.h"

AVVideoHint *av_video_hint_alloc(माप_प्रकार nb_rects,
                                 माप_प्रकार *out_size)
{
    संरचना TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    अचर माप_प्रकार rect_offset = दुरत्व(संरचना TestStruct, rect);
    माप_प्रकार size = rect_offset;
    AVVideoHint *hint;

    *out_size = 0;
    यदि (nb_rects > (SIZE_MAX - size) / परिमाण(AVVideoRect))
        फर्काऊ रिक्त;
    size += परिमाण(AVVideoRect) * nb_rects;

    hint = av_mallocz(size);
    यदि (!hint)
        फर्काऊ रिक्त;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_size   = परिमाण(AVVideoRect);

    *out_size = size;

    फर्काऊ hint;
}

AVVideoHint *av_video_hint_create_side_data(AVFrame *frame,
                                            माप_प्रकार nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    माप_प्रकार size = 0;

    hint = av_video_hint_alloc(nb_rects, &size);
    यदि (!hint)
        फर्काऊ रिक्त;

    buf = av_buffer_create((uint8_t *)hint, size, रिक्त, रिक्त, 0);
    यदि (!buf) {
        av_freep(&hint);
        फर्काऊ रिक्त;
    }

    यदि (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_HINT, buf)) {
        av_buffer_unref(&buf);
        फर्काऊ रिक्त;
    }

    फर्काऊ hint;
}
