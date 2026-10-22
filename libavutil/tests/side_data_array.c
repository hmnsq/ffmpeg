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

ساکن خالی print_entries(ثابت AVFrame_Side_ڈیٹا **sd, ثابت صحیح nb_sd)
{
    برائے (صحیح i = 0; i < nb_sd; i++) {
        ثابت AVFrame_Side_ڈیٹا *اندراج_2 = sd[i];

        لکھو("sd %d (size %zu), %s",
               i, اندراج_2->سائز, av_چوکھٹا_side_ڈیٹا_name(اندراج_2->type));

        اگر (اندراج_2->type != AV_چوکھٹا_ڈیٹا_SEI_UNREGISTERED) {
            حرف_لکھو('\n');
            جاری;
        }

        لکھو(": %d\n", *(int32_t *)اندراج_2->ڈیٹا);
    }
}

قسمتعریف ساخت چوکھٹا_Side_ڈیٹا_سیٹ {
    AVFrame_Side_ڈیٹا **sd;
    صحیح            nb_sd;
} چوکھٹا_Side_ڈیٹا_سیٹ;

صحیح مین(خالی)
{
    چوکھٹا_Side_ڈیٹا_سیٹ سیٹ = { 0 };

    av_assert0(
        av_چوکھٹا_side_ڈیٹا_new(&سیٹ.sd, &سیٹ.nb_sd,
                               AV_چوکھٹا_ڈیٹا_CONTENT_LIGHT_LEVEL,
                               حجم(int64_t), 0));
    av_assert0(
        av_چوکھٹا_side_ڈیٹا_new(&سیٹ.sd, &سیٹ.nb_sd,
                               AV_چوکھٹا_ڈیٹا_CONTENT_LIGHT_LEVEL,
                               حجم(int32_t), AV_چوکھٹا_SIDE_ڈیٹا_FLAG_REPLACE));

    // test entries in the middle
    برائے (صحیح قدر = 1; قدر < 4; قدر++) {
        AVFrame_Side_ڈیٹا *sd = av_چوکھٹا_side_ڈیٹا_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_ڈیٹا_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->ڈیٹا = قدر;
    }

    av_assert0(
        av_چوکھٹا_side_ڈیٹا_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_ڈیٹا_SPHERICAL,
           حجم(int64_t), 0));

    av_assert0(
        av_چوکھٹا_side_ڈیٹا_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_ڈیٹا_SPHERICAL,
            حجم(int32_t), AV_چوکھٹا_SIDE_ڈیٹا_FLAG_REPLACE));

    // test entries at the end
    برائے (صحیح قدر = 1; قدر < 4; قدر++) {
        AVFrame_Side_ڈیٹا *sd = av_چوکھٹا_side_ڈیٹا_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_ڈیٹا_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->ڈیٹا = قدر + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ثابت AVFrame_Side_ڈیٹا **)سیٹ.sd, سیٹ.nb_sd);

    {
        AVFrame_Side_ڈیٹا *sd = av_چوکھٹا_side_ڈیٹا_new(
            &سیٹ.sd, &سیٹ.nb_sd, AV_چوکھٹا_ڈیٹا_SEI_UNREGISTERED,
            حجم(int32_t), AV_چوکھٹا_SIDE_ڈیٹا_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->ڈیٹا = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ثابت AVFrame_Side_ڈیٹا **)سیٹ.sd, سیٹ.nb_sd);

    av_چوکھٹا_side_ڈیٹا_free(&سیٹ.sd, &سیٹ.nb_sd);

    واپس 0;
}
