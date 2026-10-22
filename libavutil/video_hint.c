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

#அந்தர்பாவ <string.h>

#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *out_size)
{
    கட்டமைப்பு TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    மாறிலி size_t rect_offset = offsetof(கட்டமைப்பு TestStruct, rect);
    size_t size = rect_offset;
    AVVideoHint *hint;

    *out_size = 0;
    எனில் (nb_rects > (SIZE_MAX - size) / அளவு(AVVideoRect))
        திரும்பு வெற்று;
    size += அளவு(AVVideoRect) * nb_rects;

    hint = av_mallocz(size);
    எனில் (!hint)
        திரும்பு வெற்று;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_size   = அளவு(AVVideoRect);

    *out_size = size;

    திரும்பு hint;
}

AVVideoHint *av_video_hint_create_side_data(AVFrame *frame,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t size = 0;

    hint = av_video_hint_alloc(nb_rects, &size);
    எனில் (!hint)
        திரும்பு வெற்று;

    buf = av_buffer_create((uint8_t *)hint, size, வெற்று, வெற்று, 0);
    எனில் (!buf) {
        av_freep(&hint);
        திரும்பு வெற்று;
    }

    எனில் (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_HINT, buf)) {
        av_buffer_unref(&buf);
        திரும்பு வெற்று;
    }

    திரும்பு hint;
}
