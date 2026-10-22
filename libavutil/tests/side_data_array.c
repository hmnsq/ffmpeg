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

#समावेश <stdio.h>
#समावेश "libavutil/frame.c"
#समावेश "libavutil/internal.h"

अटल व्योम print_entries(स्थिर AVFrame_Side_तथ्य **sd, स्थिर पूर्णांक nb_sd)
{
    क्रम (पूर्णांक i = 0; i < nb_sd; i++) {
        स्थिर AVFrame_Side_तथ्य *entry = sd[i];

        म_लिखो("sd %d (size %zu), %s",
               i, entry->आकार, av_frame_side_तथ्य_name(entry->type));

        अगर (entry->type != AV_FRAME_तथ्य_SEI_UNREGISTERED) {
            अक्षर_दो('\n');
            जारी;
        }

        म_लिखो(": %d\n", *(int32_t *)entry->तथ्य);
    }
}

प्रकार काष्ठा Frame_Side_तथ्य_Set {
    AVFrame_Side_तथ्य **sd;
    पूर्णांक            nb_sd;
} Frame_Side_तथ्य_Set;

पूर्णांक मुख्य(व्योम)
{
    Frame_Side_तथ्य_Set set = { 0 };

    av_assert0(
        av_frame_side_तथ्य_new(&set.sd, &set.nb_sd,
                               AV_FRAME_तथ्य_CONTENT_LIGHT_LEVEL,
                               माप(int64_t), 0));
    av_assert0(
        av_frame_side_तथ्य_new(&set.sd, &set.nb_sd,
                               AV_FRAME_तथ्य_CONTENT_LIGHT_LEVEL,
                               माप(int32_t), AV_FRAME_SIDE_तथ्य_FLAG_REPLACE));

    // test entries in the middle
    क्रम (पूर्णांक मूल्य = 1; मूल्य < 4; मूल्य++) {
        AVFrame_Side_तथ्य *sd = av_frame_side_तथ्य_new(
            &set.sd, &set.nb_sd, AV_FRAME_तथ्य_SEI_UNREGISTERED,
            माप(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->तथ्य = मूल्य;
    }

    av_assert0(
        av_frame_side_तथ्य_new(
            &set.sd, &set.nb_sd, AV_FRAME_तथ्य_SPHERICAL,
           माप(int64_t), 0));

    av_assert0(
        av_frame_side_तथ्य_new(
            &set.sd, &set.nb_sd, AV_FRAME_तथ्य_SPHERICAL,
            माप(int32_t), AV_FRAME_SIDE_तथ्य_FLAG_REPLACE));

    // test entries at the end
    क्रम (पूर्णांक मूल्य = 1; मूल्य < 4; मूल्य++) {
        AVFrame_Side_तथ्य *sd = av_frame_side_तथ्य_new(
            &set.sd, &set.nb_sd, AV_FRAME_तथ्य_SEI_UNREGISTERED,
            माप(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->तथ्य = मूल्य + 3;
    }

    माला_दो("Initial addition results with duplicates:");
    print_entries((स्थिर AVFrame_Side_तथ्य **)set.sd, set.nb_sd);

    {
        AVFrame_Side_तथ्य *sd = av_frame_side_तथ्य_new(
            &set.sd, &set.nb_sd, AV_FRAME_तथ्य_SEI_UNREGISTERED,
            माप(int32_t), AV_FRAME_SIDE_तथ्य_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->तथ्य = 1337;
    }

    माला_दो("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((स्थिर AVFrame_Side_तथ्य **)set.sd, set.nb_sd);

    av_frame_side_तथ्य_free(&set.sd, &set.nb_sd);

    वापस 0;
}
