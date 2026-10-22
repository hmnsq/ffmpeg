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

#ضمن <stdio.h>
#ضمن "libavutil/frame.c"
#ضمن "libavutil/internal.h"

ساكن فراغ print_entries(ثابت AVFrameSideData **sd, ثابت صحيح nb_sd)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        ثابت AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        𐡄𐡍 (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            استمر;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

تعريفنوع بنية FrameSideDataSet {
    AVFrameSideData **sd;
    صحيح            nb_sd;
} FrameSideDataSet;

صحيح main(فراغ)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               حجم(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               حجم(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    لكل (صحيح value = 1; value < 4; value++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = value;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           حجم(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            حجم(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    لكل (صحيح value = 1; value < 4; value++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = value + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ثابت AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            حجم(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ثابت AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    أرجع 0;
}
