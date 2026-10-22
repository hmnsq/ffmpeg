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

स्थिर शून्य print_entries(ध्रुव AVFrame_Side_दत्त **sd, ध्रुव पूर्णाङ्क nb_sd)
{
    प्रति (पूर्णाङ्क i = 0; i < nb_sd; i++) {
        ध्रुव AVFrame_Side_दत्त *प्रविष्टिः = sd[i];

        प्रारूप_लिख("sd %d (size %zu), %s",
               i, प्रविष्टिः->आकार, av_frame_side_दत्त_name(प्रविष्टिः->type));

        यदि (प्रविष्टिः->type != AV_FRAME_दत्त_SEI_UNREGISTERED) {
            अक्षरं_लिख('\n');
            अनुवर्त;
        }

        प्रारूप_लिख(": %d\n", *(int32_t *)प्रविष्टिः->दत्त);
    }
}

प्रकारनिर्देश संरचना Frame_Side_दत्त_समुच्चयः {
    AVFrame_Side_दत्त **sd;
    पूर्णाङ्क            nb_sd;
} Frame_Side_दत्त_समुच्चयः;

पूर्णाङ्क मुख्यम्(शून्य)
{
    Frame_Side_दत्त_समुच्चयः समुच्चयः = { 0 };

    av_assert0(
        av_frame_side_दत्त_new(&समुच्चयः.sd, &समुच्चयः.nb_sd,
                               AV_FRAME_दत्त_CONTENT_LIGHT_LEVEL,
                               परिमाण(int64_t), 0));
    av_assert0(
        av_frame_side_दत्त_new(&समुच्चयः.sd, &समुच्चयः.nb_sd,
                               AV_FRAME_दत्त_CONTENT_LIGHT_LEVEL,
                               परिमाण(int32_t), AV_FRAME_SIDE_दत्त_FLAG_REPLACE));

    // test entries in the middle
    प्रति (पूर्णाङ्क मानम् = 1; मानम् < 4; मानम्++) {
        AVFrame_Side_दत्त *sd = av_frame_side_दत्त_new(
            &समुच्चयः.sd, &समुच्चयः.nb_sd, AV_FRAME_दत्त_SEI_UNREGISTERED,
            परिमाण(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->दत्त = मानम्;
    }

    av_assert0(
        av_frame_side_दत्त_new(
            &समुच्चयः.sd, &समुच्चयः.nb_sd, AV_FRAME_दत्त_SPHERICAL,
           परिमाण(int64_t), 0));

    av_assert0(
        av_frame_side_दत्त_new(
            &समुच्चयः.sd, &समुच्चयः.nb_sd, AV_FRAME_दत्त_SPHERICAL,
            परिमाण(int32_t), AV_FRAME_SIDE_दत्त_FLAG_REPLACE));

    // test entries at the end
    प्रति (पूर्णाङ्क मानम् = 1; मानम् < 4; मानम्++) {
        AVFrame_Side_दत्त *sd = av_frame_side_दत्त_new(
            &समुच्चयः.sd, &समुच्चयः.nb_sd, AV_FRAME_दत्त_SEI_UNREGISTERED,
            परिमाण(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->दत्त = मानम् + 3;
    }

    पङ्क्तिं_लिख("Initial addition results with duplicates:");
    print_entries((ध्रुव AVFrame_Side_दत्त **)समुच्चयः.sd, समुच्चयः.nb_sd);

    {
        AVFrame_Side_दत्त *sd = av_frame_side_दत्त_new(
            &समुच्चयः.sd, &समुच्चयः.nb_sd, AV_FRAME_दत्त_SEI_UNREGISTERED,
            परिमाण(int32_t), AV_FRAME_SIDE_दत्त_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->दत्त = 1337;
    }

    पङ्क्तिं_लिख("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ध्रुव AVFrame_Side_दत्त **)समुच्चयः.sd, समुच्चयः.nb_sd);

    av_frame_side_दत्त_free(&समुच्चयः.sd, &समुच्चयः.nb_sd);

    प्रत्यागम 0;
}
