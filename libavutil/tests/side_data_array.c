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

স্থির শূন্য print_entries(ধ্রুবক AVFrame_Side_তথ্য **sd, ধ্রুবক পূর্ণসংখ্যা nb_sd)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < nb_sd; i++) {
        ধ্রুবক AVFrame_Side_তথ্য *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->আকার_2, av_frame_side_তথ্য_name(entry->type));

        যদি (entry->type != AV_FRAME_তথ্য_SEI_UNREGISTERED) {
            putchar('\n');
            চালু;
        }

        printf(": %d\n", *(int32_t *)entry->তথ্য);
    }
}

প্রকারলেখ কাঠামো Frame_Side_তথ্য_Set {
    AVFrame_Side_তথ্য **sd;
    পূর্ণসংখ্যা            nb_sd;
} Frame_Side_তথ্য_Set;

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    Frame_Side_তথ্য_Set set = { 0 };

    av_assert0(
        av_frame_side_তথ্য_new(&set.sd, &set.nb_sd,
                               AV_FRAME_তথ্য_CONTENT_LIGHT_LEVEL,
                               আকার(int64_t), 0));
    av_assert0(
        av_frame_side_তথ্য_new(&set.sd, &set.nb_sd,
                               AV_FRAME_তথ্য_CONTENT_LIGHT_LEVEL,
                               আকার(int32_t), AV_FRAME_SIDE_তথ্য_FLAG_REPLACE));

    // test entries in the middle
    জন্য (পূর্ণসংখ্যা মান = 1; মান < 4; মান++) {
        AVFrame_Side_তথ্য *sd = av_frame_side_তথ্য_new(
            &set.sd, &set.nb_sd, AV_FRAME_তথ্য_SEI_UNREGISTERED,
            আকার(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->তথ্য = মান;
    }

    av_assert0(
        av_frame_side_তথ্য_new(
            &set.sd, &set.nb_sd, AV_FRAME_তথ্য_SPHERICAL,
           আকার(int64_t), 0));

    av_assert0(
        av_frame_side_তথ্য_new(
            &set.sd, &set.nb_sd, AV_FRAME_তথ্য_SPHERICAL,
            আকার(int32_t), AV_FRAME_SIDE_তথ্য_FLAG_REPLACE));

    // test entries at the end
    জন্য (পূর্ণসংখ্যা মান = 1; মান < 4; মান++) {
        AVFrame_Side_তথ্য *sd = av_frame_side_তথ্য_new(
            &set.sd, &set.nb_sd, AV_FRAME_তথ্য_SEI_UNREGISTERED,
            আকার(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->তথ্য = মান + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ধ্রুবক AVFrame_Side_তথ্য **)set.sd, set.nb_sd);

    {
        AVFrame_Side_তথ্য *sd = av_frame_side_তথ্য_new(
            &set.sd, &set.nb_sd, AV_FRAME_তথ্য_SEI_UNREGISTERED,
            আকার(int32_t), AV_FRAME_SIDE_তথ্য_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->তথ্য = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ধ্রুবক AVFrame_Side_তথ্য **)set.sd, set.nb_sd);

    av_frame_side_তথ্য_free(&set.sd, &set.nb_sd);

    ফেরত 0;
}
