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

#ضمن <string.h>

#ضمن "avstring.h"
#ضمن "frame.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *باہرلا_ناپ)
{
    بنية TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ثابت size_t rect_وتھ = offsetof(بنية TestStruct, rect);
    size_t ناپ = rect_وتھ;
    AVVideoHint *hint;

    *باہرلا_ناپ = 0;
    إذا (nb_rects > (SIZE_MAX - ناپ) / حجم(AVVideoRect))
        أرجع عدم;
    ناپ += حجم(AVVideoRect) * nb_rects;

    hint = av_mallocz(ناپ);
    إذا (!hint)
        أرجع عدم;

    hint->nb_rects    = nb_rects;
    hint->rect_وتھ = rect_وتھ;
    hint->rect_ناپ   = حجم(AVVideoRect);

    *باہرلا_ناپ = ناپ;

    أرجع hint;
}

AVVideoHint *av_video_hint_create_side_انکڑے(AVFrame *چوکھٹا,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t ناپ = 0;

    hint = av_video_hint_alloc(nb_rects, &ناپ);
    إذا (!hint)
        أرجع عدم;

    buf = av_بفر_create((uint8_t *)hint, ناپ, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&hint);
        أرجع عدم;
    }

    إذا (!av_چوکھٹا_new_side_انکڑے_from_buf(چوکھٹا, AV_چوکھٹا_انکڑے_VIDEO_HINT, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع hint;
}
