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

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdio.h>

#ضمن "libavutil/frame.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/video_hint.h"

صحيح اصلي(فراغ)
{
    AVVideoHint *hint;
    AVVideoRect *rect;
    AVFrame *چوکاټ;
    size_t اندازه;

    ساكن ثابت size_t alloc_counts[] = { 0, 1, 4 };

    /* av_video_hint_alloc - various counts */
    چاپ_کړه("Testing av_video_hint_alloc()\n");
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        size_t nb = alloc_counts[i];
        hint = av_video_hint_alloc(nb, &اندازه);
        إذا (hint) {
            چاپ_کړه("alloc %zu: OK, nb_rects=%zu, size>0=%s\n",
                   nb, hint->nb_rects, اندازه > 0 ? "yes" : "no");
            av_free(hint);
        } وإلا {
            چاپ_کړه("alloc %zu: FAIL\n", nb);
        }
    }

    /* pointer consistency and write/read back */
    چاپ_کړه("\nTesting av_video_hint_get_rect()\n");
    hint = av_video_hint_alloc(3, &اندازه);
    إذا (hint) {
        /* verify av_video_hint_rects points to first rect */
        rect = av_video_hint_rects(hint);
        إذا ((uint8_t *)rect != (uint8_t *)hint + hint->rect_دننه_واټن)
            چاپ_کړه("rects: pointer inconsistent with rect_offset\n");

        لكل (صحيح i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            إذا ((uint8_t *)rect != (uint8_t *)hint + hint->rect_دننه_واټن +
                                   (size_t)i * hint->rect_اندازه)
                چاپ_کړه("rect %d: pointer inconsistent with rect_offset/rect_size\n", i);
            rect->x = i * 100;
            rect->y = i * 200;
            rect->پلنوالی = 64 + i;
            rect->لوړوالی = 48 + i;
        }
        لكل (صحيح i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            چاپ_کړه("rect %d: x=%u y=%u w=%u h=%u\n",
                   i, rect->x, rect->y, rect->پلنوالی, rect->لوړوالی);
        }

        av_free(hint);
    }

    /* type field */
    چاپ_کړه("\nTesting type field\n");
    hint = av_video_hint_alloc(1, &اندازه);
    إذا (hint) {
        hint->type = AV_VIDEO_HINT_TYPE_CONSTANT;
        چاپ_کړه("constant: type=%d\n", hint->type);
        hint->type = AV_VIDEO_HINT_TYPE_بدل_شوی;
        چاپ_کړه("changed: type=%d\n", hint->type);
        av_free(hint);
    }

    /* av_video_hint_create_side_data */
    چاپ_کړه("\nTesting av_video_hint_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        hint = av_video_hint_create_side_معلومات(چوکاټ, 2);
        إذا (hint) {
            چاپ_کړه("side_data: OK, nb_rects=%zu\n", hint->nb_rects);
            rect = av_video_hint_get_rect(hint, 0);
            rect->x = 10;
            rect->y = 20;
            rect->پلنوالی = 320;
            rect->لوړوالی = 240;
            rect = av_video_hint_get_rect(hint, 0);
            چاپ_کړه("side_data rect 0: x=%u y=%u\n", rect->x, rect->y);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کړه("\nTesting OOM paths\n");
    av_max_alloc(1);
    hint = av_video_hint_alloc(1, &اندازه);
    چاپ_کړه("alloc OOM: %s\n", hint ? "FAIL" : "OK");
    av_free(hint);
    av_max_alloc(لوی_عدد);

    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        av_max_alloc(1);
        hint = av_video_hint_create_side_معلومات(چوکاټ, 1);
        چاپ_کړه("side_data OOM: %s\n", hint ? "FAIL" : "OK");
        av_max_alloc(لوی_عدد);
        av_چوکاټ_free(&چوکاټ);
    }

    أرجع 0;
}
