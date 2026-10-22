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

#అన్తర్భావ <string.h>

#అన్తర్భావ "avstring.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *బహిర్గతం_కొలత)
{
    నిర్మాణం TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    స్థిరరాశి size_t rect_స్థానభ్రంశం = offsetof(నిర్మాణం TestStruct, rect);
    size_t కొలత = rect_స్థానభ్రంశం;
    AVVideoHint *hint;

    *బహిర్గతం_కొలత = 0;
    ఒకవేళ (nb_rects > (SIZE_MAX - కొలత) / పరిమాణం(AVVideoRect))
        తిరిగి ఖాళీ;
    కొలత += పరిమాణం(AVVideoRect) * nb_rects;

    hint = av_mallocz(కొలత);
    ఒకవేళ (!hint)
        తిరిగి ఖాళీ;

    hint->nb_rects    = nb_rects;
    hint->rect_స్థానభ్రంశం = rect_స్థానభ్రంశం;
    hint->rect_కొలత   = పరిమాణం(AVVideoRect);

    *బహిర్గతం_కొలత = కొలత;

    తిరిగి hint;
}

AVVideoHint *av_video_hint_create_side_దత్తాంశం(AVFrame *చట్రం,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t కొలత = 0;

    hint = av_video_hint_alloc(nb_rects, &కొలత);
    ఒకవేళ (!hint)
        తిరిగి ఖాళీ;

    buf = av_బఫరు_create((uint8_t *)hint, కొలత, ఖాళీ, ఖాళీ, 0);
    ఒకవేళ (!buf) {
        av_freep(&hint);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!av_చట్రం_new_side_దత్తాంశం_from_buf(చట్రం, AV_చట్రం_దత్తాంశం_VIDEO_HINT, buf)) {
        av_బఫరు_unref(&buf);
        తిరిగి ఖాళీ;
    }

    తిరిగి hint;
}
