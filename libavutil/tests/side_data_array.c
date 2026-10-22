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

ساكن فراغ print_entries(ثابت AVFrame_Side_معلومات **sd, ثابت صحيح nb_sd)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        ثابت AVFrame_Side_معلومات *ثبت = sd[i];

        چاپ_کړه("sd %d (size %zu), %s",
               i, ثبت->اندازه, av_چوکاټ_side_معلومات_name(ثبت->type));

        إذا (ثبت->type != AV_چوکاټ_معلومات_SEI_UNREGISTERED) {
            توری_چاپ_کړه('\n');
            استمر;
        }

        چاپ_کړه(": %d\n", *(int32_t *)ثبت->معلومات);
    }
}

تعريفنوع بنية چوکاټ_Side_معلومات_سېټ {
    AVFrame_Side_معلومات **sd;
    صحيح            nb_sd;
} چوکاټ_Side_معلومات_سېټ;

صحيح اصلي(فراغ)
{
    چوکاټ_Side_معلومات_سېټ سېټ = { 0 };

    av_assert0(
        av_چوکاټ_side_معلومات_new(&سېټ.sd, &سېټ.nb_sd,
                               AV_چوکاټ_معلومات_CONTENT_LIGHT_LEVEL,
                               حجم(int64_t), 0));
    av_assert0(
        av_چوکاټ_side_معلومات_new(&سېټ.sd, &سېټ.nb_sd,
                               AV_چوکاټ_معلومات_CONTENT_LIGHT_LEVEL,
                               حجم(int32_t), AV_چوکاټ_SIDE_معلومات_FLAG_REPLACE));

    // test entries in the middle
    لكل (صحيح ارزښت = 1; ارزښت < 4; ارزښت++) {
        AVFrame_Side_معلومات *sd = av_چوکاټ_side_معلومات_new(
            &سېټ.sd, &سېټ.nb_sd, AV_چوکاټ_معلومات_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->معلومات = ارزښت;
    }

    av_assert0(
        av_چوکاټ_side_معلومات_new(
            &سېټ.sd, &سېټ.nb_sd, AV_چوکاټ_معلومات_SPHERICAL,
           حجم(int64_t), 0));

    av_assert0(
        av_چوکاټ_side_معلومات_new(
            &سېټ.sd, &سېټ.nb_sd, AV_چوکاټ_معلومات_SPHERICAL,
            حجم(int32_t), AV_چوکاټ_SIDE_معلومات_FLAG_REPLACE));

    // test entries at the end
    لكل (صحيح ارزښت = 1; ارزښت < 4; ارزښت++) {
        AVFrame_Side_معلومات *sd = av_چوکاټ_side_معلومات_new(
            &سېټ.sd, &سېټ.nb_sd, AV_چوکاټ_معلومات_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->معلومات = ارزښت + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ثابت AVFrame_Side_معلومات **)سېټ.sd, سېټ.nb_sd);

    {
        AVFrame_Side_معلومات *sd = av_چوکاټ_side_معلومات_new(
            &سېټ.sd, &سېټ.nb_sd, AV_چوکاټ_معلومات_SEI_UNREGISTERED,
            حجم(int32_t), AV_چوکاټ_SIDE_معلومات_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->معلومات = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ثابت AVFrame_Side_معلومات **)سېټ.sd, سېټ.nb_sd);

    av_چوکاټ_side_معلومات_free(&سېټ.sd, &سېټ.nb_sd);

    أرجع 0;
}
