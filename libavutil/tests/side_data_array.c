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

#شامل <stdio.h>
#شامل "libavutil/frame.c"
#شامل "libavutil/internal.h"

ایستا تهی print_entries(ثابت AVFrameSideData **sd, ثابت صحیح nb_sd)
{
    برای (صحیح i = 0; i < nb_sd; i++) {
        ثابت AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        اگر (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            ادامه;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

تعریفنوع ساختار FrameSideDataSet {
    AVFrameSideData **sd;
    صحیح            nb_sd;
} FrameSideDataSet;

صحیح اصلی(تهی)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               اندازه(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               اندازه(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    برای (صحیح مقدار = 1; مقدار < 4; مقدار++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            اندازه(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = مقدار;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           اندازه(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            اندازه(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    برای (صحیح مقدار = 1; مقدار < 4; مقدار++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            اندازه(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = مقدار + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ثابت AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            اندازه(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ثابت AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    بازگشت 0;
}
