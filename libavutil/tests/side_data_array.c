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

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ "libavutil/frame.c"
#അന്തര്ഭാവ "libavutil/internal.h"

സ്ഥിതം ശൂന്യം print_entries(സ്ഥിരം AVFrameSideData **sd, സ്ഥിരം പൂർണ്ണസംഖ്യ nb_sd)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < nb_sd; i++) {
        സ്ഥിരം AVFrameSideData *entry = sd[i];

        printf("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        എങ്കിൽ (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            putchar('\n');
            തുടരുക;
        }

        printf(": %d\n", *(int32_t *)entry->data);
    }
}

തരനിർവചനം ഘടന FrameSideDataSet {
    AVFrameSideData **sd;
    പൂർണ്ണസംഖ്യ            nb_sd;
} FrameSideDataSet;

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               വലുപ്പം(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               വലുപ്പം(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    വേണ്ടി (പൂർണ്ണസംഖ്യ മൂല്യം = 1; മൂല്യം < 4; മൂല്യം++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            വലുപ്പം(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = മൂല്യം;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           വലുപ്പം(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            വലുപ്പം(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    വേണ്ടി (പൂർണ്ണസംഖ്യ മൂല്യം = 1; മൂല്യം < 4; മൂല്യം++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            വലുപ്പം(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = മൂല്യം + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((സ്ഥിരം AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            വലുപ്പം(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((സ്ഥിരം AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    തിരികെ 0;
}
