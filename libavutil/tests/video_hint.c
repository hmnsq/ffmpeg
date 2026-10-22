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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/video_hint.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVVideoHint *hint;
    AVVideoRect *rect;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2;

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t alloc_counts[] = { 0, 1, 4 };

    /* av_video_hint_alloc - various counts */
    ಬರೆ("Testing av_video_hint_alloc()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        size_t nb = alloc_counts[i];
        hint = av_video_hint_alloc(nb, &ಗಾತ್ರ_2);
        ಆದರೆ (hint) {
            ಬರೆ("alloc %zu: OK, nb_rects=%zu, size>0=%s\n",
                   nb, hint->nb_rects, ಗಾತ್ರ_2 > 0 ? "yes" : "no");
            av_free(hint);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("alloc %zu: FAIL\n", nb);
        }
    }

    /* pointer consistency and write/read back */
    ಬರೆ("\nTesting av_video_hint_get_rect()\n");
    hint = av_video_hint_alloc(3, &ಗಾತ್ರ_2);
    ಆದರೆ (hint) {
        /* verify av_video_hint_rects points to first rect */
        rect = av_video_hint_rects(hint);
        ಆದರೆ ((uint8_t *)rect != (uint8_t *)hint + hint->rect_ಸ್ಥಾನಾಂತರ)
            ಬರೆ("rects: pointer inconsistent with rect_offset\n");

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            ಆದರೆ ((uint8_t *)rect != (uint8_t *)hint + hint->rect_ಸ್ಥಾನಾಂತರ +
                                   (size_t)i * hint->rect_ಗಾತ್ರ)
                ಬರೆ("rect %d: pointer inconsistent with rect_offset/rect_size\n", i);
            rect->x = i * 100;
            rect->y = i * 200;
            rect->ಅಗಲ = 64 + i;
            rect->ಎತ್ತರ = 48 + i;
        }
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            rect = av_video_hint_get_rect(hint, i);
            ಬರೆ("rect %d: x=%u y=%u w=%u h=%u\n",
                   i, rect->x, rect->y, rect->ಅಗಲ, rect->ಎತ್ತರ);
        }

        av_free(hint);
    }

    /* type field */
    ಬರೆ("\nTesting type field\n");
    hint = av_video_hint_alloc(1, &ಗಾತ್ರ_2);
    ಆದರೆ (hint) {
        hint->type = AV_VIDEO_HINT_TYPE_CONSTANT;
        ಬರೆ("constant: type=%d\n", hint->type);
        hint->type = AV_VIDEO_HINT_TYPE_ಬದಲಾಯಿತು;
        ಬರೆ("changed: type=%d\n", hint->type);
        av_free(hint);
    }

    /* av_video_hint_create_side_data */
    ಬರೆ("\nTesting av_video_hint_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        hint = av_video_hint_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು, 2);
        ಆದರೆ (hint) {
            ಬರೆ("side_data: OK, nb_rects=%zu\n", hint->nb_rects);
            rect = av_video_hint_get_rect(hint, 0);
            rect->x = 10;
            rect->y = 20;
            rect->ಅಗಲ = 320;
            rect->ಎತ್ತರ = 240;
            rect = av_video_hint_get_rect(hint, 0);
            ಬರೆ("side_data rect 0: x=%u y=%u\n", rect->x, rect->y);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("side_data: FAIL\n");
        }
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    hint = av_video_hint_alloc(1, &ಗಾತ್ರ_2);
    ಬರೆ("alloc OOM: %s\n", hint ? "FAIL" : "OK");
    av_free(hint);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        av_max_alloc(1);
        hint = av_video_hint_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು, 1);
        ಬರೆ("side_data OOM: %s\n", hint ? "FAIL" : "OK");
        av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    ಹಿಂತಿರುಗಿ 0;
}
