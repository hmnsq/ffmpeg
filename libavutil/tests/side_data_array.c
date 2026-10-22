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

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "libavutil/frame.c"
#অন্তর্ভাব "libavutil/internal.h"

স্থির শূন্য print_entries(ধ্রুব AVFrameSideData **sd, ধ্রুব পূর্ণাঙ্ক nb_sd)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < nb_sd; i++) {
        ধ্রুব AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        যদি (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            অনুবর্ত;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

প্রকারনির্দেশ সংরচনা FrameSideDataSet {
    AVFrameSideData **sd;
    পূর্ণাঙ্ক            nb_sd;
} FrameSideDataSet;

পূর্ণাঙ্ক main(শূন্য)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               পরিমাণ(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               পরিমাণ(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    প্রতি (পূর্ণাঙ্ক মান = 1; মান < 4; মান++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            পরিমাণ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = মান;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           পরিমাণ(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            পরিমাণ(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    প্রতি (পূর্ণাঙ্ক মান = 1; মান < 4; মান++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            পরিমাণ(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = মান + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ধ্রুব AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            পরিমাণ(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ধ্রুব AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    প্রত্যাগম 0;
}
