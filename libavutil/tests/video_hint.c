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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/video_hint.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVVideoHint *hint;
    AVVideoRect *rect;
    AVFrame *చట్రం;
    size_t కొలత;

    స్థిర స్థిరరాశి size_t alloc_counts[] = { 0, 1, 4 };

    /* av_video_hint_alloc - various counts */
    రాయి("Testing av_video_hint_alloc()\n");
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        size_t nb = alloc_counts[i];
        hint = av_video_hint_alloc(nb, &కొలత);
        ఒకవేళ (hint) {
            రాయి("alloc %zu: OK, nb_rects=%zu, size>0=%s\n",
                   nb, hint->nb_rects, కొలత > 0 ? "yes" : "no");
            av_free(hint);
        } లేకపోతే {
            రాయి("alloc %zu: FAIL\n", nb);
        }
    }

    /* pointer consistency and write/read back */
    రాయి("\nTesting av_video_hint_get_rect()\n");
    hint = av_video_hint_alloc(3, &కొలత);
    ఒకవేళ (hint) {
        /* verify av_video_hint_rects points to first rect */
        rect = av_video_hint_rects(hint);
        ఒకవేళ ((uint8_t *)rect != (uint8_t *)hint + hint->rect_స్థానభ్రంశం)
            రాయి("rects: pointer inconsistent with rect_offset\n");

        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            ఒకవేళ ((uint8_t *)rect != (uint8_t *)hint + hint->rect_స్థానభ్రంశం +
                                   (size_t)i * hint->rect_కొలత)
                రాయి("rect %d: pointer inconsistent with rect_offset/rect_size\n", i);
            rect->x = i * 100;
            rect->y = i * 200;
            rect->వెడల్పు = 64 + i;
            rect->ఎత్తు = 48 + i;
        }
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            రాయి("rect %d: x=%u y=%u w=%u h=%u\n",
                   i, rect->x, rect->y, rect->వెడల్పు, rect->ఎత్తు);
        }

        av_free(hint);
    }

    /* type field */
    రాయి("\nTesting type field\n");
    hint = av_video_hint_alloc(1, &కొలత);
    ఒకవేళ (hint) {
        hint->type = AV_VIDEO_HINT_TYPE_CONSTANT;
        రాయి("constant: type=%d\n", hint->type);
        hint->type = AV_VIDEO_HINT_TYPE_మారింది;
        రాయి("changed: type=%d\n", hint->type);
        av_free(hint);
    }

    /* av_video_hint_create_side_data */
    రాయి("\nTesting av_video_hint_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        hint = av_video_hint_create_side_దత్తాంశం(చట్రం, 2);
        ఒకవేళ (hint) {
            రాయి("side_data: OK, nb_rects=%zu\n", hint->nb_rects);
            rect = av_video_hint_get_rect(hint, 0);
            rect->x = 10;
            rect->y = 20;
            rect->వెడల్పు = 320;
            rect->ఎత్తు = 240;
            rect = av_video_hint_get_rect(hint, 0);
            రాయి("side_data rect 0: x=%u y=%u\n", rect->x, rect->y);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    hint = av_video_hint_alloc(1, &కొలత);
    రాయి("alloc OOM: %s\n", hint ? "FAIL" : "OK");
    av_free(hint);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        av_max_alloc(1);
        hint = av_video_hint_create_side_దత్తాంశం(చట్రం, 1);
        రాయి("side_data OOM: %s\n", hint ? "FAIL" : "OK");
        av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
        av_చట్రం_free(&చట్రం);
    }

    తిరిగి 0;
}
