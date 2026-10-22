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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ "libavutil/frame.c"
#అన్తర్భావ "libavutil/internal.h"

స్థిర శూన్య print_entries(స్థిరరాశి AVFrame_Side_దత్తాంశం **sd, స్థిరరాశి పూర్ణాంకం nb_sd)
{
    కొరకు (పూర్ణాంకం i = 0; i < nb_sd; i++) {
        స్థిరరాశి AVFrame_Side_దత్తాంశం *నమోదు_2 = sd[i];

        రాయి("sd %d (size %zu), %s",
               i, నమోదు_2->కొలత, av_చట్రం_side_దత్తాంశం_name(నమోదు_2->type));

        ఒకవేళ (నమోదు_2->type != AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED) {
            అక్షరం_రాయి('\n');
            కొనసాగు;
        }

        రాయి(": %d\n", *(int32_t *)నమోదు_2->దత్తాంశం);
    }
}

రకనిర్వచనం నిర్మాణం చట్రం_Side_దత్తాంశం_సమితి {
    AVFrame_Side_దత్తాంశం **sd;
    పూర్ణాంకం            nb_sd;
} చట్రం_Side_దత్తాంశం_సమితి;

పూర్ణాంకం ప్రధాన(శూన్య)
{
    చట్రం_Side_దత్తాంశం_సమితి సమితి = { 0 };

    av_assert0(
        av_చట్రం_side_దత్తాంశం_new(&సమితి.sd, &సమితి.nb_sd,
                               AV_చట్రం_దత్తాంశం_CONTENT_LIGHT_LEVEL,
                               పరిమాణం(int64_t), 0));
    av_assert0(
        av_చట్రం_side_దత్తాంశం_new(&సమితి.sd, &సమితి.nb_sd,
                               AV_చట్రం_దత్తాంశం_CONTENT_LIGHT_LEVEL,
                               పరిమాణం(int32_t), AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE));

    // test entries in the middle
    కొరకు (పూర్ణాంకం విలువ = 1; విలువ < 4; విలువ++) {
        AVFrame_Side_దత్తాంశం *sd = av_చట్రం_side_దత్తాంశం_new(
            &సమితి.sd, &సమితి.nb_sd, AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED,
            పరిమాణం(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->దత్తాంశం = విలువ;
    }

    av_assert0(
        av_చట్రం_side_దత్తాంశం_new(
            &సమితి.sd, &సమితి.nb_sd, AV_చట్రం_దత్తాంశం_SPHERICAL,
           పరిమాణం(int64_t), 0));

    av_assert0(
        av_చట్రం_side_దత్తాంశం_new(
            &సమితి.sd, &సమితి.nb_sd, AV_చట్రం_దత్తాంశం_SPHERICAL,
            పరిమాణం(int32_t), AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE));

    // test entries at the end
    కొరకు (పూర్ణాంకం విలువ = 1; విలువ < 4; విలువ++) {
        AVFrame_Side_దత్తాంశం *sd = av_చట్రం_side_దత్తాంశం_new(
            &సమితి.sd, &సమితి.nb_sd, AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED,
            పరిమాణం(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->దత్తాంశం = విలువ + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((స్థిరరాశి AVFrame_Side_దత్తాంశం **)సమితి.sd, సమితి.nb_sd);

    {
        AVFrame_Side_దత్తాంశం *sd = av_చట్రం_side_దత్తాంశం_new(
            &సమితి.sd, &సమితి.nb_sd, AV_చట్రం_దత్తాంశం_SEI_UNREGISTERED,
            పరిమాణం(int32_t), AV_చట్రం_SIDE_దత్తాంశం_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->దత్తాంశం = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((స్థిరరాశి AVFrame_Side_దత్తాంశం **)సమితి.sd, సమితి.nb_sd);

    av_చట్రం_side_దత్తాంశం_free(&సమితి.sd, &సమితి.nb_sd);

    తిరిగి 0;
}
