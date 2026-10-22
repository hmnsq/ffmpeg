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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव "libavutil/frame.c"
#अन्तर्भाव "libavutil/internal.h"

स्थिर शून्य print_entries(ध्रुव AVFrameSideData **sd, ध्रुव पूर्णाङ्क nb_sd)
{
    प्रति (पूर्णाङ्क i = 0; i < nb_sd; i++) {
        ध्रुव AVFrameSideData *entry = sd[i];

        म_लिखो("sd %d (size %zu), %s",
               i, entry->size, av_frame_side_data_name(entry->type));

        यदि (entry->type != AV_FRAME_DATA_SEI_UNREGISTERED) {
            अक्षर_दो('\n');
            अनुवर्त;
        }

        म_लिखो(": %d\n", *(int32_t *)entry->data);
    }
}

प्रकारनिर्देश संरचना FrameSideDataSet {
    AVFrameSideData **sd;
    पूर्णाङ्क            nb_sd;
} FrameSideDataSet;

पूर्णाङ्क main(शून्य)
{
    FrameSideDataSet set = { 0 };

    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               परिमाण(int64_t), 0));
    av_assert0(
        av_frame_side_data_new(&set.sd, &set.nb_sd,
                               AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                               परिमाण(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries in the middle
    प्रति (पूर्णाङ्क मूल्य = 1; मूल्य < 4; मूल्य++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            परिमाण(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = मूल्य;
    }

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
           परिमाण(int64_t), 0));

    av_assert0(
        av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SPHERICAL,
            परिमाण(int32_t), AV_FRAME_SIDE_DATA_FLAG_REPLACE));

    // test entries at the end
    प्रति (पूर्णाङ्क मूल्य = 1; मूल्य < 4; मूल्य++) {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            परिमाण(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->data = मूल्य + 3;
    }

    माला_दो("Initial addition results with duplicates:");
    print_entries((ध्रुव AVFrameSideData **)set.sd, set.nb_sd);

    {
        AVFrameSideData *sd = av_frame_side_data_new(
            &set.sd, &set.nb_sd, AV_FRAME_DATA_SEI_UNREGISTERED,
            परिमाण(int32_t), AV_FRAME_SIDE_DATA_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->data = 1337;
    }

    माला_दो("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ध्रुव AVFrameSideData **)set.sd, set.nb_sd);

    av_frame_side_data_free(&set.sd, &set.nb_sd);

    प्रत्यागम 0;
}
