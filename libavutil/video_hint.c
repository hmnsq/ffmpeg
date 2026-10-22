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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *out_size)
{
    সংরচনা TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ধ্রুব size_t rect_offset = offsetof(সংরচনা TestStruct, rect);
    size_t size = rect_offset;
    AVVideoHint *hint;

    *out_size = 0;
    যদি (nb_rects > (SIZE_MAX - size) / পরিমাণ(AVVideoRect))
        প্রত্যাগম রিক্ত;
    size += পরিমাণ(AVVideoRect) * nb_rects;

    hint = av_mallocz(size);
    যদি (!hint)
        প্রত্যাগম রিক্ত;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_size   = পরিমাণ(AVVideoRect);

    *out_size = size;

    প্রত্যাগম hint;
}

AVVideoHint *av_video_hint_create_side_data(AVFrame *frame,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t size = 0;

    hint = av_video_hint_alloc(nb_rects, &size);
    যদি (!hint)
        প্রত্যাগম রিক্ত;

    buf = av_buffer_create((uint8_t *)hint, size, রিক্ত, রিক্ত, 0);
    যদি (!buf) {
        av_freep(&hint);
        প্রত্যাগম রিক্ত;
    }

    যদি (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_HINT, buf)) {
        av_buffer_unref(&buf);
        প্রত্যাগম রিক্ত;
    }

    প্রত্যাগম hint;
}
