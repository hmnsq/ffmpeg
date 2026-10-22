/*
 * Copyright (c) 2023 Jan Ekström <jeebjp@gmail.com>
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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ "libavutil/frame.c"
#ಅನ್ತರ್ಭಾವ "libavutil/internal.h"

ಸ್ಥಿರ ಶೂನ್ಯ print_entries(ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ **sd, ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ nb_sd)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_sd; i++) {
        ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ *ನಮೂದು = sd[i];

        ಬರೆ("sd %d (size %zu), %s",
               i, ನಮೂದು->ಗಾತ್ರ_2, av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_name(ನಮೂದು->type));

        ಆದರೆ (ನಮೂದು->type != AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED) {
            ಅಕ್ಷರ_ಬರೆ('\n');
            ಮುಂದುವರಿ;
        }

        ಬರೆ(": %d\n", *(int32_t *)ನಮೂದು->ದತ್ತಾಂಶ);
    }
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಚೌಕಟ್ಟು_Side_ದತ್ತಾಂಶ_ಗಣ {
    AVFrame_Side_ದತ್ತಾಂಶ **sd;
    ಪೂರ್ಣಾಂಕ            nb_sd;
} ಚೌಕಟ್ಟು_Side_ದತ್ತಾಂಶ_ಗಣ;

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಚೌಕಟ್ಟು_Side_ದತ್ತಾಂಶ_ಗಣ ಗಣ = { 0 };

    av_assert0(
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(&ಗಣ.sd, &ಗಣ.nb_sd,
                               AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_CONTENT_LIGHT_LEVEL,
                               ಗಾತ್ರ(int64_t), 0));
    av_assert0(
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(&ಗಣ.sd, &ಗಣ.nb_sd,
                               AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_CONTENT_LIGHT_LEVEL,
                               ಗಾತ್ರ(int32_t), AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE));

    // test entries in the middle
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = 1; ಮೌಲ್ಯ < 4; ಮೌಲ್ಯ++) {
        AVFrame_Side_ದತ್ತಾಂಶ *sd = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(
            &ಗಣ.sd, &ಗಣ.nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED,
            ಗಾತ್ರ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->ದತ್ತಾಂಶ = ಮೌಲ್ಯ;
    }

    av_assert0(
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(
            &ಗಣ.sd, &ಗಣ.nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SPHERICAL,
           ಗಾತ್ರ(int64_t), 0));

    av_assert0(
        av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(
            &ಗಣ.sd, &ಗಣ.nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SPHERICAL,
            ಗಾತ್ರ(int32_t), AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE));

    // test entries at the end
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = 1; ಮೌಲ್ಯ < 4; ಮೌಲ್ಯ++) {
        AVFrame_Side_ದತ್ತಾಂಶ *sd = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(
            &ಗಣ.sd, &ಗಣ.nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED,
            ಗಾತ್ರ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->ದತ್ತಾಂಶ = ಮೌಲ್ಯ + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ **)ಗಣ.sd, ಗಣ.nb_sd);

    {
        AVFrame_Side_ದತ್ತಾಂಶ *sd = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(
            &ಗಣ.sd, &ಗಣ.nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_SEI_UNREGISTERED,
            ಗಾತ್ರ(int32_t), AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->ದತ್ತಾಂಶ = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ಸ್ಥಿರಾಂಕ AVFrame_Side_ದತ್ತಾಂಶ **)ಗಣ.sd, ಗಣ.nb_sd);

    av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_free(&ಗಣ.sd, &ಗಣ.nb_sd);

    ಹಿಂತಿರುಗಿ 0;
}
