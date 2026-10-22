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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/video_hint.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVVideoHint *hint;
    AVVideoRect *rect;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;

    ਸਥਿਰ ਅਚਲ size_t alloc_counts[] = { 0, 1, 4 };

    /* av_video_hint_alloc - various counts */
    ਲਿਖੋ("Testing av_video_hint_alloc()\n");
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        size_t nb = alloc_counts[i];
        hint = av_video_hint_alloc(nb, &ਮਾਪ);
        ਜੇ (hint) {
            ਲਿਖੋ("alloc %zu: OK, nb_rects=%zu, size>0=%s\n",
                   nb, hint->nb_rects, ਮਾਪ > 0 ? "yes" : "no");
            av_free(hint);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("alloc %zu: FAIL\n", nb);
        }
    }

    /* pointer consistency and write/read back */
    ਲਿਖੋ("\nTesting av_video_hint_get_rect()\n");
    hint = av_video_hint_alloc(3, &ਮਾਪ);
    ਜੇ (hint) {
        /* verify av_video_hint_rects points to first rect */
        rect = av_video_hint_rects(hint);
        ਜੇ ((uint8_t *)rect != (uint8_t *)hint + hint->rect_ਵਿੱਥ)
            ਲਿਖੋ("rects: pointer inconsistent with rect_offset\n");

        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            ਜੇ ((uint8_t *)rect != (uint8_t *)hint + hint->rect_ਵਿੱਥ +
                                   (size_t)i * hint->rect_ਮਾਪ)
                ਲਿਖੋ("rect %d: pointer inconsistent with rect_offset/rect_size\n", i);
            rect->x = i * 100;
            rect->y = i * 200;
            rect->ਚੌੜਾਈ = 64 + i;
            rect->ਉਚਾਈ = 48 + i;
        }
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            ਲਿਖੋ("rect %d: x=%u y=%u w=%u h=%u\n",
                   i, rect->x, rect->y, rect->ਚੌੜਾਈ, rect->ਉਚਾਈ);
        }

        av_free(hint);
    }

    /* type field */
    ਲਿਖੋ("\nTesting type field\n");
    hint = av_video_hint_alloc(1, &ਮਾਪ);
    ਜੇ (hint) {
        hint->type = AV_VIDEO_HINT_TYPE_CONSTANT;
        ਲਿਖੋ("constant: type=%d\n", hint->type);
        hint->type = AV_VIDEO_HINT_TYPE_ਬਦਲਿਆ;
        ਲਿਖੋ("changed: type=%d\n", hint->type);
        av_free(hint);
    }

    /* av_video_hint_create_side_data */
    ਲਿਖੋ("\nTesting av_video_hint_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        hint = av_video_hint_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ, 2);
        ਜੇ (hint) {
            ਲਿਖੋ("side_data: OK, nb_rects=%zu\n", hint->nb_rects);
            rect = av_video_hint_get_rect(hint, 0);
            rect->x = 10;
            rect->y = 20;
            rect->ਚੌੜਾਈ = 320;
            rect->ਉਚਾਈ = 240;
            rect = av_video_hint_get_rect(hint, 0);
            ਲਿਖੋ("side_data rect 0: x=%u y=%u\n", rect->x, rect->y);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    hint = av_video_hint_alloc(1, &ਮਾਪ);
    ਲਿਖੋ("alloc OOM: %s\n", hint ? "FAIL" : "OK");
    av_free(hint);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        av_max_alloc(1);
        hint = av_video_hint_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ, 1);
        ਲਿਖੋ("side_data OOM: %s\n", hint ? "FAIL" : "OK");
        av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    ਵਾਪਸ 0;
}
