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
                                 size_t *out_আকার)
{
    কাঠামো TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ধ্রুবক size_t rect_offset = offsetof(কাঠামো TestStruct, rect);
    size_t আকার_2 = rect_offset;
    AVVideoHint *hint;

    *out_আকার = 0;
    যদি (nb_rects > (SIZE_MAX - আকার_2) / আকার(AVVideoRect))
        ফেরত ফাঁকা;
    আকার_2 += আকার(AVVideoRect) * nb_rects;

    hint = av_mallocz(আকার_2);
    যদি (!hint)
        ফেরত ফাঁকা;

    hint->nb_rects    = nb_rects;
    hint->rect_offset = rect_offset;
    hint->rect_আকার   = আকার(AVVideoRect);

    *out_আকার = আকার_2;

    ফেরত hint;
}

AVVideoHint *av_video_hint_create_side_তথ্য(AVFrame *frame,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t আকার_2 = 0;

    hint = av_video_hint_alloc(nb_rects, &আকার_2);
    যদি (!hint)
        ফেরত ফাঁকা;

    buf = av_বাফার_create((uint8_t *)hint, আকার_2, ফাঁকা, ফাঁকা, 0);
    যদি (!buf) {
        av_freep(&hint);
        ফেরত ফাঁকা;
    }

    যদি (!av_frame_new_side_তথ্য_from_buf(frame, AV_FRAME_তথ্য_VIDEO_HINT, buf)) {
        av_বাফার_unref(&buf);
        ফেরত ফাঁকা;
    }

    ফেরত hint;
}
