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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *out_size)
{
    ସଂରଚନା TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ଅଚଳ size_t rect_offset = offsetof(ସଂରଚନା TestStruct, rect);
    size_t size = rect_offset;
    AVVideoHint *hint;

    *out_size = 0;
    ଯଦି (nb_rects > (SIZE_MAX - size) / ଆକାର(AVVideoRect))
        ଫେରନ୍ତୁ ଖାଲି;
    size += ଆକାର(AVVideoRect) * nb_rects;

    hint = av_mallocz(size);
    ଯଦି (!hint)
        ଫେରନ୍ତୁ ଖାଲି;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_size   = ଆକାର(AVVideoRect);

    *out_size = size;

    ଫେରନ୍ତୁ hint;
}

AVVideoHint *av_video_hint_create_side_data(AVFrame *frame,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t size = 0;

    hint = av_video_hint_alloc(nb_rects, &size);
    ଯଦି (!hint)
        ଫେରନ୍ତୁ ଖାଲି;

    buf = av_buffer_create((uint8_t *)hint, size, ଖାଲି, ଖାଲି, 0);
    ଯଦି (!buf) {
        av_freep(&hint);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_HINT, buf)) {
        av_buffer_unref(&buf);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ hint;
}
