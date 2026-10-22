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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *ਬਾਹਰਲਾ_ਮਾਪ)
{
    ਬਣਤਰ TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ਅਚਲ size_t rect_ਵਿੱਥ = offsetof(ਬਣਤਰ TestStruct, rect);
    size_t ਮਾਪ = rect_ਵਿੱਥ;
    AVVideoHint *hint;

    *ਬਾਹਰਲਾ_ਮਾਪ = 0;
    ਜੇ (nb_rects > (SIZE_MAX - ਮਾਪ) / ਆਕਾਰ(AVVideoRect))
        ਵਾਪਸ ਨਿਰਾ;
    ਮਾਪ += ਆਕਾਰ(AVVideoRect) * nb_rects;

    hint = av_mallocz(ਮਾਪ);
    ਜੇ (!hint)
        ਵਾਪਸ ਨਿਰਾ;

    hint->nb_rects    = nb_rects;
    hint->rect_ਵਿੱਥ = rect_ਵਿੱਥ;
    hint->rect_ਮਾਪ   = ਆਕਾਰ(AVVideoRect);

    *ਬਾਹਰਲਾ_ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ hint;
}

AVVideoHint *av_video_hint_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t ਮਾਪ = 0;

    hint = av_video_hint_alloc(nb_rects, &ਮਾਪ);
    ਜੇ (!hint)
        ਵਾਪਸ ਨਿਰਾ;

    buf = av_ਬਫਰ_create((uint8_t *)hint, ਮਾਪ, ਨਿਰਾ, ਨਿਰਾ, 0);
    ਜੇ (!buf) {
        av_freep(&hint);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ_from_buf(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_VIDEO_HINT, buf)) {
        av_ਬਫਰ_unref(&buf);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ hint;
}
