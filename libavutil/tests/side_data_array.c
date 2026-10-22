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

ಸ್ಥಿರ ಶೂನ್ಯ print_entries(ಧ್ರುವ AVFrameSideData **sd, ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ nb_sd)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < nb_sd; i++) {
        ಧ್ರುವ AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        ಯದಿ (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            ಅನುವರ್ತ;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FrameSideDataSet {
    AVFrameSideData **sd;
    ಪೂರ್ಣಾಙ್ಕ            nb_sd;
} FrameSideDataSet;

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               ಪರಿಮಾಣ(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               ಪರಿಮಾಣ(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ = 1; ಮೌಲ್ಯ < 4; ಮೌಲ್ಯ++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            ಪರಿಮಾಣ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = ಮೌಲ್ಯ;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           ಪರಿಮಾಣ(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            ಪರಿಮಾಣ(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ = 1; ಮೌಲ್ಯ < 4; ಮೌಲ್ಯ++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            ಪರಿಮಾಣ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = ಮೌಲ್ಯ + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ಧ್ರುವ AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            ಪರಿಮಾಣ(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ಧ್ರುವ AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    ಪ್ರತ್ಯಾಗಮ 0;
}
