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

#समावेश <string.h>

#समावेश "avstring.h"
#समावेश "frame.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "video_hint.h"

AVVideoHint *av_video_hint_alloc(माप_प्रकार nb_rects,
                                 माप_प्रकार *out_आकार)
{
    काष्ठा TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    स्थिर माप_प्रकार rect_offset = दुरत्व(काष्ठा TestStruct, rect);
    माप_प्रकार आकार = rect_offset;
    AVVideoHint *hint;

    *out_आकार = 0;
    अगर (nb_rects > (SIZE_MAX - आकार) / माप(AVVideoRect))
        वापस शून्य;
    आकार += माप(AVVideoRect) * nb_rects;

    hint = av_mallocz(आकार);
    अगर (!hint)
        वापस शून्य;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_आकार   = माप(AVVideoRect);

    *out_आकार = आकार;

    वापस hint;
}

AVVideoHint *av_video_hint_create_side_तथ्य(AVFrame *frame,
                                            माप_प्रकार nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    माप_प्रकार आकार = 0;

    hint = av_video_hint_alloc(nb_rects, &आकार);
    अगर (!hint)
        वापस शून्य;

    buf = av_बफर_create((uint8_t *)hint, आकार, शून्य, शून्य, 0);
    अगर (!buf) {
        av_freep(&hint);
        वापस शून्य;
    }

    अगर (!av_frame_new_side_तथ्य_from_buf(frame, AV_FRAME_तथ्य_VIDEO_HINT, buf)) {
        av_बफर_unref(&buf);
        वापस शून्य;
    }

    वापस hint;
}
