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

#شامل <string.h>

#شامل "avstring.h"
#شامل "frame.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *برآمد_سائز)
{
    ساخت TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ثابت size_t rect_انحراف = offsetof(ساخت TestStruct, rect);
    size_t سائز = rect_انحراف;
    AVVideoHint *hint;

    *برآمد_سائز = 0;
    اگر (nb_rects > (SIZE_MAX - سائز) / حجم(AVVideoRect))
        واپس تہی;
    سائز += حجم(AVVideoRect) * nb_rects;

    hint = av_mallocz(سائز);
    اگر (!hint)
        واپس تہی;

    hint->nb_rects    = nb_rects;
    hint->rect_انحراف = rect_انحراف;
    hint->rect_سائز   = حجم(AVVideoRect);

    *برآمد_سائز = سائز;

    واپس hint;
}

AVVideoHint *av_video_hint_create_side_ڈیٹا(AVFrame *چوکھٹا,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t سائز = 0;

    hint = av_video_hint_alloc(nb_rects, &سائز);
    اگر (!hint)
        واپس تہی;

    buf = av_بفر_create((uint8_t *)hint, سائز, تہی, تہی, 0);
    اگر (!buf) {
        av_freep(&hint);
        واپس تہی;
    }

    اگر (!av_چوکھٹا_new_side_ڈیٹا_from_buf(چوکھٹا, AV_چوکھٹا_ڈیٹا_VIDEO_HINT, buf)) {
        av_بفر_unref(&buf);
        واپس تہی;
    }

    واپس hint;
}
