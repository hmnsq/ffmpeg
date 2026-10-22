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

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ "libavutil/frame.c"
#ଅନ୍ତର୍ଭାଵ "libavutil/internal.h"

ସ୍ଥିର ଶୂନ୍ୟ print_entries(ଅଚଳ AVFrameSideData **sd, ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sd)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < nb_sd; i++) {
        ଅଚଳ AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        ଯଦି (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            ଜାରି;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FrameSideDataSet {
    AVFrameSideData **sd;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା            nb_sd;
} FrameSideDataSet;

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               ଆକାର(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               ଆକାର(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = 1; ମୂଲ୍ୟ < 4; ମୂଲ୍ୟ++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            ଆକାର(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = ମୂଲ୍ୟ;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           ଆକାର(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            ଆକାର(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = 1; ମୂଲ୍ୟ < 4; ମୂଲ୍ୟ++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            ଆକାର(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = ମୂଲ୍ୟ + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ଅଚଳ AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            ଆକାର(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ଅଚଳ AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    ଫେରନ୍ତୁ 0;
}
