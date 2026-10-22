/*
 * Copyright (c) 2026 Lynne <dev@lynne.ee>
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

#ಅನ್ತರ್ಭಾವ "raw_color_params.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *ಗಾತ್ರ_2)
{
    AVRawColorParams *p = av_mallocz(ಗಾತ್ರ(AVRawColorParams));
    ಆದರೆ (!p)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = ಗಾತ್ರ(*p);

    ಹಿಂತಿರುಗಿ p;
}

AVRawColorParams *av_raw_color_params_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ =
        av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_RAW_COLOR_PARAMS,
                               ಗಾತ್ರ(AVRawColorParams));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, side_ದತ್ತಾಂಶ->ಗಾತ್ರ_2);

    ಹಿಂತಿರುಗಿ (AVRawColorParams *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}
