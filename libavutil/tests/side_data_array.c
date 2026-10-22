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

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ "libavutil/frame.c"
#அந்தர்பாவ "libavutil/internal.h"

நிலையான வெறுமை print_entries(மாறிலி AVFrameSideData **sd, மாறிலி முழு nb_sd)
{
    க்கு (முழு i = 0; i < nb_sd; i++) {
        மாறிலி AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        எனில் (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            தொடர்;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

வகைவரை கட்டமைப்பு FrameSideDataSet {
    AVFrameSideData **sd;
    முழு            nb_sd;
} FrameSideDataSet;

முழு முதன்மை(வெறுமை)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               அளவு(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               அளவு(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    க்கு (முழு மதிப்பு = 1; மதிப்பு < 4; மதிப்பு++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            அளவு(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = மதிப்பு;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           அளவு(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            அளவு(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    க்கு (முழு மதிப்பு = 1; மதிப்பு < 4; மதிப்பு++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            அளவு(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = மதிப்பு + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((மாறிலி AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            அளவு(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((மாறிலி AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    திரும்பு 0;
}
