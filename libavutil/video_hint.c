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
                                 size_t *ٻاهريون_سائيز)
{
    بنية TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ثابت size_t rect_وٿي = offsetof(بنية TestStruct, rect);
    size_t سائيز = rect_وٿي;
    AVVideoHint *hint;

    *ٻاهريون_سائيز = 0;
    إذا (nb_rects > (SIZE_MAX - سائيز) / حجم(AVVideoRect))
        أرجع عدم;
    سائيز += حجم(AVVideoRect) * nb_rects;

    hint = av_mallocz(سائيز);
    إذا (!hint)
        أرجع عدم;

    hint->nb_rects    = nb_rects;
    hint->rect_وٿي = rect_وٿي;
    hint->rect_سائيز   = حجم(AVVideoRect);

    *ٻاهريون_سائيز = سائيز;

    أرجع hint;
}

AVVideoHint *av_video_hint_create_side_معلومات(AVFrame *چوکٺو,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t سائيز = 0;

    hint = av_video_hint_alloc(nb_rects, &سائيز);
    إذا (!hint)
        أرجع عدم;

    buf = av_بفر_create((uint8_t *)hint, سائيز, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&hint);
        أرجع عدم;
    }

    إذا (!av_چوکٺو_new_side_معلومات_from_buf(چوکٺو, AV_چوکٺو_معلومات_VIDEO_HINT, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع hint;
}
