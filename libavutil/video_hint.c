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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "video_hint.h"

AVVideoHint *av_video_hint_alloc(size_t nb_rects,
                                 size_t *ಹೊರಹೋಗು_ಗಾತ್ರ)
{
    ರಚನೆ TestStruct {
        AVVideoHint hint;
        AVVideoRect rect;
    };
    ಸ್ಥಿರಾಂಕ size_t rect_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ TestStruct, rect);
    size_t ಗಾತ್ರ_2 = rect_ಸ್ಥಾನಾಂತರ;
    AVVideoHint *hint;

    *ಹೊರಹೋಗು_ಗಾತ್ರ = 0;
    ಆದರೆ (nb_rects > (SIZE_MAX - ಗಾತ್ರ_2) / ಗಾತ್ರ(AVVideoRect))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಗಾತ್ರ_2 += ಗಾತ್ರ(AVVideoRect) * nb_rects;

    hint = av_mallocz(ಗಾತ್ರ_2);
    ಆದರೆ (!hint)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    hint->nb_rects    = nb_rects;
    hint->rect_ಸ್ಥಾನಾಂತರ = rect_ಸ್ಥಾನಾಂತರ;
    hint->rect_ಗಾತ್ರ   = ಗಾತ್ರ(AVVideoRect);

    *ಹೊರಹೋಗು_ಗಾತ್ರ = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ hint;
}

AVVideoHint *av_video_hint_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು,
                                            size_t nb_rects)
{
    AVVideoHint *hint;
    AVBufferRef *buf;
    size_t ಗಾತ್ರ_2 = 0;

    hint = av_video_hint_alloc(nb_rects, &ಗಾತ್ರ_2);
    ಆದರೆ (!hint)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    buf = av_ಬಫರ್_create((uint8_t *)hint, ಗಾತ್ರ_2, ಖಾಲಿ, ಖಾಲಿ, 0);
    ಆದರೆ (!buf) {
        av_freep(&hint);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ_from_buf(ಚೌಕಟ್ಟು, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_VIDEO_HINT, buf)) {
        av_ಬಫರ್_unref(&buf);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ hint;
}
