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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *out_size)
{
    ഘടന TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    സ്ഥിരം size_t rect_offset = offsetof(ഘടന TestStruct, rect);
    size_t size = rect_offset;
    AVVideoHint *hint;

    *out_size = 0;
    എങ്കിൽ (nb_rects > (SIZE_MAX - size) / വലുപ്പം(AVVideoRect))
        തിരികെ ശൂന്യ;
    size += വലുപ്പം(AVVideoRect) * nb_rects;

    hint = av_mallocz(size);
    എങ്കിൽ (!hint)
        തിരികെ ശൂന്യ;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_size   = വലുപ്പം(AVVideoRect);

    *out_size = size;

    തിരികെ hint;
}

AVVideoHint *av_video_hint_create_side_data(AVFrame *frame,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t size = 0;

    hint = av_video_hint_alloc(nb_rects, &size);
    എങ്കിൽ (!hint)
        തിരികെ ശൂന്യ;

    buf = av_buffer_create((uint8_t *)hint, size, ശൂന്യ, ശൂന്യ, 0);
    എങ്കിൽ (!buf) {
        av_freep(&hint);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_HINT, buf)) {
        av_buffer_unref(&buf);
        തിരികെ ശൂന്യ;
    }

    തിരികെ hint;
}
