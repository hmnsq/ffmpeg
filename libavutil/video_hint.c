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

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *बहिर्गमनम्_आकार)
{
    संरचना TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ध्रुव size_t rect_विस्थापनम् = offsetof(संरचना TestStruct, rect);
    size_t आकार = rect_विस्थापनम्;
    AVVideoHint *hint;

    *बहिर्गमनम्_आकार = 0;
    यदि (nb_rects > (SIZE_MAX - आकार) / परिमाण(AVVideoRect))
        प्रत्यागम रिक्त;
    आकार += परिमाण(AVVideoRect) * nb_rects;

    hint = av_mallocz(आकार);
    यदि (!hint)
        प्रत्यागम रिक्त;

    hint->nb_rects    = nb_rects;
    hint->rect_विस्थापनम् = rect_विस्थापनम्;
    hint->rect_आकार   = परिमाण(AVVideoRect);

    *बहिर्गमनम्_आकार = आकार;

    प्रत्यागम hint;
}

AVVideoHint *av_video_hint_create_side_दत्त(AVFrame *frame,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t आकार = 0;

    hint = av_video_hint_alloc(nb_rects, &आकार);
    यदि (!hint)
        प्रत्यागम रिक्त;

    buf = av_बफर_create((uint8_t *)hint, आकार, रिक्त, रिक्त, 0);
    यदि (!buf) {
        av_freep(&hint);
        प्रत्यागम रिक्त;
    }

    यदि (!av_frame_new_side_दत्त_from_buf(frame, AV_FRAME_दत्त_VIDEO_HINT, buf)) {
        av_बफर_unref(&buf);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम hint;
}
