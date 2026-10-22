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

ساكن فراغ print_entries(ثابت AVFrame_Side_داده **sd, ثابت صحيح nb_sd)
{
    لكل (صحيح i = 0; i < nb_sd; i++) {
        ثابت AVFrame_Side_داده *مدخل = sd[i];

        چاپ_کن("sd %d (size %zu), %s",
               i, مدخل->اندازه, av_قاب_side_داده_name(مدخل->type));

        إذا (مدخل->type != AV_قاب_داده_SEI_UNREGISTERED) {
            حرف_چاپ_کن('\n');
            استمر;
        }

        چاپ_کن(": %d\n", *(int32_t *)مدخل->داده);
    }
}

تعريفنوع بنية قاب_Side_داده_مجموعه {
    AVFrame_Side_داده **sd;
    صحيح            nb_sd;
} قاب_Side_داده_مجموعه;

صحيح اصلی(فراغ)
{
    قاب_Side_داده_مجموعه مجموعه = { 0 };

    av_assert0(
        av_قاب_side_داده_new(&مجموعه.sd, &مجموعه.nb_sd,
                               AV_قاب_داده_CONTENT_LIGHT_LEVEL,
                               حجم(int64_t), 0));
    av_assert0(
        av_قاب_side_داده_new(&مجموعه.sd, &مجموعه.nb_sd,
                               AV_قاب_داده_CONTENT_LIGHT_LEVEL,
                               حجم(int32_t), AV_قاب_SIDE_داده_FLAG_REPLACE));

    // test entries in the middle
    لكل (صحيح مقدار = 1; مقدار < 4; مقدار++) {
        AVFrame_Side_داده *sd = av_قاب_side_داده_new(
            &مجموعه.sd, &مجموعه.nb_sd, AV_قاب_داده_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->داده = مقدار;
    }

    av_assert0(
        av_قاب_side_داده_new(
            &مجموعه.sd, &مجموعه.nb_sd, AV_قاب_داده_SPHERICAL,
           حجم(int64_t), 0));

    av_assert0(
        av_قاب_side_داده_new(
            &مجموعه.sd, &مجموعه.nb_sd, AV_قاب_داده_SPHERICAL,
            حجم(int32_t), AV_قاب_SIDE_داده_FLAG_REPLACE));

    // test entries at the end
    لكل (صحيح مقدار = 1; مقدار < 4; مقدار++) {
        AVFrame_Side_داده *sd = av_قاب_side_داده_new(
            &مجموعه.sd, &مجموعه.nb_sd, AV_قاب_داده_SEI_UNREGISTERED,
            حجم(int32_t), 0);

        av_assert0(sd);

        *(int32_t *)sd->داده = مقدار + 3;
    }

    puts("Initial addition results with duplicates:");
    print_entries((ثابت AVFrame_Side_داده **)مجموعه.sd, مجموعه.nb_sd);

    {
        AVFrame_Side_داده *sd = av_قاب_side_داده_new(
            &مجموعه.sd, &مجموعه.nb_sd, AV_قاب_داده_SEI_UNREGISTERED,
            حجم(int32_t), AV_قاب_SIDE_داده_FLAG_UNIQUE);

        av_assert0(sd);

        *(int32_t *)sd->داده = 1337;
    }

    puts("\nFinal state after a single 'no-duplicates' addition:");
    print_entries((ثابت AVFrame_Side_داده **)مجموعه.sd, مجموعه.nb_sd);

    av_قاب_side_داده_free(&مجموعه.sd, &مجموعه.nb_sd);

    أرجع 0;
}
