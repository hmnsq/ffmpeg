/*
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

#समावेश <limits.h>
#समावेश <stdint.h>
#समावेश <stdio.h>

#समावेश "libavutil/frame.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/mem.h"
#समावेश "libavutil/video_hint.h"

पूर्णांक मुख्य(व्योम)
{
    AVVideoHint *hint;
    AVVideoRect *rect;
    AVFrame *frame;
    माप_प्रकार आकार;

    अटल स्थिर माप_प्रकार alloc_counts[] = { 0, 1, 4 };

    /* av_video_hint_alloc - various counts */
    म_लिखो("Testing av_video_hint_alloc()\n");
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        माप_प्रकार nb = alloc_counts[i];
        hint = av_video_hint_alloc(nb, &आकार);
        अगर (hint) {
            म_लिखो("alloc %zu: OK, nb_rects=%zu, size>0=%s\n",
                   nb, hint->nb_rects, आकार > 0 ? "yes" : "no");
            av_free(hint);
        } अन्यथा {
            म_लिखो("alloc %zu: FAIL\n", nb);
        }
    }

    /* pointer consistency and write/read back */
    म_लिखो("\nTesting av_video_hint_get_rect()\n");
    hint = av_video_hint_alloc(3, &आकार);
    अगर (hint) {
        /* verify av_video_hint_rects points to first rect */
        rect = av_video_hint_rects(hint);
        अगर ((uint8_t *)rect != (uint8_t *)hint + hint->rect_offset)
            म_लिखो("rects: pointer inconsistent with rect_offset\n");

        क्रम (पूर्णांक i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            अगर ((uint8_t *)rect != (uint8_t *)hint + hint->rect_offset +
                                   (माप_प्रकार)i * hint->rect_आकार)
                म_लिखो("rect %d: pointer inconsistent with rect_offset/rect_size\n", i);
            rect->x = i * 100;
            rect->y = i * 200;
            rect->width = 64 + i;
            rect->height = 48 + i;
        }
        क्रम (पूर्णांक i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            म_लिखो("rect %d: x=%u y=%u w=%u h=%u\n",
                   i, rect->x, rect->y, rect->width, rect->height);
        }

        av_free(hint);
    }

    /* type field */
    म_लिखो("\nTesting type field\n");
    hint = av_video_hint_alloc(1, &आकार);
    अगर (hint) {
        hint->type = AV_VIDEO_HINT_TYPE_CONSTANT;
        म_लिखो("constant: type=%d\n", hint->type);
        hint->type = AV_VIDEO_HINT_TYPE_CHANGED;
        म_लिखो("changed: type=%d\n", hint->type);
        av_free(hint);
    }

    /* av_video_hint_create_side_data */
    म_लिखो("\nTesting av_video_hint_create_side_data()\n");
    frame = av_frame_alloc();
    अगर (frame) {
        hint = av_video_hint_create_side_तथ्य(frame, 2);
        अगर (hint) {
            म_लिखो("side_data: OK, nb_rects=%zu\n", hint->nb_rects);
            rect = av_video_hint_get_rect(hint, 0);
            rect->x = 10;
            rect->y = 20;
            rect->width = 320;
            rect->height = 240;
            rect = av_video_hint_get_rect(hint, 0);
            म_लिखो("side_data rect 0: x=%u y=%u\n", rect->x, rect->y);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    hint = av_video_hint_alloc(1, &आकार);
    म_लिखो("alloc OOM: %s\n", hint ? "FAIL" : "OK");
    av_free(hint);
    av_max_alloc(पूर्णांक_उच्च);

    frame = av_frame_alloc();
    अगर (frame) {
        av_max_alloc(1);
        hint = av_video_hint_create_side_तथ्य(frame, 1);
        म_लिखो("side_data OOM: %s\n", hint ? "FAIL" : "OK");
        av_max_alloc(पूर्णांक_उच्च);
        av_frame_free(&frame);
    }

    वापस 0;
}
