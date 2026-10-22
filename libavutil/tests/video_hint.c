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

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/frame.h"
#অন্তর্ভাব "libavutil/macros.h"
#অন্তর্ভাব "libavutil/mem.h"
#অন্তর্ভাব "libavutil/video_hint.h"

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVVideoHint *hint;
    AVVideoRect *rect;
    AVFrame *frame;
    size_t আকার_2;

    স্থির ধ্রুবক size_t alloc_counts[] = { 0, 1, 4 };

    /* av_video_hint_alloc - various counts */
    printf("Testing av_video_hint_alloc()\n");
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        size_t nb = alloc_counts[i];
        hint = av_video_hint_alloc(nb, &আকার_2);
        যদি (hint) {
            printf("alloc %zu: OK, nb_rects=%zu, size>0=%s\n",
                   nb, hint->nb_rects, আকার_2 > 0 ? "yes" : "no");
            av_free(hint);
        } অন্যথা {
            printf("alloc %zu: FAIL\n", nb);
        }
    }

    /* pointer consistency and write/read back */
    printf("\nTesting av_video_hint_get_rect()\n");
    hint = av_video_hint_alloc(3, &আকার_2);
    যদি (hint) {
        /* verify av_video_hint_rects points to first rect */
        rect = av_video_hint_rects(hint);
        যদি ((uint8_t *)rect != (uint8_t *)hint + hint->rect_offset)
            printf("rects: pointer inconsistent with rect_offset\n");

        জন্য (পূর্ণসংখ্যা i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            যদি ((uint8_t *)rect != (uint8_t *)hint + hint->rect_offset +
                                   (size_t)i * hint->rect_আকার)
                printf("rect %d: pointer inconsistent with rect_offset/rect_size\n", i);
            rect->x = i * 100;
            rect->y = i * 200;
            rect->width = 64 + i;
            rect->height = 48 + i;
        }
        জন্য (পূর্ণসংখ্যা i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            printf("rect %d: x=%u y=%u w=%u h=%u\n",
                   i, rect->x, rect->y, rect->width, rect->height);
        }

        av_free(hint);
    }

    /* type field */
    printf("\nTesting type field\n");
    hint = av_video_hint_alloc(1, &আকার_2);
    যদি (hint) {
        hint->type = AV_VIDEO_HINT_TYPE_CONSTANT;
        printf("constant: type=%d\n", hint->type);
        hint->type = AV_VIDEO_HINT_TYPE_CHANGED;
        printf("changed: type=%d\n", hint->type);
        av_free(hint);
    }

    /* av_video_hint_create_side_data */
    printf("\nTesting av_video_hint_create_side_data()\n");
    frame = av_frame_alloc();
    যদি (frame) {
        hint = av_video_hint_create_side_তথ্য(frame, 2);
        যদি (hint) {
            printf("side_data: OK, nb_rects=%zu\n", hint->nb_rects);
            rect = av_video_hint_get_rect(hint, 0);
            rect->x = 10;
            rect->y = 20;
            rect->width = 320;
            rect->height = 240;
            rect = av_video_hint_get_rect(hint, 0);
            printf("side_data rect 0: x=%u y=%u\n", rect->x, rect->y);
        } অন্যথা {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    hint = av_video_hint_alloc(1, &আকার_2);
    printf("alloc OOM: %s\n", hint ? "FAIL" : "OK");
    av_free(hint);
    av_max_alloc(INT_MAX);

    frame = av_frame_alloc();
    যদি (frame) {
        av_max_alloc(1);
        hint = av_video_hint_create_side_তথ্য(frame, 1);
        printf("side_data OOM: %s\n", hint ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    ফেরত 0;
}
