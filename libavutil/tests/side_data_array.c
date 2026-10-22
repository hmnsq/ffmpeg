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

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ "libavutil/frame.c"
#અન્તર્ભાવ "libavutil/internal.h"

સ્થિર શૂન્ય print_entries(અચલ AVFrameSideData **sd, અચલ પૂર્ણાંક nb_sd)
{
    માટે (પૂર્ણાંક i = 0; i < nb_sd; i++) {
        અચલ AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        જો (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            ચાલુ;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

પ્રકારવ્યાખ્યા સંરચના FrameSideDataSet {
    AVFrameSideData **sd;
    પૂર્ણાંક            nb_sd;
} FrameSideDataSet;

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               કદ(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               કદ(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    માટે (પૂર્ણાંક કિંમત = 1; કિંમત < 4; કિંમત++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            કદ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = કિંમત;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           કદ(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            કદ(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    માટે (પૂર્ણાંક કિંમત = 1; કિંમત < 4; કિંમત++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            કદ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = કિંમત + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((અચલ AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            કદ(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((અચલ AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    પાછા 0;
}
