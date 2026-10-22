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

ساكن فراغ print_entries(ثابت AVFrame_Side_انکڑے **sd, ثابت صحيح nb_sd)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        ثابت AVFrame_Side_انکڑے *اندراج = sd[i];

        لکھو("sd %d (size %zu), %s",
               i, اندراج->ناپ, av_چوکھٹا_side_انکڑے_name(اندراج->type));

        إذا (اندراج->type != AV_چوکھٹا_انکڑے_SEI_UNREGISTERED) {
            حرف_لکھو('\n');
            استمر;
        }

        لکھو(": %d\n", *(int32_t *)اندراج->انکڑے);
    }
}

تعريفنوع بنية چوکھٹا_Side_انکڑے_سیٹ {
    AVFrame_Side_انکڑے **sd;
    صحيح            nb_sd;
} چوکھٹا_Side_انکڑے_سیٹ;

صحيح مکھ(فراغ)
{
    چوکھٹا_Side_انکڑے_سیٹ سیٹ = { 0 };

    av_assert0(
        av_چوکھٹا_side_انکڑے_new(&سیٹ.sd, &سیٹ.nb_sd,
                               AV_چوکھٹا_انکڑے_CONTENT_LIGHT_LEVEL,
                               حجم(int64_t), 0));
    av_assert0(
        av_چوکھٹا_side_انکڑے_new(&سیٹ.sd, &سیٹ.nb_sd,
                               AV_چوکھٹا_انکڑے_CONTENT_LIGHT_LEVEL,
                               حجم(int32_t), AV_چوکھٹا_SIDE_انکڑے_FLAG_REPLACE));

    // test entries in the middle
    لكل (صحيح قدر = 1; قدر < 4; قدر++) {
        AVFrame_Side_انکڑے *sd = av_چوکھٹا_side_انکڑے_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_انکڑے_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->انکڑے = قدر;
    }

    av_assert0(
        av_چوکھٹا_side_انکڑے_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_انکڑے_SPHERICAL,
           حجم(int64_t), 0));

    av_assert0(
        av_چوکھٹا_side_انکڑے_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_انکڑے_SPHERICAL,
            حجم(int32_t), AV_چوکھٹا_SIDE_انکڑے_FLAG_REPLACE));

    // test entries at the end
    لكل (صحيح قدر = 1; قدر < 4; قدر++) {
        AVFrame_Side_انکڑے *sd = av_چوکھٹا_side_انکڑے_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_انکڑے_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->انکڑے = قدر + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ثابت AVFrame_Side_انکڑے **)سیٹ.sd, سیٹ.nb_sd);

    {
        AVFrame_Side_انکڑے *sd = av_چوکھٹا_side_انکڑے_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_انکڑے_SEI_UNREGISTERED,
            حجم(int32_t), AV_چوکھٹا_SIDE_انکڑے_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->انکڑے = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ثابت AVFrame_Side_انکڑے **)سیٹ.sd, سیٹ.nb_sd);

    av_چوکھٹا_side_انکڑے_free(&سیٹ.sd, &سیٹ.nb_sd);

    أرجع 0;
}
